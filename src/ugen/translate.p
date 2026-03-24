#include "cmplrs/allocator.h"
#include "cmplrs/uoptions.h"
#include "tree.h"
#include "ugen_regdef.h"
#include "report.h"
#include "fold.h"
#include "parm_mgr.h"
#include "eval.h"
#include "swap.h"
#include "build.h"
#include "symbol.h"
#include "tree_utils.h"
#include "tree_print.h"

/* Macros */
#define MTYPE_EQU(x, y) (x^.u.Mtype = y^.u.Mtype)
#define DTYPE_EQU(x, y) (x^.u.Dtype = y^.u.Dtype)
#define DTYPE2_EQU(x, y) (x^.u.Dtype2 = y^.u.Dtype2)
#define I1_EQU(x, y) (x^.u.I1 = y^.u.I1)
#define LENGTH_EQU(x, y) (x^.u.Length = y^.u.Length)
#define OFFSET_EQU(x, y) (x^.u.Offset = y^.u.Offset)
#define LEXLEV_EQU(x, y) (x^.u.Lexlev = y^.u.Lexlev)
#define OP1_EQU(x, y) (x^.op1 = y^.op1)
#define OP2_EQU(x, y) (x^.op2 = y^.op2)


type unk_cast_rec = packed record
    case integer of
        4: (as_u32: cardinal);
        2: (pad1, as_u16: u16);
        1: (pad2, pad3, pad4, as_u8: u8);
end;

function need_check_hl(arg0: ^tree): boolean; forward;
function build_ucond0(arg0: ^tree; arg1: integer): pointer; forward;
function cse(arg0: ^tree): pointer; forward;
function load_cse(arg0: ^Tree) : pointer; forward;
function translate(a: ^tree): pointer;  forward;
function set_rewrite(arg0: ^tree; arg1: integer; arg2: 0..32): pointer; forward;
procedure check_reg(arg0: ^Tree); forward;
procedure free_tree_and_cse(arg0: ^tree); forward;
procedure assign_vreg(arg0: Ptree; arg1: boolean); forward;
procedure add_store(arg0: ^tree); forward;
function set_rewrite_indexed(arg0: ^tree; arg1: ^tree; arg2: 0..32): pointer; forward;
function check_vreg(arg0: ^tree; arg1: boolean): boolean; forward;
function check_loads_exprs(arg0: ^tree): boolean; forward;
function translate_cvtl(arg0: ^tree): pointer; forward;

var
    vreg_count: integer;
    vregs: array[0..0] of ^tree;


var
    calls: integer;
    pseudo_leaf: boolean;
    no_cse_flag: integer;
    expr_count: 0..5;
    exprs: array [1..5] of ^tree;
    load_count: 0..5;
    loads: array [1..5] of ^tree;
    h: array [char] of char;
    lsb_first: boolean;
        expression_opcs: array [Uopcode] of boolean;
    reverse: array [Uopcode] of Uopcode;
    current_line: cardinal;
    opt_cse: u8;
    bb_size: integer;
    olevel: 0..255;
    leaf: boolean;
    has_entry: boolean;
    vreg_offset: cardinal;
    max_vreg_offset: integer;
    n_parm_regs: integer;
    n_unsaved_regs: integer;
    n_fp_parm_regs: integer;
    fp_vreg_offset: cardinal;
    max_fp_vreg_offset: integer;
    n_unsaved_fp_regs: integer;
    pdefs: pointer;
    varargs: boolean;
    use_real_fp_for_proc: boolean;
    use_real_fp_for_all: boolean;
    use_fp: boolean;
    mst_node: ^Tree;
    tail_call_opt: boolean;
    ignore_vreg: boolean;
    nooffsetopt: boolean;
    source_language: integer;
    n_saved_regs: integer;
    n_saved_fp_regs: integer;
    addr_dtype: Datatype;
    isa: mips_isa;
    opcode_arch: ( ARCH_32, ARCH_64 );


procedure force_casting(arg0: ^Tree; arg1: integer);
var
    sp24: unk_cast_rec;
    sp20: unk_cast_rec;
begin
    if arg1 <= 4 then begin
        sp20.as_u32 := 0;
        sp24.as_u32 := arg0^.u.Constval.Ival;
        case arg1 of
        4:
            sp20.as_u32 := sp24.as_u32;
        2:
            sp20.as_u16 := sp24.as_u16;
        1:
            sp20.as_u8 := sp24.as_u8;
        end;
        arg0^.u.Constval.Ival := sp20.as_u32;
    end;
end;

(*
*  Check if a number/value is a power of two using bit operations
*   
*  @param: x number to check if it is a power of two
*  @return 'true' if it is a power of two otherwise 'false'
*)
function is_power_of_two(x: integer): boolean;
var
    bits: integer;
begin
    if (x < 0) then begin
        { Negative numbers are not powers of two }
        return false;
    end;
    
    bits := 0;

    while (true) do begin
        /* Check if the least significant bit is set */
        if ((x & 1) = 1) then begin
            { If the rest of the bits are 0, it's a power of two }
            if ((rshift(cardinal(x), 1)) = 0) then begin
                return true;
            end else begin
                return false;
            end;
        end;

        { Right shift to check the next bit }
        x := rshift(x, 1);
        bits := bits + 1;

        { If we've checked all 32 bits, it's still considered a power of two }
        if (bits = 32) then begin
            return true;
        end;
    end;
end;

function get_set_const(var arg0: Valu; arg1: integer; arg2: 0..100): cardinal;
var
    var_v0: integer;
    var_t0: integer;
    var_t1: integer;
    temp_v1: integer;
    i: cardinal;
    var_a2: integer;
    temp_a3 : integer;
begin
    var_v0 := arg0.Ival;
    temp_v1 := arg1 + arg2;
    
    Assert(temp_v1 div 4 <= var_v0);

    var_t0 := 0;
    if (lsb_first = false) then begin
        var_a2 := arg1 div 4 + 1;
        var_t1 := temp_v1 div 4;
    end else begin
        var_t1 := (var_v0 * 4 - arg1) div 4;
        var_a2 := (var_v0 * 4 - temp_v1) div 4 + 1;
    end;

    for i := var_a2 to var_t1 do begin
        var_t0 := var_t0 * 16 + ord(h[arg0.Chars^.ss[i]]);
    end;
    
    return var_t0;
end;

procedure gen_set_str(arg0: ^tree);
var
    var_s0: cardinal;
    sp48: ^tree;    
    temp_v0: ^tree;
    temp_fp: ^tree;
    var_s4: ^tree;
begin
    Assert((arg0^.u.Opc In [Upar, Ustr]));
    sp48 := arg0^.next;
    temp_fp := arg0^.op1;
    var_s4 := arg0;

    arg0^.op1 := set_rewrite(temp_fp, 0, 32);
    
    for var_s0 := 1 to ((arg0^.u.Length + 3) div 4) - 1 do begin
        temp_v0 := build_1op(arg0^.u.Opc, set_rewrite(temp_fp, var_s0 * 32, 32));
        temp_v0^.u.Dtype := Sdt;
        temp_v0^.u.Mtype := arg0^.u.Mtype;
        
        temp_v0^.u.I1 := arg0^.u.I1;
        
        temp_v0^.u.Offset := arg0^.u.Offset + var_s0 * 4;
        temp_v0^.u.Length := 4;
        temp_v0^.u.Lexlev := 0;
        var_s4^.next := temp_v0;
        var_s4 := temp_v0;
    end;
    
    temp_v0^.next := sp48;
    arg0^.u.Length := 4;
    arg0^.u.Lexlev := 0;
    free_tree(temp_fp);
end;

procedure gen_set_istr(arg0: ^tree);
var
    var_s0: cardinal;
    sp48: ^tree;    
    temp_v0: ^tree;
    temp_fp: ^tree;
    var_s4: ^tree;
begin
    Assert((arg0^.u.Opc In [Uisst, Uistr]));
    
    sp48 := arg0^.next;
    temp_fp := arg0^.op2;
    var_s4 := arg0;
    

    arg0^.op2 := set_rewrite(temp_fp, 0, 32);
    
    for var_s0 := 1 to ((arg0^.u.Length + 3) div 4) - 1 do begin
        temp_v0 := set_rewrite(temp_fp, var_s0 * 32, 32);
        temp_v0 := build_2op(arg0^.u.Opc, dup_tree(arg0^.op1), temp_v0);
        temp_v0^.u.Dtype := Sdt;
        temp_v0^.u.Mtype := arg0^.u.Mtype;
        
        temp_v0^.u.I1 := arg0^.u.I1;
        
        temp_v0^.u.Offset := arg0^.u.Offset + var_s0 * 4;
        temp_v0^.u.Length := 4;
        temp_v0^.u.Lexlev := 0;
        var_s4^.next := temp_v0;
        var_s4 := temp_v0;
    end;
    
    temp_v0^.next := sp48;
    arg0^.u.Length := 4;
    arg0^.u.Lexlev := 0;
    free_tree(temp_fp);
end;


function gen_set_equ(arg0: ^tree): pointer;
var
    temp_v0: ^tree;
    var_s4: ^tree;
    var_s0: cardinal;
    
begin
    {TO CHECK}
    Assert(arg0^.u.Opc in [Uequ, Uneq]);
    var_s4 := nil;

    for var_s0 := ((arg0^.op1^.u.Length + 3) div 4) - 1 downto 0 do begin
        temp_v0 := build_2op(Uxor, set_rewrite(arg0^.op1, var_s0 * 32, 32), set_rewrite(arg0^.op2, var_s0 *32, 32));
        temp_v0^.u.Dtype := Ldt;

        if (var_s4 = nil) then begin
            var_s4 := temp_v0;
        end else begin
            var_s4 := build_2op(Uior, var_s4, temp_v0);
            var_s4^.u.Dtype := Ldt;
        end;
    end;

    free_tree(arg0^.op1);
    free_tree(arg0^.op2);

    arg0^.op1 := var_s4;
    arg0^.u.Dtype := Ldt;
    arg0^.op2 := ivalue(Ldt, 0, 0);

    return arg0;
end;

function set_rewrite({arg0: ^tree; arg1: integer; arg2: 0..31  actual range is unknown} );
var
    temp_v0: ^Tree; { spD8 }
    spD4: ^Tree;
    s0: ^Tree; { probably arg0 }
    v012: ^Tree;
    
begin
    case arg0^.u.Opc of
        Uldc:
        begin
            Assert(arg0^.u.Dtype = Sdt);
            temp_v0 := ivalue(Ldt, 0, get_set_const(arg0^.u.Constval, arg1, arg2));
            temp_v0^.u.Length := integer(arg2 + 7) div 8;
        end;

        Ulod:
        begin
            Assert(arg0^.u.Dtype = Sdt);
            temp_v0 := build_u(arg0^.u);
            temp_v0^.u.Offset := temp_v0^.u.Offset + (arg1 div 8);
            temp_v0^.u.Length := integer(arg2 + 7) div 8;
            temp_v0^.u.Lexlev := 0;
        end;

        Uilod,
        Uisld:
        begin
            Assert(arg0^.u.Dtype = Sdt);
            temp_v0 := build_u(arg0^.u);
            temp_v0^.op1 := dup_tree(arg0^.op1);
            temp_v0^.u.Offset := temp_v0^.u.Offset + (arg1 div 8);
            temp_v0^.u.Length := integer(arg2 + 7) div 8;
            temp_v0^.u.Lexlev := 0;
        end;

        Udif,
        Uint,
        Uuni:
        begin
            Assert(arg0^.u.Dtype = Sdt);
            temp_v0 := build_2op(arg0^.u.Opc, set_rewrite(arg0^.op1, arg1, arg2), set_rewrite(arg0^.op2, arg1, arg2));
            temp_v0^.u.Length := integer(arg2 + 7) div 8;
        end;

        Uadj:
        begin
            if (arg1 < arg0^.u.Offset * 8) or (arg1 >= (arg0^.u.Offset + arg0^.op1^.u.Length) * 8) then begin
                temp_v0 := ivalue(Ldt, 0, 0);
            end else begin
                temp_v0 := set_rewrite(arg0^.op1, arg1 - arg0^.u.Offset * 8, arg2);
            end;            
        end;

        Usgs:
        begin
            if (arg0^.op1^.u.Opc = Uldc) then begin
                if (arg0^.op1^.u.Offset2 < arg1) or (arg0^.op1^.u.Offset2 >= (arg1 + arg2)) then begin
                    temp_v0 := ivalue(Ldt, 0, 0);
                end else if lsb_first then begin
                    temp_v0 := ivalue(Ldt, 0, lshift(1, (arg0^.op1^.u.Offset2 - arg1)));
                end else begin
                    temp_v0 := ivalue(Ldt, 0, rshift(cardinal(16#80000000), arg0^.op1^.u.Offset2 - arg1));
                end;
            end else begin
                if (arg1 <> 0) then begin
                    temp_v0 := build_2op(Uadd, dup_tree(arg0^.op1), ivalue(Jdt, 0, -arg1));
                    temp_v0^.u.Lexlev := 0;
                end else begin 
                    temp_v0 := dup_tree(arg0^.op1);
                end;
                temp_v0 := build_2op(Ules, temp_v0, ivalue(Ldt, 0, arg2));
                temp_v0^.u.Dtype := Ldt;
                s0 := dup_tree(arg0^.op1);
                if UGEN_BIG_ENDIAN then begin
                    s0 := build_1op(Unot, s0);
                end;
                temp_v0 := build_2op(Ushl, temp_v0, s0);
            end;
        end;

        Umus:
        begin
            spD4 := dup_tree(arg0^.op1);
            s0 := dup_tree(arg0^.op2);
            if (arg1 <> 0) then begin
                spD4 := build_2op(Uadd, spD4, ivalue(Jdt, 0, -arg1));
                spD4^.u.Lexlev := 0;
            end;

            if (arg1 <> -1) then begin
                s0 := build_2op(Uadd, s0, ivalue(Jdt, 0, 1 - arg1));
                s0^.u.Lexlev := 0;
            end;

            spD4 := build_2op(Umax, spD4, ivalue(Jdt, 0, 0));
            v012 := build_2op(Usub, spD4, build_2op(Umin, s0, ivalue(Jdt, 0, arg2)));
            v012^.u.Lexlev := 0;
            temp_v0 := build_2op(Ushr, v012, ivalue(Ldt, 0, 31));
            temp_v0^.u.Dtype := Jdt;

            if UGEN_LITTLE_ENDIAN then begin
                temp_v0 := build_2op(Ushr, temp_v0, dup_tree(v012));
                temp_v0^.u.Dtype := Ldt;
                temp_v0 := build_2op(Ushl, temp_v0, dup_tree(spD4));
                temp_v0^.u.Dtype := Ldt;
            end else begin
                temp_v0 := build_2op(Ushl, temp_v0, dup_tree(v012));
                temp_v0^.u.Dtype := Ldt;
                temp_v0 := build_2op(Ushr, temp_v0, dup_tree(spD4));
                temp_v0^.u.Dtype := Ldt;
            end;
        end;

        Uchkh:
        begin
            Assert(arg0^.u.Dtype = Sdt);
            temp_v0 := set_rewrite(arg0^.op1, arg1, arg2);
        end;

        Uchkl:
        begin
            Assert(arg0^.u.Dtype = Sdt);
            temp_v0 := set_rewrite(arg0^.op1, arg1, arg2);
        end;
        
        otherwise:
        begin
            report_error(Internal, 560, "translate.p", "illegal u-code");
            print_node(err, arg0);
        end;
    end;
    return temp_v0;
end;

function set_rewrite_indexed({arg0: ^tree; arg1: ^tree; arg2: 0..31});
var
    temp_v0: ^tree;
    temp2: ^tree;
    var_s0: ^tree;
    temp1: ^tree;
begin

    case arg0^.u.Opc of                             /* irregular */
    Uldc,
    Ulod:
    begin
        Assert(arg0^.u.Dtype = Sdt);
        if (arg0^.u.Opc = Ulod) then begin
            arg0^.u.Opc := Ulda;
            arg0^.u.Dtype := addr_dtype;
        end;
        temp_v0 := build_2op(Uadd, arg0, dup_tree(arg1));
        temp_v0^.u.Lexlev := 0;
        temp_v0^.u.Dtype := addr_dtype;

        temp_v0 := build_1op(Uilod, temp_v0);
        temp_v0^.u.Dtype := Sdt;
        temp_v0^.u.Length := integer(arg2 + 7) div 8;
        temp_v0^.u.Offset := 0;
        temp_v0^.u.Offset2 := 0;
        temp_v0^.u.Lexlev := 0;
    end;
    Uilod,
    Uisld:
    begin
        Assert(arg0^.u.Dtype = Sdt);
        arg0^.op1 := build_2op(Uadd, arg0^.op1, dup_tree(arg1));
        arg0^.op1^.u.Lexlev := 0;
        arg0^.u.Lexlev := 0;
        arg0^.u.Length := integer(arg2 + 7) div 8;

        temp_v0 := arg0;
    end;
    Udif,
    Uint,
    Uuni:
    begin
        Assert(arg0^.u.Dtype = Sdt);
        temp_v0 := build_2op(arg0^.u.Opc, set_rewrite_indexed(arg0^.op1, arg1, arg2), set_rewrite_indexed(arg0^.op2, arg1, arg2));
        temp_v0^.u.Length := integer(arg2 + 7) div 8;
    end;
    Uadj:
    begin
        if (arg0^.op1^.u.Opc = Uldc) then begin
            temp_v0 := dup_tree(arg0^.op1);
            free_tree(arg0);
        end else begin
            temp_v0 := build_ucond0(arg1, arg0^.u.Length);
            temp_v0^.op2 := set_rewrite_indexed(arg0^.op1, arg1, arg2);
        end;
    end;
    Usgs:
    begin
        temp_v0 := build_2op(Umpy, dup_tree(arg1), ivalue(Ldt, 0, 8));
        temp_v0^.u.Lexlev := 0;
        temp2 := build_2op(Usub, arg0^.op1, temp_v0);
        temp2^.u.Lexlev := 0;
        var_s0 := dup_tree(temp2);
        if NOT (lsb_first) then begin
            var_s0 := build_1op(Unot, var_s0);
        end;
        temp_v0 := build_2op(Ules, temp2, ivalue(Ldt, 0, arg2));
        temp_v0^.u.Dtype := Ldt;
        temp_v0 := build_2op(Ushl, temp_v0, var_s0);
    end;
    Umus:
    begin
        temp1 := build_2op(Umpy, dup_tree(arg1), ivalue(Ldt, 0, 8));
        temp1^.u.Lexlev := 0;
        temp2 := build_2op(Usub, arg0^.op1, dup_tree(temp1));
        temp2^.u.Lexlev := 0;
        var_s0 := build_2op(Uadd, arg0^.op2, ivalue(Ldt, 0, 1));
        var_s0^.u.Lexlev := 0;
        var_s0 := build_2op(Usub, var_s0, temp1);
        var_s0^.u.Lexlev := 0;
        temp2 := build_2op(Umax, temp2, ivalue(Jdt, 0, 0));
        temp1 := build_2op(Usub, temp2, build_2op(Umin, var_s0, ivalue(Jdt, 0, arg2)));
        temp1^.u.Lexlev := 0;
        temp_v0 := build_2op(Ushr, temp1, ivalue(Ldt, 0, 31));
        temp_v0^.u.Dtype := Jdt;
        if (lsb_first) then begin
            temp_v0 := build_2op(Ushr, temp_v0, dup_tree(temp1));
            temp_v0^.u.Dtype := Ldt;
            temp_v0 := build_2op(Ushl, temp_v0, dup_tree(temp2));
            temp_v0^.u.Dtype := Ldt;
        end else begin
            temp_v0 := build_2op(Ushl, temp_v0, dup_tree(temp1));
            temp_v0^.u.Dtype := Ldt;
            temp_v0 := build_2op(Ushr, temp_v0, dup_tree(temp2));
            temp_v0^.u.Dtype := Ldt;
        end;
    end;
    Uchkh:
    begin
        Assert(arg0^.u.Dtype = Sdt);
        temp_v0 := set_rewrite_indexed(arg0^.op1, arg1, arg2);
        set_rewrite_indexed := temp_v0;
    end;
    Uchkl:
    begin
        Assert(arg0^.u.Dtype = Sdt);
        temp_v0 := set_rewrite_indexed(arg0^.op1, arg1, arg2);
        set_rewrite_indexed := temp_v0;
    end;
    otherwise begin
        report_error(Internal, 689, "translate.p", "illegal u-code");
        print_node(err, arg0);
    end;
    end;
    return temp_v0;
end;


function translate_tree(arg0: pointer): pointer;
var
    var_s0: ^tree;
    temp: ^tree;
begin
    var_s0 := arg0;

    while (var_s0 <> nil) do begin
        temp := translate(var_s0);
        var_s0 := temp^.next;
    end;

    if (calls = 0) then begin
        pseudo_leaf := true;
    end;
    return arg0;
end;

function translate({a: ^Tree});
label restart;
label lab1;
var
    a3: integer;
    s2: ^Tree;
    s1: ^Tree;
    spF4: ^Tree;
    s0: ^Tree;
    i: integer;
    v0: integer;
    spE4: ^Tree;
    pad: array [1..3] of integer;
    a31: integer;
    spD0: integer;
    spCF: Datatype;
    spC8: integer;
    s1op: Uopcode;
    r: registers;
begin
    if a^.visited then begin
        if expression_opcs[a^.u.Opc] then begin
            return cse(a);
        end; 
        
        if a^.u.Opc in [Uisld, Ulod] then begin
            return load_cse(a);
        end;
        
        return a;
    end;


restart:

    a^.visited := True;
    
    case a^.u.Opc of 
        Uloc:
        begin
            current_line := a^.u.I1;
            if opt_cse = 1 then begin
                expr_count := 0;
                load_count := 0;
                bb_size := 0;
            end else if bb_size > 75 then begin
                expr_count := 0;
                load_count := 0;
                bb_size := 0;
            end;

            bb_size := bb_size + 1;
        end;

        Uijp:
        begin
            a^.op1 := translate(a^.op1);
            
            if a^.op1^.u.Opc = Ucg2 then begin
                a^.u.Opc := Uujp;
                a^.op2 := a^.op1^.op1;
                free_tree_and_cse(a^.op1);
                a^.op1 := nil;
            end;
        end;

        Ucg2:
        begin
            a^.op1^.u.Lexlev := bitor(a^.op1^.u.Lexlev, 4);
        end;

        Ufjp,
        Utjp:
        begin
            a^.op1 := translate(a^.op1);
            
            if is_constant(a^.op1) then begin
                if a^.op1^.u.Dtype in [Idt, Kdt, Wdt] then begin
                    a3 := a^.op1^.u.Constval.dwval;
                end else begin
                    a3 := a^.op1^.u.Constval.Ival;
                end;

                if (a3 <> 0) <> (a^.u.Opc = Utjp) then begin
                    delete_statement(a);
                    return a;
                end;

                a^.u.Opc := Uujp;
                a^.op1 := nil;
            end;
        end;

        Uchkt:
        begin
            a^.op1 := translate(a^.op1);
            
            if is_constant(a^.op1) then begin
                if a^.op1^.u.Dtype in [Idt, Kdt, Wdt] then begin
                    a3 := a^.op1^.u.Constval.dwval;
                end else begin
                    a3 := a^.op1^.u.Constval.Ival;
                end;

                if a3 <> 0 then begin
                    delete_statement(a);
                end;
            end;
        end;

        Uchkn:
        begin
            a^.op1 := translate(a^.op1);
            
            if is_constant(a^.op1) then begin
                if a^.op1^.u.Dtype in [Idt, Kdt, Wdt] then begin
                    a3 := a^.op1^.u.Constval.dwval;
                end else begin
                    a3 := a^.op1^.u.Constval.Ival;
                end;

                if a3 <> 0 then begin
                    s1 := a;
                    a := dup_tree(a^.op1);
                    free_tree_and_cse(s1);
                end else begin
                    a^.unk16 := max(a^.op1^.unk16, 1);
                end;
            end else begin
                a^.unk16 := max(a^.op1^.unk16, 1);
            end;
        end;

        Uchkh,
        Uchkl:
        begin
            a^.op1 := translate(a^.op1);
            
            if not need_check_hl(a) then begin
                s1 := a;
                a := dup_tree(a^.op1);
                free_tree_and_cse(s1);
            end else begin
                a^.unk16 := max(a^.op1^.unk16, 1);
            end;
        end;

        Ucvt,
        Unot,
        Ulnot,
        Umpmv,
        Upmov,
        Uneg,
        Urnd,
        Uabs,
        Usqr,
        Usqrt,
        Utyp:
        begin
            a^.op1 := translate(a^.op1);

            if a^.u.Opc = Usqr then begin
                a^.u.Opc := Umpy;
                a^.op2 := dup_tree(a^.op1);
            end;
            
            if (a^.u.Opc = Usqrt) and not (a^.u.Dtype in [Qdt, Rdt]) then begin
                report_error(Internal, 856, "translate.p", "illegal data type for sqrt instruction");
            end;

            a^.unk16 := max(a^.op1^.unk16, 1);
        end;

        Udiv,
        Uequ,
        Ugeq,
        Ugrt,
        Uior,
        Uleq,
        Ules,
        Umax,
        Umin,
        Umod,
        Umpy,
        Uneq,
        Urem,
        Ushl,
        Ushr,
        Usub,
        Uand,
        Ucg1,
        Uxor:
        begin
            if (a^.u.Opc in [Uequ, Uneq]) and (a^.u.Dtype = Sdt) then begin
                if a^.op1^.u.Length <= 4 then begin
                    a^.u.Dtype := Ldt;
                end else begin
                    Assert(a^.op1^.u.Length = a^.op2^.u.Length);
                    a := gen_set_equ(a);
                    goto restart;
                end;
            end;

            a^.op1 := translate(a^.op1);
            if a^.u.Opc = Ucg1 then begin
                no_cse_flag := no_cse_flag + 1;
            end;

            a^.op2 := translate(a^.op2);
            if a^.u.Opc = Ucg1 then begin
                no_cse_flag := no_cse_flag - 1;
            end;

            if (a^.u.Opc = Ushl) or (a^.u.Opc = Ushr) then begin
               if (a^.op2^.u.Opc = Uldc) and (a^.op2^.u.Constval.Ival >= 32) then begin
                   a^.op2^.u.Constval.Ival := a^.op2^.u.Constval.Ival mod 32;
               end;
            end;

            if a^.op1^.unk16 = a^.op2^.unk16 then begin
                a^.unk16 := a^.op1^.unk16 + 1;
            end else begin
                a^.unk16 := max(a^.op1^.unk16, a^.op2^.unk16);
            end;

            case a^.u.Opc of
                Uleq:
                if a^.op2^.u.Opc = Uldc then begin
                    if (a^.u.Dtype in [Jdt]) then begin
                        s1 := a;
                        if a^.op2^.u.Constval.Ival = 16#7FFFFFFF then begin
                            a := ivalue(Ldt, 0, 1);
                            free_tree_and_cse(s1);
                        end;
                    end else if a^.u.Dtype = Ldt then begin
                        s1 := a;
                        if a^.op2^.u.Constval.Ival = -1 then begin
                            a := ivalue(Ldt, 0, 1);
                            free_tree_and_cse(s1);
                        end;
                    end;
                end;

                Ugrt:
                if a^.op2^.u.Opc = Uldc then begin
                    if (a^.u.Dtype in [Jdt]) then begin
                        s1 := a;
                        if a^.op2^.u.Constval.Ival = 16#7FFFFFFF then begin
                            a := ivalue(Ldt, 0, 0);
                            free_tree_and_cse(s1);
                        end;
                    end else if a^.u.Dtype = Ldt then begin
                        s1 := a;
                        if a^.op2^.u.Constval.Ival = -1 then begin
                            a := ivalue(Ldt, 0, 0);
                            free_tree_and_cse(s1);
                        end;
                    end;
                end;

                Ugeq:
                if a^.op2^.u.Opc = Uldc then begin
                    if a^.u.Dtype in [Jdt] then begin
                        s1 := a;
                        if a^.op2^.u.Constval.Ival = 16#80000000 then begin
                            a := ivalue(Ldt, 0, 1);
                            free_tree_and_cse(s1);
                        end;
                    end else if a^.u.Dtype = Ldt then begin
                        s1 := a;
                        if a^.op2^.u.Constval.Ival = 0 then begin
                            a := ivalue(Ldt, 0, 1);
                            free_tree_and_cse(s1);
                        end;
                    end;
                end;

                Ules:
                if a^.op2^.u.Opc = Uldc then begin
                    if (a^.u.Dtype in [Jdt]) then begin
                        s1 := a;
                        if a^.op2^.u.Constval.Ival = 16#80000000 then begin
                            a := ivalue(Ldt, 0, 0);
                            free_tree_and_cse(s1);
                        end;
                    end else if a^.u.Dtype = Ldt then begin
                        s1 := a;
                        if a^.op2^.u.Constval.Ival = 0 then begin
                            a := ivalue(Ldt, 0, 0);
                            free_tree_and_cse(s1);
                        end;
                    end;
                end;

                Umod:
                if (a^.op2^.u.Opc = Uldc) and (a^.ref_count = 1) then begin
                    if olevel <> 0 then begin
                        v0 := 1;
                        for a3 := 0 to 31 do begin
                            if a^.op2^.u.Constval.Ival = v0 then begin
                                a^.op2^.u.Constval.Ival := a^.op2^.u.Constval.Ival - 1;
                                a^.u.Opc := Uand;
                                break;
                            end;
                            v0 := v0 * 2;
                        end;
                    end;
                end;

                Uequ,
                Uneq:
                if olevel <> 0 then begin
                    if is_zero(a^.op2) and (a^.op1^.ref_count = 1) then begin
                        if a^.op1^.u.Opc = Umod then begin
                            a^.op1^.u.Opc := Urem;
                        end;

                        if (a^.op1^.u.Opc = Urem) and
                           (a^.op1^.u.Dtype = Jdt) and
                           is_constant(a^.op1^.op2) and
                           is_power_of_two(a^.op1^.op2^.u.Constval.Ival) then begin
                            a^.op1^.u.Dtype := Ldt;
                        end;
                    end else if is_zero(a^.op1) and (a^.op2^.ref_count = 1) then begin
                        if a^.op2^.u.Opc = Umod then begin
                            a^.op2^.u.Opc := Urem;
                        end;

                        if (a^.op2^.u.Opc = Urem) and
                           (a^.op2^.u.Dtype = Jdt) and
                           is_constant(a^.op2^.op2) and
                           is_power_of_two(a^.op2^.op2^.u.Constval.Ival) then begin
                            a^.op2^.u.Dtype := Ldt;
                        end;
                    end;
                end;

                otherwise;
            end;
        end;
        
        Uent:
        begin
            leaf := True;
            has_entry := False;

            if n_parm_regs = 4 then begin
                vreg_offset := 16;
                max_vreg_offset := vreg_offset + 4 * (n_parm_regs + n_unsaved_regs);
            end else begin
                vreg_offset := 32;
                max_vreg_offset := vreg_offset + 4 * (n_unsaved_regs);
            end;
        
            vreg_count := 0;
            if cardinal(n_fp_parm_regs * 2) = 4 then begin
                fp_vreg_offset := 176;
                max_fp_vreg_offset := fp_vreg_offset + 4 * cardinal((n_unsaved_fp_regs + n_fp_parm_regs) * 2);
            end else begin
                fp_vreg_offset := 192;
                max_fp_vreg_offset := fp_vreg_offset + 4 * cardinal(n_unsaved_fp_regs * 2);
            end;

            expr_count := 0;
            load_count := 0;
            bb_size := 0;
            pdefs := nil;
            varargs := False;
            calls := 0;

            use_real_fp_for_proc := use_real_fp_for_all or use_fp or IS_FRAMEPTR_ATTR(a^.u.Extrnal);
        end;

        Uoptn:
        begin
            if a^.u.I1 = 1 then begin
                varargs := True;
                vreg_offset := 32;
                max_vreg_offset := vreg_offset + 4 * n_unsaved_regs;
                fp_vreg_offset := 192;
                max_fp_vreg_offset := fp_vreg_offset + 4 * cardinal(n_unsaved_fp_regs * 2);
            end;
        end;

        Ucup,
        Urcuf:
        begin
            a3 := GET_STDARGS_NUM(a^.u.Push);
            if a3 > 0 then begin
                map_pars_to_regs(mst_node, a3);
            end else begin
                map_pars_to_regs(mst_node, -1);
            end;
            fix_amt_ref(mst_node);
            a^.u.Mtype := Zmt;

            if tail_call_opt and
               not IS_RETURN_ATTR(a^.u.Extrnal) and
               not IS_REALLOC_ARG_ATTR(a^.u.Extrnal) and
               not IS_GOTO_ATTR(a^.u.Extrnal) and
               not IS_COMPOSITE_CALL_ATTR(a^.u.Extrnal) and
               (a^.u.Dtype = spCF) { spCF not initialized } and
               (a^.u.Lexlev = spD0) { spD0 not initialized } then begin

                spE4 := a^.next;
                while (spE4^.u.Opc <> Uujp) do begin
                    if not (spE4^.u.Opc in [Ubgnb, Ucomm, Udef, Uendb, Ulex, Uloc, Unop, Uoptn, Usdef]) then begin
                        if not ((spE4^.u.Opc = Ustr) and
                                ((ureg(spE4^.u) = gpr_v0) or (ureg(spE4^.u) = xfr0)) and 
                                (spE4^.op1^.u.Opc = Ulod) and
                                (spE4^.op1^.u.Offset = spE4^.u.Offset)) then begin
                            goto lab1;
                        end;
                    end;
                    spE4 := spE4^.next;
                end;

                s0 := spE4^.op2^.next;
                while s0^.u.Opc in [Ubgnb, Ucomm, Udef, Uendb, Ulex, Uloc, Unop, Uoptn, Usdef] do begin
                    s0 := s0^.next;
                end;
                if s0^.u.Opc <> Uend then begin
                    goto lab1;
                end;
                
                s0 := spE4^.next;
                while s0^.u.Opc in [Ubgnb, Ucomm, Udef, Uendb, Ulex, Uloc, Unop, Uoptn, Usdef] do begin
                    s0 := s0^.next;
                end;
                if s0^.u.Opc <> Uend then begin
                    goto lab1;
                end;

                spE4 := a^.prior;
                while not((spE4^.u.Opc = Umst) or (spE4^.u.Opc = Urpar) or (spE4^.u.Opc = Ustr)) do begin
                    spE4 := spE4^.prior;
                end;
                if ((spE4^.u.Opc = Urpar) or (spE4^.u.Opc = Ustr)) then begin
                    { spC8 not initialized }
                    a3 := (spE4^.u.Offset + spE4^.u.Length + 3) div 4;
                    if (max(a3, 4) > max(spC8, 4)) then begin
                        goto lab1;
                    end;
                end;

                while (spE4^.u.Opc <> Umst) do begin
                    if (spE4^.u.Opc = Urpar) and
                       (spE4^.u.Dtype = addr_dtype) and
                       (spE4^.prior^.u.Opc = Ustr) and 
                       ((spE4^.prior^.op1^.u.Opc = Ulod) or (spE4^.prior^.op1^.u.Opc = Ulda)) and
                       ((spE4^.prior^.op1^.u.Mtype = Mmt) or (spE4^.prior^.op1^.u.Mtype = Pmt)) then begin
                        goto lab1;
                    end;
                    spE4 := spE4^.prior;
                end;

                spE4 := a^.prior;
                while not((spE4^.u.Opc = Umst) or (spE4^.u.Opc = Urpar)) do begin
                    if (spE4^.u.Opc = Ustr) and (spE4^.u.Mtype = Pmt) then begin
                        if ((spE4^.op1^.u.Opc = Ulod) and (spE4^.op1^.u.Mtype = Pmt) and (spE4^.op1^.u.Offset < spE4^.u.Offset)) or
                           ((spE4^.op1^.op1 <> nil) and (spE4^.op1^.op1^.u.Opc = Ulod) and (spE4^.op1^.op1^.u.Mtype = Pmt) and (spE4^.op1^.op1^.u.Offset < spE4^.u.Offset)) or
                           ((spE4^.op1^.op2 <> nil) and (spE4^.op1^.op2^.u.Opc = Ulod) and (spE4^.op1^.op2^.u.Mtype = Pmt) and (spE4^.op1^.op2^.u.Offset < spE4^.u.Offset)) then begin
                            goto lab1;
                        end;
                    end;
                    spE4 := spE4^.prior;
                end;

                a^.u.Mtype := Amt;
            end;

            lab1:

            if a^.u.Mtype <> Amt then begin
                if IS_RETURN_ATTR(a^.u.Extrnal) then begin
                    if IS_GOTO_ATTR(a^.u.Extrnal) then begin
                        calls := calls + 1;
                        pseudo_leaf := False;
                    end;
                end else begin
                    calls := calls + 1;
                end;
            end;
            
            expr_count := 0;
            load_count := 0;
            bb_size := 0;
        end;

        Ulab,
        Uaent:
        begin
            expr_count := 0;
            load_count := 0;
            bb_size := 0;
        end;

        Uicuf:
        begin
            a^.op1 := translate(a^.op1);
            a3 := GET_STDARGS_NUM(a^.u.Push);
            if a3 > 0 then begin 
                map_pars_to_regs(mst_node, a3);
            end else begin
                map_pars_to_regs(mst_node, -1);
            end;
                
            calls := calls + 1;
            expr_count := 0;
            load_count := 0;
            bb_size := 0;
        end;

        Ulod:
        begin
            check_reg(a);
            if a^.u.Mtype <> Rmt then begin
                a^.unk16 := 1;
            end else begin
                a^.unk16 := 0;
            end;
            return load_cse(a);
        end;

        Uvreg:
        begin
            assign_vreg(a, leaf);
        end;

        Udef:
        begin
            if (a^.u.Mtype = Tmt) and not pseudo_leaf then begin
                Assert(vreg_count = 0);
                leaf := False;
                if a^.u.I1 = 1 then begin
                    has_entry := True;
                end;

                vreg_offset := 64;
                max_vreg_offset := vreg_offset + 4 * n_saved_regs;
                fp_vreg_offset := 208;
                max_fp_vreg_offset := fp_vreg_offset + cardinal(n_saved_fp_regs * 2) * 4;
            end else if a^.u.Mtype = Pmt then begin
                pdefs := a^.op1;
                if leaf and not varargs then begin
                    spE4 := pdefs;
                    while (spE4 <> nil) and (spE4^.u.Constval.Ival <> -1) do begin
                        r := parm_reg(spE4);
                        if (r >= gpr_a0) and (r <= registers(n_parm_regs + ord(gpr_a0) - 1)) then begin
                            vreg_offset := min((spE4^.u.Constval.Ival + spE4^.u.Length + 3) div 4, 8) * 4;
                        end else begin
                            fp_vreg_offset := min(((spE4^.u.Constval.Ival + spE4^.u.Length + 7) div 8) * 2, 48) * 4;
                        end;

                        spE4 := spE4^.next;
                    end;
                end;

                s0 := pdefs;
                while s0 <> nil do begin
                    s0 := s0^.next;
                end;
                if s0 <> nil then ;
            end;
        end;

        Uiequ,
        Uigeq,
        Uigrt,
        Uileq,
        Uiles,
        Uineq,
        Umov:
        begin
            a^.op1 := translate(a^.op1);
            a^.op2 := translate(a^.op2);
            load_count := 0;
            expr_count := 0;            
            bb_size := 0;
        end;

        Uadj:
        begin
            s1 := a;
            Assert(a^.u.Length <= 32);
            a := set_rewrite(a^.op1, -a^.u.Offset, a^.u.Length * 8);
            free_tree_and_cse(s1);
            goto restart;
        end;

        Ucvtl:
        begin
            if IS_OVERFLOW_ATTR(a^.u.Lexlev) then begin
                a^.op1 := translate(a^.op1);
            end else if is_constant(a^.op1) then begin
                a := fold(a);
            end else begin
                if (a^.op1^.u.Opc = Ucvtl) and (a^.op1^.u.I1 >= a^.u.I1) then begin
                    if IS_OVERFLOW_ATTR(a^.op1^.u.Lexlev) then begin
                        s1 := a;
                        a := translate(dup_tree(s1^.op1));
                        free_tree_and_cse(s1);
                        return a;
                    end;

                    s1 := a^.op1;
                    a^.op1 := dup_tree(s1^.op1);
                    free_tree_and_cse(s1);
                end else if (a^.op1^.u.Opc = Ucvtl) and ((a^.u.Dtype = a^.op1^.u.Dtype) or (a^.op1^.u.Dtype <> Jdt)) then begin
                    s1 := a;
                    a := translate(dup_tree(s1^.op1));
                    free_tree_and_cse(s1);
                    a^.unk16 := max(s1^.op1^.unk16, 1);
                    return a;
                end;

                a := translate_cvtl(a);
                goto restart;
            end;
        end;

        Uilda:
        begin
            a^.op1 := translate(a^.op1);
            a^.op2 := ivalue(Jdt, 0, a^.u.Offset);
            a^.u.Opc := Uadd;
            a^.u.Lexlev := 0;

            if a^.op1^.unk16 = a^.op2^.unk16 then begin
                a^.unk16 := a^.op1^.unk16 + 1;
            end else begin
                a^.unk16 := max(a^.op1^.unk16, a^.op2^.unk16);
            end;
        end;

        Ulda:
        begin
            a := cse(a);
        end;

        Uldc,
        Uldrc:
        begin
            if (a^.u.Dtype = Sdt) and (a^.u.Length <= 4) then begin
                a^.u.Constval.Ival := get_set_const(a^.u.Constval, 0, a^.u.Length * 8);
                a^.u.Dtype := Ldt;
            end;

            if a^.u.Dtype in [Qdt, Rdt, Xdt] then begin
                a^.unk16 := 1;
            end else begin
                a^.unk16 := 0;
            end;
        end;

        Uadd:
        begin
            a^.op1 := translate(a^.op1);
            a^.op2 := translate(a^.op2);

            if a^.op1^.u.Opc = Ulda then begin
                swap_tree(a^.op1, a^.op2);
            end else if a^.op1^.u.Opc = Uneg then begin
                s1 := a^.op1;
                a^.op1 := dup_tree(s1^.op1);
                free_tree_and_cse(s1);
                swap_tree(a^.op1, a^.op2);
                a^.u.Opc := Usub;
            end else if a^.op2^.u.Opc = Uneg then begin
                s1 := a^.op2;
                a^.op2 := dup_tree(s1^.op1);
                free_tree_and_cse(s1);
                a^.u.Opc := Usub;
            end else if (a^.op1^.ref_count = 1) and (a^.op1^.u.Opc = Uadd) and (a^.op1^.op2^.u.Opc = Ulda) then begin
                swap_tree(a^.op2, a^.op1^.op2);
            end else if (a^.op2^.ref_count = 1) and (a^.op2^.u.Opc = Uadd) and (a^.op2^.op2^.u.Opc = Ulda) then begin
                swap_tree(a^.op1, a^.op2^.op2);
                swap_tree(a^.op1, a^.op2);
            end;

            if a^.op1^.unk16 = a^.op2^.unk16 then begin
                a^.unk16 := a^.op1^.unk16 + 1;
            end else begin
                a^.unk16 := max(a^.op1^.unk16, a^.op2^.unk16);
            end;
        end;

        Uodd:
        begin
            a^.op1 := translate(a^.op1);
            a^.u.Opc := Uand;
            a^.op2 := ivalue(Ldt, 0, 1);

            if a^.op1^.unk16 = a^.op2^.unk16 then begin
                a^.unk16 := a^.op1^.unk16 + 1;
            end else begin
                a^.unk16 := max(a^.op1^.unk16, a^.op2^.unk16);
            end;
        end;

        Uuni:
        begin
            Assert(a^.u.Length <= 4);
            a^.u.Opc := Uior;
            a^.u.Dtype := Ldt;
            goto restart;
        end;

        Uint:
        begin
            Assert(a^.u.Length <= 4);
            a^.u.Opc := Uand;
            a^.u.Dtype := Ldt;
            goto restart;
        end;

        Udif:
        begin
            Assert(a^.u.Length <= 4);
            a^.u.Opc := Uand;
            a^.u.Dtype := Ldt;
            a^.op2 := build_1op(Unot, a^.op2);
            a^.op2^.u.Dtype := Ldt;
            goto restart;
        end;

        Usgs:
        begin
            Assert(a^.u.Length <= 4);
            if lsb_first then begin
                a^.u.Opc := Ushl;
                s1 := a^.op1;
                a^.op2 := s1;
                a^.op1 := build_2op(Ules, dup_tree(a^.op1), ivalue(Ldt, 0, a^.u.Length * 32));
                a^.op1^.u.Dtype := Ldt;
            end else begin
                a^.u.Opc := Ushr;
                {s1 := a^.op1;}
                a^.op2 := a^.op1;
                a^.op1 := ivalue(Ldt, 0, 16#80000000);
            end;

            a^.u.Dtype := Ldt;
            goto restart;
        end;

        Umus:
        begin
            Assert(a^.u.Length <= 4);
            s1 := dup_tree(a^.op1);
            s0 := dup_tree(a^.op2);
            free_tree_and_cse(a);

            s0 := build_2op(Uadd, s0, ivalue(Jdt, 0, 1));
            s0^.u.Lexlev := 0;
            s0 := build_2op(Usub, s1, s0);
            s0^.u.Lexlev := 0;
            a := build_2op(Ushr, s0, ivalue(Ldt, 0, 31));
            a^.u.Dtype := Jdt;

            if lsb_first then begin
                a := build_2op(Ushr, a, dup_tree(s0));
                a^.u.Dtype := Ldt;
                a := build_2op(Ushl, a, dup_tree(s1));
                a^.u.Dtype := Ldt;
            end else begin
                a := build_2op(Ushl, a, dup_tree(s0));
                a^.u.Dtype := Ldt;
                a := build_2op(Ushr, a, dup_tree(s1));
                a^.u.Dtype := Ldt;
            end;

            goto restart;
        end;

        Uinn:
        begin
            s1 := a^.op2;
            spF4 := nil;
            if s1^.u.Length <= 4 then begin
                s2 := build_2op(Ules, dup_tree(a^.op1), ivalue(Ldt, 0, a^.u.Length * 8));
                s2^.u.Dtype := Ldt;
            end else begin
                s2 := ivalue(Ldt, 0, 1);
                s0 := a^.op1;
                if s0^.u.Opc = Uldc then begin
                    a3 := s0^.u.Constval.Ival;
                    a^.op2 := set_rewrite(s1, (a3  div 32) * 32, 32);
                    free_tree_and_cse(s1);
                end else begin
                    spF4 := build_ucond0(s0, s1^.u.Length * 8);
                    s0 := build_2op(Ushr, dup_tree(s0), ivalue(Ldt, 0, 5));
                    s0^.u.Dtype := Jdt;
                    s0 := build_2op(Umpy, s0, ivalue(Ldt, 0, 4));
                    s0^.u.Lexlev := 0;
                    a^.op2 := set_rewrite_indexed(s1, s0, 32);
                    free_tree_and_cse(s0);
                    expr_count := 0;
                    load_count := 0;
                    bb_size := 0;
                end;
            end;

            swap_tree(a^.op1, a^.op2);

            if lsb_first then begin
                if a^.op1^.u.Length < 4 then begin
                    a^.op2 := build_2op(Uand, a^.op2, ivalue(Ldt, 0, a^.op1^.u.Length * 8 - 1));
                end;
                a^.u.Opc := Ushr;
                a^.visited := False;
                
                a := build_2op(Uand, a, s2);
            end else begin
                a^.u.Opc := Ushl;
                a^.visited := False;

                if not ((s2^.u.Opc = Uldc) and (s2^.u.Constval.Ival = 1)) then begin
                    a^.op1 := build_2op(Uand, a^.op1, build_1op(Uneg, s2));
                    a^.op1^.op2^.op1^.u.Lexlev := 0;
                end else begin
                    free_tree_and_cse(s2);
                end;

                a := build_2op(Ules, a, ivalue(Jdt, 0, 0));
                a^.u.Dtype := Jdt;
            end;

            if spF4 <> nil then begin
                spF4^.op2 := a;
                a := spF4;
            end;
            
            goto restart;
        end;

        Umst:
        begin
            mst_node := a;
        end;

        Upar,
        Ustr:
        begin
            Assert(a^.ref_count = 1);
            
            if (a^.u.Dtype = Sdt) and (a^.u.Length > 4) then begin
                gen_set_str(a);
            end;

            if (a^.u.Opc = Ustr) and not ((a^.u.Mtype = Pmt) and (a^.u.I1 = 0)) then begin
                check_reg(a);
            end;

            if (a^.u.Length <= 4) then begin
                if (a^.op1^.u.Opc = Ucvtl) and 
                   (a^.u.Length * 8 = a^.op1^.u.I1) and
                   not IS_OVERFLOW_ATTR(a^.op1^.u.Lexlev) and
                   (a^.u.Mtype <> Rmt) then begin
                    s1 := a^.op1;
                    a^.op1 := dup_tree(a^.op1^.op1);
                    free_tree_and_cse(s1);
                end;
            end;

            s1op := a^.op1^.u.Opc;
            a^.op1 := translate(a^.op1);

            if (source_language = C_SOURCE) and (a^.u.Length < 4) and (s1op <> Ucvtl) and (a^.u.Mtype = Rmt) then begin
                s0 := build_1op(Ucvtl, a^.op1);
                s0^.u.I1 := a^.u.Length * 8;
                s0^.u.Dtype := a^.u.Dtype;
                a^.op1 := translate_cvtl(s0);
            end;

            if a^.u.Opc = Ustr then begin
                add_store(a);

                for a3 := 1 to expr_count do begin
                    if (exprs[a3] <> nil) and ((exprs[a3]^.u.opc = Uilod) or (exprs[a3]^.u.opc = Uistr)) then begin
                        exprs[a3] := nil;
                    end;
                end;
            end else;
        end;

        Uilod,
        Uisld:
        begin
            a^.op1 := translate(a^.op1);
            s1 := a^.op1;
            if (not nooffsetopt) and
               (a^.op1^.u.Opc = Uadd) and
               is_constant(a^.op1^.op2) and
               check_loads_exprs(s1^.op1) then begin
               a^.u.Offset := a^.u.Offset + s1^.op2^.u.Constval.Ival;
               a^.op1 := dup_tree(s1^.op1);
               free_tree_and_cse(s1);
            end;

            a^.unk16 := max(a^.op1^.unk16, 1);

            if a^.u.Opc = Uisld then begin
                return load_cse(a);
            end;
            
            if a^.u.Opc = Uilod then begin
                a := cse(a);
            end;
        end;
        

        Uirld:
        begin
            s1 := a^.op1;
            a^.op1 := translate(s1);
            a^.unk16 := max(a^.op1^.unk16, 1);
            a := cse(a);
        end;

        Uisst,
        Uistr:
        begin
            Assert(a^.ref_count = 1);
            if (a^.u.Dtype = Sdt) and (a^.u.Length > 4) then begin
                gen_set_istr(a);
            end;

            if (a^.u.Length <= 4) and (a^.op2^.u.Opc = Ucvtl) and (a^.u.Length * 8 = a^.op2^.u.I1) then begin
                s1 := a^.op2;
                a^.op2 := dup_tree(a^.op2^.op1);
                free_tree_and_cse(s1);
            end;

            a^.op1 := translate(a^.op1);
            a^.op2 := translate(a^.op2);

            s1 := a^.op1;
            if (not nooffsetopt) and (s1^.u.Opc = Uadd) and (s1^.op2^.u.Opc = Uldc) and check_loads_exprs(s1^.op1) then begin
                a^.u.Offset := a^.u.Offset + s1^.op2^.u.Constval.Ival;
                a^.op1 := dup_tree(s1^.op1);
                free_tree_and_cse(s1);
            end;

            if a^.u.Opc = Uisst then begin
                add_store(a);
            end else begin
                load_count := 0;
                expr_count := 1;
                exprs[1] := a;
                bb_size := 0;
            end;
            
        end;

        Uirst:
        begin
            Assert(a^.ref_count = 1);
            Assert(a^.u.Dtype <> Sdt);

            if (a^.u.Length <= 4) and (a^.op2^.u.Opc = Ucvtl) and (a^.u.Length * 8 = a^.op2^.u.I1) then begin
                s1 := a^.op2;
                a^.op2 := dup_tree(a^.op2^.op1);
                free_tree_and_cse(s1);
            end;

            a^.op1 := translate(a^.op1);
            a^.op2 := translate(a^.op2);

            if ignore_vreg and (a^.op1^.u.Mtype in [Mmt, Pmt]) then begin
                if (a^.op1^.u.Opc in [Uilda, Uisld, Uisst, Ulda, Ulod, Umpmv, Upar, Updef, Upmov, Urlod, Urpar, Urstr, Ustr]) and not check_vreg(a^.op1, True) then begin
                    load_count := 0;
                end;
            end else begin
                load_count := 0;
            end;

            expr_count := 1;
            exprs[1] := a;
            bb_size := 0;
            
        end;

        Uxjp:
        begin
            a^.op1 := translate(a^.op1);
        end;

        Uaos:
        begin
            a^.op1 := translate(a^.op1);
        end;

        Uldsp:
        begin
            if leaf then begin
                a^.u.Opc := Ulod;
                a^.u.Mtype := Rmt;
                a^.u.Offset := 4 * integer(gpr_sp);
                a^.unk16 := 0;
            end;
        end;

        Uldap:
        begin
            a^.u.Opc := Ulod;
            a^.u.Mtype := Rmt;
            a^.u.Offset := 4 * integer(gpr_sp);   
            a^.unk16 := 0;
        end;
        
        Ustsp:
        begin
            a^.op1 := translate(a^.op1);
            if leaf then begin
                a^.u.Opc := Ustr;
                a^.u.Mtype := Rmt;
                a^.u.Offset := 4 * integer(gpr_sp);
            end;
        end;

        Ucia:
        begin
            map_pars_to_regs(mst_node, -1);
            expr_count := 0;
            load_count := 0;
            bb_size := 0;
        end;

        Usign:
        begin
            a^.op1 := translate(a^.op1);
            a^.op2 := translate(a^.op2);

            if a^.op1^.unk16 = a^.op2^.unk16 then begin
                a^.unk16 := a^.op1^.unk16 + 1;
            end else begin
                a^.unk16 := max(a^.op1^.unk16, a^.op2^.unk16);
            end;
        end;

        otherwise;
    end;

    { fold expressions }

    if expression_opcs[a^.u.Opc] then begin
        if (a^.op1 <> nil) and is_constant(a^.op1) then begin
            if (a^.op2 = nil) or is_constant(a^.op2) then begin
                return fold(a);
            end;

            if reverse[a^.u.Opc] <> Unop then begin
                swap_tree(a^.op1, a^.op2);
                a^.u.Opc := reverse[a^.u.Opc];
            end;

            if fold1(a) then begin
                return a;
            end;
        end else if (a^.op2 <> nil) and is_constant(a^.op2) then begin
            if fold1(a) then begin
                return a;
            end;
        end;

        a := cse(a);
    end;
    
    return a;
end;

function cse_equ(arg0: ^tree; arg1: ^tree): boolean;
begin
    if (arg0 = arg1) then begin
        return true;
    end;

    if ((arg0^.u.Opc <> arg1^.u.Opc) and
        ((arg0^.u.Opc <> Uilod) or (arg1^.u.Opc <> Uistr))) then begin
        return false;
    end;


    case arg0^.u.Opc of
        Ulda:
            begin
                return MTYPE_EQU(arg0, arg1) and I1_EQU(arg0, arg1) and OFFSET_EQU(arg0, arg1) and LENGTH_EQU(arg0, arg1);
            end;

        Uchkn,
        Ulnot,                                  /* switch 5 */
        Unot,                                  /* switch 5 */
        Usqr,                                  /* switch 5 */
        Usqrt:
            begin
                return DTYPE_EQU(arg0, arg1) and OP1_EQU(arg0, arg1);
            end;

        Uabs,
        Uneg:
            begin
                return DTYPE_EQU(arg0, arg1) and LEXLEV_EQU(arg0, arg1) and OP1_EQU(arg0, arg1);
            end;

        Uchkh,
        Uchkl:
            begin
                return DTYPE_EQU(arg0, arg1) and I1_EQU(arg0, arg1) and OP1_EQU(arg0,arg1);
            end;

        Ucvtl:
            begin
                return DTYPE_EQU(arg0, arg1) and I1_EQU(arg0, arg1) and LEXLEV_EQU(arg0, arg1) and OP1_EQU(arg0, arg1);
            end;

        Ucvt,
        Urnd,
        Utyp:
            begin
                return DTYPE_EQU(arg0, arg1) and DTYPE2_EQU(arg0, arg1) and LEXLEV_EQU(arg0, arg1) and OP1_EQU(arg0, arg1);
            end;

        Uadj:
            begin
                return OFFSET_EQU(arg0, arg1) and LENGTH_EQU(arg0, arg1) and OP1_EQU(arg0, arg1);
            end;

        Uilda:
            begin
                return MTYPE_EQU(arg0, arg1) and I1_EQU(arg0, arg1) and OFFSET_EQU(arg0, arg1) and LENGTH_EQU(arg0, arg1) and OP1_EQU(arg0, arg1);
            end;

        Uand,
        Udif,
        Uequ,
        Ugeq,
        Ugrt,
        Uinn,
        Uior,
        Uleq,
        Ules,
        Umax,
        Umin,
        Umus,
        Uneq,
        Ushl,
        Ushr,
        Uxor:
            begin
                return DTYPE_EQU(arg0, arg1) and
                OP1_EQU(arg0, arg1) and
                (OP2_EQU(arg0, arg1) or
                 (const_equal(arg0^.op2, arg1^.op2)));
            end;

        Uadd,
        Udiv,
        Urem,
        Umod,
        Umpy,
        Usub:
            begin
                return DTYPE_EQU(arg0, arg1) and OP1_EQU(arg0, arg1) and LEXLEV_EQU(arg0, arg1) and (OP2_EQU(arg0, arg1) or
                                                                                                     (const_equal(arg0^.op2, arg1^.op2)));
            end;

        Uint,
        Uuni:
            begin
                return DTYPE_EQU(arg0, arg1) and LENGTH_EQU(arg0, arg1) and OP1_EQU(arg0, arg1) and (OP2_EQU(arg0, arg1) or
                                                                                                     (const_equal(arg0^.op2, arg1^.op2)));
            end;

        Uilod,
        Uisld:
            begin
                return DTYPE_EQU(arg0, arg1) and OFFSET_EQU(arg0, arg1) and LENGTH_EQU(arg0, arg1) and OP1_EQU(arg0, arg1);
            end;

        Uirld:
            begin
                return DTYPE_EQU(arg0, arg1) and I1_EQU(arg0, arg1) and LENGTH_EQU(arg0, arg1) and OP1_EQU(arg0, arg1);
            end;

        Ulca: return false;

        otherwise:
            begin
                report_error(Internal, 2114, "translate.p", "illegal u-code");
                return false;
            end;
    end;
end;

function cse({arg0: ^tree});
var
    temp_s1: ^tree;
    i: 1..5;
begin
    if (no_cse_flag > 0) then begin
        return arg0;
    end;

    if (((arg0^.u.Opc = Uilod) or (arg0^.u.Opc = Uirld)) and (IS_VOLATILE_ATTR(arg0^.u.Lexlev))) then begin
        return arg0;
    end;

    if (((arg0^.op1 = nil) or (arg0^.op1^.ref_count >= 2) or 
    (arg0^.op1^.u.Opc = Uldc)) and ((arg0^.op2 = nil) or 
    (arg0^.op2^.ref_count >= 2) or (arg0^.op2^.u.Opc = Uldc))) then begin

        for i := expr_count downto 1 do begin
            temp_s1 := exprs[i];
            if ((temp_s1 <> nil) and (cse_equ(arg0, temp_s1))) then begin
                if (arg0 = temp_s1) then begin
                    return arg0;
                end;
                free_tree_and_cse(arg0);

                if ((temp_s1^.u.Opc = Uistr) or (temp_s1^.u.Opc = Uirst)) then begin
                    temp_s1 := dup_tree(temp_s1^.op2);

                    if (temp_s1^.u.Opc = Uldc) then begin
                        if (temp_s1^.u.Length <> arg0^.u.Length) then begin
                            force_casting(temp_s1, arg0^.u.Length);
                        end;
                    end;
                    return temp_s1;
                end;
                return dup_tree(temp_s1);
            end;
        end;
    end;

    if (expr_count < integer(10)) then begin
        expr_count := expr_count + 1;
        exprs[expr_count] := arg0;
    end;
    return arg0;
end;

function overlap(arg0: ^tree; arg1: ^tree): boolean;
var
    var_v0: integer;
    var_v1: integer;
begin
    if (arg0^.u.Opc = Ulda) then begin
        var_v0 := arg0^.u.Offset2;
    end else begin
        var_v0 := arg0^.u.Offset;
    end;

    if (arg1^.u.Opc = Ulda) then begin
        var_v1 := arg1^.u.Offset2;
    end else begin
        var_v1 := arg1^.u.Offset;
    end;

    return ((var_v0 < (var_v1 + arg1^.u.Length))=true) and not bitxor(((var_v1 < (var_v0 + arg0^.u.Length))),1);

end;

procedure free_tree_and_cse({arg0: ^tree});
var
    var_v0: cardinal;
begin
    arg0^.ref_count := arg0^.ref_count - 1;

    if (arg0^.ref_count = 0) then begin
        {TODO: Match set D_10016994}
        if (arg0^.u.Opc in [Uendb..Uneq]) then begin
            for var_v0 := load_count downto 1 do begin
                if (arg0 = loads[var_v0]) then begin
                    loads[var_v0] := nil;
                end;
            end;
        end else begin
            for var_v0 := expr_count downto 1 do begin
                if (arg0 = exprs[var_v0]) then begin
                    exprs[var_v0] := nil;
                end;
            end;
        end;

        if (arg0^.op1 <> nil) then begin
            {TODO: Match set D_10016984}
            if not (arg0^.u.Opc in [Uabs..Upop]) then begin
                free_tree_and_cse(arg0^.op1);
            end;
        end;
    
        if (arg0^.op2 <> nil) then begin
            {TODO: Match set D_10016970}
            if not (arg0^.u.Opc in [Uabs..Uirst]) then begin
                free_tree_and_cse(arg0^.op2);
            end;
        end;
    
        free_node(arg0);
    end;
end;

function check_vreg({arg0: ^tree; arg1: boolean});
var
    i: integer;
    temp_s1: ^tree;
    v0: ^tree;    
begin
    for i := 0 to vreg_count - 1 do begin
        temp_s1 := vregs[i];

        if ((temp_s1 <> nil) and (arg0^.u.I1 = temp_s1^.u.I1) and (overlap(arg0, temp_s1))) then begin
            if ((arg0^.u.mtype <> temp_s1^.u.mtype)) then begin
                report_error(Internal, 2256, "translate.p", "attempt to access undefined memory location");
            end;

            if ((arg0^.u.Offset <> temp_s1^.u.Offset) or (arg0^.u.Length <> temp_s1^.u.Length)) then begin
                report_error(Internal, 2261, "translate.p", "offset/length mismatch between vreg and reference");
            end;

            if not (arg1) then begin
                v0 := vregs[i]; {Neccesary to match}
                arg0^.u.Mtype := Rmt;

                arg0^.u.Offset := temp_s1^.u.Offset2;

                if (v0^.ref_count2 = 0) then begin
                    v0^.ref_count2 := 1;
                end;
            end;
            
            return true;
        end;
    end;
    
    return false;
end;

procedure find_vreg_mtag(arg0: ^tree);
var
    var_s0: integer;
    temp_s1: ^tree;
    s4: integer;
begin
    for var_s0 := 0 to vreg_count - 1 do begin
        temp_s1 := vregs[var_s0];

        if ((temp_s1 <> nil) and (arg0^.u.I1 = temp_s1^.u.I1) and (overlap(arg0, temp_s1))) then begin
            if ((arg0^.u.mtype <> temp_s1^.u.mtype)) then begin
                report_error(Internal, 2292, "translate.p", "attempt to access undefined memory location");
            end;

            if ((arg0^.u.Offset <> temp_s1^.u.Offset) or (arg0^.u.Length <> temp_s1^.u.Length)) then begin
                report_error(Internal, 2297, "translate.p", "offset/length mismatch between vreg and reference");
            end;
            arg0^.u.Offset2 := temp_s1^.u.aryoff;
            return;
        end;
    end;
end;

procedure check_reg({arg0: ^tree});
var
    ret: integer;
    check: boolean;
begin

    Assert(arg0^.u.mtype <> Tmt);
    if (arg0^.u.mtype = Amt) then begin
        ret := check_amt(arg0);
        if (ret <> -1) then begin
            arg0^.u.Offset := ret;
            arg0^.u.Mtype := Rmt;
        end;
    end else if (arg0^.u.mtype in [Mmt, Pmt]) then begin
        if not (ignore_vreg) then begin
            check := check_vreg(arg0, false);
            return;
        end;
        if (get_domtag() <> 0) then begin
            find_vreg_mtag(arg0);
        end;
    end else if (arg0^.u.mtype = Smt) then begin
        arg0^.u.Offset2 := get_mtag(arg0^.u.I1);
    end;
end;

procedure assign_vreg({arg0: Ptree; arg1: boolean});
var
    temp_v1: cardinal;
    v1: cardinal;
begin
    case arg0^.u.Dtype of
    Qdt,
    Rdt:
    begin
        if (fp_vreg_offset <  max_fp_vreg_offset) then begin
            vregs[vreg_count] := arg0;
            vreg_count := vreg_count + 1;
            if ((arg1) and (arg0^.u.Mtype = Pmt)) then begin
                temp_v1 := parm_reg(arg0) & 255;
                if ((temp_v1 <> 72) and (temp_v1 >= 44) and (((n_fp_parm_regs * 2) + 42) >= temp_v1)) then begin
                    arg0^.u.Offset2 := temp_v1 * 4;
                    return;
                end;
                arg0^.u.Offset2 := fp_vreg_offset;
                temp_v1 := fp_vreg_offset;
            end else begin
                Assert(arg0^.u.Offset2 = -1);
                arg0^.u.Offset2 := fp_vreg_offset;
                temp_v1 := fp_vreg_offset;
            end;
            fp_vreg_offset := temp_v1 + 8;
        end;
    end;
    Adt,
    Fdt,
    Gdt,
    Hdt,
    Jdt,
    Ldt,
    Mdt,
    Ndt,
    Sdt:
    begin
        Assert(arg0^.u.Length < 5);
        if (vreg_offset < max_vreg_offset) then begin
            vregs[vreg_count] := arg0;
            vreg_count := vreg_count + 1;
            if (((arg1) or (has_entry)) and (arg0^.u.Mtype = Pmt)) then begin
                temp_v1 := parm_reg(arg0) & 255;
                if (temp_v1 = 72) then begin
                    Assert(arg0^.u.Offset2 = -1);
                    arg0^.u.Offset2 := vreg_offset;
                    temp_v1 := vreg_offset;
                end else begin
                    Assert((arg0^.u.Offset2 = -1) or (arg0^.u.Offset2 = temp_v1 * 4));
                    arg0^.u.Offset2 := temp_v1 * 4;
                    return;
                end;
            end else begin
                Assert(arg0^.u.Offset2 = -1);
                arg0^.u.Offset2 := vreg_offset;
                temp_v1 := vreg_offset;
            end;

            vreg_offset := temp_v1 + 4;
            if (((use_real_fp_for_proc and arg1) or has_entry) and (vreg_offset * 1 = 52)) then begin
                vreg_offset := vreg_offset * 1 + 4;
                return;
            end;
        end;
    end;
    Xdt:
        report_error(Internal, 2387, "translate.p", "extended float not yet supported");
    Idt,
    Kdt,
    Wdt:
    begin
        if (opcode_arch = ARCH_64) then begin
            Assert(arg0^.u.Length < 9);
            if (vreg_offset < max_vreg_offset) then begin
                vregs[vreg_count] := arg0;
                vreg_count := vreg_count + 1;
                if (((arg1) or (has_entry)) and (arg0^.u.Mtype = Pmt)) then begin
                    temp_v1 := parm_reg(arg0) & 255;
                    if (temp_v1 = 72) then begin
                        Assert(arg0^.u.Offset2 = -1);
                        arg0^.u.Offset2 := vreg_offset;
                        temp_v1 := vreg_offset;
                    end else begin
                        Assert((arg0^.u.Offset2 = -1) or (arg0^.u.Offset2 = temp_v1 * 4));
                        arg0^.u.Offset2 := temp_v1 * 4;
                        return;
                    end;
                end else begin
                    Assert(arg0^.u.Offset2 = -1);
                    arg0^.u.Offset2 := vreg_offset;
                temp_v1 := vreg_offset;
                end;
                vreg_offset := temp_v1 + 8;
                return;
            end;
        end;
        end;
    otherwise
    begin
        report_error(Internal, 2417, "translate.p", "illegal vreg type");
    end;
    end;
end;

function load_cse({arg0: ^Tree});
var
    temp_v0: ^tree;
    temp_a1: ^tree;
    
    var_v0: ^tree;
    i: 1..5;
    
begin
    if (no_cse_flag > 0) then begin
        return arg0;
    end;

    if (NOT (arg0^.u.Opc in [Uisld, Ulod]) or NOT (arg0^.u.Mtype in [Mmt, Pmt, Smt, Amt]) or IS_VOLATILE_ATTR(arg0^.u.Lexlev) or (((arg0^.u.Dtype <> Sdt) or (arg0^.u.Length >= 5)) and ((arg0^.u.Dtype = Sdt) or (arg0^.u.Length >= 9)))) then begin
        return arg0;
    end;

    for i := load_count downto 1 do begin 
        temp_a1 := loads[i];

        if (temp_a1 <> nil) then begin
            if ((temp_a1^.u.Dtype = arg0^.u.Dtype) and (temp_a1^.u.Mtype = arg0^.u.Mtype) and (temp_a1^.u.I1 = arg0^.u.I1)) then begin
                if ((UGEN_LITTLE_ENDIAN and (temp_a1^.u.Offset = arg0^.u.Offset)) or 
                    (UGEN_BIG_ENDIAN and (temp_a1^.u.Offset + temp_a1^.u.Length = arg0^.u.Offset + arg0^.u.Length))) then begin
                    if (temp_a1^.u.Length = arg0^.u.Length) then begin
                        
                        if (temp_a1^.u.Opc = Ustr) then begin
                            var_v0 := dup_tree(temp_a1^.op1);
                        end else if (temp_a1^.u.Opc = Uisst) then begin
                            var_v0 := dup_tree(temp_a1^.op2);
                        end else if (arg0 = temp_a1) then begin
                            return arg0;
                        end else begin
                            var_v0 := dup_tree(temp_a1);
                        end;
        
                        if (((source_language = C_SOURCE) and (arg0^.u.Length < temp_a1^.u.Length)) or
                            ((arg0^.u.Length < 4) and (temp_a1^.u.Opc in [Uisst, Ustr]))) then begin
                            temp_v0 := build_1op(Ucvtl, var_v0);
                            temp_v0^.u.Dtype := arg0^.u.Dtype;
                            temp_v0^.u.I1 := arg0^.u.Length * 8;
                            var_v0 := translate_cvtl(temp_v0);
                        end;
        
                        if (var_v0^.u.Opc = Uldc) then begin
                            if (var_v0^.u.Dtype <> arg0^.u.Dtype) then begin
                                var_v0^.u.Dtype := arg0^.u.Dtype;
                            end;
                        end;
        
                        free_tree(arg0);
                        return var_v0;
                    end;
                end;
            end;
        end;
    end;

    if (load_count < integer(10)) then begin
        load_count := load_count + 1;
        loads[load_count] := arg0;
    end;
    
    return arg0;
end;

function uses(arg0: ^Tree; arg1: ^Tree; arg2: cardinal): boolean;
label loop;
begin

    if (arg2 >= 16) then begin
        return true;
    end;

    loop:
    case arg0^.u.Opc of                               /* irregular */
        Ulod:
        begin
            return ((arg0^.u.Mtype = arg1^.u.Mtype) and (arg0^.u.I1 = arg1^.u.I1) and (overlap(arg0, arg1)));
        end;

        Ucg2,
        Ulab,
        Ulca,
        Ulda,
        Uldc,
        Uldsp,
        Uldrc:
            return false;
        Uchkh,
        Uchkl,
        Uchkn,
        Uchkt,
        Uabs,
        Uadj,
        Ucvt,
        Ucvtl,
        Udec,
        Uilda,
        Uilod,
        Uinc,
        Uisld,
        Ulnot,
        Uneg,
        Unot,
        Uodd,
        Urnd,
        Usgs,
        Usqr,
        Usqrt,
        Utyp,
        Uirld:
        begin
            arg0 := arg0^.op1;
            goto loop;
        end;
        Ucg1,
        Uadd,
        Uand,
        Udif,
        Udiv,
        Uequ,
        Ugeq,
        Ugrt,
        Uiequ,
        Uigeq,
        Uigrt,
        Uileq,
        Uiles,
        Uineq,
        Uinn,
        Uint,
        Uior,
        Uixa,
        Uleq,
        Ules,
        Umax,
        Umin,
        Umod,
        Umpy,
        Umus,
        Uneq,
        Urem,
        Usub,
        Ushl,
        Ushr,
        Usign,
        Uuni,
        Uxor:
        begin
            if (uses(arg0^.op1, arg1, arg2 + 1)) then begin
                return true;
            end else if (arg0^.op1 = arg0^.op2) then begin
                return false;
            end;
    
            arg0 := arg0^.op2;
            goto loop;
        end;
        otherwise:
        begin
            report_error(Internal, 2550, "translate.p", "illegal u-code");
        end;
    end;
end;

procedure add_store({arg0: ^tree});
var
    var_s3: ^tree;
    temp_s0: ^tree;
    i: 1..5;
    s2: ^tree;
begin
    s2 := arg0;

    if not (s2^.u.Mtype in [Mmt, Pmt, Amt, Smt]) then begin
        return;
    end;


    if ((s2^.u.Dtype = Sdt) and (s2^.u.Length <= 4) or
        ((s2^.u.Dtype <> Sdt) and (s2^.u.Length <= 8))) then begin
        var_s3 := s2;


        {TODO: Match set D_100169B0}
        if (s2^.u.Opc = Ustr) and
                (((s2^.op1^.u.Opc in [Uequ, Uneq]) and (s2^.op1^.u.Mtype = Rmt)) or
                 ((s2^.op1^.op1 <> nil) and (s2^.op1^.op1^.u.Opc in [Uequ, Uneq]) and (s2^.op1^.op1^.u.Mtype = Rmt))) then begin
            var_s3 := nil;
        {TODO: Match set D_100169B0}
        end else if (s2^.u.Opc = Uisst) and (s2^.op2^.u.Opc in [Uequ, Uneq]) and (s2^.op2^.u.Mtype = Rmt) then begin
            var_s3 := nil;
        end;

        for i := load_count downto 1 do begin
            temp_s0 := loads[i];

            if (temp_s0 = nil) then begin
                loads[i] := var_s3;
                var_s3 := nil;
            end else if ((temp_s0^.u.Mtype = s2^.u.Mtype) and (temp_s0^.u.I1 = s2^.u.I1) and (overlap(temp_s0, s2))) then begin
                loads[i] := var_s3;
                var_s3 := nil;
            end else if ((temp_s0^.u.Opc = Ustr) and (uses(temp_s0^.op1, s2, 0))) then begin
                loads[i] := nil;
            end;
        end;

        if ((var_s3 <> nil) and (load_count < integer(10))) then begin
            load_count := load_count + 1;
            loads[load_count] := var_s3;
        end;
    end;

end;

function is_reg(arg0: ^tree): boolean;
begin
    if (arg0^.u.Dtype in [Fdt, Cdt, Idt, Jdt]) then begin
        check_reg(arg0);
    end;
    return arg0^.u.Dtype = Gdt;
end;


function translate_cvtl({arg0: ^tree});
label lab1;
var
    temp_v1: integer;
    sp37: Datatype;
    var_s0: ^tree;
    var_a1: ^tree;
begin
    if (is_constant(arg0^.op1)) then begin 
        return fold(arg0);
    end;

    sp37 := arg0^.u.Dtype;
    temp_v1 := arg0^.u.I1;
    var_s0 := dup_tree(arg0^.op1);
    arg0^.visited := false;
    free_tree(arg0);

    if (temp_v1 >= 16#40) then begin
        return var_s0;
    end;

    if (((var_s0^.u.Opc = Ulod) and not (is_reg(var_s0))) or (var_s0^.u.Opc = Uilod) or (var_s0^.u.Opc = Uisld)) then begin
        if (var_s0^.u.Length * 8 < temp_v1) then begin
            if ((var_s0^.u.Dtype = Jdt) and (sp37 <> Jdt) and ((sp37 <> Idt) or (isa < ISA_MIPS3))) then begin
               goto lab1;
            end else begin
               return var_s0;
           end;
        end;

        if ((var_s0^.u.Length * 8 = temp_v1) and (sp37 = var_s0^.u.Dtype)) then begin
            return var_s0;
        end;

        {temp_a2 := temp_v1 div 8;}
        if ((var_s0^.u.Lexlev & 1 = 0) and (var_s0^.ref_count < 2) and (temp_v1 & 7 = 0) and (((temp_v1 div 8) = 1) or ((temp_v1 div 8) = 2) or ((temp_v1 div 8) = 4) or ((temp_v1 div 8) = 8))) then begin
            var_a1 := build_u(var_s0^.u);
            if (var_s0^.u.Opc <> Ulod) then begin
                if ((var_s0^.op1^.u.Opc = Ulod) and (is_reg(var_s0^.op1))) then begin
                    var_a1^.op1 := build_u(var_s0^.op1^.u);
                end else begin
                    var_a1^.op1 := dup_tree(var_s0^.op1);
                end;
                {var_a1^.op1 := var_v0;}
            end;
            free_tree(var_s0);
            if not (lsb_first) then begin
                var_a1^.u.Offset := ((var_a1^.u.Offset + var_a1^.u.Length) - (temp_v1 div 8));
            end;

            var_a1^.u.Length := (temp_v1 div 8);
            var_a1^.u.Dtype := sp37;
            return var_a1;
        end;
    end;
    lab1:
    if (sp37 = Jdt) then begin
        var_s0 := build_2op(Ushl, var_s0, ivalue(Ldt, 0, 32 - temp_v1));
        var_s0^.u.Dtype := sp37;
        var_s0 := build_2op(Ushr, var_s0, ivalue(Ldt, 0, 32 - temp_v1));
    end else if (sp37 = Idt) then begin
        var_s0 := build_2op(Ushl, var_s0, ivalue(Kdt, 0, 64 - temp_v1));
        var_s0^.u.Dtype := sp37;
        var_s0 := build_2op(Ushr, var_s0, ivalue(Kdt, 0, 64 - temp_v1));
    end else begin
        if (temp_v1 >= 32) then begin
            var_s0 := build_2op(Uand, var_s0, ivalue(Kdt, lshift(1, temp_v1) - 1, -1));
        end else begin
            var_s0 := build_2op(Uand, var_s0, ivalue(Ldt, 0, lshift(1, temp_v1) - 1));
        end;
        var_s0^.u.Dtype := sp37;
    end;
    
    return var_s0;
end;

function need_check_hl({arg0: ^tree});
var
    bool: boolean;
begin
    {If the Datatype is a set we don't need to check anything }
    if (arg0^.u.Dtype = Sdt) then begin
        return false;
    end;

    if (is_constant(arg0^.op1)) then begin
        return ((arg0^.u.Opc = Uchkh) and (arg0^.u.I1 < arg0^.op1^.u.Offset2)) or 
        ((arg0^.u.Opc = Uchkl) and (arg0^.u.I1 > arg0^.op1^.u.Offset2)) ;
    end;

    return true;

end;

function build_ucond0({arg0: ^tree; arg1: integer});
var
    pad: array [0..2] of integer;
    sp20: pointer;
    p: ^tree;
begin
    sp20 := dup_tree(arg0);
    p := build_2op(Ules, sp20, ivalue(Ldt, 0, arg1));
    p^.u.Dtype := Ldt;
    p := build_2op(Ucg1, p, nil);
    p^.u.Dtype := Ldt;
    return p;
end;

function check_loads_exprs({arg0: ^tree});
var
    i: integer;
begin
    for i := load_count downto 1 do begin
        if (arg0 = loads[i]) then begin
            return true;
        end;
    end;

    for i := expr_count downto 1 do begin
        if (arg0 = exprs[i]) then begin
            return true;
        end;
    end;
    return false;
end;
