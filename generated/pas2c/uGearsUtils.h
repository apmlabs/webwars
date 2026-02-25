#pragma once

#include "pas2c.h"

#include "uTypes.h"
#include "uFloat.h"
void ugearsutils_doMakeExplosion_5(LongInt X,LongInt Y,LongInt Radius,PHedgehog AttackingHog,LongWord Mask);
void ugearsutils_doMakeExplosion_6(LongInt X,LongInt Y,LongInt Radius,PHedgehog AttackingHog,LongWord Mask,LongWord Tint);
void ugearsutils_AddSplashForGear(PGear Gear,boolean justSkipping);
void ugearsutils_AddBounceEffectForGear_2(PGear Gear,single imageScale);
void ugearsutils_AddBounceEffectForGear_1(PGear Gear);
LongWord ugearsutils_ModifyDamage(LongWord dmg,PGear Gear);
void ugearsutils_ApplyDamage(PGear Gear,PHedgehog AttackerHog,LongWord Damage,TDamageSource Source);
void ugearsutils_spawnHealthTagForHH(PGear HHGear,LongWord dmg);
void ugearsutils_HHHurt(PHedgehog Hedgehog,TDamageSource Source,LongWord Damage);
void ugearsutils_HHHeal_4(PHedgehog Hedgehog,LongInt healthBoost,boolean showMessage,LongWord vgTint);
void ugearsutils_HHHeal_3(PHedgehog Hedgehog,LongInt healthBoost,boolean showMessage);
LongInt ugearsutils_IncHogHealth(PHedgehog Hedgehog,LongInt healthBoost);
void ugearsutils_CheckHHDamage(PGear Gear);
void ugearsutils_CalcRotationDirAngle(PGear Gear);
void ugearsutils_ResurrectHedgehog(PGear (*gear));
void ugearsutils_FindPlace_4(PGear (*Gear),boolean withFall,LongInt Left,LongInt Right);
void ugearsutils_FindPlace_5(PGear (*Gear),boolean withFall,LongInt Left,LongInt Right,boolean skipProximity);
void ugearsutils_FindPlace_6(PGear (*Gear),boolean withFall,LongInt Left,LongInt Right,boolean skipProximity,boolean deleteOnFail);
void ugearsutils_FindPlace_7(PGear (*Gear),boolean withFall,LongInt Left,LongInt Right,LongInt Bottom,boolean skipProximity,boolean deleteOnFail);
LongInt ugearsutils_CountLand(LongInt x,LongInt y,LongInt r,LongInt c,LongWord mask,LongWord antimask);
PGear ugearsutils_CheckGearNear_5(TGearType Kind,hwFloat X,hwFloat Y,LongInt rX,LongInt rY);
PGear ugearsutils_CheckGearNear_4(PGear Gear,TGearType Kind,LongInt rX,LongInt rY);
boolean ugearsutils_CheckGearDrowning(PGear (*Gear));
void ugearsutils_CheckCollision(PGear Gear);
void ugearsutils_CheckCollisionWithLand(PGear Gear);
void ugearsutils_AmmoShove(PGear Ammo,LongInt Damage,LongInt Power);
void ugearsutils_AmmoShoveCache(PGear Ammo,LongInt Damage,LongInt Power);
void ugearsutils_AmmoShoveLine(PGear Ammo,LongInt Damage,LongInt Power,hwFloat oX,hwFloat oY,hwFloat tX,hwFloat tY);
PGearArrayS ugearsutils_GearsNear(hwFloat X,hwFloat Y,TGearType Kind,LongInt r);
PGear ugearsutils_SpawnBoxOfSmth();
void ugearsutils_PlayBoxSpawnTaunt(PGear Gear);
void ugearsutils_ShotgunShot(PGear Gear);
LongInt ugearsutils_CountHogsInTeam(PGear HHGear,boolean countHidden);
boolean ugearsutils_CanUseTardis(PGear HHGear);
void ugearsutils_SetAllToActive();
void ugearsutils_SetAllHHToActive_1(boolean Ice);
void ugearsutils_SetAllHHToActive_0();
TAmmoType ugearsutils_GetAmmo(PHedgehog Hedgehog);
TAmmoType ugearsutils_GetUtility(PHedgehog Hedgehog);
boolean ugearsutils_WorldWrap(PGear (*Gear));
boolean ugearsutils_HomingWrap(PGear (*Gear));
boolean ugearsutils_IsHogFacingLeft(PGear Gear);
boolean ugearsutils_IsHogLocal(PHedgehog HH);
boolean ugearsutils_MakeHedgehogsStep(PGear Gear);
typedef utypes_TGearStepProcedure doStepHandlers_tt[70];
extern doStepHandlers_tt doStepHandlers;

