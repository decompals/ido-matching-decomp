/*
* @file: reorganize.c
*
*/

#include "stdio.h"
#include "stdlib.h"
#include "as1/types.h"

#pragma GLOBAL_ASM("asm/7.1/functions/as1/reorganize_init.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042D240.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042D29C.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042D36C.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042D408.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042D4AC.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042D6BC.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042DBD4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042E028.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042E238.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042E4F4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042E7D0.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042EA7C.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042ECCC.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042EE14.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042EF60.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_0042F068.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_004313D8.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00431AF4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00431E78.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00431FB4.s")

#ifdef GLOBAL_ASM_FILE
#pragma GLOBAL_ASM(
.section .rodata
glabel STR_1000E4D8
/* 09E4D8 1000E4D8 */ .asciz "unexpected opcode %s\n"
                      .balign 4

glabel STR_1000E4F0
/* 09E4F0 1000E4F0 */ .asciz "false"
                      .balign 4

glabel STR_1000E4F8
/* 09E4F8 1000E4F8 */ .asciz "reorganize.c"
                      .balign 4

glabel STR_1000E508
/* 09E508 1000E508 */ .asciz "false"
                      .balign 4

glabel STR_1000E510
/* 09E510 1000E510 */ .asciz "reorganize.c"
                      .balign 4

glabel STR_1000E520
/* 09E520 1000E520 */ .asciz "unexpected opcode %s\n"
                      .balign 4

.section .late_rodata

.late_rodata_alignment 4

glabel jtbl_1000EBFC
/* 09EBFC 1000EBFC F04072E8 */ .gpword .L00432098
/* 09EC00 1000EC00 F0407344 */ .gpword .L004320F4
/* 09EC04 1000EC04 F0407378 */ .gpword .L00432128
/* 09EC08 1000EC08 F0407378 */ .gpword .L00432128
/* 09EC0C 1000EC0C F0407378 */ .gpword .L00432128
/* 09EC10 1000EC10 F0407378 */ .gpword .L00432128
/* 09EC14 1000EC14 F0407378 */ .gpword .L00432128
/* 09EC18 1000EC18 F0407378 */ .gpword .L00432128
/* 09EC1C 1000EC1C F04073FC */ .gpword .L004321AC
/* 09EC20 1000EC20 F04073FC */ .gpword .L004321AC
/* 09EC24 1000EC24 F04073FC */ .gpword .L004321AC
/* 09EC28 1000EC28 F04073FC */ .gpword .L004321AC
/* 09EC2C 1000EC2C F0407394 */ .gpword .L00432144
/* 09EC30 1000EC30 F0407394 */ .gpword .L00432144
/* 09EC34 1000EC34 F0407394 */ .gpword .L00432144
/* 09EC38 1000EC38 F04073C8 */ .gpword .L00432178
/* 09EC3C 1000EC3C F040744C */ .gpword .L004321FC
/* 09EC40 1000EC40 F04074F4 */ .gpword .L004322A4
/* 09EC44 1000EC44 F040744C */ .gpword .L004321FC
/* 09EC48 1000EC48 F04074A8 */ .gpword .L00432258
/* 09EC4C 1000EC4C F0407378 */ .gpword .L00432128
/* 09EC50 1000EC50 F0407378 */ .gpword .L00432128
/* 09EC54 1000EC54 F0407378 */ .gpword .L00432128
/* 09EC58 1000EC58 F0407378 */ .gpword .L00432128
/* 09EC5C 1000EC5C F04073FC */ .gpword .L004321AC
/* 09EC60 1000EC60 F04073FC */ .gpword .L004321AC
/* 09EC64 1000EC64 F0407CEC */ .gpword .L00432A9C
/* 09EC68 1000EC68 F0407CEC */ .gpword .L00432A9C
/* 09EC6C 1000EC6C F0407D08 */ .gpword .L00432AB8
/* 09EC70 1000EC70 F0407D08 */ .gpword .L00432AB8
/* 09EC74 1000EC74 F0407D08 */ .gpword .L00432AB8
/* 09EC78 1000EC78 F0407D08 */ .gpword .L00432AB8
/* 09EC7C 1000EC7C F0407CEC */ .gpword .L00432A9C
/* 09EC80 1000EC80 F0407CEC */ .gpword .L00432A9C
/* 09EC84 1000EC84 F0407CEC */ .gpword .L00432A9C
/* 09EC88 1000EC88 F0407CEC */ .gpword .L00432A9C
/* 09EC8C 1000EC8C F0407CEC */ .gpword .L00432A9C
/* 09EC90 1000EC90 F0407CEC */ .gpword .L00432A9C
/* 09EC94 1000EC94 F0407CEC */ .gpword .L00432A9C
/* 09EC98 1000EC98 F0407CEC */ .gpword .L00432A9C
/* 09EC9C 1000EC9C F0407CEC */ .gpword .L00432A9C
/* 09ECA0 1000ECA0 F0407CEC */ .gpword .L00432A9C
/* 09ECA4 1000ECA4 F0407CEC */ .gpword .L00432A9C
/* 09ECA8 1000ECA8 F0407CEC */ .gpword .L00432A9C
/* 09ECAC 1000ECAC F0407CEC */ .gpword .L00432A9C
/* 09ECB0 1000ECB0 F0407CEC */ .gpword .L00432A9C
/* 09ECB4 1000ECB4 F0407CEC */ .gpword .L00432A9C
/* 09ECB8 1000ECB8 F0407430 */ .gpword .L004321E0
/* 09ECBC 1000ECBC F0407CEC */ .gpword .L00432A9C
/* 09ECC0 1000ECC0 F0407CEC */ .gpword .L00432A9C
/* 09ECC4 1000ECC4 F0407CEC */ .gpword .L00432A9C
/* 09ECC8 1000ECC8 F0407CEC */ .gpword .L00432A9C
/* 09ECCC 1000ECCC F0407CEC */ .gpword .L00432A9C
/* 09ECD0 1000ECD0 F0407CEC */ .gpword .L00432A9C
/* 09ECD4 1000ECD4 F0407CEC */ .gpword .L00432A9C
/* 09ECD8 1000ECD8 F0407CEC */ .gpword .L00432A9C
/* 09ECDC 1000ECDC F0407CEC */ .gpword .L00432A9C
/* 09ECE0 1000ECE0 F0407CEC */ .gpword .L00432A9C
/* 09ECE4 1000ECE4 F0407CEC */ .gpword .L00432A9C
/* 09ECE8 1000ECE8 F0407CEC */ .gpword .L00432A9C
/* 09ECEC 1000ECEC F0407CEC */ .gpword .L00432A9C
/* 09ECF0 1000ECF0 F0407CEC */ .gpword .L00432A9C
/* 09ECF4 1000ECF4 F0407CEC */ .gpword .L00432A9C
/* 09ECF8 1000ECF8 F0407CEC */ .gpword .L00432A9C

glabel jtbl_1000ECFC
/* 09ECFC 1000ECFC F04073C8 */ .gpword .L00432178
/* 09ED00 1000ED00 F04073FC */ .gpword .L004321AC
/* 09ED04 1000ED04 F04073C8 */ .gpword .L00432178
/* 09ED08 1000ED08 F04073C8 */ .gpword .L00432178
/* 09ED0C 1000ED0C F04073C8 */ .gpword .L00432178
/* 09ED10 1000ED10 F040730C */ .gpword .L004320BC
/* 09ED14 1000ED14 F04073C8 */ .gpword .L00432178
/* 09ED18 1000ED18 F04073C8 */ .gpword .L00432178
/* 09ED1C 1000ED1C F0407378 */ .gpword .L00432128
/* 09ED20 1000ED20 F0407378 */ .gpword .L00432128
/* 09ED24 1000ED24 F04073FC */ .gpword .L004321AC
/* 09ED28 1000ED28 F04073FC */ .gpword .L004321AC
/* 09ED2C 1000ED2C F0407D34 */ .gpword .L00432AE4
/* 09ED30 1000ED30 F0407D34 */ .gpword .L00432AE4
/* 09ED34 1000ED34 F040730C */ .gpword .L004320BC
/* 09ED38 1000ED38 F0407D34 */ .gpword .L00432AE4
/* 09ED3C 1000ED3C F0407D34 */ .gpword .L00432AE4
/* 09ED40 1000ED40 F0407D34 */ .gpword .L00432AE4
/* 09ED44 1000ED44 F0407D34 */ .gpword .L00432AE4
/* 09ED48 1000ED48 F0407D34 */ .gpword .L00432AE4
/* 09ED4C 1000ED4C F04073C8 */ .gpword .L00432178
/* 09ED50 1000ED50 F040730C */ .gpword .L004320BC
/* 09ED54 1000ED54 F04073C8 */ .gpword .L00432178
/* 09ED58 1000ED58 F04073C8 */ .gpword .L00432178
/* 09ED5C 1000ED5C F0407D34 */ .gpword .L00432AE4
/* 09ED60 1000ED60 F0407D34 */ .gpword .L00432AE4
/* 09ED64 1000ED64 F0407D34 */ .gpword .L00432AE4
/* 09ED68 1000ED68 F0407D34 */ .gpword .L00432AE4
/* 09ED6C 1000ED6C F0407D34 */ .gpword .L00432AE4
/* 09ED70 1000ED70 F0407D34 */ .gpword .L00432AE4
/* 09ED74 1000ED74 F0407D34 */ .gpword .L00432AE4
/* 09ED78 1000ED78 F0407D34 */ .gpword .L00432AE4
/* 09ED7C 1000ED7C F04073FC */ .gpword .L004321AC
/* 09ED80 1000ED80 F04073FC */ .gpword .L004321AC
/* 09ED84 1000ED84 F04073FC */ .gpword .L004321AC
/* 09ED88 1000ED88 F04073FC */ .gpword .L004321AC
/* 09ED8C 1000ED8C F0407394 */ .gpword .L00432144
/* 09ED90 1000ED90 F0407394 */ .gpword .L00432144
/* 09ED94 1000ED94 F0407394 */ .gpword .L00432144
/* 09ED98 1000ED98 F0407394 */ .gpword .L00432144
/* 09ED9C 1000ED9C F040730C */ .gpword .L004320BC
/* 09EDA0 1000EDA0 F040730C */ .gpword .L004320BC
/* 09EDA4 1000EDA4 F04073FC */ .gpword .L004321AC
/* 09EDA8 1000EDA8 F04073FC */ .gpword .L004321AC
/* 09EDAC 1000EDAC F04073FC */ .gpword .L004321AC
/* 09EDB0 1000EDB0 F04073FC */ .gpword .L004321AC
/* 09EDB4 1000EDB4 F04073FC */ .gpword .L004321AC
/* 09EDB8 1000EDB8 F04073FC */ .gpword .L004321AC
/* 09EDBC 1000EDBC F04073FC */ .gpword .L004321AC
/* 09EDC0 1000EDC0 F04073FC */ .gpword .L004321AC
/* 09EDC4 1000EDC4 F04073FC */ .gpword .L004321AC
/* 09EDC8 1000EDC8 F04073FC */ .gpword .L004321AC
/* 09EDCC 1000EDCC F04073FC */ .gpword .L004321AC
/* 09EDD0 1000EDD0 F040730C */ .gpword .L004320BC
/* 09EDD4 1000EDD4 F04073FC */ .gpword .L004321AC
/* 09EDD8 1000EDD8 F040730C */ .gpword .L004320BC
/* 09EDDC 1000EDDC F04073C8 */ .gpword .L00432178
/* 09EDE0 1000EDE0 F040730C */ .gpword .L004320BC
/* 09EDE4 1000EDE4 F04073C8 */ .gpword .L00432178
/* 09EDE8 1000EDE8 F04073C8 */ .gpword .L00432178
/* 09EDEC 1000EDEC F04073C8 */ .gpword .L00432178
/* 09EDF0 1000EDF0 F040730C */ .gpword .L004320BC
/* 09EDF4 1000EDF4 F04073C8 */ .gpword .L00432178
/* 09EDF8 1000EDF8 F04073C8 */ .gpword .L00432178

glabel jtbl_1000EDFC
/* 09EDFC 1000EDFC F04073FC */ .gpword .L004321AC
/* 09EE00 1000EE00 F04073FC */ .gpword .L004321AC
/* 09EE04 1000EE04 F04073FC */ .gpword .L004321AC
/* 09EE08 1000EE08 F04073FC */ .gpword .L004321AC
/* 09EE0C 1000EE0C F04073FC */ .gpword .L004321AC
/* 09EE10 1000EE10 F0407378 */ .gpword .L00432128
/* 09EE14 1000EE14 F04073FC */ .gpword .L004321AC

glabel jtbl_1000EE18
/* 09EE18 1000EE18 F0407CEC */ .gpword .L00432A9C
/* 09EE1C 1000EE1C F0407CEC */ .gpword .L00432A9C
/* 09EE20 1000EE20 F0407CEC */ .gpword .L00432A9C
/* 09EE24 1000EE24 F0407480 */ .gpword .L00432230
/* 09EE28 1000EE28 F0407CEC */ .gpword .L00432A9C
/* 09EE2C 1000EE2C F0407CEC */ .gpword .L00432A9C
/* 09EE30 1000EE30 F0407CEC */ .gpword .L00432A9C
/* 09EE34 1000EE34 F0407480 */ .gpword .L00432230
/* 09EE38 1000EE38 F0407378 */ .gpword .L00432128

glabel jtbl_1000EE3C
/* 09EE3C 1000EE3C F0407CEC */ .gpword .L00432A9C
/* 09EE40 1000EE40 F0407CEC */ .gpword .L00432A9C
/* 09EE44 1000EE44 F04074D8 */ .gpword .L00432288
/* 09EE48 1000EE48 F04074D8 */ .gpword .L00432288
/* 09EE4C 1000EE4C F04074D8 */ .gpword .L00432288
/* 09EE50 1000EE50 F04074D8 */ .gpword .L00432288
/* 09EE54 1000EE54 F04074D8 */ .gpword .L00432288
/* 09EE58 1000EE58 F04074D8 */ .gpword .L00432288
/* 09EE5C 1000EE5C F0407CEC */ .gpword .L00432A9C
/* 09EE60 1000EE60 F0407CEC */ .gpword .L00432A9C
/* 09EE64 1000EE64 F04074D8 */ .gpword .L00432288
/* 09EE68 1000EE68 F04074D8 */ .gpword .L00432288
/* 09EE6C 1000EE6C F04074D8 */ .gpword .L00432288
/* 09EE70 1000EE70 F04074D8 */ .gpword .L00432288
/* 09EE74 1000EE74 F04074D8 */ .gpword .L00432288
/* 09EE78 1000EE78 F0407CEC */ .gpword .L00432A9C

glabel jtbl_1000EE7C
/* 09EE7C 1000EE7C F0407CEC */ .gpword .L00432A9C
/* 09EE80 1000EE80 F0407CEC */ .gpword .L00432A9C
/* 09EE84 1000EE84 F0407CEC */ .gpword .L00432A9C
/* 09EE88 1000EE88 F0407CC4 */ .gpword .L00432A74
/* 09EE8C 1000EE8C F0407CEC */ .gpword .L00432A9C
/* 09EE90 1000EE90 F0407CEC */ .gpword .L00432A9C
/* 09EE94 1000EE94 F0407CEC */ .gpword .L00432A9C
/* 09EE98 1000EE98 F0407CC4 */ .gpword .L00432A74
/* 09EE9C 1000EE9C F0407378 */ .gpword .L00432128
/* 09EEA0 1000EEA0 F0407CC4 */ .gpword .L00432A74
/* 09EEA4 1000EEA4 F0407CC4 */ .gpword .L00432A74
/* 09EEA8 1000EEA8 F0407CC4 */ .gpword .L00432A74
/* 09EEAC 1000EEAC F0407CC4 */ .gpword .L00432A74
/* 09EEB0 1000EEB0 F0407CC4 */ .gpword .L00432A74
/* 09EEB4 1000EEB4 F0407CC4 */ .gpword .L00432A74
/* 09EEB8 1000EEB8 F0407CC4 */ .gpword .L00432A74
/* 09EEBC 1000EEBC F0407528 */ .gpword .L004322D8
/* 09EEC0 1000EEC0 F0407528 */ .gpword .L004322D8
/* 09EEC4 1000EEC4 F0407528 */ .gpword .L004322D8
/* 09EEC8 1000EEC8 F0407CC4 */ .gpword .L00432A74
/* 09EECC 1000EECC F0407528 */ .gpword .L004322D8
/* 09EED0 1000EED0 F0407528 */ .gpword .L004322D8

glabel jtbl_1000EED4
/* 09EED4 1000EED4 F04075A0 */ .gpword .L00432350
/* 09EED8 1000EED8 F0407658 */ .gpword .L00432408
/* 09EEDC 1000EEDC F04076C8 */ .gpword .L00432478
/* 09EEE0 1000EEE0 F0407CA0 */ .gpword .L00432A50
/* 09EEE4 1000EEE4 F0407AA0 */ .gpword .L00432850
/* 09EEE8 1000EEE8 F0407AE4 */ .gpword .L00432894
/* 09EEEC 1000EEEC F0407B38 */ .gpword .L004328E8
/* 09EEF0 1000EEF0 F0407BA8 */ .gpword .L00432958
/* 09EEF4 1000EEF4 F0407C30 */ .gpword .L004329E0
/* 09EEF8 1000EEF8 F0407C30 */ .gpword .L004329E0
/* 09EEFC 1000EEFC F0407C30 */ .gpword .L004329E0

glabel jtbl_1000EF00
/* 09EF00 1000EF00 F0407844 */ .gpword .L004325F4
/* 09EF04 1000EF04 F0407988 */ .gpword .L00432738
/* 09EF08 1000EF08 F0407988 */ .gpword .L00432738
/* 09EF0C 1000EF0C F0407988 */ .gpword .L00432738
/* 09EF10 1000EF10 F0407988 */ .gpword .L00432738
/* 09EF14 1000EF14 F0407958 */ .gpword .L00432708
/* 09EF18 1000EF18 F0407958 */ .gpword .L00432708
/* 09EF1C 1000EF1C F0407958 */ .gpword .L00432708
/* 09EF20 1000EF20 F0407958 */ .gpword .L00432708
/* 09EF24 1000EF24 F0407958 */ .gpword .L00432708
/* 09EF28 1000EF28 F0407958 */ .gpword .L00432708
/* 09EF2C 1000EF2C F0407958 */ .gpword .L00432708
/* 09EF30 1000EF30 F0407958 */ .gpword .L00432708
/* 09EF34 1000EF34 F0407988 */ .gpword .L00432738
/* 09EF38 1000EF38 F0407988 */ .gpword .L00432738
/* 09EF3C 1000EF3C F0407988 */ .gpword .L00432738
/* 09EF40 1000EF40 F0407988 */ .gpword .L00432738
/* 09EF44 1000EF44 F0407988 */ .gpword .L00432738
/* 09EF48 1000EF48 F0407988 */ .gpword .L00432738
/* 09EF4C 1000EF4C F0407988 */ .gpword .L00432738
/* 09EF50 1000EF50 F0407988 */ .gpword .L00432738
/* 09EF54 1000EF54 F0407988 */ .gpword .L00432738
/* 09EF58 1000EF58 F0407988 */ .gpword .L00432738
/* 09EF5C 1000EF5C F0407988 */ .gpword .L00432738
/* 09EF60 1000EF60 F0407988 */ .gpword .L00432738
/* 09EF64 1000EF64 F0407988 */ .gpword .L00432738
/* 09EF68 1000EF68 F0407988 */ .gpword .L00432738
/* 09EF6C 1000EF6C F0407988 */ .gpword .L00432738
/* 09EF70 1000EF70 F0407988 */ .gpword .L00432738
/* 09EF74 1000EF74 F040788C */ .gpword .L0043263C
/* 09EF78 1000EF78 F04078F4 */ .gpword .L004326A4
/* 09EF7C 1000EF7C F0407988 */ .gpword .L00432738
/* 09EF80 1000EF80 F0407988 */ .gpword .L00432738
/* 09EF84 1000EF84 F0407958 */ .gpword .L00432708
/* 09EF88 1000EF88 F0407958 */ .gpword .L00432708


.section .text
/* Generated by spimdisasm 1.12.4 */

glabel start_time # 261
/* 032030 00432030 3C1C0FC0 */  lui         $gp, %hi(_gp_disp)
/* 032034 00432034 279C8D80 */  addiu       $gp, $gp, %lo(_gp_disp)
# _gp_disp: 0xFBF8D80
/* 032038 00432038 0399E021 */  addu        $gp, $gp, $t9
/* 03203C 0043203C 27BDFFA0 */  addiu       $sp, $sp, -0x60
/* 032040 00432040 AFBF001C */  sw          $ra, 0x1C($sp)
/* 032044 00432044 AFBC0018 */  sw          $gp, 0x18($sp)
/* 032048 00432048 AFB00014 */  sw          $s0, 0x14($sp)
/* 03204C 0043204C 8CB80000 */  lw          $t8, 0x0($a1)
/* 032050 00432050 27AE005C */  addiu       $t6, $sp, 0x5C
/* 032054 00432054 ADD80000 */  sw          $t8, 0x0($t6)
/* 032058 00432058 94B0002E */  lhu         $s0, 0x2E($a1)
/* 03205C 0043205C 8FA2005C */  lw          $v0, 0x5C($sp)
/* 032060 00432060 0204082B */  sltu        $at, $s0, $a0
/* 032064 00432064 10200002 */  beqz        $at, .L00432070
/* 032068 00432068 00021682 */   srl        $v0, $v0, 26
/* 03206C 0043206C 00808025 */  move        $s0, $a0
.L00432070:
/* 032070 00432070 2C410040 */  sltiu       $at, $v0, 0x40
/* 032074 00432074 10200290 */  beqz        $at, .L00432AB8
/* 032078 00432078 00000000 */   nop
/* 03207C 0043207C 8F818044 */  lw          $at, %got(jtbl_1000EBFC)($gp)
/* 032080 00432080 0002C880 */  sll         $t9, $v0, 2
/* 032084 00432084 00390821 */  addu        $at, $at, $t9
/* 032088 00432088 8C39EBFC */  lw          $t9, %lo(jtbl_1000EBFC)($at)
/* 03208C 0043208C 033CC821 */  addu        $t9, $t9, $gp
/* 032090 00432090 03200008 */  jr          $t9
/* 032094 00432094 00000000 */   nop
.L00432098:
/* 032098 00432098 8FAA005C */  lw          $t2, 0x5C($sp)
/* 03209C 0043209C 8F818044 */  lw          $at, %got(jtbl_1000ECFC)($gp)
/* 0320A0 004320A0 314B003F */  andi        $t3, $t2, 0x3F
/* 0320A4 004320A4 000B5880 */  sll         $t3, $t3, 2
/* 0320A8 004320A8 002B0821 */  addu        $at, $at, $t3
/* 0320AC 004320AC 8C2BECFC */  lw          $t3, %lo(jtbl_1000ECFC)($at)
/* 0320B0 004320B0 017C5821 */  addu        $t3, $t3, $gp
/* 0320B4 004320B4 01600008 */  jr          $t3
/* 0320B8 004320B8 00000000 */   nop
.L004320BC:
/* 0320BC 004320BC 8FAC005C */  lw          $t4, 0x5C($sp)
/* 0320C0 004320C0 8F8F8A2C */  lw          $t7, %got(spec_name)($gp)
/* 0320C4 004320C4 8F998090 */  lw          $t9, %call16(fprintf)($gp)
/* 0320C8 004320C8 318D003F */  andi        $t5, $t4, 0x3F
/* 0320CC 004320CC 8F84805C */  lw          $a0, %got(__iob)($gp)
/* 0320D0 004320D0 8F858044 */  lw          $a1, %got(STR_1000E4D8)($gp)
/* 0320D4 004320D4 000D7080 */  sll         $t6, $t5, 2
/* 0320D8 004320D8 01CFC021 */  addu        $t8, $t6, $t7
/* 0320DC 004320DC 8F060000 */  lw          $a2, 0x0($t8)
/* 0320E0 004320E0 24840020 */  addiu       $a0, $a0, 0x20
/* 0320E4 004320E4 0320F809 */  jalr        $t9
/* 0320E8 004320E8 24A5E4D8 */   addiu      $a1, $a1, %lo(STR_1000E4D8)
/* 0320EC 004320EC 1000027D */  b           .L00432AE4
/* 0320F0 004320F0 8FBC0018 */   lw         $gp, 0x18($sp)
.L004320F4:
/* 0320F4 004320F4 97B9005C */  lhu         $t9, 0x5C($sp)
/* 0320F8 004320F8 332A001F */  andi        $t2, $t9, 0x1F
/* 0320FC 004320FC 254BFFF8 */  addiu       $t3, $t2, -0x8
/* 032100 00432100 2D610007 */  sltiu       $at, $t3, 0x7
/* 032104 00432104 10200008 */  beqz        $at, .L00432128
/* 032108 00432108 00000000 */   nop
/* 03210C 0043210C 8F818044 */  lw          $at, %got(jtbl_1000EDFC)($gp)
/* 032110 00432110 000B5880 */  sll         $t3, $t3, 2
/* 032114 00432114 002B0821 */  addu        $at, $at, $t3
/* 032118 00432118 8C2BEDFC */  lw          $t3, %lo(jtbl_1000EDFC)($at)
/* 03211C 0043211C 017C5821 */  addu        $t3, $t3, $gp
/* 032120 00432120 01600008 */  jr          $t3
/* 032124 00432124 00000000 */   nop
.L00432128:
/* 032128 00432128 8F82804C */  lw          $v0, %got(B_1002E8C4)($gp)
/* 03212C 0043212C 8C42E8C4 */  lw          $v0, %lo(B_1002E8C4)($v0)
/* 032130 00432130 0202082B */  sltu        $at, $s0, $v0
/* 032134 00432134 5020026C */  beql        $at, $zero, .L00432AE8
/* 032138 00432138 8FBF001C */   lw         $ra, 0x1C($sp)
/* 03213C 0043213C 10000269 */  b           .L00432AE4
/* 032140 00432140 00408025 */   move       $s0, $v0
.L00432144:
/* 032144 00432144 8F82804C */  lw          $v0, %got(B_1002E8B8)($gp)
/* 032148 00432148 8C42E8B8 */  lw          $v0, %lo(B_1002E8B8)($v0)
/* 03214C 0043214C 0202082B */  sltu        $at, $s0, $v0
/* 032150 00432150 10200002 */  beqz        $at, .L0043215C
/* 032154 00432154 00000000 */   nop
/* 032158 00432158 00408025 */  move        $s0, $v0
.L0043215C:
/* 03215C 0043215C 8F82804C */  lw          $v0, %got(B_1002E914)($gp)
/* 032160 00432160 8C42E914 */  lw          $v0, %lo(B_1002E914)($v0)
/* 032164 00432164 0202082B */  sltu        $at, $s0, $v0
/* 032168 00432168 5020025F */  beql        $at, $zero, .L00432AE8
/* 03216C 0043216C 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032170 00432170 1000025C */  b           .L00432AE4
/* 032174 00432174 00408025 */   move       $s0, $v0
.L00432178:
/* 032178 00432178 8F82804C */  lw          $v0, %got(B_1002E8BC)($gp)
/* 03217C 0043217C 8C42E8BC */  lw          $v0, %lo(B_1002E8BC)($v0)
/* 032180 00432180 0202082B */  sltu        $at, $s0, $v0
/* 032184 00432184 10200002 */  beqz        $at, .L00432190
/* 032188 00432188 00000000 */   nop
/* 03218C 0043218C 00408025 */  move        $s0, $v0
.L00432190:
/* 032190 00432190 8F82804C */  lw          $v0, %got(B_1002E914)($gp)
/* 032194 00432194 8C42E914 */  lw          $v0, %lo(B_1002E914)($v0)
/* 032198 00432198 0202082B */  sltu        $at, $s0, $v0
/* 03219C 0043219C 50200252 */  beql        $at, $zero, .L00432AE8
/* 0321A0 004321A0 8FBF001C */   lw         $ra, 0x1C($sp)
/* 0321A4 004321A4 1000024F */  b           .L00432AE4
/* 0321A8 004321A8 00408025 */   move       $s0, $v0
.L004321AC:
/* 0321AC 004321AC 8F82804C */  lw          $v0, %got(B_1002E8C0)($gp)
/* 0321B0 004321B0 8C42E8C0 */  lw          $v0, %lo(B_1002E8C0)($v0)
/* 0321B4 004321B4 0202082B */  sltu        $at, $s0, $v0
/* 0321B8 004321B8 10200002 */  beqz        $at, .L004321C4
/* 0321BC 004321BC 00000000 */   nop
/* 0321C0 004321C0 00408025 */  move        $s0, $v0
.L004321C4:
/* 0321C4 004321C4 8F82804C */  lw          $v0, %got(B_1002E914)($gp)
/* 0321C8 004321C8 8C42E914 */  lw          $v0, %lo(B_1002E914)($v0)
/* 0321CC 004321CC 0202082B */  sltu        $at, $s0, $v0
/* 0321D0 004321D0 50200245 */  beql        $at, $zero, .L00432AE8
/* 0321D4 004321D4 8FBF001C */   lw         $ra, 0x1C($sp)
/* 0321D8 004321D8 10000242 */  b           .L00432AE4
/* 0321DC 004321DC 00408025 */   move       $s0, $v0
.L004321E0:
/* 0321E0 004321E0 8F82804C */  lw          $v0, %got(B_1002E8D0)($gp)
/* 0321E4 004321E4 8C42E8D0 */  lw          $v0, %lo(B_1002E8D0)($v0)
/* 0321E8 004321E8 0202082B */  sltu        $at, $s0, $v0
/* 0321EC 004321EC 5020023E */  beql        $at, $zero, .L00432AE8
/* 0321F0 004321F0 8FBF001C */   lw         $ra, 0x1C($sp)
/* 0321F4 004321F4 1000023B */  b           .L00432AE4
/* 0321F8 004321F8 00408025 */   move       $s0, $v0
.L004321FC:
/* 0321FC 004321FC 8FAC005C */  lw          $t4, 0x5C($sp)
/* 032200 00432200 000C6980 */  sll         $t5, $t4, 6
/* 032204 00432204 000D76C2 */  srl         $t6, $t5, 27
/* 032208 00432208 2DC10009 */  sltiu       $at, $t6, 0x9
/* 03220C 0043220C 10200008 */  beqz        $at, .L00432230
/* 032210 00432210 00000000 */   nop
/* 032214 00432214 8F818044 */  lw          $at, %got(jtbl_1000EE18)($gp)
/* 032218 00432218 000E7080 */  sll         $t6, $t6, 2
/* 03221C 0043221C 002E0821 */  addu        $at, $at, $t6
/* 032220 00432220 8C2EEE18 */  lw          $t6, %lo(jtbl_1000EE18)($at)
/* 032224 00432224 01DC7021 */  addu        $t6, $t6, $gp
/* 032228 00432228 01C00008 */  jr          $t6
/* 03222C 0043222C 00000000 */   nop
.L00432230:
/* 032230 00432230 8F98804C */  lw          $t8, %got(B_1002E8D0)($gp)
/* 032234 00432234 00027880 */  sll         $t7, $v0, 2
/* 032238 00432238 2718E8D0 */  addiu       $t8, $t8, %lo(B_1002E8D0)
/* 03223C 0043223C 01F8C821 */  addu        $t9, $t7, $t8
/* 032240 00432240 8F23FFC0 */  lw          $v1, -0x40($t9)
/* 032244 00432244 0203082B */  sltu        $at, $s0, $v1
/* 032248 00432248 50200227 */  beql        $at, $zero, .L00432AE8
/* 03224C 0043224C 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032250 00432250 10000224 */  b           .L00432AE4
/* 032254 00432254 00608025 */   move       $s0, $v1
.L00432258:
/* 032258 00432258 8FAA005C */  lw          $t2, 0x5C($sp)
/* 03225C 0043225C 314B003F */  andi        $t3, $t2, 0x3F
/* 032260 00432260 2D610010 */  sltiu       $at, $t3, 0x10
/* 032264 00432264 10200008 */  beqz        $at, .L00432288
/* 032268 00432268 00000000 */   nop
/* 03226C 0043226C 8F818044 */  lw          $at, %got(jtbl_1000EE3C)($gp)
/* 032270 00432270 000B5880 */  sll         $t3, $t3, 2
/* 032274 00432274 002B0821 */  addu        $at, $at, $t3
/* 032278 00432278 8C2BEE3C */  lw          $t3, %lo(jtbl_1000EE3C)($at)
/* 03227C 0043227C 017C5821 */  addu        $t3, $t3, $gp
/* 032280 00432280 01600008 */  jr          $t3
/* 032284 00432284 00000000 */   nop
.L00432288:
/* 032288 00432288 8F82804C */  lw          $v0, %got(B_1002E8EC)($gp)
/* 03228C 0043228C 8C42E8EC */  lw          $v0, %lo(B_1002E8EC)($v0)
/* 032290 00432290 0202082B */  sltu        $at, $s0, $v0
/* 032294 00432294 50200214 */  beql        $at, $zero, .L00432AE8
/* 032298 00432298 8FBF001C */   lw         $ra, 0x1C($sp)
/* 03229C 0043229C 10000211 */  b           .L00432AE4
/* 0322A0 004322A0 00408025 */   move       $s0, $v0
.L004322A4:
/* 0322A4 004322A4 8FAC005C */  lw          $t4, 0x5C($sp)
/* 0322A8 004322A8 000C6980 */  sll         $t5, $t4, 6
/* 0322AC 004322AC 000D76C2 */  srl         $t6, $t5, 27
/* 0322B0 004322B0 2DC10016 */  sltiu       $at, $t6, 0x16
/* 0322B4 004322B4 102001EF */  beqz        $at, .L00432A74
/* 0322B8 004322B8 00000000 */   nop
/* 0322BC 004322BC 8F818044 */  lw          $at, %got(jtbl_1000EE7C)($gp)
/* 0322C0 004322C0 000E7080 */  sll         $t6, $t6, 2
/* 0322C4 004322C4 002E0821 */  addu        $at, $at, $t6
/* 0322C8 004322C8 8C2EEE7C */  lw          $t6, %lo(jtbl_1000EE7C)($at)
/* 0322CC 004322CC 01DC7021 */  addu        $t6, $t6, $gp
/* 0322D0 004322D0 01C00008 */  jr          $t6
/* 0322D4 004322D4 00000000 */   nop
.L004322D8:
/* 0322D8 004322D8 8F82804C */  lw          $v0, %got(B_1002E8E0)($gp)
/* 0322DC 004322DC 8FAF005C */  lw          $t7, 0x5C($sp)
/* 0322E0 004322E0 8C42E8E0 */  lw          $v0, %lo(B_1002E8E0)($v0)
/* 0322E4 004322E4 000F4980 */  sll         $t1, $t7, 6
/* 0322E8 004322E8 00094EC2 */  srl         $t1, $t1, 27
/* 0322EC 004322EC 0202082B */  sltu        $at, $s0, $v0
/* 0322F0 004322F0 10200002 */  beqz        $at, .L004322FC
/* 0322F4 004322F4 31E8003F */   andi       $t0, $t7, 0x3F
/* 0322F8 004322F8 00408025 */  move        $s0, $v0
.L004322FC:
/* 0322FC 004322FC 8F988944 */  lw          $t8, %got(fp_latency)($gp)
/* 032300 00432300 8F8D8A98 */  lw          $t5, %got(fp_pipelining)($gp)
/* 032304 00432304 0008C880 */  sll         $t9, $t0, 2
/* 032308 00432308 8F180000 */  lw          $t8, 0x0($t8)
/* 03230C 0043230C 8DAD0000 */  lw          $t5, 0x0($t5)
/* 032310 00432310 0328C823 */  subu        $t9, $t9, $t0
/* 032314 00432314 0019C8C0 */  sll         $t9, $t9, 3
/* 032318 00432318 00095880 */  sll         $t3, $t1, 2
/* 03231C 0043231C 03195021 */  addu        $t2, $t8, $t9
/* 032320 00432320 25AEFFFF */  addiu       $t6, $t5, -0x1
/* 032324 00432324 014B6021 */  addu        $t4, $t2, $t3
/* 032328 00432328 2DC1000B */  sltiu       $at, $t6, 0xB
/* 03232C 0043232C 102001C8 */  beqz        $at, .L00432A50
/* 032330 00432330 8D87FFC0 */   lw         $a3, -0x40($t4)
/* 032334 00432334 8F818044 */  lw          $at, %got(jtbl_1000EED4)($gp)
/* 032338 00432338 000E7080 */  sll         $t6, $t6, 2
/* 03233C 0043233C 002E0821 */  addu        $at, $at, $t6
/* 032340 00432340 8C2EEED4 */  lw          $t6, %lo(jtbl_1000EED4)($at)
/* 032344 00432344 01DC7021 */  addu        $t6, $t6, $gp
/* 032348 00432348 01C00008 */  jr          $t6
/* 03234C 0043234C 00000000 */   nop
.L00432350:
/* 032350 00432350 24050002 */  addiu       $a1, $zero, 0x2
/* 032354 00432354 11050012 */  beq         $t0, $a1, .L004323A0
/* 032358 00432358 24EA001F */   addiu      $t2, $a3, 0x1F
/* 03235C 0043235C 24010003 */  addiu       $at, $zero, 0x3
/* 032360 00432360 11010005 */  beq         $t0, $at, .L00432378
/* 032364 00432364 24F8001D */   addiu      $t8, $a3, 0x1D
/* 032368 00432368 240F0001 */  addiu       $t7, $zero, 0x1
/* 03236C 0043236C 00EF1804 */  sllv        $v1, $t7, $a3
/* 032370 00432370 10000014 */  b           .L004323C4
/* 032374 00432374 2463FFFF */   addiu      $v1, $v1, -0x1
.L00432378:
/* 032378 00432378 8F82804C */  lw          $v0, %got(B_1002E8E4)($gp)
/* 03237C 0043237C 24190007 */  addiu       $t9, $zero, 0x7
/* 032380 00432380 03191804 */  sllv        $v1, $t9, $t8
/* 032384 00432384 8C42E8E4 */  lw          $v0, %lo(B_1002E8E4)($v0)
/* 032388 00432388 0202082B */  sltu        $at, $s0, $v0
/* 03238C 0043238C 10200002 */  beqz        $at, .L00432398
/* 032390 00432390 00000000 */   nop
/* 032394 00432394 00408025 */  move        $s0, $v0
.L00432398:
/* 032398 00432398 1000000A */  b           .L004323C4
/* 03239C 0043239C 24630001 */   addiu      $v1, $v1, 0x1
.L004323A0:
/* 0323A0 004323A0 8F82804C */  lw          $v0, %got(B_1002E8EC)($gp)
/* 0323A4 004323A4 240B0001 */  addiu       $t3, $zero, 0x1
/* 0323A8 004323A8 014B1804 */  sllv        $v1, $t3, $t2
/* 0323AC 004323AC 8C42E8EC */  lw          $v0, %lo(B_1002E8EC)($v0)
/* 0323B0 004323B0 24630001 */  addiu       $v1, $v1, 0x1
/* 0323B4 004323B4 0202082B */  sltu        $at, $s0, $v0
/* 0323B8 004323B8 10200002 */  beqz        $at, .L004323C4
/* 0323BC 004323BC 00000000 */   nop
/* 0323C0 004323C0 00408025 */  move        $s0, $v0
.L004323C4:
/* 0323C4 004323C4 8F8C804C */  lw          $t4, %got(B_1002E910)($gp)
/* 0323C8 004323C8 8D8CE910 */  lw          $t4, %lo(B_1002E910)($t4)
/* 0323CC 004323CC 020C3823 */  subu        $a3, $s0, $t4
/* 0323D0 004323D0 2CE10020 */  sltiu       $at, $a3, 0x20
/* 0323D4 004323D4 502001C4 */  beql        $at, $zero, .L00432AE8
/* 0323D8 004323D8 8FBF001C */   lw         $ra, 0x1C($sp)
/* 0323DC 004323DC 8F8D804C */  lw          $t5, %got(B_1002E900)($gp)
/* 0323E0 004323E0 8DADE900 */  lw          $t5, %lo(B_1002E900)($t5)
/* 0323E4 004323E4 00ED1006 */  srlv        $v0, $t5, $a3
/* 0323E8 004323E8 00437024 */  and         $t6, $v0, $v1
/* 0323EC 004323EC 11C001BD */  beqz        $t6, .L00432AE4
.L004323F0:
/* 0323F0 004323F0 00021042 */   srl        $v0, $v0, 1
/* 0323F4 004323F4 00437824 */  and         $t7, $v0, $v1
/* 0323F8 004323F8 15E0FFFD */  bnez        $t7, .L004323F0
/* 0323FC 004323FC 26100001 */   addiu      $s0, $s0, 0x1
/* 032400 00432400 100001B9 */  b           .L00432AE8
/* 032404 00432404 8FBF001C */   lw         $ra, 0x1C($sp)
.L00432408:
/* 032408 00432408 24050002 */  addiu       $a1, $zero, 0x2
/* 03240C 0043240C 1105000C */  beq         $t0, $a1, .L00432440
/* 032410 00432410 24010003 */   addiu      $at, $zero, 0x3
/* 032414 00432414 11010003 */  beq         $t0, $at, .L00432424
/* 032418 00432418 24010004 */   addiu      $at, $zero, 0x4
/* 03241C 0043241C 1501000F */  bne         $t0, $at, .L0043245C
/* 032420 00432420 00000000 */   nop
.L00432424:
/* 032424 00432424 8F82804C */  lw          $v0, %got(B_1002E8E4)($gp)
/* 032428 00432428 8C42E8E4 */  lw          $v0, %lo(B_1002E8E4)($v0)
/* 03242C 0043242C 0202082B */  sltu        $at, $s0, $v0
/* 032430 00432430 502001AD */  beql        $at, $zero, .L00432AE8
/* 032434 00432434 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032438 00432438 100001AA */  b           .L00432AE4
/* 03243C 0043243C 00408025 */   move       $s0, $v0
.L00432440:
/* 032440 00432440 8F82804C */  lw          $v0, %got(B_1002E8EC)($gp)
/* 032444 00432444 8C42E8EC */  lw          $v0, %lo(B_1002E8EC)($v0)
/* 032448 00432448 0202082B */  sltu        $at, $s0, $v0
/* 03244C 0043244C 502001A6 */  beql        $at, $zero, .L00432AE8
/* 032450 00432450 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032454 00432454 100001A3 */  b           .L00432AE4
/* 032458 00432458 00408025 */   move       $s0, $v0
.L0043245C:
/* 03245C 0043245C 8F82804C */  lw          $v0, %got(B_1002E8FC)($gp)
/* 032460 00432460 8C42E8FC */  lw          $v0, %lo(B_1002E8FC)($v0)
/* 032464 00432464 0202082B */  sltu        $at, $s0, $v0
/* 032468 00432468 5020019F */  beql        $at, $zero, .L00432AE8
/* 03246C 0043246C 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032470 00432470 1000019C */  b           .L00432AE4
/* 032474 00432474 00408025 */   move       $s0, $v0
.L00432478:
/* 032478 00432478 24010006 */  addiu       $at, $zero, 0x6
/* 03247C 0043247C 11010199 */  beq         $t0, $at, .L00432AE4
/* 032480 00432480 24050002 */   addiu      $a1, $zero, 0x2
/* 032484 00432484 11050021 */  beq         $t0, $a1, .L0043250C
/* 032488 00432488 24010003 */   addiu      $at, $zero, 0x3
/* 03248C 0043248C 11010016 */  beq         $t0, $at, .L004324E8
/* 032490 00432490 24010004 */   addiu      $at, $zero, 0x4
/* 032494 00432494 11010006 */  beq         $t0, $at, .L004324B0
/* 032498 00432498 00000000 */   nop
/* 03249C 0043249C 8F82804C */  lw          $v0, %got(B_1002E8E4)($gp)
/* 0324A0 004324A0 8F86804C */  lw          $a2, %got(B_1002E8F8)($gp)
/* 0324A4 004324A4 8C42E8E4 */  lw          $v0, %lo(B_1002E8E4)($v0)
/* 0324A8 004324A8 10000022 */  b           .L00432534
/* 0324AC 004324AC 24C6E8F8 */   addiu      $a2, $a2, %lo(B_1002E8F8)
.L004324B0:
/* 0324B0 004324B0 8F86804C */  lw          $a2, %got(B_1002E8F8)($gp)
/* 0324B4 004324B4 24C6E8F8 */  addiu       $a2, $a2, %lo(B_1002E8F8)
/* 0324B8 004324B8 8CC20000 */  lw          $v0, 0x0($a2)
/* 0324BC 004324BC 0202082B */  sltu        $at, $s0, $v0
/* 0324C0 004324C0 10200002 */  beqz        $at, .L004324CC
/* 0324C4 004324C4 00000000 */   nop
/* 0324C8 004324C8 00408025 */  move        $s0, $v0
.L004324CC:
/* 0324CC 004324CC 8F82804C */  lw          $v0, %got(B_1002E8E4)($gp)
/* 0324D0 004324D0 8C42E8E4 */  lw          $v0, %lo(B_1002E8E4)($v0)
/* 0324D4 004324D4 0202082B */  sltu        $at, $s0, $v0
/* 0324D8 004324D8 50200017 */  beql        $at, $zero, .L00432538
/* 0324DC 004324DC 0202082B */   sltu       $at, $s0, $v0
/* 0324E0 004324E0 10000014 */  b           .L00432534
/* 0324E4 004324E4 00408025 */   move       $s0, $v0
.L004324E8:
/* 0324E8 004324E8 8F82804C */  lw          $v0, %got(B_1002E8E4)($gp)
/* 0324EC 004324EC 8C42E8E4 */  lw          $v0, %lo(B_1002E8E4)($v0)
/* 0324F0 004324F0 0202082B */  sltu        $at, $s0, $v0
/* 0324F4 004324F4 10200002 */  beqz        $at, .L00432500
/* 0324F8 004324F8 00000000 */   nop
/* 0324FC 004324FC 00408025 */  move        $s0, $v0
.L00432500:
/* 032500 00432500 8F86804C */  lw          $a2, %got(B_1002E8F8)($gp)
/* 032504 00432504 1000000B */  b           .L00432534
/* 032508 00432508 24C6E8F8 */   addiu      $a2, $a2, %lo(B_1002E8F8)
.L0043250C:
/* 03250C 0043250C 8F82804C */  lw          $v0, %got(B_1002E8EC)($gp)
/* 032510 00432510 8C42E8EC */  lw          $v0, %lo(B_1002E8EC)($v0)
/* 032514 00432514 0202082B */  sltu        $at, $s0, $v0
/* 032518 00432518 10200002 */  beqz        $at, .L00432524
/* 03251C 0043251C 00000000 */   nop
/* 032520 00432520 00408025 */  move        $s0, $v0
.L00432524:
/* 032524 00432524 8F82804C */  lw          $v0, %got(B_1002E8E4)($gp)
/* 032528 00432528 8F86804C */  lw          $a2, %got(B_1002E8F8)($gp)
/* 03252C 0043252C 8C42E8E4 */  lw          $v0, %lo(B_1002E8E4)($v0)
/* 032530 00432530 24C6E8F8 */  addiu       $a2, $a2, %lo(B_1002E8F8)
.L00432534:
/* 032534 00432534 0202082B */  sltu        $at, $s0, $v0
.L00432538:
/* 032538 00432538 1020001C */  beqz        $at, .L004325AC
/* 03253C 0043253C 250BFFFD */   addiu      $t3, $t0, -0x3
/* 032540 00432540 0050C823 */  subu        $t9, $v0, $s0
/* 032544 00432544 2F21000E */  sltiu       $at, $t9, 0xE
/* 032548 00432548 10200004 */  beqz        $at, .L0043255C
/* 03254C 0043254C 0202082B */   sltu       $at, $s0, $v0
/* 032550 00432550 10200002 */  beqz        $at, .L0043255C
/* 032554 00432554 00000000 */   nop
/* 032558 00432558 00408025 */  move        $s0, $v0
.L0043255C:
/* 03255C 0043255C 8F83804C */  lw          $v1, %got(B_1002E8E8)($gp)
/* 032560 00432560 8C63E8E8 */  lw          $v1, %lo(B_1002E8E8)($v1)
/* 032564 00432564 02032023 */  subu        $a0, $s0, $v1
/* 032568 00432568 2C810004 */  sltiu       $at, $a0, 0x4
/* 03256C 0043256C 1020000F */  beqz        $at, .L004325AC
/* 032570 00432570 0043C023 */   subu       $t8, $v0, $v1
/* 032574 00432574 24010023 */  addiu       $at, $zero, 0x23
/* 032578 00432578 57010008 */  bnel        $t8, $at, .L0043259C
/* 03257C 0043257C 24620004 */   addiu      $v0, $v1, 0x4
/* 032580 00432580 55050006 */  bnel        $t0, $a1, .L0043259C
/* 032584 00432584 24620004 */   addiu      $v0, $v1, 0x4
/* 032588 00432588 14A40008 */  bne         $a1, $a0, .L004325AC
/* 03258C 0043258C 00000000 */   nop
/* 032590 00432590 10000006 */  b           .L004325AC
/* 032594 00432594 26100001 */   addiu      $s0, $s0, 0x1
/* 032598 00432598 24620004 */  addiu       $v0, $v1, 0x4
.L0043259C:
/* 03259C 0043259C 0202082B */  sltu        $at, $s0, $v0
/* 0325A0 004325A0 10200002 */  beqz        $at, .L004325AC
/* 0325A4 004325A4 00000000 */   nop
/* 0325A8 004325A8 00408025 */  move        $s0, $v0
.L004325AC:
/* 0325AC 004325AC 51050008 */  beql        $t0, $a1, .L004325D0
/* 0325B0 004325B0 2D610023 */   sltiu      $at, $t3, 0x23
/* 0325B4 004325B4 8F82804C */  lw          $v0, %got(B_1002E8FC)($gp)
/* 0325B8 004325B8 8C42E8FC */  lw          $v0, %lo(B_1002E8FC)($v0)
/* 0325BC 004325BC 0202082B */  sltu        $at, $s0, $v0
/* 0325C0 004325C0 50200003 */  beql        $at, $zero, .L004325D0
/* 0325C4 004325C4 2D610023 */   sltiu      $at, $t3, 0x23
/* 0325C8 004325C8 00408025 */  move        $s0, $v0
/* 0325CC 004325CC 2D610023 */  sltiu       $at, $t3, 0x23
.L004325D0:
/* 0325D0 004325D0 10200059 */  beqz        $at, .L00432738
/* 0325D4 004325D4 00000000 */   nop
/* 0325D8 004325D8 8F818044 */  lw          $at, %got(jtbl_1000EF00)($gp)
/* 0325DC 004325DC 000B5880 */  sll         $t3, $t3, 2
/* 0325E0 004325E0 002B0821 */  addu        $at, $at, $t3
/* 0325E4 004325E4 8C2BEF00 */  lw          $t3, %lo(jtbl_1000EF00)($at)
/* 0325E8 004325E8 017C5821 */  addu        $t3, $t3, $gp
/* 0325EC 004325EC 01600008 */  jr          $t3
/* 0325F0 004325F0 00000000 */   nop
.L004325F4:
/* 0325F4 004325F4 8CC20000 */  lw          $v0, 0x0($a2)
/* 0325F8 004325F8 0202082B */  sltu        $at, $s0, $v0
/* 0325FC 004325FC 1020004E */  beqz        $at, .L00432738
/* 032600 00432600 00000000 */   nop
/* 032604 00432604 8F83804C */  lw          $v1, %got(B_1002E8F0)($gp)
/* 032608 00432608 24010001 */  addiu       $at, $zero, 0x1
/* 03260C 0043260C 8C63E8F0 */  lw          $v1, %lo(B_1002E8F0)($v1)
/* 032610 00432610 02035023 */  subu        $t2, $s0, $v1
/* 032614 00432614 55410005 */  bnel        $t2, $at, .L0043262C
/* 032618 00432618 0202082B */   sltu       $at, $s0, $v0
/* 03261C 0043261C 8F8C804C */  lw          $t4, %got(B_1002E8F4)($gp)
/* 032620 00432620 8D8CE8F4 */  lw          $t4, %lo(B_1002E8F4)($t4)
/* 032624 00432624 15830044 */  bne         $t4, $v1, .L00432738
/* 032628 00432628 0202082B */   sltu       $at, $s0, $v0
.L0043262C:
/* 03262C 0043262C 10200042 */  beqz        $at, .L00432738
/* 032630 00432630 00000000 */   nop
/* 032634 00432634 10000040 */  b           .L00432738
/* 032638 00432638 00408025 */   move       $s0, $v0
.L0043263C:
/* 03263C 0043263C 24010011 */  addiu       $at, $zero, 0x11
/* 032640 00432640 1121000C */  beq         $t1, $at, .L00432674
/* 032644 00432644 02002025 */   move       $a0, $s0
/* 032648 00432648 24010014 */  addiu       $at, $zero, 0x14
/* 03264C 0043264C 11210003 */  beq         $t1, $at, .L0043265C
/* 032650 00432650 24010015 */   addiu      $at, $zero, 0x15
/* 032654 00432654 15210038 */  bne         $t1, $at, .L00432738
/* 032658 00432658 00000000 */   nop
.L0043265C:
/* 03265C 0043265C 8CC20000 */  lw          $v0, 0x0($a2)
/* 032660 00432660 0202082B */  sltu        $at, $s0, $v0
/* 032664 00432664 10200034 */  beqz        $at, .L00432738
/* 032668 00432668 00000000 */   nop
/* 03266C 0043266C 10000032 */  b           .L00432738
/* 032670 00432670 00408025 */   move       $s0, $v0
.L00432674:
/* 032674 00432674 8F998020 */  lw          $t9, %got(func_00431FB4)($gp)
/* 032678 00432678 AFA70048 */  sw          $a3, 0x48($sp)
/* 03267C 0043267C AFA80050 */  sw          $t0, 0x50($sp)
/* 032680 00432680 27391FB4 */  addiu       $t9, $t9, %lo(func_00431FB4)
/* 032684 00432684 0320F809 */  jalr        $t9
/* 032688 00432688 AFA90054 */   sw         $t1, 0x54($sp)
/* 03268C 0043268C 8FBC0018 */  lw          $gp, 0x18($sp)
/* 032690 00432690 8FA70048 */  lw          $a3, 0x48($sp)
/* 032694 00432694 8FA80050 */  lw          $t0, 0x50($sp)
/* 032698 00432698 8FA90054 */  lw          $t1, 0x54($sp)
/* 03269C 0043269C 10000026 */  b           .L00432738
/* 0326A0 004326A0 00408025 */   move       $s0, $v0
.L004326A4:
/* 0326A4 004326A4 24010014 */  addiu       $at, $zero, 0x14
/* 0326A8 004326A8 11210005 */  beq         $t1, $at, .L004326C0
/* 0326AC 004326AC 24010015 */   addiu      $at, $zero, 0x15
/* 0326B0 004326B0 11210009 */  beq         $t1, $at, .L004326D8
/* 0326B4 004326B4 02002025 */   move       $a0, $s0
/* 0326B8 004326B8 1000001F */  b           .L00432738
/* 0326BC 004326BC 00000000 */   nop
.L004326C0:
/* 0326C0 004326C0 8CC20000 */  lw          $v0, 0x0($a2)
/* 0326C4 004326C4 0202082B */  sltu        $at, $s0, $v0
/* 0326C8 004326C8 1020001B */  beqz        $at, .L00432738
/* 0326CC 004326CC 00000000 */   nop
/* 0326D0 004326D0 10000019 */  b           .L00432738
/* 0326D4 004326D4 00408025 */   move       $s0, $v0
.L004326D8:
/* 0326D8 004326D8 8F998020 */  lw          $t9, %got(func_00431FB4)($gp)
/* 0326DC 004326DC AFA70048 */  sw          $a3, 0x48($sp)
/* 0326E0 004326E0 AFA80050 */  sw          $t0, 0x50($sp)
/* 0326E4 004326E4 27391FB4 */  addiu       $t9, $t9, %lo(func_00431FB4)
/* 0326E8 004326E8 0320F809 */  jalr        $t9
/* 0326EC 004326EC AFA90054 */   sw         $t1, 0x54($sp)
/* 0326F0 004326F0 8FBC0018 */  lw          $gp, 0x18($sp)
/* 0326F4 004326F4 8FA70048 */  lw          $a3, 0x48($sp)
/* 0326F8 004326F8 8FA80050 */  lw          $t0, 0x50($sp)
/* 0326FC 004326FC 8FA90054 */  lw          $t1, 0x54($sp)
/* 032700 00432700 1000000D */  b           .L00432738
/* 032704 00432704 00408025 */   move       $s0, $v0
.L00432708:
/* 032708 00432708 8F998020 */  lw          $t9, %got(func_00431FB4)($gp)
/* 03270C 0043270C 02002025 */  move        $a0, $s0
/* 032710 00432710 AFA70048 */  sw          $a3, 0x48($sp)
/* 032714 00432714 27391FB4 */  addiu       $t9, $t9, %lo(func_00431FB4)
/* 032718 00432718 AFA80050 */  sw          $t0, 0x50($sp)
/* 03271C 0043271C 0320F809 */  jalr        $t9
/* 032720 00432720 AFA90054 */   sw         $t1, 0x54($sp)
/* 032724 00432724 8FBC0018 */  lw          $gp, 0x18($sp)
/* 032728 00432728 8FA70048 */  lw          $a3, 0x48($sp)
/* 03272C 0043272C 8FA80050 */  lw          $t0, 0x50($sp)
/* 032730 00432730 8FA90054 */  lw          $t1, 0x54($sp)
/* 032734 00432734 00408025 */  move        $s0, $v0
.L00432738:
/* 032738 00432738 8F8D804C */  lw          $t5, %got(B_1002E910)($gp)
/* 03273C 0043273C 24180001 */  addiu       $t8, $zero, 0x1
/* 032740 00432740 00F83004 */  sllv        $a2, $t8, $a3
/* 032744 00432744 8DADE910 */  lw          $t5, %lo(B_1002E910)($t5)
/* 032748 00432748 020D2823 */  subu        $a1, $s0, $t5
/* 03274C 0043274C 2CA10020 */  sltiu       $at, $a1, 0x20
/* 032750 00432750 502000E5 */  beql        $at, $zero, .L00432AE8
/* 032754 00432754 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032758 00432758 8F99804C */  lw          $t9, %got(B_1002E904)($gp)
/* 03275C 0043275C 8F8E804C */  lw          $t6, %got(B_1002E908)($gp)
/* 032760 00432760 8F8F804C */  lw          $t7, %got(B_1002E90C)($gp)
/* 032764 00432764 8F39E904 */  lw          $t9, %lo(B_1002E904)($t9)
/* 032768 00432768 8DCEE908 */  lw          $t6, %lo(B_1002E908)($t6)
/* 03276C 0043276C 8DEFE90C */  lw          $t7, %lo(B_1002E90C)($t7)
/* 032770 00432770 00B92006 */  srlv        $a0, $t9, $a1
/* 032774 00432774 00C45824 */  and         $t3, $a2, $a0
/* 032778 00432778 00AE1006 */  srlv        $v0, $t6, $a1
/* 03277C 0043277C 15600016 */  bnez        $t3, .L004327D8
/* 032780 00432780 00AF1806 */   srlv       $v1, $t7, $a1
/* 032784 00432784 8F878978 */  lw          $a3, %got(r4010_a)($gp)
/* 032788 00432788 00085080 */  sll         $t2, $t0, 2
/* 03278C 0043278C 01485023 */  subu        $t2, $t2, $t0
/* 032790 00432790 000A50C0 */  sll         $t2, $t2, 3
/* 032794 00432794 00096880 */  sll         $t5, $t1, 2
/* 032798 00432798 00EA6021 */  addu        $t4, $a3, $t2
/* 03279C 0043279C 018D7021 */  addu        $t6, $t4, $t5
/* 0327A0 004327A0 8DCFFFC0 */  lw          $t7, -0x40($t6)
/* 0327A4 004327A4 0008C080 */  sll         $t8, $t0, 2
/* 0327A8 004327A8 0308C023 */  subu        $t8, $t8, $t0
/* 0327AC 004327AC 01E2C824 */  and         $t9, $t7, $v0
/* 0327B0 004327B0 5720000A */  bnel        $t9, $zero, .L004327DC
/* 0327B4 004327B4 00042042 */   srl        $a0, $a0, 1
/* 0327B8 004327B8 8F85897C */  lw          $a1, %got(r4010_s)($gp)
/* 0327BC 004327BC 0018C0C0 */  sll         $t8, $t8, 3
/* 0327C0 004327C0 00095080 */  sll         $t2, $t1, 2
/* 0327C4 004327C4 00B85821 */  addu        $t3, $a1, $t8
/* 0327C8 004327C8 016A6021 */  addu        $t4, $t3, $t2
/* 0327CC 004327CC 8D8DFFC0 */  lw          $t5, -0x40($t4)
/* 0327D0 004327D0 01A37024 */  and         $t6, $t5, $v1
/* 0327D4 004327D4 11C000C3 */  beqz        $t6, .L00432AE4
.L004327D8:
/* 0327D8 004327D8 00042042 */   srl        $a0, $a0, 1
.L004327DC:
/* 0327DC 004327DC 00C47824 */  and         $t7, $a2, $a0
/* 0327E0 004327E0 8F85897C */  lw          $a1, %got(r4010_s)($gp)
/* 0327E4 004327E4 8F878978 */  lw          $a3, %got(r4010_a)($gp)
/* 0327E8 004327E8 26100001 */  addiu       $s0, $s0, 0x1
/* 0327EC 004327EC 00021042 */  srl         $v0, $v0, 1
/* 0327F0 004327F0 15E0FFF9 */  bnez        $t7, .L004327D8
/* 0327F4 004327F4 00031842 */   srl        $v1, $v1, 1
/* 0327F8 004327F8 0008C880 */  sll         $t9, $t0, 2
/* 0327FC 004327FC 0328C823 */  subu        $t9, $t9, $t0
/* 032800 00432800 0019C8C0 */  sll         $t9, $t9, 3
/* 032804 00432804 00F9C021 */  addu        $t8, $a3, $t9
/* 032808 00432808 00095880 */  sll         $t3, $t1, 2
/* 03280C 0043280C 030B5021 */  addu        $t2, $t8, $t3
/* 032810 00432810 8D4CFFC0 */  lw          $t4, -0x40($t2)
/* 032814 00432814 01826824 */  and         $t5, $t4, $v0
/* 032818 00432818 55A0FFF0 */  bnel        $t5, $zero, .L004327DC
/* 03281C 0043281C 00042042 */   srl        $a0, $a0, 1
/* 032820 00432820 00087080 */  sll         $t6, $t0, 2
/* 032824 00432824 01C87023 */  subu        $t6, $t6, $t0
/* 032828 00432828 000E70C0 */  sll         $t6, $t6, 3
/* 03282C 0043282C 00AE7821 */  addu        $t7, $a1, $t6
/* 032830 00432830 0009C880 */  sll         $t9, $t1, 2
/* 032834 00432834 01F9C021 */  addu        $t8, $t7, $t9
/* 032838 00432838 8F0BFFC0 */  lw          $t3, -0x40($t8)
/* 03283C 0043283C 01635024 */  and         $t2, $t3, $v1
/* 032840 00432840 5540FFE6 */  bnel        $t2, $zero, .L004327DC
/* 032844 00432844 00042042 */   srl        $a0, $a0, 1
/* 032848 00432848 100000A7 */  b           .L00432AE8
/* 03284C 0043284C 8FBF001C */   lw         $ra, 0x1C($sp)
.L00432850:
/* 032850 00432850 24050002 */  addiu       $a1, $zero, 0x2
/* 032854 00432854 15050008 */  bne         $t0, $a1, .L00432878
/* 032858 00432858 00000000 */   nop
/* 03285C 0043285C 8F82804C */  lw          $v0, %got(B_1002E8EC)($gp)
/* 032860 00432860 8C42E8EC */  lw          $v0, %lo(B_1002E8EC)($v0)
/* 032864 00432864 0202082B */  sltu        $at, $s0, $v0
/* 032868 00432868 5020009F */  beql        $at, $zero, .L00432AE8
/* 03286C 0043286C 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032870 00432870 1000009C */  b           .L00432AE4
/* 032874 00432874 00408025 */   move       $s0, $v0
.L00432878:
/* 032878 00432878 8F82804C */  lw          $v0, %got(B_1002E8FC)($gp)
/* 03287C 0043287C 8C42E8FC */  lw          $v0, %lo(B_1002E8FC)($v0)
/* 032880 00432880 0202082B */  sltu        $at, $s0, $v0
/* 032884 00432884 50200098 */  beql        $at, $zero, .L00432AE8
/* 032888 00432888 8FBF001C */   lw         $ra, 0x1C($sp)
/* 03288C 0043288C 10000095 */  b           .L00432AE4
/* 032890 00432890 00408025 */   move       $s0, $v0
.L00432894:
/* 032894 00432894 24050002 */  addiu       $a1, $zero, 0x2
/* 032898 00432898 11050005 */  beq         $t0, $a1, .L004328B0
/* 03289C 0043289C 24010003 */   addiu      $at, $zero, 0x3
/* 0328A0 004328A0 11010003 */  beq         $t0, $at, .L004328B0
/* 0328A4 004328A4 24010004 */   addiu      $at, $zero, 0x4
/* 0328A8 004328A8 15010008 */  bne         $t0, $at, .L004328CC
/* 0328AC 004328AC 00000000 */   nop
.L004328B0:
/* 0328B0 004328B0 8F82804C */  lw          $v0, %got(B_1002E8EC)($gp)
/* 0328B4 004328B4 8C42E8EC */  lw          $v0, %lo(B_1002E8EC)($v0)
/* 0328B8 004328B8 0202082B */  sltu        $at, $s0, $v0
/* 0328BC 004328BC 5020008A */  beql        $at, $zero, .L00432AE8
/* 0328C0 004328C0 8FBF001C */   lw         $ra, 0x1C($sp)
/* 0328C4 004328C4 10000087 */  b           .L00432AE4
/* 0328C8 004328C8 00408025 */   move       $s0, $v0
.L004328CC:
/* 0328CC 004328CC 8F82804C */  lw          $v0, %got(B_1002E8FC)($gp)
/* 0328D0 004328D0 8C42E8FC */  lw          $v0, %lo(B_1002E8FC)($v0)
/* 0328D4 004328D4 0202082B */  sltu        $at, $s0, $v0
/* 0328D8 004328D8 50200083 */  beql        $at, $zero, .L00432AE8
/* 0328DC 004328DC 8FBF001C */   lw         $ra, 0x1C($sp)
/* 0328E0 004328E0 10000080 */  b           .L00432AE4
/* 0328E4 004328E4 00408025 */   move       $s0, $v0
.L004328E8:
/* 0328E8 004328E8 24050002 */  addiu       $a1, $zero, 0x2
/* 0328EC 004328EC 1105000C */  beq         $t0, $a1, .L00432920
/* 0328F0 004328F0 24010003 */   addiu      $at, $zero, 0x3
/* 0328F4 004328F4 11010003 */  beq         $t0, $at, .L00432904
/* 0328F8 004328F8 24010004 */   addiu      $at, $zero, 0x4
/* 0328FC 004328FC 1501000F */  bne         $t0, $at, .L0043293C
/* 032900 00432900 00000000 */   nop
.L00432904:
/* 032904 00432904 8F82804C */  lw          $v0, %got(B_1002E8E4)($gp)
/* 032908 00432908 8C42E8E4 */  lw          $v0, %lo(B_1002E8E4)($v0)
/* 03290C 0043290C 0202082B */  sltu        $at, $s0, $v0
/* 032910 00432910 50200075 */  beql        $at, $zero, .L00432AE8
/* 032914 00432914 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032918 00432918 10000072 */  b           .L00432AE4
/* 03291C 0043291C 00408025 */   move       $s0, $v0
.L00432920:
/* 032920 00432920 8F82804C */  lw          $v0, %got(B_1002E8EC)($gp)
/* 032924 00432924 8C42E8EC */  lw          $v0, %lo(B_1002E8EC)($v0)
/* 032928 00432928 0202082B */  sltu        $at, $s0, $v0
/* 03292C 0043292C 5020006E */  beql        $at, $zero, .L00432AE8
/* 032930 00432930 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032934 00432934 1000006B */  b           .L00432AE4
/* 032938 00432938 00408025 */   move       $s0, $v0
.L0043293C:
/* 03293C 0043293C 8F82804C */  lw          $v0, %got(B_1002E8FC)($gp)
/* 032940 00432940 8C42E8FC */  lw          $v0, %lo(B_1002E8FC)($v0)
/* 032944 00432944 0202082B */  sltu        $at, $s0, $v0
/* 032948 00432948 50200067 */  beql        $at, $zero, .L00432AE8
/* 03294C 0043294C 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032950 00432950 10000064 */  b           .L00432AE4
/* 032954 00432954 00408025 */   move       $s0, $v0
.L00432958:
/* 032958 00432958 24050002 */  addiu       $a1, $zero, 0x2
/* 03295C 0043295C 1105000E */  beq         $t0, $a1, .L00432998
/* 032960 00432960 24EC001F */   addiu      $t4, $a3, 0x1F
/* 032964 00432964 24010003 */  addiu       $at, $zero, 0x3
/* 032968 00432968 11010003 */  beq         $t0, $at, .L00432978
/* 03296C 0043296C 24010004 */   addiu      $at, $zero, 0x4
/* 032970 00432970 15010012 */  bne         $t0, $at, .L004329BC
/* 032974 00432974 24EE001F */   addiu      $t6, $a3, 0x1F
.L00432978:
/* 032978 00432978 8F82804C */  lw          $v0, %got(B_1002E8E4)($gp)
/* 03297C 0043297C 8C42E8E4 */  lw          $v0, %lo(B_1002E8E4)($v0)
/* 032980 00432980 0202082B */  sltu        $at, $s0, $v0
/* 032984 00432984 10200002 */  beqz        $at, .L00432990
/* 032988 00432988 00000000 */   nop
/* 03298C 0043298C 00408025 */  move        $s0, $v0
.L00432990:
/* 032990 00432990 1000FE8C */  b           .L004323C4
/* 032994 00432994 00001825 */   move       $v1, $zero
.L00432998:
/* 032998 00432998 8F82804C */  lw          $v0, %got(B_1002E8EC)($gp)
/* 03299C 0043299C 240D0001 */  addiu       $t5, $zero, 0x1
/* 0329A0 004329A0 8C42E8EC */  lw          $v0, %lo(B_1002E8EC)($v0)
/* 0329A4 004329A4 0202082B */  sltu        $at, $s0, $v0
/* 0329A8 004329A8 10200002 */  beqz        $at, .L004329B4
/* 0329AC 004329AC 00000000 */   nop
/* 0329B0 004329B0 00408025 */  move        $s0, $v0
.L004329B4:
/* 0329B4 004329B4 1000FE83 */  b           .L004323C4
/* 0329B8 004329B8 018D1804 */   sllv       $v1, $t5, $t4
.L004329BC:
/* 0329BC 004329BC 8F82804C */  lw          $v0, %got(B_1002E8FC)($gp)
/* 0329C0 004329C0 240F0001 */  addiu       $t7, $zero, 0x1
/* 0329C4 004329C4 8C42E8FC */  lw          $v0, %lo(B_1002E8FC)($v0)
/* 0329C8 004329C8 0202082B */  sltu        $at, $s0, $v0
/* 0329CC 004329CC 10200002 */  beqz        $at, .L004329D8
/* 0329D0 004329D0 00000000 */   nop
/* 0329D4 004329D4 00408025 */  move        $s0, $v0
.L004329D8:
/* 0329D8 004329D8 1000FE7A */  b           .L004323C4
/* 0329DC 004329DC 01CF1804 */   sllv       $v1, $t7, $t6
.L004329E0:
/* 0329E0 004329E0 24050002 */  addiu       $a1, $zero, 0x2
/* 0329E4 004329E4 1105000C */  beq         $t0, $a1, .L00432A18
/* 0329E8 004329E8 24010003 */   addiu      $at, $zero, 0x3
/* 0329EC 004329EC 11010003 */  beq         $t0, $at, .L004329FC
/* 0329F0 004329F0 24010004 */   addiu      $at, $zero, 0x4
/* 0329F4 004329F4 1501000F */  bne         $t0, $at, .L00432A34
/* 0329F8 004329F8 00000000 */   nop
.L004329FC:
/* 0329FC 004329FC 8F82804C */  lw          $v0, %got(B_1002E8E4)($gp)
/* 032A00 00432A00 8C42E8E4 */  lw          $v0, %lo(B_1002E8E4)($v0)
/* 032A04 00432A04 0202082B */  sltu        $at, $s0, $v0
/* 032A08 00432A08 50200037 */  beql        $at, $zero, .L00432AE8
/* 032A0C 00432A0C 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032A10 00432A10 10000034 */  b           .L00432AE4
/* 032A14 00432A14 00408025 */   move       $s0, $v0
.L00432A18:
/* 032A18 00432A18 8F82804C */  lw          $v0, %got(B_1002E8EC)($gp)
/* 032A1C 00432A1C 8C42E8EC */  lw          $v0, %lo(B_1002E8EC)($v0)
/* 032A20 00432A20 0202082B */  sltu        $at, $s0, $v0
/* 032A24 00432A24 50200030 */  beql        $at, $zero, .L00432AE8
/* 032A28 00432A28 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032A2C 00432A2C 1000002D */  b           .L00432AE4
/* 032A30 00432A30 00408025 */   move       $s0, $v0
.L00432A34:
/* 032A34 00432A34 8F82804C */  lw          $v0, %got(B_1002E8FC)($gp)
/* 032A38 00432A38 8C42E8FC */  lw          $v0, %lo(B_1002E8FC)($v0)
/* 032A3C 00432A3C 0202082B */  sltu        $at, $s0, $v0
/* 032A40 00432A40 50200029 */  beql        $at, $zero, .L00432AE8
/* 032A44 00432A44 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032A48 00432A48 10000026 */  b           .L00432AE4
/* 032A4C 00432A4C 00408025 */   move       $s0, $v0
.L00432A50:
/* 032A50 00432A50 8F998644 */  lw          $t9, %call16(assertion_failed)($gp)
/* 032A54 00432A54 8F848044 */  lw          $a0, %got(STR_1000E4F0)($gp)
/* 032A58 00432A58 8F858044 */  lw          $a1, %got(STR_1000E4F8)($gp)
/* 032A5C 00432A5C 24060B06 */  addiu       $a2, $zero, 0xB06
/* 032A60 00432A60 2484E4F0 */  addiu       $a0, $a0, %lo(STR_1000E4F0)
/* 032A64 00432A64 0320F809 */  jalr        $t9
/* 032A68 00432A68 24A5E4F8 */   addiu      $a1, $a1, %lo(STR_1000E4F8)
/* 032A6C 00432A6C 1000001D */  b           .L00432AE4
/* 032A70 00432A70 8FBC0018 */   lw         $gp, 0x18($sp)
.L00432A74:
/* 032A74 00432A74 8F998644 */  lw          $t9, %call16(assertion_failed)($gp)
/* 032A78 00432A78 8F848044 */  lw          $a0, %got(STR_1000E508)($gp)
/* 032A7C 00432A7C 8F858044 */  lw          $a1, %got(STR_1000E510)($gp)
/* 032A80 00432A80 24060B0A */  addiu       $a2, $zero, 0xB0A
/* 032A84 00432A84 2484E508 */  addiu       $a0, $a0, %lo(STR_1000E508)
/* 032A88 00432A88 0320F809 */  jalr        $t9
/* 032A8C 00432A8C 24A5E510 */   addiu      $a1, $a1, %lo(STR_1000E510)
/* 032A90 00432A90 8FBC0018 */  lw          $gp, 0x18($sp)
/* 032A94 00432A94 10000014 */  b           .L00432AE8
/* 032A98 00432A98 8FBF001C */   lw         $ra, 0x1C($sp)
.L00432A9C:
/* 032A9C 00432A9C 8F82804C */  lw          $v0, %got(B_1002E8C8)($gp)
/* 032AA0 00432AA0 8C42E8C8 */  lw          $v0, %lo(B_1002E8C8)($v0)
/* 032AA4 00432AA4 0202082B */  sltu        $at, $s0, $v0
/* 032AA8 00432AA8 5020000F */  beql        $at, $zero, .L00432AE8
/* 032AAC 00432AAC 8FBF001C */   lw         $ra, 0x1C($sp)
/* 032AB0 00432AB0 1000000C */  b           .L00432AE4
/* 032AB4 00432AB4 00408025 */   move       $s0, $v0
.L00432AB8:
/* 032AB8 00432AB8 8F988A28 */  lw          $t8, %got(op_name)($gp)
/* 032ABC 00432ABC 0002C880 */  sll         $t9, $v0, 2
/* 032AC0 00432AC0 8F84805C */  lw          $a0, %got(__iob)($gp)
/* 032AC4 00432AC4 03385821 */  addu        $t3, $t9, $t8
/* 032AC8 00432AC8 8F998090 */  lw          $t9, %call16(fprintf)($gp)
/* 032ACC 00432ACC 8F858044 */  lw          $a1, %got(STR_1000E520)($gp)
/* 032AD0 00432AD0 8D660000 */  lw          $a2, 0x0($t3)
/* 032AD4 00432AD4 24840020 */  addiu       $a0, $a0, 0x20
/* 032AD8 00432AD8 0320F809 */  jalr        $t9
/* 032ADC 00432ADC 24A5E520 */   addiu      $a1, $a1, %lo(STR_1000E520)
/* 032AE0 00432AE0 8FBC0018 */  lw          $gp, 0x18($sp)
.L00432AE4:
/* 032AE4 00432AE4 8FBF001C */  lw          $ra, 0x1C($sp)
.L00432AE8:
/* 032AE8 00432AE8 02001025 */  move        $v0, $s0
/* 032AEC 00432AEC 8FB00014 */  lw          $s0, 0x14($sp)
/* 032AF0 00432AF0 03E00008 */  jr          $ra
/* 032AF4 00432AF4 27BD0060 */   addiu      $sp, $sp, 0x60
)
#endif

#pragma GLOBAL_ASM("asm/7.1/functions/as1/start_instruction.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00433538.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00433610.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00433668.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/reorganize_bb.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/allocate_check.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/recalloc.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/addset.s")

#ifdef GLOBAL_ASM_FILE
GLOBAL_ASM(
.section .rodata
glabel STR_1000F400
/* 09F400 1000F400 */ .asciz "as1: internal: unexpected opcode %s\n"
                      .balign 4

glabel STR_1000F428
/* 09F428 1000F428 */ .asciz "as1: internal: unexpected opcode %s\n"
                      .balign 4

glabel STR_1000F450
/* 09F450 1000F450 */ .asciz "as1: internal: unexpected opcode %s\n"
                      .balign 4

glabel STR_1000F478
/* 09F478 1000F478 */ .asciz "as1: internal: unexpected opcode %s\n"
                      .balign 4

glabel STR_1000F4A0
/* 09F4A0 1000F4A0 */ .asciz "as1: internal: unexpected opcode %s\n"
                      .balign 4

.section .late_rodata

.late_rodata_alignment 4 /* Extra */

glabel jtbl_1000F500
/* 09F500 1000F500 F0409E5C */ .gpword .L00434C0C
/* 09F504 1000F504 F0409C68 */ .gpword .L00434A18
/* 09F508 1000F508 F040A7C0 */ .gpword .L00435570
/* 09F50C 1000F50C F0409CFC */ .gpword .L00434AAC
/* 09F510 1000F510 F0409C34 */ .gpword .L004349E4
/* 09F514 1000F514 F0409C34 */ .gpword .L004349E4
/* 09F518 1000F518 F0409C34 */ .gpword .L004349E4
/* 09F51C 1000F51C F0409C34 */ .gpword .L004349E4
/* 09F520 1000F520 F0409C00 */ .gpword .L004349B0
/* 09F524 1000F524 F0409C00 */ .gpword .L004349B0
/* 09F528 1000F528 F0409C00 */ .gpword .L004349B0
/* 09F52C 1000F52C F0409C00 */ .gpword .L004349B0
/* 09F530 1000F530 F0409C00 */ .gpword .L004349B0
/* 09F534 1000F534 F0409C00 */ .gpword .L004349B0
/* 09F538 1000F538 F0409C00 */ .gpword .L004349B0
/* 09F53C 1000F53C F0409C00 */ .gpword .L004349B0
/* 09F540 1000F540 F040A084 */ .gpword .L00434E34
/* 09F544 1000F544 F040A318 */ .gpword .L004350C8
/* 09F548 1000F548 F040A084 */ .gpword .L00434E34
/* 09F54C 1000F54C F040A0E8 */ .gpword .L00434E98
/* 09F550 1000F550 F0409C34 */ .gpword .L004349E4
/* 09F554 1000F554 F0409C34 */ .gpword .L004349E4
/* 09F558 1000F558 F0409C34 */ .gpword .L004349E4
/* 09F55C 1000F55C F0409C34 */ .gpword .L004349E4
/* 09F560 1000F560 F0409C00 */ .gpword .L004349B0
/* 09F564 1000F564 F0409C00 */ .gpword .L004349B0
/* 09F568 1000F568 F0409C00 */ .gpword .L004349B0
/* 09F56C 1000F56C F0409C00 */ .gpword .L004349B0
/* 09F570 1000F570 F040A794 */ .gpword .L00435544
/* 09F574 1000F574 F040A794 */ .gpword .L00435544
/* 09F578 1000F578 F040A794 */ .gpword .L00435544
/* 09F57C 1000F57C F040A794 */ .gpword .L00435544
/* 09F580 1000F580 F0409C00 */ .gpword .L004349B0
/* 09F584 1000F584 F0409C00 */ .gpword .L004349B0
/* 09F588 1000F588 F0409C00 */ .gpword .L004349B0
/* 09F58C 1000F58C F0409C00 */ .gpword .L004349B0
/* 09F590 1000F590 F0409C00 */ .gpword .L004349B0
/* 09F594 1000F594 F0409C00 */ .gpword .L004349B0
/* 09F598 1000F598 F0409C00 */ .gpword .L004349B0
/* 09F59C 1000F59C F0409C00 */ .gpword .L004349B0
/* 09F5A0 1000F5A0 F0409C34 */ .gpword .L004349E4
/* 09F5A4 1000F5A4 F0409C34 */ .gpword .L004349E4
/* 09F5A8 1000F5A8 F0409C34 */ .gpword .L004349E4
/* 09F5AC 1000F5AC F0409C34 */ .gpword .L004349E4
/* 09F5B0 1000F5B0 F0409C34 */ .gpword .L004349E4
/* 09F5B4 1000F5B4 F0409C34 */ .gpword .L004349E4
/* 09F5B8 1000F5B8 F0409C34 */ .gpword .L004349E4
/* 09F5BC 1000F5BC F0409DB0 */ .gpword .L00434B60
/* 09F5C0 1000F5C0 F0409C00 */ .gpword .L004349B0
/* 09F5C4 1000F5C4 F0409D18 */ .gpword .L00434AC8
/* 09F5C8 1000F5C8 F0409DB0 */ .gpword .L00434B60
/* 09F5CC 1000F5CC F0409DB0 */ .gpword .L00434B60
/* 09F5D0 1000F5D0 F0409C00 */ .gpword .L004349B0
/* 09F5D4 1000F5D4 F0409D4C */ .gpword .L00434AFC
/* 09F5D8 1000F5D8 F0409DB0 */ .gpword .L00434B60
/* 09F5DC 1000F5DC F0409C00 */ .gpword .L004349B0
/* 09F5E0 1000F5E0 F0409C00 */ .gpword .L004349B0
/* 09F5E4 1000F5E4 F0409DCC */ .gpword .L00434B7C
/* 09F5E8 1000F5E8 F0409DB0 */ .gpword .L00434B60
/* 09F5EC 1000F5EC F0409DB0 */ .gpword .L00434B60
/* 09F5F0 1000F5F0 F0409C00 */ .gpword .L004349B0
/* 09F5F4 1000F5F4 F0409E00 */ .gpword .L00434BB0
/* 09F5F8 1000F5F8 F0409DB0 */ .gpword .L00434B60
/* 09F5FC 1000F5FC F0409C34 */ .gpword .L004349E4

glabel jtbl_1000F600
/* 09F600 1000F600 F0409CAC */ .gpword .L00434A5C
/* 09F604 1000F604 F0409CAC */ .gpword .L00434A5C
/* 09F608 1000F608 F0409CAC */ .gpword .L00434A5C
/* 09F60C 1000F60C F0409CAC */ .gpword .L00434A5C
/* 09F610 1000F610 F0409CC8 */ .gpword .L00434A78
/* 09F614 1000F614 F0409CC8 */ .gpword .L00434A78
/* 09F618 1000F618 F0409CC8 */ .gpword .L00434A78
/* 09F61C 1000F61C F0409CC8 */ .gpword .L00434A78
/* 09F620 1000F620 F0409CAC */ .gpword .L00434A5C
/* 09F624 1000F624 F0409CAC */ .gpword .L00434A5C
/* 09F628 1000F628 F0409CAC */ .gpword .L00434A5C
/* 09F62C 1000F62C F0409CAC */ .gpword .L00434A5C
/* 09F630 1000F630 F0409CAC */ .gpword .L00434A5C
/* 09F634 1000F634 F0409CC8 */ .gpword .L00434A78
/* 09F638 1000F638 F0409CAC */ .gpword .L00434A5C
/* 09F63C 1000F63C F0409CC8 */ .gpword .L00434A78
/* 09F640 1000F640 F0409C94 */ .gpword .L00434A44
/* 09F644 1000F644 F0409C94 */ .gpword .L00434A44
/* 09F648 1000F648 F0409C94 */ .gpword .L00434A44
/* 09F64C 1000F64C F0409C94 */ .gpword .L00434A44

glabel jtbl_1000F650
/* 09F650 1000F650 F0409ED0 */ .gpword .L00434C80
/* 09F654 1000F654 F0409FFC */ .gpword .L00434DAC
/* 09F658 1000F658 F0409ED0 */ .gpword .L00434C80
/* 09F65C 1000F65C F0409ED0 */ .gpword .L00434C80
/* 09F660 1000F660 F0409E88 */ .gpword .L00434C38
/* 09F664 1000F664 F040A04C */ .gpword .L00434DFC
/* 09F668 1000F668 F0409E88 */ .gpword .L00434C38
/* 09F66C 1000F66C F0409E88 */ .gpword .L00434C38
/* 09F670 1000F670 F0409F30 */ .gpword .L00434CE0
/* 09F674 1000F674 F0409F00 */ .gpword .L00434CB0
/* 09F678 1000F678 F0409FB4 */ .gpword .L00434D64
/* 09F67C 1000F67C F0409FB4 */ .gpword .L00434D64
/* 09F680 1000F680 F040A7C0 */ .gpword .L00435570
/* 09F684 1000F684 F040A7C0 */ .gpword .L00435570
/* 09F688 1000F688 F040A04C */ .gpword .L00434DFC
/* 09F68C 1000F68C F040A7C0 */ .gpword .L00435570
/* 09F690 1000F690 F0409F4C */ .gpword .L00434CFC
/* 09F694 1000F694 F0409F64 */ .gpword .L00434D14
/* 09F698 1000F698 F0409F4C */ .gpword .L00434CFC
/* 09F69C 1000F69C F0409F64 */ .gpword .L00434D14
/* 09F6A0 1000F6A0 F0409E88 */ .gpword .L00434C38
/* 09F6A4 1000F6A4 F040A04C */ .gpword .L00434DFC
/* 09F6A8 1000F6A8 F0409E88 */ .gpword .L00434C38
/* 09F6AC 1000F6AC F0409E88 */ .gpword .L00434C38
/* 09F6B0 1000F6B0 F0409F80 */ .gpword .L00434D30
/* 09F6B4 1000F6B4 F0409F80 */ .gpword .L00434D30
/* 09F6B8 1000F6B8 F0409F80 */ .gpword .L00434D30
/* 09F6BC 1000F6BC F0409F80 */ .gpword .L00434D30
/* 09F6C0 1000F6C0 F0409F80 */ .gpword .L00434D30
/* 09F6C4 1000F6C4 F0409F80 */ .gpword .L00434D30
/* 09F6C8 1000F6C8 F0409F80 */ .gpword .L00434D30
/* 09F6CC 1000F6CC F0409F80 */ .gpword .L00434D30
/* 09F6D0 1000F6D0 F0409E88 */ .gpword .L00434C38
/* 09F6D4 1000F6D4 F0409E88 */ .gpword .L00434C38
/* 09F6D8 1000F6D8 F0409E88 */ .gpword .L00434C38
/* 09F6DC 1000F6DC F0409E88 */ .gpword .L00434C38
/* 09F6E0 1000F6E0 F0409E88 */ .gpword .L00434C38
/* 09F6E4 1000F6E4 F0409E88 */ .gpword .L00434C38
/* 09F6E8 1000F6E8 F0409E88 */ .gpword .L00434C38
/* 09F6EC 1000F6EC F0409E88 */ .gpword .L00434C38
/* 09F6F0 1000F6F0 F040A04C */ .gpword .L00434DFC
/* 09F6F4 1000F6F4 F040A04C */ .gpword .L00434DFC
/* 09F6F8 1000F6F8 F0409E88 */ .gpword .L00434C38
/* 09F6FC 1000F6FC F0409E88 */ .gpword .L00434C38
/* 09F700 1000F700 F0409E88 */ .gpword .L00434C38
/* 09F704 1000F704 F0409E88 */ .gpword .L00434C38
/* 09F708 1000F708 F0409E88 */ .gpword .L00434C38
/* 09F70C 1000F70C F0409E88 */ .gpword .L00434C38
/* 09F710 1000F710 F0409F80 */ .gpword .L00434D30
/* 09F714 1000F714 F0409F80 */ .gpword .L00434D30
/* 09F718 1000F718 F0409F80 */ .gpword .L00434D30
/* 09F71C 1000F71C F0409F80 */ .gpword .L00434D30
/* 09F720 1000F720 F0409F80 */ .gpword .L00434D30
/* 09F724 1000F724 F040A04C */ .gpword .L00434DFC
/* 09F728 1000F728 F0409F80 */ .gpword .L00434D30
/* 09F72C 1000F72C F040A04C */ .gpword .L00434DFC
/* 09F730 1000F730 F0409ED0 */ .gpword .L00434C80
/* 09F734 1000F734 F040A04C */ .gpword .L00434DFC
/* 09F738 1000F738 F0409ED0 */ .gpword .L00434C80
/* 09F73C 1000F73C F0409ED0 */ .gpword .L00434C80
/* 09F740 1000F740 F0409ED0 */ .gpword .L00434C80
/* 09F744 1000F744 F040A04C */ .gpword .L00434DFC
/* 09F748 1000F748 F0409ED0 */ .gpword .L00434C80
/* 09F74C 1000F74C F0409ED0 */ .gpword .L00434C80

glabel jtbl_1000F750
/* 09F750 1000F750 F040A0CC */ .gpword .L00434E7C
/* 09F754 1000F754 F040A0CC */ .gpword .L00434E7C
/* 09F758 1000F758 F040A0CC */ .gpword .L00434E7C
/* 09F75C 1000F75C F040A7C0 */ .gpword .L00435570
/* 09F760 1000F760 F040A0B0 */ .gpword .L00434E60
/* 09F764 1000F764 F040A0B0 */ .gpword .L00434E60
/* 09F768 1000F768 F040A0B0 */ .gpword .L00434E60

glabel jtbl_1000F76C
/* 09F76C 1000F76C F040A12C */ .gpword .L00434EDC
/* 09F770 1000F770 F040A12C */ .gpword .L00434EDC
/* 09F774 1000F774 F040A1D0 */ .gpword .L00434F80
/* 09F778 1000F778 F040A1D0 */ .gpword .L00434F80
/* 09F77C 1000F77C F040A1D0 */ .gpword .L00434F80
/* 09F780 1000F780 F040A1D0 */ .gpword .L00434F80
/* 09F784 1000F784 F040A1D0 */ .gpword .L00434F80
/* 09F788 1000F788 F040A1D0 */ .gpword .L00434F80
/* 09F78C 1000F78C F040A180 */ .gpword .L00434F30
/* 09F790 1000F790 F040A180 */ .gpword .L00434F30
/* 09F794 1000F794 F040A1D0 */ .gpword .L00434F80
/* 09F798 1000F798 F040A1D0 */ .gpword .L00434F80
/* 09F79C 1000F79C F040A1D0 */ .gpword .L00434F80
/* 09F7A0 1000F7A0 F040A1D0 */ .gpword .L00434F80
/* 09F7A4 1000F7A4 F040A1D0 */ .gpword .L00434F80
/* 09F7A8 1000F7A8 F040A19C */ .gpword .L00434F4C

glabel jtbl_1000F7AC
/* 09F7AC 1000F7AC F040A3C4 */ .gpword .L00435174
/* 09F7B0 1000F7B0 F040A3C4 */ .gpword .L00435174
/* 09F7B4 1000F7B4 F040A3F8 */ .gpword .L004351A8
/* 09F7B8 1000F7B8 F040A760 */ .gpword .L00435510
/* 09F7BC 1000F7BC F040A374 */ .gpword .L00435124
/* 09F7C0 1000F7C0 F040A374 */ .gpword .L00435124
/* 09F7C4 1000F7C4 F040A3A8 */ .gpword .L00435158
/* 09F7C8 1000F7C8 F040A760 */ .gpword .L00435510
/* 09F7CC 1000F7CC F040A354 */ .gpword .L00435104
/* 09F7D0 1000F7D0 F040A760 */ .gpword .L00435510
/* 09F7D4 1000F7D4 F040A760 */ .gpword .L00435510
/* 09F7D8 1000F7D8 F040A760 */ .gpword .L00435510
/* 09F7DC 1000F7DC F040A760 */ .gpword .L00435510
/* 09F7E0 1000F7E0 F040A760 */ .gpword .L00435510
/* 09F7E4 1000F7E4 F040A760 */ .gpword .L00435510
/* 09F7E8 1000F7E8 F040A760 */ .gpword .L00435510
/* 09F7EC 1000F7EC F040A414 */ .gpword .L004351C4
/* 09F7F0 1000F7F0 F040A414 */ .gpword .L004351C4
/* 09F7F4 1000F7F4 F040A414 */ .gpword .L004351C4
/* 09F7F8 1000F7F8 F040A760 */ .gpword .L00435510
/* 09F7FC 1000F7FC F040A414 */ .gpword .L004351C4
/* 09F800 1000F800 F040A414 */ .gpword .L004351C4

glabel jtbl_1000F804
/* 09F804 1000F804 F040A500 */ .gpword .L004352B0
/* 09F808 1000F808 F040A500 */ .gpword .L004352B0
/* 09F80C 1000F80C F040A500 */ .gpword .L004352B0
/* 09F810 1000F810 F040A500 */ .gpword .L004352B0
/* 09F814 1000F814 F040A458 */ .gpword .L00435208
/* 09F818 1000F818 F040A458 */ .gpword .L00435208
/* 09F81C 1000F81C F040A458 */ .gpword .L00435208
/* 09F820 1000F820 F040A458 */ .gpword .L00435208
/* 09F824 1000F824 F040A458 */ .gpword .L00435208
/* 09F828 1000F828 F040A458 */ .gpword .L00435208
/* 09F82C 1000F82C F040A458 */ .gpword .L00435208
/* 09F830 1000F830 F040A458 */ .gpword .L00435208
/* 09F834 1000F834 F040A458 */ .gpword .L00435208
/* 09F838 1000F838 F040A458 */ .gpword .L00435208
/* 09F83C 1000F83C F040A458 */ .gpword .L00435208
/* 09F840 1000F840 F040A458 */ .gpword .L00435208
/* 09F844 1000F844 F040A730 */ .gpword .L004354E0
/* 09F848 1000F848 F040A6DC */ .gpword .L0043548C
/* 09F84C 1000F84C F040A690 */ .gpword .L00435440
/* 09F850 1000F850 F040A690 */ .gpword .L00435440
/* 09F854 1000F854 F040A730 */ .gpword .L004354E0
/* 09F858 1000F858 F040A458 */ .gpword .L00435208
/* 09F85C 1000F85C F040A458 */ .gpword .L00435208
/* 09F860 1000F860 F040A730 */ .gpword .L004354E0
/* 09F864 1000F864 F040A730 */ .gpword .L004354E0
/* 09F868 1000F868 F040A730 */ .gpword .L004354E0
/* 09F86C 1000F86C F040A730 */ .gpword .L004354E0
/* 09F870 1000F870 F040A730 */ .gpword .L004354E0
/* 09F874 1000F874 F040A730 */ .gpword .L004354E0
/* 09F878 1000F878 F040A730 */ .gpword .L004354E0
/* 09F87C 1000F87C F040A730 */ .gpword .L004354E0
/* 09F880 1000F880 F040A730 */ .gpword .L004354E0
/* 09F884 1000F884 F040A458 */ .gpword .L00435208
/* 09F888 1000F888 F040A458 */ .gpword .L00435208
/* 09F88C 1000F88C F040A730 */ .gpword .L004354E0
/* 09F890 1000F890 F040A730 */ .gpword .L004354E0
/* 09F894 1000F894 F040A458 */ .gpword .L00435208
/* 09F898 1000F898 F040A458 */ .gpword .L00435208
/* 09F89C 1000F89C F040A730 */ .gpword .L004354E0
/* 09F8A0 1000F8A0 F040A730 */ .gpword .L004354E0
/* 09F8A4 1000F8A4 F040A730 */ .gpword .L004354E0
/* 09F8A8 1000F8A8 F040A730 */ .gpword .L004354E0
/* 09F8AC 1000F8AC F040A730 */ .gpword .L004354E0
/* 09F8B0 1000F8B0 F040A730 */ .gpword .L004354E0
/* 09F8B4 1000F8B4 F040A730 */ .gpword .L004354E0
/* 09F8B8 1000F8B8 F040A730 */ .gpword .L004354E0
/* 09F8BC 1000F8BC F040A730 */ .gpword .L004354E0
/* 09F8C0 1000F8C0 F040A730 */ .gpword .L004354E0
/* 09F8C4 1000F8C4 F040A5DC */ .gpword .L0043538C
/* 09F8C8 1000F8C8 F040A5DC */ .gpword .L0043538C
/* 09F8CC 1000F8CC F040A5DC */ .gpword .L0043538C
/* 09F8D0 1000F8D0 F040A5DC */ .gpword .L0043538C
/* 09F8D4 1000F8D4 F040A5DC */ .gpword .L0043538C
/* 09F8D8 1000F8D8 F040A5DC */ .gpword .L0043538C
/* 09F8DC 1000F8DC F040A5DC */ .gpword .L0043538C
/* 09F8E0 1000F8E0 F040A5DC */ .gpword .L0043538C
/* 09F8E4 1000F8E4 F040A5DC */ .gpword .L0043538C
/* 09F8E8 1000F8E8 F040A5DC */ .gpword .L0043538C
/* 09F8EC 1000F8EC F040A5DC */ .gpword .L0043538C
/* 09F8F0 1000F8F0 F040A5DC */ .gpword .L0043538C
/* 09F8F4 1000F8F4 F040A5DC */ .gpword .L0043538C
/* 09F8F8 1000F8F8 F040A5DC */ .gpword .L0043538C
/* 09F8FC 1000F8FC F040A5DC */ .gpword .L0043538C
/* 09F900 1000F900 F040A5DC */ .gpword .L0043538C


.section .text
/* Generated by spimdisasm 1.12.4 */

glabel defuse # 270
/* 034924 00434924 3C1C0FBF */  lui         $gp, %hi(_gp_disp)
/* 034928 00434928 279C648C */  addiu       $gp, $gp, %lo(_gp_disp)
# _gp_disp: 0xFBF648C
/* 03492C 0043492C 0399E021 */  addu        $gp, $gp, $t9
/* 034930 00434930 27BDFFC0 */  addiu       $sp, $sp, -0x40
/* 034934 00434934 AFBF001C */  sw          $ra, 0x1C($sp)
/* 034938 00434938 AFBC0018 */  sw          $gp, 0x18($sp)
/* 03493C 0043493C AFA40040 */  sw          $a0, 0x40($sp)
/* 034940 00434940 AFA60048 */  sw          $a2, 0x48($sp)
/* 034944 00434944 ACA00008 */  sw          $zero, 0x8($a1)
/* 034948 00434948 ACA00004 */  sw          $zero, 0x4($a1)
/* 03494C 0043494C ACA00000 */  sw          $zero, 0x0($a1)
/* 034950 00434950 8FAE0048 */  lw          $t6, 0x48($sp)
/* 034954 00434954 00A03825 */  move        $a3, $a1
/* 034958 00434958 ADC00000 */  sw          $zero, 0x0($t6)
/* 03495C 0043495C 8FAF0048 */  lw          $t7, 0x48($sp)
/* 034960 00434960 ADE00004 */  sw          $zero, 0x4($t7)
/* 034964 00434964 8FB80048 */  lw          $t8, 0x48($sp)
/* 034968 00434968 AF000008 */  sw          $zero, 0x8($t8)
/* 03496C 0043496C 8FA90040 */  lw          $t1, 0x40($sp)
/* 034970 00434970 97B90040 */  lhu         $t9, 0x40($sp)
/* 034974 00434974 00095180 */  sll         $t2, $t1, 6
/* 034978 00434978 00091682 */  srl         $v0, $t1, 26
/* 03497C 0043497C 000A5EC2 */  srl         $t3, $t2, 27
/* 034980 00434980 2C410040 */  sltiu       $at, $v0, 0x40
/* 034984 00434984 3328001F */  andi        $t0, $t9, 0x1F
/* 034988 00434988 AFA8003C */  sw          $t0, 0x3C($sp)
/* 03498C 0043498C 102002ED */  beqz        $at, .L00435544
/* 034990 00434990 AFAB0038 */   sw         $t3, 0x38($sp)
/* 034994 00434994 8F818044 */  lw          $at, %got(jtbl_1000F500)($gp)
/* 034998 00434998 00026080 */  sll         $t4, $v0, 2
/* 03499C 0043499C 002C0821 */  addu        $at, $at, $t4
/* 0349A0 004349A0 8C2CF500 */  lw          $t4, %lo(jtbl_1000F500)($at)
/* 0349A4 004349A4 019C6021 */  addu        $t4, $t4, $gp
/* 0349A8 004349A8 01800008 */  jr          $t4
/* 0349AC 004349AC 00000000 */   nop
.L004349B0:
/* 0349B0 004349B0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0349B4 004349B4 00E02025 */  move        $a0, $a3
/* 0349B8 004349B8 8FA5003C */  lw          $a1, 0x3C($sp)
/* 0349BC 004349BC 0320F809 */  jalr        $t9
/* 0349C0 004349C0 00000000 */   nop
/* 0349C4 004349C4 8FBC0018 */  lw          $gp, 0x18($sp)
/* 0349C8 004349C8 8FA40048 */  lw          $a0, 0x48($sp)
/* 0349CC 004349CC 8FA50038 */  lw          $a1, 0x38($sp)
/* 0349D0 004349D0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0349D4 004349D4 0320F809 */  jalr        $t9
/* 0349D8 004349D8 00000000 */   nop
/* 0349DC 004349DC 100002E4 */  b           .L00435570
/* 0349E0 004349E0 8FBC0018 */   lw         $gp, 0x18($sp)
.L004349E4:
/* 0349E4 004349E4 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0349E8 004349E8 8FA40048 */  lw          $a0, 0x48($sp)
/* 0349EC 004349EC 8FA5003C */  lw          $a1, 0x3C($sp)
/* 0349F0 004349F0 0320F809 */  jalr        $t9
/* 0349F4 004349F4 00000000 */   nop
/* 0349F8 004349F8 8FBC0018 */  lw          $gp, 0x18($sp)
/* 0349FC 004349FC 8FA40048 */  lw          $a0, 0x48($sp)
/* 034A00 00434A00 8FA50038 */  lw          $a1, 0x38($sp)
/* 034A04 00434A04 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034A08 00434A08 0320F809 */  jalr        $t9
/* 034A0C 00434A0C 00000000 */   nop
/* 034A10 00434A10 100002D7 */  b           .L00435570
/* 034A14 00434A14 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434A18:
/* 034A18 00434A18 8FAD003C */  lw          $t5, 0x3C($sp)
/* 034A1C 00434A1C 2DA10014 */  sltiu       $at, $t5, 0x14
/* 034A20 00434A20 50200016 */  beql        $at, $zero, .L00434A7C
/* 034A24 00434A24 8FAE003C */   lw         $t6, 0x3C($sp)
/* 034A28 00434A28 8F818044 */  lw          $at, %got(jtbl_1000F600)($gp)
/* 034A2C 00434A2C 000D6880 */  sll         $t5, $t5, 2
/* 034A30 00434A30 002D0821 */  addu        $at, $at, $t5
/* 034A34 00434A34 8C2DF600 */  lw          $t5, %lo(jtbl_1000F600)($at)
/* 034A38 00434A38 01BC6821 */  addu        $t5, $t5, $gp
/* 034A3C 00434A3C 01A00008 */  jr          $t5
/* 034A40 00434A40 00000000 */   nop
.L00434A44:
/* 034A44 00434A44 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034A48 00434A48 00E02025 */  move        $a0, $a3
/* 034A4C 00434A4C 2405001F */  addiu       $a1, $zero, 0x1F
/* 034A50 00434A50 0320F809 */  jalr        $t9
/* 034A54 00434A54 00000000 */   nop
/* 034A58 00434A58 8FBC0018 */  lw          $gp, 0x18($sp)
.L00434A5C:
/* 034A5C 00434A5C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034A60 00434A60 8FA40048 */  lw          $a0, 0x48($sp)
/* 034A64 00434A64 8FA50038 */  lw          $a1, 0x38($sp)
/* 034A68 00434A68 0320F809 */  jalr        $t9
/* 034A6C 00434A6C 00000000 */   nop
/* 034A70 00434A70 100002BF */  b           .L00435570
/* 034A74 00434A74 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434A78:
/* 034A78 00434A78 8FAE003C */  lw          $t6, 0x3C($sp)
.L00434A7C:
/* 034A7C 00434A7C 8F988A30 */  lw          $t8, %got(bcond_name)($gp)
/* 034A80 00434A80 8F84805C */  lw          $a0, %got(__iob)($gp)
/* 034A84 00434A84 000E7880 */  sll         $t7, $t6, 2
/* 034A88 00434A88 01F8C821 */  addu        $t9, $t7, $t8
/* 034A8C 00434A8C 8F260000 */  lw          $a2, 0x0($t9)
/* 034A90 00434A90 8F998090 */  lw          $t9, %call16(fprintf)($gp)
/* 034A94 00434A94 8F858044 */  lw          $a1, %got(STR_1000F400)($gp)
/* 034A98 00434A98 24840020 */  addiu       $a0, $a0, 0x20
/* 034A9C 00434A9C 0320F809 */  jalr        $t9
/* 034AA0 00434AA0 24A5F400 */   addiu      $a1, $a1, %lo(STR_1000F400)
/* 034AA4 00434AA4 100002B2 */  b           .L00435570
/* 034AA8 00434AA8 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434AAC:
/* 034AAC 00434AAC 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034AB0 00434AB0 00E02025 */  move        $a0, $a3
/* 034AB4 00434AB4 2405001F */  addiu       $a1, $zero, 0x1F
/* 034AB8 00434AB8 0320F809 */  jalr        $t9
/* 034ABC 00434ABC 00000000 */   nop
/* 034AC0 00434AC0 100002AB */  b           .L00435570
/* 034AC4 00434AC4 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434AC8:
/* 034AC8 00434AC8 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034ACC 00434ACC 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034AD0 00434AD0 00E02025 */  move        $a0, $a3
/* 034AD4 00434AD4 0320F809 */  jalr        $t9
/* 034AD8 00434AD8 24A50020 */   addiu      $a1, $a1, 0x20
/* 034ADC 00434ADC 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034AE0 00434AE0 8FA40048 */  lw          $a0, 0x48($sp)
/* 034AE4 00434AE4 8FA50038 */  lw          $a1, 0x38($sp)
/* 034AE8 00434AE8 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034AEC 00434AEC 0320F809 */  jalr        $t9
/* 034AF0 00434AF0 00000000 */   nop
/* 034AF4 00434AF4 1000029E */  b           .L00435570
/* 034AF8 00434AF8 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434AFC:
/* 034AFC 00434AFC 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034B00 00434B00 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034B04 00434B04 00E02025 */  move        $a0, $a3
/* 034B08 00434B08 AFA70044 */  sw          $a3, 0x44($sp)
/* 034B0C 00434B0C 0320F809 */  jalr        $t9
/* 034B10 00434B10 24A50020 */   addiu      $a1, $a1, 0x20
/* 034B14 00434B14 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034B18 00434B18 8FA70044 */  lw          $a3, 0x44($sp)
/* 034B1C 00434B1C 8F888B10 */  lw          $t0, %got(fp32regs)($gp)
/* 034B20 00434B20 91080000 */  lbu         $t0, 0x0($t0)
/* 034B24 00434B24 15000007 */  bnez        $t0, .L00434B44
/* 034B28 00434B28 00000000 */   nop
/* 034B2C 00434B2C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034B30 00434B30 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034B34 00434B34 00E02025 */  move        $a0, $a3
/* 034B38 00434B38 0320F809 */  jalr        $t9
/* 034B3C 00434B3C 24A50021 */   addiu      $a1, $a1, 0x21
/* 034B40 00434B40 8FBC0018 */  lw          $gp, 0x18($sp)
.L00434B44:
/* 034B44 00434B44 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034B48 00434B48 8FA40048 */  lw          $a0, 0x48($sp)
/* 034B4C 00434B4C 8FA50038 */  lw          $a1, 0x38($sp)
/* 034B50 00434B50 0320F809 */  jalr        $t9
/* 034B54 00434B54 00000000 */   nop
/* 034B58 00434B58 10000285 */  b           .L00435570
/* 034B5C 00434B5C 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434B60:
/* 034B60 00434B60 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034B64 00434B64 8FA40048 */  lw          $a0, 0x48($sp)
/* 034B68 00434B68 8FA50038 */  lw          $a1, 0x38($sp)
/* 034B6C 00434B6C 0320F809 */  jalr        $t9
/* 034B70 00434B70 00000000 */   nop
/* 034B74 00434B74 1000027E */  b           .L00435570
/* 034B78 00434B78 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434B7C:
/* 034B7C 00434B7C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034B80 00434B80 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034B84 00434B84 8FA40048 */  lw          $a0, 0x48($sp)
/* 034B88 00434B88 0320F809 */  jalr        $t9
/* 034B8C 00434B8C 24A50020 */   addiu      $a1, $a1, 0x20
/* 034B90 00434B90 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034B94 00434B94 8FA40048 */  lw          $a0, 0x48($sp)
/* 034B98 00434B98 8FA50038 */  lw          $a1, 0x38($sp)
/* 034B9C 00434B9C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034BA0 00434BA0 0320F809 */  jalr        $t9
/* 034BA4 00434BA4 00000000 */   nop
/* 034BA8 00434BA8 10000271 */  b           .L00435570
/* 034BAC 00434BAC 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434BB0:
/* 034BB0 00434BB0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034BB4 00434BB4 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034BB8 00434BB8 8FA40048 */  lw          $a0, 0x48($sp)
/* 034BBC 00434BBC 0320F809 */  jalr        $t9
/* 034BC0 00434BC0 24A50020 */   addiu      $a1, $a1, 0x20
/* 034BC4 00434BC4 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034BC8 00434BC8 8F8A8B10 */  lw          $t2, %got(fp32regs)($gp)
/* 034BCC 00434BCC 914A0000 */  lbu         $t2, 0x0($t2)
/* 034BD0 00434BD0 15400007 */  bnez        $t2, .L00434BF0
/* 034BD4 00434BD4 00000000 */   nop
/* 034BD8 00434BD8 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034BDC 00434BDC 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034BE0 00434BE0 8FA40048 */  lw          $a0, 0x48($sp)
/* 034BE4 00434BE4 0320F809 */  jalr        $t9
/* 034BE8 00434BE8 24A50021 */   addiu      $a1, $a1, 0x21
/* 034BEC 00434BEC 8FBC0018 */  lw          $gp, 0x18($sp)
.L00434BF0:
/* 034BF0 00434BF0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034BF4 00434BF4 8FA40048 */  lw          $a0, 0x48($sp)
/* 034BF8 00434BF8 8FA50038 */  lw          $a1, 0x38($sp)
/* 034BFC 00434BFC 0320F809 */  jalr        $t9
/* 034C00 00434C00 00000000 */   nop
/* 034C04 00434C04 1000025A */  b           .L00435570
/* 034C08 00434C08 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434C0C:
/* 034C0C 00434C0C 8FAB0040 */  lw          $t3, 0x40($sp)
/* 034C10 00434C10 8F818044 */  lw          $at, %got(jtbl_1000F650)($gp)
/* 034C14 00434C14 97A50042 */  lhu         $a1, 0x42($sp)
/* 034C18 00434C18 3169003F */  andi        $t1, $t3, 0x3F
/* 034C1C 00434C1C 00094880 */  sll         $t1, $t1, 2
/* 034C20 00434C20 00290821 */  addu        $at, $at, $t1
/* 034C24 00434C24 8C29F650 */  lw          $t1, %lo(jtbl_1000F650)($at)
/* 034C28 00434C28 00052AC2 */  srl         $a1, $a1, 11
/* 034C2C 00434C2C 013C4821 */  addu        $t1, $t1, $gp
/* 034C30 00434C30 01200008 */  jr          $t1
/* 034C34 00434C34 00000000 */   nop
.L00434C38:
/* 034C38 00434C38 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034C3C 00434C3C 00E02025 */  move        $a0, $a3
/* 034C40 00434C40 0320F809 */  jalr        $t9
/* 034C44 00434C44 00000000 */   nop
/* 034C48 00434C48 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034C4C 00434C4C 8FA40048 */  lw          $a0, 0x48($sp)
/* 034C50 00434C50 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034C54 00434C54 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034C58 00434C58 0320F809 */  jalr        $t9
/* 034C5C 00434C5C 00000000 */   nop
/* 034C60 00434C60 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034C64 00434C64 8FA40048 */  lw          $a0, 0x48($sp)
/* 034C68 00434C68 8FA50038 */  lw          $a1, 0x38($sp)
/* 034C6C 00434C6C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034C70 00434C70 0320F809 */  jalr        $t9
/* 034C74 00434C74 00000000 */   nop
/* 034C78 00434C78 1000023D */  b           .L00435570
/* 034C7C 00434C7C 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434C80:
/* 034C80 00434C80 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034C84 00434C84 00E02025 */  move        $a0, $a3
/* 034C88 00434C88 0320F809 */  jalr        $t9
/* 034C8C 00434C8C 00000000 */   nop
/* 034C90 00434C90 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034C94 00434C94 8FA40048 */  lw          $a0, 0x48($sp)
/* 034C98 00434C98 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034C9C 00434C9C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034CA0 00434CA0 0320F809 */  jalr        $t9
/* 034CA4 00434CA4 00000000 */   nop
/* 034CA8 00434CA8 10000231 */  b           .L00435570
/* 034CAC 00434CAC 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434CB0:
/* 034CB0 00434CB0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034CB4 00434CB4 00E02025 */  move        $a0, $a3
/* 034CB8 00434CB8 0320F809 */  jalr        $t9
/* 034CBC 00434CBC 00000000 */   nop
/* 034CC0 00434CC0 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034CC4 00434CC4 8FA40048 */  lw          $a0, 0x48($sp)
/* 034CC8 00434CC8 8FA50038 */  lw          $a1, 0x38($sp)
/* 034CCC 00434CCC 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034CD0 00434CD0 0320F809 */  jalr        $t9
/* 034CD4 00434CD4 00000000 */   nop
/* 034CD8 00434CD8 10000225 */  b           .L00435570
/* 034CDC 00434CDC 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434CE0:
/* 034CE0 00434CE0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034CE4 00434CE4 8FA40048 */  lw          $a0, 0x48($sp)
/* 034CE8 00434CE8 8FA50038 */  lw          $a1, 0x38($sp)
/* 034CEC 00434CEC 0320F809 */  jalr        $t9
/* 034CF0 00434CF0 00000000 */   nop
/* 034CF4 00434CF4 1000021E */  b           .L00435570
/* 034CF8 00434CF8 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434CFC:
/* 034CFC 00434CFC 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034D00 00434D00 00E02025 */  move        $a0, $a3
/* 034D04 00434D04 0320F809 */  jalr        $t9
/* 034D08 00434D08 00000000 */   nop
/* 034D0C 00434D0C 10000218 */  b           .L00435570
/* 034D10 00434D10 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434D14:
/* 034D14 00434D14 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034D18 00434D18 8FA40048 */  lw          $a0, 0x48($sp)
/* 034D1C 00434D1C 8FA50038 */  lw          $a1, 0x38($sp)
/* 034D20 00434D20 0320F809 */  jalr        $t9
/* 034D24 00434D24 00000000 */   nop
/* 034D28 00434D28 10000211 */  b           .L00435570
/* 034D2C 00434D2C 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434D30:
/* 034D30 00434D30 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034D34 00434D34 8FA40048 */  lw          $a0, 0x48($sp)
/* 034D38 00434D38 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034D3C 00434D3C 0320F809 */  jalr        $t9
/* 034D40 00434D40 00000000 */   nop
/* 034D44 00434D44 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034D48 00434D48 8FA40048 */  lw          $a0, 0x48($sp)
/* 034D4C 00434D4C 8FA50038 */  lw          $a1, 0x38($sp)
/* 034D50 00434D50 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034D54 00434D54 0320F809 */  jalr        $t9
/* 034D58 00434D58 00000000 */   nop
/* 034D5C 00434D5C 10000204 */  b           .L00435570
/* 034D60 00434D60 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434D64:
/* 034D64 00434D64 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034D68 00434D68 00E02025 */  move        $a0, $a3
/* 034D6C 00434D6C 0320F809 */  jalr        $t9
/* 034D70 00434D70 00000000 */   nop
/* 034D74 00434D74 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034D78 00434D78 8FA40048 */  lw          $a0, 0x48($sp)
/* 034D7C 00434D7C 8FA50038 */  lw          $a1, 0x38($sp)
/* 034D80 00434D80 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034D84 00434D84 0320F809 */  jalr        $t9
/* 034D88 00434D88 00000000 */   nop
/* 034D8C 00434D8C 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034D90 00434D90 8FA40048 */  lw          $a0, 0x48($sp)
/* 034D94 00434D94 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034D98 00434D98 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034D9C 00434D9C 0320F809 */  jalr        $t9
/* 034DA0 00434DA0 00000000 */   nop
/* 034DA4 00434DA4 100001F2 */  b           .L00435570
/* 034DA8 00434DA8 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434DAC:
/* 034DAC 00434DAC 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034DB0 00434DB0 00E02025 */  move        $a0, $a3
/* 034DB4 00434DB4 0320F809 */  jalr        $t9
/* 034DB8 00434DB8 00000000 */   nop
/* 034DBC 00434DBC 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034DC0 00434DC0 8FA40048 */  lw          $a0, 0x48($sp)
/* 034DC4 00434DC4 8FA50038 */  lw          $a1, 0x38($sp)
/* 034DC8 00434DC8 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034DCC 00434DCC 0320F809 */  jalr        $t9
/* 034DD0 00434DD0 00000000 */   nop
/* 034DD4 00434DD4 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034DD8 00434DD8 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034DDC 00434DDC 8FA40048 */  lw          $a0, 0x48($sp)
/* 034DE0 00434DE0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034DE4 00434DE4 00052882 */  srl         $a1, $a1, 2
/* 034DE8 00434DE8 24A50040 */  addiu       $a1, $a1, 0x40
/* 034DEC 00434DEC 0320F809 */  jalr        $t9
/* 034DF0 00434DF0 00000000 */   nop
/* 034DF4 00434DF4 100001DE */  b           .L00435570
/* 034DF8 00434DF8 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434DFC:
/* 034DFC 00434DFC 8FAC0040 */  lw          $t4, 0x40($sp)
/* 034E00 00434E00 8F8F8A2C */  lw          $t7, %got(spec_name)($gp)
/* 034E04 00434E04 8F998090 */  lw          $t9, %call16(fprintf)($gp)
/* 034E08 00434E08 318D003F */  andi        $t5, $t4, 0x3F
/* 034E0C 00434E0C 8F84805C */  lw          $a0, %got(__iob)($gp)
/* 034E10 00434E10 8F858044 */  lw          $a1, %got(STR_1000F428)($gp)
/* 034E14 00434E14 000D7080 */  sll         $t6, $t5, 2
/* 034E18 00434E18 01CFC021 */  addu        $t8, $t6, $t7
/* 034E1C 00434E1C 8F060000 */  lw          $a2, 0x0($t8)
/* 034E20 00434E20 24840020 */  addiu       $a0, $a0, 0x20
/* 034E24 00434E24 0320F809 */  jalr        $t9
/* 034E28 00434E28 24A5F428 */   addiu      $a1, $a1, %lo(STR_1000F428)
/* 034E2C 00434E2C 100001D0 */  b           .L00435570
/* 034E30 00434E30 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434E34:
/* 034E34 00434E34 8FB90038 */  lw          $t9, 0x38($sp)
.L00434E38:
/* 034E38 00434E38 2F210007 */  sltiu       $at, $t9, 0x7
/* 034E3C 00434E3C 502001CD */  beql        $at, $zero, .L00435574
/* 034E40 00434E40 8FBF001C */   lw         $ra, 0x1C($sp)
/* 034E44 00434E44 8F818044 */  lw          $at, %got(jtbl_1000F750)($gp)
/* 034E48 00434E48 0019C880 */  sll         $t9, $t9, 2
/* 034E4C 00434E4C 00390821 */  addu        $at, $at, $t9
/* 034E50 00434E50 8C39F750 */  lw          $t9, %lo(jtbl_1000F750)($at)
/* 034E54 00434E54 033CC821 */  addu        $t9, $t9, $gp
/* 034E58 00434E58 03200008 */  jr          $t9
/* 034E5C 00434E5C 00000000 */   nop
.L00434E60:
/* 034E60 00434E60 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034E64 00434E64 8FA40048 */  lw          $a0, 0x48($sp)
/* 034E68 00434E68 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034E6C 00434E6C 0320F809 */  jalr        $t9
/* 034E70 00434E70 00000000 */   nop
/* 034E74 00434E74 100001BE */  b           .L00435570
/* 034E78 00434E78 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434E7C:
/* 034E7C 00434E7C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034E80 00434E80 00E02025 */  move        $a0, $a3
/* 034E84 00434E84 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034E88 00434E88 0320F809 */  jalr        $t9
/* 034E8C 00434E8C 00000000 */   nop
/* 034E90 00434E90 100001B7 */  b           .L00435570
/* 034E94 00434E94 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434E98:
/* 034E98 00434E98 8F888AD0 */  lw          $t0, %got(isa)($gp)
/* 034E9C 00434E9C 8FAA0040 */  lw          $t2, 0x40($sp)
/* 034EA0 00434EA0 24010001 */  addiu       $at, $zero, 0x1
/* 034EA4 00434EA4 91080000 */  lbu         $t0, 0x0($t0)
/* 034EA8 00434EA8 314B003F */  andi        $t3, $t2, 0x3F
/* 034EAC 00434EAC 5101FFE2 */  beql        $t0, $at, .L00434E38
/* 034EB0 00434EB0 8FB90038 */   lw         $t9, 0x38($sp)
/* 034EB4 00434EB4 2D610010 */  sltiu       $at, $t3, 0x10
/* 034EB8 00434EB8 50200032 */  beql        $at, $zero, .L00434F84
/* 034EBC 00434EBC 8FB90040 */   lw         $t9, 0x40($sp)
/* 034EC0 00434EC0 8F818044 */  lw          $at, %got(jtbl_1000F76C)($gp)
/* 034EC4 00434EC4 000B5880 */  sll         $t3, $t3, 2
/* 034EC8 00434EC8 002B0821 */  addu        $at, $at, $t3
/* 034ECC 00434ECC 8C2BF76C */  lw          $t3, %lo(jtbl_1000F76C)($at)
/* 034ED0 00434ED0 017C5821 */  addu        $t3, $t3, $gp
/* 034ED4 00434ED4 01600008 */  jr          $t3
/* 034ED8 00434ED8 00000000 */   nop
.L00434EDC:
/* 034EDC 00434EDC 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034EE0 00434EE0 8FA40048 */  lw          $a0, 0x48($sp)
/* 034EE4 00434EE4 8FA50038 */  lw          $a1, 0x38($sp)
/* 034EE8 00434EE8 0320F809 */  jalr        $t9
/* 034EEC 00434EEC AFA70044 */   sw         $a3, 0x44($sp)
/* 034EF0 00434EF0 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034EF4 00434EF4 8FA40048 */  lw          $a0, 0x48($sp)
/* 034EF8 00434EF8 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034EFC 00434EFC 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034F00 00434F00 0320F809 */  jalr        $t9
/* 034F04 00434F04 00000000 */   nop
/* 034F08 00434F08 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034F0C 00434F0C 8FA60040 */  lw          $a2, 0x40($sp)
/* 034F10 00434F10 8FA40044 */  lw          $a0, 0x44($sp)
/* 034F14 00434F14 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034F18 00434F18 00063540 */  sll         $a2, $a2, 21
/* 034F1C 00434F1C 000636C2 */  srl         $a2, $a2, 27
/* 034F20 00434F20 0320F809 */  jalr        $t9
/* 034F24 00434F24 24C50020 */   addiu      $a1, $a2, 0x20
/* 034F28 00434F28 10000191 */  b           .L00435570
/* 034F2C 00434F2C 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434F30:
/* 034F30 00434F30 97A50042 */  lhu         $a1, 0x42($sp)
/* 034F34 00434F34 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034F38 00434F38 8FA40048 */  lw          $a0, 0x48($sp)
/* 034F3C 00434F3C 00052AC2 */  srl         $a1, $a1, 11
/* 034F40 00434F40 0320F809 */  jalr        $t9
/* 034F44 00434F44 24A50020 */   addiu      $a1, $a1, 0x20
/* 034F48 00434F48 8FBC0018 */  lw          $gp, 0x18($sp)
.L00434F4C:
/* 034F4C 00434F4C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034F50 00434F50 8FA40048 */  lw          $a0, 0x48($sp)
/* 034F54 00434F54 8FA50038 */  lw          $a1, 0x38($sp)
/* 034F58 00434F58 0320F809 */  jalr        $t9
/* 034F5C 00434F5C 00000000 */   nop
/* 034F60 00434F60 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034F64 00434F64 8FA40048 */  lw          $a0, 0x48($sp)
/* 034F68 00434F68 8FA5003C */  lw          $a1, 0x3C($sp)
/* 034F6C 00434F6C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034F70 00434F70 0320F809 */  jalr        $t9
/* 034F74 00434F74 00000000 */   nop
/* 034F78 00434F78 1000017D */  b           .L00435570
/* 034F7C 00434F7C 8FBC0018 */   lw         $gp, 0x18($sp)
.L00434F80:
/* 034F80 00434F80 8FB90040 */  lw          $t9, 0x40($sp)
.L00434F84:
/* 034F84 00434F84 97A90040 */  lhu         $t1, 0x40($sp)
/* 034F88 00434F88 97AE0042 */  lhu         $t6, 0x42($sp)
/* 034F8C 00434F8C 00193540 */  sll         $a2, $t9, 21
/* 034F90 00434F90 00194180 */  sll         $t0, $t9, 6
/* 034F94 00434F94 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034F98 00434F98 000636C2 */  srl         $a2, $a2, 27
/* 034F9C 00434F9C 000856C2 */  srl         $t2, $t0, 27
/* 034FA0 00434FA0 312C001F */  andi        $t4, $t1, 0x1F
/* 034FA4 00434FA4 000E7AC2 */  srl         $t7, $t6, 11
/* 034FA8 00434FA8 258D0020 */  addiu       $t5, $t4, 0x20
/* 034FAC 00434FAC 25F80020 */  addiu       $t8, $t7, 0x20
/* 034FB0 00434FB0 24C50020 */  addiu       $a1, $a2, 0x20
/* 034FB4 00434FB4 254B0020 */  addiu       $t3, $t2, 0x20
/* 034FB8 00434FB8 AFAD003C */  sw          $t5, 0x3C($sp)
/* 034FBC 00434FBC AFB80034 */  sw          $t8, 0x34($sp)
/* 034FC0 00434FC0 AFAB0024 */  sw          $t3, 0x24($sp)
/* 034FC4 00434FC4 AFA50030 */  sw          $a1, 0x30($sp)
/* 034FC8 00434FC8 00E02025 */  move        $a0, $a3
/* 034FCC 00434FCC 0320F809 */  jalr        $t9
/* 034FD0 00434FD0 AFA70044 */   sw         $a3, 0x44($sp)
/* 034FD4 00434FD4 8FBC0018 */  lw          $gp, 0x18($sp)
/* 034FD8 00434FD8 8FA60030 */  lw          $a2, 0x30($sp)
/* 034FDC 00434FDC 8FA70044 */  lw          $a3, 0x44($sp)
/* 034FE0 00434FE0 8F898B10 */  lw          $t1, %got(fp32regs)($gp)
/* 034FE4 00434FE4 91290000 */  lbu         $t1, 0x0($t1)
/* 034FE8 00434FE8 15200007 */  bnez        $t1, .L00435008
/* 034FEC 00434FEC 00000000 */   nop
/* 034FF0 00434FF0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 034FF4 00434FF4 00E02025 */  move        $a0, $a3
/* 034FF8 00434FF8 24C50001 */  addiu       $a1, $a2, 0x1
/* 034FFC 00434FFC 0320F809 */  jalr        $t9
/* 035000 00435000 00000000 */   nop
/* 035004 00435004 8FBC0018 */  lw          $gp, 0x18($sp)
.L00435008:
/* 035008 00435008 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 03500C 0043500C 8FA40048 */  lw          $a0, 0x48($sp)
/* 035010 00435010 8FA5003C */  lw          $a1, 0x3C($sp)
/* 035014 00435014 0320F809 */  jalr        $t9
/* 035018 00435018 00000000 */   nop
/* 03501C 0043501C 8FBC0018 */  lw          $gp, 0x18($sp)
/* 035020 00435020 8FA40048 */  lw          $a0, 0x48($sp)
/* 035024 00435024 8FA50034 */  lw          $a1, 0x34($sp)
/* 035028 00435028 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 03502C 0043502C 0320F809 */  jalr        $t9
/* 035030 00435030 00000000 */   nop
/* 035034 00435034 8FBC0018 */  lw          $gp, 0x18($sp)
/* 035038 00435038 8FA40048 */  lw          $a0, 0x48($sp)
/* 03503C 0043503C 8FA50024 */  lw          $a1, 0x24($sp)
/* 035040 00435040 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035044 00435044 0320F809 */  jalr        $t9
/* 035048 00435048 00000000 */   nop
/* 03504C 0043504C 8FBC0018 */  lw          $gp, 0x18($sp)
/* 035050 00435050 8FAD0040 */  lw          $t5, 0x40($sp)
/* 035054 00435054 24010001 */  addiu       $at, $zero, 0x1
/* 035058 00435058 8F8C8B10 */  lw          $t4, %got(fp32regs)($gp)
/* 03505C 0043505C 31AE0007 */  andi        $t6, $t5, 0x7
/* 035060 00435060 918C0000 */  lbu         $t4, 0x0($t4)
/* 035064 00435064 55800143 */  bnel        $t4, $zero, .L00435574
/* 035068 00435068 8FBF001C */   lw         $ra, 0x1C($sp)
/* 03506C 0043506C 55C10141 */  bnel        $t6, $at, .L00435574
/* 035070 00435070 8FBF001C */   lw         $ra, 0x1C($sp)
/* 035074 00435074 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035078 00435078 8FA5003C */  lw          $a1, 0x3C($sp)
/* 03507C 0043507C 8FA40048 */  lw          $a0, 0x48($sp)
/* 035080 00435080 0320F809 */  jalr        $t9
/* 035084 00435084 24A50001 */   addiu      $a1, $a1, 0x1
/* 035088 00435088 8FBC0018 */  lw          $gp, 0x18($sp)
/* 03508C 0043508C 8FA50034 */  lw          $a1, 0x34($sp)
/* 035090 00435090 8FA40048 */  lw          $a0, 0x48($sp)
/* 035094 00435094 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035098 00435098 24A50001 */  addiu       $a1, $a1, 0x1
/* 03509C 0043509C 0320F809 */  jalr        $t9
/* 0350A0 004350A0 00000000 */   nop
/* 0350A4 004350A4 8FBC0018 */  lw          $gp, 0x18($sp)
/* 0350A8 004350A8 8FA50024 */  lw          $a1, 0x24($sp)
/* 0350AC 004350AC 8FA40048 */  lw          $a0, 0x48($sp)
/* 0350B0 004350B0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0350B4 004350B4 24A50001 */  addiu       $a1, $a1, 0x1
/* 0350B8 004350B8 0320F809 */  jalr        $t9
/* 0350BC 004350BC 00000000 */   nop
/* 0350C0 004350C0 1000012B */  b           .L00435570
/* 0350C4 004350C4 8FBC0018 */   lw         $gp, 0x18($sp)
.L004350C8:
/* 0350C8 004350C8 97AF0042 */  lhu         $t7, 0x42($sp)
/* 0350CC 004350CC 8FA80038 */  lw          $t0, 0x38($sp)
/* 0350D0 004350D0 000FC2C2 */  srl         $t8, $t7, 11
/* 0350D4 004350D4 27190020 */  addiu       $t9, $t8, 0x20
/* 0350D8 004350D8 2D010016 */  sltiu       $at, $t0, 0x16
/* 0350DC 004350DC AFB90034 */  sw          $t9, 0x34($sp)
/* 0350E0 004350E0 1020010B */  beqz        $at, .L00435510
/* 0350E4 004350E4 AFA80020 */   sw         $t0, 0x20($sp)
/* 0350E8 004350E8 8F818044 */  lw          $at, %got(jtbl_1000F7AC)($gp)
/* 0350EC 004350EC 00084080 */  sll         $t0, $t0, 2
/* 0350F0 004350F0 00280821 */  addu        $at, $at, $t0
/* 0350F4 004350F4 8C28F7AC */  lw          $t0, %lo(jtbl_1000F7AC)($at)
/* 0350F8 004350F8 011C4021 */  addu        $t0, $t0, $gp
/* 0350FC 004350FC 01000008 */  jr          $t0
/* 035100 00435100 00000000 */   nop
.L00435104:
/* 035104 00435104 8FA5003C */  lw          $a1, 0x3C($sp)
/* 035108 00435108 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 03510C 0043510C 8FA40048 */  lw          $a0, 0x48($sp)
/* 035110 00435110 00052882 */  srl         $a1, $a1, 2
/* 035114 00435114 0320F809 */  jalr        $t9
/* 035118 00435118 24A50040 */   addiu      $a1, $a1, 0x40
/* 03511C 0043511C 10000114 */  b           .L00435570
/* 035120 00435120 8FBC0018 */   lw         $gp, 0x18($sp)
.L00435124:
/* 035124 00435124 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035128 00435128 00E02025 */  move        $a0, $a3
/* 03512C 0043512C 8FA50034 */  lw          $a1, 0x34($sp)
/* 035130 00435130 0320F809 */  jalr        $t9
/* 035134 00435134 00000000 */   nop
/* 035138 00435138 8FBC0018 */  lw          $gp, 0x18($sp)
/* 03513C 0043513C 8FA40048 */  lw          $a0, 0x48($sp)
/* 035140 00435140 8FA5003C */  lw          $a1, 0x3C($sp)
/* 035144 00435144 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035148 00435148 0320F809 */  jalr        $t9
/* 03514C 0043514C 00000000 */   nop
/* 035150 00435150 10000107 */  b           .L00435570
/* 035154 00435154 8FBC0018 */   lw         $gp, 0x18($sp)
.L00435158:
/* 035158 00435158 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 03515C 0043515C 8FA40048 */  lw          $a0, 0x48($sp)
/* 035160 00435160 8FA5003C */  lw          $a1, 0x3C($sp)
/* 035164 00435164 0320F809 */  jalr        $t9
/* 035168 00435168 00000000 */   nop
/* 03516C 0043516C 10000100 */  b           .L00435570
/* 035170 00435170 8FBC0018 */   lw         $gp, 0x18($sp)
.L00435174:
/* 035174 00435174 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035178 00435178 00E02025 */  move        $a0, $a3
/* 03517C 0043517C 8FA5003C */  lw          $a1, 0x3C($sp)
/* 035180 00435180 0320F809 */  jalr        $t9
/* 035184 00435184 00000000 */   nop
/* 035188 00435188 8FBC0018 */  lw          $gp, 0x18($sp)
/* 03518C 0043518C 8FA40048 */  lw          $a0, 0x48($sp)
/* 035190 00435190 8FA50034 */  lw          $a1, 0x34($sp)
/* 035194 00435194 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035198 00435198 0320F809 */  jalr        $t9
/* 03519C 0043519C 00000000 */   nop
/* 0351A0 004351A0 100000F3 */  b           .L00435570
/* 0351A4 004351A4 8FBC0018 */   lw         $gp, 0x18($sp)
.L004351A8:
/* 0351A8 004351A8 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0351AC 004351AC 00E02025 */  move        $a0, $a3
/* 0351B0 004351B0 8FA5003C */  lw          $a1, 0x3C($sp)
/* 0351B4 004351B4 0320F809 */  jalr        $t9
/* 0351B8 004351B8 00000000 */   nop
/* 0351BC 004351BC 100000EC */  b           .L00435570
/* 0351C0 004351C0 8FBC0018 */   lw         $gp, 0x18($sp)
.L004351C4:
/* 0351C4 004351C4 8FA90040 */  lw          $t1, 0x40($sp)
/* 0351C8 004351C8 8FAA003C */  lw          $t2, 0x3C($sp)
/* 0351CC 004351CC 00093540 */  sll         $a2, $t1, 21
/* 0351D0 004351D0 3122003F */  andi        $v0, $t1, 0x3F
/* 0351D4 004351D4 000636C2 */  srl         $a2, $a2, 27
/* 0351D8 004351D8 2C410040 */  sltiu       $at, $v0, 0x40
/* 0351DC 004351DC 254B0020 */  addiu       $t3, $t2, 0x20
/* 0351E0 004351E0 AFAB003C */  sw          $t3, 0x3C($sp)
/* 0351E4 004351E4 102000BE */  beqz        $at, .L004354E0
/* 0351E8 004351E8 24C60020 */   addiu      $a2, $a2, 0x20
/* 0351EC 004351EC 8F818044 */  lw          $at, %got(jtbl_1000F804)($gp)
/* 0351F0 004351F0 00026080 */  sll         $t4, $v0, 2
/* 0351F4 004351F4 002C0821 */  addu        $at, $at, $t4
/* 0351F8 004351F8 8C2CF804 */  lw          $t4, %lo(jtbl_1000F804)($at)
/* 0351FC 004351FC 019C6021 */  addu        $t4, $t4, $gp
/* 035200 00435200 01800008 */  jr          $t4
/* 035204 00435204 00000000 */   nop
.L00435208:
/* 035208 00435208 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 03520C 0043520C 00E02025 */  move        $a0, $a3
/* 035210 00435210 00C02825 */  move        $a1, $a2
/* 035214 00435214 AFA60030 */  sw          $a2, 0x30($sp)
/* 035218 00435218 0320F809 */  jalr        $t9
/* 03521C 0043521C AFA70044 */   sw         $a3, 0x44($sp)
/* 035220 00435220 8FBC0018 */  lw          $gp, 0x18($sp)
/* 035224 00435224 8FA60030 */  lw          $a2, 0x30($sp)
/* 035228 00435228 8FA70044 */  lw          $a3, 0x44($sp)
/* 03522C 0043522C 8F8D8B10 */  lw          $t5, %got(fp32regs)($gp)
/* 035230 00435230 91AD0000 */  lbu         $t5, 0x0($t5)
/* 035234 00435234 15A00007 */  bnez        $t5, .L00435254
/* 035238 00435238 00000000 */   nop
/* 03523C 0043523C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035240 00435240 00E02025 */  move        $a0, $a3
/* 035244 00435244 24C50001 */  addiu       $a1, $a2, 0x1
/* 035248 00435248 0320F809 */  jalr        $t9
/* 03524C 0043524C 00000000 */   nop
/* 035250 00435250 8FBC0018 */  lw          $gp, 0x18($sp)
.L00435254:
/* 035254 00435254 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035258 00435258 8FA40048 */  lw          $a0, 0x48($sp)
/* 03525C 0043525C 8FA50034 */  lw          $a1, 0x34($sp)
/* 035260 00435260 0320F809 */  jalr        $t9
/* 035264 00435264 00000000 */   nop
/* 035268 00435268 8FBC0018 */  lw          $gp, 0x18($sp)
/* 03526C 0043526C 8FA20020 */  lw          $v0, 0x20($sp)
/* 035270 00435270 24010011 */  addiu       $at, $zero, 0x11
/* 035274 00435274 8F8E8B10 */  lw          $t6, %got(fp32regs)($gp)
/* 035278 00435278 91CE0000 */  lbu         $t6, 0x0($t6)
/* 03527C 0043527C 55C000BD */  bnel        $t6, $zero, .L00435574
/* 035280 00435280 8FBF001C */   lw         $ra, 0x1C($sp)
/* 035284 00435284 10410003 */  beq         $v0, $at, .L00435294
/* 035288 00435288 24010012 */   addiu      $at, $zero, 0x12
/* 03528C 0043528C 544100B9 */  bnel        $v0, $at, .L00435574
/* 035290 00435290 8FBF001C */   lw         $ra, 0x1C($sp)
.L00435294:
/* 035294 00435294 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035298 00435298 8FA50034 */  lw          $a1, 0x34($sp)
/* 03529C 0043529C 8FA40048 */  lw          $a0, 0x48($sp)
/* 0352A0 004352A0 0320F809 */  jalr        $t9
/* 0352A4 004352A4 24A50001 */   addiu      $a1, $a1, 0x1
/* 0352A8 004352A8 100000B1 */  b           .L00435570
/* 0352AC 004352AC 8FBC0018 */   lw         $gp, 0x18($sp)
.L004352B0:
/* 0352B0 004352B0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0352B4 004352B4 00E02025 */  move        $a0, $a3
/* 0352B8 004352B8 00C02825 */  move        $a1, $a2
/* 0352BC 004352BC AFA60030 */  sw          $a2, 0x30($sp)
/* 0352C0 004352C0 0320F809 */  jalr        $t9
/* 0352C4 004352C4 AFA70044 */   sw         $a3, 0x44($sp)
/* 0352C8 004352C8 8FBC0018 */  lw          $gp, 0x18($sp)
/* 0352CC 004352CC 8FA60030 */  lw          $a2, 0x30($sp)
/* 0352D0 004352D0 8FA70044 */  lw          $a3, 0x44($sp)
/* 0352D4 004352D4 8F8F8B10 */  lw          $t7, %got(fp32regs)($gp)
/* 0352D8 004352D8 91EF0000 */  lbu         $t7, 0x0($t7)
/* 0352DC 004352DC 15E00007 */  bnez        $t7, .L004352FC
/* 0352E0 004352E0 00000000 */   nop
/* 0352E4 004352E4 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0352E8 004352E8 00E02025 */  move        $a0, $a3
/* 0352EC 004352EC 24C50001 */  addiu       $a1, $a2, 0x1
/* 0352F0 004352F0 0320F809 */  jalr        $t9
/* 0352F4 004352F4 00000000 */   nop
/* 0352F8 004352F8 8FBC0018 */  lw          $gp, 0x18($sp)
.L004352FC:
/* 0352FC 004352FC 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035300 00435300 8FA40048 */  lw          $a0, 0x48($sp)
/* 035304 00435304 8FA5003C */  lw          $a1, 0x3C($sp)
/* 035308 00435308 0320F809 */  jalr        $t9
/* 03530C 0043530C 00000000 */   nop
/* 035310 00435310 8FBC0018 */  lw          $gp, 0x18($sp)
/* 035314 00435314 8FA40048 */  lw          $a0, 0x48($sp)
/* 035318 00435318 8FA50034 */  lw          $a1, 0x34($sp)
/* 03531C 0043531C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035320 00435320 0320F809 */  jalr        $t9
/* 035324 00435324 00000000 */   nop
/* 035328 00435328 8FBC0018 */  lw          $gp, 0x18($sp)
/* 03532C 0043532C 8F988B10 */  lw          $t8, %got(fp32regs)($gp)
/* 035330 00435330 93180000 */  lbu         $t8, 0x0($t8)
/* 035334 00435334 5700008F */  bnel        $t8, $zero, .L00435574
/* 035338 00435338 8FBF001C */   lw         $ra, 0x1C($sp)
/* 03533C 0043533C 8FB90020 */  lw          $t9, 0x20($sp)
/* 035340 00435340 24010011 */  addiu       $at, $zero, 0x11
/* 035344 00435344 13210003 */  beq         $t9, $at, .L00435354
/* 035348 00435348 24010012 */   addiu      $at, $zero, 0x12
/* 03534C 0043534C 57210089 */  bnel        $t9, $at, .L00435574
/* 035350 00435350 8FBF001C */   lw         $ra, 0x1C($sp)
.L00435354:
/* 035354 00435354 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035358 00435358 8FA5003C */  lw          $a1, 0x3C($sp)
/* 03535C 0043535C 8FA40048 */  lw          $a0, 0x48($sp)
/* 035360 00435360 0320F809 */  jalr        $t9
/* 035364 00435364 24A50001 */   addiu      $a1, $a1, 0x1
/* 035368 00435368 8FBC0018 */  lw          $gp, 0x18($sp)
/* 03536C 0043536C 8FA50034 */  lw          $a1, 0x34($sp)
/* 035370 00435370 8FA40048 */  lw          $a0, 0x48($sp)
/* 035374 00435374 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035378 00435378 24A50001 */  addiu       $a1, $a1, 0x1
/* 03537C 0043537C 0320F809 */  jalr        $t9
/* 035380 00435380 00000000 */   nop
/* 035384 00435384 1000007A */  b           .L00435570
/* 035388 00435388 8FBC0018 */   lw         $gp, 0x18($sp)
.L0043538C:
/* 03538C 0043538C 8FA50040 */  lw          $a1, 0x40($sp)
/* 035390 00435390 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035394 00435394 00E02025 */  move        $a0, $a3
/* 035398 00435398 00052D40 */  sll         $a1, $a1, 21
/* 03539C 0043539C 00052EC2 */  srl         $a1, $a1, 27
/* 0353A0 004353A0 00052882 */  srl         $a1, $a1, 2
/* 0353A4 004353A4 0320F809 */  jalr        $t9
/* 0353A8 004353A8 24A50040 */   addiu      $a1, $a1, 0x40
/* 0353AC 004353AC 8FBC0018 */  lw          $gp, 0x18($sp)
/* 0353B0 004353B0 8FA40048 */  lw          $a0, 0x48($sp)
/* 0353B4 004353B4 8FA5003C */  lw          $a1, 0x3C($sp)
/* 0353B8 004353B8 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0353BC 004353BC 0320F809 */  jalr        $t9
/* 0353C0 004353C0 00000000 */   nop
/* 0353C4 004353C4 8FBC0018 */  lw          $gp, 0x18($sp)
/* 0353C8 004353C8 8FA40048 */  lw          $a0, 0x48($sp)
/* 0353CC 004353CC 8FA50034 */  lw          $a1, 0x34($sp)
/* 0353D0 004353D0 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0353D4 004353D4 0320F809 */  jalr        $t9
/* 0353D8 004353D8 00000000 */   nop
/* 0353DC 004353DC 8FBC0018 */  lw          $gp, 0x18($sp)
/* 0353E0 004353E0 8FA20020 */  lw          $v0, 0x20($sp)
/* 0353E4 004353E4 24010011 */  addiu       $at, $zero, 0x11
/* 0353E8 004353E8 8F888B10 */  lw          $t0, %got(fp32regs)($gp)
/* 0353EC 004353EC 91080000 */  lbu         $t0, 0x0($t0)
/* 0353F0 004353F0 55000060 */  bnel        $t0, $zero, .L00435574
/* 0353F4 004353F4 8FBF001C */   lw         $ra, 0x1C($sp)
/* 0353F8 004353F8 10410003 */  beq         $v0, $at, .L00435408
/* 0353FC 004353FC 24010012 */   addiu      $at, $zero, 0x12
/* 035400 00435400 5441005C */  bnel        $v0, $at, .L00435574
/* 035404 00435404 8FBF001C */   lw         $ra, 0x1C($sp)
.L00435408:
/* 035408 00435408 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 03540C 0043540C 8FA5003C */  lw          $a1, 0x3C($sp)
/* 035410 00435410 8FA40048 */  lw          $a0, 0x48($sp)
/* 035414 00435414 0320F809 */  jalr        $t9
/* 035418 00435418 24A50001 */   addiu      $a1, $a1, 0x1
/* 03541C 0043541C 8FBC0018 */  lw          $gp, 0x18($sp)
/* 035420 00435420 8FA50034 */  lw          $a1, 0x34($sp)
/* 035424 00435424 8FA40048 */  lw          $a0, 0x48($sp)
/* 035428 00435428 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 03542C 0043542C 24A50001 */  addiu       $a1, $a1, 0x1
/* 035430 00435430 0320F809 */  jalr        $t9
/* 035434 00435434 00000000 */   nop
/* 035438 00435438 1000004D */  b           .L00435570
/* 03543C 0043543C 8FBC0018 */   lw         $gp, 0x18($sp)
.L00435440:
/* 035440 00435440 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035444 00435444 00E02025 */  move        $a0, $a3
/* 035448 00435448 8FA50034 */  lw          $a1, 0x34($sp)
/* 03544C 0043544C 0320F809 */  jalr        $t9
/* 035450 00435450 00000000 */   nop
/* 035454 00435454 8FBC0018 */  lw          $gp, 0x18($sp)
/* 035458 00435458 8FA40048 */  lw          $a0, 0x48($sp)
/* 03545C 0043545C 8FA50038 */  lw          $a1, 0x38($sp)
/* 035460 00435460 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035464 00435464 0320F809 */  jalr        $t9
/* 035468 00435468 00000000 */   nop
/* 03546C 0043546C 8FBC0018 */  lw          $gp, 0x18($sp)
/* 035470 00435470 8FA40048 */  lw          $a0, 0x48($sp)
/* 035474 00435474 8FA5003C */  lw          $a1, 0x3C($sp)
/* 035478 00435478 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 03547C 0043547C 0320F809 */  jalr        $t9
/* 035480 00435480 00000000 */   nop
/* 035484 00435484 1000003A */  b           .L00435570
/* 035488 00435488 8FBC0018 */   lw         $gp, 0x18($sp)
.L0043548C:
/* 03548C 0043548C 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 035490 00435490 00E02025 */  move        $a0, $a3
/* 035494 00435494 8FA50034 */  lw          $a1, 0x34($sp)
/* 035498 00435498 0320F809 */  jalr        $t9
/* 03549C 0043549C 00000000 */   nop
/* 0354A0 004354A0 8FBC0018 */  lw          $gp, 0x18($sp)
/* 0354A4 004354A4 8FA40048 */  lw          $a0, 0x48($sp)
/* 0354A8 004354A8 8FA50038 */  lw          $a1, 0x38($sp)
/* 0354AC 004354AC 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0354B0 004354B0 0320F809 */  jalr        $t9
/* 0354B4 004354B4 00000000 */   nop
/* 0354B8 004354B8 8FBC0018 */  lw          $gp, 0x18($sp)
/* 0354BC 004354BC 8FA5003C */  lw          $a1, 0x3C($sp)
/* 0354C0 004354C0 8FA40048 */  lw          $a0, 0x48($sp)
/* 0354C4 004354C4 8F998364 */  lw          $t9, %call16(addset)($gp)
/* 0354C8 004354C8 00052882 */  srl         $a1, $a1, 2
/* 0354CC 004354CC 24A50040 */  addiu       $a1, $a1, 0x40
/* 0354D0 004354D0 0320F809 */  jalr        $t9
/* 0354D4 004354D4 00000000 */   nop
/* 0354D8 004354D8 10000025 */  b           .L00435570
/* 0354DC 004354DC 8FBC0018 */   lw         $gp, 0x18($sp)
.L004354E0:
/* 0354E0 004354E0 8F8B8A34 */  lw          $t3, %got(cop1func_name)($gp)
/* 0354E4 004354E4 8F998090 */  lw          $t9, %call16(fprintf)($gp)
/* 0354E8 004354E8 8F84805C */  lw          $a0, %got(__iob)($gp)
/* 0354EC 004354EC 8F858044 */  lw          $a1, %got(STR_1000F450)($gp)
/* 0354F0 004354F0 00025080 */  sll         $t2, $v0, 2
/* 0354F4 004354F4 014B4821 */  addu        $t1, $t2, $t3
/* 0354F8 004354F8 8D260000 */  lw          $a2, 0x0($t1)
/* 0354FC 004354FC 24840020 */  addiu       $a0, $a0, 0x20
/* 035500 00435500 0320F809 */  jalr        $t9
/* 035504 00435504 24A5F450 */   addiu      $a1, $a1, %lo(STR_1000F450)
/* 035508 00435508 10000019 */  b           .L00435570
/* 03550C 0043550C 8FBC0018 */   lw         $gp, 0x18($sp)
.L00435510:
/* 035510 00435510 8FAC0038 */  lw          $t4, 0x38($sp)
/* 035514 00435514 8F8E8984 */  lw          $t6, %got(cop1op_name)($gp)
/* 035518 00435518 8F998090 */  lw          $t9, %call16(fprintf)($gp)
/* 03551C 0043551C 8F84805C */  lw          $a0, %got(__iob)($gp)
/* 035520 00435520 8F858044 */  lw          $a1, %got(STR_1000F478)($gp)
/* 035524 00435524 000C6880 */  sll         $t5, $t4, 2
/* 035528 00435528 01AE7821 */  addu        $t7, $t5, $t6
/* 03552C 0043552C 8DE60000 */  lw          $a2, 0x0($t7)
/* 035530 00435530 24840020 */  addiu       $a0, $a0, 0x20
/* 035534 00435534 0320F809 */  jalr        $t9
/* 035538 00435538 24A5F478 */   addiu      $a1, $a1, %lo(STR_1000F478)
/* 03553C 0043553C 1000000C */  b           .L00435570
/* 035540 00435540 8FBC0018 */   lw         $gp, 0x18($sp)
.L00435544:
/* 035544 00435544 8F998A28 */  lw          $t9, %got(op_name)($gp)
/* 035548 00435548 0002C080 */  sll         $t8, $v0, 2
/* 03554C 0043554C 8F84805C */  lw          $a0, %got(__iob)($gp)
/* 035550 00435550 03194021 */  addu        $t0, $t8, $t9
/* 035554 00435554 8F998090 */  lw          $t9, %call16(fprintf)($gp)
/* 035558 00435558 8F858044 */  lw          $a1, %got(STR_1000F4A0)($gp)
/* 03555C 0043555C 8D060000 */  lw          $a2, 0x0($t0)
/* 035560 00435560 24840020 */  addiu       $a0, $a0, 0x20
/* 035564 00435564 0320F809 */  jalr        $t9
/* 035568 00435568 24A5F4A0 */   addiu      $a1, $a1, %lo(STR_1000F4A0)
/* 03556C 0043556C 8FBC0018 */  lw          $gp, 0x18($sp)
.L00435570:
/* 035570 00435570 8FBF001C */  lw          $ra, 0x1C($sp)
.L00435574:
/* 035574 00435574 27BD0040 */  addiu       $sp, $sp, 0x40
/* 035578 00435578 03E00008 */  jr          $ra
/* 03557C 0043557C 00000000 */   nop
)
#endif

#pragma GLOBAL_ASM("asm/7.1/functions/as1/eligible.s")

#ifdef GLOBAL_ASM_FILE
GLOBAL_ASM(
.section .rodata
/* .late_rodata_alignment 4 */
glabel jtbl_1000F9C4
/* 09F9C4 1000F9C4 F040A970 */ .gpword .L00435720
/* 09F9C8 1000F9C8 F040A9C4 */ .gpword .L00435774
/* 09F9CC 1000F9CC F040A9C4 */ .gpword .L00435774
/* 09F9D0 1000F9D0 F040A9C4 */ .gpword .L00435774
/* 09F9D4 1000F9D4 F040A9C4 */ .gpword .L00435774
/* 09F9D8 1000F9D8 F040A9C4 */ .gpword .L00435774
/* 09F9DC 1000F9DC F040A9C4 */ .gpword .L00435774
/* 09F9E0 1000F9E0 F040A9C4 */ .gpword .L00435774
/* 09F9E4 1000F9E4 F040A9C4 */ .gpword .L00435774
/* 09F9E8 1000F9E8 F040A998 */ .gpword .L00435748
/* 09F9EC 1000F9EC F040A998 */ .gpword .L00435748
/* 09F9F0 1000F9F0 F040A998 */ .gpword .L00435748
/* 09F9F4 1000F9F4 F040A998 */ .gpword .L00435748
/* 09F9F8 1000F9F8 F040A998 */ .gpword .L00435748
/* 09F9FC 1000F9FC F040A998 */ .gpword .L00435748
/* 09FA00 1000FA00 F040A998 */ .gpword .L00435748
/* 09FA04 1000FA04 F040A9C4 */ .gpword .L00435774
/* 09FA08 1000FA08 F040A9C4 */ .gpword .L00435774
/* 09FA0C 1000FA0C F040A9C4 */ .gpword .L00435774
/* 09FA10 1000FA10 F040A9C4 */ .gpword .L00435774
/* 09FA14 1000FA14 F040A9C4 */ .gpword .L00435774
/* 09FA18 1000FA18 F040A9C4 */ .gpword .L00435774
/* 09FA1C 1000FA1C F040A9C4 */ .gpword .L00435774
/* 09FA20 1000FA20 F040A9C4 */ .gpword .L00435774
/* 09FA24 1000FA24 F040A9C4 */ .gpword .L00435774
/* 09FA28 1000FA28 F040A998 */ .gpword .L00435748
/* 09FA2C 1000FA2C F040A9A0 */ .gpword .L00435750
/* 09FA30 1000FA30 F040A9A0 */ .gpword .L00435750
/* 09FA34 1000FA34 F040A9C4 */ .gpword .L00435774
/* 09FA38 1000FA38 F040A9C4 */ .gpword .L00435774
/* 09FA3C 1000FA3C F040A9C4 */ .gpword .L00435774
/* 09FA40 1000FA40 F040A9C4 */ .gpword .L00435774
/* 09FA44 1000FA44 F040A9A0 */ .gpword .L00435750
/* 09FA48 1000FA48 F040A9A0 */ .gpword .L00435750
/* 09FA4C 1000FA4C F040A9A0 */ .gpword .L00435750
/* 09FA50 1000FA50 F040A9A0 */ .gpword .L00435750
/* 09FA54 1000FA54 F040A9A0 */ .gpword .L00435750
/* 09FA58 1000FA58 F040A9A0 */ .gpword .L00435750
/* 09FA5C 1000FA5C F040A9A0 */ .gpword .L00435750
/* 09FA60 1000FA60 F040A9A0 */ .gpword .L00435750
/* 09FA64 1000FA64 F040A9C4 */ .gpword .L00435774
/* 09FA68 1000FA68 F040A9C4 */ .gpword .L00435774
/* 09FA6C 1000FA6C F040A9C4 */ .gpword .L00435774
/* 09FA70 1000FA70 F040A9C4 */ .gpword .L00435774
/* 09FA74 1000FA74 F040A9C4 */ .gpword .L00435774
/* 09FA78 1000FA78 F040A9C4 */ .gpword .L00435774
/* 09FA7C 1000FA7C F040A9C4 */ .gpword .L00435774
/* 09FA80 1000FA80 F040A9C4 */ .gpword .L00435774
/* 09FA84 1000FA84 F040A9A0 */ .gpword .L00435750
/* 09FA88 1000FA88 F040A9C4 */ .gpword .L00435774
/* 09FA8C 1000FA8C F040A9C4 */ .gpword .L00435774
/* 09FA90 1000FA90 F040A9C4 */ .gpword .L00435774
/* 09FA94 1000FA94 F040A9A0 */ .gpword .L00435750
/* 09FA98 1000FA98 F040A9C4 */ .gpword .L00435774
/* 09FA9C 1000FA9C F040A9C4 */ .gpword .L00435774
/* 09FAA0 1000FAA0 F040A9A0 */ .gpword .L00435750

glabel jtbl_1000FAA4
/* 09FAA4 1000FAA4 F040A990 */ .gpword .L00435740
/* 09FAA8 1000FAA8 F040A9C4 */ .gpword .L00435774
/* 09FAAC 1000FAAC F040A990 */ .gpword .L00435740
/* 09FAB0 1000FAB0 F040A990 */ .gpword .L00435740
/* 09FAB4 1000FAB4 F040A990 */ .gpword .L00435740
/* 09FAB8 1000FAB8 F040A9C4 */ .gpword .L00435774
/* 09FABC 1000FABC F040A990 */ .gpword .L00435740
/* 09FAC0 1000FAC0 F040A990 */ .gpword .L00435740
/* 09FAC4 1000FAC4 F040A9C4 */ .gpword .L00435774
/* 09FAC8 1000FAC8 F040A9C4 */ .gpword .L00435774
/* 09FACC 1000FACC F040A9C4 */ .gpword .L00435774
/* 09FAD0 1000FAD0 F040A9C4 */ .gpword .L00435774
/* 09FAD4 1000FAD4 F040A9C4 */ .gpword .L00435774
/* 09FAD8 1000FAD8 F040A9C4 */ .gpword .L00435774
/* 09FADC 1000FADC F040A9C4 */ .gpword .L00435774
/* 09FAE0 1000FAE0 F040A9C4 */ .gpword .L00435774
/* 09FAE4 1000FAE4 F040A990 */ .gpword .L00435740
/* 09FAE8 1000FAE8 F040A9C4 */ .gpword .L00435774
/* 09FAEC 1000FAEC F040A990 */ .gpword .L00435740
/* 09FAF0 1000FAF0 F040A9C4 */ .gpword .L00435774
/* 09FAF4 1000FAF4 F040A990 */ .gpword .L00435740
/* 09FAF8 1000FAF8 F040A9C4 */ .gpword .L00435774
/* 09FAFC 1000FAFC F040A990 */ .gpword .L00435740
/* 09FB00 1000FB00 F040A990 */ .gpword .L00435740
/* 09FB04 1000FB04 F040A9C4 */ .gpword .L00435774
/* 09FB08 1000FB08 F040A9C4 */ .gpword .L00435774
/* 09FB0C 1000FB0C F040A9C4 */ .gpword .L00435774
/* 09FB10 1000FB10 F040A9C4 */ .gpword .L00435774
/* 09FB14 1000FB14 F040A9C4 */ .gpword .L00435774
/* 09FB18 1000FB18 F040A9C4 */ .gpword .L00435774
/* 09FB1C 1000FB1C F040A9C4 */ .gpword .L00435774
/* 09FB20 1000FB20 F040A9C4 */ .gpword .L00435774
/* 09FB24 1000FB24 F040A9C4 */ .gpword .L00435774
/* 09FB28 1000FB28 F040A990 */ .gpword .L00435740
/* 09FB2C 1000FB2C F040A9C4 */ .gpword .L00435774
/* 09FB30 1000FB30 F040A990 */ .gpword .L00435740
/* 09FB34 1000FB34 F040A990 */ .gpword .L00435740
/* 09FB38 1000FB38 F040A990 */ .gpword .L00435740
/* 09FB3C 1000FB3C F040A990 */ .gpword .L00435740
/* 09FB40 1000FB40 F040A990 */ .gpword .L00435740
/* 09FB44 1000FB44 F040A9C4 */ .gpword .L00435774
/* 09FB48 1000FB48 F040A9C4 */ .gpword .L00435774
/* 09FB4C 1000FB4C F040A990 */ .gpword .L00435740
/* 09FB50 1000FB50 F040A990 */ .gpword .L00435740
/* 09FB54 1000FB54 F040A9C4 */ .gpword .L00435774
/* 09FB58 1000FB58 F040A990 */ .gpword .L00435740
/* 09FB5C 1000FB5C F040A9C4 */ .gpword .L00435774
/* 09FB60 1000FB60 F040A990 */ .gpword .L00435740
/* 09FB64 1000FB64 F040A9C4 */ .gpword .L00435774
/* 09FB68 1000FB68 F040A9C4 */ .gpword .L00435774
/* 09FB6C 1000FB6C F040A9C4 */ .gpword .L00435774
/* 09FB70 1000FB70 F040A9C4 */ .gpword .L00435774
/* 09FB74 1000FB74 F040A9C4 */ .gpword .L00435774
/* 09FB78 1000FB78 F040A9C4 */ .gpword .L00435774
/* 09FB7C 1000FB7C F040A9C4 */ .gpword .L00435774
/* 09FB80 1000FB80 F040A9C4 */ .gpword .L00435774
/* 09FB84 1000FB84 F040A990 */ .gpword .L00435740
/* 09FB88 1000FB88 F040A9C4 */ .gpword .L00435774
/* 09FB8C 1000FB8C F040A990 */ .gpword .L00435740
/* 09FB90 1000FB90 F040A990 */ .gpword .L00435740
/* 09FB94 1000FB94 F040A990 */ .gpword .L00435740
/* 09FB98 1000FB98 F040A9C4 */ .gpword .L00435774
/* 09FB9C 1000FB9C F040A990 */ .gpword .L00435740
/* 09FBA0 1000FBA0 F040A990 */ .gpword .L00435740


.section .text
/* Generated by spimdisasm 1.12.4 */

glabel cannot_trap # 272
/* 0356E4 004356E4 3C1C0FBF */  lui         $gp, %hi(_gp_disp)
/* 0356E8 004356E8 279C56CC */  addiu       $gp, $gp, %lo(_gp_disp)
# _gp_disp: 0xFBF56CC
/* 0356EC 004356EC 0399E021 */  addu        $gp, $gp, $t9
/* 0356F0 004356F0 00047682 */  srl         $t6, $a0, 26
/* 0356F4 004356F4 2DC10038 */  sltiu       $at, $t6, 0x38
/* 0356F8 004356F8 AFA40000 */  sw          $a0, 0x0($sp)
/* 0356FC 004356FC 1020001D */  beqz        $at, .L00435774
/* 035700 00435700 00001825 */   move       $v1, $zero
/* 035704 00435704 8F818044 */  lw          $at, %got(jtbl_1000F9C4)($gp)
/* 035708 00435708 000E7080 */  sll         $t6, $t6, 2
/* 03570C 0043570C 002E0821 */  addu        $at, $at, $t6
/* 035710 00435710 8C2EF9C4 */  lw          $t6, %lo(jtbl_1000F9C4)($at)
/* 035714 00435714 01DC7021 */  addu        $t6, $t6, $gp
/* 035718 00435718 01C00008 */  jr          $t6
/* 03571C 0043571C 00000000 */   nop
.L00435720:
/* 035720 00435720 8F818044 */  lw          $at, %got(jtbl_1000FAA4)($gp)
/* 035724 00435724 308F003F */  andi        $t7, $a0, 0x3F
/* 035728 00435728 000F7880 */  sll         $t7, $t7, 2
/* 03572C 0043572C 002F0821 */  addu        $at, $at, $t7
/* 035730 00435730 8C2FFAA4 */  lw          $t7, %lo(jtbl_1000FAA4)($at)
/* 035734 00435734 01FC7821 */  addu        $t7, $t7, $gp
/* 035738 00435738 01E00008 */  jr          $t7
/* 03573C 0043573C 00000000 */   nop
.L00435740:
/* 035740 00435740 03E00008 */  jr          $ra
/* 035744 00435744 24020001 */   addiu      $v0, $zero, 0x1
.L00435748:
/* 035748 00435748 03E00008 */  jr          $ra
/* 03574C 0043574C 24020001 */   addiu      $v0, $zero, 0x1
.L00435750:
/* 035750 00435750 00041980 */  sll         $v1, $a0, 6
/* 035754 00435754 00031EC2 */  srl         $v1, $v1, 27
/* 035758 00435758 3865001D */  xori        $a1, $v1, 0x1D
/* 03575C 0043575C 2CA20001 */  sltiu       $v0, $a1, 0x1
/* 035760 00435760 54400004 */  bnel        $v0, $zero, .L00435774
/* 035764 00435764 00401825 */   move       $v1, $v0
/* 035768 00435768 3862001C */  xori        $v0, $v1, 0x1C
/* 03576C 0043576C 2C420001 */  sltiu       $v0, $v0, 0x1
/* 035770 00435770 00401825 */  move        $v1, $v0
.L00435774:
/* 035774 00435774 03E00008 */  jr          $ra
/* 035778 00435778 00601025 */   move       $v0, $v1
)
#endif

int stores_to_memory(struct unk_struct_1 arg0) {
    switch (arg0.unk0_C0) {
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2C:
    case 0x2D:
    case 0x2E:
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3D:
    case 0x3E:
    case 0x3F:
        return 1;
    default:
        return 0;
    }
}

int loads_from_memory(struct unk_struct_1 arg0) {

    switch (arg0.unk0_C0) {
    case 0x1A:
    case 0x1B:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
        return 1;
    default:
        return 0;
    }
}

#pragma GLOBAL_ASM("asm/7.1/functions/as1/do_init_noalias.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/reorg_noalias.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/init_malias_table.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/parse_mtag.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/parse_malias.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00435BFC.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00435CC0.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/init_alias_table.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00435FC4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/update_alias_table.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/free_alias_table.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/do_not_alias.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/init_reorg_state.s")


