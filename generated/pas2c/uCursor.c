#include "fpcrtl.h"

#include "uCursor.h"
#include "SDLh.h"
#include "uVariables.h"
#include "uTypes.h"
void ucursor_init()
{
    SDL_ShowCursor(SDL_DISABLE);
    ucursor_resetPosition();
    SDL_SetRelativeMouseMode(SDL_TRUE);
};
void ucursor_resetPosition()
{
    if(GameType == gmtRecord)
    {
        return;
    }
    sdlh_SDL_WarpMouse(cScreenWidth / 2, cScreenHeight / 2);
    ucursor_resetPositionDelta();
};
void ucursor_resetPositionDelta()
{
    CursorPointDelta.x = 0;
    CursorPointDelta.y = 0;
};
void ucursor_updatePositionDelta(LongInt xrel,LongInt yrel)
{
    CursorPointDelta.x = CursorPointDelta.x + xrel;
    CursorPointDelta.y = CursorPointDelta.y + yrel;
};
void ucursor_updatePosition()
{
    ucursor_handlePositionUpdate(CursorPointDelta.x, CursorPointDelta.y);
    ucursor_resetPositionDelta();
};
void ucursor_handlePositionUpdate(LongInt x,LongInt y)
{
    CursorPoint.x = CursorPoint.x + x;
    CursorPoint.y = CursorPoint.y - y;
};
