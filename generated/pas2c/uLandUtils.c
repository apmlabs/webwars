#include "fpcrtl.h"

#include "uLandUtils.h"
pointer gameField;
#include "uUtils.h"
#include "uConsts.h"
#include "uVariables.h"
#include "uTypes.h"
#include "uRust.h"
Word ulandutils_LandGet(LongInt y,LongInt x)
{
    Word landget_result;
    landget_result = land_get(gameField, x, y);
    return landget_result;
};
void ulandutils_LandSet(LongInt y,LongInt x,Word value)
{
    land_set(gameField, x, y, value);
};
PWordArray ulandutils_LandRow(LongInt row)
{
    PWordArray landrow_result;
    landrow_result = land_row(gameField, row);
    return landrow_result;
};
void ulandutils_FillLand(LongInt x,LongInt y,Word border,Word value)
{
    land_fill(gameField, x, y, border, value);
};
LongWord ulandutils_LandPixelGet(LongInt y,LongInt x)
{
    LongWord landpixelget_result;
    landpixelget_result = land_pixel_get(gameField, x, y);
    return landpixelget_result;
};
void ulandutils_LandPixelSet(LongInt y,LongInt x,LongWord value)
{
    land_pixel_set(gameField, x, y, value);
};
PLongWordArray ulandutils_LandPixelRow(LongInt row)
{
    PLongWordArray landpixelrow_result;
    landpixelrow_result = land_pixel_row(gameField, row);
    return landpixelrow_result;
};
void ulandutils_GenerateOutlineTemplatedLand(LongWord featureSize,string255 seed,string255 templateType,astring dataPath)
{
    seed.s[((Byte)seed.s[0]) + 1] = 0x0;
    templateType.s[((Byte)templateType.s[0]) + 1] = 0x0;
    gameField = generate_outline_templated_game_field(featureSize, &(seed.s[1]), &(templateType.s[1]), fpcrtl__pcharA(dataPath));
    get_game_field_parameters(gameField, &(LAND_WIDTH), &(LAND_HEIGHT), &(playWidth), &(playHeight));
    MaxHedgehogs = 32;
    hasGirders = true;
    leftX = (LAND_WIDTH - playWidth) / 2;
    rightX = ((int)(leftX + playWidth) - 1);
    topY = LAND_HEIGHT - playHeight;
    cWaterLine = LAND_HEIGHT;
    LAND_WIDTH_MASK = ~(LAND_WIDTH - 1);
    LAND_HEIGHT_MASK = ~(LAND_HEIGHT - 1);
    fpcrtl_SetLength(LandDirty, LAND_HEIGHT / 32, LAND_WIDTH / 32);
    uvariables_initScreenSpaceVars();
};
void ulandutils_GenerateWfcTemplatedLand(LongWord featureSize,string255 seed,string255 templateType,astring dataPath)
{
    seed.s[((Byte)seed.s[0]) + 1] = 0x0;
    templateType.s[((Byte)templateType.s[0]) + 1] = 0x0;
    gameField = generate_wfc_templated_game_field(featureSize, &(seed.s[1]), &(templateType.s[1]), fpcrtl__pcharA(dataPath));
    get_game_field_parameters(gameField, &(LAND_WIDTH), &(LAND_HEIGHT), &(playWidth), &(playHeight));
    MaxHedgehogs = 32;
    hasGirders = true;
    leftX = (LAND_WIDTH - playWidth) / 2;
    rightX = ((int)(leftX + playWidth) - 1);
    topY = LAND_HEIGHT - playHeight;
    cWaterLine = LAND_HEIGHT;
    LAND_WIDTH_MASK = ~(LAND_WIDTH - 1);
    LAND_HEIGHT_MASK = ~(LAND_HEIGHT - 1);
    fpcrtl_SetLength(LandDirty, LAND_HEIGHT / 32, LAND_WIDTH / 32);
    uvariables_initScreenSpaceVars();
};
void ulandutils_GenerateMazeLand(LongWord featureSize,string255 seed,string255 templateType,astring dataPath)
{
    seed.s[((Byte)seed.s[0]) + 1] = 0x0;
    templateType.s[((Byte)templateType.s[0]) + 1] = 0x0;
    gameField = generate_maze_game_field(featureSize, &(seed.s[1]), &(templateType.s[1]), fpcrtl__pcharA(dataPath));
    get_game_field_parameters(gameField, &(LAND_WIDTH), &(LAND_HEIGHT), &(playWidth), &(playHeight));
    MaxHedgehogs = 32;
    hasGirders = true;
    leftX = (LAND_WIDTH - playWidth) / 2;
    rightX = ((int)(leftX + playWidth) - 1);
    topY = LAND_HEIGHT - playHeight;
    cWaterLine = LAND_HEIGHT;
    LAND_WIDTH_MASK = ~(LAND_WIDTH - 1);
    LAND_HEIGHT_MASK = ~(LAND_HEIGHT - 1);
    fpcrtl_SetLength(LandDirty, LAND_HEIGHT / 32, LAND_WIDTH / 32);
    uvariables_initScreenSpaceVars();
};
void ulandutils_ResizeLand(LongWord width,LongWord height)
{
    LongInt potW;
    LongInt potH;
    potW = uutils_toPowerOf2(width);
    potH = uutils_toPowerOf2(height);
    if((potW != LAND_WIDTH) || (potH != LAND_HEIGHT))
    {
        LAND_WIDTH = potW;
        LAND_HEIGHT = potH;
        LAND_WIDTH_MASK = ~(LAND_WIDTH - 1);
        LAND_HEIGHT_MASK = ~(LAND_HEIGHT - 1);
        cWaterLine = LAND_HEIGHT;
        gameField = create_empty_game_field(LAND_WIDTH, LAND_HEIGHT);
        fpcrtl_SetLength(LandDirty, LAND_HEIGHT / 32, LAND_WIDTH / 32);
        if(((width / 4096) >= 2) || ((height / 2048) >= 2))
        {
            cMaxZoomLevel = cMaxZoomLevel /(float) 2;
        }
        cMinMaxZoomLevelDelta = cMaxZoomLevel - cMinZoomLevel;
    }
    uvariables_initScreenSpaceVars();
};
void ulandutils_DisposeLand()
{
    dispose_game_field(gameField);
};
void ulandutils_InitWorldEdges()
{
    LongInt cy;
    LongInt cx;
    LongInt lx;
    LongInt ly;
    boolean found;
    playHeight = LAND_HEIGHT;
    topY = 0;
    lx = ((LongInt)LAND_WIDTH) - 1;
    if(cMapGen == mgDrawn)
    {
        return;
    }
    if(WorldEdge == weNone)
    {
        playWidth = LAND_WIDTH;
        leftX = 0;
        rightX = lx;
        return;
    }
    if((cMapGen == mgForts) && (WorldEdge == weWrap))
    {
        return;
    }
    ly = ((LongInt)LAND_HEIGHT) - 1;
    found = false;
    {cx = 0;
     LongInt cx__end__ = lx;
     if (cx <= cx__end__) do {
                                 {cy = ly;
                                  LongInt cy__end__ = 0;
                                  if (cy >= cy__end__) do {
                                                              if(ulandutils_LandGet(cy, cx) != 0)
                                                              {
                                                                  leftX = uutils_Max(0, cx - cWorldEdgeDist);
                                                                  found = true;
                                                                  break;
                                                              }
                                                          } while(cy-- != cy__end__);}
                                 if(found)
                                 {
                                     break;
                                 }
                             } while(cx++ != cx__end__);}
    found = false;
    {cx = lx;
     LongInt cx__end__ = 0;
     if (cx >= cx__end__) do {
                                 {cy = ly;
                                  LongInt cy__end__ = 0;
                                  if (cy >= cy__end__) do {
                                                              if(ulandutils_LandGet(cy, cx) != 0)
                                                              {
                                                                  rightX = uutils_Min(lx, cx + cWorldEdgeDist);
                                                                  found = true;
                                                                  break;
                                                              }
                                                          } while(cy-- != cy__end__);}
                                 if(found)
                                 {
                                     break;
                                 }
                             } while(cx-- != cx__end__);}
    playWidth = (rightX + 1) - leftX;
};
