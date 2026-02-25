#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uFloat.h"
#include "GL.h"
#include "uConsts.h"
#include "Math.h"
typedef struct __HwColor4f {
            Byte r;
            Byte g;
            Byte b;
            Byte a;
        } HwColor4f;
typedef enum {gsLandGen = 0x0,
              gsStart = 0x1,
              gsGame = 0x2,
              gsConfirm = 0x3,
              gsExit = 0x4,
              gsSuspend = 0x5} TGameState;
typedef enum {gmtLocal = 0x0,
              gmtDemo = 0x1,
              gmtNet = 0x2,
              gmtSave = 0x3,
              gmtLandPreview = 0x4,
              gmtBadSyntax = 0x5,
              gmtRecord = 0x6,
              gmtSyntaxHelp = 0x7} TGameType;
typedef enum {ptNone = 0x0,
              ptData = 0x1,
              ptGraphics = 0x2,
              ptThemes = 0x3,
              ptCurrTheme = 0x4,
              ptConfig = 0x5,
              ptTeams = 0x6,
              ptMaps = 0x7,
              ptMapCurrent = 0x8,
              ptDemos = 0x9,
              ptSounds = 0xa,
              ptGraves = 0xb,
              ptFonts = 0xc,
              ptForts = 0xd,
              ptLocale = 0xe,
              ptAmmoMenu = 0xf,
              ptHedgehog = 0x10,
              ptVoices = 0x11,
              ptHats = 0x12,
              ptFlags = 0x13,
              ptMissionMaps = 0x14,
              ptSuddenDeath = 0x15,
              ptButtons = 0x16,
              ptShaders = 0x17,
              ptDefaultVoice = 0x18,
              ptMisc = 0x19} TPathType;
typedef enum {sprWater = 0x0,
              sprCloud = 0x1,
              sprBomb = 0x2,
              sprBigDigit = 0x3,
              sprBigDigitGray = 0x4,
              sprBigDigitGreen = 0x5,
              sprBigDigitRed = 0x6,
              sprFrame = 0x7,
              sprLag = 0x8,
              sprArrow = 0x9,
              sprBazookaShell = 0xa,
              sprTargetP = 0xb,
              sprBee = 0xc,
              sprSmokeTrace = 0xd,
              sprRopeHook = 0xe,
              sprExplosion50 = 0xf,
              sprMineOff = 0x10,
              sprMineOn = 0x11,
              sprMineDead = 0x12,
              sprCase = 0x13,
              sprFAid = 0x14,
              sprDynamite = 0x15,
              sprPower = 0x16,
              sprClusterBomb = 0x17,
              sprClusterParticle = 0x18,
              sprFlame = 0x19,
              sprHorizont = 0x1a,
              sprHorizontL = 0x1b,
              sprHorizontR = 0x1c,
              sprSky = 0x1d,
              sprSkyL = 0x1e,
              sprSkyR = 0x1f,
              sprAMSlot = 0x20,
              sprAMAmmos = 0x21,
              sprAMAmmosBW = 0x22,
              sprAMSlotKeys = 0x23,
              sprAMCorners = 0x24,
              sprFinger = 0x25,
              sprAirBomb = 0x26,
              sprAirplane = 0x27,
              sprAmAirplane = 0x28,
              sprAmGirder = 0x29,
              sprHHTelepMask = 0x2a,
              sprSwitch = 0x2b,
              sprParachute = 0x2c,
              sprTarget = 0x2d,
              sprRopeNode = 0x2e,
              sprQuestion = 0x2f,
              sprPowerBar = 0x30,
              sprWindBar = 0x31,
              sprWindL = 0x32,
              sprWindR = 0x33,
              sprFlake = 0x34,
              sprHandRope = 0x35,
              sprHandBazooka = 0x36,
              sprHandShotgun = 0x37,
              sprHandDEagle = 0x38,
              sprHandAirAttack = 0x39,
              sprHandBaseball = 0x3a,
              sprPHammer = 0x3b,
              sprHandBlowTorch = 0x3c,
              sprBlowTorch = 0x3d,
              sprTeleport = 0x3e,
              sprHHDeath = 0x3f,
              sprShotgun = 0x40,
              sprDEagle = 0x41,
              sprHHIdle = 0x42,
              sprMortar = 0x43,
              sprTurnsLeft = 0x44,
              sprKamikaze = 0x45,
              sprWhip = 0x46,
              sprKowtow = 0x47,
              sprSad = 0x48,
              sprWave = 0x49,
              sprHurrah = 0x4a,
              sprLemonade = 0x4b,
              sprShrug = 0x4c,
              sprJuggle = 0x4d,
              sprExplPart = 0x4e,
              sprExplPart2 = 0x4f,
              sprCakeWalk = 0x50,
              sprCakeDown = 0x51,
              sprWatermelon = 0x52,
              sprEvilTrace = 0x53,
              sprHellishBomb = 0x54,
              sprSeduction = 0x55,
              sprDress = 0x56,
              sprCensored = 0x57,
              sprDrill = 0x58,
              sprHandDrill = 0x59,
              sprHandBallgun = 0x5a,
              sprBalls = 0x5b,
              sprPlane = 0x5c,
              sprHandPlane = 0x5d,
              sprUtility = 0x5e,
              sprInvulnerable = 0x5f,
              sprVampiric = 0x60,
              sprGirder = 0x61,
              sprSpeechCorner = 0x62,
              sprSpeechEdge = 0x63,
              sprSpeechTail = 0x64,
              sprThoughtCorner = 0x65,
              sprThoughtEdge = 0x66,
              sprThoughtTail = 0x67,
              sprShoutCorner = 0x68,
              sprShoutEdge = 0x69,
              sprShoutTail = 0x6a,
              sprSniperRifle = 0x6b,
              sprBubbles = 0x6c,
              sprJetpack = 0x6d,
              sprHealth = 0x6e,
              sprHandMolotov = 0x6f,
              sprMolotov = 0x70,
              sprSmoke = 0x71,
              sprSmokeWhite = 0x72,
              sprShell = 0x73,
              sprDust = 0x74,
              sprSnowDust = 0x75,
              sprExplosives = 0x76,
              sprExplosivesRoll = 0x77,
              sprAmTeleport = 0x78,
              sprSplash = 0x79,
              sprDroplet = 0x7a,
              sprBirdy = 0x7b,
              sprHandCake = 0x7c,
              sprHandConstruction = 0x7d,
              sprHandGrenade = 0x7e,
              sprHandMelon = 0x7f,
              sprHandMortar = 0x80,
              sprHandSkip = 0x81,
              sprHandCluster = 0x82,
              sprHandDynamite = 0x83,
              sprHandHellish = 0x84,
              sprHandMine = 0x85,
              sprHandSeduction = 0x86,
              sprHandVamp = 0x87,
              sprBigExplosion = 0x88,
              sprSmokeRing = 0x89,
              sprBeeTrace = 0x8a,
              sprEgg = 0x8b,
              sprTargetBee = 0x8c,
              sprHandBee = 0x8d,
              sprFeather = 0x8e,
              sprPiano = 0x8f,
              sprHandSineGun = 0x90,
              sprPortalGun = 0x91,
              sprPortal = 0x92,
              sprCheese = 0x93,
              sprHandCheese = 0x94,
              sprHandFlamethrower = 0x95,
              sprChunk = 0x96,
              sprNote = 0x97,
              sprSMineOff = 0x98,
              sprSMineOn = 0x99,
              sprHandSMine = 0x9a,
              sprHammer = 0x9b,
              sprHandResurrector = 0x9c,
              sprCross = 0x9d,
              sprAirDrill = 0x9e,
              sprNapalmBomb = 0x9f,
              sprBulletHit = 0xa0,
              sprSnowball = 0xa1,
              sprHandSnowball = 0xa2,
              sprSnow = 0xa3,
              sprSDFlake = 0xa4,
              sprSDWater = 0xa5,
              sprSDCloud = 0xa6,
              sprSDSplash = 0xa7,
              sprSDDroplet = 0xa8,
              sprTardis = 0xa9,
              sprSlider = 0xaa,
              sprBotlevels = 0xab,
              sprHandKnife = 0xac,
              sprKnife = 0xad,
              sprStar = 0xae,
              sprIceTexture = 0xaf,
              sprIceGun = 0xb0,
              sprFrozenHog = 0xb1,
              sprAmRubber = 0xb2,
              sprBoing = 0xb3,
              sprCustom1 = 0xb4,
              sprCustom2 = 0xb5,
              sprCustom3 = 0xb6,
              sprCustom4 = 0xb7,
              sprCustom5 = 0xb8,
              sprCustom6 = 0xb9,
              sprCustom7 = 0xba,
              sprCustom8 = 0xbb,
              sprFrozenAirMine = 0xbc,
              sprAirMine = 0xbd,
              sprHandAirMine = 0xbe,
              sprFlakeL = 0xbf,
              sprSDFlakeL = 0xc0,
              sprCloudL = 0xc1,
              sprSDCloudL = 0xc2,
              sprCreeper = 0xc3,
              sprHandCreeper = 0xc4,
              sprMinigun = 0xc5,
              sprSliderInverted = 0xc6,
              sprFingerBack = 0xc7,
              sprFingerBackInv = 0xc8,
              sprTargetPBack = 0xc9,
              sprTargetPBackInv = 0xca,
              sprHealthHud = 0xcb,
              sprHealthPoisonHud = 0xcc,
              sprVampHud = 0xcd,
              sprKarmaHud = 0xce,
              sprMedicHud = 0xcf,
              sprMedicPoisonHud = 0xd0,
              sprHaloHud = 0xd1,
              sprInvulnHUD = 0xd2,
              sprAmPiano = 0xd3,
              sprHandLandGun = 0xd4,
              sprFirePunch = 0xd5,
              sprThroughWrap = 0xd6,
              sprDynamiteDefused = 0xd7,
              sprHogBubble = 0xd8,
              sprHappy = 0xd9,
              sprSentry = 0xda,
              sprHandSentry = 0xdb} TSprite;
typedef enum {gtFlame = 0x0,
              gtHedgehog = 0x1,
              gtMine = 0x2,
              gtCase = 0x3,
              gtAirMine = 0x4,
              gtExplosives = 0x5,
              gtGrenade = 0x6,
              gtShell = 0x7,
              gtGrave = 0x8,
              gtBee = 0x9,
              gtShotgunShot = 0xa,
              gtPickHammer = 0xb,
              gtRope = 0xc,
              gtDEagleShot = 0xd,
              gtDynamite = 0xe,
              gtClusterBomb = 0xf,
              gtCluster = 0x10,
              gtShover = 0x11,
              gtFirePunch = 0x12,
              gtATStartGame = 0x13,
              gtATFinishGame = 0x14,
              gtParachute = 0x15,
              gtAirAttack = 0x16,
              gtAirBomb = 0x17,
              gtBlowTorch = 0x18,
              gtGirder = 0x19,
              gtTeleport = 0x1a,
              gtSwitcher = 0x1b,
              gtTarget = 0x1c,
              gtMortar = 0x1d,
              gtWhip = 0x1e,
              gtKamikaze = 0x1f,
              gtCake = 0x20,
              gtSeduction = 0x21,
              gtWatermelon = 0x22,
              gtMelonPiece = 0x23,
              gtHellishBomb = 0x24,
              gtWaterUp = 0x25,
              gtDrill = 0x26,
              gtBallGun = 0x27,
              gtBall = 0x28,
              gtRCPlane = 0x29,
              gtSniperRifleShot = 0x2a,
              gtJetpack = 0x2b,
              gtMolotov = 0x2c,
              gtBirdy = 0x2d,
              gtEgg = 0x2e,
              gtPortal = 0x2f,
              gtPiano = 0x30,
              gtGasBomb = 0x31,
              gtSineGunShot = 0x32,
              gtFlamethrower = 0x33,
              gtSMine = 0x34,
              gtPoisonCloud = 0x35,
              gtHammer = 0x36,
              gtHammerHit = 0x37,
              gtResurrector = 0x38,
              gtNapalmBomb = 0x39,
              gtSnowball = 0x3a,
              gtFlake = 0x3b,
              gtLandGun = 0x3c,
              gtTardis = 0x3d,
              gtIceGun = 0x3e,
              gtAddAmmo = 0x3f,
              gtGenericFaller = 0x40,
              gtKnife = 0x41,
              gtCreeper = 0x42,
              gtMinigun = 0x43,
              gtMinigunBullet = 0x44,
              gtSentry = 0x45} TGearType;
typedef enum {vgtFlake = 0x0,
              vgtCloud = 0x1,
              vgtExplPart = 0x2,
              vgtExplPart2 = 0x3,
              vgtFire = 0x4,
              vgtSmallDamageTag = 0x5,
              vgtTeamHealthSorter = 0x6,
              vgtSpeechBubble = 0x7,
              vgtBubble = 0x8,
              vgtSteam = 0x9,
              vgtAmmo = 0xa,
              vgtSmoke = 0xb,
              vgtSmokeWhite = 0xc,
              vgtShell = 0xd,
              vgtDust = 0xe,
              vgtSplash = 0xf,
              vgtDroplet = 0x10,
              vgtSmokeRing = 0x11,
              vgtBeeTrace = 0x12,
              vgtEgg = 0x13,
              vgtFeather = 0x14,
              vgtHealthTag = 0x15,
              vgtSmokeTrace = 0x16,
              vgtEvilTrace = 0x17,
              vgtExplosion = 0x18,
              vgtBigExplosion = 0x19,
              vgtChunk = 0x1a,
              vgtNote = 0x1b,
              vgtLineTrail = 0x1c,
              vgtBulletHit = 0x1d,
              vgtCircle = 0x1e,
              vgtSmoothWindBar = 0x1f,
              vgtStraightShot = 0x20,
              vgtNoPlaceWarn = 0x21} TVisualGearType;
typedef enum {dsUnknown = 0x0,
              dsFall = 0x1,
              dsBullet = 0x2,
              dsExplosion = 0x3,
              dsShove = 0x4,
              dsPoison = 0x5,
              dsHammer = 0x6} TDamageSource;
typedef enum {sndNone = 0x0,
              sndGrenadeImpact = 0x1,
              sndExplosion = 0x2,
              sndThrowPowerUp = 0x3,
              sndThrowRelease = 0x4,
              sndSplash = 0x5,
              sndShotgunReload = 0x6,
              sndShotgunFire = 0x7,
              sndGraveImpact = 0x8,
              sndMineImpact = 0x9,
              sndMineTick = 0xa,
              sndMudballImpact = 0xb,
              sndPickhammer = 0xc,
              sndGun = 0xd,
              sndBee = 0xe,
              sndJump1 = 0xf,
              sndJump2 = 0x10,
              sndJump3 = 0x11,
              sndYesSir = 0x12,
              sndLaugh = 0x13,
              sndIllGetYou = 0x14,
              sndJustYouWait = 0x15,
              sndIncoming = 0x16,
              sndMissed = 0x17,
              sndStupid = 0x18,
              sndFirstBlood = 0x19,
              sndBoring = 0x1a,
              sndByeBye = 0x1b,
              sndSameTeam = 0x1c,
              sndNutter = 0x1d,
              sndReinforce = 0x1e,
              sndTraitor = 0x1f,
              sndRegret = 0x20,
              sndEnemyDown = 0x21,
              sndCoward = 0x22,
              sndHurry = 0x23,
              sndWatchIt = 0x24,
              sndKamikaze = 0x25,
              sndCake = 0x26,
              sndOw1 = 0x27,
              sndOw2 = 0x28,
              sndOw3 = 0x29,
              sndOw4 = 0x2a,
              sndFirePunch1 = 0x2b,
              sndFirePunch2 = 0x2c,
              sndFirePunch3 = 0x2d,
              sndFirePunch4 = 0x2e,
              sndFirePunch5 = 0x2f,
              sndFirePunch6 = 0x30,
              sndMelon = 0x31,
              sndHellish = 0x32,
              sndYoohoo = 0x33,
              sndRCPlane = 0x34,
              sndWhipCrack = 0x35,
              sndRideOfTheValkyries = 0x36,
              sndDenied = 0x37,
              sndPlaced = 0x38,
              sndBaseballBat = 0x39,
              sndVaporize = 0x3a,
              sndWarp = 0x3b,
              sndSuddenDeath = 0x3c,
              sndMortar = 0x3d,
              sndShutter = 0x3e,
              sndHomerun = 0x3f,
              sndMolotov = 0x40,
              sndCover = 0x41,
              sndUhOh = 0x42,
              sndOops = 0x43,
              sndNooo = 0x44,
              sndHello = 0x45,
              sndRopeShot = 0x46,
              sndRopeAttach = 0x47,
              sndRopeRelease = 0x48,
              sndSwitchHog = 0x49,
              sndVictory = 0x4a,
              sndFlawless = 0x4b,
              sndSniperReload = 0x4c,
              sndSteps = 0x4d,
              sndLowGravity = 0x4e,
              sndHellishImpact1 = 0x4f,
              sndHellishImpact2 = 0x50,
              sndHellishImpact3 = 0x51,
              sndHellishImpact4 = 0x52,
              sndMelonImpact = 0x53,
              sndDroplet1 = 0x54,
              sndDroplet2 = 0x55,
              sndDroplet3 = 0x56,
              sndEggBreak = 0x57,
              sndDrillRocket = 0x58,
              sndPoisonCough = 0x59,
              sndPoisonMoan = 0x5a,
              sndBirdyLay = 0x5b,
              sndWhistle = 0x5c,
              sndBeeWater = 0x5d,
              sndPiano0 = 0x5e,
              sndPiano1 = 0x5f,
              sndPiano2 = 0x60,
              sndPiano3 = 0x61,
              sndPiano4 = 0x62,
              sndPiano5 = 0x63,
              sndPiano6 = 0x64,
              sndPiano7 = 0x65,
              sndPiano8 = 0x66,
              sndSkip = 0x67,
              sndSineGun = 0x68,
              sndOoff1 = 0x69,
              sndOoff2 = 0x6a,
              sndOoff3 = 0x6b,
              sndWhack = 0x6c,
              sndComeonthen = 0x6d,
              sndParachute = 0x6e,
              sndBump = 0x6f,
              sndResurrector = 0x70,
              sndPlane = 0x71,
              sndTardis = 0x72,
              sndFrozenHogImpact = 0x73,
              sndIceBeam = 0x74,
              sndHogFreeze = 0x75,
              sndAirMineImpact = 0x76,
              sndKnifeImpact = 0x77,
              sndExtraTime = 0x78,
              sndLaserSight = 0x79,
              sndInvulnerable = 0x7a,
              sndJetpackLaunch = 0x7b,
              sndJetpackBoost = 0x7c,
              sndPortalShot = 0x7d,
              sndPortalSwitch = 0x7e,
              sndPortalOpen = 0x7f,
              sndBlowTorch = 0x80,
              sndCountdown1 = 0x81,
              sndCountdown2 = 0x82,
              sndCountdown3 = 0x83,
              sndCountdown4 = 0x84,
              sndCreeperDrop = 0x85,
              sndCreeperWater = 0x86,
              sndCreeperDie = 0x87,
              sndCustom1 = 0x88,
              sndCustom2 = 0x89,
              sndCustom3 = 0x8a,
              sndCustom4 = 0x8b,
              sndCustom5 = 0x8c,
              sndCustom6 = 0x8d,
              sndCustom7 = 0x8e,
              sndCustom8 = 0x8f,
              sndMinigun = 0x90,
              sndFlamethrower = 0x91,
              sndIceBeamIdle = 0x92,
              sndLandGun = 0x93,
              sndCaseImpact = 0x94,
              sndExtraDamage = 0x95,
              sndFirePunchHit = 0x96,
              sndGrenade = 0x97,
              sndThisOneIsMine = 0x98,
              sndWhatThe = 0x99,
              sndSoLong = 0x9a,
              sndOhDear = 0x9b,
              sndGonnaGetYou = 0x9c,
              sndDrat = 0x9d,
              sndBugger = 0x9e,
              sndAmazing = 0x9f,
              sndBrilliant = 0xa0,
              sndExcellent = 0xa1,
              sndFire = 0xa2,
              sndWatchThis = 0xa3,
              sndRunAway = 0xa4,
              sndRevenge = 0xa5,
              sndCutItOut = 0xa6,
              sndLeaveMeAlone = 0xa7,
              sndOuch = 0xa8,
              sndHmm = 0xa9,
              sndKiss = 0xaa,
              sndFlyAway = 0xab,
              sndPlaneWater = 0xac,
              sndDynamiteFuse = 0xad,
              sndDynamiteImpact = 0xae} TSound;
typedef enum {amNothing = 0x0,
              amGrenade = 0x1,
              amClusterBomb = 0x2,
              amBazooka = 0x3,
              amBee = 0x4,
              amShotgun = 0x5,
              amPickHammer = 0x6,
              amSkip = 0x7,
              amRope = 0x8,
              amMine = 0x9,
              amDEagle = 0xa,
              amDynamite = 0xb,
              amFirePunch = 0xc,
              amWhip = 0xd,
              amBaseballBat = 0xe,
              amParachute = 0xf,
              amAirAttack = 0x10,
              amMineStrike = 0x11,
              amBlowTorch = 0x12,
              amGirder = 0x13,
              amTeleport = 0x14,
              amSwitch = 0x15,
              amMortar = 0x16,
              amKamikaze = 0x17,
              amCake = 0x18,
              amSeduction = 0x19,
              amWatermelon = 0x1a,
              amHellishBomb = 0x1b,
              amNapalm = 0x1c,
              amDrill = 0x1d,
              amBallgun = 0x1e,
              amRCPlane = 0x1f,
              amLowGravity = 0x20,
              amExtraDamage = 0x21,
              amInvulnerable = 0x22,
              amExtraTime = 0x23,
              amLaserSight = 0x24,
              amVampiric = 0x25,
              amSniperRifle = 0x26,
              amJetpack = 0x27,
              amMolotov = 0x28,
              amBirdy = 0x29,
              amPortalGun = 0x2a,
              amPiano = 0x2b,
              amGasBomb = 0x2c,
              amSineGun = 0x2d,
              amFlamethrower = 0x2e,
              amSMine = 0x2f,
              amHammer = 0x30,
              amResurrector = 0x31,
              amDrillStrike = 0x32,
              amSnowball = 0x33,
              amTardis = 0x34,
              amLandGun = 0x35,
              amIceGun = 0x36,
              amKnife = 0x37,
              amRubber = 0x38,
              amAirMine = 0x39,
              amCreeper = 0x3a,
              amMinigun = 0x3b,
              amSentry = 0x3c} TAmmoType;
typedef enum {HealthCrate = 0x0,
              AmmoCrate = 0x1,
              UtilityCrate = 0x2} TCrateType;
typedef enum {fnt16 = 0x0,
              fntBig = 0x1,
              fntSmall = 0x2,
              fntChat = 0x3} THWFont;
typedef enum {capgrpGameState = 0x0,
              capgrpAmmoinfo = 0x1,
              capgrpVolume = 0x2,
              capgrpMessage = 0x3,
              capgrpMessage2 = 0x4,
              capgrpAmmostate = 0x5} TCapGroup;
typedef enum {siGameResult = 0x0,
              siMaxStepDamage = 0x1,
              siMaxStepKills = 0x2,
              siKilledHHs = 0x3,
              siClanHealth = 0x4,
              siTeamStats = 0x5,
              siPlayerKills = 0x6,
              siMaxTeamDamage = 0x7,
              siMaxTeamKills = 0x8,
              siMaxTurnSkips = 0x9,
              siCustomAchievement = 0xa,
              siGraphTitle = 0xb,
              siPointType = 0xc,
              siTeamRank = 0xd,
              siEverAfter = 0xe} TStatInfoType;
typedef enum {waveRollup = 0x0,
              waveSad = 0x1,
              waveWave = 0x2,
              waveHurrah = 0x3,
              waveLemonade = 0x4,
              waveShrug = 0x5,
              waveJuggle = 0x6,
              waveBubble = 0x7,
              waveHappy = 0x8} TWave;
typedef enum {rmDefault = 0x0,
              rmLeftEye = 0x1,
              rmRightEye = 0x2} TRenderMode;
typedef enum {smNone = 0x0,
              smRedCyan = 0x1,
              smCyanRed = 0x2,
              smRedBlue = 0x3,
              smBlueRed = 0x4,
              smRedGreen = 0x5,
              smGreenRed = 0x6,
              smHorizontal = 0x7,
              smVertical = 0x8} TStereoMode;
typedef enum {weNone = 0x0,
              weWrap = 0x1,
              weBounce = 0x2,
              weSea = 0x3,
              weSky = 0x4} TWorldEdge;
typedef enum {uiAll = 0x0,
              uiNoTeams = 0x1,
              uiNone = 0x2} TUIDisplay;
typedef enum {mgRandom = 0x0,
              mgMaze = 0x1,
              mgPerlin = 0x2,
              mgDrawn = 0x3,
              mgForts = 0x4,
              mgWFC = 0x5} TMapGen;
typedef struct __THHFont {
            PTTF_Font Handle;
            LongInt Height;
            LongInt style;
            string255 Name;
        } THHFont;
typedef struct __TAmmo * PAmmo;
typedef struct __TAmmo {
            LongWord Propz;
            LongWord Count;
            LongWord NumPerTurn;
            LongWord Timer;
            LongWord Pos;
            TAmmoType AmmoType;
            TSound AttackVoice;
            LongWord Bounciness;
        } TAmmo;
typedef struct __TVertex2f {
            GLfloat X;
            GLfloat Y;
        } TVertex2f;
typedef struct __TVertex2i {
            GLint X;
            GLint Y;
        } TVertex2i;
typedef GLfloat TMatrix4x4f[(3 + 1)][(3 + 1)];
typedef struct __TTexture * PTexture;
typedef struct __TTexture {
            GLuint id;
            LongInt w;
            LongInt h;
            LongInt scale;
            GLfloat rx;
            GLfloat ry;
            GLfloat priority;
            TVertex2f vb[(3 + 1)];
            TVertex2f tb[(3 + 1)];
            PTexture PrevTexture;
            PTexture NextTexture;
        } TTexture;
typedef enum {heInvulnerable = 0x0,
              heResurrectable = 0x1,
              hePoisoned = 0x2,
              heResurrected = 0x3,
              heFrozen = 0x4,
              heArtillery = 0x5} THogEffect;
typedef enum {sfNone = 0x0,
              sfInit = 0x1,
              sfToBlack = 0x2,
              sfFromBlack = 0x3,
              sfToWhite = 0x4,
              sfFromWhite = 0x5} TScreenFade;
typedef struct __TGear * PGear;
typedef struct __THedgehog * PHedgehog;
typedef struct __TTeam * PTeam;
typedef struct __TClan * PClan;
typedef void(*utypes_TGearStepProcedure)(PGear Gear);
typedef struct __TGear {
            PGear NextGear;
            PGear PrevGear;
            LongWord Z;
            boolean Active;
            TGearType Kind;
            utypes_TGearStepProcedure doStep;
            TAmmoType AmmoType;
            boolean RenderTimer;
            boolean RenderHealth;
            TPoint Target;
            LongWord AIHints;
            PHedgehog LastDamage;
            LongInt CollisionIndex;
            LongWord Message;
            LongWord uid;
            PHedgehog Hedgehog;
            hwFloat X;
            hwFloat Y;
            hwFloat dX;
            hwFloat dY;
            LongWord State;
            LongWord PortalCounter;
            LongInt Radius;
            Word CollisionMask;
            LongWord AdvBounce;
            boolean Sticky;
            hwFloat Elasticity;
            hwFloat Friction;
            hwFloat Density;
            TSound ImpactSound;
            Word nImpactSounds;
            LongInt Health;
            LongInt Damage;
            LongInt Karma;
            real DirAngle;
            LongWord Boom;
            LongWord Pos;
            LongWord Angle;
            LongWord Power;
            LongWord Timer;
            LongWord WDTimer;
            LongInt Tag;
            LongWord FlightTime;
            LongWord MsgParam;
            PTexture Tex;
            LongWord Tint;
            PGear LinkedGear;
            LongInt SoundChannel;
            pointer Data;
        } TGear;
typedef PGear * TPGearArray;
typedef struct __PGearArrayS {
            LongWord size;
            TPGearArray * ar;
        } PGearArrayS;
typedef struct __TVisualGear * PVisualGear;
typedef void(*utypes_TVGearStepProcedure)(PVisualGear Gear,LongWord Steps);
typedef struct __TVisualGear {
            PVisualGear NextGear;
            PVisualGear PrevGear;
            LongWord Frame;
            LongWord FrameTicks;
            real X;
            real Y;
            real dX;
            real dY;
            real tdX;
            real tdY;
            LongWord State;
            LongWord Timer;
            real Angle;
            real dAngle;
            TVisualGearType Kind;
            utypes_TVGearStepProcedure doStep;
            PTexture Tex;
            GLfloat alpha;
            GLfloat scale;
            PHedgehog Hedgehog;
            LongInt Tag;
            string255 Text;
            LongWord Tint;
            LongWord uid;
            Byte Layer;
        } TVisualGear;
typedef struct __TStatistics {
            LongWord DamageRecv;
            LongWord DamageGiven;
            LongWord StepDamageRecvInRow;
            LongWord StepDamageRecv;
            LongWord StepDamageGiven;
            LongWord StepKills;
            boolean StepPoisoned;
            boolean StepDied;
            boolean Sacrificed;
            boolean GotRevenge;
            boolean StepRevenge;
            LongWord MaxStepDamageRecv;
            LongWord MaxStepDamageGiven;
            LongWord MaxStepKills;
            LongWord FinishedTurns;
        } TStatistics;
typedef struct __TTeamStats {
            LongWord Kills;
            LongWord Suicides;
            LongWord AIKills;
            LongWord TeamKills;
            LongWord TurnSkips;
            LongWord TeamDamage;
        } TTeamStats;
typedef struct __TClanDeathLogEntry * PClanDeathLogEntry;
typedef struct __TClanDeathLogEntry {
            LongWord Turn;
            PClan KilledClans[cMaxTeams];
            LongWord KilledClansCount;
            PClanDeathLogEntry NextEntry;
        } TClanDeathLogEntry;
typedef struct __TBinds {
            Byte indices[(cKbdMaxIndex + 1)];
            string255 binds[(255 + 1)];
            Byte lastIndex;
        } TBinds;
typedef Byte TKeyboardState[(cKeyMaxIndex + 1)];
typedef struct __TVoicepack * PVoicepack;
typedef struct __TVoicepack {
            string255 name;
            PMixChunk chunks[175];
        } TVoicepack;
typedef struct __TVoice {
            TSound snd;
            PVoicepack voicepack;
            boolean isFallback;
        } TVoice;
typedef TAmmo THHAmmo[(cMaxSlotIndex + 1)][(cMaxSlotAmmoIndex + 1)];
typedef THHAmmo * PHHAmmo;
typedef struct __THedgehog {
            string255 Name;
            PGear Gear;
            PGear GearHidden;
            PVisualGear SpeechGear;
            PTexture NameTagTex;
            PTexture HealthTagTex;
            PTexture HatTex;
            PHHAmmo Ammo;
            TAmmoType CurAmmoType;
            LongWord PickUpType;
            LongInt PickUpDelay;
            LongWord AmmoStore;
            PTeam Team;
            LongWord MultiShootAttacks;
            LongWord visStepPos;
            Byte BotLevel;
            GLfloat HatVisibility;
            TStatistics stats;
            string255 Hat;
            LongInt InitialHealth;
            boolean King;
            boolean Unplaced;
            boolean UnplacedKing;
            LongWord Timer;
            LongInt HealthBarHealth;
            LongInt Effects[6];
            PHedgehog RevengeHog;
            boolean FlownOffMap;
        } THedgehog;
typedef struct __TTeam {
            PClan Clan;
            string255 TeamName;
            boolean ExtDriven;
            TBinds Binds;
            THedgehog Hedgehogs[(cMaxHHIndex + 1)];
            LongWord CurrHedgehog;
            PTexture NameTagTex;
            PTexture OwnerTex;
            PTexture GraveTex;
            PTexture AIKillsTex;
            PTexture LuaTeamValueTex;
            PTexture FlagTex;
            string255 Flag;
            string255 GraveName;
            string255 FortName;
            string255 Owner;
            LongInt TeamHealth;
            LongInt TeamHealthBarHealth;
            LongInt DrawHealthY;
            LongWord AttackBar;
            LongWord HedgehogsNumber;
            PVoicepack voicepack;
            string255 PlayerHash;
            TTeamStats stats;
            boolean Passive;
            boolean hasKing;
            boolean hasGone;
            LongWord skippedTurns;
            boolean isGoneFlagPendingToBeSet;
            boolean isGoneFlagPendingToBeUnset;
            astring luaTeamValue;
            boolean hasLuaTeamValue;
        } TTeam;
typedef struct __TClan {
            LongWord Color;
            PTeam Teams[cMaxTeams];
            PTexture HealthTex;
            LongWord TeamsNumber;
            LongWord TagTeamIndex;
            LongWord CurrTeam;
            LongInt ClanHealth;
            LongInt ClanIndex;
            LongWord TurnNumber;
            boolean DeathLogged;
            boolean StatsHandled;
            boolean Flawless;
            boolean Passive;
            boolean LocalOrAlly;
        } TClan;
typedef void(*utypes_cdeclPtr)();
typedef void(*utypes_cdeclIntPtr)(LongInt num);
typedef double(*utypes_funcDoublePtr)();
typedef struct __TMobileRecord {
            utypes_cdeclIntPtr PerformRumble;
            utypes_cdeclPtr GameLoading;
            utypes_cdeclPtr GameLoaded;
            utypes_cdeclPtr SaveLoadingEnded;
        } TMobileRecord;
typedef enum {sidGrenade = 0x0,
              sidClusterBomb = 0x1,
              sidBazooka = 0x2,
              sidBee = 0x3,
              sidShotgun = 0x4,
              sidPickHammer = 0x5,
              sidSkip = 0x6,
              sidRope = 0x7,
              sidMine = 0x8,
              sidDEagle = 0x9,
              sidDynamite = 0xa,
              sidBaseballBat = 0xb,
              sidFirePunch = 0xc,
              sidSeconds = 0xd,
              sidParachute = 0xe,
              sidAirAttack = 0xf,
              sidMineStrike = 0x10,
              sidBlowTorch = 0x11,
              sidGirder = 0x12,
              sidTeleport = 0x13,
              sidSwitch = 0x14,
              sidMortar = 0x15,
              sidWhip = 0x16,
              sidKamikaze = 0x17,
              sidCake = 0x18,
              sidSeduction = 0x19,
              sidWatermelon = 0x1a,
              sidHellishBomb = 0x1b,
              sidDrill = 0x1c,
              sidBallgun = 0x1d,
              sidNapalm = 0x1e,
              sidRCPlane = 0x1f,
              sidLowGravity = 0x20,
              sidExtraDamage = 0x21,
              sidInvulnerable = 0x22,
              sidExtraTime = 0x23,
              sidLaserSight = 0x24,
              sidVampiric = 0x25,
              sidSniperRifle = 0x26,
              sidJetpack = 0x27,
              sidMolotov = 0x28,
              sidBirdy = 0x29,
              sidPortalGun = 0x2a,
              sidPiano = 0x2b,
              sidGasBomb = 0x2c,
              sidSineGun = 0x2d,
              sidFlamethrower = 0x2e,
              sidSMine = 0x2f,
              sidHammer = 0x30,
              sidResurrector = 0x31,
              sidDrillStrike = 0x32,
              sidSnowball = 0x33,
              sidNothing = 0x34,
              sidTardis = 0x35,
              sidLandGun = 0x36,
              sidIceGun = 0x37,
              sidKnife = 0x38,
              sidRubber = 0x39,
              sidAirMine = 0x3a,
              sidCreeper = 0x3b,
              sidMinigun = 0x3c,
              sidSentry = 0x3d} TAmmoStrId;
typedef enum {sidLoading = 0x0,
              sidDraw = 0x1,
              sidWinner = 0x2,
              sidVolume = 0x3,
              sidPaused = 0x4,
              sidConfirm = 0x5,
              sidSuddenDeath = 0x6,
              sidRemaining = 0x7,
              sidFuel = 0x8,
              sidSync = 0x9,
              sidNoEndTurn = 0xa,
              sidNotYetAvailable = 0xb,
              sidRoundSD = 0xc,
              sidRoundsSD = 0xd,
              sidReady = 0xe,
              sidBounce1 = 0xf,
              sidBounce2 = 0x10,
              sidBounce3 = 0x11,
              sidBounce4 = 0x12,
              sidBounce5 = 0x13,
              sidBounce = 0x14,
              sidMute = 0x15,
              sidAFK = 0x16,
              sidAutoCameraOff = 0x17,
              sidAutoCameraOn = 0x18,
              sidPressTarget = 0x19,
              sidNotAvailableInSD = 0x1a,
              sidHealthGain = 0x1b,
              sidEmptyCrate = 0x1c,
              sidUnknownKey = 0x1d,
              sidWinner2 = 0x1e,
              sidWinner3 = 0x1f,
              sidWinner4 = 0x20,
              sidWinner5 = 0x21,
              sidWinner6 = 0x22,
              sidWinner7 = 0x23,
              sidWinnerAll = 0x24,
              sidTeamGone = 0x25,
              sidTeamBack = 0x26,
              sidAutoSkip = 0x27,
              sidFPS = 0x28,
              sidLuaParsingOff = 0x29,
              sidLuaParsingOn = 0x2a,
              sidLuaParsingDenied = 0x2b,
              sidAmmoCount = 0x2c,
              sidChat = 0x2d,
              sidChatTeam = 0x2e,
              sidChatHog = 0x2f,
              sidUnknownGearValue = 0x30,
              sidVideoRecLuaFail = 0x31} TMsgStrId;
typedef enum {sidCmdHeaderBasic = 0x0,
              sidCmdTogglechat = 0x1,
              sidCmdTeam = 0x2,
              sidCmdMe = 0x3,
              sidCmdPause = 0x4,
              sidCmdPauseNet = 0x5,
              sidCmdFullscreen = 0x6,
              sidCmdQuit = 0x7,
              sidCmdHelp = 0x8,
              sidCmdHelpTaunts = 0x9,
              sidCmdHistory = 0xa,
              sidLua = 0xb,
              sidCmdHeaderTaunts = 0xc,
              sidCmdSpeech = 0xd,
              sidCmdThink = 0xe,
              sidCmdYell = 0xf,
              sidCmdSpeechNumberHint = 0x10,
              sidCmdHsa = 0x11,
              sidCmdHta = 0x12,
              sidCmdHya = 0x13,
              sidCmdHurrah = 0x14,
              sidCmdIlovelotsoflemonade = 0x15,
              sidCmdJuggle = 0x16,
              sidCmdRollup = 0x17,
              sidCmdShrug = 0x18,
              sidCmdWave = 0x19,
              sidCmdUnknown = 0x1a,
              sidCmdHelpRoom = 0x1b,
              sidCmdHelpRoomFail = 0x1c,
              sidCmdBubble = 0x1d,
              sidCmdHappy = 0x1e,
              sidCmdSad = 0x1f} TCmdHelpStrId;
typedef enum {eidDied = 0x0,
              eidDrowned = 0x1,
              eidRoundStart = 0x2,
              eidRoundWin = 0x3,
              eidRoundDraw = 0x4,
              eidNewHealthPack = 0x5,
              eidNewAmmoPack = 0x6,
              eidNewUtilityPack = 0x7,
              eidTurnSkipped = 0x8,
              eidHurtSelf = 0x9,
              eidHomerun = 0xa,
              eidGone = 0xb,
              eidPoisoned = 0xc,
              eidResurrected = 0xd,
              eidKamikaze = 0xe,
              eidTimeTravelEnd = 0xf,
              eidTimeout = 0x10,
              eidKingDied = 0x11} TEventId;
typedef enum {gidCaption = 0x0,
              gidSubCaption = 0x1,
              gidPlaceKing = 0x2,
              gidLowGravity = 0x3,
              gidInvulnerable = 0x4,
              gidVampiric = 0x5,
              gidKarma = 0x6,
              gidKing = 0x7,
              gidPlaceHog = 0x8,
              gidArtillery = 0x9,
              gidSolidLand = 0xa,
              gidSharedAmmo = 0xb,
              gidMineTimer = 0xc,
              gidNoMineTimer = 0xd,
              gidRandomMineTimer = 0xe,
              gidDamageModifier = 0xf,
              gidResetHealth = 0x10,
              gidAISurvival = 0x11,
              gidInfAttack = 0x12,
              gidResetWeps = 0x13,
              gidPerHogAmmo = 0x14,
              gidTagTeam = 0x15,
              gidMoreWind = 0x16} TGoalStrId;
typedef Byte * (*TDirtyTag);
typedef struct __TGear * TGearPackArray;
typedef Byte TPreview[(127 + 1)][(31 + 1)];
typedef Byte TPreviewAlpha[(127 + 1)][(255 + 1)];
typedef struct __TWidgetMovement * PWidgetMovement;
typedef struct __TWidgetMovement {
            boolean animate;
            TPoint source;
            TPoint target;
            LongWord startTime;
        } TWidgetMovement;
typedef struct __TOnScreenWidget * POnScreenWidget;
typedef struct __TOnScreenWidget {
            boolean show;
            TSprite sprite;
            TSDL_Rect frame;
            TSDL_Rect active;
            LongWord fadeAnimStart;
            TWidgetMovement moveAnim;
        } TOnScreenWidget;
typedef struct __TTouch_Data * PTouch_Data;
typedef struct __TTouch_Data {
            TSDL_FingerId id;
            LongInt x;
            LongInt y;
            LongInt dx;
            LongInt dy;
            LongInt historicalX;
            LongInt historicalY;
            LongWord timeSinceDown;
            POnScreenWidget pressedWidget;
        } TTouch_Data;
typedef struct __TSpriteData * PSpriteData;
typedef struct __TSpriteData {
            string255 FileName;
            TPathType Path;
            TPathType AltPath;
            PTexture Texture;
            PSDL_Surface Surface;
            LongInt Width;
            LongInt Height;
            LongInt imageWidth;
            LongInt imageHeight;
            boolean saveSurf;
            boolean critical;
            boolean checkSum;
            GLfloat priority;
            boolean getDimensions;
            boolean getImageDimensions;
        } TSpriteData;
enum{cakeh = 27};
typedef struct __TCakeData {
            Integer CakeI;
            struct __CakePoints {
                hwFloat x;
                hwFloat y;
            } CakePoints[cakeh];
        } TCakeData;
typedef struct __TCakeData * PCakeData;
typedef PClan TClansArray[cMaxTeams];

string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TGoalStrId enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TEventId enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TCmdHelpStrId enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TMsgStrId enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TAmmoStrId enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TScreenFade enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const THogEffect enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TMapGen enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TUIDisplay enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TWorldEdge enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TStereoMode enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TRenderMode enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TWave enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TStatInfoType enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TCapGroup enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const THWFont enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TCrateType enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TAmmoType enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TSound enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TDamageSource enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TVisualGearType enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TGearType enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TSprite enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TPathType enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TGameType enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TGameState enumvar);