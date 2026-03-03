#include "common.h"
#include "report.h"
#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"
#include "cmplrs/binasm.h"
#include "cmplrs/uoptions.h"
#include "cmplrs/stinfc.h"

type
    hex_str = packed array [1..10] of char; /* :=  "0123456789ABCDEF" */
    OpcodeTabString = packed array [1..10] of char;
    Regname = packed array[1..5] of char;
    BinasmFile = File of binasm;
    itype_str = array [1..12] of char;
    reg_str = array [1..5] of char;
    
var
    source_language: integer;
    hex_tab : array [0..15] of char;
    in_file: BinasmFile;
    current_filen: integer;
    current_linen: integer;
    source_file: Text;
    source_file_name: Filename;
    opcode_tab: array [first(asmcodes)..last(asmcodes)] of OpcodeTabString;
    reg_name_tab: array [first(registers)..last(registers)] of Regname;
    itype_tab: array [first(itype)..last(itype)] of itype_str;
    iopt_tab: array [first(set_value)..last(set_value)] of itype_str;
    ioption_type_tab: array [opt_compat_align] of array [1..15] of char;
    second_dli: boolean;
    val64: Valu;

#define ST_COPY(ustr, st) len := 1; while (st^[len] <> chr(0)) do begin ustr[len] := st^[len]; len := len + 1 end;
procedure put_string(var arg0: text; arg1: boolean); forward;

procedure put_integer_ws(var pFile: text; val: integer);
begin
    if val = 0 then return;
        if val > 0 then begin
            write(pFile, '+');
        end;
    write(pFile, val:1:10);
end;

procedure put_sym(var pFile: Text; idn: integer);
var
    sp40: Stringtext;
    str: pst_string;
    len: integer;

begin
    if (idn <> 0) then begin
        if (idn < 0) then begin
            write(pFile, '$', abs(idn):1);
        end else if ((st_fglobal_idn(idn) <> 1) and (source_language <> C_SOURCE)) then begin
            write(pFile, "$$", idn:1);
        end else begin
            sp40.ss := "";
            str := st_str_idn(idn);

            if (str = pointer(-1)) then begin
                write(pFile, "$$", idn:1);
            end else begin
                ST_COPY(sp40.ss, str);
            end;

            write(pFile, sp40.ss:0);
        end;
        
    end;
end;

procedure hex8(number: integer; var str: hex_str);
var
    i: integer;
    digit: 0..15;
begin
     str[1] := '0';
     str[2] := 'x';

    for i := 3 to 10 do begin
        digit := rshift(number, 32 - (i - 2) * 4) & 15;
        str[i] := hex_tab[digit];
    end;
    
     str[1] := '0';
     str[2] := 'x';
end;    

procedure put_hex10(var arg0: Text; arg1: integer);
var
    sp26: hex_str;
begin
    hex8(arg1, sp26);
    write(arg0, sp26);
end;

procedure hex_2(digit: char; var str: hex_str);
begin
    str[1] := hex_tab[(rshift(digit, 4) & 255)];
    str[2] := hex_tab[ord(digit) -((rshift(digit, 4) & 255) * 16)];
end; 

procedure put_alpha(var arg0: text; arg1: char);
var
    sp26: hex_str;
begin
    if not(arg1 in [' '..'~']) or (arg1 = '"') or (arg1 = '\') then begin
        hex_2(arg1, sp26);
        write(arg0, "\\X", sp26);
    end else begin
        write(arg0, arg1);
    end;
end;

procedure write_instruction(var arg0: Text);
label done;
var
    var_s7: cardinal;
    var_s2: integer;
    var_s0: cardinal;
    
begin
    write(arg0, chr(9));

    if ((in_file^.op <> zcia) and (in_file^.op <> zdli)) then begin
        write(arg0, opcode_tab[in_file^.op]:0, chr(9));
    end;
    with in_file^ do begin
    case in_file^.form of 
        frob:
        begin
            write(arg0, reg_name_tab[reg1]:0);
            write(arg0, ", ");

            if (symno <> 0) then begin
                put_sym(arg0, symno);
                put_integer_ws(arg0, regoffset);
            end else begin
                write(arg0, regoffset:1);
            end;
        
            write(arg0, '(');
            write(arg0, reg_name_tab[reg2]:0);
            write(arg0, ')');
            if (mem_tag <> 0) then begin
                write(arg0, ", ");
                write(arg0, mem_tag:1);
            end;
        end;

        fra:
        begin
            write(arg0, reg_name_tab[reg1]:0);
            write(arg0, ", ");
            put_sym(arg0, symno);
            put_integer_ws(arg0, immediate);
            if (mem_tag <> 0) then begin
                write(arg0, ", ");
                write(arg0, mem_tag:1);
            end;
        end;

        fri:
        begin
            if (op <> znop) then begin
                if ((op = fli_s) or (op = fli_d)) then begin
                    write(arg0, reg_name_tab[reg1]:0);
                    write(arg0,  ", ");
                    var_s2 := in_file^.immediate;
                    for var_s7 := 1 to integer(var_s2 - 1) div 16 + 1 do begin {Get align 16}
                        get(in_file);
                        for var_s0 := 1 to 16 do begin
                            if (lshift(var_s7, 4) - 16 + var_s0 <= var_s2) then begin
                                put_alpha(arg0, in_file^.data[var_s0]);
                            end else begin
                                goto done;
                            end;
                        end;
                    end;
                end else if (op = zcia) then begin
                    var_s2 := in_file^.immediate;
                    for var_s7 := 1 to integer(var_s2 - 1) div 16 + 1 do begin {Get align 16}
                        get(in_file);
                        for var_s0 := 1 to 16 do begin
                            if (lshift(var_s7, 4) - 16 + var_s0 <= var_s2) then begin
                                write(arg0, in_file^.data[var_s0]);
                            end else begin
                                goto done;
                            end;
                        end;
                    end;
                end else if (op = zdli) then begin
                    if (second_dli) then begin
                        write(arg0, opcode_tab[in_file^.op]:0, chr(9));
                        write(arg0, reg_name_tab[reg1]:0);
                        write(arg0, ", ");
                        val64.dwval_l := immediate;
                        write(arg0, val64.dwval:1);
                        second_dli := false;
                    end else begin
                        val64.dwval_h := immediate; 
                        second_dli := true;
                    end;
                end else begin
                    write(arg0, reg_name_tab[reg1]:0);
                    write(arg0, ", ");
                    write(arg0, immediate:1);
                end;
            end;
        end;

        frrr:
        begin
            if (reg1 <> xnoreg) then begin
                write(arg0, reg_name_tab[reg1]:0);
                write(arg0, ", ");
            end;
            write(arg0, reg_name_tab[reg2]:0);
            write(arg0, ", ");
            write(arg0, reg_name_tab[reg3]:0); 
        end;

        frri:
        begin
            write(arg0, reg_name_tab[reg1]:0);
            write(arg0, ", ");
            write(arg0, reg_name_tab[reg2]:0);
            write(arg0, ", ");
            write(arg0, immediate:1);   
        end;

        frr:
        begin
            write(arg0, reg_name_tab[reg1]:0);
            write(arg0, ", ");
            write(arg0, reg_name_tab[reg2]:0);   
        end;

        fa:
        begin
            put_sym(arg0, symno);
            put_integer_ws(arg0, immediate);
        end;

        fr:
        begin
            write(arg0, reg_name_tab[reg1]:0);
        end;
        
        fi:
        begin
            write(arg0, immediate:1);
        end;
        
        frrl:
        begin
            write(arg0, reg_name_tab[reg1]:0);
            write(arg0, ", ");
            write(arg0, reg_name_tab[reg2]:0);
            write(arg0, ", ");
            put_sym(arg0, symno);
        end;
        
        frl:
        begin
            write(arg0, reg_name_tab[reg1]:0);
            write(arg0, ", ");
            put_sym(arg0, symno);
        end;

        fl:
        begin
            put_sym(arg0, symno);
            
        end;

        forrr:
        begin
            report_error(Internal, 939, "aio.p", "orrr type instruction");
        end;

        fril:
        begin
            write(arg0, reg_name_tab[reg1]:0);
            write(arg0, ", ");
            write(arg0, immediate:1);
            write(arg0, ", ");   
            put_sym(arg0, symno);
        end;
    end;
    end;

done:
    writeln(arg0);
end;

procedure print_source(var arg0: Text; idn: integer; arg2: integer);
var
    str: pst_string;
    len: integer;
begin
    if (idn <> current_filen) then begin
        current_filen := idn;
        if (idn = 0) then begin
            idn := 2;
        end;

        str := st_str_idn(idn);
        for len := 1 to FileNameLen do begin
            source_file_name[len] := ' ';
        end;
        ST_COPY(source_file_name, str);
        if (source_file_name[1] = ' ') then begin
            report_error(Internal, 977, "aio.p", "file name is null");
            return;
        end;
        current_linen := 16#7FFFFFFF;
    end;

    if (arg2 < (current_linen - 1)) then begin
        reset(source_file, source_file_name);
        if (eof(source_file)) then begin
            return;
        end;
        current_linen := 1;
    end;

    if (((arg2 - current_linen) >= 6)) then begin
        repeat begin
            if (eof(source_file)) then begin
                return;
            end;
        
            while not eoln(source_file) do begin
                get(source_file);
            end;

            get(source_file);
            current_linen := current_linen + 1;
        end until not ((current_linen < arg2));
    end;

    while (current_linen <= arg2) do begin
        write(arg0, " #", current_linen:4, chr(9));

        while not (eoln(source_file)) do begin
            write(arg0, source_file^);
            get(source_file);
        end;

        writeln(arg0);
        get(source_file);
        current_linen := current_linen + 1;
    end;
end;

procedure write_directive(var arg0: Text);
    var
        sp44: cardinal;
begin
    {temp_s2 := unk4;}
    with in_file^ do begin
    if instr <> isym then begin
        if instr = ilabel then begin
            put_sym(arg0, symno);
            write(arg0, ':');
            writeln(arg0);
        end else begin
            write(arg0, chr(9));
            write(arg0, itype_tab[instr]:0, chr(9));
            case instr of
            ialign,
            ispace,
            ishift_addr:
            begin
                write(arg0, length:1);
            end;

            idouble,
            ifloat:
            begin
                sp44 := rep;
                put_string(arg0, false);
                write(arg0, ':');
                write(arg0, sp44:1);
            end;

            iascii,
            iasciiz:
            begin
                put_string(arg0, true);
            end;

            ifile:
            begin
                write(arg0, symno:1);
                write(arg0, ' ');
                put_string(arg0, true);
            end;

            ibyte,
            ihalf,
            igpword,
            iword:
            begin
                if symno = 0 then begin
                    write(arg0, expression:1);
                    write(arg0, ' ');
                    write(arg0, ':');
                    write(arg0, ' ');
                    write(arg0, replicate:1);
                end else begin
                    put_sym(arg0, symno);
                    put_integer_ws(arg0, expression);
                end;
            end;

            idword:
            begin
                val64.dwval_l := expression;
                get(in_file);
                val64.dwval_h := in_file^.expression;
                write(arg0, val64.dwval:1);
                write(arg0, ' ');
                write(arg0, ':');
                write(arg0, ' ');
                write(arg0, rep:1);
            end;
            
            icomm,
            ilcomm,
            iextern:
            begin
                put_sym(arg0, symno);
                write(arg0, ' ');
                write(arg0, length:1);
                if rep <> 0 then begin
                    write(arg0, ' ');
                    write(arg0, 'S');
                end;
            end;
            iweakext:
            begin
                put_sym(arg0, symno);
                if lexlevel <> 0 then begin
                    write(arg0, ',');
                    put_sym(arg0, lexlevel);
                end;
            end;

            iglobal,
            iend,
            ilab:
            begin
                put_sym(arg0, symno);
            end;

            iframe:
            begin
                write(arg0, reg_name_tab[framereg]:0);
                write(arg0, ', ');
                write(arg0, frameoffset:1);
                write(arg0, ', ');
                write(arg0, reg_name_tab[pcreg]:0);
            end;

            ivreg:
            begin
                write(arg0, reg_name_tab[reg1]:0);
                write(arg0, ', ');
                write(arg0, immediate:1);
                write(arg0, ', ');
                write(arg0, symno:1);
            end;
            iverstamp:
            begin
                write(arg0, majornumber:1);
                write(arg0, ' ');
                write(arg0, minornumber:1);
            end;
            iloc:
            begin
                write(arg0, filenumber:1);
                write(arg0, ' ');
                write(arg0, linenumber:1);
            end;

            imask,
            ifmask:
            begin
                put_hex10(arg0, regmask);
                { should be write_string instead of write_char here, using two spaces}
                write(arg0, '  ');
                write(arg0, regoffset:1);
            end;
            ient,
            iaent:
            begin
                put_sym(arg0, symno);
                write(arg0, ' ');
                write(arg0, lexlevel:1);
            end;
            ibgnb,
            iendb:
            begin
                write(arg0, symno:1);
            end;
            
            icprestore:
            begin
                write(arg0, length:1);
            end;

            iset:
            begin
                write(arg0, ' ');
                write(arg0, iopt_tab[set_value(length)]:0);
            end;
            ioption:
            begin
                write(arg0, ioption_type_tab[option]:0);
                if option = o_exception_info then begin
                    write(arg0, ' ');
                end;
                write(arg0, opt_len:1);
            end;

            inoalias,
            ialias:
            begin
                write(arg0, reg_name_tab[basereg1]:0);
                write(arg0, ',');
                write(arg0, reg_name_tab[basereg2]:0);
            end;

            ilivereg,
            igjaldef,
            igjallive,
            igjrlive:
            begin
                put_hex10(arg0, gpmask);
                write(arg0, ',');
                put_hex10(arg0, fpmask);
            end;

            icpload,
            icpadd,
            icpalias:
            begin
                write(arg0, reg_name_tab[reg1]:0);
            end;

            iedata:
            begin
                write(arg0, flag:1);
                write(arg0, ' ');
                put_sym(arg0, symno);
                write(arg0, ' ');
                put_sym(arg0, edata);
            end;

            itext:
            begin
                if in_file^.length <> 0 then begin
                    put_string(arg0, false);
                end;
            end;

            iloopno:
            begin
                write(arg0, loopnum:1);
                write(arg0, ' ');
                write(arg0, lflag:1);
            end;

            iprologue:
            begin
                write(arg0, lexlevel:1);
            end;

            imtag:
            begin
                write(arg0, tagnumber:1);
                write(arg0, ',');
                write(arg0, tagtype:1);
            end;

            idata, isdata, irdata, irestext:
            
            end;
            writeln(arg0);
            
            if (instr = iloc) then begin
                print_source(arg0, filenumber, linenumber);
            end;
        end;
    end;
    end;
end;

procedure put_string({var arg0: text; arg1: boolean});
label
    loop_end;
var
    var_s2: u16;
    var_s1: integer;
    var_s0: cardinal;
    var_s6: cardinal;
begin
    if arg1 then begin
        write(arg0, '"');
    end;

    var_s2 := in_file^.length;
    for var_s6 := 1 to integer(var_s2 - 1) div 16 + 1 do begin {Get align 16}
        get(in_file);
        for var_s0 := 1 to 16 do begin
            var_s1 := lshift(var_s6, 4) - 16 + var_s0;
            if (var_s1 <= var_s2) then begin
                put_alpha(arg0, in_file^.data[var_s0]);
            end else begin
                goto loop_end;
            end;
        end;
    end;

loop_end:
    if arg1 then begin
        write(arg0, '"');
    end;
end;

procedure output_inst_ascii(var arg0: Stringtext; var arg1: Text);
begin
    reset(in_file, arg0.ss);

    while not eof(in_file) do begin 
        if in_file^.instr = iocode then begin
            write_instruction(arg1);
        end else begin
            write_directive(arg1);
        end;
        get(in_file)
    end;
    
end;