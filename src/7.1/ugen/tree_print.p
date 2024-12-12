#include "tree.h"

type
    ugen_ucode_string =  packed array [1..4] of char;

var
    dtype_name: array [first(Datatype)..last(Datatype)] of char;
    mtype_name: array [first(Memtype)..last(Memtype)] of char;
    opc_name: array [first(Uopcode)..last(Uopcode)] of ugen_ucode_string;

{External}
function next_mark(): integer; external;

{Functions in this file but not defined (non_matching)..}
procedure print_ucode(pFile: ^Text; var u: Bcrec); external;
procedure print_node_1(pFile: ^Text; arg1: ^Tree; arg2: cardinal); external;

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

#ifdef NON_MATCHING
procedure print_ucode(pFile: ^Text; var u: Bcrec);
begin
    write(pFile^, ' ',  opc_name[u.Opc]:0);

    /* TODO: Match with the proper set (D_10016F1C) */
    if (u.Opc in [Uabs..Uirsv]) then begin
        write(pFile^, " dtype=", dtype_name[u.Dtype]);
    end;

    /* TODO: Match with the proper set (D_10016F08) */
    if (u.Opc in [Uabs..Uirsv]) then begin
        write(pFile^, " dtype2=",  dtype_name[u.Dtype2]);
    end;

    /* TODO: Match with the proper set (D_10016EF4) */
   if (u.Opc in [Uabs..Uirsv]) then begin
        write(pFile^, " mtype=", mtype_name[u.Mtype]);
    end;

    /* TODO: Match with the proper set (D_10016EE0) */
   if (u.Opc in [Uabs..Uirsv]) then begin
        write(pFile^, " lexlev=", u.lexlev);
    end;

    /* TODO: Match with the proper set (D_10016ECC) */
   if (u.Opc in [Uabs..Uirsv]) then begin
        write(pFile^, " i1=", u.I1);
    end;

 /* TODO: Match with the proper set (D_10016ECC) */
   if (u.Opc in [Uabs..Uirsv]) then begin
        write(pFile^, " blockno=", u.I1);
    end;

    if (u.Opc in [Uabs..Uirsv]) then begin
        write(pFile^, " length=", u.Length);
    end;

    if (u.Opc in [Uabs..Uirsv]) then begin
        write(pFile^, " offset=",  u.Offset);
    end;

    /* TO CHECK */
    if (u.Opc in [Uabs..Uirsv]) then begin
        write(pFile^, " offset2=", u.Offset2);
    end;

    /* TO CHECK */
    if (u.Opc in [Uabs..Uent]) then begin
        write(pFile^, " push=", u.Push);
        write(pFile^, " pop=", u.Pop);

        if (u.Opc in [Uabs..Uirsv]) then begin
            write(pFile^, " external=", u.Extrnal);
        end;
    end;

    if ((u.Opc = Ucia) and (u.Opc = Uldc)) then begin
        write(pFile^, " ival=",  u.Initval.ival);
    end else 

    if (u.Dtype in [Idt, Kdt]) then begin
        write(pFile^, " 64-bit-ival= ", u.Initval.ival);
        write(pFile^, ' ', u.Initval.ival);
    end;

    write(pFile^, " ival=", u.Initval.ival:1);
end;
#else
{GLOBAL_ASM("asm/7.1/functions/ugen/tree_print/print_ucode.s")}
#endif

#ifdef NON_MATCHING
procedure print_node_1(pFile: ^Text; arg1: ^Tree; arg2: cardinal);
begin
    write(pFile^, rshift(arg1^.unk10, 8):6, chr(9));
    indent_tree(pFile, arg2 * 2);
    print_ucode(pFile, arg1^.u);

    if ((arg1^.ref_count <> 1) ) then begin
        write(pFile^, " ref_count=", arg1^.ref_count:1);
    end;

   if (1 <= arg1^.ref_count2) then begin
        write(pFile^, " ref_count2=", integer(arg1^.ref_count2):1);
    end;

    if (arg1^.reg mod 2 = 0) then begin
        write(pFile^, " Not visited");
    end;

    if (arg1^.reg <> xnoreg) then begin
        write(pFile^, " reg=", arg1^.reg);
    end;

    if (arg1^.op1 <> nil) then begin
        write(pFile^, " op1=", rshift(arg1^.prior^.unk10, 8):1);
    end;

    if (arg1^.op2 <> nil) then begin
        write(pFile^, " op2=", rshift(arg1^.prior^.unk10, 8):1);
    end;

    if (arg1^.next <> nil) then begin
        write(pFile^, " next=", rshift(arg1^.prior^.unk10, 8):1);
    end;

    if (arg1^.prior <> nil) then begin
        write(pFile^, " prior=", rshift(arg1^.prior^.unk10, 8):1);
    end;

    writeln(pFile^);        
end;
#else
{GLOBAL_ASM("asm/7.1/functions/ugen/tree_print/print_node_1.s")}
#endif

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
                    if ((sub_arg0^.u.Opc in [Uaent, Ucg2, Uclab, Uent, Ufjp, Uijp, Ulab, Unop, Utjp, Uujp, Uxjp]) = false) then begin
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
