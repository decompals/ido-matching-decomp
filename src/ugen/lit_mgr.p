{**********************************************************************}
{  This file implements deferred generation of data section literals.  }
{  It allows building a literal pool with duplicate checking first,    }
{  and then emitting all data at once. Literals include strings,       }
{  floating-point numbers, and sets.                                   }
{**********************************************************************}

#include "common.h"
#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"
#include "val_util.h"
#include "emit.h"
#include "report.h"
#include "lit_mgr.h"

type
    PLiteral = ^Literal;
    Literal = Record
        labelno: integer;
        val: Valu;
        next: PLiteral;
    end;

var
    { .bss }
    small_strings: PLiteral;
    large_strings: PLiteral;
    floats: PLiteral;
    doubles: PLiteral;
    sets: PLiteral;

{ Clears the literal pool. Memory is not freed in the process. }
procedure reset_pool();
begin
    small_strings := nil;
    large_strings := nil;
    floats := nil;
    doubles := nil;
    sets := nil;
end;

{ Selects the .data or .sdata section. }
procedure select_data_section(dataSize: integer);
begin
    if (dataSize <= sdata_max)  then begin
        demit_dir0(isdata, 0);
    end else begin
        demit_dir0(idata, 0);
    end;
end;

{ Emits all literals from the list, each with its own local label. }
procedure emit_list(list: PLiteral; vtype: ValType);
begin
    while (list <> nil) do begin
        emit_val(create_local_label(list^.labelno), vtype, list^.val, 1);
        list := list^.next;
    end;
end;

{ Emits all literals from the pool in the following order: floats, doubles, sets, small strings, large strings.
  Floats, doubles, and sets go into either .data or .sdata; small strings always go into .sdata;
  large strings always go into .rdata. }
procedure output_pool();
begin
    if (floats <> nil) then begin
        select_data_section(4);
        demit_dir1(ialign, NO_SYM, 2);
        emit_list(floats, ValType_Float);
    end;

    if (doubles <> nil) then begin
        select_data_section(8);
        demit_dir1(ialign, NO_SYM, 3);
        emit_list(doubles, ValType_Double);
    end;

    if (sets <> nil) then begin
        select_data_section(8);
        demit_dir1(ialign, NO_SYM, 2);
        emit_list(sets, ValType_Set);
    end;

    if (small_strings <> nil) then begin
        demit_dir0(isdata, NO_SYM);
        emit_list(small_strings, ValType_Ascii);
    end;

    if (large_strings <> nil) then begin
        demit_dir0(irdata, NO_SYM);
        emit_list(large_strings, ValType_Ascii);
    end;

end;

{ Creates a new literal with a given value and label. }
function new_lit(var val: Valu; labelno: integer): pointer;
var
    newLit: PLiteral;
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

{ Adds a literal to the beginning of the list without checking for duplicates. }
procedure add_to_list_no_check(var lit: PLiteral; var val: Valu;  labelno: Integer);
var
    newLit: PLiteral;
begin
    newLit := new_lit(val, labelno);
    newLit^.next := lit;
    lit := newLit;
end;

{ Compares two values for equality by checking them character by character, as strings. }
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

{ If the literal exists in the list, returns its label number;
  otherwise, adds a new literal to the beginning of the list. }
function add_to_list(var list: PLiteral; var val: Valu; labelno: integer): integer;
var
    newLit: PLiteral;
    iter: PLiteral;

begin
    if (list <> nil) then begin
        iter := list;
        while (iter <> nil) do begin
            { If the item already exists just return its id }
            if (valu_equ(val, iter^.val)) then begin
                return iter^.labelno;
            end;
            iter := iter^.next;
        end;
    end;

    { If no duplicates were found add a new literal to the list }
    newLit := new_lit(val, labelno);
    newLit^.next := list;
    list := newLit;

    return labelno;
end;

{ Adds a constant value from Uldc and Ulca instructions to the pool,
  based on its type and size. Strings may be duplicated, while sets
  and floating-point numbers are checked for duplicates.
  Returns the label number of the added literal. }
function add_to_pool{(var u: Bcrec; labelno: integer): integer};
begin
    Assert((u.Opc = Uldc) or (u.Opc = Ulca));

    case u.dtype of
        Mdt:
            begin
                if u.Constval.Ival > sdata_max then begin
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

    return NO_LABEL;
end;
