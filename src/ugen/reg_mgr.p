{**********************************************************}
{ The register manager controls register usage.            }
{ It provides a requested or free register on demand,      }
{ and correctly handles cases where the requested          }
{ register is unavailable or all registers are occupied.   }
{                                                          }
{ There are two groups of registers: t0–t9 and all others. }
{ This manager handles allocation from the first group.    }
{ The allocation usually works as follows:                 }
{   - Initially, all registers are in the free list:       }
{       t6, t7, t8, t9, t0, t1, t2, t3, t4, t5             }
{   - Each call to `get_free_reg` removes a register       }
{     from the front of the list and returns it.           }
{   - Each call to `free_reg` returns a register           }
{     to the end of the free list.                         }
{ The same rules apply to floating-point registers.        }
{ The group allocated by this manager is ft0–ft5.          }
{**********************************************************}

#include "common.h"
#include "report.h"
#include "tree.h"
#include "temp_mgr.h"
#include "emit.h"
#include "ugen_regdef.h"
#include "reg_mgr.h"

type
    { Registers in the list are linked via the `next` field in the `Register` record.
      This means that each register can belong to only one list. }
    RegList = Record;
        head: registers;
        tail: registers;
    end;

    RegArray = array [registers] of integer;

var
    { .data }
    kind_tab: array [xr0..xr16] of RegKind := [
        i_reg, no_reg, i_reg, i_reg,
        i_reg, di_reg, i_reg, di_reg,
        i_reg, no_reg, i_reg, no_reg,
        d_reg, f_reg, i_reg, di_reg,
        x_reg
    ];

    size_tab: array [RegKind] of integer := [0, 4, 4, 8, 16, 16, 8, 4];
    size_tab2: array [RegKind] of integer := [0, 8, 4, 8, 16, 16, 8, 8];
    mips_cg_regs: array [1..4] of registers := [gpr_t6, gpr_t7, gpr_t8, gpr_t9];
    name_tab: array [registers] of array [1..5] of char := [
        "$0",    "$1",    "$2",    "$3",    "$4",    "$5",    "$6",    "$7",
        "$8",    "$9",    "$10",   "$11",   "$12",   "$13",   "$14",   "$15",
        "$16",   "$17",   "$18",   "$19",   "$20",   "$21",   "$22",   "$23",
        "$24",   "$25",   "$26",   "$27",   "$gp",   "$sp",   "$30",   "$31",
        "$f0",   "$f1",   "$f2",   "$f3",   "$f4",   "$f5",   "$f6",   "$f7",
        "$f8",   "$f9",   "$f10",  "$f11",  "$f12",  "$f13",  "$f14",  "$f15",
        "$f16",  "$f17",  "$f18",  "$f19",  "$f20",  "$f21",  "$f22",  "$f23",
        "$f24",  "$f25",  "$f26",  "$f27",  "$f28",  "$f29",  "$f30",  "$f31",
        "$fcc0", "$fcc1", "$fcc2", "$fcc3", "$fcc4", "$fcc5", "$fcc6", "$fcc7",
        "none"
    ];

    { .bss }
    gp_regs_free: RegList;
    gp_regs_used: RegList;
    fp_regs_free: RegList;
    fp_regs_used: RegList;
    restricted_regs: RegArray;
    restricted_fp_regs: RegArray;

{ unused function }
procedure clear_restricted_regs();
var 
    i: registers;
begin
    for i := first(registers) to last(registers) do begin
        restricted_regs[i] := 0;
        restricted_fp_regs[i] := 0;
    end;
end;

{ unused function }
procedure restricted_reg(reg: registers);
begin
    restricted_regs[reg] := restricted_regs[reg] + 1;
end;

{ unused function }
procedure restricted_fp_reg(reg: registers);
begin
    restricted_fp_regs[reg] := restricted_fp_regs[reg] + 1;
end;

{ Iterates through the registers in the list and finds the first one that is not in `specials`. }
function find_non_special_reg(specials: RegArray; var list: RegList): registers;
var
    iter: registers;
begin
    iter := list.head;

    while (iter <> list.tail) do begin
        if (specials[iter] = 0) then begin
            return iter;
        end;
        
        iter := regs[iter].next;
    end;

    report_error(Internal, 280, "reg_mgr.p", "Needed register: all permantently allocated: impossible ");
end;

{ This function is unused, so the argument type and return value are unclear. }
function get_reg_kind(reg: registers): RegKind;
begin
    return kind_tab[reg];
end;

{ Returns the `kind` of the register. }
function kind_of_register{(reg: registers): RegKind};
begin
    return regs[reg].reg_kind;
end;

{ Resets the state of all registers, populates the free lists, and clears the used lists. }
procedure init_regs();
var
    i: registers;
    j: cardinal;
begin
    for i := xr0 to xnoreg do begin
        regs[i].content := nil;
        regs[i].usage_count := 0;
        regs[i].next := xnoreg;
        regs[i].reg_available := false;
        regs[i].reg_kind := no_reg;
    end;
    
    { Fills the list of free general-purpose registers.
      First, these are the registers used for code generation: t6, t7, t8, t9, but their number
      can be increased (not decreased) via the `-regg` command-line argument.
      Second, these are the non-preserved registers t0, t1, t2, t3, t4, t5, whose number
      can be modified via the `-regr` command-line argument. }
    gp_regs_free.head := xnoreg;
    gp_regs_free.tail := xnoreg;

    { @BUG Although we can increase the n_cg_regs parameter, the mips_cg_regs array has a fixed length of 4. }
    for j := 1 to n_cg_regs do begin
        add_to_free_list(mips_cg_regs[j]);
    end;

    for i := gpr_t0 to registers(ord(gpr_t0) + n_unsaved_regs - 1) do begin
        add_to_free_list(i);
    end;
    
    { Fills the list of free floatin-point registers.
      First, these are the registers used for code generation: ft0, ft1, ft2, ft3, but their number
      can be increased (not decreased) via the `-fregg` command-line argument.
      Second, these are the non-preserved registers fpr_ft4, fpr_ft5 whose number
      can be modified via the `-fregr` command-line argument. }

    fp_regs_free.head := xnoreg;
    fp_regs_free.tail := xnoreg;

    i := fpr_ft0;
    for j := 1 to n_fp_cg_regs do begin
        add_to_fp_free_list(i, no_reg);
        i := succ(succ(i));
    end;

    i := fpr_ft4;
    for j := 1 to n_unsaved_fp_regs do begin
        add_to_fp_free_list(i, no_reg);
        i := succ(succ(i));
    end;

    { If the `-fp32regs` command-line parameter is set, all floating-point registers
      with odd numbers are also added to the free list. }
    if fp32regs then begin
        i := fpr_fv0f;
        for j := 1 to 16 do begin
            add_to_fp_free_list(i, no_reg);
            i := succ(succ(i));
        end;
    end;

    { Parameter registers a0, a1, a2, a3, fa0, and fa2 are prohibited from 
      use because they are live at function entry, and their values must not be overwritten. }
    for i := gpr_a0 to registers(ord(gpr_a0) + n_parm_regs - 1) do begin
        regs[i].reg_available := false;
        regs[i].usage_count := 0;
    end;

    i := fpr_fa0;
    while (i <= registers(cardinal((n_fp_parm_regs * 2) + ord(fpr_fa0) - 2))) do begin
        regs[i].reg_available := false;
        regs[i].usage_count := 0;
        i := succ(succ(i));
    end;

    { Preserved registers are also prohibited from use until they have been saved on the stack. }
    for i := gpr_s0 to registers(ord(gpr_s0) + n_saved_regs - 1) do begin
        regs[i].reg_available := false;
        regs[i].usage_count := 0;
    end;

    i := fpr_fs0;
    while (i <= registers(cardinal((n_saved_fp_regs * 2) + ord(fpr_fs0) - 2))) do begin
        if ufsm then begin
            add_to_fp_free_list(i, no_reg);
        end else begin
            regs[i].reg_available := false;
            regs[i].usage_count := 0;
        end;
        i := succ(succ(i));
    end;

    { Clears the list of used registers. }
    gp_regs_used.head := xnoreg;
    gp_regs_used.tail := xnoreg;
    fp_regs_used.head := xnoreg;
    fp_regs_used.tail := xnoreg;
end;

{ Fills the `Register` structure for the given register. The `content` field may be nil. }
procedure fill_reg{(reg: registers; content: PTree; usage_count: u16; reg_kind: RegKind)};
begin
    regs[reg].content := content;
    regs[reg].usage_count := usage_count;
    regs[reg].reg_kind := reg_kind;
end;

{ Emits a register-to-register copy instruction and also copies the fields of the structure. }
procedure copy_reg(copy_op: asmcodes; source_reg: registers; dest_reg: registers);
begin
    emit_rr(copy_op, dest_reg, source_reg);
    regs[dest_reg].content := regs[source_reg].content;
    regs[dest_reg].usage_count := regs[source_reg].usage_count;
    regs[dest_reg].reg_kind := regs[source_reg].reg_kind;
end;

{ Checks if the list is empty. }
function list_is_empty(var list: RegList): boolean;
begin
    return list.head = xnoreg;
end;

{ Prints the register kind and usage count.
  If it is used as part of a pair for a 64-bit value, also prints the second register in the pair. }
procedure dump_reg(reg: registers);
label loop;
begin
loop:
    write(output, "register ", reg);
    write(output, ":  kind ", regs[reg].reg_kind);
    write(output, ", usage ", regs[reg].usage_count);
    writeln(output);
    if (regs[reg].reg_kind = di_reg) then begin
        reg := regs[reg].dw_link;
        goto loop;
    end;
end;

{ Prints the contents of the register list to stderr. }
procedure print_regs(var list: RegList);
var
    iter: registers;
begin
    iter := list.head;
    writeln(err, "reg_list: ");
    
    while (iter <> list.tail) and (iter <> xnoreg) do begin
        writeln(err, iter);
        iter := regs[iter].next;
    end;
    writeln(err, iter);

    Assert(iter = list.tail);
end;

{ Searches the list for a register with an even number, removes it from the list, and returns it.
  The case where no such register exists is not handled, which appears to be a @BUG. }
function remove_direg(var list: RegList): registers;
var
    prev: registers;
    iter: registers;
begin
    Assert(list.head <> xnoreg);
    iter := list.head;
    prev := list.head;

    { Find the first register in the list with an even number }
    if (ord(list.head) mod 2 <> 0) then begin
        repeat begin
            prev := iter;
            iter := regs[iter].next;
        end until (ord(iter) mod 2 = 0);
    end;

    { Remove the found register from the list }
    if (iter = list.head) then begin
        list.head := regs[iter].next;
    end else begin
        regs[prev].next := regs[iter].next;
    end;

    if (iter = list.tail) then begin
        if (list.head = xnoreg) then begin
            list.tail := xnoreg;
        end else begin
            list.tail := prev;
        end;
    end;

    return iter;
end;

{ Gets the first element of the list. }
function get_head(list: RegList): registers;
begin
    Assert(list.head <> xnoreg);
    return list.head;
end;

{ Removes the first element from the list and returns it. }
function remove_head(var list: RegList): registers;
var
    first: registers;
begin
    Assert(list.head <> xnoreg);
    first := list.head;

    list.head := regs[list.head].next;
    if (first = list.tail) then begin
        Assert(list.head = xnoreg);
        list.tail := xnoreg;
    end;
    
    return first;
end;

{ Adds an available register to the end of the list. }
procedure append_to_list(reg: registers; var list: RegList);
begin
    Assert(regs[reg].reg_available);
    regs[reg].next := xnoreg;

    if (list_is_empty(list)) then begin
        list.head := reg;
        list.tail := reg;
    end else begin
        regs[list.tail].next := reg;
    end;

    list.tail := reg;
end;

{ Removes a register from the list and returns true if the register was actually in the list. }
function remove_from_list(reg: registers; var list: RegList): boolean;
var
    iter: registers;
begin
    if reg = list.head then begin
        if (reg = list.tail) then begin
            { size = 1 }
            list.head := xnoreg;
            list.tail := xnoreg;
            remove_from_list := true;
        end else begin
            list.head := regs[reg].next;
        end;
        return true;
    end;

    iter := list.head;
    while (iter <> list.tail) and (iter <> xnoreg) do begin
        if reg = regs[iter].next then begin
            if (regs[iter].next = list.tail) then begin
                list.tail := iter;
                regs[iter].next := xnoreg;                
                remove_from_list := true;
            end else begin
                regs[iter].next := regs[reg].next;
            end;
                
            return true;
        end;
        iter := regs[iter].next;
    end;

    { The register is not found. }
    return false;
end;

{ Spills a register either to the stack or into a free register. }
procedure spill(reg: registers; size: integer; var free_list: RegList; var used_list: RegList; copy_op: asmcodes);
var
    free_reg: registers;
begin
    if (opcode_arch = ARCH_32) and (regs[reg].reg_kind = di_reg) then begin
        { This is the first register of a pair holding a 64-bit value.
          Always spill to the stack; the second register of the pair can be freed. }
        spill_to_temp(reg, size);
        if remove_from_list(regs[reg].dw_link, gp_regs_used) then begin
            append_to_list(regs[reg].dw_link, gp_regs_free);
            fill_reg(regs[reg].dw_link, nil, 0, i_reg);
        end;
    end else if list_is_empty(free_list) then begin
        { No free registers; spill to the stack }
        spill_to_temp(reg, size);
    end else begin
        { A free register is available; spill into it }
        free_reg := remove_head(free_list);
        copy_reg(copy_op, reg, free_reg);

        if regs[reg].content = nil then begin
            report_error(Internal, 545, "reg_mgr.p", "register content is empty");
        end else begin
            { Forcefully assigns a new register to a tree node (usually handled by the eval function). }
            regs[reg].content^.reg := free_reg;
        end;

        append_to_list(free_reg, used_list);
    end;
end;

{ Spills the register. The kind is used to determine which free register list to use
  and which assembly operation to use for copying the register. }
procedure spill_reg(reg: registers; kind: RegKind);
var
    size: integer;
begin
    if (isa >= ISA_MIPS3) then begin
        size := size_tab2[kind];
    end else begin
        size := size_tab[kind];
    end;

    case kind of
        i_reg,
        di_reg,
        di_s_reg:
        begin
            spill(reg, size, gp_regs_free, gp_regs_used, zmove);
        end;

        f_reg:
        begin
            spill(reg, size, fp_regs_free, fp_regs_used, fmov_s);
        end;

        d_reg:
        begin
            spill(reg, size, fp_regs_free, fp_regs_used, fmov_d);
        end;

        otherwise:
        begin
            writeln(err, "reg = ", reg, " register kind  = ", kind);
            report_error(Internal, 576, "reg_mgr.p", " illegal register type");
        end;
    end;
end;

{ Acquires a single general-purpose register, spilling it if it is in use. }
procedure get_one_reg(reg: registers; node: PTree; usage_count: u16; kind: RegKind);
begin
    if not regs[reg].reg_available then begin
        { For unavailable registers, use usage_count to determine whether it is in use }
        if (regs[reg].usage_count <> 0) then begin
            spill_reg(reg, kind);
        end;        
    end else begin
        { For available registers, check whether it is in the free or used list }         
        if not (remove_from_list(reg, gp_regs_free)) then begin
            if (remove_from_list(reg, gp_regs_used)) then begin
                { The register is in the used list; spill it }
                spill_reg(reg, kind);
            end else begin
                report_error(Internal, 594, "reg_mgr.p", "register not on used/free list");
                return;
            end;
        end;
        
        { Regardless of whether it was in the free or used list, add it to the used list }
        append_to_list(reg, gp_regs_used);
    end;
    
    { Now the register is acquired; fill the structure }
    fill_reg(reg, node, usage_count, kind);
end;

{ Acquires two consecutive general-purpose registers for holding a 64-bit value.
  The first register must have an even number. }
procedure get_two_regs(reg: registers; node: PTree; usage_count: u16);
begin
    Assert(ord(reg) mod 2 = 0);
    get_one_reg(reg, node, usage_count, di_reg);
    regs[reg].dw_link := succ(reg);
    get_one_reg(succ(reg), node, usage_count, di_s_reg);
end;

{ Acquires the requested general-purpose register for use.
  If it is not available, spills it and still acquires it.
  For 64-bit values, acquires two registers. }
procedure get_reg{(reg: registers; node: PTree; usage_count: u16)};
begin
    if (node <> nil) and (opcode_arch = ARCH_32) and (node^.u.dtype in [Idt, Kdt, Wdt]) then begin
        get_two_regs(reg, node, usage_count);
    end else begin    
        get_one_reg(reg, node, usage_count, i_reg);
    end;
end;

{ Acquires a register without spilling; simply increments its usage count. }
procedure get_reg1{(reg: registers; node: PTree; usage_count: u16};
var
    second_reg: registers;
begin
    if regs[reg].reg_available and remove_from_list(reg, gp_regs_free) then begin
        { The register is free – acquire it }
        append_to_list(reg, gp_regs_used);
        if (opcode_arch = ARCH_32) and (node^.u.Dtype in [Idt, Kdt, Wdt]) then begin
            fill_reg(reg, node, usage_count, di_reg);
        end else begin
            fill_reg(reg, node, usage_count, i_reg);
        end;
    end else begin
        { Entered if the register is not free or unavailable }
        inc_usage(reg, usage_count);

        if (opcode_arch = ARCH_32) and (node^.u.Dtype in [Idt, Kdt, Wdt]) then begin
            regs[reg].reg_kind := di_reg;
        end;

        if (node <> nil) and (opcode_arch = ARCH_32) and  (node^.u.Dtype in [Idt, Kdt, Wdt]) then begin
            { Two registers are needed for a 64-bit value }
            second_reg := succ(reg);
            regs[reg].dw_link := second_reg;

            if (regs[second_reg].reg_available and (remove_from_list(second_reg, gp_regs_free))) then begin
                append_to_list(second_reg, gp_regs_used);
                fill_reg(second_reg, node, usage_count, di_s_reg);
            end else begin
                inc_usage(second_reg, usage_count);

                if (opcode_arch = ARCH_32) and (node^.u.dtype in [Idt, Kdt, Wdt]) then begin
                    regs[second_reg].reg_kind := di_s_reg;
                end;
            end;
        end;
    end;
end;

{ Acquires a floating-point register. The logic is identical to the get_one_reg function. }
procedure get_fp_reg{(reg: registers; node: PTree; kind: RegKind; usage_count: u16)};
begin
    if not regs[reg].reg_available then begin
        if (regs[reg].usage_count <> 0) then begin
            spill_reg(reg, regs[reg].reg_kind);
        end;
    end else begin
        if not (remove_from_list(reg, fp_regs_free)) then begin
            if (remove_from_list(reg, fp_regs_used)) then begin
                spill_reg(reg, regs[reg].reg_kind);
            end else begin
                report_error(Internal, 678, "reg_mgr.p", "fp register not on used/free list");
                return;
            end;
        end;
        
        append_to_list(reg, fp_regs_used);
    end;
    
    fill_reg(reg, node, usage_count, kind);
end;

{ Acquires a floating-point register without spilling }
procedure get_fp_reg1{(reg: registers; node: PTree; kind: RegKind; usage_count: u16)};
begin
    if regs[reg].reg_available and remove_from_list(reg, fp_regs_free) then begin
        append_to_list(reg, fp_regs_used);
        fill_reg(reg, node, usage_count, kind);
    end else begin
        inc_usage(reg, usage_count);
    end;
end;

{ Returns whether a free general-purpose register is free. }
function free_reg_is_available{(): boolean};
begin
    if (gp_regs_free.head = xnoreg) then begin
        return false;
    end;
    return true;
end;

{ Returns whether there is a register with an even number in the list. }
function can_get_two_regs(list: RegList): boolean;
var
    iter: registers;
begin
    if (list.head = xnoreg) then begin
        return false;
    end;

    iter := list.head;
    while ord(iter) mod 2 <> 0 do begin
        iter := regs[iter].next;
    end;
    if (iter = xnoreg) then begin
        return false;
    end;
    return true;
end;

{ Removes a pair of consecutive registers (even and odd) from all lists and returns the first one.
  Spills both registers to the stack. }
function spill_two_regs(): registers;
var
    reg: registers;
begin
    { It is assumed that, when calling this function, there is at least one register
      with an even number in the used list. Hopefully, this is always the case. }
    reg := remove_direg(gp_regs_used);
    
    if (regs[reg].reg_kind = di_reg) then begin
        { If this even register is already used to hold a 64-bit value, spill it }
        spill_to_temp(reg, size_tab[di_reg]);
        { Also free the second register of the pair }
        Assert(remove_from_list(succ(reg), gp_regs_used));
    end else begin
        { Otherwise, spill this even register }
        spill_to_temp(reg, size_tab[i_reg]);
        { Handle the next register: either spill it (if used) or remove it from the free list }
        if remove_from_list(succ(reg), gp_regs_used) then begin
            spill_to_temp(succ(reg), size_tab[i_reg]);
        end else if not remove_from_list(succ(reg), gp_regs_free) then begin
            report_error(Internal, 773, "reg_mgr.p", "register not on used/free list");
        end;
    end;

    regs[reg].dw_link := succ(reg);
    return reg;
end;

{ Returns a pair of registers for holding a 64-bit value; spills used registers if necessary. }
function get_two_free_regs(node: PTree; usage_count: u16): registers;
var
    freeReg: registers;
begin
    { This is only needed for 64-bit values }
    Assert((node <> nil) and (opcode_arch = ARCH_32) and (node^.u.dtype in [Idt, Kdt, Wdt]));

    if can_get_two_regs(gp_regs_free) then begin
        { If a free even-numbered register is available, take it }
        freeReg := remove_direg(gp_regs_free);
        regs[freeReg].dw_link :=  succ(freeReg);
        { Acquire the next register, even if it was in use }
        get_one_reg(regs[freeReg].dw_link, node, usage_count, di_s_reg);
    end else begin
        { No free even-numbered register; spill a used pair }
        freeReg := spill_two_regs();
        append_to_list(regs[freeReg].dw_link, gp_regs_used);
        fill_reg(regs[freeReg].dw_link, node, usage_count, di_s_reg);
    end;

    { Acquire the first register }
    append_to_list(freeReg, gp_regs_used);
    fill_reg(freeReg, node, usage_count, di_reg);
    return freeReg;
end;

{ Returns a free register; if none are available, spills a used one and returns it. }
function get_one_free_reg(node: PTree; usage_count: u16): registers;
var
    freeReg: registers;
begin
    if list_is_empty(gp_regs_free) then begin
        { No free registers; spill one from the used list }
        freeReg := get_head(gp_regs_used);
        if (regs[freeReg].reg_kind = di_reg) or (regs[freeReg].reg_kind = di_s_reg) then begin
            { If this register is part of a pair holding a 64-bit value, both must be spilled }
            freeReg := spill_two_regs();
            append_to_list(regs[freeReg].dw_link, gp_regs_free);
            fill_reg(regs[freeReg].dw_link, nil, 0, i_reg);
        end else begin
            { Spill a single register to the stack }
            freeReg := remove_head(gp_regs_used);
            if opcode_arch = ARCH_64 then begin
                spill_to_temp(freeReg, size_tab2[i_reg]);
            end else begin
                spill_to_temp(freeReg, size_tab[i_reg]);
            end;
        end;
    end else begin
        { At least one free register is available; take it }
        freeReg := remove_head(gp_regs_free);
    end;

    { Now acquire it }
    append_to_list(freeReg, gp_regs_used);
    fill_reg(freeReg, node, usage_count, i_reg);
    
    return freeReg;
end;

{ Returns one or two registers that can be used; spills used registers if necessary. }
function get_free_reg{(node: PTree; usage_count: u16): registers};
begin
    if (node <> nil) and (opcode_arch = ARCH_32) and (node^.u.Dtype in [Idt, Kdt, Wdt]) then begin
        return get_two_free_regs(node, usage_count);
    end else begin
        return get_one_free_reg(node, usage_count);
    end;
end;

{ Returns a free floating-point register; spills a used one if necessary. }
function get_free_fp_reg{(node: PTree; kind: RegKind; usage_count: u16): registers};
var
    freeReg: registers;
begin
    if list_is_empty(fp_regs_free) then begin
        { If no free registers are available, spill one from the used list }
        freeReg := remove_head(fp_regs_used);

        if isa >= ISA_MIPS3 then begin
            spill_to_temp(freeReg, size_tab2[regs[freeReg].reg_kind]);
        end else begin
            spill_to_temp(freeReg, size_tab[regs[freeReg].reg_kind]);
        end;
    end else begin
        { Otherwise, take a free register }
        freeReg := remove_head(fp_regs_free);
        { @INVESTIGATE: occurs in ufsm/ufsa modes; purpose unclear }
        if freeReg in ugen_fp_callee_saved then begin
            saved_regs := saved_regs + [freeReg];
        end;
    end;

    { Now acquire it }
    append_to_list(freeReg, fp_regs_used);
    fill_reg(freeReg, node, usage_count, kind);
    return freeReg;
end;

{ Returns the tree node currently associated with the register. }
function content_of{(reg: registers): PTree};
begin
    if regs[reg].content = nil then begin
        report_error(Internal, 867, "reg_mgr.p", "register content is empty");
        return; 
    end;

    return regs[reg].content;
end;

{ Increments the usage count of a register. 
  Each increment must later be matched with an equivalent number of free_reg calls. }
procedure inc_usage({reg: registers; usage_count: u16});
begin
    regs[reg].usage_count := regs[reg].usage_count + usage_count;
end;

{ Decrements the usage count by 1. If the register is part of a pair holding a 64-bit value,
  the usage count of the second register in the pair is also decremented. }
procedure dec_usage(reg: registers);
var
    dw_link: registers;
begin
    if (regs[reg].usage_count = 0) then begin
        report_error(Internal, 884, "reg_mgr.p", "usage count is 0, cannot decrement");
    end else begin
        regs[reg].usage_count := regs[reg].usage_count - 1;
    end;

    if (opcode_arch = ARCH_32) and (regs[reg].reg_kind = di_reg) then begin
        dw_link := regs[reg].dw_link;
        if regs[dw_link].usage_count = 0 then begin
            report_error(Internal, 891, "reg_mgr.p", "usage count is 0, cannot decrement");
        end else begin
            regs[dw_link].usage_count := regs[dw_link].usage_count - 1;
        end;
    end;
end;

{ Releases a register from one usage, decrementing its usage count by 1.
  When the count reaches zero, the register becomes free and can be reused. }
procedure free_reg{(reg: registers)};
var
    dw_link: registers;
begin
    dec_usage(reg);

    if regs[reg].usage_count = 0 then begin
        { Usage count reached zero – move register to free list }
        if regs[reg].reg_available then begin
            if not remove_from_list(reg, gp_regs_used) then begin
                report_error(Internal, 907, "reg_mgr.p", "register to be removed not on used list");
                return;
            end;
            append_to_list(reg, gp_regs_free);
        end;

        if (opcode_arch = ARCH_32) and (regs[reg].reg_kind = di_reg) then begin
            { If the register is part of a 64-bit pair, also release the second register }
            fill_reg(reg, nil, 0, i_reg);
            dw_link := regs[reg].dw_link;
            if regs[dw_link].reg_available then begin
                if not remove_from_list(dw_link, gp_regs_used) then begin
                    report_error(Internal, 917, "reg_mgr.p", "register to be removed not on free list");
                    return;
                end;
                append_to_list(dw_link, gp_regs_free);
            end;
            fill_reg(dw_link, nil, 0, i_reg);
        end else begin
            { Clear the structure }
            fill_reg(reg, nil, 0, i_reg);
        end;
    end;
end;

{ Releases a floating-point register from one usage, decrementing its usage count by 1.
  When the count reaches zero, the register becomes free and can be reused. }
procedure free_fp_reg{(reg: registers; kind: RegKind)};
begin
    dec_usage(reg);

    if regs[reg].usage_count = 0 then begin
        if regs[reg].reg_available then begin
            if not (remove_from_list(reg, fp_regs_used)) then begin
                report_error(Internal, 937, "reg_mgr.p", "fp register to be removed not on free list");
                return;
            end;
            append_to_list(reg, fp_regs_free);
        end;
        fill_reg(reg, nil, 0, kind);
    end;
end;

{ Forces the general-purpose register to be freed without requiring the corresponding number of `free_reg` calls.
  Does not handle the case where the register is part of a 64-bit value – potential @BUG. }
procedure force_free_reg{(reg: registers)};
begin
    if regs[reg].reg_available then begin
        if remove_from_list(reg, gp_regs_used) then begin 
            append_to_list(reg, gp_regs_free);
        end else begin
            return;
        end;
    end;

    fill_reg(reg, nil, 0, i_reg);
end;

{ Adds a general-purpose register to the free list, making it available for allocation. }
procedure add_to_free_list({reg: registers});
begin
    if regs[reg].usage_count <> 0 then begin
        report_error(Internal, 967, "reg_mgr.p", "register not free");
    end;

    fill_reg(reg, nil, 0, i_reg);
    regs[reg].reg_available := true;
    append_to_list(reg, gp_regs_free);
end;

{ Adds a floating-point register to the free list, making it available for allocation. }
procedure add_to_fp_free_list({reg: registers; kind: RegKind});
begin
    if regs[reg].usage_count <> 0 then begin
        report_error(Internal, 977, "reg_mgr.p", "fp register not free");
    end;

    fill_reg(reg, nil, 0, kind);
    regs[reg].reg_available := true;
    append_to_list(reg, fp_regs_free);
end;

{ Removes a general-purpose register from the free list, making it unavailable for allocation. }
procedure remove_from_free_list{(reg: registers)};
var
    dw_link: registers;
begin
    if regs[reg].reg_available then begin
        if not remove_from_list(reg, gp_regs_free) then begin
            report_error(Internal, 990, "reg_mgr.p", "register not free");
            return;
        end;
        regs[reg].reg_available := false;
    end;
    { @BUG usage count is not checked }
    fill_reg(reg, nil, 0, i_reg);

    if (opcode_arch = ARCH_32) and (regs[reg].reg_kind = di_reg) then begin
        { @BUG unreachable code: structure already cleared by `fill_reg` call }
        dw_link := regs[reg].dw_link;
        if regs[dw_link].reg_available then begin
            if not remove_from_list(dw_link, gp_regs_free) then begin
                report_error(Internal, 1000, "reg_mgr.p", "register not free");
                return;
            end;
            regs[dw_link].reg_available := false;
        end;
        fill_reg(dw_link, nil, 0, i_reg);
    end;
end;

{ Removes a floating-point register from the free list, making it unavailable for allocation. }
procedure remove_from_fp_free_list{(reg: registers; kind: RegKind)};
begin
    if regs[reg].reg_available then begin
        if not remove_from_list(reg, fp_regs_free) then begin
            report_error(Internal, 1013, "reg_mgr.p", "fp register not free");
            return;
        end;
        regs[reg].reg_available := false;
    end;
    { @BUG usage count is not checked }
    fill_reg(reg, nil, 0, kind);
end;

{ Returns whether a register is available for allocation by the register manager
  (in principle, not necessarily at the current moment). }
function is_available{(reg: registers): boolean};
begin
    return regs[reg].reg_available;
end;

{ Checks that all registers available for allocation by the manager are currently not in use. }
procedure check_no_used();
begin
    if not list_is_empty(gp_regs_used) then begin
        print_regs(gp_regs_used);
        report_error(Internal, 1031, "reg_mgr.p", "gp registers left in use at bb boundary");
    end;

    if not list_is_empty(fp_regs_used) then begin
        report_error(Internal, 1034, "reg_mgr.p", "fp registers left in use at bb boundary");
        print_regs(fp_regs_used); {@BUG: unreachable code }
    end;
end;

{ Returns the usage count of the register. }
function usage_count{(reg: registers): u16};
begin
    return regs[reg].usage_count;
end;

{ Moves a floating-point register in use to the end of the queue, reducing the likelihood that it will be spilled to the stack. }
procedure move_to_end_fp_list{(reg: registers)};
begin
    if remove_from_list(reg, fp_regs_used) then begin
        append_to_list(reg, fp_regs_used);
    end;
end;

{ Moves a general-purpose register in use to the end of the queue, reducing the likelihood that it will be spilled to the stack. }
procedure move_to_end_gp_list{(reg: registers)};
begin
    if (remove_from_list(reg, gp_regs_used)) then begin
        append_to_list(reg, gp_regs_used);
    end;
end;

{ unused function }
function get_free_fp_reg_special(node: PTree; kind: RegKind; usage_count: u16): registers;
var
    freeReg: registers;
begin
    if not list_is_empty(fp_regs_free) then begin
        return get_free_fp_reg(node, kind, usage_count);
    end;

    freeReg := find_non_special_reg(restricted_fp_regs, fp_regs_used);
    if not remove_from_list(freeReg, fp_regs_used) then begin
        report_error(Internal, 1075, "reg_mgr.p", "could not remove register from fp_regs_used list!");
    end;

    spill_to_temp(freeReg, size_tab[regs[freeReg].reg_kind]);
    append_to_list(freeReg, fp_regs_used);
    fill_reg(freeReg, node, usage_count, kind); 
    return freeReg;
end;

{ unused function }
function get_free_reg_special(node: PTree; usage_count: u16): registers;
var
    freeReg: registers;
begin
    if not (list_is_empty(gp_regs_free)) then begin
        return get_free_reg(node, usage_count);
    end;

    freeReg := find_non_special_reg(restricted_regs, gp_regs_used);
    if not (remove_from_list(freeReg, gp_regs_used)) then begin
        report_error(Internal, 1094, "reg_mgr.p", "could not remove register from regs_used list!");
    end;

    spill_to_temp(freeReg, size_tab[regs[freeReg].reg_kind]);
    append_to_list(freeReg, gp_regs_used);
    fill_reg(freeReg, node, usage_count, i_reg);
    return freeReg;
end;
