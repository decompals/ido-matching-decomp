#include "tree.h"
#include "report.h"

var
    n_fp_parm_regs: extern integer;
    first_pmt_offset: integer;
    n_parm_regs: extern integer;
    basicint: extern u8;
    pars: array [0..16] of integer;
    fix_amt: array [0..4] of boolean;


function pass_in_reg(arg0: ^Tree): boolean;
begin
    Assert(arg0^.u.Opc in [Upar, Updef]);
    return (arg0^.u.Constval.Ival + 1) <> 0;
end;

function parm_reg(arg0: ^Tree): integer;
begin
    Assert(arg0^.u.Opc in [Upar, Updef, Ushl, Uvreg]);

    if (arg0^.u.Constval.Ival = -1) then begin
        return ord(xnoreg);
    end;

    if (basicint = 0) then begin
        return arg0^.u.Constval.Ival div 4;
    end;
 
    return arg0^.u.Constval.Ival div 8;
end;


procedure map_pdefs_to_regs(arg0: ^Tree; arg1: integer);
var
    var_v0: integer;
    var_v1: cardinal;
begin
    for var_v1 := 1 to n_fp_parm_regs do begin
        if arg0 = nil then begin
            return;
        end;
            
        Assert(arg0^.u.Opc = Updef);

        if not (arg0^.u.Dtype in [Qdt, Rdt, Xdt]) then begin
            break;
        end;

        if (arg1 <> -1) and (arg1 < integer((var_v1 - 1) * 2) * 4) then begin
            break;
        end;

        arg0^.u.Constval.dwval_h := integer((var_v1 - 1) * 2) * 4 + 16#B0;
        arg0 := arg0^.next;                
    end;

    while (arg0 <> nil) do begin
        Assert(arg0^.u.Opc = Updef);
        var_v0 := abs(arg0^.u.Offset - first_pmt_offset);

        if (basicint = 0) then begin
            if (var_v0 < n_parm_regs * 4) then begin
                arg0^.u.Constval.dwval_h := var_v0 + 16;
            end else begin
                arg0^.u.Constval.dwval_h := -1;
            end;
        end else begin
            if (var_v0 < (n_parm_regs * 8)) then begin
                arg0^.u.Constval.dwval_h := var_v0 + 32;
            end else begin
                arg0^.u.Constval.dwval_h := -1;
            end;
        end;
        arg0 := arg0^.next;
    end;
end;

GLOBAL_ASM("asm/7.1/functions/ugen/parm_mgr/map_pars_to_regs.s")

function check_amt(arg0: ^Tree): integer;
var
    temp: integer;
begin
  
    Assert(arg0^.u.Offset >= 0);
    temp := 4;
    if (basicint = 0) then begin
        if ((arg0^.u.Offset >= (n_parm_regs * 4)) or (arg0^.u.Offset >= (n_fp_parm_regs * 2 * temp))) then begin
            return -1;
        end;
        return pars[arg0^.u.Offset div 4];
    end;

    if (arg0^.u.Offset >= (n_parm_regs * 8)) or ((arg0^.u.Offset >= (n_fp_parm_regs * 2 * temp))) then begin
        return -1;
    end;
    return pars[arg0^.u.Offset div 8];
end;

procedure check_amt_ref(arg0: ^tree);
label loop;
var
    temp_val: integer;
begin

    loop:
    arg0 := arg0;
    temp_val := 4; {Required to match}
    
    if (basicint = 0) then begin
        if (((arg0^.u.Opc = Ulod) and (arg0^.u.Mtype = Amt)) and ((arg0^.u.Offset < (n_parm_regs * 4)) 
            or (arg0^.u.Offset < (n_fp_parm_regs * 2 * temp_val)))) then begin
            pars[arg0^.u.Offset div 4] := -1;
            fix_amt[arg0^.u.Offset div 4] := true;
            return;
        end;
    end else if (((arg0^.u.Opc = Ulod) and (arg0^.u.Mtype = Amt)) and ((arg0^.u.Offset < (n_parm_regs * 8)) or (arg0^.u.Offset < (n_fp_parm_regs * 4 * temp_val)))) then begin
        pars[arg0^.u.Offset div 8] := -1;
        fix_amt[arg0^.u.Offset div 8] := true;
        return;
    end;
    
    if ((arg0^.op1 <> nil) and (arg0^.u.opc <> Ucg2)) then begin
        check_amt_ref(arg0^.op1);
    end;
    if (arg0^.op2 <> nil) then begin
	check_amt_ref(arg0^.op2);
    end;
    
end;

(*
 Scratch: https://decomp.me/scratch/A6XPP
 Score: 280 (98.10%)
*)
#ifdef NON_MATCHING
procedure fix_amt_ref(arg0: ^tree);
var
    i: integer; {s2}
    temp_v1: integer;
    temp_v0: ^tree;
    var_s0: ^tree; {s0}
begin
    temp_v1 := 3;
    
    for i := 0 to temp_v1 do begin
        fix_amt[i] := false;
    end;

    var_s0 := arg0^.next;
    while not ((var_s0^.u.Opc in [Uabs..Uirsv]) ) do begin        
        if (var_s0^.u.Opc = Upar) then begin
            check_amt_ref(var_s0^.op1);
        end;
        var_s0 := var_s0^.next;
    end;

    for i := 0 to temp_v1 do begin
        if (fix_amt[i]) then begin
            temp_v0 := build_op(Ulod);
            temp_v0^.u.Dtype := addr_dtype;
            temp_v0^.u.Mtype := Rmt;
            temp_v0^.u.Length := unitsperaddr;
            temp_v0^.u.Lexlev := 0;
            temp_v0^.u.Offset := (i + 4) * unitsperaddr;

            temp_v0 := build_1op(Ustr, temp_v0);
            temp_v0^.u.Dtype := addr_dtype;
            temp_v0^.u.Mtype := Amt;
            temp_v0^.u.Length := i * unitsperaddr;
            temp_v0^.u.Offset := i;
            
            temp_v0^.u.Lexlev := 0;
            
            temp_v0^.next := arg0^.next;
            arg0^.next := temp_v0;

            if (temp_v0 <> nil) then begin end;
        end;
    end;
end;
#else
GLOBAL_ASM("asm/7.1/functions/ugen/parm_mgr/fix_amt_ref.s")
#endif

