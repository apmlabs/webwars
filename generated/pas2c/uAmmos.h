#pragma once

#include "pas2c.h"

#include "uConsts.h"
#include "uTypes.h"
#include "uStore.h"
void uammos_initModule();
void uammos_freeModule();
void uammos_AddAmmoStore();
void uammos_SetAmmoLoadout(string255 (*s));
void uammos_SetAmmoProbability(string255 (*s));
void uammos_SetAmmoDelay(string255 (*s));
void uammos_SetAmmoReinforcement(string255 (*s));
void uammos_AssignStores();
void uammos_AddAmmo_2(THedgehog (*Hedgehog),TAmmoType ammo);
void uammos_AddAmmo_3(THedgehog (*Hedgehog),TAmmoType ammo,LongWord amt);
void uammos_SetAmmo(THedgehog (*Hedgehog),TAmmoType ammo,LongWord cnt);
LongWord uammos_HHHasAmmo(THedgehog (*Hedgehog),TAmmoType Ammo);
void uammos_PackAmmo(PHHAmmo Ammo,LongInt Slot);
void uammos_OnUsedAmmo(THedgehog (*Hedgehog));
void uammos_ApplyAngleBounds(THedgehog (*Hedgehog),TAmmoType AmmoType);
void uammos_ApplyAmmoChanges(THedgehog (*Hedgehog));
void uammos_SwitchNotHeldAmmo(THedgehog (*Hedgehog));
void uammos_SetWeapon(TAmmoType weap);
void uammos_DisableSomeWeapons();
void uammos_ResetWeapons();
PHHAmmo uammos_GetAmmoByNum(LongInt num);
PAmmo uammos_GetCurAmmoEntry(THedgehog (*Hedgehog));
PAmmo uammos_GetAmmoEntry(THedgehog (*Hedgehog),TAmmoType am);
extern LongInt StoreCnt;

