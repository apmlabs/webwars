#include "fpcrtl.h"

#include "uRender.h"
#include "uVariables.h"
#include "uUtils.h"
#include "uMatrix.h"
#include "uConsole.h"
#include "uPhysFSLayer.h"
#include "uDebug.h"
#include "uConsts.h"
static const string255 __str27 = STRINIT("tintAdd");
static const string255 __str26 = STRINIT("enableTexture");
static const string255 __str25 = STRINIT("GL_EXT_framebuffer_object");
static const string255 __str24 = STRINIT("tint");
static const string255 __str23 = STRINIT("default");
static const string255 __str22 = STRINIT("mvp");
static const string255 __str21 = STRINIT("tex0");
static const string255 __str20 = STRINIT("water");
static const string255 __str19 = STRINIT("  |----- Texture Size: ");
static const string255 __str18 = STRINIT("  |----- Version: ");
static const string255 __str17 = STRINIT("  |----- Vendor: ");
static const string255 __str16 = STRINIT("OpenGL-- Renderer: ");
static const string255 __str15 = STRINIT("Texture size too small for backgrounds, disabling.");
static const string255 __str14 = STRINIT("OpenGL Warning - driver didn't provide any valid max texture size; assuming 1024");
static const string255 __str13 = STRINIT("\" skipped");
static const string255 __str12 = STRINIT("OpenGL - \"");
static const string255 __str11 = STRINIT("Linking program failed, halting");
static const string255 __str10 = STRINIT("color");
static const string255 __str9 = STRINIT("texcoord");
static const string255 __str8 = STRINIT("vertex");
static const string255 __str7 = STRINIT(".fs");
static const string255 __str6 = STRINIT(".vs");
static const string255 __str5 = STRINIT("Shader compilation failed, halting");
static const string255 __str4 = STRINIT("===================================");
static const string255 __str3 = STRINIT("========== Compiler log  ==========");
static const string255 __str2 = STRINIT("Compiling shader: ");
static const string255 __str1 = STRINIT("");
static const string255 __str0 = STRINIT("Unable to load ");
static GLuint shaderMain;
static GLuint shaderWater;
typedef TVertex2f VertexBuffer_tt[(59 + 1)];
static VertexBuffer_tt VertexBuffer;
typedef TVertex2f TextureBuffer_tt[(7 + 1)];
static TextureBuffer_tt TextureBuffer;
static LongWord LastTint = 0;
enum{BATCH_MAX_QUADS = 1024};
enum{BATCH_VERTS_PER_QUAD = 6};
enum{BATCH_FLOATS_PER_VERT = 4};
enum{BATCH_BUFFER_SIZE = (((BATCH_MAX_QUADS * BATCH_VERTS_PER_QUAD) * BATCH_FLOATS_PER_VERT) * 4)};
typedef GLfloat batchBuf_tt[((((BATCH_MAX_QUADS * BATCH_VERTS_PER_QUAD) * BATCH_FLOATS_PER_VERT) - 1) + 1)];
static batchBuf_tt batchBuf;
static LongInt batchCount;
static GLuint batchTexId;
static GLuint batchVBO;
static boolean batchInited;
typedef TVertex2f texLRDtb_tt[(3 + 1)];
static texLRDtb_tt texLRDtb;
static texLRDtb_tt texLvb;
static texLRDtb_tt texRvb;
void urender_openglLoadIdentity_0();
void urender_openglTranslProjMatrix_3(GLfloat X,GLfloat Y,GLfloat Z);
void urender_openglScalef_3(GLfloat ScaleX,GLfloat ScaleY,GLfloat ScaleZ);
void urender_openglRotatef_4(GLfloat RotX,GLfloat RotY,GLfloat RotZ,LongInt dir);
void urender_openglTint_4(Byte r,Byte g,Byte b,Byte a);
void urender_CreateFramebuffer_3(GLuint (*frame),GLuint (*depth),GLuint (*tex));
void urender_DeleteFramebuffer_3(GLuint (*frame),GLuint (*depth),GLuint (*tex));
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
void urender_RenderClear_0()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};
void urender_RenderClear_1(TRenderMode mode)
{
    GLuint frame;
    if((cStereoMode == smHorizontal) || (cStereoMode == smVertical))
    {
        switch(mode)
        {case rmLeftEye:frame = framel;
                        break;
         case rmRightEye:frame = framer;
                         break;
         default: frame = defaultFrame;}
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frame);
        urender_RenderClear_0();
    }
    else
    {
        if(mode == rmLeftEye)
        {
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            urender_RenderClear_0();
            if(cStereoMode == smGreenRed)
            {
                glColorMask(GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE);
            }
            else
            {
                if(cStereoMode == smBlueRed)
                {
                    glColorMask(GL_FALSE, GL_FALSE, GL_TRUE, GL_TRUE);
                }
                else
                {
                    if(cStereoMode == smCyanRed)
                    {
                        glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
                    }
                    else
                    {
                        glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
                    }
                }
            }
        }
        else
        {
            if(cStereoMode == smRedGreen)
            {
                glColorMask(GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE);
            }
            else
            {
                if(cStereoMode == smRedBlue)
                {
                    glColorMask(GL_FALSE, GL_FALSE, GL_TRUE, GL_TRUE);
                }
                else
                {
                    if(cStereoMode == smRedCyan)
                    {
                        glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
                    }
                    else
                    {
                        glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
                    }
                }
            }
        }
    }
};
void urender_RenderSetClearColor(real r,real g,real b,real a)
{
    glClearColor(r, g, b, a);
};
void urender_FinishRender()
{
    urender_FlushBatch();
    if((cStereoMode == smHorizontal) || (cStereoMode == smVertical))
    {
        urender_RenderClear_1(rmDefault);
        urender_SetScale(cDefaultZoomLevel);
        urender_SetTexCoordPointer(&(texLRDtb), (3 + 1));
        glBindTexture(GL_TEXTURE_2D, texl);
        urender_SetVertexPointer(&(texLvb), (3 + 1));
        glDrawArrays(GL_TRIANGLE_FAN, 0, (3 + 1));
        glBindTexture(GL_TEXTURE_2D, texl);
        urender_SetVertexPointer(&(texRvb), (3 + 1));
        glDrawArrays(GL_TRIANGLE_FAN, 0, (3 + 1));
        urender_SetScale(zoom);
    }
};
GLuint urender_CompileShader(string255 shaderFile,GLenum shaderType)
{
    GLuint compileshader_result;
    GLuint shader;
    PFSFile f;
    astring source;
    astring line;
    PChar sourceA;
    GLint lengthA;
    GLint compileResult;
    GLint logLength;
    PChar log;
    f = uphysfslayer_pfsOpenRead(_strconcat(_strappend(cPathz[ptShaders], 0x2f), shaderFile));
    udebug_checkFails(f != NULL, _strconcat(__str0, shaderFile), true);
    source = fpcrtl_str2astr(__str1);
    while(!uphysfslayer_pfsEOF(f))
    {
        uphysfslayer_pfsReadLnA(f, &(line));
        source = _strappendA(_strconcatA(source, line), 0xa);
    }
    uphysfslayer_pfsClose(f);
    uconsole_WriteLnToConsole(_strconcat(_strappend(_strconcat(__str2, cPathz[ptShaders]), 0x2f), shaderFile));
    sourceA = fpcrtl__pcharA(source);
    lengthA = fpcrtl_LengthA(source);
    shader = glCreateShader(shaderType);
    fpcrtl_glShaderSource(shader, 1, &(sourceA), &(lengthA));
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &(compileResult));
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &(logLength));
    if(logLength > 1)
    {
        log = fpcrtl_GetMem(logLength);
        glGetShaderInfoLog(shader, logLength, NULL, log);
        uconsole_WriteLnToConsole(__str3);
        uconsole_WriteLnToConsole(fpcrtl_pchar2str(log));
        uconsole_WriteLnToConsole(__str4);
        fpcrtl_FreeMem(log, logLength);
    }
    if(compileResult != GL_TRUE)
    {
        uconsole_WriteLnToConsole(__str5);
        fpcrtl_halt(HaltStartupError);
    }
    compileshader_result = shader;
    return compileshader_result;
};
GLuint urender_CompileProgram(string255 shaderName)
{
    GLuint compileprogram_result;
    GLuint program_;
    GLuint vs;
    GLuint fs;
    GLint linkResult;
    GLint logLength;
    PChar log;
    program_ = glCreateProgram();
    vs = urender_CompileShader(_strconcat(shaderName, __str6), GL_VERTEX_SHADER);
    fs = urender_CompileShader(_strconcat(shaderName, __str7), GL_FRAGMENT_SHADER);
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);
    glBindAttribLocation(program_, aVertex, fpcrtl__pchar(__str8));
    glBindAttribLocation(program_, aTexCoord, fpcrtl__pchar(__str9));
    glBindAttribLocation(program_, aColor, fpcrtl__pchar(__str10));
    glLinkProgram(program_);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glGetProgramiv(program_, GL_LINK_STATUS, &(linkResult));
    glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &(logLength));
    if(logLength > 1)
    {
        log = fpcrtl_GetMem(logLength);
        glGetProgramInfoLog(program_, logLength, NULL, log);
        uconsole_WriteLnToConsole(__str3);
        uconsole_WriteLnToConsole(fpcrtl_pchar2str(log));
        uconsole_WriteLnToConsole(__str4);
        fpcrtl_FreeMem(log, logLength);
    }
    if(linkResult != GL_TRUE)
    {
        uconsole_WriteLnToConsole(__str11);
        fpcrtl_halt(HaltStartupError);
    }
    compileprogram_result = program_;
    return compileprogram_result;
};
boolean urender_glLoadExtension(string255 extension)
{
    boolean glloadextension_result;
    string255 logmsg;
    UNUSED (extension);
    glloadextension_result = false;
    logmsg = _strconcat(_strconcat(__str12, extension), __str13);
    uutils_AddFileLog(logmsg);
    return glloadextension_result;
};
void urender_CreateFramebuffer_3(GLuint (*frame),GLuint (*depth),GLuint (*tex))
{
    glGenFramebuffersEXT(1, &((*frame)));
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, (*frame));
    glGenRenderbuffersEXT(1, &((*depth)));
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, (*depth));
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, cScreenWidth, cScreenHeight);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, (*depth));
    glGenTextures(1, &((*tex)));
    glBindTexture(GL_TEXTURE_2D, (*tex));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, cScreenWidth, cScreenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, (*tex), 0);
};
void urender_DeleteFramebuffer_3(GLuint (*frame),GLuint (*depth),GLuint (*tex))
{
    glDeleteTextures(1, &((*tex)));
    glDeleteRenderbuffersEXT(1, &((*depth)));
    glDeleteFramebuffersEXT(1, &((*frame)));
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
        uutils_AddFileLog(__str14);
    }
    else
    {
        if((MaxTextureSize < 1024) && (MaxTextureSize >= 512))
        {
            cReducedQuality = cReducedQuality | rqNoBackground;
            uutils_AddFileLog(__str15);
        }
    }
    uutils_AddFileLog(_strconcat(__str16, fpcrtl_pchar2str(((PChar)glGetString(GL_RENDERER)))));
    uutils_AddFileLog(_strconcat(__str17, fpcrtl_pchar2str(((PChar)glGetString(GL_VENDOR)))));
    uutils_AddFileLog(_strconcat(__str18, fpcrtl_pchar2str(((PChar)glGetString(GL_VERSION)))));
    uutils_AddFileLog(_strconcat(__str19, uutils_IntToStr(MaxTextureSize)));
    uutils_AddFileLog(__str1);
    defaultFrame = 0;
    shaderWater = urender_CompileProgram(__str20);
    glUseProgram(shaderWater);
    glUniform1i(glGetUniformLocation(shaderWater, fpcrtl__pchar(__str21)), 0);
    uWaterMVPLocation = glGetUniformLocation(shaderWater, fpcrtl__pchar(__str22));
    shaderMain = urender_CompileProgram(__str23);
    glUseProgram(shaderMain);
    glUniform1i(glGetUniformLocation(shaderMain, fpcrtl__pchar(__str21)), 0);
    uMainMVPLocation = glGetUniformLocation(shaderMain, fpcrtl__pchar(__str22));
    uMainTintLocation = glGetUniformLocation(shaderMain, fpcrtl__pchar(__str24));
    uCurrentMVPLocation = uMainMVPLocation;
    urender_Tint_4(255, 255, 255, 255);
    urender_UpdateModelviewProjection();
    if((cStereoMode == smHorizontal) || (cStereoMode == smVertical))
    {
        if(urender_glLoadExtension(__str25))
        {
            urender_CreateFramebuffer_3(&(framel), &(depthl), &(texl));
            urender_CreateFramebuffer_3(&(framer), &(depthr), &(texr));
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, defaultFrame);
        }
        else
        {
            cStereoMode = smNone;
        }
    }
    texLRDtb[0].X = 0.0;
    texLRDtb[0].Y = 0.0;
    texLRDtb[1].X = 1.0;
    texLRDtb[1].Y = 0.0;
    texLRDtb[2].X = 1.0;
    texLRDtb[2].Y = 1.0;
    texLRDtb[3].X = 0.0;
    texLRDtb[3].Y = 1.0;
    if(cStereoMode == smHorizontal)
    {
        texLvb[0].X = cScreenWidth /(float) -2;
        texLvb[0].Y = cScreenHeight;
        texLvb[1].X = 0;
        texLvb[1].Y = cScreenHeight;
        texLvb[2].X = 0;
        texLvb[2].Y = 0;
        texLvb[3].X = cScreenWidth /(float) -2;
        texLvb[3].Y = 0;
        texRvb[0].X = 0;
        texRvb[0].Y = cScreenHeight;
        texRvb[1].X = cScreenWidth /(float) 2;
        texRvb[1].Y = cScreenHeight;
        texRvb[2].X = cScreenWidth /(float) 2;
        texRvb[2].Y = 0;
        texRvb[3].X = 0;
        texRvb[3].Y = 0;
    }
    else
    {
        texLvb[0].X = cScreenWidth /(float) -2;
        texLvb[0].Y = cScreenHeight /(float) 2;
        texLvb[1].X = cScreenWidth /(float) 2;
        texLvb[1].Y = cScreenHeight /(float) 2;
        texLvb[2].X = cScreenWidth /(float) 2;
        texLvb[2].Y = 0;
        texLvb[3].X = cScreenWidth /(float) -2;
        texLvb[3].Y = 0;
        texRvb[0].X = cScreenWidth /(float) -2;
        texRvb[0].Y = cScreenHeight;
        texRvb[1].X = cScreenWidth /(float) 2;
        texRvb[1].Y = cScreenHeight;
        texRvb[2].X = cScreenWidth /(float) 2;
        texRvb[2].Y = cScreenHeight /(float) 2;
        texRvb[3].X = cScreenWidth /(float) -2;
        texRvb[3].Y = cScreenHeight /(float) 2;
    }
    glViewport(0, 0, cScreenWidth, cScreenHeight);
    umatrix_initModule();
    umatrix_hglMatrixMode(MATRIX_MODELVIEW);
    umatrix_hglLoadIdentity();
    umatrix_hglScalef(2.0 /(float) cScreenWidth, -2.0 /(float) cScreenHeight, 1.0);
    umatrix_hglTranslatef(0, -cScreenHeight /(float) 2, 0);
    urender_EnableTexture(true);
    glEnableVertexAttribArray(aVertex);
    glEnableVertexAttribArray(aTexCoord);
    glGenBuffers(1, &(vBuffer));
    glGenBuffers(1, &(tBuffer));
    glGenBuffers(1, &(cBuffer));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
};
void urender_openglLoadIdentity_0()
{
    umatrix_hglLoadIdentity();
};
void urender_openglTranslProjMatrix_3(GLfloat X,GLfloat Y,GLfloat Z)
{
    umatrix_hglMatrixMode(MATRIX_PROJECTION);
    umatrix_hglTranslatef(X, Y, Z);
    umatrix_hglMatrixMode(MATRIX_MODELVIEW);
};
void urender_openglPushMatrix()
{
    umatrix_hglPushMatrix();
};
void urender_openglPopMatrix()
{
    umatrix_hglPopMatrix();
};
void urender_openglTranslatef(GLfloat X,GLfloat Y,GLfloat Z)
{
    umatrix_hglTranslatef(X, Y, Z);
};
void urender_openglScalef_3(GLfloat ScaleX,GLfloat ScaleY,GLfloat ScaleZ)
{
    umatrix_hglScalef(ScaleX, ScaleY, ScaleZ);
};
void urender_openglRotatef_4(GLfloat RotX,GLfloat RotY,GLfloat RotZ,LongInt dir)
{
    LongInt tmpdir;
    tmpdir = dir;
    umatrix_hglRotatef(RotX, RotY, RotZ, tmpdir);
};
void urender_openglUseColorOnly(boolean b)
{
    if(b)
    {
        glDisableVertexAttribArray(aTexCoord);
        glEnableVertexAttribArray(aColor);
    }
    else
    {
        glDisableVertexAttribArray(aColor);
        glEnableVertexAttribArray(aTexCoord);
    }
    urender_EnableTexture(!b);
};
void urender_UpdateModelviewProjection()
{
    TMatrix4x4f mvp;
    umatrix_hglMVP(&(mvp));
    glUniformMatrix4fv(uCurrentMVPLocation, 1, GL_FALSE, &(mvp[0][0]));
};
void urender_FlushBatch()
{
    LongInt count;
    if(batchCount == 0)
    {
        return;
    }
    count = batchCount * BATCH_VERTS_PER_QUAD;
    glBindTexture(GL_TEXTURE_2D, batchTexId);
    glBindBuffer(GL_ARRAY_BUFFER, batchVBO);
    glBufferData(GL_ARRAY_BUFFER, (count * BATCH_FLOATS_PER_VERT) * 4, &(batchBuf[0]), GL_STREAM_DRAW);
    glEnableVertexAttribArray(aVertex);
    glEnableVertexAttribArray(aTexCoord);
    glVertexAttribPointer(aVertex, 2, GL_FLOAT, GL_FALSE, BATCH_FLOATS_PER_VERT * 4, ((pointer)0));
    glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, BATCH_FLOATS_PER_VERT * 4, ((pointer)8));
    urender_UpdateModelviewProjection();
    glDrawArrays(GL_TRIANGLES, 0, count);
    batchCount = 0;
};
void urender_BatchQuad(GLuint texId,GLfloat x0,GLfloat y0,GLfloat u0,GLfloat v0,GLfloat x1,GLfloat y1,GLfloat u1,GLfloat v1,GLfloat x2,GLfloat y2,GLfloat u2,GLfloat v2,GLfloat x3,GLfloat y3,GLfloat u3,GLfloat v3)
{
    LongInt off;
    if(!batchInited)
    {
        glGenBuffers(1, &(batchVBO));
        batchInited = true;
        batchCount = 0;
        batchTexId = 0;
    }
    if((texId != batchTexId) || (batchCount >= BATCH_MAX_QUADS))
    {
        urender_FlushBatch();
        batchTexId = texId;
    }
    off = (batchCount * BATCH_VERTS_PER_QUAD) * BATCH_FLOATS_PER_VERT;
    batchBuf[off] = x0;
    batchBuf[off + 1] = y0;
    batchBuf[off + 2] = u0;
    batchBuf[off + 3] = v0;
    batchBuf[off + 4] = x1;
    batchBuf[off + 5] = y1;
    batchBuf[off + 6] = u1;
    batchBuf[off + 7] = v1;
    batchBuf[off + 8] = x2;
    batchBuf[off + 9] = y2;
    batchBuf[off + 10] = u2;
    batchBuf[off + 11] = v2;
    batchBuf[off + 12] = x0;
    batchBuf[off + 13] = y0;
    batchBuf[off + 14] = u0;
    batchBuf[off + 15] = v0;
    batchBuf[off + 16] = x2;
    batchBuf[off + 17] = y2;
    batchBuf[off + 18] = u2;
    batchBuf[off + 19] = v2;
    batchBuf[off + 20] = x3;
    batchBuf[off + 21] = y3;
    batchBuf[off + 22] = u3;
    batchBuf[off + 23] = v3;
    ++batchCount;
};
void urender_SetTexCoordPointer(pointer p,Integer n)
{
    glBindBuffer(GL_ARRAY_BUFFER, tBuffer);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * n) * 2, p, GL_STATIC_DRAW);
    glEnableVertexAttribArray(aTexCoord);
    glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, ((pointer)0));
};
void urender_SetVertexPointer(pointer p,Integer n)
{
    glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * n) * 2, p, GL_STATIC_DRAW);
    glEnableVertexAttribArray(aVertex);
    glVertexAttribPointer(aVertex, 2, GL_FLOAT, GL_FALSE, 0, ((pointer)0));
};
void urender_SetColorPointer(pointer p,Integer n)
{
    glBindBuffer(GL_ARRAY_BUFFER, cBuffer);
    glBufferData(GL_ARRAY_BUFFER, n * 4, p, GL_STATIC_DRAW);
    glEnableVertexAttribArray(aColor);
    glVertexAttribPointer(aColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, ((pointer)0));
};
void urender_EnableTexture(boolean enable)
{
    if(enable)
    {
        glUniform1i(glGetUniformLocation(shaderMain, fpcrtl__pchar(__str26)), 1);
    }
    else
    {
        glUniform1i(glGetUniformLocation(shaderMain, fpcrtl__pchar(__str26)), 0);
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
    urender_FlushBatch();
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
    urender_BatchQuad(SourceTexture->id, X, Y, _l, _t, xw, Y, _r, _t, xw, yh, _r, _b, X, yh, _l, _b);
};
void urender_DrawTexture_3(LongInt X,LongInt Y,PTexture Texture)
{
    urender_DrawTexture_4(X, Y, Texture, 1.0);
};
void urender_DrawTexture_4(LongInt X,LongInt Y,PTexture Texture,GLfloat Scale)
{
    GLfloat s;
    GLfloat x0;
    GLfloat y0;
    GLfloat x1;
    GLfloat y1;
    s = Scale;
    x0 = X + (Texture->vb[0].X * s);
    y0 = Y + (Texture->vb[0].Y * s);
    x1 = X + (Texture->vb[2].X * s);
    y1 = Y + (Texture->vb[2].Y * s);
    urender_BatchQuad(Texture->id, x0, y0, Texture->tb[0].X, Texture->tb[0].Y, x1, y0, Texture->tb[1].X, Texture->tb[1].Y, x1, y1, Texture->tb[2].X, Texture->tb[2].Y, x0, y1, Texture->tb[3].X, Texture->tb[3].Y);
};
void urender_DrawTexture2(LongInt X,LongInt Y,PTexture Texture,GLfloat Scale,GLfloat Overlap)
{
    GLfloat s;
    GLfloat x0;
    GLfloat y0;
    GLfloat x1;
    GLfloat y1;
    GLfloat tl;
    GLfloat tr;
    GLfloat tt;
    GLfloat tb;
    s = Scale;
    x0 = X + (Texture->vb[0].X * s);
    y0 = Y + (Texture->vb[0].Y * s);
    x1 = X + (Texture->vb[2].X * s);
    y1 = Y + (Texture->vb[2].Y * s);
    tl = Texture->tb[0].X + Overlap;
    tr = Texture->tb[1].X - Overlap;
    tt = Texture->tb[0].Y + Overlap;
    tb = Texture->tb[2].Y - Overlap;
    urender_BatchQuad(Texture->id, x0, y0, tl, tt, x1, y0, tr, tt, x1, y1, tr, tb, x0, y1, tl, tb);
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
    GLfloat sa;
    GLfloat ca;
    GLfloat ox;
    GLfloat oy;
    GLfloat s;
    GLfloat cx0;
    GLfloat cy0;
    GLfloat cx1;
    GLfloat cy1;
    GLfloat cx2;
    GLfloat cy2;
    GLfloat cx3;
    GLfloat cy3;
    GLfloat rx;
    GLfloat ry;
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
    s = Scale;
    cx0 = -hw * s;
    cy0 = -hh * s;
    cx1 = hw * s;
    cy1 = -hh * s;
    cx2 = hw * s;
    cy2 = hh * s;
    cx3 = -hw * s;
    cy3 = hh * s;
    ox = Dir * OffsetX;
    oy = OffsetY;
    cx0 = cx0 + ox;
    cy0 = cy0 + oy;
    cx1 = cx1 + ox;
    cy1 = cy1 + oy;
    cx2 = cx2 + ox;
    cy2 = cy2 + oy;
    cx3 = cx3 + ox;
    cy3 = cy3 + oy;
    if(Angle != 0)
    {
        ca = cos((Angle * Dir) * 1.745329252e-2);
        sa = sin((Angle * Dir) * 1.745329252e-2);
        rx = cx0;
        ry = cy0;
        cx0 = (rx * ca) - (ry * sa);
        cy0 = (rx * sa) + (ry * ca);
        rx = cx1;
        ry = cy1;
        cx1 = (rx * ca) - (ry * sa);
        cy1 = (rx * sa) + (ry * ca);
        rx = cx2;
        ry = cy2;
        cx2 = (rx * ca) - (ry * sa);
        cy2 = (rx * sa) + (ry * ca);
        rx = cx3;
        ry = cy3;
        cx3 = (rx * ca) - (ry * sa);
        cy3 = (rx * sa) + (ry * ca);
    }
    cx0 = cx0 + X;
    cy0 = cy0 + Y;
    cx1 = cx1 + X;
    cy1 = cy1 + Y;
    cx2 = cx2 + X;
    cy2 = cy2 + Y;
    cx3 = cx3 + X;
    cy3 = cy3 + Y;
    urender_BatchQuad(Texture->id, cx0, cy0, fl, ft, cx1, cy1, fr, ft, cx2, cy2, fr, fb, cx3, cy3, fl, fb);
};
void urender_DrawSpriteRotated(TSprite Sprite,LongInt X,LongInt Y,LongInt Dir,real Angle)
{
    urender_DrawTextureRotated(SpritesData[Sprite].Texture, SpritesData[Sprite].Width, SpritesData[Sprite].Height, X, Y, Dir, Angle);
};
void urender_DrawSpriteRotatedF(TSprite Sprite,LongInt X,LongInt Y,LongInt Frame,LongInt Dir,real Angle)
{
    LongInt hw;
    LongInt hh;
    GLfloat ca;
    GLfloat sa;
    GLfloat rx;
    GLfloat ry;
    GLfloat mx;
    GLfloat cx0;
    GLfloat cy0;
    GLfloat cx1;
    GLfloat cy1;
    GLfloat cx2;
    GLfloat cy2;
    GLfloat cx3;
    GLfloat cy3;
    TSDL_Rect r;
    LongInt row;
    LongInt col;
    LongInt numFramesFirstCol;
    GLfloat fl;
    GLfloat fr;
    GLfloat ft;
    GLfloat fb;
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
    hw = SpritesData[Sprite].Width / 2;
    hh = SpritesData[Sprite].Height / 2;
    if(SpritesData[Sprite].imageHeight == 0)
    {
        return;
    }
    numFramesFirstCol = SpritesData[Sprite].imageHeight / SpritesData[Sprite].Height;
    row = Frame % numFramesFirstCol;
    col = Frame / numFramesFirstCol;
    r.x = col * SpritesData[Sprite].Width;
    r.w = SpritesData[Sprite].Width;
    r.y = row * SpritesData[Sprite].Height;
    r.h = SpritesData[Sprite].Height;
    fl = (r.x /(float) (*SpritesData[Sprite].Texture).w) * (*SpritesData[Sprite].Texture).rx;
    fr = ((r.x + r.w) /(float) (*SpritesData[Sprite].Texture).w) * (*SpritesData[Sprite].Texture).rx;
    ft = (r.y /(float) (*SpritesData[Sprite].Texture).h) * (*SpritesData[Sprite].Texture).ry;
    fb = ((r.y + r.h) /(float) (*SpritesData[Sprite].Texture).h) * (*SpritesData[Sprite].Texture).ry;
    cx0 = -hw;
    cy0 = -hh;
    cx1 = hw;
    cy1 = -hh;
    cx2 = hw;
    cy2 = hh;
    cx3 = -hw;
    cy3 = hh;
    if(Angle != 0)
    {
        ca = cos(Angle * 1.745329252e-2);
        sa = sin(Angle * 1.745329252e-2);
        rx = cx0;
        ry = cy0;
        cx0 = (rx * ca) - (ry * sa);
        cy0 = (rx * sa) + (ry * ca);
        rx = cx1;
        ry = cy1;
        cx1 = (rx * ca) - (ry * sa);
        cy1 = (rx * sa) + (ry * ca);
        rx = cx2;
        ry = cy2;
        cx2 = (rx * ca) - (ry * sa);
        cy2 = (rx * sa) + (ry * ca);
        rx = cx3;
        ry = cy3;
        cx3 = (rx * ca) - (ry * sa);
        cy3 = (rx * sa) + (ry * ca);
    }
    if(Dir < 0)
    {
        mx = -1.0;
    }
    else
    {
        mx = 1.0;
    }
    cx0 = cx0 * mx;
    cx1 = cx1 * mx;
    cx2 = cx2 * mx;
    cx3 = cx3 * mx;
    if(Dir < 0)
    {
        rx = fl;
        fl = fr;
        fr = rx;
    }
    cx0 = cx0 + X;
    cy0 = cy0 + Y;
    cx1 = cx1 + X;
    cy1 = cy1 + Y;
    cx2 = cx2 + X;
    cy2 = cy2 + Y;
    cx3 = cx3 + X;
    cy3 = cy3 + Y;
    urender_BatchQuad((*SpritesData[Sprite].Texture).id, cx0, cy0, fl, ft, cx1, cy1, fr, ft, cx2, cy2, fr, fb, cx3, cy3, fl, fb);
};
void urender_DrawSpriteRotatedFReal(TSprite Sprite,real X,real Y,LongInt Frame,LongInt Dir,real Angle)
{
    LongInt hw;
    LongInt hh;
    GLfloat ca;
    GLfloat sa;
    GLfloat rx;
    GLfloat ry;
    GLfloat mx;
    GLfloat cx0;
    GLfloat cy0;
    GLfloat cx1;
    GLfloat cy1;
    GLfloat cx2;
    GLfloat cy2;
    GLfloat cx3;
    GLfloat cy3;
    TSDL_Rect r;
    LongInt row;
    LongInt col;
    LongInt numFramesFirstCol;
    GLfloat fl;
    GLfloat fr;
    GLfloat ft;
    GLfloat fb;
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
    hw = SpritesData[Sprite].Width / 2;
    hh = SpritesData[Sprite].Height / 2;
    if(SpritesData[Sprite].imageHeight == 0)
    {
        return;
    }
    numFramesFirstCol = SpritesData[Sprite].imageHeight / SpritesData[Sprite].Height;
    row = Frame % numFramesFirstCol;
    col = Frame / numFramesFirstCol;
    r.x = col * SpritesData[Sprite].Width;
    r.w = SpritesData[Sprite].Width;
    r.y = row * SpritesData[Sprite].Height;
    r.h = SpritesData[Sprite].Height;
    fl = (r.x /(float) (*SpritesData[Sprite].Texture).w) * (*SpritesData[Sprite].Texture).rx;
    fr = ((r.x + r.w) /(float) (*SpritesData[Sprite].Texture).w) * (*SpritesData[Sprite].Texture).rx;
    ft = (r.y /(float) (*SpritesData[Sprite].Texture).h) * (*SpritesData[Sprite].Texture).ry;
    fb = ((r.y + r.h) /(float) (*SpritesData[Sprite].Texture).h) * (*SpritesData[Sprite].Texture).ry;
    cx0 = -hw;
    cy0 = -hh;
    cx1 = hw;
    cy1 = -hh;
    cx2 = hw;
    cy2 = hh;
    cx3 = -hw;
    cy3 = hh;
    if(Angle != 0)
    {
        ca = cos(Angle * 1.745329252e-2);
        sa = sin(Angle * 1.745329252e-2);
        rx = cx0;
        ry = cy0;
        cx0 = (rx * ca) - (ry * sa);
        cy0 = (rx * sa) + (ry * ca);
        rx = cx1;
        ry = cy1;
        cx1 = (rx * ca) - (ry * sa);
        cy1 = (rx * sa) + (ry * ca);
        rx = cx2;
        ry = cy2;
        cx2 = (rx * ca) - (ry * sa);
        cy2 = (rx * sa) + (ry * ca);
        rx = cx3;
        ry = cy3;
        cx3 = (rx * ca) - (ry * sa);
        cy3 = (rx * sa) + (ry * ca);
    }
    if(Dir < 0)
    {
        mx = -1.0;
    }
    else
    {
        mx = 1.0;
    }
    cx0 = cx0 * mx;
    cx1 = cx1 * mx;
    cx2 = cx2 * mx;
    cx3 = cx3 * mx;
    if(Dir < 0)
    {
        rx = fl;
        fl = fr;
        fr = rx;
    }
    cx0 = cx0 + X;
    cy0 = cy0 + Y;
    cx1 = cx1 + X;
    cy1 = cy1 + Y;
    cx2 = cx2 + X;
    cy2 = cy2 + Y;
    cx3 = cx3 + X;
    cy3 = cy3 + Y;
    urender_BatchQuad((*SpritesData[Sprite].Texture).id, cx0, cy0, fl, ft, cx1, cy1, fr, ft, cx2, cy2, fr, fb, cx3, cy3, fl, fb);
};
void urender_DrawSpritePivotedF(TSprite Sprite,LongInt X,LongInt Y,LongInt Frame,LongInt Dir,LongInt PivotX,LongInt PivotY,real Angle)
{
    LongInt hw;
    LongInt hh;
    GLfloat ca;
    GLfloat sa;
    GLfloat rx;
    GLfloat ry;
    GLfloat mx;
    GLfloat cx0;
    GLfloat cy0;
    GLfloat cx1;
    GLfloat cy1;
    GLfloat cx2;
    GLfloat cy2;
    GLfloat cx3;
    GLfloat cy3;
    TSDL_Rect r;
    LongInt row;
    LongInt col;
    LongInt numFramesFirstCol;
    GLfloat fl;
    GLfloat fr;
    GLfloat ft;
    GLfloat fb;
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
    hw = SpritesData[Sprite].Width / 2;
    hh = SpritesData[Sprite].Height / 2;
    if(SpritesData[Sprite].imageHeight == 0)
    {
        return;
    }
    numFramesFirstCol = SpritesData[Sprite].imageHeight / SpritesData[Sprite].Height;
    row = Frame % numFramesFirstCol;
    col = Frame / numFramesFirstCol;
    r.x = col * SpritesData[Sprite].Width;
    r.w = SpritesData[Sprite].Width;
    r.y = row * SpritesData[Sprite].Height;
    r.h = SpritesData[Sprite].Height;
    fl = (r.x /(float) (*SpritesData[Sprite].Texture).w) * (*SpritesData[Sprite].Texture).rx;
    fr = ((r.x + r.w) /(float) (*SpritesData[Sprite].Texture).w) * (*SpritesData[Sprite].Texture).rx;
    ft = (r.y /(float) (*SpritesData[Sprite].Texture).h) * (*SpritesData[Sprite].Texture).ry;
    fb = ((r.y + r.h) /(float) (*SpritesData[Sprite].Texture).h) * (*SpritesData[Sprite].Texture).ry;
    cx0 = -hw - PivotX;
    cy0 = -hh - PivotY;
    cx1 = hw - PivotX;
    cy1 = -hh - PivotY;
    cx2 = hw - PivotX;
    cy2 = hh - PivotY;
    cx3 = -hw - PivotX;
    cy3 = hh - PivotY;
    if(Angle != 0)
    {
        ca = cos(Angle * 1.745329252e-2);
        sa = sin(Angle * 1.745329252e-2);
        rx = cx0;
        ry = cy0;
        cx0 = (rx * ca) - (ry * sa);
        cy0 = (rx * sa) + (ry * ca);
        rx = cx1;
        ry = cy1;
        cx1 = (rx * ca) - (ry * sa);
        cy1 = (rx * sa) + (ry * ca);
        rx = cx2;
        ry = cy2;
        cx2 = (rx * ca) - (ry * sa);
        cy2 = (rx * sa) + (ry * ca);
        rx = cx3;
        ry = cy3;
        cx3 = (rx * ca) - (ry * sa);
        cy3 = (rx * sa) + (ry * ca);
    }
    cx0 = cx0 + PivotX;
    cy0 = cy0 + PivotY;
    cx1 = cx1 + PivotX;
    cy1 = cy1 + PivotY;
    cx2 = cx2 + PivotX;
    cy2 = cy2 + PivotY;
    cx3 = cx3 + PivotX;
    cy3 = cy3 + PivotY;
    if(Dir < 0)
    {
        mx = -1.0;
    }
    else
    {
        mx = 1.0;
    }
    cx0 = cx0 * mx;
    cx1 = cx1 * mx;
    cx2 = cx2 * mx;
    cx3 = cx3 * mx;
    if(Dir < 0)
    {
        rx = fl;
        fl = fr;
        fr = rx;
    }
    cx0 = cx0 + X;
    cy0 = cy0 + Y;
    cx1 = cx1 + X;
    cy1 = cy1 + Y;
    cx2 = cx2 + X;
    cy2 = cy2 + Y;
    cx3 = cx3 + X;
    cy3 = cy3 + Y;
    urender_BatchQuad((*SpritesData[Sprite].Texture).id, cx0, cy0, fl, ft, cx1, cy1, fr, ft, cx2, cy2, fr, fb, cx3, cy3, fl, fb);
};
void urender_DrawTextureRotated(PTexture Texture,LongInt hw,LongInt hh,LongInt X,LongInt Y,LongInt Dir,real Angle)
{
    GLfloat ca;
    GLfloat sa;
    GLfloat rx;
    GLfloat ry;
    GLfloat cx0;
    GLfloat cy0;
    GLfloat cx1;
    GLfloat cy1;
    GLfloat cx2;
    GLfloat cy2;
    GLfloat cx3;
    GLfloat cy3;
    if(urender_isDxAreaOffscreen(X, 2 * hw) != 0)
    {
        return;
    }
    if(urender_isDyAreaOffscreen(Y, 2 * hh) != 0)
    {
        return;
    }
    if(Dir < 0)
    {
        hw = -hw;
    }
    cx0 = -hw;
    cy0 = -hh;
    cx1 = hw;
    cy1 = -hh;
    cx2 = hw;
    cy2 = hh;
    cx3 = -hw;
    cy3 = hh;
    if(Angle != 0)
    {
        if(Dir < 0)
        {
            ca = cos(-Angle * 1.745329252e-2);
            sa = sin(-Angle * 1.745329252e-2);
        }
        else
        {
            ca = cos(Angle * 1.745329252e-2);
            sa = sin(Angle * 1.745329252e-2);
        }
        rx = cx0;
        ry = cy0;
        cx0 = (rx * ca) - (ry * sa);
        cy0 = (rx * sa) + (ry * ca);
        rx = cx1;
        ry = cy1;
        cx1 = (rx * ca) - (ry * sa);
        cy1 = (rx * sa) + (ry * ca);
        rx = cx2;
        ry = cy2;
        cx2 = (rx * ca) - (ry * sa);
        cy2 = (rx * sa) + (ry * ca);
        rx = cx3;
        ry = cy3;
        cx3 = (rx * ca) - (ry * sa);
        cy3 = (rx * sa) + (ry * ca);
    }
    urender_BatchQuad(Texture->id, cx0 + X, cy0 + Y, Texture->tb[0].X, Texture->tb[0].Y, cx1 + X, cy1 + Y, Texture->tb[1].X, Texture->tb[1].Y, cx2 + X, cy2 + Y, Texture->tb[2].X, Texture->tb[2].Y, cx3 + X, cy3 + Y, Texture->tb[3].X, Texture->tb[3].Y);
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
    urender_FlushBatch();
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
    urender_FlushBatch();
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
    urender_FlushBatch();
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
    GLfloat ca;
    GLfloat sa;
    GLfloat rx;
    GLfloat ry;
    GLfloat cx0;
    GLfloat cy0;
    GLfloat cx1;
    GLfloat cy1;
    GLfloat cx2;
    GLfloat cy2;
    GLfloat cx3;
    GLfloat cy3;
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
    cx0 = -16;
    cy0 = -16;
    cx1 = 16;
    cy1 = -16;
    cx2 = 16;
    cy2 = 16;
    cx3 = -16;
    cy3 = 16;
    if(Angle != 0)
    {
        ca = cos(Angle * 1.745329252e-2);
        sa = sin(Angle * 1.745329252e-2);
        rx = cx0;
        ry = cy0;
        cx0 = (rx * ca) - (ry * sa);
        cy0 = (rx * sa) + (ry * ca);
        rx = cx1;
        ry = cy1;
        cx1 = (rx * ca) - (ry * sa);
        cy1 = (rx * sa) + (ry * ca);
        rx = cx2;
        ry = cy2;
        cx2 = (rx * ca) - (ry * sa);
        cy2 = (rx * sa) + (ry * ca);
        rx = cx3;
        ry = cy3;
        cx3 = (rx * ca) - (ry * sa);
        cy3 = (rx * sa) + (ry * ca);
    }
    urender_BatchQuad(HHTexture->id, cx0 + X, cy0 + Y, l, t, cx1 + X, cy1 + Y, r, t, cx2 + X, cy2 + Y, r, b, cx3 + X, cy3 + Y, l, b);
};
void urender_DrawScreenWidget(POnScreenWidget widget)
{
    UNUSED (widget);
};
void urender_BeginWater()
{
    urender_FlushBatch();
    glUseProgram(shaderWater);
    uCurrentMVPLocation = uWaterMVPLocation;
    urender_UpdateModelviewProjection();
    urender_openglUseColorOnly(true);
};
void urender_EndWater()
{
    glUseProgram(shaderMain);
    uCurrentMVPLocation = uMainMVPLocation;
    urender_UpdateModelviewProjection();
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
    urender_FlushBatch();
    glBindTexture(GL_TEXTURE_2D, (*SpritesData[sprite].Texture).id);
    urender_SetVertexPointer(&(VertexBuffer[0]), 8);
    urender_SetTexCoordPointer(&(TextureBuffer[0]), 8);
    glDrawArrays(GL_TRIANGLE_STRIP, first, count);
    urender_untint();
};
void urender_openglTint_4(Byte r,Byte g,Byte b,Byte a)
{
    real scale = (1.0 /(float) 255.0);
    glUniform4f(uMainTintLocation, r * scale, g * scale, b * scale, a * scale);
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
    urender_FlushBatch();
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
    urender_FlushBatch();
    urender_openglTint_4(0xff, 0xff, 0xff, 0xff);
    LastTint = cWhiteColor;
};
void urender_setTintAdd(boolean enable)
{
    urender_FlushBatch();
    if(enable)
    {
        glUniform1i(glGetUniformLocation(shaderMain, fpcrtl__pchar(__str27)), 1);
    }
    else
    {
        glUniform1i(glGetUniformLocation(shaderMain, fpcrtl__pchar(__str27)), 0);
    }
};
void urender_ChangeDepth(TRenderMode rm,GLfloat d)
{
    LongInt tmp;
    d = d /(float) 5;
    if(rm == rmDefault)
    {
        return;
    }
    else
    {
        if(rm == rmLeftEye)
        {
            d = -d;
        }
    }
    cStereoDepth = cStereoDepth + d;
    urender_openglTranslProjMatrix_3(d, 0, 0);
    tmp = fpcrtl_round((d /(float) cScaleFactor) * cScreenWidth);
    ViewLeftX = ViewLeftX - tmp;
    ViewRightX = ViewRightX - tmp;
};
void urender_ResetDepth(TRenderMode rm)
{
    LongInt tmp;
    if(rm == rmDefault)
    {
        return;
    }
    urender_openglTranslProjMatrix_3(-cStereoDepth, 0, 0);
    tmp = fpcrtl_round((cStereoDepth /(float) cScaleFactor) * cScreenWidth);
    ViewLeftX = ViewLeftX + tmp;
    ViewRightX = ViewRightX + tmp;
    cStereoDepth = 0;
};
void urender_initModule()
{
    LastTint = cWhiteColor + 1;
    batchInited = false;
    batchCount = 0;
    batchTexId = 0;
};
void urender_freeModule()
{
    if(cOnlyStats)
    {
        return;
    }
    if(batchInited)
    {
        glDeleteBuffers(1, &(batchVBO));
    }
    glDeleteProgram(shaderMain);
    glDeleteProgram(shaderWater);
    glDeleteBuffers(1, &(vBuffer));
    glDeleteBuffers(1, &(tBuffer));
    glDeleteBuffers(1, &(cBuffer));
};
