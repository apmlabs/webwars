#include <stdio.h>
#include <physfs.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define EXPORT EMSCRIPTEN_KEEPALIVE
#else
#define EXPORT
#endif

EXPORT int physfs_probe_open(const char* path) {
    if (!path) return -100;

    PHYSFS_File* f = PHYSFS_openRead(path);
    if (!f) {
        const char* err = PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
        printf("[physfs_probe] openRead failed: %s | path=%s\n", err ? err : "(null)", path);
        return -1;
    }

    PHYSFS_sint64 len = PHYSFS_fileLength(f);
    if (len < 0) {
        PHYSFS_close(f);
        return -2;
    }

    unsigned char b = 0;
    PHYSFS_sint64 r = PHYSFS_readBytes(f, &b, 1);
    if (r != 1 && len > 0) {
        PHYSFS_close(f);
        return -3;
    }

    PHYSFS_close(f);
    printf("[physfs_probe] OK path=%s len=%lld firstByte=%u\n", path, (long long)len, (unsigned)b);
    return (int)len;
}
