#include "common.h"
#include "cmplrs/binasm.h"
#include "reg_mgr.h"
#include "report.h"
#include "frame_offset.h"
#include "ugen_regdef.h"

{Extern variables}
var
    opcode_arch: boolean;

type
    Ptemp = ^Temp_rec;
    Temp_rec = Record;
    index: u8;
    usage_count: u16;
    free: boolean;
    area_size: integer;
    offset: integer;
    next: ^Temp_rec;
end;

var
    temps: ^Temp_rec;
    temps_offset: integer;
    current_temp_index: u8;
    frame_pointer: extern u8; {From frame_offset maybe?}
    reversed_stack: extern boolean;


type
spill_rec = Record
    unk: ^unk_rgmr_rec;
    temp: Ptemp;
end;

procedure emit_rob(reg: asmcodes; offset: registers; a2: integer; arg3: integer; arg4: integer); external;

procedure init_temps();
begin
    temps := nil;
    current_temp_index := 1;
end;

function lookup_temp(index: u8): Ptemp;
var
    temp: Ptemp;
begin
    temp := temps;

    while (temp <> nil) do begin
        if ((index = temp^.index) and not (temp^.free)) then begin
            return temp;
        end;
        temp := temp^.next;
    end;
    return nil;
end;

function make_new_temp(areaSize: integer): pointer;
var
    temp: Ptemp;
begin

    new(temp);

    if (temp = nil) then begin
        report_error(Internal, 76, "temp_mgr.p", "Insufficiant memory");
        return temp;
    end;
    if (areaSize >= 5) then begin
        if (temps_offset & 7 <> 0) then begin
            temps_offset := temps_offset + temps_offset &7;
        end;
    end;

    temp^.free := false;
    temp^.offset := temps_offset;
    temp^.area_size := areaSize;

    temp^.index := current_temp_index;
    current_temp_index := current_temp_index + 1;

    temps_offset := temps_offset + areaSize;
    temp^.next := temps;

    temps := temp;

    return temp;
end;

function find_free_temp(areaSize: integer): Ptemp;
var
    temp: Ptemp;
begin
    temp := temps;
    while (temp <> nil) do begin
        if ((temp^.free) and (areaSize = temp^.area_size)) then begin
            temp^.free := false;
            return temp;
        end;
        temp := temp^.next;
    end;
    return nil;
end;

procedure gen_store(reg: registers; offset: integer; areaSize: integer);
var
    op: first(asmcodes)..last(asmcodes);
begin
    if (reg in [gpr_zero..gpr_ra]) then begin
        if (areaSize <= 4) then begin
            op := zsw;
        end else if (areaSize <= 8) then begin
            op := zsd;
        end else begin
            report_error(Internal, 124, "temp_mgr.p", "illegal size temporary");
            return;
        end;

    end else if (areaSize <= 4) then begin
        op := fs_s;
    end else if (areaSize <= 8) then begin
        op := fs_d;
    end else begin
        report_error(Internal, 133, "temp_mgr.p", "illegal size temporary");
        return;
    end;

    if (reversed_stack) then begin
        if ((op = zsd) and not (opcode_arch)) then begin
            emit_rob(zsw, reg, frame_offset1(offset + (((areaSize + 3) div 4) * 4)), frame_pointer, 0);
            emit_rob(zsw, succ(reg), frame_offset1(offset + (((areaSize + 3) div 4) * 4)) + 4, frame_pointer, 0);
            return;
        end;
        emit_rob(op, reg, frame_offset1(offset + (((areaSize + 3) div 4) * 4)), frame_pointer, 0);
        return;
    end;

    if ((op = zsd) and not (opcode_arch)) then begin
        emit_rob(zsw, reg, frame_offset1(offset), frame_pointer, 0);
        emit_rob(zsw, succ(reg), frame_offset1(offset) + 4, frame_pointer, 0);
    end else begin
        emit_rob(op, reg, frame_offset1(offset), frame_pointer, 0);
    end;
end;

procedure spill_to_temp(reg: registers; areaSize: integer);
var
    spill: spill_rec;
begin
    if (not (opcode_arch) and (kind_of_register(reg) = 6)) then begin
        areaSize := 8;
    end;
    spill.temp :=  find_free_temp(areaSize);
    if (spill.temp = nil) then begin
        spill.temp := make_new_temp(areaSize);
    end;

    spill.unk := content_of(reg);
    spill.unk^.temp_index := spill.temp^.index;

    spill.temp^.usage_count := usage_count(reg);
    spill.temp^.area_size := areaSize;
    gen_store(reg, spill.temp^.offset, areaSize);
end;

procedure free_temp(index: u8);
var
    temp: Ptemp;
begin
    temp := lookup_temp(index);
    if (temp = nil) then begin
        report_error(Internal, 192, "temp_mgr.p", "temporary not found");
        return;
    end;
    temp^.free := true;
end;

function temp_offset(index: u8): integer;
var
    temp: Ptemp;
begin
    temp := lookup_temp(index);
    if (temp = nil) then begin
        report_error(Internal, 204, "temp_mgr.p", "temporary not found");
    end else begin
        return temp^.offset;
    end;
end;

function temp_usage_count(index: u8): u16;
var
    temp: Ptemp;
begin
    temp := lookup_temp(index);
    if (temp = nil) then begin
        report_error(Internal, 216, "temp_mgr.p", "temporary not found");
    end else begin
        return temp^.usage_count;
    end;
end;

function get_temp_area_size(): integer;
var
    size: integer;
    temp: Ptemp;
begin
    size := 0;

    temp := temps;

    while (temp <> nil) do begin
        size := size + temp^.area_size;
        temp := temp^.next;
    end;

    return size;
end;

procedure set_temps_offset(offset: integer);
begin
    temps_offset := offset;
end;




