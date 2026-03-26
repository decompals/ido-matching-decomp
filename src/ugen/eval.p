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
#include "entry_exit.h"
#include "val_util.h"
#include "lit_mgr.h"
#include "ibuffer.h"
#include "tree_print.h"

function get_domtag(): integer; external;

procedure eval(arg0: ^tree; arg1: registers); forward;
function reg(arg0: ^tree): registers; forward;
function flt_reg(arg0: ^tree): registers; forward;
procedure move_to_dest(arg0: registers; arg1: registers; arg2: Datatype); forward;
procedure load_fp_literal(arg0: ^tree; arg1: registers); forward;
procedure eval_flt_flt_cvt(arg0: ^tree; arg1: registers); forward;
procedure eval_flt_int_cvt(arg0: ^tree; arg1: registers); forward;
procedure eval_int_flt_cvt(arg0: ^tree; arg1: registers); forward;
procedure eval_int_int_cvt(arg0: ^tree; arg1: registers); forward;

type
    Scalar_types = (ST_s8, ST_u8, ST_s16, ST_u16, ST_s32, ST_u32, ST_s64, ST_f32, ST_f64);

    asmcodearray = array[Scalar_types] of asmcodes;

    sp1Ctype = record
        case integer of
        0: (asint: integer);
        1: (unk0: u16; unk2: u8; unk3: u8);
    end;

var
    reversed_stack: boolean;
    frame_pointer: registers;
    basicint: u8;
    pic_level: integer;
    align8: boolean;
    align16: boolean;
    align32: boolean;
    align64: boolean;
    pdefs: ^tree;
    source_language: integer;
    ignore_vreg: boolean;
    pseudo_leaf: boolean;
    use_real_fp_for_proc: boolean;
    ufsa: boolean;
    cpalias_ok: boolean;
    use_cpalias: boolean;
    pmov_regs: set of registers;
    current_line: cardinal;
    first_loc: boolean;
    first_file_number: integer;
    first_line_number: integer;
    ascii_out: boolean;
    stack_limit_bn: integer;
    noalias_regs: array[registers] of cardinal;
    noalias_on_off: array[registers] of boolean;
    use_real_fp_for_all: boolean;
    use_fp: boolean;
    framesz_relocatable: boolean;
    home_vararg_reg: boolean;
    generate_again: boolean;
    saved_regs_size: cardinal;
    frame_size: cardinal;
    local_var_size: integer;
    max_arg_build: integer;
    reloc_arg_build: integer;
    temp_size: integer;
    has_calls: boolean;
    uses_gp: boolean;
    num_i_ptr_indexes: cardinal;
    curlev: integer;
    entry_point_index: integer;
    load_stack_limit: boolean;
    has_aent: boolean;
    current_text_sec: Valu;
    first_ent: boolean;
    resident_text: boolean;
    debug_ugen: boolean;
    glevel: u8;
    has_cia_in_file: boolean;
    i_ptrs_for_gp_offset: array[1..20] of integer;
    first_pmt_offset: integer;
    olevel: u8;
    no_jal_use_jalr_only: boolean;
    opt_cse: u8;
    max_stack: integer;

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
        regs[arg0].dw_link := succ(arg0);
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
           (reg >= fpr_fs0) and (reg <= registers(ord(fpr_fs0) + 2 * (n_saved_fp_regs - 1)));
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
        end else if (arg1^.u.Dtype in [Idt, Kdt, Qdt, Wdt]) and (arg0 in [zld, zsd]) and ((opcode_arch = ARCH_32) or (regs[arg2].dw_link = succ(arg2))) then begin
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

function ureg(var arg0: Bcrec): registers;
begin
    if arg0.Mtype = Rmt then begin
        return registers(arg0.Offset div 4);
    end else begin
        return xnoreg;
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
#line 2500
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
#line 2709
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
#line 2881
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

{ exactly the same as is_parm_regs }
function in_parm_regs(reg: registers): boolean;
begin
    return (reg >= gpr_a0) and (reg <= registers(ord(gpr_a0) + n_parm_regs - 1)) or
           (reg >= xfr12) and (reg <= registers(ord(xfr12) + 2 * (n_fp_parm_regs - 1)));
end;

procedure gen_regs(arg0: ^tree);
var
    v0: registers;
    v1: registers;
    s0: registers;
begin
    v0 := registers(arg0^.u.Offset);
    v1 := registers(ord(v0) + arg0^.u.Length - 1);

    case arg0^.u.I1 of
        2, 4:
        begin
            for s0 := v0 to v1 do begin
                saved_regs := saved_regs + [s0];
                if s0 in ugen_fp_callee_saved then begin
                    ugen_fp_callee_saved := ugen_fp_callee_saved - [s0];
                    remove_from_fp_free_list(s0, no_reg);
                end;
            end;
        end;

        1:
        begin
            for s0 := v0 to v1 do begin
                saved_regs := saved_regs - [s0];
                if not in_parm_regs(s0) then begin
                    remove_from_free_list(s0);
                end;
            end;
        end;

        3:
        begin
            s0 := v0;
            while ord(s0) <= ord(v1) do begin
                saved_regs := saved_regs - [s0];
                saved_regs := saved_regs - [succ(s0)];
                if not in_parm_regs(s0) then begin
                    remove_from_fp_free_list(s0, d_reg);
                end;
                s0 := succ(succ(s0));
            end;
        end;

        otherwise;
    end;
end;

function get_saved_regs_size(arg0: ^tree): integer;
var
    v1: integer;
    a0: registers;
    a3: integer;
    a2: integer;
    t0: boolean;    
    
begin
    if basicint = 0 then begin
        a2 := 4;
    end else begin
        a2 := 8;
    end;

    v1 := 0;
    a3 := 6;
    t0 := false;

    arg0 := arg0^.next;
    while arg0 <> nil do begin
        case arg0^.u.Opc of
            Uvreg:
            begin
                if (arg0^.u.Constval.Ival <> -1) and not ignore_vreg then begin
                    a0 := registers(arg0^.u.Constval.Ival div 4);
                    if is_saved_reg(a0) then begin
                        if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                            v1 := v1 + 8;
                        end else begin
                            v1 := v1 + ((arg0^.u.Length + 3) div 4) * 4;
                        end;
                    end;
                end;
            end;

            Udef:
            begin
                if arg0^.u.Mtype = Tmt then begin
                    if pic_level > 0 then begin
                        v1 := v1 + a2 * 2;
                    end else begin
                        v1 := v1 + a2;
                    end;

                    if pseudo_leaf then begin
                        v1 := v1 - a2;
                    end;
                end;

                if use_real_fp_for_proc then begin
                    v1 := v1 + a2;
                end;
            end;

            Uregs:
            begin
                if (arg0^.u.Offset < 31) and (arg0^.u.Offset + arg0^.u.Length >= 31) then begin
                    t0 := true;
                end;

                if arg0^.u.I1 = 2 then begin
                    v1 := v1 + arg0^.u.Length * 4;
                end else if arg0^.u.I1 = 4 then begin
                    v1 := v1 + arg0^.u.Length * 4;
                    a3 := a3 - arg0^.u.Length;
                end;
            end;

            Ulod,
            Uend,
            Ustp,
            Ustr:
            begin
                if ufsa or ufsm then begin
                    v1 := v1 + a3 * 8;
                end;

                if cpalias_ok then begin
                    use_cpalias := (pic_level > 0) and not pseudo_leaf and not t0;
                end;

                if v1 = 0 then begin
                    return v1;
                end else begin
                    return ((v1 + 8) div 8) * 8;
                end;
            end;
            
            otherwise;
        end;
            
        arg0 := arg0^.next;
    end;
end;

procedure unhome_parms;
var
    r: registers;
begin
    for r := gpr_a0 to registers(ord(gpr_a0) + n_parm_regs - 1) do begin
        saved_regs := saved_regs - [r];
    end;
end;

procedure home_parms(arg0: integer);
label out;
var
    r: registers;
    s3: ^tree;
    v0: registers;
    s0: integer;
begin
    s3 := pdefs;
    while s3 <> nil do begin
        if (s3^.u.Lexlev <> 2) then begin
            if not pass_in_reg(s3) then begin
                break;
            end;
        
            v0 := parm_reg(s3);
            if v0 in [xfr0..xfr31] then begin
                saved_regs := saved_regs + [v0];
                if s3^.u.Length > 4 then begin
                    Assert((s3^.u.Dtype in [Idt, Kdt, Wdt]) or (s3^.u.Dtype = Qdt));
                    saved_regs := saved_regs + [succ(v0)];
                end;
            end else begin
                s0 := (s3^.u.Length + 3) div 4;
                while s0 <> 0 do begin
                    saved_regs := saved_regs + [v0];
                    if not is_parm_reg(v0) then begin
                        goto out;
                    end;
                    v0 := succ(v0);
                    s0 := s0 - 1;
                end;
            end;
        end;
        
        s3 := s3^.next;
    end;

out:
    
    if arg0 <> -1 then begin
        arg0 := (arg0 mod 16#10000) div 4;
        for r := registers(ord(gpr_a0) + arg0) to registers(ord(gpr_a0) + n_parm_regs - 1) do begin
            saved_regs := saved_regs + [r];
        end;
    end;
end;

procedure clean_tree(arg0: ^tree);
begin
    repeat
        arg0^.unk18 := 0;
        arg0^.reg := xnoreg;
        
        if (arg0^.op1 <> nil) and not(arg0^.u.Opc in [Uent, Uaent, Ulab, Uclab, Ucg2]) then begin
            clean_tree(arg0^.op1);
        end;

        if (arg0^.op2 <> nil) and not(arg0^.u.Opc in [Uent, Uaent, Ulab, Uclab, Ucg2, Ufjp, Uijp, Utjp, Uujp, Uxjp]) then begin
            clean_tree(arg0^.op2);
        end;

        arg0 := arg0^.next;
    until arg0 = nil;
end;

procedure clear_pmov_regs;
begin
    pmov_regs := [];
end;

procedure save_pmov_reg(reg: registers);
begin
    pmov_regs := pmov_regs + [reg];
end;

procedure load_pmov_regs;
var
    r: registers;
begin
    if pmov_regs <> [] then begin
        for r := gpr_a0 to registers(ord(gpr_a0) + n_parm_regs - 1) do begin
            if r in pmov_regs then begin
                emit_rob(zlw, r, 4 * (ord(r) - ord(gpr_a0)), gpr_sp, 0);
            end;
        end;
    end;
end;

function cvt_tab(arg0: Datatype; arg1: Datatype): asmcodes;
begin
    case arg0 of
        Adt, Hdt, Jdt, Ldt:
        case arg1 of
            Rdt: return fcvt_s_w;
            Qdt: return fcvt_d_w;
            otherwise return znop;
        end;

        Idt,
        Kdt,
        Wdt:
        case arg1 of
            Rdt: return fcvt_s_l;
            Qdt: return fcvt_d_l;
            otherwise return znop;
        end;

        Rdt:
        case arg1 of
            Idt: return ztrunc_l_s;
            Jdt: return ztrunc_w_s;
            Kdt, Wdt: return ztrunc_l_s;
            Adt, Hdt, Ldt: return ztrunc_w_s;
            Qdt: return fcvt_d_s;
            otherwise return znop;
        end;

        Qdt:
        case arg1 of
            Idt: return ztrunc_l_d;
            Jdt: return ztrunc_w_d;
            Kdt, Wdt: return ztrunc_l_d;
            Adt, Hdt, Ldt: return ztrunc_w_d;
            Rdt: return fcvt_s_d;
            otherwise return znop;
        end;

        otherwise return znop;
    end;
end;

function rnd_tab(arg0: Datatype; arg1: Datatype): asmcodes;
begin
    if arg0 = Rdt then begin
        case arg1 of
            Adt, Hdt, Ldt: return zroundu_w_s;            
            Jdt: return zround_w_s;
            Idt: return zround_l_s;
            Kdt, Wdt: return zround_l_s;
            otherwise return znop;
        end;        
    end else if arg0 = Qdt then begin
        case arg1 of
            Adt, Hdt, Ldt: return zroundu_w_d;            
            Jdt: return zround_w_d;
            Idt: return zround_l_d;
            Kdt, Wdt: return zround_l_d;
            otherwise return znop;
        end;
    end else begin
        return znop;
    end;
end;

function invert_livereg(input: cardinal): cardinal;
var
    out: cardinal;
    var_v0: cardinal;
    var_a1: cardinal;
begin
    out := 0;
    var_v0 := 1;
    var_a1 := 16#80000000;

    while input <> 0 do begin
        if (var_a1 & input) <> 0 then begin
            out := out + var_v0;
            input := input - var_a1;
        end;
        var_a1 := rshift(var_a1, 1);
        var_v0 := lshift(var_v0, 1);
    end;
    return out;
end;

procedure eval{(arg0: ^tree; arg1: registers)};
label next_op;
var
    temp_s2: registers;
    sp186: registers;
    var_s3: registers;
    var_s0_2: registers;
    var_s0_13: integer;
    var_s0_3: ^tree;
    var_v0_2: ^tree;
    var_s1_2: ^tree;
    var_s2_2: ^tree;
    var_s1_10: integer;
    var_s2_3: integer;
    temp_s3_4: integer;
    var_s5: asmcodes;
    sp15C: ^tree;
    var_a0_2: itype;
    sp154: integer; { varargs option }
    sp150: cardinal;
    temp_s4: integer;
    temp_s7_2: integer;
    sp147: boolean;
    sp146: boolean;
    sp145: boolean;
    sp144: boolean;
    temp_s7: boolean;
    sp13C: integer; { GPR mask }
    sp138: integer; { FPR mask }
    temp_v0_11: integer;
    sp130: integer;
    sp12C: sp1Ctype;
    sp128: sp1Ctype;
    sp127: Datatype; { return type }
    var_a2_2: integer;
    sp110: binasm;
    temp_mtype: Memtype;
    var_s0: Datatype;
    temp_s1: Datatype;
    temp_s4_2: registers;
    temp_a3: integer;
begin
    if arg0^.reg <> xnoreg then begin
        if arg0^.unk18 <> 0 then begin
            restore_from_temp(arg0);
        end;
        if arg0^.reg in [xfr0..xfr31] then begin
            move_to_end_fp_list(arg0^.reg);
        end else begin
            move_to_end_gp_list(arg0^.reg);
        end;
        return;
    end;
    if arg0^.ref_count >= 2 then begin
        arg1 := xnoreg;
    end;
    while arg0 <> nil do begin
        case arg0^.u.Opc of
        Uloc: begin
            temp_a3 := arg0^.u.I1;
            current_line := temp_a3;
            if first_loc then begin
                first_file_number := arg0^.u.Lexlev;
                sp150 := first_file_number;
                first_line_number := temp_a3;
                first_loc := false;
            end else begin
                if (sp150 <> arg0^.u.Lexlev) and ascii_out then begin
                    sp150 := arg0^.u.Lexlev;
                    emit_file(arg0^.u.Lexlev, false);
                end;
                emit_dir2(iloc, 0, arg0^.u.Lexlev, arg0^.u.I1);
            end;
        end;
        Uoptn: begin
            if arg0^.u.I1 = 1 then begin
                sp154 := arg0^.u.Length;
            end else if arg0^.u.I1 = 2 then begin
                stack_limit_bn := arg0^.u.Length;
            end else if arg0^.u.I1 = 8 then begin
                sp110.symno := 0;
                sp110.instr := ioption;
                sp110.option := o_exception_info;
                sp110.opt_int_value := arg0^.u.Length;
                append_i(sp110);
            end;
        end;
        Uunal: begin
            sp186 := registers(arg0^.u.I1);
            var_s3 := registers(arg0^.u.Lexlev);
            if arg0^.u.Dtype = Adt then begin
                var_a0_2 := ialias;
                if (noalias_regs[var_s3] & lshift(1, ord(sp186))) <> 0 then begin
                    noalias_regs[var_s3] := noalias_regs[var_s3] - lshift(1, ord(sp186));
                    noalias_regs[sp186] := noalias_regs[sp186] - lshift(1, ord(var_s3));
                end;
            end else begin
                var_a0_2 := inoalias;
                noalias_regs[var_s3] := noalias_regs[var_s3] ! lshift(1, ord(sp186));
                noalias_regs[sp186] := noalias_regs[sp186] ! lshift(1, ord(var_s3));
            end;
            emit_alias(var_a0_2, var_s3, sp186);
        end;
        Ubgn: begin
            demit_dir2(iverstamp, 0, arg0^.u.Length, arg0^.u.Offset);
            demit_dir1(ioption, 0, pic_level);
        end;
        Uent: begin
            sp154 := -1; sp130 := -1;
            clear_saved_regs();
            init_regs();
            init_temps();
            reset_pool();
            for var_s0_2 := xr0 to xr31 do begin
                noalias_regs[var_s0_2] := 0;
                noalias_on_off[var_s0_2] := false;
            end;
            pdefs := nil;
            use_real_fp_for_proc := use_real_fp_for_all or use_fp or framesz_relocatable or ((arg0^.u.Extrnal & 2) <> 0);
            if ((arg0^.u.Extrnal & 128) <> 0) and (source_language = 2) then begin
                home_vararg_reg := true;
            end else begin
                home_vararg_reg := false;
            end;
            if (arg0^.u.Extrnal & 16#200) <> 0 then begin
                if reversed_stack then begin
                    sp128.asint := 0;
                end else begin
                    sp128.asint := -1;
                end;
                sp128.unk2 := arg0^.u.Pop;
                sp128.unk3 := arg0^.u.Push;
                sp12C := sp128;
            end else begin
                sp12C.asint := -1;
            end;
            if use_real_fp_for_proc then begin
                frame_pointer := xr13;
                remove_from_free_list(xr13);
            end else begin
                frame_pointer := xr29;
            end;
            if ufsa or ufsm then begin
                for var_s0_2 := fpr_fs0 to registers(ord(fpr_fs0) + ((n_saved_fp_regs - 1) * 2)) do begin
                    ugen_fp_callee_saved := ugen_fp_callee_saved + [var_s0_2];
                end;
            end else begin
                ugen_fp_callee_saved := [];
            end;
            if not generate_again then begin
                saved_regs_size := get_saved_regs_size(arg0);
                frame_size := saved_regs_size;
                save_i_ptrs();
            end;
            local_var_size := 0;
            max_arg_build := 0;
            reloc_arg_build := 0;
            temp_size := 0;
            has_calls := false;
            uses_gp := false;
            num_i_ptr_indexes := 0;
            curlev := integer(arg0^.u.Lexlev);
            entry_point_index := arg0^.u.I1;
            sp147 := (arg0^.u.Offset & 1) <> 0;
            sp146 := (arg0^.u.Offset & 32) <> 0;
            sp145 := (arg0^.u.Offset & 4) <> 0;
            sp144 := (arg0^.u.Offset & 8) <> 0;
            load_stack_limit := false;
            if (arg0^.u.Offset & 16) <> 0 then begin
                load_stack_limit := true;
                stack_limit_bn := 0;
                if not generate_again then begin
                    frame_size := frame_size + 4;
                end;
                saved_regs := saved_regs + [xr23];
            end;
            var_v0_2 := arg0^.next;
            frame_size := (integer((frame_size + 7)) div 8) * 8;
            while var_v0_2^.u.Opc in [Uaent, Ubgn, Ubgnb, Uclab, Ucomm, Udef, Uendb, Uent, Ulex, Uloc, Unop, Uoptn, Updef, Uregs, Usdef, Uunal] do begin
                var_v0_2 := var_v0_2^.next;
            end;
            sp15C := var_v0_2;
            sp127 := arg0^.u.Dtype;
            has_aent := false;
            current_text_sec.Ival := 0;
            if first_ent then begin
                first_ent := false;
                if resident_text then begin
                    demit_dir0(irestext, 0);
                end;
            end;
            if (arg0^.u.Offset & 16#100) <> 0 then begin
                frame_size := 0;
                saved_regs_size := 0;
                clear_saved_regs();
            end;
        end;
        Uaent: begin
            if (arg0^.u.Offset & 128) <> 0 then begin
                home_vararg_reg := true;
            end else begin
                unhome_parms();
            end;
            has_aent := true;
            gen_entry(arg0^.u.I1, arg0^.u.Lexlev, frame_size, local_var_size, temp_size, saved_regs_size);
        end;
        Uend: begin
            check_no_used();
            if not generate_again then begin
                if get_temp_area_size() <> 0 then begin
                    generate_again := true;
                    restore_i_ptrs();
                    temp_size := ((get_temp_area_size() + 7) div 8) * 8;
                    frame_size := frame_size + temp_size;
                    set_temps_offset(-((frame_size - max_arg_build) - saved_regs_size));
                    clean_tree(sp15C);
                    first_loc := true;
                    if debug_ugen then begin
                        writeln("generate_again");
                    end;
                    init_temps();
                    eval(sp15C, xnoreg);
                end;
                generate_again := false;
                if (ibuffer^[i_ptr - 1].instr = iocode) and (ibuffer^[i_ptr - 1].op = zb) then begin 
                    emit_dir1(ialign, 0, 5);
                end;
                output_pool();
                if sp130 = -1 then begin
                    sp13C := 0;
                    sp138 := 0;
                    if has_aent then begin
                        sp13C := 16#20000000;
                        sp138 := 16#F0000000;
                    end else if sp127 <> Pdt then begin
                        case sp127 of
                        Rdt:
                            sp138 := 16#A0000000;
                        Qdt:
                            sp138 := 16#F0000000;
                        Idt,
                        Kdt: begin
                            if basicint = 0 then begin
                                sp13C := 16#30000000;
                            end else begin
                                sp13C := 16#20000000;
                            end;
                        end;
                        otherwise
                            sp13C := 16#20000000;
                        end;
                    end;
                    var_s0_3 := pdefs;
                    while (var_s0_3 <> nil) and (var_s0_3^.u.Offset2 <> -1) do begin
                        if var_s0_3^.u.Lexlev <> 1 then begin
                            var_s3 := parm_reg(var_s0_3);
                            if var_s0_3^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                                sp138 := sp138 ! rshift(cardinal(16#80000000), u8(var_s3) - 32);
                                if var_s0_3^.u.Length = 8 then begin
                                    sp138 := sp138 ! rshift(cardinal(16#80000000), u8(var_s3) - 32 + 1);
                                end;
                            end else begin
                                sp13C := sp13C ! rshift(cardinal(16#80000000), u8(var_s3));
                                if var_s0_3^.u.Length = 8 then begin
                                    sp13C := sp13C ! rshift(cardinal(16#80000000), u8(var_s3) + 1);
                                end;
                            end;
                        end;
                        var_s0_3 := var_s0_3^.next;
                    end;
                    sp13C := sp13C ! 16#0000FF0E;
                    sp138 := sp138 ! 16#00000FFF;
                    emit_regmask(ilivereg, sp13C, sp138);
                end;
                gen_entry_exit(
                    entry_point_index,
                    sp147,
                    curlev, 
                    frame_size,
                    local_var_size,
                    not has_calls,
                    first_file_number,
                    first_line_number,
                    sp145,
                    sp144,
                    load_stack_limit,
                    reloc_arg_build,
                    temp_size,
                    sp146,
                    saved_regs_size,
                    current_text_sec,
                    sp130,
                    sp154,
                    sp12C.asint);
                if sp130 <> -1 then begin
                    emit_a(zj, sp130, 0, franone);
                end;
                emit_dir0(iend, arg0^.u.I1);
            end;
            return;
        end;
        Ussym: begin
            current_text_sec := arg0^.u.Constval;
        end;
        Umsym: begin
            emit_dir0(ialloc, arg0^.u.I1);
        end;
        Udef: begin
            case arg0^.u.Mtype of
            Pmt: begin
                pdefs := arg0^.op1;
                home_parms(sp154);
            end;
            Tmt: begin
                if use_real_fp_for_proc then begin
                    add_to_free_list(frame_pointer);
                    frame_pointer := xr30;
                    saved_regs := saved_regs + [frame_pointer];
                    frame_size := frame_size + 8;
                    saved_regs_size := saved_regs_size + 8;
                end;
                if pic_level > 0 then begin
                    use_cpalias := use_cpalias and (frame_pointer <> xr30);
                    if use_cpalias then begin
                        saved_regs := saved_regs + [xr30];
                    end else begin
                        saved_regs := saved_regs + [xr28];
                    end;
                end;
                max_arg_build := ((arg0^.u.Length + 7) div 8) * 8;
                if not pseudo_leaf then begin
                    saved_regs := saved_regs + [xr31];
                    if not generate_again then begin
                        if framesz_relocatable then begin
                            reloc_arg_build := max_arg_build;
                            max_arg_build := 0;
                        end else begin
                            frame_size := frame_size + max_arg_build;
                        end;
                    end;
                end;
            end;
            Mmt: begin
                local_var_size := ((arg0^.u.Length + 7) div 8) * 8;
                if not generate_again then begin
                    frame_size := frame_size + local_var_size;
                end;
            end;
            otherwise
                report_error(Internal, 3942, "eval.p", "unknown memory type in DEF ucode");
            end;
        end;
        Uregs: begin
            gen_regs(arg0);
        end;
        Uvreg: begin
            if get_domtag() <> 0 then begin
                emit_dir2(imtag, 0, arg0^.u.aryoff, 9);
            end;
            if (arg0^.u.Offset2 <> -1) and (arg0^.ref_count2 <> 0) then begin
                save_vreg(arg0);
                if arg0^.u.Mtype = Pmt then begin
                    load_parm_vreg(arg0);
                end;
                if (glevel <> 0) and (glevel <> 3) and (arg0^.u.Lexlev = 0) then begin
                    var_s3 := registers(arg0^.u.Offset2 div 4);
                    emit_vreg(var_s3, arg0^.u.Offset, arg0^.u.I1);
                end;
            end;
        end;
        Ulab: begin
            check_no_used();
            if arg0^.u.Lexlev <> 1 then begin
                define_label(arg0^.u.I1);
            end;
            if arg0^.u.Length <> 0 then begin
                if has_cia_in_file and ((arg0^.u.Lexlev & 2) <> 0) then begin
                    define_exception_label(arg0^.u.Length);
                end;
                emit_dir0(ilab, arg0^.u.Length);
            end;
            if ((arg0^.u.Lexlev & 1) <> 0) and (pic_level > 0) then begin
                uses_gp := true;
                num_i_ptr_indexes := num_i_ptr_indexes + 1;
                assert(num_i_ptr_indexes <= 20);
                i_ptrs_for_gp_offset[num_i_ptr_indexes] := i_ptr;
                emit_rob(zlw, xr28, 0, xr29, 0);
            end;
        end;
        Ustr: begin
            arg1 := ureg(arg0^.u);
            if arg1 <> xnoreg then begin
                if is_end_return(arg0^.next) and (sp127 in [Idt, Kdt, Wdt]) then begin
                    setting_int64_return := true;
                end;
                if (opcode_arch = ARCH_64) and (basicint = 0) and setting_int64_return and (arg1 = xr2) then begin
                    case arg0^.op1^.u.Opc of
                        Uldc: regs[arg1].dw_link := succ(arg1);
                        Ulod: regs[arg1].dw_link := succ(arg1);
                        otherwise: ;
                    end;
                end;
                eval(arg0^.op1, arg1);
                temp_s2 := reg(arg0^.op1);
                if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (basicint = 0) and ((processing_args and (arg1 in [xr4, xr6])) or (setting_int64_return and (arg1 = xr2))) then begin
                    if opcode_arch = ARCH_32 then begin
                        move_two_regs(arg1, temp_s2);
                    end else if (temp_s2 <> arg1) or (regs[temp_s2].dw_link <> succ(temp_s2)) then begin
                        move_dreg_to_regs(arg1, temp_s2);
                    end;
                end else begin
                    move_to_dest(arg1, temp_s2, arg0^.u.Dtype);
                end;
            end else begin
                if (arg0^.op1^.u.Opc = Ucvt) and ((arg0^.op1^.u.Dtype = Jdt) or ((arg0^.op1^.u.Dtype = Idt) and (opcode_arch = ARCH_64))) and (arg0^.op1^.u.Dtype2 = Qdt) and (arg0^.op1^.ref_count = 1) and (arg0^.u.Length = 4) then begin
                    move_cvt_flag := arg0^.op1^.unk10;
                end;
                eval(arg0^.op1, xnoreg);
                var_s3 := reg(arg0^.op1);
                if not lsb_first and (arg0^.u.Dtype = Sdt) and (arg0^.u.Length < 4) then begin
                    sp186 := get_free_reg(nil, 1);
                    emit_rri_(zsrl, sp186, var_s3, 32 - (arg0^.u.Length * 8), franone);
                    var_s3 := sp186;
                    free_reg(sp186);
                end;
                temp_s7 := ((arg0^.u.Lexlev & 1) <> 0);
                if temp_s7 then begin
                    emit_dir0(iset, 11);
                end;
                if (arg0^.u.Mtype = Pmt) and (arg0^.u.I1 = 0) then begin
                    var_s5 := store_op_tab[arg0^.u.Dtype];
                    if move_cvt_flag = arg0^.op1^.unk10 then begin
                        if arg0^.op1^.u.Dtype = Jdt then begin
                            var_s5 := zswc1;
                        end else begin
                            var_s5 := zsdc1;
                        end;
                    end;
                    if (opcode_arch = ARCH_32) and (var_s5 = zsd) then begin
                        emit_rob(zsw, var_s3, arg0^.u.Offset, xr29, 0);
                        emit_rob(zsw, succ(var_s3), arg0^.u.Offset + 4, xr29, 0);
                    end else begin
                        emit_rob(var_s5, var_s3, arg0^.u.Offset, xr29, 0);
                    end;
                end else begin
                    if move_cvt_flag = arg0^.op1^.unk10 then begin
                        if arg0^.op1^.u.Dtype = Jdt then begin
                            var_s5 := zswc1;
                        end else begin
                            var_s5 := zsdc1;
                        end;
                        loadstore(var_s5, arg0, var_s3, 0);
                    end else begin
                        var_s5 := lsopc(store_table, arg0, var_s3);
                        unaligned_loadstore(var_s5, arg0, var_s3);
                    end;
                end;
                if temp_s7 then begin
                    emit_dir0(iset, 12);
                end;
                move_cvt_flag := -1;
            end;
            if setting_int64_return then begin
                setting_int64_return := false;
                if opcode_arch = ARCH_64 then begin
                    regs[xr2].dw_link := xnoreg;
                end;
            end;
        end;
        Umst: begin
            sp13C := 0;
            sp138 := 0;
            processing_args := true;
            clear_pmov_regs();
            if arg0^.u.I1 <> 0 then begin
                emit_ri_(zsubu, xr29, max_arg_build, franone);
            end;
            var_s2_2 := arg0^.next;
            while (var_s2_2^.u.Opc <> Ucup) and (var_s2_2^.u.Opc <> Urcuf) and (var_s2_2^.u.Opc <> Uicuf) and (var_s2_2^.u.Opc <> Ucia) do begin
                if ((var_s2_2^.u.Opc = Ustr) and (var_s2_2^.u.Mtype = Rmt)) or (var_s2_2^.u.Opc = Urpar) then begin
                    if var_s2_2^.u.Opc = Ustr then begin
                        var_s3 := registers((var_s2_2^.u.Offset) div 4);
                    end else begin
                        var_s3 := registers((var_s2_2^.u.Offset2) div 4);
                    end;
                    if var_s3 in [xfr0..xfr31] then begin
                        sp138 := sp138 ! rshift(cardinal(16#80000000), u8(var_s3) - 32);
                        if var_s2_2^.u.Length = 8 then begin
                            sp138 := sp138 ! rshift(cardinal(16#80000000), u8(var_s3) - 32 + 1);
                        end;
                    end else begin
                        sp13C := sp13C ! rshift(cardinal(16#80000000), u8(var_s3));
                        if var_s2_2^.u.Length = 8 then begin
                            sp13C := sp13C ! rshift(cardinal(16#80000000), u8(var_s3) + 1);
                        end;
                    end;
                end;
                var_s2_2 := var_s2_2^.next;
            end;
        end;
        Umpmv,
        Upmov: begin
            eval_mov(arg0);
            if arg0^.u.Opc = Upmov then begin
                var_s2_3 := abs(arg0^.u.Offset - first_pmt_offset);
                while var_s2_3 < abs(arg0^.u.Offset - first_pmt_offset) + arg0^.u.Length do begin
                    temp_v0_11 := (var_s2_3 div 4) + 4;
                    if temp_v0_11 >= 64 then begin
                        goto next_op;
                    end;
                    var_s0_2 := registers(temp_v0_11);
                    if not is_parm_reg(var_s0_2) then begin
                        goto next_op;
                    end;
                    save_pmov_reg(var_s0_2);
                    if var_s0_2 in [xfr0..xfr31] then begin
                        sp138 := sp138 ! rshift(cardinal(16#80000000), u8(var_s0_2) - 32);
                        if arg0^.u.Length = 8 then begin
                            sp138 := sp138 ! rshift(cardinal(16#80000000), u8(var_s0_2) - 32 + 1);
                        end;
                    end else begin
                        sp13C := sp13C ! rshift(cardinal(16#80000000), u8(var_s0_2));
                    end;
                    var_s2_3 := var_s2_3 + 4;
                end;
            end;
        end;
        Upar: begin
            arg1 := parm_reg(arg0);
            if arg1 <> xnoreg then begin
                if (opcode_arch = ARCH_64) and (basicint = 0) then begin
                    case arg0^.op1^.u.Opc of
                        Uldc: regs[arg1].dw_link := succ(arg1);
                        Ulod: regs[arg1].dw_link := succ(arg1);
                        otherwise: ;
                    end;
                end;
                eval(arg0^.op1, arg1);
                if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (basicint = 0) then begin
                    temp_s2 := reg(arg0^.op1);
                    if opcode_arch = ARCH_32 then begin
                        move_two_regs(arg1, temp_s2);
                    end else if (temp_s2 <> arg1) or (regs[temp_s2].dw_link <> succ(temp_s2)) then begin
                        move_dreg_to_regs(arg1, temp_s2);
                    end;
                end else begin
                    move_to_dest(arg1, reg(arg0^.op1), arg0^.u.Dtype);
                end;
                if arg1 in [xfr0..xfr31] then begin
                    sp138 := sp138 ! rshift(cardinal(16#80000000), u8(integer(arg1)) - 32);
                    if arg0^.u.Length = 8 then begin
                        sp138 := sp138 ! rshift(cardinal(16#80000000), u8(integer(arg1)) - 32 + 1);
                    end;
                end else begin
                    sp13C := sp13C ! rshift(cardinal(16#80000000), u8(arg1));
                    if arg0^.u.Length = 8 then begin
                        sp13C := sp13C ! rshift(cardinal(16#80000000), u8(arg1) + 1);
                    end;
                end;
            end else begin
                eval(arg0^.op1, xnoreg);
                var_s3 := reg(arg0^.op1);
                if var_s3 in [xfr0..xfr31] then begin
                    var_s5 := store_table[ST_f32];
                    if arg0^.u.Length > 4 then begin
                        assert(arg0^.u.Dtype = Qdt);
                        var_s5 := store_table[ST_f64];
                    end;
                end else begin
                    var_s5 := store_table[ST_s32];
                    if arg0^.u.Length > 4 then begin
                        assert((arg0^.u.Dtype in [Idt, Kdt, Wdt]) or (arg0^.u.Dtype = Qdt));
                        var_s5 := store_table[ST_s64];
                    end;
                end;
                if (opcode_arch = ARCH_32) and (var_s5 = zsd) then begin
                    var_s5 := double_to_singles[var_s5];
                    emit_rob(var_s5, var_s3, arg0^.u.Offset, xr29, 0);
                    emit_rob(var_s5, succ(var_s3), arg0^.u.Offset + 4, xr29, 0);
                end else begin
                    emit_rob(var_s5, var_s3, arg0^.u.Offset, xr29, 0);
                end;
            end;
        end;
        Urpar: begin
            if olevel >= 2 then begin
                if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (basicint = 0) and (opcode_arch = ARCH_64) then begin
                    arg1 := parm_reg(arg0);
                    if (arg1 <> xnoreg) and (arg1 in [xr4, xr6]) then begin
                        move_dreg_to_regs(arg1, arg1);
                    end;
                end;
            end;
        end;
        Ucup,
        Urcuf: begin
            check_no_used();
            load_pmov_regs();
            sp13C := sp13C ! 16#0000000E;
            sp138 := sp138 ! 16#00000000;
            if (arg0^.u.Extrnal & 16#100) <> 0 then begin
                sp13C := sp13C ! 16#5FFF0000;
                sp138 := sp138 ! 16#FFFFF000;
            end;
            emit_regmask(ilivereg, sp13C, sp138);
            if arg0^.u.Mtype = Amt then begin
                sp130 := arg0^.u.I1;
            end else if arg0^.u.Opc = Urcuf then begin
                if (arg0^.u.Extrnal & 128 <> 0) then begin
                    emit_a(zj, arg0^.u.I1, 0, franone);
                end else begin
                    emit_a(zjal, arg0^.u.I1, 0, frcprel);
                end;
            end else begin
                if no_jal_use_jalr_only then begin
                    temp_s1 := arg0^.u.Dtype;
                    temp_mtype := arg0^.u.Mtype;
                    arg0^.u.Mtype := Smt;
                    arg0^.u.Dtype := Jdt;

                    temp_s3_4 := arg0^.u.Offset;
                    temp_s4 := arg0^.u.Offset2;
                    arg0^.u.Offset := 0;
                    arg0^.u.Offset2 := 0;

                    loadstore(zla, arg0, xr8, 0);

                    arg0^.u.Offset := temp_s3_4;
                    arg0^.u.Offset2 := temp_s4;
                    arg0^.u.Dtype := temp_s1;
                    arg0^.u.Mtype := temp_mtype;

                    check_no_used();
                    load_pmov_regs();
                    if (arg0^.u.Extrnal & 128) <> 0 then begin
                        emit_r(zj, xr8);
                    end else begin
                        emit_r(zjal, xr8);
                    end;
                end else begin
                    if (arg0^.u.Extrnal & 128) <> 0 then begin
                        emit_a(zj, arg0^.u.I1, 0, franone);
                    end else begin
                        emit_a(zjal, arg0^.u.I1, 0, franone);
                    end;
                end;
            end;
            if opcode_arch = ARCH_64 then begin
                regs[xr4].dw_link := xnoreg;
                regs[xr6].dw_link := xnoreg;
            end;
            processing_args := false;
            if arg0^.u.Dtype in [Idt, Kdt, Wdt] then begin
                processing_int64_return := true;
            end;
        end;
        Uicuf: begin
            sp13C := sp13C ! 16#0000000E;
            sp138 := sp138 ! 16#00000000;
            if pic_level > 0 then begin
                sp13C := sp13C ! rshift(cardinal(16#80000000), ord(xr25));
            end;
            emit_regmask(ilivereg, sp13C, sp138);
            eval(arg0^.op1, xr25);
            var_s3 := reg(arg0^.op1);
            if (pic_level > 0) and (var_s3 <> xr25) then begin
                emit_rr(zmove, xr25, var_s3);
            end;
            check_no_used();
            load_pmov_regs();
            if (arg0^.u.Offset & 128) <> 0 then begin
                emit_r(zj, var_s3);
            end else begin
                emit_r(zjal, var_s3);
            end;
            if (opcode_arch = ARCH_64) and (basicint = 0) then begin
                if regs[xr4].dw_link = succ(xr4) then begin
                    regs[xr4].dw_link := xnoreg;
                end;
                if regs[xr6].dw_link = succ(xr6) then begin
                    regs[xr6].dw_link := xnoreg;
                end;
            end;
            processing_args := false;
            if arg0^.u.Dtype in [Idt, Kdt, Wdt] then begin
                processing_int64_return := true;
            end;
        end;
        Umax,
        Umin: begin
            if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                eval_fp_min_max(arg0, arg1);
                return;
            end;
            if arg0^.op2^.u.Opc <> Uldc then begin
                eval(arg0^.op2, xnoreg);
            end;
            eval(arg0^.op1, xnoreg);
            if arg0^.op2^.u.Opc <> Uldc then begin
                sp186 := reg(arg0^.op2);
            end;
            var_s3 := reg(arg0^.op1);
            if arg1 = xnoreg then begin
                if (usage_count(var_s3) = 0) and is_available(var_s3) then begin
                    arg1 := var_s3;
                    get_reg(var_s3, arg0, arg0^.ref_count);
                end else if (arg0^.op2^.u.Opc <> Uldc) and (usage_count(sp186) = 0) and is_available(sp186) then begin
                    temp_s4_2 := var_s3;
                    var_s3 := sp186;
                    sp186 := temp_s4_2;
                    arg1 := var_s3;
                    get_reg(var_s3, arg0, arg0^.ref_count);
                end else begin
                    arg1 := get_free_reg(arg0, arg0^.ref_count);
                end;
            end else begin
                get_reg(arg1, arg0, arg0^.ref_count);
            end;
            arg0^.reg := arg1;
            if (arg1 = sp186) and (arg0^.op2^.u.Opc <> Uldc) then begin
                sp186 := var_s3;
            end else if arg1 <> var_s3 then begin
                emit_rr(zmove, arg1, var_s3);
                if opcode_arch = ARCH_32 then begin
                    if arg0^.u.Dtype in [Idt, Kdt, Wdt] then begin
                        emit_rr(zmove, succ(arg1), succ(var_s3));
                    end;
                end;
            end;
            var_s5 := uop_to_asm(arg0);
            temp_s7_2 := gen_label_id();
            if arg0^.op2^.u.Opc = Uldc then begin
                if arg0^.u.Dtype in [Idt, Kdt, Wdt] then begin
                    emit_branch_rill(var_s5, arg1, arg0^.op2^.u.Constval.dwval_h, arg0^.op2^.u.Constval.dwval_l, temp_s7_2, arg0);
                    if opcode_arch = ARCH_32 then begin
                        emit_ri_(zli, arg1, arg0^.op2^.u.Constval.dwval_h, franone);
                        emit_ri_(zli, succ(arg1), arg0^.op2^.u.Constval.dwval_l, franone);
                    end else begin
                        emit_rii(zdli, arg1, arg0^.op2^.u.Constval);
                    end;
                end else begin
                    emit_rill(var_s5, arg1, arg0^.op2^.u.Constval.Ival, temp_s7_2);
                    emit_ri_(zli, arg1, arg0^.op2^.u.Constval.Ival, franone);
                end;
            end else begin
                emit_branch_rrll(var_s5, arg1, sp186, temp_s7_2, arg0);
                emit_rr(zmove, arg1, sp186);
                if opcode_arch = ARCH_32 then begin
                    if arg0^.u.Dtype in [Idt, Kdt, Wdt] then begin
                        emit_rr(zmove, succ(arg1), succ(sp186));
                    end;
                end;
            end;
            define_label(temp_s7_2);
        end;
        Utjp: begin
            jump(arg0^.op1, false, arg0^.op2^.u.I1);
        end;
        Ufjp: begin
            jump(arg0^.op1, true, arg0^.op2^.u.I1);
        end;
        Uujp: begin
            if is_end_return(arg0) and (frame_size = 0) and not load_stack_limit and is_empty_saved_regs() and (frame_pointer = xr29) then begin
                if sp127 <> Pdt then begin
                    if sp127 in [Qdt, Rdt, Xdt] then begin
                        sp13C := 0;
                        sp138 := 16#C0000000;
                    end else begin
                        sp138 := 0;
                        if (basicint = 0) and (sp127 in [Idt, Kdt, Wdt]) then begin
                            sp13C := 16#30000000;
                        end else begin
                            sp13C := 16#20000000;
                        end;
                    end;
                end else begin
                    sp13C := 0;
                    sp138 := 0;
                end;
                var_s0_3 := pdefs;
                while (var_s0_3 <> nil) and (var_s0_3^.u.Offset2 <> -1) do begin
                    if var_s0_3^.u.Lexlev <> 1 then begin
                        var_s3 := parm_reg(var_s0_3);
                        if var_s0_3^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                            sp138 := sp138 ! rshift(cardinal(16#80000000), u8(var_s3) - 32);
                            if var_s0_3^.u.Length = 8 then begin
                                sp138 := sp138 ! rshift(cardinal(16#80000000), u8(var_s3) - 32 + 1);
                            end;
                        end else begin
                            sp13C := sp13C ! rshift(cardinal(16#80000000), u8(var_s3));
                            if var_s0_3^.u.Length = 8 then begin
                                sp13C := sp13C ! rshift(cardinal(16#80000000), u8(var_s3) + 1);
                            end;
                        end;
                    end;
                    var_s0_3 := var_s0_3^.next;
                end;
                sp13C := sp13C ! 16#0000FF0E;
                sp138 := sp138 ! 16#00000FFF;
                emit_regmask(ilivereg, sp13C, sp138);
                emit_r(zj, xr31);
            end else begin
                emit_ll(zb, arg0^.op2^.u.I1);
            end;
        end;
        Uijp: begin
            eval(arg0^.op1, xnoreg);
            emit_r(zj, reg(arg0^.op1));
        end;
        Ucg2: begin
            arg1 := get_dest(arg0, arg1);
            emit_rll(zla, arg1, arg0^.op1^.u.I1);
        end;
        Uldc: begin
            if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                load_fp_literal(arg0, arg1);
            end else if (arg0^.u.Dtype = Sdt) and (arg0^.u.Length > 4) then begin
                var_s0_13 := add_to_pool(arg0^.u, gen_label_id());
                arg1 := get_dest(arg0, arg1);
                emit_rll(zla, arg1, var_s0_13);
            end else if is_zero(arg0) then begin
                if (opcode_arch = ARCH_32) and (arg0^.u.Dtype in [Idt, Kdt, Wdt]) then begin
                    arg1 := get_dest(arg0, arg1);
                    emit_ri_(zli, arg1, 0, franone);
                    emit_ri_(zli, succ(arg1), 0, franone);
                end else begin
                    arg1 := xr0;
                    arg0^.reg := xr0;
                    inc_usage(xr0, arg0^.ref_count);
                end;
            end else begin
                arg1 := get_dest(arg0, arg1);
                if arg0^.u.Dtype in [Idt, Kdt, Wdt] then begin
                    if (opcode_arch = ARCH_32) or (regs[arg1].dw_link = succ(arg1)) then begin
                        emit_ri_(zli, arg1, arg0^.u.Constval.dwval_h, franone);
                        emit_ri_(zli, succ(arg1), arg0^.u.Constval.dwval_l, franone);
                    end else begin
                        emit_rii(zdli, arg1, arg0^.u.Constval);
                    end;
                end else begin
                    emit_ri_(zli, arg1, arg0^.u.Constval.Ival, franone);
                end;
            end;
        end;
        Uldrc: begin
            assert(not (arg0^.u.Dtype in [Idt, Kdt, Wdt]));
            if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                arg1 := get_dest(arg0, arg1);
                emit_rrfi(fasm(fli_s, arg0^.u.Dtype), arg1, arg0^.u.I1);
            end else begin
                arg1 := get_dest(arg0, arg1);
                emit_rrfi(zli, arg1, arg0^.u.I1);
            end;
        end;
        Ulod: begin
            var_s3 := ureg(arg0^.u);
            if var_s3 <> xnoreg then begin
                if var_s3 in [xfr0..xfr31] then begin
                    get_fp_reg1(var_s3, arg0, reg_kind_tab[arg0^.u.Dtype], arg0^.ref_count);
                end else begin
                    get_reg1(var_s3, arg0, arg0^.ref_count);
                    if processing_int64_return and (var_s3 = xr2) then begin
                        processing_int64_return := false;
                        if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (opcode_arch = ARCH_64) and (basicint = 0) then begin
                            emit_rri_(zdsll, var_s3, var_s3, 32, franone);
                            emit_rri_(zdsll, succ(var_s3), succ(var_s3), 32, franone);
                            if lsb_first then begin
                                emit_rri_(zdsrl, var_s3, var_s3, 32, franone);
                            end else begin
                                emit_rri_(zdsrl, succ(var_s3), succ(var_s3), 32, franone);
                            end;
                            emit_rrr(zor, var_s3, var_s3, succ(var_s3));
                        end;
                    end;
                end;
                arg0^.reg := var_s3;
            end else begin
                arg1 := get_dest(arg0, arg1);
                temp_s7 := ((arg0^.u.Lexlev & 1) <> 0);
                if temp_s7 then begin
                    emit_dir0(iset, 11);
                end;
                var_s5 := lsopc(load_table, arg0, arg1);
                unaligned_loadstore(var_s5, arg0, arg1);
                if not lsb_first and (arg0^.u.Dtype = Sdt) and (arg0^.u.Length < 4) then begin
                    emit_ri_(zsll, arg1, 32 - (arg0^.u.Length * 8), franone);
                end;
                if temp_s7 then begin
                    emit_dir0(iset, 12);
                end;
            end;
        end;
        Uilod,
        Uisld: begin
            var_s2_2 := arg0^.op1;
            temp_s7 := ((arg0^.u.Lexlev & 1) <> 0);
            if (var_s2_2^.ref_count = 1) and (pic_level = 0) and (var_s2_2^.u.Opc = Uadd) and (var_s2_2^.op2^.ref_count = 1) and (var_s2_2^.op2^.u.Opc = Ulda) and (var_s2_2^.op2^.u.Mtype in [Mmt, Pmt, Smt]) and (get_sym_kind(var_s2_2^.op2^.u.I1) <> 5) then begin
                if var_s2_2^.op2^.u.Mtype = Smt then begin
                    eval(var_s2_2^.op1, xnoreg);
                    var_s3 := reg(var_s2_2^.op1);
                    arg1 := get_dest(arg0, arg1);
                    if temp_s7 then begin
                        emit_dir0(iset, 11);
                    end;
                    var_s5 := lsopc(load_table, arg0, arg1);
                    iloadistore(arg0, var_s5, arg1, arg0^.u.Offset + var_s2_2^.op2^.u.Offset, var_s2_2^.op2^.u.I1, var_s3);
                    if temp_s7 then begin
                        emit_dir0(iset, 12);
                    end;
                end else begin
                    eval(var_s2_2^.op1, xnoreg);
                    var_s3 := reg(var_s2_2^.op1);
                    arg1 := get_dest(arg0, arg1);
                    if (arg0^.u.Dtype in [Qdt, Rdt, Xdt]) or (arg0^.u.Dtype in [Idt, Kdt, Wdt]) then begin
                        sp186 := get_free_reg(nil, 1);
                        free_reg(sp186);
                    end else begin
                        sp186 := arg1;
                    end;
                    if temp_s7 then begin
                        emit_dir0(iset, 11);
                    end;
                    emit_rrr(zaddu, sp186, frame_pointer, var_s3);
                    var_s5 := lsopc(load_table, arg0, arg1);
                    iloadistore(arg0, var_s5, arg1, arg0^.u.Offset + frame_offset(var_s2_2^.op2), 0, sp186);
                    if temp_s7 then begin
                        emit_dir0(iset, 12);
                    end;
                end;
            end else begin
                eval(arg0^.op1, xnoreg);
                var_s3 := reg(arg0^.op1);
                arg1 := get_dest(arg0, arg1);
                if temp_s7 then begin
                    emit_dir0(iset, 11);
                end;
                if (arg0^.u.Opc = Uilod) and (var_s2_2^.u.Opc = Uadd) then begin
                    var_s1_2 := var_s2_2^.op1;
                    if var_s1_2^.u.Opc = Umpy then begin
                        var_s1_2 := var_s1_2^.op1;
                    end;
                    if var_s1_2^.u.Opc = Ulod then begin
                        for var_s0_2 := xr1 to xr31 do begin
                            if ((noalias_regs[var_s0_2] & lshift(1, ord(var_s1_2^.reg))) <> 0) and ((noalias_regs[var_s3] & noalias_regs[var_s0_2]) = 0) then begin
                                noalias_on_off[var_s0_2] := true;
                                emit_alias(inoalias, var_s3, var_s0_2);
                            end;
                        end;
                    end;
                end;
                var_s5 := lsopc(load_table, arg0, arg1);
                iloadistore(arg0, var_s5, arg1, arg0^.u.Offset, 0, var_s3);
                for var_s0_2 := xr1 to xr31 do begin
                    if noalias_on_off[var_s0_2] then begin
                        noalias_on_off[var_s0_2] := false;
                        emit_alias(ialias, var_s3, var_s0_2);
                    end;
                end;
                if temp_s7 then begin
                    emit_dir0(iset, 12);
                end;
            end;
            if not lsb_first and (arg0^.u.Dtype = Sdt) and (arg0^.u.Length < 4) then begin
                emit_ri_(zsll, arg1, 32 - (arg0^.u.Length * 8), franone);
            end;
        end;
        Uirld: begin
            temp_s7 := ((arg0^.u.Lexlev & 1) <> 0);
            var_s2_2 := arg0^.op1;
            eval(arg0^.op1, xnoreg);
            var_s3 := reg(arg0^.op1);
            arg1 := get_dest(arg0, arg1);
            if temp_s7 then begin
                emit_dir0(iset, 11);
            end;
            if var_s2_2^.u.Opc = Uadd then begin
                var_s1_2 := var_s2_2^.op1;
                if var_s1_2^.u.Opc = Umpy then begin
                    var_s1_2 := var_s1_2^.op1;
                end;
                if var_s1_2^.u.Opc = Ulod then begin
                    for var_s0_2 := xr1 to xr31 do begin
                        if ((noalias_regs[var_s0_2] & lshift(1, ord(var_s1_2^.reg))) <> 0) and ((noalias_regs[var_s3] & noalias_regs[var_s0_2]) = 0) then begin
                            noalias_on_off[var_s0_2] := true;
                            emit_alias(inoalias, var_s3, var_s0_2);
                        end;
                    end;
                end;
            end;
            var_s5 := lsopc(load_table, arg0, arg1);
            rloadrstore(arg0, var_s5, arg1, arg0^.u.I1, var_s3);
            for var_s0_2 := xr1 to xr31 do begin
                if noalias_on_off[var_s0_2] then begin
                    noalias_on_off[var_s0_2] := false;
                    emit_alias(ialias, var_s3, var_s0_2);
                end;
            end;
            if temp_s7 then begin
                emit_dir0(iset, 12);
            end;
            if not lsb_first and (arg0^.u.Dtype = Sdt) and (arg0^.u.Length < 4) then begin
                emit_ri_(zsll, arg1, 32 - (arg0^.u.Length * 8), franone);
            end;
        end;
        Uisst,
        Uistr: begin
            if (arg0^.op2^.u.Opc = Ucvt) and ((arg0^.op2^.u.Dtype = Jdt) or ((arg0^.op2^.u.Dtype = Idt) and (opcode_arch = ARCH_64))) and (arg0^.op2^.u.Dtype2 = Qdt) and (arg0^.op2^.ref_count = 1) and (arg0^.u.Length = 4) then begin
                move_cvt_flag := arg0^.op2^.unk10;
            end;
            eval(arg0^.op2, xnoreg);
            var_s2_2 := arg0^.op1;
            temp_s7 := ((arg0^.u.Lexlev & 1) <> 0);
            if (var_s2_2^.ref_count = 1) and (pic_level = 0) and (var_s2_2^.u.Opc = Uadd) and (var_s2_2^.op2^.ref_count = 1) and (var_s2_2^.op2^.u.Opc = Ulda) and (var_s2_2^.op2^.u.Mtype in [Mmt, Pmt, Smt]) and (get_sym_kind(var_s2_2^.op2^.u.I1) <> 5) then begin
                if var_s2_2^.op2^.u.Mtype = Smt then begin
                    eval(var_s2_2^.op1, xnoreg);
                    sp186 := reg(arg0^.op2);
                    if not lsb_first and (arg0^.u.Dtype = Sdt) and (arg0^.u.Length < 4) then begin
                        temp_s4_2 := get_free_reg(nil, 1);
                        emit_rri_(zsrl, temp_s4_2, sp186, 32 - (arg0^.u.Length * 8), franone);
                        sp186 := temp_s4_2;
                        free_reg(temp_s4_2);
                    end;
                    var_s3 := reg(var_s2_2^.op1);
                    if temp_s7 then begin
                        emit_dir0(iset, 11);
                    end;
                    if move_cvt_flag = arg0^.op2^.unk10 then begin
                        if arg0^.op2^.u.Dtype = Jdt then begin
                            var_s5 := zswc1;
                        end else begin
                            var_s5 := zsdc1;
                        end;
                    end else begin
                        var_s5 := lsopc(store_table, arg0, sp186);
                    end;
                    iloadistore(arg0, var_s5, sp186, arg0^.u.Offset + var_s2_2^.op2^.u.Offset, var_s2_2^.op2^.u.I1, var_s3);
                    if temp_s7 then begin
                        emit_dir0(iset, 12);
                    end;
                end else begin
                    eval(var_s2_2^.op1, xnoreg);
                    sp186 := reg(arg0^.op2);
                    if not lsb_first and ((arg0^.u.Dtype) = Sdt) and (arg0^.u.Length < 4) then begin
                        temp_s4_2 := get_free_reg(nil, 1);
                        emit_rri_(zsrl, temp_s4_2, sp186, 32 - (arg0^.u.Length * 8), franone);
                        sp186 := temp_s4_2;
                        free_reg(temp_s4_2);
                    end;
                    var_s3 := reg(var_s2_2^.op1);
                    temp_s4_2 := get_free_reg(nil, 1);
                    free_reg(temp_s4_2);
                    if temp_s7 then begin
                        emit_dir0(iset, 11);
                    end;
                    emit_rrr(zaddu, temp_s4_2, frame_pointer, var_s3);
                    if move_cvt_flag = arg0^.op2^.unk10 then begin
                        if arg0^.op2^.u.Dtype = Jdt then begin
                            var_s5 := zswc1;
                        end else begin
                            var_s5 := zsdc1;
                        end;
                    end else begin
                        var_s5 := lsopc(store_table, arg0, sp186);
                    end;
                    iloadistore(arg0, var_s5, sp186, arg0^.u.Offset + frame_offset(var_s2_2^.op2), 0, temp_s4_2);
                    if temp_s7 then begin
                        emit_dir0(iset, 12);
                    end;
                end;
            end else begin
                eval(arg0^.op1, xnoreg);
                sp186 := reg(arg0^.op2);
                if not lsb_first and ((arg0^.u.Dtype) = Sdt) and (arg0^.u.Length < 4) then begin
                    temp_s4_2 := get_free_reg(nil, 1);
                    emit_rri_(zsrl, temp_s4_2, sp186, 32 - (arg0^.u.Length * 8), franone);
                    sp186 := temp_s4_2;
                    free_reg(temp_s4_2);
                end;
                var_s3 := reg(arg0^.op1);
                if temp_s7 then begin
                    emit_dir0(iset, 11);
                end;
                if (arg0^.u.Opc = Uistr) and (var_s2_2^.u.Opc = Uadd) then begin
                    var_s1_2 := var_s2_2^.op1;
                    if var_s1_2^.u.Opc = Umpy then begin
                        var_s1_2 := var_s1_2^.op1;
                    end;
                    if var_s1_2^.u.Opc = Ulod then begin
                        for var_s0_2 := xr1 to xr31 do begin
                        if ((noalias_regs[var_s0_2] & lshift(1, ord(var_s1_2^.reg))) <> 0) and ((noalias_regs[var_s3] & noalias_regs[var_s0_2]) = 0) then begin
                                noalias_on_off[var_s0_2] := true;
                                emit_alias(inoalias, var_s3, var_s0_2);
                            end;
                        end;
                    end;
                end;
                if move_cvt_flag = arg0^.op2^.unk10 then begin
                    if arg0^.op2^.u.Dtype = Jdt then begin
                        var_s5 := zswc1;
                    end else begin
                        var_s5 := zsdc1;
                    end;
                end else begin
                    var_s5 := lsopc(store_table, arg0, sp186);
                end;
                iloadistore(arg0, var_s5, sp186, arg0^.u.Offset, 0, var_s3);
                for var_s0_2 := xr1 to xr31 do begin
                    if noalias_on_off[var_s0_2] then begin
                        noalias_on_off[var_s0_2] := false;
                        emit_alias(ialias, var_s3, var_s0_2);
                    end;
                end;
                if temp_s7 then begin
                    emit_dir0(iset, 12);
                end;
            end;
            move_cvt_flag := -1;
        end;
        Uirst: begin
            if (arg0^.op2^.u.Opc = Ucvt) and ((arg0^.op2^.u.Dtype = Jdt) or (arg0^.op2^.u.Dtype = idt) and (opcode_arch = ARCH_64)) and (arg0^.op2^.u.Dtype2 = Qdt) and (arg0^.op2^.ref_count = 1) and (arg0^.u.Length = 4) then begin
                move_cvt_flag := arg0^.op2^.unk10;
            end;
            eval(arg0^.op2, xnoreg);
            temp_s7 := ((arg0^.u.Lexlev & 1) <> 0);
            var_s2_2 := arg0^.op1;
            eval(arg0^.op1, xnoreg);
            sp186 := reg(arg0^.op2);
            if not lsb_first and (arg0^.u.Dtype = Sdt) and (arg0^.u.Length < 4) then begin
                temp_s4_2 := get_free_reg(nil, 1);
                emit_rri_(zsrl, temp_s4_2, sp186, 32 - (arg0^.u.Length * 8), franone);
                sp186 := temp_s4_2;
                free_reg(temp_s4_2);
            end;
            var_s3 := reg(arg0^.op1);
            if temp_s7 then begin
                emit_dir0(iset, 11);
            end;
            if var_s2_2^.u.Opc = Uadd then begin
                var_s1_2 := var_s2_2^.op1;
                if var_s1_2^.u.Opc = Umpy then begin
                    var_s1_2 := var_s1_2^.op1;
                end;
                if var_s1_2^.u.Opc = Ulod then begin
                    for var_s0_2 := xr1 to xr31 do begin
                        if ((noalias_regs[var_s0_2] & lshift(1, ord(var_s1_2^.reg))) <> 0) and ((noalias_regs[var_s3] & noalias_regs[var_s0_2]) = 0) then begin
                            noalias_on_off[var_s0_2] := true;
                            emit_alias(inoalias, var_s3, var_s0_2);
                        end;
                    end
                end;
            end;
            if move_cvt_flag = arg0^.op2^.unk10 then begin
                if arg0^.op2^.u.Dtype = Jdt then begin
                    var_s5 := zswc1;
                end else begin
                    var_s5 := zsdc1;
                end;
            end else begin
                var_s5 := lsopc(store_table, arg0, sp186);
            end;
            rloadrstore(arg0, var_s5, sp186, arg0^.u.I1, var_s3);
            for var_s0_2 := xr1 to xr31 do begin
                if noalias_on_off[var_s0_2] then begin
                    noalias_on_off[var_s0_2] := false;
                    emit_alias(ialias, var_s3, var_s0_2);
                end;
            end;
            if temp_s7 then begin
                emit_dir0(iset, 12);
            end;
            move_cvt_flag := -1;
        end;
        Ulda: begin
            arg1 := get_dest(arg0, arg1);
            case arg0^.u.Mtype of
            Mmt,
            Pmt:
                if get_sym_kind(arg0^.u.I1) = 5 then begin
                    if basicint = 1 then begin
                        emit_rrri(zdsubu, arg1, frame_pointer, arg0^.u.I1);
                        if arg0^.u.Offset <> 0 then begin
                            emit_rri_(zdaddu, arg1, arg1, arg0^.u.Offset, franone);
                        end;
                    end else begin
                        emit_rrri(zsubu, arg1, frame_pointer, arg0^.u.I1);
                        if arg0^.u.Offset <> 0 then begin
                            emit_rri_(zaddu, arg1, arg1, arg0^.u.Offset, franone);
                        end;
                    end;
                end else if (arg0^.u.Mtype = Pmt) and framesz_relocatable then begin
                    if basicint = 1 then begin
                        emit_rri_(zdaddu, arg1, frame_pointer, frame_offset(arg0), franone);
                    end else begin
                        emit_rri_(zaddu, arg1, frame_pointer, frame_offset(arg0), franone);
                    end;
                end else begin
                    if basicint = 1 then begin
                        emit_rri_(zdaddu, arg1, frame_pointer, frame_offset(arg0), franone);
                    end else begin
                        emit_rri_(zaddu, arg1, frame_pointer, frame_offset(arg0), franone);
                    end;
                end;
            Smt:
                if basicint = 1 then begin
                    emit_ra(zdla, arg1, arg0^.u.I1, arg0^.u.Offset, 0);
                end else begin
                    emit_ra(zla, arg1, arg0^.u.I1, arg0^.u.Offset, 0);
                end;
            otherwise
                report_error(Internal, 5211, "eval.p", "Unknown memory type in LDA");
            end;
        end;
        Ulca: begin
            var_s0_13 := add_to_pool(arg0^.u, gen_label_id());
            arg1 := get_dest(arg0, arg1);
            emit_rll(zla, arg1, var_s0_13);
        end;
        Ulnot: begin
            var_s5 := uop_to_asm(arg0);
            eval(arg0^.op1, arg1);
            var_s3 := reg(arg0^.op1);
            arg1 := get_dest(arg0, arg1);
            emit_rri_(var_s5, arg1, var_s3, 0, franone);
        end;
        Unot: begin
            var_s5 := uop_to_asm(arg0);
            if (arg0^.op1^.u.Opc = Uior) and (opt_cse = 2) and (arg0^.op1^.ref_count = 1) then begin
                nor_flag := true;
                arg0^.op1^.ref_count := arg0^.ref_count;
                eval(arg0^.op1, arg1);
                arg0^.reg := arg0^.op1^.reg;
                fill_reg(arg0^.reg, arg0, arg0^.ref_count, regs[arg0^.reg].reg_kind);
                arg0^.op1^.ref_count := 1;
            end else begin
                eval(arg0^.op1, arg1);
                var_s3 := reg(arg0^.op1);
                arg1 := get_dest(arg0, arg1);
                dw_emit_rr(var_s5, arg1, var_s3, arg0);
            end;
        end;
        Uabs,
        Uneg: begin
            var_s0 := arg0^.u.Dtype;
            var_s5 := uop_to_asm(arg0);
            if var_s0 in [Qdt, Rdt, Xdt] then begin
                if not (arg1 in [xfr0..xfr31]) then begin
                    arg1 := xnoreg;
                end;
            end;
            eval(arg0^.op1, arg1);
            var_s3 := reg(arg0^.op1);
            arg1 := get_dest(arg0, arg1);
            if ((arg0^.u.Dtype = Jdt) or (arg0^.u.Dtype = Ldt)) and (arg0^.u.Opc = Uabs) then begin
                move_to_dest(arg1, var_s3, arg0^.u.Dtype);
                temp_s7_2 := gen_label_id();
                emit_rll(zbgez, var_s3, temp_s7_2);
                emit_rrr(zsubu, arg1, xr0, var_s3);
                define_label(temp_s7_2);
            end else begin
                dw_emit_rr(var_s5, arg1, var_s3, arg0);
            end;
        end;
        Uadd,
        Uand,
        Udiv,
        Uequ,
        Ugeq,
        Ugrt,
        Uior,
        Uleq,
        Ules,
        Umpy,
        Uneq,
        Urem,
        Ushl,
        Ushr,
        Usub,
        Uxor: begin
            var_s0 := arg0^.u.Dtype;
            if var_s0 in [Qdt, Rdt, Xdt] then begin
                if arg0^.u.Opc in [Uequ, Ugeq, Ugrt, Uleq, Ules, Uneq] then begin
                    eval_fp_cond(arg0, arg1);
                end else begin
                    eval2(fop(arg0^.u.Opc, var_s0), arg0, arg1);
                end;
            end else begin
                var_s5 := uop_to_asm(arg0);
                if (arg0^.u.Opc = Uior) and nor_flag then begin
                    nor_flag := false;
                    var_s5 := op_nor;
                end;
                if is_constant(arg0^.op2) then begin
                    if (opcode_arch = ARCH_32) and (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (var_s0 <> result_type(arg0)) then begin
                        eval(arg0^.op1, xnoreg);
                    end else begin
                        eval(arg0^.op1, arg1);
                    end;
                    var_s3 := reg(arg0^.op1);
                    arg1 := get_dest(arg0, arg1);
                    if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (arg1 = var_s3) and not (arg0^.u.Opc in [Uadd, Usub]) then begin
                        temp_s2 := get_free_reg(arg0, 1);
                    end else begin
                        temp_s2 := arg1;
                    end;
                    var_s0_3 := arg0^.op2;
                    if var_s0_3^.u.Dtype in [Idt, Kdt, Wdt] then begin
                        var_s1_10 := var_s0_3^.u.Constval.dwval_l;
                        if (arg0^.u.Opc = Ushl) or (arg0^.u.Opc = Ushr) then begin
                            var_s1_10 := var_s1_10 & 63;
                        end;
                    end else begin
                        var_s1_10 := var_s0_3^.u.Constval.Ival;
                        if (arg0^.u.Opc = Ushl) or (arg0^.u.Opc = Ushr) then begin
                            var_s1_10 := var_s1_10 & 31;
                        end;
                    end;
                    if var_s0_3^.u.Dtype in [Idt, Kdt, Wdt] then begin
                        dw_emit_rri(var_s5, temp_s2, var_s3, var_s0_3^.u.Constval.Ival, var_s1_10, arg0);
                    end else if var_s1_10 < 0 then begin
                        dw_emit_rri(var_s5, temp_s2, var_s3, -1, var_s1_10, arg0);
                    end else begin
                        dw_emit_rri(var_s5, temp_s2, var_s3, 0, var_s1_10, arg0);
                    end;
                    if temp_s2 <> arg1 then begin
                        if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (opcode_arch = ARCH_32) then begin
                            move_two_regs(arg1, temp_s2);
                        end else begin
                            emit_rr(zmove, arg1, temp_s2);
                        end;
                        free_reg(temp_s2);
                    end;
                end else if arg0^.op2^.u.Opc = Uldrc then begin
                    eval(arg0^.op1, arg1);
                    var_s3 := reg(arg0^.op1);
                    arg1 := get_dest(arg0, arg1);
                    var_s1_10 := arg0^.op2^.u.I1;
                    if (arg0^.u.Opc = Uand) and (arg0^.op1^.u.Opc = Uilod) and (arg0^.op1^.u.Length = 1) then begin
                        var_s5 := zandi;
                    end;
                    emit_rrri(var_s5, arg1, var_s3, var_s1_10);
                end else begin
                    eval2(var_s5, arg0, arg1);
                end;
            end;
        end;
        Umod: begin
            var_s5 := uop_to_asm(arg0);
            temp_s7_2 := gen_label_id();
            eval(arg0^.op1, xnoreg);
            if arg0^.op2^.u.Opc = Uldc then begin
                var_s3 := reg(arg0^.op1);
                arg1 := get_dest(arg0, arg1);
                emit_rri_(var_s5, arg1, var_s3, arg0^.op2^.u.Constval.Ival, franone);
                if arg0^.op2^.u.Constval.Ival >= 0 then begin
                    emit_rill(zbge, arg1, 0, temp_s7_2);
                end else begin
                    emit_rill(zble, arg1, 0, temp_s7_2);
                end;
                emit_rri_(zadd, arg1, arg1, arg0^.op2^.u.Constval.Ival, franone);
            end else begin
                eval(arg0^.op2, xnoreg);
                var_s3 := reg(arg0^.op1);
                arg1 := get_dest(arg0, arg1);
                sp186 := reg(arg0^.op2);
                temp_s4_2 := get_free_reg(nil, 1);
                free_reg(temp_s4_2);
                assert(sp186 <> arg1);
                emit_rrr(var_s5, arg1, var_s3, sp186);
                emit_rrr(zxor, temp_s4_2, arg1, sp186);
                emit_rill(zbge, temp_s4_2, 0, temp_s7_2);
                emit_rrr(zaddu, arg1, arg1, sp186);
            end;
            define_label(temp_s7_2);
        end;
        Ucvtl: begin
            assert((arg0^.u.Lexlev & 2) <> 0);
            eval(arg0^.op1, xnoreg);
            if arg1 = arg0^.op1^.reg then begin
                arg1 := xnoreg;
            end;
            arg1 := get_dest(arg0, arg1);
            var_s3 := reg(arg0^.op1);
            if arg0^.u.Dtype in [Idt, Kdt, Wdt] then begin
                if opcode_arch = ARCH_64 then begin
                    emit_rri_(zdsll, arg1, var_s3, 64 - arg0^.u.I1, franone);
                    var_s5 := zdsrl;
                    if arg0^.u.Dtype = Idt then begin
                        var_s5 := zdsra;
                    end;
                    emit_rri_(var_s5, arg1, arg1, 64 - arg0^.u.I1, franone);
                end;
            end else begin
                emit_rri_(zsll, arg1, var_s3, 32 - arg0^.u.I1, franone);
                var_s5 := zsrl;
                if arg0^.u.Dtype = Jdt then begin
                    var_s5 := zsra;
                end;
                emit_rri_(var_s5, arg1, arg1, 32 - arg0^.u.I1, franone);
            end;
            emit_rri_(ztne, arg1, var_s3, 6, franone);
        end;
        Ucvt: begin
            if not (arg0^.u.Dtype in [Adt, Hdt, Idt, Jdt, Kdt, Ldt, Qdt, Rdt, Wdt, Xdt]) or not (arg0^.u.Dtype2 in [Adt, Hdt, Idt, Jdt, Kdt, Ldt, Qdt, Rdt, Wdt, Xdt]) then begin
                report_error(Internal, 5531, "eval.p", "illegal type conversions");
                return;
            end;
            if arg0^.u.Dtype2 in [Qdt, Rdt, Xdt] then begin
                if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                    eval_flt_flt_cvt(arg0, arg1);
                end else begin
                    eval_flt_int_cvt(arg0, arg1);
                end;
            end else begin
                if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                    eval_int_flt_cvt(arg0, arg1);
                end else begin
                    eval_int_int_cvt(arg0, arg1);
                end;
            end;
        end;
        Utyp: begin
            if (not (arg0^.u.Dtype in [Adt, Fdt, Gdt, Hdt, Idt, Jdt, Kdt, Ldt, Ndt, Wdt]) and (arg0^.u.Dtype <> Rdt)) or (not (arg0^.u.Dtype2 in [Adt, Fdt, Gdt, Hdt, Idt, Jdt, Kdt, Ldt, Ndt, Wdt]) and (arg0^.u.Dtype2 <> Rdt)) then begin
                report_error(Internal, 5558, "eval.p", "illegal type retyping");
                return;
            end;
            eval(arg0^.op1, xnoreg);
            var_s3 := reg(arg0^.op1);
            if arg0^.u.Dtype2 in [Adt, Fdt, Gdt, Hdt, Idt, Jdt, Kdt, Ldt, Ndt, Wdt] then begin
                if (arg0^.u.Dtype) = Rdt then begin
                    arg1 := get_dest(arg0, arg1);
                    emit_rr(zmtc1, var_s3, arg1);
                end else begin
                    arg1 := get_dest(arg0, var_s3);
                end;
            end else begin
                if arg0^.u.Dtype in [Adt, Fdt, Gdt, Hdt, Idt, Jdt, Kdt, Ldt, Ndt, Wdt] then begin
                    arg1 := get_dest(arg0, arg1);
                    emit_rr(zmfc1, arg1, var_s3);
                end else begin
                    arg1 := get_dest(arg0, var_s3);
                end;
            end;
        end;
        Uchkt: begin
            trap(arg0^.u.I1, arg0^.op1, true);
        end;
        Uchkn: begin
            eval(arg0^.op1, arg1);
            var_s3 := arg0^.op1^.reg;
            arg0^.reg := var_s3;
            inc_usage(arg0^.reg, arg0^.ref_count - 1);
            emit_rri_(zteq, var_s3, xr0, 8, franone);
        end;
        Uchkh,
        Uchkl: begin
            eval(arg0^.op1, arg1);
            var_s3 := arg0^.op1^.reg;
            arg0^.reg := var_s3;
            inc_usage(arg0^.reg, arg0^.ref_count - 1);
            if arg0^.u.Opc = Uchkh then begin
                var_a2_2 := arg0^.u.I1 + 1;
                if arg0^.u.Dtype = Jdt then begin
                    var_s5 := ztge;
                    var_s0_13 := cardinal(16#80000000);
                end else begin
                    var_s5 := ztgeu;
                    var_s0_13 := 0;
                end;
            end else begin
                var_a2_2 := arg0^.u.I1;
                var_s5 := ztltu;
                if (arg0^.u.Dtype) = Jdt then begin
                    var_s5 := ztlt;
                    var_s0_13 := cardinal(16#80000000);
                end else begin
                    var_s0_13 := 0;
                end;
            end;
            if var_a2_2 <> var_s0_13 then begin
                emit_ri_(var_s5, var_s3, var_a2_2, franone);
            end;
        end;
        Uiequ,
        Uigeq,
        Uigrt,
        Uileq,
        Uiles,
        Uineq: begin
            eval_irel(arg0);
        end;
        Umov: begin
            eval_mov(arg0);
        end;
        Uxjp: begin
            eval(arg0^.op1, xnoreg);
            var_s3 := reg(arg0^.op1);
            if opcode_arch = ARCH_32 then begin
                if arg0^.u.Dtype in [Idt, Kdt, Wdt] then begin
                    var_s3 := succ(var_s3);
                end;
            end;
            sp186 := var_s3;
            if not is_available(var_s3) then begin
                sp186 := get_free_reg(nil, 1);
                free_reg(sp186);
            end;
            emit_rri_(zsll, sp186, var_s3, 2, franone);
            emit_rllb(zlw, sp186, 0, arg0^.op2^.u.I1, sp186);
            if pic_level = 2 then begin
                emit_cpadd(sp186);
            end;
            emit_r(zj, sp186);
        end;
        Uclab: begin
            if arg0^.u.Length = 0 then begin
                goto next_op;
            end;
            emit_dir0(irdata, 0);
            define_label(arg0^.u.I1);
            
            temp_v0_11 := arg0^.u.Length;

            if (temp_v0_11 <> 0) then begin
                var_s0_13 := temp_v0_11;
                repeat begin
                    arg0 := arg0^.next;
                    emit_dir_ll(arg0^.op2^.u.I1, 0);
                    var_s0_13 := var_s0_13 - 1;
                end until (var_s0_13 = 0);
            end;
            
            if current_text_sec.Ival <> 0 then begin
                emit_itext(current_text_sec);
            end else begin
                emit_dir0(itext, 0);
            end;
        end;
        Unop: begin
        end;
        Ucomm: begin
        end;
        Ubgnb: begin
            emit_dir0(ibgnb, arg0^.u.I1);
        end;
        Uendb: begin
            emit_dir0(iendb, arg0^.u.I1);
        end;
        Urnd: begin
            eval_flt_int_cvt(arg0, arg1);
        end;
        Ucg1: begin
            if arg0^.op1^.u.Opc = Uldc then begin
                if arg0^.op1^.u.Constval.Ival = 0 then begin
                    arg1 := xr0;
                    arg0^.reg := xr0;
                    inc_usage(xr0, arg0^.ref_count);
                end else begin
                    eval(arg0^.op2, arg1);
                    arg0^.reg := arg0^.op2^.reg;
                    inc_usage(arg0^.reg, arg0^.ref_count - 1);
                end;
            end else begin
                temp_s7_2 := gen_label_id();
                eval(arg0^.op1, xnoreg);
                var_s3 := reg(arg0^.op1);
                if (usage_count(var_s3) = 0) and is_available(var_s3) then begin
                    arg1 := var_s3;
                    get_reg(var_s3, arg0, arg0^.ref_count);
                end else begin
                    arg1 := get_free_reg(arg0, arg0^.ref_count);
                    move_to_dest(arg1, var_s3, arg0^.u.Dtype);
                end;
                arg0^.reg := arg1;
                emit_rill(zbeq, var_s3, 0, temp_s7_2);
                eval(arg0^.op2, xnoreg);
                var_s3 := reg(arg0^.op2);
                if arg1 <> var_s3 then begin
                    move_to_dest(arg1, var_s3, arg0^.u.Dtype);
                    if arg0^.unk18 <> 0 then begin
                        arg0^.reg := get_free_reg(arg0, temp_usage_count(arg0^.unk18));
                        free_temp(arg0^.unk18);
                        arg0^.unk18 := 0;
                    end;
                end;
                define_label(temp_s7_2);
            end;
        end;
        Uaos: begin
            if is_constant(arg0^.op1) then begin
                if (max_stack <> -1) and (arg0^.op1^.u.Constval.Ival >= (max_stack - 8)) then begin
                    if not (xr31 in saved_regs) then begin
                        saved_regs := saved_regs + [xr31];
                        frame_size := frame_size + 8;
                    end;
                    get_reg(xr24, nil, 1);
                    emit_ri_(zli, xr24, arg0^.op1^.u.Constval.Ival, franone);
                    free_reg(xr24);
                    emit_regmask(ilivereg, 16#000000C0, 0);
                    emit_a(zjal, stack_limit_bn, 0, franone);
                end;
                if reversed_stack then begin
                    emit_rri_(zaddu, xr29, xr29, arg0^.op1^.u.Offset2, franone);
                end else begin
                    emit_rri_(zsubu, xr29, xr29, arg0^.op1^.u.Offset2, franone);
                end;
                if (max_stack <> -1) and (arg0^.op1^.u.Offset2 < max_stack - 8) then begin
                    emit_rob(zsw, xr0, 0, xr29, 0);
                end;
            end else begin
                if max_stack <> -1 then begin
                    eval(arg0^.op1, xr24);
                    var_s3 := xr24;
                    move_to_dest(xr24, reg(arg0^.op1), arg0^.u.Dtype);
                    if not (xr31 in saved_regs) then begin
                        saved_regs := saved_regs + [xr31];
                        frame_size := frame_size + 8;
                    end;
                    emit_regmask(ilivereg, 16#000000C0, 0);
                    emit_a(zjal, stack_limit_bn, 0, franone);
                end else begin
                    eval(arg0^.op1, xnoreg);
                    var_s3 := reg(arg0^.op1);
                end;
                if reversed_stack then begin
                    emit_rrr(zaddu, xr29, xr29, var_s3);
                end else begin
                    emit_rrr(zsubu, xr29, xr29, var_s3);
                end;
            end;
            if sp144 then begin
                if isa = ISA_MIPS2 then begin
                    emit_rri_(ztltu, xr29, xr23, 9, franone);
                end else begin
                    temp_s7_2 := gen_label_id();
                    emit_rrll(zbgeu, xr29, xr23, temp_s7_2);
                    emit_i(zbreak, 9);
                    define_label(temp_s7_2);
                end;
            end;
        end;
        Uldsp: begin
            arg1 := get_dest(arg0, arg1);
            if framesz_relocatable then begin
                emit_rri_(zaddu, arg1, xr29, reloc_arg_build, franone);
            end else begin
                emit_rri_(zaddu, arg1, xr29, max_arg_build, franone);
            end;
        end;
        Ustsp: begin
            eval(arg0^.op1, xnoreg);
            var_s3 := reg(arg0^.op1);
            if framesz_relocatable then begin
                emit_rri_(zsubu, xr29, var_s3, reloc_arg_build, franone);
            end else begin
                emit_rri_(zsubu, xr29, var_s3, max_arg_build, franone);
            end;
        end;
        Utpeq,
        Utpge,
        Utpgt,
        Utple,
        Utplt,
        Utpne: begin
            assert(arg0^.u.Dtype in [Qdt, Rdt, Xdt]);
            var_s5 := fop(arg0^.u.Opc, arg0^.u.Dtype);
            eval(arg0^.op1, xnoreg);
            eval(arg0^.op2, xnoreg);
            if arg0^.u.Opc in [Utpge, Utpgt] then begin
                sp186 := flt_reg(arg0^.op1);
                var_s3 := flt_reg(arg0^.op2);
            end else begin
                var_s3 := flt_reg(arg0^.op1);
                sp186 := flt_reg(arg0^.op2);
            end;
            emit_rr(var_s5, var_s3, sp186);
            var_s5 := zbc1f;
            if arg0^.u.Opc = Utpne then begin
                var_s5 := zbc1t;
            end;
            temp_s7_2 := gen_label_id();
            emit_ll(var_s5, temp_s7_2);
            emit_i(zbreak, arg0^.u.I1);
            define_label(temp_s7_2);
        end;
        Ucia: begin
            check_no_used();
            if arg0^.u.Lexlev <> 0 then begin
                saved_regs := saved_regs + [xr31];
            end;
            emit_rfi(zcia, xnoreg, arg0^.u.Constval);
        end;
        Ulbdy: begin
            emit_loopno(arg0^.u.I1, arg0^.u.Lexlev);
        end;
        Usqrt: begin
            var_s5 := fop(arg0^.u.Opc, arg0^.u.Dtype);
            if not (arg1 in [xfr0..xfr31]) then begin
                arg1 := xnoreg;
            end;
            eval(arg0^.op1, arg1);
            var_s3 := reg(arg0^.op1);
            arg1 := get_dest(arg0, arg1);
            emit_rr(var_s5, arg1, var_s3);
        end;
        Umtag: begin
            emit_dir2(imtag, 0, arg0^.u.I1, arg0^.u.Lexlev);
        end;
        Ualia: begin
            emit_dir2(imalias, 0, arg0^.u.I1, arg0^.u.Lexlev);
        end;
        Usign: begin
            eval_2ops(arg0);
            temp_s7_2 := gen_label_id();
            if arg0^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                temp_s4_2 := get_free_fp_reg(nil, reg_kind_tab[arg0^.u.Dtype], 1);
                var_s3 := flt_reg(arg0^.op1);
                sp186 := flt_reg(arg0^.op2);
                arg1 := get_dest(arg0, arg1);
                if sp186 = arg1 then begin
                    temp_s2 := get_free_fp_reg(nil, reg_kind_tab[arg0^.op2^.u.Dtype], 1);
                    emit_rr(fasm(fmov_s, arg0^.u.Dtype), temp_s2, sp186);
                end else begin
                    temp_s2 := sp186;
                end;
                var_s5 := fop(Uabs, arg0^.u.Dtype);
                emit_rr(var_s5, arg1, var_s3);
                var_s1_2 := rvalue(arg0^.u.Dtype, "0.0");
                emit_rfi(fasm(fli_s, arg0^.u.Dtype), temp_s4_2, var_s1_2^.u.Constval);
                free_tree(var_s1_2);
                var_s5 := fop(Ules, arg0^.u.Dtype);
                emit_rr(var_s5, temp_s2, temp_s4_2);
                emit_ll(zbc1f, temp_s7_2);
                var_s5 := fop(Uneg, arg0^.u.Dtype);
                free_fp_reg(temp_s4_2, reg_kind_tab[arg0^.u.Dtype]);
                if temp_s2 <> sp186 then begin
                    free_fp_reg(temp_s2, reg_kind_tab[arg0^.op2^.u.Dtype]);
                end;
            end else begin
                var_s3 := reg(arg0^.op1);
                var_s5 := znegu;
                sp186 := reg(arg0^.op2);
                arg1 := get_dest(arg0, arg1);
                if sp186 = arg1 then begin
                    temp_s2 := get_free_reg(nil, 1);
                    dw_emit_rr(zmove, temp_s2, sp186, arg0);
                end else begin
                    temp_s2 := sp186;
                end;
                if opcode_arch = ARCH_32 then begin
                    dw_emit_rr(zabs, arg1, var_s3, arg0);
                end else begin
                    emit_rr(zdabs, arg1, var_s3);
                end;
                emit_branch_rill(zbge, temp_s2, 0, 0, temp_s7_2, arg0);
                if (arg0^.u.Lexlev & 2) <> 0 then begin
                    var_s5 := zneg;
                end;
                if temp_s2 <> sp186 then begin
                    free_reg(temp_s2);
                end;
            end;
            if opcode_arch = ARCH_32 then begin
                dw_emit_rr(var_s5, arg1, arg1, arg0);
            end else if (arg0^.u.Lexlev & 2) <> 0 then begin
                emit_rr(zdneg, arg1, arg1);
            end else begin
                emit_rr(zdnegu, arg1, arg1);
            end;
            define_label(temp_s7_2);
            arg0^.reg := arg1;
        end;
        Ustp: begin
            break;
        end;
        otherwise begin
            report_error(Internal, 6009, "eval.p", "unexpected u-code");
            print_node(err, arg0);
            flush(err);
        end;
        end;

next_op:
        if debug_ugen then begin
            writeln(err,
                "current_line = ", current_line,
                " opc = ", arg0^.u.Opc,
                " reg = ", arg0^.reg,
                " ref_count = ", arg0^.ref_count);
        end;
        arg0 := arg0^.next;
    end;
end;

procedure init_eval();
begin
    first_loc := true;
    first_file_number := 0;
    first_line_number := 0;
    generate_again := false;
end;

procedure load_fp_literal{(arg0: ^tree; arg1: registers)};
begin
    arg1 := get_dest(arg0, arg1);
    emit_rfi(fasm(fli_s, arg0^.u.Dtype), arg1, arg0^.u.Constval);
end;

procedure eval_int_flt_cvt{(arg0: ^tree; arg1: registers)};
var
    sp66: asmcodes;
    sp65: registers;
    sp64: registers;
    sp63: registers;
    sp62: registers;
    sp5C: ^tree;
    sp58: integer;
    var_a1: boolean;
    sp56: Datatype;
begin
    eval(arg0^.op1, xnoreg);
    sp66 := cvt_tab(arg0^.u.Dtype2, arg0^.u.Dtype);
    sp65 := arg0^.op1^.reg;
    assert(sp65 in [xr0..xr31]);
    sp64 := flt_reg(arg0^.op1);
    arg1 := get_dest(arg0, arg1);
    if arg1 in [xfr0..xfr31] then begin
        sp62 := arg1;
    end else begin
        sp62 := sp64;
    end;
    emit_rr(sp66, sp62, sp64);
    if arg0^.u.Dtype2 in [Idt, Jdt] then begin
        var_a1 := false;
    end else begin
        var_a1 := true;
    end;
    if arg0^.op1^.u.Opc = Uldc then begin
        if arg0^.u.Dtype2 = Ldt then begin
            if (arg0^.op1^.u.Constval.Ival > 0) and (arg0^.op1^.u.Constval.Ival < last(integer)) then begin
                var_a1 := false;
            end;
        end;
        if arg0^.u.Dtype2 = Kdt then begin
            if (arg0^.op1^.u.Constval.dwval > 0) and (arg0^.op1^.u.Constval.dwval < last(integer)) then begin
                var_a1 := false;
            end;
        end;
    end;
    if var_a1 then begin
        sp63 := get_free_fp_reg(nil, reg_kind_tab[sp56], 1);
        sp58 := gen_label_id();
        emit_rrll(zbge, sp65, xr0, sp58);
        sp56 := arg0^.u.Dtype;
        sp5C := rvalue(sp56, '4294967296.0');
        emit_rfi(fasm(fli_s, sp56), sp63, sp5C^.u.Constval);
        free_tree(sp5C);
        emit_rrr(fasm(fadd_s, sp56), sp62, sp62, sp63);
        define_label(sp58);
        free_fp_reg(sp63, reg_kind_tab[sp56]);
    end;
    move_to_dest(arg1, sp62, arg0^.u.Dtype);
end;

procedure eval_flt_int_cvt{(arg0: ^tree; arg1: registers)};
var
    sp5E: asmcodes;
    sp5D: registers;
    sp5C: registers;
    sp5B: registers;
    sp5A: registers;
    temp_a0: registers;
    sp54: integer;
    sp50: integer;
    sp4C: integer;
    sp48: ^tree;
    sp47: Datatype;
begin
    eval(arg0^.op1, xnoreg);
    sp5E := cvt_tab(arg0^.u.Dtype2, arg0^.u.Dtype);
    if arg0^.u.Opc = Urnd then begin
        sp5E := rnd_tab(arg0^.u.Dtype2, arg0^.u.Dtype);
    end;
    sp5A := flt_reg(arg0^.op1);
    if (arg0^.u.Opc = Ucvt) and not (arg0^.u.Dtype in [Idt, Jdt]) then begin
        move_cvt_flag := -1;
        sp47 := arg0^.u.Dtype2;
        sp5B := get_free_fp_reg(nil, reg_kind_tab[sp47], 1);
        sp5D := get_free_reg(nil, 1);
        arg1 := get_dest(arg0, arg1);
        sp4C := gen_label_id();
        if (opcode_arch = ARCH_64) and (arg0^.u.Dtype = Ldt) then begin
            emit_rr(ztrunc_l_s, sp5B, sp5A);
            emit_rr(zdmfc1, arg1, sp5B);
            emit_rri_(zdsrl, sp5D, arg1, 32, franone);
            emit_branch_rill(zbeq, sp5D, 0, 0, sp4C, arg0);
            emit_ri_(zli, arg1, -1, franone);
            define_label(sp4C);
        end else begin
            sp54 := gen_label_id();
            sp50 := gen_label_id();
            emit_rr(zcfc1, sp5D, xr31);
            emit_ri_(zli, arg1, 1, franone);
            emit_rr(zctc1, arg1, xr31);
            if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (opcode_arch = ARCH_64) then begin
                emit_rr(fasm(fcvt_l_s, sp47), sp5B, sp5A);
            end else begin
                emit_rr(fasm(fcvt_w_s, sp47), sp5B, sp5A);
            end;
            emit_rr(zcfc1, arg1, xr31);
            emit_dir0(iset, 6);
            emit_rri_(zand, xr1, arg1, 4, franone);
            emit_rri_(zand, arg1, arg1, 120, franone);
            emit_dir0(iset, 5);
            emit_branch_rill(zbeq, arg1, 0, 0, sp54, arg0);
            if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (opcode_arch = ARCH_64) then begin
                sp48 := rvalue(sp47, '9223372036854775808.0');
            end else begin
                sp48 := rvalue(sp47, '2147483648.0');
            end;
            emit_rfi(fasm(fli_s, sp47), sp5B, sp48^.u.Constval);
            free_tree(sp48);
            emit_rrr(fasm(fsub_s, sp47), sp5B, sp5A, sp5B);
            emit_ri_(zli, arg1, 1, franone);
            emit_rr(zctc1, arg1, xr31);
            if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (opcode_arch = ARCH_64) then begin
                emit_rr(fasm(fcvt_l_s, sp47), sp5B, sp5B);
            end else begin
                emit_rr(fasm(fcvt_w_s, sp47), sp5B, sp5B);
            end;
            emit_rr(zcfc1, arg1, xr31);
            emit_dir0(iset, 6);
            emit_rri_(zand, xr1, arg1, 4, franone);
            emit_rri_(zand, arg1, arg1, 120, franone);
            emit_dir0(iset, 5);
            emit_branch_rill(zbne, arg1, 0, 0, sp50, arg0);
            emit_dir0(iset, 6);
            if opcode_arch = ARCH_64 then begin
                emit_dir0(iset, 5);
                emit_rr(zdmfc1, arg1, sp5B);
                sp48 := dwvalue(arg0^.u.Dtype, 0);
                sp48^.u.Constval.Ival := 16#80000000;
                sp5C := get_free_reg(nil, 1);
                emit_rii(zdli, sp5C, sp48^.u.Constval);
                free_tree(sp48);
                emit_rrr(zor, arg1, arg1, sp5C);
                free_reg(sp5C);
            end else begin
                emit_rr(zmfc1, arg1, sp5B);
                emit_ri_(zli, xr1, 16#80000000, franone);
                emit_rrr(zor, arg1, arg1, xr1);
                emit_dir0(iset, 5);
            end;
            emit_ll(zb, sp4C);
            define_label(sp50);
            if opcode_arch = ARCH_64 then begin
                sp48 := dwvalue(arg0^.u.Dtype, -1);
                emit_rii(zdli, arg1, sp48^.u.Constval);
                free_tree(sp48);
            end else begin
                emit_ri_(zli, arg1, -1, franone);
            end;
            emit_ll(zb, sp4C);
            define_label(sp54);
            if opcode_arch = ARCH_64 then begin
                emit_rr(zdmfc1, arg1, sp5B);
            end else begin
                emit_rr(zmfc1, arg1, sp5B);
            end;
            emit_branch_rill(zblt, arg1, 0, 0, sp50, arg0);
            define_label(sp4C);
            emit_rr(zctc1, sp5D, xr31);
        end;
        free_fp_reg(sp5B, reg_kind_tab[sp47]);
        free_reg(sp5D);
    end else begin
        sp5D := get_free_reg(nil, 1);
        sp5B := get_free_fp_reg(nil, reg_kind_tab[arg0^.u.Dtype2], 1);
        emit_rrr(sp5E, sp5B, sp5A, sp5D);
        free_reg(sp5D);
        if move_cvt_flag <> arg0^.unk10 then begin
            free_fp_reg(sp5B, reg_kind_tab[arg0^.u.Dtype2]);
            temp_a0 := get_dest(arg0, arg1);
            move_to_dest(temp_a0, sp5B, arg0^.u.Dtype);
        end else begin
            arg0^.reg := sp5B;
        end;
    end;
end;

procedure eval_int_int_cvt{(arg0: ^tree; arg1: registers)};

    procedure func_004340D4(arg0: ^tree; arg1: registers);
    var
        temp_s1: registers;
        temp_a0: registers;
        sp34: integer;
    begin
        if opcode_arch = ARCH_64 then begin
            if (arg0^.op1^.u.Opc = Ulod) and (ureg(arg0^.op1^.u) = xnoreg) then begin
                arg0^.op1^.u.Dtype := arg0^.u.Dtype;
            end;
            eval(arg0^.op1, xnoreg);
            temp_s1 := reg(arg0^.op1);
            assert(temp_s1 in [xr0..xr31]);
            if arg0^.u.Dtype <> arg0^.op1^.u.Dtype then begin
                emit_rri_(zdsll, temp_s1, temp_s1, 32, franone);
                if arg0^.u.Dtype in [Adt, Idt, Jdt, Wdt] then begin
                    emit_rri_(zdsra, temp_s1, temp_s1, 32, franone);
                end else begin
                    emit_rri_(zdsrl, temp_s1, temp_s1, 32, franone);
                end;
            end;
            temp_a0 := get_dest(arg0, arg1);
            move_to_dest(temp_a0, temp_s1, arg0^.u.Dtype);
        end else begin
            assert((arg0^.u.Lexlev & 2) <> 0);
            eval(arg0^.op1, xnoreg);
            sp34 := gen_label_id();
            temp_s1 := reg(arg0^.op1);
            assert(temp_s1 in [xr0..xr31]);
            emit_rrll(zbgeu, temp_s1, xr0, sp34);
            emit_i(zbreak, 6);
            define_label(sp34);
            temp_a0 := get_dest(arg0, arg1);
            move_to_dest(temp_a0, temp_s1, arg0^.u.Dtype);
        end;
    end;
    
    procedure func_00434500(arg0: ^tree; arg1: registers);
    var
        sp2B: registers;

        procedure func_00434374(arg0: ^tree; arg1: registers);
        begin
            if lsb_first then begin
                move_to_dest(arg1, sp2B, arg0^.u.Dtype);
                emit_ri_(zli, succ(arg1), 0, franone);
            end else begin
                move_to_dest(succ(arg1), sp2B, arg0^.u.Dtype);
                emit_ri_(zli, arg1, 0, franone);
            end;
        end;
        
        procedure func_00434430(arg0: ^tree; arg1: registers);
        begin
            if lsb_first then begin
                move_to_dest(arg1, sp2B, arg0^.u.Dtype);
                emit_rri_(zsra, succ(arg1), sp2B, 31, franone);
            end else begin
                move_to_dest(succ(arg1), sp2B, arg0^.u.Dtype);
                emit_rri_(zsra, arg1, sp2B, 31, franone);
            end;
        end;

    begin
        eval(arg0^.op1, xnoreg);
        sp2B := reg(arg0^.op1);
        assert(sp2B in [xr0..xr31]);
        arg1 := get_dest(arg0, arg1);
        if opcode_arch = ARCH_32 then begin
            if arg0^.u.Dtype2 = Ldt then begin
                func_00434374(arg0, arg1);
            end else begin
                func_00434430(arg0, arg1);
            end;
        end else begin
            move_to_dest(arg1, sp2B, arg0^.u.Dtype);
        end;
    end;
    
    procedure func_00434618(arg0: ^tree; arg1: registers);
    var
        sp33: registers;
        temp_s0: registers;
    begin
        eval(arg0^.op1, xnoreg);
        sp33 := reg(arg0^.op1);
        assert(sp33 in [xr0..xr31]);
        temp_s0 := get_dest(arg0, arg1);
        if opcode_arch = ARCH_64 then begin
            move_to_dest(temp_s0, sp33, arg0^.u.Dtype);
            emit_rri_(zdsll, temp_s0, temp_s0, 32, franone);
            if arg0^.u.Dtype in [Idt, Jdt] then begin
                emit_rri_(zdsra, temp_s0, temp_s0, 32, franone);
            end else begin
                emit_rri_(zdsrl, temp_s0, temp_s0, 32, franone);
            end;
        end else begin
            if lsb_first then begin
                move_to_dest(temp_s0, sp33, arg0^.u.Dtype);
            end else begin
                move_to_dest(temp_s0, succ(sp33), arg0^.u.Dtype);
            end;
        end;
    end;

begin
    if arg0^.u.Dtype in [Idt, Kdt, Wdt] then begin
        func_00434500(arg0, arg1);
    end else if arg0^.u.Dtype2 in [Idt, Kdt, Wdt] then begin
        func_00434618(arg0, arg1);
    end else begin
        func_004340D4(arg0, arg1);
    end;
end;

procedure eval_flt_flt_cvt{(arg0: ^tree; arg1: registers)};
var
    sp26: asmcodes;
    sp25: registers;
    sp24: registers;
begin
    eval(arg0^.op1, xnoreg);
    sp26 := cvt_tab(arg0^.u.Dtype2, arg0^.u.Dtype);
    sp24 := flt_reg(arg0^.op1);
    arg1 := get_dest(arg0, arg1);
    sp25 := arg1;
    if not (arg1 in [xfr0..xfr31]) then begin
        sp25 := get_free_fp_reg(nil, reg_kind_tab[arg0^.u.Dtype], 1);
    end;
    emit_rr(sp26, sp25, sp24);
    if sp25 <> arg1 then begin
        free_fp_reg(sp25, reg_kind_tab[arg0^.u.Dtype]);
    end;
    move_to_dest(arg1, sp25, arg0^.u.Dtype);
end;