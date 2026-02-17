// Post-initialization: wire up stdin/stdout and start game

var engineStarted = false;

Module.onRuntimeInitialized = function() {
    console.log('[HW] Runtime initialized');
    Module.setStatus('Engine ready!');
    
    console.log('[HW] Available exports:', Object.keys(Module).filter(k => k.startsWith('_')));
    
    // Give user control to start
    var startButton = document.getElementById('startGame');
    if (startButton) {
        startButton.disabled = false;
        startButton.onclick = function() {
            if (engineStarted) {
                console.log('[HW] Engine already started, ignoring');
                return;
            }
            engineStarted = true;
            
            console.log('[HW] User clicked start');
            
            // Enqueue IPC messages BEFORE main() starts reading stdin
            HWEngine.startHotseatGame();
            
            // Ensure --internal flag is present
            Module.arguments = Module.arguments || [];
            if (!Module.arguments.includes('--internal')) {
                Module.arguments.unshift('--internal');
            }
            
            // Start engine via main() to trigger argument parsing
            try {
                console.log('[boot] about to run', Module.arguments);
                Module.run();
                console.log('[HW] Engine started successfully');
            } catch(e) {
                console.error('[HW] run failed:', e);
                Module.setStatus('Error: ' + e.message);
                engineStarted = false; // Allow retry
            }
        };
    }
};
