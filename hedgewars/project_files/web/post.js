// Post-initialization: wire up stdin/stdout and start game

Module.onRuntimeInitialized = function() {
    console.log('[HW] Runtime initialized');
    console.log('[HW] Calling hwengine_RunEngine_internal()');
    
    try {
        var result = Module._hwengine_RunEngine_internal();
        console.log('[HW] Engine returned:', result);
    } catch(e) {
        // Suppress RuntimeError: unreachable during shutdown cleanup
        if (e instanceof WebAssembly.RuntimeError && e.message.indexOf('unreachable') !== -1) {
            console.log('[HW] Engine shutdown (cleanup error suppressed)');
        } else {
            console.error('[HW] Engine failed:', e);
        }
    }
};
