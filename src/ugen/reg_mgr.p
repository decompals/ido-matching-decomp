#include "common.h"
#include "report.h"
#include "tree.h"
#include "temp_mgr.h"
#include "emit.h"
#include "ugen_regdef.h"

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
    usage_count: u16;
    unk6: registers;
    reg_available: registers;
    reg_kind: RegKind;
    unk9: registers;
end;

type
    regArray = array [registers] of integer;

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
    ugen_fp_callee_saved: set of registers;
    saved_regs: set of registers;
    restricted_fp_regs: RegArray;
    restricted_regs: RegArray;
    kind_tab: array [registers] of registers;
    mips_cg_regs: array [1..100] of registers;
    n_cg_regs: integer;
    n_unsaved_regs: integer;
    n_unsaved_fp_regs: integer;
    n_parm_regs: integer;
    n_fp_cg_regs: integer;
    n_fp_parm_regs: integer;
    n_saved_regs: integer;
    fp32regs: boolean;
    n_saved_fp_regs: integer;
    ufsm: boolean;

procedure add_to_fp_free_list(arg0: registers; arg1: RegKind); forward;
procedure add_to_free_list(arg0: registers); forward;
procedure inc_usage(arg0: registers; arg1: u16); forward;

procedure clear_restricted_regs();
var 
    i: registers;
begin
    for i := first(registers) to last(registers) do begin
        restricted_regs[i] := 0;
        restricted_fp_regs[i] := 0;
    end;
end;

procedure restricted_reg(arg0: registers);
begin
    restricted_regs[arg0] := restricted_regs[arg0]  + 1;
end;

procedure restricted_fp_reg(arg0: registers);
begin
    restricted_fp_regs[arg0] := restricted_fp_regs[arg0]  + 1;
end;

function find_non_special_reg(arg0: regarray; var arg1: UsedRegs): registers;
var
    var_v1: registers;
begin
    var_v1 := arg1.unk0;

    while (var_v1 <> arg1.unk1) do begin
        if (arg0[var_v1] = 0) then begin
            return var_v1;
        end;
        
        var_v1 := regs[var_v1].unk6;
    end;

    report_error(Internal, 280, "reg_mgr.p", "Needed register: all permantently allocated: impossible ");
end;

function get_reg_kind(arg0: registers): registers;
begin
    return kind_tab[arg0];
end;

function kind_of_register(arg0: registers): RegKind;
begin
    return regs[arg0].reg_kind;
end;

procedure init_regs();
var
    i: registers;
    j: cardinal;
begin
    for i := xr0 to xnoreg do begin
        regs[i].unk0 := nil;
        regs[i].usage_count := 0;
        regs[i].unk6 := xnoreg;
        regs[i].reg_available := gpr_zero;
        regs[i].reg_kind := no_reg;
    end;
    
    gp_regs_free.unk0 := xnoreg;
    gp_regs_free.unk1 := xnoreg;

    for j := 1 to n_cg_regs do begin
        add_to_free_list(mips_cg_regs[j]);
    end;

    for i := gpr_t0 to registers(n_unsaved_regs + 7) do begin
        add_to_free_list(i);
    end;

    fp_regs_free.unk0 := xnoreg;
    fp_regs_free.unk1 := xnoreg;

    i := xfr4;
    for j := 1 to n_fp_cg_regs do begin
        add_to_fp_free_list(i, no_reg);
        i := succ(succ(i));
    end;

    i := xfr16;
    for j := 1 to n_unsaved_fp_regs do begin
        add_to_fp_free_list(i, no_reg);
        i := succ(succ(i));
    end;

    if (fp32regs) then begin
        i := xfr1;
        for j := 1 to 16 do begin
            add_to_fp_free_list(i, no_reg);
            i := succ(succ(i));
        end;
    end;
    for i := gpr_a0 to registers(ord(n_parm_regs) + 3) do begin
        regs[i].reg_available := gpr_zero;
        regs[i].usage_count := 0;
    end;

    i := xfr12;
    while (i <= registers(cardinal((n_fp_parm_regs * 2) + 16#2A))) do begin
        regs[i].reg_available := gpr_zero;
        regs[i].usage_count := 0;
        i := succ(succ(i));
    end;

    for i := xr16 to registers(ord (n_saved_regs) + 15) do begin
        regs[i].reg_available := gpr_zero;
        regs[i].usage_count := 0;
    end;

    i := registers(16#34);
    while (i <= registers(cardinal((n_saved_fp_regs * 2) + 16#32))) do begin
        if ufsm then begin
            add_to_fp_free_list(i, no_reg);
        end else begin
            regs[i].reg_available := gpr_zero;
            regs[i].usage_count := 0;
        end;
        i := succ(succ(i));
    end;


    gp_regs_used.unk0 := xnoreg;
    gp_regs_used.unk1 := xnoreg;
    fp_regs_used.unk0 := xnoreg;
    fp_regs_used.unk1 := xnoreg;
end;

procedure fill_reg(reg: registers; contents: ^tree; usage_count: u16; reg_kind: RegKind);
begin
    regs[reg].unk0 := contents;
    regs[reg].usage_count := usage_count;
    regs[reg].reg_kind := reg_kind;
end;

procedure copy_reg(op: asmcodes; source_reg: registers; dest_reg: registers);
begin
    emit_rr(op, dest_reg, source_reg);
    regs[dest_reg].unk0 := regs[source_reg].unk0;
    regs[dest_reg].usage_count := regs[source_reg].usage_count;
    regs[dest_reg].reg_kind := regs[source_reg].reg_kind;
end;


{ Why use *pass by reference* in this function? }
function list_is_empty(var arg0: registers): boolean;
begin
    return arg0 = xnoreg;
end;

procedure dump_reg(reg: registers);
label loop;
begin
loop:
    write(output, "register ", reg);
    write(output, ": kind  ", regs[reg].reg_kind);
    write(output, ", usage ", regs[reg].usage_count);
    writeln(output);
    if (regs[reg].reg_kind = di_reg) then begin
        reg := regs[reg].unk9;
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
        end else begin
            arg0.unk1 := var_a1;
        end;
    end;

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
    Assert(regs[arg0].reg_available <> gpr_zero);
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

    if (regs[arg0].reg_available = gpr_zero) then begin
        if (regs[arg0].usage_count <> 0) then begin
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

procedure get_reg1(arg0: registers; arg1: ^tree; arg2: u16);
var
    temp_v0: registers;
begin
    if ((regs[arg0].reg_available <> gpr_zero) and (remove_from_list(arg0, gp_regs_free))) then begin
            append_to_list(arg0, gp_regs_used);
            if (opcode_arch = 0) then begin
                if (arg1^.u.Dtype in [Idt, Kdt, Wdt]) then begin
                    fill_reg(arg0, arg1, arg2, di_reg);
                    return;
                end;
            end;
            fill_reg(arg0, arg1, arg2, i_reg);
        return;
    end;
    inc_usage(arg0, arg2);

    if ((opcode_arch = 0) and (arg1^.u.Dtype in [Idt, Kdt, Wdt])) then begin
        regs[arg0].reg_kind := di_reg;
    end;

    if ((arg1 <> nil) and (opcode_arch = 0) and  (arg1^.u.Dtype in [Idt, Kdt, Wdt])) then begin
        temp_v0 := succ(arg0);
        regs[arg0].unk9 := temp_v0;

        if ((regs[temp_v0].reg_available <> gpr_zero) and (remove_from_list(temp_v0, gp_regs_free))) then begin
            append_to_list(temp_v0, gp_regs_used);
            fill_reg(temp_v0, arg1, arg2, di_s_reg);
            return;
        end;

        inc_usage(temp_v0, arg2);

        if (opcode_arch = 0) then begin
            if (arg1^.u.dtype in [Idt, Kdt, Wdt]) then begin
                regs[temp_v0].reg_kind := di_s_reg;
            end;
        end;
    end;
end;

procedure get_fp_reg(arg0: registers; arg1: ^tree; arg2: RegKind; arg3: u16);
begin
    if (regs[arg0].reg_available = gpr_zero) then begin
        if (regs[arg0].usage_count <> 0) then begin
            spill_reg(arg0, regs[arg0].reg_kind);
        end;
    end else begin

    if not (remove_from_list(arg0, fp_regs_free)) then begin
        if (remove_from_list(arg0, fp_regs_used)) then begin
            spill_reg(arg0, regs[arg0].reg_kind);
        end else begin
            report_error(Internal, 678, "reg_mgr.p", "fp register not on used/free list");
            return;
        end;
    end;
    
    append_to_list(arg0, fp_regs_used);
    end;
    
    fill_reg(arg0, arg1, arg3, arg2);
end;

procedure get_fp_reg1(arg0: registers; arg1: ^tree; arg2: RegKind; arg3: u16);
begin
    if ((regs[arg0].reg_available <> gpr_zero) and (remove_from_list(arg0, fp_regs_free))) then begin
        append_to_list(arg0, fp_regs_used);
        fill_reg(arg0, arg1, arg3, arg2);
    end else begin
        inc_usage(arg0, arg3);
    end;
end;

function free_reg_is_available(): boolean;
begin
    if (gp_regs_free.unk0 = xnoreg) then begin
        return false;
    end;
    return true;
end;

function can_get_two_regs(arg0: UsedRegs): boolean;
var
    var_v0: registers;
begin
    if (arg0.unk0 = xnoreg) then begin
        return false;
    end;

    var_v0 := arg0.unk0;
    while (ord(var_v0) & 1 <> 0) do begin
        var_v0 := regs[var_v0].unk6;
    end;
    if (var_v0 = xnoreg) then begin
        return false;
    end;
    return true;
end;

function spill_two_regs(): registers;
var
    temp_v0: registers;
    var_s0: registers;
begin
    temp_v0 := remove_direg(gp_regs_used);
    
    if (regs[temp_v0].reg_kind = di_reg) then begin
        spill_to_temp(temp_v0, size_tab[di_reg]);
        Assert(remove_from_list(succ(temp_v0), gp_regs_used));
    end else begin
        spill_to_temp(temp_v0, size_tab[i_reg]);
        if (remove_from_list(succ(temp_v0), gp_regs_used)) then begin
            spill_to_temp(succ(temp_v0), size_tab[i_reg]);
        end else if not (remove_from_list(succ(temp_v0), gp_regs_free)) then begin
            report_error(Internal, 773, "reg_mgr.p", "register not on used/free list");
        end;
    end;
    regs[temp_v0].unk9 := succ(temp_v0);
    return temp_v0;
end;

function get_two_free_regs(arg0: ^tree; arg1: u16): registers;
var
    temp_v0: registers;
begin
    Assert((arg0 <> nil) and (opcode_arch = 0) and (arg0^.u.dtype in [Idt, Kdt, Wdt]));

    if (can_get_two_regs(gp_regs_free)) then begin
        temp_v0 := remove_direg(gp_regs_free);
        regs[temp_v0].unk9 :=  succ(temp_v0);
        get_one_reg(regs[temp_v0].unk9, arg0, arg1, di_s_reg);
    end else begin
        temp_v0 := spill_two_regs();
        append_to_list(regs[temp_v0].unk9, gp_regs_used);
        fill_reg(regs[temp_v0].unk9, arg0, arg1, di_s_reg);
    end;
    append_to_list(temp_v0, gp_regs_used);
    fill_reg(temp_v0, arg0, arg1, di_reg);
    return temp_v0;
end;

function get_one_free_reg(arg0: ^tree; arg1: u16): registers;
var
    temp_v0: registers;
    temp_v1: RegKind;
    
begin
    if (list_is_empty(gp_regs_free.unk0)) then begin
        temp_v0 := get_head(gp_regs_used);
        temp_v1 := regs[temp_v0].reg_kind;
        if ((temp_v1 = di_reg) or (temp_v1 = di_s_reg)) then begin
            temp_v0 := spill_two_regs();
            append_to_list(regs[temp_v0].unk9, gp_regs_free);
            fill_reg(regs[temp_v0].unk9, nil, 0, i_reg);
        end else begin
            temp_v0 := remove_head(gp_regs_used);
            if (opcode_arch = 1) then begin
                spill_to_temp(temp_v0, size_tab2[i_reg]);
            end else begin
                spill_to_temp(temp_v0, size_tab[i_reg]);
            end;
        end;
    end else begin
        temp_v0 := remove_head(gp_regs_free);
    end;

    append_to_list(temp_v0, gp_regs_used);
    fill_reg(temp_v0, arg0, arg1, i_reg);
    return temp_v0;
end;

function get_free_reg(arg0: ^tree; arg1: u16): registers;
begin
    if ((arg0 <> nil) and (opcode_arch = 0)) then begin
        if (arg0^.u.Dtype in [Idt, Kdt, Wdt]) then begin
            return get_two_free_regs(arg0, arg1);
        end;
    end;
    return get_one_free_reg(arg0, arg1);
end;

function get_free_fp_reg(arg0: ^tree; arg1: RegKind; arg2: u16): registers;
var
    var_s0: registers;
begin
    if (list_is_empty(fp_regs_free.unk0)) then begin
        var_s0 := remove_head(fp_regs_used);

        if (isa >= ISA_MIPS3) then begin
            spill_to_temp(var_s0, size_tab2[regs[var_s0].reg_kind]);
        end else begin
            spill_to_temp(var_s0, size_tab[regs[var_s0].reg_kind]);
        end;
    end else begin
        var_s0 := remove_head(fp_regs_free);

        if (var_s0 in ugen_fp_callee_saved) then begin
            saved_regs := saved_regs + [var_s0];
        end;
    end;
    append_to_list(var_s0, fp_regs_used);
    fill_reg(var_s0, arg0, arg2, arg1);
    return var_s0;
end;

function content_of(arg0: registers): pointer;
var
    var_v0: ^tree;
begin
    var_v0 := regs[arg0].unk0;
    if (var_v0 = nil) then begin
        report_error(Internal, 867, "reg_mgr.p", "register content is empty");
        return; 
    end;

    content_of := var_v0;
end;

procedure inc_usage({arg0: registers; arg1: u16});
begin
    regs[arg0].usage_count := regs[arg0].usage_count + arg1;
end;

procedure dec_usage(arg0: registers);
var
    v0: registers;
begin
    if (regs[arg0].usage_count = 0) then begin
        report_error(Internal, 884, "reg_mgr.p", "usage count is 0, cannot decrement");
    end else begin
        regs[arg0].usage_count := regs[arg0].usage_count - 1;
    end;

    if ((opcode_arch = 0) and (regs[arg0].reg_kind = di_reg)) then begin
        v0 := regs[arg0].unk9;
        if (regs[v0].usage_count = 0) then begin
            report_error(Internal, 891, "reg_mgr.p", "usage count is 0, cannot decrement");
            return;
        end;
        regs[v0].usage_count := regs[v0].usage_count - 1;
    end;
end;

procedure free_reg(arg0: registers);
var
    temp_a0: registers;
begin
    dec_usage(arg0);

    if (regs[arg0].usage_count = 0) then begin
        if (regs[arg0].reg_available <> gpr_zero) then begin
            if not (remove_from_list(arg0, gp_regs_used)) then begin
                report_error(Internal, 907, "reg_mgr.p", "register to be removed not on used list");
                return;
            end;
            append_to_list(arg0, gp_regs_free);
        end;
        if ((opcode_arch = 0) and (regs[arg0].reg_kind = di_reg)) then begin
            fill_reg(arg0, nil, 0, i_reg);
            temp_a0 := regs[arg0].unk9;
            if (regs[temp_a0].reg_available <> gpr_zero) then begin
                if not (remove_from_list(temp_a0, gp_regs_used)) then begin
                    report_error(Internal, 917, "reg_mgr.p", "register to be removed not on free list");
                    return;
                end;
                append_to_list(temp_a0, gp_regs_free);
            end;
            fill_reg(temp_a0, nil, 0, i_reg);
            return;
        end;
        fill_reg(arg0, nil, 0, i_reg);
    end;
end;

procedure free_fp_reg(arg0: registers; arg1: RegKind);
begin
    dec_usage(arg0);

    if ((regs[arg0].usage_count = 0)) then begin
        if ((regs[arg0].reg_available <> gpr_zero)) then begin
            if not (remove_from_list(arg0, fp_regs_used)) then begin
                report_error(Internal, 937, "reg_mgr.p", "fp register to be removed not on free list");
                return;
            end;
            append_to_list(arg0, fp_regs_free);
        end;
        fill_reg(arg0, nil, 0, arg1);
    end;
end;

{ Weird control flow }
procedure force_free_reg(arg0: registers);
begin
    if ((regs[arg0].reg_available <> gpr_zero)) then begin
        if (remove_from_list(arg0, gp_regs_used)) then begin 
            return;
        end;
        append_to_list(arg0, gp_regs_free);
    end;
    fill_reg(arg0, nil, 0, i_reg);
end;

procedure add_to_free_list({arg0: registers});
begin
    if (regs[arg0].usage_count <> 0) then begin
        report_error(Internal, 967, "reg_mgr.p", "register not free");
    end;
    fill_reg(arg0, nil, 0, i_reg);
    regs[arg0].reg_available := gpr_at;
    append_to_list(arg0, gp_regs_free);
end;

procedure add_to_fp_free_list({arg0: registers; arg1: RegKind});
begin
    if (regs[arg0].usage_count <> 0) then begin
        report_error(Internal, 977, "reg_mgr.p", "fp register not free");
    end;
    fill_reg(arg0, nil, 0, arg1);
    regs[arg0].reg_available := gpr_at;
    append_to_list(arg0, fp_regs_free);
end;

procedure remove_from_free_list(arg0: registers);
var
    temp_a0: registers;
begin
    if (regs[arg0].reg_available <> gpr_zero) then begin
        if not (remove_from_list(arg0, gp_regs_free)) then begin
            report_error(Internal, 990, "reg_mgr.p", "register not free");
            return;
        end;
        regs[arg0].reg_available := gpr_zero;
    end;
    fill_reg(arg0, nil, 0, i_reg);

    if ((opcode_arch = 0) and (regs[arg0].reg_kind = di_reg)) then begin
        temp_a0 := regs[arg0].unk9;
        if (regs[temp_a0].reg_available <> gpr_zero) then begin
            if not (remove_from_list(temp_a0, gp_regs_free)) then begin
                report_error(Internal, 1000, "reg_mgr.p", "register not free");
                return;
            end;
            regs[temp_a0].reg_available := gpr_zero;
        end;
        fill_reg(temp_a0, nil, 0, i_reg);
    end;
end;

procedure remove_from_fp_free_list(arg0: registers; arg1: RegKind);
begin
    if (regs[arg0].reg_available <> gpr_zero) then begin
        if not (remove_from_list(arg0, fp_regs_free)) then begin
            report_error(Internal, 1013, "reg_mgr.p", "fp register not free");
            return;
        end;
        regs[arg0].reg_available := gpr_zero;
    end;
    fill_reg(arg0, nil, 0, arg1);
end;

function is_available(arg0: registers): registers;
begin
    return regs[arg0].reg_available;
end;

procedure check_no_used();
begin
    if not (list_is_empty(gp_regs_used.unk0)) then begin
        print_regs(gp_regs_used);
        report_error(Internal, 1031, "reg_mgr.p", "gp registers left in use at bb boundary");
    end;

    if not (list_is_empty(fp_regs_used.unk0)) then begin
        report_error(Internal, 1034, "reg_mgr.p", "fp registers left in use at bb boundary");
        print_regs(fp_regs_used); {@bug: Unreached code }
    end;
end;

function usage_count(arg0: registers): u16;
begin
    return regs[arg0].usage_count;
end;

procedure move_to_end_fp_list(arg0: registers);
begin
    if (remove_from_list(arg0, fp_regs_used)) then begin
        append_to_list(arg0, fp_regs_used);
    end;
end;

procedure move_to_end_gp_list(arg0: registers);
begin
    if (remove_from_list(arg0, gp_regs_used)) then begin
        append_to_list(arg0, gp_regs_used);
    end;
end;

function get_free_fp_reg_special(arg0: ^tree; arg1: RegKind; arg2: u16): registers;
var
    temp_s0: registers;
begin
    if not (list_is_empty(fp_regs_free.unk0)) then begin
        return get_free_fp_reg(arg0, arg1, arg2);
    end;
    temp_s0 := find_non_special_reg(restricted_fp_regs, fp_regs_used);

    if not (remove_from_list(temp_s0, fp_regs_used)) then begin
        report_error(Internal, 1075, "reg_mgr.p", "could not remove register from fp_regs_used list!");
    end;

    spill_to_temp(temp_s0, size_tab[regs[temp_s0].reg_kind]);
    append_to_list(temp_s0, fp_regs_used);
    fill_reg(temp_s0, arg0, arg2, arg1); 
    return temp_s0;
end;

function get_free_reg_special(arg0: ^tree; arg1: u16): registers;
var
    temp_s0: registers;
begin
    if not (list_is_empty(gp_regs_free.unk0)) then begin
        return get_free_reg(arg0, arg1);
    end;
    temp_s0 := find_non_special_reg(restricted_regs, gp_regs_used);
    if not (remove_from_list(temp_s0, gp_regs_used)) then begin
        report_error(Internal, 1094, "reg_mgr.p", "could not remove register from regs_used list!");
    end;
    spill_to_temp(temp_s0, size_tab[regs[temp_s0].reg_kind]);
    append_to_list(temp_s0, gp_regs_used);
    fill_reg(temp_s0, arg0, arg1, i_reg);
    return temp_s0;
end;
