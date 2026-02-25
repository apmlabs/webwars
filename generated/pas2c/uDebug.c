#include "fpcrtl.h"

#include "uDebug.h"
boolean allOK;
#include "SDLh.h"
#include "uConsole.h"
#include "uCommands.h"
#include "uConsts.h"
static const string255 __str1 = STRINIT(": ");
static const string255 __str0 = STRINIT("fatal ");
void udebug_OutError(string255 Msg,boolean isFatalError)
{
    uconsole_WriteLnToConsole(Msg);
    if(isFatalError)
    {
        ucommands_ParseCommand_2(_strconcat(__str0, lastConsoleline), true);
        fpcrtl_halt(HaltFatalError);
    }
};
void udebug_TryDo(boolean Assert,string255 Msg,boolean isFatal)
{
    if(!Assert)
    {
        udebug_OutError(Msg, isFatal);
    }
};
boolean udebug_checkFails(boolean Assert,string255 Msg,boolean isFatal)
{
    boolean checkfails_result;
    if(!Assert)
    {
        lastConsoleline = Msg;
        udebug_OutError(Msg, isFatal);
    }
    allOK = allOK && (Assert || !isFatal);
    checkfails_result = !Assert && isFatal;
    return checkfails_result;
};
boolean udebug_SDLCheck(boolean Assert,string255 Msg,boolean isFatal)
{
    boolean sdlcheck_result;
    string255 s;
    if(!Assert)
    {
        s = fpcrtl_pchar2str(SDL_GetError());
        udebug_OutError(_strconcat(_strconcat(Msg, __str1), s), isFatal);
    }
    allOK = allOK && (Assert || !isFatal);
    sdlcheck_result = !Assert && isFatal;
    return sdlcheck_result;
};
