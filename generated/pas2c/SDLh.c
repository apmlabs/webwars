#include "fpcrtl.h"

#include "SDLh.h"
;
;
;
;
;
#include "uStore.h"
void sdlh_SDL_WarpMouse(Word x,Word y)
{
    ustore_WarpMouse(x, y);
};
boolean sdlh_SDL_MustLock(PSDL_Surface Surface)
{
    boolean sdl_mustlock_result;
    sdl_mustlock_result = (Surface->flags & SDL_RLEACCEL) != 0;
    return sdl_mustlock_result;
};
void sdlh_SDLNet_Write16(Word value,pointer buf)
{
    (*((PByteArray)buf))[1] = value;
    (*((PByteArray)buf))[0] = value >> 8;
};
void sdlh_SDLNet_Write32(LongWord value,pointer buf)
{
    (*((PByteArray)buf))[3] = value;
    (*((PByteArray)buf))[2] = value >> 8;
    (*((PByteArray)buf))[1] = value >> 16;
    (*((PByteArray)buf))[0] = value >> 24;
};
Word sdlh_SDLNet_Read16(pointer buf)
{
    Word sdlnet_read16_result;
    sdlnet_read16_result = (*((PByteArray)buf))[1] | ((*((PByteArray)buf))[0] << 8);
    return sdlnet_read16_result;
};
LongWord sdlh_SDLNet_Read32(pointer buf)
{
    LongWord sdlnet_read32_result;
    sdlnet_read32_result = (((*((PByteArray)buf))[3] | ((*((PByteArray)buf))[2] << 8)) | ((*((PByteArray)buf))[1] << 16)) | ((*((PByteArray)buf))[0] << 24);
    return sdlnet_read32_result;
};
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TMix_Fading enumvar)
{
    switch(enumvar){
    case MIX_NO_FADING:
        return fpcrtl_make_string("MIX_NO_FADING");
        break;
    case MIX_FADING_OUT:
        return fpcrtl_make_string("MIX_FADING_OUT");
        break;
    case MIX_FADING_IN:
        return fpcrtl_make_string("MIX_FADING_IN");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TMusic enumvar)
{
    switch(enumvar){
    case MUS_CMD:
        return fpcrtl_make_string("MUS_CMD");
        break;
    case MUS_WAV:
        return fpcrtl_make_string("MUS_WAV");
        break;
    case MUS_MOD:
        return fpcrtl_make_string("MUS_MOD");
        break;
    case MUS_MID:
        return fpcrtl_make_string("MUS_MID");
        break;
    case MUS_OGG:
        return fpcrtl_make_string("MUS_OGG");
        break;
    case MUS_MP3:
        return fpcrtl_make_string("MUS_MP3");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TSDL_ArrayByteOrder enumvar)
{
    switch(enumvar){
    case SDL_ARRAYORDER_NONE:
        return fpcrtl_make_string("SDL_ARRAYORDER_NONE");
        break;
    case SDL_ARRAYORDER_RGB:
        return fpcrtl_make_string("SDL_ARRAYORDER_RGB");
        break;
    case SDL_ARRAYORDER_RGBA:
        return fpcrtl_make_string("SDL_ARRAYORDER_RGBA");
        break;
    case SDL_ARRAYORDER_ARGB:
        return fpcrtl_make_string("SDL_ARRAYORDER_ARGB");
        break;
    case SDL_ARRAYORDER_BGR:
        return fpcrtl_make_string("SDL_ARRAYORDER_BGR");
        break;
    case SDL_ARRAYORDER_BGRA:
        return fpcrtl_make_string("SDL_ARRAYORDER_BGRA");
        break;
    case SDL_ARRAYORDER_ABGR:
        return fpcrtl_make_string("SDL_ARRAYORDER_ABGR");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TSDL_GLattr enumvar)
{
    switch(enumvar){
    case SDL_GL_RED_SIZE:
        return fpcrtl_make_string("SDL_GL_RED_SIZE");
        break;
    case SDL_GL_GREEN_SIZE:
        return fpcrtl_make_string("SDL_GL_GREEN_SIZE");
        break;
    case SDL_GL_BLUE_SIZE:
        return fpcrtl_make_string("SDL_GL_BLUE_SIZE");
        break;
    case SDL_GL_ALPHA_SIZE:
        return fpcrtl_make_string("SDL_GL_ALPHA_SIZE");
        break;
    case SDL_GL_BUFFER_SIZE:
        return fpcrtl_make_string("SDL_GL_BUFFER_SIZE");
        break;
    case SDL_GL_DOUBLEBUFFER:
        return fpcrtl_make_string("SDL_GL_DOUBLEBUFFER");
        break;
    case SDL_GL_DEPTH_SIZE:
        return fpcrtl_make_string("SDL_GL_DEPTH_SIZE");
        break;
    case SDL_GL_STENCIL_SIZE:
        return fpcrtl_make_string("SDL_GL_STENCIL_SIZE");
        break;
    case SDL_GL_ACCUM_RED_SIZE:
        return fpcrtl_make_string("SDL_GL_ACCUM_RED_SIZE");
        break;
    case SDL_GL_ACCUM_GREEN_SIZE:
        return fpcrtl_make_string("SDL_GL_ACCUM_GREEN_SIZE");
        break;
    case SDL_GL_ACCUM_BLUE_SIZE:
        return fpcrtl_make_string("SDL_GL_ACCUM_BLUE_SIZE");
        break;
    case SDL_GL_ACCUM_ALPHA_SIZE:
        return fpcrtl_make_string("SDL_GL_ACCUM_ALPHA_SIZE");
        break;
    case SDL_GL_STEREO:
        return fpcrtl_make_string("SDL_GL_STEREO");
        break;
    case SDL_GL_MULTISAMPLEBUFFERS:
        return fpcrtl_make_string("SDL_GL_MULTISAMPLEBUFFERS");
        break;
    case SDL_GL_MULTISAMPLESAMPLES:
        return fpcrtl_make_string("SDL_GL_MULTISAMPLESAMPLES");
        break;
    case SDL_GL_ACCELERATED_VISUAL:
        return fpcrtl_make_string("SDL_GL_ACCELERATED_VISUAL");
        break;
    case SDL_GL_RETAINED_BACKING:
        return fpcrtl_make_string("SDL_GL_RETAINED_BACKING");
        break;
    case SDL_GL_CONTEXT_MAJOR_VERSION:
        return fpcrtl_make_string("SDL_GL_CONTEXT_MAJOR_VERSION");
        break;
    case SDL_GL_CONTEXT_MINOR_VERSION:
        return fpcrtl_make_string("SDL_GL_CONTEXT_MINOR_VERSION");
        break;
    case SDL_GL_CONTEXT_EGL:
        return fpcrtl_make_string("SDL_GL_CONTEXT_EGL");
        break;
    case SDL_GL_CONTEXT_FLAGS:
        return fpcrtl_make_string("SDL_GL_CONTEXT_FLAGS");
        break;
    case SDL_GL_CONTEXT_PROFILE_MASK:
        return fpcrtl_make_string("SDL_GL_CONTEXT_PROFILE_MASK");
        break;
    case SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        return fpcrtl_make_string("SDL_GL_SHARE_WITH_CURRENT_CONTEXT");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TSDL_eventaction enumvar)
{
    switch(enumvar){
    case SDL_ADDEVENT:
        return fpcrtl_make_string("SDL_ADDEVENT");
        break;
    case SDL_PEEPEVENT:
        return fpcrtl_make_string("SDL_PEEPEVENT");
        break;
    case SDL_GETEVENT:
        return fpcrtl_make_string("SDL_GETEVENT");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}