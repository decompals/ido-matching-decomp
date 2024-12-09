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
    return (arg0^.unk30 + 1) <> 0;
end;

function parm_reg(arg0: ^Tree): integer;
begin
    Assert(arg0^.u.Opc in [Upar, Updef, Ushl, Uvreg]);

    if (arg0^.unk30 = -1) then begin
        return ord(xnoreg);
    end;

    if (basicint = 0) then begin
        return arg0^.unk30 div 4;
    end;
 
    return arg0^.unk30 div 8;
end;

{GLOBAL_ASM("asm/7.1/functions/ugen/parm_mgr/map_pdefs_to_regs.s")}

{GLOBAL_ASM("asm/7.1/functions/ugen/parm_mgr/map_pars_to_regs.s")}

#ifdef NON_MATCHING
function check_amt(arg0: ^TRee): integer;
var
    temp: integer;
begin
  
    Assert(arg0^.unk2C >= 0);
    if (basicint = 0) then begin
        if ((arg0^.unk2C >= (n_parm_regs * 4)) or (arg0^.unk2C >= (n_fp_parm_regs * 8))) then begin
            return -1;
        end;
        return pars[arg0^.unk2C div 4];
    end;
    if ((arg0^.unk2C >= (n_parm_regs * 8)) or (arg0^.unk2C >= (4 * n_fp_parm_regs *2 ))) then begin
        return -1;
    end;
    return pars[arg0^.unk2C div 8];
end;
#else
GLOBAL_ASM("asm/7.1/functions/ugen/parm_mgr/check_amt.s")
#endif

{GLOBAL_ASM("asm/7.1/functions/ugen/parm_mgr/check_amt_ref.s")}

{GLOBAL_ASM("asm/7.1/functions/ugen/parm_mgr/fix_amt_ref.s")}


