#ifndef COMMON_H
#define COMMON_H

#include "cmplrs/binasm.h"

#define UGEN_LITTLE_ENDIAN (lsb_first)
#define UGEN_BIG_ENDIAN (not lsb_first)

const
    NO_LABEL = 0;
    NO_SYM = 0;

type
    u16 = 0..65535 ;
    u8 =  0..255 of char;
    s8 = -128..127;

    ugen_report  = (
        Fix,
        Info,
        Warn,
        Error,
        Internal
    );

{ global variables }

var
    lsb_first: boolean;
    sdata_max: integer;
    opcode_arch: ( ARCH_32, ARCH_64 );
    isa: ( ISA_MIPS1, ISA_MIPS2, ISA_MIPS3 );
    ugen_fp_callee_saved: set of registers;
    saved_regs: set of registers;    
    n_cg_regs: integer;
    n_unsaved_regs: integer;
    n_unsaved_fp_regs: integer;
    n_parm_regs: integer;
    n_fp_cg_regs: integer;
    n_fp_parm_regs: integer;
    n_saved_regs: integer;
    fp32regs: boolean;
    n_saved_fp_regs: integer;
    ufsm: boolean;

#endif /* COMMON_H */
