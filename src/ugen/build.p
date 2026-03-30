#include "common.h"
#include "cmplrs/uoptions.h"
#include "tree.h"
#include "tree_utils.h"
#include "fold.h"
#include "report.h"
#include "swap.h"
#include "symbol.h"
#include "cmplrs/uread.h"

procedure print_ucode(var f: Text; var ucode: Bcrec); external;

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
    ms_stamp: integer;
    non_local_mtag: integer;
    nooffsetopt: boolean;
    opt_parms: u8;
    pseudo_leaf: u8;
    resident_text: s8;
    reverse: extern array[Uopcode] of Uopcode;
    similar_data_types: array[Datatype] of set of Datatype := [
        Adt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt, Wdt],
        Fdt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt, Wdt],
        Gdt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt, Wdt],
        Hdt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt, Wdt],
        Jdt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt],
        Ldt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt],
        Ndt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt, Wdt],
        Wdt: [Adt, Fdt, Gdt, Hdt, Idt, Kdt, Ndt, Wdt],

        Idt: [Idt, Kdt, Wdt],
        Kdt: [Idt, Kdt, Wdt],

        Qdt: [Qdt],
        Rdt: [Rdt],
        Xdt: [Xdt],

        otherwise []
    ];
    similar_data_types_dw: array[Datatype] of set of Datatype := [
        Adt: [Adt, Fdt, Gdt, Hdt, Jdt, Ndt, Wdt],
        Fdt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt, Wdt],
        Gdt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt, Wdt],
        Hdt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt, Wdt],
        Jdt: [Adt, Fdt, Gdt, Hdt, Jdt, Ndt],
        Ldt: [Fdt, Gdt, Hdt, Ldt, Ndt],
        Ndt: [Adt, Fdt, Gdt, Hdt, Jdt, Ldt, Ndt, Wdt],
        Wdt: [Adt, Fdt, Gdt, Hdt, Idt, Kdt, Ndt, Wdt],

        Idt: [Idt, Kdt, Wdt],
        Kdt: [Idt, Kdt, Wdt],

        Qdt: [Qdt],
        Rdt: [Rdt],
        Xdt: [Xdt],
        
        otherwise []
    ];
    stack_limit_bn: integer;    
    trap_to_compare: array[Utpeq..Utpne] of Uopcode := [Uneq, Ules, Uleq, Ugrt, Ugeq, Uequ];
    
    unitsperaddr: integer;
    use_fp: s8;
    will_use_real_fp_for_proc: s8;
    strp: Stringtextptr;

    syms: PTree := nil;

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
    temp_v0: PTree;
    var_v1: PTree;
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
procedure gen_sym(var ucode: Bcrec); external;
procedure add_init(var ucode: Bcrec); external;
procedure set_size(arg0: integer; arg1: cardinal); external;
procedure map_pdefs_to_regs(arg0: ^Tree; arg1: integer); external;
{function find_label(arg0: integer): pointer; external;}
function overlap(arg0: PTree; arg1: PTree): boolean; external;
function parm_reg(arg0: ^Tree): integer; external;


/* Variables */
#define CASE_OPC(x) (x)

function build_tree(verbose: boolean): pointer;
label binop_out;
const
    stack_size = 400;
var
    stack_pos: 0..stack_size;
    node_stack: array[1..stack_size] of PTree;
    value_stack: array[1..stack_size] of integer;
    lexlev_stack: array[1..stack_size] of integer;
    dtype_stack: array [1..stack_size] of Datatype;
    statement_list: PTree;
    sp1F0: integer;
    sp1EC: integer;
    var_s4: integer;
    ucode: Bcrec;
    sp1C4: Stringtextptr;
    sp1C0: PTree;
    sp1BC: PTree;
    sp1B8: PTree;
    sp1B4: PTree;
    sp1B0: PTree;
    sp1AC: PTree;
    sp1A8: PTree;
    sp1A4: PTree;
    tree_s3: PTree; {pad1A0}
    temp_fp: integer; {pad19C}
    tree_s0: PTree; {pad198}
    temp_v0: integer; {pad194}
    var_s0: integer; {pad190}
    sp18C: integer;
    sp188: integer;
    sp184: integer;
    sp183: boolean;
    sp182: boolean;
    sp181: char;
    dtype_s1: Datatype;
    sp17C: integer;
    sp17B: u8;
    sp174: cardinal;
    var_s1: cardinal;
    tree_s2: PTree;
    var_s5: integer;
    sp167: boolean;
    sp166: boolean;
    sp165: boolean;
    sp164: boolean;
    sp160: integer;
    sp15F: boolean;
    sp158: integer;
var {extra var here makes sp128 initialize first}
    sp128: array [0..3] of UnkRec_1;
    sp127: boolean;
    
    { Inner functions }

    procedure append_statement(stmt: PTree);
    begin
        statement_list^.next := stmt;
        stmt^.prior := statement_list;
        statement_list := stmt;
    end;

    procedure extend_statement_list(new_list: PTree);
    begin
        statement_list^.next := new_list;
        new_list^.prior := statement_list;

        while new_list^.next <> nil do begin
            new_list^.next^.prior := new_list;
            new_list := new_list^.next;
        end;

        statement_list := new_list;
    end;

    procedure list_insert(list: PTree; sublist: PTree);
    var
        next: ^Tree;
    begin
        next := list^.next;
        list^.next := sublist;

        while (sublist^.next <> nil) do begin
            sublist := sublist^.next;
        end;

        sublist^.next := next;
    end;

    procedure func_0040E2AC(pos: 1..stack_size);
    var
        dtype: Datatype;
    begin
        if dtype_stack[pos] = Ldt then begin
            dtype := Ldt;
        end else begin
            dtype := Jdt;
        end;

        if node_stack[pos] = nil then begin
            node_stack[pos] := ivalue(dtype, 0, value_stack[pos]);
        end else if value_stack[pos] <> 0 then begin
            if (node_stack[pos]^.u.Dtype in [Idt, Jdt, Kdt, Ldt]) then begin
                if value_stack[pos] < 0 then begin
                    node_stack[pos] := build_2op(Uadd, node_stack[pos], ivalue(node_stack[pos]^.u.Dtype, -1, value_stack[pos]));
                end else begin
                    node_stack[pos] := build_2op(Uadd, node_stack[pos], ivalue(node_stack[pos]^.u.Dtype, 0, value_stack[pos]));
                end;
            end else begin
                node_stack[pos] := build_2op(Uadd, node_stack[pos], ivalue(dtype, 0, value_stack[pos]));
            end;

            node_stack[pos]^.u.Lexlev := lexlev_stack[pos];
        end;

        value_stack[pos] := 0;
        lexlev_stack[pos] := 0;
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
    
    procedure func_0040EC54(arg0: PTree);
    var
        var_s0: PTree;
        sp2C : PTree;
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
    s0: PTree;
    v0: PTree;
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

    procedure func_0040EF8C(arg0: PTree);
    begin
        while arg0 <> nil do begin
            sp158 := sp158 + 1;
            arg0^.u.aryoff := sp158;
            arg0 := arg0^.next;
        end;
    end;

    

    procedure func_0040EFBC(arg0: PTree);
    var
        mtag: PTree;
        t: PTree;
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

    procedure func_0040F0B8(arg0: PTree);
    var
        v0: PTree;
        next: PTree;
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
        temp_v0 : PTree;
    begin
        assert(arg0^.u.Opc = Ulab);
        temp_v0 := build_op(Unop);
        temp_v0^.u.I1 := arg0^.u.I1;
        temp_v0^.op1 := arg0;
        temp_v0^.next := sp1A8;
        sp1A8 := temp_v0;
    end;

    function func_0040F230(arg0: PTree): boolean;
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
        var_s2 : PTree;
        var_v0 : PTree;
        temp_v0 : PTree;
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

    statement_list := nil;
    stack_pos := 0;

    while (true) do begin
        readuinstr(ucode, sp1C4);
        case ucode.Opc of

            {Parse different Uopcodes}
            CASE_OPC(Ufsym):
            begin
                gen_sym(ucode);
                if domtag then begin
                    tree_s3 := build_u(ucode);
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
                gen_sym(ucode);
            end;

            CASE_OPC(Umsym):
            begin
                gen_sym(ucode);
                append_statement(build_u(ucode));
                framesz_relocatable := 1;
            end;

            CASE_OPC(Ussym):
            begin
                ucode.constval.chars := sp1C4;
                if (ucode.constval.Ival >= 9) then begin
                    ucode.constval.Ival := 8;
                    ucode.constval.chars^.ss[9] := char(0);
                end;
                new(sp1C4);
                tree_s3 := build_u(ucode);
                tree_s3^.u.Dtype := Mdt;
                append_statement(tree_s3);
            end;

            CASE_OPC(Uinit):
            begin
                if ucode.Dtype in [Mdt, Qdt, Rdt, Sdt, Xdt] then begin
                    ucode.Initval.Chars := sp1C4;
                    new(sp1C4, 1);
                end;
                add_init(ucode);
            end;

            CASE_OPC(Usdef):
            begin
                set_size(ucode.I1, ucode.Length);
            end;

            CASE_OPC(Ubgn):
            begin
                ms_stamp := ucode.Length;
                ls_stamp := ucode.Offset;
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
                 append_statement(build_u(ucode));
            end;

            CASE_OPC(Uendb):
            begin
                 append_statement(build_u(ucode));
            end;

            CASE_OPC(Ucomm),
            CASE_OPC(Uloc),
            CASE_OPC(Uregs):
            begin
                tree_s3 := build_u(ucode);
                if statement_list = nil then begin
                    statement_list := tree_s3;
                    build_tree := tree_s3;
                end else begin
                    append_statement(tree_s3);
                end;

                if (ucode.Opc = Uloc) then begin
                    current_line := ucode.I1;
                end else if (ucode.Opc = Ucomm) then begin
                    ucode.Constval.Chars := sp1C4;
                    if (verbose) then begin
                        if ((statement_list^.prior <> nil) and (statement_list^.prior^.u.Opc = Uent)) then begin
                            sp181 := ' ';
                            var_s0 := ucode.Constval.Ival;
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
                tree_s3 := build_u(ucode);
                tree_s3^.next := sp1AC;
                sp1AC := tree_s3;

                if (ucode.I1 = UCO_VARARGS) then begin
                    sp17C := ucode.Length;
                end else if (sp1AC^.u.I1 = UCO_STACK_REVERSED) then begin
                    reversed_stack := true;
                    first_pmt_offset := -4;
                end else if (sp1AC^.u.I1 = UCO_RSTEXT) then begin
                    resident_text := 1;
                end else if (sp1AC^.u.I1 = UCO_SOURCE) then begin
                    source_language := ucode.Length;
                    if ((ucode.Length = ADA_SOURCE) and (glevel <> 0) and (glevel < 3)) then begin
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
                Assert(stack_pos = 0);
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
                sp1C0 := build_u(ucode);
                sp17C := -1;
                sp166 := false;
                sp165 := false;
                sp183 := false;
                sp15F := false;

                if (statement_list = nil) then begin                
                    build_tree := sp1C0;
                    statement_list := sp1C0;
                    sp158 := 0;
                    sp128[0].unk_00 := UNK_ENUM_A_0;
                    sp128[1].unk_00 := UNK_ENUM_A_0;
                    sp128[2].unk_00 := UNK_ENUM_A_0;
                    sp128[3].unk_00 := UNK_ENUM_A_0;
                end else begin
                    append_statement(sp1C0);
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
                gen_sym(ucode);
                sp167 := IS_PRESERVE_STACK_ATTR(ucode.Extrnal);
            end;

        CASE_OPC(Uaent):
        begin
            sp182 := true;
             append_statement(build_u(ucode));
        end;

        CASE_OPC(Uend):
        begin
             append_statement(sp1A4);
             append_statement(build_u(ucode));


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
                list_insert(sp1C0, sp1BC);
            end;

            if (syms <> nil) then begin
                func_0040EFBC(syms);
                list_insert(sp1C0, syms);
                syms := nil;
            end;

            if (sp1B0 <> nil) then begin
                list_insert(sp1C0, sp1B0);
            end;

            if (sp1AC <> nil) then begin
                list_insert(sp1C0, sp1AC);
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
            tree_s3 := build_u(ucode);
            func_0040F0B8(tree_s3);
            if tree_s3^.u.Lexlev <> 1 then sp17B := 1;
        end;

        CASE_OPC(Udef):
        begin
            if reversed_stack then begin
                assert((ucode.Mtype <> Mmt) or (ucode.Length >= sp184));
            end else begin
                assert((ucode.Mtype <> Mmt) or (ucode.Length >= -sp188));
                
            end;
            tree_s3 := build_u(ucode);
            if (ucode.Mtype = Pmt) then tree_s3^.op1 := sp1B8;
            tree_s3^.next := sp1B0;
            sp1B0 := tree_s3;
        end;

        CASE_OPC(Uvreg):
        begin
            ucode.Constval.Ival := -1;
            func_0040EC54(build_u(ucode));
        end;

        CASE_OPC(Uunal):
        begin
             append_statement(build_u(ucode));
        end;

        CASE_OPC(Uret):
        begin
            assert(stack_pos = 0);
            tree_s3 := build_op(Uujp);
            tree_s3^.op2 := sp1A4;
            append_statement(tree_s3);
        end;

        CASE_OPC(Uujp):
        begin
            assert(stack_pos = 0);
            tree_s3 := build_u(ucode);
            tree_s3^.op2 := find_label(ucode.I1);
             append_statement(tree_s3);
        end;

        CASE_OPC(Uijp):
        begin
            func_0040E2AC(stack_pos);
            tree_s3 := build_u1(ucode, node_stack[stack_pos]);
            stack_pos := stack_pos - 1;
            assert(stack_pos = 0);
            append_statement(tree_s3);
        end;

        CASE_OPC(Utjp),
        CASE_OPC(Ufjp):
        begin
            func_0040E2AC(stack_pos);
            tree_s3 := build_u2(ucode, node_stack[stack_pos], find_label(ucode.I1));
            stack_pos :=  stack_pos - 1;
            assert(stack_pos = 0);
            if is_constant(tree_s3^.op1) then begin
                 if ((not is_zero(tree_s3^.op1)) <> (ucode.Opc = Utjp)) then begin
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
            append_statement(tree_s3);
        end;

        CASE_OPC(Ulab):
        begin
            assert(stack_pos = 0);
            tree_s3 := find_label(ucode.I1);
            tree_s3^.u := ucode;
            tree_s3^.u.Offset2 := 0;
            append_statement(tree_s3);
            if IS_IJP_ATTR(ucode.Lexlev) then begin
                func_0040F1BC(tree_s3);
            end;
            if IS_EXCEPTION_ATTR(ucode.Lexlev) then begin
                sp166 := true;
            end;
        end;

        CASE_OPC(Uldef):
        begin
            assert(stack_pos = 0);
            tree_s3 := search_label(ucode.I1);
            if tree_s3 = nil then begin
                report_error(Internal, 1409, "build.p", "LDEF before LAB");
            end else begin
                tree_s3^.u.Lexlev := ucode.Lexlev;
                tree_s3^.u.Length := ucode.Length;
            end;
        end;

        CASE_OPC(Uclab):
        begin
            assert(stack_pos = 0);
            tree_s3 := find_label(ucode.I1);
            tree_s3^.u := ucode;
            tree_s3^.u.Offset := 0;
            tree_s3^.u.Offset2 := 1;
            var_s5 := -1;
            var_s4 := -1;

            append_statement(tree_s3);
            tree_s2 := statement_list;
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
            for var_s1 := 1 to ucode.Length do begin
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
                append_statement(tree_s0);
            end;
            tree_s3 := build_op(Uclab);
            tree_s3^.u.Length := 0;
            tree_s3^.u.I1 := ucode.I1;
            append_statement(tree_s3);
        end;

        CASE_OPC(Uxjp):
        begin
            if (node_stack[stack_pos] = nil) and (search_label(ucode.I1) <> nil) then begin
                tree_s3 := new_tree();
                tree_s3^.u.Opc := Uujp;

                sp174 := value_stack[stack_pos] - ucode.lbound;
                if (sp174 >= ucode.hbound) then begin
                    tree_s3^.op2 := find_label(ucode.Length);
                end else begin
                    tree_s0 := find_label(ucode.I1);
                    assert(tree_s0^.u.Opc = Uclab);
                    sp174 := sp174 + 1;
                    repeat begin
                        tree_s0 := tree_s0^.next;
                        assert((tree_s0 <> nil) and (tree_s0^.u.Opc = Uujp));
                        sp174 := sp174 - 1;
                    end until sp174 = 0;
                    tree_s3^.op2 := tree_s0^.op2;
                end;
                append_statement(tree_s3);
            end else begin
                value_stack[stack_pos] := value_stack[stack_pos] - ucode.lbound;
                lexlev_stack[stack_pos] := 0;
                func_0040E2AC(stack_pos);
                tree_s2 := node_stack[stack_pos];
                if ucode.Dtype in [Idt, Kdt, Wdt] then begin
                    dtype_s1 := Kdt;
                end else begin
                    dtype_s1 := Ldt;
                end;
                tree_s2^.u.Dtype := dtype_s1;
                if (tree_s2^.u.Opc = Uand) and 
                   (((tree_s2^.op2^.u.Opc = Uldc) and (tree_s2^.op2^.u.Constval.Ival <= ucode.hbound - ucode.lbound) and (tree_s2^.op2^.u.Constval.Ival > 0)) or 
                    ((tree_s2^.op1^.u.Opc = Uldc) and (tree_s2^.op1^.u.Constval.Ival <= ucode.hbound - ucode.lbound) and (tree_s2^.op1^.u.Constval.Ival > 0)))then begin
                        append_statement(build_u2(ucode, tree_s2, find_label(ucode.I1)));
                        stack_pos := stack_pos - 1;
                        assert(stack_pos = 0);
                        continue;
                end else if (statement_list^.u.Opc = Ustr) and (statement_list^.op1^.u.Opc = Uand) and
                    (((statement_list^.op1^.op1^.u.Opc = Uldc) and (statement_list^.op1^.op1^.u.Constval.Ival <= ucode.hbound - ucode.lbound) and (statement_list^.op1^.op1^.u.Constval.Ival > 0)) or 
                     ((statement_list^.op1^.op2^.u.Opc = Uldc) and (statement_list^.op1^.op2^.u.Constval.Ival <= ucode.hbound - ucode.lbound) and (statement_list^.op1^.op2^.u.Constval.Ival > 0))) then begin
                    if tree_s2^.u.Opc = Ulod then begin
                        tree_s3 := tree_s2;
                    end else begin
                        tree_s3 := tree_s2^.op1;
                    end;
                    if (tree_s3^.u.Mtype = statement_list^.u.Mtype) 
                    then if ((tree_s2^.u.Opc <> Uadd) or (tree_s2^.op2 = nil) or (tree_s2^.op2^.u.Opc <> Uldc) or (tree_s2^.op2^.u.Constval.Ival >= 0)) 
                    then if (tree_s3^.u.I1 = statement_list^.u.I1) 
                    then if ((lsb_first and (tree_s3^.u.lbound = statement_list^.u.lbound)) or 
                           ((not lsb_first) and (tree_s3^.u.lbound + tree_s3^.u.hbound = statement_list^.u.lbound + statement_list^.u.hbound))) 
                    then if (statement_list^.u.hbound = tree_s3^.u.hbound) then begin
                        append_statement(build_u2(ucode, tree_s2, find_label(ucode.I1)));
                        stack_pos := stack_pos - 1;
                        assert(stack_pos = 0);
                        continue;
                    end;
                end;
                tree_s0 := build_2op(Ufjp, build_2op(Ules, dup_tree(tree_s2), ivalue(dtype_s1, 0, (ucode.hbound - ucode.lbound + 1))), find_label(ucode.Length));
                tree_s0^.u.Lexlev := 0;
                append_statement(tree_s0);
                append_statement(build_u2(ucode, tree_s2, find_label(ucode.I1)));
            end;
            stack_pos := stack_pos - 1;
            assert(stack_pos = 0);
        end;

        CASE_OPC(Umst):
        begin
            append_statement(build_u(ucode));
        end;

        CASE_OPC(Upar),
        CASE_OPC(Upmov),
        CASE_OPC(Umpmv):
        begin
            sp1EC := max(sp1EC, abs(ucode.Offset - first_pmt_offset) + ucode.Length);
            sp15F := true;
            if (stack_pos = 0) and (source_language = C_SOURCE) then begin
                stack_pos := 2;
                writeln(err, "Internal error due to probable C source error. Please recompile your C code with the -prototypes flag to cc(1)");
                report_error(Internal, 1708, "build.p", "Cannot continue");
            end;
            func_0040E2AC(stack_pos);
            tree_s3 := build_u1(ucode, node_stack[stack_pos]);
            stack_pos := stack_pos - 1;
            assert(stack_pos = 0);
            extend_statement_list(tree_s3);
        end;

        CASE_OPC(Urpar):
        begin
            sp1EC := max(sp1EC, abs(ucode.Offset - first_pmt_offset) + ucode.Length);
            assert(stack_pos = 0);
            ucode.Offset2 := ucode.Lexlev * 4;
            append_statement(build_u(ucode));
        end;

        CASE_OPC(Ucup),
        CASE_OPC(Urcuf):
        begin
            assert(stack_pos = 0);
            tree_s3 := build_u(ucode);
            sp1F0 := sp1F0 + 1;
            if not IS_RETURN_ATTR(ucode.Extrnal) then begin
                pseudo_leaf := 0;
            end;
            append_statement(tree_s3);
        end;

        CASE_OPC(Uicuf):
        begin
            func_0040E2AC(stack_pos);
            tree_s3 := build_u1(ucode, node_stack[stack_pos]);
            stack_pos := stack_pos - 1;
            assert(stack_pos = 0);
            if not IS_THUNK_CALL_ATTR(ucode.Extrnal) then begin
                sp1F0 := sp1F0 + 1;
                pseudo_leaf := 0;
            end;
            append_statement(tree_s3);
        end;

        CASE_OPC(Umov):
        begin
            func_0040E2AC(stack_pos);
            func_0040E2AC(stack_pos - 1);
            tree_s3 := build_u2(ucode, node_stack[stack_pos - 1], node_stack[stack_pos]);
            stack_pos := pred(pred(stack_pos));
            assert(stack_pos = 0);
            append_statement(tree_s3);
        end;

        CASE_OPC(Uaos),
        CASE_OPC(Ustr),
        CASE_OPC(Ustsp):
        begin
            if ucode.Opc = Ustr then ucode.Constval.Ival := 0;
            if (ucode.Opc = Ustr) and (ucode.Mtype = Rmt) then ucode.Offset := ucode.Offset * 4;
            if (ucode.Opc = Ustr) and (ucode.Mtype = Pmt) and (ucode.I1 = 0) then begin
                sp1EC := max(sp1EC, abs(ucode.Offset - first_pmt_offset) + ucode.Length);
            end;
            if (ucode.Opc = Uaos) or (ucode.Opc = Ustsp) then begin
                use_fp := 1;
            end;
            func_0040E2AC(stack_pos);
            tree_s3 := build_u1(ucode, node_stack[stack_pos]);
            if (ucode.Opc = Ustr) 
               and (node_stack[stack_pos]^.u.Opc = Ulod)
               and (ucode.Offset = node_stack[stack_pos]^.u.Offset)
               and (ucode.Dtype = node_stack[stack_pos]^.u.Dtype)
               and (ucode.Mtype = node_stack[stack_pos]^.u.Mtype)
               and (ucode.I1 = node_stack[stack_pos]^.u.I1)
               and (ucode.Length = node_stack[stack_pos]^.u.Length)
               and not IS_VOLATILE_ATTR(ucode.Lexlev) then begin
                stack_pos := stack_pos - 1;
                assert(stack_pos = 0);
            end else begin
                stack_pos := stack_pos - 1;
                if (ucode.Opc = Uaos) and (stack_pos <> 0) then begin
                    writeln(err, "Found Uaos u-code in unexpected spot. Perhaps value returned from alloca(3) was not assigned to simple variable. (See alloca man page)");
                    flush(err);
                    report_error(Internal, 1807, "build.p", "Cannot continue");
                end else begin
                    assert(stack_pos = 0);
                end;
                extend_statement_list(tree_s3);
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
            ucode.Offset2 := 0;
            if nooffsetopt then func_0040E2AC(stack_pos - 1);
            if node_stack[stack_pos - 1] = nil then begin
                temp_fp := value_stack[stack_pos - 1] + ucode.Offset;
                ucode.Offset := (bitxor(bitand(temp_fp, 16#FFFF), 16#8000) - 16#8000);
                if basicint = 1 then begin
                    node_stack[stack_pos - 1] := dwvalue(Wdt, temp_fp - ucode.Offset);
                end else begin
                    node_stack[stack_pos - 1] := ivalue(Adt, 0, temp_fp - ucode.Offset);
                end;
            end else begin
                ucode.Offset := ucode.Offset + value_stack[stack_pos - 1];
            end;
            value_stack[stack_pos - 1] := 0;
            func_0040E2AC(stack_pos);
            tree_s3 := build_u2(ucode, node_stack[stack_pos - 1], node_stack[stack_pos]);
            stack_pos := pred(pred(stack_pos));
            assert(stack_pos = 0);
            extend_statement_list(tree_s3);
        end;

        CASE_OPC(Uistr):
        begin
            ucode.Offset2 := ucode.Offset;
            if nooffsetopt then func_0040E2AC( stack_pos - 1);
            if stack_pos < 2 then stack_pos := 2;
            if node_stack[stack_pos - 1] = nil then begin
                temp_fp := value_stack[stack_pos - 1] + ucode.I1;
                ucode.Offset := bitxor(bitand(temp_fp, 16#FFFF), 16#8000) - 16#8000;
                if basicint = 1 then begin
                    node_stack[stack_pos - 1] := dwvalue(Wdt, temp_fp - ucode.Offset);
                end else begin
                    node_stack[stack_pos - 1] := ivalue(Adt, 0, temp_fp - ucode.Offset);
                end;
            end else begin
                ucode.Offset := ucode.I1 + value_stack[stack_pos - 1];
            end;
            value_stack[stack_pos - 1] := 0;
            func_0040E2AC(stack_pos);
            tree_s3 := build_u2(ucode, node_stack[stack_pos - 1], node_stack[stack_pos]);
            stack_pos :=  pred(pred(stack_pos));
            assert(stack_pos = 0);

            extend_statement_list(tree_s3);
        end;

        CASE_OPC(Uirst):
        begin
            func_0040E2AC( stack_pos - 1);
            if stack_pos < 2 then stack_pos := 2;
            value_stack[stack_pos - 1] := 0;
            func_0040E2AC(stack_pos);
            tree_s3 := build_u2(ucode, node_stack[stack_pos - 1], node_stack[stack_pos]);
            stack_pos :=  pred(pred(stack_pos));
            assert(stack_pos = 0);
            extend_statement_list(tree_s3);
        end;

        CASE_OPC(Urstr):
        begin
            tree_s3 := build_op(Ulod);
            tree_s3^.u.Mtype := Rmt;
            tree_s3^.u.Offset := ucode.Lexlev * 4;
            tree_s3^.u.Length := ucode.Length;
            tree_s3^.u.Dtype := ucode.Dtype;
            tree_s3^.u.I1 := ucode.I1;
            tree_s3^.u.Lexlev := 0;
            tree_s0 := build_u1(ucode, tree_s3);
            tree_s0^.u.Opc := Ustr;
            tree_s0^.u.Offset2 := 0;
            tree_s0^.u.Lexlev := 0;
            append_statement(tree_s0);
        end;

        CASE_OPC(Urlod):
        begin
            tree_s0 := build_u(ucode);
            tree_s0^.u.Opc := Ulod;
            tree_s0^.u.Offset2 := 0;
            tree_s0^.u.Lexlev := 0;

            tree_s3 := build_op(Ustr);
            tree_s3^.u.Mtype := Rmt;
            tree_s3^.u.Offset := ucode.Lexlev * 4;
            tree_s3^.u.Offset2 := 0;
            tree_s3^.u.Length := ucode.Length;
            tree_s3^.u.Dtype := ucode.Dtype;
            tree_s3^.u.I1 := ucode.I1;
            tree_s3^.u.Lexlev := 0;
            tree_s3^.op1 := tree_s0;
            append_statement(tree_s3);
        end;

        CASE_OPC(Urldc):
        begin
            if ucode.Dtype in [Mdt,Qdt,Rdt,Sdt,Xdt] then begin
                ucode.Constval.Chars := sp1C4;
                new(sp1C4);
            end;
            tree_s0 := build_u(ucode);
            tree_s0^.u.Opc := Uldc;
            if ((ucode.Dtype = Fdt) or (ucode.Dtype = Ndt)) then begin
                tree_s0^.u.Opc := Ulda;
                tree_s0^.u.I1 := ucode.Constval.Ival;
                tree_s0^.u.Dtype := addr_dtype;
                tree_s0^.u.Mtype := Smt;
                tree_s0^.u.Offset := 0;
                tree_s0^.u.Offset2 := 0;
                tree_s0^.u.Length := unitsperaddr;
            end else if (ucode.Dtype = Gdt) then begin
                tree_s0 := build_1op(Ucg2, find_label(ucode.Constval.Ival));
                tree_s0^.u.Dtype := Gdt;
            end;
            tree_s3 := build_op(Ustr);
            tree_s3^.u.Dtype := ucode.Dtype;
            tree_s3^.u.Mtype := Rmt; 
            tree_s3^.u.Offset := ucode.I1 * 4;
            tree_s3^.u.Offset2 := 0;
            tree_s3^.u.Length := ucode.Length;
            tree_s3^.op1 := tree_s0;
            append_statement(tree_s3);
        end;

        CASE_OPC(Urlda):
        begin
            tree_s0 := build_u(ucode);
            tree_s0^.u.Opc := Ulda;
            tree_s0^.u.Dtype := addr_dtype;
            if ucode.Mtype = Pmt then func_0040E474(tree_s0);
            tree_s3 := build_op(Ustr);
            tree_s3^.u.Dtype := addr_dtype;
            tree_s3^.u.Mtype := Rmt;
            tree_s3^.u.Offset := ucode.Length * unitsperaddr; {0x28(v0)}
            tree_s3^.u.Offset2 := 0; {0x30(v0)}
            tree_s3^.u.Length := unitsperaddr; {0x28(v0)}
            tree_s3^.op1 := tree_s0; {0(v0)}
            tree_s0^.u.Length := unitsperaddr; {0x28(s0)}
            append_statement(tree_s3);
        end;

        CASE_OPC(Ulca):
        begin
            ucode.Constval.Chars := sp1C4;
            new(sp1C4);
            tree_s3 := build_u(ucode);
            stack_pos := stack_pos + 1;
            node_stack[stack_pos] := tree_s3;
            value_stack[stack_pos] := 0;
            lexlev_stack[stack_pos] := 0;
        end;

        CASE_OPC(Ulda):
        begin
            ucode.Dtype := addr_dtype;
            tree_s3 := build_u(ucode);
            if ucode.Mtype = Mmt then begin
                if reversed_stack then begin
                    sp184 := max(sp184, ucode.Offset2);
                end else begin
                    sp188 := min(sp188, ucode.Offset2);
                end;
            end else if ucode.Mtype = Pmt then begin
                func_0040E474(tree_s3);
            end;
            stack_pos := stack_pos + 1;
            node_stack[stack_pos] := tree_s3;
            value_stack[stack_pos] := 0;
            lexlev_stack[stack_pos] := 0;
        end;
        
        CASE_OPC(Uldc):
        begin
            stack_pos := stack_pos + 1;
            value_stack[stack_pos] := 0;
            lexlev_stack[stack_pos] := 0;
            dtype_stack[stack_pos] := Zdt;
            dtype_s1 := ucode.Dtype;
            if ucode.Dtype in [Mdt,Qdt,Rdt,Sdt] then begin
                ucode.Constval.Chars := sp1C4;
                new(sp1C4);
                node_stack[stack_pos] := build_u(ucode);
            end else if (ucode.Dtype = Fdt) or (ucode.Dtype = Ndt) then begin
                tree_s3 := build_op(Ulda);
                tree_s3^.u.I1 := ucode.Constval.Ival;
                tree_s3^.u.Mtype := Smt;
                tree_s3^.u.Dtype := addr_dtype;
                tree_s3^.u.Offset := 0;
                node_stack[stack_pos] := tree_s3;
            end else if ucode.Dtype = Gdt then begin
                tree_s3 := build_1op(Ucg2, find_label(ucode.Constval.Ival));
                tree_s3^.u.Dtype := Gdt;
                node_stack[stack_pos] := tree_s3;
            end else if ucode.Dtype in [Idt,Kdt] then begin
                node_stack[stack_pos] := build_u(ucode);
            end else begin
                node_stack[stack_pos] := nil;
                value_stack[stack_pos] := ucode.Constval.Ival;
                dtype_stack[stack_pos] := ucode.Dtype;
            end;
        end;
        
        CASE_OPC(Uldrc):
        begin
            stack_pos := stack_pos + 1;
            value_stack[stack_pos] := 0;
            lexlev_stack[stack_pos] := 0;
            dtype_stack[stack_pos] := Zdt;
            node_stack[stack_pos] := build_u(ucode);
        end;
        
        CASE_OPC(Uldap),
        CASE_OPC(Uldsp),
        CASE_OPC(Ulod):
        begin
            if (ucode.Opc = Ulod) and (ucode.Mtype = Rmt) then ucode.Offset := ucode.Offset * 4;
            tree_s3 := build_u(ucode);
            tree_s3^.u.Offset2 := 0;
            stack_pos := stack_pos + 1;
            node_stack[stack_pos] := tree_s3;
            value_stack[stack_pos] := 0;
            lexlev_stack[stack_pos] := 0;
            if (tree_s3^.u.Opc = Ulod) and (tree_s3^.u.Mtype = Pmt) then func_0040E474(tree_s3);
            if (tree_s3^.u.Opc = Uldsp) or (tree_s3^.u.Opc = Uldap) then tree_s3^.u.Dtype := addr_dtype;
        end;

        CASE_OPC(Uchkt):
        begin
            func_0040E2AC(stack_pos);
            ucode.I1 := 10;
            tree_s3 := build_u1(ucode, node_stack[stack_pos]);
            stack_pos := stack_pos - 1;
            append_statement(tree_s3);
        end;

        CASE_OPC(Utpeq),
        CASE_OPC(Utpge),
        CASE_OPC(Utpgt),
        CASE_OPC(Utple),
        CASE_OPC(Utplt),
        CASE_OPC(Utpne):
        begin
            func_0040E2AC(stack_pos - 1);
            func_0040E2AC(stack_pos);
            tree_s3 := build_u2(ucode, node_stack[stack_pos - 1], node_stack[stack_pos]);
            stack_pos :=  pred(pred(stack_pos));
            if (tree_s3^.u.Dtype in [Qdt, Rdt, Xdt]) then begin
                append_statement(tree_s3);
            end else begin
                tree_s3^.u.Opc := trap_to_compare[ucode.Opc];
                tree_s3 := build_1op(Uchkt, tree_s3);
                tree_s3^.u.I1 := ucode.I1;
                append_statement(tree_s3);
            end;
        end;

        CASE_OPC(Ucvt):
        begin
            if not (ucode.Dtype in similar_data_types[ucode.Dtype2]) or
                (IS_OVERFLOW_ATTR(ucode.Lexlev) and ((ucode.Dtype in [Idt, Jdt]) <> (ucode.Dtype2 in [Idt, Jdt])) or
                ((opcode_arch = ARCH_64) and not (ucode.Dtype in similar_data_types_dw[ucode.Dtype2]))) then begin
                func_0040E2AC(stack_pos);
                node_stack[stack_pos] := build_u1(ucode, node_stack[stack_pos]);
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
            func_0040E2AC(stack_pos);
            node_stack[stack_pos] := build_u1(ucode, node_stack[stack_pos]);
        end;

        CASE_OPC(Uneg):
        begin
            if IS_OVERFLOW_ATTR(ucode.Lexlev) and (value_stack[stack_pos] = 16#80000000) then begin
                func_0040E2AC(stack_pos);
            end;
            value_stack[stack_pos] := -value_stack[stack_pos];
            if node_stack[stack_pos] <> nil then begin
                node_stack[stack_pos] := build_u1(ucode, node_stack[stack_pos]);
            end;
        end;

        CASE_OPC(Uinc):
        begin
            temp_fp := value_stack[stack_pos] + ucode.I1;
            if IS_OVERFLOW_ATTR(ucode.Lexlev) and (add_overflow(ucode.Dtype, value_stack[stack_pos], ucode.I1)) then begin
                func_0040E2AC(stack_pos);
                temp_fp := ucode.I1;
            end;
            value_stack[stack_pos] := temp_fp;
            lexlev_stack[stack_pos] := bitor(lexlev_stack[stack_pos], ucode.Lexlev);
        end;

        CASE_OPC(Udec):
        begin
            temp_fp := value_stack[stack_pos] - ucode.I1;
            if (IS_OVERFLOW_ATTR(ucode.Lexlev) and (sub_overflow(ucode.Dtype, value_stack[stack_pos], ucode.I1))) then begin
                func_0040E2AC(stack_pos);
                temp_fp := -ucode.I1;
            end;
            value_stack[stack_pos] := temp_fp;
            lexlev_stack[stack_pos] := bitor(lexlev_stack[stack_pos], ucode.Lexlev);
        end;

        CASE_OPC(Uisld):
        begin
            ucode.Offset2 := 0;
            if nooffsetopt then begin
                func_0040E2AC(stack_pos);
            end;
            if node_stack[stack_pos] = nil then begin
                temp_fp := value_stack[stack_pos] + ucode.Offset;
                ucode.Offset := bitxor(bitand(temp_fp, 16#FFFF), 16#8000) - 16#8000;
                if basicint = 1 then begin
                    node_stack[stack_pos] := dwvalue(Wdt, temp_fp - ucode.Offset);
                end else begin
                    node_stack[stack_pos] := ivalue(Adt, 0, temp_fp - ucode.Offset);
                end;
            end else begin
                ucode.Offset := ucode.Offset + value_stack[stack_pos];
            end;
           
            node_stack[stack_pos] := build_u1(ucode, node_stack[stack_pos]);
            value_stack[stack_pos] := 0;
            lexlev_stack[stack_pos] := 0;
        end;

        CASE_OPC(Uilod):
        begin
            ucode.Offset2 := ucode.Offset;
            if nooffsetopt then begin
                func_0040E2AC(stack_pos);
            end;
            if (node_stack[stack_pos] = nil) then begin
                temp_fp := value_stack[stack_pos] + ucode.I1;
                ucode.Offset := bitxor(bitand(temp_fp, 16#FFFF), 16#8000) - 16#8000;
                if basicint = 1 then begin
                    node_stack[stack_pos] := dwvalue(Wdt, temp_fp - ucode.Offset);
                end else begin
                    node_stack[stack_pos] := ivalue(Adt, 0, temp_fp - ucode.Offset);
                end;
            end else begin
                ucode.Offset := ucode.I1 + value_stack[stack_pos];
            end;
            node_stack[stack_pos] := build_u1(ucode, node_stack[stack_pos]);
            value_stack[stack_pos] := 0;
            lexlev_stack[stack_pos] := 0;
        end;
        
        CASE_OPC(Uirld):
        begin
            func_0040E2AC(stack_pos);
            node_stack[stack_pos] := build_u1(ucode, node_stack[stack_pos]);
            value_stack[stack_pos] := 0;
            lexlev_stack[stack_pos] := 0;
        end;
        
        CASE_OPC(Udup):
        begin
            stack_pos := stack_pos + 1;
            if node_stack[stack_pos - 1] = nil then begin
                node_stack[stack_pos] := nil;
                value_stack[stack_pos] := value_stack[stack_pos - 1];
            end else begin
                func_0040E2AC(stack_pos - 1);
                node_stack[stack_pos] := dup_tree(node_stack[stack_pos - 1]);
                value_stack[stack_pos] := 0;
            end;
            lexlev_stack[stack_pos] := 0;
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
            if IS_OVERFLOW_ATTR(ucode.Lexlev) then if
                ((((node_stack[stack_pos - 1] <> nil) and (ucode.Dtype <> node_stack[stack_pos - 1]^.u.Dtype))
            or ((node_stack[stack_pos] <> nil) and (ucode.Dtype <> node_stack[stack_pos]^.u.Dtype))
            or (ucode.Lexlev <> lexlev_stack[stack_pos - 1])
            or (ucode.Lexlev <> lexlev_stack[stack_pos]))) then begin
                func_0040E2AC(stack_pos - 1);
                func_0040E2AC(stack_pos);
            end;
            case ucode.Opc of 
            CASE_OPC(Uadd):
            begin
                if IS_OVERFLOW_ATTR(ucode.Lexlev) and add_overflow(ucode.Dtype, value_stack[stack_pos - 1], value_stack[stack_pos]) then begin
                    temp_fp := value_stack[stack_pos - 1];
                    sp18C := lexlev_stack[stack_pos - 1];
                    value_stack[stack_pos - 1] := 0;
                    lexlev_stack[stack_pos - 1] := 0;
                    func_0040E2AC(stack_pos);
                end else begin
                    temp_fp := value_stack[stack_pos - 1] + value_stack[stack_pos];
                    value_stack[stack_pos - 1] := 0;
                    value_stack[stack_pos] := 0;
                    sp18C := lexlev_stack[stack_pos - 1] ! lexlev_stack[stack_pos] ! ucode.Lexlev;
                end;
                if node_stack[stack_pos] = nil then begin
                    value_stack[stack_pos - 1] := temp_fp;
                    lexlev_stack[stack_pos - 1] := lexlev_stack[stack_pos - 1] ! ucode.Lexlev;
                    stack_pos := stack_pos - 1;
                    continue;
                end else if node_stack[stack_pos - 1] = nil then begin
                    node_stack[stack_pos - 1] := node_stack[stack_pos];
                    value_stack[stack_pos - 1] := temp_fp;
                    lexlev_stack[stack_pos - 1] := lexlev_stack[stack_pos] ! ucode.Lexlev;
                    stack_pos :=  stack_pos - 1;
                    continue;
                end;
            end;
            
            CASE_OPC(Ubsub), CASE_OPC(Usub):
            begin
                if ucode.Opc = Ubsub then ucode.Opc := Usub;
                if IS_OVERFLOW_ATTR(ucode.Lexlev) and sub_overflow(ucode.Dtype, value_stack[stack_pos - 1], value_stack[stack_pos]) then begin
                    temp_fp := value_stack[stack_pos - 1];
                    sp18C := lexlev_stack[stack_pos - 1];
                    value_stack[stack_pos - 1] := 0;
                    func_0040E2AC(stack_pos);
                end else begin
                    temp_fp := value_stack[stack_pos - 1] - value_stack[stack_pos];
                    value_stack[stack_pos - 1] := 0;
                    value_stack[stack_pos] := 0;
                    sp18C := lexlev_stack[stack_pos - 1] ! lexlev_stack[stack_pos] ! ucode.lexlev;
                end;
                if node_stack[stack_pos] = nil then begin
                    value_stack[stack_pos - 1] := temp_fp;
                    lexlev_stack[stack_pos - 1] := lexlev_stack[stack_pos - 1] ! ucode.Lexlev;
                    stack_pos := stack_pos - 1;
                    continue;
                end else if node_stack[stack_pos - 1] = nil then begin
                    value_stack[stack_pos - 1] := temp_fp;
                    lexlev_stack[stack_pos - 1] := sp18C;
                    node_stack[stack_pos - 1] := build_1op(Uneg, node_stack[stack_pos]);
                    node_stack[stack_pos - 1]^.u.Lexlev := node_stack[stack_pos]^.u.Lexlev;
                    stack_pos := stack_pos - 1;
                    continue;
                end;
            end;
            
            CASE_OPC(Umpy):
            begin
                if IS_OVERFLOW_ATTR(ucode.Lexlev) then begin 
                    {empty, likely debug}
                end else if node_stack[stack_pos] = nil then begin
                    temp_fp := value_stack[stack_pos - 1] * value_stack[stack_pos];
                    value_stack[stack_pos - 1] := 0;
                    if node_stack[stack_pos - 1] = nil then begin
                        stack_pos :=  stack_pos - 1;
                        value_stack[stack_pos] := temp_fp;
                        continue;
                    end;
                end else if node_stack[stack_pos - 1] = nil then begin
                    temp_fp := value_stack[stack_pos] * value_stack[stack_pos - 1];
                    value_stack[stack_pos] := 0;
                end;
            end;
            
            CASE_OPC(Uixa):
            begin
                temp_fp := value_stack[stack_pos - 1] + value_stack[stack_pos] * ucode.I1;
                value_stack[stack_pos - 1] := 0;
                value_stack[stack_pos] := 0;
                if node_stack[stack_pos] = nil then begin
                    stack_pos := stack_pos - 1;
                    value_stack[stack_pos] := temp_fp;
                    continue;
                end else if ucode.I1 <> 1 then begin
                    node_stack[stack_pos] := build_2op(Umpy, node_stack[stack_pos], ivalue(Ldt, 0, ucode.I1));
                    node_stack[stack_pos]^.u.Lexlev := ucode.Lexlev;
                end;
                ucode.Opc := Uadd;
            end;
            
            CASE_OPC(Uequ), CASE_OPC(Uneq):
            begin
                if node_stack[stack_pos] = nil then begin
                    temp_fp := value_stack[stack_pos - 1];
                end else if node_stack[stack_pos - 1] = nil then begin
                    temp_fp := value_stack[stack_pos];
                end else temp_fp := min(value_stack[stack_pos - 1], value_stack[stack_pos]);
                value_stack[stack_pos - 1] := value_stack[stack_pos - 1] - temp_fp;
                value_stack[stack_pos] := value_stack[stack_pos] - temp_fp;
                temp_fp := 0;
            end;
            
            CASE_OPC(Ugeq), CASE_OPC(Ugrt), CASE_OPC(Uleq), CASE_OPC(Ules):
            begin
                if (value_stack[stack_pos - 1] <> 0) and (value_stack[stack_pos] = 0) then begin
                    swap_tree(node_stack[stack_pos - 1], node_stack[stack_pos]);
                    swap_int(value_stack[stack_pos - 1], value_stack[stack_pos]);
                    ucode.Opc := reverse[ucode.Opc];
                end;
                if ucode.Dtype = Jdt then begin
                    if (node_stack[stack_pos] = nil) or (node_stack[stack_pos]^.u.Dtype = Jdt) then begin
                        if (value_stack[stack_pos] = 1) and (ucode.Opc = Ules) then begin
                            ucode.Opc := Uleq;
                            value_stack[stack_pos] := 0;
                        end else if (value_stack[stack_pos] = 1) and (ucode.Opc = Ugeq) then begin
                            ucode.Opc := Ugrt;
                            value_stack[stack_pos] := 0;
                        end else if (value_stack[stack_pos] = -1) and (ucode.Opc = Uleq) then begin
                            ucode.Opc := Ules;
                            value_stack[stack_pos] := 0;
                        end else if (value_stack[stack_pos] = -1) and (ucode.Opc = Ugrt) then begin
                            ucode.Opc := Ugeq;
                            value_stack[stack_pos] := 0;
                        end;
                    end;
                end;
            end;
            
            CASE_OPC(Umax), CASE_OPC(Umin):;
            
            CASE_OPC(Ushl), CASE_OPC(Ushr):
            begin
                value_stack[stack_pos] := value_stack[stack_pos] & 16#1F;
            end;
            
            CASE_OPC(Umod):
            begin
                if (node_stack[stack_pos] = nil) and (value_stack[stack_pos] <> 0) and (node_stack[stack_pos - 1] <> nil) and (node_stack[stack_pos - 1]^.u.Dtype <> Ldt) then begin
                    value_stack[stack_pos - 1] := value_stack[stack_pos - 1] mod value_stack[stack_pos];
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
            func_0040E2AC(stack_pos);
            func_0040E2AC(stack_pos - 1);
            tree_s3 := build_u2(ucode, node_stack[stack_pos - 1], node_stack[stack_pos]);
            stack_pos := stack_pos - 1;
            node_stack[stack_pos] := tree_s3;
            value_stack[stack_pos] := temp_fp;
            lexlev_stack[stack_pos] := sp18C;
            
        end;
        
        CASE_OPC(Uidx):
        begin
            if IS_OVERFLOW_ATTR(ucode.Lexlev) and
            (((node_stack[stack_pos - 1] <> nil) and (ucode.Dtype <> node_stack[stack_pos - 1]^.u.Dtype))
            or ((node_stack[stack_pos] <> nil) and (ucode.Dtype <> node_stack[stack_pos]^.u.Dtype))
            or ((node_stack[stack_pos - 2] <> nil) and (ucode.Dtype <> node_stack[stack_pos - 2]^.u.Dtype)) or
            (ucode.Lexlev <> lexlev_stack[stack_pos - 2])
            or (ucode.Lexlev <> lexlev_stack[stack_pos - 1])
            or (ucode.Lexlev <> lexlev_stack[stack_pos])) then begin
                func_0040E2AC(stack_pos);
                func_0040E2AC(stack_pos - 1);
                func_0040E2AC(pred(pred(stack_pos)));
            end;
            if (node_stack[stack_pos - 2] = nil) and (node_stack[stack_pos - 1] = nil) then begin
                tree_s3 := node_stack[stack_pos];
                temp_fp := value_stack[stack_pos] + (value_stack[stack_pos - 1] * value_stack[stack_pos - 2]);
                value_stack[stack_pos - 2] := 0;
                value_stack[stack_pos - 1] := 0;
                value_stack[stack_pos] := 0;
                stack_pos :=  pred(pred(stack_pos));
                lexlev_stack[stack_pos] := 0;
                node_stack[stack_pos] := tree_s3;
                value_stack[stack_pos] := temp_fp;
            end else begin
                if node_stack[stack_pos - 2] = nil then begin
                    temp_fp := value_stack[stack_pos] + (value_stack[stack_pos - 1] * value_stack[stack_pos - 2]);
                    value_stack[stack_pos - 1] := 0;
                    value_stack[stack_pos] := 0;
                end else if node_stack[stack_pos - 1] = nil then begin
                    temp_fp := value_stack[stack_pos] + (value_stack[stack_pos - 1] * value_stack[stack_pos - 2]);
                    value_stack[stack_pos - 2] := 0;
                    value_stack[stack_pos] := 0;
                end else begin
                    temp_fp := value_stack[stack_pos];
                    value_stack[stack_pos] := 0;
                end;
                func_0040E2AC(pred(pred(stack_pos)));
                func_0040E2AC(stack_pos - 1);
                if (node_stack[stack_pos - 2] <> nil) or (value_stack[stack_pos - 2] <> 1) then begin
                    node_stack[stack_pos - 1] := build_2op(Umpy, node_stack[stack_pos - 1], node_stack[stack_pos - 2]);
                    node_stack[stack_pos - 1]^.u.Lexlev := ucode.Lexlev;
                end;

                if node_stack[stack_pos] <> nil then begin
                    tree_s3 := build_2op(Uadd, node_stack[stack_pos], node_stack[stack_pos - 1]);
                end else begin
                    tree_s3 := node_stack[stack_pos - 1];
                end;
                stack_pos :=  pred(pred(stack_pos));
                node_stack[stack_pos] := tree_s3;
                value_stack[stack_pos] := temp_fp;
                lexlev_stack[stack_pos] := 0;
            end;
        end;
        
        CASE_OPC(Uswp):
        begin
            swap_tree(node_stack[stack_pos - 1], node_stack[stack_pos]);
            swap_int(value_stack[stack_pos - 1], value_stack[stack_pos]);
            swap_int(lexlev_stack[stack_pos - 1], lexlev_stack[stack_pos]);
        end;
        
        CASE_OPC(Upop):
        begin
            if not func_0040F230(node_stack[stack_pos]) then begin
                stack_pos :=  stack_pos - 1;
            end else begin
                func_0040E2AC(stack_pos);
                tree_s3 := build_u1(ucode, node_stack[stack_pos]);
                stack_pos := stack_pos - 1;
                tree_s3^.u.Opc := Ustr;
                tree_s3^.u.Mtype := Rmt;
                tree_s3^.u.Offset := 0;
                tree_s3^.u.Offset2 := 0;
                tree_s3^.u.Length := tree_s3^.op1^.u.Length;
                tree_s3^.u.Dtype := tree_s3^.op1^.u.Dtype;
                tree_s3^.u.I1 := tree_s3^.op1^.u.I1;
                append_statement(tree_s3);
            end;
        end;
        
        CASE_OPC(Uxpar): begin
            if stack_pos - 1 = 0 then; {force a3}
            stack_pos :=  stack_pos - 1; 
        end;
        
        CASE_OPC(Ucia):
        begin
            assert(stack_pos = 0);
            ucode.Constval.Chars := sp1C4;
            ucode.Constval.Ival := ucode.Length;
            new(sp1C4);
            sp183 := true;
            tree_s3 := build_u(ucode);
            if (tree_s3^.u.lexlev <> 0) or (sp15F) then begin
                sp1F0 := sp1F0 + 1;
                pseudo_leaf := 0;
            end;
            append_statement(tree_s3);
        end;
        
        CASE_OPC(Ulbgn): begin
            sp160 := ucode.I1;
        end;
        
        CASE_OPC(Ulbdy): begin
            ucode.I1 := sp160;
            append_statement(build_u(ucode));
        end;
        
        CASE_OPC(Umtag):
        begin
            append_statement(build_u(ucode));
            sp158 := ucode.I1;
            if ucode.Lexlev = 3 then non_local_mtag := sp158;
        end;
        
        CASE_OPC(Ualia): append_statement(build_u(ucode));
        
        CASE_OPC(Ueof): report_error(Internal, 2626, "build.p", "bad input to ugen:  end-of-file seen unexpectedly");

        CASE_OPC(Uclbd), CASE_OPC(Ucubd), CASE_OPC(Ulbd), CASE_OPC(Uubd),
        CASE_OPC(Ulend), CASE_OPC(Ulex),
        CASE_OPC(Ultrm), CASE_OPC(Unop),
        CASE_OPC(Ustep), CASE_OPC(Uctrl):;

        otherwise begin
            report_error(Internal, 2634, "build.p", "bad input to ugen:  unexpected u-code"); 
            print_ucode(err, ucode);
            writeln(err);
            flush(err);
        end;
            
        end;
    end;
end;

