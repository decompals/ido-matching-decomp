#include "common.h"
#include "report.h"
#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"
#include "cmplrs/uoptions.h"
#include "cmplrs/stinfc.h"

#define ST_STRING_COPY(ustr, st) len := 1; while (st^[len] <> chr(0)) do begin ustr[len] := st^[len]; len := len + 1 end;
#define TAB chr(9)

type
    hex10 = packed array [1..10] of char; /* :=  "0123456789ABCDEF" */
    hex2 = packed array [1..2] of char;
    
var
    { .bss }
    current_linen: integer;
    in_file: File of binasm;
    source_file: Text;
    val64: Valu;
    source_file_name: Filename;    

    { .data }
    reg_name_tab: array [registers] of array[1..5] of char := [
        "$0",    "$1",    "$2",    "$3",    "$4",    "$5",    "$6",    "$7",
        "$8",    "$9",    "$10",   "$11",   "$12",   "$13",   "$14",   "$15",
        "$16",   "$17",   "$18",   "$19",   "$20",   "$21",   "$22",   "$23",
        "$24",   "$25",   "$26",   "$27",   "$gp",   "$sp",   "$30",   "$31",
        "$f0",   "$f1",   "$f2",   "$f3",   "$f4",   "$f5",   "$f6",   "$f7",
        "$f8",   "$f9",   "$f10",  "$f11",  "$f12",  "$f13",  "$f14",  "$f15",
        "$f16",  "$f17",  "$f18",  "$f19",  "$f20",  "$f21",  "$f22",  "$f23",
        "$f24",  "$f25",  "$f26",  "$f27",  "$f28",  "$f29",  "$f30",  "$f31",
        "$fcc0", "$fcc1", "$fcc2", "$fcc3", "$fcc4", "$fcc5", "$fcc6", "$fcc7",
        "$0"
    ];

    itype_tab: array [itype] of array [1..12] of char := [
        "label",     "sym",         ".globl",    ".cpload",
        ".align",    ".ascii",      ".asciiz",   ".byte",
        ".comm",     ".lcomm",      ".data",     ".double",
        ".file",     ".float",      ".half",     ".cprestore",
        ".gpword",   ".cpadd",      ".weakext",  ".loopno",
        ".space",    ".text",       ".word",     "code",
        ".end",      ".sdata",      ".rdata",    ".ent",
        ".loc",      ".bgnb",       ".endb",     ".asm0",
        ".set",      ".cpalias",    ".rep",      ".endrep",
        ".lab",      ".vreg",       ".mask",     ".fmask",
        ".err",      ".globabs",    ".verstamp", ".frame",
        ".extended", ".extern",     ".aent",     ".option",
        ".noalias",  ".alias",      ".mtag",     ".malias",
        ".comm",     ".livereg",    ".gjaldef",  ".gjallive",
        ".gjrlive",  ".shift_addr", ".restext",  ".dword",
        ".prologue", ".edata",      ".comm"
    ];

    iopt_tab: array [set_value] of array [1..12] of char := [
        "undefined",    "reorder",   "noreorder",   "macro",      
        "nomacro",      "at",        "noat",        "move",
        "nomove",       "bopt",      "nobopt",      "volatile",
        "novolatile",   "transform", "notransform", "reposition",
        "noreposition",
    ];

    ioption_type_tab: array [opt_compat_align] of array [1..15] of char := [
        "undefined", "O", "pic", "exception_info"
    ];

    opcode_tab: array [asmcodes] of array [1..10] of char := [
        "abs",        "add",        "addu",       "and",        "b",          "bc0f",       "bc0t",      "bc1f",
        "bc1t",       "bc2f",       "bc2t",       "bad",        "bad",        "beq",        "bge",       "bgeu",
        "bgez",       "bgt",        "bgtu",       "bgtz",       "ble",        "bleu",       "blez",      "blt",
        "bltu",       "bltz",       "bne",        "break",      "c0",         "c1",         "c2",        "bad",
        "div",        "divu",       "j",          "jal",        "la",         "lb",         "lbu",       "lh",
        "lhu",        "li",         "lw",         "jr",         "lwc1",       "lwc2",       "bad",       "mfhi",
        "mflo",       "move",       "jalr",       "swc1",       "swc2",       "bad",        "mthi",      "mtlo",
        "mul",        "mulo",       "mulou",      "mult",       "multu",      "neg",        "nop",       "nor",
        "or",         "rem",        "remu",       "rfe",        "rol",        "ror",        "sb",        "seq",
        "sge",        "sgeu",       "sgt",        "sgtu",       "sh",         "sle",        "sleu",      "sll",
        "slt",        "sltu",       "sne",        "sra",        "srl",        "sub",        "subu",      "sw",
        "syscall",    "xor",        "not",        "lwl",        "lwr",        "swl",        "swr",       "vcall",
        "mfc0",       "mfc1",       "mfc2",       "bad",        "mtc0",       "mtc1",       "mtc2",      "bad",
        "tlbr",       "tlbwi",      "tlbwr",      "tlbp",       "ld",         "sd",         "z110",      "ldc1",
        "ldc2",       "bad",        "tlbp1",      "sdc1",       "sds2",       "bad",        "l.s",       "l.d",
        "l.e",        "s.s",        "s.d",        "s.e",        "add.s",      "add.d",      "add.e",     "sub.s",
        "sub.d",      "sub.e",      "mul.s",      "mul.d",      "mul.e",      "div.s",      "div.d",     "div.e",
        "sqrt.s",     "sqrt.d",     "sqrt.e",     "mov.s",      "mov.d",      "mov.e",      "abs.s",     "abs.d",
        "abs.e",      "cvt.s.d",    "cvt.s.e",    "cvt.s.w",    "cvt.d.s",    "cvt.d.e",    "cvt.d.w",   "cvt.e.s",
        "cvt.e.d",    "cvt.e.w",    "cvt.w.s",    "cvt.w.d",    "cvt.w.e",    "c.f.s",      "c.f.d",     "c.f.e",
        "c.un.s",     "c.un.d",     "c.un.e",     "c.eq.s",     "c.eq.d",     "c.eq.e",     "c.ueq.s",   "c.ueq.d",
        "c.ueq.e",    "c.olt.s",    "c.olt.d",    "c.olt.e",    "c.ult.s",    "c.ult.d",    "c.ult.e",   "c.ole.s",
        "e.ole.d",    "c.ole.e",    "c.ule.s",    "c.ule.d",    "c.ule.e",    "c.sf.s",     "c.sf.d",    "c.sf.e",
        "c.ngle.s",   "c.ngle.d",   "c.ngle.e",   "c.seq.s",    "c.seq.d",    "c.seq.e",    "c.ngl.s",   "c.ngl.d",
        "c.ngl.e",    "c.lt.s",     "c.lt.d",     "c.lt.e",     "c.nge.s",    "c.nge.d",    "c.nge.e",   "c.le.s",
        "c.le.d",     "c.le.e",     "c.ngt.s",    "c.ngt.d",    "c.ngt.d",    "lui",        "ulw",       "ulh",
        "ulhu",       "usw",        "ush",        "addi",       "addiu",      "slti",       "sltiu",     "andi",
        "ori",        "xori",       "z218",       "negu",       "beqz",       "bnez",       "neg.s",     "neg.d",
        "neg.e",      "cfc1",       "ctc1",       "bal",        "bgezal",     "bltzal",     "mtc1.d",    "mfc1.d",
        "trunc.w.s",  "trunc.w.d",  "trunc.w.e",  "round.w.s",  "round.w.d",  "round.w.e",  "addou",     "subou",
        "truncu.w.s", "truncu.w.d", "truncu.w.e", "roundu.w.s", "roundu.w.d", "roundu.w.e", "cfc0",      "cfc2",
        "bad",        "ctc0",       "ctc2",       "bad",        "li.s",       "li.d",       "li.e",      "tlt",
        "tltu",       "tge",        "tgeu",       "teq",        "tne",        "ll",         "sc",        "ceil.w.s",
        "ceil.w.d",   "ceil.w.e",   "ceilu.w.s",  "ceilu.w.d",  "ceilu.w.e",  "floor.w.s",  "floor.w.d", "floor.w.e",
        "flooru.w.s", "flooru.w.d", "flooru.w.e", "beql",       "beqzl",      "bnel",       "bnezl",     "blel",
        "bleul",      "blezl",      "zbgtl",      "bgtul",      "bgtzl",      "bltl",       "bltul",     "bltzl",
        "bltzall",    "bgel",       "bgeul",      "bgezl",      "bgezall",    "bc0fl",      "bc0tl",     "bc1fl",
        "bc1tl",      "bc2fl",      "bc2tl",      "bad",        "bad",        "ldl",        "ldr",       "lld",
        "lwu",        "sdl",        "sdr",        "scd",        "daddi",      "daddiu",     "dadd",      "daddu",
        "dsub",       "dsubu",      "dsll",       "dsrl",       "dsra",       "dsllv",      "dsrlv",     "dsrav",
        "dmult",      "dmultu",     "ddiv",       "ddivu",      "lsc1",       "ssc1",       "dmtc1",     "dmfc1",
        "dmtc0",      "dmfc0",      "dmtc2",      "dmfc2",      "dli",        "dla",        "eret",      "trunc.l.s",
        "zround.l.s", "ceil.l.s",   "floor.l.s",  "trunc.l.d",  "zround.l.d", "ceil.l.d",   "floor.l.d", "trunc.l.e",
        "round.l.e",  "ceil.l.e",   "floor.l.e",  "cvt.l.s",    "cvt.l.d",    "cvt.l.e",    "cvt.l.w",   "cvt.s.l",
        "cvt.d.l",    "cvt.e.l",    "cvt.w.l",    "cache",      "cia",        "uld",        "usd",       "dabs",
        "dneg",       "dnegu",      "dmul",       "dmulo",      "dmulou",     "drem",       "dremu",     "drol",
        "dror",       "daddou",     "dsubou",     "bad",        "bad",        "bad",        "bad",        "bad",
        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",
        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",
        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",
        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",
        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",
        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",        "bad",
        "bad",        "bad",        "bad",        "bad",        "bad",        "bad"
    ];

    hex_tab : array [0..15] of char := [
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    ];

    current_filen: integer := -2;
    second_dli: boolean := False;

procedure put_integer_ws(var f: Text; val: integer);
begin
    if val = 0 then return;
        if val > 0 then begin
            write(f, '+');
        end;
    write(f, val:1);
end;

{ Prints the symbol’s name, or just its number with $ or $$ prefix.
  The symbol is looked up by its idn (dense number) in the symbol table. }
procedure put_sym(var f: Text; idn: integer);
var
    sym_name: Stringtext;
    st_str: pst_string;
    len: integer;

begin
    if (idn <> 0) then begin
        if (idn < 0) then begin
            { Negative number indicates a local label; prints as a simple number with a $ prefix, e.g., $23 }
            write(f, '$', abs(idn):1);
        end else if (st_fglobal_idn(idn) <> 1) and (source_language <> C_SOURCE) then begin
            { Static symbol not from C source; prints number with $$ prefix, e.g., $$23 }
            write(f, "$$", idn:1);
        end else begin
            sym_name.ss := "";
            st_str := st_str_idn(idn);

            if (st_str = pointer(-1)) then begin
                { Symbol not found in the symbol table; prints its number with $$ prefix anyway, e.g., $$23 }
                write(f, "$$", idn:1);
            end else begin
                ST_STRING_COPY(sym_name.ss, st_str);
            end;

            { Prints the symbol’s string representation }
            write(f, sym_name.ss:0);
        end;
        
    end;
end;

{ Converts a number to a hexadecimal string in the format 0x0123ABCD }
procedure hex8(number: integer; var str: hex10);
var
    i: integer;
    digit: 0..15;
begin
     str[1] := '0';
     str[2] := 'x';

    for i := 3 to 10 do begin
        digit := rshift(number, 32 - (i - 2) * 4) & 16#F;
        str[i] := hex_tab[digit];
    end;
    
     str[1] := '0';
     str[2] := 'x';
end;    

{ Prints a number in hexadecimal form, e.g., 0x0123ABCD }
procedure put_hex10(var f: Text; number: integer);
var
    hex_str: hex10;
begin
    hex8(number, hex_str);
    write(f, hex_str);
end;

{ Converts a character to its hexadecimal representation, e.g., 'A' → "41" }
procedure hex_2(digit: char; var str: hex2);
begin
    str[1] := hex_tab[(rshift(digit, 4) & 255)];
    str[2] := hex_tab[ord(digit) -((rshift(digit, 4) & 255) * 16)];
end; 

{ Prints a character as-is, or in hexadecimal code if non-printable, e.g., '\x1A'}
procedure put_alpha(var f: Text; c: char);
var
    hex_str: hex2;
begin
    if not(c in [' '..'~']) or (c = '"') or (c = '\') then begin
        hex_2(c, hex_str);
        write(f, "\\X", hex_str);
    end else begin
        write(f, c);
    end;
end;

{ Prints a string read from the input file }
procedure put_string(var f: Text; quoted: boolean);
label
    loop_end;
var
    length: u16;
    j: cardinal;
    i: cardinal;
begin
    if quoted then begin
        write(f, '"');
    end;

    length := in_file^.length;
    for i := 1 to integer(length - 1) div bin_rec_len + 1 do begin
        get(in_file);
        for j := 1 to bin_rec_len do begin
            if (i - 1) * bin_rec_len + j <= length then begin
                put_alpha(f, in_file^.data[j]);
            end else begin
                goto loop_end;
            end;
        end;
    end;

loop_end:
    if quoted then begin
        write(f, '"');
    end;
end;

#line 783
{ Prints an instruction. May need to read multiple binasm records from the input file. }
procedure write_instruction(var f: Text);
label done;
var
    str_length: integer;
    j: cardinal;
    i: cardinal;
begin
    { Always starts with a tab character }
    write(f, TAB);

    { Writes the opcode string, except for cia and dli, which are handled separately }
    if (in_file^.op <> zcia) and (in_file^.op <> zdli) then begin
        write(f, opcode_tab[in_file^.op]:0, TAB);
    end;

    with in_file^ do begin
        case form of 
            { Prints an instruction in the format:
                opcode  $dest, symbol+offset($src), mem_tag
              or
                opcode  $dest, offset($src), mem_tag
              mem_tag is optional }
            frob:
            begin
                write(f, reg_name_tab[reg1]:0);
                write(f, ", ");

                if symno <> 0 then begin
                    put_sym(f, symno);
                    put_integer_ws(f, immediate);
                end else begin
                    write(f, immediate:1);
                end;
            
                write(f, '(');
                write(f, reg_name_tab[reg2]:0);
                write(f, ')');
                if (mem_tag <> 0) then begin
                    write(f, ", ");
                    write(f, mem_tag:1);
                end;
            end;

            { Prints an instruction in the format:
                opcode  $dest, symbol+offset, mem_tag
              mem_tag is optional }
            fra:
            begin
                write(f, reg_name_tab[reg1]:0);
                write(f, ", ");
                put_sym(f, symno);
                put_integer_ws(f, immediate);
                if (mem_tag <> 0) then begin
                    write(f, ", ");
                    write(f, mem_tag:1);
                end;
            end;

            { Prints an instruction in the format:
                opcode  $dest, imm
              Special cases:
               * For nop, only the opcode is printed.
              Some instructions may have variable length, requiring reading the appropriate number of bytes from the input file.
               * For fli_s and fli_d:
                    opcode $dest, 1.2345e7
               * For cia:
                    cia any inline assembly code
               * For dli, two entries are read to obtain a 64-bit value:
                    dli $dest, 1234567887654321
               }
            fri:
            begin
                if op <> znop then begin
                    if (op = fli_s) or (op = fli_d) then begin
                        write(f, reg_name_tab[reg1]:0);
                        write(f,  ", ");
                        str_length := in_file^.immediate;
                        for i := 1 to integer(str_length - 1) div bin_rec_len + 1 do begin
                            get(in_file);
                            for j := 1 to bin_rec_len do begin
                                if (i - 1) * bin_rec_len + j <= str_length then begin
                                    put_alpha(f, in_file^.data[j]);
                                end else begin
                                    goto done;
                                end;
                            end;
                        end;
                    end else if (op = zcia) then begin
                        str_length := in_file^.immediate;
                        for i := 1 to integer(str_length - 1) div bin_rec_len + 1 do begin
                            get(in_file);
                            for j := 1 to bin_rec_len do begin
                                if (i - 1) * bin_rec_len + j <= str_length then begin
                                    write(f, in_file^.data[j]);
                                end else begin
                                    goto done;
                                end;
                            end;
                        end;
                    end else if (op = zdli) then begin
                        if second_dli then begin
                            write(f, opcode_tab[in_file^.op]:0, TAB);
                            write(f, reg_name_tab[reg1]:0);
                            write(f, ", ");
                            val64.dwval_l := immediate;
                            write(f, val64.dwval:1);
                            second_dli := false;
                        end else begin
                            val64.dwval_h := immediate; 
                            second_dli := true;
                        end;
                    end else begin
                        write(f, reg_name_tab[reg1]:0);
                        write(f, ", ");
                        write(f, immediate:1);
                    end;
                end;
            end;

            { Prints an instruction in the format:
                opcode  $dest, $src1, $src2
            }
            frrr:
            begin
                if (reg1 <> xnoreg) then begin
                    write(f, reg_name_tab[reg1]:0);
                    write(f, ", ");
                end;
                write(f, reg_name_tab[reg2]:0);
                write(f, ", ");
                write(f, reg_name_tab[reg3]:0); 
            end;

            { Prints an instruction in the format:
                opcode  $dest, $src, imm
            }
            frri:
            begin
                write(f, reg_name_tab[reg1]:0);
                write(f, ", ");
                write(f, reg_name_tab[reg2]:0);
                write(f, ", ");
                write(f, immediate:1);   
            end;

            { Prints an instruction in the format:
                opcode  $dest, $src
            }
            frr:
            begin
                write(f, reg_name_tab[reg1]:0);
                write(f, ", ");
                write(f, reg_name_tab[reg2]:0);   
            end;

            { Prints an instruction in the format:
                opcode  symbol+offset
            }
            fa:
            begin
                put_sym(f, symno);
                put_integer_ws(f, immediate);
            end;

            { Prints an instruction in the format:
                opcode  $dest
            }
            fr:
            begin
                write(f, reg_name_tab[reg1]:0);
            end;
            
            { Prints an instruction in the format:
                opcode  imm
            }
            fi:
            begin
                write(f, immediate:1);
            end;
            
            { Prints an instruction in the format:
                opcode  $src1, $src2, label
            }
            frrl:
            begin
                write(f, reg_name_tab[reg1]:0);
                write(f, ", ");
                write(f, reg_name_tab[reg2]:0);
                write(f, ", ");
                put_sym(f, symno);
            end;
            
            { Prints an instruction in the format:
                opcode  $src, label
            }
            frl:
            begin
                write(f, reg_name_tab[reg1]:0);
                write(f, ", ");
                put_sym(f, symno);
            end;

            { Prints an instruction in the format:
                opcode  $src, label
            }
            fl:
            begin
                put_sym(f, symno);
                
            end;

            forrr:
            begin
                report_error(Internal, 939, "aio.p", "orrr type instruction");
            end;

            { Prints an instruction in the format:
                opcode  $src, imm, label
            }
            fril:
            begin
                write(f, reg_name_tab[reg1]:0);
                write(f, ", ");
                write(f, immediate:1);
                write(f, ", ");   
                put_sym(f, symno);
            end;
        end;
    end;

done:
    writeln(f);
end;

{ Prints one or more lines of source code read from the file corresponding to `fileno` }
procedure print_source(var f: Text; fileno: integer; lineno: integer);
var
    file_name: pst_string;
    len: integer;
begin
    if fileno <> current_filen then begin
        current_filen := fileno;

        { @INVESTIGATE: meaning of these file numbers is unclear }
        if fileno = 0 then begin
            fileno := 2;
        end;

        { file number is an `idn` into the string table }
        file_name := st_str_idn(fileno);

        for len := 1 to FileNameLen do begin
            source_file_name[len] := ' ';
        end;
        ST_STRING_COPY(source_file_name, file_name);
        if (source_file_name[1] = ' ') then begin
            report_error(Internal, 977, "aio.p", "file name is null");
            return;
        end;

        { force line reset to trigger file reload logic }
        current_linen := last(integer);
    end;

    { if line number goes backwards, assume file restart }
    if lineno < current_linen - 1 then begin
        reset(source_file, source_file_name);
        if eof(source_file) then begin
            return;
        end;
        current_linen := 1;
    end;

    { skip lines, keeping at most 5 lines of look-back }
    if lineno - current_linen > 5 then begin
        repeat begin
            if eof(source_file) then begin
                return;
            end;
        
            while not eoln(source_file) do begin
                get(source_file);
            end;

            get(source_file);
            current_linen := current_linen + 1;
        end until (current_linen >= lineno);
    end;

    { print lines as comments }
    while current_linen <= lineno do begin
        write(f, " #", current_linen:4, TAB);

        while not eoln(source_file) do begin
            write(f, source_file^);
            get(source_file);
        end;

        writeln(f);
        get(source_file);
        current_linen := current_linen + 1;
    end;
end;

#line 1022
{ Prints an assembler directive with its parameters. Skips `isym`. For `iloc`, also prints corresponding source lines. }
procedure write_directive(var f: Text);
var
    f_rep: cardinal;
begin
    with in_file^ do begin
        if instr <> isym then begin
            if instr = ilabel then begin
                { print label as "symbol:" }
                put_sym(f, symno);
                write(f, ':');
                writeln(f);
            end else begin
                write(f, TAB);
                write(f, itype_tab[instr]:0, TAB);

                case instr of
                    ialign,
                    ispace,
                    ishift_addr:
                    begin
                        write(f, length:1);
                    end;

                    idouble,
                    ifloat:
                    begin
                        f_rep := rep;
                        put_string(f, false);
                        write(f, ':');
                        write(f, f_rep:1);
                    end;

                    iascii,
                    iasciiz:
                    begin
                        put_string(f, true);
                    end;

                    ifile:
                    begin
                        write(f, symno:1);
                        write(f, ' ');
                        put_string(f, true);
                    end;

                    { data directive: either raw expression or symbol+offset }
                    ibyte,
                    ihalf,
                    igpword,
                    iword:
                    begin
                        if symno = 0 then begin
                            write(f, expression:1);
                            write(f, ' ');
                            write(f, ':');
                            write(f, ' ');
                            write(f, replicate:1);
                        end else begin
                            put_sym(f, symno);
                            put_integer_ws(f, expression);
                        end;
                    end;

                    idword:
                    begin
                        val64.dwval_h := expression;
                        get(in_file);
                        val64.dwval_l := in_file^.expression;
                        write(f, val64.dwval:1);
                        write(f, ' ');
                        write(f, ':');
                        write(f, ' ');
                        write(f, rep:1);
                    end;
                    
                    { @INVESTIGATE: if `rep` is non-zero, an additional 'S' flag is printed (purpose unclear) }
                    icomm,
                    ilcomm,
                    iextern:
                    begin
                        put_sym(f, symno);
                        write(f, ' ');
                        write(f, length:1);
                        if rep <> 0 then begin
                            write(f, ' ');
                            write(f, 'S');
                        end;
                    end;

                    iweakext:
                    begin
                        put_sym(f, symno);
                        if lexlevel <> 0 then begin
                            write(f, ',');
                            put_sym(f, lexlevel);
                        end;
                    end;

                    iglobal,
                    iend,
                    ilab:
                    begin
                        put_sym(f, symno);
                    end;

                    iframe:
                    begin
                        write(f, reg_name_tab[framereg]:0);
                        write(f, ', ');
                        write(f, frameoffset:1);
                        write(f, ', ');
                        write(f, reg_name_tab[pcreg]:0);
                    end;

                    ivreg:
                    begin
                        write(f, reg_name_tab[reg1]:0);
                        write(f, ', ');
                        write(f, immediate:1);
                        write(f, ', ');
                        write(f, symno:1);
                    end;

                    iverstamp:
                    begin
                        write(f, majornumber:1);
                        write(f, ' ');
                        write(f, minornumber:1);
                    end;

                    iloc:
                    begin
                        write(f, filenumber:1);
                        write(f, ' ');
                        write(f, linenumber:1);
                    end;

                    imask,
                    ifmask:
                    begin
                        put_hex10(f, regmask);
                        write(f, ', ');
                        write(f, regoffset:1);
                    end;

                    ient,
                    iaent:
                    begin
                        put_sym(f, symno);
                        write(f, ' ');
                        write(f, lexlevel:1);
                    end;
                    ibgnb,
                    iendb:
                    begin
                        write(f, symno:1);
                    end;
                    
                    icprestore:
                    begin
                        write(f, length:1);
                    end;

                    iset:
                    begin
                        write(f, ' ');
                        write(f, iopt_tab[set_value(length)]:0);
                    end;

                    ioption:
                    begin
                        write(f, ioption_type_tab[option]:0);
                        if option = o_exception_info then begin
                            write(f, ' ');
                        end;
                        write(f, opt_len:1);
                    end;

                    inoalias,
                    ialias:
                    begin
                        write(f, reg_name_tab[basereg1]:0);
                        write(f, ',');
                        write(f, reg_name_tab[basereg2]:0);
                    end;

                    ilivereg,
                    igjaldef,
                    igjallive,
                    igjrlive:
                    begin
                        put_hex10(f, gpmask);
                        write(f, ',');
                        put_hex10(f, fpmask);
                    end;

                    icpload,
                    icpadd,
                    icpalias:
                    begin
                        write(f, reg_name_tab[reg1]:0);
                    end;

                    iedata:
                    begin
                        write(f, flag:1);
                        write(f, ' ');
                        put_sym(f, symno);
                        write(f, ' ');
                        put_sym(f, edata);
                    end;

                    { optional segment name for .text directive }
                    itext:
                    begin
                        if in_file^.length <> 0 then begin
                            put_string(f, false);
                        end;
                    end;

                    iloopno:
                    begin
                        write(f, loopnum:1);
                        write(f, ' ');
                        write(f, lflag:1);
                    end;

                    iprologue:
                    begin
                        write(f, lexlevel:1);
                    end;

                    imtag:
                    begin
                        write(f, tagnumber:1);
                        write(f, ',');
                        write(f, tagtype:1);
                    end;

                    idata, isdata, irdata, irestext:
                end;
                writeln(f);
                
                if (instr = iloc) then begin
                    print_source(f, filenumber, linenumber);
                end;
            end;
        end;
    end;
end;

{ Reads a binasm file and writes the corresponding textual assembly output }
procedure output_inst_ascii(var binasm_file_name: Filename; var outf: Text);
begin
    reset(in_file, binasm_file_name);

    while not eof(in_file) do begin 
        if in_file^.instr = iocode then begin
            write_instruction(outf);
        end else begin
            write_directive(outf);
        end;
        get(in_file)
    end;
end;