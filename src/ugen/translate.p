#include "cmplrs/allocator.h"
#include "tree.h"
#include "report.h"
#include "fold.h"
#include "tree_utils.h"

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

function translate(a0: pointer): pointer;  external;
function set_rewrite(arg0: ^tree; arg1: integer; arg2: Uopcode): pointer; external;
procedure check_reg(arg0: ^Tree); forward;
procedure free_tree_and_cse(arg0: ^tree); forward;

var
    vreg_count: integer;
    vregs: array[0..0] of ^tree;


var
    calls: integer;
    pseudo_leaf: boolean;
    no_cse_flag: integer;
    expr_count: 1..5;
    exprs: array [1..5] of ^tree;
    load_count: 1..5;
    loads: array [1..5] of ^tree;
    h: array [char] of char;
    lsb_first: boolean;

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
    if (UGEN_BIG_ENDIAN) then begin
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

    arg0^.op1 := set_rewrite(temp_fp, 0, Uendb);
    
    for var_s0 := 1 to ((arg0^.u.Length + 3) div 4) - 1 do begin
        temp_v0 := build_1op(arg0^.u.Opc, set_rewrite(temp_fp, var_s0 * 32, uendb));
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
    

    arg0^.op2 := set_rewrite(temp_fp, 0, Uendb);
    
    for var_s0 := 1 to ((arg0^.u.Length + 3) div 4) - 1 do begin
        temp_v0 := set_rewrite(temp_fp, var_s0 * 32, uendb);
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
        temp_v0 := build_2op(Uxor, set_rewrite(arg0^.op1, var_s0 * 32, uendb), set_rewrite(arg0^.op2, var_s0 *32, Uendb));
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

function set_rewrite(arg0: ^tree; arg1: integer; arg2: 0..31 { actual range is unknown } ): pointer;
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

function set_rewrite_indexed(arg0: ^tree; arg1: ^tree; arg2: 0..31): pointer;
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

GLOBAL_ASM("asm/7.1/functions/ugen/translate/translate.s")

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

function cse(arg0: ^tree): pointer; 
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

function check_vreg(arg0: ^tree; arg1: boolean): boolean;
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

procedure assign_vreg(arg0: Ptree; arg1: boolean);
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
        if (opcode_arch = 1) then begin
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

function load_cse(arg0: ^Tree) : pointer;
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

        {Length -> 0x28} 
        {Offset -> 0x2C} 
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

procedure add_store(arg0: ^tree);
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

GLOBAL_ASM("asm/7.1/functions/ugen/translate/translate_cvtl.s")

function need_check_hl(arg0: ^tree): boolean;
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

procedure build_ucond0(arg0: ^tree; arg1: integer);
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
end;

function check_loads_expr(arg0: ^tree): boolean;
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
