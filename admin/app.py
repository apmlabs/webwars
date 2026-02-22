from flask import Flask, jsonify, send_from_directory
from apscheduler.schedulers.background import BackgroundScheduler
import subprocess, sqlite3, time, json, os, re, requests
from collections import defaultdict
from datetime import datetime, timezone

# Load .env file if present
_env_path = os.path.join(os.path.dirname(__file__), '.env')
if os.path.exists(_env_path):
    with open(_env_path) as f:
        for line in f:
            line = line.strip()
            if line and not line.startswith('#') and '=' in line:
                k, v = line.split('=', 1)
                os.environ.setdefault(k.strip(), v.strip())

app = Flask(__name__)
DB_PATH = os.path.join(os.path.dirname(__file__), 'webwars_admin.db')
SSH_KEY = os.environ.get('ADMIN_SSH_KEY', os.path.expanduser('~/.ssh/webwars-prod.pem'))
PROD_HOST = os.environ.get('ADMIN_PROD_HOST', 'ubuntu@localhost')
DEV_IP = os.environ.get('ADMIN_DEV_IP', '')
SSH_OPTS = f'-i {SSH_KEY} -o ConnectTimeout=5 -o StrictHostKeyChecking=no'
GEOIP_CACHE = {}  # ip -> {lat, lon, city, country, isp}
PORT = 5052

def get_db():
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    conn = get_db()
    conn.executescript('''
        CREATE TABLE IF NOT EXISTS visitors (
            id INTEGER PRIMARY KEY,
            ip TEXT NOT NULL,
            page TEXT,
            user_agent TEXT,
            timestamp INTEGER NOT NULL,
            lat REAL, lon REAL, city TEXT, country TEXT, isp TEXT
        );
        CREATE TABLE IF NOT EXISTS snapshots (
            id INTEGER PRIMARY KEY,
            timestamp INTEGER NOT NULL,
            ws_connections INTEGER DEFAULT 0,
            hw_connections INTEGER DEFAULT 0,
            active_visitors INTEGER DEFAULT 0
        );
        CREATE INDEX IF NOT EXISTS idx_visitors_ts ON visitors(timestamp);
        CREATE INDEX IF NOT EXISTS idx_visitors_ip ON visitors(ip);
        CREATE INDEX IF NOT EXISTS idx_snapshots_ts ON snapshots(timestamp);
    ''')
    conn.close()

def ssh_cmd(cmd):
    try:
        r = subprocess.run(f'ssh {SSH_OPTS} {PROD_HOST} {repr(cmd)}',
                           shell=True, capture_output=True, text=True, timeout=10)
        return r.stdout.strip()
    except:
        return ''

def geolocate(ip):
    if ip in GEOIP_CACHE:
        return GEOIP_CACHE[ip]
    # Skip private/local IPs
    if ip.startswith(('10.', '172.', '192.168.', '127.', '::1', 'fe80')):
        return None
    try:
        r = requests.get(f'http://ip-api.com/json/{ip}?fields=status,lat,lon,city,country,isp', timeout=3)
        d = r.json()
        if d.get('status') == 'success':
            geo = {k: d[k] for k in ('lat', 'lon', 'city', 'country', 'isp')}
            GEOIP_CACHE[ip] = geo
            return geo
    except:
        pass
    return None

BOT_PATTERNS = ('bot','crawler','spider','claudebot','gptbot','bytespider','l9scan','leakix',
    'censys','shodan','zgrab','masscan','nmap','nuclei','nikto','dirbuster','gobuster',
    'wfuzz','sqlmap','scan','go-http','httpx','recordedfuture','headlesschrome',
    'python-requests','curl/','wget/','libwww','java/','perl','ruby','php/')
PROBE_PATHS = ('/.well-known','/.env','/.git','/wp-','/admin','/cgi-bin','/boaform',
    '/server','/actuator','/solr','/vendor','/config','/debug','/shell','/owa',
    '/remote','/login','/telescope','/api/management','/wordpress','/_next',
    '/robots.txt','/sitemap','/xmlrpc','/favicon.ico','/favicon.png',
    '/css/support_parent','/js/lkk_','/js/twint','/@vite','/.vscode')
FAKE_UAS = ('iPhone13,2; U; CPU iPhone OS 14_0','Nexus 5 Build/MRA',
    'Windows NT 6.1; WOW64; Trident/7.0; AS','Android 6.0; Nexus 5')

CLOUD_ISP_PATTERNS = ('amazon','aws','google llc','google cloud','microsoft','digitalocean',
    'ovh','hetzner','linode','vultr','oracle','alibaba','tencent','cloudflare','akamai',
    'fastly','pfcloud','leaseweb','contabo','scaleway','upcloud','kamatera','choopa',
    'hostroyale','egihosting','oculus networks','logicweb','m247','syn ltd',
    'onyphe','censys','hostinger','geekyworks','wirels connect',
    'applied computational','acuit','recordedfuture','netcup','cyber data',
    'pavlov media','stark industries','datacamp','zscaler')

HIDDEN_IPS = {'90.174.10.182'}  # dev
_HIDDEN_SQL = ','.join(f"'{ip}'" for ip in HIDDEN_IPS)

def is_cloud_ip(isp):
    if not isp: return True  # unknown ISP = suspicious
    return any(p in isp.lower() for p in CLOUD_ISP_PATTERNS)

def is_bot(ip, path, ua, status):
    if ip == DEV_IP: return True  # our dev server
    ua_lower = ua.lower()
    if any(b in ua_lower for b in BOT_PATTERNS): return True
    if any(path.startswith(p) for p in PROBE_PATHS): return True
    if any(f in ua for f in FAKE_UAS): return True
    if ua == '-' or len(ua) < 10: return True
    if status >= 400: return True
    return False

def parse_nginx_log(line):
    m = re.match(r'(\S+) .+? \[(.+?)\] "(\S+) (\S+) .+?" (\d+) \d+ ".+?" "(.+?)"', line)
    if not m: return None
    ip, ts_str, method, path, status, ua = m.groups()
    status = int(status)
    if is_bot(ip, path, ua, status): return None
    try:
        ts = int(datetime.strptime(ts_str, '%d/%b/%Y:%H:%M:%S %z').timestamp())
    except:
        ts = int(time.time())
    return {'ip': ip, 'path': path, 'ua': ua, 'status': status, 'ts': ts}

def poll_prod():
    """Fetch latest data from prod server."""
    now = int(time.time())
    conn = get_db()

    # 1. Get last processed timestamp
    row = conn.execute('SELECT MAX(timestamp) FROM visitors').fetchone()
    last_ts = row[0] or 0

    # 2. Fetch nginx access log (full on first run, tail on subsequent)
    if last_ts == 0:
        log_lines = ssh_cmd('cat /var/log/nginx/access.log 2>/dev/null')
    else:
        log_lines = ssh_cmd('tail -200 /var/log/nginx/access.log 2>/dev/null')
    new_visitors = []
    for line in log_lines.split('\n'):
        if not line.strip():
            continue
        parsed = parse_nginx_log(line)
        if not parsed or parsed['ts'] <= last_ts:
            continue
        new_visitors.append(parsed)

    # Geolocate new IPs + any previously ungeolocated ones
    ungeo = conn.execute('SELECT DISTINCT ip FROM visitors WHERE lat IS NULL').fetchall()
    ips_to_geo = (set(v['ip'] for v in new_visitors) | set(r['ip'] for r in ungeo)) - set(GEOIP_CACHE.keys())
    for ip in list(ips_to_geo)[:40]:  # max 40 per poll (stay under 45/min)
        geolocate(ip)
        time.sleep(0.08)

    for v in new_visitors:
        geo = GEOIP_CACHE.get(v['ip'], {})
        conn.execute(
            'INSERT INTO visitors (ip, page, user_agent, timestamp, lat, lon, city, country, isp) VALUES (?,?,?,?,?,?,?,?,?)',
            (v['ip'], v['path'], v['ua'], v['ts'],
             geo.get('lat'), geo.get('lon'), geo.get('city'), geo.get('country'), geo.get('isp'))
        )

    # Backfill geo for old rows
    for ip, geo in GEOIP_CACHE.items():
        conn.execute('UPDATE visitors SET lat=?, lon=?, city=?, country=?, isp=? WHERE ip=? AND lat IS NULL',
                     (geo['lat'], geo['lon'], geo['city'], geo['country'], geo['isp'], ip))

    # 3. Count active WS and HW connections
    ws_out = ssh_cmd('ss -tnp state established | grep -c ":8080" || echo 0')
    hw_out = ssh_cmd('ss -tnp state established | grep -c ":46631" || echo 0')
    ws_conns = int(ws_out) if ws_out.isdigit() else 0
    hw_conns = int(hw_out) if hw_out.isdigit() else 0

    # Active visitors = unique IPs in last 5 min
    five_min_ago = now - 300
    active = conn.execute('SELECT COUNT(DISTINCT ip) FROM visitors WHERE timestamp > ?', (five_min_ago,)).fetchone()[0]

    conn.execute('INSERT INTO snapshots (timestamp, ws_connections, hw_connections, active_visitors) VALUES (?,?,?,?)',
                 (now, ws_conns, hw_conns, active))
    conn.commit()
    conn.close()
    print(f'[{datetime.now(timezone.utc).strftime("%H:%M:%S")}] Poll: {len(new_visitors)} new visitors, {ws_conns} WS, {hw_conns} HW, {active} active')

# --- API Routes ---

@app.route('/')
def index():
    return send_from_directory(os.path.dirname(__file__), 'index.html')

@app.route('/api/live')
def api_live():
    """Current live stats."""
    conn = get_db()
    now = int(time.time())
    snap = conn.execute('SELECT * FROM snapshots ORDER BY timestamp DESC LIMIT 1').fetchone()
    total_sessions = conn.execute(f'SELECT COUNT(*) FROM visitors WHERE ip NOT IN ({_HIDDEN_SQL})').fetchone()[0]

    # Human = not from cloud ISP
    all_visitors = conn.execute(f'SELECT DISTINCT ip, isp FROM visitors WHERE isp IS NOT NULL AND ip NOT IN ({_HIDDEN_SQL})').fetchall()
    humans = sum(1 for v in all_visitors if not is_cloud_ip(v['isp']))
    played = conn.execute(f"SELECT COUNT(DISTINCT ip) FROM visitors WHERE page LIKE '%%.data' AND ip NOT IN ({_HIDDEN_SQL})").fetchone()[0]
    active_5m = conn.execute(f'SELECT COUNT(DISTINCT ip) FROM visitors WHERE timestamp > ? AND ip NOT IN ({_HIDDEN_SQL})', (now - 300,)).fetchone()[0]

    pages = conn.execute(f'''
        SELECT page, isp, COUNT(*) as c FROM visitors WHERE timestamp > ? AND ip NOT IN ({_HIDDEN_SQL}) GROUP BY page, isp ORDER BY c DESC
    ''', (now - 7 * 86400,)).fetchall()

    # Aggregate per page with human/bot split
    page_stats = {}
    for r in pages:
        p = r['page']
        if p not in page_stats:
            page_stats[p] = {'total': 0, 'human': 0}
        page_stats[p]['total'] += r['c']
        if not is_cloud_ip(r['isp']):
            page_stats[p]['human'] += r['c']

    conn.close()
    return jsonify({
        'ws_connections': snap['ws_connections'] if snap else 0,
        'hw_connections': snap['hw_connections'] if snap else 0,
        'active_5m': active_5m,
        'humans': humans,
        'played': played,
        'total_sessions': total_sessions,
        'pages': page_stats,
        'timestamp': snap['timestamp'] if snap else now
    })

@app.route('/api/map')
def api_map():
    """All geolocated visitors for the map."""
    conn = get_db()
    now = int(time.time())
    rows = conn.execute(f'''
        SELECT ip, lat, lon, city, country, isp, MAX(timestamp) as last_seen, COUNT(*) as visits,
               GROUP_CONCAT(DISTINCT page) as pages
        FROM visitors WHERE lat IS NOT NULL AND ip NOT IN ({_HIDDEN_SQL})
        GROUP BY ip ORDER BY last_seen DESC LIMIT 500
    ''').fetchall()
    conn.close()
    return jsonify([{
        'ip': r['ip'], 'lat': r['lat'], 'lon': r['lon'],
        'city': r['city'], 'country': r['country'], 'isp': r['isp'],
        'last_seen': r['last_seen'], 'visits': r['visits'], 'pages': r['pages'],
        'active': r['last_seen'] > now - 300,
        'played': any(p in (r['pages'] or '') for p in ('.data', '.wasm')),
        'cloud': is_cloud_ip(r['isp'])
    } for r in rows])

@app.route('/api/history')
def api_history():
    """Connection history for charts."""
    conn = get_db()
    now = int(time.time())
    # Last 24h of snapshots, one per minute
    snaps = conn.execute('''
        SELECT timestamp, ws_connections, hw_connections, active_visitors
        FROM snapshots WHERE timestamp > ? ORDER BY timestamp
    ''', (now - 86400,)).fetchall()

    # Hourly visitor counts for last 7 days
    hourly = conn.execute(f'''
        SELECT (timestamp / 3600) * 3600 as hour, COUNT(DISTINCT ip) as visitors, COUNT(*) as pageviews
        FROM visitors WHERE timestamp > ? AND ip NOT IN ({_HIDDEN_SQL}) GROUP BY hour ORDER BY hour
    ''', (now - 7 * 86400,)).fetchall()

    conn.close()
    return jsonify({
        'snapshots': [dict(r) for r in snaps],
        'hourly': [dict(r) for r in hourly]
    })

@app.route('/api/visitors')
def api_visitors():
    """Recent visitor log."""
    conn = get_db()
    rows = conn.execute(f'''
        SELECT ip, page, city, country, isp, timestamp, user_agent
        FROM visitors WHERE ip NOT IN ({_HIDDEN_SQL}) ORDER BY timestamp DESC LIMIT 100
    ''').fetchall()
    conn.close()
    return jsonify([{**dict(r), 'cloud': is_cloud_ip(r['isp'])} for r in rows])

if __name__ == '__main__':
    init_db()
    poll_prod()  # initial poll
    scheduler = BackgroundScheduler()
    scheduler.add_job(poll_prod, 'interval', seconds=30)
    scheduler.start()
    print(f'WebWars Admin Panel on http://localhost:{PORT}')
    app.run(host='0.0.0.0', port=PORT, debug=False)
