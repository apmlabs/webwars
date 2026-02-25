#include "fpcrtl.h"

#include "uKeyNames.h"
#include "uPhysFSLayer.h"
#include "uUtils.h"
#include "uVariables.h"
#include "uTypes.h"
#include "uConsole.h"
static const string255 __str2 = STRINIT("misc/keys.csv file not found");
static const string255 __str1 = STRINIT("");
static const string255 __str0 = STRINIT("/keys.csv");
void ukeynames_populateKeyNames(TKeyNames (*KeyArray))
{
    PFSFile f;
    string255 l;
    string255 keyname;
    string255 tmp;
    LongInt i;
    LongInt scancode;
    if(uphysfslayer_pfsExists(_strconcat(cPathz[ptMisc], __str0)))
    {
        f = uphysfslayer_pfsOpenRead(_strconcat(cPathz[ptMisc], __str0));
        l = __str1;
        uphysfslayer_pfsReadLn(f, &(l));
        while(!uphysfslayer_pfsEOF(f) && (_strncompare(l, __str1)))
        {
            tmp = __str1;
            i = 1;
            while((i <= fpcrtl_Length(l)) && (l.s[i] != 0x2c))
            {
                tmp = _strappend(tmp, l.s[i]);
                ++i;
            }
            scancode = uutils_StrToInt(tmp);
            if(i < fpcrtl_Length(l))
            {
                keyname = fpcrtl_copy(l, i + 1, fpcrtl_Length(l) - i);
                if((keyname.s[1] == 0x22) && (keyname.s[fpcrtl_Length(keyname)] == 0x22))
                {
                    keyname = fpcrtl_copy(keyname, 2, fpcrtl_Length(keyname) - 2);
                }
                else
                {
                    keyname = fpcrtl_copy(keyname, 1, fpcrtl_Length(keyname) - 1);
                }
            }
            uphysfslayer_pfsReadLn(f, &(l));
            (*KeyArray)[scancode] = keyname;
        }
        uphysfslayer_pfsClose(f);
    }
    else
    {
        uconsole_WriteLnToConsole(__str2);
        uutils_AddFileLog(__str2);
        fpcrtl_halt(HaltStartupError);
    }
};
