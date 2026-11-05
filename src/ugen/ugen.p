#include "common.h"
#include "report.h"
#include "tree.h"
#include "tree_utils.h"
#include "u_tree.h"
#include "ibuffer.h"
#include "emit.h"
#include "aio.h"
#include "cmplrs/allocator.h"
#include "cmplrs/uini.h"
#include "cmplrs/uread.h"
#include "cmplrs/uwri.h"
#include "cmplrs/stinfc.h"

{Macros}
#define CASE_ARG(a) a:
#define ARG_OPT(index, opt) (arg[index] = opt)
#define IS_OPT(opt) streq(arg, opt)

#define SKIP_END_SPACES(len, line)  len := sizeof(line); \
    while ((len <> 0) and (line[len] = ' ')) do begin  \
        len := len - 1; \
    end; \


{Special types for ugen.p }
type
    { Required to match }
    ugen_debug_levels = first(DebugLevels)..last(DebugLevels) of integer;
    ugen_opt_levels = first(OptLevels)..last(OptLevels) of integer;
    ugen_str =  packed array [1..12] of char; {Used for printing out the ucode parse tree phase (translate, build, etc..)}
    opt_str = packed array [1..32] of char; {Used for checking the options}


{ Functions called from C }

function mktemp(var path: Filename): integer; external;
procedure unlink(var path: Filename); external;
function getenv(var arg0: Filename): integer; external;
procedure output_inst_bin(var a0: binasm; a1: cardinal; var a2: binasm; a3: cardinal); external;
procedure cat_files(var a1: Filename; var a2: Filename); external;
procedure open_bin_file(var str: Filename); external;
procedure set_domtag(arg0: boolean); external;

procedure print_tree(var f: Text; arg1: ^tree; arg2: cardinal; arg3: cardinal); external;
procedure labelopt(a0: ^Tree; var a1: Text; debugTree: boolean; arg2: boolean); external;
procedure initialize_tree(); external;
procedure clear_sym_tab(); external;
procedure init_build(); external;
function build_tree(verbose: boolean): pointer; external;
function translate_tree(a: ^Tree): pointer; external;
procedure init_eval(); external;
procedure eval(arg0: ^Tree; arg1: registers); external;
procedure close_bin_file(); external;
procedure output_decls(); external;

var
    addr_dtype: Datatype;
    align8: boolean;
    align16: boolean;
    align32: boolean;
    align64: boolean;
    apc: boolean;
    ascii_out: boolean;
    basicint: boolean;
    cpalias_ok: boolean;
    excpt: boolean;
    first_ent: boolean;
    fp_initialized: s8;
    init_dynmem: boolean;
    max_stack: integer;
    mscoff: boolean;
    no_jal_use_jalr_only: boolean;
    non_local_mtag: integer;
    nooffsetopt: boolean;
    opt_labels: boolean;
    print_warnings: boolean;
    saw_cap_g: boolean;
    sgi_unsigned_conv: boolean;
    tail_call_opt: boolean; { Tail call optimization flag }
    tree_heap: pointer;
    tree_heap_mark: integer;
    ufsa: boolean;
    unitsperaddr: integer;
    use_real_fp_for_all: boolean;


#define CASE_ARG(a) a:
#define ARG_OPT(index, opt) (arg[index] = opt)
#define IS_OPT(opt) streq(arg, opt)

#define SKIP_END_SPACES(len, line)  len := sizeof(line); \
    while ((len <> 0) and (line[len] = ' ')) do begin  \
        len := len - 1; \
    end; \


procedure set_opts(arg0: OptLevels; arg1: DebugLevels); external;

{Program block}

program ugen;

label default; { original name: badoption }
var
    treeDumpFileName: Filename; {Name of the file where the different tree phases are dumped/logged}
    treeDumpFile: Text; {File where the different tree phases are dumped/logged}
var
    ugenTempFileName: Filename;
    ugenTempFileFd: integer;
    pad1: integer;
    inputFileName: Filename;
    outputFileName: Filename;
    asmOutputFilePath: Filename;
    treeUcodeFileName: Filename;
    stFileName: st_string;
    debugTree: boolean;
    verbose: boolean;
    arg: Filename;
    asmOutputFile: Text;
    inputFileNameLen: integer;
    i: integer;
    pad2: cardinal;
    ugenTempFileNameLen: integer;
    nameLen: integer;
    debugLevel: ugen_debug_levels;
    optLevel: ugen_opt_levels;
    reg: char;
    debugLabelOptPhase: boolean;
    useTempFile: boolean; {sp515}
    warnLevel: cardinal; {sp510}
    useXpgEnv: boolean; {sp50F}
    pad3: integer;
    xpgEnvVar: Filename;
    index: cardinal;
    pTree: ^Tree;

    { Inner functions.. }

    { Original name: atoi }
    function str_atoi(var arg0: Filename): integer;
    var
        len: integer;
        value: integer;
    begin
        len := 1;
        value := 0;

        while (arg0[len] <> ' ') do begin
            Assert(arg0[len] in ['0'..'9']);
            value := value * 10 + (ord(arg0[len]) - ord('0'));
            len := len + 1;
        end;
        return value;
    end;

    { Original name: assign_dense_labels }
    procedure assign_dense_labels(arg0: ^Tree);
    var
        iter: ^tree;
    begin
        iter := arg0;
        while (iter <> nil) do begin
            if (((iter^.u.Opc = Ulab) and (iter^.u.Lexlev <> GOOB_TARGET)) or (iter^.u.Opc = Uclab)) then begin
                iter^.u.I1 := gen_label_id();
            end;
            iter := iter^.next;
        end;
    end;

    { Original name: process_reg }
    procedure process_reg(opt: char; regs: integer);
    begin
        case opt of
            CASE_ARG('a')
            begin
                n_parm_regs := regs;
            end;

            CASE_ARG('g')
            begin
                if (regs < 4) then begin
                    report_error(Internal, 138, "ugen.p", "insufficient code generator registers");
                    n_cg_regs := 4;
                end else begin
                    n_cg_regs := regs;
                end;
            end;

            CASE_ARG('r')
            begin
                n_unsaved_regs := regs;
            end;

            CASE_ARG('e')
            begin
                n_saved_regs := regs;
            end;

            CASE_ARG(' ')
            otherwise:
            begin
                report_error(Internal, 16#9A, "ugen.p", "illegal register type");
            end;
        end;
    end;

    { Original name: process_fp_reg }
    procedure process_fp_reg(opt: char; regs: integer);
    begin
        case (opt) of
            CASE_ARG('a')
                begin
                    n_fp_parm_regs := regs;
                end;
            CASE_ARG('g')
                begin
                    if (regs < 2) then begin
                        report_error(Internal, 166, "ugen.p", "insufficient code generator fp registers");
                        n_fp_cg_regs := 2;
                    return;
                end;
                n_fp_cg_regs := regs;
            end;
            CASE_ARG('r')
                begin
                    n_unsaved_fp_regs := regs;
                end;
            CASE_ARG('e')
                begin
                    n_saved_fp_regs := regs;
                end;
            CASE_ARG(' ')
                begin
                    n_fp_parm_regs := 0;
                    n_unsaved_fp_regs := 0;
                    n_saved_fp_regs := 0;

                    if (regs < 2) then begin
                        report_error(Internal, 182, "ugen.p", "insufficient code generator fp registers ");
                        n_fp_cg_regs := 2;
                        return;
                    end;
                    n_fp_cg_regs := regs - 1;
                end;
            otherwise:
                report_error(Internal, 193, "ugen.p", "illegal register type");
        end;
    end;

    { Original name: dump_tree }
    procedure dump_tree(t: ^Tree; phase: ugen_str);
    begin
        if (treeDumpFileName[1] <> chr(0)) then begin
            writeln(treeDumpFile, "Tree dump after ", phase:0);
            writeln(treeDumpFile);
            print_tree(treeDumpFile, t, 16#7FFFFFFF, 16#7FFFFFFF);
            writeln(treeDumpFile);
            flush(treeDumpFile);
        end else begin
            writeln(err, "Tree dump after ", phase:0);
            writeln(err);
            print_tree(err, t, 16#7FFFFFFF, 16#7FFFFFFF);
            writeln(err);
        end;
    end;

    { original name: filenameassign }
    procedure copy_filename(var dest: Filename; src: opt_str);
    var
        len: integer;
    begin
        len := 1;

        while src[len] <> ' ' do begin
            dest[len] := src[len];
            len := len + 1;
        end;

        for len := len to 1024 do begin
            dest[len] := ' ';
        end;
    end;

    { Original name: make_temp_file }
    procedure create_temp_file();
    var
        fd: integer;
    begin
        copy_filename(ugenTempFileName, "/tmp/ugentmpXXXXXX");

        ugenTempFileName[19] := chr(0);
        fd := mktemp(ugenTempFileName);
        ugenTempFileFd := fd;

        if (ugenTempFileFd = 0) then begin
            report_error(Internal, 254, "ugen.p", "No suitable file can be created");
        end;
    end;

    { Original name: remove_temp_file }
    procedure unlink_temp_file();
    begin
        unlink(ugenTempFileName);
    end;


    { Original name: filenameeq }
    function streq(var str1: Filename; str2: opt_str): boolean;
    var pos: integer;
    begin
        pos := 1;
        while (str2[pos] <> ' ') do begin
            if (str1[pos] <> str2[pos]) then begin
                return false;
            end;
            pos := pos + 1;
        end;
        return str1[pos] = ' ';
    end;

begin
    useXpgEnv := false;

    xpgEnvVar := "_XPG";
    xpgEnvVar[5] := chr(0);

    if (getenv(xpgEnvVar) <> 0) then begin
        useXpgEnv := true;
    end;

    if (argc < 2) then begin
        writeln(err, "Usage is: ugen [-o binfile] [-l listfile] [-e dumpfile] [-t symbolfilename] [-d] [-trapuv] [-G smallsize] [-p] file.F");
        return 0;
    end else begin
        inputFileName[1] := chr(0);
        sdata_max := 8;

        {Null terminate the strings?}

        outputFileName[1] := chr(0);
        asmOutputFilePath[1] := chr(0);
        lsb_first := false;
        treeUcodeFileName[1] := chr(0);
        stFileName[1] := chr(0);
        fp_initialized := 0;
        ugenTempFileName[1] := chr(0);
        treeDumpFileName[1] := chr(0);
        ascii_out := false;
        useTempFile := false;
        debugTree := false;
        saw_cap_g := false;
        set_domtag(false);
        excpt := false;
        non_local_mtag := 0;
        verbose := false;
        init_dynmem := false;
        debugLabelOptPhase := false;
        use_real_fp_for_all := false;
        debugLevel := DEBUG_LEVEL_g0;
        optLevel := OPT_LEVEL_O1;
        debug_ugen := false;
        warnLevel := ord(Fix);
        index := 1;
        pic_level := 0;
        cpalias_ok := false;
        n_parm_regs := 4;
        n_fp_parm_regs := 2;
        n_cg_regs := 4;
        n_fp_cg_regs := 4;
        n_saved_regs := 8;
        n_saved_fp_regs := 6;
        n_unsaved_regs := 6;
        n_unsaved_fp_regs := 2;
        apc := false;
        align8 := false;
        align16 := false;
        align32 := false;
        align64 := false;
        ufsa := false;
        ufsm := false;
        tail_call_opt := true;
        sgi_unsigned_conv := true;
        no_jal_use_jalr_only := false;
        first_ent := true;
        print_warnings := true;
        max_stack := -1;
        opcode_arch := ARCH_32;
        basicint := false;
        addr_dtype := Adt;
        unitsperaddr := 4;
        fp32regs := false;



        if (argc >= 2) then begin
            repeat
                argv(index, arg);
                if (arg[1] = '-') then begin
                    case arg[2] of
                        CASE_ARG('j')
                            if (ARG_OPT(3, 'a')) and (ARG_OPT(4, 'l')) and (ARG_OPT(5, 'r')) then begin
                                no_jal_use_jalr_only := true;
                            end else goto default;

                        CASE_ARG('o')
                            if (ARG_OPT(3, ' ')) then begin
                                if (index + 1 = argc) then begin
                                    writeln(err, 'filename required after -o');
                                    halt(1);
                                end;
                                index := index + 1; {Stop immediately}
                                argv(index, outputFileName);
                            end else goto default;

                        CASE_ARG('u')
                            if (ARG_OPT(3, 'f') and ARG_OPT(4, 's')) then begin
                                if (ARG_OPT(5, 'a')) then begin
                                    ufsa := true;
                                end else if (ARG_OPT(5, 'm')) then begin
                                    ufsm := true;
                                end else goto default

                            end else if (ARG_OPT(3, ' ')) then begin
                                if ((index + 1) = argc) then begin
                                    writeln(err, "filename required after -u");
                                    halt(1);
                                end;
                                index := index + 1;
                                argv(index, treeUcodeFileName);
                            end else goto default;

                        CASE_ARG('l')
                            if (ARG_OPT(3, ' ')) then begin
                                if ((index + 1) = argc) then begin
                                    writeln(err, "filename required after -l");
                                    halt(1);
                                end;
                                index := index + 1;
                                argv(index, asmOutputFilePath);
                                ascii_out := true; {Assembly output: TRUE}
                            end else goto default;

                        CASE_ARG('t')
                            if (ARG_OPT(3, 'e') and (ARG_OPT(4, 'm')) and (ARG_OPT(5, 'p'))) then begin
                                if (succ(index) = argc) then begin
                                    writeln(err, "filename required after -temp");
                                    halt(1);
                                end;

                                index := index + 1;
                                argv(index, ugenTempFileName);
                                useTempFile := true;

                            end else if ((ARG_OPT(3, 'r')) and (ARG_OPT(4, 'a')) and (ARG_OPT(5, 'p')) and (ARG_OPT(6, 'u')) and (ARG_OPT(7, 'v'))) then begin
                                init_dynmem := true;
                            end else if (ARG_OPT(3,  ' ')) then begin
                                if ((index + 1) = argc) then begin
                                    writeln(err, "filename required after -t");
                                    halt(1);
                                end;
                                index := index +1;
                                argv(index, stFileName);
                            end else goto default;

                        CASE_ARG('e')
                        begin
                            if (ARG_OPT(3,  ' ')) then begin
                                if ((index + 1) = argc) then begin
                                    writeln(err, "filename required after -e");
                                    halt(1);
                                end;

                                index := index + 1;
                                argv(index, treeDumpFileName);
                                debugTree := true;
                            end else if (ARG_OPT(3,  'x') and (ARG_OPT(4, 'c')) and (ARG_OPT(5, 'p')) and (ARG_OPT(6, 't')) and (ARG_OPT(7, ' '))) then begin
                                excpt := true;
                            end else goto default;
                        end;
                        CASE_ARG('d')
                        begin
                            if (IS_OPT("-dwopcode")) then begin
                                isa := ISA_MIPS3;
                                opcode_arch := ARCH_64;
                            end else if (IS_OPT("-domtag")) then begin
                                set_domtag(true);
                            end else begin
                                debug_ugen := true;
                                debugTree := true;
                            end;
                        end;

                        CASE_ARG('E')
                            if (ARG_OPT(3, 'L')) then begin
                                lsb_first := true;
                            end else if (ARG_OPT(3,  'B')) then begin
                                lsb_first := false;
                            end else goto default;

                        CASE_ARG('g')
                            if (ARG_OPT(3, ' ')) then begin
                                writeln(err, "numeric argument required for -g");
                            end else if ((arg[3] >= '0') and (arg[3] < '5')) then begin
                                debugLevel := DebugLevels(ord(arg[3]) - ord('0');
                            end else goto default;

                        CASE_ARG('O')
                            if (ARG_OPT(3, ' ')) then begin
                                writeln(err, "numeric argument required for -O");
                            end else if ((arg[3] >= '0') and (arg[3] < '5')) then begin
                                optLevel := OptLevels(ord(arg[3]) - ord('0'));
                            end else goto default;

                        CASE_ARG('G')
                            if (ARG_OPT(3, ' ')) then begin
                                if ((index + 1) = argc) then begin
                                    writeln(err, "numeric argument required for -G");
                                    halt(1);
                                end;

                                index := index + 1;
                                argv(index, arg);
                                sdata_max := str_atoi(arg);

                                if ((pic_level >= 2) and (sdata_max <> 0)) then begin
                                    saw_cap_g := true;
                                    writeln(err, "-pic2 implies -G 0. -G option ignored");
                                    sdata_max := 0;
                                end;

                            end else goto default;

                        CASE_ARG('r')
                            if ((ARG_OPT(3, 'e')) and (arg[4] = 'g')) then begin
                                index := index + 1;
                                reg := arg[5];
                                argv(index, arg);
                                process_reg(reg, str_atoi(arg));
                            end else goto default;

                        CASE_ARG('f')
                            if (ARG_OPT(3, 'r') and ARG_OPT(4, 'e') and ARG_OPT(5, 'g')) then begin
                                index := index + 1;
                                reg := arg[6];
                                argv(index, arg);
                                process_fp_reg(reg, str_atoi(arg));
                            end else begin
                                if (streq(arg, "-fp32regs")) then begin
                                    fp32regs := true;
                                end else goto default;
                            end;

                        CASE_ARG('L')
                            if (ARG_OPT(3, ' ')) then begin
                                debugLabelOptPhase := true;
                            end else goto default;

                        CASE_ARG('F')
                            if (ARG_OPT(3, 'P')) then begin
                                use_real_fp_for_all := true;
                            end else goto default;

                        CASE_ARG('v')
                            if (ARG_OPT(3, ' ')) then begin
                                verbose := true;
                            end else goto default;

                        CASE_ARG('n')
                            if (IS_OPT("-nooffsetopt")) then begin
                                nooffsetopt := true;
                            end else begin
                                if (IS_OPT("-nocpalias")) then begin
                                    cpalias_ok := false;
                                end else if (IS_OPT("-notailopt")) then begin
                                    tail_call_opt := false;
                                end else if (IS_OPT("-nounsignedconv")) then begin
                                    sgi_unsigned_conv := false;
                                end else goto default;
                            end;

                        CASE_ARG('m')
                            if (IS_OPT("-mips1")) then begin
                                isa := ISA_MIPS1;
                            end else if (IS_OPT("-mips2")) then begin
                                isa := ISA_MIPS2;
                            end else if (IS_OPT("-mips3")) then begin
                                isa := ISA_MIPS3;
                                opcode_arch := ARCH_64;
                            end else if (IS_OPT("-mscoff")) then begin
                                mscoff := true;
                            end else goto default;

                        CASE_ARG('p')
                        begin
                            if (IS_OPT("-pic0")) then begin
                                pic_level := 0;
                            end else if (IS_OPT("-pic1") or IS_OPT("-pic")) then begin
                                pic_level := 1;
                            end else if (IS_OPT("-pic2")) then begin
                                pic_level := 2;
                            end else goto default;
                            if (pic_level >= 2) then begin
                                sdata_max := 0;
                                if (saw_cap_g) then begin
                                    writeln(err, "-pic2 implies -G 0. -G option ignored");
                                end;
                            end;
                        end;

                        CASE_ARG('a')
                            if (ARG_OPT(3, 'p') and ARG_OPT(4, 'c')) then begin
                                apc := true; {Enable Apollo Pascal extensions}
                            end else begin
                                if (IS_OPT("-align8")) then begin
                                    align8 := true;
                                end else if (IS_OPT("-align16")) then begin
                                    align16 := true;
                                end else if (IS_OPT("-align32")) then begin
                                    align32 := true;
                                end else if (IS_OPT("-align64")) then begin
                                    align64 := true;
                                end else goto default;
                            end;

                        CASE_ARG('w')
                            case arg[3] of
                                CASE_ARG('1')
                                begin
                                    warnLevel := ord(Info);
                                    print_warnings := false;
                                end;

                                CASE_ARG('2')
                                begin
                                    warnLevel := ord(Warn);
                                end;

                                CASE_ARG('3')
                                begin
                                    warnLevel := ord(Error);
                                    print_warnings := false;
                                end;

                                otherwise:
                                    print_warnings := false;
                            end;

                        CASE_ARG('c')
                            if (IS_OPT("-cpalias")) then begin
                                cpalias_ok := true;
                            end else if (IS_OPT("-checkstack")) then begin
                                if ((index + 1) = argc) then begin
                                    writeln(err, "numeric argument required for -checkstack");
                                    halt(1);
                                end;

                                index := index + 1;
                                argv(index, arg);
                                max_stack := str_atoi(arg);

                            end else goto default;

                        CASE_ARG('6')
                            if (ARG_OPT(3, '4') and ARG_OPT(4, 'd') and ARG_OPT(5, 'a') and ARG_OPT(6, 't') and ARG_OPT(7, 'a') and ARG_OPT(8, ' ')) then begin
                                isa := ISA_MIPS3;
                                opcode_arch := ARCH_64;
                                basicint := true;
                                addr_dtype := Wdt;
                                unitsperaddr := 8;
                            end else goto default;

                        CASE_ARG('-')
                            if ((useXpgEnv = true) and ARG_OPT(3, '-')) then begin
                                argv(index, xpgEnvVar);

                                SKIP_END_SPACES(inputFileNameLen, xpgEnvVar);

                                if (inputFileNameLen <> 0) then begin
                                    xpgEnvVar[inputFileNameLen + 1] := chr(0);
                                end else begin
                                    writeln(err, arg:0, " not understood");
                                end;

                                for i := 3 to inputFileNameLen + 1 do begin
                                    inputFileName[i - 2] := xpgEnvVar[i];
                                end;

                            end;

                            otherwise:
                            default:
                                writeln(err, arg:0, " not understood");
                    end;
                end else begin
                    argv(index, inputFileName);

                    SKIP_END_SPACES(inputFileNameLen, inputFileName);
                end;

                index := index + 1;
             until (index >= argc);
        end;

        if (inputFileName[1] = chr(0)) then begin
            writeln(err, "Must specify .F file");
            halt(1);
        end;

        if ((n_parm_regs + n_saved_regs + n_unsaved_regs) >= 19) then begin
            report_error(Internal, 779, "ugen.p", "too many registers");
            halt(1);
        end;

        if ((n_fp_parm_regs + n_saved_fp_regs + n_unsaved_fp_regs) >= 11) then begin
            report_error(Internal, 784, "ugen.p", "too many fp registers");
            halt(1);
        end;

        if (fp32regs and ((isa = ISA_MIPS1) or (isa = ISA_MIPS2))) then begin
            report_error(Internal, 789, "ugen.p", "fp32regs is only legal for mips3 and future architectures");
            halt(1);
        end;

        if (ascii_out) then begin
            SKIP_END_SPACES(nameLen, asmOutputFilePath);
            asmOutputFilePath[nameLen + 1] := chr(0);

            rewrite(asmOutputFile, asmOutputFilePath);

            if (stFileName[1] = chr(0)) then begin
                for index := 1 to inputFileNameLen - 1 do begin
                    stFileName[index] := inputFileName[index];
                end;
                nameLen := inputFileNameLen;
                stFileName[nameLen] := 'T';
            end else begin
                nameLen := sizeof(stFileName) - 1;
                while ((nameLen <> 0) and (stFileName[nameLen] = ' ')) do begin
                    nameLen := nameLen - 1;
                end;
            end;

            stFileName[nameLen + 1] := chr(0);
            if (st_readbinary(stFileName, 'r') < 0) then begin
                writeln(err, "Cannot read symbol table file");
                halt(1);
            end;
        end;

        initialize_tree();
        init_ibuffer();
        uini();
        initur(inputFileName);

        if (outputFileName[1] = chr(0)) then begin
            outputFileName := inputFileName;
            outputFileName[inputFileNameLen] := 'G'; {binasm extension}
            nameLen := inputFileNameLen;
        end else begin
           SKIP_END_SPACES(nameLen, outputFileName);
        end;

        outputFileName[nameLen + 1] := chr(0);

        if (ugenTempFileName[1] = chr(0)) then begin
            create_temp_file();
        end else begin
            SKIP_END_SPACES(ugenTempFileNameLen, ugenTempFileName);
            ugenTempFileName[ugenTempFileNameLen + 1] := chr(0);
        end;

        if (treeDumpFileName[1] <> chr(0)) then begin
            rewrite(treeDumpFile, treeDumpFileName);
        end;

        set_opts(optLevel, debugLevel);

        if (verbose) then begin
            write(err, "ugen:");
        end;

        clear_sym_tab();
        open_bin_file(ugenTempFileName);
        init_build();

        while (true) do begin
            clear_ibuffer();
            tree_heap_mark := alloc_mark(tree_heap);
            pTree := build_tree(verbose);

            if (pTree = nil) then begin
                break;
            end;

            if (debugTree) then begin
                dump_tree(pTree, "Build");
            end;

            pTree := translate_tree(pTree);

            if (debugTree) then begin
                dump_tree(pTree, "Translate");
            end;

            if (opt_labels) then begin
                if (treeDumpFileName[1] <> chr(0)) then begin
                    labelopt(pTree, treeDumpFile, debugTree, debugLabelOptPhase);
                end else begin
                    labelopt(pTree, err, debugTree, debugLabelOptPhase);
                end;
            end;

            assign_dense_labels(pTree);

            if (treeUcodeFileName[1] <> chr(0)) then begin
                { Save the ucode represented by the tree }
                inituwrite(treeUcodeFileName);
                u_tree(pTree);
                {@bug: The output file will be truncated, since the call of uputclose is missing }
            end;

            init_eval();
            eval(pTree, xnoreg);
            output_inst_bin(ibuffer^[1], pred(i_ptr), ibuffer^[ibuffer_size], ibuffer_size - d_ptr);
            alloc_release(tree_heap, tree_heap_mark);
        end;

        close_bin_file();
        clear_ibuffer();
        emit_vers();
        emit_pic(pic_level);
        output_decls();
        open_bin_file(outputFileName);
        output_inst_bin(ibuffer^[1], pred(i_ptr), ibuffer^[ibuffer_size], ibuffer_size - d_ptr);
        close_bin_file();
        cat_files(outputFileName, ugenTempFileName);

        if not (useTempFile) then begin
            unlink_temp_file();
        end;

        if (ascii_out) then begin
            outputFileName[nameLen + 1] := ' ';
            output_inst_ascii(outputFileName, asmOutputFile);
        end;

        if (verbose) then begin
            writeln(err);
        end;

        if (has_errors(warnLevel)) then begin
            halt(1);
        end;
    end;

    return 0;
end.
