// Post-initialization: wire up stdin/stdout and start game

var engineStarted = false;

Module.onRuntimeInitialized = function() {
    console.log('[HW] Runtime initialized');
    Module.setStatus('Engine starting...');
    
    console.log('[HW] Calling Module.run() with arguments:', Module.arguments);
    Module.run();
};
