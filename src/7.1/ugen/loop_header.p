#include "common.h"
#include "report.h"
#include "tree.h"
#include "tree_utils.h"

var
    pay: extern cardinal;
    current_line: extern integer;

    {.data}
    stop_ops: set of Uopcode := [Uaent, Uclab, Udef, Uent, Uoptn, Uregs, Uvreg, Uxjp];
    not_real_stms: set of Uopcode := [Ubgnb, Ucomm, Uendb, Uloc, Unop];

    inverse: array [First(Uopcode)..Last(Uopcode)] of Uopcode := (
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Uneq, Unop, Unop, Unop, Unop,
        Ules, Uleq, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Ugrt, Ugeq, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Uequ, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop, Unop,
        Unop, Unop, Unop, Unop, Unop, Unop,
    );

procedure insert(arg0: Ptree; arg1: Ptree);
begin
    arg0^.next := arg1;
    arg0^.prior := arg1^.prior;
    arg0^.prior^.next := arg0;
    arg1^.prior := arg0;
end;

procedure append(arg0: Ptree; arg1: Ptree);
begin
    arg0^.prior := arg1;
    arg0^.next := arg1^.next;
    arg1^.next := arg0;
    arg0^.next^.prior := arg0;
end;

function make_new_label(): pointer;
var
    sp20: Ptree;
begin
    sp20 := Ptree(build_op(Ulab));
    sp20^.u.I1 := gen_label_id();
    sp20^.u.Lexlev := 0;
    sp20^.u.Length := 0;
    return sp20;
end;

function make_new_jump(arg0: Ptree): pointer;
var
    ret: pointer;
begin
    ret := build_2op(Uujp, nil, arg0);
    return ret;
end;

function cmp_tree(arg0: Ptree; arg1: Ptree): boolean;
var
    spB8: integer;
begin
    spB8 := 1;

    arg0^.ref_count2 := arg0^.ref_count2 +1;
    arg1^.ref_count2 := arg1^.ref_count2 +1;

    if (arg0 = arg1) then begin
        return true;
    end;

    if (arg0^.u.Opc <> arg1^.u.Opc) then begin
        return false;
    end;

    case arg0^.u.Opc of
        Ulod:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and (arg0^.u.Mtype = arg1^.u.Mtype) and 
            (arg0^.u.I1 = arg1^.u.I1) and (arg0^.u.Offset = arg1^.u.Offset) and 
            (arg0^.u.Length = arg1^.u.Length) and (arg0^.u.Lexlev = arg1^.u.Lexlev);

            if (arg0^.u.Mtype = Rmt) then begin
                spB8 := 0;
            end;
        end;

        Ustr:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and (arg0^.u.Mtype = arg1^.u.Mtype) and 
            (arg0^.u.I1 = arg1^.u.I1) and (arg0^.u.Offset = arg1^.u.Offset) and 
            (arg0^.u.Length = arg1^.u.Length) and (arg0^.u.Lexlev = arg1^.u.Lexlev) and (cmp_tree(arg0^.op1, arg1^.op1));

            if (arg0^.u.Mtype = Rmt) then begin
                spB8 := 0;
            end;
        end;

        Upar:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and (arg0^.u.Mtype = arg1^.u.Mtype) and 
            (arg0^.u.I1 = arg1^.u.I1) and (arg0^.u.Offset = arg1^.u.Offset) and 
            (arg0^.u.Length = arg1^.u.Length) and (cmp_tree(arg0^.op1, arg1^.op1));
        end;

        Umst:
        begin
            cmp_tree := arg0^.u.Lexlev = arg1^.u.Lexlev;
        end;

        Ucup: {Call user procedure}
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and (arg0^.u.Lexlev = arg1^.u.Lexlev) and 
            (arg0^.u.I1 = arg1^.u.I1) and (arg0^.u.Pop = arg1^.u.Pop) and 
            (arg0^.u.Push = arg1^.u.Push) and (arg0^.u.Offset = arg1^.u.Offset);
        end;

        Urcuf:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and 
            (arg0^.u.I1 = arg1^.u.I1) and (arg0^.u.Pop = arg1^.u.Pop) and 
            (arg0^.u.Push = arg1^.u.Push) and (arg0^.u.Offset = arg1^.u.Offset);
        end;

        Uicuf:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and 
             (arg0^.u.Pop = arg1^.u.Pop) and 
            (arg0^.u.Push = arg1^.u.Push) and (arg0^.u.Offset = arg1^.u.Offset) and (cmp_tree(arg0^.op1, arg1^.op1));
        end;

        Utjp,
        Ufjp:
        begin
            cmp_tree := cmp_tree(arg0^.op1, arg1^.op1);
        end;

        Uujp:
        begin
            cmp_tree := cmp_tree(arg0^.op2, arg1^.op2);
        end;

        Uijp:
        begin
            cmp_tree := cmp_tree(arg0^.op1, arg1^.op1);
        end;

        Ucg2:
        begin
            cmp_tree := cmp_tree(arg0^.op1, arg1^.op1);
        end;

        Uldc:
        begin
            cmp_tree := const_equal(arg0, arg1);

            if (arg0^.u.Constval.Ival = 0) then begin
                spB8 := 0;
            end;
        end;

        Uilod:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and (arg0^.u.Offset = arg1^.u.Offset) and 
            (arg0^.u.Length = arg1^.u.Length) and (arg0^.u.Lexlev = arg1^.u.Lexlev) and 
            (cmp_tree(arg0^.op1, arg1^.op1));
        end;

        Uistr:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and 
            (arg0^.u.Offset = arg1^.u.Offset) and 
            (arg0^.u.Length = arg1^.u.Length) and (arg0^.u.Lexlev = arg1^.u.Lexlev) and 
            (cmp_tree(arg0^.op1, arg1^.op1)) and (cmp_tree(arg0^.op2, arg1^.op2));
        end;

        Uisld:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and (arg0^.u.Mtype = arg1^.u.Mtype) and 
            (arg0^.u.I1 = arg1^.u.I1) and (arg0^.u.Offset = arg1^.u.Offset) and 
            (arg0^.u.Length = arg1^.u.Length) and (arg0^.u.Lexlev = arg1^.u.Lexlev) and
            (cmp_tree(arg0^.op1, arg1^.op1));
        end;

        Uisst:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and (arg0^.u.Mtype = arg1^.u.Mtype) and 
            (arg0^.u.I1 = arg1^.u.I1) and (arg0^.u.Offset = arg1^.u.Offset) and 
            (arg0^.u.Length = arg1^.u.Length) and (arg0^.u.Lexlev = arg1^.u.Lexlev) and 
            (cmp_tree(arg0^.op1, arg1^.op1)) and (cmp_tree(arg0^.op2, arg1^.op2));
        end;

        Ulda:
        begin
            cmp_tree := (arg0^.u.Mtype = arg1^.u.Mtype) and (arg0^.u.I1 = arg1^.u.I1) and 
            (arg0^.u.Offset = arg1^.u.Offset) and (arg0^.u.Length = arg1^.u.Length) and 
            (arg0^.u.Constval.Ival = arg1^.u.Constval.Ival);
            
        end;

        Ulca:
        begin
            cmp_tree := FALSE;
        end;

        Uabs,
        Ulnot,
        Uneg,
        Unot:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and (cmp_tree(arg0^.op1, arg1^.op1));
        end;
        
        Ucg1,
        Uadd,
        Uand,
        Udiv,
        Usub,
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
        Uxor:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and 
            (cmp_tree(arg0^.op1, arg1^.op1)) and 
            (cmp_tree(arg0^.op2, arg1^.op2));
        end;

        Ucvt,
        Urnd,
        Utyp:
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and (arg0^.u.Pop = arg1^.u.Pop) and cmp_tree(arg0^.op1, arg1^.op2);
        end;

        Uchkn,
        Uchkt:
        begin
            cmp_tree := cmp_tree(arg0^.op1, arg1^.op1);
        end;

        Uchkh, {Check higher}
        Uchkl: { Check lower}
        begin
            cmp_tree := (arg0^.u.Dtype = arg1^.u.Dtype) and (arg0^.u.Length = arg1^.u.Length) 
            and (cmp_tree(arg0^.op1, arg1^.op1));
        end;

        Uiequ,
        Uigeq,
        Uigrt,
        Uileq,
        Uiles,
        Uineq,
        Umov:
        begin
            cmp_tree := (arg0^.u.I1 = arg1^.u.I1) and (arg0^.u.Length = arg1^.u.Length) and 
            (cmp_tree(arg0^.op1, arg1^.op1)) and (cmp_tree(arg0^.op2, arg1^.op2));
        end;

        Ucia,
        Uclab,
        Unop,
        Uxjp:
        begin
            cmp_tree := false;
        end;

        Ulab:
        begin
            cmp_tree := true;
        end;

        Ulbdy: ; { missing return? }

        otherwise begin
            report_error(Internal, 247, "loop_header.p", "unknown u-code");
        end;
    end;

    pay := pay + spB8;
end;

function cmp_tree_again(arg0: Ptree; arg1: Ptree): boolean;
var
    temp_v0_2: Ptree;
begin
    if (arg0^.u.Opc = Ulab) then begin
        temp_v0_2 := arg1;
        while (temp_v0_2^.u.Opc = Ulab) do begin
            if (temp_v0_2 = arg0) then begin
                return true;
            end;

            temp_v0_2 := temp_v0_2^.prior;
        end;

        return false;
    end;

    if (arg1^.ref_count2 <> arg1^.ref_count) then begin
        return false;
    end;

    case arg0^.u.Opc of
        Ucup, 
        Ulca, 
        Ulda, 
        Uldc, 
        Ulod, 
        Umst, 
        Urcuf:
        begin
            return true;
        end;
        Ucg2, 
        Uchkh,
        Uchkl,
        Uchkn,
        Uchkt,
        Uabs,
        Ucvt, 
        Uicuf,
        Uijp, 
        Uilod,
        Uisld,
        Ulnot,
        Uneg, 
        Unot, 
        Upar, 
        Urnd, 
        Utyp, 
        Ustr: 
        begin
            return cmp_tree_again(arg0^.op1, arg1^.op1);
        end;
        Uujp: 
            return cmp_tree_again(arg0^.op2, arg1^.op2);
        Ucg1, 
        Uadd, 
        Uand, 
        Udiv, 
        Uequ, 
        Ufjp, 
        Ugeq, 
        Ugrt, 
        Uiequ,
        Uigeq,
        Uigrt,
        Uileq,
        Uiles,
        Uineq,
        Uior, 
        Uisst,
        Uistr,
        Uleq, 
        Ules, 
        Umax, 
        Umin, 
        Umod, 
        Umov, 
        Umpy, 
        Uneq, 
        Urem, 
        Ushl, 
        Ushr, 
        Usub, 
        Utjp, 
        Uxor: 
        begin
            return cmp_tree_again(arg0^.op1, arg1^.op1) and cmp_tree_again(arg0^.op2, arg1^.op2);
        end;

        otherwise:
        begin
            report_error(Internal, 299, "loop_header.p", "unknown u-code");
            return false;
        end;
    
    end;
    
    
    return false;
end;

procedure move_label(arg0: Ptree; arg1: Pointer);
begin
    arg0^.prior^.next := arg0^.next;
    arg0^.next^.prior := arg0^.prior;
    insert(arg0, arg1);
end;

function get_prior_stm(arg0: Ptree): pointer;
begin
    arg0 := arg0^.prior;
    
    while ((arg0^.u.Opc in not_real_stms)) do begin
        arg0 := arg0^.prior;
    end;

    return arg0;
end;

function get_prior_stm1(arg0: Ptree): pointer;
begin
    arg0 := arg0^.prior;
    
    while ((arg0^.u.Opc in not_real_stms) or (arg0^.u.Opc = Ulab)) do begin
        arg0 := arg0^.prior;
    end;

    return arg0;
end;

function find_br(arg0: Ptree): pointer;
var
    var_v1: Ptree;
begin
    var_v1 := arg0^.op2;

    while not (var_v1^.u.Opc in [Ufjp, Utjp]) do begin
        if (var_v1 = arg0) or ((not (var_v1^.u.Opc in not_real_stms)) and (var_v1^.u.Opc <> Ulab)) then begin
            return nil;
        end;
        var_v1 := var_v1^.prior;
    end;
    return var_v1;
end;

procedure match_uconds(arg0: Ptree);
label found;
var
    var_s1: Ptree;
    var_s3: Ptree;
    var_s2: Ptree; {Probably real}
    var_s6: Ptree;
    var_s7: boolean;
    var_s0: Ptree;
begin
    var_s0 := arg0;
    var_s6 := arg0^.op2;
    var_s7 := false;

    while (true) do begin
        var_s6 := get_prior_stm1(var_s6);
        var_s0 := get_prior_stm(var_s0);
    
        while (var_s0^.u.Opc = Ulab) do begin
            if (var_s0 = arg0^.op2) then begin
                goto found;
            end;
            var_s0 := get_prior_stm(var_s0);
        end;

        if (var_s6 = arg0) or (var_s6^.u.Opc in stop_ops) or (var_s0^.u.Opc in stop_ops) then begin
            break;
        end;

        if not cmp_tree(var_s0, var_s6) then begin;
            break;
        end;

        var_s7 := true;
    end;

found:
    if (var_s7) then begin
        var_s3 := arg0^.op2;
        var_s2 := arg0;
        var_s7 := false;

        while ((var_s3 <> var_s6)) do begin
            var_s1 := var_s3;
            var_s3 := get_prior_stm(var_s3);

            while (var_s3^.u.Opc = Ulab) do begin
                var_s1 := var_s3;
                var_s3 := get_prior_stm(var_s3);
            end;

            var_s2 := get_prior_stm(var_s2);

            while (var_s2^.u.Opc = Ulab) do begin
                var_s0 := var_s2;
                var_s2 := get_prior_stm(var_s0);
                move_label(var_s0, var_s1);
            end;

            if (var_s3 = var_s6) or not cmp_tree_again(var_s2, var_s3) then break;

            var_s7 := true;
        end;

        if (var_s7) then begin
            var_s0 := arg0;
            while (var_s0 <> var_s2) do begin
                delete_statement(var_s0);
                var_s0 := get_prior_stm(var_s0);
            end;

            var_s6 := make_new_label();
            append(make_new_jump(var_s6), var_s2);
            append(var_s6, var_s3);
            
        end;
    end;
end;

function cmp_br(arg0: Ptree; arg1: Ptree): boolean;
begin
    arg0^.ref_count2 := succ(arg0^.ref_count2);
    arg1^.ref_count2 := succ(arg1^.ref_count2);
    

    arg0^.op1^.ref_count2 := succ(arg0^.op1^.ref_count2);
    arg1^.op1^.ref_count2 := succ(arg1^.op1^.ref_count2);

    if ((arg0^.op1^.u.Opc in [Uequ, Ugeq, Ugrt, Uleq, Ules, Uneq]) and (arg1^.op1^.u.Opc in [Uequ, Ugeq, Ugrt, Uleq, Ules, Uneq])) then begin
        
        if ((arg0^.u.Opc = arg1^.u.Opc) and (arg0^.op1^.u.Opc = inverse[arg1^.op1^.u.Opc]) or
            (arg0^.u.Opc <> arg1^.u.Opc) and (arg0^.op1^.u.Opc = arg1^.op1^.u.Opc)) then begin
            return (cmp_tree(arg0^.op1^.op1, arg1^.op1^.op1) and (cmp_tree(arg0^.op1^.op2, arg1^.op1^.op2)));
        end;
    end else begin
        return (arg0^.u.Opc <> arg1^.u.Opc) and (cmp_tree(arg0^.op1, arg1^.op1));
    end;
    
    return false;
end;

procedure match_conds(arg0: Ptree);
var
    var_s1: Ptree; {s0} 
    var_s3: Ptree; {s4} 
    var_s2: Ptree; {s2}
    var_s6: Ptree; {s5}
    var_s0: Ptree; {s1}
    temp_v0: Ptree; {s3}
begin
    temp_v0 := find_br(arg0);
    pay := 0;

    if ((temp_v0 <> nil) and (find_br(temp_v0) = arg0) and (cmp_br(arg0, temp_v0))) then begin
        var_s0 := arg0;
        var_s6 := temp_v0;

        while true do begin
            var_s6 := get_prior_stm1(var_s6);
            var_s0 := get_prior_stm1(var_s0);
    
            if ((var_s6^.u.Opc in stop_ops) or (var_s0^.u.Opc in stop_ops) or not (cmp_tree(var_s0, var_s6))) then begin
                break;
            end;
        end;

        if (pay >= 3) then begin
            var_s2 := arg0;
            var_s3 := temp_v0;
            if (cmp_tree_again(var_s2^.op1, var_s3^.op1)) then begin 
                while ((var_s3 <> var_s6)) do begin
                    var_s1 := var_s3;
                    var_s3 := get_prior_stm(var_s3);

                    while (var_s3^.u.Opc = Ulab) do begin
                        var_s1 := var_s3;
                        var_s3 := get_prior_stm(var_s3);
                    end;

                    var_s2 := get_prior_stm(var_s2);

                    while (var_s2^.u.Opc = Ulab) do begin
                        var_s0 := var_s2;
                        var_s2 := get_prior_stm(var_s0);
                        move_label(var_s0, var_s1);
                    end;

                    if (var_s3 = var_s6) or not cmp_tree_again(var_s2, var_s3) then break;
                end;

                var_s0 := arg0;
                while (var_s0 <> var_s2) do begin
                    delete_statement(var_s0);
                    var_s0 := get_prior_stm(var_s0);
                end;

                if (var_s0 <> nil) then begin end; { Fake match }

                var_s6 := make_new_label();
                append(make_new_jump(var_s6), var_s2);
                append(var_s6, var_s3);
                
            end;
        end;
    end;
end;

procedure cross_jump(arg0: Ptree);
var
    i: cardinal;
begin
    while (arg0 <> nil) do begin
        case arg0^.u.Opc of
            Uloc:
            begin
                current_line := arg0^.u.Length;
            end;

            Uclab:
            begin
                for i := 1 to arg0^.u.Length do begin
                    arg0 := arg0^.next;
                end;
            end;

            Uujp:
            begin
                match_uconds(arg0);
            end;

            Ufjp,
            Utjp:
            begin
                match_conds(arg0);
            end;

            otherwise:;
        end;
        arg0 := arg0^.next;
    end;
end;