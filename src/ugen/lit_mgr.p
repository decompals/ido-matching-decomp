#include "common.h"
#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"
#include "cmplrs/binasm.h"
#include "val_util.h"
#include "emit.h"
#include "report.h"

type
    PLiteral = ^Literal;
    Literal = Record
    labelno: integer;
    val: Valu;
    next: ^Literal;
end;

var
    doubles: PLiteral;
    floats: PLiteral;
    large_strings: PLiteral;
    sets: PLiteral;
    small_strings: PLiteral;
    sdata_max:  integer;

procedure emit_list(list: ^Literal; vtype: ValType); forward;

procedure reset_pool();
begin
    small_strings := nil;
    large_strings := nil;
    floats := nil;
    doubles := nil;
    sets := nil;
end;

procedure select_data_section(dataSize: integer);
begin
    if (dataSize <= sdata_max)  then begin
        demit_dir0(isdata, 0);
    end else begin
        demit_dir0(idata, 0);
    end;
end;

procedure emit_list({list: ^Literal; vtype: ValType}); {Not a subtype}
begin
    while (list <> nil) do begin
        emit_val(create_local_label(list^.labelno), vtype, list^.val, 1);
        list := list^.next;
    end;
end;

procedure output_pool();
begin
    if (floats <> nil) then begin
        select_data_section(4);
        demit_dir1(ialign, 0, 2);
        emit_list(floats, ValType_Float);
    end;

    if (doubles <> nil) then begin
        select_data_section(8);
        demit_dir1(ialign, 0, 3);
        emit_list(doubles, ValType_Double);
    end;

    if (sets <> nil) then begin
        select_data_section(8);
        demit_dir1(ialign, 0, 2);
        emit_list(sets, ValType_Set);
    end;

    if (small_strings <> nil) then begin
        demit_dir0(isdata, 0);
        emit_list(small_strings, ValType_Ascii);
    end;

    if (large_strings <> nil) then begin
        demit_dir0(irdata, 0);
        emit_list(large_strings, ValType_Ascii);
    end;

end;

function new_lit(var val: Valu; labelno: integer): pointer;
var
    newLit: ^Literal;
begin
    new(newLit);

    if (newLit = nil) then begin
        report_error(Internal, 106, 'lit_mgr.p', 'Insufficiant memory');
        return newLit;
    end;

    newLit^.labelno := labelno;
    newLit^.val := val;
    return newLit;
end;

procedure add_to_list_no_check(var lit: PLiteral; var val: Valu;  labelno: Integer);
var
    newLit: ^Literal;
begin
    newLit := new_lit(val, labelno);
    newLit^.next := lit;
    lit := newLit;
end;

function valu_equ(var val1: Valu; var val2: Valu): boolean;
var
    i: cardinal;
begin
    if (val1.Ival <> val2.Ival) then begin
        return false;
    end;

    for i := 1 to val1.Ival do begin
        if (val1.Chars^.ss[i] <> val2.Chars^.ss[i]) then begin
            return false;
        end;
    end;

    return true;
end;

function add_to_list(var lit: PLiteral; var val: Valu; labelno: integer): integer;
var
    temp_v0: ^Literal;
    s0: ^Literal;
begin
    temp_v0 := lit;

    if (temp_v0 <> nil) then begin
        s0 := temp_v0;
        while (s0 <> nil) do begin
            { If the item already exists return its id }
            if (valu_equ(val, s0^.val)) then begin
                return s0^.labelno;
            end;
            s0 := s0^.next;
        end;
    end;

    { If no duplicates were found add a new literal to the list }
    temp_v0 := new_lit(val, labelno);
    temp_v0^.next := lit;
    lit := temp_v0;

    return labelno;
end;

function add_to_pool(var u: Bcrec; labelno: integer): integer;
begin
    Assert((u.Opc = Uldc) or (u.Opc = Ulca));

    case u.dtype of
        Mdt:
            begin
                if (sdata_max < u.Constval.Ival) then begin
                    add_to_list_no_check(large_strings, u.Constval, labelno);
                end else
                    add_to_list_no_check(small_strings, u.Constval, labelno);
                return labelno;
            end;

        Qdt:
            begin
                return add_to_list(doubles, u.Constval, labelno);
            end;
        Rdt:
            begin
                return add_to_list(floats, u.Constval, labelno);
            end;

        Sdt:
            begin
                return add_to_list(sets, u.Constval, labelno);
            end;

        otherwise
            begin
                report_error(Internal, 186, "lit_mgr.p", "illegal data type");
            end;
    end;

    return 0;
end;
