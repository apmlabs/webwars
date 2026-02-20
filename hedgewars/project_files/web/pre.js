// Hedgewars Engine - Browser IPC Bridge
// Implements message queue for engine IPC protocol

var Module = Module || {};
Module.locateFile = function(path, prefix) {
    if (path.endsWith('.data') || path.endsWith('.wasm')) return path;
    return prefix + path;
};

Module.preRun = Module.preRun || [];
Module.preRun.push(function() {
    try { FS.stat('/Data'); } catch(e) { console.error('[DATA] /Data NOT FOUND:', e.message); }
});

var HWEngine = {
    messageQueue: [],
    outputBuffer: [],
    stderrBuffer: [],

    readIPC: function(bufPtr, maxLen) {
        var count = 0;
        while (count < maxLen && this.messageQueue.length > 0) {
            Module.HEAPU8[bufPtr + count] = this.messageQueue.shift();
            count++;
        }
        return count;
    },

    writeIPC: function(bufPtr, len) {
        var bytes = new Uint8Array(Module.HEAPU8.buffer, bufPtr, len);

        // Auto-respond to pings
        if (len >= 2 && bytes[1] === 0x3f) {
            Array.prototype.unshift.apply(this.messageQueue, [0x03, 0x21, 0x00, 0x00]);
        }

        // Auto-respond to config request 'C'
        if (len >= 2 && bytes[1] === 0x43) {
            if (this.mpConfig) this.startMultiplayerGame();
            else this.startHotseatGame();
        }

        // In multiplayer, relay engine messages to lobby
        if (this.mpConfig && len >= 2) {
            var msgType = bytes[1];
            // Engine game messages that need relaying (same set as checkNetCmd legalMessages)
            var relay = 'M#+LlRrUuDdZzAaSjJ,NpPwtgfhbc12345';
            if (relay.indexOf(String.fromCharCode(msgType)) !== -1) {
                var raw = new Uint8Array(len);
                for (var i = 0; i < len; i++) raw[i] = bytes[i];
                var b64 = btoa(String.fromCharCode.apply(null, raw));
                // Direct function call — lobby is in the same page
                if (typeof window._webwars_emRelay === 'function') window._webwars_emRelay(b64);
            }
            if (msgType === 0x71) {
                if (typeof window._webwars_roundFinished === 'function') window._webwars_roundFinished();
            }
        }
    },

    sendMessage: function(msg) {
        if (typeof msg === 'string') msg = new TextEncoder().encode(msg);
        if (msg.length > 254) { console.error('Message too long:', msg.length); return; }
        this.messageQueue.push(msg.length);
        for (var i = 0; i < msg.length; i++) this.messageQueue.push(msg[i]);
    },

    readByte: function() {
        return this.messageQueue.length > 0 ? this.messageQueue.shift() : -1;
    },

    onStdoutByte: function(ch) { this.outputBuffer.push(ch); },

    onStderrByte: function(ch) {
        this.stderrBuffer.push(ch);
        if (ch === 10) {
            var msg = new TextDecoder().decode(new Uint8Array(this.stderrBuffer)).trim();
            // Suppress IPC debug spam
            if (msg.indexOf('[IPC LEVEL') === -1 && msg.indexOf('[Cmd]') === -1)
                console.log('[HW]', msg);
            this.stderrBuffer = [];
        }
    },

    // Ammo string: exactly 60 digits (one per TAmmoType 1..60, amNothing excluded)
    // 9=infinite, 0=disabled. Default scheme based on real Hedgewars:
    // Positions: Grenade Cluster Bazooka Bee Shotgun PickHammer Skip Rope Mine Deagle
    //            Dynamite FirePunch Whip BaseballBat Parachute Airstrike MineStrike
    //            BlowTorch Girder Teleport Switch Mortar Kamikaze Cake Seduction
    //            Watermelon HellishBomb Napalm Drill Ballgun RCPlane LowGravity
    //            ExtraDamage Invulnerable ExtraTime LaserSight Vampiric SniperRifle
    //            Jetpack Molotov Birdy PortalGun Piano GasBomb SineGun Flamethrower
    //            SMine Hammer Resurrector DrillStrike Snowball Tardis LandGun IceGun
    //            Knife Rubber AirMine Creeper Minigun Sentry
    defaultAmmo: '939192919291929192919191919191919191919191919191919191919191',
    zeroAmmo:    '000000000000000000000000000000000000000000000000000000000000',
    defaultProb: '040504050405040504050404040404040404040404040404040404040404',
    defaultDelay:'000000000000020000000000000000000000000000000000000000000000',
    defaultReinf:'000000000000000000000000000000000000000000000000000000000000',

    // Map → theme mapping (from each map's map.cfg line 1)
    mapThemes: {
        'Cake':'Cake','Castle':'Nature','Cave':'Island','Islands':'Deepspace',
        'Mushrooms':'Nature','Tree':'Halloween','Cheese':'Cheese','Bath':'Bath',
        'Bamboo':'Bamboo','Battlefield':'Nature','Blox':'Blox','Cogs':'EarthRise',
        'EarthRise':'EarthRise','Hammock':'Nature','Hedgelove':'Nature',
        'Hogville':'Nature','Lonely_Island':'Island','Plane':'Planes',
        'Sticks':'Bamboo','Trash':'Compost'
    },

    sendAmmoAndTeam: function(hash, color, name, hogs) {
        // Sanity check: engine expects exactly 60 chars per ammo string
        if (this.defaultAmmo.length !== 60 || this.zeroAmmo.length !== 60) {
            console.error('[HW] FATAL: ammo string length wrong! default=' + this.defaultAmmo.length + ' zero=' + this.zeroAmmo.length);
        }
        // Ammo store MUST be sent before each team (per Hedgewars protocol)
        this.sendMessage('eammloadt ' + this.defaultAmmo);
        this.sendMessage('eammprob ' + this.defaultProb);
        this.sendMessage('eammdelay ' + this.defaultDelay);
        this.sendMessage('eammreinf ' + this.defaultReinf);
        this.sendMessage('eammstore');

        // addteam format: "eaddteam <hash> <color_decimal> <name>"
        this.sendMessage('eaddteam ' + hash + ' ' + color + ' ' + name);
        this.sendMessage('efort Earth');

        // addhh format: "eaddhh <botlevel> <health> <name>"
        for (var i = 0; i < hogs.length; i++) {
            this.sendMessage('eaddhh 0 100 ' + hogs[i]);
            this.sendMessage('ehat NoHat');
        }
    },

    startHotseatGame: function() {
        console.log('[HW] Starting hotseat game...');

        var seed = '{' + Math.random().toString(36).substring(2, 10) + '}';
        var maps = Object.keys(this.mapThemes);
        var map = maps[Math.floor(Math.random() * maps.length)];
        var theme = this.mapThemes[map];
        console.log('[HW] Selected map: ' + map + ' theme: ' + theme);

        // Order matches real Hedgewars server (EngineInteraction.hs)
        // 1. Map + theme
        this.sendMessage('emap ' + map);
        this.sendMessage('etheme ' + theme);

        // 2. Seed + game config
        this.sendMessage('eseed ' + seed);
        this.sendMessage('e$gmflags 0');
        this.sendMessage('e$damagepct 100');
        this.sendMessage('e$turntime 45000');
        this.sendMessage('e$sd_turns 15');
        this.sendMessage('e$casefreq 5');
        this.sendMessage('e$minestime 3000');
        this.sendMessage('e$minesnum 4');
        this.sendMessage('e$minedudpct 0');
        this.sendMessage('e$explosives 2');
        this.sendMessage('e$airmines 0');
        this.sendMessage('e$healthprob 35');
        this.sendMessage('e$hcaseamount 25');
        this.sendMessage('e$waterrise 47');
        this.sendMessage('e$healthdec 5');
        this.sendMessage('e$ropepct 100');
        this.sendMessage('e$getawaytime 100');
        this.sendMessage('e$worldedge 0');
        this.sendMessage('e$template_filter 0');
        this.sendMessage('e$feature_size 12');
        this.sendMessage('e$mapgen 0');

        // 3. Teams (ammo store sent per-team)
        this.sendAmmoAndTeam('x', '4980735', 'Red Team',
            ['Hog A1', 'Hog A2', 'Hog A3', 'Hog A4']);
        this.sendAmmoAndTeam('x', '16776960', 'Blue Team',
            ['Hog B1', 'Hog B2', 'Hog B3', 'Hog B4']);

        // 4. Start
        this.sendMessage('TL');
        this.sendMessage('!');
    },

    startMultiplayerGame: function() {
        var cfg = this.mpConfig;
        console.log('[HW] Starting multiplayer game...', cfg);

        // Map (random gen or named map)
        var mapgen = cfg.mapgen || '0';
        var mapGenTypes = ['+rnd+', '+maze+', '+drawn+', '+perlin+'];
        var mapName = cfg.map || mapGenTypes[parseInt(mapgen)] || '+rnd+';
        if (mapGenTypes.indexOf(mapName) === -1) this.sendMessage('emap ' + mapName);

        // Theme
        this.sendMessage('etheme ' + (cfg.theme || 'Nature'));

        // Script
        if (cfg.script && cfg.script !== 'Normal') {
            this.sendMessage('escript Scripts/Multiplayer/' + cfg.script.replace(/ /g, '_') + '.lua');
        }

        // Seed + map gen
        this.sendMessage('eseed ' + (cfg.seed || String(Date.now())));
        this.sendMessage('e$mapgen ' + mapgen);
        this.sendMessage('e$template_filter ' + (cfg.template || '0'));
        this.sendMessage('e$feature_size ' + (cfg.featureSize || '12'));

        // Scheme params from server CFG
        var scheme = cfg.scheme || [];
        // Game flags from first 27 booleans
        var gmflags = 0;
        var flagConsts = [0x1000,0x10,0x4,0x8,0x20,0x40,0x80,0x100,0x200,0x400,0x800,0x2000,0x4000,0x8000,0x10000,0x20000,0x40000,0x80000,0x100000,0x200000,0x400000,0x800000,0x1000000,0x2000000,0x4000000,0x8000000,0x10000000];
        for (var i = 0; i < 27 && i < scheme.length; i++) {
            if (scheme[i] === 'true') gmflags |= flagConsts[i];
        }
        this.sendMessage('e$gmflags ' + gmflags);

        // Numeric scheme params (indices 27+)
        var paramNames = ['e$damagepct','e$turntime','','e$sd_turns','e$casefreq','e$minestime','e$minesnum','e$minedudpct','e$explosives','e$airmines','e$healthprob','e$hcaseamount','e$waterrise','e$healthdec','e$ropepct','e$getawaytime','e$worldedge'];
        var paramMult = [1,1000,0,1,1,1000,1,1,1,1,1,1,1,1,1,1,1];
        for (var j = 0; j < paramNames.length; j++) {
            if (paramNames[j] && (27 + j) < scheme.length) {
                this.sendMessage(paramNames[j] + ' ' + (parseInt(scheme[27 + j]) * paramMult[j]));
            }
        }

        // Fallback defaults if no scheme
        if (scheme.length === 0) {
            this.sendMessage('e$gmflags 0');
            this.sendMessage('e$damagepct 100');
            this.sendMessage('e$turntime 45000');
            this.sendMessage('e$sd_turns 15');
            this.sendMessage('e$casefreq 5');
            this.sendMessage('e$minestime 3000');
            this.sendMessage('e$minesnum 4');
            this.sendMessage('e$minedudpct 0');
            this.sendMessage('e$explosives 2');
            this.sendMessage('e$airmines 0');
            this.sendMessage('e$healthprob 35');
            this.sendMessage('e$hcaseamount 25');
            this.sendMessage('e$waterrise 47');
            this.sendMessage('e$healthdec 5');
            this.sendMessage('e$ropepct 100');
            this.sendMessage('e$getawaytime 100');
            this.sendMessage('e$worldedge 0');
            this.sendMessage('e$template_filter 0');
            this.sendMessage('e$feature_size 12');
        }

        // Teams — ammo per team, matching EngineInteraction.hs teamSetup
        var ammo = cfg.ammo || '';
        var initHealth = (scheme.length > 27) ? scheme[27] : '100';
        var teams = cfg.teams || [];
        for (var k = 0; k < teams.length; k++) {
            var t = teams[k];
            // Ammo store per team
            if (ammo.length >= 56 * 4) {
                var n = ammo.length / 4;
                this.sendMessage('eammloadt ' + ammo.substring(0, n));
                this.sendMessage('eammprob ' + ammo.substring(n, n*2));
                this.sendMessage('eammdelay ' + ammo.substring(n*2, n*3));
                this.sendMessage('eammreinf ' + ammo.substring(n*3, n*4));
            } else {
                this.sendMessage('eammloadt ' + this.defaultAmmo);
                this.sendMessage('eammprob ' + this.defaultProb);
                this.sendMessage('eammdelay ' + this.defaultDelay);
                this.sendMessage('eammreinf ' + this.defaultReinf);
            }
            // eammstore if scheme says so (index 14=true or index 20=false)
            var needStore = (scheme.length > 14 && scheme[14] === 'true') || (scheme.length <= 20 || scheme[20] === 'false');
            if (needStore) this.sendMessage('eammstore');

            // Team color: (1 + colorIndex) * 2113696
            var colorDecimal = (1 + parseInt(t.color || '0')) * 2113696;
            this.sendMessage('eaddteam <hash> ' + colorDecimal + ' ' + t.name);
            this.sendMessage('erdriven');
            this.sendMessage('efort ' + (t.fort || 'Plane'));

            // Hedgehogs
            var hhnum = t.hhnum || 4;
            var hogs = t.hogs || [];
            for (var h = 0; h < hhnum && h < hogs.length; h++) {
                this.sendMessage('eaddhh ' + (t.diff || '0') + ' ' + initHealth + ' ' + hogs[h].name);
                this.sendMessage('ehat ' + (hogs[h].hat || 'NoHat'));
            }
        }

        // Start — TN for network game
        this.sendMessage('TN');
        this.sendMessage('!');
    }
};

Module.HWEngine = HWEngine;

// Load multiplayer config from sessionStorage if ?mp=1
if (typeof window !== 'undefined' && window.location.search.indexOf('mp=1') !== -1) {
    try {
        var cfg = JSON.parse(sessionStorage.getItem('webwars_game'));
        if (cfg) { HWEngine.mpConfig = cfg; console.log('[HW] Multiplayer mode, config loaded from sessionStorage'); }
    } catch(e) { console.error('[HW] Failed to load MP config:', e); }
}
// Also check for mpConfig injected directly by lobby page (dynamic load)
if (typeof window !== 'undefined' && window._webwars_mpConfig && !HWEngine.mpConfig) {
    HWEngine.mpConfig = window._webwars_mpConfig;
    console.log('[HW] Multiplayer mode, config injected by lobby');
}
Module.noInitialRun = false;
Module.arguments = ['--prefix', '/Data', '--user-prefix', '/Data', 'test.hwd'];
Module.preRun = Module.preRun || [];
Module.postRun = Module.postRun || [];

Module.preRun.push(function() {
    FS.init(
        function() { var b = HWEngine.readByte(); return (b === -1) ? null : (b & 0xFF); },
        function(ch) { HWEngine.onStdoutByte(ch); },
        function(ch) { HWEngine.onStderrByte(ch); }
    );
});

Module.print = function(text) { if (text) console.log('[Engine]', text); };
Module.printErr = function(text) {
    if (!text) return;
    if (text.indexOf('dependency: fp') !== -1) return;
    if (text.indexOf('still waiting') !== -1) return;
    if (text.indexOf('Aborted(Assertion') !== -1) return;
    if (text.indexOf('user callback triggered') !== -1) return;
    console.error('[Engine Error]', text);
};

// setStatus and canvas are defined in hwengine.html before this script loads.
// Do NOT redefine them here — the HTML versions handle the progress bar UI.
