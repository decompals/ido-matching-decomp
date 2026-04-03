#ifndef ENTRY_EXIT_H
#define ENTRY_EXIT_H

procedure emit_file(arg0: integer; arg1: boolean); external;
procedure clear_saved_regs(); external;
procedure gen_entry(arg0: integer; arg1: integer; arg2: integer; arg3: integer; arg4: integer; arg5: integer); external;
procedure gen_entry_exit(
    arg0: integer;
    arg1: boolean;
    arg2: integer;
    arg3: cardinal;
    arg4: integer;
    arg5: boolean;
    arg6: integer;
    arg7: integer;
    arg8: boolean;
    arg9: boolean;
    argA: boolean;
    argB: integer;
    argC: integer;
    argD: boolean;
    argE: integer;
    arg10: Valu;
    arg12: integer;
    arg13: integer;
    arg14: integer); external;
function is_empty_saved_regs(): boolean; external;

#endif /* ENTRY_EXIT_H */
