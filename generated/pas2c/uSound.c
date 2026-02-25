#include "fpcrtl.h"

#include "uSound.h"
string255 MusicFN;
string255 SDMusicFN;
string255 FallbackMusicFN;
string255 FallbackSDMusicFN;
LongInt Volume;
LongWord SoundTimerTicks;
boolean LastVoiceFailed;
#include "uVariables.h"
#include "uConsole.h"
#include "uCommands.h"
#include "uDebug.h"
#include "uPhysFSLayer.h"
static const string255 __str18 = STRINIT("sdmusic.ogg");
static const string255 __str17 = STRINIT("voicepack");
static const string255 __str16 = STRINIT(" \"/voicepack\"");
static const string255 __str15 = STRINIT("Mix_FadeInMusic");
static const string255 __str14 = STRINIT("No fallback music configured!");
static const string255 __str13 = STRINIT("Music not found. Trying fallback music.");
static const string255 __str12 = STRINIT("Mix_LoadMUS_RW");
static const string255 __str11 = STRINIT("/Music/");
static const string255 __str10 = STRINIT("Mix_LoadWAV_RW");
static const string255 __str9 = STRINIT(" ... ");
static const string255 __str8 = STRINIT("Mix_Init");
static const string255 __str7 = STRINIT("Cannot init OPUS: ");
static const string255 __str6 = STRINIT("Init SDL_mixer... ");
static const string255 __str5 = STRINIT("Open audio...");
static const string255 __str4 = STRINIT("Init sound...");
static const string255 __str3 = STRINIT("");
static const string255 __str2 = STRINIT("Default_qau");
static const string255 __str1 = STRINIT("en");
static const string255 __str0 = STRINIT("_qau");
enum{chanTPU = 32};
static LongInt cInitVolume;
static LongInt previousVolume;
typedef LongInt lastChan_tt[175];
static lastChan_tt lastChan;
typedef TVoicepack voicepacks_tt[(cMaxTeams + 1)];
static voicepacks_tt voicepacks;
static PVoicepack defVoicepack;
static PMixMusic Mus;
static boolean isMusicEnabled;
static boolean isSoundEnabled;
static boolean isAutoDampening;
static boolean isSEBackup;
typedef TVoice VoiceList_tt[(7 + 1)];
static VoiceList_tt VoiceList = {{
                                     .snd = sndNone,
                                     .voicepack = NULL,
                                     .isFallback = false
                                 },
                                 {
                                     .snd = sndNone,
                                     .voicepack = NULL,
                                     .isFallback = false
                                 },
                                 {
                                     .snd = sndNone,
                                     .voicepack = NULL,
                                     .isFallback = false
                                 },
                                 {
                                     .snd = sndNone,
                                     .voicepack = NULL,
                                     .isFallback = false
                                 },
                                 {
                                     .snd = sndNone,
                                     .voicepack = NULL,
                                     .isFallback = false
                                 },
                                 {
                                     .snd = sndNone,
                                     .voicepack = NULL,
                                     .isFallback = false
                                 },
                                 {
                                     .snd = sndNone,
                                     .voicepack = NULL,
                                     .isFallback = false
                                 },
                                 {
                                     .snd = sndNone,
                                     .voicepack = NULL,
                                     .isFallback = false
                                 }};
typedef struct __Soundz_tt {
            string255 FileName;
            TPathType Path;
            TPathType AltPath;
        } Soundz_tt[175];
static Soundz_tt Soundz = {{
                               .FileName = STRINIT(""),
                               .Path = ptNone,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("grenadeimpact.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("explosion.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("throwpowerup.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("throwrelease.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("splash.ogg"),
                               .Path = ptCurrTheme,
                               .AltPath = ptSounds
                           },
                           {
                               .FileName = STRINIT("shotgunreload.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("shotgunfire.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("graveimpact.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("mineimpact.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("minetick.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Droplet1.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("pickhammer.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("gun.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("bee.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Jump1.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Jump2.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Jump3.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Yessir.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Laugh.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Illgetyou.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Justyouwait.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Incoming.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Missed.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Stupid.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Firstblood.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Boring.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Byebye.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Sameteam.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Nutter.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Reinforcements.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Traitor.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Youllregretthat.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Enemydown.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Coward.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Hurry.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Watchit.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Kamikaze.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("cake2.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Ow1.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Ow2.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Ow3.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Ow4.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Firepunch1.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Firepunch2.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Firepunch3.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Firepunch4.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Firepunch5.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Firepunch6.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Melon.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Hellish.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Yoohoo.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("rcplane.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("whipcrack.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("ride_of_the_valkyries.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("denied.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("placed.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("baseballbat.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("steam.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("warp.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("suddendeath.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("mortar.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("shutterclick.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("homerun.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("molotov.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Takecover.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Uh-oh.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Oops.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Nooo.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Hello.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("ropeshot.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("ropeattach.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("roperelease.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("switchhog.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Victory.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Flawless.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("sniperreload.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("steps.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("lowgravity.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("hell_growl.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("hell_ooff.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("hell_ow.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("hell_ugh.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("melonimpact.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Droplet1.ogg"),
                               .Path = ptCurrTheme,
                               .AltPath = ptSounds
                           },
                           {
                               .FileName = STRINIT("Droplet2.ogg"),
                               .Path = ptCurrTheme,
                               .AltPath = ptSounds
                           },
                           {
                               .FileName = STRINIT("Droplet3.ogg"),
                               .Path = ptCurrTheme,
                               .AltPath = ptSounds
                           },
                           {
                               .FileName = STRINIT("egg.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("drillgun.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("PoisonCough.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptDefaultVoice
                           },
                           {
                               .FileName = STRINIT("PoisonMoan.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptDefaultVoice
                           },
                           {
                               .FileName = STRINIT("BirdyLay.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Whistle.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("beewater.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("1C.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("2D.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("3E.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("4F.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("5G.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("6A.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("7B.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("8C.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("9D.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("skip.ogg"),
                               .Path = ptCurrTheme,
                               .AltPath = ptSounds
                           },
                           {
                               .FileName = STRINIT("sinegun.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Ooff1.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Ooff2.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Ooff3.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("hammer.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Comeonthen.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("parachute.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("bump.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("hogchant3.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("plane.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("TARDIS.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("frozen_hog_impact.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("ice_beam.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("hog_freeze.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("airmine_impact.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("knife_impact.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("extratime.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("lasersight.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("invulnerable.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("ufo.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("jetpackboost.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("portalshot.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("portalswitch.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("portalopen.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("blowtorch.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("countdown1.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("countdown2.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("countdown3.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("countdown4.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("rubberduck_drop.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("rubberduck_water.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("rubberduck_die.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("custom1.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("custom2.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("custom3.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("custom4.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("custom5.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("custom6.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("custom7.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("custom8.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("minigun.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("flamethrower.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("ice_beam_idle.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("landgun.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("graveimpact.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("hell_ugh.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("firepunch_hit.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Grenade.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Thisoneismine.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Whatthe.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Solong.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Ohdear.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Gonnagetyou.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Drat.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Bugger.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Amazing.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Brilliant.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Excellent.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Fire.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Watchthis.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Runaway.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Revenge.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Cutitout.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Leavemealone.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Ouch.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Hmm.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Kiss.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("Flyaway.ogg"),
                               .Path = ptVoices,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("planewater.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("dynamitefuse.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           },
                           {
                               .FileName = STRINIT("dynamiteimpact.ogg"),
                               .Path = ptSounds,
                               .AltPath = ptNone
                           }};
pointer usound_AskForVoicepack(string255 name)
{
    pointer askforvoicepack_result;
    LongWord i;
    string255 tmp;
    string255 nameStart;
    string255 langName;
    string255 path;
    nameStart = name;
    i = 0;
    tmp = fpcrtl_copy(name, fpcrtl_Length(name) - 3, 4);
    if(_strcompare(tmp, __str0))
    {
        name = fpcrtl_copy(name, 1, fpcrtl_Length(name) - 4);
    }
    if((_strncompare(cLanguage, __str1)) && (_strcompare(tmp, __str0)))
    {
        langName = _strconcat(_strappend(name, 0x5f), cLanguage);
        path = _strconcat(_strappend(cPathz[ptVoices], 0x2f), langName);
        if(uphysfslayer_pfsExists(path))
        {
            name = langName;
        }
        else
        {
            if(fpcrtl_Length(cLanguage) > 3)
            {
                langName = _strconcat(_strappend(name, 0x5f), fpcrtl_copy(cLanguage, 1, 2));
                path = _strconcat(_strappend(cPathz[ptVoices], 0x2f), langName);
                if(uphysfslayer_pfsExists(path))
                {
                    name = langName;
                }
            }
        }
    }
    path = _strconcat(_strappend(cPathz[ptVoices], 0x2f), name);
    if((_strncompare(nameStart, __str2)) && !uphysfslayer_pfsExists(path))
    {
        return usound_AskForVoicepack(__str2);
    }
    while(((_strncompare(voicepacks[i].name, name)) && (_strncompare(voicepacks[i].name, __str3))) && (i < cMaxTeams))
    {
        ++i;
    }
    voicepacks[i].name = name;
    askforvoicepack_result = &(voicepacks[i]);
    return askforvoicepack_result;
};
void usound_InitSound()
{
    LongInt channels = 2;
    boolean success;
    string255 s;
    if(!(isSoundEnabled || isMusicEnabled))
    {
        isAudioMuted = true;
        cInitVolume = 0;
        return;
    }
    uconsole_WriteToConsole(__str4);
    success = SDL_InitSubSystem(SDL_INIT_AUDIO) == 0;
    if(success)
    {
        uconsole_WriteLnToConsole(msgOK);
        uconsole_WriteToConsole(__str5);
        success = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, channels, 1024) == 0;
    }
    if(success)
    {
        uconsole_WriteLnToConsole(msgOK);
    }
    else
    {
        uconsole_WriteLnToConsole(msgFailed);
        isSoundEnabled = false;
        isMusicEnabled = false;
        isAudioMuted = true;
        cInitVolume = 0;
    }
    uconsole_WriteToConsole(__str6);
    if((Mix_Init(MIX_INIT_OGG | MIX_INIT_OPUS) & MIX_INIT_OPUS) == 0)
    {
        s = fpcrtl_pchar2str(SDL_GetError());
        uconsole_WriteToConsole(_strconcat(__str7, s));
        if(udebug_SDLCheck(Mix_Init(MIX_INIT_OGG) != 0, __str8, true))
        {
            return;
        }
    }
    uconsole_WriteLnToConsole(msgOK);
    cIsSoundEnabled = true;
    Mix_AllocateChannels((chanTPU + 1));
    previousVolume = cInitVolume;
    usound_ChangeVolume(cInitVolume);
};
void usound_ResetSound()
{
    isSoundEnabled = isSEBackup;
};
void usound_SetSound(boolean enabled)
{
    isSEBackup = isSoundEnabled;
    isSoundEnabled = enabled;
};
void usound_SetAudioDampen(boolean enabled)
{
    isAutoDampening = enabled;
};
void usound_ReleaseSound(boolean complete)
{
    TSound i;
    LongWord t;
    {t = 0;
     LongWord t__end__ = cMaxTeams;
     if (t <= t__end__) do {
                               if(_strncompare(voicepacks[t].name, __str3))
                               {
                                   {i = 0;
                                    TSound i__end__ = 174;
                                    if (i <= i__end__) do {
                                                              if(voicepacks[t].chunks[i] != NULL)
                                                              {
                                                                  if(complete || (Mix_Playing(lastChan[i]) == 0))
                                                                  {
                                                                      Mix_HaltChannel(lastChan[i]);
                                                                      lastChan[i] = -1;
                                                                      Mix_FreeChunk(voicepacks[t].chunks[i]);
                                                                      voicepacks[t].chunks[i] = NULL;
                                                                  }
                                                              }
                                                          } while(i++ != i__end__);}
                               }
                           } while(t++ != t__end__);}
    if(complete)
    {
        if(Mus != NULL)
        {
            Mix_HaltMusic();
            Mix_FreeMusic(Mus);
            Mus = NULL;
        }
        while(Mix_Init(0) != 0)
        {
            Mix_Quit();
        }
        Mix_CloseAudio();
    }
};
TSound usound_GetFallbackV(TSound snd)
{
    TSound getfallbackv_result;
    if(((snd == sndFirePunch2) || (snd == sndFirePunch3) || (snd == sndFirePunch4) || (snd == sndFirePunch5) || (snd == sndFirePunch6)))
    {
        getfallbackv_result = sndFirePunch1;
    }
    else
    {
        if(((snd == sndOw2) || (snd == sndOw3) || (snd == sndOw4) || (snd == sndOuch)))
        {
            getfallbackv_result = sndOw1;
        }
        else
        {
            if(((snd == sndOoff2) || (snd == sndOoff3)))
            {
                getfallbackv_result = sndOoff1;
            }
            else
            {
                if(snd == sndGrenade)
                {
                    if(fpcrtl_random(2) == 0)
                    {
                        getfallbackv_result = sndNooo;
                    }
                    else
                    {
                        getfallbackv_result = sndUhOh;
                    }
                }
                else
                {
                    if(snd == sndCover)
                    {
                        if(fpcrtl_random(2) == 0)
                        {
                            getfallbackv_result = sndWatchThis;
                        }
                        else
                        {
                            getfallbackv_result = sndFire;
                        }
                    }
                    else
                    {
                        if(((snd == sndBugger)))
                        {
                            getfallbackv_result = sndDrat;
                        }
                        else
                        {
                            if(((snd == sndDrat)))
                            {
                                getfallbackv_result = sndBugger;
                            }
                            else
                            {
                                if(((snd == sndGonnaGetYou) || (snd == sndIllGetYou) || (snd == sndRevenge) || (snd == sndCutItOut) || (snd == sndLeaveMeAlone)))
                                {
                                    getfallbackv_result = sndRegret;
                                }
                                else
                                {
                                    if(((snd == sndOhDear) || (snd == sndSoLong)))
                                    {
                                        getfallbackv_result = sndByeBye;
                                    }
                                    else
                                    {
                                        if(((snd == sndWhatThe) || (snd == sndUhOh)))
                                        {
                                            getfallbackv_result = sndNooo;
                                        }
                                        else
                                        {
                                            if(snd == sndRunAway)
                                            {
                                                getfallbackv_result = sndOops;
                                            }
                                            else
                                            {
                                                if(snd == sndThisOneIsMine)
                                                {
                                                    getfallbackv_result = sndReinforce;
                                                }
                                                else
                                                {
                                                    if(((snd == sndAmazing) || (snd == sndBrilliant) || (snd == sndExcellent)))
                                                    {
                                                        getfallbackv_result = sndEnemyDown;
                                                    }
                                                    else
                                                    {
                                                        if(snd == sndPoisonCough)
                                                        {
                                                            getfallbackv_result = sndPoisonMoan;
                                                        }
                                                        else
                                                        {
                                                            if(snd == sndPoisonMoan)
                                                            {
                                                                getfallbackv_result = sndPoisonCough;
                                                            }
                                                            else
                                                            {
                                                                if(snd == sndFlawless)
                                                                {
                                                                    getfallbackv_result = sndVictory;
                                                                }
                                                                else
                                                                {
                                                                    if(snd == sndSameTeam)
                                                                    {
                                                                        getfallbackv_result = sndTraitor;
                                                                    }
                                                                    else
                                                                    {
                                                                        if(snd == sndMelon)
                                                                        {
                                                                            getfallbackv_result = sndCover;
                                                                        }
                                                                        else
                                                                        {
                                                                            if(snd == sndHmm)
                                                                            {
                                                                                getfallbackv_result = sndHello;
                                                                            }
                                                                            else
                                                                            {
                                                                                getfallbackv_result = sndNone;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return getfallbackv_result;
};
boolean usound_PlaySound_1(TSound snd)
{
    boolean playsound_result;
    playsound_result = usound_PlaySoundV_5(snd, NULL, false, false, false);
    return playsound_result;
};
boolean usound_PlaySound_2(TSound snd,boolean keepPlaying)
{
    boolean playsound_result;
    playsound_result = usound_PlaySoundV_5(snd, NULL, keepPlaying, false, false);
    return playsound_result;
};
boolean usound_PlaySound_3(TSound snd,boolean keepPlaying,boolean ignoreMask)
{
    boolean playsound_result;
    playsound_result = usound_PlaySoundV_5(snd, NULL, keepPlaying, ignoreMask, false);
    return playsound_result;
};
boolean usound_PlaySound_4(TSound snd,boolean keepPlaying,boolean ignoreMask,boolean soundAsMusic)
{
    boolean playsound_result;
    playsound_result = usound_PlaySoundV_5(snd, NULL, keepPlaying, ignoreMask, soundAsMusic);
    return playsound_result;
};
boolean usound_PlaySoundV_2(TSound snd,PVoicepack voicepack)
{
    boolean playsoundv_result;
    playsoundv_result = usound_PlaySoundV_5(snd, voicepack, false, false, false);
    return playsoundv_result;
};
boolean usound_PlaySoundV_3(TSound snd,PVoicepack voicepack,boolean keepPlaying)
{
    boolean playsoundv_result;
    playsoundv_result = usound_PlaySoundV_5(snd, voicepack, keepPlaying, false, false);
    return playsoundv_result;
};
boolean usound_PlaySoundV_4(TSound snd,PVoicepack voicepack,boolean keepPlaying,boolean ignoreMask)
{
    boolean playsoundv_result;
    playsoundv_result = usound_PlaySoundV_5(snd, voicepack, keepPlaying, ignoreMask, false);
    return playsoundv_result;
};
boolean usound_PlaySoundV_5(TSound snd,PVoicepack voicepack,boolean keepPlaying,boolean ignoreMask,boolean soundAsMusic)
{
    boolean playsoundv_result;
    string255 s;
    TSound tempSnd;
    TSound loadSnd;
    PSDL_RWops rwops;
    playsoundv_result = false;
    if((!isSoundEnabled && !(soundAsMusic && isMusicEnabled)) || fastUntilLag)
    {
        return playsoundv_result;
    }
    if((keepPlaying && (lastChan[snd] != -1)) && (Mix_Playing(lastChan[snd]) != 0))
    {
        return playsoundv_result;
    }
    if((ignoreMask == false) && (MaskedSounds[snd] == true))
    {
        return playsoundv_result;
    }
    if(voicepack != NULL)
    {
        if(((voicepack->chunks[snd] == NULL) && (Soundz[snd].Path == ptVoices)) && (_strncompare(Soundz[snd].FileName, __str3)))
        {
            loadSnd = snd;
            s = _strconcat(_strappend(_strconcat(_strappend(cPathz[Soundz[loadSnd].Path], 0x2f), voicepack->name), 0x2f), Soundz[loadSnd].FileName);
            if(!uphysfslayer_pfsExists(s))
            {
                tempSnd = usound_GetFallbackV(snd);
                if(tempSnd != sndNone)
                {
                    loadSnd = tempSnd;
                }
                s = _strconcat(_strappend(_strconcat(_strappend(cPathz[Soundz[loadSnd].Path], 0x2f), voicepack->name), 0x2f), Soundz[loadSnd].FileName);
            }
            uconsole_WriteToConsole(_strconcat(_strconcat(msgLoading, s), __str9));
            rwops = uphysfslayer_rwopsOpenRead(s);
            if(rwops == NULL)
            {
                s = _strconcat(_strappend(cPathz[Soundz[loadSnd].AltPath], 0x2f), Soundz[loadSnd].FileName);
                uconsole_WriteToConsole(_strconcat(_strconcat(msgLoading, s), __str9));
                rwops = uphysfslayer_rwopsOpenRead(s);
            }
            voicepack->chunks[snd] = Mix_LoadWAV_RW(rwops, 1);
            if(voicepack->chunks[snd] == NULL)
            {
                uconsole_WriteLnToConsole(msgFailed);
            }
            else
            {
                uconsole_WriteLnToConsole(msgOK);
            }
        }
        lastChan[snd] = Mix_PlayChannelTimed(-1, voicepack->chunks[snd], 0, -1);
        playsoundv_result = true;
    }
    else
    {
        if(((defVoicepack->chunks[snd] == NULL) && (Soundz[snd].Path != ptVoices)) && (_strncompare(Soundz[snd].FileName, __str3)))
        {
            s = _strconcat(_strappend(cPathz[Soundz[snd].Path], 0x2f), Soundz[snd].FileName);
            uconsole_WriteToConsole(_strconcat(_strconcat(msgLoading, s), __str9));
            rwops = uphysfslayer_rwopsOpenRead(s);
            if(rwops == NULL)
            {
                s = _strconcat(_strappend(cPathz[Soundz[snd].AltPath], 0x2f), Soundz[snd].FileName);
                uconsole_WriteToConsole(_strconcat(_strconcat(msgLoading, s), __str9));
                rwops = uphysfslayer_rwopsOpenRead(s);
            }
            defVoicepack->chunks[snd] = Mix_LoadWAV_RW(rwops, 1);
            if(udebug_SDLCheck(defVoicepack->chunks[snd] != NULL, __str10, true))
            {
                return playsoundv_result;
            }
            uconsole_WriteLnToConsole(msgOK);
        }
        lastChan[snd] = Mix_PlayChannelTimed(-1, defVoicepack->chunks[snd], 0, -1);
        playsoundv_result = true;
    }
    return playsoundv_result;
};
void usound_PlayMusicSound(TSound snd)
{
    usound_PauseMusic();
    usound_PlaySound_4(snd, false, false, true);
};
void usound_StopMusicSound(TSound snd)
{
    usound_StopSound_2(snd, true);
    usound_ResumeMusic();
};
void usound_AddVoice_2(TSound snd,PVoicepack voicepack)
{
    usound_AddVoice_4(snd, voicepack, false, false);
};
void usound_AddVoice_4(TSound snd,PVoicepack voicepack,boolean ignoreMask,boolean isFallback)
{
    LongInt i;
    if((!isSoundEnabled || fastUntilLag) || ((LastVoice.snd == snd) && (LastVoice.voicepack == voicepack)))
    {
        return;
    }
    if((ignoreMask == false) && (MaskedSounds[snd] == true))
    {
        return;
    }
    if((snd == sndVictory) || (snd == sndFlawless))
    {
        Mix_FadeOutChannel(-1, 800);
        {i = 0;
         LongInt i__end__ = 7;
         if (i <= i__end__) do {
                                   VoiceList[i].snd = sndNone;
                               } while(i++ != i__end__);}
        LastVoice.snd = sndNone;
    }
    i = 0;
    while((i <= 7) && (VoiceList[i].snd != sndNone))
    {
        ++i;
    }
    if(((i > 0) && (VoiceList[i - 1].snd == snd)) && (VoiceList[i - 1].voicepack == voicepack))
    {
        return;
    }
    if(i <= 7)
    {
        VoiceList[i].snd = snd;
        VoiceList[i].voicepack = voicepack;
        VoiceList[i].isFallback = isFallback;
    }
};
void usound_PlayNextVoice()
{
    LongInt i;
    boolean played;
    if((!isSoundEnabled || fastUntilLag) || (((LastVoice.snd != sndNone) && (lastChan[LastVoice.snd] != -1)) && (Mix_Playing(lastChan[LastVoice.snd]) != 0)))
    {
        return;
    }
    i = 0;
    while((i < 7) && (VoiceList[i].snd == sndNone))
    {
        ++i;
    }
    played = false;
    if((VoiceList[i].snd != sndNone) && (!VoiceList[i].isFallback || LastVoiceFailed))
    {
        LastVoice.snd = VoiceList[i].snd;
        LastVoice.voicepack = VoiceList[i].voicepack;
        LastVoice.isFallback = VoiceList[i].isFallback;
        VoiceList[i].snd = sndNone;
        played = usound_PlaySoundV_2(LastVoice.snd, LastVoice.voicepack);
        LastVoiceFailed = !played;
    }
    else
    {
        LastVoice.snd = sndNone;
    }
};
LongInt usound_LoopSound_1(TSound snd)
{
    LongInt loopsound_result;
    loopsound_result = usound_LoopSoundV_2(snd, NULL);
    return loopsound_result;
};
LongInt usound_LoopSound_2(TSound snd,LongInt fadems)
{
    LongInt loopsound_result;
    loopsound_result = usound_LoopSoundV_3(snd, NULL, fadems);
    return loopsound_result;
};
LongInt usound_LoopSoundV_2(TSound snd,PVoicepack voicepack)
{
    LongInt loopsoundv_result;
    UNUSED (voicepack);
    loopsoundv_result = usound_LoopSoundV_3(snd, NULL, 0);
    return loopsoundv_result;
};
LongInt usound_LoopSoundV_3(TSound snd,PVoicepack voicepack,LongInt fadems)
{
    LongInt loopsoundv_result;
    string255 s;
    PSDL_RWops rwops;
    if(!isSoundEnabled || fastUntilLag)
    {
        loopsoundv_result = -1;
        return loopsoundv_result;
    }
    if(voicepack != NULL)
    {
        if(((voicepack->chunks[snd] == NULL) && (Soundz[snd].Path == ptVoices)) && (_strncompare(Soundz[snd].FileName, __str3)))
        {
            s = _strconcat(_strappend(_strconcat(_strappend(cPathz[Soundz[snd].Path], 0x2f), voicepack->name), 0x2f), Soundz[snd].FileName);
            uconsole_WriteToConsole(_strappend(_strconcat(msgLoading, s), 0x20));
            rwops = uphysfslayer_rwopsOpenRead(s);
            if(rwops == NULL)
            {
                s = _strconcat(_strappend(cPathz[Soundz[snd].AltPath], 0x2f), Soundz[snd].FileName);
                uconsole_WriteToConsole(_strconcat(_strconcat(msgLoading, s), __str9));
                rwops = uphysfslayer_rwopsOpenRead(s);
            }
            voicepack->chunks[snd] = Mix_LoadWAV_RW(rwops, 1);
            if(voicepack->chunks[snd] == NULL)
            {
                uconsole_WriteLnToConsole(msgFailed);
            }
            else
            {
                uconsole_WriteLnToConsole(msgOK);
            }
        }
        loopsoundv_result = Mix_PlayChannelTimed(-1, voicepack->chunks[snd], -1, -1);
    }
    else
    {
        if(((defVoicepack->chunks[snd] == NULL) && (Soundz[snd].Path != ptVoices)) && (_strncompare(Soundz[snd].FileName, __str3)))
        {
            s = _strconcat(_strappend(cPathz[Soundz[snd].Path], 0x2f), Soundz[snd].FileName);
            uconsole_WriteToConsole(_strappend(_strconcat(msgLoading, s), 0x20));
            defVoicepack->chunks[snd] = Mix_LoadWAV_RW(uphysfslayer_rwopsOpenRead(s), 1);
            if(udebug_SDLCheck(defVoicepack->chunks[snd] != NULL, __str10, true))
            {
                return -1;
            }
            uconsole_WriteLnToConsole(msgOK);
        }
        if(fadems > 0)
        {
            loopsoundv_result = Mix_FadeInChannelTimed(-1, defVoicepack->chunks[snd], -1, fadems, -1);
        }
        else
        {
            loopsoundv_result = Mix_PlayChannelTimed(-1, defVoicepack->chunks[snd], -1, -1);
        }
    }
    return loopsoundv_result;
};
void usound_StopSound_1(TSound snd)
{
    usound_StopSound_2(snd, false);
};
void usound_StopSound_2(TSound snd,boolean soundAsMusic)
{
    if(!isSoundEnabled && !(soundAsMusic && isMusicEnabled))
    {
        return;
    }
    if((lastChan[snd] != -1) && (Mix_Playing(lastChan[snd]) != 0))
    {
        Mix_HaltChannel(lastChan[snd]);
        lastChan[snd] = -1;
    }
};
void usound_StopSoundChan_1(LongInt chn)
{
    if(!isSoundEnabled)
    {
        return;
    }
    if((chn != -1) && (Mix_Playing(chn) != 0))
    {
        Mix_HaltChannel(chn);
    }
};
void usound_StopSoundChan_2(LongInt chn,LongInt fadems)
{
    if(!isSoundEnabled)
    {
        return;
    }
    if((chn != -1) && (Mix_Playing(chn) != 0))
    {
        if(isAudioMuted)
        {
            Mix_HaltChannel(chn);
        }
        else
        {
            Mix_FadeOutChannel(chn, fadems);
        }
    }
};
void usound_PlayMusic()
{
    string255 s;
    return;
    if((_strcompare(MusicFN, __str3)) || !isMusicEnabled)
    {
        return;
    }
    if(SuddenDeath && (_strncompare(SDMusicFN, __str3)))
    {
        s = _strconcat(__str11, SDMusicFN);
    }
    else
    {
        s = _strconcat(__str11, MusicFN);
    }
    uconsole_WriteToConsole(_strappend(_strconcat(msgLoading, s), 0x20));
    Mus = Mix_LoadMUS_RW(uphysfslayer_rwopsOpenRead(s));
    udebug_SDLCheck(Mus != NULL, __str12, false);
    if(Mus != NULL)
    {
        uconsole_WriteLnToConsole(msgOK);
    }
    if(Mus == NULL)
    {
        uconsole_WriteLnToConsole(__str13);
        if(SuddenDeath && (_strncompare(FallbackSDMusicFN, __str3)))
        {
            s = _strconcat(__str11, FallbackSDMusicFN);
        }
        else
        {
            if(!SuddenDeath && (_strncompare(FallbackMusicFN, __str3)))
            {
                s = _strconcat(__str11, FallbackMusicFN);
            }
            else
            {
                uconsole_WriteLnToConsole(__str14);
                s = __str3;
            }
        }
        if(_strncompare(s, __str3))
        {
            uconsole_WriteLnToConsole(_strappend(_strconcat(msgLoading, s), 0x20));
            Mus = Mix_LoadMUS_RW(uphysfslayer_rwopsOpenRead(s));
            udebug_SDLCheck(Mus != NULL, __str12, false);
            if(Mus != NULL)
            {
                uconsole_WriteLnToConsole(msgOK);
            }
        }
    }
    if(Mus != NULL)
    {
        udebug_SDLCheck(Mix_FadeInMusic(Mus, -1, 3000) != -1, __str15, false);
    }
};
void usound_SetVolume(LongInt vol)
{
    cInitVolume = vol;
};
LongInt usound_GetVolumePercent()
{
    LongInt getvolumepercent_result;
    getvolumepercent_result = (Volume * 100) / MIX_MAX_VOLUME;
    if((getvolumepercent_result == 0) && (Volume > 0))
    {
        getvolumepercent_result = 1;
    }
    else
    {
        if((getvolumepercent_result == 100) && (Volume < MIX_MAX_VOLUME))
        {
            getvolumepercent_result = 99;
        }
    }
    return getvolumepercent_result;
};
LongInt usound_ChangeVolume(LongInt voldelta)
{
    LongInt changevolume_result;
    changevolume_result = 0;
    if(!(isSoundEnabled || isMusicEnabled) || ((voldelta == 0) && !(cInitVolume == 0)))
    {
        return changevolume_result;
    }
    Volume += voldelta;
    if(Volume < 0)
    {
        Volume = 0;
    }
    Mix_Volume(-1, Volume);
    Volume = Mix_Volume(-1, -1);
    if(isMusicEnabled)
    {
        Mix_VolumeMusic((Volume * 4) / 8);
    }
    changevolume_result = usound_GetVolumePercent();
    if(isMusicEnabled)
    {
        if(Volume == 0)
        {
            usound_PauseMusic();
        }
        else
        {
            usound_ResumeMusic();
        }
    }
    isAudioMuted = Volume == 0;
    return changevolume_result;
};
void usound_DampenAudio()
{
    if(isAudioMuted || !isAutoDampening)
    {
        return;
    }
    previousVolume = Volume;
    usound_ChangeVolume((-Volume * 7) / 9);
};
void usound_UndampenAudio()
{
    if(isAudioMuted || !isAutoDampening)
    {
        return;
    }
    usound_ChangeVolume(previousVolume - Volume);
};
void usound_MuteAudio()
{
    if(!(isSoundEnabled || isMusicEnabled))
    {
        return;
    }
    if(isAudioMuted)
    {
        usound_ResumeMusic();
        usound_ChangeVolume(previousVolume);
    }
    else
    {
        usound_PauseMusic();
        previousVolume = Volume;
        usound_ChangeVolume(-Volume);
    }
};
void usound_SetMusic(boolean enabled)
{
    isMusicEnabled = enabled;
};
void usound_SetMusicName(string255 musicname)
{
    MusicFN = musicname;
};
void usound_PauseMusic()
{
    if((_strcompare(MusicFN, __str3)) || !isMusicEnabled)
    {
        return;
    }
    if(Mus != NULL)
    {
        Mix_PauseMusic(Mus);
    }
};
void usound_ResumeMusic()
{
    if((_strcompare(MusicFN, __str3)) || !isMusicEnabled)
    {
        return;
    }
    if(Mus != NULL)
    {
        Mix_ResumeMusic(Mus);
    }
};
void usound_ChangeMusic(string255 musicname)
{
    MusicFN = musicname;
    if((_strcompare(MusicFN, __str3)) || !isMusicEnabled)
    {
        return;
    }
    usound_StopMusic();
    usound_PlayMusic();
};
void usound_StopMusic()
{
    if((_strcompare(MusicFN, __str3)) || !isMusicEnabled)
    {
        return;
    }
    if(Mus != NULL)
    {
        Mix_FreeMusic(Mus);
        Mus = NULL;
    }
};
void usound_chVoicepack(string255 (*s))
{
    if(CurrentTeam == NULL)
    {
        udebug_OutError(_strconcat(errmsgIncorrectUse, __str16), true);
    }
    if((*s).s[1] == 0x22)
    {
        fpcrtl_Delete((*s), 1, 1);
    }
    if((*s).s[((Byte)(*s).s[0])] == 0x22)
    {
        fpcrtl_Delete((*s), ((Byte)(*s).s[0]), 1);
    }
    CurrentTeam->voicepack = usound_AskForVoicepack((*s));
};
void usound_preInitModule()
{
    isMusicEnabled = true;
    isSoundEnabled = true;
    isAutoDampening = true;
    cInitVolume = 100;
};
void usound_initModule()
{
    LongInt t;
    TSound i;
    ucommands_RegisterVariable_3(__str17, &(usound_chVoicepack), false);
    MusicFN = __str3;
    SDMusicFN = __str18;
    FallbackMusicFN = __str3;
    FallbackSDMusicFN = __str18;
    Mus = NULL;
    isAudioMuted = false;
    isSEBackup = isSoundEnabled;
    Volume = 0;
    SoundTimerTicks = 0;
    defVoicepack = usound_AskForVoicepack(__str2);
    LastVoiceFailed = false;
    {i = 0;
     TSound i__end__ = 174;
     if (i <= i__end__) do {
                               lastChan[i] = -1;
                           } while(i++ != i__end__);}
    {t = 0;
     LongInt t__end__ = cMaxTeams;
     if (t <= t__end__) do {
                               if(_strncompare(voicepacks[t].name, __str3))
                               {
                                   {i = 0;
                                    TSound i__end__ = 174;
                                    if (i <= i__end__) do {
                                                              voicepacks[t].chunks[i] = NULL;
                                                          } while(i++ != i__end__);}
                               }
                           } while(t++ != t__end__);}
    {i = 0;
     TSound i__end__ = 174;
     if (i <= i__end__) do {
                               defVoicepack->chunks[i] = NULL;
                           } while(i++ != i__end__);}
};
void usound_freeModule()
{
    if(isSoundEnabled || isMusicEnabled)
    {
        usound_ReleaseSound(true);
    }
};
