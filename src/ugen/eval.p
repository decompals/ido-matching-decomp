#include "cmplrs/uoptions.h"
#include "tree.h"
#include "reg_mgr.h"
#include "emit.h"
#include "emit_dw.h"
#include "report.h"
#include "tree_utils.h"
#include "ugen_regdef.h"
#include "temp_mgr.h"
#include "frame_offset.h"
#include "symbol.h"
#include "fold.h"
#include "translate.h"
#include "parm_mgr.h"

procedure eval(arg0: ^tree; arg1: registers); forward;
function reg(arg0: ^tree): registers; forward;
function flt_reg(arg0: ^tree): registers; forward;
procedure move_to_dest(arg0: registers; arg1: registers; arg2: Datatype); forward;

type
    Scalar_types = (ST_s8, ST_u8, ST_s16, ST_u16, ST_s32, ST_u32, ST_s64, ST_f32, ST_f64);

    asmcodearray = array[Scalar_types] of asmcodes;

var
    lsb_first: boolean;
    opcode_arch: ( ARCH_32, ARCH_64 );
    regs: array [registers] of Register;
    n_saved_regs: integer;
    n_saved_fp_regs: integer;
    n_parm_regs: integer;
    n_fp_parm_regs: integer;
    isa: mips_isa;
    reversed_stack: boolean;
    frame_pointer: registers;
    basicint: u8;
    pic_level: integer;
    align8: boolean;
    align16: boolean;
    align32: boolean;
    align64: boolean;
    saved_regs: set of registers;
    pdefs: ^tree;
    source_language: integer;

    { .data }
    get_filename: boolean := false;
    processing_args: boolean := false;
    processing_int64_return: boolean := false;
    setting_int64_return: boolean := false;

    spop_tab: array[Uopcode] of asmcodes := [
        Uadd: fadd_s,
        Usub: fsub_s,
        Umpy: fmul_s,
        Udiv: fdiv_s,        
        Uneg: fneg_s,
        Uabs: fabs_s,
        Usqrt: fsqrt_s,        

        Uldc: fli_s,

        Uequ: fc_eq_s,
        Uneq: fc_eq_s,
        Utpeq: fc_eq_s,
        Utpne: fc_eq_s,
        Ugeq: fc_le_s,
        Uleq: fc_le_s,
        Umin: fc_le_s,
        Utpge: fc_le_s,
        Utple: fc_le_s,
        Ugrt: fc_lt_s,
        Ules: fc_lt_s,
        Umax: fc_lt_s,
        Utpgt: fc_lt_s,
        Utplt: fc_lt_s,

        otherwise zbad
    ];

    dpop_tab: array[Uopcode] of asmcodes := [
        Uadd: fadd_d,
        Usub: fsub_d,
        Umpy: fmul_d,
        Udiv: fdiv_d,        
        Uneg: fneg_d,
        Uabs: fabs_d,
        Usqrt: fsqrt_d,

        Uldc: fli_d,

        Uequ: fc_eq_d,
        Uneq: fc_eq_d,
        Utpeq: fc_eq_d,
        Utpne: fc_eq_d,
        Ugeq: fc_le_d,
        Uleq: fc_le_d,
        Umin: fc_le_d,
        Utpge: fc_le_d,
        Utple: fc_le_d,
        Ugrt: fc_lt_d,
        Ules: fc_lt_d,
        Umax: fc_lt_d,
        Utpgt: fc_lt_d,
        Utplt: fc_lt_d,

        otherwise zbad
    ];

    br: array[Uopcode] of asmcodes := [
        Uequ: zbeq,
        Uneq: zbne,
        Ugeq: zbge,
        Ugrt: zbgt,
        Uleq: zble,
        Ules: zblt,

        otherwise zbad
    ];

    ubr: array[Uopcode] of asmcodes := [
        Uequ: zbeq,
        Uneq: zbne,
        Ugeq: zbgeu,
        Ugrt: zbgtu,
        Uleq: zbleu,
        Ules: zbltu,

        otherwise zbad
    ];

    inv: array[asmcodes] of asmcodes := [
        zbeq: zbne,
        zbne: zbeq,
        zbge: zblt,
        zblt: zbge,
        zbgt: zble,
        zble: zbgt,
        zbgeu: zbltu,
        zbltu: zbgeu,
        zbgtu: zbleu,
        zbleu: zbgtu,

        zteq: ztne,
        ztne: zteq,
        ztlt: ztge,
        ztge: ztlt,
        ztltu: ztgeu,
        ztgeu: ztltu,

        otherwise zbad
    ];

    trapop: array[Uopcode] of asmcodes := [
        Uequ: zteq,
        Uneq: ztne,
        Ugeq: ztge,
        Ules: ztlt,

        otherwise zbad
    ];

    utrapop: array[Uopcode] of asmcodes := [
        Uequ: zteq,
        Uneq: ztne,
        Ugeq: ztgeu,
        Ules: ztltu,

        otherwise zbad
    ];

    reg_kind_tab: array[Datatype] of RegKind := [
        Adt: f_reg,
        Gdt: f_reg,
        Hdt: f_reg,
        Jdt: f_reg,
        Ldt: f_reg,
        Rdt: f_reg,

        Qdt: d_reg,
        Wdt: d_reg,

        otherwise no_reg
    ];

    load_op_tab: array[Datatype] of asmcodes := [
        Adt: zlw,
        Fdt: zlw,
        Gdt: zlw,
        Hdt: zlw,
        Jdt: zlw,
        Ldt: zlw,
        Ndt: zlw,
        Sdt: zlw,

        Idt: zld,
        Kdt: zld,
        Wdt: zld,
        
        Rdt: fl_s,
        Qdt: fl_d,

        otherwise zbad
    ];

    store_op_tab: array[Datatype] of asmcodes := [
        Adt: zsw,
        Fdt: zsw,
        Gdt: zsw,
        Hdt: zsw,
        Jdt: zsw,
        Ldt: zsw,
        Ndt: zsw,
        Sdt: zsw,

        Idt: zsd,
        Kdt: zsd,
        Wdt: zsd,
        
        Rdt: fs_s,
        Qdt: fs_d,

        otherwise zbad
    ];

    load_table: asmcodearray := [
        zlb, zlbu, zlh, zlhu, zlw, zlwu, zld, fl_s, fl_d
    ];
    
    store_table: asmcodearray := [
        zsb, zsb, zsh, zsh, zsw, zsw, zsd, fs_s, fs_d
    ];

    double_to_singles: array[asmcodes] of asmcodes := [
        zld: zlw,
        zsd: zsw,
        fl_d: fl_s,
        fs_d: fs_s,

        otherwise zbad
    ];

    unaligned_load_store1: array[asmcodes] of asmcodes := [
        zlw: zlwl,
        zld: zlwl,
        zsw: zswl,        
        zsd: zswl,

        otherwise zbad
    ];

    unaligned_load_store2: array[asmcodes] of asmcodes := [
        zlw: zlwr,
        zld: zlwr,
        zsw: zswr,        
        zsd: zswr,

        otherwise zbad
    ];

    unaligned_load_store_tab: array[asmcodes] of asmcodes := [
        zlb: zlb,
        zsb: zsb,
        zlh: zulh,
        zlhu: zulhu,
        zsh: zush,
        zlw: zulw,
        zlwu: zulwu,
        zsw: zusw,
        zld: zuld,        
        zsd: zusd,

        otherwise zbad
    ];

    op_tab: array[Uopcode] of asmcodes := [
        Uigeq: zsle,
        Uileq: zsle,
        Uigrt: zslt,
        Uiles: zslt,

        otherwise znop
    ];

    op: array[Uopcode] of asmcodes := [
        Uadd: zaddu,
        Usub: zsubu,
        Umpy: zmul,
        Udiv: zdiv,
        Umod: zrem,
        Urem: zrem,
        Uabs: zabs,
        Uneg: znegu,
        Uand: zand,
        Uior: zor,
        Uxor: zxor,
        Unot: znot,
        Ushl: zsll,
        Ushr: zsra,

        Umax: zbge,
        Umin: zble,

        Uequ: zseq,
        Uneq: zsne,
        Ulnot: zseq,
        Ugeq: zsge,
        Ugrt: zsgt,
        Ules: zslt,
        Uleq: zsle,

        Uchkh: zble,
        Uchkl: zbge,

        otherwise zbad
    ];

    uop: array[Uopcode] of asmcodes := [
        Uadd: zaddu,
        Usub: zsubu,
        Umpy: zmul,
        Udiv: zdivu,
        Umod: zremu,
        Urem: zremu,
        Uabs: zabs,
        Uneg: znegu,
        Uand: zand,
        Uior: zor,
        Uxor: zxor,
        Unot: znot,
        Ushl: zsll,
        Ushr: zsrl,

        Umax: zbgeu,
        Umin: zbleu,

        Uequ: zseq,
        Uneq: zsne,
        Ulnot: zseq,
        Ugeq: zsgeu,
        Ugrt: zsgtu,
        Ules: zsltu,
        Uleq: zsleu,

        Uchkh: zbleu,
        Uchkl: zbgeu,

        otherwise zbad
    ];

    oop: array[Uopcode] of asmcodes := [
        Uadd: zadd,
        Usub: zsub,
        Umpy: zmulo,
        Udiv: zdiv,
        Umod: zrem,
        Urem: zrem,
        Uabs: zabs,
        Uneg: zneg,
        Uand: zand,
        Uior: zor,
        Uxor: zxor,
        Unot: znot,
        Ushl: zsll,
        Ushr: zsra,

        Umax: zbge,
        Umin: zble,

        Uequ: zseq,
        Uneq: zsne,
        Ulnot: zseq,
        Ugeq: zsge,
        Ugrt: zsgt,
        Ules: zslt,
        Uleq: zsle,

        Uchkh: zble,
        Uchkl: zbge,

        otherwise zbad
    ];

    ouop: array[Uopcode] of asmcodes := [
        Uadd: zaddou,
        Usub: zsubou,
        Umpy: zmulou,
        Udiv: zdivu,
        Umod: zremu,
        Urem: zremu,
        Uabs: zabs,
        Uneg: zneg,
        Uand: zand,
        Uior: zor,
        Uxor: zxor,
        Unot: znot,
        Ushl: zsll,
        Ushr: zsrl,

        Umax: zbgeu,
        Umin: zbleu,

        Uequ: zseq,
        Uneq: zsne,
        Ulnot: zseq,
        Ugeq: zsgeu,
        Ugrt: zsgtu,
        Ules: zsltu,
        Uleq: zsleu,

        Uchkh: zbleu,
        Uchkl: zbgeu,

        otherwise zbad
    ];

    dw_op: array[Uopcode] of asmcodes := [
        Uadd: zdaddu,
        Usub: zdsubu,
        Umpy: zdmul,
        Udiv: zddiv,
        Umod: zdrem,
        Urem: zdrem,
        Uabs: zdabs,
        Uneg: zdnegu,
        Uand: zand,
        Uior: zor,
        Uxor: zxor,
        Unot: znot,
        Ushl: zdsll,
        Ushr: zdsra,

        Umax: zbge,
        Umin: zble,

        Uequ: zseq,
        Uneq: zsne,
        Ulnot: zseq,
        Ugeq: zsge,
        Ugrt: zsgt,
        Ules: zslt,
        Uleq: zsle,

        Uchkh: zble,
        Uchkl: zbge,

        otherwise zbad
    ];

    dw_uop: array[Uopcode] of asmcodes := [
        Uadd: zdaddu,
        Usub: zdsubu,
        Umpy: zdmul,
        Udiv: zddivu,
        Umod: zdremu,
        Urem: zdremu,
        Uabs: zdabs,
        Uneg: zdnegu,
        Uand: zand,
        Uior: zor,
        Uxor: zxor,
        Unot: znot,
        Ushl: zdsll,
        Ushr: zdsrl,

        Umax: zbgeu,
        Umin: zbleu,

        Uequ: zseq,
        Uneq: zsne,
        Ulnot: zseq,
        Ugeq: zsgeu,
        Ugrt: zsgtu,
        Ules: zsltu,
        Uleq: zsleu,

        Uchkh: zbleu,
        Uchkl: zbgeu,

        otherwise zbad
    ];

    dw_oop: array[Uopcode] of asmcodes := [
        Uadd: zdadd,
        Usub: zdsub,
        Umpy: zdmulo,
        Udiv: zddiv,
        Umod: zdrem,
        Urem: zdrem,
        Uabs: zdabs,
        Uneg: zdneg,
        Uand: zand,
        Uior: zor,
        Uxor: zxor,
        Unot: znot,
        Ushl: zdsll,
        Ushr: zdsra,

        Umax: zbge,
        Umin: zble,

        Uequ: zseq,
        Uneq: zsne,
        Ulnot: zseq,
        Ugeq: zsge,
        Ugrt: zsgt,
        Ules: zslt,
        Uleq: zsle,

        Uchkh: zble,
        Uchkl: zbge,

        otherwise zbad
    ];

    dw_ouop: array[Uopcode] of asmcodes := [
        Uadd: zdaddou,
        Usub: zdsubou,
        Umpy: zdmulou,
        Udiv: zddivu,
        Umod: zdremu,
        Urem: zdremu,
        Uabs: zdabs,
        Uneg: zdneg,
        Uand: zand,
        Uior: zor,
        Uxor: zxor,
        Unot: znot,
        Ushl: zdsll,
        Ushr: zdsrl,

        Umax: zbgeu,
        Umin: zbleu,

        Uequ: zseq,
        Uneq: zsne,
        Ulnot: zseq,
        Ugeq: zsgeu,
        Ugrt: zsgtu,
        Ules: zsltu,
        Uleq: zsleu,

        Uchkh: zbleu,
        Uchkl: zbgeu,

        otherwise zbad
    ];

    op_nor: asmcodes := znor;
    nor_flag: boolean := false;
    move_cvt_flag: integer := -1;

function is_end_return(arg0: ^tree): boolean;
var
    var_v0: ^tree;
    var_v1: Uopcode;
begin
    if arg0^.u.Opc = Uujp then begin
        var_v0 := arg0^.op2^.next;
    end else begin
        var_v0 := arg0;
    end;
    var_v1 := var_v0^.u.Opc;
    while var_v1 in [Ubgnb, Ucomm, Udef, Uendb, Ulab, Ulex, Uloc, Unop, Uoptn, Usdef] do begin
        var_v0 := var_v0^.next;
        var_v1 := var_v0^.u.Opc;
    end;
    return var_v1 = Uend;
end;

procedure move_dreg_to_regs(arg0: registers; arg1: registers);
begin
    if arg1 = xr0 then begin
        emit_ri_(zli, arg0, 0, franone);
        emit_ri_(zli, succ(arg0), 0, franone);
    end else if lsb_first then begin
        if arg0 = arg1 then begin
            emit_rri_(zdsra, succ(arg0), arg1, 32, franone);
            emit_rri_(zdsll, arg0, arg1, 32, franone);
            emit_rri_(zdsra, arg0, arg0, 32, franone);
        end else begin
            emit_rri_(zdsll, arg0, arg1, 32, franone);
            emit_rri_(zdsra, arg0, arg0, 32, franone);
            emit_rri_(zdsra, succ(arg0), arg1, 32, franone);
        end;
    end else begin
        if arg0 = arg1 then begin
            emit_rri_(zdsll, succ(arg0), arg1, 32, franone);
            emit_rri_(zdsra, succ(arg0), succ(arg0), 32, franone);
            emit_rri_(zdsra, arg0, arg1, 32, franone);
        end else begin
            emit_rri_(zdsra, arg0, arg1, 32, franone);
            emit_rri_(zdsll, succ(arg0), arg1, 32, franone);
            emit_rri_(zdsra, succ(arg0), succ(arg0), 32, franone);
        end;
    end;
    if (opcode_arch = ARCH_64) and (arg0 in [xr4, xr6]) then begin
        regs[arg0].unk9 := succ(arg0);
    end;
end;

procedure move_two_regs(arg0: registers; arg1: registers);
var
    sp26: asmcodes;
begin
    if arg0 <> arg1 then begin
        if (arg1 in [xfr0..xfr31]) and (arg0 in [xr0..xr31]) then begin
            sp26 := zmfc1;
        end else begin
            sp26 := zmove;
        end;
        emit_rr(sp26, arg0, arg1);
        emit_rr(sp26, succ(arg0), succ(arg1));
    end;
end;

function fasm(arg0: asmcodes; arg1: Datatype): asmcodes;
begin
    case arg1 of
        Rdt: return arg0;
        Qdt: return succ(arg0);
        Xdt: report_error(Internal, 838, 'eval.p', 'extended floating point not yet supported');
        otherwise report_error(Internal, 844, 'eval.p', 'illegal data type');
    end;
end;

function fop(arg0: Uopcode; arg1: Datatype): asmcodes;
begin
    case arg1 of
        Rdt: return spop_tab[arg0];
        Qdt: return dpop_tab[arg0];
        Xdt: report_error(Internal, 856, 'eval.p', 'extended floating point not yet supported');
        otherwise report_error(Internal, 862, 'eval.p', 'illegal data type');
    end;
end;

function uop_to_asm(arg0: ^tree): asmcodes;
begin
    if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
        return fop(arg0^.u.Opc, arg0^.u.Dtype);
    end;
    if IS_OVERFLOW_ATTR(arg0^.u.Lexlev) then begin
        case arg0^.u.Dtype of
            Idt:
                if opcode_arch = ARCH_64 then begin
                    return dw_oop[arg0^.u.Opc];
                end else begin
                    return oop[arg0^.u.Opc];
                end;
            Kdt:
                if opcode_arch = ARCH_64 then begin
                    return dw_ouop[arg0^.u.Opc];
                end else begin
                    return ouop[arg0^.u.Opc];
                end;
            Jdt:
                return oop[arg0^.u.Opc];
            otherwise
                if arg0^.u.Opc = Ulnot then begin
                    return oop[arg0^.u.Opc];
                end else begin
                    return ouop[arg0^.u.Opc];
                end;
        end;
    end else begin
        case arg0^.u.Dtype of
            Idt:
                if opcode_arch = ARCH_64 then begin
                    return dw_op[arg0^.u.Opc];
                end else begin
                    return op[arg0^.u.Opc];
                end;
            Kdt:
                if opcode_arch = ARCH_64 then begin
                    return dw_uop[arg0^.u.Opc];
                end else begin
                    return uop[arg0^.u.Opc];
                end;
            Jdt:
                return op[arg0^.u.Opc];
            otherwise
                if arg0^.u.Opc = Ulnot then begin
                    return op[arg0^.u.Opc];
                end else begin
                    return uop[arg0^.u.Opc];
                end;
        end;
    end;
end;

procedure jump(arg0: ^tree; arg1: boolean; arg2: integer);
var
    var_s3: asmcodes;
    sp3D: registers;
    sp3C: registers;
begin
    if arg0^.ref_count <> 1 then begin
        eval(arg0, xnoreg);
    end;
    if arg0^.reg <> xnoreg then begin
        var_s3 := zbne;
        if arg1 then begin
            var_s3 := zbeq;
        end;
        if result_type(arg0) in [Idt, Kdt, Wdt] then begin
            emit_branch_rill(var_s3, reg(arg0), 0, 0, arg2, arg0);
        end else begin
            emit_rrll(var_s3, reg(arg0), xr0, arg2);
        end;
    end else begin
        case arg0^.u.Opc of
            Ulnot: begin
                jump(arg0^.op1, not arg1, arg2);
            end;
            Uleq, Ules, Uequ, Uneq, Ugeq, Ugrt: begin
                if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                    var_s3 := fop(arg0^.u.Opc, arg0^.u.Dtype);
                    if arg0^.u.Opc = Uneq then begin
                        arg1 := not arg1;
                    end;
                    eval(arg0^.op1, xnoreg);
                    eval(arg0^.op2, xnoreg);
                    if arg0^.u.Opc in [Ugeq, Ugrt] then begin
                        sp3C := flt_reg(arg0^.op1);
                        sp3D := flt_reg(arg0^.op2);
                    end else begin
                        sp3D := flt_reg(arg0^.op1);
                        sp3C := flt_reg(arg0^.op2);
                    end;
                    emit_rr(var_s3, sp3D, sp3C);
                    var_s3 := zbc1t;
                    if arg1 then begin
                        var_s3 := zbc1f;
                    end;
                    emit_ll(var_s3, arg2);
                end else begin
                    var_s3 := br[arg0^.u.Opc];
                    if (arg0^.u.Dtype <> Jdt) and (arg0^.u.Dtype <> Idt) then begin
                        var_s3 := ubr[arg0^.u.Opc];
                    end;
                    if arg1 then begin
                        var_s3 := inv[var_s3];
                    end;
                    if arg0^.op2^.u.Opc = Uldc then begin
                        eval(arg0^.op1, xnoreg);
                        if arg0^.op2^.u.Dtype in [Idt, Kdt, Wdt] then begin
                            emit_branch_rill(var_s3, reg(arg0^.op1), arg0^.op2^.u.Constval.dwval_h, arg0^.op2^.u.Constval.dwval_l, arg2, arg0);
                        end else begin
                            emit_rill(var_s3, reg(arg0^.op1), arg0^.op2^.u.Constval.Ival, arg2);
                        end;
                    end else begin
                        eval(arg0^.op1, xnoreg);
                        eval(arg0^.op2, xnoreg);
                        sp3D := reg(arg0^.op1);
                        sp3C := reg(arg0^.op2);
                        emit_branch_rrll(var_s3, sp3D, sp3C, arg2, arg0);
                    end;
                end;
            end;
            otherwise begin
                eval(arg0, xnoreg);
                var_s3 := zbne;
                if arg1 then begin
                    var_s3 := zbeq;
                end;
                emit_branch_rill(var_s3, reg(arg0), 0, 0, arg2, arg0);
            end;
        end;
    end;
end;

procedure trap(arg0: integer; arg1: ^tree; arg2: boolean);
var
    sp3F: Uopcode;
    sp3C: asmcodes;
    sp3B: registers;
    sp3A: registers;
    temp_v0: integer;
    sp30: ^tree;
    sp2C: ^tree;
    label
        start;
begin
    if addr(arg2) <> nil then;

    start:

    if arg1^.ref_count <> 1 then begin
        eval(arg1, xnoreg);
    end;
    if arg1^.reg <> xnoreg then begin
        sp3C := ztne;
        if arg2 then begin
            sp3C := zteq;
        end;
        emit_trap_rri(sp3C, reg(arg1), xr0, arg0, arg1);
    end else begin
        sp3F := arg1^.u.Opc;
        case sp3F of
            Ulnot: begin
                arg1 := arg1^.op1;
                arg2 := not arg2;
                goto start; {manual tail recursion}
                {trap(arg0, arg1^.op1, not arg2);} 
            end;
            Uleq, Ules, Uequ, Uneq, Ugeq, Ugrt: begin
                if arg1^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                    sp3C := fop(sp3F, arg1^.u.Dtype);
                    if arg1^.u.Opc = Uneq then begin
                        arg2 := not arg2;
                    end;
                    eval(arg1^.op1, xnoreg);
                    eval(arg1^.op2, xnoreg);
                    if arg1^.u.Opc in [Ugeq, Ugrt] then begin
                        sp3A := flt_reg(arg1^.op1);
                        sp3B := flt_reg(arg1^.op2);
                    end else begin
                        sp3B := flt_reg(arg1^.op1);
                        sp3A := flt_reg(arg1^.op2);
                    end;
                    emit_rr(sp3C, sp3B, sp3A);
                    sp3C := zbc1f;
                    if arg2 then begin
                        sp3C := zbc1t;
                    end;
                    temp_v0 := gen_label_id();
                    emit_ll(sp3C, temp_v0);
                    emit_i(zbreak, arg0);
                    define_label(temp_v0);
                end else begin
                    sp30 := arg1^.op1;
                    sp2C := arg1^.op2;
                    case sp3F of
                        Uleq: begin
                            if sp2C^.u.Opc = Uldc then begin
                                sp3F := Ules;
                                sp2C := ivalue(sp2C^.u.Dtype, 0, sp2C^.u.Constval.Ival + 1);
                            end else begin
                                sp3F := Ugeq;
                                sp30 := arg1^.op2;
                                sp2C := arg1^.op1;
                            end;
                        end;
                        Ugrt: begin
                            if sp2C^.u.Opc = Uldc then begin
                                sp3F := Ugeq;
                                sp2C := ivalue(sp2C^.u.Dtype, 0, sp2C^.u.Constval.Ival + 1);
                            end else begin
                                sp3F := Ules;
                                sp30 := arg1^.op2;
                                sp2C := arg1^.op1;
                            end;
                        end;
                        otherwise: begin end;
                    end;
                    sp3C := trapop[sp3F];
                    if arg1^.u.Dtype <> Jdt then begin
                        sp3C := utrapop[sp3F];
                    end;
                    if arg2 then begin
                        sp3C := inv[sp3C];
                    end;
                    if (sp2C^.u.Opc = Uldc) and (arg0 = 8) then begin
                        eval(sp30, xnoreg);
                        if (opcode_arch = ARCH_32) and (sp2C^.u.Dtype in [Idt, Kdt, Wdt]) then begin
                            emit_trap_ri(sp3C, reg(sp30), sp2C^.u.Constval.dwval_h, sp2C^.u.Constval.dwval_l, arg1);
                        end else begin
                            emit_ri_(sp3C, reg(sp30), sp2C^.u.Constval.Ival, franone);
                        end;
                    end else begin
                        eval(sp30, xnoreg);
                        eval(sp2C, xnoreg);
                        sp3B := reg(sp30);
                        sp3A := reg(sp2C);
                        emit_trap_rri(sp3C, sp3B, sp3A, arg0, arg1);
                    end;
                end;
            end;
            otherwise begin
                eval(arg1, xnoreg);
                sp3C := ztne;
                if arg2 then begin
                    sp3C := zteq;
                end;
                emit_trap_rri(sp3C, reg(arg1), xr0, arg0, arg1);
            end;
        end;
    end;
end;

function is_saved_reg(reg: registers): boolean;
begin
    return (reg >= gpr_s0) and (reg <= registers(ord(gpr_s0) + n_saved_regs - 1)) or
           (reg in [gpr_s8, gpr_ra]) or
           (reg >= xfr20) and (reg <= registers(ord(xfr20) + 2 * (n_saved_fp_regs - 1)));
end;

function is_parm_reg(reg: registers): boolean;
begin
    return (reg >= gpr_a0) and (reg <= registers(ord(gpr_a0) + n_parm_regs - 1)) or
           (reg >= xfr12) and (reg <= registers(ord(xfr12) + 2 * (n_fp_parm_regs - 1)));
end;

function is_fp_reg(reg: registers): boolean;
begin
    return (reg >= xfr0) and (reg <= xfr31);
end;

procedure restore_from_temp(arg0: ^tree);
var
    spC7: Datatype;
    spC0: integer;
    spBE: asmcodes;
begin
    spC7 := result_type(arg0);
    if (isa < ISA_MIPS3) and (opcode_arch = ARCH_32) then begin
        spC0 := 4;
    end else begin
        spC0 := 8;
    end;
    case spC7 of
        Rdt, Qdt: begin
            arg0^.reg := get_free_fp_reg(arg0, reg_kind_tab[spC7], temp_usage_count(arg0^.unk18));
            if spC7 = Qdt then begin
                spC0 := 8;
            end;
        end;
        Xdt:
            report_error(Internal, 1323,  'eval.p', 'extended floating point type not yet supported');
        Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt, Sdt: begin
            arg0^.reg := get_free_reg(arg0, temp_usage_count(arg0^.unk18));
        end;
        Idt, Kdt, Wdt: begin
            spC0 := 8;
            arg0^.reg := get_free_reg(arg0, temp_usage_count(arg0^.unk18));
        end;
        otherwise
            report_error(Internal, 1345, 'eval.p', 'unknown temporary type');
    end;
    spBE := load_op_tab[spC7];
    if reversed_stack then begin
        if (spBE = zld) and (opcode_arch = ARCH_32) then begin
            emit_rob(zlw, arg0^.reg, frame_offset1(temp_offset(arg0^.unk18) + spC0), frame_pointer, 0);
            emit_rob(zlw, succ(arg0^.reg), frame_offset1(temp_offset(arg0^.unk18) + spC0) + 4, frame_pointer, 0);
        end else begin
            emit_rob(spBE, arg0^.reg, frame_offset1(temp_offset(arg0^.unk18) + spC0), frame_pointer, 0);
        end;
    end else begin
        if (spBE = zld) and (opcode_arch = ARCH_32) then begin
            emit_rob(zlw, arg0^.reg, frame_offset1(temp_offset(arg0^.unk18)), frame_pointer, 0);
            emit_rob(zlw, succ(arg0^.reg), frame_offset1(temp_offset(arg0^.unk18)) + 4, frame_pointer, 0);
        end else begin
            emit_rob(spBE, arg0^.reg, frame_offset1(temp_offset(arg0^.unk18)), frame_pointer, 0);
        end;
    end;
    free_temp(arg0^.unk18);
    arg0^.unk18 := 0;
end;

function reg{(arg0: ^tree): registers};
begin
    if arg0^.reg = xnoreg then begin
        report_error(Internal, 1384, 'eval.p', 'tree node not evaluated');
        return xnoreg;
    end;

    if arg0^.unk18 <> 0 then begin
        restore_from_temp(arg0);
    end;

    if arg0^.reg in [xfr0..xfr31] then begin
        free_fp_reg(arg0^.reg, reg_kind_tab[arg0^.u.Dtype]);
    end else begin
        free_reg(arg0^.reg);
    end;

    return arg0^.reg;
end;

procedure binary_regs(arg0: ^tree; arg1: ^tree; var arg2: registers; var arg3: registers);
begin
    if arg0^.reg = xnoreg then begin
        report_error(Internal, 1408, 'eval.p', 'tree node not evaluated');
    end;

    if arg0^.unk18 <> 0 then begin
        restore_from_temp(arg0);
    end;

    if arg1^.reg = xnoreg then begin
        report_error(Internal, 1416, 'eval.p', 'tree node not evaluated');
    end;

    if arg1^.unk18 <> 0 then begin
        restore_from_temp(arg1);
    end;

    if arg0^.reg in [xfr0..xfr31] then begin
        free_fp_reg(arg0^.reg, reg_kind_tab[arg0^.u.Dtype]);
    end else begin
        free_reg(arg0^.reg);
    end;

    if arg1^.reg in [xfr0..xfr31] then begin
        free_fp_reg(arg1^.reg, reg_kind_tab[arg1^.u.Dtype]);
    end else begin
        free_reg(arg1^.reg);
    end;

    arg2 := arg0^.reg;
    arg3 := arg1^.reg;
end;

function flt_reg{(arg0: ^tree): registers};
var
    r: registers;
    r1: registers;
    dtype: Datatype;
begin
    r := reg(arg0);

    if not((r >= xfr0) and (r <= xfr30)) then begin
        dtype := result_type(arg0);
        if dtype in [Qdt, Rdt, Xdt] then begin
            r1 := get_free_fp_reg(arg0, reg_kind_tab[dtype], usage_count(r) + 1);
            move_to_dest(r1, r, dtype);
            force_free_reg(r);
            free_fp_reg(r1, reg_kind_tab[dtype]);
            arg0^.reg := r1;
        end else begin
            r1 := get_free_fp_reg(arg0, reg_kind_tab[dtype], 1);
            move_to_dest(r1, r, dtype);
            free_fp_reg(r1, reg_kind_tab[dtype]);
            return r1;
        end;
    end;
    
    return arg0^.reg;
end;

procedure binary_flt_regs(arg0: ^tree; arg1: ^tree; var arg2: registers; var arg3: registers);
var
    reg1: registers;
    reg2: registers;

    function func_0042567C(arg0: ^tree; r: registers): registers;
    var
        r1: registers;
        dtype: Datatype;
    begin
        if not((r >= xfr0) and (r <= xfr30)) then begin
            dtype := result_type(arg0);
            if dtype in [Qdt, Rdt, Xdt] then begin
                r1 := get_free_fp_reg(arg0, reg_kind_tab[dtype], usage_count(r) + 1);
                move_to_dest(r1, r, dtype);
                force_free_reg(r);
                free_fp_reg(r1, reg_kind_tab[dtype]);
                arg0^.reg := r1;
            end else begin
                r1 := get_free_fp_reg(arg0, reg_kind_tab[dtype], 1);
                move_to_dest(r1, r, dtype);
                free_fp_reg(r1, reg_kind_tab[dtype]);
                return r1;
            end;
        end;
        
        return arg0^.reg;
    end;
begin
    binary_regs(arg0, arg1, reg1, reg2);
    arg2 := func_0042567C(arg0, reg1);
    arg3 := func_0042567C(arg1, reg2);
end;

function get_dest(arg0: ^tree; arg1: registers): registers;
var
    dtype: Datatype;
    dtype2: Datatype;
begin
    dtype := result_type(arg0);

    if arg1 = xnoreg then begin
        if not(dtype in [Qdt, Rdt, Xdt]) then begin
            arg1 := get_free_reg(arg0, arg0^.ref_count);
        end else begin
            arg1 := get_free_fp_reg(arg0, reg_kind_tab[dtype], arg0^.ref_count);
        end;
    end else if arg1 in [xfr0..xfr31] then begin
        get_fp_reg(arg1, arg0, reg_kind_tab[dtype], 1);
    end else if (opcode_arch = ARCH_32) and (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (arg0^.u.Dtype <> dtype) then begin
        dtype2 := arg0^.u.Dtype;
        arg0^.u.Dtype := dtype;
        get_reg(arg1, arg0, 1);
        arg0^.u.Dtype := dtype2;
    end else begin
        get_reg(arg1, arg0, 1);
    end;

    arg0^.reg := arg1;    
    return arg1;
end;

procedure move_to_dest{(arg0: registers; arg1: registers; arg2: Datatype)};
var
    op: asmcodes;
begin
    if arg0 = arg1 then begin
        return;
    end;

    if (arg1 in [xr0..xr31]) and (arg0 in [xfr0..xfr31]) then begin
        op := zmtc1;
        if arg2 = Qdt then begin
            op := zmtc1_d;
        end;
        if (opcode_arch = ARCH_64) and (arg2 in [Idt, Kdt, Wdt]) then begin
            op := zdmtc1;
        end;
        emit_rr(op, arg1, arg0);
    end else if (arg1 in [xfr0..xfr31]) and (arg0 in [xr0..xr31]) then begin
        op := zmfc1;
        if arg2 = Qdt then begin
            op := zmfc1_d;
        end;
        if (opcode_arch = ARCH_64) and (arg2 in [Idt, Kdt, Wdt]) then begin
            op := zdmfc1;
        end;
        emit_rr(op, arg0, arg1);
    end else if (arg1 in [xfr0..xfr31]) and (arg0 in [xfr0..xfr31]) then begin
        if arg2 = Rdt then begin
            op := fmov_s;
        end else begin
            op := fmov_d;
        end;
        emit_rr(op, arg0, arg1);
    end else if (arg1 in [xr0..xr31]) and (arg0 in [xr0..xr31]) then begin
        emit_rr(zmove, arg0, arg1);
    end else begin
        report_error(Internal, 1594, 'eval.p', 'unknown register type');
    end;
end;

function lsopc(var arg0: asmcodearray; arg1: ^tree; arg2: registers): asmcodes;
begin
    if arg2 in [xfr0..xfr31] then begin
        if arg1^.u.Length <= 4 then begin
            assert(arg1^.u.Dtype = Rdt);
            lsopc := arg0[ST_f32];
        end else if arg1^.u.Length <= 8 then begin
            assert(arg1^.u.Dtype = Qdt);
            lsopc := arg0[ST_f64];
        end else begin
            report_error(Internal, 1614, 'eval.p', 'illegal size in load/store');
        end;
    end else begin
        case arg1^.u.Dtype of
        Jdt:
            if arg1^.u.Length = 4 then begin
                lsopc := arg0[ST_s32];
            end else if arg1^.u.Length = 1 then begin
                lsopc := arg0[ST_s8];
            end else if arg1^.u.Length = 2 then begin
                lsopc := arg0[ST_s16];
            end else begin
                report_error(Internal, 1630, 'eval.p', 'illegal size in load/store');
            end;
        Ldt:
            if arg1^.u.Length = 4 then begin
                if isa >= ISA_MIPS3 then begin
                    lsopc := arg0[ST_u32];
                end else begin
                    lsopc := arg0[ST_s32];
                end;
            end else if arg1^.u.Length = 1 then begin
                lsopc := arg0[ST_u8];
            end else if arg1^.u.Length = 2 then begin
                lsopc := arg0[ST_u16];
            end else begin
                report_error(Internal, 1647, 'eval.p', 'illegal size in load/store');
            end;
        Idt:
            if arg1^.u.Length = 4 then begin
                lsopc := arg0[ST_s32];
            end else if arg1^.u.Length = 1 then begin
                lsopc := arg0[ST_s8];
            end else if arg1^.u.Length = 2 then begin
                lsopc := arg0[ST_s16];
            end else if arg1^.u.Length = 8 then begin
                lsopc := arg0[ST_s64];
            end else begin
                report_error(Internal, 1659, 'eval.p', 'illegal size in load/store');
            end;
        Kdt:
            if arg1^.u.Length = 4 then begin
                if isa >= ISA_MIPS3 then begin
                    lsopc := arg0[ST_u32];
                end else begin
                    lsopc := arg0[ST_s32];
                end;
            end else if arg1^.u.Length = 1 then begin
                lsopc := arg0[ST_u8];
            end else if arg1^.u.Length = 2 then begin
                lsopc := arg0[ST_u16];
            end else if arg1^.u.Length = 8 then begin
                lsopc := arg0[ST_s64];
            end else begin
                report_error(Internal, 1681, 'eval.p', 'illegal size in load/store');
            end;
        Adt, Fdt, Gdt, Hdt, Mdt, Ndt, Sdt, Wdt:
            if arg1^.u.Length = 4 then begin
                if basicint = 1 then begin
                    lsopc := arg0[ST_u32];
                end else begin
                    lsopc := arg0[ST_s32];
                end;
            end else if arg1^.u.Length = 1 then begin
                lsopc := arg0[ST_u8];
            end else if arg1^.u.Length = 2 then begin
                lsopc := arg0[ST_u16];
            end else if arg1^.u.Length = 8 then begin
                lsopc := arg0[ST_s64];
            end else begin
                report_error(Internal, 1697, 'eval.p', 'illegal size in load/store');
            end;
        Rdt:
            lsopc := arg0[ST_s32];
        Qdt:
            lsopc := arg0[ST_s64];
        otherwise begin
            report_error(Internal, 1712, 'eval.p', 'illegal data type in load/store');
            lsopc := arg0[ST_s32];
        end;
        end;
    end;
end;

procedure loadstore(fasm: asmcodes; arg1: ^tree; arg2: registers; arg3: integer);
var
    tempr: registers;
begin
    case arg1^.u.Mtype of
        Mmt,
        Pmt:
        begin
            if get_sym_kind(arg1^.u.I1) = 5 then begin
                if fasm <> zla then begin
                    tempr := get_free_reg(nil, 1);
                    if basicint = 1 then begin
                        emit_rrri(zdsubu, tempr, frame_pointer, arg1^.u.I1);
                    end else begin
                        emit_rrri(zsubu, tempr, frame_pointer, arg1^.u.I1);
                    end;
                    emit_rob(fasm, arg2, arg1^.u.Offset, tempr, 0);
                    free_reg(tempr);
                end else begin
                    emit_rrab(zla, arg2, arg3, arg1^.u.I1, frame_pointer);
                    if arg1^.u.Offset <> 0 then begin
                        emit_rri_(zaddu, arg2, arg2, arg1^.u.Offset, franone);
                    end;
                end;
            end else begin
                emit_rob(fasm, arg2, frame_offset(arg1) + arg3, frame_pointer, arg1^.u.Constval.Ival);
            end;
        end;

        Smt:
        begin
            if pic_level > 0 then begin
                if (arg1^.u.I1 <> 0) and ((arg1^.u.Offset + arg3 > 16#7FFF) or (arg1^.u.Offset + arg3 < -16#8000)) then begin
                    tempr := get_free_reg(nil, 1);
                    emit_ra(zla, tempr, arg1^.u.I1, arg1^.u.Offset + arg3, arg1^.u.Constval.Ival);
                    emit_rob(fasm, arg2, 0, tempr, arg1^.u.Constval.Ival);
                    free_reg(tempr);
                end else begin
                    emit_ra(fasm, arg2, arg1^.u.I1, arg1^.u.Offset + arg3, arg1^.u.Constval.Ival);
                end;
            end else begin
                emit_ra(fasm, arg2, arg1^.u.I1, arg1^.u.Offset + arg3, arg1^.u.Constval.Ival);
            end;
        end;

        Amt:
        begin
            emit_rob(fasm, arg2, arg1^.u.Offset + arg3, gpr_sp, arg1^.u.Constval.Ival);
        end;

        otherwise report_error(Internal, 1773, 'eval.p', 'illegal memory type in load/store');
    end;
end;

procedure iloadistore(arg0: ^tree;
                      arg1: asmcodes;
                      arg2: registers;
                      arg3: integer;
                      arg4: cardinal;
                      arg5: registers);
var
    v1: integer;
    sp30: integer;

    procedure func_00426B44;
    var
        s1: registers;
    begin
        s1 := get_free_reg(nil, 1);
        if (arg1 = fs_s) or (arg1 = zswc1) then begin
            move_to_dest(s1, arg2, Rdt);
            emit_rab(zusw, s1, arg3, arg4, arg5, sp30);
        end else begin
            emit_rab(zulw, s1, arg3, arg4, arg5, sp30);
            move_to_dest(arg2, s1, Rdt);
        end;

        free_reg(s1);
    end;

    procedure func_00426C54;
    var
        sp40: integer;
        sp3C: integer;
        s3: registers;
        singleop: asmcodes;
    begin
        if lsb_first or not is_fp_reg(arg2) then begin
            sp3C := arg3 + 4;
            sp40 := arg3;
        end else begin
            sp40 := arg3 + 4;
            sp3C := arg3;            
        end;

        if is_fp_reg(arg2) and (v1 = 4) then begin
            singleop := double_to_singles[arg1];
            emit_rab(singleop, arg2, sp40, arg4, arg5, sp30);
            emit_rab(singleop, succ(arg2), sp3C, arg4, arg5, sp30);
        end else begin
            s3 := get_free_reg(nil, 1);
            if arg1 = fs_d then begin
                move_to_dest(s3, arg2, Rdt);
                emit_rab(zusw, s3, sp40, arg4, arg5, sp30);
                move_to_dest(s3, succ(arg2), Rdt);
                emit_rab(zusw, s3, sp3C, arg4, arg5, sp30);
            end else begin
                emit_rab(zulw, s3, sp40, arg4, arg5, sp30);
                move_to_dest(arg2, s3, Rdt);
                emit_rab(zulw, s3, sp3C, arg4, arg5, sp30);
                move_to_dest(succ(arg2), s3, Rdt);
            end;
            free_reg(s3);
        end;
    end;
begin
    v1 := integer(arg0^.u.Lexlev) div 8;
    sp30 := arg0^.u.Constval.Ival;

    if v1 = 0 then begin
        v1 := arg0^.u.Length;
    end;
    if align8 then begin
        v1 := 1;
    end else if align16 then begin
        v1 := 2;
    end else if align32 then begin
        v1 := 4;
    end else if align64 then begin
        v1 := 8;
    end;

    if (arg0^.u.Length > 4) and (arg0^.u.Length > v1) then begin
        if is_fp_reg(arg2) or (arg0^.u.Dtype in [Qdt, Rdt, Xdt]) then begin
            func_00426C54();
        end else if v1 < 4 then begin
            arg1 := double_to_singles[arg1];
            if lsb_first then begin
                emit_rab(unaligned_load_store_tab[arg1], arg2, arg3 + 4, arg4, arg5, sp30);
                emit_rab(unaligned_load_store_tab[arg1], succ(arg2), arg3, arg4, arg5, sp30);
            end else begin
                emit_rab(unaligned_load_store_tab[arg1], arg2, arg3, arg4, arg5, sp30);
                emit_rab(unaligned_load_store_tab[arg1], succ(arg2), arg3 + 4, arg4, arg5, sp30);
            end;
        end else begin
            arg1 := double_to_singles[arg1];
            emit_rab(arg1, arg2, arg3, arg4, arg5, sp30);
            emit_rab(arg1, succ(arg2), arg3 + 4, arg4, arg5, sp30);
        end;
    end else if (arg0^.u.Length = 4) and ((arg0^.u.Length > v1) or (arg3 mod v1 <> 0)) then begin
        if (arg0^.u.Dtype = Rdt) or is_fp_reg(arg2) then begin
            func_00426B44();
        end else begin
            emit_rab(unaligned_load_store_tab[arg1], arg2, arg3, arg4, arg5, sp30);
        end;
    end else if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
        emit_rab(arg1, arg2, arg3, arg4, arg5, sp30);
    end else if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (opcode_arch = ARCH_32) and (arg1 in [zld, zsd]) then begin
        arg1 := double_to_singles[arg1];
        if arg5 = arg2 then begin
            emit_dir0(iset, ord(set_noat));
            emit_rr(zmove, gpr_at, arg5);
            arg5 := gpr_at;
        end;

        emit_rab(arg1, arg2, arg3, arg4, arg5, sp30);
        emit_rab(arg1, succ(arg2), arg3 + 4, arg4, arg5, sp30);

        if arg5 = gpr_at then begin
            emit_dir0(iset, ord(set_at));
        end;
    end else if arg3 mod arg0^.u.Length <> 0 then begin
        emit_rab(unaligned_load_store_tab[arg1], arg2, arg3, arg4, arg5, sp30);
    end else if (v1 = 1) and (arg1 in [zlh, zlhu, zsh]) then begin
        emit_rab(unaligned_load_store_tab[arg1], arg2, arg3, arg4, arg5, sp30);
    end else begin
        emit_rab(arg1, arg2, arg3, arg4, arg5, sp30);
    end;
end;

procedure rloadrstore(arg0: ^tree;
                      arg1: asmcodes;
                      arg2: registers;
                      arg3: cardinal;
                      arg4: registers);
var
    v1: integer;

    procedure func_00427538;
    var
        s1: registers;
    begin
        emit_dir0(iset, ord(set_noat));
        if arg1 = fs_s then begin
            move_to_dest(gpr_at, arg2, Rdt);
            emit_rrab(zusw, gpr_at, 0, arg3, arg4);
        end else begin
            emit_rrab(zulw, gpr_at, 0, arg3, arg4);
            move_to_dest(arg2, gpr_at, Rdt);
        end;
        emit_dir0(iset, ord(set_at));
    end;

begin
    v1 := integer(arg0^.u.Lexlev) div 8;
    if v1 = 0 then begin
        v1 := arg0^.u.Length;
    end;

    if (arg0^.u.Length > 4) and (align32 or (arg0^.u.Length > v1)) then begin
        if is_fp_reg(arg2) then begin
            if lsb_first then begin
                emit_rrab(double_to_singles[arg1], arg2, 0, arg3, arg4);
                emit_rrab(double_to_singles[arg1], succ(arg2), 4, arg3, arg4);
            end else begin
                emit_rrab(double_to_singles[arg1], arg2, 4, arg3, arg4);
                emit_rrab(double_to_singles[arg1], succ(arg2), 0, arg3, arg4);
            end;
        end else if v1 < 4 then begin
            arg1 := double_to_singles[arg1];
            if lsb_first then begin
                emit_rrab(unaligned_load_store_tab[arg1], arg2, 4, arg3, arg4);
                emit_rrab(unaligned_load_store_tab[arg1], succ(arg2), 0, arg3, arg4);
            end else begin
                emit_rrab(unaligned_load_store_tab[arg1], arg2, 0, arg3, arg4);
                emit_rrab(unaligned_load_store_tab[arg1], succ(arg2), 4, arg3, arg4);
            end;
        end else begin
            arg1 := double_to_singles[arg1];
            emit_rrab(arg1, arg2, 0, arg3, arg4);
            emit_rrab(arg1, succ(arg2), 4, arg3, arg4);
        end;
    end else if (arg0^.u.Length = 4) and (arg0^.u.Length > v1) then begin
        if arg0^.u.Dtype = Rdt then begin
            func_00427538();
        end else begin
            emit_rrab(unaligned_load_store_tab[arg1], arg2, 0, arg3, arg4);
        end;
    end else if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
        emit_rrab(arg1, arg2, 0, arg3, arg4);
    end else if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (opcode_arch = ARCH_32) and (arg1 in [zld, zsd]) then begin
        arg1 := double_to_singles[arg1];
        if arg4 = arg2 then begin
            emit_dir0(iset, ord(set_noat));
            emit_rr(zmove, gpr_at, arg4);
            arg4 := gpr_at;
        end;

        emit_rrab(arg1, arg2, 0, arg3, arg4);
        emit_rrab(arg1, succ(arg2), 4, arg3, arg4);

        if arg4 = gpr_at then begin
            emit_dir0(iset, ord(set_at));
        end;
    end else if (v1 = 1) and (arg1 in [zlh, zlhu, zsh]) then begin
        emit_rrab(unaligned_load_store_tab[arg1], arg2, 0, arg3, arg4);
    end else begin
        emit_rrab(arg1, arg2, 0, arg3, arg4);
    end;
end;

procedure loadstore_for_two_words(arg0: asmcodes; arg1: ^tree; arg2: registers);
begin
    if lsb_first then begin
        loadstore(arg0, arg1, arg2, 4);
        loadstore(arg0, arg1, succ(arg2), 0);
    end else begin
        loadstore(arg0, arg1, arg2, 0);
        loadstore(arg0, arg1, succ(arg2), 4);
    end;
end;

procedure unaligned_loadstore_for_fp_word(arg0: asmcodes; arg1: ^tree; arg2: registers; arg3: integer);
var
    tempr: registers;
begin
    tempr := get_free_reg(nil, 1);
    if arg0 = fs_s then begin
        move_to_dest(tempr, arg2, Rdt);
        loadstore(zusw, arg1, tempr, 0);
    end else begin
        loadstore(zulw, arg1, tempr, 0);
        move_to_dest(arg2, tempr, Rdt);
    end;
    free_reg(tempr);
end;

procedure unaligned_loadstore_for_two_fp_w(arg0: asmcodes; arg1: ^tree; arg2: registers);
var
    sp24: integer;
    sp20: integer;
    tempr: registers;
begin
    if lsb_first or not is_fp_reg(arg2) then begin
        sp24 := 0;
        sp20 := 4;
    end else begin
        sp24 := 4;
        sp20 := 0;
    end;

    tempr := get_free_reg(nil, 1);
    if arg0 = fs_s then begin
        move_to_dest(tempr, arg2, Rdt);
        loadstore(zusw, arg1, tempr, sp24);
        move_to_dest(tempr, succ(arg2), Rdt);
        loadstore(zusw, arg1, tempr, sp20);
    end else begin
        loadstore(zulw, arg1, tempr, sp24);
        move_to_dest(arg2, tempr, Rdt);
        loadstore(zulw, arg1, tempr, sp20);
        move_to_dest(succ(arg2), tempr, Rdt);
    end;
    free_reg(tempr);
end;

procedure loadstore_for_two_fp_words(arg0: asmcodes; arg1: ^tree; arg2: registers);
begin
    if lsb_first then begin
        loadstore(arg0, arg1, arg2, 0);
        loadstore(arg0, arg1, succ(arg2), 4);
    end else if is_fp_reg(arg2) then begin
        loadstore(arg0, arg1, arg2, 4);
        loadstore(arg0, arg1, succ(arg2), 0);
    end else begin
        loadstore(arg0, arg1, arg2, 0);
        loadstore(arg0, arg1, succ(arg2), 4);
    end;
end;

procedure unaligned_loadstore(arg0: asmcodes; arg1: ^tree; arg2: registers);
var
    sp24: integer;

    procedure func_00428190();
        procedure func_00427FB8();
        begin
            arg0 := double_to_singles[arg0];
            if lsb_first then begin
                loadstore(unaligned_load_store_tab[arg0], arg1, arg2, 4);
                loadstore(unaligned_load_store_tab[arg0], arg1, succ(arg2), 0);
            end else begin
                loadstore(unaligned_load_store_tab[arg0], arg1, arg2, 0);
                loadstore(unaligned_load_store_tab[arg0], arg1, succ(arg2), 4);
            end;
        end;

        procedure func_004280C4();
        begin
            arg0 := double_to_singles[arg0];
            if is_fp_reg(arg2) or (arg1^.u.Dtype in [Qdt, Rdt, Xdt]) then begin
                unaligned_loadstore_for_two_fp_w(arg0, arg1, arg2);
            end else begin
                loadstore_for_two_words(arg0, arg1, arg2);
            end;
        end;
    begin
        if ((arg1^.u.Offset mod 4) <> 0) and not is_fp_reg(arg2) then begin
            func_00427FB8();
        end else if ((arg1^.u.Offset mod 8) <> 0) or ((sp24 mod 8) <> 0) then begin
            func_004280C4();
        end else if (arg1^.u.Dtype in [Idt, Kdt, Qdt, Wdt]) and (arg0 in [zld, zsd]) and ((opcode_arch = ARCH_32) or (regs[arg2].unk9 = succ(arg2))) then begin
            arg0 := double_to_singles[arg0];
            if is_fp_reg(arg2) or (arg1^.u.Dtype in [Qdt, Rdt, Xdt]) then begin
                loadstore_for_two_fp_words(arg0, arg1, arg2);
            end else begin
                loadstore_for_two_words(arg0, arg1, arg2);
            end;
        end else begin
            loadstore(arg0, arg1, arg2, 0);
        end;
    end;
begin
    if align8 then begin
        sp24 := 1;
    end else if align16 then begin
        sp24 := 2;
    end else if align32 then begin
        sp24 := 4;
    end else begin
        sp24 := 8;
    end;

    if arg1^.u.Length > 4 then begin
        func_00428190();
    end else if (arg1^.u.Length = 4) and (arg1^.u.Offset mod 4 <> 0) then begin
        if is_fp_reg(arg2) then begin
            unaligned_loadstore_for_fp_word(arg0, arg1, arg2, 0);
        end else begin
            loadstore(unaligned_load_store_tab[arg0], arg1, arg2, 0);
        end;
    end else if (arg1^.u.Offset mod arg1^.u.Length) <> 0 then begin
        loadstore(unaligned_load_store_tab[arg0], arg1, arg2, 0);
    end else begin
        loadstore(arg0, arg1, arg2, 0);
    end;
end;

procedure eval_2ops(arg0: ^tree);
begin
    if arg0^.op1^.unk16 >= arg0^.op2^.unk16 then begin
        eval(arg0^.op1, xnoreg);
        eval(arg0^.op2, xnoreg);
    end else begin
        eval(arg0^.op2, xnoreg);
        eval(arg0^.op1, xnoreg);
    end;
end;

procedure eval_fp_cond(arg0: ^tree; arg1: registers);
var
    sp2F: registers;
    sp2E: registers;
    sp28: integer;
    var_s1: asmcodes;
begin
    var_s1 := fop(arg0^.u.Opc, arg0^.u.Dtype);
    eval_2ops(arg0);
    if arg0^.u.Opc in [Ugeq, Ugrt] then begin
        sp2E := flt_reg(arg0^.op1);
        sp2F := flt_reg(arg0^.op2);
    end else begin
        sp2F := flt_reg(arg0^.op1);
        sp2E := flt_reg(arg0^.op2);
    end;
    emit_rr(var_s1, sp2F, sp2E);
    arg1 := get_dest(arg0, arg1);
    emit_rr(zmove, arg1, xr0);
    sp28 := gen_label_id();
    var_s1 := zbc1f;
    if arg0^.u.Opc = Uneq then begin
        var_s1 := zbc1t;
    end;
    emit_ll(var_s1, sp28);
    emit_ri_(zli, arg1, 1, franone);
    define_label(sp28);
end;

procedure eval_fp_min_max(arg0: ^tree; arg1: registers);
var
    sp36: asmcodes;
    sp34: asmcodes;
    temp_s1: integer;
    sp2F: registers;
    sp2E: registers;
    temp_v0: registers;
begin
    sp36 := fop(arg0^.u.Opc, arg0^.u.Dtype);
    sp34 := zbc1t;
    if arg0^.u.Opc = Umax then begin
        sp34 := zbc1f;
    end;
    eval(arg0^.op1, xnoreg);
    eval(arg0^.op2, xnoreg);
    sp2F := flt_reg(arg0^.op1);
    sp2E := flt_reg(arg0^.op2);
    if (arg1 = xnoreg) or not (arg1 in [xfr0..xfr31]) then begin
        if (usage_count(sp2F) = 0) and is_available(sp2F) then begin
            arg1 := sp2F;
            get_fp_reg(sp2F, arg0, reg_kind_tab[arg0^.u.Dtype], arg0^.ref_count);
        end else if (usage_count(sp2E) = 0) and is_available(sp2E) then begin
            temp_v0 := sp2F;
            sp2F := sp2E;
            sp2E := temp_v0;
            arg1 := sp2F;
            get_fp_reg(sp2F, arg0, reg_kind_tab[arg0^.u.Dtype], arg0^.ref_count);
        end else begin
            arg1 := get_free_fp_reg(arg0, reg_kind_tab[arg0^.u.Dtype], arg0^.ref_count);
        end;
    end else begin
        get_fp_reg(arg1, arg0, reg_kind_tab[arg0^.u.Dtype], arg0^.ref_count);
    end;
    arg0^.reg := arg1;
    if arg1 = sp2E then begin
        sp2E := sp2F;
    end else if arg1 <> sp2F then begin
        move_to_dest(arg1, sp2F, arg0^.u.Dtype);
    end;
    temp_s1 := gen_label_id();
    emit_rr(sp36, arg1, sp2E);
    emit_ll(sp34, temp_s1);
    move_to_dest(arg1, sp2E, arg0^.u.Dtype);
    define_label(temp_s1);
end;

procedure eval2(arg0: asmcodes; arg1: ^tree; arg2: registers);
var
    sp2F: registers;
    sp2E: registers;
    sp2C: registers;
begin
    eval_2ops(arg1);

    if arg1^.u.Dtype in [Qdt, Rdt, Xdt] then begin
        binary_flt_regs(arg1^.op1, arg1^.op2, sp2F, sp2E);
    end else if arg1^.u.Dtype in [Idt, Kdt, Wdt] then begin
        binary_regs(arg1^.op1, arg1^.op2, sp2F, sp2E);
    end else begin
        binary_regs(arg1^.op1, arg1^.op2, sp2F, sp2E);
    end;

    if (arg1^.u.Dtype in [Qdt, Rdt, Xdt]) and not (arg2 in [xfr0..xfr31]) then begin
        arg2 := xnoreg;
    end;

    sp2C := get_dest(arg1, arg2);
    dw_emit_rrr(arg0, sp2C, sp2F, sp2E, arg1);
end;

function ureg(var arg0: Bcrec): integer;
begin
    if arg0.Mtype = Rmt then begin
        return arg0.Offset div 4;
    end else begin
        return ord(xnoreg);
    end;
end;

function copy(arg0: registers): registers;
var
    a1: registers;
begin
    assert(arg0 in [xr0..xr31]);

    if (usage_count(arg0) = 0) and is_available(arg0) then begin
        get_reg(arg0, nil, 1);
        return arg0;
    end else begin
        a1 := get_free_reg(nil, 1);
        if a1 <> arg0 then begin
            emit_rr(zmove, a1, arg0);
        end;
        return a1;
    end;
end;

procedure eval_mov(arg0: ^tree);
var
    var_s1: cardinal;
    sp118: integer;
    sp114: integer;
    sp110: ^tree;
    sp10C: ^tree;
    var_s2: integer;
    var_s3: integer;
    loadop: asmcodes;
    storeop: asmcodes;
    spFF: registers;
    spFE: registers;
    spFD: registers;
    spFC: registers;
    spFB: registers;
    var_s0: cardinal;
    spF0: integer;
    spEF: boolean;
    spEE: boolean;
    spED: boolean;
    temp_v1: cardinal;
    var_a3: cardinal;
begin
    var_s1 := arg0^.u.Length;
    if arg0^.u.Opc = Umov then begin
        sp118 := arg0^.u.I1;
        if arg0^.u.Lexlev <> 0 then begin
            sp114 := arg0^.u.Lexlev;
        end else begin
            sp114 := sp118;
        end;
        sp110 := arg0^.op1;
        sp10C := arg0^.op2;
    end else begin
        sp110 := nil;
        sp118 := arg0^.u.Lexlev;
        sp114 := sp118;
        sp10C := arg0^.op1;
    end;
    sp118 := sp118 div 8;
    sp114 := sp114 div 8;
    var_s3 := 0;
    if (sp110 <> nil) and (sp110^.ref_count = 1) and (sp110^.u.Opc = Uadd) and is_constant(sp110^.op2) and (sp110^.op2^.u.Constval.Ival >= -16#8000) and (sp110^.op2^.u.Constval.Ival < 16#8000) then begin
        var_s3 := sp110^.op2^.u.Constval.Ival;
        sp110 := sp110^.op1;
    end;
    var_s2 := 0;
    if (sp10C^.ref_count = 1) and (sp10C^.u.Opc = Uadd) and is_constant(sp10C^.op2) and (sp10C^.op2^.u.Constval.Ival >= -16#8000) and (sp10C^.op2^.u.Constval.Ival < 16#8000) then begin
        var_s2 := sp10C^.op2^.u.Constval.Ival;
        sp10C := sp10C^.op1;
    end;
    if (var_s1 in [1, 2, 4]) and
        (((cardinal(sp118) >= 2) and (cardinal(sp114) >= 2)) or (var_s1 <> 2)) and
        ((sp110 = nil) or ((sp110^.ref_count = 1) and (sp110^.u.Opc = Ulda))) and
        (sp10C^.ref_count = 1) and
        (sp10C^.u.Opc = Ulda) then begin

        spFF := get_free_reg(nil, 1);
        free_reg(spFF);
        case var_s1 of
            1: begin
                loadop := zlbu;
                storeop := zsb;
            end;
            2: begin
                loadop := zlhu;
                storeop := zsh;
            end;
            4: begin
                if sp118 < 4 then begin
                    loadop := zulw;
                end else begin
                    loadop := zlw;
                end;
                if sp114 < 4 then begin
                    storeop := zusw;
                end else begin
                    storeop := zsw;
                end;
            end;
        end;
        case sp10C^.u.Mtype of
            Mmt, Pmt: begin
                if get_sym_kind(sp10C^.u.I1) = 5 then begin
                    if basicint = 1 then begin
                        emit_rrri(zdsubu, spFF, frame_pointer, sp10C^.u.I1);
                    end else begin
                        emit_rrri(zsubu, spFF, frame_pointer, sp10C^.u.I1);
                    end;
                    emit_rob(loadop, spFF, 0, spFF, 0);
                end else begin
                    var_s2 := var_s2 + frame_offset(sp10C);
                    emit_rob(loadop, spFF, var_s2, frame_pointer, 0);
                end;
            end;
            Smt: begin
                var_s2 := var_s2 + sp10C^.u.Offset;
                emit_ra(loadop, spFF, sp10C^.u.I1, var_s2, 0);
            end;
            otherwise begin
                report_error(Internal, 2548, "eval.p", "Unknown memory type in LDA");
            end;
        end;
        if sp110 = nil then begin
            emit_rob(storeop, spFF, var_s3 + arg0^.u.Offset, xr29, 0);
        end else begin
            case sp110^.u.Mtype of
                Mmt, Pmt: begin
                    if get_sym_kind(sp110^.u.I1) = 5 then begin
                        if basicint = 1 then begin
                            emit_rrri(zdsubu, spFF, frame_pointer, sp110^.u.I1);
                        end else begin
                            emit_rrri(zsubu, spFF, frame_pointer, sp110^.u.I1);
                        end;
                        emit_rob(storeop, spFF, 0, spFF, 0);
                    end else begin
                        var_s3 := var_s3 + frame_offset(sp110);
                        emit_rob(storeop, spFF, var_s3, frame_pointer, 0);
                    end;
                end;
                Smt: begin
                    var_s3 := var_s3 + sp110^.u.Offset;
                    emit_ra(storeop, spFF, sp110^.u.I1, var_s3, 0);
                end;
                otherwise begin
                    report_error(Internal, 2579, "eval.p", "Unknown memory type in LDA");
                end;
            end;
        end;
    end else begin
        if sp110 <> nil then begin
            eval(sp110, xnoreg);
        end;
        eval(sp10C, xnoreg);
        if sp110 = nil then begin
            spFB := xr29;
            var_s3 := var_s3 + arg0^.u.Offset;
        end else begin
            spFB := reg(sp110);
        end;
        spFC := reg(sp10C);
        spFE := get_free_reg(nil, 1);
        if free_reg_is_available() or (var_s3 >= 16#8000 - 12) or (var_s2 >= 16#8000 - 12) or
            (((var_s3 + var_s1 >= 16#8000) or (var_s2 + var_s1 >= 16#8000)) and (integer(var_s1) <= 32)) then begin
            spEF := true;
            spFF := get_free_reg(nil, 1);
        end else begin
            spEF := false;
            emit_dir0(iset, 6);
            spFF := xr1;
        end;
        if sp118 < 4 then begin
            loadop := zulw;
        end else begin
            loadop := zlw;
        end;
        if sp114 < 4 then begin
            storeop := zusw;
        end else begin
            storeop := zsw;
        end;
        if (opcode_arch = ARCH_64) and (sp118 = 8) and (sp114 = 8) then begin
            spED := true;
            var_s0 := 8;
            loadop := zld;
            storeop := zsd;
        end else begin
            spED := false;
            var_s0 := 4;
        end;
        if var_s1 > var_s0 * 8 then begin
            spFC := copy(spFC);
            spFB := copy(spFB);
            if spEF and not free_reg_is_available() then begin
                spEF := false;
                emit_dir0(iset, 6);
                spFD := xr1;
            end else begin
                spFD := get_free_reg(nil, 1);
                free_reg(spFD);
            end;
            free_reg(spFC);
            free_reg(spFB);

            temp_v1 := var_s0 * 3;
            var_a3 := (var_s1 div temp_v1) * temp_v1;
            var_s1 := var_s1 - var_a3;

            emit_rri_(zaddu, spFD, spFC, var_a3, franone);

            spF0 := gen_label_id();
            define_label(spF0);

            emit_rob(loadop, spFF, var_s2 + var_s0 * 0, spFC, 0);
            emit_rri_(zaddu, spFC, spFC, var_s0 * 3, franone);
            emit_rob(storeop, spFF, var_s3 + var_s0 * 0, spFB, 0);
            emit_rob(loadop, spFE, var_s2 - var_s0 * 2, spFC, 0);
            emit_rri_(zaddu, spFB, spFB, var_s0 * 3, franone);
            emit_rob(storeop, spFE, var_s3 - var_s0 * 2, spFB, 0);
            emit_rob(loadop, spFF, var_s2 - var_s0 * 1, spFC, 0);
            emit_rob(storeop, spFF, var_s3 - var_s0 * 1, spFB, 0);
            emit_rrll(zbne, spFC, spFD, spF0);

            if not spEF and (spFD = xr1) then begin
                spEF := true;
                emit_dir0(iset, 5);
            end;
        end;
        spEE := false;
        if (sp110 <> nil) and (sp110^.u.Opc = Ulda) and (sp10C^.u.Opc = Ulda) and (sp110^.u.I1 <> sp10C^.u.I1) then begin
            spEE := true;
            emit_alias(inoalias, spFC, spFB);
        end;
        while var_s1 >= var_s0 do begin
            emit_rob(loadop, spFF, var_s2, spFC, 0);
            emit_rob(storeop, spFF, var_s3, spFB, 0);
            var_s2 := var_s2 + var_s0;
            var_s3 := var_s3 + var_s0;
            var_s1 := var_s1 - var_s0;

            if var_s1 >= var_s0 then begin
                emit_rob(loadop, spFE, var_s2, spFC, 0);
                emit_rob(storeop, spFE, var_s3, spFB, 0);
                var_s2 := var_s2 + var_s0;
                var_s3 := var_s3 + var_s0;
                var_s1 := var_s1 - var_s0;
            end;
        end;
        if (var_s1 >= 4) and spED then begin
            emit_rob(zlw, spFE, var_s2, spFC, 0);
            emit_rob(zsw, spFE, var_s3, spFB, 0);
            var_s2 := var_s2 + 4;
            var_s3 := var_s3 + 4;
            var_s1 := var_s1 - 4;
        end;
        case var_s1 of
            0: begin end;
            1: begin
                emit_rob(zlbu, spFF, var_s2, spFC, 0);
                emit_rob(zsb, spFF, var_s3, spFB, 0);
            end;
            2: begin
                if (cardinal(sp118) < 2) or (cardinal(sp114) < 2) then begin
                    emit_rob(zlbu, spFF, var_s2, spFC, 0);
                    emit_rob(zsb, spFF, var_s3, spFB, 0);
                    emit_rob(zlbu, spFE, var_s2 + 1, spFC, 0);
                    emit_rob(zsb, spFE, var_s3 + 1, spFB, 0);
                end else begin
                    emit_rob(zlhu, spFF, var_s2, spFC, 0);
                    emit_rob(zsh, spFF, var_s3, spFB, 0);
                end;
            end;
            3: begin
                if (sp118 >= 4) and (sp114 >= 4) then begin
                    if lsb_first then begin
                        emit_rob(zlwl, spFF, var_s2 + 2, spFC, 0);
                        emit_rob(zswl, spFF, var_s3 + 2, spFB, 0);
                    end else begin
                        emit_rob(zlwr, spFF, var_s2 + 2, spFC, 0);
                        emit_rob(zswr, spFF, var_s3 + 2, spFB, 0);
                    end;
                end else if (cardinal(sp118) >= 2) and (cardinal(sp114) >= 2) then begin
                    emit_rob(zlhu, spFF, var_s2, spFC, 0);
                    emit_rob(zsh, spFF, var_s3, spFB, 0);
                    emit_rob(zlbu, spFE, var_s2 + 2, spFC, 0);
                    emit_rob(zsb, spFE, var_s3 + 2, spFB, 0);
                end else begin
                    emit_rob(zlbu, spFF, var_s2, spFC, 0);
                    emit_rob(zsb, spFF, var_s3, spFB, 0);
                    emit_rob(zlbu, spFE, var_s2 + 1, spFC, 0);
                    emit_rob(zsb, spFE, var_s3 + 1, spFB, 0);
                    emit_rob(zlbu, spFF, var_s2 + 2, spFC, 0);
                    emit_rob(zsb, spFF, var_s3 + 2, spFB, 0);
                end;
            end;
        end;
        free_reg(spFE);
        if spEE then begin
            emit_alias(ialias, spFC, spFB);
        end;
        if not spEF then begin
            emit_dir0(iset, 5);
        end else begin
            free_reg(spFF);
        end;
    end;
end;

procedure get_ops(arg0: ^tree; var arg1: asmcodes; var arg2: asmcodes; var arg3: integer);
var
    t0: integer;
    t1: integer;
begin
    assert(arg0^.u.Opc in [Uiequ, Uigeq, Uigrt, Uileq, Uiles, Uineq, Umov, Umpmv, Upmov]);

    t1 := arg0^.u.Length;
    t0 := arg0^.u.I1;
    
    if (arg0^.u.Opc = Upmov) or (arg0^.u.Opc = Umpmv) then begin
        t0 := arg0^.u.Lexlev;
    end;

    case arg0^.u.Opc of
        Uiequ,
        Uineq,
        Umov,
        Umpmv,
        Upmov:
        begin
            if ((t0 = 32) and (t1 mod 4 = 0)) or ((t0 = 64) and (t1 mod 8 = 0)) then begin
                arg1 := zlw;
                arg2 := zsw;
                arg3 := 4;
            end else if (t0 = 16) and (t1 mod 2 = 0) then begin
                arg1 := zlhu;
                arg2 := zsh;
                arg3 := 2;
            end else begin
                arg1 := zlbu;
                arg2 := zsb;
                arg3 := 1;
            end;

            if (arg0^.u.Opc <> Umov) and (arg0^.u.Opc <> Upmov) and (arg0^.u.Opc <> Umpmv) then begin
                arg2 := znop;
            end;
        end;

        Uigrt,
        Uiles,
        Uigeq,
        Uileq:
        begin
            arg1 := zlbu;
            arg2 := op_tab[arg0^.u.Opc];
            arg3 := 1;
        end;

        otherwise report_error(Internal, 2835, 'eval.p', 'illegal indirect opcode');
    end;
end;

procedure eval_irel(arg0: ^tree);
var
    sp4F: registers;
    sp4E: registers;
    sp4D: registers;
    sp4C: registers;
    sp4B: registers;
    sp44: integer;
    sp40: integer;
    sp3C: integer;
    sp3A: asmcodes;
    sp38: asmcodes;
    sp34: integer;
begin
    eval(arg0^.op1, xnoreg);
    eval(arg0^.op2, xnoreg);
    get_ops(arg0, sp3A, sp38, sp34);
    sp4D := copy(reg(arg0^.op1));
    sp4C := copy(reg(arg0^.op2));
    sp4B := get_free_reg(arg0, arg0^.ref_count);
    sp4E := get_free_reg(nil, 1);
    sp44 := gen_label_id();
    sp40 := gen_label_id();
    sp3C := gen_label_id();
    emit_rri_(zadd, sp4B, sp4D, arg0^.u.Length, franone);
    define_label(sp44);
    emit_dir0(iset, 6);
    emit_rob(sp3A, xr1, 0, sp4D, 0);
    emit_rri_(zadd, sp4D, sp4D, sp34, franone);
    emit_rob(sp3A, sp4E, 0, sp4C, 0);
    emit_rri_(zadd, sp4C, sp4C, sp34, franone);
    emit_rrll(zbne, xr1, sp4E, sp40);
    emit_rrll(zbne, sp4D, sp4B, sp44);
    emit_dir0(iset, 5);
    case arg0^.u.Opc of
        Uiequ: begin
            emit_ri_(zli, sp4B, 1, franone);
            emit_ll(zb, sp3C);
            define_label(sp40);
            emit_ri_(zli, sp4B, 0, franone);
            define_label(sp3C);
        end;
        Uineq: begin
            emit_ri_(zli, sp4B, 0, franone);
            emit_ll(zb, sp3C);
            define_label(sp40);
            emit_ri_(zli, sp4B, 1, franone);
            define_label(sp3C);
        end;
        Uileq, Uiles: begin
            define_label(sp40);
            emit_rrr(sp38, sp4B, xr1, sp4E);
        end;
        Uigeq, Uigrt: begin
            define_label(sp40);
            emit_rrr(sp38, sp4B, sp4E, xr1);
        end;
    end;
    arg0^.reg := sp4B;
    free_reg(sp4D);
    free_reg(sp4C);
    free_reg(sp4E);
end;

procedure save_vreg(arg0: ^tree);
var
    sp27: registers;
begin
    sp27 := registers(arg0^.u.Constval.Ival div 4);

    if is_saved_reg(sp27) then begin
        saved_regs := saved_regs + [sp27];
        if (arg0^.u.Length > 4) or (arg0^.u.Dtype in [Qdt, Rdt, Xdt]) then begin
            saved_regs := saved_regs + [succ(sp27)];
        end;
    end else begin
        saved_regs := saved_regs - [sp27];
        if sp27 in [xfr0..xfr31] then begin
            saved_regs := saved_regs - [succ(sp27)];
            remove_from_fp_free_list(sp27, d_reg);
        end else begin
            remove_from_free_list(sp27);
            if arg0^.u.Length > 4 then begin
                saved_regs := saved_regs - [succ(sp27)];
                remove_from_free_list(succ(sp27));
            end;
        end;
    end;
end;

function pass_in_register(arg0: ^tree): registers;
var
    cur: ^tree;
begin
    cur := pdefs;
    while cur <> nil do begin
        if overlap(arg0, cur) then begin
            return parm_reg(cur);
        end;

        cur := cur^.next;
    end;
    return xnoreg;
end;

procedure load_parm_vreg(arg0: ^tree);
var
    s0: registers;
    v0: registers;
begin
    s0 := registers(arg0^.u.Constval.Ival div 4);
    v0 := pass_in_register(arg0);

    if v0 <> xnoreg then begin
        move_to_dest(s0, v0, arg0^.u.Dtype);
        if (source_language = C_SOURCE) and (arg0^.u.Length < 4) then begin
            if arg0^.u.Dtype = Jdt then begin
                emit_rri_(zsll, s0, s0, 32 - arg0^.u.Length * 8, franone);
                emit_rri_(zsra, s0, s0, 32 - arg0^.u.Length * 8, franone);
            end else begin
                emit_rri_(zand, s0, s0, lshift(1, arg0^.u.Length * 8) - 1, franone);
            end;
        end;
    end else begin
        loadstore(lsopc(load_table, arg0, s0), arg0, s0, 0);
    end;
end;

procedure eval{(arg0: ^tree; arg1: registers)};
begin
end;
