#include "fpcrtl.h"

#include "uConsole.h"
string255 lastConsoleline;
#include "uUtils.h"
static const string255 __str1 = STRINIT("");
static const string255 __str0 = STRINIT("[Con] ");
void uconsole_WriteToConsole(string255 s)
{
    uutils_AddFileLog(_strconcat(__str0, s));
    fpcrtl_write(stderr, s);
};
void uconsole_WriteLnToConsole(string255 s)
{
    uconsole_WriteToConsole(s);
    fpcrtl_writeLn(stderr, __str1);
    lastConsoleline = s;
};
