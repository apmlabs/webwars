#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "LuaPas.h"
static const string255 PhysfsLibName = STRINIT("libphysfs");
static const string255 PhyslayerLibName = STRINIT("libphyslayer");
void uphysfslayer_initModule(PChar localPrefix,PChar userPrefix);
void uphysfslayer_freeModule();
typedef pointer PFSFile;
PSDL_RWops uphysfslayer_rwopsOpenRead(string255 fname);
PSDL_RWops uphysfslayer_rwopsOpenWrite(string255 fname);
PFSFile uphysfslayer_pfsOpenRead(string255 fname);
PFSFile uphysfslayer_pfsOpenWrite(string255 fname);
boolean uphysfslayer_pfsFlush(PFSFile f);
boolean uphysfslayer_pfsClose(PFSFile f);
void uphysfslayer_pfsReadLn(PFSFile f,string255 (*s));
void uphysfslayer_pfsReadLnA(PFSFile f,astring (*s));
void uphysfslayer_pfsWriteLn(PFSFile f,string255 s);
void uphysfslayer_pfsWriteRaw(PFSFile f,PChar s,QWord len);
Int64 uphysfslayer_pfsBlockRead(PFSFile f,pointer buf,Int64 size);
boolean uphysfslayer_pfsEOF(PFSFile f);
boolean uphysfslayer_pfsExists(string255 fname);
boolean uphysfslayer_pfsMakeDir(string255 path);
PChar physfsReader(Plua_State L,PFSFile f,Psize_t sz);
void physfsReaderSetBuffer(pointer buf);
void hedgewarsMountPackage(PChar filename);

