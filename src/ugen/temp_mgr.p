#include "common.h"
#include "tree.h"
#include "reg_mgr.h"
#include "report.h"
#include "frame_offset.h"
#include "ugen_regdef.h"
#include "emit.h"

type
    Ptemp = ^Temp_rec;
    Temp_rec = Record;
        index: u8;
        usage_count: u16;
        free: boolean;
        size: integer;
        offset: integer;
        next: Ptemp;
    end;

var
    temps: Ptemp;
    temps_offset: integer;
    current_temp_index: u8;

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

    while temp <> nil do begin
        if (index = temp^.index) and not (temp^.free) then begin
            return temp;
        end;
        temp := temp^.next;
    end;
    return nil;
end;

function make_new_temp(size: integer): Ptemp;
var
    temp: Ptemp;
begin
    new(temp);

    if temp = nil then begin
        report_error(Internal, 76, "temp_mgr.p", "Insufficiant memory");
        return temp;
    end;

    if size > 4 then begin
        if temps_offset mod 8 <> 0 then begin
            temps_offset := temps_offset + temps_offset mod 8;
        end;
    end;

    temp^.free := false;
    temp^.offset := temps_offset;
    temp^.size := size;

    temp^.index := current_temp_index;
    current_temp_index := current_temp_index + 1;

    temps_offset := temps_offset + size;
    temp^.next := temps;

    temps := temp;

    return temp;
end;

function find_free_temp(size: integer): Ptemp;
var
    temp: Ptemp;
begin
    temp := temps;
    while temp <> nil do begin
        if (temp^.free) and (size = temp^.size) then begin
            temp^.free := false;
            return temp;
        end;
        temp := temp^.next;
    end;
    return nil;
end;

procedure gen_store(reg: registers; offset: integer; size: integer);
var
    op: asmcodes;
begin
    if IS_GPR(reg) then begin
        if size <= 4 then begin
            op := zsw;
        end else if size <= 8 then begin
            op := zsd;
        end else begin
            report_error(Internal, 124, "temp_mgr.p", "illegal size temporary");
            return;
        end;
    end else begin
        if size <= 4 then begin
            op := fs_s;
        end else if size <= 8 then begin
            op := fs_d;
        end else begin
            report_error(Internal, 133, "temp_mgr.p", "illegal size temporary");
            return;
        end;
    end;

    if reversed_stack then begin
        if (op = zsd) and (opcode_arch = ARCH_32) then begin
            emit_rob(zsw, reg, frame_offset1(offset + ALIGN_UP(size, 4)), frame_pointer, 0);
            emit_rob(zsw, succ(reg), frame_offset1(offset + ALIGN_UP(size, 4)) + 4, frame_pointer, 0);
        end else begin
            emit_rob(op, reg, frame_offset1(offset + ALIGN_UP(size, 4)), frame_pointer, 0);
        end;
    end else begin
        if (op = zsd) and (opcode_arch = ARCH_32) then begin
            emit_rob(zsw, reg, frame_offset1(offset), frame_pointer, 0);
            emit_rob(zsw, succ(reg), frame_offset1(offset) + 4, frame_pointer, 0);
        end else begin
            emit_rob(op, reg, frame_offset1(offset), frame_pointer, 0);
        end;
    end;
end;

procedure spill_to_temp(reg: registers; size: integer);
var
    temp: Ptemp;
    unk: PTree;    
begin
    if (opcode_arch = ARCH_32) and (kind_of_register(reg) = di_reg) then begin
        size := 8;
    end;
    temp :=  find_free_temp(size);
    if (temp = nil) then begin
        temp := make_new_temp(size);
    end;

    unk := content_of(reg);
    unk^.temp_id := temp^.index;

    temp^.usage_count := usage_count(reg);
    temp^.size := size;
    gen_store(reg, temp^.offset, size);
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

function get_temp_size(): integer;
var
    size: integer;
    temp: Ptemp;
begin
    size := 0;

    temp := temps;

    while (temp <> nil) do begin
        size := size + temp^.size;
        temp := temp^.next;
    end;

    return size;
end;

procedure set_temps_offset(offset: integer);
begin
    temps_offset := offset;
end;




