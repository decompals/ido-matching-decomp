{*****************************************************}
{ Manages the stack spill area for registers.         }
{ Allocates spill slots and stores registers to the   }
{ stack, but does not restore them.                   }
{ Spill slots may be reused.                          }
{*****************************************************}

#include "common.h"
#include "tree.h"
#include "reg_mgr.h"
#include "report.h"
#include "frame_offset.h"
#include "ugen_regdef.h"
#include "emit.h"

type
    PSpillSlot = ^SpillSlot;
    SpillSlot = Record;
        index: u8;
        usage_count: u16;
        is_free: boolean;
        size: integer;
        offset: integer;
        next: PSpillSlot;
    end;

var
    temps: PSpillSlot;
    temps_offset: integer;
    current_temp_index: u8;

{ Resets the spill slot allocator state }
procedure init_temps();
begin
    temps := nil;
    current_temp_index := 1;
end;

{ Returns an active spill slot by index, or nil if not found }
function lookup_temp(index: u8): PSpillSlot;
var
    slot: PSpillSlot;
begin

    slot := temps;
    while slot <> nil do begin
        if (index = slot^.index) and not slot^.is_free then begin
            return slot;
        end;
        slot := slot^.next;
    end;

    return nil;
end;

{ Allocates a new spill slot of the given size.
  The slot is placed at the end of the spill area. }
function make_new_temp(size: integer): PSpillSlot;
var
    slot: PSpillSlot;
begin
    new(slot);

    if slot = nil then begin
        report_error(Internal, 76, "temp_mgr.p", "Insufficiant memory");
        return slot;
    end;

    if size > 4 then begin
        if temps_offset mod 8 <> 0 then begin
            temps_offset := temps_offset + temps_offset mod 8;
        end;
    end;

    slot^.is_free := false;
    slot^.offset := temps_offset;
    slot^.size := size;

    slot^.index := current_temp_index;
    current_temp_index := current_temp_index + 1;

    temps_offset := temps_offset + size;

    { Insert into list }
    slot^.next := temps;
    temps := slot;

    return slot;
end;

{ Finds a free spill slot of the exact size, or returns nil }
function find_free_temp(size: integer): PSpillSlot;
var
    slot: PSpillSlot;
begin
    slot := temps;
    while slot <> nil do begin
        if slot^.is_free and (size = slot^.size) then begin
            slot^.is_free := false;
            return slot;
        end;
        slot := slot^.next;
    end;

    return nil;
end;

{ Emits instructions to store a register into a spill slot }
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
        { Converts offset relative to the frame base into an address
          relative to the actual frame_pointer register (which is SP) }
        if (op = zsd) and (opcode_arch = ARCH_32) then begin
            { Store both registers forming a 64-bit value }
            emit_rob(zsw, reg, frame_offset1(offset), frame_pointer, 0);
            emit_rob(zsw, succ(reg), frame_offset1(offset) + 4, frame_pointer, 0);
        end else begin
            emit_rob(op, reg, frame_offset1(offset), frame_pointer, 0);
        end;
    end;
end;

{ Spills a register to a spill slot.
  Reuses a free slot if possible, otherwise allocates a new one.
  For 64-bit values on 32-bit targets, the register pair is stored
  as a single 8-byte slot. }
procedure spill_to_temp(reg: registers; size: integer);
var
    slot: PSpillSlot;
    node: PTree;    
begin
    if (opcode_arch = ARCH_32) and (kind_of_register(reg) = di_reg) then begin
        size := 8;
    end;

    slot :=  find_free_temp(size);
    if slot = nil then begin
        slot := make_new_temp(size);
    end;

    node := content_of(reg);
    node^.temp_id := slot^.index;

    slot^.usage_count := usage_count(reg);
    slot^.size := size;
    gen_store(reg, slot^.offset, size);
end;

{ Marks the spill slot with the given index as free }
procedure free_temp(index: u8);
var
    slot: PSpillSlot;
begin
    slot := lookup_temp(index);
    if (slot = nil) then begin
        report_error(Internal, 192, "temp_mgr.p", "temporary not found");
        return;
    end;
    slot^.is_free := true;
end;

{ Returns the spill slot offset relative to the frame base (not SP) }
function temp_offset(index: u8): integer;
var
    slot: PSpillSlot;
begin
    slot := lookup_temp(index);
    if (slot = nil) then begin
        report_error(Internal, 204, "temp_mgr.p", "temporary not found");
    end else begin
        return slot^.offset;
    end;
end;

{ Returns the usage count stored in the spill slot }
function temp_usage_count(index: u8): u16;
var
    slot: PSpillSlot;
begin
    slot := lookup_temp(index);
    if (slot = nil) then begin
        report_error(Internal, 216, "temp_mgr.p", "temporary not found");
    end else begin
        return slot^.usage_count;
    end;
end;

{ Returns total size of the spill area }
function get_temp_area_size(): integer;
var
    size: integer;
    slot: PSpillSlot;
begin
    size := 0;

    slot := temps;
    while (slot <> nil) do begin
        size := size + slot^.size;
        slot := slot^.next;
    end;

    return size;
end;

{ Sets the base offset of the spill area relative to the frame base }
procedure set_temps_offset(offset: integer);
begin
    temps_offset := offset;
end;




