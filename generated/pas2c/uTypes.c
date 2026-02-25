#include "fpcrtl.h"

#include "uTypes.h"

string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TGoalStrId enumvar)
{
    switch(enumvar){
    case gidCaption:
        return fpcrtl_make_string("gidCaption");
        break;
    case gidSubCaption:
        return fpcrtl_make_string("gidSubCaption");
        break;
    case gidPlaceKing:
        return fpcrtl_make_string("gidPlaceKing");
        break;
    case gidLowGravity:
        return fpcrtl_make_string("gidLowGravity");
        break;
    case gidInvulnerable:
        return fpcrtl_make_string("gidInvulnerable");
        break;
    case gidVampiric:
        return fpcrtl_make_string("gidVampiric");
        break;
    case gidKarma:
        return fpcrtl_make_string("gidKarma");
        break;
    case gidKing:
        return fpcrtl_make_string("gidKing");
        break;
    case gidPlaceHog:
        return fpcrtl_make_string("gidPlaceHog");
        break;
    case gidArtillery:
        return fpcrtl_make_string("gidArtillery");
        break;
    case gidSolidLand:
        return fpcrtl_make_string("gidSolidLand");
        break;
    case gidSharedAmmo:
        return fpcrtl_make_string("gidSharedAmmo");
        break;
    case gidMineTimer:
        return fpcrtl_make_string("gidMineTimer");
        break;
    case gidNoMineTimer:
        return fpcrtl_make_string("gidNoMineTimer");
        break;
    case gidRandomMineTimer:
        return fpcrtl_make_string("gidRandomMineTimer");
        break;
    case gidDamageModifier:
        return fpcrtl_make_string("gidDamageModifier");
        break;
    case gidResetHealth:
        return fpcrtl_make_string("gidResetHealth");
        break;
    case gidAISurvival:
        return fpcrtl_make_string("gidAISurvival");
        break;
    case gidInfAttack:
        return fpcrtl_make_string("gidInfAttack");
        break;
    case gidResetWeps:
        return fpcrtl_make_string("gidResetWeps");
        break;
    case gidPerHogAmmo:
        return fpcrtl_make_string("gidPerHogAmmo");
        break;
    case gidTagTeam:
        return fpcrtl_make_string("gidTagTeam");
        break;
    case gidMoreWind:
        return fpcrtl_make_string("gidMoreWind");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TEventId enumvar)
{
    switch(enumvar){
    case eidDied:
        return fpcrtl_make_string("eidDied");
        break;
    case eidDrowned:
        return fpcrtl_make_string("eidDrowned");
        break;
    case eidRoundStart:
        return fpcrtl_make_string("eidRoundStart");
        break;
    case eidRoundWin:
        return fpcrtl_make_string("eidRoundWin");
        break;
    case eidRoundDraw:
        return fpcrtl_make_string("eidRoundDraw");
        break;
    case eidNewHealthPack:
        return fpcrtl_make_string("eidNewHealthPack");
        break;
    case eidNewAmmoPack:
        return fpcrtl_make_string("eidNewAmmoPack");
        break;
    case eidNewUtilityPack:
        return fpcrtl_make_string("eidNewUtilityPack");
        break;
    case eidTurnSkipped:
        return fpcrtl_make_string("eidTurnSkipped");
        break;
    case eidHurtSelf:
        return fpcrtl_make_string("eidHurtSelf");
        break;
    case eidHomerun:
        return fpcrtl_make_string("eidHomerun");
        break;
    case eidGone:
        return fpcrtl_make_string("eidGone");
        break;
    case eidPoisoned:
        return fpcrtl_make_string("eidPoisoned");
        break;
    case eidResurrected:
        return fpcrtl_make_string("eidResurrected");
        break;
    case eidKamikaze:
        return fpcrtl_make_string("eidKamikaze");
        break;
    case eidTimeTravelEnd:
        return fpcrtl_make_string("eidTimeTravelEnd");
        break;
    case eidTimeout:
        return fpcrtl_make_string("eidTimeout");
        break;
    case eidKingDied:
        return fpcrtl_make_string("eidKingDied");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TCmdHelpStrId enumvar)
{
    switch(enumvar){
    case sidCmdHeaderBasic:
        return fpcrtl_make_string("sidCmdHeaderBasic");
        break;
    case sidCmdTogglechat:
        return fpcrtl_make_string("sidCmdTogglechat");
        break;
    case sidCmdTeam:
        return fpcrtl_make_string("sidCmdTeam");
        break;
    case sidCmdMe:
        return fpcrtl_make_string("sidCmdMe");
        break;
    case sidCmdPause:
        return fpcrtl_make_string("sidCmdPause");
        break;
    case sidCmdPauseNet:
        return fpcrtl_make_string("sidCmdPauseNet");
        break;
    case sidCmdFullscreen:
        return fpcrtl_make_string("sidCmdFullscreen");
        break;
    case sidCmdQuit:
        return fpcrtl_make_string("sidCmdQuit");
        break;
    case sidCmdHelp:
        return fpcrtl_make_string("sidCmdHelp");
        break;
    case sidCmdHelpTaunts:
        return fpcrtl_make_string("sidCmdHelpTaunts");
        break;
    case sidCmdHistory:
        return fpcrtl_make_string("sidCmdHistory");
        break;
    case sidLua:
        return fpcrtl_make_string("sidLua");
        break;
    case sidCmdHeaderTaunts:
        return fpcrtl_make_string("sidCmdHeaderTaunts");
        break;
    case sidCmdSpeech:
        return fpcrtl_make_string("sidCmdSpeech");
        break;
    case sidCmdThink:
        return fpcrtl_make_string("sidCmdThink");
        break;
    case sidCmdYell:
        return fpcrtl_make_string("sidCmdYell");
        break;
    case sidCmdSpeechNumberHint:
        return fpcrtl_make_string("sidCmdSpeechNumberHint");
        break;
    case sidCmdHsa:
        return fpcrtl_make_string("sidCmdHsa");
        break;
    case sidCmdHta:
        return fpcrtl_make_string("sidCmdHta");
        break;
    case sidCmdHya:
        return fpcrtl_make_string("sidCmdHya");
        break;
    case sidCmdHurrah:
        return fpcrtl_make_string("sidCmdHurrah");
        break;
    case sidCmdIlovelotsoflemonade:
        return fpcrtl_make_string("sidCmdIlovelotsoflemonade");
        break;
    case sidCmdJuggle:
        return fpcrtl_make_string("sidCmdJuggle");
        break;
    case sidCmdRollup:
        return fpcrtl_make_string("sidCmdRollup");
        break;
    case sidCmdShrug:
        return fpcrtl_make_string("sidCmdShrug");
        break;
    case sidCmdWave:
        return fpcrtl_make_string("sidCmdWave");
        break;
    case sidCmdUnknown:
        return fpcrtl_make_string("sidCmdUnknown");
        break;
    case sidCmdHelpRoom:
        return fpcrtl_make_string("sidCmdHelpRoom");
        break;
    case sidCmdHelpRoomFail:
        return fpcrtl_make_string("sidCmdHelpRoomFail");
        break;
    case sidCmdBubble:
        return fpcrtl_make_string("sidCmdBubble");
        break;
    case sidCmdHappy:
        return fpcrtl_make_string("sidCmdHappy");
        break;
    case sidCmdSad:
        return fpcrtl_make_string("sidCmdSad");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TMsgStrId enumvar)
{
    switch(enumvar){
    case sidLoading:
        return fpcrtl_make_string("sidLoading");
        break;
    case sidDraw:
        return fpcrtl_make_string("sidDraw");
        break;
    case sidWinner:
        return fpcrtl_make_string("sidWinner");
        break;
    case sidVolume:
        return fpcrtl_make_string("sidVolume");
        break;
    case sidPaused:
        return fpcrtl_make_string("sidPaused");
        break;
    case sidConfirm:
        return fpcrtl_make_string("sidConfirm");
        break;
    case sidSuddenDeath:
        return fpcrtl_make_string("sidSuddenDeath");
        break;
    case sidRemaining:
        return fpcrtl_make_string("sidRemaining");
        break;
    case sidFuel:
        return fpcrtl_make_string("sidFuel");
        break;
    case sidSync:
        return fpcrtl_make_string("sidSync");
        break;
    case sidNoEndTurn:
        return fpcrtl_make_string("sidNoEndTurn");
        break;
    case sidNotYetAvailable:
        return fpcrtl_make_string("sidNotYetAvailable");
        break;
    case sidRoundSD:
        return fpcrtl_make_string("sidRoundSD");
        break;
    case sidRoundsSD:
        return fpcrtl_make_string("sidRoundsSD");
        break;
    case sidReady:
        return fpcrtl_make_string("sidReady");
        break;
    case sidBounce1:
        return fpcrtl_make_string("sidBounce1");
        break;
    case sidBounce2:
        return fpcrtl_make_string("sidBounce2");
        break;
    case sidBounce3:
        return fpcrtl_make_string("sidBounce3");
        break;
    case sidBounce4:
        return fpcrtl_make_string("sidBounce4");
        break;
    case sidBounce5:
        return fpcrtl_make_string("sidBounce5");
        break;
    case sidBounce:
        return fpcrtl_make_string("sidBounce");
        break;
    case sidMute:
        return fpcrtl_make_string("sidMute");
        break;
    case sidAFK:
        return fpcrtl_make_string("sidAFK");
        break;
    case sidAutoCameraOff:
        return fpcrtl_make_string("sidAutoCameraOff");
        break;
    case sidAutoCameraOn:
        return fpcrtl_make_string("sidAutoCameraOn");
        break;
    case sidPressTarget:
        return fpcrtl_make_string("sidPressTarget");
        break;
    case sidNotAvailableInSD:
        return fpcrtl_make_string("sidNotAvailableInSD");
        break;
    case sidHealthGain:
        return fpcrtl_make_string("sidHealthGain");
        break;
    case sidEmptyCrate:
        return fpcrtl_make_string("sidEmptyCrate");
        break;
    case sidUnknownKey:
        return fpcrtl_make_string("sidUnknownKey");
        break;
    case sidWinner2:
        return fpcrtl_make_string("sidWinner2");
        break;
    case sidWinner3:
        return fpcrtl_make_string("sidWinner3");
        break;
    case sidWinner4:
        return fpcrtl_make_string("sidWinner4");
        break;
    case sidWinner5:
        return fpcrtl_make_string("sidWinner5");
        break;
    case sidWinner6:
        return fpcrtl_make_string("sidWinner6");
        break;
    case sidWinner7:
        return fpcrtl_make_string("sidWinner7");
        break;
    case sidWinnerAll:
        return fpcrtl_make_string("sidWinnerAll");
        break;
    case sidTeamGone:
        return fpcrtl_make_string("sidTeamGone");
        break;
    case sidTeamBack:
        return fpcrtl_make_string("sidTeamBack");
        break;
    case sidAutoSkip:
        return fpcrtl_make_string("sidAutoSkip");
        break;
    case sidFPS:
        return fpcrtl_make_string("sidFPS");
        break;
    case sidLuaParsingOff:
        return fpcrtl_make_string("sidLuaParsingOff");
        break;
    case sidLuaParsingOn:
        return fpcrtl_make_string("sidLuaParsingOn");
        break;
    case sidLuaParsingDenied:
        return fpcrtl_make_string("sidLuaParsingDenied");
        break;
    case sidAmmoCount:
        return fpcrtl_make_string("sidAmmoCount");
        break;
    case sidChat:
        return fpcrtl_make_string("sidChat");
        break;
    case sidChatTeam:
        return fpcrtl_make_string("sidChatTeam");
        break;
    case sidChatHog:
        return fpcrtl_make_string("sidChatHog");
        break;
    case sidUnknownGearValue:
        return fpcrtl_make_string("sidUnknownGearValue");
        break;
    case sidVideoRecLuaFail:
        return fpcrtl_make_string("sidVideoRecLuaFail");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TAmmoStrId enumvar)
{
    switch(enumvar){
    case sidGrenade:
        return fpcrtl_make_string("sidGrenade");
        break;
    case sidClusterBomb:
        return fpcrtl_make_string("sidClusterBomb");
        break;
    case sidBazooka:
        return fpcrtl_make_string("sidBazooka");
        break;
    case sidBee:
        return fpcrtl_make_string("sidBee");
        break;
    case sidShotgun:
        return fpcrtl_make_string("sidShotgun");
        break;
    case sidPickHammer:
        return fpcrtl_make_string("sidPickHammer");
        break;
    case sidSkip:
        return fpcrtl_make_string("sidSkip");
        break;
    case sidRope:
        return fpcrtl_make_string("sidRope");
        break;
    case sidMine:
        return fpcrtl_make_string("sidMine");
        break;
    case sidDEagle:
        return fpcrtl_make_string("sidDEagle");
        break;
    case sidDynamite:
        return fpcrtl_make_string("sidDynamite");
        break;
    case sidBaseballBat:
        return fpcrtl_make_string("sidBaseballBat");
        break;
    case sidFirePunch:
        return fpcrtl_make_string("sidFirePunch");
        break;
    case sidSeconds:
        return fpcrtl_make_string("sidSeconds");
        break;
    case sidParachute:
        return fpcrtl_make_string("sidParachute");
        break;
    case sidAirAttack:
        return fpcrtl_make_string("sidAirAttack");
        break;
    case sidMineStrike:
        return fpcrtl_make_string("sidMineStrike");
        break;
    case sidBlowTorch:
        return fpcrtl_make_string("sidBlowTorch");
        break;
    case sidGirder:
        return fpcrtl_make_string("sidGirder");
        break;
    case sidTeleport:
        return fpcrtl_make_string("sidTeleport");
        break;
    case sidSwitch:
        return fpcrtl_make_string("sidSwitch");
        break;
    case sidMortar:
        return fpcrtl_make_string("sidMortar");
        break;
    case sidWhip:
        return fpcrtl_make_string("sidWhip");
        break;
    case sidKamikaze:
        return fpcrtl_make_string("sidKamikaze");
        break;
    case sidCake:
        return fpcrtl_make_string("sidCake");
        break;
    case sidSeduction:
        return fpcrtl_make_string("sidSeduction");
        break;
    case sidWatermelon:
        return fpcrtl_make_string("sidWatermelon");
        break;
    case sidHellishBomb:
        return fpcrtl_make_string("sidHellishBomb");
        break;
    case sidDrill:
        return fpcrtl_make_string("sidDrill");
        break;
    case sidBallgun:
        return fpcrtl_make_string("sidBallgun");
        break;
    case sidNapalm:
        return fpcrtl_make_string("sidNapalm");
        break;
    case sidRCPlane:
        return fpcrtl_make_string("sidRCPlane");
        break;
    case sidLowGravity:
        return fpcrtl_make_string("sidLowGravity");
        break;
    case sidExtraDamage:
        return fpcrtl_make_string("sidExtraDamage");
        break;
    case sidInvulnerable:
        return fpcrtl_make_string("sidInvulnerable");
        break;
    case sidExtraTime:
        return fpcrtl_make_string("sidExtraTime");
        break;
    case sidLaserSight:
        return fpcrtl_make_string("sidLaserSight");
        break;
    case sidVampiric:
        return fpcrtl_make_string("sidVampiric");
        break;
    case sidSniperRifle:
        return fpcrtl_make_string("sidSniperRifle");
        break;
    case sidJetpack:
        return fpcrtl_make_string("sidJetpack");
        break;
    case sidMolotov:
        return fpcrtl_make_string("sidMolotov");
        break;
    case sidBirdy:
        return fpcrtl_make_string("sidBirdy");
        break;
    case sidPortalGun:
        return fpcrtl_make_string("sidPortalGun");
        break;
    case sidPiano:
        return fpcrtl_make_string("sidPiano");
        break;
    case sidGasBomb:
        return fpcrtl_make_string("sidGasBomb");
        break;
    case sidSineGun:
        return fpcrtl_make_string("sidSineGun");
        break;
    case sidFlamethrower:
        return fpcrtl_make_string("sidFlamethrower");
        break;
    case sidSMine:
        return fpcrtl_make_string("sidSMine");
        break;
    case sidHammer:
        return fpcrtl_make_string("sidHammer");
        break;
    case sidResurrector:
        return fpcrtl_make_string("sidResurrector");
        break;
    case sidDrillStrike:
        return fpcrtl_make_string("sidDrillStrike");
        break;
    case sidSnowball:
        return fpcrtl_make_string("sidSnowball");
        break;
    case sidNothing:
        return fpcrtl_make_string("sidNothing");
        break;
    case sidTardis:
        return fpcrtl_make_string("sidTardis");
        break;
    case sidLandGun:
        return fpcrtl_make_string("sidLandGun");
        break;
    case sidIceGun:
        return fpcrtl_make_string("sidIceGun");
        break;
    case sidKnife:
        return fpcrtl_make_string("sidKnife");
        break;
    case sidRubber:
        return fpcrtl_make_string("sidRubber");
        break;
    case sidAirMine:
        return fpcrtl_make_string("sidAirMine");
        break;
    case sidCreeper:
        return fpcrtl_make_string("sidCreeper");
        break;
    case sidMinigun:
        return fpcrtl_make_string("sidMinigun");
        break;
    case sidSentry:
        return fpcrtl_make_string("sidSentry");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TScreenFade enumvar)
{
    switch(enumvar){
    case sfNone:
        return fpcrtl_make_string("sfNone");
        break;
    case sfInit:
        return fpcrtl_make_string("sfInit");
        break;
    case sfToBlack:
        return fpcrtl_make_string("sfToBlack");
        break;
    case sfFromBlack:
        return fpcrtl_make_string("sfFromBlack");
        break;
    case sfToWhite:
        return fpcrtl_make_string("sfToWhite");
        break;
    case sfFromWhite:
        return fpcrtl_make_string("sfFromWhite");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const THogEffect enumvar)
{
    switch(enumvar){
    case heInvulnerable:
        return fpcrtl_make_string("heInvulnerable");
        break;
    case heResurrectable:
        return fpcrtl_make_string("heResurrectable");
        break;
    case hePoisoned:
        return fpcrtl_make_string("hePoisoned");
        break;
    case heResurrected:
        return fpcrtl_make_string("heResurrected");
        break;
    case heFrozen:
        return fpcrtl_make_string("heFrozen");
        break;
    case heArtillery:
        return fpcrtl_make_string("heArtillery");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TMapGen enumvar)
{
    switch(enumvar){
    case mgRandom:
        return fpcrtl_make_string("mgRandom");
        break;
    case mgMaze:
        return fpcrtl_make_string("mgMaze");
        break;
    case mgPerlin:
        return fpcrtl_make_string("mgPerlin");
        break;
    case mgDrawn:
        return fpcrtl_make_string("mgDrawn");
        break;
    case mgForts:
        return fpcrtl_make_string("mgForts");
        break;
    case mgWFC:
        return fpcrtl_make_string("mgWFC");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TUIDisplay enumvar)
{
    switch(enumvar){
    case uiAll:
        return fpcrtl_make_string("uiAll");
        break;
    case uiNoTeams:
        return fpcrtl_make_string("uiNoTeams");
        break;
    case uiNone:
        return fpcrtl_make_string("uiNone");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TWorldEdge enumvar)
{
    switch(enumvar){
    case weNone:
        return fpcrtl_make_string("weNone");
        break;
    case weWrap:
        return fpcrtl_make_string("weWrap");
        break;
    case weBounce:
        return fpcrtl_make_string("weBounce");
        break;
    case weSea:
        return fpcrtl_make_string("weSea");
        break;
    case weSky:
        return fpcrtl_make_string("weSky");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TStereoMode enumvar)
{
    switch(enumvar){
    case smNone:
        return fpcrtl_make_string("smNone");
        break;
    case smRedCyan:
        return fpcrtl_make_string("smRedCyan");
        break;
    case smCyanRed:
        return fpcrtl_make_string("smCyanRed");
        break;
    case smRedBlue:
        return fpcrtl_make_string("smRedBlue");
        break;
    case smBlueRed:
        return fpcrtl_make_string("smBlueRed");
        break;
    case smRedGreen:
        return fpcrtl_make_string("smRedGreen");
        break;
    case smGreenRed:
        return fpcrtl_make_string("smGreenRed");
        break;
    case smHorizontal:
        return fpcrtl_make_string("smHorizontal");
        break;
    case smVertical:
        return fpcrtl_make_string("smVertical");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TRenderMode enumvar)
{
    switch(enumvar){
    case rmDefault:
        return fpcrtl_make_string("rmDefault");
        break;
    case rmLeftEye:
        return fpcrtl_make_string("rmLeftEye");
        break;
    case rmRightEye:
        return fpcrtl_make_string("rmRightEye");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TWave enumvar)
{
    switch(enumvar){
    case waveRollup:
        return fpcrtl_make_string("waveRollup");
        break;
    case waveSad:
        return fpcrtl_make_string("waveSad");
        break;
    case waveWave:
        return fpcrtl_make_string("waveWave");
        break;
    case waveHurrah:
        return fpcrtl_make_string("waveHurrah");
        break;
    case waveLemonade:
        return fpcrtl_make_string("waveLemonade");
        break;
    case waveShrug:
        return fpcrtl_make_string("waveShrug");
        break;
    case waveJuggle:
        return fpcrtl_make_string("waveJuggle");
        break;
    case waveBubble:
        return fpcrtl_make_string("waveBubble");
        break;
    case waveHappy:
        return fpcrtl_make_string("waveHappy");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TStatInfoType enumvar)
{
    switch(enumvar){
    case siGameResult:
        return fpcrtl_make_string("siGameResult");
        break;
    case siMaxStepDamage:
        return fpcrtl_make_string("siMaxStepDamage");
        break;
    case siMaxStepKills:
        return fpcrtl_make_string("siMaxStepKills");
        break;
    case siKilledHHs:
        return fpcrtl_make_string("siKilledHHs");
        break;
    case siClanHealth:
        return fpcrtl_make_string("siClanHealth");
        break;
    case siTeamStats:
        return fpcrtl_make_string("siTeamStats");
        break;
    case siPlayerKills:
        return fpcrtl_make_string("siPlayerKills");
        break;
    case siMaxTeamDamage:
        return fpcrtl_make_string("siMaxTeamDamage");
        break;
    case siMaxTeamKills:
        return fpcrtl_make_string("siMaxTeamKills");
        break;
    case siMaxTurnSkips:
        return fpcrtl_make_string("siMaxTurnSkips");
        break;
    case siCustomAchievement:
        return fpcrtl_make_string("siCustomAchievement");
        break;
    case siGraphTitle:
        return fpcrtl_make_string("siGraphTitle");
        break;
    case siPointType:
        return fpcrtl_make_string("siPointType");
        break;
    case siTeamRank:
        return fpcrtl_make_string("siTeamRank");
        break;
    case siEverAfter:
        return fpcrtl_make_string("siEverAfter");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TCapGroup enumvar)
{
    switch(enumvar){
    case capgrpGameState:
        return fpcrtl_make_string("capgrpGameState");
        break;
    case capgrpAmmoinfo:
        return fpcrtl_make_string("capgrpAmmoinfo");
        break;
    case capgrpVolume:
        return fpcrtl_make_string("capgrpVolume");
        break;
    case capgrpMessage:
        return fpcrtl_make_string("capgrpMessage");
        break;
    case capgrpMessage2:
        return fpcrtl_make_string("capgrpMessage2");
        break;
    case capgrpAmmostate:
        return fpcrtl_make_string("capgrpAmmostate");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const THWFont enumvar)
{
    switch(enumvar){
    case fnt16:
        return fpcrtl_make_string("fnt16");
        break;
    case fntBig:
        return fpcrtl_make_string("fntBig");
        break;
    case fntSmall:
        return fpcrtl_make_string("fntSmall");
        break;
    case fntChat:
        return fpcrtl_make_string("fntChat");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TCrateType enumvar)
{
    switch(enumvar){
    case HealthCrate:
        return fpcrtl_make_string("HealthCrate");
        break;
    case AmmoCrate:
        return fpcrtl_make_string("AmmoCrate");
        break;
    case UtilityCrate:
        return fpcrtl_make_string("UtilityCrate");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TAmmoType enumvar)
{
    switch(enumvar){
    case amNothing:
        return fpcrtl_make_string("amNothing");
        break;
    case amGrenade:
        return fpcrtl_make_string("amGrenade");
        break;
    case amClusterBomb:
        return fpcrtl_make_string("amClusterBomb");
        break;
    case amBazooka:
        return fpcrtl_make_string("amBazooka");
        break;
    case amBee:
        return fpcrtl_make_string("amBee");
        break;
    case amShotgun:
        return fpcrtl_make_string("amShotgun");
        break;
    case amPickHammer:
        return fpcrtl_make_string("amPickHammer");
        break;
    case amSkip:
        return fpcrtl_make_string("amSkip");
        break;
    case amRope:
        return fpcrtl_make_string("amRope");
        break;
    case amMine:
        return fpcrtl_make_string("amMine");
        break;
    case amDEagle:
        return fpcrtl_make_string("amDEagle");
        break;
    case amDynamite:
        return fpcrtl_make_string("amDynamite");
        break;
    case amFirePunch:
        return fpcrtl_make_string("amFirePunch");
        break;
    case amWhip:
        return fpcrtl_make_string("amWhip");
        break;
    case amBaseballBat:
        return fpcrtl_make_string("amBaseballBat");
        break;
    case amParachute:
        return fpcrtl_make_string("amParachute");
        break;
    case amAirAttack:
        return fpcrtl_make_string("amAirAttack");
        break;
    case amMineStrike:
        return fpcrtl_make_string("amMineStrike");
        break;
    case amBlowTorch:
        return fpcrtl_make_string("amBlowTorch");
        break;
    case amGirder:
        return fpcrtl_make_string("amGirder");
        break;
    case amTeleport:
        return fpcrtl_make_string("amTeleport");
        break;
    case amSwitch:
        return fpcrtl_make_string("amSwitch");
        break;
    case amMortar:
        return fpcrtl_make_string("amMortar");
        break;
    case amKamikaze:
        return fpcrtl_make_string("amKamikaze");
        break;
    case amCake:
        return fpcrtl_make_string("amCake");
        break;
    case amSeduction:
        return fpcrtl_make_string("amSeduction");
        break;
    case amWatermelon:
        return fpcrtl_make_string("amWatermelon");
        break;
    case amHellishBomb:
        return fpcrtl_make_string("amHellishBomb");
        break;
    case amNapalm:
        return fpcrtl_make_string("amNapalm");
        break;
    case amDrill:
        return fpcrtl_make_string("amDrill");
        break;
    case amBallgun:
        return fpcrtl_make_string("amBallgun");
        break;
    case amRCPlane:
        return fpcrtl_make_string("amRCPlane");
        break;
    case amLowGravity:
        return fpcrtl_make_string("amLowGravity");
        break;
    case amExtraDamage:
        return fpcrtl_make_string("amExtraDamage");
        break;
    case amInvulnerable:
        return fpcrtl_make_string("amInvulnerable");
        break;
    case amExtraTime:
        return fpcrtl_make_string("amExtraTime");
        break;
    case amLaserSight:
        return fpcrtl_make_string("amLaserSight");
        break;
    case amVampiric:
        return fpcrtl_make_string("amVampiric");
        break;
    case amSniperRifle:
        return fpcrtl_make_string("amSniperRifle");
        break;
    case amJetpack:
        return fpcrtl_make_string("amJetpack");
        break;
    case amMolotov:
        return fpcrtl_make_string("amMolotov");
        break;
    case amBirdy:
        return fpcrtl_make_string("amBirdy");
        break;
    case amPortalGun:
        return fpcrtl_make_string("amPortalGun");
        break;
    case amPiano:
        return fpcrtl_make_string("amPiano");
        break;
    case amGasBomb:
        return fpcrtl_make_string("amGasBomb");
        break;
    case amSineGun:
        return fpcrtl_make_string("amSineGun");
        break;
    case amFlamethrower:
        return fpcrtl_make_string("amFlamethrower");
        break;
    case amSMine:
        return fpcrtl_make_string("amSMine");
        break;
    case amHammer:
        return fpcrtl_make_string("amHammer");
        break;
    case amResurrector:
        return fpcrtl_make_string("amResurrector");
        break;
    case amDrillStrike:
        return fpcrtl_make_string("amDrillStrike");
        break;
    case amSnowball:
        return fpcrtl_make_string("amSnowball");
        break;
    case amTardis:
        return fpcrtl_make_string("amTardis");
        break;
    case amLandGun:
        return fpcrtl_make_string("amLandGun");
        break;
    case amIceGun:
        return fpcrtl_make_string("amIceGun");
        break;
    case amKnife:
        return fpcrtl_make_string("amKnife");
        break;
    case amRubber:
        return fpcrtl_make_string("amRubber");
        break;
    case amAirMine:
        return fpcrtl_make_string("amAirMine");
        break;
    case amCreeper:
        return fpcrtl_make_string("amCreeper");
        break;
    case amMinigun:
        return fpcrtl_make_string("amMinigun");
        break;
    case amSentry:
        return fpcrtl_make_string("amSentry");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TSound enumvar)
{
    switch(enumvar){
    case sndNone:
        return fpcrtl_make_string("sndNone");
        break;
    case sndGrenadeImpact:
        return fpcrtl_make_string("sndGrenadeImpact");
        break;
    case sndExplosion:
        return fpcrtl_make_string("sndExplosion");
        break;
    case sndThrowPowerUp:
        return fpcrtl_make_string("sndThrowPowerUp");
        break;
    case sndThrowRelease:
        return fpcrtl_make_string("sndThrowRelease");
        break;
    case sndSplash:
        return fpcrtl_make_string("sndSplash");
        break;
    case sndShotgunReload:
        return fpcrtl_make_string("sndShotgunReload");
        break;
    case sndShotgunFire:
        return fpcrtl_make_string("sndShotgunFire");
        break;
    case sndGraveImpact:
        return fpcrtl_make_string("sndGraveImpact");
        break;
    case sndMineImpact:
        return fpcrtl_make_string("sndMineImpact");
        break;
    case sndMineTick:
        return fpcrtl_make_string("sndMineTick");
        break;
    case sndMudballImpact:
        return fpcrtl_make_string("sndMudballImpact");
        break;
    case sndPickhammer:
        return fpcrtl_make_string("sndPickhammer");
        break;
    case sndGun:
        return fpcrtl_make_string("sndGun");
        break;
    case sndBee:
        return fpcrtl_make_string("sndBee");
        break;
    case sndJump1:
        return fpcrtl_make_string("sndJump1");
        break;
    case sndJump2:
        return fpcrtl_make_string("sndJump2");
        break;
    case sndJump3:
        return fpcrtl_make_string("sndJump3");
        break;
    case sndYesSir:
        return fpcrtl_make_string("sndYesSir");
        break;
    case sndLaugh:
        return fpcrtl_make_string("sndLaugh");
        break;
    case sndIllGetYou:
        return fpcrtl_make_string("sndIllGetYou");
        break;
    case sndJustYouWait:
        return fpcrtl_make_string("sndJustYouWait");
        break;
    case sndIncoming:
        return fpcrtl_make_string("sndIncoming");
        break;
    case sndMissed:
        return fpcrtl_make_string("sndMissed");
        break;
    case sndStupid:
        return fpcrtl_make_string("sndStupid");
        break;
    case sndFirstBlood:
        return fpcrtl_make_string("sndFirstBlood");
        break;
    case sndBoring:
        return fpcrtl_make_string("sndBoring");
        break;
    case sndByeBye:
        return fpcrtl_make_string("sndByeBye");
        break;
    case sndSameTeam:
        return fpcrtl_make_string("sndSameTeam");
        break;
    case sndNutter:
        return fpcrtl_make_string("sndNutter");
        break;
    case sndReinforce:
        return fpcrtl_make_string("sndReinforce");
        break;
    case sndTraitor:
        return fpcrtl_make_string("sndTraitor");
        break;
    case sndRegret:
        return fpcrtl_make_string("sndRegret");
        break;
    case sndEnemyDown:
        return fpcrtl_make_string("sndEnemyDown");
        break;
    case sndCoward:
        return fpcrtl_make_string("sndCoward");
        break;
    case sndHurry:
        return fpcrtl_make_string("sndHurry");
        break;
    case sndWatchIt:
        return fpcrtl_make_string("sndWatchIt");
        break;
    case sndKamikaze:
        return fpcrtl_make_string("sndKamikaze");
        break;
    case sndCake:
        return fpcrtl_make_string("sndCake");
        break;
    case sndOw1:
        return fpcrtl_make_string("sndOw1");
        break;
    case sndOw2:
        return fpcrtl_make_string("sndOw2");
        break;
    case sndOw3:
        return fpcrtl_make_string("sndOw3");
        break;
    case sndOw4:
        return fpcrtl_make_string("sndOw4");
        break;
    case sndFirePunch1:
        return fpcrtl_make_string("sndFirePunch1");
        break;
    case sndFirePunch2:
        return fpcrtl_make_string("sndFirePunch2");
        break;
    case sndFirePunch3:
        return fpcrtl_make_string("sndFirePunch3");
        break;
    case sndFirePunch4:
        return fpcrtl_make_string("sndFirePunch4");
        break;
    case sndFirePunch5:
        return fpcrtl_make_string("sndFirePunch5");
        break;
    case sndFirePunch6:
        return fpcrtl_make_string("sndFirePunch6");
        break;
    case sndMelon:
        return fpcrtl_make_string("sndMelon");
        break;
    case sndHellish:
        return fpcrtl_make_string("sndHellish");
        break;
    case sndYoohoo:
        return fpcrtl_make_string("sndYoohoo");
        break;
    case sndRCPlane:
        return fpcrtl_make_string("sndRCPlane");
        break;
    case sndWhipCrack:
        return fpcrtl_make_string("sndWhipCrack");
        break;
    case sndRideOfTheValkyries:
        return fpcrtl_make_string("sndRideOfTheValkyries");
        break;
    case sndDenied:
        return fpcrtl_make_string("sndDenied");
        break;
    case sndPlaced:
        return fpcrtl_make_string("sndPlaced");
        break;
    case sndBaseballBat:
        return fpcrtl_make_string("sndBaseballBat");
        break;
    case sndVaporize:
        return fpcrtl_make_string("sndVaporize");
        break;
    case sndWarp:
        return fpcrtl_make_string("sndWarp");
        break;
    case sndSuddenDeath:
        return fpcrtl_make_string("sndSuddenDeath");
        break;
    case sndMortar:
        return fpcrtl_make_string("sndMortar");
        break;
    case sndShutter:
        return fpcrtl_make_string("sndShutter");
        break;
    case sndHomerun:
        return fpcrtl_make_string("sndHomerun");
        break;
    case sndMolotov:
        return fpcrtl_make_string("sndMolotov");
        break;
    case sndCover:
        return fpcrtl_make_string("sndCover");
        break;
    case sndUhOh:
        return fpcrtl_make_string("sndUhOh");
        break;
    case sndOops:
        return fpcrtl_make_string("sndOops");
        break;
    case sndNooo:
        return fpcrtl_make_string("sndNooo");
        break;
    case sndHello:
        return fpcrtl_make_string("sndHello");
        break;
    case sndRopeShot:
        return fpcrtl_make_string("sndRopeShot");
        break;
    case sndRopeAttach:
        return fpcrtl_make_string("sndRopeAttach");
        break;
    case sndRopeRelease:
        return fpcrtl_make_string("sndRopeRelease");
        break;
    case sndSwitchHog:
        return fpcrtl_make_string("sndSwitchHog");
        break;
    case sndVictory:
        return fpcrtl_make_string("sndVictory");
        break;
    case sndFlawless:
        return fpcrtl_make_string("sndFlawless");
        break;
    case sndSniperReload:
        return fpcrtl_make_string("sndSniperReload");
        break;
    case sndSteps:
        return fpcrtl_make_string("sndSteps");
        break;
    case sndLowGravity:
        return fpcrtl_make_string("sndLowGravity");
        break;
    case sndHellishImpact1:
        return fpcrtl_make_string("sndHellishImpact1");
        break;
    case sndHellishImpact2:
        return fpcrtl_make_string("sndHellishImpact2");
        break;
    case sndHellishImpact3:
        return fpcrtl_make_string("sndHellishImpact3");
        break;
    case sndHellishImpact4:
        return fpcrtl_make_string("sndHellishImpact4");
        break;
    case sndMelonImpact:
        return fpcrtl_make_string("sndMelonImpact");
        break;
    case sndDroplet1:
        return fpcrtl_make_string("sndDroplet1");
        break;
    case sndDroplet2:
        return fpcrtl_make_string("sndDroplet2");
        break;
    case sndDroplet3:
        return fpcrtl_make_string("sndDroplet3");
        break;
    case sndEggBreak:
        return fpcrtl_make_string("sndEggBreak");
        break;
    case sndDrillRocket:
        return fpcrtl_make_string("sndDrillRocket");
        break;
    case sndPoisonCough:
        return fpcrtl_make_string("sndPoisonCough");
        break;
    case sndPoisonMoan:
        return fpcrtl_make_string("sndPoisonMoan");
        break;
    case sndBirdyLay:
        return fpcrtl_make_string("sndBirdyLay");
        break;
    case sndWhistle:
        return fpcrtl_make_string("sndWhistle");
        break;
    case sndBeeWater:
        return fpcrtl_make_string("sndBeeWater");
        break;
    case sndPiano0:
        return fpcrtl_make_string("sndPiano0");
        break;
    case sndPiano1:
        return fpcrtl_make_string("sndPiano1");
        break;
    case sndPiano2:
        return fpcrtl_make_string("sndPiano2");
        break;
    case sndPiano3:
        return fpcrtl_make_string("sndPiano3");
        break;
    case sndPiano4:
        return fpcrtl_make_string("sndPiano4");
        break;
    case sndPiano5:
        return fpcrtl_make_string("sndPiano5");
        break;
    case sndPiano6:
        return fpcrtl_make_string("sndPiano6");
        break;
    case sndPiano7:
        return fpcrtl_make_string("sndPiano7");
        break;
    case sndPiano8:
        return fpcrtl_make_string("sndPiano8");
        break;
    case sndSkip:
        return fpcrtl_make_string("sndSkip");
        break;
    case sndSineGun:
        return fpcrtl_make_string("sndSineGun");
        break;
    case sndOoff1:
        return fpcrtl_make_string("sndOoff1");
        break;
    case sndOoff2:
        return fpcrtl_make_string("sndOoff2");
        break;
    case sndOoff3:
        return fpcrtl_make_string("sndOoff3");
        break;
    case sndWhack:
        return fpcrtl_make_string("sndWhack");
        break;
    case sndComeonthen:
        return fpcrtl_make_string("sndComeonthen");
        break;
    case sndParachute:
        return fpcrtl_make_string("sndParachute");
        break;
    case sndBump:
        return fpcrtl_make_string("sndBump");
        break;
    case sndResurrector:
        return fpcrtl_make_string("sndResurrector");
        break;
    case sndPlane:
        return fpcrtl_make_string("sndPlane");
        break;
    case sndTardis:
        return fpcrtl_make_string("sndTardis");
        break;
    case sndFrozenHogImpact:
        return fpcrtl_make_string("sndFrozenHogImpact");
        break;
    case sndIceBeam:
        return fpcrtl_make_string("sndIceBeam");
        break;
    case sndHogFreeze:
        return fpcrtl_make_string("sndHogFreeze");
        break;
    case sndAirMineImpact:
        return fpcrtl_make_string("sndAirMineImpact");
        break;
    case sndKnifeImpact:
        return fpcrtl_make_string("sndKnifeImpact");
        break;
    case sndExtraTime:
        return fpcrtl_make_string("sndExtraTime");
        break;
    case sndLaserSight:
        return fpcrtl_make_string("sndLaserSight");
        break;
    case sndInvulnerable:
        return fpcrtl_make_string("sndInvulnerable");
        break;
    case sndJetpackLaunch:
        return fpcrtl_make_string("sndJetpackLaunch");
        break;
    case sndJetpackBoost:
        return fpcrtl_make_string("sndJetpackBoost");
        break;
    case sndPortalShot:
        return fpcrtl_make_string("sndPortalShot");
        break;
    case sndPortalSwitch:
        return fpcrtl_make_string("sndPortalSwitch");
        break;
    case sndPortalOpen:
        return fpcrtl_make_string("sndPortalOpen");
        break;
    case sndBlowTorch:
        return fpcrtl_make_string("sndBlowTorch");
        break;
    case sndCountdown1:
        return fpcrtl_make_string("sndCountdown1");
        break;
    case sndCountdown2:
        return fpcrtl_make_string("sndCountdown2");
        break;
    case sndCountdown3:
        return fpcrtl_make_string("sndCountdown3");
        break;
    case sndCountdown4:
        return fpcrtl_make_string("sndCountdown4");
        break;
    case sndCreeperDrop:
        return fpcrtl_make_string("sndCreeperDrop");
        break;
    case sndCreeperWater:
        return fpcrtl_make_string("sndCreeperWater");
        break;
    case sndCreeperDie:
        return fpcrtl_make_string("sndCreeperDie");
        break;
    case sndCustom1:
        return fpcrtl_make_string("sndCustom1");
        break;
    case sndCustom2:
        return fpcrtl_make_string("sndCustom2");
        break;
    case sndCustom3:
        return fpcrtl_make_string("sndCustom3");
        break;
    case sndCustom4:
        return fpcrtl_make_string("sndCustom4");
        break;
    case sndCustom5:
        return fpcrtl_make_string("sndCustom5");
        break;
    case sndCustom6:
        return fpcrtl_make_string("sndCustom6");
        break;
    case sndCustom7:
        return fpcrtl_make_string("sndCustom7");
        break;
    case sndCustom8:
        return fpcrtl_make_string("sndCustom8");
        break;
    case sndMinigun:
        return fpcrtl_make_string("sndMinigun");
        break;
    case sndFlamethrower:
        return fpcrtl_make_string("sndFlamethrower");
        break;
    case sndIceBeamIdle:
        return fpcrtl_make_string("sndIceBeamIdle");
        break;
    case sndLandGun:
        return fpcrtl_make_string("sndLandGun");
        break;
    case sndCaseImpact:
        return fpcrtl_make_string("sndCaseImpact");
        break;
    case sndExtraDamage:
        return fpcrtl_make_string("sndExtraDamage");
        break;
    case sndFirePunchHit:
        return fpcrtl_make_string("sndFirePunchHit");
        break;
    case sndGrenade:
        return fpcrtl_make_string("sndGrenade");
        break;
    case sndThisOneIsMine:
        return fpcrtl_make_string("sndThisOneIsMine");
        break;
    case sndWhatThe:
        return fpcrtl_make_string("sndWhatThe");
        break;
    case sndSoLong:
        return fpcrtl_make_string("sndSoLong");
        break;
    case sndOhDear:
        return fpcrtl_make_string("sndOhDear");
        break;
    case sndGonnaGetYou:
        return fpcrtl_make_string("sndGonnaGetYou");
        break;
    case sndDrat:
        return fpcrtl_make_string("sndDrat");
        break;
    case sndBugger:
        return fpcrtl_make_string("sndBugger");
        break;
    case sndAmazing:
        return fpcrtl_make_string("sndAmazing");
        break;
    case sndBrilliant:
        return fpcrtl_make_string("sndBrilliant");
        break;
    case sndExcellent:
        return fpcrtl_make_string("sndExcellent");
        break;
    case sndFire:
        return fpcrtl_make_string("sndFire");
        break;
    case sndWatchThis:
        return fpcrtl_make_string("sndWatchThis");
        break;
    case sndRunAway:
        return fpcrtl_make_string("sndRunAway");
        break;
    case sndRevenge:
        return fpcrtl_make_string("sndRevenge");
        break;
    case sndCutItOut:
        return fpcrtl_make_string("sndCutItOut");
        break;
    case sndLeaveMeAlone:
        return fpcrtl_make_string("sndLeaveMeAlone");
        break;
    case sndOuch:
        return fpcrtl_make_string("sndOuch");
        break;
    case sndHmm:
        return fpcrtl_make_string("sndHmm");
        break;
    case sndKiss:
        return fpcrtl_make_string("sndKiss");
        break;
    case sndFlyAway:
        return fpcrtl_make_string("sndFlyAway");
        break;
    case sndPlaneWater:
        return fpcrtl_make_string("sndPlaneWater");
        break;
    case sndDynamiteFuse:
        return fpcrtl_make_string("sndDynamiteFuse");
        break;
    case sndDynamiteImpact:
        return fpcrtl_make_string("sndDynamiteImpact");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TDamageSource enumvar)
{
    switch(enumvar){
    case dsUnknown:
        return fpcrtl_make_string("dsUnknown");
        break;
    case dsFall:
        return fpcrtl_make_string("dsFall");
        break;
    case dsBullet:
        return fpcrtl_make_string("dsBullet");
        break;
    case dsExplosion:
        return fpcrtl_make_string("dsExplosion");
        break;
    case dsShove:
        return fpcrtl_make_string("dsShove");
        break;
    case dsPoison:
        return fpcrtl_make_string("dsPoison");
        break;
    case dsHammer:
        return fpcrtl_make_string("dsHammer");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TVisualGearType enumvar)
{
    switch(enumvar){
    case vgtFlake:
        return fpcrtl_make_string("vgtFlake");
        break;
    case vgtCloud:
        return fpcrtl_make_string("vgtCloud");
        break;
    case vgtExplPart:
        return fpcrtl_make_string("vgtExplPart");
        break;
    case vgtExplPart2:
        return fpcrtl_make_string("vgtExplPart2");
        break;
    case vgtFire:
        return fpcrtl_make_string("vgtFire");
        break;
    case vgtSmallDamageTag:
        return fpcrtl_make_string("vgtSmallDamageTag");
        break;
    case vgtTeamHealthSorter:
        return fpcrtl_make_string("vgtTeamHealthSorter");
        break;
    case vgtSpeechBubble:
        return fpcrtl_make_string("vgtSpeechBubble");
        break;
    case vgtBubble:
        return fpcrtl_make_string("vgtBubble");
        break;
    case vgtSteam:
        return fpcrtl_make_string("vgtSteam");
        break;
    case vgtAmmo:
        return fpcrtl_make_string("vgtAmmo");
        break;
    case vgtSmoke:
        return fpcrtl_make_string("vgtSmoke");
        break;
    case vgtSmokeWhite:
        return fpcrtl_make_string("vgtSmokeWhite");
        break;
    case vgtShell:
        return fpcrtl_make_string("vgtShell");
        break;
    case vgtDust:
        return fpcrtl_make_string("vgtDust");
        break;
    case vgtSplash:
        return fpcrtl_make_string("vgtSplash");
        break;
    case vgtDroplet:
        return fpcrtl_make_string("vgtDroplet");
        break;
    case vgtSmokeRing:
        return fpcrtl_make_string("vgtSmokeRing");
        break;
    case vgtBeeTrace:
        return fpcrtl_make_string("vgtBeeTrace");
        break;
    case vgtEgg:
        return fpcrtl_make_string("vgtEgg");
        break;
    case vgtFeather:
        return fpcrtl_make_string("vgtFeather");
        break;
    case vgtHealthTag:
        return fpcrtl_make_string("vgtHealthTag");
        break;
    case vgtSmokeTrace:
        return fpcrtl_make_string("vgtSmokeTrace");
        break;
    case vgtEvilTrace:
        return fpcrtl_make_string("vgtEvilTrace");
        break;
    case vgtExplosion:
        return fpcrtl_make_string("vgtExplosion");
        break;
    case vgtBigExplosion:
        return fpcrtl_make_string("vgtBigExplosion");
        break;
    case vgtChunk:
        return fpcrtl_make_string("vgtChunk");
        break;
    case vgtNote:
        return fpcrtl_make_string("vgtNote");
        break;
    case vgtLineTrail:
        return fpcrtl_make_string("vgtLineTrail");
        break;
    case vgtBulletHit:
        return fpcrtl_make_string("vgtBulletHit");
        break;
    case vgtCircle:
        return fpcrtl_make_string("vgtCircle");
        break;
    case vgtSmoothWindBar:
        return fpcrtl_make_string("vgtSmoothWindBar");
        break;
    case vgtStraightShot:
        return fpcrtl_make_string("vgtStraightShot");
        break;
    case vgtNoPlaceWarn:
        return fpcrtl_make_string("vgtNoPlaceWarn");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TGearType enumvar)
{
    switch(enumvar){
    case gtFlame:
        return fpcrtl_make_string("gtFlame");
        break;
    case gtHedgehog:
        return fpcrtl_make_string("gtHedgehog");
        break;
    case gtMine:
        return fpcrtl_make_string("gtMine");
        break;
    case gtCase:
        return fpcrtl_make_string("gtCase");
        break;
    case gtAirMine:
        return fpcrtl_make_string("gtAirMine");
        break;
    case gtExplosives:
        return fpcrtl_make_string("gtExplosives");
        break;
    case gtGrenade:
        return fpcrtl_make_string("gtGrenade");
        break;
    case gtShell:
        return fpcrtl_make_string("gtShell");
        break;
    case gtGrave:
        return fpcrtl_make_string("gtGrave");
        break;
    case gtBee:
        return fpcrtl_make_string("gtBee");
        break;
    case gtShotgunShot:
        return fpcrtl_make_string("gtShotgunShot");
        break;
    case gtPickHammer:
        return fpcrtl_make_string("gtPickHammer");
        break;
    case gtRope:
        return fpcrtl_make_string("gtRope");
        break;
    case gtDEagleShot:
        return fpcrtl_make_string("gtDEagleShot");
        break;
    case gtDynamite:
        return fpcrtl_make_string("gtDynamite");
        break;
    case gtClusterBomb:
        return fpcrtl_make_string("gtClusterBomb");
        break;
    case gtCluster:
        return fpcrtl_make_string("gtCluster");
        break;
    case gtShover:
        return fpcrtl_make_string("gtShover");
        break;
    case gtFirePunch:
        return fpcrtl_make_string("gtFirePunch");
        break;
    case gtATStartGame:
        return fpcrtl_make_string("gtATStartGame");
        break;
    case gtATFinishGame:
        return fpcrtl_make_string("gtATFinishGame");
        break;
    case gtParachute:
        return fpcrtl_make_string("gtParachute");
        break;
    case gtAirAttack:
        return fpcrtl_make_string("gtAirAttack");
        break;
    case gtAirBomb:
        return fpcrtl_make_string("gtAirBomb");
        break;
    case gtBlowTorch:
        return fpcrtl_make_string("gtBlowTorch");
        break;
    case gtGirder:
        return fpcrtl_make_string("gtGirder");
        break;
    case gtTeleport:
        return fpcrtl_make_string("gtTeleport");
        break;
    case gtSwitcher:
        return fpcrtl_make_string("gtSwitcher");
        break;
    case gtTarget:
        return fpcrtl_make_string("gtTarget");
        break;
    case gtMortar:
        return fpcrtl_make_string("gtMortar");
        break;
    case gtWhip:
        return fpcrtl_make_string("gtWhip");
        break;
    case gtKamikaze:
        return fpcrtl_make_string("gtKamikaze");
        break;
    case gtCake:
        return fpcrtl_make_string("gtCake");
        break;
    case gtSeduction:
        return fpcrtl_make_string("gtSeduction");
        break;
    case gtWatermelon:
        return fpcrtl_make_string("gtWatermelon");
        break;
    case gtMelonPiece:
        return fpcrtl_make_string("gtMelonPiece");
        break;
    case gtHellishBomb:
        return fpcrtl_make_string("gtHellishBomb");
        break;
    case gtWaterUp:
        return fpcrtl_make_string("gtWaterUp");
        break;
    case gtDrill:
        return fpcrtl_make_string("gtDrill");
        break;
    case gtBallGun:
        return fpcrtl_make_string("gtBallGun");
        break;
    case gtBall:
        return fpcrtl_make_string("gtBall");
        break;
    case gtRCPlane:
        return fpcrtl_make_string("gtRCPlane");
        break;
    case gtSniperRifleShot:
        return fpcrtl_make_string("gtSniperRifleShot");
        break;
    case gtJetpack:
        return fpcrtl_make_string("gtJetpack");
        break;
    case gtMolotov:
        return fpcrtl_make_string("gtMolotov");
        break;
    case gtBirdy:
        return fpcrtl_make_string("gtBirdy");
        break;
    case gtEgg:
        return fpcrtl_make_string("gtEgg");
        break;
    case gtPortal:
        return fpcrtl_make_string("gtPortal");
        break;
    case gtPiano:
        return fpcrtl_make_string("gtPiano");
        break;
    case gtGasBomb:
        return fpcrtl_make_string("gtGasBomb");
        break;
    case gtSineGunShot:
        return fpcrtl_make_string("gtSineGunShot");
        break;
    case gtFlamethrower:
        return fpcrtl_make_string("gtFlamethrower");
        break;
    case gtSMine:
        return fpcrtl_make_string("gtSMine");
        break;
    case gtPoisonCloud:
        return fpcrtl_make_string("gtPoisonCloud");
        break;
    case gtHammer:
        return fpcrtl_make_string("gtHammer");
        break;
    case gtHammerHit:
        return fpcrtl_make_string("gtHammerHit");
        break;
    case gtResurrector:
        return fpcrtl_make_string("gtResurrector");
        break;
    case gtNapalmBomb:
        return fpcrtl_make_string("gtNapalmBomb");
        break;
    case gtSnowball:
        return fpcrtl_make_string("gtSnowball");
        break;
    case gtFlake:
        return fpcrtl_make_string("gtFlake");
        break;
    case gtLandGun:
        return fpcrtl_make_string("gtLandGun");
        break;
    case gtTardis:
        return fpcrtl_make_string("gtTardis");
        break;
    case gtIceGun:
        return fpcrtl_make_string("gtIceGun");
        break;
    case gtAddAmmo:
        return fpcrtl_make_string("gtAddAmmo");
        break;
    case gtGenericFaller:
        return fpcrtl_make_string("gtGenericFaller");
        break;
    case gtKnife:
        return fpcrtl_make_string("gtKnife");
        break;
    case gtCreeper:
        return fpcrtl_make_string("gtCreeper");
        break;
    case gtMinigun:
        return fpcrtl_make_string("gtMinigun");
        break;
    case gtMinigunBullet:
        return fpcrtl_make_string("gtMinigunBullet");
        break;
    case gtSentry:
        return fpcrtl_make_string("gtSentry");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TSprite enumvar)
{
    switch(enumvar){
    case sprWater:
        return fpcrtl_make_string("sprWater");
        break;
    case sprCloud:
        return fpcrtl_make_string("sprCloud");
        break;
    case sprBomb:
        return fpcrtl_make_string("sprBomb");
        break;
    case sprBigDigit:
        return fpcrtl_make_string("sprBigDigit");
        break;
    case sprBigDigitGray:
        return fpcrtl_make_string("sprBigDigitGray");
        break;
    case sprBigDigitGreen:
        return fpcrtl_make_string("sprBigDigitGreen");
        break;
    case sprBigDigitRed:
        return fpcrtl_make_string("sprBigDigitRed");
        break;
    case sprFrame:
        return fpcrtl_make_string("sprFrame");
        break;
    case sprLag:
        return fpcrtl_make_string("sprLag");
        break;
    case sprArrow:
        return fpcrtl_make_string("sprArrow");
        break;
    case sprBazookaShell:
        return fpcrtl_make_string("sprBazookaShell");
        break;
    case sprTargetP:
        return fpcrtl_make_string("sprTargetP");
        break;
    case sprBee:
        return fpcrtl_make_string("sprBee");
        break;
    case sprSmokeTrace:
        return fpcrtl_make_string("sprSmokeTrace");
        break;
    case sprRopeHook:
        return fpcrtl_make_string("sprRopeHook");
        break;
    case sprExplosion50:
        return fpcrtl_make_string("sprExplosion50");
        break;
    case sprMineOff:
        return fpcrtl_make_string("sprMineOff");
        break;
    case sprMineOn:
        return fpcrtl_make_string("sprMineOn");
        break;
    case sprMineDead:
        return fpcrtl_make_string("sprMineDead");
        break;
    case sprCase:
        return fpcrtl_make_string("sprCase");
        break;
    case sprFAid:
        return fpcrtl_make_string("sprFAid");
        break;
    case sprDynamite:
        return fpcrtl_make_string("sprDynamite");
        break;
    case sprPower:
        return fpcrtl_make_string("sprPower");
        break;
    case sprClusterBomb:
        return fpcrtl_make_string("sprClusterBomb");
        break;
    case sprClusterParticle:
        return fpcrtl_make_string("sprClusterParticle");
        break;
    case sprFlame:
        return fpcrtl_make_string("sprFlame");
        break;
    case sprHorizont:
        return fpcrtl_make_string("sprHorizont");
        break;
    case sprHorizontL:
        return fpcrtl_make_string("sprHorizontL");
        break;
    case sprHorizontR:
        return fpcrtl_make_string("sprHorizontR");
        break;
    case sprSky:
        return fpcrtl_make_string("sprSky");
        break;
    case sprSkyL:
        return fpcrtl_make_string("sprSkyL");
        break;
    case sprSkyR:
        return fpcrtl_make_string("sprSkyR");
        break;
    case sprAMSlot:
        return fpcrtl_make_string("sprAMSlot");
        break;
    case sprAMAmmos:
        return fpcrtl_make_string("sprAMAmmos");
        break;
    case sprAMAmmosBW:
        return fpcrtl_make_string("sprAMAmmosBW");
        break;
    case sprAMSlotKeys:
        return fpcrtl_make_string("sprAMSlotKeys");
        break;
    case sprAMCorners:
        return fpcrtl_make_string("sprAMCorners");
        break;
    case sprFinger:
        return fpcrtl_make_string("sprFinger");
        break;
    case sprAirBomb:
        return fpcrtl_make_string("sprAirBomb");
        break;
    case sprAirplane:
        return fpcrtl_make_string("sprAirplane");
        break;
    case sprAmAirplane:
        return fpcrtl_make_string("sprAmAirplane");
        break;
    case sprAmGirder:
        return fpcrtl_make_string("sprAmGirder");
        break;
    case sprHHTelepMask:
        return fpcrtl_make_string("sprHHTelepMask");
        break;
    case sprSwitch:
        return fpcrtl_make_string("sprSwitch");
        break;
    case sprParachute:
        return fpcrtl_make_string("sprParachute");
        break;
    case sprTarget:
        return fpcrtl_make_string("sprTarget");
        break;
    case sprRopeNode:
        return fpcrtl_make_string("sprRopeNode");
        break;
    case sprQuestion:
        return fpcrtl_make_string("sprQuestion");
        break;
    case sprPowerBar:
        return fpcrtl_make_string("sprPowerBar");
        break;
    case sprWindBar:
        return fpcrtl_make_string("sprWindBar");
        break;
    case sprWindL:
        return fpcrtl_make_string("sprWindL");
        break;
    case sprWindR:
        return fpcrtl_make_string("sprWindR");
        break;
    case sprFlake:
        return fpcrtl_make_string("sprFlake");
        break;
    case sprHandRope:
        return fpcrtl_make_string("sprHandRope");
        break;
    case sprHandBazooka:
        return fpcrtl_make_string("sprHandBazooka");
        break;
    case sprHandShotgun:
        return fpcrtl_make_string("sprHandShotgun");
        break;
    case sprHandDEagle:
        return fpcrtl_make_string("sprHandDEagle");
        break;
    case sprHandAirAttack:
        return fpcrtl_make_string("sprHandAirAttack");
        break;
    case sprHandBaseball:
        return fpcrtl_make_string("sprHandBaseball");
        break;
    case sprPHammer:
        return fpcrtl_make_string("sprPHammer");
        break;
    case sprHandBlowTorch:
        return fpcrtl_make_string("sprHandBlowTorch");
        break;
    case sprBlowTorch:
        return fpcrtl_make_string("sprBlowTorch");
        break;
    case sprTeleport:
        return fpcrtl_make_string("sprTeleport");
        break;
    case sprHHDeath:
        return fpcrtl_make_string("sprHHDeath");
        break;
    case sprShotgun:
        return fpcrtl_make_string("sprShotgun");
        break;
    case sprDEagle:
        return fpcrtl_make_string("sprDEagle");
        break;
    case sprHHIdle:
        return fpcrtl_make_string("sprHHIdle");
        break;
    case sprMortar:
        return fpcrtl_make_string("sprMortar");
        break;
    case sprTurnsLeft:
        return fpcrtl_make_string("sprTurnsLeft");
        break;
    case sprKamikaze:
        return fpcrtl_make_string("sprKamikaze");
        break;
    case sprWhip:
        return fpcrtl_make_string("sprWhip");
        break;
    case sprKowtow:
        return fpcrtl_make_string("sprKowtow");
        break;
    case sprSad:
        return fpcrtl_make_string("sprSad");
        break;
    case sprWave:
        return fpcrtl_make_string("sprWave");
        break;
    case sprHurrah:
        return fpcrtl_make_string("sprHurrah");
        break;
    case sprLemonade:
        return fpcrtl_make_string("sprLemonade");
        break;
    case sprShrug:
        return fpcrtl_make_string("sprShrug");
        break;
    case sprJuggle:
        return fpcrtl_make_string("sprJuggle");
        break;
    case sprExplPart:
        return fpcrtl_make_string("sprExplPart");
        break;
    case sprExplPart2:
        return fpcrtl_make_string("sprExplPart2");
        break;
    case sprCakeWalk:
        return fpcrtl_make_string("sprCakeWalk");
        break;
    case sprCakeDown:
        return fpcrtl_make_string("sprCakeDown");
        break;
    case sprWatermelon:
        return fpcrtl_make_string("sprWatermelon");
        break;
    case sprEvilTrace:
        return fpcrtl_make_string("sprEvilTrace");
        break;
    case sprHellishBomb:
        return fpcrtl_make_string("sprHellishBomb");
        break;
    case sprSeduction:
        return fpcrtl_make_string("sprSeduction");
        break;
    case sprDress:
        return fpcrtl_make_string("sprDress");
        break;
    case sprCensored:
        return fpcrtl_make_string("sprCensored");
        break;
    case sprDrill:
        return fpcrtl_make_string("sprDrill");
        break;
    case sprHandDrill:
        return fpcrtl_make_string("sprHandDrill");
        break;
    case sprHandBallgun:
        return fpcrtl_make_string("sprHandBallgun");
        break;
    case sprBalls:
        return fpcrtl_make_string("sprBalls");
        break;
    case sprPlane:
        return fpcrtl_make_string("sprPlane");
        break;
    case sprHandPlane:
        return fpcrtl_make_string("sprHandPlane");
        break;
    case sprUtility:
        return fpcrtl_make_string("sprUtility");
        break;
    case sprInvulnerable:
        return fpcrtl_make_string("sprInvulnerable");
        break;
    case sprVampiric:
        return fpcrtl_make_string("sprVampiric");
        break;
    case sprGirder:
        return fpcrtl_make_string("sprGirder");
        break;
    case sprSpeechCorner:
        return fpcrtl_make_string("sprSpeechCorner");
        break;
    case sprSpeechEdge:
        return fpcrtl_make_string("sprSpeechEdge");
        break;
    case sprSpeechTail:
        return fpcrtl_make_string("sprSpeechTail");
        break;
    case sprThoughtCorner:
        return fpcrtl_make_string("sprThoughtCorner");
        break;
    case sprThoughtEdge:
        return fpcrtl_make_string("sprThoughtEdge");
        break;
    case sprThoughtTail:
        return fpcrtl_make_string("sprThoughtTail");
        break;
    case sprShoutCorner:
        return fpcrtl_make_string("sprShoutCorner");
        break;
    case sprShoutEdge:
        return fpcrtl_make_string("sprShoutEdge");
        break;
    case sprShoutTail:
        return fpcrtl_make_string("sprShoutTail");
        break;
    case sprSniperRifle:
        return fpcrtl_make_string("sprSniperRifle");
        break;
    case sprBubbles:
        return fpcrtl_make_string("sprBubbles");
        break;
    case sprJetpack:
        return fpcrtl_make_string("sprJetpack");
        break;
    case sprHealth:
        return fpcrtl_make_string("sprHealth");
        break;
    case sprHandMolotov:
        return fpcrtl_make_string("sprHandMolotov");
        break;
    case sprMolotov:
        return fpcrtl_make_string("sprMolotov");
        break;
    case sprSmoke:
        return fpcrtl_make_string("sprSmoke");
        break;
    case sprSmokeWhite:
        return fpcrtl_make_string("sprSmokeWhite");
        break;
    case sprShell:
        return fpcrtl_make_string("sprShell");
        break;
    case sprDust:
        return fpcrtl_make_string("sprDust");
        break;
    case sprSnowDust:
        return fpcrtl_make_string("sprSnowDust");
        break;
    case sprExplosives:
        return fpcrtl_make_string("sprExplosives");
        break;
    case sprExplosivesRoll:
        return fpcrtl_make_string("sprExplosivesRoll");
        break;
    case sprAmTeleport:
        return fpcrtl_make_string("sprAmTeleport");
        break;
    case sprSplash:
        return fpcrtl_make_string("sprSplash");
        break;
    case sprDroplet:
        return fpcrtl_make_string("sprDroplet");
        break;
    case sprBirdy:
        return fpcrtl_make_string("sprBirdy");
        break;
    case sprHandCake:
        return fpcrtl_make_string("sprHandCake");
        break;
    case sprHandConstruction:
        return fpcrtl_make_string("sprHandConstruction");
        break;
    case sprHandGrenade:
        return fpcrtl_make_string("sprHandGrenade");
        break;
    case sprHandMelon:
        return fpcrtl_make_string("sprHandMelon");
        break;
    case sprHandMortar:
        return fpcrtl_make_string("sprHandMortar");
        break;
    case sprHandSkip:
        return fpcrtl_make_string("sprHandSkip");
        break;
    case sprHandCluster:
        return fpcrtl_make_string("sprHandCluster");
        break;
    case sprHandDynamite:
        return fpcrtl_make_string("sprHandDynamite");
        break;
    case sprHandHellish:
        return fpcrtl_make_string("sprHandHellish");
        break;
    case sprHandMine:
        return fpcrtl_make_string("sprHandMine");
        break;
    case sprHandSeduction:
        return fpcrtl_make_string("sprHandSeduction");
        break;
    case sprHandVamp:
        return fpcrtl_make_string("sprHandVamp");
        break;
    case sprBigExplosion:
        return fpcrtl_make_string("sprBigExplosion");
        break;
    case sprSmokeRing:
        return fpcrtl_make_string("sprSmokeRing");
        break;
    case sprBeeTrace:
        return fpcrtl_make_string("sprBeeTrace");
        break;
    case sprEgg:
        return fpcrtl_make_string("sprEgg");
        break;
    case sprTargetBee:
        return fpcrtl_make_string("sprTargetBee");
        break;
    case sprHandBee:
        return fpcrtl_make_string("sprHandBee");
        break;
    case sprFeather:
        return fpcrtl_make_string("sprFeather");
        break;
    case sprPiano:
        return fpcrtl_make_string("sprPiano");
        break;
    case sprHandSineGun:
        return fpcrtl_make_string("sprHandSineGun");
        break;
    case sprPortalGun:
        return fpcrtl_make_string("sprPortalGun");
        break;
    case sprPortal:
        return fpcrtl_make_string("sprPortal");
        break;
    case sprCheese:
        return fpcrtl_make_string("sprCheese");
        break;
    case sprHandCheese:
        return fpcrtl_make_string("sprHandCheese");
        break;
    case sprHandFlamethrower:
        return fpcrtl_make_string("sprHandFlamethrower");
        break;
    case sprChunk:
        return fpcrtl_make_string("sprChunk");
        break;
    case sprNote:
        return fpcrtl_make_string("sprNote");
        break;
    case sprSMineOff:
        return fpcrtl_make_string("sprSMineOff");
        break;
    case sprSMineOn:
        return fpcrtl_make_string("sprSMineOn");
        break;
    case sprHandSMine:
        return fpcrtl_make_string("sprHandSMine");
        break;
    case sprHammer:
        return fpcrtl_make_string("sprHammer");
        break;
    case sprHandResurrector:
        return fpcrtl_make_string("sprHandResurrector");
        break;
    case sprCross:
        return fpcrtl_make_string("sprCross");
        break;
    case sprAirDrill:
        return fpcrtl_make_string("sprAirDrill");
        break;
    case sprNapalmBomb:
        return fpcrtl_make_string("sprNapalmBomb");
        break;
    case sprBulletHit:
        return fpcrtl_make_string("sprBulletHit");
        break;
    case sprSnowball:
        return fpcrtl_make_string("sprSnowball");
        break;
    case sprHandSnowball:
        return fpcrtl_make_string("sprHandSnowball");
        break;
    case sprSnow:
        return fpcrtl_make_string("sprSnow");
        break;
    case sprSDFlake:
        return fpcrtl_make_string("sprSDFlake");
        break;
    case sprSDWater:
        return fpcrtl_make_string("sprSDWater");
        break;
    case sprSDCloud:
        return fpcrtl_make_string("sprSDCloud");
        break;
    case sprSDSplash:
        return fpcrtl_make_string("sprSDSplash");
        break;
    case sprSDDroplet:
        return fpcrtl_make_string("sprSDDroplet");
        break;
    case sprTardis:
        return fpcrtl_make_string("sprTardis");
        break;
    case sprSlider:
        return fpcrtl_make_string("sprSlider");
        break;
    case sprBotlevels:
        return fpcrtl_make_string("sprBotlevels");
        break;
    case sprHandKnife:
        return fpcrtl_make_string("sprHandKnife");
        break;
    case sprKnife:
        return fpcrtl_make_string("sprKnife");
        break;
    case sprStar:
        return fpcrtl_make_string("sprStar");
        break;
    case sprIceTexture:
        return fpcrtl_make_string("sprIceTexture");
        break;
    case sprIceGun:
        return fpcrtl_make_string("sprIceGun");
        break;
    case sprFrozenHog:
        return fpcrtl_make_string("sprFrozenHog");
        break;
    case sprAmRubber:
        return fpcrtl_make_string("sprAmRubber");
        break;
    case sprBoing:
        return fpcrtl_make_string("sprBoing");
        break;
    case sprCustom1:
        return fpcrtl_make_string("sprCustom1");
        break;
    case sprCustom2:
        return fpcrtl_make_string("sprCustom2");
        break;
    case sprCustom3:
        return fpcrtl_make_string("sprCustom3");
        break;
    case sprCustom4:
        return fpcrtl_make_string("sprCustom4");
        break;
    case sprCustom5:
        return fpcrtl_make_string("sprCustom5");
        break;
    case sprCustom6:
        return fpcrtl_make_string("sprCustom6");
        break;
    case sprCustom7:
        return fpcrtl_make_string("sprCustom7");
        break;
    case sprCustom8:
        return fpcrtl_make_string("sprCustom8");
        break;
    case sprFrozenAirMine:
        return fpcrtl_make_string("sprFrozenAirMine");
        break;
    case sprAirMine:
        return fpcrtl_make_string("sprAirMine");
        break;
    case sprHandAirMine:
        return fpcrtl_make_string("sprHandAirMine");
        break;
    case sprFlakeL:
        return fpcrtl_make_string("sprFlakeL");
        break;
    case sprSDFlakeL:
        return fpcrtl_make_string("sprSDFlakeL");
        break;
    case sprCloudL:
        return fpcrtl_make_string("sprCloudL");
        break;
    case sprSDCloudL:
        return fpcrtl_make_string("sprSDCloudL");
        break;
    case sprCreeper:
        return fpcrtl_make_string("sprCreeper");
        break;
    case sprHandCreeper:
        return fpcrtl_make_string("sprHandCreeper");
        break;
    case sprMinigun:
        return fpcrtl_make_string("sprMinigun");
        break;
    case sprSliderInverted:
        return fpcrtl_make_string("sprSliderInverted");
        break;
    case sprFingerBack:
        return fpcrtl_make_string("sprFingerBack");
        break;
    case sprFingerBackInv:
        return fpcrtl_make_string("sprFingerBackInv");
        break;
    case sprTargetPBack:
        return fpcrtl_make_string("sprTargetPBack");
        break;
    case sprTargetPBackInv:
        return fpcrtl_make_string("sprTargetPBackInv");
        break;
    case sprHealthHud:
        return fpcrtl_make_string("sprHealthHud");
        break;
    case sprHealthPoisonHud:
        return fpcrtl_make_string("sprHealthPoisonHud");
        break;
    case sprVampHud:
        return fpcrtl_make_string("sprVampHud");
        break;
    case sprKarmaHud:
        return fpcrtl_make_string("sprKarmaHud");
        break;
    case sprMedicHud:
        return fpcrtl_make_string("sprMedicHud");
        break;
    case sprMedicPoisonHud:
        return fpcrtl_make_string("sprMedicPoisonHud");
        break;
    case sprHaloHud:
        return fpcrtl_make_string("sprHaloHud");
        break;
    case sprInvulnHUD:
        return fpcrtl_make_string("sprInvulnHUD");
        break;
    case sprAmPiano:
        return fpcrtl_make_string("sprAmPiano");
        break;
    case sprHandLandGun:
        return fpcrtl_make_string("sprHandLandGun");
        break;
    case sprFirePunch:
        return fpcrtl_make_string("sprFirePunch");
        break;
    case sprThroughWrap:
        return fpcrtl_make_string("sprThroughWrap");
        break;
    case sprDynamiteDefused:
        return fpcrtl_make_string("sprDynamiteDefused");
        break;
    case sprHogBubble:
        return fpcrtl_make_string("sprHogBubble");
        break;
    case sprHappy:
        return fpcrtl_make_string("sprHappy");
        break;
    case sprSentry:
        return fpcrtl_make_string("sprSentry");
        break;
    case sprHandSentry:
        return fpcrtl_make_string("sprHandSentry");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TPathType enumvar)
{
    switch(enumvar){
    case ptNone:
        return fpcrtl_make_string("ptNone");
        break;
    case ptData:
        return fpcrtl_make_string("ptData");
        break;
    case ptGraphics:
        return fpcrtl_make_string("ptGraphics");
        break;
    case ptThemes:
        return fpcrtl_make_string("ptThemes");
        break;
    case ptCurrTheme:
        return fpcrtl_make_string("ptCurrTheme");
        break;
    case ptConfig:
        return fpcrtl_make_string("ptConfig");
        break;
    case ptTeams:
        return fpcrtl_make_string("ptTeams");
        break;
    case ptMaps:
        return fpcrtl_make_string("ptMaps");
        break;
    case ptMapCurrent:
        return fpcrtl_make_string("ptMapCurrent");
        break;
    case ptDemos:
        return fpcrtl_make_string("ptDemos");
        break;
    case ptSounds:
        return fpcrtl_make_string("ptSounds");
        break;
    case ptGraves:
        return fpcrtl_make_string("ptGraves");
        break;
    case ptFonts:
        return fpcrtl_make_string("ptFonts");
        break;
    case ptForts:
        return fpcrtl_make_string("ptForts");
        break;
    case ptLocale:
        return fpcrtl_make_string("ptLocale");
        break;
    case ptAmmoMenu:
        return fpcrtl_make_string("ptAmmoMenu");
        break;
    case ptHedgehog:
        return fpcrtl_make_string("ptHedgehog");
        break;
    case ptVoices:
        return fpcrtl_make_string("ptVoices");
        break;
    case ptHats:
        return fpcrtl_make_string("ptHats");
        break;
    case ptFlags:
        return fpcrtl_make_string("ptFlags");
        break;
    case ptMissionMaps:
        return fpcrtl_make_string("ptMissionMaps");
        break;
    case ptSuddenDeath:
        return fpcrtl_make_string("ptSuddenDeath");
        break;
    case ptButtons:
        return fpcrtl_make_string("ptButtons");
        break;
    case ptShaders:
        return fpcrtl_make_string("ptShaders");
        break;
    case ptDefaultVoice:
        return fpcrtl_make_string("ptDefaultVoice");
        break;
    case ptMisc:
        return fpcrtl_make_string("ptMisc");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TGameType enumvar)
{
    switch(enumvar){
    case gmtLocal:
        return fpcrtl_make_string("gmtLocal");
        break;
    case gmtDemo:
        return fpcrtl_make_string("gmtDemo");
        break;
    case gmtNet:
        return fpcrtl_make_string("gmtNet");
        break;
    case gmtSave:
        return fpcrtl_make_string("gmtSave");
        break;
    case gmtLandPreview:
        return fpcrtl_make_string("gmtLandPreview");
        break;
    case gmtBadSyntax:
        return fpcrtl_make_string("gmtBadSyntax");
        break;
    case gmtRecord:
        return fpcrtl_make_string("gmtRecord");
        break;
    case gmtSyntaxHelp:
        return fpcrtl_make_string("gmtSyntaxHelp");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TGameState enumvar)
{
    switch(enumvar){
    case gsLandGen:
        return fpcrtl_make_string("gsLandGen");
        break;
    case gsStart:
        return fpcrtl_make_string("gsStart");
        break;
    case gsGame:
        return fpcrtl_make_string("gsGame");
        break;
    case gsConfirm:
        return fpcrtl_make_string("gsConfirm");
        break;
    case gsExit:
        return fpcrtl_make_string("gsExit");
        break;
    case gsSuspend:
        return fpcrtl_make_string("gsSuspend");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}