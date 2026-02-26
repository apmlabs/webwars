#include "fpcrtl.h"

#include "uRender.h"
#include "uVariables.h"
#include "uUtils.h"
#include "uConsts.h"
static const string255 __str8 = STRINIT("");
static const string255 __str7 = STRINIT("  |----- Texture Size: ");
static const string255 __str6 = STRINIT("  |----- Version: ");
static const string255 __str5 = STRINIT("  |----- Vendor: ");
static const string255 __str4 = STRINIT("OpenGL-- Renderer: ");
static const string255 __str3 = STRINIT("Texture size too small for backgrounds, disabling.");
static const string255 __str2 = STRINIT("OpenGL Warning - driver didn't provide any valid max texture size; assuming 1024");
static const string255 __str1 = STRINIT("\" skipped");
static const string255 __str0 = STRINIT("OpenGL - \"");
enum{FADE_ANIM_TIME = 500};
enum{MOVE_ANIM_TIME = 500};
typedef TVertex2f VertexBuffer_tt[(59 + 1)];
static VertexBuffer_tt VertexBuffer;
typedef TVertex2f TextureBuffer_tt[(7 + 1)];
static TextureBuffer_tt TextureBuffer;
static LongWord LastTint = 0;
static pointer LastColorPointer;
static pointer LastTexCoordPointer;
static pointer LastVertexPointer;
void urender_openglLoadIdentity_0();
void urender_openglTranslProjMatrix_3(GLfloat X,GLfloat Y,GLfloat Z);
void urender_openglScalef_3(GLfloat ScaleX,GLfloat ScaleY,GLfloat ScaleZ);
void urender_openglRotatef_4(GLfloat RotX,GLfloat RotY,GLfloat RotZ,LongInt dir);
void urender_openglTint_4(Byte r,Byte g,Byte b,Byte a);
boolean urender_isAreaOffscreen(LongInt X,LongInt Y,LongInt Width,LongInt Height)
{
    boolean isareaoffscreen_result;
    isareaoffscreen_result = (urender_isDxAreaOffscreen(X, Width) != 0) || (urender_isDyAreaOffscreen(Y, Height) != 0);
    return isareaoffscreen_result;
};
boolean urender_isCircleOffscreen(LongInt X,LongInt Y,LongInt RadiusSquared)
{
    boolean iscircleoffscreen_result;
    LongInt dRightX;
    LongInt dBottomY;
    LongInt dLeftX;
    LongInt dTopY;
    dRightX = X - ViewRightX;
    dBottomY = Y - ViewBottomY;
    dLeftX = ViewLeftX - X;
    dTopY = ViewTopY - Y;
    iscircleoffscreen_result = ((((dRightX > 0) && (fpcrtl_sqr(dRightX) > RadiusSquared)) || ((dBottomY > 0) && (fpcrtl_sqr(dBottomY) > RadiusSquared))) || ((dLeftX > 0) && (fpcrtl_sqr(dLeftX) > RadiusSquared))) || ((dTopY > 0) && (fpcrtl_sqr(dTopY) > RadiusSquared));
    return iscircleoffscreen_result;
};
LongInt urender_isDxAreaOffscreen(LongInt X,LongInt Width)
{
    LongInt isdxareaoffscreen_result;
    if(X > ViewRightX)
    {
        return 1;
    }
    if((X + Width) < ViewLeftX)
    {
        return -1;
    }
    isdxareaoffscreen_result = 0;
    return isdxareaoffscreen_result;
};
LongInt urender_isDyAreaOffscreen(LongInt Y,LongInt Height)
{
    LongInt isdyareaoffscreen_result;
    if(Y > ViewBottomY)
    {
        return 1;
    }
    if((Y + Height) < ViewTopY)
    {
        return -1;
    }
    isdyareaoffscreen_result = 0;
    return isdyareaoffscreen_result;
};
void urender_RenderClear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};
void urender_RenderSetClearColor(real r,real g,real b,real a)
{
    glClearColor(r, g, b, a);
};
void urender_FinishRender()
{
};
boolean urender_glLoadExtension(string255 extension)
{
    boolean glloadextension_result;
    string255 logmsg;
    UNUSED (extension);
    glloadextension_result = false;
    logmsg = _strconcat(_strconcat(__str0, extension), __str1);
    uutils_AddFileLog(logmsg);
    return glloadextension_result;
};
void urender_RendererCleanup()
{
};
void urender_RendererSetup()
{
    LongInt AuxBufNum = 0;
    astring tmpstr;
    LongInt tmpint;
    LongInt tmpn;
    UNUSED (AuxBufNum);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &(MaxTextureSize));
    if(MaxTextureSize <= 0)
    {
        MaxTextureSize = 1024;
        uutils_AddFileLog(__str2);
    }
    else
    {
        if((MaxTextureSize < 1024) && (MaxTextureSize >= 512))
        {
            cReducedQuality = cReducedQuality | rqNoBackground;
            uutils_AddFileLog(__str3);
        }
    }
    uutils_AddFileLog(_strconcat(__str4, fpcrtl_pchar2str(((PChar)glGetString(GL_RENDERER)))));
    uutils_AddFileLog(_strconcat(__str5, fpcrtl_pchar2str(((PChar)glGetString(GL_VENDOR)))));
    uutils_AddFileLog(_strconcat(__str6, fpcrtl_pchar2str(((PChar)glGetString(GL_VERSION)))));
    uutils_AddFileLog(_strconcat(__str7, uutils_IntToStr(MaxTextureSize)));
    uutils_AddFileLog(__str8);
    defaultFrame = 0;
    glViewport(0, 0, cScreenWidth, cScreenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(2.0 /(float) cScreenWidth, -2.0 /(float) cScreenHeight, 1.0);
    glTranslatef(0, -cScreenHeight /(float) 2, 0);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glDisable(GL_DITHER);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
};
void urender_openglLoadIdentity_0()
{
    glLoadIdentity();
};
void urender_openglTranslProjMatrix_3(GLfloat X,GLfloat Y,GLfloat Z)
{
    glMatrixMode(GL_PROJECTION);
    glTranslatef(X, Y, Z);
    glMatrixMode(GL_MODELVIEW);
};
void urender_openglPushMatrix()
{
    glPushMatrix();
};
void urender_openglPopMatrix()
{
    glPopMatrix();
};
void urender_openglTranslatef(GLfloat X,GLfloat Y,GLfloat Z)
{
    glTranslatef(X, Y, Z);
};
void urender_openglScalef_3(GLfloat ScaleX,GLfloat ScaleY,GLfloat ScaleZ)
{
    glScalef(ScaleX, ScaleY, ScaleZ);
};
void urender_openglRotatef_4(GLfloat RotX,GLfloat RotY,GLfloat RotZ,LongInt dir)
{
    LongInt tmpdir;
    tmpdir = dir;
    glRotatef(RotX, RotY, RotZ, tmpdir);
};
void urender_openglUseColorOnly(boolean b)
{
    if(b)
    {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        LastTexCoordPointer = NULL;
    }
    else
    {
        glDisableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        LastColorPointer = NULL;
    }
    urender_EnableTexture(!b);
};
void urender_UpdateModelviewProjection()
{
};
void urender_SetTexCoordPointer(pointer p,Integer n)
{
    if(p == LastTexCoordPointer)
    {
        return;
    }
    UNUSED (n);
    glTexCoordPointer(2, GL_FLOAT, 0, p);
    LastTexCoordPointer = p;
};
void urender_SetVertexPointer(pointer p,Integer n)
{
    if(p == LastVertexPointer)
    {
        return;
    }
    UNUSED (n);
    glVertexPointer(2, GL_FLOAT, 0, p);
    LastVertexPointer = p;
};
void urender_SetColorPointer(pointer p,Integer n)
{
    if(p == LastColorPointer)
    {
        return;
    }
    UNUSED (n);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, p);
    LastColorPointer = p;
};
void urender_EnableTexture(boolean enable)
{
    if(enable)
    {
        glEnable(GL_TEXTURE_2D);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }
};
void urender_UpdateViewLimits()
{
    LongInt tmp;
    tmp = fpcrtl_round(0.5 + (cScreenWidth /(float) cScaleFactor));
    ViewRightX = tmp;
    ViewLeftX = -tmp;
    tmp = fpcrtl_round(0.5 + (cScreenHeight /(float) cScaleFactor));
    ViewBottomY = tmp + (cScreenHeight / 2);
    ViewTopY = -tmp + (cScreenHeight / 2);
    if(cViewLimitsDebug)
    {
        tmp = fpcrtl_trunc((uutils_Min(cScreenWidth, cScreenHeight) / 2) /(float) cScaleFactor);
        ViewLeftX = ViewLeftX + fpcrtl_trunc(tmp);
        ViewRightX = ViewRightX - fpcrtl_trunc(tmp);
        ViewBottomY = ViewBottomY - fpcrtl_trunc(tmp);
        ViewTopY = ViewTopY + fpcrtl_trunc(tmp);
    }
    ViewWidth = (ViewRightX - ViewLeftX) + 1;
    ViewHeight = (ViewBottomY - ViewTopY) + 1;
};
void urender_SetScale(GLfloat f)
{
    if(f == cScaleFactor)
    {
        return;
    }
    if(f == cDefaultZoomLevel)
    {
        urender_openglPopMatrix();
    }
    else
    {
        if(cScaleFactor == cDefaultZoomLevel)
        {
            urender_openglPushMatrix();
        }
        urender_openglLoadIdentity_0();
        urender_openglScalef_3(f /(float) cScreenWidth, -f /(float) cScreenHeight, 1.0);
        urender_openglTranslatef(0, -cScreenHeight / 2, 0);
    }
    cScaleFactor = f;
    urender_UpdateViewLimits();
    urender_UpdateModelviewProjection();
};
void urender_DrawSpriteFromRect(TSprite Sprite,TSDL_Rect r,LongInt X,LongInt Y,LongInt Height,LongInt Position)
{
    r.y = r.y + (Height * Position);
    r.h = Height;
    urender_DrawTextureFromRect_4(X, Y, &(r), SpritesData[Sprite].Texture);
};
void urender_DrawTextureFromRect_4(LongInt X,LongInt Y,PSDL_Rect r,PTexture SourceTexture)
{
    urender_DrawTextureFromRectDir(X, Y, r->w, r->h, r, SourceTexture, 1);
};
void urender_DrawTextureFromRect_6(LongInt X,LongInt Y,LongInt W,LongInt H,PSDL_Rect r,PTexture SourceTexture)
{
    urender_DrawTextureFromRectDir(X, Y, W, H, r, SourceTexture, 1);
};
void urender_DrawTextureFromRectDir(LongInt X,LongInt Y,LongInt W,LongInt H,PSDL_Rect r,PTexture SourceTexture,LongInt Dir)
{
    real _l;
    real _r;
    real _t;
    real _b;
    LongInt xw;
    LongInt yh;
    if((SourceTexture->h == 0) || (SourceTexture->w == 0))
    {
        return;
    }
    if((fpcrtl_abs(X) > W) && (((fpcrtl_abs(X + (W /(float) 2)) - (W /(float) 2)) * 2) > ViewWidth))
    {
        return;
    }
    if((fpcrtl_abs(Y) > H) && (((fpcrtl_abs((Y + (H /(float) 2)) - (0.5 * cScreenHeight)) - (H /(float) 2)) * 2) > ViewHeight))
    {
        return;
    }
    _l = (r->x /(float) SourceTexture->w) * SourceTexture->rx;
    _r = ((r->x + r->w) /(float) SourceTexture->w) * SourceTexture->rx;
    if(Dir < 0)
    {
        _t = _l;
        _l = _r;
        _r = _t;
    }
    _t = (r->y /(float) SourceTexture->h) * SourceTexture->ry;
    _b = ((r->y + r->h) /(float) SourceTexture->h) * SourceTexture->ry;
    xw = X + W;
    yh = Y + H;
    VertexBuffer[0].X = X;
    VertexBuffer[0].Y = Y;
    VertexBuffer[1].X = xw;
    VertexBuffer[1].Y = Y;
    VertexBuffer[2].X = xw;
    VertexBuffer[2].Y = yh;
    VertexBuffer[3].X = X;
    VertexBuffer[3].Y = yh;
    TextureBuffer[0].X = _l;
    TextureBuffer[0].Y = _t;
    TextureBuffer[1].X = _r;
    TextureBuffer[1].Y = _t;
    TextureBuffer[2].X = _r;
    TextureBuffer[2].Y = _b;
    TextureBuffer[3].X = _l;
    TextureBuffer[3].Y = _b;
    glBindTexture(GL_TEXTURE_2D, SourceTexture->id);
    urender_SetVertexPointer(&(VertexBuffer[0]), 4);
    urender_SetTexCoordPointer(&(TextureBuffer[0]), 4);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
};
void urender_DrawTexture_3(LongInt X,LongInt Y,PTexture Texture)
{
    urender_DrawTexture_4(X, Y, Texture, 1.0);
};
void urender_DrawTexture_4(LongInt X,LongInt Y,PTexture Texture,GLfloat Scale)
{
    urender_openglPushMatrix();
    urender_openglTranslatef(X, Y, 0);
    if(Scale != 1.0)
    {
        urender_openglScalef_3(Scale, Scale, 1);
    }
    glBindTexture(GL_TEXTURE_2D, Texture->id);
    urender_SetVertexPointer(&(Texture->vb), (3 + 1));
    urender_SetTexCoordPointer(&(Texture->tb), (3 + 1));
    urender_UpdateModelviewProjection();
    glDrawArrays(GL_TRIANGLE_FAN, 0, (3 + 1));
    urender_openglPopMatrix();
    urender_UpdateModelviewProjection();
};
void urender_DrawTexture2(LongInt X,LongInt Y,PTexture Texture,GLfloat Scale,GLfloat Overlap)
{
    typedef TVertex2f TextureBuffer_tt[(3 + 1)];
    TextureBuffer_tt TextureBuffer;
    urender_openglPushMatrix();
    urender_openglTranslatef(X, Y, 0);
    urender_openglScalef_3(Scale, Scale, 1);
    glBindTexture(GL_TEXTURE_2D, Texture->id);
    TextureBuffer[0].X = Texture->tb[0].X + Overlap;
    TextureBuffer[0].Y = Texture->tb[0].Y + Overlap;
    TextureBuffer[1].X = Texture->tb[1].X - Overlap;
    TextureBuffer[1].Y = Texture->tb[1].Y + Overlap;
    TextureBuffer[2].X = Texture->tb[2].X - Overlap;
    TextureBuffer[2].Y = Texture->tb[2].Y - Overlap;
    TextureBuffer[3].X = Texture->tb[3].X + Overlap;
    TextureBuffer[3].Y = Texture->tb[3].Y - Overlap;
    urender_SetVertexPointer(&(Texture->vb), 4);
    urender_SetTexCoordPointer(&(TextureBuffer), 4);
    urender_UpdateModelviewProjection();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    urender_openglPopMatrix();
    urender_UpdateModelviewProjection();
};
void urender_DrawTextureF(PTexture Texture,GLfloat Scale,LongInt X,LongInt Y,LongInt Frame,LongInt Dir,LongInt w,LongInt h)
{
    urender_DrawTextureRotatedF(Texture, Scale, 0, 0, X, Y, Frame, Dir, w, h, 0);
};
void urender_DrawTextureRotatedF(PTexture Texture,GLfloat Scale,GLfloat OffsetX,GLfloat OffsetY,LongInt X,LongInt Y,LongInt Frame,LongInt Dir,LongInt w,LongInt h,real Angle)
{
    GLfloat ft;
    GLfloat fb;
    GLfloat fl;
    GLfloat fr;
    LongInt hw;
    LongInt hh;
    LongInt nx;
    LongInt ny;
    if(Scale <= 1)
    {
        if(Angle != 0)
        {
            if((OffsetX == 0) && (OffsetY == 0))
            {
                if(urender_isDxAreaOffscreen(X - w, 2 * w) != 0)
                {
                    return;
                }
                if(urender_isDyAreaOffscreen(Y - h, 2 * h) != 0)
                {
                    return;
                }
            }
        }
        else
        {
            if(urender_isDxAreaOffscreen((X + (Dir * fpcrtl_trunc(OffsetX))) - (w / 2), w) != 0)
            {
                return;
            }
            if(urender_isDyAreaOffscreen((Y + fpcrtl_trunc(OffsetY)) - (h / 2), h) != 0)
            {
                return;
            }
        }
    }
    if(Dir == 0)
    {
        Dir = 1;
    }
    if(Dir > 0)
    {
        hw = w / 2;
    }
    else
    {
        hw = -w / 2;
    }
    hh = h / 2;
    nx = Texture->w / w;
    if(nx == 0)
    {
        nx = 1;
    }
    ny = Texture->h / h;
    if(ny == 0)
    {
        ny = 1;
    }
    ft = ((Frame % ny) * Texture->ry) /(float) ny;
    fb = (((Frame % ny) + 1) * Texture->ry) /(float) ny;
    fl = ((Frame / ny) * Texture->rx) /(float) nx;
    fr = (((Frame / ny) + 1) * Texture->rx) /(float) nx;
    urender_openglPushMatrix();
    urender_openglTranslatef(X, Y, 0);
    if(Angle != 0)
    {
        urender_openglRotatef_4(Angle, 0, 0, Dir);
    }
    if((OffsetX != 0) || (OffsetY != 0))
    {
        urender_openglTranslatef(Dir * OffsetX, OffsetY, 0);
    }
    if(Scale != 1.0)
    {
        urender_openglScalef_3(Scale, Scale, 1);
    }
    glBindTexture(GL_TEXTURE_2D, Texture->id);
    VertexBuffer[0].X = -hw;
    VertexBuffer[0].Y = -hh;
    VertexBuffer[1].X = hw;
    VertexBuffer[1].Y = -hh;
    VertexBuffer[2].X = hw;
    VertexBuffer[2].Y = hh;
    VertexBuffer[3].X = -hw;
    VertexBuffer[3].Y = hh;
    TextureBuffer[0].X = fl;
    TextureBuffer[0].Y = ft;
    TextureBuffer[1].X = fr;
    TextureBuffer[1].Y = ft;
    TextureBuffer[2].X = fr;
    TextureBuffer[2].Y = fb;
    TextureBuffer[3].X = fl;
    TextureBuffer[3].Y = fb;
    urender_SetVertexPointer(&(VertexBuffer[0]), 4);
    urender_SetTexCoordPointer(&(TextureBuffer[0]), 4);
    urender_UpdateModelviewProjection();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    urender_openglPopMatrix();
    urender_UpdateModelviewProjection();
};
void urender_DrawSpriteRotated(TSprite Sprite,LongInt X,LongInt Y,LongInt Dir,real Angle)
{
    urender_DrawTextureRotated(SpritesData[Sprite].Texture, SpritesData[Sprite].Width, SpritesData[Sprite].Height, X, Y, Dir, Angle);
};
void urender_DrawSpriteRotatedF(TSprite Sprite,LongInt X,LongInt Y,LongInt Frame,LongInt Dir,real Angle)
{
    if(Angle != 0)
    {
        if(urender_isCircleOffscreen(X, Y, (fpcrtl_sqr(SpritesData[Sprite].Width) + fpcrtl_sqr(SpritesData[Sprite].Height)) / 4))
        {
            return;
        }
    }
    else
    {
        if(urender_isDxAreaOffscreen(X - (SpritesData[Sprite].Width / 2), SpritesData[Sprite].Width) != 0)
        {
            return;
        }
        if(urender_isDyAreaOffscreen(Y - (SpritesData[Sprite].Height / 2), SpritesData[Sprite].Height) != 0)
        {
            return;
        }
    }
    urender_openglPushMatrix();
    urender_openglTranslatef(X, Y, 0);
    if(Dir < 0)
    {
        urender_openglScalef_3(-1.0, 1.0, 1.0);
    }
    if(Angle != 0)
    {
        urender_openglRotatef_4(Angle, 0, 0, 1);
    }
    urender_UpdateModelviewProjection();
    urender_DrawSprite_4(Sprite, -SpritesData[Sprite].Width / 2, -SpritesData[Sprite].Height / 2, Frame);
    urender_openglPopMatrix();
    urender_UpdateModelviewProjection();
};
void urender_DrawSpriteRotatedFReal(TSprite Sprite,real X,real Y,LongInt Frame,LongInt Dir,real Angle)
{
    if(Angle != 0)
    {
        if(urender_isCircleOffscreen(fpcrtl_round(X), fpcrtl_round(Y), (fpcrtl_sqr(SpritesData[Sprite].Width) + fpcrtl_sqr(SpritesData[Sprite].Height)) / 4))
        {
            return;
        }
    }
    else
    {
        if(urender_isDxAreaOffscreen(fpcrtl_round(X) - (SpritesData[Sprite].Width / 2), SpritesData[Sprite].Width) != 0)
        {
            return;
        }
        if(urender_isDyAreaOffscreen(fpcrtl_round(Y) - (SpritesData[Sprite].Height / 2), SpritesData[Sprite].Height) != 0)
        {
            return;
        }
    }
    urender_openglPushMatrix();
    urender_openglTranslatef(X, Y, 0);
    if(Dir < 0)
    {
        urender_openglScalef_3(-1.0, 1.0, 1.0);
    }
    if(Angle != 0)
    {
        urender_openglRotatef_4(Angle, 0, 0, 1);
    }
    urender_UpdateModelviewProjection();
    urender_DrawSprite_4(Sprite, -SpritesData[Sprite].Width / 2, -SpritesData[Sprite].Height / 2, Frame);
    urender_openglPopMatrix();
    urender_UpdateModelviewProjection();
};
void urender_DrawSpritePivotedF(TSprite Sprite,LongInt X,LongInt Y,LongInt Frame,LongInt Dir,LongInt PivotX,LongInt PivotY,real Angle)
{
    if(Angle != 0)
    {
        if(urender_isCircleOffscreen(X, Y, (9 * (fpcrtl_sqr(SpritesData[Sprite].Width) + fpcrtl_sqr(SpritesData[Sprite].Height))) / 4))
        {
            return;
        }
    }
    else
    {
        if(urender_isDxAreaOffscreen(X - (SpritesData[Sprite].Width / 2), SpritesData[Sprite].Width) != 0)
        {
            return;
        }
        if(urender_isDyAreaOffscreen(Y - (SpritesData[Sprite].Height / 2), SpritesData[Sprite].Height) != 0)
        {
            return;
        }
    }
    urender_openglPushMatrix();
    urender_openglTranslatef(X, Y, 0);
    if(Dir < 0)
    {
        urender_openglScalef_3(-1.0, 1.0, 1.0);
    }
    if(Angle != 0)
    {
        urender_openglTranslatef(PivotX, PivotY, 0);
        urender_openglRotatef_4(Angle, 0, 0, 1);
        urender_openglTranslatef(-PivotX, -PivotY, 0);
    }
    urender_UpdateModelviewProjection();
    urender_DrawSprite_4(Sprite, -SpritesData[Sprite].Width / 2, -SpritesData[Sprite].Height / 2, Frame);
    urender_openglPopMatrix();
    urender_UpdateModelviewProjection();
};
void urender_DrawTextureRotated(PTexture Texture,LongInt hw,LongInt hh,LongInt X,LongInt Y,LongInt Dir,real Angle)
{
    if(urender_isDxAreaOffscreen(X, 2 * hw) != 0)
    {
        return;
    }
    if(urender_isDyAreaOffscreen(Y, 2 * hh) != 0)
    {
        return;
    }
    urender_openglPushMatrix();
    urender_openglTranslatef(X, Y, 0);
    if(Dir < 0)
    {
        hw = -hw;
        urender_openglRotatef_4(Angle, 0, 0, -1);
    }
    else
    {
        urender_openglRotatef_4(Angle, 0, 0, 1);
    }
    glBindTexture(GL_TEXTURE_2D, Texture->id);
    VertexBuffer[0].X = -hw;
    VertexBuffer[0].Y = -hh;
    VertexBuffer[1].X = hw;
    VertexBuffer[1].Y = -hh;
    VertexBuffer[2].X = hw;
    VertexBuffer[2].Y = hh;
    VertexBuffer[3].X = -hw;
    VertexBuffer[3].Y = hh;
    urender_SetVertexPointer(&(VertexBuffer[0]), 4);
    urender_SetTexCoordPointer(&(Texture->tb), 4);
    urender_UpdateModelviewProjection();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    urender_openglPopMatrix();
    urender_UpdateModelviewProjection();
};
void urender_DrawSprite_4(TSprite Sprite,LongInt X,LongInt Y,LongInt Frame)
{
    LongInt row;
    LongInt col;
    LongInt numFramesFirstCol;
    if(SpritesData[Sprite].imageHeight == 0)
    {
        return;
    }
    numFramesFirstCol = SpritesData[Sprite].imageHeight / SpritesData[Sprite].Height;
    row = Frame % numFramesFirstCol;
    col = Frame / numFramesFirstCol;
    urender_DrawSprite_5(Sprite, X, Y, col, row);
};
void urender_DrawSprite_5(TSprite Sprite,LongInt X,LongInt Y,LongInt FrameX,LongInt FrameY)
{
    TSDL_Rect r;
    r.x = FrameX * SpritesData[Sprite].Width;
    r.w = SpritesData[Sprite].Width;
    r.y = FrameY * SpritesData[Sprite].Height;
    r.h = SpritesData[Sprite].Height;
    urender_DrawTextureFromRect_4(X, Y, &(r), SpritesData[Sprite].Texture);
};
void urender_DrawSpriteClipped(TSprite Sprite,LongInt X,LongInt Y,LongInt TopY,LongInt RightX,LongInt BottomY,LongInt LeftX)
{
    TSDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = SpritesData[Sprite].Width;
    r.h = SpritesData[Sprite].Height;
    if(X < LeftX)
    {
        r.x = LeftX - X;
    }
    if(Y < TopY)
    {
        r.y = TopY - Y;
    }
    if((Y + SpritesData[Sprite].Height) > BottomY)
    {
        r.h = (BottomY - Y) + 1;
    }
    if((X + SpritesData[Sprite].Width) > RightX)
    {
        r.w = (RightX - X) + 1;
    }
    if((r.h < r.y) || (r.w < r.x))
    {
        return;
    }
    r.h -= r.y;
    r.w -= r.x;
    urender_DrawTextureFromRect_4(X + r.x, Y + r.y, &(r), SpritesData[Sprite].Texture);
};
void urender_DrawTextureCentered(LongInt X,LongInt Top,PTexture Source)
{
    GLfloat scale;
    LongInt left;
    if((Source->w + 20) > cScreenWidth)
    {
        scale = cScreenWidth /(float) (Source->w + 20);
        urender_DrawTexture_4(X - (fpcrtl_round(Source->w * scale) / 2), Top, Source, scale);
    }
    else
    {
        left = X - (Source->w / 2);
        if(!urender_isAreaOffscreen(left, Top, Source->w, Source->h))
        {
            urender_DrawTexture_3(left, Top, Source);
        }
    }
};
void urender_DrawLine_6(single X0,single Y0,single X1,single Y1,single Width,LongWord color)
{
    urender_DrawLine_9(X0, Y0, X1, Y1, Width, (color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);
};
void urender_DrawLine_9(single X0,single Y0,single X1,single Y1,single Width,Byte r,Byte g,Byte b,Byte a)
{
    urender_openglPushMatrix();
    urender_openglTranslatef(WorldDx, WorldDy, 0);
    urender_UpdateModelviewProjection();
    urender_DrawLineOnScreen(X0, Y0, X1, Y1, Width, r, g, b, a);
    urender_openglPopMatrix();
    urender_UpdateModelviewProjection();
};
void urender_DrawLineWrapped_8(single X0,single Y0,single X1,single Y1,single Width,boolean goesLeft,LongWord Wraps,LongWord color)
{
    urender_DrawLineWrapped_11(X0, Y0, X1, Y1, Width, goesLeft, Wraps, (color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);
};
void urender_DrawLineWrapped_11(single X0,single Y0,single X1,single Y1,single Width,boolean goesLeft,LongWord Wraps,Byte r,Byte g,Byte b,Byte a)
{
    LongWord w;
    single startX;
    single startY;
    single endX;
    single endY;
    single totalX;
    single totalY;
    single x;
    urender_openglPushMatrix();
    urender_openglTranslatef(WorldDx, WorldDy, 0);
    urender_UpdateModelviewProjection();
    startX = X0;
    startY = Y0;
    if(Wraps == 0)
    {
        endX = X1;
        endY = Y1;
        urender_DrawLineOnScreen(startX, startY, endX, endY, Width, r, g, b, a);
    }
    else
    {
        if(goesLeft)
        {
            endX = leftX;
            totalX = (rightX - X1) + (X0 - leftX);
            x = X0 - leftX;
        }
        else
        {
            endX = rightX;
            totalX = (rightX - X0) + (X1 - leftX);
            x = rightX - X0;
        }
        if(Wraps >= 2)
        {
            totalX = totalX + ((rightX - leftX) * (Wraps - 1));
        }
        totalY = Y1 - Y0;
        endY = Y0 + ((totalY /(float) totalX) * x);
        urender_DrawLineOnScreen(startX, startY, endX, endY, Width, r, g, b, a);
        {w = 1;
         LongWord w__end__ = Wraps;
         if (w <= w__end__) do {
                                   startY = endY;
                                   if(goesLeft)
                                   {
                                       startX = rightX;
                                       if(w < Wraps)
                                       {
                                           endX = leftX;
                                       }
                                       else
                                       {
                                           endX = X1;
                                       }
                                   }
                                   else
                                   {
                                       startX = leftX;
                                       if(w < Wraps)
                                       {
                                           endX = rightX;
                                       }
                                       else
                                       {
                                           endX = X1;
                                       }
                                   }
                                   if(w < Wraps)
                                   {
                                       x = x + (rightX - leftX);
                                       endY = Y0 + ((totalY /(float) totalX) * x);
                                   }
                                   else
                                   {
                                       endY = Y1;
                                   }
                                   urender_DrawLineOnScreen(startX, startY, endX, endY, Width, r, g, b, a);
                               } while(w++ != w__end__);}
    }
    urender_openglPopMatrix();
    urender_UpdateModelviewProjection();
};
void urender_DrawLineOnScreen(single X0,single Y0,single X1,single Y1,single Width,Byte r,Byte g,Byte b,Byte a)
{
    glEnable(GL_LINE_SMOOTH);
    urender_EnableTexture(false);
    glLineWidth(Width);
    urender_Tint_4(r, g, b, a);
    VertexBuffer[0].X = X0;
    VertexBuffer[0].Y = Y0;
    VertexBuffer[1].X = X1;
    VertexBuffer[1].Y = Y1;
    urender_SetVertexPointer(&(VertexBuffer[0]), 2);
    glDrawArrays(GL_LINES, 0, 2);
    urender_untint();
    urender_EnableTexture(true);
    glDisable(GL_LINE_SMOOTH);
};
void urender_DrawRect(TSDL_Rect rect,Byte r,Byte g,Byte b,Byte a,boolean Fill)
{
    if((fpcrtl_abs(rect.x) > rect.w) && (((fpcrtl_abs(rect.x + (rect.w /(float) 2)) - (rect.w /(float) 2)) * 2) > ViewWidth))
    {
        return;
    }
    if((fpcrtl_abs(rect.y) > rect.h) && (((fpcrtl_abs((rect.y + (rect.h /(float) 2)) - (cScreenHeight /(float) 2)) - (rect.h /(float) 2)) * 2) > ViewHeight))
    {
        return;
    }
    urender_EnableTexture(false);
    urender_Tint_4(r, g, b, a);
    {
        VertexBuffer[0].X = rect.x;
        VertexBuffer[0].Y = rect.y;
        VertexBuffer[1].X = rect.x + rect.w;
        VertexBuffer[1].Y = rect.y;
        VertexBuffer[2].X = rect.x + rect.w;
        VertexBuffer[2].Y = rect.y + rect.h;
        VertexBuffer[3].X = rect.x;
        VertexBuffer[3].Y = rect.y + rect.h;
    }
    urender_SetVertexPointer(&(VertexBuffer[0]), 4);
    if(Fill)
    {
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    else
    {
        glLineWidth(1);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
    urender_untint();
    urender_EnableTexture(true);
};
void urender_DrawCircle_8(LongInt X,LongInt Y,LongInt Radius,LongInt Width,Byte r,Byte g,Byte b,Byte a)
{
    urender_Tint_4(r, g, b, a);
    urender_DrawCircle_4(X, Y, Radius, Width);
    urender_untint();
};
void urender_DrawCircle_5(LongInt X,LongInt Y,LongInt Radius,LongInt Width,LongWord color)
{
    urender_Tint_1(color);
    urender_DrawCircle_4(X, Y, Radius, Width);
    urender_untint();
};
void urender_DrawCircle_4(LongInt X,LongInt Y,LongInt Radius,LongInt Width)
{
    LongInt i;
    i = Radius + Width;
    if(urender_isDxAreaOffscreen(X - i, 2 * i) != 0)
    {
        return;
    }
    if(urender_isDyAreaOffscreen(Y - i, 2 * i) != 0)
    {
        return;
    }
    {i = 0;
     LongInt i__end__ = 59;
     if (i <= i__end__) do {
                               VertexBuffer[i].X = X + (Radius * cos((i * pi) /(float) 30));
                               VertexBuffer[i].Y = Y + (Radius * sin((i * pi) /(float) 30));
                           } while(i++ != i__end__);}
    urender_EnableTexture(false);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(Width);
    urender_SetVertexPointer(&(VertexBuffer[0]), 60);
    glDrawArrays(GL_LINE_LOOP, 0, 60);
    urender_EnableTexture(true);
    glDisable(GL_LINE_SMOOTH);
};
void urender_DrawCircleFilled(LongInt X,LongInt Y,LongInt Radius,Byte r,Byte g,Byte b,Byte a)
{
    LongInt i;
    VertexBuffer[0].X = X;
    VertexBuffer[0].Y = Y;
    {i = 1;
     LongInt i__end__ = 19;
     if (i <= i__end__) do {
                               VertexBuffer[i].X = X + (Radius * cos((i * pi) /(float) 9));
                               VertexBuffer[i].Y = Y + (Radius * sin((i * pi) /(float) 9));
                           } while(i++ != i__end__);}
    urender_EnableTexture(false);
    urender_Tint_4(r, g, b, a);
    urender_SetVertexPointer(&(VertexBuffer[0]), 20);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
    urender_untint();
    urender_EnableTexture(true);
};
void urender_DrawHedgehog(LongInt X,LongInt Y,LongInt Dir,LongWord Pos,LongWord Step,real Angle)
{
    real l;
    real r;
    real t;
    real b;
    typedef TVertex2f VertexBuffer_tt[(3 + 1)];
    VertexBuffer_tt VertexBuffer = {{
                                        .X = -16,
                                        .Y = -16
                                    },
                                    {
                                        .X = 16,
                                        .Y = -16
                                    },
                                    {
                                        .X = 16,
                                        .Y = 16
                                    },
                                    {
                                        .X = -16,
                                        .Y = 16
                                    }};
    if((fpcrtl_abs(X) > 32) && (((fpcrtl_abs(X) - 16) * 2) > ViewWidth))
    {
        return;
    }
    if((fpcrtl_abs(Y) > 32) && (((fpcrtl_abs(Y - (cScreenHeight /(float) 2)) - 16) * 2) > ViewHeight))
    {
        return;
    }
    t = (Pos * 32) /(float) HHTexture->h;
    b = ((Pos + 1) * 32) /(float) HHTexture->h;
    if(Dir == -1)
    {
        l = ((Step + 1) * 32) /(float) HHTexture->w;
        r = (Step * 32) /(float) HHTexture->w;
    }
    else
    {
        l = (Step * 32) /(float) HHTexture->w;
        r = ((Step + 1) * 32) /(float) HHTexture->w;
    }
    urender_openglPushMatrix();
    urender_openglTranslatef(X, Y, 0);
    urender_openglRotatef_4(Angle, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, HHTexture->id);
    TextureBuffer[0].X = l;
    TextureBuffer[0].Y = t;
    TextureBuffer[1].X = r;
    TextureBuffer[1].Y = t;
    TextureBuffer[2].X = r;
    TextureBuffer[2].Y = b;
    TextureBuffer[3].X = l;
    TextureBuffer[3].Y = b;
    urender_SetVertexPointer(&(VertexBuffer[0]), 4);
    urender_SetTexCoordPointer(&(TextureBuffer[0]), 4);
    urender_UpdateModelviewProjection();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    urender_openglPopMatrix();
    urender_UpdateModelviewProjection();
};
void urender_DrawScreenWidget(POnScreenWidget widget)
{
    Byte alpha = 0xff;
    {
        if((*widget).fadeAnimStart != 0)
        {
            if(RealTicks > ((*widget).fadeAnimStart + FADE_ANIM_TIME))
            {
                (*widget).fadeAnimStart = 0;
            }
            else
            {
                if((*widget).show)
                {
                    alpha = ((Byte)fpcrtl_trunc(((((int64_t) (RealTicks)) - ((int64_t) ((*widget).fadeAnimStart))) /(float) FADE_ANIM_TIME) * 0xff));
                }
                else
                {
                    alpha = ((Byte)0xff - fpcrtl_trunc(((((int64_t) (RealTicks)) - ((int64_t) ((*widget).fadeAnimStart))) /(float) FADE_ANIM_TIME) * 0xff));
                }
            }
        }
        {
            if((*widget).moveAnim.animate)
            {
                if(RealTicks > ((*widget).moveAnim.startTime + MOVE_ANIM_TIME))
                {
                    (*widget).moveAnim.startTime = 0;
                    (*widget).moveAnim.animate = false;
                    (*widget).frame.x = (*widget).moveAnim.target.x;
                    (*widget).frame.y = (*widget).moveAnim.target.y;
                    (*widget).active.x = (*widget).active.x + ((*widget).moveAnim.target.x - (*widget).moveAnim.source.x);
                    (*widget).active.y = (*widget).active.y + ((*widget).moveAnim.target.y - (*widget).moveAnim.source.y);
                }
                else
                {
                    (*widget).frame.x = (*widget).moveAnim.source.x + fpcrtl_round(((*widget).moveAnim.target.x - (*widget).moveAnim.source.x) * ((((int64_t) (RealTicks)) - ((int64_t) ((*widget).moveAnim.startTime))) /(float) MOVE_ANIM_TIME));
                    (*widget).frame.y = (*widget).moveAnim.source.y + fpcrtl_round(((*widget).moveAnim.target.y - (*widget).moveAnim.source.y) * ((((int64_t) (RealTicks)) - ((int64_t) ((*widget).moveAnim.startTime))) /(float) MOVE_ANIM_TIME));
                }
            }
        }
        if((*widget).show || ((*widget).fadeAnimStart != 0))
        {
            urender_Tint_4(0xff, 0xff, 0xff, alpha);
            urender_DrawTexture_4((*widget).frame.x, (*widget).frame.y, SpritesData[(*widget).sprite].Texture, buttonScale);
            urender_untint();
        }
    }
};
void urender_BeginWater()
{
    urender_openglUseColorOnly(true);
};
void urender_EndWater()
{
    urender_openglUseColorOnly(false);
};
void urender_PrepareVbForWater(boolean WithWalls,LongInt InTopY,LongInt OutTopY,LongInt InLeftX,LongInt OutLeftX,LongInt InRightX,LongInt OutRightX,LongInt BottomY,LongInt (*first),LongInt (*count))
{
    LongInt firsti;
    LongInt afteri;
    LongInt lol;
    firsti = -1;
    afteri = 0;
    if(InTopY < 0)
    {
        InTopY = 0;
    }
    if(!WithWalls)
    {
        InLeftX = OutLeftX;
        InRightX = OutRightX;
    }
    else
    {
        if(GameTicks < 2000)
        {
            lol = 2000 - GameTicks;
        }
        else
        {
            lol = 0;
        }
        if(InLeftX > ViewLeftX)
        {
            VertexBuffer[0].X = OutLeftX - lol;
            VertexBuffer[0].Y = OutTopY;
            VertexBuffer[1].X = InLeftX - lol;
            VertexBuffer[1].Y = OutTopY;
            firsti = 0;
            afteri = 4;
        }
        if(InRightX < ViewRightX)
        {
            VertexBuffer[6].X = OutRightX + lol;
            VertexBuffer[6].Y = OutTopY;
            VertexBuffer[7].X = InRightX + lol;
            VertexBuffer[7].Y = OutTopY;
            if(firsti < 0)
            {
                firsti = 4;
            }
            afteri = 8;
        }
    }
    if(InTopY < ViewBottomY)
    {
        if((firsti < 0) || (firsti > 2))
        {
            firsti = 2;
        }
        if(afteri < 6)
        {
            afteri = 6;
        }
    }
    if(firsti < 0)
    {
        (*first) = -1;
        (*count) = 0;
        return;
    }
    if(firsti < 4)
    {
        VertexBuffer[2].X = OutLeftX;
        VertexBuffer[2].Y = BottomY;
        VertexBuffer[3].X = InLeftX;
        VertexBuffer[3].Y = InTopY;
    }
    if(afteri > 4)
    {
        VertexBuffer[4].X = OutRightX;
        VertexBuffer[4].Y = BottomY;
        VertexBuffer[5].X = InRightX;
        VertexBuffer[5].Y = InTopY;
    }
    (*first) = firsti;
    (*count) = afteri - firsti;
};
void urender_DrawWater(Byte Alpha,LongInt OffsetY,LongInt OffsetX)
{
    LongInt first;
    LongInt count;
    if(WorldEdge != weSea)
    {
        urender_PrepareVbForWater(false, (OffsetY + WorldDy) + cWaterLine, 0, 0, ViewLeftX, 0, ViewRightX, ViewBottomY, &(first), &(count));
    }
    else
    {
        urender_PrepareVbForWater(true, (OffsetY + WorldDy) + cWaterLine, ViewTopY, (leftX + WorldDx) - OffsetX, ViewLeftX, (rightX + WorldDx) + OffsetX, ViewRightX, ViewBottomY, &(first), &(count));
    }
    if(count < 1)
    {
        return;
    }
    urender_UpdateModelviewProjection();
    urender_BeginWater();
    if(SuddenDeathDmg)
    {
        if(SDWaterColorArray[0].a != Alpha)
        {
            SDWaterColorArray[0].a = Alpha;
            SDWaterColorArray[1].a = Alpha;
            SDWaterColorArray[2].a = Alpha;
            SDWaterColorArray[3].a = Alpha;
            SDWaterColorArray[4].a = Alpha;
            SDWaterColorArray[5].a = Alpha;
            SDWaterColorArray[6].a = Alpha;
            SDWaterColorArray[7].a = Alpha;
        }
        urender_SetColorPointer(&(SDWaterColorArray[0]), 8);
    }
    else
    {
        if(WaterColorArray[0].a != Alpha)
        {
            WaterColorArray[0].a = Alpha;
            WaterColorArray[1].a = Alpha;
            WaterColorArray[2].a = Alpha;
            WaterColorArray[3].a = Alpha;
            WaterColorArray[4].a = Alpha;
            WaterColorArray[5].a = Alpha;
            WaterColorArray[6].a = Alpha;
            WaterColorArray[7].a = Alpha;
        }
        urender_SetColorPointer(&(WaterColorArray[0]), 8);
    }
    urender_SetVertexPointer(&(VertexBuffer[0]), 8);
    glDrawArrays(GL_TRIANGLE_STRIP, first, count);
    urender_EndWater();
    glColor4ub(0xff, 0xff, 0xff, 0xff);
};
void urender_DrawWaves(LongInt Dir,LongInt dX,LongInt dY,LongInt oX,Byte tnt)
{
    LongInt first;
    LongInt count;
    LongInt topy;
    LongInt lx;
    LongInt rx;
    LongInt spriteHeight;
    LongInt spriteWidth;
    LongInt waterSpeed;
    LongWord waterFrames;
    LongWord waterFrameTicks;
    LongWord frame;
    GLfloat lw;
    GLfloat nWaves;
    GLfloat shift;
    GLfloat realHeight;
    TSprite sprite;
    if(SuddenDeathDmg)
    {
        sprite = sprSDWater;
        waterFrames = watSDFrames;
        waterFrameTicks = watSDFrameTicks;
        waterSpeed = watSDMove;
    }
    else
    {
        sprite = sprWater;
        waterFrames = watFrames;
        waterFrameTicks = watFrameTicks;
        waterSpeed = watMove;
    }
    spriteHeight = SpritesData[sprite].Height;
    realHeight = (*SpritesData[sprite].Texture).ry /(float) waterFrames;
    dY = -cWaveHeight + dY;
    oX = -cWaveHeight + oX;
    lx = (leftX + WorldDx) - oX;
    rx = (rightX + WorldDx) + oX;
    topy = (cWaterLine + WorldDy) + dY;
    if(WorldEdge != weSea)
    {
        urender_PrepareVbForWater(false, topy, 0, 0, ViewLeftX, 0, ViewRightX, topy + spriteHeight, &(first), &(count));
    }
    else
    {
        urender_PrepareVbForWater(true, topy, ViewTopY, lx, lx - spriteHeight, rx, rx + spriteHeight, topy + spriteHeight, &(first), &(count));
    }
    if(count < 1)
    {
        return;
    }
    if(SuddenDeathDmg)
    {
        urender_Tint_4((((((LongInt)tnt) * SDWaterColorArray[1].r) / 255) + 255) - tnt, (((((LongInt)tnt) * SDWaterColorArray[1].g) / 255) + 255) - tnt, (((((LongInt)tnt) * SDWaterColorArray[1].b) / 255) + 255) - tnt, 255);
    }
    else
    {
        urender_Tint_4((((((LongInt)tnt) * WaterColorArray[1].r) / 255) + 255) - tnt, (((((LongInt)tnt) * WaterColorArray[1].g) / 255) + 255) - tnt, (((((LongInt)tnt) * WaterColorArray[1].b) / 255) + 255) - tnt, 255);
    }
    if(WorldEdge == weSea)
    {
        lw = playWidth;
        dX = oX;
    }
    else
    {
        lw = ViewWidth;
        dX = dX - WorldDx;
    }
    spriteWidth = SpritesData[sprite].Width;
    nWaves = lw /(float) spriteWidth;
    shift = -nWaves /(float) 2;
    if(waterFrames > 1)
    {
        frame = (RealTicks / waterFrameTicks) % waterFrames;
    }
    else
    {
        frame = 0;
    }
    TextureBuffer[3].X = shift + ((((((LongInt)((RealTicks * waterSpeed) / 100) >> 6) * Dir) + dX) % spriteWidth) /(float) (spriteWidth - 1));
    TextureBuffer[3].Y = frame * realHeight;
    TextureBuffer[5].X = TextureBuffer[3].X + nWaves;
    TextureBuffer[5].Y = frame * realHeight;
    TextureBuffer[4].X = TextureBuffer[5].X;
    TextureBuffer[4].Y = (frame + 1) * realHeight;
    TextureBuffer[2].X = TextureBuffer[3].X;
    TextureBuffer[2].Y = (frame + 1) * realHeight;
    if(WorldEdge == weSea)
    {
        nWaves = (topy - ViewTopY) /(float) spriteWidth;
        TextureBuffer[1].X = TextureBuffer[3].X - nWaves;
        TextureBuffer[1].Y = frame * realHeight;
        TextureBuffer[0].X = TextureBuffer[1].X;
        TextureBuffer[0].Y = (frame + 1) * realHeight;
        TextureBuffer[7].X = TextureBuffer[5].X + nWaves;
        TextureBuffer[7].Y = frame * realHeight;
        TextureBuffer[6].X = TextureBuffer[7].X;
        TextureBuffer[6].Y = (frame + 1) * realHeight;
    }
    glBindTexture(GL_TEXTURE_2D, (*SpritesData[sprite].Texture).id);
    urender_SetVertexPointer(&(VertexBuffer[0]), 8);
    urender_SetTexCoordPointer(&(TextureBuffer[0]), 8);
    glDrawArrays(GL_TRIANGLE_STRIP, first, count);
    urender_untint();
};
void urender_openglTint_4(Byte r,Byte g,Byte b,Byte a)
{
    glColor4ub(r, g, b, a);
};
void urender_Tint_4(Byte r,Byte g,Byte b,Byte a)
{
    LongWord nc;
    LongWord tw;
    nc = (((r << 24) | (g << 16)) | (b << 8)) | a;
    if(nc == LastTint)
    {
        return;
    }
    if(GrayScale)
    {
        tw = fpcrtl_round(((r * RGB_LUMINANCE_RED) + (g * RGB_LUMINANCE_GREEN)) + (b * RGB_LUMINANCE_BLUE));
        if(tw > 255)
        {
            tw = 255;
        }
        r = tw;
        g = tw;
        b = tw;
    }
    urender_openglTint_4(r, g, b, a);
    LastTint = nc;
};
void urender_Tint_1(LongWord c)
{
    if(c == LastTint)
    {
        return;
    }
    urender_Tint_4((c >> 24) & 0xff, (c >> 16) & 0xff, (c >> 8) & 0xff, c & 0xff);
};
void urender_untint()
{
    if(cWhiteColor == LastTint)
    {
        return;
    }
    urender_openglTint_4(0xff, 0xff, 0xff, 0xff);
    LastTint = cWhiteColor;
};
void urender_setTintAdd(boolean enable)
{
    if(enable)
    {
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
    }
    else
    {
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
};
void urender_ChangeDepth(TRenderMode rm,GLfloat d)
{
    LongInt tmp;
    UNUSED (rm);
    UNUSED (d);
    UNUSED (tmp);
};
void urender_ResetDepth(TRenderMode rm)
{
    LongInt tmp;
    UNUSED (rm);
    UNUSED (tmp);
};
void urender_initModule()
{
    LastTint = cWhiteColor + 1;
    LastColorPointer = NULL;
    LastTexCoordPointer = NULL;
    LastVertexPointer = NULL;
};
void urender_freeModule()
{
    if(cOnlyStats)
    {
        return;
    }
};
