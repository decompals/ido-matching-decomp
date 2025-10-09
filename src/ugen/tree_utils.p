#include "cmplrs/allocator.h"
#include "tree.h"
#include "report.h"
#include "fold.h"

var
    tree_break: integer := 0; /* .data */
    tree_mark: integer;
    tree_counter: integer;
    label_id_counter: integer;
    tree_heap: pointer;
    addr_dtype : Datatype;


function ivalue(Dtype: Datatype; dwval_l: integer; dwval_h: integer): pointer; forward;

procedure initialize_tree();
begin
    tree_mark := 0;
    tree_counter := 0;
    label_id_counter := 31;
end;

function gen_label_id(): integer;
begin
    label_id_counter := label_id_counter + 1;
    gen_label_id := label_id_counter;
end;

function new_tree(): pointer;
var
    p_Tree: ^Tree;
begin
    p_Tree := alloc_new(sizeof(Tree), tree_heap);
    
    tree_counter := tree_counter + 1;    
    
    p_Tree^.unk10 := tree_counter;
    p_Tree^.next := nil;
    p_Tree^.prior := nil;
    p_Tree^.op1 := nil;
    p_Tree^.op2 := nil;    
    
    p_Tree^.ref_count := 1;
    p_Tree^.ref_count2 := 0;
    p_Tree^.reg := xnoreg;
    p_Tree^.unk18 := 0;
    p_Tree^.unk16 := 0;
    p_Tree^.mark := tree_mark;
    p_Tree^.visited := false;
    
    p_Tree^.u.Opc := Unop;
    p_Tree^.u.LexLev := 0;
    p_Tree^.u.Offset2 := 0;

    if (p_Tree^.unk10 = tree_break) then begin
        writeln(err, "BPT here");
    end;

    return p_Tree;
end;

procedure build_u(var u: Bcrec);
var
    p_tree: ^tree;
begin
    p_tree := new_tree();
    p_tree^.u := u;
end;

procedure build_u1(var u: Bcrec; op1: ^Tree);
var
    p_tree: ^tree;
begin
    p_tree := new_tree();
    p_tree^.u := u;
    p_tree^.op1 := op1;
end;

procedure build_u2(var u: Bcrec; op1: ^Tree; op2: ^Tree);
var
    p_tree: ^tree;
begin
    p_tree := new_tree();
    p_tree^.u := u;
    p_tree^.op1 := op1;
    p_tree^.op2 := op2;
end;

function build_op(arg0: Uopcode): pointer;
var
    p_tree: ^tree;
begin
    p_tree := new_tree();
    p_tree^.u.Opc := arg0;
    return p_tree;
end;

function build_1op(uopc: Uopcode; op: ^tree): pointer;
var
    pTree: ^tree;
begin

    pTree := new_tree();
    pTree^.u.Opc := uopc;

    case op^.u.Opc of
        Uequ, {23}
        Ugeq, {28}
        Ugrt, {29}
        Uiequ,{2E}
        Uigeq,{2F}
        Uigrt,{30}
        Uileq,{34}
        Uiles,{35}
        Uineq,{38}
        Uinn, {3A}
        Uleq, {4D}
        Ules, {4E}
        Uneq: {5F}
            pTree^.u.Dtype := Ldt;
        Ulda: {47}
            pTree^.u.Dtype := addr_dtype;
        otherwise:
            pTree^.u.Dtype := op^.u.Dtype;
    end;
    pTree^.op1 := op;
    pTree^.u.Length := op^.u.Length;
    return pTree;
end;

function build_2op(Opc: Uopcode; op1: ^tree; op2: ^tree): pointer;
var
    pTree: ^tree;
begin

    pTree := new_tree();
    pTree^.u.Opc := Opc;

    if Opc <> Uujp then begin 
        case op1^.u.Opc of
            Uequ, {23}
            Ugeq, {28}
            Ugrt, {29}
            Uiequ,{2E}
            Uigeq,{2F}
            Uigrt,{30}
            Uileq,{34}
            Uiles,{35}
            Uineq,{38}
            Uinn, {3A}
            Uleq, {4D}
            Ules, {4E}
            Uneq: {5F}
                pTree^.u.Dtype := Ldt;
            Ulda: {47}
                pTree^.u.Dtype := addr_dtype;
            otherwise:
            begin
                pTree^.u.Dtype := op1^.u.Dtype;
            end;    
        end;
        pTree^.u.Length := op1^.u.Length;
    end;
    
    
    pTree^.op1 := op1;
    pTree^.op2 := op2;
    return pTree;
end;

procedure free_node(arg0: ^Tree);
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
        if(t^.op1 <> nil) then begin
            if((t^.u.Opc in [Uaent, Ucg2, Uclab, Uent, Ulab, Unop]) = 0)  then begin
                free_tree(t^.op1);
            end;
        end;


    if(t^.op2 <> nil) then begin
        if((t^.u.Opc in [Uaent, Ucg2, Uclab, Uent, Ufjp, Uijp, Ulab, Unop, Utjp, Uujp, Uxjp]) = 0) then begin
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
    if(arg0^.op1 <> nil) then begin
        if((arg0^.u.Opc in [Uaent, Ucg2, Uclab, Uent, Ulab, Unop]) = 0) then begin
            free_tree(arg0^.op1);
        end;
    end;

    if(arg0^.op2 <> nil) then begin
        if((arg0^.u.Opc in [Uaent, Ucg2, Uclab, Uent, Ufjp, Uijp, Ulab, Unop, Utjp, Uujp, Uxjp]) = 0) then begin
            free_tree(arg0^.op2);
        end;
    end;

    arg0^.op1 := nil;
    arg0^.op2 := nil;
    arg0^.u.Opc := Unop;
end;

function dup_tree(arg0 : ^tree): pointer;
var
    ret : pointer;
begin
    if (is_constant(arg0) <> false) then begin
        if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) then begin
            ret := ivalue(arg0^.u.Dtype, arg0^.u.Constval.dwval_h, arg0^.u.Constval.dwval_l);
        end else begin
            ret := ivalue(arg0^.u.Dtype, 0, arg0^.u.Constval.Ival)
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
    p_tree: ^tree;
begin
    p_tree := new_tree();
    p_tree^.u.Opc := Uldc;
    p_tree^.u.Dtype := Dtype;
    
    if (Dtype in [Idt, Kdt, Wdt]) then begin
        p_tree^.u.Constval.dwval_l:= dwval_h;
        p_tree^.u.Constval.dwval_h:= dwval_l;
        p_tree^.u.Length := 8;
    end else begin
        p_tree^.u.Constval.Ival := dwval_h;
        p_tree^.u.Length := 4;
    end;

    return p_tree;
end;

function dwvalue(Dtype: Datatype; arg1: integer64): pointer;
var
    temp_v0: ^tree;
begin
    temp_v0 := new_tree();
    temp_v0^.u.Opc := Uldc;
    temp_v0^.u.Dtype := Dtype;

    { Check for 64 bit data types
        Idt -> s64
        Kdt -> u64
        Wdt -> s64*
    }
    
    if (Dtype in [Idt, Kdt, Wdt]) then begin
        temp_v0^.u.Constval.dwval := arg1;
        temp_v0^.u.Length := 8;
    end else begin
        temp_v0^.u.Constval.dwval_h := arg1;
        temp_v0^.u.Length := 4;
    end;


    return temp_v0;
end;

function rvalue(Dtype: Datatype; arg1: String): pointer;
var
    p_tree: ^tree;
    temp_v0_2: stringtextptr;
    len: cardinal;
    
begin
    p_tree := new_tree();
    p_tree^.u.Opc := Uldc;
    p_tree^.u.Dtype := Dtype;
    p_Tree^.u.Length := 4;

    if (Dtype = Qdt) then begin
        p_Tree^.u.Length := 8;
    end;

    len := 1;
    while (arg1[len] <> ' ') do begin
        len := len + 1;
    end;
    
    p_tree^.u.Constval.Ival := len - 1;    
    new(temp_v0_2);
    p_tree^.u.Constval.chars := temp_v0_2;

    if (temp_v0_2 = nil) then begin
        report_error(Internal, 377, "tree_utils.p", "Insufficiant memory");
    end else begin
        for len := 1 to len - 1 do begin
            p_tree^.u.Constval.chars^.ss[len] := arg1[len];
        end;
    end;

    return p_tree;
end;

function is_zero(arg0: ^Tree): boolean;
begin
    if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) then begin
        is_zero := boolean((arg0^.u.Opc = Uldc) and (arg0^.u.Constval.dwval_h = 0) and (arg0^.u.Constval.dwval_l = 0));
    end else 
    
    is_zero := (arg0^.u.Opc = Uldc) and ((arg0^.u.Constval.Ival = 0));
end;

function is_ivalue(arg0: ^tree; arg1: integer; arg2: integer): boolean;
begin
    return is_constant(arg0) and (arg0^.u.Constval.Ival >= arg1) and  (arg2 >= arg0^.u.Constval.Ival);
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

function const_equal(arg0: ^Tree; arg1: ^Tree): boolean;

    function func_0044AED0(): boolean;
    var
        len: cardinal;
    begin
        for len := 1 to arg0^.u.Constval.Ival do begin
            if (arg0^.u.Constval.chars^.ss[len] <> arg1^.u.Constval.chars^.ss[len]) then begin
                return false;
            end;
        end;
        return true;
    end;
    
begin
    if ((arg0^.u.Opc <> Uldc) or (arg1^.u.Opc <> Uldc)) then begin
        return false;
    end;

    if (((arg0^.u.Dtype in [Idt, Kdt, Wdt]) and (arg1^.u.Dtype = arg0^.u.Dtype) and 
        (arg0^.u.Constval.dwval = arg1^.u.Constval.dwval) ))  then begin
        return true;
    end;

    if ((arg0^.u.Dtype in [Adt, Hdt, Jdt, Ldt]) and (arg1^.u.Dtype = arg0^.u.Dtype) and 
        (arg0^.u.Constval.Ival = arg1^.u.Constval.Ival)) then begin
        return true;
    end;

    if ((arg0^.u.Dtype in [Qdt, Rdt, Xdt]) and (arg1^.u.Dtype = arg0^.u.Dtype) and 
        (arg0^.u.Constval.Ival = arg1^.u.Constval.Ival) and (func_0044AED0())) then begin
        return true;
    end;

    return false;
end;
