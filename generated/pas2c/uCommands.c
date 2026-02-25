#include "fpcrtl.h"

#include "uCommands.h"
boolean isDeveloperMode;
boolean isExternalSource;
#include "uConsts.h"
#include "uVariables.h"
#include "uConsole.h"
#include "uUtils.h"
#include "SDLh.h"
static const string255 __str11 = STRINIT("/-attack");
static const string255 __str10 = STRINIT("/-down");
static const string255 __str9 = STRINIT("/-up");
static const string255 __str8 = STRINIT("/-right");
static const string255 __str7 = STRINIT("/-left");
static const string255 __str6 = STRINIT("gencmd R");
static const string255 __str5 = STRINIT(": \"/");
static const string255 __str4 = STRINIT(": \"$");
static const string255 __str3 = STRINIT("Unknown command: ");
static const string255 __str2 = STRINIT("");
static const string255 __str1 = STRINIT("[Cmd] ");
static const string255 __str0 = STRINIT("fatal RegisterVariable: value = nil");
typedef struct __TVariable * PVariable;
typedef struct __TVariable {
            PVariable Next;
            string255 Name;
            ucommands_TCommandHandler Handler;
            boolean Trusted;
            boolean Rand;
        } TVariable;
static PVariable Variables;
void ucommands_RegisterVariable_3(string255 Name,ucommands_TCommandHandler ucommands_p,boolean Trusted)
{
    ucommands_RegisterVariable_4(Name, ucommands_p, Trusted, false);
};
void ucommands_RegisterVariable_4(string255 Name,ucommands_TCommandHandler ucommands_p,boolean Trusted,boolean Rand)
{
    PVariable value;
    fpcrtl_new(value);
    if(value == NULL)
    {
        ucommands_ParseCommand_2(__str0, true);
    }
    fpcrtl_FillChar((*value), sizeof(TVariable), 0);
    value->Name = Name;
    value->Handler = ucommands_p;
    value->Trusted = Trusted;
    value->Rand = Rand;
    if(Variables == NULL)
    {
        Variables = value;
    }
    else
    {
        value->Next = Variables;
        Variables = value;
    }
};
void ucommands_ParseCommand_2(string255 CmdStr,boolean TrustedSource)
{
    ucommands_ParseCommand_3(CmdStr, TrustedSource, false);
};
void ucommands_ParseCommand_3(string255 CmdStr,boolean TrustedSource,boolean ExternalSource)
{
    string255 s;
    PVariable t;
    char c;
    isExternalSource = ExternalSource || ((CurrentTeam != NULL) && CurrentTeam->ExtDriven);
    if(CmdStr.s[0] == 0x0)
    {
        return;
    }
    uutils_AddFileLog(_strconcat(__str1, uutils_sanitizeForLog(CmdStr)));
    c = CmdStr.s[1];
    if((c == 0x2f) || (c == 0x24))
    {
        fpcrtl_Delete(CmdStr, 1, 1);
    }
    s = __str2;
    uutils_SplitBySpace(&(CmdStr), &(s));
    t = Variables;
    while(t != NULL)
    {
        if(_strcompare(t->Name, CmdStr))
        {
            if(TrustedSource || t->Trusted)
            {
                if(t->Rand && !uutils_CheckNoTeamOrHH())
                {
                    CheckSum = ((CheckSum ^ ((LongWord)sdlh_SDLNet_Read32(&(CmdStr)))) ^ ((LongWord)s.s[0])) ^ GameTicks;
                }
                t->Handler(&(s));
            }
            return;
        }
        else
        {
            t = t->Next;
        }
    }
    uconsole_WriteLnToConsole(_strconcat(__str3, CmdStr));
    switch(c)
    {case '$':uconsole_WriteLnToConsole(_strappend(_strconcat(_strconcat(errmsgUnknownVariable, __str4), CmdStr), 0x22));
              break;
     default: uconsole_WriteLnToConsole(_strappend(_strconcat(_strconcat(errmsgUnknownCommand, __str5), CmdStr), 0x22));}
};
void ucommands_ParseTeamCommand(string255 s)
{
    boolean Trusted;
    Trusted = ((CurrentTeam != NULL) && !CurrentTeam->ExtDriven) && (CurrentHedgehog->BotLevel == 0);
    ucommands_ParseCommand_2(s, Trusted);
    if(((CurrentTeam != NULL) && !CurrentTeam->ExtDriven) && (ReadyTimeLeft > 1))
    {
        ucommands_ParseCommand_2(__str6, true);
    }
};
void ucommands_StopMessages(LongWord Message)
{
    if((Message & gmLeft) != 0)
    {
        ucommands_ParseCommand_2(__str7, true);
    }
    else
    {
        if((Message & gmRight) != 0)
        {
            ucommands_ParseCommand_2(__str8, true);
        }
        else
        {
            if((Message & gmUp) != 0)
            {
                ucommands_ParseCommand_2(__str9, true);
            }
            else
            {
                if((Message & gmDown) != 0)
                {
                    ucommands_ParseCommand_2(__str10, true);
                }
                else
                {
                    if((Message & gmAttack) != 0)
                    {
                        ucommands_ParseCommand_2(__str11, true);
                    }
                }
            }
        }
    }
};
void ucommands_initModule()
{
    Variables = NULL;
    isDeveloperMode = true;
};
void ucommands_freeModule()
{
    PVariable t;
    PVariable tt;
    tt = Variables;
    Variables = NULL;
    while(tt != NULL)
    {
        t = tt;
        tt = tt->Next;
        fpcrtl_dispose(t);
    }
};
