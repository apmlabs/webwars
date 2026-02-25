#include "fpcrtl.h"

#include "uGame.h"
#include "uInputHandler.h"
#include "uTeams.h"
#include "uIO.h"
#include "uAI.h"
#include "uGears.h"
#include "uSound.h"
#include "uLocale.h"
#include "uCaptions.h"
#include "uTypes.h"
#include "uVariables.h"
#include "uCommands.h"
#include "uConsts.h"
#include "uVisualGearsList.h"
#include "uUtils.h"
#include "uDebug.h"
static const string255 __str0 = STRINIT("End of input, halting now");
void ugame_DoGameTick(LongInt Lag)
{
    enum{maxCheckedGameDuration = (((3 * 60) * 60) * 1000)};
    LongInt i;
    LongInt j;
    astring s;
    SoundTimerTicks += Lag;
    if(SoundTimerTicks >= 50)
    {
        SoundTimerTicks = 0;
        if(cVolumeDelta != 0)
        {
            j = Volume;
            i = usound_ChangeVolume(cVolumeDelta);
            if(!cIsSoundEnabled || (isAudioMuted && (j != i)))
            {
                ucaptions_AddCaption(trmsg[sidMute], capcolSetting, capgrpVolume);
            }
            else
            {
                if(!isAudioMuted)
                {
                    s = fpcrtl_str2astr(uutils_IntToStr(i));
                    ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidVolume], s), capcolSetting, capgrpVolume);
                }
            }
        }
        else
        {
            if(cMuteToggle)
            {
                usound_MuteAudio();
                if(isAudioMuted)
                {
                    ucaptions_AddCaption(trmsg[sidMute], capcolSetting, capgrpVolume);
                }
                else
                {
                    s = fpcrtl_str2astr(uutils_IntToStr(usound_GetVolumePercent()));
                    ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidVolume], s), capcolSetting, capgrpVolume);
                }
                cMuteToggle = false;
            }
        }
    }
    if(isPaused)
    {
        return;
    }
    if(!CurrentTeam->ExtDriven)
    {
        uio_NetGetNextCmd();
        if(!allOK)
        {
            return;
        }
        isInLag = false;
        uio_FlushMessages(Lag);
    }
    if(GameType != gmtRecord)
    {
        if(Lag > 100)
        {
            Lag = 100;
        }
        else
        {
            if(((GameType == gmtSave) || (fastUntilLag && (GameType == gmtNet))) || fastForward)
            {
                Lag = 2500;
            }
        }
        if(GameType == gmtDemo)
        {
            if(isSpeed)
            {
                i = ((int64_t) (RealTicks)) - ((int64_t) (SpeedStart));
                if(i < 2000)
                {
                    Lag = Lag * 5;
                }
                else
                {
                    if(i < 4000)
                    {
                        Lag = Lag * 10;
                    }
                    else
                    {
                        if(i < 6000)
                        {
                            Lag = Lag * 20;
                        }
                        else
                        {
                            if(i < 8000)
                            {
                                Lag = Lag * 40;
                            }
                            else
                            {
                                Lag = Lag * 80;
                            }
                        }
                    }
                }
            }
            else
            {
                if(cOnlyStats)
                {
                    if(GameTicks >= maxCheckedGameDuration)
                    {
                        GameState = gsExit;
                        return;
                    }
                    Lag = maxCheckedGameDuration + 60000;
                }
            }
        }
    }
    if(cTestLua)
    {
        Lag = 2147483647;
    }
    usound_PlayNextVoice();
    i = 1;
    while(((GameState != gsExit) && (i <= Lag)) && allOK)
    {
        if(!CurrentTeam->ExtDriven)
        {
            if(CurrentHedgehog->BotLevel != 0)
            {
                uai_ProcessBot();
            }
            ugears_ProcessGears();
        }
        else
        {
            uio_NetGetNextCmd();
            if(!allOK)
            {
                return;
            }
            if(isInLag)
            {
                switch(GameType)
                {case gmtNet:{
                                 uvisualgearslist_AddVisualGear_3(0, 0, vgtTeamHealthSorter);
                                 uvisualgearslist_AddVisualGear_3(0, 0, vgtSmoothWindBar);
                                 break;
                             }
                             break;
                 case gmtDemo:
                 case gmtRecord:{
                                    uutils_AddFileLog(__str0);
                                    GameState = gsExit;
                                    return;
                                }
                                break;
                 case gmtSave:{
                                  uteams_RestoreTeamsFromSave();
                                  uinputhandler_SetBinds(&(CurrentTeam->Binds));
                                  ucommands_StopMessages(((gmLeft | gmRight) | gmUp) | gmDown);
                                  usound_ResetSound();
                                  usound_PlayMusic();
                                  GameType = gmtLocal;
                                  uvisualgearslist_AddVisualGear_3(0, 0, vgtTeamHealthSorter);
                                  uvisualgearslist_AddVisualGear_3(0, 0, vgtSmoothWindBar);
                              }
                              break;
                 default: break;}
            }
            else
            {
                ugears_ProcessGears();
            }
        }
        ++i;
    }
};
