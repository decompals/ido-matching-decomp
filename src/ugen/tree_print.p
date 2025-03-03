#include "tree.h"

type
    ugen_ucode_string =  packed array [1..4] of char;

var
    opc_name: array [first(Uopcode)..last(Uopcode)] of ugen_ucode_string := [
        "abs",  "add", "adj", "aent", "and", "aos", "asym", "bgn",
        "bgnb", "foo", "cond", "lvar", "chkh", "chkl", "chkn", "chkt",
        "cia",  "clab", "foo", "comm", "csym", "foo", "foo", "cup",
        "cvt",  "cvtl", "dec", "def", "dif", "div", "dup", "end",
        "endb", "ent", "eof", "equ", "esym", "foo", "fjp", "fsym",
        "geq",  "grt", "gsym", "hsym", "icuf", "idx", "iequ", "igeq",
        "igrt", "ijp", "ilda", "foo", "ileq", "iles", "ilod", "inc",
        "ineq", "init", "inn", "int", "ior", "isld", "isst", "istr",
        "foo", "ixa", "lab", "foo", "lbdy", "foo", "lca", "lda",
        "ldap", "ldc", "foo", "ldsp", "foo", "leq", "les", "lex",
        "lnot", "loc", "lod", "lsym", "foo", "max", "min", "mod",
        "mov", "foo", "mpmv", "mpy", "mst", "mus", "neg", "neq",
        "nop", "not", "odd", "optn", "par", "pdef", "pmov", "pop",
        "regs", "rem", "ret", "rlda", "rldc", "rlod", "rnd", "rpar",
        "rstr", "sdef", "sgs", "shl", "shr", "sign", "sqr", "sqrt",
        "foo", "foo", "stp", "str", "stsp", "sub", "swp", "tjp",
        "foo", "foo", "foo", "foo", "foo", "foo", "typ", "foo",
        "ujp", "foo", "uni", "vreg", "xjp", "xor", "foo", "mtag",
        "alia", "foo", "foo", "irld", "irst", "ldrc", "msym", "rcuf",
        "ksym", "foo", "foo", "foo"
    ];
    dtype_name: array [first(Datatype)..last(Datatype)] of char := [
        "A", "C", "F", "G", "H", "I", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "W", "X", "Z"
    ];
    mtype_name: array [first(Memtype)..last(Memtype)] of char := [
        "Z", "M", "P", "R", "S", "A", "T", "K"
    ];
    unused: integer := 0;
    
{External}
function next_mark(): integer; external;

procedure indent_tree(pFile: ^text; arg1: cardinal);
var 
    temp: cardinal;
    var_s0: cardinal;
begin
    temp :=  rshift(arg1, 3);

    if (temp <> 0) then begin
        var_s0 := temp;
        repeat begin
            write(pFile^, chr(9));        
            var_s0 := pred(var_s0);
        end until (var_s0 = 0);
    end;
    write(pFile^, ' ':arg1&7);
end;

procedure print_ucode(pFile: ^Text; var u: Bcrec);
begin
    write(pFile^, '',  opc_name[u.Opc]:0);

    if (u.Opc in [Uabs, Uadd, Uadj, Uaent, Uand, Uchkh, Uchkl, Ucia,
                  Ucup, Ucvt, Ucvtl, Udec, Udif, Udiv, Udup, Uent,
                  Uequ, Ugeq, Ugrt, Uicuf, Uidx, Uiequ, Uigeq, Uigrt,
                  Uilda, Uileq, Uiles, Uilod, Uinc, Uineq, Uinit, Uinn,
                  Uint, Uior, Uisld, Uisst, Uistr, Uixa, Ulca, Uldap,
                  Uldc, Uldsp, Uleq, Ules, Ulnot, Ulod, Umax, Umin,
                  Umod, Umov, Umpmv, Umpy, Umus, Uneg, Uneq, Unot,
                  Uodd, Upar, Updef, Upmov, Upop, Urem, Urlod, Urnd,
                  Urpar, Urstr, Usgs, Ushl, Ushr, Usign, Usqr, Ustr,
                  Usub, Uswp, Utyp, Uuni, Uvreg, Uxjp, Uxor, Uirld,
                  Uirst, Uldrc, Urcuf]) then begin
        write(pFile^, " dtype=", dtype_name[u.Dtype]);
    end;

    if (u.Opc in [Ucvt, Urnd, Uswp, Utyp]) then begin
        write(pFile^, " dtype2=",  dtype_name[u.Dtype2]);
    end;

    if (u.Opc in [Udef, Uilda, Uinit, Uisld, Uisst, Ulda, Ulod, Umpmv,
                  Upar, Updef, Upmov, Urlod, Urpar, Urstr, Ustr, Uvreg]) then begin
        write(pFile^, " mtype=", mtype_name[u.Mtype]);
    end;

    { Uabs shouldn't be in this set, but removing it breaks both code and data a lot }
    if (u.Opc in [Uabs, Uent, Uilod, Uistr, Ulab, Ulbdy, Ulex, Uloc, Ulod,
                  Umov, Umpmv, Umst, Upmov, Uregs, Urlod, Urpar, Urstr,
                  Ustr, Umtag, Ualia, Uirld, Uirst]) then begin
        write(pFile^, " lexlev=", u.lexlev:1);
    end;

    if (u.Opc in [Uclab, Ufjp, Ulab, Utjp, Uujp]) then begin
        write(pFile^, " i1=", u.I1:1);
    end;

    if (u.Opc in [Uaent, Ubgn, Ubgnb, Uchkh, Uchkl, Ucsym, Ucup, Ucvtl,
                  Uendb, Uent, Uesym, Ufsym, Ugsym, Uilda, Uilod, Uinit,
                  Uinn, Uisld, Uisst, Uistr, Uixa, Ulca, Ulda, Ulex,
                  Uloc, Ulod, Ulsym, Umpmv, Upar, Updef, Upmov, Uregs,
                  Urlod, Urpar, Urstr, Usdef, Ustr, Uvreg, Umtag, Ualia,
                  Uirld, Uirst, Umsym, Urcuf, Uksym]) then begin
        write(pFile^, " blockno=", u.I1:1);
    end;

    if (u.Opc in [Uadj, Ubgn, Ucia, Uclab, Ucsym, Udec, Udef, Udif,
                  Ufsym, Ugsym, Uiequ, Uigeq, Uigrt, Uilda, Uileq, Uiles,
                  Uilod, Uinc, Uineq, Uinit, Uinn, Uint, Uisld, Uisst,
                  Uistr, Ulab, Ulca, Ulda, Uldc, Ulod, Ulsym, Umov,
                  Umpmv, Umus, Uoptn, Upar, Updef, Upmov, Uregs, Urlod,
                  Urpar, Urstr, Usdef, Usgs, Ustr, Uuni, Uvreg, Uxjp,
                  Uirld, Uirst, Uldrc]) then
    begin
        write(pFile^, " length=", u.Length:1);
    end;

    if (u.Opc in [Uadj, Ubgn, Uilda, Uilod, Uinit, Uisld, Uisst, Uistr,
                  Ulda, Ulod, Umpmv, Upar, Updef, Upmov, Uregs, Urlod, Urpar,
                  Urstr, Ustr, Uvreg, Uirld, Uirst]) then              
    begin
        write(pFile^, " offset=",  u.Offset:1);
    end;

    if (u.Opc in [Uilda, Uinit, Ulda, Upar, Updef, Uvreg]) then begin
        write(pFile^, " offset2=", u.Offset2:1);
    end;

    if (u.Opc in [Uaent, Ucup, Uent, Uicuf]) then begin
        write(pFile^, " push=", u.Push:1);
        write(pFile^, " pop=", u.Pop:1);

        if (u.Opc in [Uaent, Uent]) then begin
            write(pFile^, " external=", u.Extrnal:1);
        end;
    end;

    case u.Opc of
        Ucia:
            write(pFile^, " ival=",  u.Constval.ival:1);
        Uldc:
            begin
                if (u.Dtype in [Idt, Kdt]) then begin
                    write(pFile^, " 64-bit-ival= ", u.Constval.dwval_h:1, ' ', u.Constval.dwval_l:1);
                end else 
                    write(pFile^, " ival=", u.Constval.Ival:1);
            end;
        otherwise: 
    end;
end;

procedure print_node_1(pFile: ^Text; arg1: ^Tree; arg2: cardinal);
begin
    write(pFile^, arg1^.unk10:6, chr(9));
    indent_tree(pFile, arg2 * 2);
    print_ucode(pFile, arg1^.u);

    if ((arg1^.ref_count <> 1) ) then begin
        write(pFile^, " ref_count=", arg1^.ref_count:1);
    end;

   if (arg1^.ref_count2 <> 0) then begin
        write(pFile^, " ref_count2=", arg1^.ref_count2:1);
    end;

    if (arg1^.visited = false) then begin
        write(pFile^, " Not visited");
    end;

    if (arg1^.reg <> xnoreg) then begin
        write(pFile^, " reg=", arg1^.reg);
    end;

    if (arg1^.op1 <> nil) then begin
        write(pFile^, " op1=", arg1^.op1^.unk10:1);
    end;

    if (arg1^.op2 <> nil) then begin
        write(pFile^, " op2=", arg1^.op2^.unk10:1);
    end;

    if (arg1^.next <> nil) then begin
        write(pFile^, " next=", arg1^.next^.unk10:1);
    end;

    if (arg1^.prior <> nil) then begin
        write(pFile^, " prior=", arg1^.prior^.unk10:1);
    end;

    writeln(pFile^);        
end;

procedure print_node(pFile: ^Text; arg1: ^Tree);
begin
    print_node_1(pFile, arg1, 0);
end;

procedure print_tree(pFile: ^Text; arg1: ^tree; arg2: cardinal; arg3: cardinal);
var
    mark: integer;
    sp20: cardinal; /* sp - 8*/

    /* inner function */
    procedure func_00449D24(sub_arg0: ^Tree; sub_arg1: Cardinal);
    begin
        while (sub_arg0 <> nil) do begin
            if (sub_arg0^.unk17 = mark) then break;

            sub_arg0^.unk17 := mark;
            print_node_1(pFile, sub_arg0, sub_arg1);

            if (sub_arg1 < arg2) then begin
                if (sub_arg0^.op1 <> nil) then begin
                    if ((sub_arg0^.u.Opc in [Uaent, Ucg2, Uclab, Uent, Ulab, Unop]) = false) then begin
                        func_00449D24(sub_arg0^.op1, succ(sub_arg1));
                    end;
                end;

                        
                if (sub_arg0^.op2 <> nil) then begin
                    if ((sub_arg0^.u.Opc in [Uaent, Uclab, Uent, Ufjp, Ulab, Unop, Utjp, Uujp, Uxjp]) = false) then begin
                        func_00449D24(sub_arg0^.op2, succ(sub_arg1));
                    end;
                end;
            end;
    
            if (sp20 >= arg3) then break;

            sp20 := sp20 + 1;
            sub_arg0 := sub_arg0^.next;
        end;      
    end;

begin
    mark := next_mark();
    sp20 := 0;
    func_00449D24(arg1, 0);
end;

#ifdef NON_MATCHING
procedure debug_tree(arg0: ^tree);
begin
    print_tree(output, arg0, 20, 0);
end;
#else
GLOBAL_ASM("asm/7.1/functions/ugen/tree_print/debug_tree.s")
#endif
