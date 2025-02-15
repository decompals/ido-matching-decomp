#include "tree.h"
#include "report.h"

var
    basicint: extern u8;
    n_fp_parm_regs: extern integer;
    n_parm_regs: extern integer;
    pars: array [0..16] of integer;

function pass_in_reg(arg0: ^Tree): boolean;
begin
    Assert(arg0^.u.Opc in [Upar, Updef]);
    return (arg0^.u.Constval.dwval_h + 1) <> 0;
end;

function parm_reg(arg0: ^Tree): integer;
begin
    Assert(arg0^.u.Opc in [Upar, Updef, Ushl, Uvreg]);

    if (arg0^.u.Constval.dwval_h= -1) then begin
        return ord(xnoreg);
    end;

    if (basicint = 0) then begin
        return arg0^.u.Constval.dwval_h div 4;
    end;
 
    return arg0^.u.Constval.dwval_h div 8;
end;

GLOBAL_ASM("asm/7.1/functions/ugen/parm_mgr/map_pdefs_to_regs.s")

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

GLOBAL_ASM("asm/7.1/functions/ugen/parm_mgr/check_amt_ref.s")

GLOBAL_ASM("asm/7.1/functions/ugen/parm_mgr/fix_amt_ref.s")


