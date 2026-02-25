#include "fpcrtl.h"

#include "uCommandHandlers.h"
#include "uCommands.h"
#include "uTypes.h"
#include "uVariables.h"
#include "uIO.h"
#include "uDebug.h"
#include "uConsts.h"
#include "uScript.h"
#include "uUtils.h"
#include "SDLh.h"
#include "uWorld.h"
#include "uRandom.h"
#include "uCaptions.h"
#include "uVisualGearsList.h"
#include "uGearsHedgehog.h"
#include "uChat.h"
#include "uConsole.h"
static const string255 __str154 = STRINIT("timer_u");
static const string255 __str153 = STRINIT("gearinfo");
static const string255 __str152 = STRINIT("-mission");
static const string255 __str151 = STRINIT("+mission");
static const string255 __str150 = STRINIT("sff");
static const string255 __str149 = STRINIT("ff");
static const string255 __str148 = STRINIT("advmapgen");
static const string255 __str147 = STRINIT("worldedge");
static const string255 __str146 = STRINIT("record");
static const string255 __str145 = STRINIT("missvar");
static const string255 __str144 = STRINIT("campvar");
static const string255 __str143 = STRINIT("-cur_r");
static const string255 __str142 = STRINIT("+cur_r");
static const string255 __str141 = STRINIT("-cur_l");
static const string255 __str140 = STRINIT("+cur_l");
static const string255 __str139 = STRINIT("-cur_d");
static const string255 __str138 = STRINIT("+cur_d");
static const string255 __str137 = STRINIT("-cur_u");
static const string255 __str136 = STRINIT("+cur_u");
static const string255 __str135 = STRINIT("pause");
static const string255 __str134 = STRINIT("findhh");
static const string255 __str133 = STRINIT("mute");
static const string255 __str132 = STRINIT("-voldown");
static const string255 __str131 = STRINIT("+voldown");
static const string255 __str130 = STRINIT("-volup");
static const string255 __str129 = STRINIT("+volup");
static const string255 __str128 = STRINIT("put");
static const string255 __str127 = STRINIT("taunt");
static const string255 __str126 = STRINIT("timer");
static const string255 __str125 = STRINIT("switch");
static const string255 __str124 = STRINIT("-precise");
static const string255 __str123 = STRINIT("+precise");
static const string255 __str122 = STRINIT("ammomenu");
static const string255 __str121 = STRINIT("zoomreset");
static const string255 __str120 = STRINIT("zoomout");
static const string255 __str119 = STRINIT("zoomin");
static const string255 __str118 = STRINIT("-speedup");
static const string255 __str117 = STRINIT("+speedup");
static const string255 __str116 = STRINIT("halt");
static const string255 __str115 = STRINIT("forcequit");
static const string255 __str114 = STRINIT("quit");
static const string255 __str113 = STRINIT("minestime");
static const string255 __str112 = STRINIT("turntime");
static const string255 __str111 = STRINIT("gmflags");
static const string255 __str110 = STRINIT("explosives");
static const string255 __str109 = STRINIT("sentries");
static const string255 __str108 = STRINIT("airmines");
static const string255 __str107 = STRINIT("minesnum");
static const string255 __str106 = STRINIT("minedudpct");
static const string255 __str105 = STRINIT("getawaytime");
static const string255 __str104 = STRINIT("ropepct");
static const string255 __str103 = STRINIT("damagepct");
static const string255 __str102 = STRINIT("inithealth");
static const string255 __str101 = STRINIT("healthdec");
static const string255 __str100 = STRINIT("waterrise");
static const string255 __str99 = STRINIT("sd_turns");
static const string255 __str98 = STRINIT("hcaseamount");
static const string255 __str97 = STRINIT("healthprob");
static const string255 __str96 = STRINIT("casefreq");
static const string255 __str95 = STRINIT("ready");
static const string255 __str94 = STRINIT("delay");
static const string255 __str93 = STRINIT("feature_size");
static const string255 __str92 = STRINIT("maze_size");
static const string255 __str91 = STRINIT("mapgen");
static const string255 __str90 = STRINIT("template_filter");
static const string255 __str89 = STRINIT("seed");
static const string255 __str88 = STRINIT("theme");
static const string255 __str87 = STRINIT("map");
static const string255 __str86 = STRINIT("rdriven");
static const string255 __str85 = STRINIT("rottags");
static const string255 __str84 = STRINIT("rotmask");
static const string255 __str83 = STRINIT("capture");
static const string255 __str82 = STRINIT("spectate");
static const string255 __str81 = STRINIT("proto");
static const string255 __str80 = STRINIT("scriptparam");
static const string255 __str79 = STRINIT("script");
static const string255 __str78 = STRINIT("gencmd");
static const string255 __str77 = STRINIT("setweap");
static const string255 __str76 = STRINIT("slot");
static const string255 __str75 = STRINIT("-attack");
static const string255 __str74 = STRINIT("nextturn");
static const string255 __str73 = STRINIT("ljump");
static const string255 __str72 = STRINIT("hjump");
static const string255 __str71 = STRINIT("-down");
static const string255 __str70 = STRINIT("+down");
static const string255 __str69 = STRINIT("+attack");
static const string255 __str68 = STRINIT("-left");
static const string255 __str67 = STRINIT("+left");
static const string255 __str66 = STRINIT("-up");
static const string255 __str65 = STRINIT("+up");
static const string255 __str64 = STRINIT("-right");
static const string255 __str63 = STRINIT("+right");
static const string255 __str62 = STRINIT("server");
static const string255 __str61 = STRINIT("[DEBUG chSetSeed] BLOCKED by isDeveloperMode check");
static const string255 __str60 = STRINIT("[DEBUG chSetSeed] Set cifRandomize flag");
static const string255 __str59 = STRINIT(" s=");
static const string255 __str58 = STRINIT("[DEBUG chSetSeed] isDeveloperMode=");
static const string255 __str57 = STRINIT("FALSE");
static const string255 __str56 = STRINIT("TRUE");
static const string255 __str55 = STRINIT("/map.lua");
static const string255 __str54 = STRINIT("Maps/");
static const string255 __str53 = STRINIT("[HANDLER] chSetMap BLOCKED by isDeveloperMode=false");
static const string255 __str52 = STRINIT("");
static const string255 __str51 = STRINIT("[HANDLER] chSetMap setting cifMap flag");
static const string255 __str50 = STRINIT("[HANDLER] chSetMap called with: ");
static const string255 __str49 = STRINIT("onSetWeapon");
static const string255 __str48 = STRINIT("Malformed /setweap");
static const string255 __str47 = STRINIT("onSlot");
static const string255 __str46 = STRINIT("timer ");
static const string255 __str45 = STRINIT("onTimer");
static const string255 __str44 = STRINIT("Malformed /timer");
static const string255 __str43 = STRINIT("Next turn: time ");
static const string255 __str42 = STRINIT("Desync detected");
static const string255 __str41 = STRINIT("/nextturn called when not all gears are inactive");
static const string255 __str40 = STRINIT("onSwitch");
static const string255 __str39 = STRINIT("S");
static const string255 __str38 = STRINIT("onAttackUp");
static const string255 __str37 = STRINIT("a");
static const string255 __str36 = STRINIT("onAttack");
static const string255 __str35 = STRINIT("A");
static const string255 __str34 = STRINIT("/+attack: hedgehog's Gear^.State = ");
static const string255 __str33 = STRINIT("onHJump");
static const string255 __str32 = STRINIT("J");
static const string255 __str31 = STRINIT("onLJump");
static const string255 __str30 = STRINIT("j");
static const string255 __str29 = STRINIT("onPreciseUp");
static const string255 __str28 = STRINIT("z");
static const string255 __str27 = STRINIT("onPrecise");
static const string255 __str26 = STRINIT("Z");
static const string255 __str25 = STRINIT("onDownUp");
static const string255 __str24 = STRINIT("d");
static const string255 __str23 = STRINIT("onDown");
static const string255 __str22 = STRINIT("D");
static const string255 __str21 = STRINIT("onUpUp");
static const string255 __str20 = STRINIT("u");
static const string255 __str19 = STRINIT("onUp");
static const string255 __str18 = STRINIT("U");
static const string255 __str17 = STRINIT("onRightUp");
static const string255 __str16 = STRINIT("r");
static const string255 __str15 = STRINIT("onRight");
static const string255 __str14 = STRINIT("R");
static const string255 __str13 = STRINIT("onLeftUp");
static const string255 __str12 = STRINIT("l");
static const string255 __str11 = STRINIT("onLeft");
static const string255 __str10 = STRINIT("L");
static const string255 __str9 = STRINIT("onParameters");
static const string255 __str8 = STRINIT("ScriptParam");
static const string255 __str7 = STRINIT(" \"/rdriven\"");
static const string255 __str6 = STRINIT("Protocol version mismatch: engine is too new (got ");
static const string255 __str5 = STRINIT(", expecting ");
static const string255 __str4 = STRINIT("Protocol version mismatch: engine is too old (got ");
static const string255 __str3 = STRINIT("H");
static const string255 __str2 = STRINIT("Q");
static const string255 __str1 = STRINIT("m");
static const string255 __str0 = STRINIT("confirm");
typedef Byte cTagsMasks_tt[(15 + 1)];
static cTagsMasks_tt cTagsMasks = {7,
                                   0,
                                   0,
                                   0,
                                   0,
                                   4,
                                   5,
                                   6,
                                   15,
                                   8,
                                   8,
                                   8,
                                   8,
                                   12,
                                   13,
                                   14};
typedef Byte cTagsMasksNoHealth_tt[(15 + 1)];
static cTagsMasksNoHealth_tt cTagsMasksNoHealth = {3,
                                                   0,
                                                   1,
                                                   2,
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   11,
                                                   8,
                                                   9,
                                                   10,
                                                   8,
                                                   8,
                                                   8,
                                                   8};
void ucommandhandlers_chGenCmd(string255 (*s))
{
    switch((*s).s[1])
    {case 'R':if(ReadyTimeLeft > 0)
              {
                  ReadyTimeLeft = 0;
                  if(!isExternalSource)
                  {
                      uio_SendIPC(_strprepend(0x63, (*s)));
                  }
              }
              break;
     default: break;}
};
void ucommandhandlers_chQuit(string255 (*s))
{
    UNUSED ((*s));
    if(GameState == gsGame)
    {
        uchat_CloseChat();
        GameState = gsConfirm;
    }
    else
    {
        if(GameState == gsConfirm)
        {
            GameState = gsGame;
            uchat_RestoreChat();
        }
    }
    uworld_updateCursorVisibility();
};
void ucommandhandlers_chForceQuit(string255 (*s))
{
    UNUSED ((*s));
    GameState = gsConfirm;
    ucommands_ParseCommand_2(__str0, true);
};
void ucommandhandlers_chConfirm(string255 (*s))
{
    UNUSED ((*s));
    if(GameState == gsConfirm)
    {
        if(LuaCmdUsed)
        {
            uio_SendIPC(__str1);
        }
        uio_SendIPC(__str2);
        GameState = gsExit;
    }
};
void ucommandhandlers_chHalt(string255 (*s))
{
    UNUSED ((*s));
    if(LuaCmdUsed)
    {
        uio_SendIPC(__str1);
    }
    uio_SendIPC(__str3);
    GameState = gsExit;
};
void ucommandhandlers_chCheckProto(string255 (*s))
{
    LongInt i;
    if(isDeveloperMode)
    {
        i = uutils_StrToInt((*s));
        udebug_checkFails(i <= cNetProtoVersion, _strappend(_strconcat(_strconcat(_strconcat(__str4, uutils_IntToStr(i)), __str5), uutils_IntToStr(cNetProtoVersion)), 0x29), true);
        udebug_checkFails(i >= cNetProtoVersion, _strappend(_strconcat(_strconcat(_strconcat(__str6, uutils_IntToStr(i)), __str5), uutils_IntToStr(cNetProtoVersion)), 0x29), true);
    }
};
void ucommandhandlers_chTeamLocal(string255 (*s))
{
    UNUSED ((*s));
    if(!isDeveloperMode)
    {
        return;
    }
    if(CurrentTeam == NULL)
    {
        udebug_OutError(_strconcat(errmsgIncorrectUse, __str7), true);
    }
    CurrentTeam->ExtDriven = true;
};
void ucommandhandlers_chScript(string255 (*s))
{
    if((*s).s[1] == 0x22)
    {
        fpcrtl_Delete((*s), 1, 1);
    }
    if((*s).s[((Byte)(*s).s[0])] == 0x22)
    {
        fpcrtl_Delete((*s), ((Byte)(*s).s[0]), 1);
    }
    cScriptName = (*s);
    uscript_ScriptLoad((*s), true);
};
void ucommandhandlers_chScriptParam(string255 (*s))
{
    uscript_ScriptSetString(__str8, (*s));
    uscript_ScriptCall_1(__str9);
};
void ucommandhandlers_chCurU_p(string255 (*s))
{
    UNUSED ((*s));
    uutils_updateCursorMovementDelta((LocalMessage & gmPrecise) != 0, -1, &(CursorMovementY));
};
void ucommandhandlers_chCurU_m(string255 (*s))
{
    UNUSED ((*s));
    if(CursorMovementY < 0)
    {
        uutils_updateCursorMovementDelta((LocalMessage & gmPrecise) != 0, 0, &(CursorMovementY));
    }
};
void ucommandhandlers_chCurD_p(string255 (*s))
{
    UNUSED ((*s));
    uutils_updateCursorMovementDelta((LocalMessage & gmPrecise) != 0, 1, &(CursorMovementY));
};
void ucommandhandlers_chCurD_m(string255 (*s))
{
    UNUSED ((*s));
    if(CursorMovementY > 0)
    {
        uutils_updateCursorMovementDelta((LocalMessage & gmPrecise) != 0, 0, &(CursorMovementY));
    }
};
void ucommandhandlers_chCurL_p(string255 (*s))
{
    UNUSED ((*s));
    uutils_updateCursorMovementDelta((LocalMessage & gmPrecise) != 0, -1, &(CursorMovementX));
};
void ucommandhandlers_chCurL_m(string255 (*s))
{
    UNUSED ((*s));
    if(CursorMovementX < 0)
    {
        uutils_updateCursorMovementDelta((LocalMessage & gmPrecise) != 0, 0, &(CursorMovementX));
    }
};
void ucommandhandlers_chCurR_p(string255 (*s))
{
    UNUSED ((*s));
    uutils_updateCursorMovementDelta((LocalMessage & gmPrecise) != 0, 1, &(CursorMovementX));
};
void ucommandhandlers_chCurR_m(string255 (*s))
{
    UNUSED ((*s));
    if(CursorMovementX > 0)
    {
        uutils_updateCursorMovementDelta((LocalMessage & gmPrecise) != 0, 0, &(CursorMovementX));
    }
};
void ucommandhandlers_chLeft_p(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str10);
    }
    bShowFinger = false;
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmLeft & InputMask);
    }
    uscript_ScriptCall_1(__str11);
};
void ucommandhandlers_chLeft_m(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str12);
    }
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message & ~(gmLeft & InputMask);
    }
    uscript_ScriptCall_1(__str13);
};
void ucommandhandlers_chRight_p(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str14);
    }
    bShowFinger = false;
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmRight & InputMask);
    }
    uscript_ScriptCall_1(__str15);
};
void ucommandhandlers_chRight_m(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str16);
    }
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message & ~(gmRight & InputMask);
    }
    uscript_ScriptCall_1(__str17);
};
void ucommandhandlers_chUp_p(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str18);
    }
    bShowFinger = false;
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmUp & InputMask);
    }
    uscript_ScriptCall_1(__str19);
};
void ucommandhandlers_chUp_m(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str20);
    }
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message & ~(gmUp & InputMask);
    }
    uscript_ScriptCall_1(__str21);
};
void ucommandhandlers_chDown_p(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str22);
    }
    bShowFinger = false;
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmDown & InputMask);
    }
    uscript_ScriptCall_1(__str23);
};
void ucommandhandlers_chDown_m(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str24);
    }
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message & ~(gmDown & InputMask);
    }
    uscript_ScriptCall_1(__str25);
};
void ucommandhandlers_chPrecise_p(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str26);
    }
    bShowFinger = false;
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmPrecise & InputMask);
    }
    uscript_ScriptCall_1(__str27);
};
void ucommandhandlers_chPrecise_m(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str28);
    }
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message & ~(gmPrecise & InputMask);
    }
    uscript_ScriptCall_1(__str29);
};
void ucommandhandlers_chLJump(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str30);
    }
    bShowFinger = false;
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmLJump & InputMask);
    }
    uscript_ScriptCall_1(__str31);
};
void ucommandhandlers_chHJump(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str32);
    }
    bShowFinger = false;
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmHJump & InputMask);
    }
    uscript_ScriptCall_1(__str33);
};
void ucommandhandlers_chAttack_p(string255 (*s))
{
    boolean inbtwnTrgtAttks;
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    bShowFinger = false;
    {
        uutils_AddFileLog(_strconcat(__str34, uutils_IntToStr((*CurrentHedgehog->Gear).State)));
        if(((*CurrentHedgehog->Gear).State & gstHHDriven) != 0)
        {
            inbtwnTrgtAttks = ((GameFlags & gfInfAttack) != 0) && ((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_NeedTarget) != 0);
            if(!inbtwnTrgtAttks)
            {
                FollowGear = CurrentHedgehog->Gear;
            }
            if(!isExternalSource)
            {
                uio_SendIPC(__str35);
            }
            (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmAttack & InputMask);
            uscript_ScriptCall_1(__str36);
        }
    }
};
void ucommandhandlers_chAttack_m(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    {
        if(!isExternalSource && (((*CurrentHedgehog->Gear).Message & gmAttack) != 0))
        {
            uio_SendIPC(__str37);
        }
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message & ~(gmAttack & InputMask);
        uscript_ScriptCall_1(__str38);
    }
};
void ucommandhandlers_chSwitch(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(__str39);
    }
    bShowFinger = false;
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmSwitch & InputMask);
    }
    uscript_ScriptCall_1(__str40);
};
void ucommandhandlers_chNextTurn(string255 (*s))
{
    PGear gi;
    UNUSED ((*s));
    if(udebug_checkFails(AllInactive, __str41, true))
    {
        return;
    }
    CheckSum = CheckSum ^ GameTicks;
    gi = GearsList;
    while(gi != NULL)
    {
        {
            CheckSum = (((((((CheckSum ^ (*gi).X.Round) ^ (*gi).X.Frac) ^ (*gi).dX.Round) ^ (*gi).dX.Frac) ^ (*gi).Y.Round) ^ (*gi).Y.Frac) ^ (*gi).dY.Round) ^ (*gi).dY.Frac;
        }
        urandom_AddRandomness(CheckSum);
        gi = gi->NextGear;
    }
    if(!isExternalSource)
    {
        (*s).s[0] = 0x5;
        (*s).s[1] = 0x4e;
        sdlh_SDLNet_Write32(CheckSum, &((*s).s[2]));
        uio_SendIPC((*s));
    }
    else
    {
        udebug_checkFails(CurrentTeam->hasGone || (CheckSum == lastTurnChecksum), __str42, true);
    }
    uutils_AddFileLog(_strconcat(__str43, uutils_IntToStr(GameTicks)));
};
void ucommandhandlers_chTimer(string255 (*s))
{
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(udebug_checkFails((((*s).s[0] == 0x1) && ((*s).s[1] >= 0x31)) && ((*s).s[1] <= 0x35), __str44, true))
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC((*s));
    }
    bShowFinger = false;
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmTimer & InputMask);
        (*CurrentHedgehog->Gear).MsgParam = ((Byte)(*s).s[1]) - (0x30);
        uscript_ScriptCall_2(__str45, (*CurrentHedgehog->Gear).MsgParam);
    }
};
void ucommandhandlers_chTimerU(string255 (*s))
{
    LongWord t;
    Byte tb;
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(((*CurrentHedgehog->Gear).Message & gmPrecise) == 0)
    {
        t = ugearshedgehog_HHGetTimerMsg(CurrentHedgehog->Gear);
    }
    else
    {
        t = ugearshedgehog_HHGetBouncinessMsg(CurrentHedgehog->Gear);
    }
    if(t != MSGPARAM_INVALID)
    {
        ++t;
        if(t > 5)
        {
            t = 1;
        }
        tb = t % 255;
        ucommands_ParseCommand_2(_strappend(__str46, ((char)tb + (0x30))), true);
    }
};
void ucommandhandlers_chSlot(string255 (*s))
{
    LongWord slot;
    string255 ss;
    if(((*s).s[0] != 0x1) || uutils_CheckNoTeamOrHH())
    {
        return;
    }
    slot = ((Byte)(*s).s[1]) - 49;
    if(slot > cMaxSlotIndex)
    {
        return;
    }
    if(!isExternalSource)
    {
        ss.s[0] = 0x1;
        ss.s[1] = ((char)((Byte)(*s).s[1]) + 79);
        uio_SendIPC(ss);
    }
    bShowFinger = false;
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmSlot & InputMask);
        (*CurrentHedgehog->Gear).MsgParam = slot;
        uscript_ScriptCall_2(__str47, (*CurrentHedgehog->Gear).MsgParam);
    }
};
void ucommandhandlers_chSetWeapon(string255 (*s))
{
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if((*s).s[1] == 0x7e)
    {
        (*s).s[1] = 0x0;
    }
    if(udebug_checkFails(((*s).s[0] == 0x1) && ((*s).s[1] <= ((char)60)), __str48, true))
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(_strprepend(0x77, (*s)));
    }
    {
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmWeapon & InputMask);
        (*CurrentHedgehog->Gear).MsgParam = ((Byte)(*s).s[1]);
        uscript_ScriptCall_2(__str49, (*CurrentHedgehog->Gear).MsgParam);
    }
};
void ucommandhandlers_chTaunt(string255 (*s))
{
    if(((*s).s[0] != 0x1) || uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(((TWave)(*s).s[1]) > 8)
    {
        return;
    }
    if(!isExternalSource)
    {
        uio_SendIPC(_strprepend(0x74, (*s)));
    }
    ugearshedgehog_PlayTaunt(((Byte)(*s).s[1]));
};
void ucommandhandlers_chPut(string255 (*s))
{
    UNUSED ((*s));
    uio_doPut(0, 0, false);
};
void ucommandhandlers_chCapture(string255 (*s))
{
    UNUSED ((*s));
    flagMakeCapture = true;
    flagDumpLand = (LocalMessage & gmPrecise) != 0;
};
void ucommandhandlers_chRecord(string255 (*s))
{
    UNUSED ((*s));
};
void ucommandhandlers_chSetMap(string255 (*s))
{
    uconsole_WriteLnToConsole(_strconcat(__str50, (*s)));
    if(isDeveloperMode)
    {
        uconsole_WriteLnToConsole(__str51);
        if(_strcompare((*s), __str52))
        {
            cPathz[ptMapCurrent] = (*s);
        }
        else
        {
            cPathz[ptMapCurrent] = _strconcat(_strappend(cPathz[ptMaps], 0x2f), (*s));
        }
        InitStepsFlags = InitStepsFlags | cifMap;
    }
    else
    {
        uconsole_WriteLnToConsole(__str53);
    }
    cMapName = (*s);
    uscript_ScriptLoad(_strconcat(_strconcat(__str54, (*s)), __str55), false);
};
void ucommandhandlers_chSetTheme(string255 (*s))
{
    if(isDeveloperMode)
    {
        cPathz[ptCurrTheme] = _strconcat(_strappend(cPathz[ptThemes], 0x2f), (*s));
        Theme = (*s);
        InitStepsFlags = InitStepsFlags | cifTheme;
    }
};
void ucommandhandlers_chSetSeed(string255 (*s))
{
    string255 devStr;
    if(isDeveloperMode)
    {
        devStr = __str56;
    }
    else
    {
        devStr = __str57;
    }
    uutils_AddFileLog(_strconcat(_strconcat(_strconcat(__str58, devStr), __str59), fpcrtl_copy((*s), 1, 32)));
    if(isDeveloperMode)
    {
        urandom_SetRandomSeed((*s), true);
        cSeed = (*s);
        InitStepsFlags = InitStepsFlags | cifRandomize;
        uutils_AddFileLog(__str60);
    }
    else
    {
        uutils_AddFileLog(__str61);
    }
};
void ucommandhandlers_chAmmoMenu(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        bShowAmmoMenu = !bShowAmmoMenu;
    }
    else
    {
        {
            {
                bSelected = false;
                if(bShowAmmoMenu)
                {
                    bShowAmmoMenu = false;
                }
                else
                {
                    if((((*CurrentTeam).Hedgehogs[(*CurrentTeam).CurrHedgehog].Gear == NULL) || (((*CurrentTeam).Hedgehogs[(*CurrentTeam).CurrHedgehog].Gear->State & (gstAttacking | gstAttacked)) != 0)) || (((*CurrentTeam).Hedgehogs[(*CurrentTeam).CurrHedgehog].Gear->State & gstHHDriven) == 0))
                    {
                    }
                    else
                    {
                        bShowAmmoMenu = true;
                    }
                }
            }
        }
    }
};
void ucommandhandlers_chVolUp_p(string255 (*s))
{
    UNUSED ((*s));
    cVolumeUpKey = true;
    uutils_updateVolumeDelta((LocalMessage & gmPrecise) != 0);
};
void ucommandhandlers_chVolUp_m(string255 (*s))
{
    UNUSED ((*s));
    cVolumeUpKey = false;
    uutils_updateVolumeDelta((LocalMessage & gmPrecise) != 0);
};
void ucommandhandlers_chVolDown_p(string255 (*s))
{
    UNUSED ((*s));
    cVolumeDownKey = true;
    uutils_updateVolumeDelta((LocalMessage & gmPrecise) != 0);
};
void ucommandhandlers_chVolDown_m(string255 (*s))
{
    UNUSED ((*s));
    cVolumeDownKey = false;
    uutils_updateVolumeDelta((LocalMessage & gmPrecise) != 0);
};
void ucommandhandlers_chMute(string255 (*s))
{
    UNUSED ((*s));
    cMuteToggle = true;
};
void ucommandhandlers_chFindhh(string255 (*s))
{
    UNUSED ((*s));
    if(uutils_CheckNoTeamOrHH())
    {
        return;
    }
    if(autoCameraOn)
    {
        FollowGear = NULL;
        ucaptions_AddCaption(trmsg[sidAutoCameraOff], capcolSetting, capgrpVolume);
        autoCameraOn = false;
    }
    else
    {
        ucaptions_AddCaption(trmsg[sidAutoCameraOn], capcolSetting, capgrpVolume);
        bShowFinger = true;
        if(!CurrentHedgehog->Unplaced)
        {
            FollowGear = CurrentHedgehog->Gear;
        }
        autoCameraOn = true;
    }
};
void ucommandhandlers_chPause(string255 (*s))
{
    if((GameType != gmtNet) || (_strcompare((*s), __str62)))
    {
        isPaused = !isPaused;
    }
    else
    {
        if(CurrentTeam->ExtDriven || (CurrentHedgehog->BotLevel > 0))
        {
            isAFK = !isAFK;
        }
        else
        {
            isAFK = false;
        }
    }
    uworld_updateCursorVisibility();
};
void ucommandhandlers_chRotateMask(string255 (*s))
{
    UNUSED ((*s));
    if((LocalMessage & (gmPrecise | gmSwitch)) == (gmPrecise | gmSwitch))
    {
        if(UIDisplay != uiNone)
        {
            UIDisplay = uiNone;
        }
        else
        {
            UIDisplay = uiAll;
        }
    }
    else
    {
        if(UIDisplay != uiNoTeams)
        {
            UIDisplay = uiNoTeams;
        }
        else
        {
            UIDisplay = uiAll;
        }
    }
};
void ucommandhandlers_chRotateTags(string255 (*s))
{
    UNUSED ((*s));
    if((LocalMessage & gmSwitch) == gmSwitch)
    {
        if((cTagsMask & htTransparent) == 0)
        {
            cTagsMask = cTagsMask | htTransparent;
            cPrevTagsMask = cPrevTagsMask | htTransparent;
        }
        else
        {
            cTagsMask = cTagsMask & ~htTransparent;
            cPrevTagsMask = cPrevTagsMask & ~htTransparent;
        }
    }
    else
    {
        if((LocalMessage & gmPrecise) == gmPrecise)
        {
            cPrevTagsMask = cTagsMask;
            if((GameFlags & gfInvulnerable) == 0)
            {
                cTagsMask = cTagsMasks[cTagsMask];
            }
            else
            {
                cTagsMask = cTagsMasksNoHealth[cTagsMask];
            }
        }
        else
        {
            if((cTagsMask & ((htTeamName | htName) | htHealth)) == 0)
            {
                cTagsMask = cPrevTagsMask;
                if((GameFlags & gfInvulnerable) != 0)
                {
                    cTagsMask = cTagsMask & ~htHealth;
                }
            }
            else
            {
                cPrevTagsMask = cTagsMask;
                cTagsMask = cTagsMask & ~((htTeamName | htName) | htHealth);
            }
        }
    }
};
void ucommandhandlers_chSpeedup_p(string255 (*s))
{
    UNUSED ((*s));
    SpeedStart = RealTicks;
    isSpeed = true;
};
void ucommandhandlers_chSpeedup_m(string255 (*s))
{
    UNUSED ((*s));
    isSpeed = false;
};
void ucommandhandlers_chZoomIn(string255 (*s))
{
    UNUSED ((*s));
    if((LocalMessage & gmPrecise) != 0)
    {
        ZoomValue = ZoomValue + cZoomDeltaSmall;
    }
    else
    {
        ZoomValue = ZoomValue + cZoomDelta;
    }
    if(ZoomValue > cMinZoomLevel)
    {
        ZoomValue = cMinZoomLevel;
    }
};
void ucommandhandlers_chZoomOut(string255 (*s))
{
    UNUSED ((*s));
    if((LocalMessage & gmPrecise) != 0)
    {
        ZoomValue = ZoomValue - cZoomDeltaSmall;
    }
    else
    {
        ZoomValue = ZoomValue - cZoomDelta;
    }
    if(ZoomValue < cMaxZoomLevel)
    {
        ZoomValue = cMaxZoomLevel;
    }
};
void ucommandhandlers_chZoomReset(string255 (*s))
{
    UNUSED ((*s));
    if((LocalMessage & gmPrecise) != 0)
    {
        ZoomValue = cDefaultZoomLevel;
    }
    else
    {
        ZoomValue = UserZoom;
    }
};
void ucommandhandlers_chMapGen(string255 (*s))
{
    cMapGen = ((TMapGen)uutils_StrToInt((*s)));
};
void ucommandhandlers_chTemplateFilter(string255 (*s))
{
    cTemplateFilter = uutils_StrToInt((*s));
};
void ucommandhandlers_chFeatureSize(string255 (*s))
{
    cFeatureSize = uutils_StrToInt((*s));
};
void ucommandhandlers_chInactDelay(string255 (*s))
{
    cInactDelay = uutils_StrToInt((*s));
};
void ucommandhandlers_chReadyDelay(string255 (*s))
{
    cReadyDelay = uutils_StrToInt((*s));
};
void ucommandhandlers_chCaseFactor(string255 (*s))
{
    cCaseFactor = uutils_StrToInt((*s));
};
void ucommandhandlers_chHealthCaseProb(string255 (*s))
{
    cHealthCaseProb = uutils_StrToInt((*s));
};
void ucommandhandlers_chHealthCaseAmount(string255 (*s))
{
    cHealthCaseAmount = uutils_StrToInt((*s));
};
void ucommandhandlers_chSuddenDTurns(string255 (*s))
{
    cSuddenDTurns = uutils_StrToInt((*s));
};
void ucommandhandlers_chWaterRise(string255 (*s))
{
    cWaterRise = uutils_StrToInt((*s));
};
void ucommandhandlers_chHealthDecrease(string255 (*s))
{
    cHealthDecrease = uutils_StrToInt((*s));
};
void ucommandhandlers_chInitHealth(string255 (*s))
{
    cInitHealth = uutils_StrToInt((*s));
};
void ucommandhandlers_chDamagePercent(string255 (*s))
{
    cDamagePercent = uutils_StrToInt((*s));
};
void ucommandhandlers_chRopePercent(string255 (*s))
{
    cRopePercent = uutils_StrToInt((*s));
};
void ucommandhandlers_chGetAwayTime(string255 (*s))
{
    cGetAwayTime = uutils_StrToInt((*s));
};
void ucommandhandlers_chMineDudPercent(string255 (*s))
{
    cMineDudPercent = uutils_StrToInt((*s));
};
void ucommandhandlers_chLandMines(string255 (*s))
{
    cLandMines = uutils_StrToInt((*s));
};
void ucommandhandlers_chAirMines(string255 (*s))
{
    cAirMines = uutils_StrToInt((*s));
};
void ucommandhandlers_chSentries(string255 (*s))
{
    cSentries = uutils_StrToInt((*s));
};
void ucommandhandlers_chExplosives(string255 (*s))
{
    cExplosives = uutils_StrToInt((*s));
};
void ucommandhandlers_chGameFlags(string255 (*s))
{
    GameFlags = uutils_StrToInt((*s));
    if((GameFlags & gfSharedAmmo) != 0)
    {
        GameFlags = GameFlags & ~gfPerHogAmmo;
    }
};
void ucommandhandlers_chHedgehogTurnTime(string255 (*s))
{
    cHedgehogTurnTime = uutils_StrToInt((*s));
};
void ucommandhandlers_chMinesTime(string255 (*s))
{
    cMinesTime = uutils_StrToInt((*s));
};
void ucommandhandlers_chFastUntilLag(string255 (*s))
{
    fastUntilLag = uutils_StrToInt((*s)) != 0;
    fastForward = fastUntilLag;
    if(!fastUntilLag)
    {
        uvisualgearslist_AddVisualGear_3(0, 0, vgtTeamHealthSorter);
        uvisualgearslist_AddVisualGear_3(0, 0, vgtSmoothWindBar);
    }
};
void ucommandhandlers_chFastForward(string255 (*cmd))
{
    string255 str0;
    string255 str1;
    string255 str2;
    Integer h;
    Integer m;
    Integer s;
    if(GameType != gmtDemo)
    {
        return;
    }
    if(uutils_CountChar((*cmd), 0x3a) > 2)
    {
        return;
    }
    str0 = (*cmd);
    uutils_SplitByChar(&(str0), &(str1), 0x3a);
    uutils_SplitByChar(&(str1), &(str2), 0x3a);
    if(_strncompare(str2, __str52))
    {
        h = uutils_StrToInt(str0);
        m = uutils_StrToInt(str1);
        s = uutils_StrToInt(str2);
    }
    else
    {
        if(_strncompare(str1, __str52))
        {
            h = 0;
            m = uutils_StrToInt(str0);
            s = uutils_StrToInt(str1);
        }
        else
        {
            h = 0;
            m = 0;
            s = uutils_StrToInt(str0);
        }
    }
    FFGameTick = ((s + (m * 60)) + ((h * 60) * 60)) * 1000;
    if(FFGameTick > GameTicks)
    {
        fastUntilLag = true;
        fastForward = true;
    }
};
void ucommandhandlers_chStopFastForward(string255 (*s))
{
    if(GameType != gmtDemo)
    {
        return;
    }
    fastUntilLag = false;
    fastForward = false;
    uvisualgearslist_AddVisualGear_3(0, 0, vgtTeamHealthSorter);
    uvisualgearslist_AddVisualGear_3(0, 0, vgtSmoothWindBar);
};
void ucommandhandlers_chCampVar(string255 (*s))
{
    CampaignVariable = (*s);
};
void ucommandhandlers_chMissVar(string255 (*s))
{
    MissionVariable = (*s);
};
void ucommandhandlers_chWorldEdge(string255 (*s))
{
    WorldEdge = ((TWorldEdge)uutils_StrToInt((*s)));
};
void ucommandhandlers_chAdvancedMapGenMode(string255 (*s))
{
    UNUSED ((*s));
    cAdvancedMapGenMode = true;
};
void ucommandhandlers_chShowMission_p(string255 (*s))
{
    UNUSED ((*s));
    isShowMission = true;
};
void ucommandhandlers_chShowMission_m(string255 (*s))
{
    UNUSED ((*s));
    isShowMission = false;
    if(!isForceMission)
    {
        uworld_HideMission();
    }
};
void ucommandhandlers_chGearInfo(string255 (*s))
{
    UNUSED ((*s));
    isShowGearInfo = !isShowGearInfo;
};
void ucommandhandlers_initModule()
{
    ucommands_RegisterVariable_4(__str63, &(ucommandhandlers_chRight_p), false, true);
    ucommands_RegisterVariable_4(__str64, &(ucommandhandlers_chRight_m), false, true);
    ucommands_RegisterVariable_4(__str65, &(ucommandhandlers_chUp_p), false, true);
    ucommands_RegisterVariable_4(__str66, &(ucommandhandlers_chUp_m), false, true);
    ucommands_RegisterVariable_4(__str67, &(ucommandhandlers_chLeft_p), false, true);
    ucommands_RegisterVariable_4(__str68, &(ucommandhandlers_chLeft_m), false, true);
    ucommands_RegisterVariable_3(__str69, &(ucommandhandlers_chAttack_p), false);
    ucommands_RegisterVariable_4(__str70, &(ucommandhandlers_chDown_p), false, true);
    ucommands_RegisterVariable_4(__str71, &(ucommandhandlers_chDown_m), false, true);
    ucommands_RegisterVariable_4(__str72, &(ucommandhandlers_chHJump), false, true);
    ucommands_RegisterVariable_4(__str73, &(ucommandhandlers_chLJump), false, true);
    ucommands_RegisterVariable_3(__str74, &(ucommandhandlers_chNextTurn), false);
    ucommands_RegisterVariable_3(__str75, &(ucommandhandlers_chAttack_m), false);
    ucommands_RegisterVariable_3(__str76, &(ucommandhandlers_chSlot), false);
    ucommands_RegisterVariable_4(__str77, &(ucommandhandlers_chSetWeapon), false, true);
    ucommands_RegisterVariable_3(__str78, &(ucommandhandlers_chGenCmd), false);
    ucommands_RegisterVariable_3(__str79, &(ucommandhandlers_chScript), false);
    ucommands_RegisterVariable_3(__str80, &(ucommandhandlers_chScriptParam), false);
    ucommands_RegisterVariable_3(__str81, &(ucommandhandlers_chCheckProto), true);
    ucommands_RegisterVariable_3(__str82, &(ucommandhandlers_chFastUntilLag), false);
    ucommands_RegisterVariable_3(__str83, &(ucommandhandlers_chCapture), true);
    ucommands_RegisterVariable_3(__str84, &(ucommandhandlers_chRotateMask), true);
    ucommands_RegisterVariable_3(__str85, &(ucommandhandlers_chRotateTags), true);
    ucommands_RegisterVariable_3(__str86, &(ucommandhandlers_chTeamLocal), false);
    ucommands_RegisterVariable_3(__str87, &(ucommandhandlers_chSetMap), false);
    ucommands_RegisterVariable_3(__str88, &(ucommandhandlers_chSetTheme), false);
    ucommands_RegisterVariable_3(__str89, &(ucommandhandlers_chSetSeed), false);
    ucommands_RegisterVariable_3(__str90, &(ucommandhandlers_chTemplateFilter), false);
    ucommands_RegisterVariable_3(__str91, &(ucommandhandlers_chMapGen), false);
    ucommands_RegisterVariable_3(__str92, &(ucommandhandlers_chTemplateFilter), false);
    ucommands_RegisterVariable_3(__str93, &(ucommandhandlers_chFeatureSize), false);
    ucommands_RegisterVariable_3(__str94, &(ucommandhandlers_chInactDelay), false);
    ucommands_RegisterVariable_3(__str95, &(ucommandhandlers_chReadyDelay), false);
    ucommands_RegisterVariable_3(__str96, &(ucommandhandlers_chCaseFactor), false);
    ucommands_RegisterVariable_3(__str97, &(ucommandhandlers_chHealthCaseProb), false);
    ucommands_RegisterVariable_3(__str98, &(ucommandhandlers_chHealthCaseAmount), false);
    ucommands_RegisterVariable_3(__str99, &(ucommandhandlers_chSuddenDTurns), false);
    ucommands_RegisterVariable_3(__str100, &(ucommandhandlers_chWaterRise), false);
    ucommands_RegisterVariable_3(__str101, &(ucommandhandlers_chHealthDecrease), false);
    ucommands_RegisterVariable_3(__str102, &(ucommandhandlers_chInitHealth), false);
    ucommands_RegisterVariable_3(__str103, &(ucommandhandlers_chDamagePercent), false);
    ucommands_RegisterVariable_3(__str104, &(ucommandhandlers_chRopePercent), false);
    ucommands_RegisterVariable_3(__str105, &(ucommandhandlers_chGetAwayTime), false);
    ucommands_RegisterVariable_3(__str106, &(ucommandhandlers_chMineDudPercent), false);
    ucommands_RegisterVariable_3(__str107, &(ucommandhandlers_chLandMines), false);
    ucommands_RegisterVariable_3(__str108, &(ucommandhandlers_chAirMines), false);
    ucommands_RegisterVariable_3(__str109, &(ucommandhandlers_chSentries), false);
    ucommands_RegisterVariable_3(__str110, &(ucommandhandlers_chExplosives), false);
    ucommands_RegisterVariable_3(__str111, &(ucommandhandlers_chGameFlags), false);
    ucommands_RegisterVariable_3(__str112, &(ucommandhandlers_chHedgehogTurnTime), false);
    ucommands_RegisterVariable_3(__str113, &(ucommandhandlers_chMinesTime), false);
    ucommands_RegisterVariable_3(__str114, &(ucommandhandlers_chQuit), true);
    ucommands_RegisterVariable_3(__str115, &(ucommandhandlers_chForceQuit), true);
    ucommands_RegisterVariable_3(__str0, &(ucommandhandlers_chConfirm), true);
    ucommands_RegisterVariable_3(__str116, &(ucommandhandlers_chHalt), true);
    ucommands_RegisterVariable_3(__str117, &(ucommandhandlers_chSpeedup_p), true);
    ucommands_RegisterVariable_3(__str118, &(ucommandhandlers_chSpeedup_m), true);
    ucommands_RegisterVariable_3(__str119, &(ucommandhandlers_chZoomIn), true);
    ucommands_RegisterVariable_3(__str120, &(ucommandhandlers_chZoomOut), true);
    ucommands_RegisterVariable_3(__str121, &(ucommandhandlers_chZoomReset), true);
    ucommands_RegisterVariable_3(__str122, &(ucommandhandlers_chAmmoMenu), true);
    ucommands_RegisterVariable_4(__str123, &(ucommandhandlers_chPrecise_p), false, true);
    ucommands_RegisterVariable_4(__str124, &(ucommandhandlers_chPrecise_m), false, true);
    ucommands_RegisterVariable_3(__str125, &(ucommandhandlers_chSwitch), false);
    ucommands_RegisterVariable_4(__str126, &(ucommandhandlers_chTimer), false, true);
    ucommands_RegisterVariable_3(__str127, &(ucommandhandlers_chTaunt), false);
    ucommands_RegisterVariable_3(__str128, &(ucommandhandlers_chPut), false);
    ucommands_RegisterVariable_3(__str129, &(ucommandhandlers_chVolUp_p), true);
    ucommands_RegisterVariable_3(__str130, &(ucommandhandlers_chVolUp_m), true);
    ucommands_RegisterVariable_3(__str131, &(ucommandhandlers_chVolDown_p), true);
    ucommands_RegisterVariable_3(__str132, &(ucommandhandlers_chVolDown_m), true);
    ucommands_RegisterVariable_3(__str133, &(ucommandhandlers_chMute), true);
    ucommands_RegisterVariable_3(__str134, &(ucommandhandlers_chFindhh), true);
    ucommands_RegisterVariable_3(__str135, &(ucommandhandlers_chPause), true);
    ucommands_RegisterVariable_3(__str136, &(ucommandhandlers_chCurU_p), true);
    ucommands_RegisterVariable_3(__str137, &(ucommandhandlers_chCurU_m), true);
    ucommands_RegisterVariable_3(__str138, &(ucommandhandlers_chCurD_p), true);
    ucommands_RegisterVariable_3(__str139, &(ucommandhandlers_chCurD_m), true);
    ucommands_RegisterVariable_3(__str140, &(ucommandhandlers_chCurL_p), true);
    ucommands_RegisterVariable_3(__str141, &(ucommandhandlers_chCurL_m), true);
    ucommands_RegisterVariable_3(__str142, &(ucommandhandlers_chCurR_p), true);
    ucommands_RegisterVariable_3(__str143, &(ucommandhandlers_chCurR_m), true);
    ucommands_RegisterVariable_3(__str144, &(ucommandhandlers_chCampVar), true);
    ucommands_RegisterVariable_3(__str145, &(ucommandhandlers_chMissVar), true);
    ucommands_RegisterVariable_3(__str146, &(ucommandhandlers_chRecord), true);
    ucommands_RegisterVariable_3(__str147, &(ucommandhandlers_chWorldEdge), false);
    ucommands_RegisterVariable_3(__str148, &(ucommandhandlers_chAdvancedMapGenMode), false);
    ucommands_RegisterVariable_3(__str149, &(ucommandhandlers_chFastForward), true);
    ucommands_RegisterVariable_3(__str150, &(ucommandhandlers_chStopFastForward), true);
    ucommands_RegisterVariable_3(__str151, &(ucommandhandlers_chShowMission_p), true);
    ucommands_RegisterVariable_3(__str152, &(ucommandhandlers_chShowMission_m), true);
    ucommands_RegisterVariable_3(__str153, &(ucommandhandlers_chGearInfo), true);
    ucommands_RegisterVariable_3(__str154, &(ucommandhandlers_chTimerU), true);
};
void ucommandhandlers_freeModule()
{
};
