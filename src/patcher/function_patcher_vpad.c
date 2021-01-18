#include "../utils/function_patcher.h"
#include "function_patcher_vpad.h"
#include "../utils/logger.h"

int drcSwapped __attribute__((section(".data"))) = FALSE;

declareFunctionHook(int, VPADRead, int chan, VPADData *buffer, u32 buffer_size, s32 *error) {
    int result = real_VPADRead(chan, buffer, buffer_size, error);
	if(result <= 0) return result;

    int swap_button = VPAD_BUTTON_L | VPAD_BUTTON_MINUS;
    if((buffer[0].btns_h & swap_button) == swap_button) {
        if(buffer[0].btns_d & swap_button) {
            drcSwapped = !drcSwapped; // toggle drcSwapped
        }
    }

    return result;
}

FunctionHook method_hooks_vpad[] __attribute__((section(".data"))) = {
	makeFunctionHook(VPADRead, LIB_VPAD, STATIC_FUNCTION)
};

u32 method_hooks_size_vpad __attribute__((section(".data"))) = sizeof(method_hooks_vpad) / sizeof(FunctionHook);

volatile unsigned int method_calls_vpad[sizeof(method_hooks_vpad) / sizeof(FunctionHook) *
									   FUNCTION_PATCHER_METHOD_STORE_SIZE] __attribute__((section(".data")));