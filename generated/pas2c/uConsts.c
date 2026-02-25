#include "fpcrtl.h"

#include "uConsts.h"
;
;
;
;
cFontsPaths_tt cFontsPaths = {NULL,
                              NULL};
;
;
;
;
;
;
;
;
;
;
;
;
;
LongInt cameraKeyboardSpeed = 10;
LongInt cameraKeyboardSpeedSlow = 3;
TSDL_Color cWhiteColorChannels = {
                                     .r = 0xff,
                                     .g = 0xff,
                                     .b = 0xff,
                                     .a = 0xff
                                 };
TSDL_Color cNearBlackColorChannels = {
                                         .r = 0x00,
                                         .g = 0x00,
                                         .b = 0x10,
                                         .a = 0xff
                                     };
Byte cInvertTextColorAt = 64;
LongWord cWhiteColor = 0xffffffff;
LongWord cNearBlackColor = 0xff000010;
LongWord capcolDefault = 0xffffffff;
LongWord capcolSetting = 0xffcccccc;
LongWord capcolDefaultLua = 0xffffffff;
LongWord capcolSettingLua = 0xccccccff;
LongWord cCentralMessageColor = 0xffffff00;
hwFloat cAirPlaneSpeed = {
                             .isNegative = false,
                             .QWordValue = 3006477107
                         };
hwFloat cBombsSpeed = {
                          .isNegative = false,
                          .QWordValue = 429496729
                      };
LongInt cVisibleWater = 128;
LongInt cTeamHealthWidth = 128;
LongInt cGearContourThreshold = 179;
LongInt JETPACK_FUEL_INFINITE = -2147483648;
LongInt BIRDY_ENERGY_INFINITE = -2147483648;
probabilityLevels_tt probabilityLevels = {0,
                                          20,
                                          30,
                                          60,
                                          100,
                                          200,
                                          400,
                                          600,
                                          800};
bouncinessLevels_tt bouncinessLevels = {350,
                                        700,
                                        defaultBounciness,
                                        2000,
                                        4000};
TPoint cTargetPointRef = {
                             .x = NoPointX,
                             .y = 0
                         };
LongInt cTeamHealthHeight = 19;
LongInt cFontBorder = 2;
LongInt cFontPadding = 2;

