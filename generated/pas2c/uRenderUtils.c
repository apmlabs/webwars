#include "fpcrtl.h"

#include "uRenderUtils.h"
#include "uVariables.h"
#include "uConsts.h"
#include "uTextures.h"
#include "SysUtils.h"
#include "uUtils.h"
#include "uDebug.h"
static const string255 __str6 = STRINIT("...");
static const string255 __str5 = STRINIT("");
static const string255 __str4 = STRINIT("RenderString: fail to create surface");
static const string255 __str3 = STRINIT(" ");
static const string255 __str2 = STRINIT("rotateSurface failed, expecting 32 bit surface");
static const string255 __str1 = STRINIT("flipSurface failed, expecting 32 bit surface");
static const string255 __str0 = STRINIT("TTF_RenderUTF8_Blended");
void urenderutils_DrawRoundRect(PSDL_Rect rect,LongWord BorderColor,LongWord FillColor,PSDL_Surface Surface,boolean Clear)
{
    TSDL_Rect r;
    r = (*rect);
    if(Clear)
    {
        SDL_FillRect(Surface, &(r), SDL_MapRGBA(Surface->format, 0, 0, 0, 0));
    }
    BorderColor = SDL_MapRGB(Surface->format, BorderColor >> 16, BorderColor >> 8, BorderColor & 0xff);
    FillColor = SDL_MapRGB(Surface->format, FillColor >> 16, FillColor >> 8, FillColor & 0xff);
    r.y = rect->y + (cFontBorder / 2);
    r.h = rect->h - cFontBorder;
    SDL_FillRect(Surface, &(r), BorderColor);
    r.x = rect->x + (cFontBorder / 2);
    r.w = rect->w - cFontBorder;
    r.y = rect->y;
    r.h = rect->h;
    SDL_FillRect(Surface, &(r), BorderColor);
    r.x = rect->x + cFontBorder;
    r.y = rect->y + (cFontBorder / 2);
    r.w = rect->w - (cFontBorder * 2);
    r.h = rect->h - cFontBorder;
    SDL_FillRect(Surface, &(r), FillColor);
    r.x = rect->x + (cFontBorder / 2);
    r.y = rect->y + cFontBorder;
    r.w = rect->w - cFontBorder;
    r.h = rect->h - (cFontBorder * 2);
    SDL_FillRect(Surface, &(r), FillColor);
};
LongInt urenderutils_GetSurfaceFrameCoordinateX(PSDL_Surface Surface,LongInt Frame,LongInt frameWidth,LongInt frameHeight)
{
    LongInt getsurfaceframecoordinatex_result;
    LongInt nx;
    LongInt ny;
    nx = Surface->w / frameWidth;
    if(nx == 0)
    {
        nx = 1;
    }
    ny = Surface->h / frameHeight;
    if(ny == 0)
    {
        ny = 1;
    }
    getsurfaceframecoordinatex_result = (Frame / ny) * frameWidth;
    return getsurfaceframecoordinatex_result;
};
LongInt urenderutils_GetSurfaceFrameCoordinateY(PSDL_Surface Surface,LongInt Frame,LongInt frameHeight)
{
    LongInt getsurfaceframecoordinatey_result;
    LongInt ny;
    ny = Surface->h / frameHeight;
    if(ny == 0)
    {
        ny = 1;
    }
    getsurfaceframecoordinatey_result = (Frame % ny) * frameHeight;
    return getsurfaceframecoordinatey_result;
};
boolean urenderutils_IsTooDarkToRead(LongWord TextColor)
{
    boolean istoodarktoread_result;
    TSDL_Color clr;
    clr.r = (TextColor >> 16) & 0xff;
    clr.g = (TextColor >> 8) & 0xff;
    clr.b = TextColor & 0xff;
    istoodarktoread_result = !(((clr.r >= cInvertTextColorAt) || (clr.g >= cInvertTextColorAt)) || (clr.b >= cInvertTextColorAt));
    return istoodarktoread_result;
};
TSDL_Rect urenderutils_WriteInRoundRect(PSDL_Surface Surface,LongInt X,LongInt Y,LongWord Color,THWFont Font,astring s,LongWord maxLength)
{
    TSDL_Rect writeinroundrect_result;
    LongWord w;
    LongWord h;
    PSDL_Surface tmpsurf;
    TSDL_Rect finalRect;
    TSDL_Rect textRect;
    TSDL_Color clr;
    TTF_SizeUTF8(Fontz[Font].Handle, fpcrtl__pcharA(s), &(w), &(h));
    if((maxLength > 0) && (w > fpcrtl_round(maxLength * HDPIScaleFactor)))
    {
        w = fpcrtl_round(maxLength * HDPIScaleFactor);
    }
    finalRect.x = X;
    finalRect.y = Y;
    finalRect.w = (w + (cFontBorder * 2)) + (cFontPadding * 2);
    finalRect.h = h + (cFontBorder * 2);
    textRect.x = X;
    textRect.y = Y;
    textRect.w = w;
    textRect.h = h;
    clr.r = (Color >> 16) & 0xff;
    clr.g = (Color >> 8) & 0xff;
    clr.b = Color & 0xff;
    clr.a = 0xff;
    if(!urenderutils_IsTooDarkToRead(Color))
    {
        urenderutils_DrawRoundRect(&(finalRect), cWhiteColor, cNearBlackColor, Surface, true);
    }
    else
    {
        urenderutils_DrawRoundRect(&(finalRect), cNearBlackColor, cWhiteColor, Surface, true);
    }
    tmpsurf = TTF_RenderUTF8_Blended(Fontz[Font].Handle, fpcrtl__pcharA(s), clr);
    finalRect.x = (X + cFontBorder) + cFontPadding;
    finalRect.y = Y + cFontBorder;
    if(udebug_SDLCheck(tmpsurf != NULL, __str0, true))
    {
        return finalRect;
    }
    SDL_UpperBlit(tmpsurf, &(textRect), Surface, &(finalRect));
    SDL_FreeSurface(tmpsurf);
    finalRect.x = X;
    finalRect.y = Y;
    finalRect.w = (w + (cFontBorder * 2)) + (cFontPadding * 2);
    finalRect.h = h + (cFontBorder * 2);
    writeinroundrect_result = finalRect;
    return writeinroundrect_result;
};
void urenderutils_flipSurface(PSDL_Surface Surface,boolean Vertical)
{
    LongInt y;
    LongInt x;
    LongInt i;
    LongInt j;
    LongWord tmpPixel;
    PLongWordArray pixels;
    if(udebug_checkFails((*Surface->format).BytesPerPixel == 4, __str1, true))
    {
        return;
    }
    SDL_LockSurface(Surface);
    pixels = Surface->pixels;
    if(Vertical)
    {
        {y = 0;
         LongInt y__end__ = (Surface->h / 2) - 1;
         if (y <= y__end__) do {
                                   {x = 0;
                                    LongInt x__end__ = Surface->w - 1;
                                    if (x <= x__end__) do {
                                                              i = (y * Surface->w) + x;
                                                              j = (((Surface->h - y) - 1) * Surface->w) + x;
                                                              tmpPixel = (*pixels)[i];
                                                              (*pixels)[i] = (*pixels)[j];
                                                              (*pixels)[j] = tmpPixel;
                                                          } while(x++ != x__end__);}
                               } while(y++ != y__end__);}
    }
    else
    {
        {x = 0;
         LongInt x__end__ = (Surface->w / 2) - 1;
         if (x <= x__end__) do {
                                   {y = 0;
                                    LongInt y__end__ = Surface->h - 1;
                                    if (y <= y__end__) do {
                                                              i = (y * Surface->w) + x;
                                                              j = (y * Surface->w) + ((Surface->w - x) - 1);
                                                              tmpPixel = (*pixels)[i];
                                                              (*pixels)[i] = (*pixels)[j];
                                                              (*pixels)[j] = tmpPixel;
                                                          } while(y++ != y__end__);}
                               } while(x++ != x__end__);}
    }
    SDL_UnlockSurface(Surface);
};
void urenderutils_copyToXY(PSDL_Surface src,PSDL_Surface dest,LongInt destX,LongInt destY)
{
    urenderutils_copyToXYFromRect(src, dest, 0, 0, src->w, src->h, destX, destY);
};
void urenderutils_copyToXYFromRect(PSDL_Surface src,PSDL_Surface dest,LongInt srcX,LongInt srcY,LongInt srcW,LongInt srcH,LongInt destX,LongInt destY)
{
    LongInt spi;
    LongInt dpi;
    LongInt iX;
    LongInt iY;
    LongInt dX;
    LongInt dY;
    LongInt lX;
    LongInt lY;
    LongInt aT;
    PLongWordArray srcPixels;
    PLongWordArray destPixels;
    Byte rD;
    Byte gD;
    Byte bD;
    Byte aD;
    Byte rT;
    Byte gT;
    Byte bT;
    SDL_LockSurface(src);
    SDL_LockSurface(dest);
    srcPixels = src->pixels;
    destPixels = dest->pixels;
    dX = destX - srcX;
    dY = destY - srcY;
    lX = uutils_Min(srcX + srcW, src->w) - 1;
    if((lX + dX) >= dest->w)
    {
        lX = (dest->w - dX) - 1;
    }
    lY = uutils_Min(srcY + srcH, src->h) - 1;
    if((lY + dY) >= dest->h)
    {
        lY = (dest->h - dY) - 1;
    }
    {iX = srcX;
     LongInt iX__end__ = lX;
     if (iX <= iX__end__) do {
                                 {iY = srcY;
                                  LongInt iY__end__ = lY;
                                  if (iY <= iY__end__) do {
                                                              spi = ((iY * src->pitch) / 4) + iX;
                                                              dpi = (((iY + dY) * dest->pitch) / 4) + (iX + dX);
                                                              aT = ((*srcPixels)[spi] & AMask) >> AShift;
                                                              if(aT == 255)
                                                              {
                                                                  (*destPixels)[dpi] = (*srcPixels)[spi];
                                                                  continue;
                                                              }
                                                              aD = ((*destPixels)[dpi] & AMask) >> AShift;
                                                              if(aD == 0)
                                                              {
                                                                  (*destPixels)[dpi] = (*srcPixels)[spi];
                                                                  continue;
                                                              }
                                                              SDL_GetRGB((*srcPixels)[spi], src->format, &(rT), &(gT), &(bT));
                                                              SDL_GetRGB((*destPixels)[dpi], dest->format, &(rD), &(gD), &(bD));
                                                              rT = ((rD * (255 - aT)) + (rT * aT)) / 255;
                                                              gT = ((gD * (255 - aT)) + (gT * aT)) / 255;
                                                              bT = ((bD * (255 - aT)) + (bT * aT)) / 255;
                                                              aT = aD + (((255 - ((LongInt)aD)) * aT) / 255);
                                                              (*destPixels)[dpi] = SDL_MapRGBA(dest->format, rT, gT, bT, ((Byte)aT));
                                                          } while(iY++ != iY__end__);}
                             } while(iX++ != iX__end__);}
    SDL_UnlockSurface(src);
    SDL_UnlockSurface(dest);
};
void urenderutils_DrawSprite2Surf(TSprite sprite,PSDL_Surface dest,LongInt x,LongInt y)
{
    urenderutils_DrawSpriteFrame2Surf(sprite, dest, x, y, 0);
};
void urenderutils_DrawSpriteFrame2Surf(TSprite sprite,PSDL_Surface dest,LongInt x,LongInt y,LongInt frame)
{
    LongInt numFramesFirstCol;
    LongInt row;
    LongInt col;
    numFramesFirstCol = SpritesData[sprite].imageHeight / SpritesData[sprite].Height;
    row = frame % numFramesFirstCol;
    col = frame / numFramesFirstCol;
    urenderutils_copyToXYFromRect(SpritesData[sprite].Surface, dest, col * SpritesData[sprite].Width, row * SpritesData[sprite].Height, SpritesData[sprite].Width, SpritesData[sprite].Height, x, y);
};
void urenderutils_DrawLine2Surf(PSDL_Surface dest,LongInt x0,LongInt y0,LongInt x1,LongInt y1,Byte r,Byte g,Byte b)
{
    LongInt dx;
    LongInt dy;
    LongInt err;
    LongInt e2;
    LongInt sx;
    LongInt sy;
    LongInt yMax;
    PLongWordArray destPixels;
    yMax = dest->pitch / 4;
    SDL_LockSurface(dest);
    destPixels = dest->pixels;
    dx = fpcrtl_abs(x1 - x0);
    dy = fpcrtl_abs(y1 - y0);
    if(x0 < x1)
    {
        sx = 1;
    }
    else
    {
        sx = -1;
    }
    if(y0 < y1)
    {
        sy = 1;
    }
    else
    {
        sy = -1;
    }
    err = dx - dy;
    while(true)
    {
        (*destPixels)[(y0 * yMax) + x0] = SDL_MapRGB(dest->format, r, g, b);
        if((x0 == x1) && (y0 == y1))
        {
            break;
        }
        e2 = 2 * err;
        if(e2 > -dy)
        {
            err = err - dy;
            x0 = x0 + sx;
        }
        if(e2 < dx)
        {
            err = err + dx;
            y0 = y0 + sy;
        }
    }
    SDL_UnlockSurface(dest);
};
void urenderutils_copyRotatedSurface(PSDL_Surface src,PSDL_Surface dest)
{
    LongInt y;
    LongInt x;
    LongInt i;
    LongInt j;
    PLongWordArray srcPixels;
    PLongWordArray destPixels;
    udebug_checkFails((*src->format).BytesPerPixel == 4, __str2, true);
    udebug_checkFails((*dest->format).BytesPerPixel == 4, __str2, true);
    if(!allOK)
    {
        return;
    }
    SDL_LockSurface(src);
    SDL_LockSurface(dest);
    srcPixels = src->pixels;
    destPixels = dest->pixels;
    j = 0;
    {x = 0;
     LongInt x__end__ = src->w - 1;
     if (x <= x__end__) do {
                               {y = 0;
                                LongInt y__end__ = src->h - 1;
                                if (y <= y__end__) do {
                                                          i = (((src->h - 1) - y) * (src->pitch / 4)) + x;
                                                          (*destPixels)[j] = (*srcPixels)[i];
                                                          ++j;
                                                      } while(y++ != y__end__);}
                           } while(x++ != x__end__);}
    SDL_UnlockSurface(src);
    SDL_UnlockSurface(dest);
};
PTexture urenderutils_RenderStringTex(astring s,LongWord Color,THWFont font)
{
    PTexture renderstringtex_result;
    renderstringtex_result = urenderutils_RenderStringTexLim(s, Color, font, 0);
    return renderstringtex_result;
};
PTexture urenderutils_RenderStringTexLim(astring s,LongWord Color,THWFont font,LongWord maxLength)
{
    PTexture renderstringtexlim_result;
    LongWord w;
    LongWord h;
    PSDL_Surface finalSurface;
    if(cOnlyStats)
    {
        renderstringtexlim_result = NULL;
    }
    else
    {
        if(fpcrtl_LengthA(s) == 0)
        {
            s = fpcrtl_str2astr(__str3);
        }
        font = uutils_CheckCJKFont(s, font);
        w = 0;
        h = 0;
        TTF_SizeUTF8(Fontz[font].Handle, fpcrtl__pcharA(s), &(w), &(h));
        if((maxLength > 0) && (w > fpcrtl_round(maxLength * HDPIScaleFactor)))
        {
            w = fpcrtl_round(maxLength * HDPIScaleFactor);
        }
        finalSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, (w + (cFontBorder * 2)) + (cFontPadding * 2), h + (cFontBorder * 2), 32, RMask, GMask, BMask, AMask);
        if(udebug_checkFails(finalSurface != NULL, __str4, true))
        {
            return NULL;
        }
        urenderutils_WriteInRoundRect(finalSurface, 0, 0, Color, font, s, maxLength);
        udebug_checkFails(SDL_SetColorKey(finalSurface, SDL_TRUE, 0) == 0, errmsgTransparentSet, false);
        renderstringtexlim_result = utextures_Surface2Tex(finalSurface, false);
        SDL_FreeSurface(finalSurface);
    }
    return renderstringtexlim_result;
};
boolean urenderutils_GetNextSpeechLine(astring s,char ldelim,LongInt (*startFrom),astring (*substr))
{
    boolean getnextspeechline_result;
    Integer p;
    Integer l;
    Integer m;
    Integer r;
    boolean newl;
    boolean skip;
    char c;
    m = fpcrtl_LengthA(s);
    (*substr) = fpcrtl_str2astr(__str5);
    fpcrtl_SetLengthA((*substr), m);
    r = 0;
    l = 0;
    newl = true;
    {p = uutils_Max(1, (*startFrom));
     Integer p__end__ = m;
     if (p <= p__end__) do {
                               ++r;
                               c = s.s[p];
                               skip = (newl || (p == m)) && ((c == 0x20) || (c == ldelim));
                               if(!skip)
                               {
                                   newl = c == ldelim;
                                   if(newl)
                                   {
                                       break;
                                   }
                                   ++l;
                                   (*substr).s[l] = c;
                               }
                           } while(p++ != p__end__);}
    (*startFrom) += r;
    fpcrtl_SetLengthA((*substr), l);
    getnextspeechline_result = l > 0;
    return getnextspeechline_result;
};
PTexture urenderutils_RenderSpeechBubbleTex(astring s,LongWord SpeechType,THWFont font)
{
    PTexture renderspeechbubbletex_result;
    LongInt textWidth;
    LongInt textHeight;
    LongInt x;
    LongInt y;
    LongInt w;
    LongInt h;
    LongInt i;
    LongInt j;
    LongInt pos;
    LongInt line;
    LongInt numLines;
    LongInt edgeWidth;
    LongInt edgeHeight;
    LongInt cornerWidth;
    LongInt cornerHeight;
    PSDL_Surface finalSurface;
    PSDL_Surface tmpsurf;
    PSDL_Surface rotatedEdge;
    TSDL_Rect rect;
    astring substr;
    TSprite edge;
    TSprite corner;
    TSprite tail;
    if(cOnlyStats)
    {
        return NULL;
    }
    switch(SpeechType)
    {case 1:{
                edge = sprSpeechEdge;
                corner = sprSpeechCorner;
                tail = sprSpeechTail;
            }
            break;
     case 2:{
                edge = sprThoughtEdge;
                corner = sprThoughtCorner;
                tail = sprThoughtTail;
            }
            break;
     case 3:{
                edge = sprShoutEdge;
                corner = sprShoutCorner;
                tail = sprShoutTail;
            }
            break;
     default: return NULL;}
    edgeHeight = SpritesData[edge].Height;
    edgeWidth = SpritesData[edge].Width;
    cornerWidth = SpritesData[corner].Width;
    cornerHeight = SpritesData[corner].Height;
    numLines = 0;
    if(fpcrtl_LengthA(s) == 0)
    {
        s = fpcrtl_str2astr(__str6);
    }
    font = uutils_CheckCJKFont(s, font);
    w = 0;
    h = 0;
    TTF_SizeUTF8(Fontz[font].Handle, fpcrtl__pcharA(s), &(w), &(h));
    if(w < 8)
    {
        w = 8;
    }
    j = 0;
    if(fpcrtl_LengthA(s) > 20)
    {
        w = 0;
        i = fpcrtl_round(sqrt(fpcrtl_LengthA(s)) * 2);
        pos = 1;
        line = 0;
        while(urenderutils_GetNextSpeechLine(s, 0x1, &(pos), &(substr)))
        {
            ++numLines;
            i = 0;
            j = 0;
            TTF_SizeUTF8(Fontz[font].Handle, fpcrtl__pcharA(substr), &(i), &(j));
            if(i > w)
            {
                w = i;
            }
        }
    }
    else
    {
        numLines = 1;
    }
    if(numLines < 1)
    {
        s = fpcrtl_str2astr(__str6);
        numLines = 1;
    }
    textWidth = (((w - ((cornerWidth - edgeWidth) * 2)) / edgeWidth) * edgeWidth) + edgeWidth;
    textHeight = ((((numLines * h) + 2) - ((cornerHeight - edgeWidth) * 2)) / edgeWidth) * edgeWidth;
    textHeight = uutils_Max(textHeight, edgeWidth);
    rect.x = 0;
    rect.y = 0;
    rect.w = textWidth + (cornerWidth * 2);
    rect.h = ((textHeight + (cornerHeight * 2)) - edgeHeight) + SpritesData[tail].Height;
    finalSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w, rect.h, 32, RMask, GMask, BMask, AMask);
    if(udebug_checkFails(finalSurface != NULL, __str4, true))
    {
        return NULL;
    }
    urenderutils_copyToXY(SpritesData[corner].Surface, finalSurface, 0, 0);
    urenderutils_flipSurface(SpritesData[corner].Surface, true);
    x = 0;
    y = (textHeight + cornerHeight) - 1;
    urenderutils_copyToXY(SpritesData[corner].Surface, finalSurface, x, y);
    urenderutils_flipSurface(SpritesData[corner].Surface, false);
    x = (rect.w - cornerWidth) - 1;
    y = (textHeight + cornerHeight) - 1;
    urenderutils_copyToXY(SpritesData[corner].Surface, finalSurface, x, y);
    urenderutils_flipSurface(SpritesData[corner].Surface, true);
    x = (rect.w - cornerWidth) - 1;
    y = 0;
    urenderutils_copyToXY(SpritesData[corner].Surface, finalSurface, x, y);
    urenderutils_flipSurface(SpritesData[corner].Surface, false);
    x = cornerWidth;
    y = 0;
    while(x < ((rect.w - cornerWidth) - 1))
    {
        urenderutils_copyToXY(SpritesData[edge].Surface, finalSurface, x, y);
        x += edgeWidth;
    }
    urenderutils_flipSurface(SpritesData[edge].Surface, true);
    x = cornerWidth;
    y = ((textHeight + (cornerHeight * 2)) - edgeHeight) - 1;
    while(x < ((rect.w - cornerWidth) - 1))
    {
        urenderutils_copyToXY(SpritesData[edge].Surface, finalSurface, x, y);
        x += edgeWidth;
    }
    urenderutils_flipSurface(SpritesData[edge].Surface, true);
    rotatedEdge = SDL_CreateRGBSurface(SDL_SWSURFACE, edgeHeight, edgeWidth, 32, RMask, GMask, BMask, AMask);
    x = (rect.w - edgeHeight) - 1;
    y = cornerHeight;
    urenderutils_copyRotatedSurface(SpritesData[edge].Surface, rotatedEdge);
    while(y < (textHeight + cornerHeight))
    {
        urenderutils_copyToXY(rotatedEdge, finalSurface, x, y);
        y += edgeWidth;
    }
    urenderutils_flipSurface(rotatedEdge, false);
    x = 0;
    y = cornerHeight;
    while(y < (textHeight + cornerHeight))
    {
        urenderutils_copyToXY(rotatedEdge, finalSurface, x, y);
        y += edgeWidth;
    }
    x = cornerWidth;
    y = ((textHeight + (cornerHeight * 2)) - edgeHeight) - 1;
    urenderutils_copyToXY(SpritesData[tail].Surface, finalSurface, x, y);
    rect.x = edgeHeight;
    rect.y = edgeHeight;
    rect.w = rect.w - (edgeHeight * 2);
    rect.h = (textHeight + (cornerHeight * 2)) - (edgeHeight * 2);
    i = rect.w;
    j = rect.h;
    SDL_FillRect(finalSurface, &(rect), SDL_MapRGB(finalSurface->format, cWhiteColor >> 16, cWhiteColor >> 8, cWhiteColor & 0xff));
    pos = 1;
    line = 0;
    while(urenderutils_GetNextSpeechLine(s, 0x1, &(pos), &(substr)))
    {
        tmpsurf = TTF_RenderUTF8_Blended(Fontz[font].Handle, fpcrtl__pcharA(substr), cNearBlackColorChannels);
        rect.x = (edgeHeight + 1) + ((i - w) / 2);
        rect.y = (edgeHeight + ((j - (numLines * h)) / 2)) + (line * h);
        if(!udebug_SDLCheck(tmpsurf != NULL, __str0, true))
        {
            SDL_UpperBlit(tmpsurf, NULL, finalSurface, &(rect));
            SDL_FreeSurface(tmpsurf);
        }
        ++line;
    }
    renderspeechbubbletex_result = utextures_Surface2Tex(finalSurface, true);
    SDL_FreeSurface(rotatedEdge);
    SDL_FreeSurface(finalSurface);
    return renderspeechbubbletex_result;
};
