#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"
#include "cmplrs/binasm.h"
#include "common.h"
#include "val_util.h"
#include "report.h"
#include "emit.h"

var
    { .data }
    val_dir_tab: array [ValType_Byte..ValType_Set] of itype := (
        ibyte, ihalf, iword, idword, ifloat, idouble, iascii, iword, ibyte
    );
    hi: array [first(char)..last(char)] of u8 := (
        '0': 0,
        '1': 1,
        '2': 2,
        '3': 3,
        '4': 4,
        '5': 5,
        '6': 6,
        '7': 7,
        '8': 8,
        '9': 9,
        'A': 10, 'a': 10,
        'B': 11, 'b': 11,
        'C': 12, 'c': 12,
        'D': 13, 'd': 13,
        'E': 14, 'e': 14,
        'F': 15, 'f': 15
    );
    { .bss }
    lsb_first: boolean;

procedure emit_composite_val(var value: Valu);
var
    num_records: cardinal;
    remainder: cardinal;
    i: cardinal;
    j: cardinal;
    inst: binasm;
    offset: cardinal;
begin
    num_records := value.Ival div 16;
    remainder := value.Ival mod 16;
    for i := 1 to num_records do begin
        offset := lshift(i, 4) - 16;
        for j := 1 to 16 do begin
            inst.data[j] := value.Chars^.ss[offset + j];
        end;

        append_d(inst);
    end;

    if remainder <> 0 then begin
        inst.data := "";
        for i := 1 to remainder do begin
            inst.data[i] := value.Chars^.ss[lshift(num_records, 4) + i];
        end;

        append_d(inst);
    end;
end;

procedure emit_val{(arg0: integer; vtype: ValType; var value: Valu; rep: cardinal)};
var
    inst: binasm;
    i: integer;
begin
    if arg0 <> 0 then begin
        demit_dir0(ilabel, arg0);
    end;

    case vtype of
        ValType_Null: report_error(Internal, 135, "val_util.p", "null value");
        ValType_Byte,
        ValType_Half,
        ValType_Word: begin
            inst.instr := val_dir_tab[vtype];
            inst.expression := value.Ival;
            inst.replicate := rep;
            inst.symno := 0;
            append_d(inst);
        end;
        ValType_Dword: begin
            inst.instr := val_dir_tab[vtype];
            inst.expression := value.dwval_h;
            inst.replicate := rep;
            inst.symno := 0;
            append_d(inst);

            inst.instr := val_dir_tab[vtype];
            inst.expression := value.dwval_l;
            inst.replicate := rep;
            inst.symno := 0;
            append_d(inst);
        end;
        ValType_Float,
        ValType_Double,
        ValType_Ascii: begin
            inst.instr := val_dir_tab[vtype];
            inst.expression := value.Ival;
            inst.symno := 0;
            inst.replicate := rep;            
            append_d(inst);
            emit_composite_val(value);
        end;
        ValType_Label: ; { emit nothing }
        ValType_Set: begin
            assert(value.Ival mod 2 = 0);
            if not lsb_first then begin
                for i := 1 to value.Ival div 2 do begin
                    inst.instr := val_dir_tab[vtype];
                    inst.expression := hi[value.Chars^.ss[2 * i - 1]] * 16 + hi[value.Chars^.ss[2 * i]];
                    inst.replicate := 1;
                    inst.symno := 0;
                    append_d(inst);
                end;
            end else begin
                for i := value.Ival div 2 downto 1 do begin
                    inst.instr := val_dir_tab[vtype];
                    inst.expression := hi[value.Chars^.ss[2 * i - 1]] * 16 + hi[value.Chars^.ss[2 * i]];
                    inst.replicate := 1;
                    inst.symno := 0;
                    append_d(inst);
                end;
            end;
        end;
    end;
end;

procedure emit_label_val{(arg0: integer; symno: integer; value: integer; size: cardinal)};
var
    inst: binasm;
begin
    if size = 2 then begin
        inst.instr := val_dir_tab[ValType_Half];
    end else begin
        inst.instr := val_dir_tab[ValType_Label];
    end;
    inst.expression := value;
    inst.replicate := 1;
    inst.symno := symno;

    append_d(inst);
end;

function find_val_type{(dtype: Datatype; size: integer): ValType};
begin
    case dtype of
        Idt, Jdt, Kdt, Ldt: begin
            if size = 1 then begin
                return ValType_Byte;
            end else if size <= 2 then begin
                return ValType_Half;
            end else if size <= 4 then begin
                return ValType_Word;
            end else begin
                return ValType_Dword;
            end;
        end;
        Adt, Hdt: return ValType_Word;
        Wdt: return ValType_Dword;
        Rdt: return ValType_Float;
        Qdt: return ValType_Double;
        Mdt: return ValType_Ascii;
        Fdt, Ndt: return ValType_Label;
        Sdt: return ValType_Set;
        Xdt: report_error(Internal, 242, "val_util.p", "extended floating point not yet supported");
        otherwise report_error(Internal, 248, "val_util.p", "unknown data type");
    end;
end;
