#pragma GLOBAL_ASM("asm/7.1/functions/as1/null_terminate.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/eindex.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/name_and_line.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/get_filename.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/call_name_and_line.s")

#ifdef LANGUAGE_PASCAL
procedure call_perror(arg0 : integer; arg1 : pchar);
begin
    call_name_and_line();
    perror(arg1);
    flush(err); /* flush! */
end;
#else
#pragma GLOBAL_ASM("asm/7.1/functions/as1/call_perror.s")
#endif

#pragma GLOBAL_ASM("asm/7.1/functions/as1/new_error.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/posterror.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/p_assertion_failed.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/assertion_failed.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/postcerror.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/negative_file_opt.s")

#ifdef LANGUAGE_PASCAL
function which_opt(arg0: s8): integer;
var
i : integer;
begin
    for i := 0 to 105 do
    begin
        if strcmp(arg0, l_addr(addr(opt_strings[i]))) = 0 then
        begin
            return i;
        end;
    end;
    return 105;
end;
#else
#pragma GLOBAL_ASM("asm/7.1/functions/as1/which_opt.s")
#endif

#pragma GLOBAL_ASM("asm/7.1/functions/as1/get_lstring.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/get_sstring.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/grow_array.s")

#pragma GLOBAL_ASM("asm/7.1/functions/as1/grow_array_size.s")

