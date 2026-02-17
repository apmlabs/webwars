// Post-initialization: wire up stdin/stdout and start game

var engineStarted = false;

Module.onRuntimeInitialized = function() {
    console.log('[HW] Runtime initialized - engine will auto-start');
};
