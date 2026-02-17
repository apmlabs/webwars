// Post-initialization: wire up stdin/stdout and start game

var engineStarted = false;

Module.onRuntimeInitialized = function() {
    console.log('[HW] Runtime initialized');
    console.log('[HW] Calling hwengine_RunEngine_internal()');
    
    try {
        var result = Module._hwengine_RunEngine_internal();
        console.log('[HW] Engine returned:', result);
    } catch(e) {
        console.error('[HW] Engine failed:', e);
    }
};
