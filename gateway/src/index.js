const WebSocket = require('ws');
const net = require('net');

const WS_PORT = process.env.WS_PORT || 8080;
const HW_HOST = process.env.HW_HOST || 'localhost';
const HW_PORT = process.env.HW_PORT || 46631;

const wss = new WebSocket.Server({ port: WS_PORT });

console.log(`WebWars Gateway listening on ws://localhost:${WS_PORT}`);
console.log(`Forwarding to Hedgewars server at ${HW_HOST}:${HW_PORT}`);

wss.on('connection', (ws, req) => {
  const clientIp = req.socket.remoteAddress;
  console.log(`[${clientIp}] Client connected`);

  const tcpClient = net.connect(HW_PORT, HW_HOST, () => {
    console.log(`[${clientIp}] Connected to Hedgewars server`);
  });

  // Buffer for incomplete TCP messages
  let tcpBuf = '';

  // WebSocket → TCP: browser sends JSON arrays like ["NICK","player1"]
  // Convert to HW protocol: "NICK\nplayer1\n\n"
  ws.on('message', (data) => {
    try {
      const msg = JSON.parse(data);
      if (Array.isArray(msg)) {
        const cmd = msg[0];
        if (cmd !== 'PONG') console.log(`[${clientIp}] WS→HW: ${cmd}${msg.length>1?' '+msg.slice(1,3).join(' '):''}${msg.length>3?' ...':''}`)
        tcpClient.write(msg.join('\n') + '\n\n');
      }
    } catch (err) {
      console.error(`[${clientIp}] Bad WS message:`, err.message);
    }
  });

  // TCP → WebSocket: HW protocol uses \n\n as message delimiter
  // Each message is multiple lines. Send as JSON array to browser.
  tcpClient.on('data', (chunk) => {
    tcpBuf += chunk.toString();
    let idx;
    while ((idx = tcpBuf.indexOf('\n\n')) !== -1) {
      const raw = tcpBuf.slice(0, idx);
      tcpBuf = tcpBuf.slice(idx + 2);
      if (raw.length === 0) continue;
      const parts = raw.split('\n');
      const cmd = parts[0];
      if (cmd !== 'PING') console.log(`[${clientIp}] HW→WS: ${cmd}${parts.length>1?' '+parts.slice(1,3).join(' '):''}${parts.length>3?' ...':''}`)
      try {
        if (ws.readyState === WebSocket.OPEN) {
          ws.send(JSON.stringify(parts));
        }
      } catch (err) {
        console.error(`[${clientIp}] WS send error:`, err.message);
      }
    }
  });

  ws.on('close', () => {
    console.log(`[${clientIp}] WebSocket closed`);
    tcpClient.end();
  });

  tcpClient.on('close', () => {
    console.log(`[${clientIp}] TCP closed`);
    if (ws.readyState === WebSocket.OPEN) ws.close();
  });

  ws.on('error', (err) => {
    console.error(`[${clientIp}] WS error:`, err.message);
    tcpClient.end();
  });

  tcpClient.on('error', (err) => {
    console.error(`[${clientIp}] TCP error:`, err.message);
    if (ws.readyState === WebSocket.OPEN) ws.close();
  });
});

wss.on('error', (err) => {
  console.error('Gateway error:', err);
});

process.on('SIGINT', () => {
  console.log('\nShutting down gateway...');
  wss.close(() => process.exit(0));
});
