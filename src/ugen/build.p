#include "common.h"
#include "cmplrs/uoptions.h"
#include "tree.h"
#include "tree_utils.h"
#include "fold.h"
#include "report.h"
#include "swap.h"
#include "symbol.h"
#include "cmplrs/uread.h"

procedure print_ucode(var f: Text; var u: Bcrec); external;

var
    domtag: boolean;
    label_hash_table: array [0..252] of Ptree;
    addr_dtype: Datatype;
    basicint: u8;
    current_line: integer;
    first_pmt_offset: integer;
    framesz_relocatable: s8;
    glevel: u8;
    has_cia_in_file: s8;
    ignore_vreg: s8;
    ls_stamp: integer;
    lsb_first: boolean;
    ms_stamp: integer;
    n_fp_parm_regs: integer;
    n_parm_regs: integer;
    non_local_mtag: integer;
    nooffsetopt: boolean;
    opcode_arch: u8;
    opt_parms: u8;
    pseudo_leaf: u8;
    resident_text: s8;
    reverse: extern array[Uopcode] of Uopcode;
    reversed_stack: boolean;
    similar_data_types: array[Datatype] of set of Datatype;
    similar_data_types_dw: array[Datatype] of set of Datatype;
    source_language: integer;
    stack_limit_bn: integer;
    syms: pointer;
    trap_to_compare: array[Utpeq..Utpne] of Uopcode := [Uneq, Ules, Uleq, Ugrt, Ugeq, Uequ];
    unitsperaddr: integer;
    use_fp: s8;
    will_use_real_fp_for_proc: s8;
    strp: Stringtextptr;


procedure set_domtag(arg0: boolean);
begin
    domtag := arg0;
end;

function get_domtag(): boolean;
begin
    get_domtag := domtag;
end;

function search_label(index: cardinal): pointer;
var
    label_hash_iterator: ptree;
begin
{ To note:
    Why does SGI Pascal generate this strange patern
        if index mod 253 then
            index := 253;   //then we have some cardinal vs integer issues
    }
    label_hash_iterator := label_hash_table[(index mod 253) & 255];
    while (label_hash_iterator <> nil)  do begin
        if (index = label_hash_iterator^.u.I1) then begin
            break;
        end;
        label_hash_iterator := label_hash_iterator^.op1;
    end;
    return label_hash_iterator;
end;

function find_label(arg0: cardinal): pointer;
var
    temp_v0: ^tree;
    var_v1: ^tree;
begin

    var_v1 := label_hash_table[(arg0 mod 253) & 255];
    while (var_v1 <> nil) do begin
        if (arg0 = var_v1^.u.I1) then begin
            return var_v1;
        end;
        var_v1 := var_v1^.op1;
    end;
    temp_v0 := build_op(Ulab);
    temp_v0^.u.Lexlev := 0;
    temp_v0^.u.Length := 0;
    temp_v0^.u.I1 := arg0;
    temp_v0^.op1 := label_hash_table[(arg0 mod 253) & 255];
    label_hash_table[(arg0 mod 253) & 255] := temp_v0;
    return temp_v0;
end;


procedure init_build();
begin
    new(strp);
end;

type
    UnkEnumA = (UNK_ENUM_A_0, UNK_ENUM_A_1, UNK_ENUM_A_2, UNK_ENUM_A_3, UNK_ENUM_A_4);
    UnkRec_1 = Record;
        unk_00: UnkEnumA; { 0x00 }
        dtype: Datatype; { 0x01 }
        offset: integer; { 0x04 }
        length: integer; { 0x08 }
    end;

/* Procedures */
function get_data_area(var arg0: Bcrec): u8; external;
procedure gen_sym(var u: Bcrec); external;
procedure add_init(var u: Bcrec); external;
procedure set_size(arg0: integer; arg1: cardinal); external;
procedure map_pdefs_to_regs(arg0: ^Tree; arg1: integer); external;
{function find_label(arg0: integer): pointer; external;}
function overlap(arg0: ^tree; arg1: ^tree): boolean; external;
function parm_reg(arg0: ^Tree): integer; external;


/* Variables */
#define CASE_OPC(x) (x)

function build_tree(verbose: boolean): pointer;
label binop_out;
var
    { Temp declaration.. }
    {sp164C: ^tree;}
    {v0_sp1648 : cardinal;}
    {pad16: integer16;}
    sp1648: 0..400;
    sp1004: array[1..400] of Ptree; {v064C}
    sp9C4: array[1..400] of integer; {v0C8C}
    sp384: array[1..400] of integer; {v012CC}
    sp1F7: array [1..400] of Datatype;
    sp1F4: ^tree; {v0145C}
    sp1F0: integer;
    sp1EC: integer;
    {var_a1: integer; }{pad1E8}
    {sp1E4: Stringtextptr;} {sp1C8.Initval.Chars}
    {sp1E0: integer;} {sp1C8.Initval.Ival}
    {sp1DC: Stringtextptr;} {sp1C8.Constval.Chars}
    {sp1D8: integer;} {sp1C8.Constval.Ival}
    {sp1D4: integer;} {sp1C8.Offset}
    {sp1D0: integer;} {sp1C8.Length}
    {sp1CC: integer;} {sp1C8.I1}
    var_s4: integer; {pad154}
    sp1C8: Bcrec;
    sp1C4: Stringtextptr;
    sp1C0: ^tree;
    sp1BC: ^tree;
    sp1B8: ^tree;
    sp1B4: ^tree;
    sp1B0: ^tree;
    sp1AC: ^tree;
    sp1A8: ^tree;
    sp1A4: ^tree;
    tree_s3: ^tree; {pad1A0}
    temp_fp: integer; {pad19C}
    tree_s0: ^tree; {pad198}
    temp_v0: integer; {pad194}
    var_s0: integer; {pad190}
    sp18C: integer;
    sp188: integer;
    sp184: integer;
    sp183: boolean;
    sp182: boolean;
    sp181: char;
    dtype_s1: Datatype;{pad180}
    sp17C: integer;
    sp17B: u8;
    sp174: cardinal;
    var_s1: cardinal; {pad170}
    tree_s2: ^tree; {pad16C}
    var_s5: integer; {pad168}
    sp167: boolean; {v014E9}
    sp166: boolean; {v014EA}
    sp165: boolean; {v014EB}
    sp164: boolean; {pad}
    sp160: integer;
    sp15F: boolean;
    sp158: integer;
var {extra var here makes sp128 initialize first}
    sp128: array [0..3] of UnkRec_1;
    sp127: boolean;
    
    { Inner functions }

    { Change tree? }
    procedure func_0040E238(arg0: ^Tree);
    begin
        sp1F4^.next := arg0;
        arg0^.prior := sp1F4;
        sp1F4 := arg0;
    end;

    procedure func_0040E24C(arg0: ^Tree);
    begin
        sp1F4^.next := arg0;
        arg0^.prior := sp1F4;

        while (arg0^.next <> nil) do begin
            arg0^.next^.prior := arg0;
            arg0 := arg0^.next;
        end;

        sp1F4 := arg0;
    end;

    procedure func_0040E280(arg0: ^Tree; arg1: ^Tree);
    var
        v0: ^Tree;
    begin
        v0 := arg0^.next;
        arg0^.next := arg1;

        while (arg1^.next <> nil) do begin
            arg1 := arg1^.next;
        end;

        arg1^.next := v0;
    end;

    procedure func_0040E2AC(arg0: 0..399 of integer16);
    var
        sp43: Datatype;
    begin
        if sp1F7[arg0] = Ldt then begin
            sp43 := Ldt;
        end else begin
            sp43 := Jdt;
        end;

        if sp1004[arg0] = nil then begin
            sp1004[arg0] := ivalue(sp43, 0, sp9C4[arg0]);
        end else begin
            if sp9C4[arg0] <> 0 then begin
                if (sp1004[arg0]^.u.Dtype in [Idt, Jdt, Kdt, Ldt]) then begin
                    if sp9C4[arg0] < 0 then begin
                        sp1004[arg0] := build_2op(Uadd, sp1004[arg0], ivalue(sp1004[arg0]^.u.Dtype, -1, sp9C4[arg0]));
                    end else begin
                        sp1004[arg0] := build_2op(Uadd, sp1004[arg0], ivalue(sp1004[arg0]^.u.Dtype, 0, sp9C4[arg0]));
                    end;
                end else begin
                    sp1004[arg0] := build_2op(Uadd, sp1004[arg0], ivalue(sp43, 0, sp9C4[arg0]));
                end;
                    sp1004[arg0]^.u.Lexlev := sp384[arg0];
            end;
        end;

        sp9C4[arg0] := 0;
        sp384[arg0] := 0;
    end;

    procedure func_0040E474(arg0: ^Tree);
    var
        i: integer;
        t1: integer;
        v0: integer;
    begin
        if sp166 then begin
            sp165 := True;
        end;

#line 415
        case arg0^.u.Opc of
            Ulod, Ustr: 
            begin
                v0 := abs(arg0^.u.Offset - first_pmt_offset);
                i := max(v0 div 4, 0);
                t1 := min((v0 + arg0^.u.Length - 1) div 4, 3);
                while i <= t1 do begin
                    case sp128[i].unk_00 of {7 lines between previous case and this case}
                       UNK_ENUM_A_0:
                        begin
                            sp128[i].unk_00 := UNK_ENUM_A_1;
                            sp128[i].dtype := arg0^.u.Dtype;
                            sp128[i].offset := arg0^.u.Offset;
                            sp128[i].length := arg0^.u.Length;
                        end;
                        
                        UNK_ENUM_A_1: 
                        if (sp128[i].dtype <> arg0^.u.Dtype) or 
                           (sp128[i].offset <> arg0^.u.Offset) or
                           (sp128[i].length <> arg0^.u.Length) then begin

                            sp128[i].unk_00 := UNK_ENUM_A_2;
                            
                            if lsb_first then begin
                                sp128[i].length := min(sp128[i].length, arg0^.u.Length);
                            end else if arg0^.u.Length + arg0^.u.Offset < sp128[i].length + sp128[i].offset then begin
                                sp128[i].length := arg0^.u.Length;
                                sp128[i].offset := arg0^.u.Offset;                                
                            end;

                            if not (arg0^.u.Dtype in [Jdt, Ldt]) then begin
                                sp128[i].dtype := arg0^.u.Dtype;
                            end;
                        end;

                        UNK_ENUM_A_2, UNK_ENUM_A_3: 
                        if (sp128[i].dtype <> arg0^.u.Dtype) or 
                           (sp128[i].offset <> arg0^.u.Offset) or
                           (sp128[i].length <> arg0^.u.Length) then begin
                            
                            if lsb_first then begin
                                sp128[i].length := min(sp128[i].length, arg0^.u.Length);
                            end else if arg0^.u.Length + arg0^.u.Offset < sp128[i].length + sp128[i].offset then begin
                                sp128[i].length := arg0^.u.Length;
                                sp128[i].offset := arg0^.u.Offset;                                
                            end;

                            if not (arg0^.u.Dtype in [Jdt, Ldt]) then begin
                                sp128[i].dtype := arg0^.u.Dtype;
                            end;
                        end;
                        
                        UNK_ENUM_A_4: ;
                    end;

                    if (arg0^.u.LexLev & 1) <> 0 then begin
                        sp128[i].unk_00 := UNK_ENUM_A_4;
                    end;
                    
                    i := i + 1;
                end;
            end;

            Ulda:
            begin
                v0 := abs(arg0^.u.Offset2 - first_pmt_offset);
                i := max(v0 div 4, 0);
                t1 := min((v0 + arg0^.u.Length - 1) div 4, 3);
                
                while i <= t1 do begin
                    sp128[i].unk_00 := UNK_ENUM_A_3;
                    sp128[i].dtype := arg0^.u.Dtype;
                    i := i + 1;
                end;
            end;
        end;

    end;

    function func_0040E884(arg0: ^Tree): boolean;
    var
        a1: integer;
        a3: integer;
        v02: cardinal;
        v1: integer;
        a1_length: integer;
    begin
        v1 := abs(arg0^.u.Offset - first_pmt_offset);
        a1 := v1 div 4;
        a3 := (v1 + arg0^.u.Length - 1) div 4;
        
        if (a1 < 0) or (a3 > 3) then begin
            return False;
        end;

        if sp128[a1].unk_00 = UNK_ENUM_A_4 then begin
            return False;
        end;

        case arg0^.u.Dtype of
            Jdt,
            Ldt:
            begin
                if a1 <> a3 then begin
                    return False;
                end;

                a1_length := sp128[a1].length;
                if (a1_length <> 4) and (not sp183) then begin
                    if lsb_first then begin
                        if (sp128[a1].offset <> arg0^.u.Offset) or (a1_length * 1 <> arg0^.u.Length) then begin
                            return False;
                        end;
                    end else if sp128[a1].offset + sp128[a1].length <> arg0^.u.Offset + arg0^.u.Length then begin
                        return False;
                    end;

                    arg0^.u.Offset := sp128[a1].offset;
                    arg0^.u.Length := a1_length;
                end;

                if sp128[a1].unk_00 = UNK_ENUM_A_3 then begin
                    return False;
                end;
            end;

            Adt,
            Fdt,
            Gdt,
            Hdt,
            Mdt,
            Rdt,
            Wdt:
            begin
                if ((a1 <> a3) or (sp128[a1].dtype <> arg0^.u.Dtype) or (sp128[a1].offset <> arg0^.u.Offset) or (sp128[a1].length <> arg0^.u.Length)) and not sp183 then begin
                    return false;
                end else if (sp128[a1].unk_00 = UNK_ENUM_A_3) then begin
                    return false; 
                end;
            end;

            Qdt:
            begin
                if ((a1 + 1 <> a3) or (sp128[a1].dtype <> Qdt) or (sp128[a1].offset <> arg0^.u.Offset) or (sp128[a1].length <> 8) or (sp128[a3].unk_00 = UNK_ENUM_A_2) or (sp128[a3].dtype <> Qdt) or (sp128[a3].offset <> arg0^.u.Offset) or (sp128[a3].length <> 8)) and not sp183 then begin
                    return False;
                end else if sp128[a1].unk_00 = UNK_ENUM_A_3 then begin
                    return false;
                end;
            end;

            otherwise return False;
        end;

        v02 := parm_reg(arg0);
        return ((basicint = 0) and (arg0^.u.Dtype in [Adt, Fdt, Gdt, Hdt, Jdt, Ldt])) or
               ((basicint = 1) and (arg0^.u.Dtype in [Fdt, Gdt, Hdt, Idt, Kdt, Wdt])) or
               ((arg0^.u.Dtype = Mdt) and (arg0^.u.Length = unitsperaddr)) or
               ((arg0^.u.Dtype = Sdt) and (arg0^.u.Length <= unitsperaddr)) or
               sp183 or
               ((arg0^.u.Dtype in [Qdt, Rdt, Xdt]) and (v02 >= 44) and (v02 <= cardinal(42 + 2 * n_fp_parm_regs)));
    end;
    
    procedure func_0040EC54(arg0: ^tree);
    var
        var_s0: ^tree;
        sp2C : ^tree;
    begin
        if sp1BC = nil then begin
            sp1BC := arg0;
            return;
        end;
        sp2C := nil;
        var_s0 := sp1BC;
        if (arg0^.u.Mtype = Pmt) then begin
            while (var_s0 <> nil) and (var_s0^.u.Mtype = Pmt) do begin
                if overlap(arg0, var_s0) then begin
                    if (var_s0^.u.Offset2 = -1) and (arg0^.u.Offset2 <> -1) then begin
                        var_s0^.u.Offset2 := arg0^.u.Offset2;
                    end;
                    return;
                end;
                if reversed_stack then begin if (var_s0^.u.Offset < arg0^.u.Offset) then break;
                end else if (arg0^.u.Offset < var_s0^.u.Offset) then break;
                
                sp2C := var_s0;
                var_s0 := var_s0^.next;
            end;
        end else begin
            while (var_s0 <> nil) and (var_s0^.u.Mtype = Pmt) do begin
                sp2C := var_s0;
                var_s0 := var_s0^.next;
            end;
            if reversed_stack then begin
                while (var_s0 <> nil) and (var_s0^.u.Offset < arg0^.u.Offset) do begin
                    sp2C := var_s0;
                    var_s0 := var_s0^.next;
                end;
            end else while (var_s0 <> nil) and (arg0^.u.Offset < var_s0^.u.Offset) do begin
                sp2C := var_s0;
                var_s0 := var_s0^.next;
            end;
            if not (var_s0 <> nil) or (arg0^.u.Offset <> var_s0^.u.Offset) or (arg0^.u.I1 <> var_s0^.u.I1) then begin
                assert(((var_s0 = nil)) or (arg0^.u.Offset <> var_s0^.u.Offset) or (arg0^.u.I1 <> var_s0^.u.I1));
            end else return;
        end;
        arg0^.next := var_s0;
        if sp2C = nil then begin 
            sp1BC := arg0;
        end else begin
            sp2C^.next := arg0;
        end;
    end;

    procedure func_0040EED4();
    var
    s0: ^tree;
    v0: ^tree;
    begin
        s0 := sp1B8;
        while s0 <> nil do begin
            if func_0040E884(s0) then begin
                v0 := build_u(s0^.u);
                v0^.u.Opc := Uvreg;
                v0^.u.Lexlev := 0;
                v0^.u.Offset2 := s0^.u.Offset2;
                func_0040EC54(v0);
            end;
            s0:= s0^.next;
        end;
    end;

    procedure func_0040EF8C(arg0: ^tree);
    begin
        while arg0 <> nil do begin
            sp158 := sp158 + 1;
            arg0^.u.aryoff := sp158;
            arg0 := arg0^.next;
        end;
    end;

    

    procedure func_0040EFBC(arg0: ^tree);
    var
        mtag: ^tree;
        t: ^tree;
        s2 : integer;
    begin
        mtag := nil;
        while arg0 <> nil do begin
            if arg0^.u.Opc = Ufsym then begin
                set_mtag(arg0^.u.I1, sp158);
                arg0^.u.Lexlev := 6;
            end;
            arg0^.u.I1 := sp158;
            arg0^.u.Opc := Umtag;
            mtag := arg0;
            arg0 := arg0^.next;
        end;
        if non_local_mtag = 0 then begin
            s2 := sp158;
            t := new_tree(); 
            t^.u.Opc := Umtag;
            t^.u.Lexlev := 3;
            t^.u.I1 := s2;
            non_local_mtag := sp158;
            sp158 := sp158 + 1;
            mtag^.next := t;
        end;
    end;

    procedure func_0040F0B8(arg0: ^tree);
    var
        v0: ^tree;
        next: ^tree;
    begin
        if sp1B8 = nil then begin
            sp1B8 := arg0;
            sp1B4 := arg0;
            return;
        end;
        if arg0^.u.Offset = sp1B8^.u.Offset then return;
        if reversed_stack then begin
            if (sp1B8^.u.Offset < arg0^.u.Offset) then begin
                arg0^.next := sp1B8;
                sp1B8 := arg0;
                return;
            end;
        end else if arg0^.u.Offset < sp1B8^.u.Offset then begin
            arg0^.next := sp1B8;
            sp1B8 := arg0;
            return;
        end else if arg0^.u.Offset = sp1B4^.u.Offset then begin 
            return;
        end else if sp1B4^.u.Offset < arg0^.u.Offset then begin
            sp1B4^.next := arg0;
            sp1B4 := arg0;
            return;
        end;
        v0 := sp1B8;
        next := v0^.next;
        while (next <> nil)  do begin
            if arg0^.u.Offset = next^.u.Offset then return;
            if reversed_stack then begin
                if next^.u.Offset < arg0^.u.Offset then begin
                    v0^.next := arg0;
                    arg0^.next := next;
                    return;
                end;
            end else if arg0^.u.Offset < next^.u.Offset then begin
                v0^.next := arg0;
                arg0^.next := next;
                return;
            end;
            v0 := next;
            next := next^.next;
        end;
        v0^.next := arg0;
    end;


    procedure func_0040F1BC(arg0: ^Tree);
    var
        temp_v0 : ^tree;
    begin
        assert(arg0^.u.Opc = Ulab);
        temp_v0 := build_op(Unop);
        temp_v0^.u.I1 := arg0^.u.I1;
        temp_v0^.op1 := arg0;
        temp_v0^.next := sp1A8;
        sp1A8 := temp_v0;
    end;

    function func_0040F230(arg0: ^tree): boolean;
var
    temp_v0: boolean;
begin
    if (arg0 = nil) then begin
        return false;
    end;

    if ((arg0^.u.Opc in [Uilod, Uistr, Ulod, Umov, Ustr]) and (arg0^.u.Lexlev & 1 <> 0)) then begin
        return true;
    end;
    if (arg0^.op1 <> nil) then begin
        temp_v0 := func_0040F230(arg0^.op1);
        if (arg0^.op2 <> nil) then begin
            if NOT (temp_v0) then begin
                temp_v0 := func_0040F230(arg0^.op2);
            end;
            return temp_v0;
        end;
        return temp_v0;
    end;
    return false;
end;  

    procedure func_0040F328();
    label next;
    var
        var_s2 : ^tree;
        var_v0 : ^tree;
        temp_v0 : ^tree;
    begin
        if not sp127 then begin
            var_s2 := sp1B8;
            while (var_s2 <> nil) and (var_s2^.u.Offset2 <> -1) do begin
                if var_s2^.u.Lexlev <> 1 then begin
                    if (sp1F0 <> 0) or ((sp1F0 = 0) and (opt_parms = 0) and (not sp183)) then begin
                        var_v0 := sp1BC;
                        while (var_v0 <> nil) do begin
                            if (var_v0^.u.Offset2 = var_s2^.u.Offset2) then goto next;
                            var_v0 := var_v0^.next;
                        end;
                    end;
                    temp_v0 := build_u(var_s2^.u);
                    temp_v0^.u.Opc := Ulod;
                    temp_v0^.u.Lexlev := 0;
                    temp_v0^.u.Mtype := Pmt;
                    temp_v0^.u.Offset2 := 0;
                    temp_v0 := build_u1(var_s2^.u, temp_v0);
                    temp_v0^.u.Opc := Ustr;
                    temp_v0^.u.Lexlev := 0;
                    temp_v0^.u.Mtype := Rmt;
                    temp_v0^.u.Offset := var_s2^.u.Offset2;
                    temp_v0^.u.Offset2 := 0;
                    temp_v0^.next := sp1A4^.next;
                    sp1A4^.next := temp_v0;
                end;
                next:
                var_s2 := var_s2^.next;
            end;
        end;
    end;
begin
    for var_s1 := lbound(label_hash_table) to hbound(label_hash_table) do begin
        label_hash_table[var_s1] := nil;
    end;

    new(sp1C4);
    sp1F4 := nil;
    sp1648 := 0;

    while (true) do begin
        readuinstr(sp1C8, sp1C4);

        case sp1C8.Opc of

            {Parse different Uopcodes}
            CASE_OPC(Ufsym):
            begin
                gen_sym(sp1C8);
                if domtag then begin
                    tree_s3 := build_u(sp1C8);
                    tree_s3^.next := syms;
                    syms := tree_s3;
                end;
            end;

            CASE_OPC(Uasym),
            CASE_OPC(Ucsym),
            CASE_OPC(Uesym),
            CASE_OPC(Uhsym),
            CASE_OPC(Ugsym),
            CASE_OPC(Ulsym),
            CASE_OPC(Uksym),
            CASE_OPC(Uosym):
            begin
                gen_sym(sp1C8);
            end;

            CASE_OPC(Umsym):
            begin
                gen_sym(sp1C8);
                func_0040E238(build_u(sp1C8));
                framesz_relocatable := 1;
            end;

            CASE_OPC(Ussym):
            begin
                sp1C8.constval.chars := sp1C4;
                if (sp1C8.constval.Ival >= 9) then begin
                    sp1C8.constval.Ival := 8;
                    sp1C8.constval.chars^.ss[9] := char(0);
                end;
                new(sp1C4);
                tree_s3 := build_u(sp1C8);
                tree_s3^.u.Dtype := Mdt;
                func_0040E238(tree_s3);
            end;

            CASE_OPC(Uinit):
            begin
                if sp1C8.Dtype in [Mdt, Qdt, Rdt, Sdt, Xdt] then begin
                    sp1C8.Initval.Chars := sp1C4;
                    new(sp1C4, 1);
                end;
                add_init(sp1C8);
            end;

            CASE_OPC(Usdef):
            begin
                set_size(sp1C8.I1, sp1C8.Length);
            end;

            CASE_OPC(Ubgn):
            begin
                ms_stamp := sp1C8.Length;
                ls_stamp := sp1C8.Offset;
                first_pmt_offset := 0;
                reversed_stack := false;
                resident_text := 0;
                has_cia_in_file := 0; { Bool }
            end;

            CASE_OPC(Ustp):
            begin
                if (syms <> nil) then begin
                    free_tree(syms);
                end;

                return nil;
            end;


            {Parse block uopcodes}

            CASE_OPC(Ubgnb):
            begin
                func_0040E238(build_u(sp1C8));
            end;

            CASE_OPC(Uendb):
            begin
                func_0040E238(build_u(sp1C8));
            end;

            CASE_OPC(Ucomm),
            CASE_OPC(Uloc),
            CASE_OPC(Uregs):
            begin
                tree_s3 := build_u(sp1C8);
                if (sp1F4 = nil) then begin
                    sp1F4 := tree_s3;
                    build_tree := tree_s3;
                end else begin
                    func_0040E238(tree_s3);
                end;

                if (sp1C8.Opc = Uloc) then begin
                    current_line := sp1C8.I1;
                end else if (sp1C8.Opc = Ucomm) then begin
                    sp1C8.Constval.Chars := sp1C4;
                    if (verbose) then begin
                        if ((sp1F4^.prior <> nil) and (sp1F4^.prior^.u.Opc = Uent)) then begin
                            sp181 := ' ';
                            var_s0 := sp1C8.Constval.Ival;
                            while (sp1C4^.ss[var_s0] = sp181) do var_s0 := var_s0 - 1;
                            write(err, sp181, sp1C4^.ss:var_s0);
                        end;
                    end;
                end else begin
                    opt_parms := 0;
                    ignore_vreg := 1;
                    sp127 := true;
                end;
            end;

            CASE_OPC(Uoptn):
            begin
                tree_s3 := build_u(sp1C8);
                tree_s3^.next := sp1AC;
                sp1AC := tree_s3;

                if (sp1C8.I1 = UCO_VARARGS) then begin
                    sp17C := sp1C8.Length;
                end else if (sp1AC^.u.I1 = UCO_STACK_REVERSED) then begin
                    reversed_stack := true;
                    first_pmt_offset := -4;
                end else if (sp1AC^.u.I1 = UCO_RSTEXT) then begin
                    resident_text := 1;
                end else if (sp1AC^.u.I1 = UCO_SOURCE) then begin
                    source_language := sp1C8.Length;
                    if ((sp1C8.Length = ADA_SOURCE) and (glevel <> 0) and (glevel < 3)) then begin
                        opt_parms := 0;
                    end;
                end else if (sp1AC^.u.I1 = UCO_USE_AS0) then begin
                    has_cia_in_file := 1;
                end else if (sp1AC^.u.I1 = UCO_STACK_LIMIT) then begin
                    stack_limit_bn := sp1AC^.u.Length;
                end;
            end;

            {Procedure entry point}
            CASE_OPC(Uent):
            begin
                Assert(sp1648 = 0);
                sp1F0 := 0;
                sp1EC := 0;
                sp188 := 0;
                sp184 := 0;
                sp127 := false;
                sp1BC := nil;
                sp1B0 := nil;
                sp1B8 := nil;
                sp1AC := nil;
                sp1A8 := nil;
                sp182 := false;
                sp17B := 0;
                sp1C0 := build_u(sp1C8);
                sp17C := -1;
                sp166 := false;
                sp165 := false;
                sp183 := false;
                sp15F := false;


                if (sp1F4 = nil) then begin
                
                    build_tree := sp1C0;
                    sp1F4 := sp1C0;
                    sp158 := 0;
                    sp128[0].unk_00 := UNK_ENUM_A_0;
                    sp128[1].unk_00 := UNK_ENUM_A_0;
                    sp128[2].unk_00 := UNK_ENUM_A_0;
                    sp128[3].unk_00 := UNK_ENUM_A_0;
                end else begin
                    func_0040E238(sp1C0);
                    sp158 := 0;
                    sp128[0].unk_00 := UNK_ENUM_A_0;
                    sp128[1].unk_00 := UNK_ENUM_A_0;
                    sp128[2].unk_00 := UNK_ENUM_A_0;
                    sp128[3].unk_00 := UNK_ENUM_A_0;
                end;

                sp1A4 := build_op(Ulab);
                sp1A4^.u.Lexlev := 0;
                sp1A4^.u.Length := 0;
                pseudo_leaf := 1;
                framesz_relocatable := 0;
                use_fp := 0;
                will_use_real_fp_for_proc := 0;
                gen_sym(sp1C8);
                sp167 := IS_PRESERVE_STACK_ATTR(sp1C8.Extrnal);
            end;

        CASE_OPC(Uaent):
        begin
            sp182 := true;
            func_0040E238(build_u(sp1C8));
        end;

        CASE_OPC(Uend):
        begin
            func_0040E238(sp1A4);
            func_0040E238(build_u(sp1C8));


            if (sp1F0 <> 0) then begin
                tree_s3 := build_op(Udef);
                tree_s3^.u.Mtype := Tmt;
                tree_s3^.u.Length := max(sp1EC, max(n_parm_regs * 4, cardinal(n_fp_parm_regs * 2) * 4));
                tree_s3^.u.I1 := 0;
                if (sp182) then begin
                    tree_s3^.u.I1 := 1;            
                end;
    
                tree_s3^.next := sp1B0;
                sp1B0 := tree_s3;
            end;

            if (not sp127) then begin
                opt_parms := 1;
                ignore_vreg := 0;
            end;

            if (sp1B8 <> nil) then begin
                map_pdefs_to_regs(sp1B8, sp17C);

                if (opt_parms <> 0) then if
                ((sp182) or ((sp1F0 = 0) and (sp17C <> -1)) or (pseudo_leaf <> 0)) then if
                ((source_language <> ADA_SOURCE) or (not sp167)) then if
                (not sp165) then begin
                    func_0040EED4();
                end;

                if (sp17B <> 0) then begin
                    func_0040F328();
                end;
            end;

            if (sp1BC <> nil) then begin
                if domtag then begin
                    func_0040EF8C(sp1BC);
                end;
                func_0040E280(sp1C0, sp1BC);
            end;

            if (syms <> nil) then begin
                func_0040EFBC(syms);
                func_0040E280(sp1C0, syms);
                syms := nil;
            end;

            if (sp1B0 <> nil) then begin
                func_0040E280(sp1C0, sp1B0);
            end;

            if (sp1AC <> nil) then begin
                func_0040E280(sp1C0, sp1AC);
            end;

            if (sp1A8 <> nil) then begin
            tree_s2 := sp1C0;
            while (tree_s2 <> sp1A4) do begin
                if (tree_s2^.u.Opc = Uijp) then begin
                    tree_s2^.op2 := sp1A8;
                end;
                tree_s2 := tree_s2^.next;
            end;
            end;
            return;
        end;

        CASE_OPC(Updef):
        begin
            tree_s3 := build_u(sp1C8);
            func_0040F0B8(tree_s3);
            if tree_s3^.u.Lexlev <> 1 then sp17B := 1;
        end;

        CASE_OPC(Udef):
        begin
            if reversed_stack then begin
                assert((sp1C8.Mtype <> Mmt) or (sp1C8.Length >= sp184));
            end else begin
                assert((sp1C8.Mtype <> Mmt) or (sp1C8.Length >= -sp188));
                
            end;
            tree_s3 := build_u(sp1C8);
            if (sp1C8.Mtype = Pmt) then tree_s3^.op1 := sp1B8;
            tree_s3^.next := sp1B0;
            sp1B0 := tree_s3;
        end;

        CASE_OPC(Uvreg):
        begin
            sp1C8.Constval.Ival := -1;
            func_0040EC54(build_u(sp1C8));
        end;

        CASE_OPC(Uunal):
        begin
            func_0040E238(build_u(sp1C8));
        end;

        CASE_OPC(Uret):
        begin
            assert(sp1648 = 0);
            tree_s3 := build_op(Uujp);
            tree_s3^.op2 := sp1A4;
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Uujp):
        begin
            assert(sp1648 = 0);
            tree_s3 := build_u(sp1C8);
            tree_s3^.op2 := find_label(sp1C8.I1);
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Uijp):
        begin
            func_0040E2AC(sp1648);
            tree_s3 := build_u1(sp1C8, sp1004[sp1648]);
            sp1648 := sp1648 - 1;
            assert(sp1648 = 0);
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Utjp),
        CASE_OPC(Ufjp):
        begin
            func_0040E2AC(sp1648);
            tree_s3 := build_u2(sp1C8, sp1004[sp1648], find_label(sp1C8.I1));
            sp1648 :=  sp1648 - 1;
            assert(sp1648 = 0);
            if is_constant(tree_s3^.op1) then begin
                 if ((not is_zero(tree_s3^.op1)) <> (sp1C8.Opc = Utjp)) then begin
                    free_tree(tree_s3);
                    continue;
                end else begin
                    tree_s3^.u.Opc := Uujp;
                    tree_s3^.op1 := nil;
                end;
            end else if tree_s3^.op1^.u.Opc = Ulnot then begin
                tree_s0 := tree_s3^.op1;
                tree_s3^.op1 := dup_tree(tree_s0^.op1);
                if tree_s3^.u.Opc = Utjp then begin tree_s3^.u.Opc := Ufjp;
                end                            else tree_s3^.u.Opc := Utjp;
                if tree_s3^.u.Lexlev <> 0 then begin
                    if tree_s3^.u.Lexlev = 1 then begin tree_s3^.u.Lexlev := 2;
                    end                            else tree_s3^.u.Lexlev := 1;
                end;
                free_tree(tree_s0);
            end;
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Ulab):
        begin
            assert(sp1648 = 0);
            tree_s3 := find_label(sp1C8.I1);
            tree_s3^.u := sp1C8;
            tree_s3^.u.Offset2 := 0;
            func_0040E238(tree_s3);
            if IS_IJP_ATTR(sp1C8.Lexlev) then begin
                func_0040F1BC(tree_s3);
            end;
            if IS_EXCEPTION_ATTR(sp1C8.Lexlev) then begin
                sp166 := true;
            end;
        end;

        CASE_OPC(Uldef):
        begin
            assert(sp1648 = 0);
            tree_s3 := search_label(sp1C8.I1);
            if tree_s3 = nil then begin
                report_error(Internal, 1409, "build.p", "LDEF before LAB");
            end else begin
                tree_s3^.u.Lexlev := sp1C8.Lexlev;
                tree_s3^.u.Length := sp1C8.Length;
            end;
        end;

        CASE_OPC(Uclab):
        begin
            assert(sp1648 = 0);
            tree_s3 := find_label(sp1C8.I1);
            tree_s3^.u := sp1C8;
            tree_s3^.u.Offset := 0;
            tree_s3^.u.Offset2 := 1;
            var_s5 := -1;
            var_s4 := -1;

            func_0040E238(tree_s3);
            tree_s2 := sp1F4;
            while (tree_s2 <> nil) and ((tree_s2^.u.Opc <> Uxjp) or (tree_s2^.u.I1 <> tree_s3^.u.I1)) do begin
                tree_s2 := tree_s2^.prior;
            end;

            if tree_s2 <> nil then begin
                if tree_s2^.op1^.u.Opc = Uand then begin
                    if (tree_s2^.op1^.op2^.u.Opc = Uldc) then begin
                        if tree_s2^.op1^.op2^.u.Dtype in [Idt,Kdt,Wdt] then begin
                            var_s5 := tree_s2^.op1^.op2^.u.Constval.dwval_h;
                            var_s4 := tree_s2^.op1^.op2^.u.Constval.dwval_l;
                        end else begin
                            var_s4 := tree_s2^.op1^.op2^.u.Constval.Ival;
                            if (var_s4 >= 0) then var_s5 := 0;
                        end;
                    end else if (tree_s2^.op1^.op1^.u.Opc = Uldc) then begin
                        if tree_s2^.op1^.op1^.u.Dtype in [Idt,Kdt,Wdt] then begin
                            var_s5 := tree_s2^.op1^.op1^.u.Constval.dwval_h;
                            var_s4 := tree_s2^.op1^.op1^.u.Constval.dwval_l;
                        end else begin
                            var_s4 := tree_s2^.op1^.op1^.u.Constval.Ival;
                            if (var_s4 >= 0) then var_s5 := 0;
                        end;
                    end;
                end else if (tree_s2^.prior^.u.Opc = Ufjp) then begin
                    if ((tree_s2^.prior^.prior^.u.Opc = Ustr) and (tree_s2^.prior^.prior^.op1^.u.Opc = Uand)) then begin
                        if (tree_s2^.prior^.op1^.op1^.u.Opc = Ulod) then begin
                            tree_s3 := tree_s2^.prior^.op1^.op1;
                        end else begin
                            tree_s3 := tree_s2^.prior^.op1^.op1^.op1;
                        end;
                        tree_s0 := tree_s2^.prior^.prior;
                        if ((tree_s3^.u.Mtype = tree_s0^.u.Mtype) and
                            (tree_s3^.u.I1 = tree_s0^.u.I1) and
                            (((lsb_first) and (tree_s3^.u.Offset = tree_s0^.u.Offset)) or
                             ((lsb_first = false) and ((tree_s3^.u.Offset + tree_s3^.u.Length) = (tree_s0^.u.Offset + tree_s0^.u.Length)))) 
                             and (tree_s0^.u.Length = tree_s3^.u.Length)) then begin
                            if (tree_s0^.op1^.op1^.u.Opc = Uldc) then begin
                                if tree_s0^.op1^.op1^.u.Dtype in [Idt,Kdt,Wdt] then begin
                                    var_s5 := tree_s0^.op1^.op1^.u.Constval.dwval_h;
                                    var_s4 := tree_s0^.op1^.op1^.u.Constval.dwval_l;
                                end else begin
                                    var_s4 := tree_s0^.op1^.op1^.u.Constval.Ival;
                                    if (var_s4 >= 0) then var_s5 := 0;
                                end;
                            end else if (tree_s0^.op1^.op2^.u.Opc = Uldc) then begin
                                if tree_s0^.op1^.op2^.u.Dtype in [Idt,Kdt,Wdt] then begin
                                    var_s5 := tree_s0^.op1^.op2^.u.Constval.dwval_h;
                                    var_s4 := tree_s0^.op1^.op2^.u.Constval.dwval_l;
                                end else begin
                                    var_s4 := tree_s0^.op1^.op2^.u.Constval.Ival;
                                    if (var_s4 >= 0) then var_s5 := 0;
                                end;
                            end;
                        end;
                    end;
                end;
            end else begin
            end;
            for var_s1 := 1 to sp1C8.Length do begin
                tree_s0 := new_tree();
                readuinstr(tree_s0^.u, nil);
                if tree_s0^.u.Opc <> Uujp then begin
                    report_error(Internal, 1551, "build.p", "non UJP u-code in jump table");
                end;
                if tree_s2 <> nil then begin
                    if ((tree_s2^.u.lbound_l + var_s1 - 1) < tree_s2^.u.lbound_l) then begin sp174 := 1; end
                    else sp174 := 0;
                    
                    if ((bitand(tree_s2^.u.lbound_l + var_s1 - 1, var_s4) <> tree_s2^.u.lbound_l + var_s1 - 1)) or 
                        (bitand(tree_s2^.u.lbound_h + sp174, var_s5) <> tree_s2^.u.lbound_h + sp174) then begin
                        tree_s0^.u.I1 :=  tree_s2^.u.Length;
                    end;
                end;
                tree_s0^.op2 := find_label(tree_s0^.u.I1);
                func_0040E238(tree_s0);
            end;
            tree_s3 := build_op(Uclab);
            tree_s3^.u.Length := 0;
            tree_s3^.u.I1 := sp1C8.I1;
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Uxjp):
        begin
            if (sp1004[sp1648] = nil) and (search_label(sp1C8.I1) <> nil) then begin
                tree_s3 := new_tree();
                tree_s3^.u.Opc := Uujp;

                sp174 := sp9C4[sp1648] - sp1C8.lbound;
                if (sp174 >= sp1C8.hbound) then begin
                    tree_s3^.op2 := find_label(sp1C8.Length);
                end else begin
                    tree_s0 := find_label(sp1C8.I1);
                    assert(tree_s0^.u.Opc = Uclab);
                    sp174 := sp174 + 1;
                    repeat begin
                        tree_s0 := tree_s0^.next;
                        assert((tree_s0 <> nil) and (tree_s0^.u.Opc = Uujp));
                        sp174 := sp174 - 1;
                    end until sp174 = 0;
                    tree_s3^.op2 := tree_s0^.op2;
                end;
                func_0040E238(tree_s3);
            end else begin
                sp9C4[sp1648] := sp9C4[sp1648] - sp1C8.lbound;
                sp384[sp1648] := 0;
                func_0040E2AC(sp1648);
                tree_s2 := sp1004[sp1648];
                if sp1C8.Dtype in [Idt, Kdt, Wdt] then begin
                    dtype_s1 := Kdt;
                end else begin
                    dtype_s1 := Ldt;
                end;
                tree_s2^.u.Dtype := dtype_s1;
                if (tree_s2^.u.Opc = Uand) and 
                   (((tree_s2^.op2^.u.Opc = Uldc) and (tree_s2^.op2^.u.Constval.Ival <= sp1C8.hbound - sp1C8.lbound) and (tree_s2^.op2^.u.Constval.Ival > 0)) or 
                    ((tree_s2^.op1^.u.Opc = Uldc) and (tree_s2^.op1^.u.Constval.Ival <= sp1C8.hbound - sp1C8.lbound) and (tree_s2^.op1^.u.Constval.Ival > 0)))then begin
                        func_0040E238(build_u2(sp1C8, tree_s2, find_label(sp1C8.I1)));
                        sp1648 := sp1648 - 1;
                        assert(sp1648 = 0);
                        continue;
                end else if (sp1F4^.u.Opc = Ustr) and (sp1F4^.op1^.u.Opc = Uand) and
                    (((sp1F4^.op1^.op1^.u.Opc = Uldc) and (sp1F4^.op1^.op1^.u.Constval.Ival <= sp1C8.hbound - sp1C8.lbound) and (sp1F4^.op1^.op1^.u.Constval.Ival > 0)) or 
                     ((sp1F4^.op1^.op2^.u.Opc = Uldc) and (sp1F4^.op1^.op2^.u.Constval.Ival <= sp1C8.hbound - sp1C8.lbound) and (sp1F4^.op1^.op2^.u.Constval.Ival > 0))) then begin
                    if tree_s2^.u.Opc = Ulod then begin
                        tree_s3 := tree_s2;
                    end else begin
                        tree_s3 := tree_s2^.op1;
                    end;
                    if (tree_s3^.u.Mtype = sp1F4^.u.Mtype) 
                    then if ((tree_s2^.u.Opc <> Uadd) or (tree_s2^.op2 = nil) or (tree_s2^.op2^.u.Opc <> Uldc) or (tree_s2^.op2^.u.Constval.Ival >= 0)) 
                    then if (tree_s3^.u.I1 = sp1F4^.u.I1) 
                    then if ((lsb_first and (tree_s3^.u.lbound = sp1F4^.u.lbound)) or 
                           ((not lsb_first) and (tree_s3^.u.lbound + tree_s3^.u.hbound = sp1F4^.u.lbound + sp1F4^.u.hbound))) 
                    then if (sp1F4^.u.hbound = tree_s3^.u.hbound) then begin
                        func_0040E238(build_u2(sp1C8, tree_s2, find_label(sp1C8.I1)));
                        sp1648 := sp1648 - 1;
                        assert(sp1648 = 0);
                        continue;
                    end;
                end;
                tree_s0 := build_2op(Ufjp, build_2op(Ules, dup_tree(tree_s2), ivalue(dtype_s1, 0, (sp1C8.hbound - sp1C8.lbound + 1))), find_label(sp1C8.Length));
                tree_s0^.u.Lexlev := 0;
                func_0040E238(tree_s0);
                func_0040E238(build_u2(sp1c8, tree_s2, find_label(sp1C8.I1)));
            end;
            sp1648 := sp1648 - 1;
            assert(sp1648 = 0);
        end;

        CASE_OPC(Umst):
        begin
            func_0040E238(build_u(sp1C8));
        end;

        CASE_OPC(Upar),
        CASE_OPC(Upmov),
        CASE_OPC(Umpmv):
        begin
            sp1EC := max(sp1EC, abs(sp1C8.Offset - first_pmt_offset) + sp1C8.Length);
            sp15F := true;
            if (sp1648 = 0) and (source_language = C_SOURCE) then begin
                sp1648 := 2;
                writeln(err, "Internal error due to probable C source error. Please recompile your C code with the -prototypes flag to cc(1)");
                report_error(Internal, 1708, "build.p", "Cannot continue");
            end;
            func_0040E2AC(sp1648);
            tree_s3 := build_u1(sp1C8, sp1004[sp1648]);
            sp1648 := sp1648 - 1;
            assert(sp1648 = 0);
            func_0040E24C(tree_s3);
        end;

        CASE_OPC(Urpar):
        begin
            sp1EC := max(sp1EC, abs(sp1C8.Offset - first_pmt_offset) + sp1C8.Length);
            assert(sp1648 = 0);
            sp1C8.Offset2 := sp1C8.Lexlev * 4;
            func_0040E238(build_u(sp1C8));
        end;

        CASE_OPC(Ucup),
        CASE_OPC(Urcuf):
        begin
            assert(sp1648 = 0);
            tree_s3 := build_u(sp1C8);
            sp1F0 := sp1F0 + 1;
            if not IS_RETURN_ATTR(sp1C8.Extrnal) then begin
                pseudo_leaf := 0;
            end;
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Uicuf):
        begin
            func_0040E2AC(sp1648);
            tree_s3 := build_u1(sp1C8, sp1004[sp1648]);
            sp1648 := sp1648 - 1;
            assert(sp1648 = 0);
            if not IS_THUNK_CALL_ATTR(sp1C8.Extrnal) then begin
                sp1F0 := sp1F0 + 1;
                pseudo_leaf := 0;
            end;
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Umov):
        begin
            func_0040E2AC(sp1648);
            func_0040E2AC(sp1648 - 1);
            tree_s3 := build_u2(sp1C8, sp1004[sp1648 - 1], sp1004[sp1648]);
            sp1648 := pred(pred(sp1648));
            assert(sp1648 = 0);
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Uaos),
        CASE_OPC(Ustr),
        CASE_OPC(Ustsp):
        begin
            if sp1C8.Opc = Ustr then sp1C8.Constval.Ival := 0;
            if (sp1C8.Opc = Ustr) and (sp1C8.Mtype = Rmt) then sp1C8.Offset := sp1C8.Offset * 4;
            if (sp1C8.Opc = Ustr) and (sp1C8.Mtype = Pmt) and (sp1C8.I1 = 0) then begin
                sp1EC := max(sp1EC, abs(sp1C8.Offset - first_pmt_offset) + sp1C8.Length);
            end;
            if (sp1C8.Opc = Uaos) or (sp1C8.Opc = Ustsp) then begin
                use_fp := 1;
            end;
            func_0040E2AC(sp1648);
            tree_s3 := build_u1(sp1C8, sp1004[sp1648]);
            if (sp1C8.Opc = Ustr) 
               and (sp1004[sp1648]^.u.Opc = Ulod)
               and (sp1C8.Offset = sp1004[sp1648]^.u.Offset)
               and (sp1C8.Dtype = sp1004[sp1648]^.u.Dtype)
               and (sp1C8.Mtype = sp1004[sp1648]^.u.Mtype)
               and (sp1C8.I1 = sp1004[sp1648]^.u.I1)
               and (sp1C8.Length = sp1004[sp1648]^.u.Length)
               and not IS_VOLATILE_ATTR(sp1C8.Lexlev) then begin
                sp1648 := sp1648 - 1;
                assert(sp1648 = 0);
            end else begin
                sp1648 := sp1648 - 1;
                if (sp1C8.Opc = Uaos) and (sp1648 <> 0) then begin
                    writeln(err, "Found Uaos u-code in unexpected spot. Perhaps value returned from alloca(3) was not assigned to simple variable. (See alloca man page)");
                    flush(err);
                    report_error(Internal, 1807, "build.p", "Cannot continue");
                end else begin
                    assert(sp1648 = 0);
                end;
                func_0040E24C(tree_s3);
                if (tree_s3^.u.Opc = Ustr) and (tree_s3^.u.Mtype = Pmt) then begin
                    func_0040E474(tree_s3);
                end;
                if (tree_s3^.u.Opc = Uaos) or (tree_s3^.u.Opc = Ustsp) then begin
                    tree_s3^.u.Dtype := addr_dtype;
                end;
            end;
        end;

        CASE_OPC(Uisst):
        begin
            sp1C8.Offset2 := 0;
            if nooffsetopt then func_0040E2AC( (sp1648 - 1));
            if sp1004[sp1648 - 1] = nil then begin
                temp_fp := sp9C4[sp1648 - 1] + sp1C8.Offset;
                sp1C8.Offset := (bitxor(bitand(temp_fp, 16#FFFF), 16#8000) - 16#8000);
                if basicint = 1 then begin
                    sp1004[sp1648 - 1] := dwvalue(Wdt, temp_fp - sp1C8.Offset);
                end else begin
                    sp1004[sp1648 - 1] := ivalue(Adt, 0, temp_fp - sp1C8.Offset);
                end;
            end else begin
                sp1C8.Offset := sp1C8.Offset + sp9C4[sp1648 - 1];
            end;
            sp9C4[sp1648 - 1] := 0;
            func_0040E2AC(sp1648);
            tree_s3 := build_u2(sp1C8, sp1004[sp1648 - 1], sp1004[sp1648]);
            sp1648 := pred(pred(sp1648));
            assert(sp1648 = 0);
            func_0040E24C(tree_s3);
        end;

        CASE_OPC(Uistr):
        begin
            sp1C8.Offset2 := sp1C8.Offset;
            if nooffsetopt then func_0040E2AC( sp1648 - 1);
            if sp1648 < 2 then sp1648 := 2;
            if sp1004[sp1648 - 1] = nil then begin
                temp_fp := sp9C4[sp1648 - 1] + sp1C8.I1;
                sp1C8.Offset := bitxor(bitand(temp_fp, 16#FFFF), 16#8000) - 16#8000;
                if basicint = 1 then begin
                    sp1004[sp1648 - 1] := dwvalue(Wdt, temp_fp - sp1C8.Offset);
                end else begin
                    sp1004[sp1648 - 1] := ivalue(Adt, 0, temp_fp - sp1C8.Offset);
                end;
            end else begin
                sp1C8.Offset := sp1C8.I1 + sp9C4[sp1648 - 1];
            end;
            sp9C4[sp1648 - 1] := 0;
            func_0040E2AC(sp1648);
            tree_s3 := build_u2(sp1C8, sp1004[sp1648 - 1], sp1004[sp1648]);
            sp1648 :=  pred(pred(sp1648));
            assert(sp1648 = 0);

            func_0040E24C(tree_s3);
        end;

        CASE_OPC(Uirst):
        begin
            func_0040E2AC( sp1648 - 1);
            if sp1648 < 2 then sp1648 := 2;
            sp9C4[sp1648 - 1] := 0;
            func_0040E2AC(sp1648);
            tree_s3 := build_u2(sp1C8, sp1004[sp1648 - 1], sp1004[sp1648]);
            sp1648 :=  pred(pred(sp1648));
            assert(sp1648 = 0);
            func_0040E24C(tree_s3);
        end;

        CASE_OPC(Urstr):
        begin
            tree_s3 := build_op(Ulod);
            tree_s3^.u.Mtype := Rmt;
            tree_s3^.u.Offset := sp1C8.Lexlev * 4;
            tree_s3^.u.Length := sp1C8.Length;
            tree_s3^.u.Dtype := sp1C8.Dtype;
            tree_s3^.u.I1 := sp1C8.I1;
            tree_s3^.u.Lexlev := 0;
            tree_s0 := build_u1(sp1C8, tree_s3);
            tree_s0^.u.Opc := Ustr;
            tree_s0^.u.Offset2 := 0;
            tree_s0^.u.Lexlev := 0;
            func_0040E238(tree_s0);
        end;

        CASE_OPC(Urlod):
        begin
            tree_s0 := build_u(sp1C8);
            tree_s0^.u.Opc := Ulod;
            tree_s0^.u.Offset2 := 0;
            tree_s0^.u.Lexlev := 0;

            tree_s3 := build_op(Ustr);
            tree_s3^.u.Mtype := Rmt;
            tree_s3^.u.Offset := sp1C8.Lexlev * 4;
            tree_s3^.u.Offset2 := 0;
            tree_s3^.u.Length := sp1C8.Length;
            tree_s3^.u.Dtype := sp1C8.Dtype;
            tree_s3^.u.I1 := sp1C8.I1;
            tree_s3^.u.Lexlev := 0;
            tree_s3^.op1 := tree_s0;
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Urldc):
        begin
            if sp1C8.Dtype in [Mdt,Qdt,Rdt,Sdt,Xdt] then begin
                sp1C8.Constval.Chars := sp1C4;
                new(sp1C4);
            end;
            tree_s0 := build_u(sp1C8);
            tree_s0^.u.Opc := Uldc;
            if ((sp1C8.Dtype = Fdt) or (sp1C8.Dtype = Ndt)) then begin
                tree_s0^.u.Opc := Ulda;
                tree_s0^.u.I1 := sp1C8.Constval.Ival;
                tree_s0^.u.Dtype := addr_dtype;
                tree_s0^.u.Mtype := Smt;
                tree_s0^.u.Offset := 0;
                tree_s0^.u.Offset2 := 0;
                tree_s0^.u.Length := unitsperaddr;
            end else if (sp1C8.Dtype = Gdt) then begin
                tree_s0 := build_1op(Ucg2, find_label(sp1C8.Constval.Ival));
                tree_s0^.u.Dtype := Gdt;
            end;
            tree_s3 := build_op(Ustr);
            tree_s3^.u.Dtype := sp1C8.Dtype;
            tree_s3^.u.Mtype := Rmt; 
            tree_s3^.u.Offset := sp1C8.I1 * 4;
            tree_s3^.u.Offset2 := 0;
            tree_s3^.u.Length := sp1C8.Length;
            tree_s3^.op1 := tree_s0;
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Urlda):
        begin
            tree_s0 := build_u(sp1C8);
            tree_s0^.u.Opc := Ulda;
            tree_s0^.u.Dtype := addr_dtype;
            if sp1C8.Mtype = Pmt then func_0040E474(tree_s0);
            tree_s3 := build_op(Ustr);
            tree_s3^.u.Dtype := addr_dtype;
            tree_s3^.u.Mtype := Rmt;
            tree_s3^.u.Offset := sp1C8.Length * unitsperaddr; {0x28(v0)}
            tree_s3^.u.Offset2 := 0; {0x30(v0)}
            tree_s3^.u.Length := unitsperaddr; {0x28(v0)}
            tree_s3^.op1 := tree_s0; {0(v0)}
            tree_s0^.u.Length := unitsperaddr; {0x28(s0)}
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Ulca):
        begin
            sp1C8.Constval.Chars := sp1C4;
            new(sp1C4);
            tree_s3 := build_u(sp1C8);
            sp1648 := sp1648 + 1;
            sp1004[sp1648] := tree_s3;
            sp9C4[sp1648] := 0;
            sp384[sp1648] := 0;
        end;

        CASE_OPC(Ulda):
        begin
            sp1C8.Dtype := addr_dtype;
            tree_s3 := build_u(sp1C8);
            if sp1C8.Mtype = Mmt then begin
                if reversed_stack then begin
                    sp184 := max(sp184, sp1C8.Offset2);
                end else begin
                    sp188 := min(sp188, sp1C8.Offset2);
                end;
            end else if sp1C8.Mtype = Pmt then begin
                func_0040E474(tree_s3);
            end;
            sp1648 := sp1648 + 1;
            sp1004[sp1648] := tree_s3;
            sp9C4[sp1648] := 0;
            sp384[sp1648] := 0;
        end;
        
        CASE_OPC(Uldc):
        begin
            sp1648 := sp1648 + 1;
            sp9C4[sp1648] := 0;
            sp384[sp1648] := 0;
            sp1F7[sp1648] := Zdt;
            dtype_s1 := sp1C8.Dtype;
            if sp1C8.Dtype in [Mdt,Qdt,Rdt,Sdt] then begin
                sp1C8.Constval.Chars := sp1C4;
                new(sp1C4);
                sp1004[sp1648] := build_u(sp1C8);
            end else if (sp1C8.Dtype = Fdt) or (sp1C8.Dtype = Ndt) then begin
                tree_s3 := build_op(Ulda);
                tree_s3^.u.I1 := sp1C8.Constval.Ival;
                tree_s3^.u.Mtype := Smt;
                tree_s3^.u.Dtype := addr_dtype;
                tree_s3^.u.Offset := 0;
                sp1004[sp1648] := tree_s3;
            end else if sp1C8.Dtype = Gdt then begin
                tree_s3 := build_1op(Ucg2, find_label(sp1C8.Constval.Ival));
                tree_s3^.u.Dtype := Gdt;
                sp1004[sp1648] := tree_s3;
            end else if sp1C8.Dtype in [Idt,Kdt] then begin
                sp1004[sp1648] := build_u(sp1C8);
            end else begin
                sp1004[sp1648] := nil;
                sp9C4[sp1648] := sp1C8.Constval.Ival;
                sp1F7[sp1648] := sp1C8.Dtype;
            end;
        end;
        
        CASE_OPC(Uldrc):
        begin
            sp1648 := sp1648 + 1;
            sp9C4[sp1648] := 0;
            sp384[sp1648] := 0;
            sp1F7[sp1648] := Zdt;
            sp1004[sp1648] := build_u(sp1C8);
        end;
        
        CASE_OPC(Uldap),
        CASE_OPC(Uldsp),
        CASE_OPC(Ulod):
        begin
            if (sp1C8.Opc = Ulod) and (sp1C8.Mtype = Rmt) then sp1C8.Offset := sp1C8.Offset * 4;
            tree_s3 := build_u(sp1C8);
            tree_s3^.u.Offset2 := 0;
            sp1648 := sp1648 + 1;
            sp1004[sp1648] := tree_s3;
            sp9C4[sp1648] := 0;
            sp384[sp1648] := 0;
            if (tree_s3^.u.Opc = Ulod) and (tree_s3^.u.Mtype = Pmt) then func_0040E474(tree_s3);
            if (tree_s3^.u.Opc = Uldsp) or (tree_s3^.u.Opc = Uldap) then tree_s3^.u.Dtype := addr_dtype;
        end;

        CASE_OPC(Uchkt):
        begin
            func_0040E2AC(sp1648);
            sp1C8.I1 := 10;
            tree_s3 := build_u1(sp1C8, sp1004[sp1648]);
            sp1648 := sp1648 - 1;
            func_0040E238(tree_s3);
        end;

        CASE_OPC(Utpeq),
        CASE_OPC(Utpge),
        CASE_OPC(Utpgt),
        CASE_OPC(Utple),
        CASE_OPC(Utplt),
        CASE_OPC(Utpne):
        begin
            func_0040E2AC(sp1648 - 1);
            func_0040E2AC(sp1648);
            tree_s3 := build_u2(sp1C8, sp1004[sp1648 - 1], sp1004[sp1648]);
            sp1648 :=  pred(pred(sp1648));
            if (tree_s3^.u.Dtype in [Qdt, Rdt, Xdt]) then begin
                func_0040E238(tree_s3);
            end else begin
                tree_s3^.u.Opc := trap_to_compare[sp1C8.Opc];
                tree_s3 := build_1op(Uchkt, tree_s3);
                tree_s3^.u.I1 := sp1C8.I1;
                func_0040E238(tree_s3);
            end;
        end;

        CASE_OPC(Ucvt):
        begin
            if not (sp1C8.Dtype in similar_data_types[sp1C8.Dtype2]) or
                (IS_OVERFLOW_ATTR(sp1C8.Lexlev) and ((sp1C8.Dtype in [Idt, Jdt]) <> (sp1C8.Dtype2 in [Idt, Jdt])) or
                ((opcode_arch = 1) and not (sp1C8.Dtype in similar_data_types_dw[sp1C8.Dtype2]))) then begin
                func_0040E2AC(sp1648);
                sp1004[sp1648] := build_u1(sp1C8, sp1004[sp1648]);
            end;
        end;
        
        CASE_OPC(Uabs),
        CASE_OPC(Uadj),
        CASE_OPC(Uchkh),
        CASE_OPC(Uchkl),
        CASE_OPC(Uchkn),
        CASE_OPC(Ucvtl),
        CASE_OPC(Uilda),
        CASE_OPC(Ulnot),
        CASE_OPC(Unot),
        CASE_OPC(Uodd),
        CASE_OPC(Urnd),
        CASE_OPC(Usgs),
        CASE_OPC(Usqr),
        CASE_OPC(Usqrt),
        CASE_OPC(Utyp):
        begin
            func_0040E2AC(sp1648);
            sp1004[sp1648] := build_u1(sp1C8, sp1004[sp1648]);
        end;

        CASE_OPC(Uneg):
        begin
            if IS_OVERFLOW_ATTR(sp1C8.Lexlev) and (sp9C4[sp1648] = 16#80000000) then begin
                func_0040E2AC(sp1648);
            end;
            sp9C4[sp1648] := -sp9C4[sp1648];
            if sp1004[sp1648] <> nil then begin
                sp1004[sp1648] := build_u1(sp1C8, sp1004[sp1648]);
            end;
        end;

        CASE_OPC(Uinc):
        begin
            temp_fp := sp9C4[sp1648] + sp1C8.I1;
            if IS_OVERFLOW_ATTR(sp1C8.Lexlev) and (add_overflow(sp1C8.Dtype, sp9C4[sp1648], sp1C8.I1)) then begin
                func_0040E2AC(sp1648);
                temp_fp := sp1C8.I1;
            end;
            sp9C4[sp1648] := temp_fp;
            sp384[sp1648] := bitor(sp384[sp1648], sp1C8.Lexlev);
        end;

        CASE_OPC(Udec):
        begin
            temp_fp := sp9C4[sp1648] - sp1C8.I1;
            if (IS_OVERFLOW_ATTR(sp1C8.Lexlev) and (sub_overflow(sp1C8.Dtype, sp9C4[sp1648], sp1C8.I1))) then begin
                func_0040E2AC(sp1648);
                temp_fp := -sp1C8.I1;
            end;
            sp9C4[sp1648] := temp_fp;
            sp384[sp1648] := bitor(sp384[sp1648], sp1C8.Lexlev);
        end;

        CASE_OPC(Uisld):
        begin
            sp1C8.Offset2 := 0;
            if nooffsetopt then begin
                func_0040E2AC(sp1648);
            end;
            if sp1004[sp1648] = nil then begin
                temp_fp := sp9C4[sp1648] + sp1C8.Offset;
                sp1C8.Offset := bitxor(bitand(temp_fp, 16#FFFF), 16#8000) - 16#8000;
                if basicint = 1 then begin
                    sp1004[sp1648] := dwvalue(Wdt, temp_fp - sp1C8.Offset);
                end else begin
                    sp1004[sp1648] := ivalue(Adt, 0, temp_fp - sp1C8.Offset);
                end;
            end else begin
                sp1C8.Offset := sp1C8.Offset + sp9C4[sp1648];
            end;
           
            sp1004[sp1648] := build_u1(sp1C8, sp1004[sp1648]);
            sp9C4[sp1648] := 0;
            sp384[sp1648] := 0;
        end;

        CASE_OPC(Uilod):
        begin
            sp1C8.Offset2 := sp1C8.Offset;
            if nooffsetopt then begin
                func_0040E2AC(sp1648);
            end;
            if (sp1004[sp1648] = nil) then begin
                temp_fp := sp9C4[sp1648] + sp1C8.I1;
                sp1C8.Offset := bitxor(bitand(temp_fp, 16#FFFF), 16#8000) - 16#8000;
                if basicint = 1 then begin
                    sp1004[sp1648] := dwvalue(Wdt, temp_fp - sp1C8.Offset);
                end else begin
                    sp1004[sp1648] := ivalue(Adt, 0, temp_fp - sp1C8.Offset);
                end;
            end else begin
                sp1C8.Offset := sp1C8.I1 + sp9C4[sp1648];
            end;
            sp1004[sp1648] := build_u1(sp1C8, sp1004[sp1648]);
            sp9C4[sp1648] := 0;
            sp384[sp1648] := 0;
        end;
        
        CASE_OPC(Uirld):
        begin
            func_0040E2AC(sp1648);
            sp1004[sp1648] := build_u1(sp1C8, sp1004[sp1648]);
            sp9C4[sp1648] := 0;
            sp384[sp1648] := 0;
        end;
        
        CASE_OPC(Udup):
        begin
            sp1648 := sp1648 + 1;
            if sp1004[sp1648 - 1] = nil then begin
                sp1004[sp1648] := nil;
                sp9C4[sp1648] := sp9C4[sp1648 - 1];
            end else begin
                func_0040E2AC(sp1648 - 1);
                sp1004[sp1648] := dup_tree(sp1004[sp1648 - 1]);
                sp9C4[sp1648] := 0;
            end;
            sp384[sp1648] := 0;
        end;
        
        CASE_OPC(Uadd),
        CASE_OPC(Uand),
        CASE_OPC(Ubsub),
        CASE_OPC(Udif),
        CASE_OPC(Udiv),
        CASE_OPC(Uequ),
        CASE_OPC(Ugeq),
        CASE_OPC(Ugrt),
        CASE_OPC(Uiequ),
        CASE_OPC(Uigeq),
        CASE_OPC(Uigrt),
        CASE_OPC(Uileq),
        CASE_OPC(Uiles),
        CASE_OPC(Uineq),
        CASE_OPC(Uinn),
        CASE_OPC(Uint),
        CASE_OPC(Uior),
        CASE_OPC(Uixa),
        CASE_OPC(Uleq),
        CASE_OPC(Ules),
        CASE_OPC(Umax),
        CASE_OPC(Umin),
        CASE_OPC(Umod),
        CASE_OPC(Umpy),
        CASE_OPC(Umus),
        CASE_OPC(Uneq),
        CASE_OPC(Urem),
        CASE_OPC(Ushl),
        CASE_OPC(Ushr),
        CASE_OPC(Usign),
        CASE_OPC(Usub),
        CASE_OPC(Uuni),
        CASE_OPC(Uxor):
        begin
            temp_fp := 0;
            sp18C := 0;
            if IS_OVERFLOW_ATTR(sp1C8.Lexlev) then if
                ((((sp1004[sp1648 - 1] <> nil) and (sp1C8.Dtype <> sp1004[sp1648 - 1]^.u.Dtype))
            or ((sp1004[sp1648] <> nil) and (sp1C8.Dtype <> sp1004[sp1648]^.u.Dtype))
            or (sp1C8.Lexlev <> sp384[sp1648 - 1])
            or (sp1C8.Lexlev <> sp384[sp1648]))) then begin
                func_0040E2AC(sp1648 - 1);
                func_0040E2AC(sp1648);
            end;
            case sp1C8.Opc of 
            CASE_OPC(Uadd):
            begin
                if IS_OVERFLOW_ATTR(sp1C8.Lexlev) and add_overflow(sp1C8.Dtype, sp9C4[sp1648 - 1], sp9C4[sp1648]) then begin
                    temp_fp := sp9C4[sp1648 - 1];
                    sp18C := sp384[sp1648 - 1];
                    sp9C4[sp1648 - 1] := 0;
                    sp384[sp1648 - 1] := 0;
                    func_0040E2AC(sp1648);
                end else begin
                    temp_fp := sp9C4[sp1648 - 1] + sp9C4[sp1648];
                    sp9C4[sp1648 - 1] := 0;
                    sp9C4[sp1648] := 0;
                    sp18C := sp384[sp1648 - 1] ! sp384[sp1648] ! sp1C8.Lexlev;
                end;
                if sp1004[sp1648] = nil then begin
                    sp9C4[sp1648 - 1] := temp_fp;
                    sp384[sp1648 - 1] := sp384[sp1648 - 1] ! sp1C8.Lexlev;
                    sp1648 := sp1648 - 1;
                    continue;
                end else if sp1004[sp1648 - 1] = nil then begin
                    sp1004[sp1648 - 1] := sp1004[sp1648];
                    sp9C4[sp1648 - 1] := temp_fp;
                    sp384[sp1648 - 1] := sp384[sp1648] ! sp1C8.Lexlev;
                    sp1648 :=  sp1648 - 1;
                    continue;
                end;
            end;
            
            CASE_OPC(Ubsub), CASE_OPC(Usub):
            begin
                if sp1C8.Opc = Ubsub then sp1C8.Opc := Usub;
                if IS_OVERFLOW_ATTR(sp1C8.Lexlev) and sub_overflow(sp1C8.Dtype, sp9C4[sp1648 - 1], sp9C4[sp1648]) then begin
                    temp_fp := sp9C4[sp1648 - 1];
                    sp18C := sp384[sp1648 - 1];
                    sp9C4[sp1648 - 1] := 0;
                    func_0040E2AC(sp1648);
                end else begin
                    temp_fp := sp9C4[sp1648 - 1] - sp9C4[sp1648];
                    sp9C4[sp1648 - 1] := 0;
                    sp9C4[sp1648] := 0;
                    sp18C := sp384[sp1648 - 1] ! sp384[sp1648] ! sp1C8.lexlev;
                end;
                if sp1004[sp1648] = nil then begin
                    sp9C4[sp1648 - 1] := temp_fp;
                    sp384[sp1648 - 1] := sp384[sp1648 - 1] ! sp1C8.Lexlev;
                    sp1648 := sp1648 - 1;
                    continue;
                end else if sp1004[sp1648 - 1] = nil then begin
                    sp9C4[sp1648 - 1] := temp_fp;
                    sp384[sp1648 - 1] := sp18C;
                    sp1004[sp1648 - 1] := build_1op(Uneg, sp1004[sp1648]);
                    sp1004[sp1648 - 1]^.u.Lexlev := sp1004[sp1648]^.u.Lexlev;
                    sp1648 := sp1648 - 1;
                    continue;
                end;
            end;
            
            CASE_OPC(Umpy):
            begin
                if IS_OVERFLOW_ATTR(sp1C8.Lexlev) then begin 
                    {empty, likely debug}
                end else if sp1004[sp1648] = nil then begin
                    temp_fp := sp9C4[sp1648 - 1] * sp9C4[sp1648];
                    sp9C4[sp1648 - 1] := 0;
                    if sp1004[sp1648 - 1] = nil then begin
                        sp1648 :=  sp1648 - 1;
                        sp9C4[sp1648] := temp_fp;
                        continue;
                    end;
                end else if sp1004[sp1648 - 1] = nil then begin
                    temp_fp := sp9C4[sp1648] * sp9C4[sp1648 - 1];
                    sp9C4[sp1648] := 0;
                end;
            end;
            
            CASE_OPC(Uixa):
            begin
                temp_fp := sp9C4[sp1648 - 1] + sp9C4[sp1648] * sp1C8.I1;
                sp9C4[sp1648 - 1] := 0;
                sp9C4[sp1648] := 0;
                if sp1004[sp1648] = nil then begin
                    sp1648 := sp1648 - 1;
                    sp9C4[sp1648] := temp_fp;
                    continue;
                end else if sp1C8.I1 <> 1 then begin
                    sp1004[sp1648] := build_2op(Umpy, sp1004[sp1648], ivalue(Ldt, 0, sp1C8.I1));
                    sp1004[sp1648]^.u.Lexlev := sp1C8.Lexlev;
                end;
                sp1C8.Opc := Uadd;
            end;
            
            CASE_OPC(Uequ), CASE_OPC(Uneq):
            begin
                if sp1004[sp1648] = nil then begin
                    temp_fp := sp9C4[sp1648 - 1];
                end else if sp1004[sp1648 - 1] = nil then begin
                    temp_fp := sp9C4[sp1648];
                end else temp_fp := min(sp9C4[sp1648 - 1], sp9C4[sp1648]);
                sp9C4[sp1648 - 1] := sp9C4[sp1648 - 1] - temp_fp;
                sp9C4[sp1648] := sp9C4[sp1648] - temp_fp;
                temp_fp := 0;
            end;
            
            CASE_OPC(Ugeq), CASE_OPC(Ugrt), CASE_OPC(Uleq), CASE_OPC(Ules):
            begin
                if (sp9C4[sp1648 - 1] <> 0) and (sp9C4[sp1648] = 0) then begin
                    swap_tree(sp1004[sp1648 - 1], sp1004[sp1648]);
                    swap_int(sp9C4[sp1648 - 1], sp9C4[sp1648]);
                    sp1C8.Opc := reverse[sp1C8.Opc];
                end;
                if sp1C8.Dtype = Jdt then begin
                    if (sp1004[sp1648] = nil) or (sp1004[sp1648]^.u.Dtype = Jdt) then begin
                        if (sp9C4[sp1648] = 1) and (sp1C8.Opc = Ules) then begin
                            sp1C8.Opc := Uleq;
                            sp9C4[sp1648] := 0;
                        end else if (sp9C4[sp1648] = 1) and (sp1C8.Opc = Ugeq) then begin
                            sp1C8.Opc := Ugrt;
                            sp9C4[sp1648] := 0;
                        end else if (sp9C4[sp1648] = -1) and (sp1C8.Opc = Uleq) then begin
                            sp1C8.Opc := Ules;
                            sp9C4[sp1648] := 0;
                        end else if (sp9C4[sp1648] = -1) and (sp1C8.Opc = Ugrt) then begin
                            sp1C8.Opc := Ugeq;
                            sp9C4[sp1648] := 0;
                        end;
                    end;
                end;
            end;
            
            CASE_OPC(Umax), CASE_OPC(Umin):;
            
            CASE_OPC(Ushl), CASE_OPC(Ushr):
            begin
                sp9C4[sp1648] := sp9C4[sp1648] & 16#1F;
            end;
            
            CASE_OPC(Umod):
            begin
                if (sp1004[sp1648] = nil) and (sp9C4[sp1648] <> 0) and (sp1004[sp1648 - 1] <> nil) and (sp1004[sp1648 - 1]^.u.Dtype <> Ldt) then begin
                    sp9C4[sp1648 - 1] := sp9C4[sp1648 - 1] mod sp9C4[sp1648];
                end;
            end;
            
            {CASE_OPC(Uand): 
            CASE_OPC(Udif):
            CASE_OPC(Udiv):
            CASE_OPC(Uiequ):
            CASE_OPC(Uigeq):
            CASE_OPC(Uigrt):
            CASE_OPC(Uileq):
            CASE_OPC(Uiles):
            CASE_OPC(Uineq):
            CASE_OPC(Uinn):
            CASE_OPC(Uint):
            CASE_OPC(Uior):
            CASE_OPC(Umus):
            CASE_OPC(Urem):
            CASE_OPC(Usign):
            CASE_OPC(Uuni):
            CASE_OPC(Uxor):}
            otherwise:;
            end;

            binop_out:
            func_0040E2AC(sp1648);
            func_0040E2AC(sp1648 - 1);
            tree_s3 := build_u2(sp1C8, sp1004[sp1648 - 1], sp1004[sp1648]);
            sp1648 := sp1648 - 1;
            sp1004[sp1648] := tree_s3;
            sp9C4[sp1648] := temp_fp;
            sp384[sp1648] := sp18C;
            
        end;
        
        CASE_OPC(Uidx):
        begin
            if IS_OVERFLOW_ATTR(sp1C8.Lexlev) and
            (((sp1004[sp1648 - 1] <> nil) and (sp1C8.Dtype <> sp1004[sp1648 - 1]^.u.Dtype))
            or ((sp1004[sp1648] <> nil) and (sp1C8.Dtype <> sp1004[sp1648]^.u.Dtype))
            or ((sp1004[sp1648 - 2] <> nil) and (sp1C8.Dtype <> sp1004[sp1648 - 2]^.u.Dtype)) or
            (sp1C8.Lexlev <> sp384[sp1648 - 2])
            or (sp1C8.Lexlev <> sp384[sp1648 - 1])
            or (sp1C8.Lexlev <> sp384[sp1648])) then begin
                func_0040E2AC(sp1648);
                func_0040E2AC(sp1648 - 1);
                func_0040E2AC(pred(pred(sp1648)));
            end;
            if (sp1004[sp1648 - 2] = nil) and (sp1004[sp1648 - 1] = nil) then begin
                tree_s3 := sp1004[sp1648];
                temp_fp := sp9C4[sp1648] + (sp9C4[sp1648 - 1] * sp9C4[sp1648 - 2]);
                sp9C4[sp1648 - 2] := 0;
                sp9C4[sp1648 - 1] := 0;
                sp9C4[sp1648] := 0;
                sp1648 :=  pred(pred(sp1648));
                sp384[sp1648] := 0;
                sp1004[sp1648] := tree_s3;
                sp9C4[sp1648] := temp_fp;
            end else begin
                if sp1004[sp1648 - 2] = nil then begin
                    temp_fp := sp9C4[sp1648] + (sp9C4[sp1648 - 1] * sp9C4[sp1648 - 2]);
                    sp9C4[sp1648 - 1] := 0;
                    sp9C4[sp1648] := 0;
                end else if sp1004[sp1648 - 1] = nil then begin
                    temp_fp := sp9C4[sp1648] + (sp9C4[sp1648 - 1] * sp9C4[sp1648 - 2]);
                    sp9C4[sp1648 - 2] := 0;
                    sp9C4[sp1648] := 0;
                end else begin
                    temp_fp := sp9C4[sp1648];
                    sp9C4[sp1648] := 0;
                end;
                func_0040E2AC(pred(pred(sp1648)));
                func_0040E2AC(sp1648 - 1);
                if (sp1004[sp1648 - 2] <> nil) or (sp9C4[sp1648 - 2] <> 1) then begin
                    sp1004[sp1648 - 1] := build_2op(Umpy, sp1004[sp1648 - 1], sp1004[sp1648 - 2]);
                    sp1004[sp1648 - 1]^.u.Lexlev := sp1C8.Lexlev;
                end;

                if sp1004[sp1648] <> nil then begin
                    tree_s3 := build_2op(Uadd, sp1004[sp1648], sp1004[sp1648 - 1]);
                end else begin
                    tree_s3 := sp1004[sp1648 - 1];
                end;
                sp1648 :=  pred(pred(sp1648));
                sp1004[sp1648] := tree_s3;
                sp9C4[sp1648] := temp_fp;
                sp384[sp1648] := 0;
            end;
        end;
        
        CASE_OPC(Uswp):
        begin
            swap_tree(sp1004[sp1648 - 1], sp1004[sp1648]);
            swap_int(sp9C4[sp1648 - 1], sp9C4[sp1648]);
            swap_int(sp384[sp1648 - 1], sp384[sp1648]);
        end;
        
        CASE_OPC(Upop):
        begin
            if not func_0040F230(sp1004[sp1648]) then begin
                sp1648 :=  sp1648 - 1;
            end else begin
                func_0040E2AC(sp1648);
                tree_s3 := build_u1(sp1C8, sp1004[sp1648]);
                sp1648 := sp1648 - 1;
                tree_s3^.u.Opc := Ustr;
                tree_s3^.u.Mtype := Rmt;
                tree_s3^.u.Offset := 0;
                tree_s3^.u.Offset2 := 0;
                tree_s3^.u.Length := tree_s3^.op1^.u.Length;
                tree_s3^.u.Dtype := tree_s3^.op1^.u.Dtype;
                tree_s3^.u.I1 := tree_s3^.op1^.u.I1;
                func_0040E238(tree_s3);
            end;
        end;
        
        CASE_OPC(Uxpar): begin
            if sp1648 - 1 = 0 then; {force a3}
            sp1648 :=  sp1648 - 1; 
        end;
        
        CASE_OPC(Ucia):
        begin
            assert(sp1648 = 0);
            sp1C8.Constval.Chars := sp1C4;
            sp1C8.Constval.Ival := sp1C8.Length;
            new(sp1C4);
            sp183 := true;
            tree_s3 := build_u(sp1C8);
            if (tree_s3^.u.lexlev <> 0) or (sp15F) then begin
                sp1F0 := sp1F0 + 1;
                pseudo_leaf := 0;
            end;
            func_0040E238(tree_s3);
        end;
        
        CASE_OPC(Ulbgn): begin
            sp160 := sp1C8.I1;
        end;
        
        CASE_OPC(Ulbdy): begin
            sp1C8.I1 := sp160;
            func_0040E238(build_u(sp1C8));
        end;
        
        CASE_OPC(Umtag):
        begin
            func_0040E238(build_u(sp1C8));
            sp158 := sp1C8.I1;
            if sp1C8.Lexlev = 3 then non_local_mtag := sp158;
        end;
        
        CASE_OPC(Ualia): func_0040E238(build_u(sp1C8));
        
        CASE_OPC(Ueof): report_error(Internal, 2626, "build.p", "bad input to ugen:  end-of-file seen unexpectedly");

        CASE_OPC(Uclbd), CASE_OPC(Ucubd), CASE_OPC(Ulbd), CASE_OPC(Uubd),
        CASE_OPC(Ulend), CASE_OPC(Ulex),
        CASE_OPC(Ultrm), CASE_OPC(Unop),
        CASE_OPC(Ustep), CASE_OPC(Uctrl):;

        otherwise begin
            report_error(Internal, 2634, "build.p", "bad input to ugen:  unexpected u-code"); 
            print_ucode(err, sp1C8);
            writeln(err);
            flush(err);
        end;
            
        end;
    end;
end;

