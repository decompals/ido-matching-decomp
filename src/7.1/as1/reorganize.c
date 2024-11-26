/*
* @file: reorganize.c
*
*/

struct unk_1 {
    unsigned unk0_C0 : 6;
};

/*
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

//late_rodata issues

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/start_time.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/start_instruction.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00433538.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00433610.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/func_00433668.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/reorganize_bb.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/allocate_check.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/recalloc.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/addset.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/defuse.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/eligible.s")

//#pragma GLOBAL_ASM("asm/7.1/functions/as1/cannot_trap.s")
*/

int stores_to_memory(struct unk_1 arg0) {
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

int loads_from_memory(struct unk_1 arg0) {

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

/*
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

*/
