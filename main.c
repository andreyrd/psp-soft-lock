#include <pspkernel.h>
#include <pspuser.h>
#include <pspthreadman.h>
#include <pspmodulemgr.h>
#include <pspctrl.h>

PSP_MODULE_INFO("Locker", 0x1000, 0, 1);
PSP_HEAP_SIZE_KB(1000);

int main_thread(SceSize args, void *argp){
    sceKernelDelayThread(5000000);

    int locked = 0;
    
    SceCtrlData ctrls;
    
    while(1){
        if(locked){
            sceCtrlReadBufferPositive(&ctrls, 1);
        } else {
            sceCtrlPeekBufferPositive(&ctrls, 1);
            sceKernelDelayThread(1000);
        }

        if(ctrls.Buttons & PSP_CTRL_L & PSP_CTRL_R & PSP_CTRL_SQUARE){
            locked = !locked;
            while(ctrls.Buttons & PSP_CTRL_L & PSP_CTRL_R & PSP_CTRL_SQUARE){
                sceCtrlPeekBufferPositive(&ctrls, 1);
            }
        }
    }

    return 0;
}

int module_start(SceSize args, void *argp){
    int thid;

    thid = sceKernelCreateThread("Locker", main_thread, 0x18, 0x1000, 0, NULL);
    if(thid >= 0) sceKernelStartThread(thid, args, argp);

    return 0;
}
