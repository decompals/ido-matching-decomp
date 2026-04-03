#ifndef PARM_MGR_H
#define PARM_MGR_H

procedure fix_amt_ref(arg0: ^tree); external;
procedure map_pars_to_regs(arg0: ^Tree; arg1: integer); external;
function parm_reg(arg0: ^Tree): registers; external;
function pass_in_reg(arg0: ^Tree): boolean; external;
function check_amt(arg0: ^Tree): integer; external;
#endif /* PARM_MGR_H */
