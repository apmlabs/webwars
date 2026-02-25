#include "fpcrtl.h"

#include "uAILandMarks.h"
#include "uVariables.h"
enum{gr = 2};
typedef Byte * (*marks_tt);
static fpcrtl_dimension_t marks_dimension_info ={.dim = 0, .a = {0, 0, 0, 0}};
static marks_tt marks = NULL;
static LongWord WIDTH;
static LongWord HEIGHT;
void uailandmarks_addMark(LongInt X,LongInt Y,Byte mark)
{
    if(((X & LAND_WIDTH_MASK) == 0) && ((Y & LAND_HEIGHT_MASK) == 0))
    {
        X = X >> gr;
        Y = Y >> gr;
        marks[Y][X] = marks[Y][X] | mark;
    }
};
boolean uailandmarks_checkMark(LongInt X,LongInt Y,Byte mark)
{
    boolean checkmark_result;
    checkmark_result = (((X & LAND_WIDTH_MASK) == 0) && ((Y & LAND_HEIGHT_MASK) == 0)) && ((marks[Y >> gr][X >> gr] & mark) != 0);
    return checkmark_result;
};
void uailandmarks_clearAllMarks()
{
    LongWord Y;
    LongWord X;
    {Y = 0;
     LongWord Y__end__ = ((int)(HEIGHT) - 1);
     if (Y <= Y__end__) do {
                               {X = 0;
                                LongWord X__end__ = ((int)(WIDTH) - 1);
                                if (X <= X__end__) do {
                                                          marks[Y][X] = 0;
                                                      } while(X++ != X__end__);}
                           } while(Y++ != Y__end__);}
};
void uailandmarks_clearMarks(Byte mark)
{
    LongWord Y;
    LongWord X;
    {Y = 0;
     LongWord Y__end__ = ((int)(HEIGHT) - 1);
     if (Y <= Y__end__) do {
                               {X = 0;
                                LongWord X__end__ = ((int)(WIDTH) - 1);
                                if (X <= X__end__) do {
                                                          marks[Y][X] = marks[Y][X] & ~mark;
                                                      } while(X++ != X__end__);}
                           } while(Y++ != Y__end__);}
};
void uailandmarks_setAILandMarks()
{
    WIDTH = LAND_WIDTH >> gr;
    HEIGHT = LAND_HEIGHT >> gr;
    fpcrtl_SetLength(marks, HEIGHT, WIDTH);
};
void uailandmarks_initModule()
{
};
void uailandmarks_freeModule()
{
    fpcrtl_SetLength(marks, 0, 0);
};
