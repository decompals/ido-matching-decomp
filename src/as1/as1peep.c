#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "common.h"
#include "sys/inst.h"

//#pragma .s")iclude "common.h".s")iclude "malloc.h"

typedef struct UnkStruct_10023CF8_s {
    /* 0x0 */ short unk0;                             /* inferred */
    /* 0x2 */ short unk2;                             /* inferred */
    /* 0x4 */ int unk4;                             /* inferred */
} UnkStruct_10023CF8;                               /* size = 0x8 */

typedef struct UnkStruct_ctnt_s {
    /* 0x0 */ unsigned int unk0;                             /* inferred */
    /* 0x4 */ unsigned short unk4;                             /* inferred */
    /* 0x6 */ unsigned short unk6;                             /* inferred */
} UnkStruct_ctnt;                                   /* size = 0x8 */
static unsigned int B_10023CF0;
static unsigned int B_10023CF4;
static UnkStruct_10023CF8* B_10023CF8; // n_memory
extern UnkStruct_ctnt* ctnt;
extern void* imm_psym;

void xfree(void* ptr);

void func_004161F0(void) {
    void* a0;

    B_10023CF0 = 0;
    B_10023CF4 = 0;
    ctnt = recalloc(ctnt, 0, 0x280);
    a0 = B_10023CF8;
    if (a0 != 0) {
        xfree(a0);
    }
    B_10023CF8 = 0;
    imm_psym = recalloc(imm_psym, 0, 0x140);
}

void func_00416294(void) {
    int temp_v0;

    temp_v0 = B_10023CF4;
    B_10023CF4 += 0x32;
    ctnt = recalloc(ctnt, (temp_v0 * 8) + 0x280, (B_10023CF4 * 8) + 0x280);
    B_10023CF8 = recalloc(B_10023CF8, (temp_v0 * 8), B_10023CF4 * 8);
    imm_psym = recalloc(imm_psym, (temp_v0 * 4) + 0x140, (B_10023CF4 * 4) + 0x140);
}

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00416364.s")

int get_mem_reg(int arg0, short arg1, int arg2) {
    short var_a1;
    int temp_a0;
    int temp_a3;
    unsigned int i;
    int v0;

    for (i = 0; i < B_10023CF0; i++) {
        if ((arg0 == B_10023CF8[i].unk2) && (arg2 == B_10023CF8[i].unk4) && (arg1 == B_10023CF8[i].unk0)) {
            return i + 0x50;
        }
    }
    if (B_10023CF0 == B_10023CF4) {
        func_00416294();
    }
    i = B_10023CF0;
    B_10023CF0++;
    B_10023CF8[i].unk0 = arg1;
    B_10023CF8[i].unk4 = arg2;
    B_10023CF8[i].unk2 = arg0;
    return i + 0x50;
}

// find_def_reg
int func_00416670(unsigned int arg0) {
    if (ctnt[arg0].unk0 == 3) {
        return ctnt[arg0].unk6;
    }
    if ((arg0 >= 0x20U) && (arg0 < 0x40U) && (arg0 & 1)) {
        if ((ctnt[arg0 - 1].unk0 == 3) && (fp32regs == 0) && (ctnt[arg0 - 1].unk4 == 3)) {
            return ctnt[arg0 - 1].unk6 + 1;
        }
    }
    return -1;
}


// find_def_mem
unsigned int func_00416710(int arg0, short arg1, int arg2, int arg3) {
    int temp_a0;
    unsigned int i;

    for (i = 0; i < 0x50; i++) {
        if ((ctnt[i].unk0 == 4) && (arg3 == ctnt[i].unk4)) {
            temp_a0 = ctnt[i].unk6 - 0x50;
            if ((ctnt[temp_a0].unk0 != 2) && (ctnt[temp_a0].unk0 != 1)) {
                if ((arg0 == B_10023CF8[temp_a0].unk2) && (arg1 == B_10023CF8[temp_a0].unk0) &&
                    (arg2 == B_10023CF8[temp_a0].unk4)) {
                    return i;
                }
            }
        }
    }

    for (i = 0x50; i < B_10023CF0 + 0x50; i++) {
        if ((ctnt[i].unk0 != 0) && (arg3 == ctnt[i].unk4)) {
            if ((arg0 == B_10023CF8[i - 0x50].unk2) && (arg1 == B_10023CF8[i - 0x50].unk0) && (arg2 == B_10023CF8[i - 0x50].unk4)) {
                return i;
            }
        }
    }

    return -1;
}


//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00416880.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00416A08.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00416B30.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00416BDC.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00416C60.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00416CC4.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/change_bb.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00416FE4.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00417254.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00417844.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00417ACC.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00417D3C.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00417DC0.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_004180DC.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/redundant.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00418F08.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00418FA8.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/defined_in_between.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_004195F0.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_004196D4.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_004198CC.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00419AB4.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00419CC4.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00419E14.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_00419FE4.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_0041A4BC.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_0041AB40.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_0041AC0C.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_0041BB98.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_0041BBA4.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_0041C08C.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_0041C0C8.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/func_0041C354.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/do_passI_opt.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/as1peep/do_passII_opt.s")
