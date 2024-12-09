#include "tree.h"
#include "report.h"
#include "cmplrs/allocator.h"

var
    tree_heap: pointer;
    tree_mark: integer;
    tree_counter: integer;
    label_id_counter: integer;
    addr_dtype: Datatype;
    tree_break: integer;

function ivalue(arg0: Datatype; arg1: integer; arg2: integer): pointer; forward;

{No decomped yet}
function new_tree(): pointer; external;
function is_constant(op: ^tree): boolean; external;

procedure initialize_tree();
begin
    tree_mark := 0;
    tree_counter := 0;
    label_id_counter := 31;
end;

procedure gen_label_id();
begin
    label_id_counter := label_id_counter + 1;
end;
 
{GLOBAL_ASM("asm/7.1/functions/ugen/tree_utils/new_tree.s")}

procedure build_u(var arg0: Bcrec);
var
    temp_v0: ^tree;
begin
    temp_v0 := new_tree();
    temp_v0^.u := arg0;
end;

procedure build_u1(var arg0: Bcrec; arg1: ^Tree);
var
    temp_v0: ^tree;
begin
    temp_v0 := new_tree();
    temp_v0^.u := arg0;
    temp_v0^.op1 := arg1;
end;

procedure build_u2(var arg0: Bcrec; arg1: ^Tree; arg2: ^Tree);
var
    temp_v0: ^tree;
begin
    temp_v0 := new_tree();
    temp_v0^.u := arg0;
    temp_v0^.op1 := arg1;
    temp_v0^.op2 := arg2;
end;


procedure build_op(arg0: Uopcode);
var
    temp_v0: ^tree;
begin
    temp_v0 := new_tree();
    temp_v0^.u.Opc := arg0;
end;

{GLOBAL_ASM("asm/7.1/functions/ugen/tree_utils/build_1op.s")}

{GLOBAL_ASM("asm/7.1/functions/ugen/tree_utils/build_2op.s")}

procedure free_node(arg0: pointer);
begin

end;

procedure free_tree(t: ^tree);
label init;
var
    temp_s1: ^tree;
begin

init:    
    t^.ref_count := t^.ref_count - 1;

    if (t^.ref_count = 0) then begin
        if (t^.op1 <> nil) then begin
            if ((t^.u.Opc in [Uaent, Ucg2, Uclab, Uent, Ulab, Unop]) = 0)  then begin
                free_tree(t^.next);
            end;
        end;


    if (t^.op2 <> nil) then begin
        if ((t^.u.Opc in [Uaent, Ucg2, Uclab, Uent, Ufjp, Uijp, Ulab, Unop, Utjp, Uujp, Uxjp]) = 0) then begin
            free_tree(t^.op2);
        end;
    end;

    temp_s1 := t^.next;
    free_node(t);
    t := temp_s1;

    if t <> nil then begin
            goto init; 
        end;
    end;
end;    
    
procedure delete_statement(arg0: ^tree);
begin
    if (arg0^.next <> nil) then begin
        if((arg0^.u.Opc in [Uaent, Ucg2, Uclab, Uent, Ulab, Unop]) = 0) then begin
            free_tree(arg0^.next);
        end;
    end;

    if(arg0^.op2  <> nil) then begin
        if((arg0^.u.Opc in [Uaent, Ucg2, Uclab, Uent, Ufjp, Uijp, Ulab, Unop, Utjp, Uujp, Uxjp]) = 0) then begin
            free_tree(arg0^.op2);
        end;
    end;

    arg0^.op1 := nil;
    arg0^.op2 := nil;
    arg0^.u.Opc := Unop;
end;

function dup_tree(arg0 : ^tree): pointer;
var ret : pointer;
begin
    if (is_constant(arg0) <> false) then begin
        if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) then begin
            ret := ivalue(arg0^.u.Dtype, arg0^.unk30, arg0^.unk34);
        end else begin
            ret := ivalue(arg0^.u.Dtype, 0, arg0^.unk30)
        end;
    end else begin
    
    {Sanity check}
    if (arg0^.ref_count = 16#FFFF) then begin
            report_error(Internal, 300, 'tree_utils.p', 'ref_count overflow');
        end else begin 
            arg0^.ref_count := arg0^.ref_count + 1;
        end;
        ret := arg0;
    end;
    return ret;
end;

function next_mark(): integer;
begin
    tree_mark := (tree_mark + 1) & 255;
    next_mark := tree_mark;
end;

function ivalue();
var
    temp_v0: ^tree;
begin
    temp_v0 := new_tree();
    temp_v0^.u.Opc := Uldc;
    temp_v0^.u.Dtype := arg0;
    
    if (arg0 in [Idt, Kdt, Wdt]) then begin
        temp_v0^.unk34 := arg2;
        temp_v0^.unk30 := arg1;
        temp_v0^.unk28 := 8;
    end else begin
        temp_v0^.unk30 := arg2;
        temp_v0^.unk28 := 4;
    end;

    return temp_v0;
end;

GLOBAL_ASM("asm/7.1/functions/ugen/tree_utils/dwvalue.s")

{GLOBAL_ASM("asm/7.1/functions/ugen/tree_utils/rvalue.s")}

GLOBAL_ASM("asm/7.1/functions/ugen/tree_utils/is_zero.s")

function is_ivalue(arg0: ^tree; arg1: integer; arg2: integer): boolean;
begin
    return is_constant(arg0) and (arg0^.unk30 >= arg1) and  (arg2  >= arg0^.unk30);
end;

function result_type(arg0: ^Tree): Datatype;
begin
    case arg0^.u.Opc of
    Ulca,
    Ulda,
    Uldsp:
        result_type := addr_dtype;
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
    Uleq,
    Ules,
    Ulnot,
    Uneq,
    Uodd:
        result_type := Ldt;
    otherwise:
        result_type := arg0^.u.Dtype;
    end;
end;

GLOBAL_ASM("asm/7.1/functions/ugen/tree_utils/func_0044AED0.s")

GLOBAL_ASM("asm/7.1/functions/ugen/tree_utils/const_equal.s")
