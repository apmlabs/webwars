// Post-initialization: start game
// With JSPI, exported functions return Promises when they suspend.

Module.onRuntimeInitialized = async function() {
    console.log('[HW] Runtime initialized');

    // Diagnostic: instrument Asyncify to trace JSPI wrapping
    if (typeof WebAssembly.promising === 'function') {
        console.log('[HW] JSPI available');
        // Check which exports got promising-wrapped
        var asyncExports = Module.asm ? Object.keys(Module.asm).filter(k => 
            typeof Module.asm[k] === 'function' && Module['_' + k] !== Module.asm[k]
        ) : [];
        console.log('[HW] Async exports:', asyncExports);
        console.log('[HW] _hwengine_RunEngine_internal is function:', typeof Module._hwengine_RunEngine_internal);
    }

    console.log('[HW] Calling hwengine_RunEngine_internal()');
    
    try {
        var result = await Module._hwengine_RunEngine_internal();
        console.log('[HW] Engine returned:', result);
    } catch(e) {
        if (e instanceof WebAssembly.RuntimeError && e.message.indexOf('unreachable') !== -1) {
            console.log('[HW] Engine shutdown (cleanup error suppressed)');
        } else if (e === 'unwind') {
            console.log('[HW] Engine entered main loop (unwind)');
        } else {
            console.error('[HW] Engine failed:', e);
        }
    }
};
