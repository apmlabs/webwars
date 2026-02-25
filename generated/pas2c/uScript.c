#include "fpcrtl.h"

#include "uScript.h"
#include "LuaPas.h"
#include "uConsole.h"
#include "uConsts.h"
#include "uGears.h"
#include "uGearsList.h"
#include "uGearsUtils.h"
#include "uFloat.h"
#include "uWorld.h"
#include "uAmmos.h"
#include "uTeams.h"
#include "uSound.h"
#include "uChat.h"
#include "uStats.h"
#include "uStore.h"
#include "uRandom.h"
#include "uTypes.h"
#include "uVariables.h"
#include "uCommands.h"
#include "uCaptions.h"
#include "uDebug.h"
#include "uCollisions.h"
#include "uRenderUtils.h"
#include "uTextures.h"
#include "uLandGraphics.h"
#include "uUtils.h"
#include "uIO.h"
#include "uVisualGearsList.h"
#include "uGearsHandlersMess.h"
#include "uPhysFSLayer.h"
#include "uLocale.h"
#include "SDLh.h"
static const string255 __str449 = STRINIT("TEST_FAILED");
static const string255 __str448 = STRINIT("TEST_SUCCESSFUL");
static const string255 __str447 = STRINIT("EXPLForceDraw");
static const string255 __str446 = STRINIT("EXPLDoNotTouchAny");
static const string255 __str445 = STRINIT("EXPLPoisoned");
static const string255 __str444 = STRINIT("EXPLNoGfx");
static const string255 __str443 = STRINIT("EXPLDontDraw");
static const string255 __str442 = STRINIT("EXPLDoNotTouchHH");
static const string255 __str441 = STRINIT("EXPLNoDamage");
static const string255 __str440 = STRINIT("EXPLAutoSound");
static const string255 __str439 = STRINIT("lfAllObjMask");
static const string255 __str438 = STRINIT("lfNotHHObjMask");
static const string255 __str437 = STRINIT("lfHHMask");
static const string255 __str436 = STRINIT("lfCurHogCrate");
static const string255 __str435 = STRINIT("lfLandMask");
static const string255 __str434 = STRINIT("lfBouncy");
static const string255 __str433 = STRINIT("lfIce");
static const string255 __str432 = STRINIT("lfIndestructible");
static const string255 __str431 = STRINIT("aihDoesntMatter");
static const string255 __str430 = STRINIT("aihUsualProcessing");
static const string255 __str429 = STRINIT("gstNoGravity");
static const string255 __str428 = STRINIT("gstFrozen");
static const string255 __str427 = STRINIT("gstSubmersible");
static const string255 __str426 = STRINIT("gstInvisible");
static const string255 __str425 = STRINIT("gstHHGone");
static const string255 __str424 = STRINIT("gstLoser");
static const string255 __str423 = STRINIT("gstNotKickable");
static const string255 __str422 = STRINIT("gstWait");
static const string255 __str421 = STRINIT("gstWinner");
static const string255 __str420 = STRINIT("gstHHDeath");
static const string255 __str419 = STRINIT("gstAnimation");
static const string255 __str418 = STRINIT("gstHHHJump");
static const string255 __str417 = STRINIT("gstNoDamage");
static const string255 __str416 = STRINIT("gstHHThinking");
static const string255 __str415 = STRINIT("gsttmpFlag");
static const string255 __str414 = STRINIT("gstHHJumping");
static const string255 __str413 = STRINIT("gstChooseTarget");
static const string255 __str412 = STRINIT("gstCollision");
static const string255 __str411 = STRINIT("gstAttacking");
static const string255 __str410 = STRINIT("gstAttacked");
static const string255 __str409 = STRINIT("gstMoving");
static const string255 __str408 = STRINIT("gstHHDriven");
static const string255 __str407 = STRINIT("gstDrowning");
static const string255 __str406 = STRINIT("capcolSetting");
static const string255 __str405 = STRINIT("capcolDefault");
static const string255 __str404 = STRINIT("MAX_TURN_TIME");
static const string255 __str403 = STRINIT("MAX_HOG_HEALTH");
static const string255 __str402 = STRINIT("NO_CURSOR");
static const string255 __str401 = STRINIT("BIRDY_ENERGY_INFINITE");
static const string255 __str400 = STRINIT("JETPACK_FUEL_INFINITE");
static const string255 __str399 = STRINIT("AMMO_INFINITE");
static const string255 __str398 = STRINIT("SAY_SHOUT");
static const string255 __str397 = STRINIT("SAY_THINK");
static const string255 __str396 = STRINIT("SAY_SAY");
static const string255 __str395 = STRINIT("gmAllStoppable");
static const string255 __str394 = STRINIT("gmPrecise");
static const string255 __str393 = STRINIT("gmAnimate");
static const string255 __str392 = STRINIT("gmTimer");
static const string255 __str391 = STRINIT("gmWeapon");
static const string255 __str390 = STRINIT("gmSlot");
static const string255 __str389 = STRINIT("gmDestroy");
static const string255 __str388 = STRINIT("gmHJump");
static const string255 __str387 = STRINIT("gmLJump");
static const string255 __str386 = STRINIT("gmAttack");
static const string255 __str385 = STRINIT("gmSwitch");
static const string255 __str384 = STRINIT("gmDown");
static const string255 __str383 = STRINIT("gmUp");
static const string255 __str382 = STRINIT("gmRight");
static const string255 __str381 = STRINIT("gmLeft");
static const string255 __str380 = STRINIT("gfShoppaBorder");
static const string255 __str379 = STRINIT("gfTagTeam");
static const string255 __str378 = STRINIT("gfMoreWind");
static const string255 __str377 = STRINIT("gfDisableWind");
static const string255 __str376 = STRINIT("gfPerHogAmmo");
static const string255 __str375 = STRINIT("gfResetWeps");
static const string255 __str374 = STRINIT("gfInfAttack");
static const string255 __str373 = STRINIT("gfAISurvival");
static const string255 __str372 = STRINIT("gfDisableLandObjects");
static const string255 __str371 = STRINIT("gfDisableGirders");
static const string255 __str370 = STRINIT("gfSharedAmmo");
static const string255 __str369 = STRINIT("gfPlaceHog");
static const string255 __str368 = STRINIT("gfKing");
static const string255 __str367 = STRINIT("gfRandomOrder");
static const string255 __str366 = STRINIT("gfOneClanMode");
static const string255 __str365 = STRINIT("gfArtillery");
static const string255 __str364 = STRINIT("gfKarma");
static const string255 __str363 = STRINIT("gfVampiric");
static const string255 __str362 = STRINIT("gfResetHealth");
static const string255 __str361 = STRINIT("gfInvulnerable");
static const string255 __str360 = STRINIT("gfLaserSight");
static const string255 __str359 = STRINIT("gfLowGravity");
static const string255 __str358 = STRINIT("gfDivideTeams");
static const string255 __str357 = STRINIT("gfBottomBorder");
static const string255 __str356 = STRINIT("gfBorder");
static const string255 __str355 = STRINIT("gfSolidLand");
static const string255 __str354 = STRINIT("gfMultiWeapon");
static const string255 __str353 = STRINIT("gfSwitchHog");
static const string255 __str352 = STRINIT("gtDuck");
static const string255 __str351 = STRINIT("amDuck");
static const string255 __str350 = STRINIT("desktop");
static const string255 __str349 = STRINIT("INTERFACE");
static const string255 __str348 = STRINIT("LOCALE");
static const string255 __str347 = STRINIT("lua_open failed");
static const string255 __str346 = STRINIT("Error while calling ");
static const string255 __str345 = STRINIT("Writing to ReadyTimeLeft directly is deprecated! Use SetReadyTimeLeft instead!");
static const string255 __str344 = STRINIT("Writing to TurnTimeLeft directly is deprecated! Use SetTurnTimeLeft instead!");
static const string255 __str343 = STRINIT("TopY");
static const string255 __str342 = STRINIT("RightX");
static const string255 __str341 = STRINIT("LeftX");
static const string255 __str340 = STRINIT("LAND_HEIGHT");
static const string255 __str339 = STRINIT("LAND_WIDTH");
static const string255 __str338 = STRINIT("CurrentHedgehog");
static const string255 __str337 = STRINIT("WaterLine");
static const string255 __str336 = STRINIT("TotalRounds");
static const string255 __str335 = STRINIT("GameTime");
static const string255 __str334 = STRINIT("ReadyTimeLeft");
static const string255 __str333 = STRINIT("TurnTimeLeft");
static const string255 __str332 = STRINIT(" loaded");
static const string255 __str331 = STRINIT("(error ");
static const string255 __str330 = STRINIT("Failed to load ");
static const string255 __str329 = STRINIT("Scripts/OfficialChallengeHashes.lua");
static const string255 __str328 = STRINIT("Locale/");
static const string255 __str327 = STRINIT(".hwp");
static const string255 __str326 = STRINIT("Error reading script: ");
static const string255 __str325 = STRINIT("[LUA] Script not found: ");
static const string255 __str324 = STRINIT("Script not found: ");
static const string255 __str323 = STRINIT("onScreenResize");
static const string255 __str322 = STRINIT("TeamsCount");
static const string255 __str321 = STRINIT("ClansCount");
static const string255 __str320 = STRINIT("onNewAmmoStore");
static const string255 __str319 = STRINIT("onAmmoStoreInit");
static const string255 __str318 = STRINIT("theme ");
static const string255 __str317 = STRINIT("map ");
static const string255 __str316 = STRINIT("onGameInit");
static const string255 __str315 = STRINIT("Goals");
static const string255 __str314 = STRINIT("Theme");
static const string255 __str313 = STRINIT("Map");
static const string255 __str312 = STRINIT("AmmoTypeMax");
static const string255 __str311 = STRINIT("GetAwayTime");
static const string255 __str310 = STRINIT("HealthDecrease");
static const string255 __str309 = STRINIT("WaterRise");
static const string255 __str308 = STRINIT("SuddenDeathTurns");
static const string255 __str307 = STRINIT("Ready");
static const string255 __str306 = STRINIT("Delay");
static const string255 __str305 = STRINIT("Explosives");
static const string255 __str304 = STRINIT("AirMinesNum");
static const string255 __str303 = STRINIT("MineDudPercent");
static const string255 __str302 = STRINIT("MinesTime");
static const string255 __str301 = STRINIT("MinesNum");
static const string255 __str300 = STRINIT("RopePercent");
static const string255 __str299 = STRINIT("DamagePercent");
static const string255 __str298 = STRINIT("InitHealth");
static const string255 __str297 = STRINIT("HealthCaseAmount");
static const string255 __str296 = STRINIT("HealthCaseProb");
static const string255 __str295 = STRINIT("MaxCaseDrops");
static const string255 __str294 = STRINIT("CaseFreq");
static const string255 __str293 = STRINIT("TurnTime");
static const string255 __str292 = STRINIT("ScreenWidth");
static const string255 __str291 = STRINIT("ScreenHeight");
static const string255 __str290 = STRINIT("WorldEdge");
static const string255 __str289 = STRINIT("CursorY");
static const string255 __str288 = STRINIT("CursorX");
static const string255 __str287 = STRINIT("seed ");
static const string255 __str286 = STRINIT("onPreviewInit");
static const string255 __str285 = STRINIT("MapFeatureSize");
static const string255 __str284 = STRINIT("MapGen");
static const string255 __str283 = STRINIT("TemplateNumber");
static const string255 __str282 = STRINIT("TemplateFilter");
static const string255 __str281 = STRINIT("Seed");
static const string255 __str280 = STRINIT(": false");
static const string255 __str279 = STRINIT(": true");
static const string255 __str278 = STRINIT("Lua:  ");
static const string255 __str277 = STRINIT(" elements):");
static const string255 __str276 = STRINIT("Lua: Stack (");
static const string255 __str275 = STRINIT("Not in lua test mode, engine will keep running. Reported test result: ");
static const string255 __str274 = STRINIT("Lua test finished, result: ");
static const string255 __str273 = STRINIT("Parameter must be either ");
static const string255 __str272 = STRINIT("FAILED");
static const string255 __str271 = STRINIT("Success");
static const string255 __str270 = STRINIT("FlushPoints");
static const string255 __str269 = STRINIT("x, y [, width [, erase] ]");
static const string255 __str268 = STRINIT("AddPoint");
static const string255 __str267 = STRINIT("draw ");
static const string255 __str266 = STRINIT("x, y");
static const string255 __str265 = STRINIT("DumpPoint");
static const string255 __str264 = STRINIT("count");
static const string255 __str263 = STRINIT("StartGhostPoints");
static const string255 __str262 = STRINIT("GetTurnTimePaused");
static const string255 __str261 = STRINIT("isPaused");
static const string255 __str260 = STRINIT("SetTurnTimePaused");
static const string255 __str259 = STRINIT("newReadyTimeLeft");
static const string255 __str258 = STRINIT("SetReadyTimeLeft");
static const string255 __str257 = STRINIT("newTurnTimeLeft");
static const string255 __str256 = STRINIT("SetTurnTimeLeft");
static const string255 __str255 = STRINIT("x, y, radius[, options]");
static const string255 __str254 = STRINIT("Explode");
static const string255 __str253 = STRINIT("SetLaserSight");
static const string255 __str252 = STRINIT("bool");
static const string255 __str251 = STRINIT("SetVampiric");
static const string255 __str250 = STRINIT("achievementId, teamname, location, value");
static const string255 __str249 = STRINIT("DeclareAchievement");
static const string255 __str248 = STRINIT("scriptPath [, mustExist]");
static const string255 __str247 = STRINIT("HedgewarsScriptLoad");
static const string255 __str246 = STRINIT("gearUid, aiHints");
static const string255 __str245 = STRINIT("SetGearAIHints");
static const string255 __str244 = STRINIT("waterline");
static const string255 __str243 = STRINIT("SetWaterLine");
static const string255 __str242 = STRINIT("percent");
static const string255 __str241 = STRINIT("SetGravity");
static const string255 __str240 = STRINIT("GetGravity");
static const string255 __str239 = STRINIT("x1, y1, x2, y2, landOnly");
static const string255 __str238 = STRINIT("TestRectForObstacle");
static const string255 __str237 = STRINIT("IsHogHidden");
static const string255 __str236 = STRINIT("RestoreHog");
static const string255 __str235 = STRINIT("HideHog");
static const string255 __str234 = STRINIT("v?");
static const string255 __str233 = STRINIT("GetMissionVar");
static const string255 __str232 = STRINIT("v!");
static const string255 __str231 = STRINIT("SaveMissionVar");
static const string255 __str230 = STRINIT("V?");
static const string255 __str229 = STRINIT("varname");
static const string255 __str228 = STRINIT("GetCampaignVar");
static const string255 __str227 = STRINIT("V!");
static const string255 __str226 = STRINIT("varname, value");
static const string255 __str225 = STRINIT("SaveCampaignVar");
static const string255 __str224 = STRINIT("GetCurAmmoType");
static const string255 __str223 = STRINIT("PlaceRubber");
static const string255 __str222 = STRINIT("x, y, frameIdx");
static const string255 __str221 = STRINIT("PlaceGirder");
static const string255 __str220 = STRINIT(" cannot be placed! (required information not loaded)");
static const string255 __str219 = STRINIT("Reserved/");
static const string255 __str218 = STRINIT("Reserved");
static const string255 __str217 = STRINIT("Changed hat to: ");
static const string255 __str216 = STRINIT("gearUid, hat");
static const string255 __str215 = STRINIT("SetHogHat");
static const string255 __str214 = STRINIT("GetHogHat");
static const string255 __str213 = STRINIT("GetGearRadius");
static const string255 __str212 = STRINIT("MapHasBorder");
static const string255 __str211 = STRINIT("GetWind");
static const string255 __str210 = STRINIT("Script set wind = ");
static const string255 __str209 = STRINIT("windSpeed");
static const string255 __str208 = STRINIT("SetWind");
static const string255 __str207 = STRINIT("Lua: Tried to pass 0 to GetRandom!");
static const string255 __str206 = STRINIT("number");
static const string255 __str205 = STRINIT("GetRandom");
static const string255 __str204 = STRINIT("ammoType, slot");
static const string255 __str203 = STRINIT("SetAmmoSlot");
static const string255 __str202 = STRINIT("GetZoom");
static const string255 __str201 = STRINIT("zoomLevel");
static const string255 __str200 = STRINIT("SetZoom");
static const string255 __str199 = STRINIT("gearUid, dx, dy");
static const string255 __str198 = STRINIT("SetGearVelocity");
static const string255 __str197 = STRINIT("GetGearVelocity");
static const string255 __str196 = STRINIT("SetGearTarget");
static const string255 __str195 = STRINIT("GetGearTarget");
static const string255 __str194 = STRINIT("gearUid, x, y");
static const string255 __str193 = STRINIT("SetGearPosition");
static const string255 __str192 = STRINIT("GetGearPosition");
static const string255 __str191 = STRINIT("gearUid, boolean");
static const string255 __str190 = STRINIT("HogTurnLeft");
static const string255 __str189 = STRINIT("Lua error: AddMissionHog: Error adding hog. Maybe function was called outside of onGameInit.");
static const string255 __str188 = STRINIT("Lua error: AddMissionHog: Could not add hog. Mission team is not set!");
static const string255 __str187 = STRINIT("health");
static const string255 __str186 = STRINIT("AddMissionHog");
static const string255 __str185 = STRINIT("Lua error: AddHog: Error adding hog. Maybe function was called outside of onGameInit.");
static const string255 __str184 = STRINIT("hat ");
static const string255 __str183 = STRINIT("addhh ");
static const string255 __str182 = STRINIT("hogname, botlevel, health, hat");
static const string255 __str181 = STRINIT("AddHog");
static const string255 __str180 = STRINIT("TeamDamage");
static const string255 __str179 = STRINIT("TurnSkips");
static const string255 __str178 = STRINIT("TeamKills");
static const string255 __str177 = STRINIT("AIKills");
static const string255 __str176 = STRINIT("Suicides");
static const string255 __str175 = STRINIT("Kills");
static const string255 __str174 = STRINIT("GetTeamStats");
static const string255 __str173 = STRINIT("DismissTeam");
static const string255 __str172 = STRINIT("GetTeamClan");
static const string255 __str171 = STRINIT("teamname");
static const string255 __str170 = STRINIT("GetTeamIndex");
static const string255 __str169 = STRINIT("teamIdx");
static const string255 __str168 = STRINIT("GetTeamName");
static const string255 __str167 = STRINIT("teamname, isPassive");
static const string255 __str166 = STRINIT("SetTeamPassive");
static const string255 __str165 = STRINIT("teamname[, label]");
static const string255 __str164 = STRINIT("SetTeamLabel");
static const string255 __str163 = STRINIT("Lua error: AddMissionTeam: Invalid 'color' argument, must be between ");
static const string255 __str162 = STRINIT("Lua error: AddMissionTeam: Could not add team. Note: This function only works in singleplayer missions!");
static const string255 __str161 = STRINIT("color");
static const string255 __str160 = STRINIT("AddMissionTeam");
static const string255 __str159 = STRINIT("flag ");
static const string255 __str158 = STRINIT("voicepack ");
static const string255 __str157 = STRINIT("fort ");
static const string255 __str156 = STRINIT("grave ");
static const string255 __str155 = STRINIT("addteam x ");
static const string255 __str154 = STRINIT("Lua error: AddTeam: Invalid 'color' argument, must be between ");
static const string255 __str153 = STRINIT("teamname, color, grave, fort, voicepack [, flag]");
static const string255 __str152 = STRINIT("AddTeam");
static const string255 __str151 = STRINIT("gearUid, fall, left, right [, tryHarder]");
static const string255 __str150 = STRINIT("FindPlace");
static const string255 __str149 = STRINIT("0");
static const string255 __str148 = STRINIT(" requires the teamname parameter");
static const string255 __str147 = STRINIT(" does not support the teamname parameter");
static const string255 __str146 = STRINIT("skip");
static const string255 __str145 = STRINIT("gearUid, tag");
static const string255 __str144 = STRINIT("SetTag");
static const string255 __str143 = STRINIT("GetTag");
static const string255 __str142 = STRINIT("GetState");
static const string255 __str141 = STRINIT("gearUid, state");
static const string255 __str140 = STRINIT("SetState");
static const string255 __str139 = STRINIT("gearUid, flighttime");
static const string255 __str138 = STRINIT("SetFlightTime");
static const string255 __str137 = STRINIT("gearUid, timer");
static const string255 __str136 = STRINIT("SetTimer");
static const string255 __str135 = STRINIT("gearUid, healthBoost [, showMessage [, tint]]");
static const string255 __str134 = STRINIT("HealHog");
static const string255 __str133 = STRINIT("gearUid, health");
static const string255 __str132 = STRINIT("SetHealth");
static const string255 __str131 = STRINIT("EnableSwitchHog");
static const string255 __str130 = STRINIT("SwitchHog");
static const string255 __str129 = STRINIT("gearUid, text, manner [, vgState]");
static const string255 __str128 = STRINIT("HogSay");
static const string255 __str127 = STRINIT("FollowGear");
static const string255 __str126 = STRINIT("fromGearUid, toGearUid");
static const string255 __str125 = STRINIT("CopyPV");
static const string255 __str124 = STRINIT("GetY");
static const string255 __str123 = STRINIT("GetX");
static const string255 __str122 = STRINIT("GetHealth");
static const string255 __str121 = STRINIT("GetFlightTime");
static const string255 __str120 = STRINIT("GetTimer");
static const string255 __str119 = STRINIT("SetHogName");
static const string255 __str118 = STRINIT("GetHogName");
static const string255 __str117 = STRINIT("gearUid, name");
static const string255 __str116 = STRINIT("SetHogTeamName");
static const string255 __str115 = STRINIT("GetHogTeamName");
static const string255 __str114 = STRINIT("IsHogLocal");
static const string255 __str113 = STRINIT("IsHogAlive");
static const string255 __str112 = STRINIT("GetHogFort");
static const string255 __str111 = STRINIT("GetHogFlag");
static const string255 __str110 = STRINIT("GetHogGrave");
static const string255 __str109 = STRINIT("GetHogVoicepack");
static const string255 __str108 = STRINIT(" and 0xffffffff!");
static const string255 __str107 = STRINIT("Lua error: SetClanColor: Invalid 'color' argument, must be between ");
static const string255 __str106 = STRINIT("clan, color");
static const string255 __str105 = STRINIT("SetClanColor");
static const string255 __str104 = STRINIT(" clans, so valid range is: 0-");
static const string255 __str103 = STRINIT("Argument 'clanIdx' out of range! (There are currently ");
static const string255 __str102 = STRINIT("Argument 'clanIdx' must be a number!");
static const string255 __str101 = STRINIT("clanIdx");
static const string255 __str100 = STRINIT("GetClanColor");
static const string255 __str99 = STRINIT("GetHogClan");
static const string255 __str98 = STRINIT("gearUid, level");
static const string255 __str97 = STRINIT("SetHogLevel");
static const string255 __str96 = STRINIT("GetHogLevel");
static const string255 __str95 = STRINIT("gearUid, mask");
static const string255 __str94 = STRINIT("SetGearCollisionMask");
static const string255 __str93 = STRINIT("GetGearCollisionMask");
static const string255 __str92 = STRINIT("gearUid, value");
static const string255 __str91 = STRINIT("SetGearPos");
static const string255 __str90 = STRINIT("GetGearPos");
static const string255 __str89 = STRINIT("gearUid, message");
static const string255 __str88 = STRINIT("SetGearMessage");
static const string255 __str87 = STRINIT("gearUid, Friction");
static const string255 __str86 = STRINIT("SetGearFriction");
static const string255 __str85 = STRINIT("GetGearFriction");
static const string255 __str84 = STRINIT("gearUid, Elasticity");
static const string255 __str83 = STRINIT("SetGearElasticity");
static const string255 __str82 = STRINIT("GetGearElasticity");
static const string255 __str81 = STRINIT("GetGearMessage");
static const string255 __str80 = STRINIT("GetGearType");
static const string255 __str79 = STRINIT("GetFollowGear");
static const string255 __str78 = STRINIT("GetGearValues");
static const string255 __str77 = STRINIT("GetVisualGearValues");
static const string255 __str76 = STRINIT("GetVisualGearType");
static const string255 __str75 = STRINIT("vgUid");
static const string255 __str74 = STRINIT("DeleteVisualGear");
static const string255 __str73 = STRINIT("gearUid");
static const string255 __str72 = STRINIT("DeleteGear");
static const string255 __str71 = STRINIT("SpawnSupplyCrate");
static const string255 __str70 = STRINIT("SpawnUtilityCrate");
static const string255 __str69 = STRINIT("x, y, content [, amount]");
static const string255 __str68 = STRINIT("SpawnAmmoCrate");
static const string255 __str67 = STRINIT("x, y [, health]");
static const string255 __str66 = STRINIT("SpawnHealthCrate");
static const string255 __str65 = STRINIT("SpawnFakeUtilityCrate");
static const string255 __str64 = STRINIT("SpawnFakeAmmoCrate");
static const string255 __str63 = STRINIT("x, y [, explode [, poison]]");
static const string255 __str62 = STRINIT("SpawnFakeHealthCrate");
static const string255 __str61 = STRINIT("gameflag");
static const string255 __str60 = STRINIT("GetGameFlag");
static const string255 __str59 = STRINIT("ClearGameFlags");
static const string255 __str58 = STRINIT("DisableGameFlags");
static const string255 __str57 = STRINIT("GameFlags");
static const string255 __str56 = STRINIT("gameFlag, ... ");
static const string255 __str55 = STRINIT("EnableGameFlags");
static const string255 __str54 = STRINIT("Invalid stringType!");
static const string255 __str53 = STRINIT("TGoalStrId");
static const string255 __str52 = STRINIT("TMsgStrId");
static const string255 __str51 = STRINIT("Argument 'msgId' must be a number!");
static const string255 __str50 = STRINIT("caption, subcaption, text, icon, time [, forceDisplay]");
static const string255 __str49 = STRINIT("ShowMission");
static const string255 __str48 = STRINIT("setweap ");
static const string255 __str47 = STRINIT("ParseCommand");
static const string255 __str46 = STRINIT("WriteLnToChat");
static const string255 __str45 = STRINIT("Lua: ");
static const string255 __str44 = STRINIT("string");
static const string255 __str43 = STRINIT("WriteLnToConsole");
static const string255 __str42 = STRINIT("mask");
static const string255 __str41 = STRINIT("SetInputMask");
static const string255 __str40 = STRINIT("");
static const string255 __str39 = STRINIT("GetInputMask");
static const string255 __str38 = STRINIT("dividend, divisor");
static const string255 __str37 = STRINIT("div");
static const string255 __str36 = STRINIT("value");
static const string255 __str35 = STRINIT("bnot");
static const string255 __str34 = STRINIT("bor");
static const string255 __str33 = STRINIT("value1, value2");
static const string255 __str32 = STRINIT("band");
static const string255 __str31 = STRINIT("Invalid mapgen id!");
static const string255 __str30 = STRINIT("Invalid sprite id!");
static const string255 __str29 = STRINIT("Invalid capgroup type!");
static const string255 __str28 = STRINIT("Invalid effect type!");
static const string255 __str27 = STRINIT("Invalid goal string ID!");
static const string255 __str26 = STRINIT("Invalid message ID!");
static const string255 __str25 = STRINIT("Invalid soundId!");
static const string255 __str24 = STRINIT("Invalid statInfoType!");
static const string255 __str23 = STRINIT("Invalid ammoType!");
static const string255 __str22 = STRINIT("Invalid visualGearType!");
static const string255 __str21 = STRINIT("Invalid gearType!");
static const string255 __str20 = STRINIT(" or more");
static const string255 __str19 = STRINIT(", but at most ");
static const string255 __str18 = STRINIT("at least ");
static const string255 __str17 = STRINIT(" or ");
static const string255 __str16 = STRINIT("either ");
static const string255 __str15 = STRINIT("exactly ");
static const string255 __str14 = STRINIT(", should be: ");
static const string255 __str13 = STRINIT("Wrong number of parameters! (is: ");
static const string255 __str12 = STRINIT(" )");
static const string255 __str11 = STRINIT(" ( ");
static const string255 __str10 = STRINIT("-- SYNTAX: ");
static const string255 __str9 = STRINIT(": ");
static const string255 __str8 = STRINIT("]: ");
static const string255 __str7 = STRINIT(": [ ... ");
static const string255 __str6 = STRINIT("LUA ERROR");
static const string255 __str5 = STRINIT("LUA WARNING");
static const string255 __str4 = STRINIT("Sl");
static const string255 __str3 = STRINIT("[Lua] Error while parsing!");
static const string255 __str2 = STRINIT("[Lua] input string parsing error!");
static const string255 __str1 = STRINIT("[Lua] > ");
static const string255 __str0 = STRINIT("[Lua] input string: ");
static Plua_State luaState;
static string255 ScriptAmmoLoadout;
static string255 ScriptAmmoProbability;
static string255 ScriptAmmoDelay;
static string255 ScriptAmmoReinforcement;
static boolean ScriptLoaded;
static string255 PointsBuffer;
static LongInt PrevCursorX;
static LongInt PrevCursorY;
static LongWord PendingTurnTimeLeft;
static LongWord PendingReadyTimeLeft;
static boolean isPendingTurnTimeLeft;
static boolean isPendingReadyTimeLeft;
void uscript_ScriptPrepareAmmoStore_0();
void uscript_ScriptApplyAmmoStore_0();
void uscript_ScriptSetAmmo_5(TAmmoType ammo,Byte count,Byte probability,Byte delay,Byte reinforcement);
void uscript_ScriptSetAmmoDelay_2(TAmmoType ammo,LongWord delay);
static lua_Debug LuaDebugInfo;
void uscript_SetGlobals_0();
void uscript_GetGlobals_0();
void uscript_LuaParseString(shortstring s)
{
    uscript_SetGlobals_0();
    uutils_AddFileLog(_strconcat(__str0, s));
    uchat_AddChatString(_strconcat(_strprepend(0x3, __str1), s));
    if(luapas_luaL_dostring(luaState, uutils_Str2PChar(s)) != 0)
    {
        uutils_AddFileLog(__str2);
        uchat_AddChatString(_strprepend(0x5, __str3));
    }
    else
    {
        uscript_GetGlobals_0();
    }
};
boolean uscript_LuaUpdateDebugInfo()
{
    boolean luaupdatedebuginfo_result;
    fpcrtl_FillChar(LuaDebugInfo, sizeof(LuaDebugInfo), 0);
    if(lua_getstack(luaState, 1, &(LuaDebugInfo)) == 0)
    {
        return false;
    }
    lua_getinfo(luaState, fpcrtl__pchar(__str4), &(LuaDebugInfo));
    return true;
    return luaupdatedebuginfo_result;
};
void uscript_LuaErrorOrWarning(string255 s,boolean isWarning)
{
    string255 src;
    string255 intro;
    enum{maxsrclen = 20};
    if(isWarning)
    {
        intro = __str5;
    }
    else
    {
        intro = __str6;
    }
    if(uscript_LuaUpdateDebugInfo())
    {
        src = fpcrtl_StrPas(LuaDebugInfo.source);
        s = _strconcat(_strconcat(_strconcat(_strappend(_strconcat(_strconcat(intro, __str7), fpcrtl_copy(src, fpcrtl_Length(src) - maxsrclen, maxsrclen - 3)), 0x3a), uutils_IntToStr(LuaDebugInfo.currentline)), __str8), s);
    }
    else
    {
        s = _strconcat(_strconcat(intro, __str9), s);
    }
    uconsole_WriteLnToConsole(s);
    if(isWarning)
    {
        uchat_AddChatString(_strprepend(0x0, s));
    }
    else
    {
        uchat_AddChatString(_strprepend(0x5, s));
    }
    if(cTestLua && !isWarning)
    {
        fpcrtl_halt(HaltTestLuaError);
    }
};
void uscript_LuaError(string255 s)
{
    uscript_LuaErrorOrWarning(s, false);
};
void uscript_LuaWarning(string255 s)
{
    uscript_LuaErrorOrWarning(s, true);
};
void uscript_LuaCallError(string255 error,string255 call,string255 paramsyntax)
{
    uscript_LuaError(_strconcat(_strconcat(call, __str9), error));
    uscript_LuaError(_strconcat(_strconcat(_strconcat(_strconcat(__str10, call), __str11), paramsyntax), __str12));
};
void uscript_LuaParameterCountError(string255 expected,string255 call,string255 paramsyntax,LongInt wrongcount)
{
    uscript_LuaCallError(_strappend(_strconcat(_strconcat(_strconcat(__str13, uutils_IntToStr(wrongcount)), __str14), expected), 0x29), call, paramsyntax);
};
boolean uscript_CheckLuaParamCount(Plua_State L,LongInt count,string255 call,string255 paramsyntax)
{
    boolean checkluaparamcount_result;
    LongInt c;
    c = lua_gettop(L);
    if(c != count)
    {
        uscript_LuaParameterCountError(_strconcat(__str15, uutils_IntToStr(count)), call, paramsyntax, c);
        return false;
    }
    checkluaparamcount_result = true;
    return checkluaparamcount_result;
};
boolean uscript_CheckAndFetchParamCount(Plua_State L,LongInt count1,LongInt count2,string255 call,string255 paramsyntax,LongInt (*actual))
{
    boolean checkandfetchparamcount_result;
    (*actual) = lua_gettop(L);
    if(((*actual) != count1) && ((*actual) != count2))
    {
        uscript_LuaParameterCountError(_strconcat(_strconcat(_strconcat(__str16, uutils_IntToStr(count1)), __str17), uutils_IntToStr(count2)), call, paramsyntax, (*actual));
        return false;
    }
    checkandfetchparamcount_result = true;
    return checkandfetchparamcount_result;
};
boolean uscript_CheckAndFetchParamCountRange(Plua_State L,LongInt count1,LongInt count2,string255 call,string255 paramsyntax,LongInt (*actual))
{
    boolean checkandfetchparamcountrange_result;
    (*actual) = lua_gettop(L);
    if(((*actual) < count1) || ((*actual) > count2))
    {
        uscript_LuaParameterCountError(_strconcat(_strconcat(_strconcat(__str18, uutils_IntToStr(count1)), __str19), uutils_IntToStr(count2)), call, paramsyntax, (*actual));
        return false;
    }
    checkandfetchparamcountrange_result = true;
    return checkandfetchparamcountrange_result;
};
boolean uscript_CheckAndFetchLuaParamMinCount(Plua_State L,LongInt minCount,string255 call,string255 paramsyntax,LongInt (*actual))
{
    boolean checkandfetchluaparammincount_result;
    (*actual) = lua_gettop(L);
    if((*actual) < minCount)
    {
        uscript_LuaParameterCountError(_strconcat(uutils_IntToStr(minCount), __str20), call, paramsyntax, (*actual));
        return false;
    }
    checkandfetchluaparammincount_result = true;
    return checkandfetchluaparammincount_result;
};
LongInt uscript_LuaToGearTypeOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatogeartypeord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (69)))
    {
        uscript_LuaCallError(__str21, call, paramsyntax);
        luatogeartypeord_result = -1;
    }
    else
    {
        luatogeartypeord_result = i;
    }
    return luatogeartypeord_result;
};
LongInt uscript_LuaToVisualGearTypeOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatovisualgeartypeord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (33)))
    {
        uscript_LuaCallError(__str22, call, paramsyntax);
        luatovisualgeartypeord_result = -1;
    }
    else
    {
        luatovisualgeartypeord_result = i;
    }
    return luatovisualgeartypeord_result;
};
LongInt uscript_LuaToAmmoTypeOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatoammotypeord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (60)))
    {
        uscript_LuaCallError(__str23, call, paramsyntax);
        luatoammotypeord_result = -1;
    }
    else
    {
        luatoammotypeord_result = i;
    }
    return luatoammotypeord_result;
};
LongInt uscript_LuaToStatInfoTypeOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatostatinfotypeord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (14)))
    {
        uscript_LuaCallError(__str24, call, paramsyntax);
        luatostatinfotypeord_result = -1;
    }
    else
    {
        luatostatinfotypeord_result = i;
    }
    return luatostatinfotypeord_result;
};
LongInt uscript_LuaToSoundOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatosoundord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (174)))
    {
        uscript_LuaCallError(__str25, call, paramsyntax);
        luatosoundord_result = -1;
    }
    else
    {
        luatosoundord_result = i;
    }
    return luatosoundord_result;
};
static inline LongInt uscript_LuaToMsgStrIdOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatomsgstridord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (49)))
    {
        uscript_LuaCallError(__str26, call, paramsyntax);
        luatomsgstridord_result = -1;
    }
    else
    {
        luatomsgstridord_result = i;
    }
    return luatomsgstridord_result;
};
static inline LongInt uscript_LuaToGoalStrIdOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatogoalstridord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (22)))
    {
        uscript_LuaCallError(__str27, call, paramsyntax);
        luatogoalstridord_result = -1;
    }
    else
    {
        luatogoalstridord_result = i;
    }
    return luatogoalstridord_result;
};
LongInt uscript_LuaToHogEffectOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatohogeffectord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (5)))
    {
        uscript_LuaCallError(__str28, call, paramsyntax);
        luatohogeffectord_result = -1;
    }
    else
    {
        luatohogeffectord_result = i;
    }
    return luatohogeffectord_result;
};
LongInt uscript_LuaToCapGroupOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatocapgroupord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (5)))
    {
        uscript_LuaCallError(__str29, call, paramsyntax);
        luatocapgroupord_result = -1;
    }
    else
    {
        luatocapgroupord_result = i;
    }
    return luatocapgroupord_result;
};
LongInt uscript_LuaToSpriteOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatospriteord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (219)))
    {
        uscript_LuaCallError(__str30, call, paramsyntax);
        luatospriteord_result = -1;
    }
    else
    {
        luatospriteord_result = i;
    }
    return luatospriteord_result;
};
LongInt uscript_LuaToMapGenOrd(Plua_State L,LongInt i,string255 call,string255 paramsyntax)
{
    LongInt luatomapgenord_result;
    if(luapas_lua_isnoneornil(L, i))
    {
        i = -1;
    }
    else
    {
        i = fpcrtl_trunc(lua_tonumber(L, i));
    }
    if((i < (0)) || (i > (5)))
    {
        uscript_LuaCallError(__str31, call, paramsyntax);
        luatomapgenord_result = -1;
    }
    else
    {
        luatomapgenord_result = i;
    }
    return luatomapgenord_result;
};
LongInt uscript_lc_band(Plua_State L)
{
    LongInt lc_band_result;
    if(uscript_CheckLuaParamCount(L, 2, __str32, __str33))
    {
        lua_pushnumber(L, fpcrtl_trunc(lua_tonumber(L, 2)) & fpcrtl_trunc(lua_tonumber(L, 1)));
    }
    else
    {
        lua_pushnil(L);
    }
    lc_band_result = 1;
    return lc_band_result;
};
LongInt uscript_lc_bor(Plua_State L)
{
    LongInt lc_bor_result;
    if(uscript_CheckLuaParamCount(L, 2, __str34, __str33))
    {
        lua_pushnumber(L, fpcrtl_trunc(lua_tonumber(L, 2)) | fpcrtl_trunc(lua_tonumber(L, 1)));
    }
    else
    {
        lua_pushnil(L);
    }
    lc_bor_result = 1;
    return lc_bor_result;
};
LongInt uscript_lc_bnot(Plua_State L)
{
    LongInt lc_bnot_result;
    if(uscript_CheckLuaParamCount(L, 1, __str35, __str36))
    {
        lua_pushnumber(L, ~fpcrtl_trunc(lua_tonumber(L, 1)));
    }
    else
    {
        lua_pushnil(L);
    }
    lc_bnot_result = 1;
    return lc_bnot_result;
};
LongInt uscript_lc_div(Plua_State L)
{
    LongInt lc_div_result;
    if(uscript_CheckLuaParamCount(L, 2, __str37, __str38))
    {
        lua_pushnumber(L, fpcrtl_trunc(lua_tonumber(L, 1)) / fpcrtl_trunc(lua_tonumber(L, 2)));
    }
    else
    {
        lua_pushnil(L);
    }
    lc_div_result = 1;
    return lc_div_result;
};
LongInt uscript_lc_getinputmask(Plua_State L)
{
    LongInt lc_getinputmask_result;
    if(uscript_CheckLuaParamCount(L, 0, __str39, __str40))
    {
        lua_pushnumber(L, InputMask);
    }
    lc_getinputmask_result = 1;
    return lc_getinputmask_result;
};
LongInt uscript_lc_setinputmask(Plua_State L)
{
    LongInt lc_setinputmask_result;
    if(uscript_CheckLuaParamCount(L, 1, __str41, __str42))
    {
        InputMask = fpcrtl_trunc(lua_tonumber(L, 1));
    }
    lc_setinputmask_result = 0;
    return lc_setinputmask_result;
};
LongInt uscript_lc_writelntoconsole(Plua_State L)
{
    LongInt lc_writelntoconsole_result;
    if(uscript_CheckLuaParamCount(L, 1, __str43, __str44))
    {
        uconsole_WriteLnToConsole(_strconcat(__str45, luapas_lua_tostring(L, 1)));
    }
    lc_writelntoconsole_result = 0;
    return lc_writelntoconsole_result;
};
LongInt uscript_lc_writelntochat(Plua_State L)
{
    LongInt lc_writelntochat_result;
    if(uscript_CheckLuaParamCount(L, 1, __str46, __str44))
    {
        uchat_AddChatString(_strprepend(0x2, luapas_lua_tostring(L, 1)));
    }
    lc_writelntochat_result = 0;
    return lc_writelntochat_result;
};
LongInt uscript_lc_parsecommand(Plua_State L)
{
    LongInt lc_parsecommand_result;
    PChar t;
    LongWord i;
    LongWord c;
    string255 s;
    if(uscript_CheckLuaParamCount(L, 1, __str47, __str44))
    {
        t = lua_tolstring(L, 1, ((Psize_t)&(c)));
        {i = 1;
         LongWord i__end__ = c;
         if (i <= i__end__) do {
                                   s.s[i] = t[i - 1];
                               } while(i++ != i__end__);}
        s.s[0] = ((char)c);
        ucommands_ParseCommand_3(s, true, true);
    }
    lc_parsecommand_result = 0;
    return lc_parsecommand_result;
};
LongInt uscript_lc_setweapon(Plua_State L)
{
    LongInt lc_setweapon_result;
    LongInt at;
    static const string255 callStr = STRINIT("SetWeapon");
    static const string255 paramsStr = STRINIT("ammoType");
    if((CurrentHedgehog != NULL) && uscript_CheckLuaParamCount(L, 1, callStr, paramsStr))
    {
        at = uscript_LuaToAmmoTypeOrd(L, 1, callStr, paramsStr);
        if(at >= 0)
        {
            ucommands_ParseCommand_3(_strappend(__str48, ((char)at)), true, true);
        }
    }
    lc_setweapon_result = 0;
    return lc_setweapon_result;
};
LongInt uscript_lc_setcinematicmode(Plua_State L)
{
    LongInt lc_setcinematicmode_result;
    static const string255 callStr = STRINIT("SetCinematicMode");
    static const string255 paramsStr = STRINIT("enable");
    if(uscript_CheckLuaParamCount(L, 1, callStr, paramsStr))
    {
        CinematicScript = lua_toboolean(L, 1);
    }
    lc_setcinematicmode_result = 0;
    return lc_setcinematicmode_result;
};
LongInt uscript_lc_setmaxbuilddistance(Plua_State L)
{
    LongInt lc_setmaxbuilddistance_result;
    LongInt np;
    static const string255 callStr = STRINIT("SetMaxBuildDistance");
    static const string255 paramsStr = STRINIT("[ distInPx ]");
    if(uscript_CheckAndFetchParamCountRange(L, 0, 1, callStr, paramsStr, &(np)))
    {
        if(np == 0)
        {
            cBuildMaxDist = cDefaultBuildMaxDist;
        }
        else
        {
            cBuildMaxDist = fpcrtl_trunc(lua_tonumber(L, 1));
        }
    }
    lc_setmaxbuilddistance_result = 0;
    return lc_setmaxbuilddistance_result;
};
LongInt uscript_lc_setnextweapon(Plua_State L)
{
    LongInt lc_setnextweapon_result;
    LongInt at;
    TAmmo nextAmmo;
    LongInt s;
    LongInt a;
    LongInt cs;
    LongInt fa;
    static const string255 callStr = STRINIT("SetNextWeapon");
    static const string255 paramsStr = STRINIT("");
    if((CurrentHedgehog != NULL) && uscript_CheckLuaParamCount(L, 0, callStr, paramsStr))
    {
        at = -1;
        {
            cs = 0;
            fa = 0;
            if((*CurrentHedgehog).CurAmmoType != amNothing)
            {
                cs = Ammoz[(*CurrentHedgehog).CurAmmoType].Slot;
                while((fa < cMaxSlotAmmoIndex) && ((*(*CurrentHedgehog).Ammo)[cs][fa].AmmoType != (*CurrentHedgehog).CurAmmoType))
                {
                    ++fa;
                }
                ++fa;
            }
            {s = cs;
             LongInt s__end__ = (cs + cMaxSlotIndex) + 1;
             if (s <= s__end__) do {
                                       {a = fa;
                                        LongInt a__end__ = cMaxSlotAmmoIndex;
                                        if (a <= a__end__) do {
                                                                  if((a == fa) && (s == ((cs + cMaxSlotIndex) + 1)))
                                                                  {
                                                                      return 0;
                                                                  }
                                                                  nextAmmo = (*(*CurrentHedgehog).Ammo)[s % (cMaxSlotIndex + 1)][a];
                                                                  if(((nextAmmo.AmmoType != amNothing) && (nextAmmo.AmmoType != amSkip)) && (nextAmmo.Count > 0))
                                                                  {
                                                                      at = (nextAmmo.AmmoType);
                                                                      break;
                                                                  }
                                                              } while(a++ != a__end__);}
                                       if(at >= 0)
                                       {
                                           break;
                                       }
                                       fa = 0;
                                   } while(s++ != s__end__);}
        }
        if(at >= 0)
        {
            ucommands_ParseCommand_3(_strappend(__str48, ((char)at)), true, true);
        }
    }
    lc_setnextweapon_result = 0;
    return lc_setnextweapon_result;
};
LongInt uscript_lc_showmission(Plua_State L)
{
    LongInt lc_showmission_result;
    LongInt n;
    if(uscript_CheckAndFetchParamCount(L, 5, 6, __str49, __str50, &(n)))
    {
        if(n == 5)
        {
            uworld_ShowMission_5(luapas_lua_tostringA(L, 1), luapas_lua_tostringA(L, 2), luapas_lua_tostringA(L, 3), fpcrtl_trunc(lua_tonumber(L, 4)), fpcrtl_trunc(lua_tonumber(L, 5)));
        }
        else
        {
            uworld_ShowMission_6(luapas_lua_tostringA(L, 1), luapas_lua_tostringA(L, 2), luapas_lua_tostringA(L, 3), fpcrtl_trunc(lua_tonumber(L, 4)), fpcrtl_trunc(lua_tonumber(L, 5)), lua_toboolean(L, 6));
        }
    }
    lc_showmission_result = 0;
    return lc_showmission_result;
};
LongInt uscript_lc_hidemission(Plua_State L)
{
    LongInt lc_hidemission_result;
    UNUSED (L);
    uworld_HideMission();
    lc_hidemission_result = 0;
    return lc_hidemission_result;
};
LongInt uscript_lc_getenginestring(Plua_State L)
{
    LongInt lc_getenginestring_result;
    string255 stringType;
    LongInt msgId;
    static const string255 callStr = STRINIT("GetEngineString");
    static const string255 paramsStr = STRINIT("stringType, msgId");
    if(uscript_CheckLuaParamCount(L, 2, callStr, paramsStr))
    {
        stringType = luapas_lua_tostring(L, 1);
        if(!lua_isnumber(L, 2))
        {
            uscript_LuaError(__str51);
            lua_pushnil(L);
        }
        else
        {
            if(_strcompare(stringType, __str52))
            {
                msgId = uscript_LuaToMsgStrIdOrd(L, 2, callStr, paramsStr);
                if(msgId == -1)
                {
                    lua_pushnil(L);
                }
                else
                {
                    lua_pushstring(L, fpcrtl__pcharA(trmsg[((TMsgStrId)msgId)]));
                }
            }
            else
            {
                if(_strcompare(stringType, __str53))
                {
                    msgId = uscript_LuaToGoalStrIdOrd(L, 2, callStr, paramsStr);
                    if(msgId == -1)
                    {
                        lua_pushnil(L);
                    }
                    else
                    {
                        lua_pushstring(L, fpcrtl__pcharA(trgoal[((TGoalStrId)msgId)]));
                    }
                }
                else
                {
                    uscript_LuaError(__str54);
                    lua_pushnil(L);
                }
            }
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getenginestring_result = 1;
    return lc_getenginestring_result;
};
LongInt uscript_lc_setammotexts(Plua_State L)
{
    LongInt lc_setammotexts_result;
    static const string255 callStr = STRINIT("SetAmmoTexts");
    static const string255 paramsStr = STRINIT("ammoType, name, caption, description [, showExtra]");
    Integer n;
    boolean showExtra;
    if(uscript_CheckAndFetchParamCount(L, 4, 5, callStr, paramsStr, &(n)))
    {
        if(n == 5)
        {
            showExtra = lua_toboolean(L, 5);
        }
        else
        {
            showExtra = true;
        }
        uworld_SetAmmoTexts(((TAmmoType)uscript_LuaToAmmoTypeOrd(L, 1, callStr, paramsStr)), luapas_lua_tostringA(L, 2), luapas_lua_tostringA(L, 3), luapas_lua_tostringA(L, 4), showExtra);
    }
    lc_setammotexts_result = 0;
    return lc_setammotexts_result;
};
LongInt uscript_lc_setammodescriptionappendix(Plua_State L)
{
    LongInt lc_setammodescriptionappendix_result;
    static const string255 callStr = STRINIT("SetAmmoDescriptionAppendix");
    static const string255 paramsStr = STRINIT("ammoType, descAppend");
    TAmmoType ammoType;
    astring descAppend;
    if(uscript_CheckLuaParamCount(L, 2, callStr, paramsStr))
    {
        ammoType = ((TAmmoType)uscript_LuaToAmmoTypeOrd(L, 1, callStr, paramsStr));
        descAppend = luapas_lua_tostringA(L, 2);
        trluaammoa[Ammoz[ammoType].NameId] = descAppend;
    }
    lc_setammodescriptionappendix_result = 0;
    return lc_setammodescriptionappendix_result;
};
LongInt uscript_lc_enablegameflags(Plua_State L)
{
    LongInt lc_enablegameflags_result;
    Integer i;
    Integer n;
    if(uscript_CheckAndFetchLuaParamMinCount(L, 1, __str55, __str56, &(n)))
    {
        {i = 1;
         Integer i__end__ = n;
         if (i <= i__end__) do {
                                   GameFlags = GameFlags | ((LongWord)fpcrtl_trunc(lua_tonumber(L, i)));
                               } while(i++ != i__end__);}
        uscript_ScriptSetInteger(__str57, GameFlags);
    }
    lc_enablegameflags_result = 0;
    return lc_enablegameflags_result;
};
LongInt uscript_lc_disablegameflags(Plua_State L)
{
    LongInt lc_disablegameflags_result;
    Integer i;
    Integer n;
    if(uscript_CheckAndFetchLuaParamMinCount(L, 1, __str58, __str56, &(n)))
    {
        {i = 1;
         Integer i__end__ = n;
         if (i <= i__end__) do {
                                   GameFlags = GameFlags & ~((LongWord)fpcrtl_trunc(lua_tonumber(L, i)));
                               } while(i++ != i__end__);}
        uscript_ScriptSetInteger(__str57, GameFlags);
    }
    lc_disablegameflags_result = 0;
    return lc_disablegameflags_result;
};
LongInt uscript_lc_cleargameflags(Plua_State L)
{
    LongInt lc_cleargameflags_result;
    if(uscript_CheckLuaParamCount(L, 0, __str59, __str40))
    {
        GameFlags = 0;
        uscript_ScriptSetInteger(__str57, GameFlags);
    }
    lc_cleargameflags_result = 0;
    return lc_cleargameflags_result;
};
LongInt uscript_lc_getgameflag(Plua_State L)
{
    LongInt lc_getgameflag_result;
    if(uscript_CheckLuaParamCount(L, 1, __str60, __str61))
    {
        lua_pushboolean(L, (GameFlags & ((LongWord)fpcrtl_trunc(lua_tonumber(L, 1)))) != 0);
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getgameflag_result = 1;
    return lc_getgameflag_result;
};
LongInt uscript_lc_addcaption(Plua_State L)
{
    LongInt lc_addcaption_result;
    LongInt cg;
    static const string255 callStr = STRINIT("AddCaption");
    static const string255 paramsStr = STRINIT("text [, color, captiongroup]");
    if(uscript_CheckAndFetchParamCount(L, 1, 3, callStr, paramsStr, &(cg)))
    {
        if(cg == 1)
        {
            ucaptions_AddCaption(luapas_lua_tostringA(L, 1), capcolDefault, capgrpMessage);
        }
        else
        {
            cg = uscript_LuaToCapGroupOrd(L, 3, callStr, paramsStr);
            if(cg >= 0)
            {
                ucaptions_AddCaption(luapas_lua_tostringA(L, 1), fpcrtl_trunc(lua_tonumber(L, 2)) >> 8, ((TCapGroup)cg));
            }
        }
    }
    lc_addcaption_result = 0;
    return lc_addcaption_result;
};
LongInt uscript_lc_spawnfakehealthcrate(Plua_State L)
{
    LongInt lc_spawnfakehealthcrate_result;
    PGear gear;
    boolean explode;
    boolean poison;
    LongInt n;
    if(uscript_CheckAndFetchParamCountRange(L, 2, 4, __str62, __str63, &(n)))
    {
        explode = false;
        poison = false;
        if((n >= 3) && !luapas_lua_isnil(L, 3))
        {
            explode = lua_toboolean(L, 3);
        }
        if((n == 4) && !luapas_lua_isnil(L, 4))
        {
            poison = lua_toboolean(L, 4);
        }
        gear = ugears_SpawnFakeCrateAt(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), HealthCrate, explode, poison);
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->uid);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_spawnfakehealthcrate_result = 1;
    return lc_spawnfakehealthcrate_result;
};
LongInt uscript_lc_spawnfakeammocrate(Plua_State L)
{
    LongInt lc_spawnfakeammocrate_result;
    PGear gear;
    boolean explode;
    boolean poison;
    LongInt n;
    if(uscript_CheckAndFetchParamCountRange(L, 2, 4, __str64, __str63, &(n)))
    {
        explode = false;
        poison = false;
        if((n >= 3) && !luapas_lua_isnil(L, 3))
        {
            explode = lua_toboolean(L, 3);
        }
        if((n == 4) && !luapas_lua_isnil(L, 4))
        {
            poison = lua_toboolean(L, 4);
        }
        gear = ugears_SpawnFakeCrateAt(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), AmmoCrate, explode, poison);
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->uid);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_spawnfakeammocrate_result = 1;
    return lc_spawnfakeammocrate_result;
};
LongInt uscript_lc_spawnfakeutilitycrate(Plua_State L)
{
    LongInt lc_spawnfakeutilitycrate_result;
    PGear gear;
    boolean explode;
    boolean poison;
    LongInt n;
    if(uscript_CheckAndFetchParamCountRange(L, 2, 4, __str65, __str63, &(n)))
    {
        explode = false;
        poison = false;
        if((n >= 3) && !luapas_lua_isnil(L, 3))
        {
            explode = lua_toboolean(L, 3);
        }
        if((n == 4) && !luapas_lua_isnil(L, 4))
        {
            poison = lua_toboolean(L, 4);
        }
        gear = ugears_SpawnFakeCrateAt(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), UtilityCrate, explode, poison);
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->uid);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_spawnfakeutilitycrate_result = 1;
    return lc_spawnfakeutilitycrate_result;
};
LongInt uscript_lc_spawnhealthcrate(Plua_State L)
{
    LongInt lc_spawnhealthcrate_result;
    PGear gear;
    LongInt health;
    LongInt n;
    if(uscript_CheckAndFetchParamCount(L, 2, 3, __str66, __str67, &(n)))
    {
        if(n == 3)
        {
            health = fpcrtl_trunc(lua_tonumber(L, 3));
        }
        else
        {
            health = cHealthCaseAmount;
        }
        gear = ugears_SpawnCustomCrateAt(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), HealthCrate, health, 0);
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->uid);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_spawnhealthcrate_result = 1;
    return lc_spawnhealthcrate_result;
};
LongInt uscript_lc_spawnammocrate(Plua_State L)
{
    LongInt lc_spawnammocrate_result;
    PGear gear;
    LongInt n;
    if(uscript_CheckAndFetchParamCount(L, 3, 4, __str68, __str69, &(n)))
    {
        if(n == 3)
        {
            gear = ugears_SpawnCustomCrateAt(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), AmmoCrate, fpcrtl_trunc(lua_tonumber(L, 3)), 0);
        }
        else
        {
            gear = ugears_SpawnCustomCrateAt(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), AmmoCrate, fpcrtl_trunc(lua_tonumber(L, 3)), fpcrtl_trunc(lua_tonumber(L, 4)));
        }
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->uid);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_spawnammocrate_result = 1;
    return lc_spawnammocrate_result;
};
LongInt uscript_lc_spawnutilitycrate(Plua_State L)
{
    LongInt lc_spawnutilitycrate_result;
    PGear gear;
    LongInt n;
    if(uscript_CheckAndFetchParamCount(L, 3, 4, __str70, __str69, &(n)))
    {
        if(n == 3)
        {
            gear = ugears_SpawnCustomCrateAt(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), UtilityCrate, fpcrtl_trunc(lua_tonumber(L, 3)), 0);
        }
        else
        {
            gear = ugears_SpawnCustomCrateAt(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), UtilityCrate, fpcrtl_trunc(lua_tonumber(L, 3)), fpcrtl_trunc(lua_tonumber(L, 4)));
        }
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->uid);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_spawnutilitycrate_result = 1;
    return lc_spawnutilitycrate_result;
};
LongInt uscript_lc_spawnsupplycrate(Plua_State L)
{
    LongInt lc_spawnsupplycrate_result;
    PGear gear;
    LongInt n;
    LongInt at;
    TCrateType t;
    if(uscript_CheckAndFetchParamCount(L, 3, 4, __str71, __str69, &(n)))
    {
        at = fpcrtl_trunc(lua_tonumber(L, 3));
        if((Ammoz[((TAmmoType)at)].Ammo.Propz & ammoprop_Utility) != 0)
        {
            t = UtilityCrate;
        }
        else
        {
            t = AmmoCrate;
        }
        if(n == 3)
        {
            gear = ugears_SpawnCustomCrateAt(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), t, at, 0);
        }
        else
        {
            gear = ugears_SpawnCustomCrateAt(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), t, at, fpcrtl_trunc(lua_tonumber(L, 4)));
        }
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->uid);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_spawnsupplycrate_result = 1;
    return lc_spawnsupplycrate_result;
};
LongInt uscript_lc_addgear(Plua_State L)
{
    LongInt lc_addgear_result;
    PGear gear;
    LongInt x;
    LongInt y;
    LongInt s;
    LongInt t;
    hwFloat dx;
    hwFloat dy;
    TGearType gt;
    static const string255 callStr = STRINIT("AddGear");
    static const string255 paramsStr = STRINIT("x, y, gearType, state, dx, dy, timer");
    if(uscript_CheckLuaParamCount(L, 7, callStr, paramsStr))
    {
        t = uscript_LuaToGearTypeOrd(L, 3, callStr, paramsStr);
        if(t >= 0)
        {
            gt = ((TGearType)t);
            x = fpcrtl_trunc(lua_tonumber(L, 1));
            y = fpcrtl_trunc(lua_tonumber(L, 2));
            s = fpcrtl_trunc(lua_tonumber(L, 4));
            dx = ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(fpcrtl_trunc(lua_tonumber(L, 5))), 1000000);
            dy = ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(fpcrtl_trunc(lua_tonumber(L, 6))), 1000000);
            t = fpcrtl_trunc(lua_tonumber(L, 7));
            gear = ugearslist_AddGear_7(x, y, gt, s, dx, dy, t);
            lastGearByUID = gear;
            lua_pushnumber(L, gear->uid);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_addgear_result = 1;
    return lc_addgear_result;
};
LongInt uscript_lc_deletegear(Plua_State L)
{
    LongInt lc_deletegear_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str72, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->Message = gear->Message | gmDelete;
        }
    }
    lc_deletegear_result = 0;
    return lc_deletegear_result;
};
LongInt uscript_lc_addvisualgear(Plua_State L)
{
    LongInt lc_addvisualgear_result;
    PVisualGear vg;
    LongInt x;
    LongInt y;
    LongInt s;
    LongInt n;
    LongInt layer;
    boolean c;
    TVisualGearType vgt;
    LongWord uid;
    static const string255 callStr = STRINIT("AddVisualGear");
    static const string255 paramsStr = STRINIT("x, y, visualGearType, state, critical [, layer]");
    uid = 0;
    if(uscript_CheckAndFetchParamCount(L, 5, 6, callStr, paramsStr, &(n)))
    {
        s = uscript_LuaToVisualGearTypeOrd(L, 3, callStr, paramsStr);
        if(s >= 0)
        {
            vgt = ((TVisualGearType)s);
            x = fpcrtl_trunc(lua_tonumber(L, 1));
            y = fpcrtl_trunc(lua_tonumber(L, 2));
            s = fpcrtl_trunc(lua_tonumber(L, 4));
            c = lua_toboolean(L, 5);
            if(n == 6)
            {
                layer = fpcrtl_trunc(lua_tonumber(L, 6));
                vg = uvisualgearslist_AddVisualGear_6(x, y, vgt, s, c, layer);
            }
            else
            {
                vg = uvisualgearslist_AddVisualGear_5(x, y, vgt, s, c);
            }
            if(vg != NULL)
            {
                lastVisualGearByUID = vg;
                uid = vg->uid;
                lua_pushnumber(L, uid);
            }
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_addvisualgear_result = 1;
    return lc_addvisualgear_result;
};
LongInt uscript_lc_deletevisualgear(Plua_State L)
{
    LongInt lc_deletevisualgear_result;
    PVisualGear vg;
    vg = NULL;
    if(uscript_CheckLuaParamCount(L, 1, __str74, __str75))
    {
        vg = uvisualgearslist_VisualGearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(vg != NULL)
        {
            uvisualgearslist_DeleteVisualGear(vg);
        }
    }
    lua_pushboolean(L, vg != NULL);
    lc_deletevisualgear_result = 1;
    return lc_deletevisualgear_result;
};
LongInt uscript_lc_getvisualgeartype(Plua_State L)
{
    LongInt lc_getvisualgeartype_result;
    PVisualGear vg;
    if(uscript_CheckLuaParamCount(L, 1, __str76, __str75))
    {
        vg = uvisualgearslist_VisualGearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(vg != NULL)
        {
            lua_pushnumber(L, (vg->Kind));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getvisualgeartype_result = 1;
    return lc_getvisualgeartype_result;
};
LongInt uscript_lc_getvisualgearvalues(Plua_State L)
{
    LongInt lc_getvisualgearvalues_result;
    PVisualGear vg;
    if(uscript_CheckLuaParamCount(L, 1, __str77, __str75))
    {
        vg = uvisualgearslist_VisualGearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(vg != NULL)
        {
            lua_pushnumber(L, fpcrtl_round(vg->X));
            lua_pushnumber(L, fpcrtl_round(vg->Y));
            lua_pushnumber(L, vg->dX);
            lua_pushnumber(L, vg->dY);
            lua_pushnumber(L, vg->Angle);
            lua_pushnumber(L, vg->Frame);
            lua_pushnumber(L, vg->FrameTicks);
            lua_pushnumber(L, vg->State);
            lua_pushnumber(L, vg->Timer);
            lua_pushnumber(L, vg->Tint);
            lua_pushnumber(L, vg->scale);
        }
        else
        {
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
    }
    lc_getvisualgearvalues_result = 10;
    return lc_getvisualgearvalues_result;
};
LongInt uscript_lc_setvisualgearvalues(Plua_State L)
{
    LongInt lc_setvisualgearvalues_result;
    PVisualGear vg;
    vg = uvisualgearslist_VisualGearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
    if(vg != NULL)
    {
        if(!luapas_lua_isnoneornil(L, 2))
        {
            vg->X = fpcrtl_trunc(lua_tonumber(L, 2));
        }
        if(!luapas_lua_isnoneornil(L, 3))
        {
            vg->Y = fpcrtl_trunc(lua_tonumber(L, 3));
        }
        if(!luapas_lua_isnoneornil(L, 4))
        {
            vg->dX = lua_tonumber(L, 4);
        }
        if(!luapas_lua_isnoneornil(L, 5))
        {
            vg->dY = lua_tonumber(L, 5);
        }
        if(!luapas_lua_isnoneornil(L, 6))
        {
            vg->Angle = lua_tonumber(L, 6);
        }
        if(!luapas_lua_isnoneornil(L, 7))
        {
            vg->Frame = fpcrtl_trunc(lua_tonumber(L, 7));
        }
        if(!luapas_lua_isnoneornil(L, 8))
        {
            vg->FrameTicks = fpcrtl_trunc(lua_tonumber(L, 8));
        }
        if(!luapas_lua_isnoneornil(L, 9))
        {
            vg->State = fpcrtl_trunc(lua_tonumber(L, 9));
        }
        if(!luapas_lua_isnoneornil(L, 10))
        {
            vg->Timer = fpcrtl_trunc(lua_tonumber(L, 10));
        }
        if(!luapas_lua_isnoneornil(L, 11))
        {
            vg->Tint = fpcrtl_trunc(lua_tonumber(L, 11));
        }
        if(!luapas_lua_isnoneornil(L, 12))
        {
            vg->scale = fpcrtl_trunc(lua_tonumber(L, 12));
        }
    }
    lc_setvisualgearvalues_result = 0;
    return lc_setvisualgearvalues_result;
};
LongInt uscript_lc_getgearvalues(Plua_State L)
{
    LongInt lc_getgearvalues_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str78, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->Angle);
            lua_pushnumber(L, gear->Power);
            lua_pushnumber(L, gear->WDTimer);
            lua_pushnumber(L, gear->Radius);
            lua_pushnumber(L, ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(gear->Density, _10000)));
            lua_pushnumber(L, gear->Karma);
            lua_pushnumber(L, gear->DirAngle);
            lua_pushnumber(L, gear->AdvBounce);
            lua_pushnumber(L, ((Integer)gear->ImpactSound));
            lua_pushnumber(L, gear->nImpactSounds);
            lua_pushnumber(L, gear->Tint);
            lua_pushnumber(L, gear->Damage);
            lua_pushnumber(L, gear->Boom);
        }
        else
        {
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
    }
    lc_getgearvalues_result = 13;
    return lc_getgearvalues_result;
};
LongInt uscript_lc_setgearvalues(Plua_State L)
{
    LongInt lc_setgearvalues_result;
    PGear gear;
    gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
    if(gear != NULL)
    {
        if(!luapas_lua_isnoneornil(L, 2))
        {
            gear->Angle = fpcrtl_trunc(lua_tonumber(L, 2));
        }
        if(!luapas_lua_isnoneornil(L, 3))
        {
            gear->Power = fpcrtl_trunc(lua_tonumber(L, 3));
        }
        if(!luapas_lua_isnoneornil(L, 4))
        {
            gear->WDTimer = fpcrtl_trunc(lua_tonumber(L, 4));
        }
        if(!luapas_lua_isnoneornil(L, 5))
        {
            gear->Radius = fpcrtl_trunc(lua_tonumber(L, 5));
        }
        if(!luapas_lua_isnoneornil(L, 6))
        {
            gear->Density = ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(fpcrtl_trunc(lua_tonumber(L, 6))), 10000);
        }
        if(!luapas_lua_isnoneornil(L, 7))
        {
            gear->Karma = fpcrtl_trunc(lua_tonumber(L, 7));
        }
        if(!luapas_lua_isnoneornil(L, 8))
        {
            gear->DirAngle = lua_tonumber(L, 8);
        }
        if(!luapas_lua_isnoneornil(L, 9))
        {
            gear->AdvBounce = fpcrtl_trunc(lua_tonumber(L, 9));
        }
        if(!luapas_lua_isnoneornil(L, 10))
        {
            gear->ImpactSound = ((TSound)fpcrtl_trunc(lua_tonumber(L, 10)));
        }
        if(!luapas_lua_isnoneornil(L, 11))
        {
            gear->nImpactSounds = fpcrtl_trunc(lua_tonumber(L, 11));
        }
        if(!luapas_lua_isnoneornil(L, 12))
        {
            gear->Tint = fpcrtl_trunc(lua_tonumber(L, 12));
        }
        if(!luapas_lua_isnoneornil(L, 13))
        {
            gear->Damage = fpcrtl_trunc(lua_tonumber(L, 13));
        }
        if(!luapas_lua_isnoneornil(L, 14))
        {
            gear->Boom = fpcrtl_trunc(lua_tonumber(L, 14));
        }
    }
    lc_setgearvalues_result = 0;
    return lc_setgearvalues_result;
};
LongInt uscript_lc_getfollowgear(Plua_State L)
{
    LongInt lc_getfollowgear_result;
    if(uscript_CheckLuaParamCount(L, 0, __str79, __str40))
    {
        if(FollowGear == NULL)
        {
            lua_pushnil(L);
        }
        else
        {
            lua_pushnumber(L, FollowGear->uid);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getfollowgear_result = 1;
    return lc_getfollowgear_result;
};
LongInt uscript_lc_getgeartype(Plua_State L)
{
    LongInt lc_getgeartype_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str80, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, (gear->Kind));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getgeartype_result = 1;
    return lc_getgeartype_result;
};
LongInt uscript_lc_getgearmessage(Plua_State L)
{
    LongInt lc_getgearmessage_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str81, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->Message);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getgearmessage_result = 1;
    return lc_getgearmessage_result;
};
LongInt uscript_lc_getgearelasticity(Plua_State L)
{
    LongInt lc_getgearelasticity_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str82, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(gear->Elasticity, _10000)));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getgearelasticity_result = 1;
    return lc_getgearelasticity_result;
};
LongInt uscript_lc_setgearelasticity(Plua_State L)
{
    LongInt lc_setgearelasticity_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str83, __str84))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->Elasticity = ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(fpcrtl_trunc(lua_tonumber(L, 2))), 10000);
        }
    }
    lc_setgearelasticity_result = 0;
    return lc_setgearelasticity_result;
};
LongInt uscript_lc_getgearfriction(Plua_State L)
{
    LongInt lc_getgearfriction_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str85, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(gear->Friction, _10000)));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getgearfriction_result = 1;
    return lc_getgearfriction_result;
};
LongInt uscript_lc_setgearfriction(Plua_State L)
{
    LongInt lc_setgearfriction_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str86, __str87))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->Friction = ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(fpcrtl_trunc(lua_tonumber(L, 2))), 10000);
        }
    }
    lc_setgearfriction_result = 0;
    return lc_setgearfriction_result;
};
LongInt uscript_lc_setgearmessage(Plua_State L)
{
    LongInt lc_setgearmessage_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str88, __str89))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->Message = fpcrtl_trunc(lua_tonumber(L, 2));
        }
    }
    lc_setgearmessage_result = 0;
    return lc_setgearmessage_result;
};
LongInt uscript_lc_getgearpos(Plua_State L)
{
    LongInt lc_getgearpos_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str90, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->Pos);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getgearpos_result = 1;
    return lc_getgearpos_result;
};
LongInt uscript_lc_setgearpos(Plua_State L)
{
    LongInt lc_setgearpos_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str91, __str92))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->Pos = fpcrtl_trunc(lua_tonumber(L, 2));
        }
    }
    lc_setgearpos_result = 0;
    return lc_setgearpos_result;
};
LongInt uscript_lc_getgearcollisionmask(Plua_State L)
{
    LongInt lc_getgearcollisionmask_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str93, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->CollisionMask);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getgearcollisionmask_result = 1;
    return lc_getgearcollisionmask_result;
};
LongInt uscript_lc_setgearcollisionmask(Plua_State L)
{
    LongInt lc_setgearcollisionmask_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str94, __str95))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->CollisionMask = fpcrtl_trunc(lua_tonumber(L, 2));
        }
    }
    lc_setgearcollisionmask_result = 0;
    return lc_setgearcollisionmask_result;
};
LongInt uscript_lc_gethoglevel(Plua_State L)
{
    LongInt lc_gethoglevel_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str96, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && ((gear->Kind == gtHedgehog) || (gear->Kind == gtGrave))) && (gear->Hedgehog != NULL))
        {
            lua_pushnumber(L, (*gear->Hedgehog).BotLevel);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    lc_gethoglevel_result = 1;
    return lc_gethoglevel_result;
};
LongInt uscript_lc_sethoglevel(Plua_State L)
{
    LongInt lc_sethoglevel_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str97, __str98))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && (gear->Kind == gtHedgehog)) && (gear->Hedgehog != NULL))
        {
            (*gear->Hedgehog).BotLevel = fpcrtl_trunc(lua_tonumber(L, 2));
        }
    }
    lc_sethoglevel_result = 0;
    return lc_sethoglevel_result;
};
LongInt uscript_lc_gethogclan(Plua_State L)
{
    LongInt lc_gethogclan_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str99, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && ((gear->Kind == gtHedgehog) || (gear->Kind == gtGrave))) && (gear->Hedgehog != NULL))
        {
            lua_pushnumber(L, (*(*(*gear->Hedgehog).Team).Clan).ClanIndex);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gethogclan_result = 1;
    return lc_gethogclan_result;
};
LongInt uscript_lc_getclancolor(Plua_State L)
{
    LongInt lc_getclancolor_result;
    Integer idx;
    if(uscript_CheckLuaParamCount(L, 1, __str100, __str101))
    {
        idx = fpcrtl_trunc(lua_tonumber(L, 1));
        if(!lua_isnumber(L, 1))
        {
            uscript_LuaError(__str102);
            lua_pushnil(L);
        }
        else
        {
            if((idx < 0) || (idx >= ClansCount))
            {
                uscript_LuaError(_strappend(_strconcat(_strconcat(_strconcat(__str103, uutils_IntToStr(ClansCount)), __str104), uutils_IntToStr(ClansCount - 1)), 0x29));
                lua_pushnil(L);
            }
            else
            {
                lua_pushnumber(L, (ClansArray[idx]->Color << 8) | 0xff);
            }
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getclancolor_result = 1;
    return lc_getclancolor_result;
};
LongInt uscript_lc_setclancolor(Plua_State L)
{
    LongInt lc_setclancolor_result;
    PClan clan;
    PTeam team;
    THedgehog hh;
    LongInt i;
    LongInt j;
    Int64 colorArg;
    LongWord color;
    if(uscript_CheckLuaParamCount(L, 2, __str105, __str106))
    {
        i = fpcrtl_trunc(lua_tonumber(L, 1));
        if(i >= ClansCount)
        {
            return 0;
        }
        clan = ClansArray[i];
        colorArg = fpcrtl_trunc(lua_tonumber(L, 2));
        if((colorArg < 0) && (fpcrtl_abs(colorArg) <= cClanColors))
        {
            color = ClanColorArray[((int)(fpcrtl_abs(colorArg)) - 1)];
        }
        else
        {
            if((colorArg >= 0) && (colorArg <= 0xffffffff))
            {
                color = colorArg >> 8;
            }
            else
            {
                udebug_OutError(_strconcat(_strconcat(__str107, uutils_IntToStr(-cClanColors)), __str108), true);
                lc_setclancolor_result = 0;
                return lc_setclancolor_result;
            }
        }
        clan->Color = color;
        {i = 0;
         LongInt i__end__ = ((int)(clan->TeamsNumber) - 1);
         if (i <= i__end__) do {
                                   team = clan->Teams[i];
                                   {j = 0;
                                    LongInt j__end__ = cMaxHHIndex;
                                    if (j <= j__end__) do {
                                                              hh = team->Hedgehogs[j];
                                                              if((hh.Gear != NULL) || (hh.GearHidden != NULL))
                                                              {
                                                                  utextures_FreeAndNilTexture(&(hh.NameTagTex));
                                                                  hh.NameTagTex = urenderutils_RenderStringTex(fpcrtl_str2astr(hh.Name), clan->Color, fnt16);
                                                                  ustore_RenderHealth(&(hh));
                                                                  team->Hedgehogs[j] = hh;
                                                              }
                                                          } while(j++ != j__end__);}
                                   utextures_FreeAndNilTexture(&(team->NameTagTex));
                                   team->NameTagTex = urenderutils_RenderStringTex(fpcrtl_str2astr((*clan->Teams[i]).TeamName), clan->Color, fnt16);
                               } while(i++ != i__end__);}
        utextures_FreeAndNilTexture(&(clan->HealthTex));
        clan->HealthTex = ustore_makeHealthBarTexture(cTeamHealthWidth + 5, cTeamHealthHeight, clan->Color);
    }
    lc_setclancolor_result = 0;
    return lc_setclancolor_result;
};
LongInt uscript_lc_gethogvoicepack(Plua_State L)
{
    LongInt lc_gethogvoicepack_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str109, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && (gear->Kind == gtHedgehog)) && (gear->Hedgehog != NULL))
        {
            lua_pushstring(L, uutils_Str2PChar((*(*(*gear->Hedgehog).Team).voicepack).name));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gethogvoicepack_result = 1;
    return lc_gethogvoicepack_result;
};
LongInt uscript_lc_gethoggrave(Plua_State L)
{
    LongInt lc_gethoggrave_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str110, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && ((gear->Kind == gtHedgehog) || (gear->Kind == gtGrave))) && (gear->Hedgehog != NULL))
        {
            lua_pushstring(L, uutils_Str2PChar((*(*gear->Hedgehog).Team).GraveName));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gethoggrave_result = 1;
    return lc_gethoggrave_result;
};
LongInt uscript_lc_gethogflag(Plua_State L)
{
    LongInt lc_gethogflag_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str111, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && (gear->Kind == gtHedgehog)) && (gear->Hedgehog != NULL))
        {
            lua_pushstring(L, uutils_Str2PChar((*(*gear->Hedgehog).Team).Flag));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gethogflag_result = 1;
    return lc_gethogflag_result;
};
LongInt uscript_lc_gethogfort(Plua_State L)
{
    LongInt lc_gethogfort_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str112, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && (gear->Kind == gtHedgehog)) && (gear->Hedgehog != NULL))
        {
            lua_pushstring(L, uutils_Str2PChar((*(*gear->Hedgehog).Team).FortName));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gethogfort_result = 1;
    return lc_gethogfort_result;
};
LongInt uscript_lc_ishogalive(Plua_State L)
{
    LongInt lc_ishogalive_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str113, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            if(gear->Kind == gtHedgehog)
            {
                if((((gear->Health > 0) && (gear->Health > gear->Damage)) && ((gear->State & (gstDrowning | gstHHDeath)) == 0)) && ((gear->Message & gmDestroy) == 0))
                {
                    lua_pushboolean(L, true);
                }
                else
                {
                    lua_pushboolean(L, false);
                }
            }
            else
            {
                lua_pushboolean(L, false);
            }
        }
        else
        {
            lua_pushboolean(L, false);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_ishogalive_result = 1;
    return lc_ishogalive_result;
};
LongInt uscript_lc_ishoglocal(Plua_State L)
{
    LongInt lc_ishoglocal_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str114, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && (gear->Kind == gtHedgehog)) && (gear->Hedgehog != NULL))
        {
            lua_pushboolean(L, ugearsutils_IsHogLocal(gear->Hedgehog));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_ishoglocal_result = 1;
    return lc_ishoglocal_result;
};
LongInt uscript_lc_gethogteamname(Plua_State L)
{
    LongInt lc_gethogteamname_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str115, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && ((gear->Kind == gtHedgehog) || (gear->Kind == gtGrave))) && (gear->Hedgehog != NULL))
        {
            lua_pushstring(L, uutils_Str2PChar((*(*gear->Hedgehog).Team).TeamName));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gethogteamname_result = 1;
    return lc_gethogteamname_result;
};
LongInt uscript_lc_sethogteamname(Plua_State L)
{
    LongInt lc_sethogteamname_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str116, __str117))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && ((gear->Kind == gtHedgehog) || (gear->Kind == gtGrave))) && (gear->Hedgehog != NULL))
        {
            (*(*gear->Hedgehog).Team).TeamName = luapas_lua_tostring(L, 2);
            utextures_FreeAndNilTexture(&((*(*gear->Hedgehog).Team).NameTagTex));
            (*(*gear->Hedgehog).Team).NameTagTex = urenderutils_RenderStringTex(fpcrtl_str2astr((*(*gear->Hedgehog).Team).TeamName), (*(*(*gear->Hedgehog).Team).Clan).Color, fnt16);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_sethogteamname_result = 1;
    return lc_sethogteamname_result;
};
LongInt uscript_lc_gethogname(Plua_State L)
{
    LongInt lc_gethogname_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str118, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && ((gear->Kind == gtHedgehog) || (gear->Kind == gtGrave))) && (gear->Hedgehog != NULL))
        {
            lua_pushstring(L, uutils_Str2PChar((*gear->Hedgehog).Name));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gethogname_result = 1;
    return lc_gethogname_result;
};
LongInt uscript_lc_sethogname(Plua_State L)
{
    LongInt lc_sethogname_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str119, __str117))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && (gear->Kind == gtHedgehog)) && (gear->Hedgehog != NULL))
        {
            (*gear->Hedgehog).Name = luapas_lua_tostring(L, 2);
            utextures_FreeAndNilTexture(&((*gear->Hedgehog).NameTagTex));
            (*gear->Hedgehog).NameTagTex = urenderutils_RenderStringTex(fpcrtl_str2astr((*gear->Hedgehog).Name), (*(*(*gear->Hedgehog).Team).Clan).Color, fnt16);
        }
    }
    lc_sethogname_result = 0;
    return lc_sethogname_result;
};
LongInt uscript_lc_gettimer(Plua_State L)
{
    LongInt lc_gettimer_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str120, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->Timer);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gettimer_result = 1;
    return lc_gettimer_result;
};
LongInt uscript_lc_getflighttime(Plua_State L)
{
    LongInt lc_getflighttime_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str121, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->FlightTime);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getflighttime_result = 1;
    return lc_getflighttime_result;
};
LongInt uscript_lc_gethealth(Plua_State L)
{
    LongInt lc_gethealth_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str122, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->Health);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gethealth_result = 1;
    return lc_gethealth_result;
};
LongInt uscript_lc_getx(Plua_State L)
{
    LongInt lc_getx_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str123, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, ufloat_hwRound(gear->X));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getx_result = 1;
    return lc_getx_result;
};
LongInt uscript_lc_gety(Plua_State L)
{
    LongInt lc_gety_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str124, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, ufloat_hwRound(gear->Y));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gety_result = 1;
    return lc_gety_result;
};
LongInt uscript_lc_copypv(Plua_State L)
{
    LongInt lc_copypv_result;
    PGear gears;
    PGear geard;
    if(uscript_CheckLuaParamCount(L, 2, __str125, __str126))
    {
        gears = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        geard = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 2)));
        if((gears != NULL) && (geard != NULL))
        {
            geard->X = gears->X;
            geard->Y = gears->Y;
            geard->dX = gears->dX;
            geard->dY = gears->dY;
        }
    }
    lc_copypv_result = 0;
    return lc_copypv_result;
};
LongInt uscript_lc_followgear(Plua_State L)
{
    LongInt lc_followgear_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str127, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            FollowGear = gear;
        }
    }
    lc_followgear_result = 0;
    return lc_followgear_result;
};
LongInt uscript_lc_hogsay(Plua_State L)
{
    LongInt lc_hogsay_result;
    PGear gear;
    PVisualGear vgear;
    LongWord s;
    LongInt n;
    if(uscript_CheckAndFetchParamCount(L, 3, 4, __str128, __str129, &(n)))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            if(n == 4)
            {
                s = fpcrtl_trunc(lua_tonumber(L, 4));
            }
            else
            {
                s = 0;
            }
            vgear = uvisualgearslist_AddVisualGear_5(0, 0, vgtSpeechBubble, s, true);
            if(vgear != NULL)
            {
                vgear->Text = luapas_lua_tostring(L, 2);
                if(gear->Kind == gtHedgehog)
                {
                    uchat_AddChatString(_strprepend(0x9, ulocale_Format_3(fpcrtl_astr2str(trmsg[sidChatHog]), (*gear->Hedgehog).Name, vgear->Text)));
                    vgear->Hedgehog = gear->Hedgehog;
                }
                else
                {
                    vgear->Frame = gear->uid;
                }
                vgear->FrameTicks = fpcrtl_trunc(lua_tonumber(L, 3));
                if((vgear->FrameTicks < 1) || (vgear->FrameTicks > 3))
                {
                    vgear->FrameTicks = 1;
                }
                lua_pushnumber(L, vgear->uid);
            }
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_hogsay_result = 1;
    return lc_hogsay_result;
};
LongInt uscript_lc_switchhog(Plua_State L)
{
    LongInt lc_switchhog_result;
    PGear gear;
    PGear prevgear;
    if(uscript_CheckLuaParamCount(L, 1, __str130, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if((((gear != NULL) && (gear->Kind == gtHedgehog)) && (gear->Hedgehog != NULL)) && (CurrentHedgehog != NULL))
        {
            CurrentHedgehog->MultiShootAttacks = 0;
            prevgear = CurrentHedgehog->Gear;
            if(prevgear != NULL)
            {
                prevgear->Active = false;
                prevgear->State = prevgear->State & ~gstHHDriven;
                prevgear->Z = cHHZ;
                prevgear->Message = (prevgear->Message | gmRemoveFromList) | gmAddToList;
            }
            uteams_SwitchCurrentHedgehog(gear->Hedgehog);
            AmmoMenuInvalidated = true;
            CurrentTeam = CurrentHedgehog->Team;
            do {
                   CurrentTeam->CurrHedgehog = (CurrentTeam->CurrHedgehog + 1) % CurrentTeam->HedgehogsNumber;
               } while(!(CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Gear == CurrentHedgehog->Gear));
            gear->State = gear->State | gstHHDriven;
            gear->Active = true;
            gear->Z = cCurrHHZ;
            gear->Message = (gear->Message | gmRemoveFromList) | gmAddToList;
        }
    }
    lc_switchhog_result = 0;
    return lc_switchhog_result;
};
LongInt uscript_lc_enableswitchhog(Plua_State L)
{
    LongInt lc_enableswitchhog_result;
    PGear gear;
    PGear iterator;
    boolean alreadySwitching;
    if(uscript_CheckLuaParamCount(L, 0, __str131, __str40))
    {
        if((CurrentHedgehog != NULL) && (CurrentHedgehog->Gear != NULL))
        {
            alreadySwitching = false;
            iterator = GearsList;
            while(iterator != NULL)
            {
                if(iterator->Kind == gtSwitcher)
                {
                    alreadySwitching = true;
                    lua_pushnumber(L, iterator->uid);
                    break;
                }
                iterator = iterator->NextGear;
            }
            if(!alreadySwitching)
            {
                gear = ugearslist_AddGear_7(ufloat_hwRound((*CurrentHedgehog->Gear).X), ufloat_hwRound((*CurrentHedgehog->Gear).Y), gtSwitcher, 0, _0, _0, 0);
                CurAmmoGear = gear;
                lastGearByUID = gear;
                bShowFinger = false;
                lua_pushnumber(L, gear->uid);
            }
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_enableswitchhog_result = 1;
    return lc_enableswitchhog_result;
};
LongInt uscript_lc_addammo(Plua_State L)
{
    LongInt lc_addammo_result;
    PGear gear;
    LongInt at;
    LongInt n;
    LongInt c;
    static const string255 callStr = STRINIT("AddAmmo");
    static const string255 paramsStr = STRINIT("gearUid, ammoType [, ammoCount]");
    if(uscript_CheckAndFetchParamCount(L, 2, 3, callStr, paramsStr, &(n)))
    {
        at = uscript_LuaToAmmoTypeOrd(L, 2, callStr, paramsStr);
        if((at >= 0) && (((TAmmoType)at) != amNothing))
        {
            gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
            if((gear != NULL) && (gear->Hedgehog != NULL))
            {
                if(n == 2)
                {
                    uammos_AddAmmo_2(&((*gear->Hedgehog)), ((TAmmoType)at));
                }
                else
                {
                    c = fpcrtl_trunc(lua_tonumber(L, 3));
                    if(((c == 0) && (CurrentHedgehog == gear->Hedgehog)) && ((*gear->Hedgehog).CurAmmoType == ((TAmmoType)at)))
                    {
                        ucommands_ParseCommand_3(_strappend(__str48, ((char)0)), true, true);
                    }
                    uammos_SetAmmo(&((*gear->Hedgehog)), ((TAmmoType)at), c);
                }
            }
        }
    }
    lc_addammo_result = 0;
    return lc_addammo_result;
};
LongInt uscript_lc_getammocount(Plua_State L)
{
    LongInt lc_getammocount_result;
    PGear gear;
    PAmmo ammo;
    LongInt at;
    static const string255 callStr = STRINIT("GetAmmoCount");
    static const string255 paramsStr = STRINIT("gearUid, ammoType");
    if(uscript_CheckLuaParamCount(L, 2, callStr, paramsStr))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if((gear != NULL) && (gear->Hedgehog != NULL))
        {
            at = uscript_LuaToAmmoTypeOrd(L, 2, callStr, paramsStr);
            if(at >= 0)
            {
                ammo = uammos_GetAmmoEntry(&((*gear->Hedgehog)), ((TAmmoType)at));
                if(ammo->AmmoType == amNothing)
                {
                    lua_pushnumber(L, 0);
                }
                else
                {
                    lua_pushnumber(L, ammo->Count);
                }
            }
        }
        else
        {
            lua_pushnumber(L, 0);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getammocount_result = 1;
    return lc_getammocount_result;
};
LongInt uscript_lc_sethealth(Plua_State L)
{
    LongInt lc_sethealth_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str132, __str133))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->Health = fpcrtl_trunc(lua_tonumber(L, 2));
            if((gear->Kind == gtHedgehog) && (gear->Hedgehog != NULL))
            {
                if(gear->Health > cMaxHogHealth)
                {
                    gear->Health = cMaxHogHealth;
                }
                if(gear->Health < 0)
                {
                    gear->Health = 0;
                }
                ustore_RenderHealth(&((*gear->Hedgehog)));
                uteams_RecountTeamHealth((*gear->Hedgehog).Team);
            }
            else
            {
                if(gear->RenderHealth && (gear->Tex != NULL))
                {
                    utextures_FreeAndNilTexture(&(gear->Tex));
                }
            }
            gear->Active = true;
            AllInactive = false;
        }
    }
    lc_sethealth_result = 0;
    return lc_sethealth_result;
};
LongInt uscript_lc_healhog(Plua_State L)
{
    LongInt lc_healhog_result;
    PGear gear;
    LongInt healthBoost;
    LongInt n;
    if(uscript_CheckAndFetchParamCountRange(L, 2, 4, __str134, __str135, &(n)))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        healthBoost = fpcrtl_trunc(lua_tonumber(L, 2));
        if((((gear != NULL) && (gear->Kind == gtHedgehog)) && (gear->Hedgehog != NULL)) && (healthBoost >= 1))
        {
            healthBoost = ugearsutils_IncHogHealth(gear->Hedgehog, healthBoost);
            ustore_RenderHealth(&((*gear->Hedgehog)));
            uteams_RecountTeamHealth((*gear->Hedgehog).Team);
            if(n == 4)
            {
                ugearsutils_HHHeal_4(gear->Hedgehog, healthBoost, lua_toboolean(L, 3), fpcrtl_trunc(lua_tonumber(L, 4)));
            }
            else
            {
                if(n == 3)
                {
                    ugearsutils_HHHeal_3(gear->Hedgehog, healthBoost, lua_toboolean(L, 3));
                }
                else
                {
                    if(n == 2)
                    {
                        ugearsutils_HHHeal_3(gear->Hedgehog, healthBoost, true);
                    }
                }
            }
            gear->Active = true;
            AllInactive = false;
        }
    }
    lc_healhog_result = 0;
    return lc_healhog_result;
};
LongInt uscript_lc_settimer(Plua_State L)
{
    LongInt lc_settimer_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str136, __str137))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->Timer = fpcrtl_trunc(lua_tonumber(L, 2));
            if(gear->RenderTimer && (gear->Tex != NULL))
            {
                utextures_FreeAndNilTexture(&(gear->Tex));
            }
        }
    }
    lc_settimer_result = 0;
    return lc_settimer_result;
};
LongInt uscript_lc_setflighttime(Plua_State L)
{
    LongInt lc_setflighttime_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str138, __str139))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->FlightTime = fpcrtl_trunc(lua_tonumber(L, 2));
        }
    }
    lc_setflighttime_result = 0;
    return lc_setflighttime_result;
};
LongInt uscript_lc_seteffect(Plua_State L)
{
    LongInt lc_seteffect_result;
    PGear gear;
    LongInt t;
    static const string255 callStr = STRINIT("SetEffect");
    static const string255 paramsStr = STRINIT("gearUid, effect, effectState");
    if(uscript_CheckLuaParamCount(L, 3, callStr, paramsStr))
    {
        t = uscript_LuaToHogEffectOrd(L, 2, callStr, paramsStr);
        if(t >= 0)
        {
            gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
            if((gear != NULL) && (gear->Hedgehog != NULL))
            {
                (*gear->Hedgehog).Effects[((THogEffect)t)] = fpcrtl_trunc(lua_tonumber(L, 3));
            }
        }
    }
    lc_seteffect_result = 0;
    return lc_seteffect_result;
};
LongInt uscript_lc_geteffect(Plua_State L)
{
    LongInt lc_geteffect_result;
    PGear gear;
    LongInt t;
    static const string255 callStr = STRINIT("GetEffect");
    static const string255 paramsStr = STRINIT("gearUid, effect");
    if(uscript_CheckLuaParamCount(L, 2, callStr, paramsStr))
    {
        t = uscript_LuaToHogEffectOrd(L, 2, callStr, paramsStr);
        if(t >= 0)
        {
            gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
            if((gear != NULL) && (gear->Hedgehog != NULL))
            {
                lua_pushnumber(L, (*gear->Hedgehog).Effects[((THogEffect)t)]);
            }
            else
            {
                lua_pushnumber(L, 0);
            }
        }
    }
    else
    {
        lua_pushnumber(L, 0);
    }
    lc_geteffect_result = 1;
    return lc_geteffect_result;
};
LongInt uscript_lc_setstate(Plua_State L)
{
    LongInt lc_setstate_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str140, __str141))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->State = fpcrtl_trunc(lua_tonumber(L, 2));
            ugearsutils_SetAllToActive();
        }
    }
    lc_setstate_result = 0;
    return lc_setstate_result;
};
LongInt uscript_lc_getstate(Plua_State L)
{
    LongInt lc_getstate_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str142, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->State);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getstate_result = 1;
    return lc_getstate_result;
};
LongInt uscript_lc_gettag(Plua_State L)
{
    LongInt lc_gettag_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str143, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->Tag);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gettag_result = 1;
    return lc_gettag_result;
};
LongInt uscript_lc_settag(Plua_State L)
{
    LongInt lc_settag_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str144, __str145))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->Tag = fpcrtl_trunc(lua_tonumber(L, 2));
            ugearsutils_SetAllToActive();
        }
    }
    lc_settag_result = 0;
    return lc_settag_result;
};
LongInt uscript_lc_endgame(Plua_State L)
{
    LongInt lc_endgame_result;
    UNUSED (L);
    GameOver = true;
    ugearslist_AddGear_7(0, 0, gtATFinishGame, 0, _0, _0, 3000);
    lc_endgame_result = 0;
    return lc_endgame_result;
};
LongInt uscript_lc_endturn(Plua_State L)
{
    LongInt lc_endturn_result;
    LongInt n;
    static const string255 callStr = STRINIT("EndTurn");
    static const string255 paramsStr = STRINIT("[noTaunts]");
    if(uscript_CheckAndFetchParamCount(L, 0, 1, callStr, paramsStr, &(n)))
    {
        if(n >= 1)
        {
            LuaNoEndTurnTaunts = lua_toboolean(L, 1);
        }
    }
    LuaEndTurnRequested = true;
    lc_endturn_result = 0;
    return lc_endturn_result;
};
LongInt uscript_lc_retreat(Plua_State L)
{
    LongInt lc_retreat_result;
    LongInt n;
    LongInt time;
    boolean respectFactor;
    static const string255 callStr = STRINIT("Retreat");
    static const string255 paramsStr = STRINIT("time [, respectGetAwayTimeFactor]");
    if(uscript_CheckAndFetchParamCount(L, 1, 2, callStr, paramsStr, &(n)))
    {
        IsGetAwayTime = true;
        AttackBar = 0;
        time = fpcrtl_trunc(lua_tonumber(L, 1));
        if(n == 2)
        {
            respectFactor = lua_toboolean(L, 2);
        }
        else
        {
            respectFactor = true;
        }
        if(respectFactor)
        {
            PendingTurnTimeLeft = (time * cGetAwayTime) / 100;
        }
        else
        {
            PendingTurnTimeLeft = time;
        }
        isPendingTurnTimeLeft = true;
        if((CurrentHedgehog != NULL) && (CurrentHedgehog->Gear != NULL))
        {
            (*CurrentHedgehog->Gear).State = (*CurrentHedgehog->Gear).State | gstAttacked;
            (*CurrentHedgehog->Gear).State = (*CurrentHedgehog->Gear).State & ~gstAttacking;
        }
    }
    lc_retreat_result = 0;
    return lc_retreat_result;
};
LongInt uscript_lc_skipturn(Plua_State L)
{
    LongInt lc_skipturn_result;
    UNUSED (L);
    ucommands_ParseCommand_3(__str146, true, true);
    lc_skipturn_result = 0;
    return lc_skipturn_result;
};
LongInt uscript_lc_sendstat(Plua_State L)
{
    LongInt lc_sendstat_result;
    TStatInfoType statInfo;
    LongInt i;
    LongInt n;
    string255 color;
    string255 tn;
    boolean needsTn;
    static const string255 callStr = STRINIT("SendStat");
    static const string255 paramsStr = STRINIT("statInfoType, color [, teamname]");
    if(uscript_CheckAndFetchParamCount(L, 2, 3, callStr, paramsStr, &(n)))
    {
        i = uscript_LuaToStatInfoTypeOrd(L, 1, callStr, paramsStr);
        if(i >= 0)
        {
            statInfo = ((TStatInfoType)i);
            needsTn = (statInfo == siPlayerKills) || (statInfo == siClanHealth);
            if((n == 3) != needsTn)
            {
                if(n == 3)
                {
                    uscript_LuaCallError(_strconcat(uutils_EnumToStr_1(statInfo), __str147), callStr, paramsStr);
                }
                else
                {
                    uscript_LuaCallError(_strconcat(uutils_EnumToStr_1(statInfo), __str148), callStr, paramsStr);
                }
            }
            else
            {
                if(needsTn)
                {
                    {i = 0;
                     LongInt i__end__ = ((int)(TeamsCount) - 1);
                     if (i <= i__end__) do {
                                               color = __str149;
                                               tn = luapas_lua_tostring(L, 3);
                                               {
                                                   if(_strcompare((*TeamsArray[i]).TeamName, tn))
                                                   {
                                                       color = uutils_IntToStr((*TeamsArray[i]).Clan->Color);
                                                       break;
                                                   }
                                               }
                                           } while(i++ != i__end__);}
                    if(statInfo == siPlayerKills)
                    {
                        uio_SendStat(siPlayerKills, _strconcat(_strappend(_strconcat(_strappend(color, 0x20), luapas_lua_tostring(L, 2)), 0x20), tn));
                    }
                    else
                    {
                        if(statInfo == siClanHealth)
                        {
                            uio_SendStat(siClanHealth, _strconcat(_strappend(color, 0x20), luapas_lua_tostring(L, 2)));
                        }
                    }
                }
                else
                {
                    uio_SendStat(statInfo, luapas_lua_tostring(L, 2));
                }
            }
        }
    }
    lc_sendstat_result = 0;
    return lc_sendstat_result;
};
LongInt uscript_lc_sendgameresultoff(Plua_State L)
{
    LongInt lc_sendgameresultoff_result;
    UNUSED (L);
    SendGameResultOn = false;
    lc_sendgameresultoff_result = 0;
    return lc_sendgameresultoff_result;
};
LongInt uscript_lc_sendrankingstatsoff(Plua_State L)
{
    LongInt lc_sendrankingstatsoff_result;
    UNUSED (L);
    SendRankingStatsOn = false;
    lc_sendrankingstatsoff_result = 0;
    return lc_sendrankingstatsoff_result;
};
LongInt uscript_lc_sendachievementsstatsoff(Plua_State L)
{
    LongInt lc_sendachievementsstatsoff_result;
    UNUSED (L);
    SendAchievementsStatsOn = false;
    lc_sendachievementsstatsoff_result = 0;
    return lc_sendachievementsstatsoff_result;
};
LongInt uscript_lc_sendhealthstatsoff(Plua_State L)
{
    LongInt lc_sendhealthstatsoff_result;
    UNUSED (L);
    SendHealthStatsOn = false;
    lc_sendhealthstatsoff_result = 0;
    return lc_sendhealthstatsoff_result;
};
LongInt uscript_lc_findplace(Plua_State L)
{
    LongInt lc_findplace_result;
    PGear gear;
    boolean fall;
    boolean tryhard;
    LongInt left;
    LongInt right;
    LongInt n;
    if(uscript_CheckAndFetchParamCount(L, 4, 5, __str150, __str151, &(n)))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        fall = lua_toboolean(L, 2);
        left = fpcrtl_trunc(lua_tonumber(L, 3));
        right = fpcrtl_trunc(lua_tonumber(L, 4));
        if(n == 5)
        {
            tryhard = lua_toboolean(L, 5);
        }
        else
        {
            tryhard = false;
        }
        if(gear != NULL)
        {
            ugearsutils_FindPlace_5(&(gear), fall, left, right, tryhard);
        }
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->uid);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_findplace_result = 1;
    return lc_findplace_result;
};
LongInt uscript_lc_playsound(Plua_State L)
{
    LongInt lc_playsound_result;
    PGear gear;
    LongInt n;
    LongInt s;
    boolean instaVoice;
    static const string255 callStr = STRINIT("PlaySound");
    static const string255 paramsStr = STRINIT("soundId [, hhGearUid [, instaVoice]]");
    if(uscript_CheckAndFetchParamCountRange(L, 1, 3, callStr, paramsStr, &(n)))
    {
        s = uscript_LuaToSoundOrd(L, 1, callStr, paramsStr);
        if(s >= 0)
        {
            if(n == 1)
            {
                usound_PlaySound_3(((TSound)s), false, true);
            }
            else
            {
                gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 2)));
                if(((gear != NULL) && (gear->Kind == gtHedgehog)) && (gear->Hedgehog != NULL))
                {
                    instaVoice = false;
                    if(n == 3)
                    {
                        instaVoice = lua_toboolean(L, 3);
                    }
                    if(instaVoice)
                    {
                        usound_PlaySoundV_4(((TSound)s), (*(*gear->Hedgehog).Team).voicepack, false, true);
                    }
                    else
                    {
                        usound_AddVoice_4(((TSound)s), (*(*gear->Hedgehog).Team).voicepack, true, false);
                    }
                }
            }
        }
    }
    lc_playsound_result = 0;
    return lc_playsound_result;
};
LongInt uscript_lc_playmusicsound(Plua_State L)
{
    LongInt lc_playmusicsound_result;
    LongInt s;
    static const string255 callStr = STRINIT("PlayMusicSound");
    static const string255 paramsStr = STRINIT("soundId");
    if(uscript_CheckLuaParamCount(L, 1, callStr, paramsStr))
    {
        s = uscript_LuaToSoundOrd(L, 1, callStr, paramsStr);
        if(s >= 0)
        {
            usound_PlayMusicSound(((TSound)s));
        }
    }
    lc_playmusicsound_result = 0;
    return lc_playmusicsound_result;
};
LongInt uscript_lc_stopmusicsound(Plua_State L)
{
    LongInt lc_stopmusicsound_result;
    LongInt s;
    static const string255 callStr = STRINIT("StopMusicSound");
    static const string255 paramsStr = STRINIT("soundId");
    if(uscript_CheckLuaParamCount(L, 1, callStr, paramsStr))
    {
        s = uscript_LuaToSoundOrd(L, 1, callStr, paramsStr);
        if(s >= 0)
        {
            usound_StopMusicSound(((TSound)s));
        }
    }
    lc_stopmusicsound_result = 0;
    return lc_stopmusicsound_result;
};
LongInt uscript_lc_setsoundmask(Plua_State L)
{
    LongInt lc_setsoundmask_result;
    LongInt s;
    boolean soundState;
    static const string255 callStr = STRINIT("SetSoundMask");
    static const string255 paramsStr = STRINIT("soundId, isMasked");
    if(uscript_CheckLuaParamCount(L, 2, callStr, paramsStr))
    {
        s = uscript_LuaToSoundOrd(L, 1, callStr, paramsStr);
        if(s != (sndNone))
        {
            soundState = lua_toboolean(L, 2);
            MaskedSounds[((TSound)s)] = soundState;
        }
    }
    lc_setsoundmask_result = 0;
    return lc_setsoundmask_result;
};
LongInt uscript_lc_addteam(Plua_State L)
{
    LongInt lc_addteam_result;
    LongInt np;
    Int64 colorArg;
    string255 colorStr;
    if(uscript_CheckAndFetchParamCount(L, 5, 6, __str152, __str153, &(np)))
    {
        colorArg = fpcrtl_trunc(lua_tonumber(L, 2));
        if((colorArg < 0) && (fpcrtl_abs(colorArg) <= cClanColors))
        {
            colorStr = uutils_IntToStr(ClanColorArray[((int)(fpcrtl_abs(colorArg)) - 1)]);
        }
        else
        {
            if((colorArg >= 0) && (colorArg <= 0xffffffff))
            {
                colorStr = uutils_IntToStr(colorArg);
            }
            else
            {
                udebug_OutError(_strconcat(_strconcat(__str154, uutils_IntToStr(-cClanColors)), __str108), true);
                lua_pushnil(L);
                lua_pushnil(L);
                lc_addteam_result = 2;
                return lc_addteam_result;
            }
        }
        ucommands_ParseCommand_3(_strconcat(_strappend(_strconcat(__str155, colorStr), 0x20), luapas_lua_tostring(L, 1)), true, true);
        ucommands_ParseCommand_3(_strconcat(__str156, luapas_lua_tostring(L, 3)), true, true);
        ucommands_ParseCommand_3(_strconcat(__str157, luapas_lua_tostring(L, 4)), true, true);
        ucommands_ParseCommand_3(_strconcat(__str158, luapas_lua_tostring(L, 5)), true, true);
        if(np == 6)
        {
            ucommands_ParseCommand_3(_strconcat(__str159, luapas_lua_tostring(L, 6)), true, true);
        }
        if(MissionTeam != NULL)
        {
            CurrentTeam->Binds = MissionTeam->Binds;
        }
        else
        {
            CurrentTeam->Binds = DefaultBinds;
        }
        lua_pushstring(L, uutils_Str2PChar(CurrentTeam->TeamName));
        lua_pushnumber(L, TeamsCount - 1);
    }
    else
    {
        lua_pushnil(L);
        lua_pushnil(L);
    }
    lc_addteam_result = 2;
    return lc_addteam_result;
};
LongInt uscript_lc_addmissionteam(Plua_State L)
{
    LongInt lc_addmissionteam_result;
    Int64 colorArg;
    string255 colorStr;
    if(uscript_CheckLuaParamCount(L, 1, __str160, __str161))
    {
        if(MissionTeam == NULL)
        {
            udebug_OutError(__str162, true);
            lc_addmissionteam_result = 0;
            return lc_addmissionteam_result;
        }
        colorArg = fpcrtl_trunc(lua_tonumber(L, 1));
        if((colorArg < 0) && (fpcrtl_abs(colorArg) <= cClanColors))
        {
            colorStr = uutils_IntToStr(ClanColorArray[((int)(fpcrtl_abs(colorArg)) - 1)]);
        }
        else
        {
            if((colorArg >= 0) && (colorArg <= 0xffffffff))
            {
                colorStr = uutils_IntToStr(colorArg);
            }
            else
            {
                udebug_OutError(_strconcat(_strconcat(__str163, uutils_IntToStr(-cClanColors)), __str108), true);
                lua_pushnil(L);
                lua_pushnil(L);
                lc_addmissionteam_result = 2;
                return lc_addmissionteam_result;
            }
        }
        ucommands_ParseCommand_3(_strconcat(_strappend(_strconcat(__str155, colorStr), 0x20), MissionTeam->TeamName), true, true);
        ucommands_ParseCommand_3(_strconcat(__str156, MissionTeam->GraveName), true, true);
        ucommands_ParseCommand_3(_strconcat(__str157, MissionTeam->FortName), true, true);
        ucommands_ParseCommand_3(_strconcat(__str158, (*MissionTeam->voicepack).name), true, true);
        ucommands_ParseCommand_3(_strconcat(__str159, MissionTeam->Flag), true, true);
        CurrentTeam->Binds = MissionTeam->Binds;
        lua_pushstring(L, uutils_Str2PChar(CurrentTeam->TeamName));
        lua_pushnumber(L, TeamsCount - 1);
    }
    else
    {
        lua_pushnil(L);
        lua_pushnil(L);
    }
    lc_addmissionteam_result = 2;
    return lc_addmissionteam_result;
};
LongInt uscript_lc_setteamlabel(Plua_State L)
{
    LongInt lc_setteamlabel_result;
    astring teamValue;
    LongInt i;
    LongInt n;
    boolean success;
    success = false;
    if(uscript_CheckAndFetchParamCount(L, 1, 2, __str164, __str165, &(n)))
    {
        success = false;
        if(TeamsCount > 0)
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       if(_strncompare(TeamsArray[i]->TeamName, luapas_lua_tostring(L, 1)))
                                       {
                                           continue;
                                       }
                                       if((n < 2) || luapas_lua_isnil(L, 2))
                                       {
                                           utextures_FreeAndNilTexture(&(TeamsArray[i]->LuaTeamValueTex));
                                           TeamsArray[i]->hasLuaTeamValue = false;
                                           success = true;
                                       }
                                       else
                                       {
                                           if(lua_isstring(L, 2))
                                           {
                                               teamValue = fpcrtl_str2astr(luapas_lua_tostring(L, 2));
                                               TeamsArray[i]->luaTeamValue = teamValue;
                                               utextures_FreeAndNilTexture(&(TeamsArray[i]->LuaTeamValueTex));
                                               TeamsArray[i]->LuaTeamValueTex = urenderutils_RenderStringTex(teamValue, (*TeamsArray[i]->Clan).Color, fnt16);
                                               TeamsArray[i]->hasLuaTeamValue = true;
                                               success = true;
                                           }
                                       }
                                       break;
                                   } while(i++ != i__end__);}
        }
    }
    lua_pushboolean(L, success);
    lc_setteamlabel_result = 1;
    return lc_setteamlabel_result;
};
LongInt uscript_lc_setteampassive(Plua_State L)
{
    LongInt lc_setteampassive_result;
    LongInt i;
    LongInt j;
    boolean success;
    boolean passive;
    boolean passiveClan;
    success = false;
    if(uscript_CheckLuaParamCount(L, 2, __str166, __str167))
    {
        success = false;
        if(TeamsCount > 0)
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       if(_strcompare(TeamsArray[i]->TeamName, luapas_lua_tostring(L, 1)))
                                       {
                                           passive = lua_toboolean(L, 2);
                                           TeamsArray[i]->Passive = passive;
                                           if(passive)
                                           {
                                               passiveClan = true;
                                               {j = 0;
                                                LongInt j__end__ = ((int)(TeamsCount) - 1);
                                                if (j <= j__end__) do {
                                                                          if(!TeamsArray[j]->Passive)
                                                                          {
                                                                              passiveClan = false;
                                                                              break;
                                                                          }
                                                                      } while(j++ != j__end__);}
                                           }
                                           else
                                           {
                                               passiveClan = false;
                                           }
                                           (*TeamsArray[i]->Clan).Passive = passiveClan;
                                           success = true;
                                           break;
                                       }
                                   } while(i++ != i__end__);}
        }
    }
    lua_pushboolean(L, success);
    lc_setteampassive_result = 1;
    return lc_setteampassive_result;
};
LongInt uscript_lc_getteamname(Plua_State L)
{
    LongInt lc_getteamname_result;
    LongInt t;
    if(uscript_CheckLuaParamCount(L, 1, __str168, __str169))
    {
        t = fpcrtl_trunc(lua_tonumber(L, 1));
        if((t < 0) || (t >= TeamsCount))
        {
            lua_pushnil(L);
        }
        else
        {
            lua_pushstring(L, uutils_Str2PChar(TeamsArray[t]->TeamName));
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getteamname_result = 1;
    return lc_getteamname_result;
};
LongInt uscript_lc_getteamindex(Plua_State L)
{
    LongInt lc_getteamindex_result;
    LongInt i;
    boolean found;
    found = false;
    if(uscript_CheckLuaParamCount(L, 1, __str170, __str171))
    {
        if(TeamsCount > 0)
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       if(_strncompare(TeamsArray[i]->TeamName, luapas_lua_tostring(L, 1)))
                                       {
                                           continue;
                                       }
                                       lua_pushnumber(L, i);
                                       found = true;
                                       break;
                                   } while(i++ != i__end__);}
        }
    }
    if(!found)
    {
        lua_pushnil(L);
    }
    lc_getteamindex_result = 1;
    return lc_getteamindex_result;
};
LongInt uscript_lc_getteamclan(Plua_State L)
{
    LongInt lc_getteamclan_result;
    LongInt i;
    boolean found;
    found = false;
    if(uscript_CheckLuaParamCount(L, 1, __str172, __str171))
    {
        if(TeamsCount > 0)
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       if(_strncompare(TeamsArray[i]->TeamName, luapas_lua_tostring(L, 1)))
                                       {
                                           continue;
                                       }
                                       lua_pushnumber(L, (*TeamsArray[i]->Clan).ClanIndex);
                                       found = true;
                                       break;
                                   } while(i++ != i__end__);}
        }
    }
    if(!found)
    {
        lua_pushnil(L);
    }
    lc_getteamclan_result = 1;
    return lc_getteamclan_result;
};
LongInt uscript_lc_dismissteam(Plua_State L)
{
    LongInt lc_dismissteam_result;
    PGear HHGear;
    LongInt i;
    LongInt h;
    boolean hidden;
    if(uscript_CheckLuaParamCount(L, 1, __str173, __str171))
    {
        if(TeamsCount > 0)
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       if(_strncompare(TeamsArray[i]->TeamName, luapas_lua_tostring(L, 1)))
                                       {
                                           continue;
                                       }
                                       {h = 0;
                                        LongInt h__end__ = cMaxHHIndex;
                                        if (h <= h__end__) do {
                                                                  hidden = TeamsArray[i]->Hedgehogs[h].GearHidden != NULL;
                                                                  if(hidden)
                                                                  {
                                                                      uteams_RestoreHog(&(TeamsArray[i]->Hedgehogs[h]));
                                                                  }
                                                                  HHGear = TeamsArray[i]->Hedgehogs[h].Gear;
                                                                  if(HHGear != NULL)
                                                                  {
                                                                      if(!hidden)
                                                                      {
                                                                          uvisualgearslist_AddVisualGear_3(ufloat_hwRound(HHGear->X), ufloat_hwRound(HHGear->Y), vgtSmokeWhite);
                                                                          uvisualgearslist_AddVisualGear_3((ufloat_hwRound(HHGear->X) - 16) + fpcrtl_random(32), (ufloat_hwRound(HHGear->Y) - 16) + fpcrtl_random(32), vgtSmokeWhite);
                                                                          uvisualgearslist_AddVisualGear_3((ufloat_hwRound(HHGear->X) - 16) + fpcrtl_random(32), (ufloat_hwRound(HHGear->Y) - 16) + fpcrtl_random(32), vgtSmokeWhite);
                                                                          uvisualgearslist_AddVisualGear_3((ufloat_hwRound(HHGear->X) - 16) + fpcrtl_random(32), (ufloat_hwRound(HHGear->Y) - 16) + fpcrtl_random(32), vgtSmokeWhite);
                                                                          uvisualgearslist_AddVisualGear_3((ufloat_hwRound(HHGear->X) - 16) + fpcrtl_random(32), (ufloat_hwRound(HHGear->Y) - 16) + fpcrtl_random(32), vgtSmokeWhite);
                                                                      }
                                                                      HHGear->Message = HHGear->Message | gmDestroy;
                                                                      HHGear->Active = true;
                                                                      AllInactive = false;
                                                                  }
                                                              } while(h++ != h__end__);}
                                       break;
                                   } while(i++ != i__end__);}
        }
    }
    lc_dismissteam_result = 0;
    return lc_dismissteam_result;
};
LongInt uscript_lc_getteamstats(Plua_State L)
{
    LongInt lc_getteamstats_result;
    LongInt i;
    if(uscript_CheckLuaParamCount(L, 1, __str174, __str171))
    {
        if(TeamsCount > 0)
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       if(_strncompare(TeamsArray[i]->TeamName, luapas_lua_tostring(L, 1)))
                                       {
                                           continue;
                                       }
                                       luapas_lua_newtable(L);
                                       lua_pushstring(L, uutils_Str2PChar(__str175));
                                       lua_pushnumber(L, TeamsArray[i]->stats.Kills);
                                       lua_settable(L, -3);
                                       lua_pushstring(L, uutils_Str2PChar(__str176));
                                       lua_pushnumber(L, TeamsArray[i]->stats.Suicides);
                                       lua_settable(L, -3);
                                       lua_pushstring(L, uutils_Str2PChar(__str177));
                                       lua_pushnumber(L, TeamsArray[i]->stats.AIKills);
                                       lua_settable(L, -3);
                                       lua_pushstring(L, uutils_Str2PChar(__str178));
                                       lua_pushnumber(L, TeamsArray[i]->stats.TeamKills);
                                       lua_settable(L, -3);
                                       lua_pushstring(L, uutils_Str2PChar(__str179));
                                       lua_pushnumber(L, TeamsArray[i]->stats.TurnSkips);
                                       lua_settable(L, -3);
                                       lua_pushstring(L, uutils_Str2PChar(__str180));
                                       lua_pushnumber(L, TeamsArray[i]->stats.TeamDamage);
                                       lua_settable(L, -3);
                                   } while(i++ != i__end__);}
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getteamstats_result = 1;
    return lc_getteamstats_result;
};
LongInt uscript_lc_addhog(Plua_State L)
{
    LongInt lc_addhog_result;
    shortstring hatName;
    if(uscript_CheckLuaParamCount(L, 4, __str181, __str182))
    {
        hatName = luapas_lua_tostring(L, 4);
        ucommands_ParseCommand_3(_strconcat(_strappend(_strconcat(_strappend(_strconcat(__str183, luapas_lua_tostring(L, 2)), 0x20), luapas_lua_tostring(L, 3)), 0x20), luapas_lua_tostring(L, 1)), true, true);
        ucommands_ParseCommand_3(_strconcat(__str184, hatName), true, true);
        if((CurrentHedgehog != NULL) && (CurrentHedgehog->Gear != NULL))
        {
            lua_pushnumber(L, (*CurrentHedgehog->Gear).uid);
        }
        else
        {
            udebug_OutError(__str185, true);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_addhog_result = 1;
    return lc_addhog_result;
};
LongInt uscript_lc_addmissionhog(Plua_State L)
{
    LongInt lc_addmissionhog_result;
    shortstring hatName;
    if(uscript_CheckLuaParamCount(L, 1, __str186, __str187))
    {
        if(MissionTeam == NULL)
        {
            udebug_OutError(__str188, true);
            lua_pushnil(L);
            lc_addmissionhog_result = 1;
            return lc_addmissionhog_result;
        }
        {
            hatName = MissionTeam->Hedgehogs[CurrentTeam->HedgehogsNumber].Hat;
            ucommands_ParseCommand_3(_strconcat(_strappend(_strconcat(_strappend(_strconcat(__str183, uutils_IntToStr(MissionTeam->Hedgehogs[CurrentTeam->HedgehogsNumber].BotLevel)), 0x20), luapas_lua_tostring(L, 1)), 0x20), MissionTeam->Hedgehogs[CurrentTeam->HedgehogsNumber].Name), true, true);
            ucommands_ParseCommand_3(_strconcat(__str184, hatName), true, true);
        }
        if((CurrentHedgehog != NULL) && (CurrentHedgehog->Gear != NULL))
        {
            lua_pushnumber(L, (*CurrentHedgehog->Gear).uid);
        }
        else
        {
            udebug_OutError(__str189, true);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_addmissionhog_result = 1;
    return lc_addmissionhog_result;
};
LongInt uscript_lc_hogturnleft(Plua_State L)
{
    LongInt lc_hogturnleft_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str190, __str191))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->dX.isNegative = lua_toboolean(L, 2);
        }
    }
    lc_hogturnleft_result = 0;
    return lc_hogturnleft_result;
};
LongInt uscript_lc_getgearposition(Plua_State L)
{
    LongInt lc_getgearposition_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str192, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, ufloat_hwRound(gear->X));
            lua_pushnumber(L, ufloat_hwRound(gear->Y));
        }
        else
        {
            lua_pushnil(L);
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
        lua_pushnil(L);
    }
    lc_getgearposition_result = 2;
    return lc_getgearposition_result;
};
LongInt uscript_lc_setgearposition(Plua_State L)
{
    LongInt lc_setgearposition_result;
    PGear gear;
    boolean col;
    LongInt x;
    LongInt y;
    if(uscript_CheckLuaParamCount(L, 3, __str193, __str194))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            col = gear->CollisionIndex >= 0;
            x = fpcrtl_trunc(lua_tonumber(L, 2));
            y = fpcrtl_trunc(lua_tonumber(L, 3));
            if(col)
            {
                ucollisions_DeleteCI(gear);
            }
            gear->X = ufloat_int2hwFloat(x);
            gear->Y = ufloat_int2hwFloat(y);
            if(col)
            {
                ucollisions_AddCI(gear);
            }
            ugearsutils_SetAllToActive();
        }
    }
    lc_setgearposition_result = 0;
    return lc_setgearposition_result;
};
LongInt uscript_lc_getgeartarget(Plua_State L)
{
    LongInt lc_getgeartarget_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str195, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->Target.x);
            lua_pushnumber(L, gear->Target.y);
        }
        else
        {
            lua_pushnil(L);
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
        lua_pushnil(L);
    }
    lc_getgeartarget_result = 2;
    return lc_getgeartarget_result;
};
LongInt uscript_lc_setgeartarget(Plua_State L)
{
    LongInt lc_setgeartarget_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 3, __str196, __str194))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->Target.x = fpcrtl_trunc(lua_tonumber(L, 2));
            gear->Target.y = fpcrtl_trunc(lua_tonumber(L, 3));
        }
    }
    lc_setgeartarget_result = 0;
    return lc_setgeartarget_result;
};
LongInt uscript_lc_getgearvelocity(Plua_State L)
{
    LongInt lc_getgearvelocity_result;
    PGear gear;
    LongInt t;
    if(uscript_CheckLuaParamCount(L, 1, __str197, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            t = ufloat_hwRound(ufloat_hwFloat_LongInt_op_mul(gear->dX, 1000000));
            if(gear->dX.isNegative && (t == 0))
            {
                t = -1;
            }
            lua_pushnumber(L, t);
            lua_pushnumber(L, ufloat_hwRound(ufloat_hwFloat_LongInt_op_mul(gear->dY, 1000000)));
        }
    }
    else
    {
        lua_pushnil(L);
        lua_pushnil(L);
    }
    lc_getgearvelocity_result = 2;
    return lc_getgearvelocity_result;
};
LongInt uscript_lc_setgearvelocity(Plua_State L)
{
    LongInt lc_setgearvelocity_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 3, __str198, __str199))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->dX = ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(fpcrtl_trunc(lua_tonumber(L, 2))), 1000000);
            gear->dY = ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(fpcrtl_trunc(lua_tonumber(L, 3))), 1000000);
            ugearsutils_SetAllToActive();
        }
    }
    lc_setgearvelocity_result = 0;
    return lc_setgearvelocity_result;
};
LongInt uscript_lc_setzoom(Plua_State L)
{
    LongInt lc_setzoom_result;
    if(uscript_CheckLuaParamCount(L, 1, __str200, __str201))
    {
        ZoomValue = lua_tonumber(L, 1);
        if(ZoomValue < cMaxZoomLevel)
        {
            ZoomValue = cMaxZoomLevel;
        }
        if(ZoomValue > cMinZoomLevel)
        {
            ZoomValue = cMinZoomLevel;
        }
    }
    lc_setzoom_result = 0;
    return lc_setzoom_result;
};
LongInt uscript_lc_getzoom(Plua_State L)
{
    LongInt lc_getzoom_result;
    if(uscript_CheckLuaParamCount(L, 0, __str202, __str40))
    {
        lua_pushnumber(L, ZoomValue);
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getzoom_result = 1;
    return lc_getzoom_result;
};
LongInt uscript_lc_setammo(Plua_State L)
{
    LongInt lc_setammo_result;
    LongInt np;
    LongInt at;
    static const string255 callStr = STRINIT("SetAmmo");
    static const string255 paramsStr = STRINIT("ammoType, count, probability, delay [, numberInCrate]");
    if(uscript_CheckAndFetchParamCount(L, 4, 5, callStr, paramsStr, &(np)))
    {
        at = uscript_LuaToAmmoTypeOrd(L, 1, callStr, paramsStr);
        if(at >= 0)
        {
            if(np == 4)
            {
                uscript_ScriptSetAmmo_5(((TAmmoType)at), fpcrtl_trunc(lua_tonumber(L, 2)), fpcrtl_trunc(lua_tonumber(L, 3)), fpcrtl_trunc(lua_tonumber(L, 4)), 1);
            }
            else
            {
                uscript_ScriptSetAmmo_5(((TAmmoType)at), fpcrtl_trunc(lua_tonumber(L, 2)), fpcrtl_trunc(lua_tonumber(L, 3)), fpcrtl_trunc(lua_tonumber(L, 4)), fpcrtl_trunc(lua_tonumber(L, 5)));
            }
        }
    }
    lc_setammo_result = 0;
    return lc_setammo_result;
};
LongInt uscript_lc_getammo(Plua_State L)
{
    LongInt lc_getammo_result;
    LongInt i;
    LongInt at;
    LongInt rawProb;
    LongInt probLevel;
    static const string255 callStr = STRINIT("GetAmmo");
    static const string255 paramsStr = STRINIT("ammoType");
    lc_getammo_result = 0;
    if(uscript_CheckLuaParamCount(L, 1, callStr, paramsStr))
    {
        at = uscript_LuaToAmmoTypeOrd(L, 1, callStr, paramsStr);
        if(at >= 0)
        {
            i = InitialAmmoCounts[((TAmmoType)at)];
            if(i == AMMO_INFINITE)
            {
                i = 9;
            }
            lua_pushnumber(L, i);
            rawProb = Ammoz[((TAmmoType)at)].Probability;
            probLevel = -1;
            {i = 0;
             LongInt i__end__ = 8;
             if (i <= i__end__) do {
                                       if(rawProb == probabilityLevels[i])
                                       {
                                           probLevel = i;
                                       }
                                   } while(i++ != i__end__);}
            lua_pushnumber(L, probLevel);
            lua_pushnumber(L, Ammoz[((TAmmoType)at)].SkipTurns);
            lua_pushnumber(L, Ammoz[((TAmmoType)at)].NumberInCase);
            lc_getammo_result = 4;
        }
    }
    return lc_getammo_result;
};
LongInt uscript_lc_setammodelay(Plua_State L)
{
    LongInt lc_setammodelay_result;
    LongInt at;
    LongInt delay;
    static const string255 callStr = STRINIT("SetAmmoDelay");
    static const string255 paramsStr = STRINIT("ammoType, delay");
    if(uscript_CheckLuaParamCount(L, 2, callStr, paramsStr))
    {
        at = uscript_LuaToAmmoTypeOrd(L, 1, callStr, paramsStr);
        delay = fpcrtl_trunc(lua_tonumber(L, 2));
        if((at >= 0) && (((TAmmoType)at) != amNothing))
        {
            uscript_ScriptSetAmmoDelay_2(((TAmmoType)at), delay);
            if(((delay > 0) && (CurrentHedgehog != NULL)) && (CurrentHedgehog->CurAmmoType == ((TAmmoType)at)))
            {
                ucommands_ParseCommand_3(_strappend(__str48, ((char)0)), true, true);
            }
        }
    }
    lc_setammodelay_result = 0;
    return lc_setammodelay_result;
};
LongInt uscript_lc_setammoslot(Plua_State L)
{
    LongInt lc_setammoslot_result;
    LongInt at;
    LongInt slot;
    if(uscript_CheckLuaParamCount(L, 2, __str203, __str204))
    {
        at = fpcrtl_trunc(lua_tonumber(L, 1));
        slot = fpcrtl_trunc(lua_tonumber(L, 2));
        Ammoz[((TAmmoType)at)].Slot = slot - 1;
        AmmoMenuInvalidated = true;
    }
    lc_setammoslot_result = 0;
    return lc_setammoslot_result;
};
LongInt uscript_lc_getrandom(Plua_State L)
{
    LongInt lc_getrandom_result;
    LongInt m;
    if(uscript_CheckLuaParamCount(L, 1, __str205, __str206))
    {
        m = fpcrtl_trunc(lua_tonumber(L, 1));
        if(m > 0)
        {
            lua_pushnumber(L, urandom_GetRandom(m));
        }
        else
        {
            uscript_LuaError(__str207);
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getrandom_result = 1;
    return lc_getrandom_result;
};
LongInt uscript_lc_setwind(Plua_State L)
{
    LongInt lc_setwind_result;
    PVisualGear vg;
    if(uscript_CheckLuaParamCount(L, 1, __str208, __str209))
    {
        cWindSpeed = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(fpcrtl_trunc(lua_tonumber(L, 1))), 100), cMaxWindSpeed);
        cWindSpeedf = ufloat_SignAs(cWindSpeed, cWindSpeed).QWordValue /(float) ufloat_SignAs(_1, _1).QWordValue;
        if(cWindSpeed.isNegative)
        {
            cWindSpeedf = -cWindSpeedf;
        }
        vg = uvisualgearslist_AddVisualGear_3(0, 0, vgtSmoothWindBar);
        if(vg != NULL)
        {
            vg->dAngle = ufloat_hwFloat2Float(cWindSpeed);
        }
        uutils_AddFileLog(_strconcat(__str210, uutils_FloatToStr(cWindSpeed)));
    }
    lc_setwind_result = 0;
    return lc_setwind_result;
};
LongInt uscript_lc_getwind(Plua_State L)
{
    LongInt lc_getwind_result;
    extended wind;
    if(uscript_CheckLuaParamCount(L, 0, __str211, __str40))
    {
        wind = ufloat_hwFloat2Float(ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_div(cWindSpeed, cMaxWindSpeed), 100));
        if(wind < -100)
        {
            wind = -100;
        }
        else
        {
            if(wind > 100)
            {
                wind = 100;
            }
        }
        lua_pushnumber(L, wind);
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getwind_result = 1;
    return lc_getwind_result;
};
LongInt uscript_lc_maphasborder(Plua_State L)
{
    LongInt lc_maphasborder_result;
    if(uscript_CheckLuaParamCount(L, 0, __str212, __str40))
    {
        lua_pushboolean(L, hasBorder);
    }
    else
    {
        lua_pushnil(L);
    }
    lc_maphasborder_result = 1;
    return lc_maphasborder_result;
};
LongInt uscript_lc_getgearradius(Plua_State L)
{
    LongInt lc_getgearradius_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str213, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            lua_pushnumber(L, gear->Radius);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getgearradius_result = 1;
    return lc_getgearradius_result;
};
LongInt uscript_lc_gethoghat(Plua_State L)
{
    LongInt lc_gethoghat_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str214, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && ((gear->Kind == gtHedgehog) || (gear->Kind == gtGrave))) && (gear->Hedgehog != NULL))
        {
            lua_pushstring(L, uutils_Str2PChar((*gear->Hedgehog).Hat));
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_gethoghat_result = 1;
    return lc_gethoghat_result;
};
LongInt uscript_lc_sethoghat(Plua_State L)
{
    LongInt lc_sethoghat_result;
    PGear gear;
    shortstring hat;
    if(uscript_CheckLuaParamCount(L, 2, __str215, __str216))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && (gear->Kind == gtHedgehog)) && (gear->Hedgehog != NULL))
        {
            hat = luapas_lua_tostring(L, 2);
            (*gear->Hedgehog).Hat = hat;
            uutils_AddFileLog(_strconcat(__str217, hat));
            if(((fpcrtl_Length(hat) > 39) && (_strcompare(fpcrtl_copy(hat, 1, 8), __str218))) && (_strcompare(fpcrtl_copy(hat, 9, 32), (*(*gear->Hedgehog).Team).PlayerHash)))
            {
                ustore_LoadHedgehogHat(&((*gear->Hedgehog)), _strconcat(__str219, fpcrtl_copy(hat, 9, fpcrtl_Length(hat) - 8)));
            }
            else
            {
                ustore_LoadHedgehogHat(&((*gear->Hedgehog)), hat);
            }
        }
    }
    lc_sethoghat_result = 0;
    return lc_sethoghat_result;
};
LongInt uscript_lc_placesprite(Plua_State L)
{
    LongInt lc_placesprite_result;
    TSprite spr;
    Word lf;
    LongWord tint;
    LongInt i;
    LongInt n;
    boolean placed;
    boolean behind;
    boolean flipHoriz;
    boolean flipVert;
    static const string255 callStr = STRINIT("PlaceSprite");
    static const string255 paramsStr = STRINIT("x, y, sprite, frameIdx, tint, behind, flipHoriz, flipVert [, landFlag, ... ]");
    placed = false;
    if(uscript_CheckAndFetchLuaParamMinCount(L, 4, callStr, paramsStr, &(n)))
    {
        if(!luapas_lua_isnoneornil(L, 5))
        {
            tint = fpcrtl_trunc(lua_tonumber(L, 5));
        }
        else
        {
            tint = 0xffffffff;
        }
        if(!luapas_lua_isnoneornil(L, 6))
        {
            behind = lua_toboolean(L, 6);
        }
        else
        {
            behind = false;
        }
        if(!luapas_lua_isnoneornil(L, 7))
        {
            flipHoriz = lua_toboolean(L, 7);
        }
        else
        {
            flipHoriz = false;
        }
        if(!luapas_lua_isnoneornil(L, 8))
        {
            flipVert = lua_toboolean(L, 8);
        }
        else
        {
            flipVert = false;
        }
        lf = 0;
        {i = 9;
         LongInt i__end__ = n;
         if (i <= i__end__) do {
                                   lf = lf | fpcrtl_trunc(lua_tonumber(L, i));
                               } while(i++ != i__end__);}
        n = uscript_LuaToSpriteOrd(L, 3, callStr, paramsStr);
        if(n >= 0)
        {
            spr = ((TSprite)n);
            if(SpritesData[spr].Surface == NULL)
            {
                uscript_LuaError(_strconcat(_strconcat(_strconcat(callStr, __str9), uutils_EnumToStr_1(spr)), __str220));
            }
            else
            {
                placed = ulandgraphics_ForcePlaceOnLand(fpcrtl_trunc(lua_tonumber(L, 1)) - (SpritesData[spr].Width / 2), fpcrtl_trunc(lua_tonumber(L, 2)) - (SpritesData[spr].Height / 2), spr, fpcrtl_trunc(lua_tonumber(L, 4)), lf, tint, behind, flipHoriz, flipVert);
            }
        }
    }
    lua_pushboolean(L, placed);
    lc_placesprite_result = 1;
    return lc_placesprite_result;
};
LongInt uscript_lc_erasesprite(Plua_State L)
{
    LongInt lc_erasesprite_result;
    TSprite spr;
    Word lf;
    LongInt i;
    LongInt n;
    boolean eraseOnLFMatch;
    boolean onlyEraseLF;
    boolean flipHoriz;
    boolean flipVert;
    static const string255 callStr = STRINIT("EraseSprite");
    static const string255 paramsStr = STRINIT("x, y, sprite, frameIdx, eraseOnLFMatch, onlyEraseLF, flipHoriz, flipVert [, landFlag, ... ]");
    if(uscript_CheckAndFetchLuaParamMinCount(L, 4, callStr, paramsStr, &(n)))
    {
        if(!luapas_lua_isnoneornil(L, 5))
        {
            eraseOnLFMatch = lua_toboolean(L, 5);
        }
        else
        {
            eraseOnLFMatch = false;
        }
        if(!luapas_lua_isnoneornil(L, 6))
        {
            onlyEraseLF = lua_toboolean(L, 6);
        }
        else
        {
            onlyEraseLF = false;
        }
        if(!luapas_lua_isnoneornil(L, 7))
        {
            flipHoriz = lua_toboolean(L, 7);
        }
        else
        {
            flipHoriz = false;
        }
        if(!luapas_lua_isnoneornil(L, 8))
        {
            flipVert = lua_toboolean(L, 8);
        }
        else
        {
            flipVert = false;
        }
        lf = 0;
        {i = 9;
         LongInt i__end__ = n;
         if (i <= i__end__) do {
                                   lf = lf | fpcrtl_trunc(lua_tonumber(L, i));
                               } while(i++ != i__end__);}
        n = uscript_LuaToSpriteOrd(L, 3, callStr, paramsStr);
        if(n >= 0)
        {
            spr = ((TSprite)n);
            if(SpritesData[spr].Surface == NULL)
            {
                uscript_LuaError(_strconcat(_strconcat(_strconcat(callStr, __str9), uutils_EnumToStr_1(spr)), __str220));
            }
            else
            {
                ulandgraphics_EraseLand(fpcrtl_trunc(lua_tonumber(L, 1)) - (SpritesData[spr].Width / 2), fpcrtl_trunc(lua_tonumber(L, 2)) - (SpritesData[spr].Height / 2), spr, fpcrtl_trunc(lua_tonumber(L, 4)), lf, eraseOnLFMatch, onlyEraseLF, flipHoriz, flipVert);
            }
        }
    }
    lc_erasesprite_result = 0;
    return lc_erasesprite_result;
};
LongInt uscript_lc_placegirder(Plua_State L)
{
    LongInt lc_placegirder_result;
    boolean placed;
    placed = false;
    if(uscript_CheckLuaParamCount(L, 3, __str221, __str222))
    {
        placed = ulandgraphics_TryPlaceOnLandSimple(fpcrtl_trunc(lua_tonumber(L, 1)) - (SpritesData[sprAmGirder].Width / 2), fpcrtl_trunc(lua_tonumber(L, 2)) - (SpritesData[sprAmGirder].Height / 2), sprAmGirder, fpcrtl_trunc(lua_tonumber(L, 3)), true, false);
    }
    lua_pushboolean(L, placed);
    lc_placegirder_result = 1;
    return lc_placegirder_result;
};
LongInt uscript_lc_placerubber(Plua_State L)
{
    LongInt lc_placerubber_result;
    boolean placed;
    placed = false;
    if(uscript_CheckLuaParamCount(L, 3, __str223, __str222))
    {
        placed = ulandgraphics_TryPlaceOnLand_6(fpcrtl_trunc(lua_tonumber(L, 1)) - (SpritesData[sprAmRubber].Width / 2), fpcrtl_trunc(lua_tonumber(L, 2)) - (SpritesData[sprAmRubber].Height / 2), sprAmRubber, fpcrtl_trunc(lua_tonumber(L, 3)), true, lfBouncy);
    }
    lua_pushboolean(L, placed);
    lc_placerubber_result = 1;
    return lc_placerubber_result;
};
LongInt uscript_lc_getcurammotype(Plua_State L)
{
    LongInt lc_getcurammotype_result;
    if((CurrentHedgehog != NULL) && uscript_CheckLuaParamCount(L, 0, __str224, __str40))
    {
        lua_pushnumber(L, (CurrentHedgehog->CurAmmoType));
    }
    else
    {
        lua_pushnumber(L, (amNothing));
    }
    lc_getcurammotype_result = 1;
    return lc_getcurammotype_result;
};
LongInt uscript_lc_savecampaignvar(Plua_State L)
{
    LongInt lc_savecampaignvar_result;
    if(uscript_CheckLuaParamCount(L, 2, __str225, __str226))
    {
        uio_SendIPC(_strappend(_strconcat(_strappend(_strconcat(__str227, luapas_lua_tostring(L, 1)), 0x20), luapas_lua_tostring(L, 2)), 0x0));
    }
    lc_savecampaignvar_result = 0;
    return lc_savecampaignvar_result;
};
LongInt uscript_lc_getcampaignvar(Plua_State L)
{
    LongInt lc_getcampaignvar_result;
    if(uscript_CheckLuaParamCount(L, 1, __str228, __str229))
    {
        uio_SendIPCAndWaitReply(_strappend(_strconcat(__str230, luapas_lua_tostring(L, 1)), 0x0));
    }
    lua_pushstring(L, uutils_Str2PChar(CampaignVariable));
    lc_getcampaignvar_result = 1;
    return lc_getcampaignvar_result;
};
LongInt uscript_lc_savemissionvar(Plua_State L)
{
    LongInt lc_savemissionvar_result;
    if(uscript_CheckLuaParamCount(L, 2, __str231, __str226))
    {
        uio_SendIPC(_strappend(_strconcat(_strappend(_strconcat(__str232, luapas_lua_tostring(L, 1)), 0x20), luapas_lua_tostring(L, 2)), 0x0));
    }
    lc_savemissionvar_result = 0;
    return lc_savemissionvar_result;
};
LongInt uscript_lc_getmissionvar(Plua_State L)
{
    LongInt lc_getmissionvar_result;
    if(uscript_CheckLuaParamCount(L, 1, __str233, __str229))
    {
        uio_SendIPCAndWaitReply(_strappend(_strconcat(__str234, luapas_lua_tostring(L, 1)), 0x0));
    }
    lua_pushstring(L, uutils_Str2PChar(MissionVariable));
    lc_getmissionvar_result = 1;
    return lc_getmissionvar_result;
};
LongInt uscript_lc_hidehog(Plua_State L)
{
    LongInt lc_hidehog_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str235, __str73))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(((gear != NULL) && (gear->Hedgehog != NULL)) && ((*gear->Hedgehog).Gear != NULL))
        {
            ugearshandlersmess_HideHog(gear->Hedgehog);
            lua_pushboolean(L, true);
        }
        else
        {
            lua_pushboolean(L, false);
        }
    }
    lc_hidehog_result = 1;
    return lc_hidehog_result;
};
LongInt uscript_lc_restorehog(Plua_State L)
{
    LongInt lc_restorehog_result;
    LongInt i;
    LongInt h;
    LongWord uid;
    if(uscript_CheckLuaParamCount(L, 1, __str236, __str73))
    {
        uid = ((LongWord)fpcrtl_trunc(lua_tonumber(L, 1)));
        if(TeamsCount > 0)
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       {h = 0;
                                        LongInt h__end__ = cMaxHHIndex;
                                        if (h <= h__end__) do {
                                                                  if((TeamsArray[i]->Hedgehogs[h].GearHidden != NULL) && ((*TeamsArray[i]->Hedgehogs[h].GearHidden).uid == uid))
                                                                  {
                                                                      uteams_RestoreHog(&(TeamsArray[i]->Hedgehogs[h]));
                                                                      return 0;
                                                                  }
                                                              } while(h++ != h__end__);}
                                   } while(i++ != i__end__);}
        }
    }
    lc_restorehog_result = 0;
    return lc_restorehog_result;
};
LongInt uscript_lc_ishoghidden(Plua_State L)
{
    LongInt lc_ishoghidden_result;
    LongInt i;
    LongInt h;
    LongWord uid;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 1, __str237, __str73))
    {
        uid = ((LongWord)fpcrtl_trunc(lua_tonumber(L, 1)));
        gear = ugears_GearByUID(uid);
        if((gear != NULL) && (gear->Hedgehog != NULL))
        {
            lua_pushboolean(L, false);
            lc_ishoghidden_result = 1;
            return lc_ishoghidden_result;
        }
        else
        {
            if(TeamsCount > 0)
            {
                {i = 0;
                 LongInt i__end__ = ((int)(TeamsCount) - 1);
                 if (i <= i__end__) do {
                                           {h = 0;
                                            LongInt h__end__ = cMaxHHIndex;
                                            if (h <= h__end__) do {
                                                                      if((TeamsArray[i]->Hedgehogs[h].GearHidden != NULL) && ((*TeamsArray[i]->Hedgehogs[h].GearHidden).uid == uid))
                                                                      {
                                                                          lua_pushboolean(L, true);
                                                                          lc_ishoghidden_result = 1;
                                                                          return lc_ishoghidden_result;
                                                                      }
                                                                  } while(h++ != h__end__);}
                                       } while(i++ != i__end__);}
            }
        }
    }
    lua_pushnil(L);
    lc_ishoghidden_result = 1;
    return lc_ishoghidden_result;
};
LongInt uscript_lc_testrectforobstacle(Plua_State L)
{
    LongInt lc_testrectforobstacle_result;
    boolean rtn;
    if(uscript_CheckLuaParamCount(L, 5, __str238, __str239))
    {
        rtn = ucollisions_TestRectangleForObstacle(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), fpcrtl_trunc(lua_tonumber(L, 3)), fpcrtl_trunc(lua_tonumber(L, 4)), lua_toboolean(L, 5));
        lua_pushboolean(L, rtn);
    }
    else
    {
        lua_pushnil(L);
    }
    lc_testrectforobstacle_result = 1;
    return lc_testrectforobstacle_result;
};
LongInt uscript_lc_getgravity(Plua_State L)
{
    LongInt lc_getgravity_result;
    if(uscript_CheckLuaParamCount(L, 0, __str240, __str40))
    {
        lua_pushnumber(L, ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_SignAs(_0_5, cGravity), ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_LongInt_op_mul(cGravity, 50), cMaxWindSpeed))));
    }
    lc_getgravity_result = 1;
    return lc_getgravity_result;
};
LongInt uscript_lc_setgravity(Plua_State L)
{
    LongInt lc_setgravity_result;
    if(uscript_CheckLuaParamCount(L, 1, __str241, __str242))
    {
        cGravity = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(_0_02, fpcrtl_trunc(lua_tonumber(L, 1))), cMaxWindSpeed);
        cGravityf = (2.5e-4 * fpcrtl_trunc(lua_tonumber(L, 1))) * 2.0e-2;
    }
    lc_setgravity_result = 0;
    return lc_setgravity_result;
};
LongInt uscript_lc_setwaterline(Plua_State L)
{
    LongInt lc_setwaterline_result;
    PGear iterator;
    if(uscript_CheckLuaParamCount(L, 1, __str243, __str244))
    {
        cWaterLine = fpcrtl_trunc(lua_tonumber(L, 1));
        AllInactive = false;
        iterator = GearsList;
        while(iterator != NULL)
        {
            if(!(((iterator->Kind == gtPortal) || (iterator->Kind == gtAirAttack))) && ((iterator->Message & ((gmAllStoppable | gmLJump) | gmHJump)) == 0))
            {
                iterator->Active = true;
                if(iterator->dY.QWordValue == 0)
                {
                    iterator->dY.isNegative = false;
                }
                iterator->State = iterator->State | gstMoving;
                ucollisions_DeleteCI(iterator);
            }
            iterator = iterator->NextGear;
        }
    }
    lc_setwaterline_result = 0;
    return lc_setwaterline_result;
};
LongInt uscript_lc_setgearaihints(Plua_State L)
{
    LongInt lc_setgearaihints_result;
    PGear gear;
    if(uscript_CheckLuaParamCount(L, 2, __str245, __str246))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if(gear != NULL)
        {
            gear->AIHints = fpcrtl_trunc(lua_tonumber(L, 2));
        }
    }
    lc_setgearaihints_result = 0;
    return lc_setgearaihints_result;
};
LongInt uscript_lc_hedgewarsscriptload(Plua_State L)
{
    LongInt lc_hedgewarsscriptload_result;
    boolean success;
    LongInt n;
    success = false;
    if(uscript_CheckAndFetchParamCount(L, 1, 2, __str247, __str248, &(n)))
    {
        if(n == 1)
        {
            success = uscript_ScriptLoad(luapas_lua_tostring(L, 1), true);
        }
        else
        {
            success = uscript_ScriptLoad(luapas_lua_tostring(L, 1), lua_toboolean(L, 2));
        }
    }
    else
    {
        success = false;
    }
    lua_pushboolean(L, success);
    lc_hedgewarsscriptload_result = 1;
    return lc_hedgewarsscriptload_result;
};
LongInt uscript_lc_declareachievement(Plua_State L)
{
    LongInt lc_declareachievement_result;
    if(uscript_CheckLuaParamCount(L, 4, __str249, __str250))
    {
        ustats_declareAchievement(luapas_lua_tostring(L, 1), luapas_lua_tostring(L, 2), luapas_lua_tostring(L, 3), fpcrtl_trunc(lua_tonumber(L, 4)));
    }
    lc_declareachievement_result = 0;
    return lc_declareachievement_result;
};
LongInt uscript_lc_getammoname(Plua_State L)
{
    LongInt lc_getammoname_result;
    LongInt np;
    LongInt at;
    boolean ignoreOverwrite;
    static const string255 callStr = STRINIT("GetAmmoName");
    static const string255 paramsStr = STRINIT("ammoType [, ignoreOverwrite ]");
    if(uscript_CheckAndFetchParamCountRange(L, 1, 2, callStr, paramsStr, &(np)))
    {
        at = uscript_LuaToAmmoTypeOrd(L, 1, callStr, paramsStr);
        ignoreOverwrite = false;
        if(np > 1)
        {
            ignoreOverwrite = lua_toboolean(L, 2);
        }
        if(at >= 0)
        {
            if(!ignoreOverwrite && (fpcrtl_LengthA(trluaammo[Ammoz[((TAmmoType)at)].NameId]) > 0))
            {
                lua_pushstring(L, fpcrtl__pcharA(trluaammo[Ammoz[((TAmmoType)at)].NameId]));
            }
            else
            {
                lua_pushstring(L, fpcrtl__pcharA(trammo[Ammoz[((TAmmoType)at)].NameId]));
            }
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getammoname_result = 1;
    return lc_getammoname_result;
};
LongInt uscript_lc_getammotimer(Plua_State L)
{
    LongInt lc_getammotimer_result;
    LongInt at;
    PAmmo weapon;
    PGear gear;
    static const string255 callStr = STRINIT("GetAmmoTimer");
    static const string255 paramsStr = STRINIT("gearUid, ammoType");
    if(uscript_CheckLuaParamCount(L, 2, callStr, paramsStr))
    {
        gear = ugears_GearByUID(fpcrtl_trunc(lua_tonumber(L, 1)));
        if((gear != NULL) && (gear->Hedgehog != NULL))
        {
            at = uscript_LuaToAmmoTypeOrd(L, 2, callStr, paramsStr);
            weapon = uammos_GetAmmoEntry(&((*gear->Hedgehog)), ((TAmmoType)at));
            if((Ammoz[((TAmmoType)at)].Ammo.Propz & ammoprop_Timerable) != 0)
            {
                lua_pushnumber(L, weapon->Timer);
            }
            else
            {
                lua_pushnil(L);
            }
        }
        else
        {
            lua_pushnil(L);
        }
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getammotimer_result = 1;
    return lc_getammotimer_result;
};
LongInt uscript_lc_setvampiric(Plua_State L)
{
    LongInt lc_setvampiric_result;
    if(uscript_CheckLuaParamCount(L, 1, __str251, __str252))
    {
        cVampiric = lua_toboolean(L, 1);
    }
    lc_setvampiric_result = 0;
    return lc_setvampiric_result;
};
LongInt uscript_lc_getvampiric(Plua_State L)
{
    LongInt lc_getvampiric_result;
    lua_pushboolean(L, cVampiric);
    lc_getvampiric_result = 1;
    return lc_getvampiric_result;
};
LongInt uscript_lc_setlasersight(Plua_State L)
{
    LongInt lc_setlasersight_result;
    if(uscript_CheckLuaParamCount(L, 1, __str253, __str252))
    {
        cLaserSighting = lua_toboolean(L, 1);
    }
    lc_setlasersight_result = 0;
    return lc_setlasersight_result;
};
LongInt uscript_lc_getlasersight(Plua_State L)
{
    LongInt lc_getlasersight_result;
    lua_pushboolean(L, cLaserSighting);
    lc_getlasersight_result = 1;
    return lc_getlasersight_result;
};
LongInt uscript_lc_explode(Plua_State L)
{
    LongInt lc_explode_result;
    LongWord mask;
    LongInt n;
    if(uscript_CheckAndFetchParamCount(L, 3, 4, __str254, __str255, &(n)))
    {
        if(CurrentHedgehog != NULL)
        {
            mask = EXPLAutoSound;
            if(n == 4)
            {
                mask = fpcrtl_trunc(lua_tonumber(L, 4));
            }
            ugearsutils_doMakeExplosion_5(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)), fpcrtl_trunc(lua_tonumber(L, 3)), CurrentHedgehog, mask);
            lua_pushboolean(L, true);
        }
        else
        {
            lua_pushboolean(L, false);
        }
    }
    else
    {
        lua_pushboolean(L, false);
    }
    lc_explode_result = 1;
    return lc_explode_result;
};
LongInt uscript_lc_setturntimeleft(Plua_State L)
{
    LongInt lc_setturntimeleft_result;
    Int64 number;
    if(uscript_CheckLuaParamCount(L, 1, __str256, __str257))
    {
        number = fpcrtl_trunc(lua_tonumber(L, 1));
        if(number < 0)
        {
            number = 0;
        }
        if(number > cMaxTurnTime)
        {
            number = cMaxTurnTime;
        }
        PendingTurnTimeLeft = number;
        isPendingTurnTimeLeft = true;
    }
    lc_setturntimeleft_result = 0;
    return lc_setturntimeleft_result;
};
LongInt uscript_lc_setreadytimeleft(Plua_State L)
{
    LongInt lc_setreadytimeleft_result;
    Int64 number;
    if(uscript_CheckLuaParamCount(L, 1, __str258, __str259))
    {
        number = fpcrtl_trunc(lua_tonumber(L, 1));
        if(number < 0)
        {
            number = 0;
        }
        if(number > cMaxTurnTime)
        {
            number = cMaxTurnTime;
        }
        PendingReadyTimeLeft = number;
        isPendingReadyTimeLeft = true;
    }
    lc_setreadytimeleft_result = 0;
    return lc_setreadytimeleft_result;
};
LongInt uscript_lc_setturntimepaused(Plua_State L)
{
    LongInt lc_setturntimepaused_result;
    if(uscript_CheckLuaParamCount(L, 1, __str260, __str261))
    {
        LuaClockPaused = lua_toboolean(L, 1);
    }
    lc_setturntimepaused_result = 0;
    return lc_setturntimepaused_result;
};
LongInt uscript_lc_getturntimepaused(Plua_State L)
{
    LongInt lc_getturntimepaused_result;
    if(uscript_CheckLuaParamCount(L, 0, __str262, __str40))
    {
        lua_pushboolean(L, LuaClockPaused);
    }
    else
    {
        lua_pushnil(L);
    }
    lc_getturntimepaused_result = 1;
    return lc_getturntimepaused_result;
};
LongInt uscript_lc_startghostpoints(Plua_State L)
{
    LongInt lc_startghostpoints_result;
    if(uscript_CheckLuaParamCount(L, 1, __str263, __str264))
    {
        ustats_startGhostPoints(fpcrtl_trunc(lua_tonumber(L, 1)));
    }
    lc_startghostpoints_result = 0;
    return lc_startghostpoints_result;
};
LongInt uscript_lc_dumppoint(Plua_State L)
{
    LongInt lc_dumppoint_result;
    if(uscript_CheckLuaParamCount(L, 2, __str265, __str266))
    {
        ustats_dumpPoint(fpcrtl_trunc(lua_tonumber(L, 1)), fpcrtl_trunc(lua_tonumber(L, 2)));
    }
    lc_dumppoint_result = 0;
    return lc_dumppoint_result;
};
void uscript_ScriptFlushPoints()
{
    ucommands_ParseCommand_3(_strconcat(__str267, PointsBuffer), true, true);
    PointsBuffer = __str40;
};
LongInt uscript_lc_addPoint(Plua_State L)
{
    LongInt lc_addpoint_result;
    LongInt np;
    LongInt param;
    if(uscript_CheckAndFetchParamCountRange(L, 2, 4, __str268, __str269, &(np)))
    {
        param = ((LongInt)fpcrtl_trunc(lua_tonumber(L, 1)));
        PointsBuffer = _strappend(PointsBuffer, ((char)(param >> 8) & 0xff));
        PointsBuffer = _strappend(PointsBuffer, ((char)param & 0xff));
        param = ((LongInt)fpcrtl_trunc(lua_tonumber(L, 2)));
        PointsBuffer = _strappend(PointsBuffer, ((char)(param >> 8) & 0xff));
        PointsBuffer = _strappend(PointsBuffer, ((char)param & 0xff));
        if(np > 2)
        {
            param = fpcrtl_trunc(lua_tonumber(L, 3));
            param = param | 0x80;
            if((np > 3) && lua_toboolean(L, 4))
            {
                param = param | 0x40;
            }
            PointsBuffer = _strappend(PointsBuffer, ((char)param));
        }
        else
        {
            PointsBuffer = _strappend(PointsBuffer, ((char)0));
        }
        if(fpcrtl_Length(PointsBuffer) > 245)
        {
            uscript_ScriptFlushPoints();
        }
    }
    lc_addpoint_result = 0;
    return lc_addpoint_result;
};
LongInt uscript_lc_flushPoints(Plua_State L)
{
    LongInt lc_flushpoints_result;
    if(uscript_CheckLuaParamCount(L, 0, __str270, __str40))
    {
        if(fpcrtl_Length(PointsBuffer) > 0)
        {
            uscript_ScriptFlushPoints();
        }
    }
    lc_flushpoints_result = 0;
    return lc_flushpoints_result;
};
LongInt uscript_lc_endluatest(Plua_State L)
{
    LongInt lc_endluatest_result;
    string255 rstring;
    static const string255 callStr = STRINIT("EndLuaTest");
    static const string255 paramsStr = STRINIT("TEST_SUCCESSFUL or TEST_FAILED");
    if(uscript_CheckLuaParamCount(L, 1, callStr, paramsStr))
    {
        switch(fpcrtl_trunc(lua_tonumber(L, 1)))
        {case HaltTestSuccess:rstring = __str271;
                              break;
         case HaltTestFailed:rstring = __str272;
                             break;
         default: {
                      uscript_LuaCallError(_strconcat(__str273, paramsStr), callStr, paramsStr);
                      return 0;
                  }}
        if(cTestLua)
        {
            uconsole_WriteLnToConsole(_strconcat(__str274, rstring));
            fpcrtl_halt(fpcrtl_trunc(lua_tonumber(L, 1)));
        }
        else
        {
            uscript_LuaError(_strconcat(__str275, rstring));
        }
    }
    lc_endluatest_result = 0;
    return lc_endluatest_result;
};
void uscript_ScriptPrintStack()
{
    LongInt n;
    LongInt i;
    n = lua_gettop(luaState);
    uconsole_WriteLnToConsole(_strconcat(_strconcat(__str276, uutils_IntToStr(n)), __str277));
    {i = 1;
     LongInt i__end__ = n;
     if (i <= i__end__) do {
                               if(!luapas_lua_isboolean(luaState, i))
                               {
                                   uconsole_WriteLnToConsole(_strconcat(_strconcat(_strconcat(__str278, uutils_IntToStr(i)), __str9), luapas_lua_tostring(luaState, i)));
                               }
                               else
                               {
                                   if(lua_toboolean(luaState, i))
                                   {
                                       uconsole_WriteLnToConsole(_strconcat(_strconcat(__str278, uutils_IntToStr(i)), __str279));
                                   }
                                   else
                                   {
                                       uconsole_WriteLnToConsole(_strconcat(_strconcat(__str278, uutils_IntToStr(i)), __str280));
                                   }
                               }
                           } while(i++ != i__end__);}
};
void uscript_ScriptClearStack()
{
    lua_settop(luaState, 0);
};
void uscript_ScriptSetNil(string255 name)
{
    lua_pushnil(luaState);
    luapas_lua_setglobal(luaState, uutils_Str2PChar(name));
};
void uscript_ScriptSetInteger(string255 name,LongInt value)
{
    lua_pushnumber(luaState, value);
    luapas_lua_setglobal(luaState, uutils_Str2PChar(name));
};
void uscript_ScriptSetLongWord(string255 name,LongWord value)
{
    lua_pushnumber(luaState, value);
    luapas_lua_setglobal(luaState, uutils_Str2PChar(name));
};
void uscript_ScriptSetString(string255 name,string255 value)
{
    lua_pushstring(luaState, uutils_Str2PChar(value));
    luapas_lua_setglobal(luaState, uutils_Str2PChar(name));
};
LongInt uscript_ScriptGetInteger(string255 name)
{
    LongInt scriptgetinteger_result;
    luapas_lua_getglobal(luaState, uutils_Str2PChar(name));
    scriptgetinteger_result = fpcrtl_trunc(lua_tonumber(luaState, -1));
    luapas_lua_pop(luaState, 1);
    return scriptgetinteger_result;
};
string255 uscript_ScriptGetString(string255 name)
{
    string255 scriptgetstring_result;
    luapas_lua_getglobal(luaState, uutils_Str2PChar(name));
    scriptgetstring_result = luapas_lua_tostring(luaState, -1);
    luapas_lua_pop(luaState, 1);
    return scriptgetstring_result;
};
astring uscript_ScriptGetAnsiString(string255 name)
{
    astring scriptgetansistring_result;
    luapas_lua_getglobal(luaState, uutils_Str2PChar(name));
    scriptgetansistring_result = luapas_lua_tostringA(luaState, -1);
    luapas_lua_pop(luaState, 1);
    return scriptgetansistring_result;
};
void uscript_ScriptOnPreviewInit()
{
    if(!ScriptLoaded)
    {
        return;
    }
    uscript_ScriptSetString(__str281, cSeed);
    uscript_ScriptSetInteger(__str282, cTemplateFilter);
    uscript_ScriptSetInteger(__str283, LuaTemplateNumber);
    uscript_ScriptSetInteger(__str284, (cMapGen));
    uscript_ScriptSetInteger(__str285, cFeatureSize);
    uscript_ScriptCall_1(__str286);
    ucommands_ParseCommand_3(_strconcat(__str287, uscript_ScriptGetString(__str281)), true, true);
    cTemplateFilter = uscript_ScriptGetInteger(__str282);
    LuaTemplateNumber = uscript_ScriptGetInteger(__str283);
    cMapGen = ((TMapGen)uscript_ScriptGetInteger(__str284));
    cFeatureSize = uscript_ScriptGetInteger(__str285);
};
void uscript_ScriptOnGameInit()
{
    LongInt i;
    LongInt j;
    LongInt k;
    if(!ScriptLoaded)
    {
        return;
    }
    uscript_ScriptSetInteger(__str288, NoPointX);
    uscript_ScriptSetInteger(__str289, NoPointX);
    uscript_ScriptSetInteger(__str57, GameFlags);
    uscript_ScriptSetInteger(__str290, (WorldEdge));
    uscript_ScriptSetString(__str281, cSeed);
    uscript_ScriptSetInteger(__str282, cTemplateFilter);
    uscript_ScriptSetInteger(__str283, LuaTemplateNumber);
    uscript_ScriptSetInteger(__str284, (cMapGen));
    uscript_ScriptSetInteger(__str285, cFeatureSize);
    uscript_ScriptSetInteger(__str291, cScreenHeight);
    uscript_ScriptSetInteger(__str292, cScreenWidth);
    uscript_ScriptSetInteger(__str293, cHedgehogTurnTime);
    uscript_ScriptSetInteger(__str294, cCaseFactor);
    uscript_ScriptSetInteger(__str295, cMaxCaseDrops);
    uscript_ScriptSetInteger(__str296, cHealthCaseProb);
    uscript_ScriptSetInteger(__str297, cHealthCaseAmount);
    uscript_ScriptSetInteger(__str298, cInitHealth);
    uscript_ScriptSetInteger(__str299, cDamagePercent);
    uscript_ScriptSetInteger(__str300, cRopePercent);
    uscript_ScriptSetInteger(__str301, cLandMines);
    uscript_ScriptSetInteger(__str302, cMinesTime);
    uscript_ScriptSetInteger(__str303, cMineDudPercent);
    uscript_ScriptSetInteger(__str304, cAirMines);
    uscript_ScriptSetInteger(__str305, cExplosives);
    uscript_ScriptSetInteger(__str306, cInactDelay);
    uscript_ScriptSetInteger(__str307, cReadyDelay);
    uscript_ScriptSetInteger(__str308, cSuddenDTurns);
    uscript_ScriptSetInteger(__str309, cWaterRise);
    uscript_ScriptSetInteger(__str310, cHealthDecrease);
    uscript_ScriptSetInteger(__str311, cGetAwayTime);
    uscript_ScriptSetInteger(__str312, (60));
    uscript_ScriptSetString(__str313, cMapName);
    uscript_ScriptSetString(__str314, Theme);
    uscript_ScriptSetString(__str315, __str40);
    uscript_ScriptCall_1(__str316);
    ucommands_ParseCommand_3(_strconcat(__str287, uscript_ScriptGetString(__str281)), true, true);
    cTemplateFilter = uscript_ScriptGetInteger(__str282);
    LuaTemplateNumber = uscript_ScriptGetInteger(__str283);
    cMapGen = ((TMapGen)uscript_ScriptGetInteger(__str284));
    cFeatureSize = uscript_ScriptGetInteger(__str285);
    GameFlags = uscript_ScriptGetInteger(__str57);
    WorldEdge = ((TWorldEdge)uscript_ScriptGetInteger(__str290));
    cHedgehogTurnTime = uscript_ScriptGetInteger(__str293);
    cCaseFactor = uscript_ScriptGetInteger(__str294);
    cMaxCaseDrops = uscript_ScriptGetInteger(__str295);
    cHealthCaseProb = uscript_ScriptGetInteger(__str296);
    cHealthCaseAmount = uscript_ScriptGetInteger(__str297);
    cInitHealth = uscript_ScriptGetInteger(__str298);
    cDamagePercent = uscript_ScriptGetInteger(__str299);
    cRopePercent = uscript_ScriptGetInteger(__str300);
    cLandMines = uscript_ScriptGetInteger(__str301);
    cMinesTime = uscript_ScriptGetInteger(__str302);
    cMineDudPercent = uscript_ScriptGetInteger(__str303);
    cAirMines = uscript_ScriptGetInteger(__str304);
    cExplosives = uscript_ScriptGetInteger(__str305);
    cInactDelay = uscript_ScriptGetInteger(__str306);
    cReadyDelay = uscript_ScriptGetInteger(__str307);
    cSuddenDTurns = uscript_ScriptGetInteger(__str308);
    cWaterRise = uscript_ScriptGetInteger(__str309);
    cHealthDecrease = uscript_ScriptGetInteger(__str310);
    cGetAwayTime = uscript_ScriptGetInteger(__str311);
    if(_strncompare(cMapName, uscript_ScriptGetString(__str313)))
    {
        ucommands_ParseCommand_3(_strconcat(__str317, uscript_ScriptGetString(__str313)), true, true);
    }
    if(_strncompare(uscript_ScriptGetString(__str314), __str40))
    {
        ucommands_ParseCommand_3(_strconcat(__str318, uscript_ScriptGetString(__str314)), true, true);
    }
    LuaGoals = uscript_ScriptGetAnsiString(__str315);
    k = 0;
    if((GameFlags & gfSharedAmmo) != 0)
    {
        {i = 0;
         LongInt i__end__ = ((int)(ClansCount) - 1);
         if (i <= i__end__) do {
                                   {j = 0;
                                    LongInt j__end__ = ((int)(ClansArray[i]->TeamsNumber) - 1);
                                    if (j <= j__end__) do {
                                                              {k = 0;
                                                               LongInt k__end__ = ((int)((*ClansArray[i]->Teams[j]).HedgehogsNumber) - 1);
                                                               if (k <= k__end__) do {
                                                                                         (*ClansArray[i]->Teams[j]).Hedgehogs[k].AmmoStore = i;
                                                                                     } while(k++ != k__end__);}
                                                          } while(j++ != j__end__);}
                               } while(i++ != i__end__);}
    }
    else
    {
        if((GameFlags & gfPerHogAmmo) != 0)
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       {j = 0;
                                        LongInt j__end__ = ((int)(TeamsArray[i]->HedgehogsNumber) - 1);
                                        if (j <= j__end__) do {
                                                                  TeamsArray[i]->Hedgehogs[j].AmmoStore = k;
                                                                  if((StoreCnt - 1) < k)
                                                                  {
                                                                      uammos_AddAmmoStore();
                                                                  }
                                                                  ++k;
                                                              } while(j++ != j__end__);}
                                   } while(i++ != i__end__);}
        }
        else
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       {j = 0;
                                        LongInt j__end__ = ((int)(TeamsArray[i]->HedgehogsNumber) - 1);
                                        if (j <= j__end__) do {
                                                                  TeamsArray[i]->Hedgehogs[j].AmmoStore = k;
                                                              } while(j++ != j__end__);}
                                       if((StoreCnt - 1) < k)
                                       {
                                           uammos_AddAmmoStore();
                                       }
                                       ++k;
                                   } while(i++ != i__end__);}
        }
    }
    if(uscript_ScriptExists(__str319) || uscript_ScriptExists(__str320))
    {
        uammos_freeModule();
        uammos_initModule();
        if(uscript_ScriptExists(__str319))
        {
            uscript_ScriptPrepareAmmoStore_0();
            uscript_ScriptCall_1(__str319);
            uammos_SetAmmoLoadout(&(ScriptAmmoLoadout));
            uammos_SetAmmoProbability(&(ScriptAmmoProbability));
            uammos_SetAmmoDelay(&(ScriptAmmoDelay));
            uammos_SetAmmoReinforcement(&(ScriptAmmoReinforcement));
        }
        uscript_ScriptApplyAmmoStore_0();
    }
    uscript_ScriptSetInteger(__str321, ClansCount);
    uscript_ScriptSetInteger(__str322, TeamsCount);
};
void uscript_ScriptOnScreenResize()
{
    uscript_ScriptSetInteger(__str291, cScreenHeight);
    uscript_ScriptSetInteger(__str292, cScreenWidth);
    uscript_ScriptCall_1(__str323);
};
enum{BUFSIZE = 1024};
static boolean inComment;
static boolean inQuote;
static LongWord locSum;
static LongWord braceCount;
static LongWord wordCount;
static char lastChar;
PChar uscript_ScriptReader(Plua_State L,PFSFile f,Psize_t sz)
{
    PChar scriptreader_result;
    PChar mybuf;
    LongInt i;
    urandom_SetRandomSeed(cSeed, true);
    mybuf = physfsReader(L, f, sz);
    if((mybuf != NULL) && ((*sz) > 0))
    {
        {i = 0;
         LongInt i__end__ = (*sz) - 1;
         if (i <= i__end__) do {
                                   if((lastChar == 0x2d) && (mybuf[i] == 0x2d))
                                   {
                                       inComment = true;
                                   }
                                   else
                                   {
                                       if(((!inComment && (((Byte)mybuf[i]) > 0x20)) && (((Byte)mybuf[i]) < 0x7f)) && (mybuf[i] != 0x2d))
                                       {
                                           urandom_AddRandomness(((Byte)mybuf[i]));
                                           CheckSum = CheckSum ^ urandom_GetRandom(0xffffffff);
                                       }
                                   }
                                   lastChar = mybuf[i];
                                   if(((((Byte)mybuf[i]) == 0x0d) || (((Byte)mybuf[i]) == 0x0a)) || (mybuf[i] == 0x5b))
                                   {
                                       inComment = false;
                                   }
                               } while(i++ != i__end__);}
    }
    scriptreader_result = mybuf;
    return scriptreader_result;
};
PChar uscript_ScriptLocaleReader(Plua_State L,PFSFile f,Psize_t sz)
{
    PChar scriptlocalereader_result;
    PChar mybuf;
    LongInt i;
    mybuf = physfsReader(L, f, sz);
    if((mybuf != NULL) && ((*sz) > 0))
    {
        {i = 0;
         LongInt i__end__ = (*sz) - 1;
         if (i <= i__end__) do {
                                   if((!inComment && (mybuf[i] == 0x22)) && (lastChar != 0x5c))
                                   {
                                       inQuote = !inQuote;
                                   }
                                   if((!inQuote && (lastChar == 0x2d)) && (mybuf[i] == 0x2d))
                                   {
                                       inComment = true;
                                   }
                                   if(!inComment && !inQuote)
                                   {
                                       locSum = locSum ^ (((Byte)mybuf[i]) << (i % 4));
                                   }
                                   if((!inComment && !inQuote) && ((((((mybuf[i] == 0x28) || (mybuf[i] == 0x29)) || (mybuf[i] == 0x2b)) || (mybuf[i] == 0x23)) || (braceCount > 2)) || (wordCount > 6)))
                                   {
                                       CheckSum = locSum;
                                   }
                                   if((!inComment && !inQuote) && ((mybuf[i] == 0x7b) || (mybuf[i] == 0x7d)))
                                   {
                                       ++braceCount;
                                   }
                                   if((!inComment && !inQuote) && ((((((Byte)mybuf[i]) > 0x40) && (((Byte)mybuf[i]) < 0x5b)) || ((((Byte)mybuf[i]) > 0x60) && (((Byte)mybuf[i]) < 0x7b))) || ((((Byte)mybuf[i]) >= 0x30) && (((Byte)mybuf[i]) < 0x3a))))
                                   {
                                       ++wordCount;
                                   }
                                   lastChar = mybuf[i];
                                   if(((((Byte)mybuf[i]) == 0x0d) || (((Byte)mybuf[i]) == 0x0a)) || (mybuf[i] == 0x5b))
                                   {
                                       inComment = false;
                                   }
                               } while(i++ != i__end__);}
    }
    scriptlocalereader_result = mybuf;
    return scriptlocalereader_result;
};
boolean uscript_ScriptLoad(string255 name,boolean mustExist)
{
    boolean scriptload_result;
    LongInt ret;
    string255 s;
    PFSFile f;
    typedef Byte buf_tt[BUFSIZE];
    buf_tt buf;
    inComment = false;
    inQuote = false;
    lastChar = 0x58;
    braceCount = 0;
    wordCount = 0;
    locSum = 0;
    s = _strconcat(cPathz[ptData], name);
    if(!uphysfslayer_pfsExists(s))
    {
        if(mustExist)
        {
            udebug_OutError(_strconcat(__str324, name), true);
        }
        else
        {
            uutils_AddFileLog(_strconcat(__str325, name));
        }
        scriptload_result = false;
        return scriptload_result;
    }
    f = uphysfslayer_pfsOpenRead(s);
    if(f == NULL)
    {
        udebug_OutError(_strconcat(__str326, name), true);
    }
    hedgewarsMountPackage(uutils_Str2PChar(_strconcat(fpcrtl_copy(s, 3, fpcrtl_Length(s) - 6), __str327)));
    physfsReaderSetBuffer(&(buf));
    if((fpcrtl_pos(__str328, s) != 0) || (_strcompare(s, __str329)))
    {
        ret = lua_load(luaState, &(uscript_ScriptLocaleReader), f, uutils_Str2PChar(s));
    }
    else
    {
        urandom_SetRandomSeed(cSeed, true);
        ret = lua_load(luaState, &(uscript_ScriptReader), f, uutils_Str2PChar(s));
    }
    uphysfslayer_pfsClose(f);
    if(ret != 0)
    {
        uscript_LuaError(_strappend(_strconcat(_strconcat(_strconcat(__str330, name), __str331), uutils_IntToStr(ret)), 0x29));
        uscript_LuaError(luapas_lua_tostring(luaState, -1));
        scriptload_result = false;
    }
    else
    {
        uconsole_WriteLnToConsole(_strconcat(_strconcat(__str45, name), __str332));
        lua_pcall(luaState, 0, 0, 0);
        ScriptLoaded = true;
        scriptload_result = true;
    }
    return scriptload_result;
};
void uscript_SetGlobals_0()
{
    LongInt x;
    LongInt y;
    uscript_ScriptSetInteger(__str333, TurnTimeLeft);
    uscript_ScriptSetInteger(__str334, ReadyTimeLeft);
    uscript_ScriptSetInteger(__str335, GameTicks);
    uscript_ScriptSetInteger(__str336, TotalRoundsReal);
    uscript_ScriptSetInteger(__str337, cWaterLine);
    if(isCursorVisible && !bShowAmmoMenu)
    {
        x = CursorPoint.x - WorldDx;
        y = (cScreenHeight - CursorPoint.y) - WorldDy;
        if((PrevCursorX != x) || (PrevCursorY != y))
        {
            uscript_ScriptSetInteger(__str288, x);
            uscript_ScriptSetInteger(__str289, y);
            PrevCursorX = x;
            PrevCursorY = y;
        }
    }
    else
    {
        uscript_ScriptSetInteger(__str288, NoPointX);
        uscript_ScriptSetInteger(__str289, NoPointX);
        PrevCursorX = NoPointX;
        PrevCursorY = NoPointX;
    }
    if((CurrentHedgehog != NULL) && (CurrentHedgehog->Gear != NULL))
    {
        uscript_ScriptSetInteger(__str338, (*CurrentHedgehog->Gear).uid);
    }
    else
    {
        uscript_ScriptSetNil(__str338);
    }
};
void uscript_ScriptSetMapGlobals()
{
    uscript_ScriptSetInteger(__str339, LAND_WIDTH);
    uscript_ScriptSetInteger(__str340, LAND_HEIGHT);
    uscript_ScriptSetInteger(__str341, leftX);
    uscript_ScriptSetInteger(__str342, rightX);
    uscript_ScriptSetInteger(__str343, topY);
};
void uscript_GetGlobals_0()
{
    LongInt currentTTL;
    LongInt currentRTL;
    LongInt newTTL;
    LongInt newRTL;
    currentTTL = TurnTimeLeft;
    currentRTL = ReadyTimeLeft;
    newTTL = uscript_ScriptGetInteger(__str333);
    newRTL = uscript_ScriptGetInteger(__str334);
    if((currentTTL != newTTL) && !isPendingTurnTimeLeft)
    {
        TurnTimeLeft = newTTL;
        uscript_LuaWarning(__str344);
    }
    if((currentRTL != newRTL) && !isPendingReadyTimeLeft)
    {
        ReadyTimeLeft = newRTL;
        uscript_LuaWarning(__str345);
    }
    if(isPendingTurnTimeLeft)
    {
        TurnTimeLeft = PendingTurnTimeLeft;
        uscript_ScriptSetInteger(__str333, TurnTimeLeft);
        isPendingTurnTimeLeft = false;
    }
    if(isPendingReadyTimeLeft)
    {
        ReadyTimeLeft = PendingReadyTimeLeft;
        uscript_ScriptSetInteger(__str334, ReadyTimeLeft);
        isPendingReadyTimeLeft = false;
    }
};
void uscript_ScriptCall_1(string255 fname)
{
    if(!ScriptLoaded || !uscript_ScriptExists(fname))
    {
        return;
    }
    uscript_SetGlobals_0();
    luapas_lua_getglobal(luaState, uutils_Str2PChar(fname));
    if(lua_pcall(luaState, 0, 0, 0) != 0)
    {
        uscript_LuaError(_strconcat(_strconcat(_strconcat(__str346, fname), __str9), luapas_lua_tostring(luaState, -1)));
        luapas_lua_pop(luaState, 1);
    }
    uscript_GetGlobals_0();
};
LongInt uscript_ScriptCall_2(string255 fname,LongInt par1)
{
    LongInt scriptcall_result;
    scriptcall_result = uscript_ScriptCall_5(fname, par1, 0, 0, 0);
    return scriptcall_result;
};
LongInt uscript_ScriptCall_3(string255 fname,LongInt par1,LongInt par2)
{
    LongInt scriptcall_result;
    scriptcall_result = uscript_ScriptCall_5(fname, par1, par2, 0, 0);
    return scriptcall_result;
};
LongInt uscript_ScriptCall_4(string255 fname,LongInt par1,LongInt par2,LongInt par3)
{
    LongInt scriptcall_result;
    scriptcall_result = uscript_ScriptCall_5(fname, par1, par2, par3, 0);
    return scriptcall_result;
};
LongInt uscript_ScriptCall_5(string255 fname,LongInt par1,LongInt par2,LongInt par3,LongInt par4)
{
    LongInt scriptcall_result;
    if(!ScriptLoaded || !uscript_ScriptExists(fname))
    {
        return 0;
    }
    uscript_SetGlobals_0();
    luapas_lua_getglobal(luaState, uutils_Str2PChar(fname));
    lua_pushnumber(luaState, par1);
    lua_pushnumber(luaState, par2);
    lua_pushnumber(luaState, par3);
    lua_pushnumber(luaState, par4);
    scriptcall_result = 0;
    if(lua_pcall(luaState, 4, 1, 0) != 0)
    {
        uscript_LuaError(_strconcat(_strconcat(_strconcat(__str346, fname), __str9), luapas_lua_tostring(luaState, -1)));
        luapas_lua_pop(luaState, 1);
    }
    else
    {
        scriptcall_result = fpcrtl_trunc(lua_tonumber(luaState, -1));
        luapas_lua_pop(luaState, 1);
    }
    uscript_GetGlobals_0();
    return scriptcall_result;
};
boolean uscript_ScriptExists(string255 fname)
{
    boolean scriptexists_result;
    if(!ScriptLoaded)
    {
        scriptexists_result = false;
        return scriptexists_result;
    }
    luapas_lua_getglobal(luaState, uutils_Str2PChar(fname));
    scriptexists_result = !luapas_lua_isnoneornil(luaState, -1);
    luapas_lua_pop(luaState, 1);
    return scriptexists_result;
};
void uscript_ScriptPrepareAmmoStore_0()
{
    ShortInt i;
    ScriptAmmoLoadout = __str40;
    ScriptAmmoDelay = __str40;
    ScriptAmmoProbability = __str40;
    ScriptAmmoReinforcement = __str40;
    {i = 1;
     ShortInt i__end__ = (60);
     if (i <= i__end__) do {
                               ScriptAmmoLoadout = _strappend(ScriptAmmoLoadout, 0x30);
                               ScriptAmmoProbability = _strappend(ScriptAmmoProbability, 0x30);
                               ScriptAmmoDelay = _strappend(ScriptAmmoDelay, 0x30);
                               ScriptAmmoReinforcement = _strappend(ScriptAmmoReinforcement, 0x30);
                           } while(i++ != i__end__);}
};
void uscript_ScriptSetAmmo_5(TAmmoType ammo,Byte count,Byte probability,Byte delay,Byte reinforcement)
{
    if((((((ammo) < 1) || (count > 9)) || (probability > 8)) || (delay > 9)) || (reinforcement > 8))
    {
        return;
    }
    ScriptAmmoLoadout.s[(ammo)] = uutils_IntToStr(count).s[1];
    ScriptAmmoProbability.s[(ammo)] = uutils_IntToStr(probability).s[1];
    uscript_ScriptSetAmmoDelay_2(ammo, delay);
    ScriptAmmoReinforcement.s[(ammo)] = uutils_IntToStr(reinforcement).s[1];
};
void uscript_ScriptSetAmmoDelay_2(TAmmoType ammo,LongWord delay)
{
    if(StoreCnt == 0)
    {
        if(delay <= 9)
        {
            ScriptAmmoDelay.s[(ammo)] = uutils_IntToStr(delay).s[1];
        }
    }
    else
    {
        if(CurrentTeam != NULL)
        {
            Ammoz[ammo].SkipTurns = (*CurrentTeam->Clan).TurnNumber + delay;
            if(Ammoz[ammo].SkipTurns > 0)
            {
                --Ammoz[ammo].SkipTurns;
            }
            AmmoMenuInvalidated = true;
        }
    }
};
void uscript_ScriptApplyAmmoStore_0()
{
    LongInt i;
    LongInt j;
    LongInt k;
    if((GameFlags & gfSharedAmmo) != 0)
    {
        {i = 0;
         LongInt i__end__ = ((int)(ClansCount) - 1);
         if (i <= i__end__) do {
                                   if(uscript_ScriptExists(__str320))
                                   {
                                       uscript_ScriptPrepareAmmoStore_0();
                                       uscript_ScriptCall_3(__str320, i, -1);
                                       uammos_SetAmmoLoadout(&(ScriptAmmoLoadout));
                                       uammos_SetAmmoProbability(&(ScriptAmmoProbability));
                                       uammos_SetAmmoDelay(&(ScriptAmmoDelay));
                                       uammos_SetAmmoReinforcement(&(ScriptAmmoReinforcement));
                                   }
                                   uammos_AddAmmoStore();
                                   {j = 0;
                                    LongInt j__end__ = ((int)(ClansArray[i]->TeamsNumber) - 1);
                                    if (j <= j__end__) do {
                                                              {k = 0;
                                                               LongInt k__end__ = ((int)((*ClansArray[i]->Teams[j]).HedgehogsNumber) - 1);
                                                               if (k <= k__end__) do {
                                                                                         (*ClansArray[i]->Teams[j]).Hedgehogs[k].AmmoStore = StoreCnt - 1;
                                                                                     } while(k++ != k__end__);}
                                                          } while(j++ != j__end__);}
                               } while(i++ != i__end__);}
    }
    else
    {
        if((GameFlags & gfPerHogAmmo) != 0)
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       {j = 0;
                                        LongInt j__end__ = ((int)(TeamsArray[i]->HedgehogsNumber) - 1);
                                        if (j <= j__end__) do {
                                                                  if(uscript_ScriptExists(__str320))
                                                                  {
                                                                      uscript_ScriptPrepareAmmoStore_0();
                                                                      uscript_ScriptCall_3(__str320, i, j);
                                                                      uammos_SetAmmoLoadout(&(ScriptAmmoLoadout));
                                                                      uammos_SetAmmoProbability(&(ScriptAmmoProbability));
                                                                      uammos_SetAmmoDelay(&(ScriptAmmoDelay));
                                                                      uammos_SetAmmoReinforcement(&(ScriptAmmoReinforcement));
                                                                  }
                                                                  uammos_AddAmmoStore();
                                                                  TeamsArray[i]->Hedgehogs[j].AmmoStore = StoreCnt - 1;
                                                              } while(j++ != j__end__);}
                                   } while(i++ != i__end__);}
        }
        else
        {
            {i = 0;
             LongInt i__end__ = ((int)(TeamsCount) - 1);
             if (i <= i__end__) do {
                                       if(uscript_ScriptExists(__str320))
                                       {
                                           uscript_ScriptPrepareAmmoStore_0();
                                           uscript_ScriptCall_3(__str320, i, -1);
                                           uammos_SetAmmoLoadout(&(ScriptAmmoLoadout));
                                           uammos_SetAmmoProbability(&(ScriptAmmoProbability));
                                           uammos_SetAmmoDelay(&(ScriptAmmoDelay));
                                           uammos_SetAmmoReinforcement(&(ScriptAmmoReinforcement));
                                       }
                                       uammos_AddAmmoStore();
                                       {j = 0;
                                        LongInt j__end__ = ((int)(TeamsArray[i]->HedgehogsNumber) - 1);
                                        if (j <= j__end__) do {
                                                                  TeamsArray[i]->Hedgehogs[j].AmmoStore = StoreCnt - 1;
                                                              } while(j++ != j__end__);}
                                   } while(i++ != i__end__);}
        }
    }
};
void uscript_initModule()
{
    TGearType at;
    TVisualGearType vgt;
    TAmmoType am;
    TStatInfoType si;
    TSound st;
    THogEffect he;
    TCapGroup cg;
    TSprite spr;
    TMapGen mg;
    TWorldEdge we;
    TMsgStrId msi;
    TGoalStrId gsi;
    luaState = luapas_lua_open();
    if(udebug_checkFails(luaState != NULL, __str347, true))
    {
        return;
    }
    luaopen_base(luaState);
    luaopen_string(luaState);
    luaopen_math(luaState);
    luaopen_table(luaState);
    uscript_ScriptSetString(__str348, cLanguage);
    uscript_ScriptSetString(__str349, __str350);
    uscript_ScriptSetInteger(__str351, (amCreeper));
    uscript_ScriptSetInteger(__str352, (gtCreeper));
    uscript_ScriptSetInteger(__str353, gfSwitchHog);
    uscript_ScriptSetInteger(__str354, gfMultiWeapon);
    uscript_ScriptSetInteger(__str355, gfSolidLand);
    uscript_ScriptSetInteger(__str356, gfBorder);
    uscript_ScriptSetInteger(__str357, gfBottomBorder);
    uscript_ScriptSetInteger(__str358, gfDivideTeams);
    uscript_ScriptSetInteger(__str359, gfLowGravity);
    uscript_ScriptSetInteger(__str360, gfLaserSight);
    uscript_ScriptSetInteger(__str361, gfInvulnerable);
    uscript_ScriptSetInteger(__str362, gfResetHealth);
    uscript_ScriptSetInteger(__str363, gfVampiric);
    uscript_ScriptSetInteger(__str364, gfKarma);
    uscript_ScriptSetInteger(__str365, gfArtillery);
    uscript_ScriptSetInteger(__str366, gfOneClanMode);
    uscript_ScriptSetInteger(__str367, gfRandomOrder);
    uscript_ScriptSetInteger(__str368, gfKing);
    uscript_ScriptSetInteger(__str369, gfPlaceHog);
    uscript_ScriptSetInteger(__str370, gfSharedAmmo);
    uscript_ScriptSetInteger(__str371, gfDisableGirders);
    uscript_ScriptSetInteger(__str372, gfDisableLandObjects);
    uscript_ScriptSetInteger(__str373, gfAISurvival);
    uscript_ScriptSetInteger(__str374, gfInfAttack);
    uscript_ScriptSetInteger(__str375, gfResetWeps);
    uscript_ScriptSetInteger(__str376, gfPerHogAmmo);
    uscript_ScriptSetInteger(__str377, gfDisableWind);
    uscript_ScriptSetInteger(__str378, gfMoreWind);
    uscript_ScriptSetInteger(__str379, gfTagTeam);
    uscript_ScriptSetInteger(__str380, gfShoppaBorder);
    uscript_ScriptSetInteger(__str381, gmLeft);
    uscript_ScriptSetInteger(__str382, gmRight);
    uscript_ScriptSetInteger(__str383, gmUp);
    uscript_ScriptSetInteger(__str384, gmDown);
    uscript_ScriptSetInteger(__str385, gmSwitch);
    uscript_ScriptSetInteger(__str386, gmAttack);
    uscript_ScriptSetInteger(__str387, gmLJump);
    uscript_ScriptSetInteger(__str388, gmHJump);
    uscript_ScriptSetInteger(__str389, gmDestroy);
    uscript_ScriptSetInteger(__str390, gmSlot);
    uscript_ScriptSetInteger(__str391, gmWeapon);
    uscript_ScriptSetInteger(__str392, gmTimer);
    uscript_ScriptSetInteger(__str393, gmAnimate);
    uscript_ScriptSetInteger(__str394, gmPrecise);
    uscript_ScriptSetInteger(__str395, gmAllStoppable);
    uscript_ScriptSetInteger(__str396, 1);
    uscript_ScriptSetInteger(__str397, 2);
    uscript_ScriptSetInteger(__str398, 3);
    uscript_ScriptSetInteger(__str399, AMMO_INFINITE);
    uscript_ScriptSetInteger(__str400, JETPACK_FUEL_INFINITE);
    uscript_ScriptSetInteger(__str401, BIRDY_ENERGY_INFINITE);
    uscript_ScriptSetInteger(__str402, NoPointX);
    uscript_ScriptSetInteger(__str403, cMaxHogHealth);
    uscript_ScriptSetInteger(__str404, cMaxTurnTime);
    {at = 0;
     TGearType at__end__ = 69;
     if (at <= at__end__) do {
                                 uscript_ScriptSetInteger(uutils_EnumToStr_1(at), (at));
                             } while(at++ != at__end__);}
    {vgt = 0;
     TVisualGearType vgt__end__ = 33;
     if (vgt <= vgt__end__) do {
                                   uscript_ScriptSetInteger(uutils_EnumToStr_1(vgt), (vgt));
                               } while(vgt++ != vgt__end__);}
    {st = 0;
     TSound st__end__ = 174;
     if (st <= st__end__) do {
                                 uscript_ScriptSetInteger(uutils_EnumToStr_1(st), (st));
                             } while(st++ != st__end__);}
    {am = 0;
     TAmmoType am__end__ = 60;
     if (am <= am__end__) do {
                                 uscript_ScriptSetInteger(uutils_EnumToStr_1(am), (am));
                             } while(am++ != am__end__);}
    {si = 0;
     TStatInfoType si__end__ = 14;
     if (si <= si__end__) do {
                                 uscript_ScriptSetInteger(uutils_EnumToStr_1(si), (si));
                             } while(si++ != si__end__);}
    {he = 0;
     THogEffect he__end__ = 5;
     if (he <= he__end__) do {
                                 uscript_ScriptSetInteger(uutils_EnumToStr_1(he), (he));
                             } while(he++ != he__end__);}
    {cg = 0;
     TCapGroup cg__end__ = 5;
     if (cg <= cg__end__) do {
                                 uscript_ScriptSetInteger(uutils_EnumToStr_1(cg), (cg));
                             } while(cg++ != cg__end__);}
    {spr = 0;
     TSprite spr__end__ = 219;
     if (spr <= spr__end__) do {
                                   uscript_ScriptSetInteger(uutils_EnumToStr_1(spr), (spr));
                               } while(spr++ != spr__end__);}
    {mg = 0;
     TMapGen mg__end__ = 5;
     if (mg <= mg__end__) do {
                                 uscript_ScriptSetInteger(uutils_EnumToStr_1(mg), (mg));
                             } while(mg++ != mg__end__);}
    {we = 0;
     TWorldEdge we__end__ = 4;
     if (we <= we__end__) do {
                                 uscript_ScriptSetInteger(uutils_EnumToStr_1(we), (we));
                             } while(we++ != we__end__);}
    {msi = 0;
     TMsgStrId msi__end__ = 49;
     if (msi <= msi__end__) do {
                                   uscript_ScriptSetInteger(uutils_EnumToStr_1(msi), (msi));
                               } while(msi++ != msi__end__);}
    {gsi = 0;
     TGoalStrId gsi__end__ = 22;
     if (gsi <= gsi__end__) do {
                                   uscript_ScriptSetInteger(uutils_EnumToStr_1(gsi), (gsi));
                               } while(gsi++ != gsi__end__);}
    uscript_ScriptSetLongWord(__str405, capcolDefaultLua);
    uscript_ScriptSetLongWord(__str406, capcolSettingLua);
    uscript_ScriptSetInteger(__str407, gstDrowning);
    uscript_ScriptSetInteger(__str408, gstHHDriven);
    uscript_ScriptSetInteger(__str409, gstMoving);
    uscript_ScriptSetInteger(__str410, gstAttacked);
    uscript_ScriptSetInteger(__str411, gstAttacking);
    uscript_ScriptSetInteger(__str412, gstCollision);
    uscript_ScriptSetInteger(__str413, gstChooseTarget);
    uscript_ScriptSetInteger(__str414, gstHHJumping);
    uscript_ScriptSetInteger(__str415, gsttmpFlag);
    uscript_ScriptSetInteger(__str416, gstHHThinking);
    uscript_ScriptSetInteger(__str417, gstNoDamage);
    uscript_ScriptSetInteger(__str418, gstHHHJump);
    uscript_ScriptSetInteger(__str419, gstAnimation);
    uscript_ScriptSetInteger(__str420, gstHHDeath);
    uscript_ScriptSetInteger(__str421, gstWinner);
    uscript_ScriptSetInteger(__str422, gstWait);
    uscript_ScriptSetInteger(__str423, gstNotKickable);
    uscript_ScriptSetInteger(__str424, gstLoser);
    uscript_ScriptSetInteger(__str425, gstHHGone);
    uscript_ScriptSetInteger(__str426, gstInvisible);
    uscript_ScriptSetInteger(__str427, gstSubmersible);
    uscript_ScriptSetInteger(__str428, gstFrozen);
    uscript_ScriptSetInteger(__str429, gstNoGravity);
    uscript_ScriptSetInteger(__str430, aihUsualProcessing);
    uscript_ScriptSetInteger(__str431, aihDoesntMatter);
    uscript_ScriptSetInteger(__str432, lfIndestructible);
    uscript_ScriptSetInteger(__str433, lfIce);
    uscript_ScriptSetInteger(__str434, lfBouncy);
    uscript_ScriptSetInteger(__str435, lfLandMask);
    uscript_ScriptSetInteger(__str436, lfCurHogCrate);
    uscript_ScriptSetInteger(__str437, lfHHMask);
    uscript_ScriptSetInteger(__str438, lfNotHHObjMask);
    uscript_ScriptSetInteger(__str439, lfAllObjMask);
    uscript_ScriptSetInteger(__str440, EXPLAutoSound);
    uscript_ScriptSetInteger(__str441, EXPLNoDamage);
    uscript_ScriptSetInteger(__str442, EXPLDoNotTouchHH);
    uscript_ScriptSetInteger(__str443, EXPLDontDraw);
    uscript_ScriptSetInteger(__str444, EXPLNoGfx);
    uscript_ScriptSetInteger(__str445, EXPLPoisoned);
    uscript_ScriptSetInteger(__str446, EXPLDoNotTouchAny);
    uscript_ScriptSetInteger(__str447, EXPLForceDraw);
    luapas_lua_register(luaState, "HideHog", &(uscript_lc_hidehog));
    luapas_lua_register(luaState, "RestoreHog", &(uscript_lc_restorehog));
    luapas_lua_register(luaState, "IsHogHidden", &(uscript_lc_ishoghidden));
    luapas_lua_register(luaState, "SaveCampaignVar", &(uscript_lc_savecampaignvar));
    luapas_lua_register(luaState, "GetCampaignVar", &(uscript_lc_getcampaignvar));
    luapas_lua_register(luaState, "SaveMissionVar", &(uscript_lc_savemissionvar));
    luapas_lua_register(luaState, "GetMissionVar", &(uscript_lc_getmissionvar));
    luapas_lua_register(luaState, "band", &(uscript_lc_band));
    luapas_lua_register(luaState, "bor", &(uscript_lc_bor));
    luapas_lua_register(luaState, "bnot", &(uscript_lc_bnot));
    luapas_lua_register(luaState, "div", &(uscript_lc_div));
    luapas_lua_register(luaState, "GetInputMask", &(uscript_lc_getinputmask));
    luapas_lua_register(luaState, "SetInputMask", &(uscript_lc_setinputmask));
    luapas_lua_register(luaState, "AddGear", &(uscript_lc_addgear));
    luapas_lua_register(luaState, "DismissTeam", &(uscript_lc_dismissteam));
    luapas_lua_register(luaState, "EnableGameFlags", &(uscript_lc_enablegameflags));
    luapas_lua_register(luaState, "DisableGameFlags", &(uscript_lc_disablegameflags));
    luapas_lua_register(luaState, "ClearGameFlags", &(uscript_lc_cleargameflags));
    luapas_lua_register(luaState, "GetGameFlag", &(uscript_lc_getgameflag));
    luapas_lua_register(luaState, "DeleteGear", &(uscript_lc_deletegear));
    luapas_lua_register(luaState, "AddVisualGear", &(uscript_lc_addvisualgear));
    luapas_lua_register(luaState, "DeleteVisualGear", &(uscript_lc_deletevisualgear));
    luapas_lua_register(luaState, "GetVisualGearType", &(uscript_lc_getvisualgeartype));
    luapas_lua_register(luaState, "GetVisualGearValues", &(uscript_lc_getvisualgearvalues));
    luapas_lua_register(luaState, "SetVisualGearValues", &(uscript_lc_setvisualgearvalues));
    luapas_lua_register(luaState, "GetGearValues", &(uscript_lc_getgearvalues));
    luapas_lua_register(luaState, "SetGearValues", &(uscript_lc_setgearvalues));
    luapas_lua_register(luaState, "SpawnHealthCrate", &(uscript_lc_spawnhealthcrate));
    luapas_lua_register(luaState, "SpawnAmmoCrate", &(uscript_lc_spawnammocrate));
    luapas_lua_register(luaState, "SpawnUtilityCrate", &(uscript_lc_spawnutilitycrate));
    luapas_lua_register(luaState, "SpawnSupplyCrate", &(uscript_lc_spawnsupplycrate));
    luapas_lua_register(luaState, "SpawnFakeHealthCrate", &(uscript_lc_spawnfakehealthcrate));
    luapas_lua_register(luaState, "SpawnFakeAmmoCrate", &(uscript_lc_spawnfakeammocrate));
    luapas_lua_register(luaState, "SpawnFakeUtilityCrate", &(uscript_lc_spawnfakeutilitycrate));
    luapas_lua_register(luaState, "WriteLnToConsole", &(uscript_lc_writelntoconsole));
    luapas_lua_register(luaState, "WriteLnToChat", &(uscript_lc_writelntochat));
    luapas_lua_register(luaState, "GetGearType", &(uscript_lc_getgeartype));
    luapas_lua_register(luaState, "EndGame", &(uscript_lc_endgame));
    luapas_lua_register(luaState, "EndTurn", &(uscript_lc_endturn));
    luapas_lua_register(luaState, "Retreat", &(uscript_lc_retreat));
    luapas_lua_register(luaState, "SkipTurn", &(uscript_lc_skipturn));
    luapas_lua_register(luaState, "GetTeamStats", &(uscript_lc_getteamstats));
    luapas_lua_register(luaState, "SendStat", &(uscript_lc_sendstat));
    luapas_lua_register(luaState, "SendGameResultOff", &(uscript_lc_sendgameresultoff));
    luapas_lua_register(luaState, "SendRankingStatsOff", &(uscript_lc_sendrankingstatsoff));
    luapas_lua_register(luaState, "SendAchievementsStatsOff", &(uscript_lc_sendachievementsstatsoff));
    luapas_lua_register(luaState, "SendHealthStatsOff", &(uscript_lc_sendhealthstatsoff));
    luapas_lua_register(luaState, "FindPlace", &(uscript_lc_findplace));
    luapas_lua_register(luaState, "SetGearPosition", &(uscript_lc_setgearposition));
    luapas_lua_register(luaState, "GetGearPosition", &(uscript_lc_getgearposition));
    luapas_lua_register(luaState, "SetGearTarget", &(uscript_lc_setgeartarget));
    luapas_lua_register(luaState, "GetGearTarget", &(uscript_lc_getgeartarget));
    luapas_lua_register(luaState, "SetGearVelocity", &(uscript_lc_setgearvelocity));
    luapas_lua_register(luaState, "GetGearVelocity", &(uscript_lc_getgearvelocity));
    luapas_lua_register(luaState, "ParseCommand", &(uscript_lc_parsecommand));
    luapas_lua_register(luaState, "ShowMission", &(uscript_lc_showmission));
    luapas_lua_register(luaState, "HideMission", &(uscript_lc_hidemission));
    luapas_lua_register(luaState, "GetEngineString", &(uscript_lc_getenginestring));
    luapas_lua_register(luaState, "SetAmmoTexts", &(uscript_lc_setammotexts));
    luapas_lua_register(luaState, "SetAmmoDescriptionAppendix", &(uscript_lc_setammodescriptionappendix));
    luapas_lua_register(luaState, "AddCaption", &(uscript_lc_addcaption));
    luapas_lua_register(luaState, "SetAmmo", &(uscript_lc_setammo));
    luapas_lua_register(luaState, "GetAmmo", &(uscript_lc_getammo));
    luapas_lua_register(luaState, "SetAmmoDelay", &(uscript_lc_setammodelay));
    luapas_lua_register(luaState, "SetAmmoSlot", &(uscript_lc_setammoslot));
    luapas_lua_register(luaState, "PlaySound", &(uscript_lc_playsound));
    luapas_lua_register(luaState, "PlayMusicSound", &(uscript_lc_playmusicsound));
    luapas_lua_register(luaState, "StopMusicSound", &(uscript_lc_stopmusicsound));
    luapas_lua_register(luaState, "SetSoundMask", &(uscript_lc_setsoundmask));
    luapas_lua_register(luaState, "GetTeamName", &(uscript_lc_getteamname));
    luapas_lua_register(luaState, "GetTeamIndex", &(uscript_lc_getteamindex));
    luapas_lua_register(luaState, "GetTeamClan", &(uscript_lc_getteamclan));
    luapas_lua_register(luaState, "AddTeam", &(uscript_lc_addteam));
    luapas_lua_register(luaState, "AddMissionTeam", &(uscript_lc_addmissionteam));
    luapas_lua_register(luaState, "SetTeamLabel", &(uscript_lc_setteamlabel));
    luapas_lua_register(luaState, "SetTeamPassive", &(uscript_lc_setteampassive));
    luapas_lua_register(luaState, "AddHog", &(uscript_lc_addhog));
    luapas_lua_register(luaState, "AddMissionHog", &(uscript_lc_addmissionhog));
    luapas_lua_register(luaState, "AddAmmo", &(uscript_lc_addammo));
    luapas_lua_register(luaState, "GetAmmoCount", &(uscript_lc_getammocount));
    luapas_lua_register(luaState, "HealHog", &(uscript_lc_healhog));
    luapas_lua_register(luaState, "SetHealth", &(uscript_lc_sethealth));
    luapas_lua_register(luaState, "GetHealth", &(uscript_lc_gethealth));
    luapas_lua_register(luaState, "SetEffect", &(uscript_lc_seteffect));
    luapas_lua_register(luaState, "GetEffect", &(uscript_lc_geteffect));
    luapas_lua_register(luaState, "GetHogClan", &(uscript_lc_gethogclan));
    luapas_lua_register(luaState, "GetClanColor", &(uscript_lc_getclancolor));
    luapas_lua_register(luaState, "SetClanColor", &(uscript_lc_setclancolor));
    luapas_lua_register(luaState, "GetHogVoicepack", &(uscript_lc_gethogvoicepack));
    luapas_lua_register(luaState, "GetHogFlag", &(uscript_lc_gethogflag));
    luapas_lua_register(luaState, "GetHogFort", &(uscript_lc_gethogfort));
    luapas_lua_register(luaState, "GetHogGrave", &(uscript_lc_gethoggrave));
    luapas_lua_register(luaState, "IsHogAlive", &(uscript_lc_ishogalive));
    luapas_lua_register(luaState, "IsHogLocal", &(uscript_lc_ishoglocal));
    luapas_lua_register(luaState, "GetHogTeamName", &(uscript_lc_gethogteamname));
    luapas_lua_register(luaState, "SetHogTeamName", &(uscript_lc_sethogteamname));
    luapas_lua_register(luaState, "GetHogName", &(uscript_lc_gethogname));
    luapas_lua_register(luaState, "SetHogName", &(uscript_lc_sethogname));
    luapas_lua_register(luaState, "GetHogLevel", &(uscript_lc_gethoglevel));
    luapas_lua_register(luaState, "SetHogLevel", &(uscript_lc_sethoglevel));
    luapas_lua_register(luaState, "GetX", &(uscript_lc_getx));
    luapas_lua_register(luaState, "GetY", &(uscript_lc_gety));
    luapas_lua_register(luaState, "CopyPV", &(uscript_lc_copypv));
    luapas_lua_register(luaState, "FollowGear", &(uscript_lc_followgear));
    luapas_lua_register(luaState, "GetFollowGear", &(uscript_lc_getfollowgear));
    luapas_lua_register(luaState, "SetState", &(uscript_lc_setstate));
    luapas_lua_register(luaState, "GetState", &(uscript_lc_getstate));
    luapas_lua_register(luaState, "GetTag", &(uscript_lc_gettag));
    luapas_lua_register(luaState, "SetTag", &(uscript_lc_settag));
    luapas_lua_register(luaState, "SetTimer", &(uscript_lc_settimer));
    luapas_lua_register(luaState, "GetTimer", &(uscript_lc_gettimer));
    luapas_lua_register(luaState, "SetFlightTime", &(uscript_lc_setflighttime));
    luapas_lua_register(luaState, "GetFlightTime", &(uscript_lc_getflighttime));
    luapas_lua_register(luaState, "SetZoom", &(uscript_lc_setzoom));
    luapas_lua_register(luaState, "GetZoom", &(uscript_lc_getzoom));
    luapas_lua_register(luaState, "HogSay", &(uscript_lc_hogsay));
    luapas_lua_register(luaState, "SwitchHog", &(uscript_lc_switchhog));
    luapas_lua_register(luaState, "EnableSwitchHog", &(uscript_lc_enableswitchhog));
    luapas_lua_register(luaState, "HogTurnLeft", &(uscript_lc_hogturnleft));
    luapas_lua_register(luaState, "GetGearElasticity", &(uscript_lc_getgearelasticity));
    luapas_lua_register(luaState, "SetGearElasticity", &(uscript_lc_setgearelasticity));
    luapas_lua_register(luaState, "GetGearFriction", &(uscript_lc_getgearfriction));
    luapas_lua_register(luaState, "SetGearFriction", &(uscript_lc_setgearfriction));
    luapas_lua_register(luaState, "GetGearRadius", &(uscript_lc_getgearradius));
    luapas_lua_register(luaState, "GetGearMessage", &(uscript_lc_getgearmessage));
    luapas_lua_register(luaState, "SetGearMessage", &(uscript_lc_setgearmessage));
    luapas_lua_register(luaState, "GetGearPos", &(uscript_lc_getgearpos));
    luapas_lua_register(luaState, "SetGearPos", &(uscript_lc_setgearpos));
    luapas_lua_register(luaState, "GetGearCollisionMask", &(uscript_lc_getgearcollisionmask));
    luapas_lua_register(luaState, "SetGearCollisionMask", &(uscript_lc_setgearcollisionmask));
    luapas_lua_register(luaState, "GetRandom", &(uscript_lc_getrandom));
    luapas_lua_register(luaState, "SetWind", &(uscript_lc_setwind));
    luapas_lua_register(luaState, "GetWind", &(uscript_lc_getwind));
    luapas_lua_register(luaState, "MapHasBorder", &(uscript_lc_maphasborder));
    luapas_lua_register(luaState, "GetHogHat", &(uscript_lc_gethoghat));
    luapas_lua_register(luaState, "SetHogHat", &(uscript_lc_sethoghat));
    luapas_lua_register(luaState, "EraseSprite", &(uscript_lc_erasesprite));
    luapas_lua_register(luaState, "PlaceSprite", &(uscript_lc_placesprite));
    luapas_lua_register(luaState, "PlaceGirder", &(uscript_lc_placegirder));
    luapas_lua_register(luaState, "PlaceRubber", &(uscript_lc_placerubber));
    luapas_lua_register(luaState, "GetCurAmmoType", &(uscript_lc_getcurammotype));
    luapas_lua_register(luaState, "TestRectForObstacle", &(uscript_lc_testrectforobstacle));
    luapas_lua_register(luaState, "GetGravity", &(uscript_lc_getgravity));
    luapas_lua_register(luaState, "SetGravity", &(uscript_lc_setgravity));
    luapas_lua_register(luaState, "SetWaterLine", &(uscript_lc_setwaterline));
    luapas_lua_register(luaState, "SetNextWeapon", &(uscript_lc_setnextweapon));
    luapas_lua_register(luaState, "SetWeapon", &(uscript_lc_setweapon));
    luapas_lua_register(luaState, "SetCinematicMode", &(uscript_lc_setcinematicmode));
    luapas_lua_register(luaState, "SetMaxBuildDistance", &(uscript_lc_setmaxbuilddistance));
    luapas_lua_register(luaState, "GetAmmoName", &(uscript_lc_getammoname));
    luapas_lua_register(luaState, "GetAmmoTimer", &(uscript_lc_getammotimer));
    luapas_lua_register(luaState, "SetVampiric", &(uscript_lc_setvampiric));
    luapas_lua_register(luaState, "GetVampiric", &(uscript_lc_getvampiric));
    luapas_lua_register(luaState, "SetLaserSight", &(uscript_lc_setlasersight));
    luapas_lua_register(luaState, "GetLaserSight", &(uscript_lc_getlasersight));
    luapas_lua_register(luaState, "Explode", &(uscript_lc_explode));
    luapas_lua_register(luaState, "SetTurnTimeLeft", &(uscript_lc_setturntimeleft));
    luapas_lua_register(luaState, "SetReadyTimeLeft", &(uscript_lc_setreadytimeleft));
    luapas_lua_register(luaState, "SetTurnTimePaused", &(uscript_lc_setturntimepaused));
    luapas_lua_register(luaState, "GetTurnTimePaused", &(uscript_lc_getturntimepaused));
    luapas_lua_register(luaState, "AddPoint", &(uscript_lc_addPoint));
    luapas_lua_register(luaState, "FlushPoints", &(uscript_lc_flushPoints));
    luapas_lua_register(luaState, "SetGearAIHints", &(uscript_lc_setgearaihints));
    luapas_lua_register(luaState, "HedgewarsScriptLoad", &(uscript_lc_hedgewarsscriptload));
    luapas_lua_register(luaState, "DeclareAchievement", &(uscript_lc_declareachievement));
    luapas_lua_register(luaState, "StartGhostPoints", &(uscript_lc_startghostpoints));
    luapas_lua_register(luaState, "DumpPoint", &(uscript_lc_dumppoint));
    uscript_ScriptSetInteger(__str448, HaltTestSuccess);
    uscript_ScriptSetInteger(__str449, HaltTestFailed);
    luapas_lua_register(luaState, "EndLuaTest", &(uscript_lc_endluatest));
    uscript_ScriptClearStack();
    ScriptLoaded = false;
};
void uscript_freeModule()
{
    lua_close(luaState);
};
