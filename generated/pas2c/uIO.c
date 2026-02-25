#include "fpcrtl.h"

#include "uIO.h"
#include "uConsole.h"
#include "uConsts.h"
#include "uVariables.h"
#include "uCommands.h"
#include "uUtils.h"
#include "uDebug.h"
#include "uLocale.h"
#include "uSound.h"
static const string255 __str53 = STRINIT("fatal");
static const string255 __str52 = STRINIT("Got /put while not being in choose target mode");
static const string255 __str51 = STRINIT(", ");
static const string255 __str50 = STRINIT("put: ");
static const string255 __str49 = STRINIT("spectate 0");
static const string255 __str48 = STRINIT(" > ");
static const string255 __str47 = STRINIT(" (");
static const string255 __str46 = STRINIT("oops, queue error. in buffer: ");
static const string255 __str45 = STRINIT("Unexpected protocol command: ");
static const string255 __str44 = STRINIT("slot ");
static const string255 __str43 = STRINIT("timer ");
static const string255 __str42 = STRINIT("hogsay ");
static const string255 __str41 = STRINIT("taunt ");
static const string255 __str40 = STRINIT("setweap ");
static const string255 __str39 = STRINIT("got cmd \"N\": time ");
static const string255 __str38 = STRINIT("teamback s");
static const string255 __str37 = STRINIT("teamgone s");
static const string255 __str36 = STRINIT("teamback u");
static const string255 __str35 = STRINIT("teamgone u");
static const string255 __str34 = STRINIT("gencmd ");
static const string255 __str33 = STRINIT("skip");
static const string255 __str32 = STRINIT("hjump");
static const string255 __str31 = STRINIT("ljump");
static const string255 __str30 = STRINIT("switch");
static const string255 __str29 = STRINIT("-attack");
static const string255 __str28 = STRINIT("+attack");
static const string255 __str27 = STRINIT("-precise");
static const string255 __str26 = STRINIT("+precise");
static const string255 __str25 = STRINIT("-down");
static const string255 __str24 = STRINIT("+down");
static const string255 __str23 = STRINIT("-up");
static const string255 __str22 = STRINIT("+up");
static const string255 __str21 = STRINIT("-right");
static const string255 __str20 = STRINIT("+right");
static const string255 __str19 = STRINIT("-left");
static const string255 __str18 = STRINIT("+left");
static const string255 __str17 = STRINIT("hiTicks increment by remote message");
static const string255 __str16 = STRINIT("+");
static const string255 __str15 = STRINIT("?");
static const string255 __str14 = STRINIT("[IPC out] ");
static const string255 __str13 = STRINIT("Error opening file ");
static const string255 __str12 = STRINIT(" ticks ");
static const string255 __str11 = STRINIT("[IPC in] ");
static const string255 __str10 = STRINIT("");
static const string255 __str9 = STRINIT("chatmsg ");
static const string255 __str8 = STRINIT("pause server");
static const string255 __str7 = STRINIT("missvar ");
static const string255 __str6 = STRINIT("campvar ");
static const string255 __str5 = STRINIT(" IPC \"T\" :");
static const string255 __str4 = STRINIT("forcequit");
static const string255 __str3 = STRINIT("landcheck ");
static const string255 __str2 = STRINIT("!");
static const string255 __str1 = STRINIT("Ping? Pong!");
static const string255 __str0 = STRINIT("Init browser IPC... ");
LongInt hw_ipc_recv(pointer buf,LongInt maxlen);
enum{cSendEmptyPacketTime = 1000};
enum{cSendBufferSize = 1024};
typedef struct __TCmd * PCmd;
typedef struct __TCmd {
            PCmd Next;
            Word loTime;
            union
            {struct
             {Byte len;
              char cmd;};
             struct
             {string255 str;};};
        } TCmd;
static PTCPSocket IPCSock;
static PSDLNet_SocketSet fds;
static boolean isPonged;
static string255 SocketString;
static PCmd headcmd;
static PCmd lastcmd;
static LongWord flushDelayTicks;
typedef struct __sendBuffer_tt {
            Byte buf[cSendBufferSize];
            Word count;
        } sendBuffer_tt;
static sendBuffer_tt sendBuffer;
PCmd uio_AddCmd(Word Time,string255 str)
{
    PCmd addcmd_result;
    PCmd command;
    if(((((((lastcmd != NULL) && (lastcmd->cmd == 0x2b)) && (str.s[1] != 0x46)) && (str.s[1] != 0x47)) && (str.s[1] != 0x73)) && (str.s[1] != 0x68)) && (str.s[1] != 0x62))
    {
        command = lastcmd;
    }
    else
    {
        fpcrtl_new(command);
        if(headcmd == NULL)
        {
            headcmd = command;
            lastcmd = command;
        }
        else
        {
            lastcmd->Next = command;
            lastcmd = command;
        }
    }
    fpcrtl_FillChar((*command), sizeof(TCmd), 0);
    command->loTime = Time;
    command->str = str;
    if((command->cmd != 0x46) && (command->cmd != 0x47))
    {
        command->len -= 2;
    }
    addcmd_result = command;
    return addcmd_result;
};
void uio_RemoveCmd()
{
    PCmd tmp;
    tmp = headcmd;
    headcmd = headcmd->Next;
    if(headcmd == NULL)
    {
        lastcmd = NULL;
    }
    fpcrtl_dispose(tmp);
};
void uio_InitIPC()
{
    uconsole_WriteToConsole(__str0);
    IPCSock = ((PTCPSocket)1);
    uconsole_WriteLnToConsole(msgOK);
};
void uio_ParseChatCommand(string255 command,string255 message,Byte messageStartIndex)
{
    string255 text;
    text = fpcrtl_copy(message, messageStartIndex, (fpcrtl_Length(message) - messageStartIndex) + 1);
    ucommands_ParseCommand_2(_strconcat(command, text), true);
    uconsole_WriteLnToConsole(text);
};
void uio_ParseIPCCommand(string255 s)
{
    Word loTicks;
    boolean isProcessed;
    string255 nick;
    string255 msg;
    LongInt i;
    string255 unwrapped;
    isProcessed = true;
    switch(s.s[1])
    {case '!':{
                  uutils_AddFileLog(__str1);
                  isPonged = true;
              }
              break;
     case '?':uio_SendIPC(__str2);
              break;
     case 'e':{
                  unwrapped = fpcrtl_copy(s, 2, fpcrtl_Length(s) - 1);
                  ucommands_ParseCommand_2(unwrapped, true);
              }
              break;
     case 'E':udebug_OutError(fpcrtl_copy(s, 2, fpcrtl_Length(s) - 1), true);
              break;
     case 'W':udebug_OutError(fpcrtl_copy(s, 2, fpcrtl_Length(s) - 1), false);
              break;
     case 'M':ucommands_ParseCommand_2(_strconcat(__str3, s), true);
              break;
     case 'o':if(fastUntilLag)
              {
                  ucommands_ParseCommand_2(__str4, true);
              }
              break;
     case 'T':switch(s.s[2])
              {case 'L':GameType = gmtLocal;
                        break;
               case 'D':GameType = gmtDemo;
                        break;
               case 'N':GameType = gmtNet;
                        break;
               case 'S':GameType = gmtSave;
                        break;
               case 'V':GameType = gmtRecord;
                        break;
               default: udebug_OutError(_strappend(_strconcat(errmsgIncorrectUse, __str5), s.s[2]), true);}
              break;
     case 'V':{
                  if(s.s[2] == 0x2e)
                  {
                      ucommands_ParseCommand_2(_strconcat(__str6, fpcrtl_copy(s, 3, fpcrtl_Length(s) - 2)), true);
                  }
              }
              break;
     case 'v':{
                  if(s.s[2] == 0x2e)
                  {
                      ucommands_ParseCommand_2(_strconcat(__str7, fpcrtl_copy(s, 3, fpcrtl_Length(s) - 2)), true);
                  }
              }
              break;
     case 'I':ucommands_ParseCommand_2(__str8, true);
              break;
     case 's':if(GameType == gmtNet)
              {
                  uio_ParseChatCommand(__str9, s, 2);
              }
              else
              {
                  isProcessed = false;
              }
              break;
     case 'b':if(GameType == gmtNet)
              {
                  i = 2;
                  nick = __str10;
                  while((i <= fpcrtl_Length(s)) && (s.s[i] != 0x5d))
                  {
                      nick = _strappend(nick, s.s[i]);
                      ++i;
                  }
                  ++i;
                  msg = __str10;
                  while(i <= fpcrtl_Length(s))
                  {
                      msg = _strappend(msg, s.s[i]);
                      ++i;
                  }
                  s = _strprepend(0x62, ulocale_Format_3(fpcrtl_astr2str(trmsg[sidChatTeam]), nick, msg));
                  if((_strcompare(nick, __str10)) || (_strcompare(msg, __str10)))
                  {
                      isProcessed = false;
                  }
                  else
                  {
                      uio_ParseChatCommand(_strappend(__str9, 0x4), s, 2);
                  }
              }
              else
              {
                  isProcessed = false;
              }
              break;
     default: isProcessed = false;}
    if(!isProcessed)
    {
        loTicks = sdlh_SDLNet_Read16(&(s.s[((Byte)s.s[0]) - 1]));
        uio_AddCmd(loTicks, s);
        uutils_AddFileLog(_strconcat(_strconcat(_strconcat(__str11, uutils_sanitizeCharForLog(s.s[1])), __str12), uutils_IntToStr(lastcmd->loTime)));
    }
};
void uio_IPCCheckSock()
{
    LongInt i;
    string255 s;
    LongInt totalRead;
    totalRead = 0;
    do {
           i = hw_ipc_recv(&(s.s[1]), 255 - fpcrtl_Length(SocketString));
           if(i > 0)
           {
               s.s[0] = ((char)i);
               SocketString = _strconcat(SocketString, s);
               totalRead = totalRead + i;
               while((fpcrtl_Length(SocketString) > 1) && (fpcrtl_Length(SocketString) > ((Byte)SocketString.s[1])))
               {
                   uio_ParseIPCCommand(fpcrtl_copy(SocketString, 2, ((Byte)SocketString.s[1])));
                   fpcrtl_Delete(SocketString, 1, (((Byte)SocketString.s[1]) + 1));
               }
           }
       } while(!((i <= 0) || (totalRead >= 8192)));
};
void uio_LoadRecordFromFile(string255 fileName)
{
    File f;
    string255 ss = STRINIT("");
    LongInt i;
    string255 s;
    FileMode = 0;
    fpcrtl_assign(f, fileName);
    fpcrtl_reset(f, 1);
    if(udebug_checkFails(IOResult == 0, _strconcat(__str13, fileName), true))
    {
        return;
    }
    i = 0;
    s.s[0] = 0x0;
    do {
           fpcrtl_BlockRead(f, s.s[1], 255 - fpcrtl_Length(ss), i);
           if(i > 0)
           {
               s.s[0] = ((char)i);
               ss = _strconcat(ss, s);
               while(((fpcrtl_Length(ss) > 1) && (fpcrtl_Length(ss) > ((Byte)ss.s[1]))) && allOK)
               {
                   uio_ParseIPCCommand(fpcrtl_copy(ss, 2, ((Byte)ss.s[1])));
                   fpcrtl_Delete(ss, 1, (((Byte)ss.s[1]) + 1));
               }
           }
       } while(!((i == 0) || !allOK));
    fpcrtl_close(f);
};
void uio_SendStat(TStatInfoType sit,string255 s)
{
    typedef char stc_tt[15];
    stc_tt stc = {'r',
                  'D',
                  'k',
                  'K',
                  'H',
                  'T',
                  'P',
                  's',
                  'S',
                  'B',
                  'c',
                  'g',
                  'p',
                  'R',
                  'h'};
    string255 buf;
    buf = _strconcat(_chrconcat(0x69, stc[sit]), s);
    uio_SendIPCRaw(&(buf.s[0]), fpcrtl_Length(buf) + 1);
};
boolean uio_isSyncedCommand(char c)
{
    boolean issyncedcommand_result;
    switch(c)
    {case '+':
     case '#':
     case 'L':
     case 'l':
     case 'R':
     case 'r':
     case 'U':
     case 'u':
     case 'D':
     case 'd':
     case 'Z':
     case 'z':
     case 'A':
     case 'a':
     case 'S':
     case 'j':
     case 'J':
     case ',':
     case 'c':
     case 'N':
     case 'p':
     case 'P':
     case 'w':
     case 't':
     case '1':
     case '2':
     case '3':
     case '4':
     case '5':
     case 'f':
     case 'g':issyncedcommand_result = true;
              break;
     default: issyncedcommand_result = (((Byte)c) >= 128) && (((Byte)c) <= (128 + cMaxSlotIndex));}
    return issyncedcommand_result;
};
void uio_flushBuffer()
{
    if(IPCSock != NULL)
    {
        SDLNet_TCP_Send(IPCSock, &(sendBuffer.buf), sendBuffer.count);
        flushDelayTicks = 0;
        sendBuffer.count = 0;
    }
};
void uio_SendIPC(string255 s)
{
    if(IPCSock != NULL)
    {
        if(s.s[0] > 0xfb)
        {
            s.s[0] = 0xfb;
        }
        sdlh_SDLNet_Write16(GameTicks, &(s.s[(((Byte)s.s[0]) + 1)]));
        uutils_AddFileLog(_strconcat(__str14, uutils_sanitizeCharForLog(s.s[1])));
        s.s[0] += 2;
        if(uio_isSyncedCommand(s.s[1]))
        {
            if((sendBuffer.count + ((Byte)s.s[0])) >= cSendBufferSize)
            {
                uio_flushBuffer();
            }
            fpcrtl_Move(s, sendBuffer.buf[sendBuffer.count], ((Byte)s.s[0]) + 1);
            sendBuffer.count += ((Byte)s.s[0]) + 1;
            if((s.s[1] == 0x4e) || (s.s[1] == 0x23))
            {
                uio_flushBuffer();
            }
        }
        else
        {
            SDLNet_TCP_Send(IPCSock, &(s), (((Byte)s.s[0]) + 1));
        }
    }
};
void uio_SendIPCRaw(pointer p,LongWord len)
{
    if(IPCSock != NULL)
    {
        SDLNet_TCP_Send(IPCSock, p, len);
    }
};
void uio_SendIPCXY(char cmd,LongInt X,LongInt Y)
{
    string255 s;
    s.s[0] = 0x9;
    s.s[1] = cmd;
    sdlh_SDLNet_Write32(X, &(s.s[2]));
    sdlh_SDLNet_Write32(Y, &(s.s[6]));
    uio_SendIPC(s);
};
void uio_IPCWaitPongEvent()
{
    isPonged = false;
    do {
           uio_IPCCheckSock();
       } while(!(isPonged || !allOK));
};
void uio_SendIPCAndWaitReply(string255 s)
{
    uio_SendIPC(s);
    uio_SendIPC(__str15);
    uio_IPCWaitPongEvent();
};
void uio_FlushMessages(LongWord Lag)
{
    flushDelayTicks += Lag;
    if(flushDelayTicks >= cSendEmptyPacketTime)
    {
        if(sendBuffer.count == 0)
        {
            uio_SendIPC(__str16);
        }
        uio_flushBuffer();
    }
};
void uio_NetGetNextCmd()
{
    boolean tmpflag;
    string255 s;
    LongInt x32;
    LongInt y32;
    tmpflag = true;
    while(((headcmd != NULL) && (tmpflag || (headcmd->cmd == 0x23))) && (((((((GameTicks == ((LongWord)(hiTicks << 16) + headcmd->loTime)) || (headcmd->cmd == 0x73)) || (headcmd->cmd == 0x68)) || (headcmd->cmd == 0x23)) || (headcmd->cmd == 0x62)) || (headcmd->cmd == 0x46)) || (headcmd->cmd == 0x47)))
    {
        switch(headcmd->cmd)
        {case '+':;
                  break;
         case '#':{
                      uutils_AddFileLog(__str17);
                      ++hiTicks;
                  }
                  break;
         case 'L':ucommands_ParseCommand_2(__str18, true);
                  break;
         case 'l':ucommands_ParseCommand_2(__str19, true);
                  break;
         case 'R':ucommands_ParseCommand_2(__str20, true);
                  break;
         case 'r':ucommands_ParseCommand_2(__str21, true);
                  break;
         case 'U':ucommands_ParseCommand_2(__str22, true);
                  break;
         case 'u':ucommands_ParseCommand_2(__str23, true);
                  break;
         case 'D':ucommands_ParseCommand_2(__str24, true);
                  break;
         case 'd':ucommands_ParseCommand_2(__str25, true);
                  break;
         case 'Z':ucommands_ParseCommand_2(__str26, true);
                  break;
         case 'z':ucommands_ParseCommand_2(__str27, true);
                  break;
         case 'A':ucommands_ParseCommand_2(__str28, true);
                  break;
         case 'a':ucommands_ParseCommand_2(__str29, true);
                  break;
         case 'S':ucommands_ParseCommand_2(__str30, true);
                  break;
         case 'j':ucommands_ParseCommand_2(__str31, true);
                  break;
         case 'J':ucommands_ParseCommand_2(__str32, true);
                  break;
         case ',':ucommands_ParseCommand_2(__str33, true);
                  break;
         case 'c':{
                      s = fpcrtl_copy(headcmd->str, 2, ((int)(headcmd->len) - 1));
                      ucommands_ParseCommand_2(_strconcat(__str34, s), true);
                  }
                  break;
         case 's':uio_ParseChatCommand(__str9, headcmd->str, 2);
                  break;
         case 'b':uio_ParseChatCommand(_strappend(__str9, 0x4), headcmd->str, 2);
                  break;
         case 'F':ucommands_ParseCommand_2(_strconcat(__str35, fpcrtl_copy(headcmd->str, 2, ((int)(headcmd->len) - 1))), true);
                  break;
         case 'G':ucommands_ParseCommand_2(_strconcat(__str36, fpcrtl_copy(headcmd->str, 2, ((int)(headcmd->len) - 1))), true);
                  break;
         case 'f':ucommands_ParseCommand_2(_strconcat(__str37, fpcrtl_copy(headcmd->str, 2, ((int)(headcmd->len) - 1))), true);
                  break;
         case 'g':ucommands_ParseCommand_2(_strconcat(__str38, fpcrtl_copy(headcmd->str, 2, ((int)(headcmd->len) - 1))), true);
                  break;
         case 'N':{
                      tmpflag = false;
                      lastTurnChecksum = sdlh_SDLNet_Read32(&(headcmd->str.s[2]));
                      uutils_AddFileLog(_strconcat(__str39, uutils_IntToStr((hiTicks << 16) + headcmd->loTime)));
                  }
                  break;
         case 'p':{
                      x32 = sdlh_SDLNet_Read32(&(headcmd->str.s[2]));
                      y32 = sdlh_SDLNet_Read32(&(headcmd->str.s[6]));
                      uio_doPut(x32, y32, false);
                  }
                  break;
         case 'P':{
                      if(CurrentTeam->ExtDriven)
                      {
                          TargetCursorPoint.x = ((LongInt)sdlh_SDLNet_Read32(&(headcmd->str.s[2]))) + WorldDx;
                          TargetCursorPoint.y = (cScreenHeight - ((LongInt)sdlh_SDLNet_Read32(&(headcmd->str.s[6])))) - WorldDy;
                          if(!bShowAmmoMenu && autoCameraOn)
                          {
                              CursorPoint = TargetCursorPoint;
                          }
                      }
                  }
                  break;
         case 'w':ucommands_ParseCommand_2(_strappend(__str40, headcmd->str.s[2]), true);
                  break;
         case 't':ucommands_ParseCommand_2(_strappend(__str41, headcmd->str.s[2]), true);
                  break;
         case 'h':ucommands_ParseCommand_2(_strconcat(__str42, fpcrtl_copy(headcmd->str, 2, ((int)(headcmd->len) - 1))), true);
                  break;
         case '1':
         case '2':
         case '3':
         case '4':
         case '5':ucommands_ParseCommand_2(_strappend(__str43, headcmd->cmd), true);
                  break;
         default: if((((Byte)headcmd->cmd) >= 128) && (((Byte)headcmd->cmd) <= (128 + cMaxSlotIndex)))
                  {
                      ucommands_ParseCommand_2(_strappend(__str44, ((char)((Byte)headcmd->cmd) - 79)), true);
                  }
                  else
                  {
                      udebug_OutError(_strappend(__str45, headcmd->cmd), true);
                  }}
        uio_RemoveCmd();
    }
    if((((headcmd != NULL) && tmpflag) && !CurrentTeam->hasGone) && (GameTicks < (((LongWord)hiTicks << 16) + headcmd->loTime)))
    {
        udebug_checkFails(true, _strappend(_strconcat(_strconcat(_strconcat(_strconcat(_strappend(__str46, headcmd->cmd), __str47), uutils_IntToStr(GameTicks)), __str48), uutils_IntToStr((hiTicks << 16) + headcmd->loTime)), 0x29), true);
    }
    isInLag = ((headcmd == NULL) && tmpflag) && !CurrentTeam->hasGone;
    if(isInLag && fastUntilLag)
    {
        ucommands_ParseCommand_2(__str49, true);
        fastUntilLag = false;
    }
};
void uio_chFatalError(string255 (*s))
{
    uio_SendIPC(_strprepend(0x45, (*s)));
    SDL_Quit();
    if(IPCSock != NULL)
    {
        fpcrtl_halt(HaltFatalError);
    }
    else
    {
        fpcrtl_halt(HaltFatalErrorNoIPC);
    }
};
void uio_doPut(LongInt putX,LongInt putY,boolean fromAI)
{
    if(uutils_CheckNoTeamOrHH() || isPaused)
    {
        return;
    }
    bShowFinger = false;
    if(!CurrentTeam->ExtDriven && bShowAmmoMenu)
    {
        bSelected = true;
        return;
    }
    {
        {
            if(((*CurrentHedgehog->Gear).State & gstChooseTarget) != 0)
            {
                if((((Ammoz[(*CurrentHedgehog).CurAmmoType].Ammo.Propz & ammoprop_AttackInMove) != 0) || (((*CurrentHedgehog->Gear).State & gstMoving) == 0)) || ((Ammoz[(*CurrentHedgehog).CurAmmoType].Ammo.Propz & ammoprop_AttackingPut) == 0))
                {
                    if((Ammoz[(*CurrentHedgehog).CurAmmoType].Ammo.Propz & ammoprop_NoTargetAfter) != 0)
                    {
                        isCursorVisible = false;
                    }
                    if(!CurrentTeam->ExtDriven)
                    {
                        if(fromAI)
                        {
                            TargetPoint.x = putX;
                            TargetPoint.y = putY;
                        }
                        else
                        {
                            TargetPoint.x = CursorPoint.x - WorldDx;
                            TargetPoint.y = (cScreenHeight - CursorPoint.y) - WorldDy;
                        }
                        if((WorldEdge != weBounce) && ((Ammoz[(*CurrentHedgehog).CurAmmoType].Ammo.Propz & ammoprop_NoWrapTarget) == 0))
                        {
                            TargetPoint.x = uutils_CalcWorldWrap(TargetPoint.x, 0);
                        }
                        uio_SendIPCXY(0x70, TargetPoint.x, TargetPoint.y);
                    }
                    else
                    {
                        if((Ammoz[(*CurrentHedgehog).CurAmmoType].Ammo.Propz & ammoprop_NoWrapTarget) == 0)
                        {
                            TargetPoint.x = uutils_CalcWorldWrap(TargetPoint.x, 0);
                        }
                        TargetPoint.x = putX;
                        TargetPoint.y = putY;
                    }
                    uutils_AddFileLog(_strconcat(_strconcat(_strconcat(__str50, uutils_IntToStr(TargetPoint.x)), __str51), uutils_IntToStr(TargetPoint.y)));
                    (*CurrentHedgehog->Gear).State = (*CurrentHedgehog->Gear).State & ~gstChooseTarget;
                    if((Ammoz[(*CurrentHedgehog).CurAmmoType].Ammo.Propz & ammoprop_AttackingPut) != 0)
                    {
                        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmAttack & InputMask);
                    }
                    (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message & ~(((((gmHJump | gmLJump) | gmLeft) | gmRight) | gmUp) | gmDown);
                }
                else
                {
                    usound_PlaySound_1(sndDenied);
                }
            }
            else
            {
                if(CurrentTeam->ExtDriven)
                {
                    udebug_OutError(__str52, false);
                }
            }
        }
    }
};
void uio_initModule()
{
    ucommands_RegisterVariable_3(__str53, &(uio_chFatalError), true);
    IPCSock = NULL;
    fds = NULL;
    headcmd = NULL;
    lastcmd = NULL;
    isPonged = false;
    SocketString = __str10;
    hiTicks = 0;
    flushDelayTicks = 0;
    sendBuffer.count = 0;
};
void uio_freeModule()
{
    while(headcmd != NULL)
    {
        uio_RemoveCmd();
    }
    SDLNet_FreeSocketSet(fds);
    SDLNet_TCP_Close(IPCSock);
    SDLNet_Quit();
};
