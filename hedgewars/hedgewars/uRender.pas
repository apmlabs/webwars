(*
 * Hedgewars, a free turn based strategy game
 * Copyright (c) 2004-2015 Andrey Korotaev <unC0Rr@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *)

{$INCLUDE "options.inc"}
{$IF GLunit = GL}{$DEFINE GLunit:=GL,GLext}{$ENDIF}

unit uRender;

interface

uses SDLh, uTypes, GLunit;

procedure initModule;
procedure freeModule;

procedure DrawSprite            (Sprite: TSprite; X, Y, Frame: LongInt);
procedure DrawSprite            (Sprite: TSprite; X, Y, FrameX, FrameY: LongInt);
procedure DrawSpriteFromRect    (Sprite: TSprite; r: TSDL_Rect; X, Y, Height, Position: LongInt); 
procedure DrawSpriteClipped     (Sprite: TSprite; X, Y, TopY, RightX, BottomY, LeftX: LongInt);
procedure DrawSpriteRotated     (Sprite: TSprite; X, Y, Dir: LongInt; Angle: real);
procedure DrawSpriteRotatedF    (Sprite: TSprite; X, Y, Frame, Dir: LongInt; Angle: real);
procedure DrawSpriteRotatedFReal(Sprite: TSprite; X, Y: Real; Frame, Dir: LongInt; Angle: real);
procedure DrawSpritePivotedF(Sprite: TSprite; X, Y, Frame, Dir, PivotX, PivotY: LongInt; Angle: real);

procedure DrawTexture           (X, Y: LongInt; Texture: PTexture); 
procedure DrawTexture           (X, Y: LongInt; Texture: PTexture; Scale: GLfloat);
procedure DrawTexture2          (X, Y: LongInt; Texture: PTexture; Scale, Overlap: GLfloat);
procedure DrawTextureFromRect   (X, Y: LongInt; r: PSDL_Rect; SourceTexture: PTexture); 
procedure DrawTextureFromRect   (X, Y, W, H: LongInt; r: PSDL_Rect; SourceTexture: PTexture); 
procedure DrawTextureFromRectDir(X, Y, W, H: LongInt; r: PSDL_Rect; SourceTexture: PTexture; Dir: LongInt);
procedure DrawTextureCentered   (X, Top: LongInt; Source: PTexture);
procedure DrawTextureF          (Texture: PTexture; Scale: GLfloat; X, Y, Frame, Dir, w, h: LongInt);
procedure DrawTextureRotated    (Texture: PTexture; hw, hh, X, Y, Dir: LongInt; Angle: real);
procedure DrawTextureRotatedF   (Texture: PTexture; Scale, OffsetX, OffsetY: GLfloat; X, Y, Frame, Dir, w, h: LongInt; Angle: real);

procedure DrawCircle            (X, Y, Radius, Width: LongInt);
procedure DrawCircle            (X, Y, Radius, Width: LongInt; r, g, b, a: Byte);
procedure DrawCircle            (X, Y, Radius, Width: LongInt; color: LongWord);
procedure DrawCircleFilled      (X, Y, Radius: LongInt; r, g, b, a: Byte);

procedure DrawLine              (X0, Y0, X1, Y1, Width: Single; color: LongWord); 
procedure DrawLine              (X0, Y0, X1, Y1, Width: Single; r, g, b, a: Byte);
procedure DrawLineWrapped       (X0, Y0, X1, Y1, Width: Single; goesLeft: boolean; Wraps: LongWord; color: LongWord); 
procedure DrawLineWrapped       (X0, Y0, X1, Y1, Width: Single; goesLeft: boolean; Wraps: LongWord; r, g, b, a: Byte);
procedure DrawLineOnScreen      (X0, Y0, X1, Y1, Width: Single; r, g, b, a: Byte);
procedure DrawRect              (rect: TSDL_Rect; r, g, b, a: Byte; Fill: boolean);
procedure DrawHedgehog          (X, Y: LongInt; Dir: LongInt; Pos, Step: LongWord; Angle: real);
procedure DrawScreenWidget      (widget: POnScreenWidget);
procedure DrawWater             (Alpha: byte; OffsetY, OffsetX: LongInt);
procedure DrawWaves             (Dir, dX, dY, oX: LongInt; tnt: Byte);

procedure RenderClear           ();
{$IFDEF USE_S3D_RENDERING}
procedure RenderClear           (mode: TRenderMode);
{$ENDIF}
procedure RenderSetClearColor   (r, g, b, a: real);
procedure Tint                  (r, g, b, a: Byte);
procedure Tint                  (c: Longword); 
procedure untint(); 
procedure setTintAdd            (enable: boolean); 

// call this to finish the rendering of current frame
procedure FinishRender();

{$IFDEF GL2}
procedure FlushBatch();
{$ENDIF}

function isAreaOffscreen(X, Y, Width, Height: LongInt): boolean; 
function isCircleOffscreen(X, Y, RadiusSquared: LongInt): boolean; 

// 0 => not offscreen, <0 => left/top of screen >0 => right/below of screen
function isDxAreaOffscreen(X, Width: LongInt): LongInt; 
function isDyAreaOffscreen(Y, Height: LongInt): LongInt; 

procedure SetScale(f: GLfloat);
procedure UpdateViewLimits();

procedure RendererSetup();
procedure RendererCleanup();

procedure ChangeDepth(rm: TRenderMode; d: GLfloat);
procedure ResetDepth(rm: TRenderMode);

// TODO everything below this should not need a public interface

procedure EnableTexture(enable:Boolean);

procedure SetTexCoordPointer(p: Pointer;n: Integer); 
procedure SetVertexPointer(p: Pointer;n: Integer); 
procedure SetColorPointer(p: Pointer;n: Integer); 

procedure UpdateModelviewProjection(); 

procedure openglPushMatrix      (); 
procedure openglPopMatrix       (); 
procedure openglTranslatef      (X, Y, Z: GLfloat); 


implementation
uses {$IFNDEF PAS2C} StrUtils, {$ENDIF}uVariables, uUtils
     {$IFDEF GL2}, uMatrix, uConsole, uPhysFSLayer, uDebug{$ENDIF}, uConsts;

{$IFDEF USE_TOUCH_INTERFACE}
const
    FADE_ANIM_TIME = 500;
    MOVE_ANIM_TIME = 500;
{$ENDIF}

{$IFDEF GL2}
var
    shaderMain: GLuint;
    shaderWater: GLuint;
{$ENDIF}

var VertexBuffer : array [0 ..59] of TVertex2f;
    TextureBuffer: array [0 .. 7] of TVertex2f;
    LastTint: LongWord = 0;
{$IFNDEF GL2}
    LastColorPointer , LastTexCoordPointer , LastVertexPointer : Pointer;
{$ENDIF}

{$IFDEF GL2}
{ ── Sprite Batch System ── }
const
    BATCH_MAX_QUADS = 1024;
    BATCH_VERTS_PER_QUAD = 6; { two triangles }
    BATCH_FLOATS_PER_VERT = 4; { x, y, u, v }
    BATCH_BUFFER_SIZE = BATCH_MAX_QUADS * BATCH_VERTS_PER_QUAD * BATCH_FLOATS_PER_VERT * 4; { bytes }

var
    batchBuf: array[0..BATCH_MAX_QUADS * BATCH_VERTS_PER_QUAD * BATCH_FLOATS_PER_VERT - 1] of GLfloat;
    batchCount: LongInt;
    batchTexId: GLuint;
    batchVBO: GLuint;
    batchInited: Boolean;
{$ENDIF}

{$IFDEF USE_S3D_RENDERING}
    // texture/vertex buffers for left/right/default eye modes
    texLRDtb, texLvb, texRvb: array [0..3] of TVertex2f;
{$ENDIF}

procedure openglLoadIdentity    (); forward;
procedure openglTranslProjMatrix(X, Y, Z: GLFloat); forward;
procedure openglScalef          (ScaleX, ScaleY, ScaleZ: GLfloat); forward;
procedure openglRotatef         (RotX, RotY, RotZ: GLfloat; dir: LongInt); forward;
procedure openglTint            (r, g, b, a: Byte); forward;

{$IFDEF USE_S3D_RENDERING OR USE_VIDEO_RECORDING}
procedure CreateFramebuffer(var frame, depth, tex: GLuint); forward;
procedure DeleteFramebuffer(var frame, depth, tex: GLuint); forward;
{$ENDIF}

function isAreaOffscreen(X, Y, Width, Height: LongInt): boolean; 
begin
    isAreaOffscreen:= (isDxAreaOffscreen(X, Width) <> 0) or (isDyAreaOffscreen(Y, Height) <> 0);
end;

function isCircleOffscreen(X, Y, RadiusSquared: LongInt): boolean; 
var dRightX, dBottomY, dLeftX, dTopY: LongInt;
begin
    dRightX:= (X - ViewRightX);
    dBottomY:= (Y - ViewBottomY);
    dLeftX:= (ViewLeftX - X);
    dTopY:= (ViewTopY - Y);
    isCircleOffscreen:= 
        ((dRightX > 0) and (sqr(dRightX) > RadiusSquared)) or
        ((dBottomY > 0) and (sqr(dBottomY) > RadiusSquared)) or
        ((dLeftX > 0) and (sqr(dLeftX) > RadiusSquared)) or
        ((dTopY > 0) and (sqr(dTopY) > RadiusSquared))
end;

function isDxAreaOffscreen(X, Width: LongInt): LongInt; 
begin
    if X > ViewRightX then exit(1);
    if X + Width < ViewLeftX then exit(-1);
    isDxAreaOffscreen:= 0;
end;

function isDyAreaOffscreen(Y, Height: LongInt): LongInt; 
begin
    if Y > ViewBottomY then exit(1);
    if Y + Height < ViewTopY then exit(-1);
    isDyAreaOffscreen:= 0;
end;

procedure RenderClear();
begin
    glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);
end;

{$IFDEF USE_S3D_RENDERING}
procedure RenderClear(mode: TRenderMode);
var frame: GLuint;
begin
    if (cStereoMode = smHorizontal) or (cStereoMode = smVertical) then
        begin
        case mode of
            rmLeftEye:  frame:= frameL;
            rmRightEye: frame:= frameR;
            else
                frame:= defaultFrame;
        end;

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frame);

        RenderClear();
        end
    else
        begin
        // draw left eye in red channel only
        if mode = rmLeftEye then
            begin
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            RenderClear();
            if cStereoMode = smGreenRed then
                glColorMask(GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE)
            else if cStereoMode = smBlueRed then
                glColorMask(GL_FALSE, GL_FALSE, GL_TRUE, GL_TRUE)
            else if cStereoMode = smCyanRed then
                glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE)
            else
                glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
            end
        else
            begin
            // draw right eye in selected channel(s) only
            if cStereoMode = smRedGreen then
                glColorMask(GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE)
            else if cStereoMode = smRedBlue then
                glColorMask(GL_FALSE, GL_FALSE, GL_TRUE, GL_TRUE)
            else if cStereoMode = smRedCyan then
                glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE)
            else
                glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
            end;
        end;
end;
{$ENDIF}

procedure RenderSetClearColor(r, g, b, a: real);
begin
    glClearColor(r, g, b, a);
end;

procedure FinishRender();
begin
{$IFDEF GL2}
FlushBatch();
{$ENDIF}

{$IFDEF USE_S3D_RENDERING}
if (cStereoMode = smHorizontal) or (cStereoMode = smVertical) then
    begin
    RenderClear(rmDefault);

    SetScale(cDefaultZoomLevel);


    // same for all
    SetTexCoordPointer(@texLRDtb, Length(texLRDtb));


    // draw left frame
    glBindTexture(GL_TEXTURE_2D, texl);
    SetVertexPointer(@texLvb, Length(texLvb));
    //UpdateModelviewProjection;
    glDrawArrays(GL_TRIANGLE_FAN, 0, Length(texLvb));

    // draw right frame
    glBindTexture(GL_TEXTURE_2D, texl);
    SetVertexPointer(@texRvb, Length(texRvb));
    //UpdateModelviewProjection;
    glDrawArrays(GL_TRIANGLE_FAN, 0, Length(texRvb));

    SetScale(zoom);
    end;
{$ENDIF}
end;

{$IFDEF GL2}
function CompileShader(shaderFile: string; shaderType: GLenum): GLuint;
var
    shader: GLuint;
    f: PFSFile;
    source, line: ansistring;
    sourceA: Pchar;
    lengthA: GLint;
    compileResult: GLint;
    logLength: GLint;
    log: PChar;
begin
    f:= pfsOpenRead(cPathz[ptShaders] + '/' + shaderFile);
    checkFails(f <> nil, 'Unable to load ' + shaderFile, true);

    source:='';
    while not pfsEof(f) do
    begin
        pfsReadLnA(f, line);
        source:= source + line + #10;
    end;

    pfsClose(f);

    WriteLnToConsole('Compiling shader: ' + cPathz[ptShaders] + '/' + shaderFile);

    sourceA:=PChar(source);
    lengthA:=Length(source);

    shader:=glCreateShader(shaderType);
    glShaderSource(shader, 1, @sourceA, @lengthA);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, @compileResult);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, @logLength);

    if logLength > 1 then
    begin
        log := GetMem(logLength);
        glGetShaderInfoLog(shader, logLength, nil, log);
        WriteLnToConsole('========== Compiler log  ==========');
        WriteLnToConsole(shortstring(log));
        WriteLnToConsole('===================================');
        FreeMem(log, logLength);
    end;

    if compileResult <> GL_TRUE then
    begin
        WriteLnToConsole('Shader compilation failed, halting');
        halt(HaltStartupError);
    end;

    CompileShader:= shader;
end;

function CompileProgram(shaderName: string): GLuint;
var
    program_: GLuint;
    vs, fs: GLuint;
    linkResult: GLint;
    logLength: GLint;
    log: PChar;
begin
    program_:= glCreateProgram();
    vs:= CompileShader(shaderName + '.vs', GL_VERTEX_SHADER);
    fs:= CompileShader(shaderName + '.fs', GL_FRAGMENT_SHADER);
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);

    glBindAttribLocation(program_, aVertex, PChar('vertex'));
    glBindAttribLocation(program_, aTexCoord, PChar('texcoord'));
    glBindAttribLocation(program_, aColor, PChar('color'));

    glLinkProgram(program_);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glGetProgramiv(program_, GL_LINK_STATUS, @linkResult);
    glGetProgramiv(program_, GL_INFO_LOG_LENGTH, @logLength);

    if logLength > 1 then
    begin
        log := GetMem(logLength);
        glGetProgramInfoLog(program_, logLength, nil, log);
        WriteLnToConsole('========== Compiler log  ==========');
        WriteLnToConsole(shortstring(log));
        WriteLnToConsole('===================================');
        FreeMem(log, logLength);
    end;

    if linkResult <> GL_TRUE then
    begin
        WriteLnToConsole('Linking program failed, halting');
        halt(HaltStartupError);
    end;

    CompileProgram:= program_;
end;
{$ENDIF}

function glLoadExtension(extension : shortstring) : boolean;
var logmsg: shortstring;
begin
    extension:= extension; // avoid hint
    glLoadExtension:= false;
    logmsg:= 'OpenGL - "' + extension + '" skipped';

{$IFNDEF IPHONEOS}
//TODO: pas2c does not handle
{$IFNDEF PAS2C}
// FreePascal doesnt come with OpenGL ES 1.1 Extension headers
{$IF GLunit <> gles11}

    glLoadExtension:= glext_LoadExtension(extension);

    if glLoadExtension then
        logmsg:= 'OpenGL - "' + extension + '" loaded'
    else
        logmsg:= 'OpenGL - "' + extension + '" failed to load';

{$ENDIF}
{$ENDIF}
{$ENDIF}
    AddFileLog(logmsg);
end;

{$IFDEF USE_S3D_RENDERING OR USE_VIDEO_RECORDING}
procedure CreateFramebuffer(var frame, depth, tex: GLuint);
begin
    glGenFramebuffersEXT(1, @frame);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frame);
    glGenRenderbuffersEXT(1, @depth);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, cScreenWidth, cScreenHeight);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth);
    glGenTextures(1, @tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8,  cScreenWidth, cScreenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nil);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tex, 0);
end;

procedure DeleteFramebuffer(var frame, depth, tex: GLuint);
begin
    glDeleteTextures(1, @tex);
    glDeleteRenderbuffersEXT(1, @depth);
    glDeleteFramebuffersEXT(1, @frame);
end;
{$ENDIF}

procedure RendererCleanup();
begin
{$IFNDEF PAS2C}
{$IFDEF USE_VIDEO_RECORDING}
    if defaultFrame <> 0 then
        DeleteFramebuffer(defaultFrame, depthv, texv);
{$ENDIF}
{$IFDEF USE_S3D_RENDERING}
    if (cStereoMode = smHorizontal) or (cStereoMode = smVertical) then
        begin
        DeleteFramebuffer(framel, depthl, texl);
        DeleteFramebuffer(framer, depthr, texr);
        end
{$ENDIF}
{$ENDIF}
end;

procedure RendererSetup();
var AuxBufNum: LongInt = 0;
    tmpstr: ansistring;
    tmpint: LongInt;
    tmpn: LongInt;
begin
    // suppress hint/warning
    AuxBufNum:= AuxBufNum;

    // get the max (h and v) size for textures that the gpu can support
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, @MaxTextureSize);
    if MaxTextureSize <= 0 then
        begin
        MaxTextureSize:= 1024;
        AddFileLog('OpenGL Warning - driver didn''t provide any valid max texture size; assuming 1024');
        end
    else if (MaxTextureSize < 1024) and (MaxTextureSize >= 512) then
        begin
        cReducedQuality := cReducedQuality or rqNoBackground;
        AddFileLog('Texture size too small for backgrounds, disabling.');
        end;
    // everyone loves debugging
    // find out which gpu we are using (for extension compatibility maybe?)
    AddFileLog('OpenGL-- Renderer: ' + shortstring(pchar(glGetString(GL_RENDERER))));
    AddFileLog('  |----- Vendor: ' + shortstring(pchar(glGetString(GL_VENDOR))));
    AddFileLog('  |----- Version: ' + shortstring(pchar(glGetString(GL_VERSION))));
    AddFileLog('  |----- Texture Size: ' + inttostr(MaxTextureSize));
{$IFDEF USE_VIDEO_RECORDING}
    glGetIntegerv(GL_AUX_BUFFERS, @AuxBufNum);
    AddFileLog('  |----- Number of auxiliary buffers: ' + inttostr(AuxBufNum));
{$ENDIF}
{$IFNDEF PAS2C}
    AddFileLog('  \----- Extensions: ');

    // fetch extentions and store them in string
    tmpstr := StrPas(PChar(glGetString(GL_EXTENSIONS)));
    tmpn := WordCount(tmpstr, [' ']);
    tmpint := 1;

    repeat
        begin
        // print up to 3 extentions per row
        // ExtractWord will return empty string if index out of range
        //AddFileLog(TrimRight(
        AddFileLog(Trim(
            ExtractWord(tmpint, tmpstr, [' ']) + ' ' +
            ExtractWord(tmpint+1, tmpstr, [' ']) + ' ' +
            ExtractWord(tmpint+2, tmpstr, [' '])
        ));
        tmpint := tmpint + 3;
        end;
    until (tmpint > tmpn);
{$ENDIF}
    AddFileLog('');

    defaultFrame:= 0;

{$IFDEF USE_VIDEO_RECORDING}
    if GameType = gmtRecord then
        begin
        if glLoadExtension('GL_EXT_framebuffer_object') then
            begin
            CreateFramebuffer(defaultFrame, depthv, texv);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, defaultFrame);
            AddFileLog('Using framebuffer for video recording.');
            end
        else if AuxBufNum > 0 then
            begin
            glDrawBuffer(GL_AUX0);
            glReadBuffer(GL_AUX0);
            AddFileLog('Using auxiliary buffer for video recording.');
            end
        else
            begin
            glDrawBuffer(GL_BACK);
            glReadBuffer(GL_BACK);
            AddFileLog('Warning: off-screen rendering is not supported; using back buffer but it may not work.');
            end;
        end;
{$ENDIF}

{$IFDEF GL2}

{$IFNDEF PAS2C}
    if not Load_GL_VERSION_2_0 then
        begin
        WriteLnToConsole('Load_GL_VERSION_2_0 returned false!');
        halt(HaltStartupError);
        end;
{$ENDIF}

    shaderWater:= CompileProgram('water');
    glUseProgram(shaderWater);
    glUniform1i(glGetUniformLocation(shaderWater, pchar('tex0')), 0);
    uWaterMVPLocation:= glGetUniformLocation(shaderWater, pchar('mvp'));

    shaderMain:= CompileProgram('default');
    glUseProgram(shaderMain);
    glUniform1i(glGetUniformLocation(shaderMain, pchar('tex0')), 0);
    uMainMVPLocation:= glGetUniformLocation(shaderMain, pchar('mvp'));
    uMainTintLocation:= glGetUniformLocation(shaderMain, pchar('tint'));

    uCurrentMVPLocation:= uMainMVPLocation;

    Tint(255, 255, 255, 255);
    UpdateModelviewProjection;
{$ENDIF}

{$IFDEF USE_S3D_RENDERING}
    if (cStereoMode = smHorizontal) or (cStereoMode = smVertical) then
        begin
        // prepare left and right frame buffers and associated textures
        if glLoadExtension('GL_EXT_framebuffer_object') then
            begin
            CreateFramebuffer(framel, depthl, texl);
            CreateFramebuffer(framer, depthr, texr);




            // reset
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, defaultFrame)
            end
        else
            cStereoMode:= smNone;
        end;

    // set up vertex/texture buffers for frame textures
    texLRDtb[0].X:= 0.0;
    texLRDtb[0].Y:= 0.0;
    texLRDtb[1].X:= 1.0;
    texLRDtb[1].Y:= 0.0;
    texLRDtb[2].X:= 1.0;
    texLRDtb[2].Y:= 1.0;
    texLRDtb[3].X:= 0.0;
    texLRDtb[3].Y:= 1.0;

    if cStereoMode = smHorizontal then
        begin
        texLvb[0].X:= cScreenWidth / -2;
        texLvb[0].Y:= cScreenHeight;
        texLvb[1].X:= 0;
        texLvb[1].Y:= cScreenHeight;
        texLvb[2].X:= 0;
        texLvb[2].Y:= 0;
        texLvb[3].X:= cScreenWidth / -2;
        texLvb[3].Y:= 0;

        texRvb[0].X:= 0;
        texRvb[0].Y:= cScreenHeight;
        texRvb[1].X:= cScreenWidth / 2;
        texRvb[1].Y:= cScreenHeight;
        texRvb[2].X:= cScreenWidth / 2;
        texRvb[2].Y:= 0;
        texRvb[3].X:= 0;
        texRvb[3].Y:= 0;
        end
    else
        begin
        texLvb[0].X:= cScreenWidth / -2;
        texLvb[0].Y:= cScreenHeight / 2;
        texLvb[1].X:= cScreenWidth / 2;
        texLvb[1].Y:= cScreenHeight / 2;
        texLvb[2].X:= cScreenWidth / 2;
        texLvb[2].Y:= 0;
        texLvb[3].X:= cScreenWidth / -2;
        texLvb[3].Y:= 0;

        texRvb[0].X:= cScreenWidth / -2;
        texRvb[0].Y:= cScreenHeight;
        texRvb[1].X:= cScreenWidth / 2;
        texRvb[1].Y:= cScreenHeight;
        texRvb[2].X:= cScreenWidth / 2;
        texRvb[2].Y:= cScreenHeight / 2;
        texRvb[3].X:= cScreenWidth / -2;
        texRvb[3].Y:= cScreenHeight / 2;
        end;
{$ENDIF}

// set view port to whole window
glViewport(0, 0, cScreenWidth, cScreenHeight);

{$IFDEF GL2}
    uMatrix.initModule;
    hglMatrixMode(MATRIX_MODELVIEW);
    // prepare default translation/scaling
    hglLoadIdentity();
    hglScalef(2.0 / cScreenWidth, -2.0 / cScreenHeight, 1.0);
    hglTranslatef(0, -cScreenHeight / 2, 0);

    EnableTexture(True);

    glEnableVertexAttribArray(aVertex);
    glEnableVertexAttribArray(aTexCoord);
    glGenBuffers(1, @vBuffer);
    glGenBuffers(1, @tBuffer);
    glGenBuffers(1, @cBuffer);
{$ELSE}
    glMatrixMode(GL_MODELVIEW);
    // prepare default translation/scaling
    glLoadIdentity();
    glScalef(2.0 / cScreenWidth, -2.0 / cScreenHeight, 1.0);
    glTranslatef(0, -cScreenHeight / 2, 0);

    // disable/lower perspective correction (will not need it anyway)
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    // disable dithering
    glDisable(GL_DITHER);
    // enable common states by default as they save a lot
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
{$ENDIF}

    // enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // disable/lower perspective correction (will not need it anyway)
end;

procedure openglLoadIdentity(); 
begin
{$IFDEF GL2}
    hglLoadIdentity();
{$ELSE}
    glLoadIdentity();
{$ENDIF}
end;

procedure openglTranslProjMatrix(X, Y, Z: GLfloat); 
begin
{$IFDEF GL2}
    hglMatrixMode(MATRIX_PROJECTION);
    hglTranslatef(X, Y, Z);
    hglMatrixMode(MATRIX_MODELVIEW);
{$ELSE}
    glMatrixMode(GL_PROJECTION);
    glTranslatef(X, Y, Z);
    glMatrixMode(GL_MODELVIEW);
{$ENDIF}
end;

procedure openglPushMatrix(); 
begin
{$IFDEF GL2}
    hglPushMatrix();
{$ELSE}
    glPushMatrix();
{$ENDIF}
end;

procedure openglPopMatrix(); 
begin
{$IFDEF GL2}
    hglPopMatrix();
{$ELSE}
    glPopMatrix();
{$ENDIF}
end;

procedure openglTranslatef(X, Y, Z: GLfloat); 
begin
{$IFDEF GL2}
    hglTranslatef(X, Y, Z);
{$ELSE}
    glTranslatef(X, Y, Z);
{$ENDIF}
end;

procedure openglScalef(ScaleX, ScaleY, ScaleZ: GLfloat); 
begin
{$IFDEF GL2}
    hglScalef(ScaleX, ScaleY, ScaleZ);
{$ELSE}
    glScalef(ScaleX, ScaleY, ScaleZ);
{$ENDIF}
end;

procedure openglRotatef(RotX, RotY, RotZ: GLfloat; dir: LongInt); 
{ workaround for pascal bug https://bugs.freepascal.org/view.php?id=27222 }
var tmpdir: LongInt;
begin
tmpdir:=dir;
{$IFDEF GL2}
    hglRotatef(RotX, RotY, RotZ, tmpdir);
{$ELSE}
    glRotatef(RotX, RotY, RotZ, tmpdir);
{$ENDIF}
end;

procedure openglUseColorOnly(b :boolean); 
begin
    if b then
        begin
        {$IFDEF GL2}
        glDisableVertexAttribArray(aTexCoord);
        glEnableVertexAttribArray(aColor);
        {$ELSE}
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        LastTexCoordPointer:= nil;
        {$ENDIF}
        end
    else
        begin
        {$IFDEF GL2}
        glDisableVertexAttribArray(aColor);
        glEnableVertexAttribArray(aTexCoord);
        {$ELSE}
        glDisableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        LastColorPointer:= nil;
        {$ENDIF}
        end;
    EnableTexture(not b);
end;

procedure UpdateModelviewProjection(); 
{$IFDEF GL2}
var
    mvp: TMatrix4x4f;
{$ENDIF}
begin
{$IFDEF GL2}
    //MatrixMultiply(mvp, mProjection, mModelview);
{$HINTS OFF}
    hglMVP(mvp);
{$HINTS ON}
    glUniformMatrix4fv(uCurrentMVPLocation, 1, GL_FALSE, @mvp[0, 0]);
{$ENDIF}
end;

{$IFDEF GL2}
{ ── Sprite Batch: flush accumulated quads in one draw call ── }
procedure FlushBatch();
var count: LongInt;
begin
    if batchCount = 0 then exit;
    count:= batchCount * BATCH_VERTS_PER_QUAD;

    glBindTexture(GL_TEXTURE_2D, batchTexId);
    glBindBuffer(GL_ARRAY_BUFFER, batchVBO);
    glBufferData(GL_ARRAY_BUFFER, count * BATCH_FLOATS_PER_VERT * 4, @batchBuf[0], GL_STREAM_DRAW);

    glEnableVertexAttribArray(aVertex);
    glEnableVertexAttribArray(aTexCoord);
    glVertexAttribPointer(aVertex,   2, GL_FLOAT, GL_FALSE, BATCH_FLOATS_PER_VERT * 4, pointer(0));
    glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, BATCH_FLOATS_PER_VERT * 4, pointer(8));

    UpdateModelviewProjection;
    glDrawArrays(GL_TRIANGLES, 0, count);

    batchCount:= 0;
end;

{ ── Sprite Batch: add one quad with pre-transformed vertices ── }
procedure BatchQuad(texId: GLuint;
    x0, y0, u0, v0,
    x1, y1, u1, v1,
    x2, y2, u2, v2,
    x3, y3, u3, v3: GLfloat);
var off: LongInt;
begin
    if (not batchInited) then
        begin
        glGenBuffers(1, @batchVBO);
        batchInited:= true;
        batchCount:= 0;
        batchTexId:= 0;
        end;

    if (texId <> batchTexId) or (batchCount >= BATCH_MAX_QUADS) then
        begin
        FlushBatch();
        batchTexId:= texId;
        end;

    off:= batchCount * BATCH_VERTS_PER_QUAD * BATCH_FLOATS_PER_VERT;
    { triangle 1: v0-v1-v2 }
    batchBuf[off   ]:= x0; batchBuf[off+1]:= y0; batchBuf[off+2]:= u0; batchBuf[off+3]:= v0;
    batchBuf[off+ 4]:= x1; batchBuf[off+5]:= y1; batchBuf[off+6]:= u1; batchBuf[off+7]:= v1;
    batchBuf[off+ 8]:= x2; batchBuf[off+9]:= y2; batchBuf[off+10]:= u2; batchBuf[off+11]:= v2;
    { triangle 2: v0-v2-v3 }
    batchBuf[off+12]:= x0; batchBuf[off+13]:= y0; batchBuf[off+14]:= u0; batchBuf[off+15]:= v0;
    batchBuf[off+16]:= x2; batchBuf[off+17]:= y2; batchBuf[off+18]:= u2; batchBuf[off+19]:= v2;
    batchBuf[off+20]:= x3; batchBuf[off+21]:= y3; batchBuf[off+22]:= u3; batchBuf[off+23]:= v3;

    inc(batchCount);
end;
{$ENDIF}

procedure SetTexCoordPointer(p: Pointer; n: Integer); 
begin
{$IFDEF GL2}
    glBindBuffer(GL_ARRAY_BUFFER, tBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * n * 2, p, GL_STATIC_DRAW);
    glEnableVertexAttribArray(aTexCoord);
    glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, pointer(0));
{$ELSE}
    if p = LastTexCoordPointer then
        exit;
    n:= n;
    glTexCoordPointer(2, GL_FLOAT, 0, p);
    LastTexCoordPointer:= p;
{$ENDIF}
end;

procedure SetVertexPointer(p: Pointer; n: Integer); 
begin
{$IFDEF GL2}
    glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * n * 2, p, GL_STATIC_DRAW);
    glEnableVertexAttribArray(aVertex);
    glVertexAttribPointer(aVertex, 2, GL_FLOAT, GL_FALSE, 0, pointer(0));
{$ELSE}
    if p = LastVertexPointer then
        exit;
    n:= n;
    glVertexPointer(2, GL_FLOAT, 0, p);
    LastVertexPointer:= p;
{$ENDIF}
end;

procedure SetColorPointer(p: Pointer; n: Integer); 
begin
{$IFDEF GL2}
    glBindBuffer(GL_ARRAY_BUFFER, cBuffer);
    glBufferData(GL_ARRAY_BUFFER, n * 4, p, GL_STATIC_DRAW);
    glEnableVertexAttribArray(aColor);
    glVertexAttribPointer(aColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, pointer(0));
{$ELSE}
    if p = LastColorPointer then
        exit;
    n:= n;
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, p);
    LastColorPointer:= p;
{$ENDIF}
end;

procedure EnableTexture(enable:Boolean);
begin
    {$IFDEF GL2}
    if enable then
        glUniform1i(glGetUniformLocation(shaderMain, pchar('enableTexture')), 1)
    else
        glUniform1i(glGetUniformLocation(shaderMain, pchar('enableTexture')), 0);
    {$ELSE}
    if enable then
        glEnable(GL_TEXTURE_2D)
    else
        glDisable(GL_TEXTURE_2D);
    {$ENDIF}
end;

procedure UpdateViewLimits();
var tmp: LongInt;
begin
    // cScaleFactor is 2.0 on "no zoom"
    tmp:= round(0.5 + cScreenWidth / cScaleFactor);
    ViewRightX :=  tmp;
    ViewLeftX  := -tmp;
    tmp:= round(0.5 + cScreenHeight / cScaleFactor);
    ViewBottomY:=  tmp + cScreenHeight div 2;
    ViewTopY   := -tmp + cScreenHeight div 2;

    // visual debugging fun :D
    if cViewLimitsDebug then
        begin
        // some margin on each side
        tmp:= trunc(min(cScreenWidth, cScreenHeight) div 2 / cScaleFactor);
        ViewLeftX  := ViewLeftX   + trunc(tmp);
        ViewRightX := ViewRightX  - trunc(tmp);
        ViewBottomY:= ViewBottomY - trunc(tmp);
        ViewTopY   := ViewTopY    + trunc(tmp);
        end;

    ViewWidth := ViewRightX  - ViewLeftX + 1;
    ViewHeight:= ViewBottomY - ViewTopY  + 1;
end;

procedure SetScale(f: GLfloat);
begin
    // leave immediately if scale factor did not change
    if f = cScaleFactor then
        exit;

    // for going back to default scaling just pop matrix
    if f = cDefaultZoomLevel then
        begin
        openglPopMatrix;
        end
    else
        begin
        if cScaleFactor = cDefaultZoomLevel then
            begin
            openglPushMatrix; // save default scaling in matrix;
            end;
        openglLoadIdentity();
        openglScalef(f / cScreenWidth, -f / cScreenHeight, 1.0);
        openglTranslatef(0, -cScreenHeight div 2, 0);
        end;

    cScaleFactor:= f;
    updateViewLimits();

    UpdateModelviewProjection;
end;

procedure DrawSpriteFromRect(Sprite: TSprite; r: TSDL_Rect; X, Y, Height, Position: LongInt); 
begin
r.y:= r.y + Height * Position;
r.h:= Height;
DrawTextureFromRect(X, Y, @r, SpritesData[Sprite].Texture)
end;

procedure DrawTextureFromRect(X, Y: LongInt; r: PSDL_Rect; SourceTexture: PTexture); 
begin
DrawTextureFromRectDir(X, Y, r^.w, r^.h, r, SourceTexture, 1)
end;

procedure DrawTextureFromRect(X, Y, W, H: LongInt; r: PSDL_Rect; SourceTexture: PTexture); 
begin
DrawTextureFromRectDir(X, Y, W, H, r, SourceTexture, 1)
end;

procedure DrawTextureFromRectDir(X, Y, W, H: LongInt; r: PSDL_Rect; SourceTexture: PTexture; Dir: LongInt);
var _l, _r, _t, _b: real;
    xw, yh: LongInt;
begin
if (SourceTexture^.h = 0) or (SourceTexture^.w = 0) then
    exit;

{if isDxAreaOffscreen(X, W) <> 0 then
    exit;
if isDyAreaOffscreen(Y, H) <> 0 then
    exit;}

// do not draw anything outside the visible screen space (first check fixes some sprite drawing, e.g. hedgehogs)
if (abs(X) > W) and ((abs(X + W / 2) - W / 2) * 2 > ViewWidth) then
    exit;
if (abs(Y) > H) and ((abs(Y + H / 2 - (0.5 * cScreenHeight)) - H / 2) * 2 > ViewHeight) then
    exit;

_l:= r^.x / SourceTexture^.w * SourceTexture^.rx;
_r:= (r^.x + r^.w) / SourceTexture^.w * SourceTexture^.rx;

// if direction is mirrored, switch left and right
if Dir < 0 then
    begin
    _t:= _l;
    _l:= _r;
    _r:= _t;
    end;

_t:= r^.y / SourceTexture^.h * SourceTexture^.ry;
_b:= (r^.y + r^.h) / SourceTexture^.h * SourceTexture^.ry;


xw:= X + W;
yh:= Y + H;

VertexBuffer[0].X:= X;
VertexBuffer[0].Y:= Y;
VertexBuffer[1].X:= xw;
VertexBuffer[1].Y:= Y;
VertexBuffer[2].X:= xw;
VertexBuffer[2].Y:= yh;
VertexBuffer[3].X:= X;
VertexBuffer[3].Y:= yh;

TextureBuffer[0].X:= _l;
TextureBuffer[0].Y:= _t;
TextureBuffer[1].X:= _r;
TextureBuffer[1].Y:= _t;
TextureBuffer[2].X:= _r;
TextureBuffer[2].Y:= _b;
TextureBuffer[3].X:= _l;
TextureBuffer[3].Y:= _b;


{$IFDEF GL2}
BatchQuad(SourceTexture^.id,
    X, Y, _l, _t,
    xw, Y, _r, _t,
    xw, yh, _r, _b,
    X, yh, _l, _b);
{$ELSE}
glBindTexture(GL_TEXTURE_2D, SourceTexture^.id);
SetVertexPointer(@VertexBuffer[0], 4);
SetTexCoordPointer(@TextureBuffer[0], 4);

glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
{$ENDIF}

end;

procedure DrawTexture(X, Y: LongInt; Texture: PTexture); 
begin
    DrawTexture(X, Y, Texture, 1.0);
end;

procedure DrawTexture(X, Y: LongInt; Texture: PTexture; Scale: GLfloat);
{$IFDEF GL2}
var s: GLfloat;
    x0, y0, x1, y1: GLfloat;
begin
s:= Scale;
x0:= X + Texture^.vb[0].X * s;
y0:= Y + Texture^.vb[0].Y * s;
x1:= X + Texture^.vb[2].X * s;
y1:= Y + Texture^.vb[2].Y * s;
BatchQuad(Texture^.id,
    x0, y0, Texture^.tb[0].X, Texture^.tb[0].Y,
    x1, y0, Texture^.tb[1].X, Texture^.tb[1].Y,
    x1, y1, Texture^.tb[2].X, Texture^.tb[2].Y,
    x0, y1, Texture^.tb[3].X, Texture^.tb[3].Y);
end;
{$ELSE}
begin
openglPushMatrix;
openglTranslatef(X, Y, 0);

if Scale <> 1.0 then
    openglScalef(Scale, Scale, 1);

glBindTexture(GL_TEXTURE_2D, Texture^.id);

SetVertexPointer(@Texture^.vb, Length(Texture^.vb));
SetTexCoordPointer(@Texture^.tb, Length(Texture^.vb));

UpdateModelviewProjection;

glDrawArrays(GL_TRIANGLE_FAN, 0, Length(Texture^.vb));
openglPopMatrix;

UpdateModelviewProjection;
end;
{$ENDIF}

{ this contains tweaks in order to avoid land tile borders in blurry land mode }
procedure DrawTexture2(X, Y: LongInt; Texture: PTexture; Scale, Overlap: GLfloat);
var
{$IFDEF GL2}
    s: GLfloat;
    x0, y0, x1, y1: GLfloat;
    tl, tr, tt, tb: GLfloat;
begin
s:= Scale;
x0:= X + Texture^.vb[0].X * s;
y0:= Y + Texture^.vb[0].Y * s;
x1:= X + Texture^.vb[2].X * s;
y1:= Y + Texture^.vb[2].Y * s;
tl:= Texture^.tb[0].X + Overlap;
tr:= Texture^.tb[1].X - Overlap;
tt:= Texture^.tb[0].Y + Overlap;
tb:= Texture^.tb[2].Y - Overlap;
BatchQuad(Texture^.id,
    x0, y0, tl, tt,
    x1, y0, tr, tt,
    x1, y1, tr, tb,
    x0, y1, tl, tb);
end;
{$ELSE}
    TextureBuffer: array [0..3] of TVertex2f;
begin
openglPushMatrix;
openglTranslatef(X, Y, 0);
openglScalef(Scale, Scale, 1);

glBindTexture(GL_TEXTURE_2D, Texture^.id);

TextureBuffer[0].X:= Texture^.tb[0].X + Overlap;
TextureBuffer[0].Y:= Texture^.tb[0].Y + Overlap;
TextureBuffer[1].X:= Texture^.tb[1].X - Overlap;
TextureBuffer[1].Y:= Texture^.tb[1].Y + Overlap;
TextureBuffer[2].X:= Texture^.tb[2].X - Overlap;
TextureBuffer[2].Y:= Texture^.tb[2].Y - Overlap;
TextureBuffer[3].X:= Texture^.tb[3].X + Overlap;
TextureBuffer[3].Y:= Texture^.tb[3].Y - Overlap;

SetVertexPointer(@Texture^.vb, 4);
SetTexCoordPointer(@TextureBuffer, 4);

UpdateModelviewProjection;

glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
openglPopMatrix;

UpdateModelviewProjection;
end;
{$ENDIF}

procedure DrawTextureF(Texture: PTexture; Scale: GLfloat; X, Y, Frame, Dir, w, h: LongInt);
begin
    DrawTextureRotatedF(Texture, Scale, 0, 0, X, Y, Frame, Dir, w, h, 0)
end;

procedure DrawTextureRotatedF(Texture: PTexture; Scale, OffsetX, OffsetY: GLfloat; X, Y, Frame, Dir, w, h: LongInt; Angle: real);
var ft, fb, fl, fr: GLfloat;
    hw, hh, nx, ny: LongInt;
{$IFDEF GL2}
    sa, ca, ox, oy, s: GLfloat;
    cx0, cy0, cx1, cy1, cx2, cy2, cx3, cy3: GLfloat;
    rx, ry: GLfloat;
{$ENDIF}
begin
// visibility check only under trivial conditions
if (Scale <= 1) then
    begin
    if Angle <> 0  then
        begin
        if (OffsetX = 0) and (OffsetY = 0) then
            begin
            if isDxAreaOffscreen(X - w, 2 * w) <> 0 then
                exit;
            if isDYAreaOffscreen(Y - h, 2 * h) <> 0 then
                exit;
            end;
        end
    else
        begin
        if isDxAreaOffscreen(X + dir * trunc(OffsetX) - w div 2, w) <> 0 then
            exit;
        if isDYAreaOffscreen(Y + trunc(OffsetY) - h div 2, h) <> 0 then
            exit;
        end;
    end;

if Dir = 0 then Dir:= 1;

if Dir > 0 then
    hw:=  w div 2
else
    hw:= -w div 2;
hh:= h div 2;

nx:= Texture^.w div w;
if nx = 0 then nx:= 1;
ny:= Texture^.h div h;
if ny = 0 then ny:= 1;

ft:= (Frame mod ny) * Texture^.ry / ny;
fb:= ((Frame mod ny) + 1) * Texture^.ry / ny;
fl:= (Frame div ny) * Texture^.rx / nx;
fr:= ((Frame div ny) + 1) * Texture^.rx / nx;

{$IFDEF GL2}
{ CPU-transform: build 4 corners in world space }
{ Matrix order: T(X,Y) * R(Angle*Dir) * T(offset) * S(scale) * vertex }
s:= Scale;
{ step 1: scale local corners }
cx0:= -hw * s; cy0:= -hh * s;
cx1:=  hw * s; cy1:= -hh * s;
cx2:=  hw * s; cy2:=  hh * s;
cx3:= -hw * s; cy3:=  hh * s;

{ step 2: add offset (not scaled — offset is applied after scale in matrix) }
ox:= Dir * OffsetX;
oy:= OffsetY;
cx0:= cx0 + ox; cy0:= cy0 + oy;
cx1:= cx1 + ox; cy1:= cy1 + oy;
cx2:= cx2 + ox; cy2:= cy2 + oy;
cx3:= cx3 + ox; cy3:= cy3 + oy;

{ step 3: rotate }
if Angle <> 0 then
    begin
    ca:= cos(Angle * Dir * 0.01745329252);
    sa:= sin(Angle * Dir * 0.01745329252);
    rx:= cx0; ry:= cy0; cx0:= rx*ca - ry*sa; cy0:= rx*sa + ry*ca;
    rx:= cx1; ry:= cy1; cx1:= rx*ca - ry*sa; cy1:= rx*sa + ry*ca;
    rx:= cx2; ry:= cy2; cx2:= rx*ca - ry*sa; cy2:= rx*sa + ry*ca;
    rx:= cx3; ry:= cy3; cx3:= rx*ca - ry*sa; cy3:= rx*sa + ry*ca;
    end;

{ step 4: translate to world position }
cx0:= cx0 + X; cy0:= cy0 + Y;
cx1:= cx1 + X; cy1:= cy1 + Y;
cx2:= cx2 + X; cy2:= cy2 + Y;
cx3:= cx3 + X; cy3:= cy3 + Y;

BatchQuad(Texture^.id,
    cx0, cy0, fl, ft,
    cx1, cy1, fr, ft,
    cx2, cy2, fr, fb,
    cx3, cy3, fl, fb);
{$ELSE}
openglPushMatrix;
openglTranslatef(X, Y, 0);

if Angle <> 0 then
    openglRotatef(Angle, 0, 0, Dir);

if (OffsetX <> 0) or (OffsetY <> 0) then
    openglTranslatef(Dir*OffsetX, OffsetY, 0);

if Scale <> 1.0 then
    openglScalef(Scale, Scale, 1);

glBindTexture(GL_TEXTURE_2D, Texture^.id);

VertexBuffer[0].X:= -hw;
VertexBuffer[0].Y:= -hh;
VertexBuffer[1].X:=  hw;
VertexBuffer[1].Y:= -hh;
VertexBuffer[2].X:=  hw;
VertexBuffer[2].Y:=  hh;
VertexBuffer[3].X:= -hw;
VertexBuffer[3].Y:=  hh;

TextureBuffer[0].X:= fl;
TextureBuffer[0].Y:= ft;
TextureBuffer[1].X:= fr;
TextureBuffer[1].Y:= ft;
TextureBuffer[2].X:= fr;
TextureBuffer[2].Y:= fb;
TextureBuffer[3].X:= fl;
TextureBuffer[3].Y:= fb;

SetVertexPointer(@VertexBuffer[0], 4);
SetTexCoordPointer(@TextureBuffer[0], 4);

UpdateModelviewProjection;
glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

openglPopMatrix;
UpdateModelviewProjection;
{$ENDIF}
end;

procedure DrawSpriteRotated(Sprite: TSprite; X, Y, Dir: LongInt; Angle: real);
begin
    DrawTextureRotated(SpritesData[Sprite].Texture,
        SpritesData[Sprite].Width,
        SpritesData[Sprite].Height,
        X, Y, Dir, Angle)
end;

procedure DrawSpriteRotatedF(Sprite: TSprite; X, Y, Frame, Dir: LongInt; Angle: real);
{$IFDEF GL2}
var hw, hh: LongInt;
    ca, sa, rx, ry, mx: GLfloat;
    cx0, cy0, cx1, cy1, cx2, cy2, cx3, cy3: GLfloat;
    r: TSDL_Rect;
    row, col, numFramesFirstCol: LongInt;
    fl, fr, ft, fb: GLfloat;
{$ENDIF}
begin

if Angle <> 0  then
    begin
    if isCircleOffscreen(X, Y, (sqr(SpritesData[Sprite].Width) + sqr(SpritesData[Sprite].Height)) div 4) then
        exit;
    end
else
    begin
    if isDxAreaOffscreen(X - SpritesData[Sprite].Width div 2, SpritesData[Sprite].Width) <> 0 then
        exit;
    if isDYAreaOffscreen(Y - SpritesData[Sprite].Height div 2 , SpritesData[Sprite].Height) <> 0 then
        exit;
    end;

{$IFDEF GL2}
hw:= SpritesData[Sprite].Width div 2;
hh:= SpritesData[Sprite].Height div 2;

{ compute frame UVs }
if SpritesData[Sprite].imageHeight = 0 then exit;
numFramesFirstCol:= SpritesData[Sprite].imageHeight div SpritesData[Sprite].Height;
row:= Frame mod numFramesFirstCol;
col:= Frame div numFramesFirstCol;
r.x:= col * SpritesData[Sprite].Width;
r.w:= SpritesData[Sprite].Width;
r.y:= row * SpritesData[Sprite].Height;
r.h:= SpritesData[Sprite].Height;
fl:= r.x / SpritesData[Sprite].Texture^.w * SpritesData[Sprite].Texture^.rx;
fr:= (r.x + r.w) / SpritesData[Sprite].Texture^.w * SpritesData[Sprite].Texture^.rx;
ft:= r.y / SpritesData[Sprite].Texture^.h * SpritesData[Sprite].Texture^.ry;
fb:= (r.y + r.h) / SpritesData[Sprite].Texture^.h * SpritesData[Sprite].Texture^.ry;

{ CPU transform: T(X,Y) * Scale(Dir,1) * R(Angle) * vertex(-hw..hw, -hh..hh) }
cx0:= -hw; cy0:= -hh;
cx1:=  hw; cy1:= -hh;
cx2:=  hw; cy2:=  hh;
cx3:= -hw; cy3:=  hh;

if Angle <> 0 then
    begin
    ca:= cos(Angle * 0.01745329252);
    sa:= sin(Angle * 0.01745329252);
    rx:= cx0; ry:= cy0; cx0:= rx*ca - ry*sa; cy0:= rx*sa + ry*ca;
    rx:= cx1; ry:= cy1; cx1:= rx*ca - ry*sa; cy1:= rx*sa + ry*ca;
    rx:= cx2; ry:= cy2; cx2:= rx*ca - ry*sa; cy2:= rx*sa + ry*ca;
    rx:= cx3; ry:= cy3; cx3:= rx*ca - ry*sa; cy3:= rx*sa + ry*ca;
    end;

{ mirror }
if Dir < 0 then mx:= -1.0 else mx:= 1.0;
cx0:= cx0 * mx; cx1:= cx1 * mx; cx2:= cx2 * mx; cx3:= cx3 * mx;

{ if mirrored, swap UVs horizontally }
if Dir < 0 then
    begin
    rx:= fl; fl:= fr; fr:= rx;
    end;

{ translate }
cx0:= cx0 + X; cy0:= cy0 + Y;
cx1:= cx1 + X; cy1:= cy1 + Y;
cx2:= cx2 + X; cy2:= cy2 + Y;
cx3:= cx3 + X; cy3:= cy3 + Y;

BatchQuad(SpritesData[Sprite].Texture^.id,
    cx0, cy0, fl, ft,
    cx1, cy1, fr, ft,
    cx2, cy2, fr, fb,
    cx3, cy3, fl, fb);
{$ELSE}
openglPushMatrix;
openglTranslatef(X, Y, 0);

if Dir < 0 then
    openglScalef(-1.0, 1.0, 1.0);

if Angle <> 0  then
    openglRotatef(Angle, 0, 0, 1);

UpdateModelviewProjection;

DrawSprite(Sprite, -SpritesData[Sprite].Width div 2, -SpritesData[Sprite].Height div 2, Frame);

openglPopMatrix;

UpdateModelviewProjection;
{$ENDIF}
end;

procedure DrawSpriteRotatedFReal(Sprite: TSprite; X, Y: Real; Frame, Dir: LongInt; Angle: real);
{$IFDEF GL2}
var hw, hh: LongInt;
    ca, sa, rx, ry, mx: GLfloat;
    cx0, cy0, cx1, cy1, cx2, cy2, cx3, cy3: GLfloat;
    r: TSDL_Rect;
    row, col, numFramesFirstCol: LongInt;
    fl, fr, ft, fb: GLfloat;
{$ENDIF}
begin

    if Angle <> 0  then
    begin
        if isCircleOffscreen(round(X), round(Y), (sqr(SpritesData[Sprite].Width) + sqr(SpritesData[Sprite].Height)) div 4) then
            exit;
    end
    else
    begin
        if isDxAreaOffscreen(round(X) - SpritesData[Sprite].Width div 2, SpritesData[Sprite].Width) <> 0 then
            exit;
        if isDYAreaOffscreen(round(Y) - SpritesData[Sprite].Height div 2 , SpritesData[Sprite].Height) <> 0 then
            exit;
    end;

{$IFDEF GL2}
hw:= SpritesData[Sprite].Width div 2;
hh:= SpritesData[Sprite].Height div 2;

if SpritesData[Sprite].imageHeight = 0 then exit;
numFramesFirstCol:= SpritesData[Sprite].imageHeight div SpritesData[Sprite].Height;
row:= Frame mod numFramesFirstCol;
col:= Frame div numFramesFirstCol;
r.x:= col * SpritesData[Sprite].Width;
r.w:= SpritesData[Sprite].Width;
r.y:= row * SpritesData[Sprite].Height;
r.h:= SpritesData[Sprite].Height;
fl:= r.x / SpritesData[Sprite].Texture^.w * SpritesData[Sprite].Texture^.rx;
fr:= (r.x + r.w) / SpritesData[Sprite].Texture^.w * SpritesData[Sprite].Texture^.rx;
ft:= r.y / SpritesData[Sprite].Texture^.h * SpritesData[Sprite].Texture^.ry;
fb:= (r.y + r.h) / SpritesData[Sprite].Texture^.h * SpritesData[Sprite].Texture^.ry;

cx0:= -hw; cy0:= -hh;
cx1:=  hw; cy1:= -hh;
cx2:=  hw; cy2:=  hh;
cx3:= -hw; cy3:=  hh;

if Angle <> 0 then
    begin
    ca:= cos(Angle * 0.01745329252);
    sa:= sin(Angle * 0.01745329252);
    rx:= cx0; ry:= cy0; cx0:= rx*ca - ry*sa; cy0:= rx*sa + ry*ca;
    rx:= cx1; ry:= cy1; cx1:= rx*ca - ry*sa; cy1:= rx*sa + ry*ca;
    rx:= cx2; ry:= cy2; cx2:= rx*ca - ry*sa; cy2:= rx*sa + ry*ca;
    rx:= cx3; ry:= cy3; cx3:= rx*ca - ry*sa; cy3:= rx*sa + ry*ca;
    end;

if Dir < 0 then mx:= -1.0 else mx:= 1.0;
cx0:= cx0 * mx; cx1:= cx1 * mx; cx2:= cx2 * mx; cx3:= cx3 * mx;

if Dir < 0 then
    begin
    rx:= fl; fl:= fr; fr:= rx;
    end;

cx0:= cx0 + X; cy0:= cy0 + Y;
cx1:= cx1 + X; cy1:= cy1 + Y;
cx2:= cx2 + X; cy2:= cy2 + Y;
cx3:= cx3 + X; cy3:= cy3 + Y;

BatchQuad(SpritesData[Sprite].Texture^.id,
    cx0, cy0, fl, ft,
    cx1, cy1, fr, ft,
    cx2, cy2, fr, fb,
    cx3, cy3, fl, fb);
{$ELSE}
    openglPushMatrix;
    openglTranslatef(X, Y, 0);

    if Dir < 0 then
        openglScalef(-1.0, 1.0, 1.0);

    if Angle <> 0  then
        openglRotatef(Angle, 0, 0, 1);

    UpdateModelviewProjection;

    DrawSprite(Sprite, -SpritesData[Sprite].Width div 2, -SpritesData[Sprite].Height div 2, Frame);

    openglPopMatrix;

    UpdateModelviewProjection;
{$ENDIF}
end;

procedure DrawSpritePivotedF(Sprite: TSprite; X, Y, Frame, Dir, PivotX, PivotY: LongInt; Angle: real);
{$IFDEF GL2}
var hw, hh: LongInt;
    ca, sa, rx, ry, mx: GLfloat;
    cx0, cy0, cx1, cy1, cx2, cy2, cx3, cy3: GLfloat;
    r: TSDL_Rect;
    row, col, numFramesFirstCol: LongInt;
    fl, fr, ft, fb: GLfloat;
{$ENDIF}
begin
if Angle <> 0  then
    begin
    if isCircleOffscreen(X, Y, 9 * (sqr(SpritesData[Sprite].Width) + sqr(SpritesData[Sprite].Height)) div 4) then
        exit;
    end
else
    begin
    if isDxAreaOffscreen(X - SpritesData[Sprite].Width div 2, SpritesData[Sprite].Width) <> 0 then
        exit;
    if isDYAreaOffscreen(Y - SpritesData[Sprite].Height div 2 , SpritesData[Sprite].Height) <> 0 then
        exit;
    end;

{$IFDEF GL2}
hw:= SpritesData[Sprite].Width div 2;
hh:= SpritesData[Sprite].Height div 2;

if SpritesData[Sprite].imageHeight = 0 then exit;
numFramesFirstCol:= SpritesData[Sprite].imageHeight div SpritesData[Sprite].Height;
row:= Frame mod numFramesFirstCol;
col:= Frame div numFramesFirstCol;
r.x:= col * SpritesData[Sprite].Width;
r.w:= SpritesData[Sprite].Width;
r.y:= row * SpritesData[Sprite].Height;
r.h:= SpritesData[Sprite].Height;
fl:= r.x / SpritesData[Sprite].Texture^.w * SpritesData[Sprite].Texture^.rx;
fr:= (r.x + r.w) / SpritesData[Sprite].Texture^.w * SpritesData[Sprite].Texture^.rx;
ft:= r.y / SpritesData[Sprite].Texture^.h * SpritesData[Sprite].Texture^.ry;
fb:= (r.y + r.h) / SpritesData[Sprite].Texture^.h * SpritesData[Sprite].Texture^.ry;

{ CPU transform: T(X,Y) * Scale(Dir,1) * T(Pivot) * R(Angle) * T(-Pivot) * vertex(-hw..) }
{ start with local vertex + offset from pivot }
cx0:= -hw - PivotX; cy0:= -hh - PivotY;
cx1:=  hw - PivotX; cy1:= -hh - PivotY;
cx2:=  hw - PivotX; cy2:=  hh - PivotY;
cx3:= -hw - PivotX; cy3:=  hh - PivotY;

{ rotate around pivot }
if Angle <> 0 then
    begin
    ca:= cos(Angle * 0.01745329252);
    sa:= sin(Angle * 0.01745329252);
    rx:= cx0; ry:= cy0; cx0:= rx*ca - ry*sa; cy0:= rx*sa + ry*ca;
    rx:= cx1; ry:= cy1; cx1:= rx*ca - ry*sa; cy1:= rx*sa + ry*ca;
    rx:= cx2; ry:= cy2; cx2:= rx*ca - ry*sa; cy2:= rx*sa + ry*ca;
    rx:= cx3; ry:= cy3; cx3:= rx*ca - ry*sa; cy3:= rx*sa + ry*ca;
    end;

{ translate back from pivot }
cx0:= cx0 + PivotX; cy0:= cy0 + PivotY;
cx1:= cx1 + PivotX; cy1:= cy1 + PivotY;
cx2:= cx2 + PivotX; cy2:= cy2 + PivotY;
cx3:= cx3 + PivotX; cy3:= cy3 + PivotY;

{ mirror }
if Dir < 0 then mx:= -1.0 else mx:= 1.0;
cx0:= cx0 * mx; cx1:= cx1 * mx; cx2:= cx2 * mx; cx3:= cx3 * mx;

if Dir < 0 then
    begin
    rx:= fl; fl:= fr; fr:= rx;
    end;

{ translate to world position }
cx0:= cx0 + X; cy0:= cy0 + Y;
cx1:= cx1 + X; cy1:= cy1 + Y;
cx2:= cx2 + X; cy2:= cy2 + Y;
cx3:= cx3 + X; cy3:= cy3 + Y;

BatchQuad(SpritesData[Sprite].Texture^.id,
    cx0, cy0, fl, ft,
    cx1, cy1, fr, ft,
    cx2, cy2, fr, fb,
    cx3, cy3, fl, fb);
{$ELSE}
openglPushMatrix;
openglTranslatef(X, Y, 0);

if Dir < 0 then
    openglScalef(-1.0, 1.0, 1.0);

if Angle <> 0  then
    begin
    openglTranslatef(PivotX, PivotY, 0);
    openglRotatef(Angle, 0, 0, 1);
    openglTranslatef(-PivotX, -PivotY, 0);
    end;

UpdateModelviewProjection;

DrawSprite(Sprite, -SpritesData[Sprite].Width div 2, -SpritesData[Sprite].Height div 2, Frame);

openglPopMatrix;

UpdateModelviewProjection;
{$ENDIF}
end;

procedure DrawTextureRotated(Texture: PTexture; hw, hh, X, Y, Dir: LongInt; Angle: real);
{$IFDEF GL2}
var ca, sa, rx, ry: GLfloat;
    cx0, cy0, cx1, cy1, cx2, cy2, cx3, cy3: GLfloat;
begin
if isDxAreaOffscreen(X, 2 * hw) <> 0 then exit;
if isDyAreaOffscreen(Y, 2 * hh) <> 0 then exit;

if Dir < 0 then hw:= -hw;

cx0:= -hw; cy0:= -hh;
cx1:=  hw; cy1:= -hh;
cx2:=  hw; cy2:=  hh;
cx3:= -hw; cy3:=  hh;

if Angle <> 0 then
    begin
    if Dir < 0 then
        begin ca:= cos(-Angle * 0.01745329252); sa:= sin(-Angle * 0.01745329252); end
    else
        begin ca:= cos(Angle * 0.01745329252); sa:= sin(Angle * 0.01745329252); end;
    rx:= cx0; ry:= cy0; cx0:= rx*ca - ry*sa; cy0:= rx*sa + ry*ca;
    rx:= cx1; ry:= cy1; cx1:= rx*ca - ry*sa; cy1:= rx*sa + ry*ca;
    rx:= cx2; ry:= cy2; cx2:= rx*ca - ry*sa; cy2:= rx*sa + ry*ca;
    rx:= cx3; ry:= cy3; cx3:= rx*ca - ry*sa; cy3:= rx*sa + ry*ca;
    end;

BatchQuad(Texture^.id,
    cx0 + X, cy0 + Y, Texture^.tb[0].X, Texture^.tb[0].Y,
    cx1 + X, cy1 + Y, Texture^.tb[1].X, Texture^.tb[1].Y,
    cx2 + X, cy2 + Y, Texture^.tb[2].X, Texture^.tb[2].Y,
    cx3 + X, cy3 + Y, Texture^.tb[3].X, Texture^.tb[3].Y);
end;
{$ELSE}
begin
if isDxAreaOffscreen(X, 2 * hw) <> 0 then exit;
if isDyAreaOffscreen(Y, 2 * hh) <> 0 then exit;

openglPushMatrix;
openglTranslatef(X, Y, 0);

if Dir < 0 then
    begin
    hw:= - hw;
    openglRotatef(Angle, 0, 0, -1);
    end
else
    openglRotatef(Angle, 0, 0, 1);

glBindTexture(GL_TEXTURE_2D, Texture^.id);

VertexBuffer[0].X:= -hw;
VertexBuffer[0].Y:= -hh;
VertexBuffer[1].X:= hw;
VertexBuffer[1].Y:= -hh;
VertexBuffer[2].X:= hw;
VertexBuffer[2].Y:= hh;
VertexBuffer[3].X:= -hw;
VertexBuffer[3].Y:= hh;

SetVertexPointer(@VertexBuffer[0], 4);
SetTexCoordPointer(@Texture^.tb, 4);

UpdateModelviewProjection;

glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

openglPopMatrix;

UpdateModelviewProjection;
end;
{$ENDIF}

procedure DrawSprite(Sprite: TSprite; X, Y, Frame: LongInt);
var row, col, numFramesFirstCol: LongInt;
begin
    if SpritesData[Sprite].imageHeight = 0 then
        exit;
    numFramesFirstCol:= SpritesData[Sprite].imageHeight div SpritesData[Sprite].Height;
    row:= Frame mod numFramesFirstCol;
    col:= Frame div numFramesFirstCol;
    DrawSprite(Sprite, X, Y, col, row);
end;

procedure DrawSprite(Sprite: TSprite; X, Y, FrameX, FrameY: LongInt);
var r: TSDL_Rect;
begin
    r.x:= FrameX * SpritesData[Sprite].Width;
    r.w:= SpritesData[Sprite].Width;
    r.y:= FrameY * SpritesData[Sprite].Height;
    r.h:= SpritesData[Sprite].Height;
    DrawTextureFromRect(X, Y, @r, SpritesData[Sprite].Texture)
end;

procedure DrawSpriteClipped(Sprite: TSprite; X, Y, TopY, RightX, BottomY, LeftX: LongInt);
var r: TSDL_Rect;
begin
r.x:= 0;
r.y:= 0;
r.w:= SpritesData[Sprite].Width;
r.h:= SpritesData[Sprite].Height;

if (X < LeftX) then
    r.x:= LeftX - X;
if (Y < TopY) then
    r.y:= TopY - Y;

if (Y + SpritesData[Sprite].Height > BottomY) then
    r.h:= BottomY - Y + 1;
if (X + SpritesData[Sprite].Width > RightX) then
    r.w:= RightX - X + 1;

if (r.h < r.y) or (r.w < r.x) then
    exit;

dec(r.h, r.y);
dec(r.w, r.x);

DrawTextureFromRect(X + r.x, Y + r.y, @r, SpritesData[Sprite].Texture)
end;

procedure DrawTextureCentered(X, Top: LongInt; Source: PTexture);
var scale: GLfloat;
    left : LongInt;
begin
    // scale down if larger than screen
    if (Source^.w + 20) > cScreenWidth then
        begin
        scale:= cScreenWidth / (Source^.w + 20);
        DrawTexture(X - round(Source^.w * scale) div 2, Top, Source, scale);
        end
    else
        begin
        left:= X - Source^.w div 2;
        if (not isAreaOffscreen(left, Top, Source^.w, Source^.h)) then
            DrawTexture(left, Top, Source);
        end;
end;

// Same as below, but with color as LongWord
procedure DrawLine(X0, Y0, X1, Y1, Width: Single; color: LongWord); 
begin
DrawLine(X0, Y0, X1, Y1, Width, (color shr 24) and $FF, (color shr 16) and $FF, (color shr 8) and $FF, color and $FF)
end;

// Draw line between 2 points
// X0, Y0: Start point
// X0, Y1: End point
// Width: Visual line width
// r, g, b, a: Color
procedure DrawLine(X0, Y0, X1, Y1, Width: Single; r, g, b, a: Byte);
begin
{$IFDEF GL2}
    FlushBatch();
{$ENDIF}
    openglPushMatrix();
    openglTranslatef(WorldDx, WorldDy, 0);

    UpdateModelviewProjection;

    DrawLineOnScreen(X0, Y0, X1, Y1, Width, r, g, b, a);

    openglPopMatrix();

    UpdateModelviewProjection;
end;

// Same as below, but with color as a longword
procedure DrawLineWrapped(X0, Y0, X1, Y1, Width: Single; goesLeft: boolean; Wraps: LongWord; color: LongWord); 
begin
DrawLineWrapped(X0, Y0, X1, Y1, Width, goesLeft, Wraps, (color shr 24) and $FF, (color shr 16) and $FF, (color shr 8) and $FF, color and $FF);
end;

// Draw a line between 2 points, but it wraps around the
// world edge for a given number of times.
// goesLeft: true if the line direction from the start point is left
// Wraps: Number of times the line intersects the wrapping world edge
// r, g, b, a: color
procedure DrawLineWrapped(X0, Y0, X1, Y1, Width: Single; goesLeft: boolean; Wraps: LongWord; r, g, b, a: Byte);
var w: LongWord;
    startX, startY, endX, endY: Single;
    // total X and Y distance the line travels if you would unwrap it
    // with this we know the slope of the line.
    totalX, totalY: Single;
    // x variable for the line formula
    x: Single;
begin
{$IFDEF GL2}
    FlushBatch();
{$ENDIF}
    openglPushMatrix();
    openglTranslatef(WorldDx, WorldDy, 0);

    UpdateModelviewProjection;

    startX:= X0;
    startY:= Y0;
    if (Wraps = 0) then
        begin
        // Wraps=0 is trivial: Just draw one direct connection
        endX:= X1;
        endY:= Y1;
        DrawLineOnScreen(startX, startY, endX, endY, Width, r, g, b, a);
        end
    else
        begin
        // A wrapping line is drawn using multiple line segments
        // which stop at the left and right border. We
        // calculate the points at which the line intersects with the border.
        // Then we draws all line segments.

        // Calculate position of first wrap point
        if goesLeft then
            begin
            endX:= LeftX;
            totalX:= (RightX - X1) + (X0 - LeftX);
            x:= X0 - LeftX;
            end
        else
            begin
            endX:= RightX;
            totalX:= (RightX - X0) + (X1 - LeftX);
            x:= RightX - X0;
            end;
        if (Wraps >= 2) then
            totalX:= totalX + ((RightX - LeftX) * (Wraps-1));
        totalY:= Y1 - Y0;
        // Calculate Y of first wrap point using the line formula
        endY:= Y0 + (totalY / totalX) * x;
        // Draw line segment between starting point and first wrap point
        DrawLineOnScreen(startX, startY, endX, endY, Width, r, g, b, a);

        // Calculate and draw all remaining line segments
        for w:=1 to Wraps do
            begin
            startY:= endY;
            if goesLeft then
                begin
                startX:= RightX;
                if w < Wraps then
                    endX:= LeftX
                else
                    endX:= X1;
                end
            else
                begin
                startX:= LeftX;
                if w < Wraps then
                    endX:= RightX
                else
                    endX:= X1;
                end;
            if w < Wraps then
                begin
                x:= x + (RightX - LeftX);
                endY:= Y0 + (totalY / totalX) * x;
                end
            else
                endY:= Y1;

            DrawLineOnScreen(startX, startY, endX, endY, Width, r, g, b, a);
            end;

        end;

    openglPopMatrix();

    UpdateModelviewProjection;
end;

procedure DrawLineOnScreen(X0, Y0, X1, Y1, Width: Single; r, g, b, a: Byte);
begin
    glEnable(GL_LINE_SMOOTH);

    EnableTexture(False);

    glLineWidth(Width);

    Tint(r, g, b, a);
    VertexBuffer[0].X:= X0;
    VertexBuffer[0].Y:= Y0;
    VertexBuffer[1].X:= X1;
    VertexBuffer[1].Y:= Y1;

    SetVertexPointer(@VertexBuffer[0], 2);
    glDrawArrays(GL_LINES, 0, 2);
    untint();

    EnableTexture(True);

    glDisable(GL_LINE_SMOOTH);
end;

procedure DrawRect(rect: TSDL_Rect; r, g, b, a: Byte; Fill: boolean);
begin
// do not draw anything outside the visible screen space (first check fixes some sprite drawing, e.g. hedgehogs)
if (abs(rect.x) > rect.w) and ((abs(rect.x + rect.w / 2) - rect.w / 2) * 2 > ViewWidth) then
    exit;
if (abs(rect.y) > rect.h) and ((abs(rect.y + rect.h / 2 - (cScreenHeight / 2)) - rect.h / 2) * 2 > ViewHeight) then
    exit;

EnableTexture(False);
Tint(r, g, b, a);

with rect do
begin
    VertexBuffer[0].X:= x;
    VertexBuffer[0].Y:= y;
    VertexBuffer[1].X:= x + w;
    VertexBuffer[1].Y:= y;
    VertexBuffer[2].X:= x + w;
    VertexBuffer[2].Y:= y + h;
    VertexBuffer[3].X:= x;
    VertexBuffer[3].Y:= y + h;
end;

SetVertexPointer(@VertexBuffer[0], 4);
if Fill then
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4)
else
    begin
    glLineWidth(1);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    end;

untint;

EnableTexture(True);

end;

procedure DrawCircle(X, Y, Radius, Width: LongInt; r, g, b, a: Byte);
begin
    Tint(r, g, b, a);
    DrawCircle(X, Y, Radius, Width);
    untint;
end;

procedure DrawCircle(X, Y, Radius, Width: LongInt; color: LongWord);
begin
    Tint(color);
    DrawCircle(X, Y, Radius, Width);
    untint;
end;

procedure DrawCircle(X, Y, Radius, Width: LongInt);
var
    i: LongInt;
begin
{$IFDEF GL2}
    FlushBatch();
{$ENDIF}
    i:= Radius + Width;
    if isDxAreaOffscreen(X - i, 2 * i) <> 0 then
        exit;
    if isDyAreaOffscreen(Y - i, 2 * i) <> 0 then
        exit;

    for i := 0 to 59 do begin
        VertexBuffer[i].X := X + Radius*cos(i*pi/30);
        VertexBuffer[i].Y := Y + Radius*sin(i*pi/30);
    end;

    EnableTexture(False);
    glEnable(GL_LINE_SMOOTH);
    //openglPushMatrix;
    glLineWidth(Width);
    SetVertexPointer(@VertexBuffer[0], 60);
    glDrawArrays(GL_LINE_LOOP, 0, 60);
    //openglPopMatrix;
    EnableTexture(True);
    glDisable(GL_LINE_SMOOTH);
end;

procedure DrawCircleFilled(X, Y, Radius: LongInt; r, g, b, a: Byte);
var
    i: LongInt;
begin
    VertexBuffer[0].X := X;
    VertexBuffer[0].Y := Y;

    for i := 1 to 19 do begin
        VertexBuffer[i].X := X + Radius*cos(i*pi/9);
        VertexBuffer[i].Y := Y + Radius*sin(i*pi/9);
    end;

    EnableTexture(False);
    Tint(r, g, b, a);
    SetVertexPointer(@VertexBuffer[0], 20);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
    Untint();
    EnableTexture(True);
end;

procedure DrawHedgehog(X, Y: LongInt; Dir: LongInt; Pos, Step: LongWord; Angle: real);
var l, r, t, b: real;
{$IFDEF GL2}
    ca, sa, rx, ry: GLfloat;
    cx0, cy0, cx1, cy1, cx2, cy2, cx3, cy3: GLfloat;
{$ELSE}
const VertexBuffer: array [0..3] of TVertex2f = (
        (X: -16; Y: -16),
        (X:  16; Y: -16),
        (X:  16; Y:  16),
        (X: -16; Y:  16));
{$ENDIF}
begin
    if (abs(X) > 32) and ((abs(X) - 16) * 2 > ViewWidth) then
        exit;
    if (abs(Y) > 32) and ((abs(Y - cScreenHeight / 2) - 16) * 2 > ViewHeight) then
        exit;

    t:= Pos * 32 / HHTexture^.h;
    b:= (Pos + 1) * 32 / HHTexture^.h;

    if Dir = -1 then
        begin
        l:= (Step + 1) * 32 / HHTexture^.w;
        r:= Step * 32 / HHTexture^.w
        end
    else
        begin
        l:= Step * 32 / HHTexture^.w;
        r:= (Step + 1) * 32 / HHTexture^.w
    end;

{$IFDEF GL2}
    cx0:= -16; cy0:= -16;
    cx1:=  16; cy1:= -16;
    cx2:=  16; cy2:=  16;
    cx3:= -16; cy3:=  16;
    if Angle <> 0 then
        begin
        ca:= cos(Angle * 0.01745329252);
        sa:= sin(Angle * 0.01745329252);
        rx:= cx0; ry:= cy0; cx0:= rx*ca - ry*sa; cy0:= rx*sa + ry*ca;
        rx:= cx1; ry:= cy1; cx1:= rx*ca - ry*sa; cy1:= rx*sa + ry*ca;
        rx:= cx2; ry:= cy2; cx2:= rx*ca - ry*sa; cy2:= rx*sa + ry*ca;
        rx:= cx3; ry:= cy3; cx3:= rx*ca - ry*sa; cy3:= rx*sa + ry*ca;
        end;
    BatchQuad(HHTexture^.id,
        cx0 + X, cy0 + Y, l, t,
        cx1 + X, cy1 + Y, r, t,
        cx2 + X, cy2 + Y, r, b,
        cx3 + X, cy3 + Y, l, b);
{$ELSE}
    openglPushMatrix();
    openglTranslatef(X, Y, 0);
    openglRotatef(Angle, 0, 0, 1);

    glBindTexture(GL_TEXTURE_2D, HHTexture^.id);

    TextureBuffer[0].X:= l;
    TextureBuffer[0].Y:= t;
    TextureBuffer[1].X:= r;
    TextureBuffer[1].Y:= t;
    TextureBuffer[2].X:= r;
    TextureBuffer[2].Y:= b;
    TextureBuffer[3].X:= l;
    TextureBuffer[3].Y:= b;

    SetVertexPointer(@VertexBuffer[0], 4);
    SetTexCoordPointer(@TextureBuffer[0], 4);

    UpdateModelviewProjection;

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    openglPopMatrix;

    UpdateModelviewProjection;
{$ENDIF}
end;

procedure DrawScreenWidget(widget: POnScreenWidget);
{$IFDEF USE_TOUCH_INTERFACE}
var alpha: byte = $FF;
begin
with widget^ do
    begin
    if (fadeAnimStart <> 0) then
        begin
        if RealTicks > (fadeAnimStart + FADE_ANIM_TIME) then
            fadeAnimStart:= 0
        else
            if show then
                alpha:= Byte(trunc((RealTicks - fadeAnimStart)/FADE_ANIM_TIME * $FF))
            else
                alpha:= Byte($FF - trunc((RealTicks - fadeAnimStart)/FADE_ANIM_TIME * $FF));
        end;

    with moveAnim do
        if animate then
            if RealTicks > (startTime + MOVE_ANIM_TIME) then
                begin
                startTime:= 0;
                animate:= false;
                frame.x:= target.x;
                frame.y:= target.y;
                active.x:= active.x + (target.x - source.x);
                active.y:= active.y + (target.y - source.y);
                end
            else
                begin
                frame.x:= source.x + Round((target.x - source.x) * ((RealTicks - startTime) / MOVE_ANIM_TIME));
                frame.y:= source.y + Round((target.y - source.y) * ((RealTicks - startTime) / MOVE_ANIM_TIME));
                end;

    if show or (fadeAnimStart <> 0) then
        begin
        Tint($FF, $FF, $FF, alpha);
        DrawTexture(frame.x, frame.y, spritesData[sprite].Texture, buttonScale);
        untint;
        end;
    end;
{$ELSE}
begin
widget:= widget; // avoid hint
{$ENDIF}
end;

procedure BeginWater;
begin
{$IFDEF GL2}
    FlushBatch();
    glUseProgram(shaderWater);
    uCurrentMVPLocation:=uWaterMVPLocation;
    UpdateModelviewProjection;
{$ENDIF}

    openglUseColorOnly(true);
end;

procedure EndWater;
begin
{$IFDEF GL2}
    glUseProgram(shaderMain);
    uCurrentMVPLocation:=uMainMVPLocation;
    UpdateModelviewProjection;
{$ENDIF}

    openglUseColorOnly(false);
end;

procedure PrepareVbForWater(
    WithWalls: Boolean;
    InTopY, OutTopY, InLeftX, OutLeftX, InRightX, OutRightX, BottomY: LongInt;
    out first, count: LongInt);

var firsti, afteri, lol: LongInt;
begin

    // We will draw both bottom water and the water walls with a single call,
    // by rendering a GL_TRIANGLE_STRIP of eight points.
    //
    // GL_TRIANGLE_STRIP works like this: "always create triangle between
    // newest point and the two points that were specified before it."
    //
    // To get the result we want we will order the points like this:
    //                                                                     ^ -Y
    //                                                                     |
    //       0-------1         7-------6   <--------------------- OutTopY -|
    //       |      /|         |     _/|                                   |
    //       |     / |         |    /  |                                   |
    //       |    /  |         |  _/   |                                   |
    //       |   /   |         | /     |                                   |
    //       |  /  _.3---------5{      |   <--------------------- InTopY --|
    //       | / _/   `---.___   `--._ |                                   |
    //       |/_/             `---.___\|                                   |
    //       2-------------------------4   <--------------------- BottomY -|
    //                                                                     |
    //       ^       ^         ^       ^                                   V +Y
    //       |       |         |       |
    //       |       |         |       |
    //       |       |         |       |
    //       |       |         |       |
    //       |       |         |       |
    //       |       |         |       |
    //       |       |         |       |
    //  OutLeftX  InLeftX  InRightX  OutRightX
    //       |       |         |       |
    // <---------------------------------------->
    //     -X                              +X
    //

firsti:= -1;
afteri:=  0;

if InTopY < 0 then
    InTopY:= 0;

if not WithWalls then
    begin
    // if no walls are needed, then bottom water surface spans full length
    InLeftX := OutLeftX;
    InRightX:= OutRightX;
    end
else
    begin

    // animate water walls raise animation at start of game
    if GameTicks < 2000 then
        lol:= 2000 - GameTicks
    else
        lol:= 0;

    if InLeftX > ViewLeftX then
        begin
        VertexBuffer[0].X:= OutLeftX - lol;
        VertexBuffer[0].Y:= OutTopY;
        VertexBuffer[1].X:= InLeftX - lol;
        VertexBuffer[1].Y:= OutTopY;
        // shares vertices 2 and 3 with bottom water
        firsti:= 0;
        afteri:= 4;
        end;

    if InRightX < ViewRightX then
        begin
        VertexBuffer[6].X:= OutRightX + lol;
        VertexBuffer[6].Y:= OutTopY;
        VertexBuffer[7].X:= InRightX + lol;
        VertexBuffer[7].Y:= OutTopY;
        // shares vertices 4 and 5 with bottom water
        if firsti < 0 then
            firsti:= 4;
        afteri:= 8;
        end;
    end;

if InTopY < ViewBottomY then
    begin
    // shares vertices 2-5 with water walls

    // starts at vertex 2
    if (firsti < 0) or (firsti > 2) then
        firsti:= 2;
    // ends at vertex 5
    if afteri < 6 then
        afteri:= 6;
    end;

if firsti < 0 then
    begin
    // nothing to draw at all!
    first:= -1;
    count:= 0;
    exit;
    end;

if firsti < 4 then
    begin
    VertexBuffer[2].X:= OutLeftX;
    VertexBuffer[2].Y:= BottomY;
    VertexBuffer[3].X:= InLeftX;
    VertexBuffer[3].Y:= InTopY;
    end;

if afteri > 4 then
    begin
    VertexBuffer[4].X:= OutRightX;
    VertexBuffer[4].Y:= BottomY;
    VertexBuffer[5].X:= InRightX;
    VertexBuffer[5].Y:= InTopY;
    end;

// first index to draw in vertex buffer
first:= firsti;
// number of points to draw
count:= afteri - firsti;

end;

procedure DrawWater(Alpha: byte; OffsetY, OffsetX: LongInt);
var first, count: LongInt;
begin

if (WorldEdge <> weSea) then
    PrepareVbForWater(false,
        OffsetY + WorldDy + cWaterLine, 0,
        0, ViewLeftX,
        0, ViewRightX,
        ViewBottomY,
        first, count)
else
    PrepareVbForWater(true,
        OffsetY + WorldDy + cWaterLine, ViewTopY,
        leftX  + WorldDx - OffsetX, ViewLeftX,
        rightX + WorldDx + OffsetX, ViewRightX,
        ViewBottomY,
        first, count);

// quit if there's nothing to draw (nothing in view)
if count < 1 then
    exit;

// drawing time

UpdateModelviewProjection;

BeginWater;

if SuddenDeathDmg then
    begin // only set alpha if it differs from what we want
    if SDWaterColorArray[0].a <> Alpha then
        begin
        SDWaterColorArray[0].a := Alpha;
        SDWaterColorArray[1].a := Alpha;
        SDWaterColorArray[2].a := Alpha;
        SDWaterColorArray[3].a := Alpha;
        SDWaterColorArray[4].a := Alpha;
        SDWaterColorArray[5].a := Alpha;
        SDWaterColorArray[6].a := Alpha;
        SDWaterColorArray[7].a := Alpha;
        end;
    SetColorPointer(@SDWaterColorArray[0], 8);
    end
else
    begin
    if WaterColorArray[0].a <> Alpha then
        begin
        WaterColorArray[0].a := Alpha;
        WaterColorArray[1].a := Alpha;
        WaterColorArray[2].a := Alpha;
        WaterColorArray[3].a := Alpha;
        WaterColorArray[4].a := Alpha;
        WaterColorArray[5].a := Alpha;
        WaterColorArray[6].a := Alpha;
        WaterColorArray[7].a := Alpha;
        end;
    SetColorPointer(@WaterColorArray[0], 8);
    end;

SetVertexPointer(@VertexBuffer[0], 8);

glDrawArrays(GL_TRIANGLE_STRIP, first, count);

EndWater;

{$IFNDEF GL2}
// must not be Tint() as color array seems to stay active and color reset is required
glColor4ub($FF, $FF, $FF, $FF);
{$ENDIF}
end;

procedure DrawWaves(Dir, dX, dY, oX: LongInt; tnt: Byte);
var first, count, topy, lx, rx, spriteHeight, spriteWidth, waterSpeed: LongInt;
    waterFrames, waterFrameTicks, frame : LongWord;
    lw, nWaves, shift, realHeight: GLfloat;
    sprite: TSprite;
begin
// note: spriteHeight is the Height of the wave sprite while
//       cWaveHeight describes how many pixels of it will be above waterline

if SuddenDeathDmg then
    begin
    sprite:= sprSDWater;
    waterFrames:= watSDFrames;
    waterFrameTicks:= watSDFrameTicks;
    waterSpeed:= watSDMove;
    end
else
    begin
    sprite:= sprWater;
    waterFrames:= watFrames;
    waterFrameTicks:= watFrameTicks;
    waterSpeed:= watMove;
    end;
 
spriteHeight:= SpritesData[sprite].Height;
realHeight:= SpritesData[sprite].Texture^.ry / waterFrames;

// shift parameters by wave height
// ( ox and dy are used to create different horizontal and vertical offsets
//   between wave layers )
dY:= -cWaveHeight + dy;
ox:= -cWaveHeight + ox;

lx:= leftX  + WorldDx - ox;
rx:= rightX + WorldDx + ox;

topy:= cWaterLine + WorldDy + dY;


if (WorldEdge <> weSea) then
    PrepareVbForWater(false,
        topy, 0,
        0, ViewLeftX,
        0, ViewRightX,
        topy + spriteHeight,
        first, count)
else
    PrepareVbForWater(true,
        topy, ViewTopY,
        lx, lx - spriteHeight,
        rx, rx + spriteHeight,
        topy + spriteHeight,
        first, count);

// quit if there's nothing to draw (nothing in view)
if count < 1 then
    exit;

if SuddenDeathDmg then
    Tint(LongInt(tnt) * SDWaterColorArray[1].r div 255 + 255 - tnt,
         LongInt(tnt) * SDWaterColorArray[1].g div 255 + 255 - tnt,
         LongInt(tnt) * SDWaterColorArray[1].b div 255 + 255 - tnt,
         255
    )
else
    Tint(LongInt(tnt) * WaterColorArray[1].r div 255 + 255 - tnt,
         LongInt(tnt) * WaterColorArray[1].g div 255 + 255 - tnt,
         LongInt(tnt) * WaterColorArray[1].b div 255 + 255 - tnt,
         255
    );

if WorldEdge = weSea then
    begin
    lw:= playWidth;
    dX:= ox;
    end
else
    begin
    lw:= ViewWidth;
    dx:= dx - WorldDx;
    end;

spriteWidth:= SpritesData[sprite].Width;
nWaves:= lw / spriteWidth;
    shift:= - nWaves / 2;

if waterFrames > 1 then
	frame:= RealTicks div waterFrameTicks mod waterFrames
else
	frame:= 0;

TextureBuffer[3].X:= shift + ((LongInt((RealTicks * waterSpeed div 100) shr 6) * Dir + dX) mod spriteWidth) / (spriteWidth - 1);
TextureBuffer[3].Y:= frame * realHeight;
TextureBuffer[5].X:= TextureBuffer[3].X + nWaves;
TextureBuffer[5].Y:= frame * realHeight;
TextureBuffer[4].X:= TextureBuffer[5].X;
TextureBuffer[4].Y:= (frame+1) * realHeight;
TextureBuffer[2].X:= TextureBuffer[3].X;
TextureBuffer[2].Y:= (frame+1) * realHeight;

if (WorldEdge = weSea) then
    begin
    nWaves:= (topy - ViewTopY) / spriteWidth;

    // left side
    TextureBuffer[1].X:= TextureBuffer[3].X - nWaves;
    TextureBuffer[1].Y:= frame * realHeight;
    TextureBuffer[0].X:= TextureBuffer[1].X;
    TextureBuffer[0].Y:= (frame+1) * realHeight;

    // right side
    TextureBuffer[7].X:= TextureBuffer[5].X + nWaves;
    TextureBuffer[7].Y:= frame * realHeight;
    TextureBuffer[6].X:= TextureBuffer[7].X;
    TextureBuffer[6].Y:= (frame+1) * realHeight;
    end;

{$IFDEF GL2}
FlushBatch();
{$ENDIF}
glBindTexture(GL_TEXTURE_2D, SpritesData[sprite].Texture^.id);

SetVertexPointer(@VertexBuffer[0], 8);
SetTexCoordPointer(@TextureBuffer[0], 8);

glDrawArrays(GL_TRIANGLE_STRIP, first, count);

untint;

end;

procedure openglTint(r, g, b, a: Byte); 
{$IFDEF GL2}
const
    scale:Real = 1.0/255.0;
{$ENDIF}
begin
    {$IFDEF GL2}
    glUniform4f(uMainTintLocation, r*scale, g*scale, b*scale, a*scale);
    {$ELSE}
    glColor4ub(r, g, b, a);
    {$ENDIF}
end;

procedure Tint(r, g, b, a: Byte);
var
    nc, tw: Longword;
begin
    nc:= (r shl 24) or (g shl 16) or (b shl 8) or a;

    if nc = LastTint then
        exit;

{$IFDEF GL2}
    FlushBatch();
{$ENDIF}

    if GrayScale then
        begin
        tw:= round(r * RGB_LUMINANCE_RED + g * RGB_LUMINANCE_GREEN + b * RGB_LUMINANCE_BLUE);
        if tw > 255 then
            tw:= 255;
        r:= tw;
        g:= tw;
        b:= tw
        end;

    openglTint(r, g, b, a);
    LastTint:= nc;
end;

procedure Tint(c: Longword); 
begin
    if c = LastTint then exit;
    Tint(((c shr 24) and $FF), ((c shr 16) and $FF), (c shr 8) and $FF, (c and $FF))
end;

procedure untint(); 
begin
    if cWhiteColor = LastTint then exit;
{$IFDEF GL2}
    FlushBatch();
{$ENDIF}
    openglTint($FF, $FF, $FF, $FF);
    LastTint:= cWhiteColor;
end;

procedure setTintAdd(enable: boolean); 
begin
    {$IFDEF GL2}
        FlushBatch();
        if enable then
            glUniform1i(glGetUniformLocation(shaderMain, pchar('tintAdd')), 1)
        else
            glUniform1i(glGetUniformLocation(shaderMain, pchar('tintAdd')), 0);
    {$ELSE}
    if enable then
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD)
    else
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    {$ENDIF}
end;

procedure ChangeDepth(rm: TRenderMode; d: GLfloat);
var tmp: LongInt;
begin
{$IFNDEF USE_S3D_RENDERING}
    rm:= rm; d:= d; tmp:= tmp; // avoid hint
{$ELSE}
    d:= d / 5;
    if rm = rmDefault then
        exit
    else if rm = rmLeftEye then
        d:= -d;
    cStereoDepth:= cStereoDepth + d;
    openglTranslProjMatrix(d, 0, 0);
    tmp:= round(d / cScaleFactor * cScreenWidth);
    ViewLeftX := ViewLeftX  - tmp;
    ViewRightX:= ViewRightX - tmp;
{$ENDIF}
end;

procedure ResetDepth(rm: TRenderMode);
var tmp: LongInt;
begin
{$IFNDEF USE_S3D_RENDERING}
    rm:= rm; tmp:= tmp; // avoid hint
{$ELSE}
    if rm = rmDefault then
        exit;
    openglTranslProjMatrix(-cStereoDepth, 0, 0);
    tmp:= round(cStereoDepth / cScaleFactor * cScreenWidth);
    ViewLeftX := ViewLeftX  + tmp;
    ViewRightX:= ViewRightX + tmp;
    cStereoDepth:= 0;
{$ENDIF}
end;


procedure initModule;
begin
    LastTint:= cWhiteColor + 1;
{$IFDEF GL2}
    batchInited:= false;
    batchCount:= 0;
    batchTexId:= 0;
{$ELSE}
    LastColorPointer    := nil;
    LastTexCoordPointer := nil;
    LastVertexPointer   := nil;
{$ENDIF}
end;

procedure freeModule;
begin
    if cOnlyStats then exit;
{$IFDEF GL2}
    if batchInited then
        glDeleteBuffers(1, @batchVBO);
    glDeleteProgram(shaderMain);
    glDeleteProgram(shaderWater);
    glDeleteBuffers(1, @vBuffer);
    glDeleteBuffers(1, @tBuffer);
    glDeleteBuffers(1, @cBuffer);
{$ENDIF}
end;
end.
