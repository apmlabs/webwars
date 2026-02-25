#pragma once

#include "pas2c.h"

extern boolean isDeveloperMode;
extern boolean isExternalSource;
typedef void(*ucommands_TCommandHandler)(string255 (*params));
void ucommands_initModule();
void ucommands_freeModule();
void ucommands_RegisterVariable_4(string255 Name,ucommands_TCommandHandler ucommands_p,boolean Trusted,boolean Rand);
void ucommands_RegisterVariable_3(string255 Name,ucommands_TCommandHandler ucommands_p,boolean Trusted);
void ucommands_ParseCommand_2(string255 CmdStr,boolean TrustedSource);
void ucommands_ParseCommand_3(string255 CmdStr,boolean TrustedSource,boolean ExternalSource);
void ucommands_ParseTeamCommand(string255 s);
void ucommands_StopMessages(LongWord Message);

