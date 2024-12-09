#include "common.h"
#include "ugen.h"
#include "reg_mgr.h"
#include "report.h"

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
    current_temp_index: u8;
    temps_offset: integer;


type
spill_rec = Record
    unk: ^unk_rgmr_rec;
    temp: Ptemp;
end;


procedure gen_store(arg0: registers; temp_id: integer; arg2: integer); external; {No decompiled yet}


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

function make_new_temp(arg0: integer): pointer;
var
    temp: Ptemp;
begin

    new(temp);

    if (temp = nil) then begin
        report_error(Internal, 76, "Insufficiant memory", "temp_mgr.p");
        return temp;
    end;
    if (arg0 >= 5) then begin
        if ( temps_offset & 7 <> 0) then begin
            temps_offset := temps_offset + temps_offset &7;
        end;
    end;

    temp^.free := FALSE;
    temp^.offset := temps_offset;
    temp^.area_size := arg0;

    temp^.index := current_temp_index;
    current_temp_index := current_temp_index + 1;

    temps_offset := temps_offset + arg0;
    temp^.next := temps;

    temps := temp;

    return temp;
end;

function find_free_temp(area_size: integer): Ptemp;
var
    temp: Ptemp;
begin
    temp := temps;
    while (temp <> nil) do begin
        if ((temp^.free) and (area_size = temp^.area_size)) then begin
            temp^.free := false;
            return temp;
        end;
        temp := temp^.next;
    end;
    return nil;
end;

procedure spill_to_temp(reg: registers; area_size: integer);
var
    spill: spill_rec;
begin
    if (not (opcode_arch) and (kind_of_register(reg) = 6)) then begin
        area_size := 8;
    end;
    spill.temp :=  find_free_temp(area_size);
    if (spill.temp = nil) then begin
        spill.temp := make_new_temp(area_size);
    end;

    spill.unk := content_of(reg);
    spill.unk^.temp_index := spill.temp^.index;

    spill.temp^.usage_count := usage_count(reg);
    spill.temp^.area_size := area_size;
    gen_store(reg, spill.temp^.offset, area_size);
end;

#ifdef NON_MATCHING

(*
 url: https://decomp.me/scratch/0r65L
 score: 96.50% (988)
*)
procedure gen_store(reg: registers; offset: integer; area_size: integer);
var
    op: first(asmcodes)..last(asmcodes); (* sp + C6 *)
    frame_calc: integer; (* sp + BC *)
begin
        if ((xr0 in [reg])) then begin {Unknown pascal set operation}

        if (area_size < 5) then begin
            op := zsw;
        end else if (area_size < 9) then begin
            op := zsd;
        end else begin
            report_error(Internal, 124, "temp_mgr.p", "illegal size temporary");
            return;
        end;

    end else if (area_size < 5) then begin
        op := fs_s;
    end else if (area_size < 9) then begin
        op := fs_d;
    end else begin
        report_error(Internal, 133, "temp_mgr.p", "illegal size temporary");
        return;
    end;
        if (reversed_stack) then begin
            if ((op = zsd) and not (opcode_arch)) then begin
                frame_calc :=  offset + (((area_size + 3) div 4) * 4);
                emit_rob(zsw, reg, frame_offset1(frame_calc), frame_pointer, 0);
                emit_rob(zsw, reg , frame_offset1(frame_calc) + 4, frame_pointer, 0);
                return;
            end;
            emit_rob(op, succ(reg), frame_offset1(offset + (((area_size + 3) div 4) * 4)), frame_pointer, 0);
            return;
        end;

        if ((op = zsd) and not (opcode_arch)) then begin
            emit_rob(zsw, reg, frame_offset1(offset), frame_pointer, 0);
            emit_rob(zsw, succ(reg), frame_offset1(offset) + 4, frame_pointer, 0);
        end else begin
            emit_rob(op, reg, frame_offset1(offset), frame_pointer, 0);
        end;
end;
#else 
{GLOBAL_ASM("asm/7.1/functions/ugen/tmp_mgr/gen_store.s")}
#endif

procedure free_temp(index: u8); {Guess}
var
    temp: Ptemp;
begin
    temp := lookup_temp(index);
    if (temp = nil) then begin
        report_error(Internal, 192, "temporary not found", "tmp_mgr.p");
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
        report_error(Internal, 204, "temporary not found", "temp_mgr.p");
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
        report_error(Internal, 216, "temporary not found", "temp_mgr.p");
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




