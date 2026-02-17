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
        var ascii = Array.from(bytes).map(function(b) { return (b >= 32 && b < 127) ? String.fromCharCode(b) : '.'; }).join('');
        console.log('[IPC->JS] ' + ascii);

        // Auto-respond to pings
        if (len >= 2 && bytes[1] === 0x3f) {
            Array.prototype.unshift.apply(this.messageQueue, [0x03, 0x21, 0x00, 0x00]);
        }

        // Auto-respond to config request 'C'
        if (len >= 2 && bytes[1] === 0x43) {
            this.startHotseatGame();
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
    // 9=infinite, 0=disabled
    defaultAmmo: '999999999999999999999999999999999999999999999999999999999999',
    zeroAmmo:    '000000000000000000000000000000000000000000000000000000000000',

    sendAmmoAndTeam: function(hash, color, name, hogs) {
        // Sanity check: engine expects exactly 60 chars per ammo string
        if (this.defaultAmmo.length !== 60 || this.zeroAmmo.length !== 60) {
            console.error('[HW] FATAL: ammo string length wrong! default=' + this.defaultAmmo.length + ' zero=' + this.zeroAmmo.length);
        }
        // Ammo store MUST be sent before each team (per Hedgewars protocol)
        this.sendMessage('eammloadt ' + this.defaultAmmo);
        this.sendMessage('eammprob ' + this.zeroAmmo);
        this.sendMessage('eammdelay ' + this.zeroAmmo);
        this.sendMessage('eammreinf ' + this.zeroAmmo);
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

        // 1. Global config (matches real Hedgewars server sequence)
        this.sendMessage('eseed ' + seed);
        this.sendMessage('e$gmflags 0');          // default game flags
        this.sendMessage('e$damagepct 100');
        this.sendMessage('e$turntime 45000');      // 45 second turns
        this.sendMessage('e$sd_turns 15');          // sudden death after 15 turns
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
        this.sendMessage('e$mapgen 0');            // 0 = random

        // 2. Teams (ammo store sent per-team, before each team)
        this.sendAmmoAndTeam('x', '4980735', 'Red Team',
            ['Hog A1', 'Hog A2', 'Hog A3', 'Hog A4']);

        this.sendAmmoAndTeam('x', '16776960', 'Blue Team',
            ['Hog B1', 'Hog B2', 'Hog B3', 'Hog B4']);

        // 3. Map (after teams)
        this.sendMessage('emap Cake');

        // 4. Game type and start
        this.sendMessage('TL');
        this.sendMessage('!');
    }
};

Module.HWEngine = HWEngine;
Module.noInitialRun = false;
Module.arguments = ['--prefix', '/Data', '--user-prefix', '/Data', '--nomusic', '--nosound', 'test.hwd'];
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

Module.setStatus = function(text) {
    if (text) {
        var el = document.getElementById('status');
        if (el) el.innerHTML = text;
    }
};

if (!Module.canvas) {
    Module.canvas = (function() {
        var canvas = document.getElementById('canvas');
        if (canvas) {
            canvas.addEventListener("webglcontextlost", function(e) { e.preventDefault(); }, false);
        }
        return canvas;
    })();
}

Module.setStatus('Downloading...');
