#include "fpcrtl.h"

#include "ArgParsers.h"
LongInt operatingsystem_parameter_argc = 0;
pointer operatingsystem_parameter_argv = NULL;
pointer operatingsystem_parameter_envp = NULL;
#include "uVariables.h"
#include "uTypes.h"
#include "uUtils.h"
#include "uSound.h"
#include "uConsts.h"
static const string255 __str62 = STRINIT("Please use --help to see possible arguments and their usage.");
static const string255 __str61 = STRINIT("\".");
static const string255 __str60 = STRINIT("Attempting to play demo file \"");
static const string255 __str59 = STRINIT("You must specify a demo file.");
static const string255 __str58 = STRINIT("The \"--internal\" option should not be manually used!");
static const string255 __str57 = STRINIT(".");
static const string255 __str56 = STRINIT("--internal");
static const string255 __str55 = STRINIT("\" is not a valid option.");
static const string255 __str54 = STRINIT("Lua test file specified: ");
static const string255 __str53 = STRINIT("--");
static const string255 __str52 = STRINIT("ERROR: use of --port is not allowed!");
static const string255 __str51 = STRINIT("  --lua-test <path to script>: Run a Lua test script");
static const string255 __str50 = STRINIT("  --stats-only: Write the round information to console without launching the game, useful for statistics only");
static const string255 __str49 = STRINIT("  --raw-quality <flags>: Manually specify the reduced quality flags");
static const string255 __str48 = STRINIT("  --frame-interval <milliseconds>: Set minimum interval (in ms) between each frame. Eg, 40 would make the game run at most 25 fps");
static const string255 __str47 = STRINIT("  --stereo <value>: Set stereoscopic rendering (1 to 14)");
static const string255 __str46 = STRINIT("Advanced options:");
static const string255 __str45 = STRINIT("  --protocol: Display protocol number and exit");
static const string255 __str44 = STRINIT("  --help: Show a list of command-line options and exit");
static const string255 __str43 = STRINIT("  --nick <name>: Set user nickname");
static const string255 __str42 = STRINIT("Miscellaneous:");
static const string255 __str41 = STRINIT("  --showfps: Show frames per second");
static const string255 __str40 = STRINIT("  --chat-size [default chat size in percent]");
static const string255 __str39 = STRINIT("  --translucent-tags: Enable translucent name and health tags");
static const string255 __str38 = STRINIT("  --no-healthtag: Disable hedgehog health tags");
static const string255 __str37 = STRINIT("  --no-hogtag: Disable hedgehog name tags");
static const string255 __str36 = STRINIT("  --no-teamtag: Disable team name tags");
static const string255 __str35 = STRINIT("  --altdmg: Show alternative damage");
static const string255 __str34 = STRINIT("HUD:");
static const string255 __str33 = STRINIT("  --nodampen: Don't dampen sound volume when game application loses focus");
static const string255 __str32 = STRINIT("  --nosound: Disable sound effects");
static const string255 __str31 = STRINIT("  --nomusic: Disable music");
static const string255 __str30 = STRINIT("  --volume <sound level>: Set volume between 0 and 100");
static const string255 __str29 = STRINIT("Audio:");
static const string255 __str28 = STRINIT("  --zoom <percent>: Start with custom zoom level");
static const string255 __str27 = STRINIT("  --low-quality: Lowers the game quality");
static const string255 __str26 = STRINIT("  --fullscreen-height <height in pixels>: Set fullscreen height");
static const string255 __str25 = STRINIT("  --fullscreen-width <width in pixels>: Set fullscreen width");
static const string255 __str24 = STRINIT("  --fullscreen: Start in fullscreen");
static const string255 __str23 = STRINIT("  --maximized: Start in maximized window");
static const string255 __str22 = STRINIT("  --height <height in pixels>: Set game window height");
static const string255 __str21 = STRINIT("  --width <width in pixels>: Set game window width");
static const string255 __str20 = STRINIT("Graphics:");
static const string255 __str19 = STRINIT("  --locale <name of file>: Set the game language (en.txt for example)");
static const string255 __str18 = STRINIT("  --user-prefix <path to folder>: Set the path to the custom data folder to find game content");
static const string255 __str17 = STRINIT("  --prefix <path to folder>: Set the path to the system game data folder");
static const string255 __str16 = STRINIT("File locations:");
static const string255 __str15 = STRINIT("where [options] can be any of the following:");
static const string255 __str14 = STRINIT("Usage: hwengine <path to demo file> [options]");
static const string255 __str13 = STRINIT("");
static const string255 __str12 = STRINIT("Use the command-line arguments to play a demo.");
static const string255 __str11 = STRINIT("This is the Hedgewars Engine (hwengine), used to play Hedgewars games and demos.");
static const string255 __str10 = STRINIT(" Command Line Parser Implementation by a Google Code-In Student ");
static const string255 __str9 = STRINIT("          \\/////////////          \\/////////  \\///////////      ");
static const string255 __str8 = STRINIT("         \\/\\\\\\\\\\\\\\\\\\\\\\\\\\/     \\////\\\\\\\\\\\\\\\\\\  /\\\\\\\\\\\\\\\\\\\\\\      ");
static const string255 __str7 = STRINIT("        \\/\\\\\\       \\/\\\\\\  \\///\\\\\\              \\/\\\\\\           ");
static const string255 __str6 = STRINIT("       \\/\\\\\\       \\/\\\\\\ \\//\\\\\\                \\/\\\\\\            ");
static const string255 __str5 = STRINIT("      \\/\\\\\\   \\/////\\\\\\ \\/\\\\\\                 \\/\\\\\\             ");
static const string255 __str4 = STRINIT("     \\/\\\\\\    /\\\\\\\\\\\\\\  /\\\\\\                 \\/\\\\\\              ");
static const string255 __str3 = STRINIT("     /\\\\\\               /\\\\\\/               \\/\\\\\\               ");
static const string255 __str2 = STRINIT("     /\\\\\\//////////      /\\\\\\////////  \\/////\\\\\\///             ");
static const string255 __str1 = STRINIT("      /\\\\\\\\\\\\\\\\\\\\\\\\        /\\\\\\\\\\\\\\\\\\  /\\\\\\\\\\\\\\\\\\\\\\             ");
static const string255 __str0 = STRINIT("                                                                ");
static boolean isInternal;
static boolean helpCommandUsed;
typedef PChar PCharArray[(255 + 1)];
typedef PCharArray * PPCharArray;
LongInt argparsers_ParamCount()
{
    LongInt paramcount_result;
    paramcount_result = operatingsystem_parameter_argc - 1;
    return paramcount_result;
};
string255 argparsers_ParamStr(LongInt i)
{
    string255 paramstr_result;
    paramstr_result = fpcrtl_StrPas((*((PPCharArray)operatingsystem_parameter_argv))[i]);
    return paramstr_result;
};
void argparsers_GciEasterEgg()
{
    fpcrtl_writeLn(stdout, __str0);
    fpcrtl_writeLn(stdout, __str1);
    fpcrtl_writeLn(stdout, __str2);
    fpcrtl_writeLn(stdout, __str3);
    fpcrtl_writeLn(stdout, __str4);
    fpcrtl_writeLn(stdout, __str5);
    fpcrtl_writeLn(stdout, __str6);
    fpcrtl_writeLn(stdout, __str7);
    fpcrtl_writeLn(stdout, __str8);
    fpcrtl_writeLn(stdout, __str9);
    fpcrtl_writeLn(stdout, __str0);
    fpcrtl_writeLn(stdout, __str10);
    fpcrtl_writeLn(stdout, __str0);
};
void argparsers_DisplayUsage()
{
    fpcrtl_writeLn(stdout, __str11);
    fpcrtl_writeLn(stdout, __str12);
    fpcrtl_writeLn(stdout, __str13);
    fpcrtl_writeLn(stdout, __str14);
    fpcrtl_writeLn(stdout, __str13);
    fpcrtl_writeLn(stdout, __str15);
    fpcrtl_writeLn(stdout, __str13);
    fpcrtl_writeLn(stdout, __str16);
    fpcrtl_writeLn(stdout, __str17);
    fpcrtl_writeLn(stdout, __str18);
    fpcrtl_writeLn(stdout, __str19);
    fpcrtl_writeLn(stdout, __str13);
    fpcrtl_writeLn(stdout, __str20);
    fpcrtl_writeLn(stdout, __str21);
    fpcrtl_writeLn(stdout, __str22);
    fpcrtl_writeLn(stdout, __str23);
    fpcrtl_writeLn(stdout, __str24);
    fpcrtl_writeLn(stdout, __str25);
    fpcrtl_writeLn(stdout, __str26);
    fpcrtl_writeLn(stdout, __str27);
    fpcrtl_writeLn(stdout, __str28);
    fpcrtl_writeLn(stdout, __str13);
    fpcrtl_writeLn(stdout, __str29);
    fpcrtl_writeLn(stdout, __str30);
    fpcrtl_writeLn(stdout, __str31);
    fpcrtl_writeLn(stdout, __str32);
    fpcrtl_writeLn(stdout, __str33);
    fpcrtl_writeLn(stdout, __str13);
    fpcrtl_writeLn(stdout, __str34);
    fpcrtl_writeLn(stdout, __str35);
    fpcrtl_writeLn(stdout, __str36);
    fpcrtl_writeLn(stdout, __str37);
    fpcrtl_writeLn(stdout, __str38);
    fpcrtl_writeLn(stdout, __str39);
    fpcrtl_writeLn(stdout, __str40);
    fpcrtl_writeLn(stdout, __str41);
    fpcrtl_writeLn(stdout, __str13);
    fpcrtl_writeLn(stdout, __str42);
    fpcrtl_writeLn(stdout, __str43);
    fpcrtl_writeLn(stdout, __str44);
    fpcrtl_writeLn(stdout, __str45);
    fpcrtl_writeLn(stdout, __str13);
    fpcrtl_writeLn(stdout, __str46);
    fpcrtl_writeLn(stdout, __str47);
    fpcrtl_writeLn(stdout, __str48);
    fpcrtl_writeLn(stdout, __str49);
    fpcrtl_writeLn(stdout, __str50);
    fpcrtl_writeLn(stdout, __str51);
    GameType = gmtSyntaxHelp;
    helpCommandUsed = true;
};
void argparsers_DisplayProtocol()
{
    fpcrtl_writeLn(stdout, uutils_IntToStr(cNetProtoVersion));
    GameType = gmtSyntaxHelp;
    helpCommandUsed = true;
};
void argparsers_statsOnlyGame()
{
    cOnlyStats = true;
    cReducedQuality = 0xffffffff ^ rqLowRes;
    usound_SetSound(false);
    usound_SetMusic(false);
    usound_SetVolume(0);
};
void argparsers_setIpcPort(LongInt port,boolean (*wrongParameter))
{
    if(isInternal)
    {
        ipcPort = port;
    }
    else
    {
        fpcrtl_writeLn(stderr, __str52);
        (*wrongParameter) = true;
    }
};
string255 argparsers_parseNick(string255 nick)
{
    string255 parsenick_result;
    if(isInternal)
    {
        parsenick_result = uutils_DecodeBase64(nick);
    }
    else
    {
        parsenick_result = nick;
    }
    return parsenick_result;
};
void argparsers_setStereoMode(LongInt tmp)
{
    GrayScale = false;
    UNUSED (tmp);
    cStereoMode = smNone;
};
void argparsers_startVideoRecording(LongInt (*paramIndex))
{
    UNUSED ((*paramIndex));
};
LongInt argparsers_getLongIntParameter(string255 str,LongInt (*paramIndex),boolean (*wrongParameter))
{
    LongInt getlongintparameter_result;
    LongInt tmpInt;
    LongInt c;
    ++(*paramIndex);
    fpcrtl_val(str, tmpInt);
    getlongintparameter_result = tmpInt;
    return getlongintparameter_result;
};
string255 argparsers_getstringParameter(string255 str,LongInt (*paramIndex),boolean (*wrongParameter))
{
    string255 getstringparameter_result;
    ++(*paramIndex);
    (*wrongParameter) = (_strcompare(str, __str13)) || (_strcompare(fpcrtl_copy(str, 1, 2), __str53));
    getstringparameter_result = str;
    return getstringparameter_result;
};
void argparsers_setZoom(string255 str,LongInt (*paramIndex),boolean (*wrongParameter))
{
    LongInt param;
    param = argparsers_getLongIntParameter(str, &((*paramIndex)), &((*wrongParameter)));
    if(param == 100)
    {
        return;
    }
    UserZoom = (param /(float) 100.0) * cDefaultZoomLevel;
    if(UserZoom < cMaxZoomLevel)
    {
        UserZoom = cMaxZoomLevel;
    }
    if(UserZoom > cMinZoomLevel)
    {
        UserZoom = cMinZoomLevel;
    }
    zoom = UserZoom;
    ZoomValue = UserZoom;
};
boolean argparsers_parseParameter(string255 cmd,string255 arg,LongInt (*paramIndex))
{
    boolean parseparameter_result;
    typedef string255 reallyAll_tt[(37 + 1)];
    reallyAll_tt reallyAll = {STRINIT("--prefix"),
                              STRINIT("--user-prefix"),
                              STRINIT("--locale"),
                              STRINIT("--fullscreen-width"),
                              STRINIT("--fullscreen-height"),
                              STRINIT("--width"),
                              STRINIT("--height"),
                              STRINIT("--maximized"),
                              STRINIT("--frame-interval"),
                              STRINIT("--volume"),
                              STRINIT("--nomusic"),
                              STRINIT("--nosound"),
                              STRINIT("--nodampen"),
                              STRINIT("--fullscreen"),
                              STRINIT("--showfps"),
                              STRINIT("--altdmg"),
                              STRINIT("--low-quality"),
                              STRINIT("--raw-quality"),
                              STRINIT("--stereo"),
                              STRINIT("--nick"),
                              STRINIT("--zoom"),
                              STRINIT("--internal"),
                              STRINIT("--port"),
                              STRINIT("--recorder"),
                              STRINIT("--landpreview"),
                              STRINIT("--stats-only"),
                              STRINIT("--gci"),
                              STRINIT("--help"),
                              STRINIT("--protocol"),
                              STRINIT("--no-teamtag"),
                              STRINIT("--no-hogtag"),
                              STRINIT("--no-healthtag"),
                              STRINIT("--translucent-tags"),
                              STRINIT("--lua-test"),
                              STRINIT("--no-holiday-silliness"),
                              STRINIT("--chat-size"),
                              STRINIT("--prefix64"),
                              STRINIT("--user-prefix64")};
    Byte cmdIndex;
    parseparameter_result = false;
    cmdIndex = 0;
    while((cmdIndex <= 37) && (_strncompare(cmd, reallyAll[cmdIndex])))
    {
        ++cmdIndex;
    }
    switch(cmdIndex)
    {case 0:PathPrefix = fpcrtl_str2astr(argparsers_getstringParameter(arg, &((*paramIndex)), &(parseparameter_result)));
            break;
     case 1:UserPathPrefix = fpcrtl_str2astr(argparsers_getstringParameter(arg, &((*paramIndex)), &(parseparameter_result)));
            break;
     case 2:cLanguageFName = argparsers_getstringParameter(arg, &((*paramIndex)), &(parseparameter_result));
            break;
     case 3:cFullscreenWidth = uutils_Max(argparsers_getLongIntParameter(arg, &((*paramIndex)), &(parseparameter_result)), cMinScreenWidth);
            break;
     case 4:cFullscreenHeight = uutils_Max(argparsers_getLongIntParameter(arg, &((*paramIndex)), &(parseparameter_result)), cMinScreenHeight);
            break;
     case 5:cWindowedWidth = uutils_Max(2 * (argparsers_getLongIntParameter(arg, &((*paramIndex)), &(parseparameter_result)) / 2), cMinScreenWidth);
            break;
     case 6:cWindowedHeight = uutils_Max(2 * (argparsers_getLongIntParameter(arg, &((*paramIndex)), &(parseparameter_result)) / 2), cMinScreenHeight);
            break;
     case 7:cWindowedMaximized = true;
            break;
     case 8:cTimerInterval = argparsers_getLongIntParameter(arg, &((*paramIndex)), &(parseparameter_result));
            break;
     case 9:usound_SetVolume(uutils_Max(argparsers_getLongIntParameter(arg, &((*paramIndex)), &(parseparameter_result)), 0));
            break;
     case 10:usound_SetMusic(false);
             break;
     case 11:usound_SetSound(false);
             break;
     case 12:usound_SetAudioDampen(false);
             break;
     case 13:cFullScreen = true;
             break;
     case 14:cShowFPS = true;
             break;
     case 15:cAltDamage = true;
             break;
     case 16:cReducedQuality = 0xffffffff ^ rqLowRes;
             break;
     case 17:cReducedQuality = argparsers_getLongIntParameter(arg, &((*paramIndex)), &(parseparameter_result));
             break;
     case 18:argparsers_setStereoMode(argparsers_getLongIntParameter(arg, &((*paramIndex)), &(parseparameter_result)));
             break;
     case 19:UserNick = argparsers_parseNick(argparsers_getstringParameter(arg, &((*paramIndex)), &(parseparameter_result)));
             break;
     case 20:argparsers_setZoom(arg, &((*paramIndex)), &(parseparameter_result));
             break;
     case 21:isInternal = true;
             break;
     case 22:argparsers_setIpcPort(argparsers_getLongIntParameter(arg, &((*paramIndex)), &(parseparameter_result)), &(parseparameter_result));
             break;
     case 23:argparsers_startVideoRecording(&((*paramIndex)));
             break;
     case 24:GameType = gmtLandPreview;
             break;
     case 25:argparsers_statsOnlyGame();
             break;
     case 26:argparsers_GciEasterEgg();
             break;
     case 27:argparsers_DisplayUsage();
             break;
     case 28:argparsers_DisplayProtocol();
             break;
     case 29:cTagsMask = cTagsMask & ~htTeamName;
             break;
     case 30:cTagsMask = cTagsMask & ~htName;
             break;
     case 31:cTagsMask = cTagsMask & ~htHealth;
             break;
     case 32:cTagsMask = cTagsMask | htTransparent;
             break;
     case 33:{
                 cTestLua = true;
                 usound_SetSound(false);
                 cScriptName = argparsers_getstringParameter(arg, &((*paramIndex)), &(parseparameter_result));
                 fpcrtl_writeLn(stdout, _strconcat(__str54, cScriptName));
             }
             break;
     case 34:cHolidaySilliness = false;
             break;
     case 35:cDefaultChatScale = (1.0 * argparsers_getLongIntParameter(arg, &((*paramIndex)), &(parseparameter_result))) /(float) 100;
             break;
     case 36:PathPrefix = fpcrtl_str2astr(uutils_DecodeBase64(argparsers_getstringParameter(arg, &((*paramIndex)), &(parseparameter_result))));
             break;
     case 37:UserPathPrefix = fpcrtl_str2astr(uutils_DecodeBase64(argparsers_getstringParameter(arg, &((*paramIndex)), &(parseparameter_result))));
             break;
     default: {
                  if((_strcompare(recordFileName, __str13)) && (_strncompare(fpcrtl_copy(cmd, 1, 2), __str53)))
                  {
                      recordFileName = cmd;
                  }
                  else
                  {
                      fpcrtl_writeLn(stderr, _strconcat(_strprepend(0x22, cmd), __str55));
                      parseparameter_result = true;
                  }
              }}
    return parseparameter_result;
};
void argparsers_parseCommandLine()
{
    LongInt paramIndex;
    LongInt paramTotal;
    LongInt index;
    LongInt nextIndex;
    boolean wrongParameter;
    paramIndex = 0;
    paramTotal = argparsers_ParamCount();
    wrongParameter = false;
    while(paramIndex <= paramTotal)
    {
        index = paramIndex;
        if(index == paramTotal)
        {
            nextIndex = index;
        }
        else
        {
            nextIndex = index + 1;
        }
        wrongParameter = argparsers_parseParameter(argparsers_ParamStr(index), argparsers_ParamStr(nextIndex), &(paramIndex));
        ++paramIndex;
    }
    if(wrongParameter == true)
    {
        GameType = gmtBadSyntax;
    }
};
void argparsers_GetParams()
{
    isInternal = _strcompare(argparsers_ParamStr(1), __str56);
    helpCommandUsed = false;
    UserPathPrefix = fpcrtl_str2astr(__str57);
    PathPrefix = fpcrtl_str2astr(cDefaultPathPrefix);
    recordFileName = __str13;
    argparsers_parseCommandLine();
    if(isInternal && (argparsers_ParamCount() <= 1))
    {
        fpcrtl_writeLn(stderr, __str58);
        GameType = gmtBadSyntax;
    }
    if(!helpCommandUsed)
    {
        if((!cTestLua && !isInternal) && (_strcompare(recordFileName, __str13)))
        {
            fpcrtl_writeLn(stderr, __str59);
            GameType = gmtBadSyntax;
        }
        else
        {
            if(_strncompare(recordFileName, __str13))
            {
                fpcrtl_writeLn(stdout, _strconcat(_strconcat(__str60, recordFileName), __str61));
            }
        }
    }
    if(GameType == gmtBadSyntax)
    {
        fpcrtl_writeLn(stderr, __str62);
    }
};
