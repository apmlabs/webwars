// Hedgewars Engine Message Queue for Browser
// Implements stdin/stdout for engine IPC protocol

// Fix asset loading path - force .data and .wasm to load from server root
var Module = Module || {};
Module.locateFile = function(path, prefix) {
    console.log('[locateFile] Called with path=' + path + ' prefix=' + prefix);
    // Force both wasm + data to be fetched from server root (same dir as hwengine.html)
    if (path.endsWith('.data')) {
        console.log('[locateFile] Returning: hwengine.data');
        return 'hwengine.data';
    }
    if (path.endsWith('.wasm')) {
        console.log('[locateFile] Returning: hwengine.wasm');
        return 'hwengine.wasm';
    }
    console.log('[locateFile] Returning: ' + prefix + path);
    return prefix + path;
};

// Log when data file starts/finishes loading
Module.preRun = Module.preRun || [];
Module.preRun.push(function() {
    console.log('[DATA] preRun: Filesystem should be mounted now');
    try {
        var stat = FS.stat('/Data');
        console.log('[DATA] /Data exists, mode=' + stat.mode);
    } catch(e) {
        console.error('[DATA] /Data NOT FOUND:', e.message);
    }
});

// WebGL debugging: track invalid texture parameter calls
var WebGLDebug = {
    invalidCalls: new Map(),
    maxLog: 5,
    
    logInvalidTexParam: function(target, pname) {
        var key = target + ':' + pname;
        if (!this.invalidCalls.has(key)) {
            this.invalidCalls.set(key, 1);
            if (this.invalidCalls.size <= this.maxLog) {
                console.warn('[WebGL Debug] Invalid texParameter: target=0x' + target.toString(16) + 
                           ' pname=0x' + pname.toString(16) + ' (decimal: ' + pname + ')');
            }
        }
    }
};

var HWEngine = {
    messageQueue: [],
    outputBuffer: [],
    stderrBuffer: [],
    
    // Read IPC bytes (called from C via EM_JS)
    readIPC: function(bufPtr, maxLen) {
        var count = 0;
        while (count < maxLen && this.messageQueue.length > 0) {
            Module.HEAPU8[bufPtr + count] = this.messageQueue.shift();
            count++;
        }
        if (count > 0) {
            console.log('[IPC] Provided', count, 'bytes to engine');
        }
        return count;
    },
    
    // Write IPC bytes (called from C when engine sends)
    writeIPC: function(bufPtr, len) {
        var bytes = new Uint8Array(Module.HEAPU8.buffer, bufPtr, len);
        var hex = Array.from(bytes).map(function(b) { return b.toString(16).padStart(2, '0'); }).join(' ');
        var ascii = Array.from(bytes).map(function(b) { return (b >= 32 && b < 127) ? String.fromCharCode(b) : '.'; }).join('');
        console.log('[IPC->JS] len=' + len + ' hex: ' + hex + ' ascii: "' + ascii + '"');
        
        // Auto-respond to pings: match exact 4-byte ping format [0x03, 0x3f, 0x00, 0x00]
        if (len === 4 && bytes[0] === 0x03 && bytes[1] === 0x3f && bytes[2] === 0x00 && bytes[3] === 0x00) {
            console.log('[IPC] Received ping [03 3f 00 00], sending pong [03 21 00 00]');
            // Insert pong at FRONT of queue as a block
            Array.prototype.unshift.apply(this.messageQueue, [0x03, 0x21, 0x00, 0x00]);
        }
        
        // Auto-respond to config request 'C': match [0x03, 0x43, 0x00, 0x00]
        if (len === 4 && bytes[0] === 0x03 && bytes[1] === 0x43 && bytes[2] === 0x00 && bytes[3] === 0x00) {
            console.log('[IPC] Received config request, sending game setup');
            this.startHotseatGame();
        }
    },
    
    // Add a message to the queue (length-prefixed protocol)
    sendMessage: function(msg) {
        if (typeof msg === 'string') {
            msg = new TextEncoder().encode(msg);
        }
        // Hedgewars protocol: [length byte][payload...]
        var len = msg.length;
        if (len > 254) {
            console.error('Message too long:', len);
            return;
        }
        this.messageQueue.push(len);
        for (var i = 0; i < msg.length; i++) {
            this.messageQueue.push(msg[i]);
        }
        console.log('[HW] Queued message:', new TextDecoder().decode(msg));
    },
    
    // Read one byte from queue (called by engine stdin)
    readByte: function() {
        if (this.messageQueue.length > 0) {
            return this.messageQueue.shift();
        }
        return -1; // No data available
    },
    
    // Callbacks for stdout/stderr
    onStdoutByte: function(ch) {
        this.outputBuffer.push(ch);
        // Try to decode complete messages (length-prefixed)
        if (this.outputBuffer.length > 1 && this.outputBuffer[0] === this.outputBuffer.length - 1) {
            var msg = new TextDecoder().decode(new Uint8Array(this.outputBuffer.slice(1)));
            console.log('[HW Output]', msg);
            this.outputBuffer = [];
        }
    },
    
    onStderrByte: function(ch) {
        this.stderrBuffer.push(ch);
        if (ch === 10) { // newline
            var msg = new TextDecoder().decode(new Uint8Array(this.stderrBuffer));
            console.error('[HW Error]', msg.trim());
            this.stderrBuffer = [];
        }
    },
    
    // Start a simple hotseat game
    startHotseatGame: function() {
        console.log('[HW] Starting hotseat game...');
        
        // Basic game setup messages
        this.sendMessage('eseed {' + Math.random().toString(36).substring(7) + '}');
        this.sendMessage('e$template_filter 0');
        this.sendMessage('e$mapgen 2');  // 2 = Maze generator (guaranteed flat corridors)
        this.sendMessage('e$maze_size 0');
        
        // Ammo configuration (60 digits for 60 ammo types)
        this.sendMessage('eammloadt 999999999999999999999999999999999999999999999999999999999999');
        this.sendMessage('eammprob 000000000000000000000000000000000000000000000000000000000000');
        this.sendMessage('eammdelay 000000000000000000000000000000000000000000000000000000000000');
        this.sendMessage('eammreinf 000000000000000000000000000000000000000000000000000000000000');
        this.sendMessage('eammstore');
        
        // Add two teams with 1 hedgehog each
        this.sendMessage('eaddteam <hash> 0 Red');
        this.sendMessage('eaddhh 0 100 Player1');
        
        this.sendMessage('eaddteam <hash> 1 Blue');
        this.sendMessage('eaddhh 0 100 Player2');
        
        // Cake map has mask.png for spawn zones
        this.sendMessage('emap Cake');
        
        // Set game type and start
        this.sendMessage('TL');  // gmtLocal
        
        // Start game
        this.sendMessage('?');
    }
};

// Extend Module instead of replacing it
if (typeof Module === 'undefined') {
    var Module = {};
}

// Expose HWEngine globally for EM_JS access
Module.HWEngine = HWEngine;

// Prevent auto-run of main() - we'll queue messages first
Module.noInitialRun = false;  // Let it run automatically

// Set command-line arguments for the engine (demo file approach)
Module.arguments = [
    '--prefix', '/Data',
    '--user-prefix', '/Data',
    '--nomusic',
    '--nosound',
    'test.hwd'  // Demo file
];

Module.preRun = Module.preRun || [];
Module.postRun = Module.postRun || [];

// Wire stdin/stdout/stderr in preRun
Module.preRun.push(function() {
    console.log('[preRun] FS.init wiring');
    
    // Don't queue messages here - respond to 'C' command instead
    console.log('[preRun] Ready for IPC');
    
    var stdinCount = 0;
    var first = [];
    
    function stdin() {
        var b = HWEngine.readByte();
        if (b === -1 || b === undefined) return null;
        
        stdinCount++;
        if (first.length < 64) first.push(b & 0xFF);
        if (stdinCount === 1) console.log('[stdin] first byte read');
        if (stdinCount === 64) console.log('[stdin] first64:', first.map(function(x) { return x.toString(16).padStart(2,'0'); }).join(' '));
        
        return b & 0xFF;
    }
    
    function stdout(ch) {
        HWEngine.onStdoutByte(ch);
    }
    
    function stderr(ch) {
        HWEngine.onStderrByte(ch);
    }
    
    FS.init(stdin, stdout, stderr);
    
    // Remove stdin spam logging
    // HWEngine.queueSize = function() { return HWEngine.messageQueue.length; };
    // setInterval(function() { 
    //     console.log('[stdin] count=', stdinCount, 'queue=', HWEngine.queueSize()); 
    // }, 1000);
});

Module.print = Module.print || function(text) {
    console.log('[Engine]', text);
};

Module.printErr = Module.printErr || function(text) {
    // Suppress ALL verbose messages during development
    if (!text) return;
    
    // Suppress dependency messages
    if (text.includes('dependency: fp')) return;
    
    // Suppress "still waiting" messages
    if (text.includes('still waiting on run dependencies')) return;
    
    // Suppress repeated assertion failures
    if (text.includes('Aborted(Assertion failed)')) return;
    
    // Suppress callback after exit messages
    if (text.includes('user callback triggered after runtime exited')) return;
    
    // Only log real errors
    console.error('[Engine Error]', text);
};

Module.setStatus = Module.setStatus || function(text) {
    if (text) {
        console.log('[Status]', text);
        var statusElement = document.getElementById('status');
        if (statusElement) {
            statusElement.innerHTML = text;
        }
    }
};

Module.monitorRunDependencies = Module.monitorRunDependencies || function(left) {
    this.totalDependencies = Math.max(this.totalDependencies || 0, left);
    Module.setStatus(left ? 'Preparing... (' + (this.totalDependencies-left) + '/' + this.totalDependencies + ')' : 'All downloads complete.');
};

if (!Module.canvas) {
    Module.canvas = (function() {
        var canvas = document.getElementById('canvas');
        if (canvas) {
            canvas.addEventListener("webglcontextlost", function(e) {
                alert('WebGL context lost. You will need to reload the page.');
                e.preventDefault();
            }, false);
            
            // Wrap getContext to instrument texParameteri calls
            var originalGetContext = canvas.getContext.bind(canvas);
            canvas.getContext = function(type, attrs) {
                var ctx = originalGetContext(type, attrs);
                if (ctx && (type === 'webgl2' || type === 'webgl')) {
                    var originalTexParameteri = ctx.texParameteri.bind(ctx);
                    ctx.texParameteri = function(target, pname, param) {
                        try {
                            originalTexParameteri(target, pname, param);
                        } catch(e) {
                            WebGLDebug.logInvalidTexParam(target, pname);
                        }
                    };
                }
                return ctx;
            };
        }
        return canvas;
    })();
}

Module.setStatus('Downloading...');

if (typeof window !== 'undefined') {
    window.onerror = function() {
        Module.setStatus('Exception thrown, see JavaScript console');
    };
}
