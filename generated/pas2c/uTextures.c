#include "fpcrtl.h"

#include "uTextures.h"
#include "GL.h"
#include "uUtils.h"
#include "uVariables.h"
#include "uConsts.h"
#include "uDebug.h"
#include "uConsole.h"
#include "uLandUtils.h"
static const string255 __str6 = STRINIT(" priority=");
static const string255 __str5 = STRINIT(" height=");
static const string255 __str4 = STRINIT("Texture not freed: width=");
static const string255 __str3 = STRINIT("FIXME FIXME FIXME. App shutdown without full cleanup of texture list; read game0.log and please report this problem");
static const string255 __str2 = STRINIT("Lock surface");
static const string255 __str1 = STRINIT("Surface2Tex failed, expecting 32 bit surface");
static const string255 __str0 = STRINIT("Surface2Tex: nil surface (missing asset), returning nil");
static PTexture TextureList;
void utextures_SetTextureParameters(boolean enableClamp)
{
    if(enableClamp && ((cReducedQuality & rqClampLess) == 0))
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
};
void utextures_ResetVertexArrays(PTexture texture)
{
    {
        (*texture).vb[0].X = 0;
        (*texture).vb[0].Y = 0;
        (*texture).vb[1].X = (*texture).w;
        (*texture).vb[1].Y = 0;
        (*texture).vb[2].X = (*texture).w;
        (*texture).vb[2].Y = (*texture).h;
        (*texture).vb[3].X = 0;
        (*texture).vb[3].Y = (*texture).h;
        (*texture).tb[0].X = 0;
        (*texture).tb[0].Y = 0;
        (*texture).tb[1].X = (*texture).rx;
        (*texture).tb[1].Y = 0;
        (*texture).tb[2].X = (*texture).rx;
        (*texture).tb[2].Y = (*texture).ry;
        (*texture).tb[3].X = 0;
        (*texture).tb[3].Y = (*texture).ry;
    }
};
PTexture utextures_NewTexture(LongWord width,LongWord height,pointer buf)
{
    PTexture newtexture_result;
    fpcrtl_new(newtexture_result);
    newtexture_result->PrevTexture = NULL;
    newtexture_result->NextTexture = NULL;
    if(TextureList != NULL)
    {
        TextureList->PrevTexture = newtexture_result;
        newtexture_result->NextTexture = TextureList;
    }
    TextureList = newtexture_result;
    newtexture_result->scale = 1;
    newtexture_result->priority = 0;
    newtexture_result->w = width;
    newtexture_result->h = height;
    newtexture_result->rx = 1.0;
    newtexture_result->ry = 1.0;
    utextures_ResetVertexArrays(newtexture_result);
    glGenTextures(1, &(newtexture_result->id));
    glBindTexture(GL_TEXTURE_2D, newtexture_result->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
    utextures_SetTextureParameters(true);
    return newtexture_result;
};
void utextures_Surface2GrayScale(PSDL_Surface surf)
{
    LongWord tw;
    LongWord x;
    LongWord y;
    PLongWordArray fromP4;
    fromP4 = surf->pixels;
    {y = 0;
     LongWord y__end__ = ((int)(surf->h) - 1);
     if (y <= y__end__) do {
                               {x = 0;
                                LongWord x__end__ = ((int)(surf->w) - 1);
                                if (x <= x__end__) do {
                                                          tw = (*fromP4)[x];
                                                          tw = fpcrtl_round(((((tw >> RShift) & 0xff) * RGB_LUMINANCE_RED) + (((tw >> GShift) & 0xff) * RGB_LUMINANCE_GREEN)) + (((tw >> BShift) & 0xff) * RGB_LUMINANCE_BLUE));
                                                          if(tw > 255)
                                                          {
                                                              tw = 255;
                                                          }
                                                          tw = ((((tw & 0xff) << RShift) | ((tw & 0xff) << BShift)) | ((tw & 0xff) << GShift)) | ((*fromP4)[x] & AMask);
                                                          (*fromP4)[x] = tw;
                                                      } while(x++ != x__end__);}
                               fromP4 = ((PLongWordArray)&((*fromP4)[surf->pitch / 4]));
                           } while(y++ != y__end__);}
};
void utextures_PrettifyAlpha(PLongWordArray row1,PLongWordArray row2,LongWord firsti,LongWord lasti,LongWord ioffset)
{
    LongWord i;
    boolean lpi;
    boolean cpi;
    boolean bpi;
    lpi = true;
    {i = firsti;
     LongWord i__end__ = lasti;
     if (i <= i__end__) do {
                               if(i == firsti)
                               {
                                   cpi = ((*row1)[i] & AMask) == 0;
                               }
                               else
                               {
                                   cpi = ((*row1)[i] & AMask) == 0;
                                   if(cpi != lpi)
                                   {
                                       if(cpi)
                                       {
                                           (*row1)[i] = (*row1)[i - 1] & ~AMask;
                                           lpi = cpi;
                                           continue;
                                       }
                                       else
                                       {
                                           (*row1)[i - 1] = (*row1)[i] & ~AMask;
                                       }
                                   }
                               }
                               lpi = cpi;
                               if(row2 != NULL)
                               {
                                   bpi = ((*row2)[i + ioffset] & AMask) == 0;
                                   if(cpi != bpi)
                                   {
                                       if(cpi)
                                       {
                                           (*row1)[i] = (*row2)[i + ioffset] & ~AMask;
                                       }
                                       else
                                       {
                                           (*row2)[i + ioffset] = (*row1)[i] & ~AMask;
                                       }
                                   }
                               }
                           } while(i++ != i__end__);}
};
void utextures_PrettifySurfaceAlpha(PSDL_Surface surf,PLongWordArray pixels)
{
    LongWord r;
    LongWord slr;
    LongWord w;
    LongWord si;
    LongWord li;
    w = surf->w;
    if((w < 2) && (surf->h < 2))
    {
        return;
    }
    slr = surf->h - 2;
    si = 0;
    li = w - 1;
    {r = 0;
     LongWord r__end__ = slr;
     if (r <= r__end__) do {
                               utextures_PrettifyAlpha(pixels, pixels, si, li, w);
                               si = si + w;
                               li = li + w;
                           } while(r++ != r__end__);}
    utextures_PrettifyAlpha(pixels, NULL, si, li, w);
};
void utextures_PrettifyAlpha2D(LongWord height,LongWord width)
{
    LongWord y;
    LongWord lx;
    LongWord sly;
    sly = height - 2;
    lx = width - 1;
    {y = 0;
     LongWord y__end__ = sly;
     if (y <= y__end__) do {
                               utextures_PrettifyAlpha(ulandutils_LandPixelRow(y), ulandutils_LandPixelRow(y + 1), 0, lx, 0);
                           } while(y++ != y__end__);}
    utextures_PrettifyAlpha(ulandutils_LandPixelRow(sly + 1), NULL, 0, lx, 0);
};
PTexture utextures_Surface2Tex(PSDL_Surface surf,boolean enableClamp)
{
    PTexture surface2tex_result;
    LongWord tw;
    LongWord th;
    LongWord x;
    LongWord y;
    pointer tmpp;
    PLongWordArray fromP4;
    PLongWordArray toP4;
    if(cOnlyStats)
    {
        return NULL;
    }
    if(surf == NULL)
    {
        uconsole_WriteLnToConsole(__str0);
        return NULL;
    }
    fpcrtl_new(surface2tex_result);
    surface2tex_result->PrevTexture = NULL;
    surface2tex_result->NextTexture = NULL;
    if(TextureList != NULL)
    {
        TextureList->PrevTexture = surface2tex_result;
        surface2tex_result->NextTexture = TextureList;
    }
    TextureList = surface2tex_result;
    surface2tex_result->scale = 1;
    surface2tex_result->priority = 0;
    surface2tex_result->w = surf->w;
    surface2tex_result->h = surf->h;
    if((*surf->format).BytesPerPixel != 4)
    {
        udebug_checkFails(false, __str1, true);
        surface2tex_result->id = 0;
        return surface2tex_result;
    }
    glGenTextures(1, &(surface2tex_result->id));
    glBindTexture(GL_TEXTURE_2D, surface2tex_result->id);
    if(sdlh_SDL_MustLock(surf))
    {
        if(udebug_SDLCheck(SDL_LockSurface(surf) >= 0, __str2, true))
        {
            return NULL;
        }
    }
    fromP4 = surf->pixels;
    if(GrayScale)
    {
        utextures_Surface2GrayScale(surf);
    }
    utextures_PrettifySurfaceAlpha(surf, fromP4);
    if(!SupportNPOTT && !(uutils_isPowerOf2(surf->w) && uutils_isPowerOf2(surf->h)))
    {
        tw = uutils_toPowerOf2(surf->w);
        th = uutils_toPowerOf2(surf->h);
        surface2tex_result->rx = surf->w /(float) tw;
        surface2tex_result->ry = surf->h /(float) th;
        tmpp = fpcrtl_GetMem((tw * th) * (*surf->format).BytesPerPixel);
        fromP4 = surf->pixels;
        toP4 = tmpp;
        {y = 0;
         LongWord y__end__ = ((int)(surf->h) - 1);
         if (y <= y__end__) do {
                                   {x = 0;
                                    LongWord x__end__ = ((int)(surf->w) - 1);
                                    if (x <= x__end__) do {
                                                              (*toP4)[x] = (*fromP4)[x];
                                                          } while(x++ != x__end__);}
                                   {x = surf->w;
                                    LongWord x__end__ = ((int)(tw) - 1);
                                    if (x <= x__end__) do {
                                                              (*toP4)[x] = (*fromP4)[0];
                                                          } while(x++ != x__end__);}
                                   toP4 = ((PLongWordArray)&((*toP4)[tw]));
                                   fromP4 = ((PLongWordArray)&((*fromP4)[surf->pitch / 4]));
                               } while(y++ != y__end__);}
        {y = surf->h;
         LongWord y__end__ = ((int)(th) - 1);
         if (y <= y__end__) do {
                                   {x = 0;
                                    LongWord x__end__ = ((int)(tw) - 1);
                                    if (x <= x__end__) do {
                                                              (*toP4)[x] = 0;
                                                          } while(x++ != x__end__);}
                                   toP4 = ((PLongWordArray)&((*toP4)[tw]));
                               } while(y++ != y__end__);}
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, tmpp);
        fpcrtl_FreeMem(tmpp, (tw * th) * (*surf->format).BytesPerPixel);
    }
    else
    {
        surface2tex_result->rx = 1.0;
        surface2tex_result->ry = 1.0;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
    }
    utextures_ResetVertexArrays(surface2tex_result);
    if(sdlh_SDL_MustLock(surf))
    {
        SDL_UnlockSurface(surf);
    }
    utextures_SetTextureParameters(enableClamp);
    return surface2tex_result;
};
void utextures_FreeAndNilTexture(PTexture (*tex))
{
    if((*tex) != NULL)
    {
        if((*tex)->NextTexture != NULL)
        {
            (*(*tex)->NextTexture).PrevTexture = (*tex)->PrevTexture;
        }
        if((*tex)->PrevTexture != NULL)
        {
            (*(*tex)->PrevTexture).NextTexture = (*tex)->NextTexture;
        }
        else
        {
            TextureList = (*tex)->NextTexture;
        }
        glDeleteTextures(1, &((*tex)->id));
        fpcrtl_dispose((*tex));
        (*tex) = NULL;
    }
};
void utextures_initModule()
{
    TextureList = NULL;
};
void utextures_freeModule()
{
    PTexture tex;
    if(TextureList != NULL)
    {
        uconsole_WriteToConsole(__str3);
    }
    while(TextureList != NULL)
    {
        tex = TextureList;
        uutils_AddFileLog(_strconcat(_strconcat(_strconcat(_strconcat(_strconcat(__str4, uutils_IntToStr(((LongInt)tex->w))), __str5), uutils_IntToStr(((LongInt)tex->h))), __str6), uutils_IntToStr(fpcrtl_round(tex->priority * 1000))));
        utextures_FreeAndNilTexture(&(tex));
    }
};
