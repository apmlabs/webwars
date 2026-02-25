#pragma once

#include "pas2c.h"

void argparsers_GetParams();
extern LongInt operatingsystem_parameter_argc;
extern pointer operatingsystem_parameter_argv;
extern pointer operatingsystem_parameter_envp;
LongInt argparsers_ParamCount();
string255 argparsers_ParamStr(LongInt i);

