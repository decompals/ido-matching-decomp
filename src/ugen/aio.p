#include "common.h"
#include "report.h"
#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"
#include "cmplrs/binasm.h"
#include "cmplrs/uoptions.h"
#include "cmplrs/stinfc.h"

type
    hex_str = packed array [1..10] of char; /* :=  "0123456789ABCDEF" */
    hex_char = packed array [1..2] of char;
    BinasmFile = File of binasm;
    
var
    source_language: integer;
    in_file: BinasmFile;    
    current_linen: integer;
    source_file: Text;
    source_file_name: Filename;
    val64: Valu;

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

#define ST_COPY(ustr, st) len := 1; while (st^[len] <> chr(0)) do begin ustr[len] := st^[len]; len := len + 1 end;

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

procedure hex_2(digit: char; var str: hex_char);
begin
    str[1] := hex_tab[(rshift(digit, 4) & 255)];
    str[2] := hex_tab[ord(digit) -((rshift(digit, 4) & 255) * 16)];
end; 

procedure put_alpha(var arg0: text; arg1: char);
var
    sp26: hex_char;
begin
    if not(arg1 in [' '..'~']) or (arg1 = '"') or (arg1 = '\') then begin
        hex_2(arg1, sp26);
        write(arg0, "\\X", sp26);
    end else begin
        write(arg0, arg1);
    end;
end;

procedure put_string(var arg0: text; arg1: boolean);
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

#line 786
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

#line 1025
procedure write_directive(var arg0: Text);
    var
        sp44: cardinal;
begin
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
                val64.dwval_h := expression;
                get(in_file);
                val64.dwval_l := in_file^.expression;
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
                write(arg0, ', ');
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