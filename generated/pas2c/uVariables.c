#include "fpcrtl.h"

#include "uVariables.h"
LongInt cMinScreenWidth;
LongInt cMinScreenHeight;
LongInt cFullscreenWidth;
LongInt cFullscreenHeight;
LongInt cWindowedWidth;
LongInt cWindowedHeight;
boolean cWindowedMaximized;
LongInt cScreenWidth;
LongInt cScreenHeight;
LongInt cNewScreenWidth;
LongInt cNewScreenHeight;
LongWord cScreenResizeDelay;
Word ipcPort;
boolean AprilOne;
boolean cFullScreen;
string255 cLanguageFName;
string255 cLanguage;
LongInt cTimerInterval;
astring PathPrefix;
astring UserPathPrefix;
boolean cShowFPS;
boolean cFlattenFlakes;
boolean cFlattenClouds;
boolean cIce;
boolean cSnow;
boolean isInChatMode;
boolean cAltDamage;
LongWord cReducedQuality;
boolean cHolidaySilliness;
string255 UserNick;
string255 recordFileName;
LongWord cReadyDelay;
TStereoMode cStereoMode;
boolean cOnlyStats;
string255 cMapName;
LongInt syncedPixelDigest;
boolean isCursorVisible;
boolean isInLag;
boolean isPaused;
boolean isInMultiShoot;
boolean isSpeed;
boolean isAFK;
boolean isShowMission;
boolean isShowGearInfo;
boolean isForceMission;
LongWord SpeedStart;
boolean fastUntilLag;
boolean fastForward;
boolean fastScrolling;
boolean autoCameraOn;
LongWord CheckSum;
string255 CampaignVariable;
string255 MissionVariable;
LongWord GameTicks;
LongWord FFGameTick;
LongWord OuchTauntTimer;
TGameState GameState;
TGameType GameType;
LongWord InputMask;
LongWord GameFlags;
TWorldEdge WorldEdge;
LongWord LeftImpactTimer;
LongWord RightImpactTimer;
LongWord TurnTimeLeft;
boolean TurnClockActive;
LongWord TagTurnTimeLeft;
LongWord ReadyTimeLeft;
LongWord TimeNotInTurn;
boolean IsGetAwayTime;
boolean GameOver;
LongInt cSuddenDTurns;
LongInt LastSuddenDWarn;
LongInt cInitHealth;
LongInt cDamagePercent;
LongWord cMineDudPercent;
LongInt cTemplateFilter;
LongInt cFeatureSize;
TMapGen cMapGen;
LongWord cRopePercent;
LongWord cRopeNodeStep;
LongInt cRopeLayers;
LongWord cGetAwayTime;
boolean cAdvancedMapGenMode;
LongWord cHedgehogTurnTime;
LongInt cMinesTime;
LongWord cMaxAIThinkTime;
LongInt cHealthCaseProb;
LongInt cHealthCaseAmount;
LongInt cWaterRise;
LongInt cHealthDecrease;
LongWord cCloudsNumber;
LongWord cSDCloudsNumber;
Byte cTagsMask;
Byte cPrevTagsMask;
GLfloat zoom;
GLfloat ZoomValue;
GLfloat UserZoom;
real ChatScaleValue;
real cDefaultChatScale;
real UIScaleValue;
LongInt cWaterLine;
LongInt cGearScrEdgesDist;
boolean isAudioMuted;
LongWord ExplosionBorderColorR;
LongWord ExplosionBorderColorG;
LongWord ExplosionBorderColorB;
LongWord ExplosionBorderColorNoA;
LongWord ExplosionBorderColor;
LongWord IceColor;
LongWord IceEdgeColor;
Byte WaterOpacity;
Byte SDWaterOpacity;
boolean GrayScale;
CountTexz_tt CountTexz;
LongInt LAND_WIDTH;
LongInt LAND_HEIGHT;
LongWord LAND_WIDTH_MASK;
LongWord LAND_HEIGHT_MASK;
PTexture ChefHatTexture;
PTexture CrosshairTexture;
PTexture GenericHealthTexture;
LongInt cLeftScreenBorder;
LongInt cRightScreenBorder;
LongWord cScreenSpace;
LongWord cCaseFactor;
LongWord cMaxCaseDrops;
LongWord cLandMines;
LongWord cAirMines;
LongWord cSentries;
LongWord cExplosives;
string255 cScriptName;
string255 cScriptParam;
string255 cSeed;
boolean cIsSoundEnabled;
LongInt cVolumeDelta;
boolean cVolumeUpKey;
boolean cVolumeDownKey;
boolean cMuteToggle;
boolean cHasFocus;
LongWord cInactDelay;
boolean bBetweenTurns;
boolean bWaterRising;
boolean bDuringWaterRise;
LongInt CrosshairX;
LongInt CrosshairY;
PGear CrosshairGear;
LongInt CursorMovementX;
LongInt CursorMovementY;
LongInt cWaveHeight;
hwFloat cDrownSpeed;
real cDrownSpeedf;
hwFloat cMaxWindSpeed;
hwFloat cWindSpeed;
real cWindSpeedf;
hwFloat cElastic;
hwFloat cGravity;
real cGravityf;
boolean cLowGravity;
LongInt cBuildMaxDist;
hwFloat cDamageModifier;
boolean cLaserSighting;
boolean cLaserSightingSniper;
boolean cVampiric;
PTexture WeaponTooltipTex;
boolean AmmoMenuInvalidated;
TSDL_Rect AmmoRect;
PTexture HHTexture;
real cMaxZoomLevel;
real cMinZoomLevel;
real cZoomDelta;
real cZoomDeltaSmall;
real cMinMaxZoomLevelDelta;
LongInt cDemoClockFPSOffsetY;
boolean flagMakeCapture;
boolean flagDumpLand;
LongWord InitStepsFlags;
LongWord RealTicks;
LongInt AttackBar;
WaterColorArray_tt WaterColorArray;
SDWaterColorArray_tt SDWaterColorArray;
ClanColorArray_tt ClanColorArray;
TPoint TargetCursorPoint;
TPoint CursorPoint;
TPoint CursorPointDelta;
TPoint TargetPoint;
TScreenFade ScreenFade;
LongInt ScreenFadeValue;
LongInt ScreenFadeSpeed;
boolean InCinematicMode;
LongInt CinematicSteps;
LongInt CinematicBarH;
boolean CinematicScript;
TUIDisplay UIDisplay;
LongWord LocalMessage;
string255 Theme;
boolean disableLandBack;
LongInt WorldDx;
LongInt WorldDy;
LongInt SpeechHogNumber;
LongInt ViewLeftX;
LongInt ViewRightX;
LongInt ViewBottomY;
LongInt ViewTopY;
LongInt ViewWidth;
LongInt ViewHeight;
LongInt UIWidth;
LongInt UIHeight;
boolean cViewLimitsDebug;
LongInt dirtyLandTexCount;
Word hiTicks;
astring LuaGoals;
LongWord LuaTemplateNumber;
boolean LuaEndTurnRequested;
boolean LuaNoEndTurnTaunts;
boolean LuaClockPaused;
boolean LuaCmdUsed;
MaskedSounds_tt MaskedSounds;
TVoice LastVoice;
TMobileRecord mobileRecord;
LongInt MaxTextureSize;
PSDL_Window SDLwindow;
PSDL_GLContext SDLGLcontext;
cPathz_tt cPathz;
cPathzInit_tt cPathzInit = {STRINIT(""),
                            STRINIT("//"),
                            STRINIT("/Graphics"),
                            STRINIT("/Themes"),
                            STRINIT("/Themes/Nature"),
                            STRINIT("/Config"),
                            STRINIT("/Config/Teams"),
                            STRINIT("/Maps"),
                            STRINIT(""),
                            STRINIT("/Demos"),
                            STRINIT("/Sounds"),
                            STRINIT("/Graphics/Graves"),
                            STRINIT("/Fonts"),
                            STRINIT("/Forts"),
                            STRINIT("/Locale"),
                            STRINIT("/Graphics/AmmoMenu"),
                            STRINIT("/Graphics/Hedgehog"),
                            STRINIT("/Sounds/voices"),
                            STRINIT("/Graphics/Hats"),
                            STRINIT("/Graphics/Flags"),
                            STRINIT("/Missions/Maps"),
                            STRINIT("/Graphics/SuddenDeath"),
                            STRINIT("/Graphics/Buttons"),
                            STRINIT("/Shaders"),
                            STRINIT("/Sounds/voices/Default"),
                            STRINIT("/misc")};
Fontz_tt Fontz;
FontzInit_tt FontzInit = {{
                              .Handle = NULL,
                              .Height = 12,
                              .style = TTF_STYLE_NORMAL,
                              .Name = STRINIT("DejaVuSans-Bold.ttf")
                          },
                          {
                              .Handle = NULL,
                              .Height = 24,
                              .style = TTF_STYLE_NORMAL,
                              .Name = STRINIT("DejaVuSans-Bold.ttf")
                          },
                          {
                              .Handle = NULL,
                              .Height = 10,
                              .style = TTF_STYLE_NORMAL,
                              .Name = STRINIT("DejaVuSans-Bold.ttf")
                          },
                          {
                              .Handle = NULL,
                              .Height = 12,
                              .style = TTF_STYLE_NORMAL,
                              .Name = STRINIT("DejaVuSans-Bold.ttf")
                          },
                          {
                              .Handle = NULL,
                              .Height = 12,
                              .style = TTF_STYLE_NORMAL,
                              .Name = STRINIT("wqy-zenhei.ttc")
                          },
                          {
                              .Handle = NULL,
                              .Height = 24,
                              .style = TTF_STYLE_NORMAL,
                              .Name = STRINIT("wqy-zenhei.ttc")
                          },
                          {
                              .Handle = NULL,
                              .Height = 10,
                              .style = TTF_STYLE_NORMAL,
                              .Name = STRINIT("wqy-zenhei.ttc")
                          },
                          {
                              .Handle = NULL,
                              .Height = 12,
                              .style = TTF_STYLE_NORMAL,
                              .Name = STRINIT("wqy-zenhei.ttc")
                          }};
SpritesData_tt SpritesData;
SpritesDataInit_tt SpritesDataInit = {{
                                          .FileName = STRINIT("BlueWater"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = -1,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Clouds"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 256,
                                          .Height = 128,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Bomb"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 8,
                                          .Height = 8,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("BigDigits"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("BigDigitsGray"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("BigDigitsGreen"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("BigDigitsRed"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Frame"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 4,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Lag"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 65,
                                          .Height = 65,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Arrow"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("BazookaShell"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Targetp"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Bee"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SmokeTrace"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("RopeHook"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Expl50"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("MineOff"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 8,
                                          .Height = 8,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("MineOn"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 8,
                                          .Height = 8,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("MineDead"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 8,
                                          .Height = 8,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Case"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 48,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("FirstAid"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 48,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("dynamite"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Power"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ClBomb"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ClParticle"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Flame"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("horizont"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("horizontL"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("horizontR"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Sky"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SkyL"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SkyR"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Slot"),
                                          .Path = ptAmmoMenu,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Ammos_base"),
                                          .Path = ptAmmoMenu,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Ammos_bw_base"),
                                          .Path = ptAmmoMenu,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SlotKeys"),
                                          .Path = ptAmmoMenu,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Corners"),
                                          .Path = ptAmmoMenu,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 2,
                                          .Height = 2,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Finger"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("AirBomb"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Airplane"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 256,
                                          .Height = 128,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amAirplane"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amGirder"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 160,
                                          .Height = 160,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("hhMask"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Switch"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 40,
                                          .Height = 40,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Parachute"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 48,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Target"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("RopeNode"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("thinking"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("PowerBar"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 256,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("WindBar"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 151,
                                          .Height = 17,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("WindL"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 80,
                                          .Height = 13,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("WindR"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 80,
                                          .Height = 13,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Flake"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amRope"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amBazooka"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amShotgun"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amDEagle"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amAirAttack"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amBaseball"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Hammer"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amBTorch_i"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amBTorch_w"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Teleport"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("HHDeath"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amShotgun_w"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amDEagle_w"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Idle"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Mortar"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("TurnsLeft"),
                                          .Path = ptAmmoMenu,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amKamikaze"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amWhip"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Kowtow"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Sad"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Wave"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Hurrah"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ILoveLemonade"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Shrug"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Juggle"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ExplPart"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ExplPart2"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Cake_walk"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Cake_down"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Watermelon"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("EvilTrace"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("HellishBomb"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Seduction"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("HHDress"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Censored"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Drill"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amDrill"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amBallgun"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Balls"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 20,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("RCPlane"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amRCPlane"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Utility"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 48,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Invulnerable"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 48,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Vampiric"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 48,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amGirder"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 512,
                                          .Height = 512,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SpeechCorner"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 12,
                                          .Height = 9,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SpeechEdge"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 25,
                                          .Height = 9,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SpeechTail"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 25,
                                          .Height = 26,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ThoughtCorner"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 49,
                                          .Height = 37,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ThoughtEdge"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 23,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ThoughtTail"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 45,
                                          .Height = 65,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ShoutCorner"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 34,
                                          .Height = 23,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ShoutEdge"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 30,
                                          .Height = 20,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ShoutTail"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 30,
                                          .Height = 37,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amSniperRifle"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Bubbles"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amJetpack"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Health"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amMolotov"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Molotov"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Smoke"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 22,
                                          .Height = 22,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SmokeWhite"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 22,
                                          .Height = 22,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Shells"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 8,
                                          .Height = 8,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLow,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Dust"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 22,
                                          .Height = 22,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SnowDust"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 22,
                                          .Height = 22,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Explosives"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 48,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("ExplosivesRoll"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 48,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amTeleport"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Splash"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 80,
                                          .Height = 50,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Droplet"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Birdy"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 75,
                                          .Height = 75,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amCake"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amConstruction"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amGrenade"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amMelon"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amMortar"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amSkip"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amCluster"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amDynamite"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amHellish"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amMine"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amSeduction"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amVamp"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 128,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("BigExplosion"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 385,
                                          .Height = 385,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SmokeRing"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 200,
                                          .Height = 200,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("BeeTrace"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Egg"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("TargetBee"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amBee"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 128,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Feather"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 15,
                                          .Height = 25,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Piano"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 128,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amSineGun"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amPortalGun"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Portal"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("cheese"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amCheese"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amFlamethrower"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 128,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Chunk"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Note"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SMineOff"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 8,
                                          .Height = 8,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SMineOn"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 8,
                                          .Height = 8,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amSMine"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amHammer"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amResurrector"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Cross"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 108,
                                          .Height = 138,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("AirDrill"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("NapalmBomb"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("BulletHit"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Snowball"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amSnowball"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptHedgehog,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Snow"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 4,
                                          .Height = 4,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SDFlake"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptSuddenDeath,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SDWater"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptSuddenDeath,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = -2,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SDClouds"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptSuddenDeath,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 256,
                                          .Height = 128,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SDSplash"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptSuddenDeath,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 80,
                                          .Height = 50,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SDDroplet"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptSuddenDeath,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 16,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Timebox"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 50,
                                          .Height = 81,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("slider"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 3,
                                          .Height = 17,
                                          .imageWidth = 3,
                                          .imageHeight = 17,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLow,
                                          .getDimensions = false,
                                          .getImageDimensions = false
                                      },
                                      {
                                          .FileName = STRINIT("botlevels"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 22,
                                          .Height = 15,
                                          .imageWidth = 22,
                                          .imageHeight = 15,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLow,
                                          .getDimensions = false,
                                          .getImageDimensions = false
                                      },
                                      {
                                          .FileName = STRINIT("amCleaver"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 128,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("cleaver"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 64,
                                          .imageHeight = 128,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLow,
                                          .getDimensions = false,
                                          .getImageDimensions = false
                                      },
                                      {
                                          .FileName = STRINIT("star"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 12,
                                          .Height = 12,
                                          .imageWidth = 12,
                                          .imageHeight = 12,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLow,
                                          .getDimensions = false,
                                          .getImageDimensions = false
                                      },
                                      {
                                          .FileName = STRINIT("icetexture"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 128,
                                          .Height = 128,
                                          .imageWidth = 128,
                                          .imageHeight = 128,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLow,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amIceGun"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 32,
                                          .imageHeight = 32,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLow,
                                          .getDimensions = false,
                                          .getImageDimensions = false
                                      },
                                      {
                                          .FileName = STRINIT("amFrozenHog"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 64,
                                          .imageHeight = 64,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLow,
                                          .getDimensions = false,
                                          .getImageDimensions = false
                                      },
                                      {
                                          .FileName = STRINIT("amRubber"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 160,
                                          .Height = 160,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("boing"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 101,
                                          .Height = 97,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLow,
                                          .getDimensions = false,
                                          .getImageDimensions = false
                                      },
                                      {
                                          .FileName = STRINIT("custom1"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpLow,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("custom2"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpLow,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("custom3"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpLow,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("custom4"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpLow,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("custom5"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpLow,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("custom6"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpLow,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("custom7"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpLow,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("custom8"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 0,
                                          .Height = 0,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpLow,
                                          .getDimensions = true,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("FrozenAirMine"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 32,
                                          .imageHeight = 32,
                                          .saveSurf = true,
                                          .critical = true,
                                          .checkSum = true,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("AirMine"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amAirMine"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("FlakeL"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SDFlakeL"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptSuddenDeath,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpHighest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("CloudsL"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 256,
                                          .Height = 128,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("SDCloudsL"),
                                          .Path = ptCurrTheme,
                                          .AltPath = ptGraphics,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 256,
                                          .Height = 128,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = false,
                                          .checkSum = false,
                                          .priority = tpHigh,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Duck"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amDuck"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amMinigun"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("sliderInverted"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 3,
                                          .Height = 17,
                                          .imageWidth = 3,
                                          .imageHeight = 17,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLow,
                                          .getDimensions = false,
                                          .getImageDimensions = false
                                      },
                                      {
                                          .FileName = STRINIT("FingerBack"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("FingerBackInv"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 48,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("TargetpBack"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("TargetpBackInv"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("HealthHUD"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 18,
                                          .Height = 18,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("HealthPoisonHUD"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 18,
                                          .Height = 18,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("VampHUD"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 24,
                                          .Height = 18,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("KarmaHUD"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 18,
                                          .Height = 18,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("MedicHUD"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 18,
                                          .Height = 18,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("MedicPoisonHUD"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 18,
                                          .Height = 18,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("HaloHUD"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 22,
                                          .Height = 11,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("InvulnHUD"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 18,
                                          .Height = 18,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amPiano"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 42,
                                          .Height = 42,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amLandGun"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amShoryuken"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("throughWrap"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 16,
                                          .Height = 13,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("dynamiteDefused"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Bubble"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 38,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Happy"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpLowest,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("Duck"),
                                          .Path = ptGraphics,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 32,
                                          .Height = 32,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      },
                                      {
                                          .FileName = STRINIT("amDuck"),
                                          .Path = ptHedgehog,
                                          .AltPath = ptNone,
                                          .Texture = NULL,
                                          .Surface = NULL,
                                          .Width = 64,
                                          .Height = 64,
                                          .imageWidth = 0,
                                          .imageHeight = 0,
                                          .saveSurf = false,
                                          .critical = true,
                                          .checkSum = false,
                                          .priority = tpMedium,
                                          .getDimensions = false,
                                          .getImageDimensions = true
                                      }};
Wavez_tt Wavez = {{
                      .Sprite = sprKowtow,
                      .FramesCount = 12,
                      .Interval = 125,
                      .cmd = STRINIT("/rollup"),
                      .Voice = sndNone,
                      .VoiceDelay = 0
                  },
                  {
                      .Sprite = sprSad,
                      .FramesCount = 14,
                      .Interval = 125,
                      .cmd = STRINIT("/sad"),
                      .Voice = sndNone,
                      .VoiceDelay = 0
                  },
                  {
                      .Sprite = sprWave,
                      .FramesCount = 16,
                      .Interval = 125,
                      .cmd = STRINIT("/wave"),
                      .Voice = sndHello,
                      .VoiceDelay = 5
                  },
                  {
                      .Sprite = sprHurrah,
                      .FramesCount = 14,
                      .Interval = 125,
                      .cmd = STRINIT("/hurrah"),
                      .Voice = sndNone,
                      .VoiceDelay = 0
                  },
                  {
                      .Sprite = sprLemonade,
                      .FramesCount = 24,
                      .Interval = 125,
                      .cmd = STRINIT("/ilovelotsoflemonade"),
                      .Voice = sndNone,
                      .VoiceDelay = 0
                  },
                  {
                      .Sprite = sprShrug,
                      .FramesCount = 24,
                      .Interval = 125,
                      .cmd = STRINIT("/shrug"),
                      .Voice = sndNone,
                      .VoiceDelay = 0
                  },
                  {
                      .Sprite = sprJuggle,
                      .FramesCount = 49,
                      .Interval = 38,
                      .cmd = STRINIT("/juggle"),
                      .Voice = sndNone,
                      .VoiceDelay = 0
                  },
                  {
                      .Sprite = sprHogBubble,
                      .FramesCount = 19,
                      .Interval = 125,
                      .cmd = STRINIT("/bubble"),
                      .Voice = sndNone,
                      .VoiceDelay = 0
                  },
                  {
                      .Sprite = sprHappy,
                      .FramesCount = 14,
                      .Interval = 125,
                      .cmd = STRINIT("/happy"),
                      .Voice = sndNone,
                      .VoiceDelay = 0
                  }};
Ammoz_tt Ammoz;
TAmmoCounts InitialAmmoCounts;
AmmozInit_tt AmmozInit = {{
                              .NameId = sidNothing,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 0,
                              .Ammo = {
                                          .Propz = ((ammoprop_NoCrosshair | ammoprop_DontHold) | ammoprop_Effect),
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amNothing,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = cHiddenSlotIndex,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidGrenade,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_Timerable | ammoprop_Power) | ammoprop_AltUse) | ammoprop_SetBounce) | ammoprop_NeedUpDown),
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 0,
                                          .Timer = 3000,
                                          .Pos = 0,
                                          .AmmoType = amGrenade,
                                          .AttackVoice = sndCover,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 1,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidClusterBomb,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 3,
                              .Ammo = {
                                          .Propz = ((((ammoprop_Timerable | ammoprop_Power) | ammoprop_AltUse) | ammoprop_SetBounce) | ammoprop_NeedUpDown),
                                          .Count = 5,
                                          .NumPerTurn = 0,
                                          .Timer = 3000,
                                          .Pos = 0,
                                          .AmmoType = amClusterBomb,
                                          .AttackVoice = sndCover,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 1,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidBazooka,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_Power | ammoprop_AltUse) | ammoprop_NeedUpDown),
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amBazooka,
                                          .AttackVoice = sndFire,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 0,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = -6
                          },
                          {
                              .NameId = sidBee,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((((ammoprop_Power | ammoprop_NeedTarget) | ammoprop_NoTargetAfter) | ammoprop_NoWrapTarget) | ammoprop_DontHold) | ammoprop_AltUse) | ammoprop_NeedUpDown),
                                          .Count = 2,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amBee,
                                          .AttackVoice = sndFire,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 0,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 2,
                              .PosSprite = sprTargetBee,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidShotgun,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_ForwMsgs | ammoprop_NeedUpDown) | ammoprop_DoesntStopTimerInMultiShoot),
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 1,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amShotgun,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 2,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = -6
                          },
                          {
                              .NameId = sidPickHammer,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_ForwMsgs | ammoprop_AttackInMove) | ammoprop_NoCrosshair) | ammoprop_DontHold) | ammoprop_DoesntStopTimerWhileAttackingInInfAttackMode),
                                          .Count = 2,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amPickHammer,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 6,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidSkip,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((ammoprop_NoCrosshair | ammoprop_AttackInMove) | ammoprop_DontHold) | ammoprop_ForceTurnEnd),
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amSkip,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 9,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidRope,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 3,
                              .Ammo = {
                                          .Propz = ((((((ammoprop_NoRoundEnd | ammoprop_ForwMsgs) | ammoprop_AttackInMove) | ammoprop_Utility) | ammoprop_AltAttack) | ammoprop_NeedUpDown) | ammoprop_DoesntStopTimerWhileAttacking),
                                          .Count = 5,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amRope,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 7,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = (cMaxAngle / 2),
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidMine,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_NoCrosshair | ammoprop_AttackInMove) | ammoprop_DontHold) | ammoprop_AltUse) | ammoprop_SetBounce),
                                          .Count = 2,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amMine,
                                          .AttackVoice = sndLaugh,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 4,
                              .TimeAfterTurn = 5000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidDEagle,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 2,
                              .Ammo = {
                                          .Propz = (ammoprop_NeedUpDown | ammoprop_DoesntStopTimerInMultiShoot),
                                          .Count = 3,
                                          .NumPerTurn = 3,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amDEagle,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 2,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = -6
                          },
                          {
                              .NameId = sidDynamite,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((ammoprop_NoCrosshair | ammoprop_AttackInMove) | ammoprop_DontHold) | ammoprop_AltUse),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amDynamite,
                                          .AttackVoice = sndLaugh,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 4,
                              .TimeAfterTurn = 5000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidFirePunch,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_NoCrosshair | ammoprop_ForwMsgs) | ammoprop_AttackInMove),
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amFirePunch,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 3,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidWhip,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ammoprop_NoCrosshair,
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amWhip,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 3,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidBaseballBat,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (ammoprop_DontHold | ammoprop_NeedUpDown),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amBaseballBat,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 3,
                              .TimeAfterTurn = 5000,
                              .minAngle = 0,
                              .maxAngle = (cMaxAngle / 2),
                              .isDamaging = true,
                              .SkipTurns = 2,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidParachute,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((((((ammoprop_NoRoundEnd | ammoprop_ForwMsgs) | ammoprop_AttackInMove) | ammoprop_NoCrosshair) | ammoprop_DontHold) | ammoprop_Utility) | ammoprop_AltAttack) | ammoprop_ShowSelIcon) | ammoprop_NeedUpDown),
                                          .Count = 2,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amParachute,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 7,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidAirAttack,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_NoCrosshair | ammoprop_NeedTarget) | ammoprop_AttackingPut) | ammoprop_DontHold) | ammoprop_NotBorder),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amAirAttack,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 5,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 5,
                              .PosCount = 2,
                              .PosSprite = sprAmAirplane,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidMineStrike,
                              .NameTex = NULL,
                              .Probability = 200,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_NoCrosshair | ammoprop_NeedTarget) | ammoprop_AttackingPut) | ammoprop_DontHold) | ammoprop_NotBorder),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amMineStrike,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 5,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 5,
                              .PosCount = 2,
                              .PosSprite = sprAmAirplane,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidBlowTorch,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 2,
                              .Ammo = {
                                          .Propz = ((ammoprop_ForwMsgs | ammoprop_NeedUpDown) | ammoprop_DoesntStopTimerWhileAttackingInInfAttackMode),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amBlowTorch,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 6,
                              .TimeAfterTurn = 3000,
                              .minAngle = 804,
                              .maxAngle = 1327,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidGirder,
                              .NameTex = NULL,
                              .Probability = 150,
                              .NumberInCase = 3,
                              .Ammo = {
                                          .Propz = ((((ammoprop_NoRoundEnd | ammoprop_NoCrosshair) | ammoprop_NeedTarget) | ammoprop_Utility) | ammoprop_AttackingPut),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amGirder,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 6,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 8,
                              .PosSprite = sprAmGirder,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidTeleport,
                              .NameTex = NULL,
                              .Probability = 200,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((((ammoprop_ForwMsgs | ammoprop_NoCrosshair) | ammoprop_NeedTarget) | ammoprop_AttackingPut) | ammoprop_AttackInMove) | ammoprop_Utility) | ammoprop_DontHold),
                                          .Count = 2,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amTeleport,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 7,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 2,
                              .PosSprite = sprAmTeleport,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidSwitch,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((((ammoprop_NoRoundEnd | ammoprop_ForwMsgs) | ammoprop_NoCrosshair) | ammoprop_Utility) | ammoprop_ShowSelIcon) | ammoprop_DontHold),
                                          .Count = 3,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amSwitch,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 9,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidMortar,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 4,
                              .Ammo = {
                                          .Propz = ammoprop_NeedUpDown,
                                          .Count = 4,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amMortar,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 0,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = -6
                          },
                          {
                              .NameId = sidKamikaze,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_ForwMsgs | ammoprop_DontHold) | ammoprop_NeedUpDown) | ammoprop_AttackInMove) | ammoprop_ForceTurnEnd),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amKamikaze,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 3,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidCake,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((ammoprop_ForwMsgs | ammoprop_NoCrosshair) | ammoprop_DontHold) | ammoprop_Track),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amCake,
                                          .AttackVoice = sndLaugh,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 4,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 4,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidSeduction,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_ForwMsgs | ammoprop_DontHold) | ammoprop_NoCrosshair),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amSeduction,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 3,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidWatermelon,
                              .NameTex = NULL,
                              .Probability = 400,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((ammoprop_Timerable | ammoprop_Power) | ammoprop_NeedUpDown) | ammoprop_AltUse),
                                          .Count = 0,
                                          .NumPerTurn = 0,
                                          .Timer = 3000,
                                          .Pos = 0,
                                          .AmmoType = amWatermelon,
                                          .AttackVoice = sndMelon,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 1,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidHellishBomb,
                              .NameTex = NULL,
                              .Probability = 400,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_Power | ammoprop_NeedUpDown) | ammoprop_AltUse),
                                          .Count = 0,
                                          .NumPerTurn = 0,
                                          .Timer = 5000,
                                          .Pos = 0,
                                          .AmmoType = amHellishBomb,
                                          .AttackVoice = sndWatchThis,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 1,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidNapalm,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_NoCrosshair | ammoprop_NeedTarget) | ammoprop_AttackingPut) | ammoprop_DontHold) | ammoprop_NotBorder),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amNapalm,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 5,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 7,
                              .PosCount = 2,
                              .PosSprite = sprAmAirplane,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidDrill,
                              .NameTex = NULL,
                              .Probability = 300,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_Power | ammoprop_NeedUpDown) | ammoprop_AltUse),
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amDrill,
                                          .AttackVoice = sndFire,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 0,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprDrill,
                              .ejectX = 0,
                              .ejectY = -6
                          },
                          {
                              .NameId = sidBallgun,
                              .NameTex = NULL,
                              .Probability = 400,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_ForwMsgs | ammoprop_NeedUpDown) | ammoprop_DontHold),
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 0,
                                          .Timer = 5001,
                                          .Pos = 0,
                                          .AmmoType = amBallgun,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 4,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = -3
                          },
                          {
                              .NameId = sidRCPlane,
                              .NameTex = NULL,
                              .Probability = 200,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (ammoprop_ForwMsgs | ammoprop_NeedUpDown),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amRCPlane,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 4,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 4,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidLowGravity,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((((ammoprop_NoRoundEnd | ammoprop_NoCrosshair) | ammoprop_DontHold) | ammoprop_AltUse) | ammoprop_ShowSelIcon) | ammoprop_Utility) | ammoprop_Effect),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amLowGravity,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 9,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidExtraDamage,
                              .NameTex = NULL,
                              .Probability = 15,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((((ammoprop_NoRoundEnd | ammoprop_NoCrosshair) | ammoprop_DontHold) | ammoprop_AltUse) | ammoprop_ShowSelIcon) | ammoprop_Utility) | ammoprop_Effect),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amExtraDamage,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 9,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidInvulnerable,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((((ammoprop_NoRoundEnd | ammoprop_NoCrosshair) | ammoprop_DontHold) | ammoprop_AltUse) | ammoprop_ShowSelIcon) | ammoprop_Utility) | ammoprop_Effect),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amInvulnerable,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 8,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidExtraTime,
                              .NameTex = NULL,
                              .Probability = 30,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((((ammoprop_NoRoundEnd | ammoprop_NoCrosshair) | ammoprop_DontHold) | ammoprop_AltUse) | ammoprop_ShowSelIcon) | ammoprop_Utility) | ammoprop_Effect),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amExtraTime,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 9,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidLaserSight,
                              .NameTex = NULL,
                              .Probability = 15,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((((((ammoprop_NoRoundEnd | ammoprop_NoCrosshair) | ammoprop_DontHold) | ammoprop_AltUse) | ammoprop_ShowSelIcon) | ammoprop_Utility) | ammoprop_NeedUpDown) | ammoprop_Effect),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amLaserSight,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 8,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidVampiric,
                              .NameTex = NULL,
                              .Probability = 15,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((((ammoprop_NoRoundEnd | ammoprop_NoCrosshair) | ammoprop_DontHold) | ammoprop_AltUse) | ammoprop_Utility) | ammoprop_Effect),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amVampiric,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 8,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidSniperRifle,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 2,
                              .Ammo = {
                                          .Propz = (((ammoprop_NeedUpDown | ammoprop_OscAim) | ammoprop_NoMoveAfter) | ammoprop_DoesntStopTimerInMultiShoot),
                                          .Count = 2,
                                          .NumPerTurn = 1,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amSniperRifle,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 2,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = -5
                          },
                          {
                              .NameId = sidJetpack,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((((((ammoprop_NoRoundEnd | ammoprop_ForwMsgs) | ammoprop_AttackInMove) | ammoprop_DontHold) | ammoprop_Utility) | ammoprop_NeedUpDown) | ammoprop_ShowSelIcon) | ammoprop_AltAttack),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amJetpack,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 7,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidMolotov,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_Power | ammoprop_NeedUpDown) | ammoprop_AltUse),
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 0,
                                          .Timer = 3000,
                                          .Pos = 0,
                                          .AmmoType = amMolotov,
                                          .AttackVoice = sndWatchThis,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 1,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidBirdy,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_ForwMsgs | ammoprop_NoCrosshair) | ammoprop_NeedUpDown) | ammoprop_ShowSelIcon) | ammoprop_DontHold),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amBirdy,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 7,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidPortalGun,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_NoRoundEnd | ammoprop_AttackInMove) | ammoprop_DontHold) | ammoprop_NeedUpDown) | ammoprop_Utility),
                                          .Count = 1,
                                          .NumPerTurn = 3,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amPortalGun,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 7,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = -5,
                              .ejectY = -7
                          },
                          {
                              .NameId = sidPiano,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((((ammoprop_NoCrosshair | ammoprop_NeedTarget) | ammoprop_AttackingPut) | ammoprop_DontHold) | ammoprop_NotBorder) | ammoprop_ForceTurnEnd),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amPiano,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 5,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 7,
                              .PosCount = 1,
                              .PosSprite = sprAmPiano,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidGasBomb,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_Timerable | ammoprop_Power) | ammoprop_AltUse) | ammoprop_NeedUpDown) | ammoprop_SetBounce),
                                          .Count = AMMO_INFINITE,
                                          .NumPerTurn = 0,
                                          .Timer = 3000,
                                          .Pos = 0,
                                          .AmmoType = amGasBomb,
                                          .AttackVoice = sndCover,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 1,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidSineGun,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 2,
                              .Ammo = {
                                          .Propz = (ammoprop_AttackInMove | ammoprop_NeedUpDown),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amSineGun,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 2,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidFlamethrower,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_ForwMsgs | ammoprop_NeedUpDown) | ammoprop_DontHold),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 5001,
                                          .Pos = 0,
                                          .AmmoType = amFlamethrower,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 6,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = -3
                          },
                          {
                              .NameId = sidSMine,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_Power | ammoprop_AltUse) | ammoprop_NeedUpDown),
                                          .Count = 1,
                                          .NumPerTurn = 1,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amSMine,
                                          .AttackVoice = sndLaugh,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 4,
                              .TimeAfterTurn = 5000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidHammer,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ammoprop_NoCrosshair,
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amHammer,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 3,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidResurrector,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((ammoprop_NoCrosshair | ammoprop_Utility) | ammoprop_NoRoundEnd) | ammoprop_DoesntStopTimerWhileAttacking),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amResurrector,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 8,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidDrillStrike,
                              .NameTex = NULL,
                              .Probability = 200,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((((ammoprop_NoCrosshair | ammoprop_NeedTarget) | ammoprop_AttackingPut) | ammoprop_DontHold) | ammoprop_Timerable) | ammoprop_NotBorder),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 5000,
                                          .Pos = 0,
                                          .AmmoType = amDrillStrike,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 5,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 6,
                              .PosCount = 2,
                              .PosSprite = sprAmAirplane,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidSnowball,
                              .NameTex = NULL,
                              .Probability = 0,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((ammoprop_Power | ammoprop_AltUse) | ammoprop_NeedUpDown) | ammoprop_NoRoundEnd),
                                          .Count = 2,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amSnowball,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 0,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidTardis,
                              .NameTex = NULL,
                              .Probability = 200,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((((ammoprop_ForwMsgs | ammoprop_NoCrosshair) | ammoprop_Utility) | ammoprop_ShowSelIcon) | ammoprop_DontHold) | ammoprop_ForceTurnEnd),
                                          .Count = 2,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amTardis,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 8,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 2,
                              .PosSprite = sprAmTeleport,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidLandGun,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_NoRoundEnd | ammoprop_NeedUpDown) | ammoprop_Utility),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 5001,
                                          .Pos = 0,
                                          .AmmoType = amLandGun,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 6,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = -3
                          },
                          {
                              .NameId = sidIceGun,
                              .NameTex = NULL,
                              .Probability = 20,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_ForwMsgs | ammoprop_NeedUpDown) | ammoprop_DontHold),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 5001,
                                          .Pos = 0,
                                          .AmmoType = amIceGun,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 2,
                              .TimeAfterTurn = 0,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = -3
                          },
                          {
                              .NameId = sidKnife,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_Power | ammoprop_AltUse) | ammoprop_NeedUpDown),
                                          .Count = 1,
                                          .NumPerTurn = 1,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amKnife,
                                          .AttackVoice = sndWatchThis,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 0,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidRubber,
                              .NameTex = NULL,
                              .Probability = 150,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((((ammoprop_NoRoundEnd | ammoprop_NoCrosshair) | ammoprop_NeedTarget) | ammoprop_Utility) | ammoprop_AttackingPut),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amRubber,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 6,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = false,
                              .SkipTurns = 0,
                              .PosCount = 4,
                              .PosSprite = sprAmRubber,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidAirMine,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_Power | ammoprop_AltUse) | ammoprop_NeedUpDown),
                                          .Count = 2,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amAirMine,
                                          .AttackVoice = sndLaugh,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 5,
                              .TimeAfterTurn = 5000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidCreeper,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = (((ammoprop_NoCrosshair | ammoprop_AttackInMove) | ammoprop_DontHold) | ammoprop_AltUse),
                                          .Count = 2,
                                          .NumPerTurn = 0,
                                          .Timer = 15000,
                                          .Pos = 0,
                                          .AmmoType = amCreeper,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 8,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 15,
                              .ejectY = -7
                          },
                          {
                              .NameId = sidMinigun,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ammoprop_NeedUpDown,
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amMinigun,
                                          .AttackVoice = sndNone,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 2,
                              .TimeAfterTurn = 3000,
                              .minAngle = (cMaxAngle / 6),
                              .maxAngle = ((5 * cMaxAngle) / 6),
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 0,
                              .ejectY = 0
                          },
                          {
                              .NameId = sidSentry,
                              .NameTex = NULL,
                              .Probability = 100,
                              .NumberInCase = 1,
                              .Ammo = {
                                          .Propz = ((ammoprop_NoCrosshair | ammoprop_AttackInMove) | ammoprop_DontHold),
                                          .Count = 1,
                                          .NumPerTurn = 0,
                                          .Timer = 0,
                                          .Pos = 0,
                                          .AmmoType = amSentry,
                                          .AttackVoice = sndLaugh,
                                          .Bounciness = defaultBounciness
                                      },
                              .Slot = 9,
                              .TimeAfterTurn = 3000,
                              .minAngle = 0,
                              .maxAngle = 0,
                              .isDamaging = true,
                              .SkipTurns = 0,
                              .PosCount = 0,
                              .PosSprite = sprWater,
                              .ejectX = 10,
                              .ejectY = -5
                          }};
fpcrtl_dimension_t LandDirty_dimension_info ={.dim = 0, .a = {0, 0, 0, 0}};
TDirtyTag LandDirty = NULL;
fpcrtl_dimension_t Flakes_dimension_info ={.dim = 0, .a = {0, 0, 0, 0}};
TGearPackArray Flakes = NULL;
LongWord FlakesCount;
boolean hasBorder;
boolean hasGirders;
LongInt playHeight;
LongInt playWidth;
LongInt leftX;
LongInt rightX;
LongInt topY;
LongWord MaxHedgehogs;
PSDL_Surface LandBackSurface;
PGear CurAmmoGear;
PGear lastGearByUID;
PGear GearsList;
boolean AllInactive;
boolean PrvInactive;
LongWord KilledHHs;
boolean SuddenDeath;
boolean SuddenDeathActive;
boolean SuddenDeathDmg;
LongWord SpeechType;
string255 SpeechText;
boolean PlacingHogs;
boolean PlacingKings;
LongInt StepSoundTimer;
LongInt StepSoundChannel;
PTeam CurrentTeam;
PTeam PreviousTeam;
PTeam MissionTeam;
PHedgehog CurrentHedgehog;
TeamsArray_tt TeamsArray;
LongWord TeamsCount;
LongWord VisibleTeamsCount;
TClansArray ClansArray;
TClansArray SpawnClansArray;
LongWord ClansCount;
LongInt LocalTeam;
LongInt LocalAmmo;
LongWord CurMinAngle;
LongWord CurMaxAngle;
PGear FollowGear;
LongInt WindBarWidth;
boolean bShowAmmoMenu;
boolean bSelected;
boolean bShowFinger;
boolean bShowSwitcher;
LongWord Frames;
TSDL_Color WaterColor;
TSDL_Color DeepWaterColor;
TSDL_Color SDTint;
TSDL_Color SkyColor;
TSDL_Color RQSkyColor;
TSDL_Color SDSkyColor;
LongInt SkyOffset;
PTexture PauseTexture;
PTexture AFKTexture;
PTexture SyncTexture;
PTexture ConfirmTexture;
GLfloat cScaleFactor;
float cUIScaleFactor;
GLfloat cStereoDepth;
boolean SupportNPOTT;
LongInt Step;
PSDL_Surface MissionIcons;
PTexture ropeIconTex;
GLuint framel;
GLuint framer;
GLuint depthl;
GLuint depthr;
GLuint texl;
GLuint texr;
GLuint defaultFrame;
GLuint depthv;
GLuint texv;
PVisualGear lastVisualGearByUID;
LongWord vobFrameTicks;
LongWord vobFramesCount;
LongWord vobCount;
LongInt vobVelocity;
LongInt vobFallSpeed;
LongWord vobSDFrameTicks;
LongWord vobSDFramesCount;
LongWord vobSDCount;
LongInt vobSDVelocity;
LongInt vobSDFallSpeed;
LongWord watFrames;
LongWord watFrameTicks;
LongInt watMove;
LongWord watSDFrames;
LongWord watSDFrameTicks;
LongInt watSDMove;
TBinds DefaultBinds;
LongWord lastTurnChecksum;
TMatrix4x4f mModelview;
TMatrix4x4f mProjection;
GLuint vBuffer;
GLuint tBuffer;
GLuint cBuffer;
GLint uCurrentMVPLocation;
GLint uMainMVPLocation;
GLint uMainTintLocation;
GLint uWaterMVPLocation;
GLint aVertex;
GLint aTexCoord;
GLint aColor;
char lDecimalSeparator;
trammo_tt trammo;
trammoc_tt trammoc;
trammod_tt trammod;
trluaammo_tt trluaammo;
trluaammoc_tt trluaammoc;
trluaammod_tt trluaammod;
trluaammoa_tt trluaammoa;
trluaammoe_tt trluaammoe;
trmsg_tt trmsg;
trgoal_tt trgoal;
trcmd_tt trcmd;
boolean cTestLua;
static const string255 __str2 = STRINIT("./");
static const string255 __str1 = STRINIT("");
static const string255 __str0 = STRINIT("en.txt");
void uvariables_preInitModule()
{
    cFullscreenWidth = 0;
    cFullscreenHeight = 0;
    cWindowedWidth = 1024;
    cWindowedHeight = 768;
    cWindowedMaximized = false;
    cScreenWidth = cWindowedWidth;
    cScreenHeight = cWindowedHeight;
    cShowFPS = false;
    cAltDamage = false;
    cHolidaySilliness = true;
    cTimerInterval = 8;
    cReducedQuality = rqAntiBoom;
    cLanguageFName = __str0;
    cFullScreen = false;
    UserPathPrefix = fpcrtl_str2astr(__str1);
    ipcPort = 0;
    recordFileName = __str1;
    UserNick = __str1;
    cStereoMode = smNone;
    GrayScale = false;
    PathPrefix = fpcrtl_str2astr(__str2);
    GameType = gmtLocal;
    cOnlyStats = false;
    cScriptName = __str1;
    cScriptParam = __str1;
    cTestLua = false;
    UserZoom = cDefaultZoomLevel;
    zoom = cDefaultZoomLevel;
    ZoomValue = cDefaultZoomLevel;
    cMaxZoomLevel = 1.0;
    cMinZoomLevel = 3.0;
    cZoomDelta = 0.25;
    cZoomDeltaSmall = 0.125;
    cDefaultChatScale = 1.0;
    cTagsMask = (htTeamName | htName) | htHealth;
    cPrevTagsMask = cTagsMask;
};
void uvariables_initScreenSpaceVars()
{
    cLeftScreenBorder = fpcrtl_round(-cMinZoomLevel * cScreenWidth);
    cRightScreenBorder = fpcrtl_round((cMinZoomLevel * cScreenWidth) + LAND_WIDTH);
    cScreenSpace = cRightScreenBorder - cLeftScreenBorder;
};
void uvariables_initModule()
{
    string255 s;
    Integer i;
    TSound t;
    TAmmoStrId a;
    THWFont fi;
    LastVoice.snd = sndNone;
    LastVoice.voicepack = NULL;
    fpcrtl_Move(cPathzInit, cPathz, sizeof(cPathz));
    fpcrtl_Move(FontzInit, Fontz, sizeof(Fontz));
    fpcrtl_Move(SpritesDataInit, SpritesData, sizeof(SpritesData));
    fpcrtl_Move(AmmozInit, Ammoz, sizeof(Ammoz));
    {fi = 0;
     THWFont fi__end__ = 7;
     if (fi <= fi__end__) do {
                                 Fontz[fi].Height = fpcrtl_round(HDPIScaleFactor * FontzInit[fi].Height);
                             } while(fi++ != fi__end__);}
    cLanguage = cLanguageFName;
    uutils_SplitByChar(&(cLanguage), &(s), 0x2e);
    cFlattenFlakes = false;
    cFlattenClouds = false;
    cIce = false;
    cSnow = false;
    lastVisualGearByUID = NULL;
    lastGearByUID = NULL;
    cReadyDelay = 5000;
    isInChatMode = false;
    if((cReducedQuality & rqLowRes) != 0)
    {
        LAND_WIDTH = 2048;
        LAND_HEIGHT = 1024;
        LAND_WIDTH_MASK = 0xfffff800;
        LAND_HEIGHT_MASK = 0xfffffc00;
    }
    else
    {
        LAND_WIDTH = 4096;
        LAND_HEIGHT = 2048;
        LAND_WIDTH_MASK = 0xfffff000;
        LAND_HEIGHT_MASK = 0xfffff800;
    }
    WaterColorArray[0].r = 52;
    WaterColorArray[0].g = 60;
    WaterColorArray[0].b = 125;
    WaterColorArray[0].a = 255;
    WaterColorArray[2] = WaterColorArray[0];
    WaterColorArray[4] = WaterColorArray[0];
    WaterColorArray[6] = WaterColorArray[0];
    WaterColorArray[1].r = 84;
    WaterColorArray[1].g = 92;
    WaterColorArray[1].b = 157;
    WaterColorArray[1].a = 255;
    WaterColorArray[3] = WaterColorArray[1];
    WaterColorArray[5] = WaterColorArray[1];
    WaterColorArray[7] = WaterColorArray[1];
    WaterOpacity = 0x80;
    ClanColorArray[0] = 0xffff0204;
    ClanColorArray[1] = 0xff4980c1;
    ClanColorArray[2] = 0xff1de6ba;
    ClanColorArray[3] = 0xffb541ef;
    ClanColorArray[4] = 0xffe55bb0;
    ClanColorArray[5] = 0xff20bf00;
    ClanColorArray[6] = 0xfffe8b0e;
    ClanColorArray[7] = 0xff8f5902;
    ClanColorArray[8] = 0xffffff01;
    SDWaterColorArray[0].r = 150;
    SDWaterColorArray[0].g = 112;
    SDWaterColorArray[0].b = 169;
    SDWaterColorArray[0].a = 255;
    SDWaterColorArray[2] = SDWaterColorArray[0];
    SDWaterColorArray[4] = SDWaterColorArray[0];
    SDWaterColorArray[6] = SDWaterColorArray[0];
    SDWaterColorArray[1].r = 182;
    SDWaterColorArray[1].g = 144;
    SDWaterColorArray[1].b = 201;
    SDWaterColorArray[1].a = 255;
    SDWaterColorArray[3] = SDWaterColorArray[1];
    SDWaterColorArray[5] = SDWaterColorArray[1];
    SDWaterColorArray[7] = SDWaterColorArray[1];
    SDWaterOpacity = 0x80;
    SDTint.r = 0x80;
    SDTint.g = 0x80;
    SDTint.b = 0x80;
    SDTint.a = 0xff;
    ExplosionBorderColorR = 80;
    ExplosionBorderColorG = 80;
    ExplosionBorderColorB = 80;
    ExplosionBorderColor = 0xff808080;
    ExplosionBorderColorNoA = ExplosionBorderColor & ~AMask;
    IceColor = (((0x44 << RShift) | (0x97 << GShift)) | (0xa9 << BShift)) | (0xa0 << AShift);
    IceEdgeColor = (((0x8a << RShift) | (0xaf << GShift)) | (0xb2 << BShift)) | (0xff << AShift);
    WaterOpacity = 0x80;
    cWaveHeight = 32;
    cDrownSpeed.QWordValue = 257698038;
    cDrownSpeedf = 6.0e-2;
    cMaxWindSpeed.QWordValue = 1073742;
    cWindSpeed.QWordValue = 0;
    cWindSpeedf = 0.0;
    cElastic = _0_9;
    cGravity = ufloat_hwFloat_LongInt_op_mul(cMaxWindSpeed, 2);
    cGravityf = 2.5e-4 * 2;
    cLowGravity = false;
    cBuildMaxDist = cDefaultBuildMaxDist;
    cDamageModifier = _1;
    TargetPoint = cTargetPointRef;
    aVertex = 0;
    aTexCoord = 1;
    aColor = 2;
    lDecimalSeparator = 0x2e;
    cMinMaxZoomLevelDelta = cMaxZoomLevel - cMinZoomLevel;
    cDemoClockFPSOffsetY = 0;
    CursorMovementX = 0;
    CursorMovementY = 0;
    GameTicks = 0;
    FFGameTick = 0;
    OuchTauntTimer = 0;
    CheckSum = 0;
    cWaterLine = LAND_HEIGHT;
    cGearScrEdgesDist = 240;
    InputMask = 0xffffffff;
    GameFlags = 0;
    WorldEdge = weNone;
    LeftImpactTimer = 0;
    RightImpactTimer = 0;
    TurnTimeLeft = 0;
    IsGetAwayTime = false;
    GameOver = false;
    TurnClockActive = true;
    TagTurnTimeLeft = 0;
    TimeNotInTurn = 0;
    cSuddenDTurns = 15;
    LastSuddenDWarn = -2;
    cInitHealth = 100;
    cDamagePercent = 100;
    cRopePercent = 100;
    cRopeNodeStep = 4;
    cRopeLayers = 1;
    cGetAwayTime = 100;
    cMineDudPercent = 0;
    cTemplateFilter = 0;
    cFeatureSize = 12;
    cMapGen = mgRandom;
    cHedgehogTurnTime = 45000;
    cMinesTime = 3000;
    cMaxAIThinkTime = 9000;
    cCloudsNumber = 9;
    cSDCloudsNumber = 9;
    cHealthCaseProb = 35;
    cHealthCaseAmount = 25;
    cWaterRise = 47;
    cHealthDecrease = 5;
    cAdvancedMapGenMode = false;
    InitStepsFlags = 0;
    RealTicks = 0;
    AttackBar = 0;
    cCaseFactor = 5;
    cMaxCaseDrops = 5;
    cLandMines = 4;
    cAirMines = 0;
    cSentries = 0;
    cExplosives = 2;
    GameState = 0;
    if(cDefaultChatScale < cMinChatScaleValue)
    {
        cDefaultChatScale = cMinChatScaleValue;
    }
    else
    {
        if(cDefaultChatScale > cMaxChatScaleValue)
        {
            cDefaultChatScale = cMaxChatScaleValue;
        }
    }
    ChatScaleValue = cDefaultChatScale;
    UIScaleValue = cDefaultUIScaleLevel;
    WeaponTooltipTex = NULL;
    cLaserSighting = false;
    cLaserSightingSniper = false;
    cVampiric = false;
    flagMakeCapture = false;
    flagDumpLand = false;
    bBetweenTurns = false;
    bWaterRising = false;
    bDuringWaterRise = false;
    isCursorVisible = false;
    isInLag = false;
    isPaused = false;
    isInMultiShoot = false;
    isSpeed = false;
    isAFK = false;
    isShowMission = false;
    isShowGearInfo = false;
    isForceMission = false;
    SpeedStart = 0;
    fastUntilLag = false;
    fastForward = false;
    fastScrolling = false;
    autoCameraOn = true;
    cSeed = __str1;
    cIsSoundEnabled = false;
    cVolumeDelta = 0;
    cVolumeUpKey = false;
    cVolumeDownKey = false;
    cMuteToggle = false;
    cHasFocus = true;
    cInactDelay = 100;
    ReadyTimeLeft = 0;
    disableLandBack = false;
    ScreenFade = sfNone;
    InCinematicMode = false;
    CinematicSteps = 0;
    CinematicBarH = 0;
    CinematicScript = false;
    uvariables_initScreenSpaceVars();
    dirtyLandTexCount = 0;
    vobFrameTicks = 0;
    vobFramesCount = 4;
    vobCount = 0;
    vobVelocity = 10;
    vobFallSpeed = 100;
    watFrames = 1;
    watFrameTicks = 0;
    watMove = 100;
    vobSDFrameTicks = 0;
    vobSDFramesCount = 4;
    vobSDCount = (30 * cScreenSpace) / LAND_WIDTH;
    vobSDVelocity = 15;
    vobSDFallSpeed = 250;
    watSDFrames = 1;
    watSDFrameTicks = 0;
    watSDMove = 100;
    cMinScreenWidth = uutils_Min(cScreenWidth, 640);
    cMinScreenHeight = uutils_Min(cScreenHeight, 480);
    cNewScreenWidth = cScreenWidth;
    cNewScreenHeight = cScreenHeight;
    cScreenResizeDelay = 0;
    if(cFullscreenWidth == 0)
    {
        cFullscreenWidth = uutils_Min(cWindowedWidth, 640);
    }
    if(cFullscreenHeight == 0)
    {
        cFullscreenHeight = uutils_Min(cWindowedHeight, 480);
    }
    SpeechHogNumber = -1;
    LuaGoals = fpcrtl_str2astr(__str1);
    cMapName = __str1;
    syncedPixelDigest = 1;
    LuaTemplateNumber = 0;
    LuaEndTurnRequested = false;
    LuaNoEndTurnTaunts = false;
    LuaCmdUsed = false;
    {t = 0;
     TSound t__end__ = 174;
     if (t <= t__end__) do {
                               MaskedSounds[t] = false;
                           } while(t++ != t__end__);}
    {a = 0;
     TAmmoStrId a__end__ = 61;
     if (a <= a__end__) do {
                               trluaammoe[a] = true;
                           } while(a++ != a__end__);}
    UIDisplay = uiAll;
    LocalMessage = 0;
    cStereoDepth = 0;
    cViewLimitsDebug = false;
    AprilOne = false;
    CurAmmoGear = NULL;
    lastGearByUID = NULL;
    GearsList = NULL;
    CurrentTeam = NULL;
    PreviousTeam = NULL;
    MissionTeam = NULL;
    CurrentHedgehog = NULL;
    FollowGear = NULL;
    lastVisualGearByUID = NULL;
    ChefHatTexture = NULL;
    CrosshairTexture = NULL;
    GenericHealthTexture = NULL;
    WeaponTooltipTex = NULL;
    HHTexture = NULL;
    LandBackSurface = NULL;
    ConfirmTexture = NULL;
    MissionIcons = NULL;
    ropeIconTex = NULL;
    SDLwindow = NULL;
    SDLGLcontext = NULL;
    FlakesCount = 0;
    {i = 0;
     Integer i__end__ = (cMaxTeams - 1);
     if (i <= i__end__) do {
                               ClansArray[i] = NULL;
                           } while(i++ != i__end__);}
    fpcrtl_memcpy(SpawnClansArray, ClansArray, sizeof(ClansArray));
    {i = 0;
     Integer i__end__ = (cMaxTeams - 1);
     if (i <= i__end__) do {
                               TeamsArray[i] = NULL;
                           } while(i++ != i__end__);}
    {i = 0;
     Integer i__end__ = (AMMO_INFINITE - 1);
     if (i <= i__end__) do {
                               CountTexz[i] = NULL;
                           } while(i++ != i__end__);}
};
void uvariables_freeModule()
{
};
