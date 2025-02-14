#include "common.h"
#include "report.h"
#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"

{ TODO: find a home for these }
procedure demit_dir0(arg0: integer; arg1: integer); external;
procedure demit_dir1(arg0: integer; arg1: integer; arg2: integer); external;
procedure demit_dir2(arg0: integer; arg1: integer; arg2: integer; arg3: integer); external;
procedure demit_edata(arg0: integer; arg1: integer; arg2: integer); external;
procedure demit_weakext(arg0: integer; arg1: integer); external;
procedure emit_dir0(arg0: integer; arg1: integer); external;
procedure emit_label_val(arg0: integer; arg1: integer; arg2: integer; arg3: cardinal); external;
procedure emit_val(arg0: integer; arg1: u8; var arg2: Valu; arg3: cardinal); external;
function find_val_type(dtype: Datatype; size: cardinal): u8; external;

type
    SymbolInit = packed record
        { 0x00 } u: Bcrec;
        { 0x20 } next: ^SymbolInit;
    end;

    SymbolAlias = packed record
        { 0x00 } unk0: integer;
        { 0x04 } unk4: integer;
        { 0x08 } next: ^SymbolAlias;
    end;

    Symbol = packed record
        { 0x00 } unk0: integer; { id? }
        { 0x04 } unk4: integer;
        { 0x08 } next: ^Symbol; { next in hash table }
        { 0x0C } kind: u8; { TODO: enum }
        { 0x0D } lexlev: u8;
        { 0x0E } unkE: u8; { alignment? }
        { 0x10 } size: cardinal;
        { 0x14 } mtag: integer;
        { 0x18 } data_area: u8; { TODO: enum }
        { 0x1C } unk1C: ^SymbolInit; { inits head? }
        { 0x20 } unk20: ^SymbolInit; { inits tail? }
        { 0x24 } unk24: ^Symbol; { next in inordered_inits }
        { 0x28 } unk28: ^SymbolAlias; { aliases? }
    end;

var
    headof_inordered_inits: ^Symbol := nil;
    tailof_inordered_inits: ^Symbol := nil;
    last_inits_handled: ^SymbolInit := nil;
    last_inits_handled_blkno: integer := 0;

{ TODO: find a home for these }
var
    sym_hash_tab: array[0..255] of ^Symbol;
    non_local_mtag: integer;
    sdata_max: integer;
    apc: u8;
    excpt: u8;
    source_language: integer; { 2=Fortran }

function sym_hash(arg0: integer): integer;
begin
    return arg0 & 16#FF;
end;

function get_data_area(var u: Bcrec): u8;
var
    data_area: integer;
begin
    data_area := GET_DATA_AREA(u.Lexlev);

    if (data_area = DEFAULT_DATA_AREA) then begin
        return 0;
    end else if (data_area = READONLY_DATA_AREA) then begin
        return 1;
    end else if (data_area = SMALL_DATA_AREA) then begin
        return 2;
    end else if (data_area = LARGE_DATA_AREA) then begin
        return 3;
    end else if (data_area = TEXT_AREA) then begin
        return 4;
    end else if (data_area = EXCEPTION_DATA_AREA) then begin
        return 5;
    end else begin
        report_error(Internal, 136, "symbol.p", "illegal data area specified for symbol");
        { @bug: missing return }
    end;
end;

function get_sym_type(var u: Bcrec): integer;
begin
    if ((u.Opc = Ulsym) or (u.Opc = Ufsym)) then begin
        return 4;
    end;

    if (u.Opc = Ugsym) then begin
        return 2;
    end;

    if (u.Opc = Uksym) then begin
        return 3;
    end;

    if (u.Opc = Uosym) then begin
        return 6;
    end;

    if (u.Opc = Umsym) then begin
        return 5;
    end;

    if (u.Opc = Uesym) then begin
        return 1;
    end;

    if (u.Opc = Uasym) then begin
        return 8;
    end;

    if (u.Opc = Ucsym) then begin
        return 7;
    end;

    if (u.Opc = Uent) then begin
        return 9;
    end;

    return 0;
end;

function make_new_sym(arg0: integer; kind: u8; data_area: u8): pointer;
var
    sym: ^Symbol;
    idx: integer;
begin
    new(sym);

    if (sym = nil) then begin
        report_error(Internal, 174, "symbol.p", "Insufficiant memory");
        return sym;
    end;

    idx := sym_hash(arg0) & 16#FF;

    sym^.lexlev := 0;
    sym^.unkE := 0;
    sym^.size := 0;
    sym^.mtag := 0;
    sym^.unk1C := nil;
    sym^.unk20 := nil;
    sym^.unk24 := nil;
    sym^.unk28 := nil;
    sym^.unk4 := 0;

    sym^.next := sym_hash_tab[idx];
    sym_hash_tab[idx] := sym;

    sym^.kind := kind;
    sym^.unk0 := arg0;
    sym^.data_area := data_area;

    return sym;
end;

function change_sym_type(arg0: u8; arg1: u8): integer;
begin
    if ((arg0 = 1) or ((arg0 = 4) and (arg1 = 7))) then return arg1;
    return arg0;
end;

function lookup_sym(arg0: integer): pointer;
var
    sym: ^Symbol;
begin
    sym := sym_hash_tab[sym_hash(arg0) & 16#FF];
    while (sym <> nil) do begin
        if (sym^.unk0 = arg0) then return sym;
        sym := sym^.next;
    end;
    return sym;
end;

procedure clear_sym_tab();
var
    i: integer;
begin
    for i := 0 to 255 do sym_hash_tab[i] := nil;
end;

procedure gen_sym(u: ^Bcrec);
var
    sym: ^Symbol;
    pad: integer;
    kind: u8;
    data_area: u8;
    temp_v0_6: ^SymbolAlias;
begin
    case (u^.Opc) of
        Uent: begin
            if (IS_NOSIDEEFFECT_ATTR(u^.Extrnal)) then kind := 10 else kind := 9;
            sym := make_new_sym(u^.I1, kind, 0);
        end;

        Uasym: begin
            if (((u^.lexlev & 1) = 1) and (u^.Length = 0)) then begin
                emit_dir0(16#12, u^.I1);
                return;
            end;
            sym := lookup_sym(u^.Length);
            if (sym = nil) then begin
                report_error(Internal, 257, "symbol.p", "aliased symbol not found");
                return;
            end;
            new(temp_v0_6);
            if (temp_v0_6 = nil) then begin
                report_error(Internal, 262, "symbol.p", "Insufficiant memory");
                return;
            end;

            temp_v0_6^.unk0 := u^.I1;
            temp_v0_6^.unk4 := u^.lexlev & 1;
            temp_v0_6^.next := sym^.unk28;

            sym^.unk28 := temp_v0_6;
        end;

        Ucsym, Uesym, Ufsym, Ugsym, Ulsym, Uksym: begin
            assert(integer(u^.lexlev) < 16#F4);
            sym := lookup_sym(u^.I1);
            kind := get_sym_type(u^);
            if (sym = nil) then begin
                data_area := get_data_area(u^);
                if ((kind <> 1) or (data_area <> 1)) then begin
                    sym := make_new_sym(u^.I1, kind, data_area);
                    if ((u^.Opc = Ulsym) or (u^.Opc = Ufsym) or (u^.Opc = Ugsym)) then begin
                        sym^.unkE := max(u^.lexlev & ~DATA_AREA_MASK, 2);
                    end;
                end else
                    return;
            end else begin
                sym^.kind := change_sym_type(kind, sym^.kind);
                sym^.unkE := max(sym^.unkE, u^.lexlev & ~DATA_AREA_MASK);
            end;
            if (u^.Length <> 0) then begin
                sym^.size := max(sym^.size, u^.Length);
            end;
        end;

        Umsym: begin
            sym := lookup_sym(u^.I1);
            kind := get_sym_type(u^);
            if (sym = nil) then begin
                sym := make_new_sym(u^.I1, kind, 0);
            end else begin
                sym^.kind := change_sym_type(kind, sym^.kind);
            end;
        end;

        Uosym: ;

        Uhsym: begin
            sym := lookup_sym(u^.I1);
            if (sym = nil) then begin
                report_error(Internal, 310, "symbol.p", "Exception variable symbol not found");
                return;
            end;
            if (excpt <> 0) then begin
                demit_edata(u^.Length, 1, u^.I1);
            end;
        end;

        otherwise report_error(Internal, 327, "symbol.p", "illegal symbol type");
    end
end;

procedure set_lex_level(arg0: integer; lexlev: cardinal);
var
    sym: ^Symbol;
begin
    sym := lookup_sym(arg0);
    sym^.lexlev := max(lexlev, sym^.lexlev);
end;

procedure set_size(arg0: integer; size: cardinal);
var
    sym: ^Symbol;
begin
    sym := lookup_sym(arg0);
    sym^.size := max(size, sym^.size);
end;

function some_init_overlap(sym: ^Symbol; u: Bcrec): pointer;
var
    var_v1: ^SymbolInit;
    var_a1: ^SymbolInit;
    var_v0: boolean;
begin
    var_v1 := sym^.unk1C;
    if (var_v1 = nil) then return nil;

    var_a1 := sym^.unk20;
    if (u.Offset >= sym^.unk20^.u.Offset2 + sym^.unk20^.u.Length) then begin
        var_v1 := var_a1;
    end else if ((source_language = 2) and (last_inits_handled <> nil) and
            (last_inits_handled^.next <> nil) and (u.I1 = last_inits_handled_blkno) and
            (u.Offset >= last_inits_handled^.u.Offset2 + last_inits_handled^.u.Length)) then begin
        var_v1 := last_inits_handled;
    end else begin
        last_inits_handled_blkno := 0;
        last_inits_handled := nil;
    end;

    var_v0 := false;
    while (not var_v0) do begin
        if ((u.Offset >= var_v1^.u.Offset2 + var_v1^.u.Length) or (var_v1^.u.Offset >= u.Offset2 + u.Length)) then begin
            if ((source_language = 2) and (var_v1^.u.Offset >= u.Offset2 + u.Length)) then begin
                var_v0 := true;
            end;
        end else begin
            return var_v1;
        end;

        if (var_v1 = sym^.unk20) then begin
            var_v0 := true;
        end else begin
            var_v1 := var_v1^.next;
        end;
    end;

    return nil;
end;

procedure complex_init_duplicate_p(init: ^SymbolInit; sym: ^Symbol);
var
    new_init: ^SymbolInit;
begin
    new(new_init);

    new_init^.next := init^.next;
    new_init^.u := init^.u;
    init^.next := new_init;

    if (init = sym^.unk20) then begin
        sym^.unk20 := new_init;
    end;
    if (source_language = 2) then begin
        last_inits_handled := new_init;
        last_inits_handled_blkno := new_init^.u.I1;
    end;
end;

function integral_type(u: Bcrec): boolean;
begin
    if ((u.Dtype = Adt) or (u.Dtype = Hdt) or (u.Dtype = Ldt) or (u.Dtype = Jdt) or (u.Dtype = Fdt) or (u.Dtype = Gdt) or (u.Dtype = Ndt)) then begin
        integral_type := true;
    end else begin
        integral_type := false;
    end;
end;

procedure complex_insert_init(arg0: ^SymbolInit; sym: ^Symbol; u: Bcrec);
var
    sp130: Bcrec;
    sp110: Bcrec;
    var_s1: ^SymbolInit;
    str: ^Stringtext;
    i: cardinal;
    j: cardinal;
    temp_lo: integer;
    temp_s1: integer;
begin;
    sp130 := u;
    sp110 := arg0^.u;

    if ((sp130.Length <> sp110.Length) and (sp110.Dtype <> sp130.Dtype)) then begin
        report_error(Internal, 463, "symbol.p", "Illegal complex_init:  illegal overlapping FORTRAN DATA statements?");
    end;

    while (sp130.Offset < sp130.Offset2 + sp130.Length) do begin
        sp110 := arg0^.u;

        if (sp110.Offset < sp130.Offset) then begin
            complex_init_duplicate_p(arg0, sym);
            if ((sp130.Dtype = Mdt) and (sp110.Dtype = Mdt)) then begin
                var_s1 := arg0^.next;

                var_s1^.u.Offset := sp130.Offset;
                var_s1^.u.Offset2 := sp130.Offset;
                var_s1^.u.Length := arg0^.u.Length - (sp130.Offset - sp110.Offset);
                var_s1^.u.Initval.Ival := arg0^.u.Length - (sp130.Offset - sp110.Offset);

                arg0^.u.Length := sp130.Offset - sp110.Offset;
                arg0^.u.Initval.Ival := sp130.Offset - sp110.Offset;
            end else begin
                temp_lo := (sp130.Offset - sp110.Offset) div sp110.Length;
                arg0^.u.Offset2 := sp110.Offset + (temp_lo - 1) * sp110.Length;
                arg0^.next^.u.Offset := sp130.Offset;
                if (sp130.Offset <> temp_lo * sp110.Length + sp110.Offset) then begin
                    report_error(Warn, 491, "symbol.p", "Initialization of overlapping data. Not handled correctly");
                end;
            end;
            arg0 := arg0^.next;
            continue;
        end;

        if (sp110.Offset = sp130.Offset) then begin
            if (sp110.Offset2 < sp130.Offset2) then begin
                sp130.Offset := sp110.Offset2 + sp110.Length;
                arg0^.u.Initval := sp130.Initval;
                if (arg0 = sym^.unk20) then begin
                    arg0^.u.Offset2 := sp130.Offset2;
                    return;
                end;
                arg0 := arg0^.next;
                continue;
            end else if (sp110.Offset2 = sp130.Offset2) then begin
                if ((sp130.Dtype = Mdt) and (sp110.Dtype = Mdt) and (sp130.Length < sp110.Length)) then begin
                    complex_init_duplicate_p(arg0, sym);
                    var_s1 := arg0^.next;

                    var_s1^.u.Offset := arg0^.u.Offset + sp130.Length;
                    var_s1^.u.Offset2 := var_s1^.u.Offset;

                    new(str);

                    i := 1;
                    for j := sp130.Length + 1 to var_s1^.u.Initval.Ival do begin
                        str^.ss[i] := var_s1^.u.Initval.Chars^.ss[j];
                        i := i + 1;
                    end;

                    var_s1^.u.Initval.Chars := str;
                    arg0^.u := sp130;
                    var_s1^.u.Length := sp110.Length - sp130.Length;
                    var_s1^.u.Initval.Ival := sp110.Length - sp130.Length;
                end else begin
                    arg0^.u := sp130;
                end;
                return;
            end else begin
                complex_init_duplicate_p(arg0, sym);
                arg0^.u := sp130;
                arg0^.next^.u.Offset := sp130.Offset2 + sp130.Length;
                return;
            end;
        end else begin
            complex_init_duplicate_p(arg0, sym);
            arg0^.u := sp130;

            if ((sp130.Dtype = Mdt) and (sp110.Dtype = Mdt)) then begin
                temp_s1 := sp110.Offset - sp130.Offset;
                arg0^.u.Length := temp_s1;
                sp130.Offset := sp130.Offset + arg0^.u.Length;
                arg0^.u.Initval.Ival := arg0^.u.Length;
                sp130.Length := sp130.Length - arg0^.u.Length;
                sp130.Offset2 := sp130.Offset;

                new(str);

                i := 1;
                for j := temp_s1 + 1 to sp130.Initval.Ival do begin
                    str^.ss[i] := sp130.Initval.Chars^.ss[j];
                    i := i + 1;
                end;

                sp130.Initval.Chars := str;
                sp130.Initval.Ival := sp130.Length;
            end else begin
                arg0^.u.Offset2 := sp130.Offset + (((sp110.Offset - sp130.Offset) div sp130.Length) - 1) * sp130.Length;
                arg0^.next^.u.Offset := sp110.Offset;
                sp130.Offset := arg0^.u.Offset2 + sp130.Length;
                if (sp130.Offset <> sp110.Offset) then begin
                    report_error(Warn, 591, "symbol.p", "initialization of overlapping data. Not handled correctly");
                end;
            end;
        end;

        arg0 := arg0^.next;
    end;
end;

procedure append_init(sym: ^Symbol; u: ^Bcrec);
var
    var_s0: ^SymbolInit;
    var_v0: ^SymbolInit;
    temp_t3: ^SymbolInit;
    temp_t1: ^SymbolInit;
    temp_a0: ^SymbolInit;
    temp_a1: integer;
    temp_t4: integer;
begin
    case (u^.Dtype) of
        Jdt, Ldt, Mdt, Qdt, Rdt, Xdt: var_s0 := some_init_overlap(sym, u^);
        otherwise: var_s0 := nil;
    end;

    if (var_s0 <> nil) then begin
        complex_insert_init(var_s0, sym, u^);
        return;
    end;

    new(var_v0);
    if (var_v0 = nil) then begin
        report_error(Internal, 629, "symbol.p", "Insufficiant memory");
        return;
    end;

    if (headof_inordered_inits = nil) then begin
        headof_inordered_inits := sym;
        tailof_inordered_inits := sym;
    end else if ((sym^.unk24 = nil) and (sym <> tailof_inordered_inits)) then begin
        tailof_inordered_inits^.unk24 := sym;
        tailof_inordered_inits := sym;
    end;

    var_v0^.u := u^;
    var_v0^.next := nil;

    if (source_language = 2) then begin
        temp_t3 := sym^.unk1C;
        if (temp_t3 <> nil) then begin
            var_s0 := temp_t3;
            if ((last_inits_handled <> nil) and (last_inits_handled^.next <> nil) and
                (last_inits_handled_blkno = u^.I1) and (u^.Offset >= last_inits_handled^.u.Offset2 + last_inits_handled^.u.Length)) then begin
                var_s0 := last_inits_handled;
            end;
        end;
    end;

    last_inits_handled := var_v0;
    last_inits_handled_blkno := var_v0^.u.I1;

    temp_t3 := sym^.unk1C;
    if (temp_t3 = nil) then begin
        sym^.unk1C := var_v0;
        sym^.unk20 := var_v0;
        return;
    end;

    temp_t1 := sym^.unk20;
    temp_a1 := u^.Offset;
    if (temp_t1^.u.Offset < temp_a1) then begin
        temp_t1^.next := var_v0;
        sym^.unk20 := var_v0;
        return;
    end;

    temp_t4 := temp_t3^.u.Offset;
    if (temp_a1 < temp_t4) then begin
        var_v0^.next := temp_t3;
        sym^.unk1C := var_v0;
        return;
    end;

    if (source_language <> 2) then begin
        var_s0 := temp_t3;
    end;

    if (temp_a1 <> var_s0^.u.Offset) then begin
        while (var_s0 <> temp_t1) do begin
            temp_a0 := var_s0^.next;
            if (temp_a1 < temp_a0^.u.Offset) then begin
                var_v0^.next := temp_a0;
                var_s0^.next := var_v0;
                return;
            end else if ((temp_a1 = temp_a0^.u.Offset) and (((source_language = 1) and (apc <> 0)) or (source_language = 2))) then begin
                if (temp_t1 = temp_a0) then begin
                    var_s0^.next := var_v0;
                    sym^.unk20 := var_v0;
                end else begin
                    var_v0^.next := temp_a0^.next;
                    var_s0^.next := var_v0;
                end;
                return;
            end;
            var_s0 := temp_a0;
        end;
    end;

    if (((source_language = 1) or (source_language = 2)) and (temp_t4 = temp_a1)) then begin
        var_v0^.next := temp_t3^.next;
        sym^.unk1C := var_v0;
    end else begin
        report_error(Internal, 715, "symbol.p", "illegal inits");
    end;
end;

procedure add_init(u: ^Bcrec);
begin
    append_init(lookup_sym(u^.I1), u);
end;

{ TODO: fake u16? might be fixed if data_area is an enum }
procedure choose_area(data_area: u16; size: cardinal);
var
    var_v0: u8;
begin
    var_v0 := data_area;
    case (var_v0) of
        0: if (size > sdata_max) then demit_dir0(16#A, 0) else demit_dir0(16#19, 0);
        1: demit_dir0(16#1A, 0);
        2: demit_dir0(16#19, 0);
        3: demit_dir0(16#A, 0);
        4: demit_dir0(16#15, 0);
        5: if (excpt <> 0) then demit_edata(0, 0, 0);
    end;
end;

procedure force_alignment(arg0: u8);
begin
    if (arg0 <> 0) then begin
        demit_dir1(4, 0, arg0);
    end;
    demit_dir1(4, 0, 0);
end;

procedure emit_init(sym: ^Symbol);
var
    var_s0: ^SymbolAlias;
    var_s0_2: integer; { current offset }
    var_s3: ^SymbolInit;
    temp_s6: integer; { length }
    temp_s2: u8; { type enum }
    var_a2: integer;
    var_s0_3: integer;
    var_a3: integer;
begin
    demit_dir0(0, sym^.unk0);

    var_s0 := sym^.unk28;
    while (var_s0 <> nil) do begin
        if (var_s0^.unk4 = 1) then begin
            demit_weakext(var_s0^.unk0, 0);
        end;
        demit_dir0(0, var_s0^.unk0);
        var_s0 := var_s0^.next;
    end;

    var_s0_2 := 0;
    var_s3 := sym^.unk1C;
    while (var_s3 <> nil) do begin
        temp_s6 := var_s3^.u.Length;
        temp_s2 := find_val_type(var_s3^.u.Dtype, temp_s6);
        var_a2 := var_s3^.u.Offset - var_s0_2;
        if (var_a2 <> 0) then begin
            if (var_a2 < 0) then begin
                if (source_language = 2) then begin
                    report_error(Warn, 805, "symbol.p", "Fortran error - Duplicate initialization (ovelapping DATA statements)");
                end else begin
                    report_error(Internal, 810, "symbol.p", "illegal value in .space - illegal initialization bounds");
                end;
                var_a2 := 0;
            end;
            demit_dir1(16#14, 0, var_a2);
        end;

        if (temp_s2 = 8) then begin
            if (var_s3^.u.Lexlev <> 0) then begin
                if (temp_s6 = 2) then begin
                    demit_dir1(16#39, 0, var_s3^.u.Lexlev);
                end else begin
                    report_error(Warn, 825, "symbol.p", "Illegal shift in INIT. Shift ignored");
                end;
            end;
            emit_label_val(0, var_s3^.u.Initval.Ival, var_s3^.u.aryoff, temp_s6);
        end else begin
            if (var_s3^.u.Offset <> var_s3^.u.Offset2) then begin
                var_s0_3 := ((var_s3^.u.Offset2 - var_s3^.u.Offset) div temp_s6) + 1;
                if (var_s0_3 >= 16#10000) then begin
                    while (var_s0_3 >= 16#10000) do begin
                        emit_val(0, temp_s2, var_s3^.u.Initval, 16#FFFF);
                        var_s0_3 := var_s0_3 - 16#FFFF;
                    end;
                end;
                var_a3 := var_s0_3;
            end else begin
                var_a3 := 1;
            end;
            emit_val(0, temp_s2, var_s3^.u.Initval, var_a3);
        end;
        var_s0_2 := var_s3^.u.Offset2 + temp_s6;
        var_s3 := var_s3^.next;
    end;

    var_a2 := sym^.size - var_s0_2;
    if (var_a2 <> 0) then begin
        if (var_a2 < 0) then begin
            if (source_language = 2) then begin
                report_error(Warn, 868, "symbol.p", "Fortran error - Duplicate initialization -- illegal DATA statements");
            end else begin
                report_error(Warn, 873, "symbol.p", "illegal value in .space - illegal initialization bounds");
            end;
            var_a2 := 0;
        end;
        demit_dir1(16#14, 0, var_a2);
    end;
end;

procedure emit_symbol(sym: ^Symbol);
var
    var_s0: ^SymbolAlias;
begin
    case (sym^.kind) of
        1: begin
            if (sym^.size <> 0) then begin
                if (sym^.data_area = 2) then begin
                    demit_dir2(16#2D, sym^.unk0, sym^.size, 1);
                end else begin
                    demit_dir2(16#2D, sym^.unk0, sym^.size, 0);
                end;
            end;
        end;

        2, 4: begin
            if (sym^.kind = 2) then begin
                demit_dir0(2, sym^.unk0);
            end;
            if (sym^.size <> 0) then begin
                if (sym^.unk1C = nil) then begin
                    if (sym^.data_area = 2) then begin
                        demit_dir2(9, sym^.unk0, sym^.size, 1);
                    end else begin
                        demit_dir2(9, sym^.unk0, sym^.size, 0);
                    end;
                end else begin
                    choose_area(sym^.data_area, sym^.size);
                    force_alignment(sym^.unkE);
                    emit_init(sym);
                end;
            end;
        end;

        7: begin
            if (sym^.unk1C = nil) then begin
                if (sym^.size <> 0) then begin
                    if (sym^.data_area = 2) then begin
                        demit_dir2(8, sym^.unk0, sym^.size, 1);
                    end else begin
                        demit_dir2(8, sym^.unk0, sym^.size, 0);
                    end;
                end;
            end else begin
                demit_dir0(2, sym^.unk0);
                choose_area(sym^.data_area, sym^.size);
                force_alignment(3);
                emit_init(sym);
            end;
        end;

        10: begin
            var_s0 := sym^.unk28;
            while (var_s0 <> nil) do begin
                if (var_s0^.unk4 = 1) then begin
                    demit_weakext(var_s0^.unk0, sym^.unk0);
                end;
                var_s0 := var_s0^.next;
            end;
        end;

        3, 5, 6, 9: ;

        otherwise: report_error(Internal, 956, "symbol.p", "illegal symbol type");
    end;
end;

procedure output_decls();
var
    sym: ^Symbol;
    i: integer;
begin
    sym := headof_inordered_inits;
    while (sym <> nil) do begin
        emit_symbol(sym);
        sym^.unk0 := -1;
        sym := sym^.unk24;
    end;

    headof_inordered_inits := nil;
    tailof_inordered_inits := nil;

    for i := 0 to 255 do begin
        if (sym_hash_tab[i] <> nil) then begin
            sym := sym_hash_tab[i];
            while (sym <> nil) do begin
                if (sym^.unk0 <> -1) then begin
                    emit_symbol(sym);
                end;
                sym := sym^.next;
            end;
        end;
    end;
end;

procedure output_entry_point(arg0: integer);
var
    sym: ^Symbol;
    var_s0: ^SymbolAlias;
begin
    sym := lookup_sym(arg0);
    if (sym = nil) then begin
        report_error(Internal, 999, "symbol.p", "symbol not found");
        return;
    end;

    demit_dir0(0, arg0);

    var_s0 := sym^.unk28;
    while (var_s0 <> nil) do begin
        if (sym^.kind = 10) then begin
            demit_dir0(2, var_s0^.unk0);
        end;
        demit_dir0(0, var_s0^.unk0);
        var_s0 := var_s0^.next;
    end;
end;

procedure change_label_number(arg0: integer; arg1: integer);
var
    sym: ^Symbol;
begin
    sym := lookup_sym(arg0);
    if (sym = nil) then begin
        report_error(Internal, 1018, "symbol.p", "label not found in symbol table");
        return;
    end;
    sym^.unk4 := -arg1;
end;

procedure set_mtag(arg0: integer; cur_mtag: ^integer);
var
    sym: ^Symbol;
begin
    sym := lookup_sym(arg0);
    if ((sym <> nil) and (sym^.mtag = 0)) then begin
        cur_mtag^ := cur_mtag^ + 1;
        sym^.mtag := cur_mtag^;
    end;
end;

function get_mtag(arg0: integer): integer;
var
    sym: ^Symbol;
    mtag: integer;
begin
    sym := lookup_sym(arg0);
    if (sym <> nil) then begin
        mtag := sym^.mtag;
    end else begin
        mtag := non_local_mtag;
    end;
    return mtag;
end;

function get_sym_kind(arg0: integer): integer;
var
    sym: ^Symbol;
    kind: integer;
begin
    sym := lookup_sym(arg0);
    if (sym <> nil) then begin
        kind := sym^.kind;
    end else begin
        kind := 0;
    end;
    return kind;
end;
