/*
* @file: as1peep.c
*
*/
#include "stdio.h"
#include "as1/types.h"
#include "as1/protos.h"

static s32 B_10023CF0;
static s32 B_10023CF4;
static s32 B_10023CF8;
extern s32 ctnt;
extern s32 imm_psym;

void func_004161F0(void) {
    s32 x;
    B_10023CF0 = 0;
    B_10023CF4 = 0;
    ctnt = recalloc(ctnt, 0, 0x280);
    x = B_10023CF8;
    if (x != 0) {
        xfree(x);
    }
    B_10023CF8 = 0;
    imm_psym = recalloc(imm_psym, 0, 0x140);
}

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416294.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416364.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/get_mem_reg.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416670.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416710.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416880.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416A08.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416B30.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416BDC.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416C60.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416CC4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/change_bb.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00416FE4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00417254.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00417844.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00417ACC.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00417D3C.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00417DC0.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_004180DC.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/redundant.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00418F08.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00418FA8.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/defined_in_between.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_004195F0.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_004196D4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_004198CC.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00419AB4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00419CC4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00419E14.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00419FE4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0041A4BC.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0041AB40.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0041AC0C.s")

int func_0041BB98(int arg0) {
    return 0;
}

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0041BBA4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0041C08C.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0041C0C8.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0041C354.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/do_passI_opt.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/do_passII_opt.s")
