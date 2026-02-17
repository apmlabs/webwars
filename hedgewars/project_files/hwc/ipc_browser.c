// Browser IPC shim - replaces SDL_net with JS callback
#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <stdio.h>
#include <string.h>

// Called from JS to provide IPC bytes (engine reads)
EM_JS(int, hw_ipc_read_js, (unsigned char* buf, int maxlen), {
    return Module.HWEngine.readIPC(buf, maxlen);
});

// Called to send IPC bytes to JS (engine writes)
EM_JS(void, hw_ipc_write_js, (const unsigned char* buf, int len), {
    Module.HWEngine.writeIPC(buf, len);
});

// Replacement for SDL_net IPC read
int hw_ipc_recv(unsigned char* buf, int maxlen) {
    int n = hw_ipc_read_js(buf, maxlen);
    if (n > 0) {
        fprintf(stderr, "[IPC] Read %d bytes\n", n);
    }
    return n;
}

// Stub out SDL_net functions (not used in browser)
int SDLNet_Init() { return 0; }
void SDLNet_Quit() {}
void* SDLNet_AllocSocketSet(int max) { return (void*)1; }
int SDLNet_ResolveHost(void* addr, const char* host, unsigned short port) { return 0; }
void* SDLNet_TCP_Open(void* addr) { return (void*)1; }

// REAL send function - forward to JS
int SDLNet_TCP_Send(void* sock, const void* data, int len) {
    fprintf(stderr, "[IPC] Send %d bytes: ", len);
    const unsigned char* bytes = (const unsigned char*)data;
    for (int i = 0; i < len && i < 32; i++) {
        fprintf(stderr, "%02x ", bytes[i]);
    }
    fprintf(stderr, "\n");
    hw_ipc_write_js(bytes, len);
    return len;
}

int SDLNet_TCP_Recv(void* sock, void* data, int maxlen) { return 0; }
int SDLNet_AddSocket(void* set, void* sock) { return 1; }
int SDLNet_CheckSockets(void* set, unsigned int timeout) { return 0; }
void SDLNet_FreeSocketSet(void* set) {}
void SDLNet_TCP_Close(void* sock) {}

// Byte order functions (used by other code)
unsigned short SDLNet_Read16(void* ptr) {
    unsigned char* p = (unsigned char*)ptr;
    return (p[0] << 8) | p[1];
}
void SDLNet_Write16(unsigned short value, void* ptr) {
    unsigned char* p = (unsigned char*)ptr;
    p[0] = (value >> 8) & 0xFF;
    p[1] = value & 0xFF;
}
unsigned int SDLNet_Read32(void* ptr) {
    unsigned char* p = (unsigned char*)ptr;
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}
void SDLNet_Write32(unsigned int value, void* ptr) {
    unsigned char* p = (unsigned char*)ptr;
    p[0] = (value >> 24) & 0xFF;
    p[1] = (value >> 16) & 0xFF;
    p[2] = (value >> 8) & 0xFF;
    p[3] = value & 0xFF;
}

#endif
