#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uConsts.h"
#include "uTypes.h"
void usound_preInitModule();
void usound_initModule();
void usound_freeModule();
void usound_InitSound();
void usound_ReleaseSound(boolean complete);
void usound_ResetSound();
void usound_SetSound(boolean enabled);
void usound_SetAudioDampen(boolean enabled);
void usound_SetMusic(boolean enabled);
void usound_SetMusicName(string255 musicname);
void usound_PlayMusic();
void usound_PauseMusic();
void usound_ResumeMusic();
void usound_ChangeMusic(string255 musicname);
void usound_StopMusic();
boolean usound_PlaySound_1(TSound snd);
boolean usound_PlaySound_2(TSound snd,boolean keepPlaying);
boolean usound_PlaySound_3(TSound snd,boolean keepPlaying,boolean ignoreMask);
boolean usound_PlaySound_4(TSound snd,boolean keepPlaying,boolean ignoreMask,boolean soundAsMusic);
boolean usound_PlaySoundV_2(TSound snd,PVoicepack voicepack);
boolean usound_PlaySoundV_3(TSound snd,PVoicepack voicepack,boolean keepPlaying);
boolean usound_PlaySoundV_4(TSound snd,PVoicepack voicepack,boolean keepPlaying,boolean ignoreMask);
boolean usound_PlaySoundV_5(TSound snd,PVoicepack voicepack,boolean keepPlaying,boolean ignoreMask,boolean soundAsMusic);
void usound_PlayMusicSound(TSound snd);
void usound_StopMusicSound(TSound snd);
LongInt usound_LoopSound_1(TSound snd);
LongInt usound_LoopSound_2(TSound snd,LongInt fadems);
LongInt usound_LoopSoundV_2(TSound snd,PVoicepack voicepack);
LongInt usound_LoopSoundV_3(TSound snd,PVoicepack voicepack,LongInt fadems);
void usound_StopSound_1(TSound snd);
void usound_StopSound_2(TSound snd,boolean soundAsMusic);
void usound_StopSoundChan_1(LongInt chn);
void usound_StopSoundChan_2(LongInt chn,LongInt fadems);
void usound_AddVoice_2(TSound snd,PVoicepack voicepack);
void usound_AddVoice_4(TSound snd,PVoicepack voicepack,boolean ignoreMask,boolean isFallback);
void usound_PlayNextVoice();
void usound_DampenAudio();
void usound_UndampenAudio();
void usound_MuteAudio();
void usound_SetVolume(LongInt vol);
LongInt usound_ChangeVolume(LongInt voldelta);
LongInt usound_GetVolumePercent();
pointer usound_AskForVoicepack(string255 name);
extern string255 MusicFN;
extern string255 SDMusicFN;
extern string255 FallbackMusicFN;
extern string255 FallbackSDMusicFN;
extern LongInt Volume;
extern LongWord SoundTimerTicks;
extern boolean LastVoiceFailed;

