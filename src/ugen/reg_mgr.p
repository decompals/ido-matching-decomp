#include "common.h"
#include "report.h"
#include "tree.h"
#include "temp_mgr.h"
#include "emit.h"

type RegKind = (
    /* 0 */ no_reg,
    /* 1 */ i_reg, 
    /* 2 */ f_reg,
    /* 3 */ d_reg,
    /* 4 */ x_reg, 
    /* 5 */ q_reg,
    /* 6 */ di_reg,
    /* 7 */ di_s_reg 
);

type 
    UsedRegs = Record;
    unk0: registers;
    unk1: registers;
end;

type
    Register = Record;
    unk0: ^Tree;
    unk4: u16;
    unk6: registers;
    unk7: registers;
    reg_kind: RegKind;
    unk9: registers;
end;

var
    regs: array [first(registers)..last(registers)] of Register;
    gp_regs_used: UsedRegs;
    gp_regs_free: UsedRegs;
    size_tab: array [first(RegKind)..last(RegKind)] of integer;
    size_tab2: array [first(RegKind)..last(RegKind)] of integer;
    opcode_arch: u8;
    isa: mips_isa;
    fp_regs_free: UsedRegs;
    fp_regs_used: UsedRegs;


procedure fill_reg(arg0: registers; arg1: ^tree; arg2: u16; reg_kind: RegKind);
begin
    regs[arg0].unk0 := arg1;
    regs[arg0].unk4 := arg2;
    regs[arg0].reg_kind := reg_kind;
end;

procedure copy_reg(arg0: asmcodes; arg1: registers; arg2: registers);
begin
    emit_rr(arg0, arg2, arg1);
    regs[arg2].unk0 := regs[arg1].unk0;
    regs[arg2].unk4 := regs[arg1].unk4;
    regs[arg2].reg_kind := regs[arg1].reg_kind;
end;


{ Why use *pass by reference* in this function? }
function list_is_empty(var arg0: registers): boolean;
begin
    return arg0 = xnoreg;
end;

procedure dump_reg(arg0: registers);
label loop;
begin
loop:
    write(output, "register ", arg0);
    write(output, ": kind  ", regs[arg0].reg_kind);
    write(output, ", usage ", regs[arg0].unk4);
    writeln(output);
    if (regs[arg0].reg_kind = di_reg) then begin
        arg0 := regs[arg0].unk9;
        goto loop;
    end;
end;

procedure print_regs(var arg0: UsedRegs);
var
    var_s1: registers;
begin
    var_s1 := arg0.unk0;
    writeln(err, "reg_list: ");
    
    while ((var_s1 <> arg0.unk1) and (var_s1 <> xnoreg)) do begin
        writeln(err, var_s1);
        var_s1 := regs[var_s1].unk6;
    end;

    writeln(err, var_s1);
    Assert(var_s1 = arg0.unk1);
end;

function remove_direg(var arg0: UsedRegs): registers;
label ret;
var
    var_a1: registers;
    var_v1: registers;
begin
    Assert(arg0.unk0 <> xnoreg);
    var_v1 := arg0.unk0;
    var_a1 := arg0.unk0;

    if (ord(arg0.unk0) & 1 <> 0) then begin
        repeat begin
            var_a1 := var_v1;
            var_v1 := regs[var_v1].unk6;
        end until (ord(var_v1) & 1 = 0);
    end;

    if (var_v1 = arg0.unk0) then begin
        arg0.unk0 := regs[var_v1].unk6;
    end else begin
        regs[var_a1].unk6 := regs[var_v1].unk6;
    end;

    if (var_v1 = arg0.unk1) then begin
        if (arg0.unk0 = xnoreg) then begin
            arg0.unk1 := xnoreg;
            goto ret; { Required to match }
        end;
        arg0.unk1 := var_a1;
    end;

    ret:
    return var_v1;

end;

function get_head(reg: UsedRegs): registers;
begin
    Assert(reg.unk0 <> xnoreg);
    return reg.unk0;
end;

function remove_head(var arg0: UsedRegs): registers;
var
    temp_v1: registers;
begin
    Assert(arg0.unk0 <> xnoreg);
    temp_v1 := arg0.unk0;
    arg0.unk0 := regs[arg0.unk0].unk6;
    if (temp_v1 = arg0.unk1) then begin
        Assert(arg0.unk0 = xnoreg);
        arg0.unk1 := xnoreg;
    end;
    
    return temp_v1;
end;

procedure append_to_list(arg0: registers; var arg1: UsedRegs);
begin
    Assert(regs[arg0].unk7 <> xr0);
    regs[arg0].unk6 := xnoreg;

    if (list_is_empty(arg1.unk0)) then begin
        arg1.unk0 := arg0;
        arg1.unk1 := arg0;
    end else begin
        regs[arg1.unk1].unk6 := arg0;
    end;
    arg1.unk1 := arg0;
end;

function remove_from_list(arg0: registers; var arg1: UsedRegs): boolean;
var
    temp_a3: registers;
    temp_v1: registers;
    var_a2: registers;
begin
    if (arg0 = arg1.unk0) then begin
        if (arg0 = arg1.unk1) then begin
            arg1.unk0 := xnoreg;
            arg1.unk1 := xnoreg;
            remove_from_list := true;
        end else begin
            arg1.unk0 := regs[arg0].unk6;
        end;
        return true;
    end;
    temp_v1 := arg1.unk1;
    var_a2 := arg1.unk0;
    while ((var_a2 <> temp_v1) and (var_a2 <> xnoreg)) do begin
        if (arg0 = regs[var_a2].unk6) then begin
            if (temp_v1 = regs[var_a2].unk6) then begin
                arg1.unk1 := var_a2;
                regs[var_a2].unk6 := xnoreg;                
                remove_from_list := true;
            end else begin
                regs[var_a2].unk6 := regs[arg0].unk6;
            end;
                
            return true;
        end;
        var_a2 := regs[var_a2].unk6;
    end;
    return false;
end;

procedure spill(arg0: registers; arg1: integer; var arg2: UsedRegs; var arg3: UsedRegs; arg4: asmcodes);
var
    temp_v0: registers;
    temp_a0: ^Tree;
begin
    if ((opcode_arch = 0) and (regs[arg0].reg_kind = di_reg)) then begin
        spill_to_temp(arg0, arg1);
        if (remove_from_list(regs[arg0].unk9, gp_regs_used)) then begin
            append_to_list(regs[arg0].unk9, gp_regs_free);
            fill_reg(regs[arg0].unk9, nil, 0, i_reg);
        end;
    end else if (list_is_empty(arg2.unk0)) then begin
        spill_to_temp(arg0, arg1);
    end else begin
        temp_v0 := remove_head(arg2);
        copy_reg(arg4, arg0, temp_v0);
        if (regs[arg0].unk0 = nil) then begin
            report_error(Internal, 545, "ugen.p", "register content is empty");
        end else begin
            regs[arg0].unk0^.reg := temp_v0;
        end;
        append_to_list(temp_v0, arg3);
    end;
end;

procedure spill_reg(reg: registers; reg_kind: RegKind);
var
    size: integer;
begin
    if (isa >= ISA_MIPS3) then begin
        size := size_tab2[reg_kind];
    end else begin
        size := size_tab[reg_kind];
    end;

    case reg_kind of
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
            writeln(err, "reg = ", reg, "  register kind = ", reg_kind);
            report_error(Internal, 576, "ugen.p", "illegal register type ");
        end;
    end;
end;

procedure get_one_reg(arg0: registers; arg1: ^tree; arg2: u16; arg3: RegKind);
label list_append;
begin

    if (regs[arg0].unk7 = xr0) then begin
        if (regs[arg0].unk4 <> 0) then begin
            spill_reg(arg0, arg3);
        end;
    end else if not (remove_from_list(arg0, gp_regs_free)) then begin
        if (remove_from_list(arg0, gp_regs_used)) then begin
            spill_reg(arg0, arg3);
            goto list_append;
        end;
        
        report_error(Internal, 594, "reg_mgr.p", "register not on used/free list");
        return;
    end else begin
        list_append:
        append_to_list(arg0, gp_regs_used);
    end;
    fill_reg(arg0, arg1, arg2, arg3);
end;

procedure get_two_regs(arg0: registers; arg1: ^tree; arg2: u16);
var
    temp_a0: registers;
begin
    Assert(ord(arg0) & 1 = 0);
    get_one_reg(arg0, arg1, arg2, di_reg);
    regs[arg0].unk9 := succ(arg0);
    get_one_reg(succ(arg0), arg1, arg2, di_s_reg);
end;

procedure get_reg(arg0: registers; arg1: ^tree; arg2: u16);
begin
    if ((arg1 <> nil) and (opcode_arch = 0)) then begin
        {Check for: s64, u64, s64*}
        if (arg1^.u.dtype in [Idt, Kdt, Wdt]) then begin
            get_two_regs(arg0, arg1, arg2);
            return;
        end;
    end;

    get_one_reg(arg0, arg1, arg2, i_reg);
end;