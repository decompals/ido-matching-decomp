#include "common.h"
#include "tree.h"
#include "tree_utils.h"

function fold_identities(arg0: Uopcode; arg2: integer64; arg1: boolean): boolean; external;
function fold_idempotents(arg0: Uopcode; arg1: integer64; arg2: boolean; var arg3: integer64): boolean; external;
function fold_constant(arg0: Uopcode; arg1: Datatype; arg2: integer64; 
arg3: integer64; arg4: boolean; arg5: boolean; arg6: boolean; var arg7: integer): boolean; external;
procedure free_tree_and_cse(arg0: pointer); external;

function add_overflow(arg0: u8; arg1: integer; arg2: integer): boolean;
begin
    if arg0 = 6 then begin
        add_overflow := (bitxor(arg1, arg2) >= 0) and (bitxor(cardinal(arg1), (arg1 + arg2)) < 0)
    end else
    add_overflow := ~cardinal(arg1) < cardinal(arg2);
end;

function sub_overflow(arg0: u8; arg1: integer; arg2: integer): boolean;
begin
    if arg0 = 6 then begin
    sub_overflow := (bitxor(arg1, arg2) < 0) and (bitxor(cardinal(arg1), (arg1 - arg2)) < 0)
    end else

    sub_overflow := cardinal(arg1) < cardinal(arg2);
end;

function is_constant(arg0: ^tree): boolean;
begin
    return (arg0^.u.Opc = Uldc) and (arg0^.u.Dtype in [Adt, Hdt..Kdt, Ldt, Wdt]);
end;

function llconst(p_tree: ^tree; dtype: Datatype): integer64;
begin
    { Check for s64, u64, s64* }
    if (dtype in [Idt, Kdt, Wdt]) then begin
        llconst := p_tree^.u.Constval.dwval; 
    { s64 s32 }
    end else if (dtype in [Idt, Jdt]) then begin
        llconst := p_tree^.u.Constval.dwval_h;
    end else begin
        llconst := cardinal(p_tree^.u.Constval.dwval_h);
    end;
end;

function fold(arg0: ^Tree): pointer;
var
    sp70: integer64;
    sp68: integer64;
    sp60: integer64;
    temp_a0_2: Datatype;
    temp_a0_3: ^Tree;
begin    
    if (arg0^.u.Opc = Ucvt) then begin
        if (IS_OVERFLOW_ATTR(arg0^.u.Lexlev)) then begin
            return arg0;
        end;
        
        if (arg0^.u.Dtype in [Qdt, Rdt, Xdt]) then begin    
            return arg0;
        end;
        
        if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and not (arg0^.op1^.u.Dtype in [Idt, Kdt, Wdt]) then begin
            arg0^.op1^.u.Constval.dwval := llconst(arg0^.op1, arg0^.op1^.u.Dtype);
        end else if not (arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (arg0^.op1^.u.Dtype in [Idt, Kdt, Wdt]) then begin
            arg0^.op1^.u.Constval.dwval_h := arg0^.op1^.u.Constval.dwval;
        end;
        arg0^.op1^.u.Dtype := arg0^.u.Dtype;
        return arg0^.op1;
    end;
    
    sp68 := llconst(arg0^.op1, arg0^.u.Dtype);

    if (arg0^.op2 <> nil) then begin
        sp60 := llconst(arg0^.op2, arg0^.u.Dtype);
    end else if (arg0^.u.Opc = Ucvtl) then begin
        sp60 := arg0^.u.I1;
    end;

    if (fold_constant(arg0^.u.Opc, arg0^.u.Dtype, sp68, sp60, 
        arg0^.u.Dtype in [Idt, Jdt], not (arg0^.u.Dtype in [Idt, Kdt, Wdt]), 
        IS_OVERFLOW_ATTR(arg0^.u.Lexlev), sp70)) 
    then begin
        arg0^.visited := false;
        arg0^.op1^.visited := false;

        if (arg0^.op2 <> nil) then begin
            arg0^.op2^.visited := false;
        end;
        free_tree(arg0);

        temp_a0_2 := result_type(arg0);
        if (temp_a0_2 in [Idt, Kdt, Wdt]) then begin
            temp_a0_3 := dwvalue(temp_a0_2, sp70);
        end else begin
            temp_a0_3 := ivalue(temp_a0_2, 0, sp70);
        end;
    end else begin
        return arg0;
    end;
    return temp_a0_3;
end;

function fold1(var arg0: Ptree): boolean;
var
    sp50: integer64;
    sp48: integer64;
    var_a0: Ptree;
    temp_s0: Ptree;
begin

    if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) then begin
        if (is_constant(arg0^.op1)) then begin
            var_a0 := arg0^.op2;
            sp50 := arg0^.op1^.u.Constval.dwval;
        end else begin
            var_a0 := arg0^.op2;
            sp50 := arg0^.op2^.u.Constval.dwval;    
        end;
    end else begin
        if (is_constant(arg0^.op1)) then begin
            var_a0 := arg0^.op2;
            sp50 := arg0^.op1^.u.Constval.Ival;
        end else begin
            var_a0 := arg0^.op2;
            sp50 := arg0^.op2^.u.Constval.Ival;    
        end;
    end;


    if (fold_identities(arg0^.u.Opc, sp50, is_constant(var_a0))) then begin
        temp_s0 := arg0;
        temp_s0^.visited := false;
        
        if (is_constant(temp_s0^.op1)) then begin
            arg0 := dup_tree(temp_s0^.op2);
        end else begin
            arg0 := dup_tree(temp_s0^.op1);
        end;
        free_tree(temp_s0);
        return true;
    end;

    if (fold_idempotents(arg0^.u.Opc, sp50, is_constant(arg0^.op2), sp48)) then begin
        temp_s0 := arg0;

        if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) then begin
            arg0 := dwvalue(temp_s0^.u.Dtype, sp48);
        end else begin
            arg0 := ivalue(temp_s0^.u.Dtype, 0, sp48);
        end;
        temp_s0^.visited := false;
        free_tree_and_cse(temp_s0);
        return true;
    end;
    
    return false;
end;
