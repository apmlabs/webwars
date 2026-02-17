// Hedgewars Engine Message Queue for Browser
// Implements stdin/stdout for engine IPC protocol

var HWEngine = {
    messageQueue: [],
    outputBuffer: [],
    stderrBuffer: [],
    
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
        this.sendMessage('e$mapgen 0');
        this.sendMessage('e$maze_size 0');
        
        // Add two teams
        this.sendMessage('eaddteam <hash> 0 Red');
        this.sendMessage('eaddhh 0 100 Player1');
        
        this.sendMessage('eaddteam <hash> 1 Blue');  
        this.sendMessage('eaddhh 0 100 Player2');
        
        // Start game
        this.sendMessage('?');
    }
};

// Extend Module instead of replacing it
if (typeof Module === 'undefined') {
    var Module = {};
}

// Prevent auto-run of main() - we'll call it explicitly from the button
Module.noInitialRun = true;

// Set command-line arguments for the engine
Module.arguments = [
    '--internal',           // Use IPC mode (read from stdin)
    '--prefix', '/Data',
    '--user-prefix', '/Data'
];

Module.preRun = Module.preRun || [];
Module.postRun = Module.postRun || [];

// Wire stdin/stdout/stderr in preRun
Module.preRun.push(function() {
    console.log('[preRun] FS.init wiring');
    
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
    
    HWEngine.queueSize = function() { return HWEngine.messageQueue.length; };
    setInterval(function() { 
        console.log('[stdin] count=', stdinCount, 'queue=', HWEngine.queueSize()); 
    }, 1000);
});

Module.print = Module.print || function(text) {
    console.log('[Engine]', text);
};

Module.printErr = Module.printErr || function(text) {
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
