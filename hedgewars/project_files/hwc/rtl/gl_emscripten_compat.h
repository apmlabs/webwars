/*
 * OpenGL compatibility layer for Emscripten/WebGL
 * Maps desktop GL constants to WebGL equivalents
 */

#ifndef GL_EMSCRIPTEN_COMPAT_H
#define GL_EMSCRIPTEN_COMPAT_H

#ifdef __EMSCRIPTEN__

/* BGRA format not available in WebGL - use RGBA instead */
#ifndef GL_BGRA
#define GL_BGRA GL_RGBA
#endif

/* GL_LINE_SMOOTH not available in GLES2/WebGL - define as no-op */
#ifndef GL_LINE_SMOOTH
#define GL_LINE_SMOOTH 0x0B20
#endif

/* GL_TEXTURE_PRIORITY not available in GLES2/WebGL - define as no-op */
#ifndef GL_TEXTURE_PRIORITY
#define GL_TEXTURE_PRIORITY 0x8066
#endif

#endif /* __EMSCRIPTEN__ */

#endif /* GL_EMSCRIPTEN_COMPAT_H */
