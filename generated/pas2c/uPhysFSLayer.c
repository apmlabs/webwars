#include "fpcrtl.h"

#include "uPhysFSLayer.h"
;
;
#include "uConsts.h"
#include "uUtils.h"
#include "uVariables.h"
#include "physfs.h"
static const string255 __str6 = STRINIT("/Data");
static const string255 __str5 = STRINIT("/Config/Logs");
static const string255 __str4 = STRINIT("/Config/Data");
static const string255 __str3 = STRINIT("/Config");
static const string255 __str2 = STRINIT(" hedgewars");
static const string255 __str1 = STRINIT("/");
static const string255 __str0 = STRINIT("");
PSDL_RWops PHYSFSRWOPS_openRead(PChar fname);
PSDL_RWops PHYSFSRWOPS_openWrite(PChar fname);
void hedgewarsMountPackages();
Int64 uphysfslayer_PHYSFS_readBytes(PFSFile f,pointer buffer,Int64 len)
{
    Int64 physfs_readbytes_result;
    physfs_readbytes_result = PHYSFS_read(f, buffer, 1, len);
    return physfs_readbytes_result;
};
PSDL_RWops uphysfslayer_rwopsOpenRead(string255 fname)
{
    return PHYSFSRWOPS_openRead(uutils_Str2PChar(fname));
};
PSDL_RWops uphysfslayer_rwopsOpenWrite(string255 fname)
{
    return PHYSFSRWOPS_openWrite(uutils_Str2PChar(fname));
};
PFSFile uphysfslayer_pfsOpenRead(string255 fname)
{
    PFSFile pfsopenread_result;
    PFSFile f;
    f = PHYSFS_openRead(uutils_Str2PChar(fname));
    if(f != NULL)
    {
        PHYSFS_setBuffer(f, 4096);
    }
    return f;
    return pfsopenread_result;
};
PFSFile uphysfslayer_pfsOpenWrite(string255 fname)
{
    return PHYSFS_openWrite(uutils_Str2PChar(fname));
};
boolean uphysfslayer_pfsEOF(PFSFile f)
{
    return PHYSFS_eof(f);
};
boolean uphysfslayer_pfsFlush(PFSFile f)
{
    return PHYSFS_flush(f);
};
boolean uphysfslayer_pfsClose(PFSFile f)
{
    return PHYSFS_close(f);
};
boolean uphysfslayer_pfsExists(string255 fname)
{
    return PHYSFS_exists(uutils_Str2PChar(fname));
};
boolean uphysfslayer_pfsMakeDir(string255 path)
{
    return PHYSFS_mkdir(uutils_Str2PChar(path));
};
PPChar uphysfslayer_pfsEnumerateFiles(string255 dir)
{
    return PHYSFS_enumerateFiles(uutils_Str2PChar(dir));
};
void uphysfslayer_pfsFreeList(PPChar list)
{
    PHYSFS_freeList(list);
};
void uphysfslayer_pfsReadLn(PFSFile f,string255 (*s))
{
    char c;
    (*s).s[0] = 0x0;
    while((uphysfslayer_PHYSFS_readBytes(f, &(c), 1) == 1) && (c != 0xa))
    {
        if((c != 0xd) && ((*s).s[0] < 0xff))
        {
            ++(*s).s[0];
            (*s).s[((Byte)(*s).s[0])] = c;
        }
    }
};
void uphysfslayer_pfsReadLnA(PFSFile f,astring (*s))
{
    char c;
    string255 b;
    (*s) = fpcrtl_str2astr(__str0);
    b.s[0] = 0x0;
    while((uphysfslayer_PHYSFS_readBytes(f, &(c), 1) == 1) && (c != 0xa))
    {
        if(c != 0xd)
        {
            ++b.s[0];
            b.s[((Byte)b.s[0])] = c;
            if(b.s[0] == 0xff)
            {
                (*s) = _strconcatA((*s), fpcrtl_str2astr(b));
                b.s[0] = 0x0;
            }
        }
    }
    (*s) = _strconcatA((*s), fpcrtl_str2astr(b));
};
void uphysfslayer_pfsWriteLn(PFSFile f,string255 s)
{
    char c;
    c = 0xa;
    PHYSFS_writeBytes(f, &(s.s[1]), ((Byte)s.s[0]));
    PHYSFS_writeBytes(f, &(c), 1);
};
void uphysfslayer_pfsWriteRaw(PFSFile f,PChar s,QWord len)
{
    PHYSFS_writeBytes(f, s, len);
};
Int64 uphysfslayer_pfsBlockRead(PFSFile f,pointer buf,Int64 size)
{
    Int64 pfsblockread_result;
    Int64 r;
    r = uphysfslayer_PHYSFS_readBytes(f, buf, size);
    if(r <= 0)
    {
        pfsblockread_result = 0;
    }
    else
    {
        pfsblockread_result = r;
    }
    return pfsblockread_result;
};
void uphysfslayer_pfsMount(PChar path,PChar mountpoint)
{
    PHYSFS_mount(path, mountpoint, false);
};
void uphysfslayer_pfsMountAtRoot(PChar path)
{
    uphysfslayer_pfsMount(path, fpcrtl__pchar(__str1));
};
void uphysfslayer_initModule(PChar localPrefix,PChar userPrefix)
{
    LongInt i;
    string255 cPhysfsId;
    PChar fp;
    cPhysfsId = _strconcat(fpcrtl_pchar2str(fpcrtl_GetCurrentDir()), __str2);
    i = PHYSFS_init(uutils_Str2PChar(cPhysfsId));
    {i = 0;
     LongInt i__end__ = 1;
     if (i <= i__end__) do {
                               fp = cFontsPaths[i];
                               if(fp != NULL)
                               {
                                   uphysfslayer_pfsMount(fp, "/Fonts");
                               }
                           } while(i++ != i__end__);}
    uphysfslayer_pfsMountAtRoot(localPrefix);
    uphysfslayer_pfsMount(userPrefix, fpcrtl__pchar(__str3));
    uphysfslayer_pfsMakeDir(__str4);
    uphysfslayer_pfsMakeDir(__str5);
    uphysfslayer_pfsMountAtRoot(uutils_Str2PChar(_strconcat(fpcrtl_pchar2str(userPrefix), __str6)));
    PHYSFS_setWriteDir(userPrefix);
    hedgewarsMountPackages();
    uphysfslayer_pfsMountAtRoot(userPrefix);
    if(cTestLua)
    {
        uphysfslayer_pfsMountAtRoot(uutils_Str2PChar(uutils_ExtractFileDir(cScriptName)));
        cScriptName = uutils_ExtractFileName(cScriptName);
    }
};
void uphysfslayer_freeModule()
{
    PHYSFS_deinit();
};
