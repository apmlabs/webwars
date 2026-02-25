#include "fpcrtl.h"

#include "uAI2.h"
#include "uLandUtils.h"
#include "uFloat.h"
#include "uVariables.h"
#include "uAmmos.h"
#include "uConsts.h"
#include "uTypes.h"
#include "uCommands.h"
#include "uUtils.h"
#include "uDebug.h"
#include "uAILandMarks.h"
#include "uGearsUtils.h"
#include "uRust.h"
static const string255 __str0 = STRINIT("");
static pointer ai;
void uai2_initiateThinking()
{
    LongWord currHedgehogIndex;
    LongWord itHedgehog;
    TAmmoType itAmmo;
    TAmmoCounts ammoCounts;
    ai_clear_team(ai);
    currHedgehogIndex = CurrentTeam->CurrHedgehog;
    itHedgehog = currHedgehogIndex;
    do {
           {
               if((CurrentTeam->Hedgehogs[itHedgehog].Gear != NULL) && (CurrentTeam->Hedgehogs[itHedgehog].Effects[heFrozen] == 0))
               {
                   {itAmmo = 0;
                    TAmmoType itAmmo__end__ = 60;
                    if (itAmmo <= itAmmo__end__) do {
                                                        ammoCounts[itAmmo] = uammos_HHHasAmmo(&(CurrentTeam->Hedgehogs[itHedgehog]), itAmmo);
                                                    } while(itAmmo++ != itAmmo__end__);}
                   ai_add_team_hedgehog(ai, ufloat_hwFloat2Float(CurrentTeam->Hedgehogs[itHedgehog].Gear->X), ufloat_hwFloat2Float(CurrentTeam->Hedgehogs[itHedgehog].Gear->Y), &(ammoCounts));
               }
           }
           itHedgehog = (itHedgehog + 1) % CurrentTeam->HedgehogsNumber;
       } while(!(itHedgehog == currHedgehogIndex));
    ai_think(ai);
};
void uai2_processActions()
{
    HedgehogState state;
    string255 action;
    {
        state.x = ufloat_hwFloat2Float((*CurrentHedgehog).Gear->X);
        state.y = ufloat_hwFloat2Float((*CurrentHedgehog).Gear->Y);
        state.angle = (*CurrentHedgehog).Gear->Angle;
        state.looking_to_the_right = !(*CurrentHedgehog).Gear->dX.isNegative;
        state.is_moving = ((*CurrentHedgehog).Gear->State & ((gstAttacking | gstHHJumping) | gstMoving)) != 0;
    }
    ai_get_action(ai, &(state), &(action));
    if(_strncompare(action, __str0))
    {
        ucommands_ParseCommand_2(action, true);
    }
};
void uai2_ProcessBot()
{
    {
        if(((*CurrentHedgehog).Gear == NULL) || (((*CurrentHedgehog).Gear->State & gstHHDriven) == 0))
        {
            return;
        }
    }
    if(ai == NULL)
    {
        ai = create_ai(gameField);
    }
    if(!ai_have_plan())
    {
        uai2_initiateThinking();
        return;
    }
    else
    {
        uai2_processActions();
    }
};
void uai2_initModule()
{
    ai = NULL;
};
