#ifndef COMMON_H
#define COMMON_H

#include "cmplrs/binasm.h"

#define ALIGN_UP(x, v) ((((x) + (v) - 1) div (v)) * (v))

#define UGEN_LITTLE_ENDIAN (lsb_first)
#define UGEN_BIG_ENDIAN (not lsb_first)

#define IS_GPR(reg) ((reg) in [xr0..xr31])
#define IS_FPR(reg) ((reg) in [xfr0..xfr31])

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
    frame_pointer: registers;
    reversed_stack: boolean;
    frame_size: integer;
    debug_ugen: boolean;
    has_calls: boolean;
    uses_gp: boolean;
    pic_level: integer;
    source_language: integer; { see cmplrs/uoptions.h for values }

{ external functions }

procedure memset(p: pointer; value: integer; size: cardinal); external;

#endif /* COMMON_H */
