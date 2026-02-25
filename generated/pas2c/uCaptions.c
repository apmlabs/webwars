#include "fpcrtl.h"

#include "uCaptions.h"
#include "uTextures.h"
#include "uRenderUtils.h"
#include "uVariables.h"
#include "uRender.h"
static const string255 __str0 = STRINIT("");
typedef struct __TCaptionStr {
            PTexture Tex;
            LongWord EndTime;
            astring Text;
            LongWord Color;
        } TCaptionStr;
typedef TCaptionStr Captions_tt[6];
static Captions_tt Captions;
void ucaptions_AddCaption(astring s,LongWord Color,TCapGroup Group)
{
    if(cOnlyStats)
    {
        return;
    }
    if(fpcrtl_LengthA(s) == 0)
    {
        return;
    }
    if((_strncompareA(Captions[Group].Text, s)) || (Captions[Group].Color != Color))
    {
        utextures_FreeAndNilTexture(&(Captions[Group].Tex));
    }
    if(Captions[Group].Tex == NULL)
    {
        Captions[Group].Color = Color;
        Captions[Group].Text = s;
        Captions[Group].Tex = urenderutils_RenderStringTex(s, Color, fntBig);
    }
    switch(Group)
    {case capgrpGameState:Captions[Group].EndTime = RealTicks + 2200;
                          break;
     default: Captions[Group].EndTime = (RealTicks + 1400) + (((LongWord)(*Captions[Group].Tex).w) * 3);}
};
void ucaptions_ReloadCaptions(boolean unload)
{
    TCapGroup Group;
    {Group = 0;
     TCapGroup Group__end__ = 5;
     if (Group <= Group__end__) do {
                                       if(unload)
                                       {
                                           utextures_FreeAndNilTexture(&(Captions[Group].Tex));
                                       }
                                       else
                                       {
                                           if(fpcrtl_LengthA(Captions[Group].Text) > 0)
                                           {
                                               Captions[Group].Tex = urenderutils_RenderStringTex(Captions[Group].Text, Captions[Group].Color, fntBig);
                                           }
                                       }
                                   } while(Group++ != Group__end__);}
};
void ucaptions_DrawCaptions()
{
    TCapGroup grp;
    LongInt offset;
    offset = 8;
    {grp = 0;
     TCapGroup grp__end__ = 5;
     if (grp <= grp__end__) do {
                                   {
                                       if(Captions[grp].Tex != NULL)
                                       {
                                           urender_DrawTextureCentered(0, offset, Captions[grp].Tex);
                                           offset += Captions[grp].Tex->h + 2;
                                           if(Captions[grp].EndTime <= RealTicks)
                                           {
                                               utextures_FreeAndNilTexture(&(Captions[grp].Tex));
                                               Captions[grp].Text = fpcrtl_str2astr(__str0);
                                               Captions[grp].EndTime = 0;
                                           }
                                       }
                                   }
                               } while(grp++ != grp__end__);}
};
void ucaptions_initModule()
{
    fpcrtl_FillChar(Captions, sizeof(Captions), 0);
};
void ucaptions_freeModule()
{
    TCapGroup group;
    {group = 0;
     TCapGroup group__end__ = 5;
     if (group <= group__end__) do {
                                       utextures_FreeAndNilTexture(&(Captions[group].Tex));
                                   } while(group++ != group__end__);}
};
