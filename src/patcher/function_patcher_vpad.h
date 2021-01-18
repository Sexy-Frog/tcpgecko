#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../utils/function_patcher.h"

extern int drcSwapped; 

extern FunctionHook method_hooks_vpad[];

extern u32 method_hooks_size_vpad;

extern volatile unsigned int method_calls_vpad[];

#ifdef __cplusplus
}
#endif