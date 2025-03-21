#ifndef EMIT_DW_H
#define EMIT_DW_H
procedure emit_branch_rrll(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: ^tree); external;
procedure emit_branch_rill(arg0: asmcodes; arg1: registers; arg2: integer; arg3: integer; arg4: integer; arg5: ^tree); external;
procedure emit_trap_rri(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: ^tree); external;
procedure emit_trap_ri(arg0: asmcodes; arg1: registers; arg2: integer; arg3: integer; arg4: ^tree); external;
procedure dw_emit_rrr(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers; arg4: ^tree); external;
procedure dw_emit_rri(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer; arg5: ^tree); external;
procedure dw_emit_rr(arg0: asmcodes; arg1: registers; arg2: registers; arg3: ^tree); external;
#endif /* EMIT_DW_H */
