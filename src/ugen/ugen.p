#include "report.h"
#include "tree.h"
#include "tree_utils.h"
#include "u_tree.h"
#include "ibuffer.h"
#include "emit.h"
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
    debug_levels = 0..4 of integer;
    opt_levels = 0..3 of integer;
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
procedure labelopt(a0: ^Tree; a1: ^Text; debug: boolean; arg2: boolean); external;
procedure initialize_tree(); external;
procedure clear_sym_tab(); external;
procedure init_build(); external;
function build_tree(verbose: boolean): pointer; external; 
function translate_tree(a: ^Tree): pointer; external;
procedure init_eval(); external;
procedure eval(arg0: ^Tree; arg1: u8); external;
procedure close_bin_file(); external;
procedure output_decls(); external;
procedure output_inst_ascii(var f: Filename; var pFile: Text); external;

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
    debug_ugen: boolean;
    excpt: boolean;
    first_ent: boolean;
    fp32regs: boolean;
    fp_initialized: s8;
    init_dynmem: boolean;
    isa: mips_isa;
    lsb_first: boolean;
    max_stack: integer;
    mscoff: boolean;
    n_cg_regs: integer;
    n_fp_cg_regs: integer;
    n_fp_parm_regs: integer;
    n_parm_regs: integer;
    n_saved_fp_regs: integer;
    n_saved_regs: integer;
    n_unsaved_fp_regs: integer;
    n_unsaved_regs: integer;
    no_jal_use_jalr_only: boolean;
    non_local_mtag: integer;
    nooffsetopt: boolean;
    opcode_arch: boolean;
    opt_labels: u8;
    pic_level: integer;
    print_warnings: boolean;
    saw_cap_g: boolean;
    sdata_max: integer;
    sgi_unsigned_conv: boolean;
    tail_call_opt: boolean;
    tree_heap: pointer;
    tree_heap_mark: integer;
    ufsa: boolean;
    ufsm: boolean;
    unitsperaddr: integer;
    use_real_fp_for_all: boolean;


#define CASE_ARG(a) a:
#define ARG_OPT(index, opt) (arg[index] = opt)
#define IS_OPT(opt) streq(arg, opt)

#define SKIP_END_SPACES(len, line)  len := sizeof(line); \
    while ((len <> 0) and (line[len] = ' ')) do begin  \
        len := len - 1; \
    end; \


procedure set_opts(arg0: opt_levels; arg1: debug_levels); external;

{Program block}

program ugen;

label default;
var    
    sp1DD0: Filename; {sp1DD0}
    temp_file: Text; {sp1DC8}
var
    temp_fname: Filename; {sp19C8}
    temp_fd: integer; {sp19C4}
    pad1: integer;
    sp15C0: Filename; {sp15C0}
    sp11C0: Filename; {sp11C0}
    spDC0: Filename; {spD40}
    sp9C0: Filename; {sp9C0}
    sp940: st_string; {sp940}
    debug: boolean; {sp93F}
    verbose: boolean; {sp93E}
    arg: Filename; {sp53E}
    sp534: Text; {sp534}
    var_s1: integer; {sp530}
    var_a0: integer;
    var_s2: cardinal;
    var_v0_4: integer;
    var_v0_3: integer;
    sp51C: debug_levels; {sp51C}
    sp518: opt_levels; {sp518}
    var_s0: char;
    sp516: boolean; {sp516}
    temp_opt: boolean; {sp515}
    warn_level: cardinal; {sp510}
    xpg_env: boolean; {sp50F}
    pad6: integer;
    sp108: Filename; {sp108}
    index: cardinal;
    temp_v0_3: ^Tree;

    { Inner functions.. }

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

    procedure func_0044B2EC(arg0: ^Tree);
    var
        var_s0: ^tree;
    begin
        var_s0 := arg0;
        while (var_s0 <> nil) do begin
            if (((var_s0^.u.Opc = Ulab) and (var_s0^.u.Lexlev <> 1)) or (var_s0^.u.Opc = Uclab)) then begin
                var_s0^.u.I1 := gen_label_id();
            end;
            var_s0 := var_s0^.next;
        end;
    end;

    procedure func_0044B384(opt: char; arg1: integer);
    begin
        case opt of                                 /* irregular */
            CASE_ARG('a')
            begin
                n_parm_regs := arg1;
            end;

            CASE_ARG('g')
            begin
                if (arg1 < 4) then begin
                    report_error(Internal, 16#8A, "ugen.p", "insufficient code generator registers");
                    n_cg_regs := 4;
                end else begin
                    n_cg_regs := arg1; 
                end;
            end;

            CASE_ARG('r')
            begin
                n_unsaved_regs := arg1;
            end;

            CASE_ARG('e')
            begin
                n_saved_regs := arg1;
            end;

            CASE_ARG(' ')
            otherwise:
            begin
                report_error(Internal, 16#9A, "ugen.p", "illegal register type");
            end;
        end;
    end;

    
    procedure func_0044B640(opt: char; arg1: integer);
    begin
        case (opt) of
            CASE_ARG('a')
                begin
                    n_fp_parm_regs := arg1;
                end;
            CASE_ARG('g')
                begin
                    if (arg1 < 2) then begin
                        report_error(Internal, 166, "ugen.p", "insufficient code generator fp registers");
                        n_fp_cg_regs := 2;
                    return;
                end;
                n_fp_cg_regs := arg1;
            end;
            CASE_ARG('r')
                begin
                    n_unsaved_fp_regs := arg1;
                end;
            CASE_ARG('e')
                begin
                    n_saved_fp_regs := arg1;
                end;
            CASE_ARG(' ')
                begin
                    n_fp_parm_regs := 0;
                    n_unsaved_fp_regs := 0;
                    n_saved_fp_regs := 0;
                    
                    if (arg1 < 2) then begin
                        report_error(Internal, 182, "ugen.p", "insufficient code generator fp registers ");
                        n_fp_cg_regs := 2;
                        return;
                    end;
                    n_fp_cg_regs := arg1 - 1;
                end;
            otherwise:
                report_error(Internal, 193, "ugen.p", "illegal register type");
        end;
    end;

    procedure dump_tree(arg0: ^Tree; phase: ugen_str); 
    begin
        if (sp1DD0[1] <> chr(0)) then begin
            writeln(temp_file, "Tree dump after ", phase:0);
            writeln(temp_file);
            print_tree(temp_file, arg0, 16#7FFFFFFF, 16#7FFFFFFF);
            writeln(temp_file);
            flush(temp_file);
        end else begin
            writeln(err, "Tree dump after ", phase:0);
            writeln(err);
            print_tree(err, arg0, 16#7FFFFFFF, 16#7FFFFFFF);
            writeln(err);
        end;
    end;

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

    
    procedure create_temp_file();
    var
        fd: integer;
    begin
        copy_filename(temp_fname, "/tmp/ugentmpXXXXXX");

        temp_fname[19] := chr(0);
        fd := mktemp(temp_fname);
        temp_fd := fd;
        
        if (temp_fd = 0) then begin
            report_error(Internal, 254, "ugen.p", "No suitable file can be created");
        end;    
    end;

    procedure unlink_temp_file();
    begin
        unlink(temp_fname);
    end;

    
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
    xpg_env := false;

    sp108 := "_XPG";    
    sp108[5] := chr(0);

    if (getenv(sp108) <> 0) then begin
        xpg_env := true;
    end;

    if (argc < 2) then begin
        writeln(err, "Usage is: ugen [-o binfile] [-l listfile] [-e dumpfile] [-t symbolfilename] [-d] [-trapuv] [-G smallsize] [-p] file.F");
        return 0;
    end else begin
        sp15C0[1] := chr(0);
        sdata_max := 8;

        {Null terminate the strings?}
        
        sp11C0[1] := chr(0);
        spDC0[1] := chr(0);
        lsb_first := false;
        sp9C0[1] := chr(0);
        sp940[1] := chr(0);
        fp_initialized := 0;
        temp_fname[1] := chr(0);
        sp1DD0[1] := chr(0);
        ascii_out := false;
        temp_opt := false;
        debug := false;
        saw_cap_g := false;
        set_domtag(false);
        excpt := false;
        non_local_mtag := 0;
        verbose := false;
        init_dynmem := false;
        sp516 := false;
        use_real_fp_for_all := false;
        sp51C := 0;
        sp518 := 1;
        debug_ugen := false;
        warn_level := ord(Fix);
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
        opcode_arch := false;
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
                                argv(index, sp11C0);
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
                                argv(index, sp9C0);
                            end else goto default;

                        CASE_ARG('l')
                            if (ARG_OPT(3, ' ')) then begin
                                if ((index + 1) = argc) then begin
                                    writeln(err, "filename required after -l");
                                    halt(1);
                                end;
                                index := index + 1;
                                argv(index, spDC0);
                                ascii_out := true; {Assembly output: TRUE}
                            end else goto default;

                        CASE_ARG('t')
                            if (ARG_OPT(3, 'e') and (ARG_OPT(4, 'm')) and (ARG_OPT(5, 'p'))) then begin
                                if (succ(index) = argc) then begin
                                    writeln(err, "filename required after -temp");
                                    halt(1);
                                end;

                                index := index + 1;
                                argv(index, temp_fname);
                                temp_opt := true;
                                
                            end else if ((ARG_OPT(3, 'r')) and (ARG_OPT(4, 'a')) and (ARG_OPT(5, 'p')) and (ARG_OPT(6, 'u')) and (ARG_OPT(7, 'v'))) then begin
                                init_dynmem := true;
                            end else if (ARG_OPT(3,  ' ')) then begin
                                if ((index + 1) = argc) then begin
                                    writeln(err, "filename required after -t");
                                    halt(1);
                                end;
                                index := index +1;
                                argv(index, sp940);
                            end else goto default;

                        CASE_ARG('e')
                            if (ARG_OPT(3,  ' ')) then begin
                                if ((index + 1) = argc) then begin
                                    writeln(err, "filename required after -e");
                                    halt(1);
                                end;
                                
                                index := index + 1;
                                argv(index, sp1DD0);
                                debug := true;
                            end else if (ARG_OPT(3,  'x') and (ARG_OPT(4, 'c')) and (ARG_OPT(5, 'p')) and (ARG_OPT(6, 't')) and (ARG_OPT(7, ' '))) then begin
                                excpt := true;
                            end else goto default;

                        CASE_ARG('d')
                        begin
                            if (IS_OPT("-dwopcode")) then begin
                                isa := ISA_MIPS3;
                                opcode_arch := true;
                            end else if (IS_OPT("-domtag")) then begin
                                set_domtag(true);
                            end else begin
                                debug_ugen := true;
                                debug := true;
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
                                sp51C := u8(arg[3]) - ord('0');
                            end else goto default;

                        CASE_ARG('O') 
                            if (ARG_OPT(3, ' ')) then begin
                                writeln(err, "numeric argument required for -O");
                            end else if ((arg[3] >= '0') and (arg[3] < '5')) then begin
                                sp518 := opt_levels(ord(arg[3]) - ord('0'));
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
                                var_s0 := arg[5];
                                argv(index, arg);
                                func_0044B384(var_s0, str_atoi(arg));
                            end else goto default;

                        CASE_ARG('f')
                            if (ARG_OPT(3, 'r') and ARG_OPT(4, 'e') and ARG_OPT(5, 'g')) then begin
                                index := index + 1;
                                var_s0 := arg[6];
                                argv(index, arg);
                                func_0044B640(var_s0, str_atoi(arg));
                            end else begin
                                if (streq(arg, "-fp32regs")) then begin
                                    fp32regs := true;
                                end else goto default;
                            end;   

                        CASE_ARG('L')
                            if (ARG_OPT(3, ' ')) then begin
                                sp516 := true;
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
                                opcode_arch := true;
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
                                    warn_level := ord(Info);
                                    print_warnings := false;
                                end;

                                CASE_ARG('2')
                                begin
                                    warn_level := ord(Warn);
                                end;

                                CASE_ARG('3')
                                begin
                                    warn_level := ord(Error);
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
                                opcode_arch := true;
                                basicint := true;
                                addr_dtype := Wdt;
                                unitsperaddr := 8;
                            end else goto default;

                        CASE_ARG('-')
                            if ((xpg_env = true) and ARG_OPT(3, '-')) then begin
                                argv(index, sp108);

                                SKIP_END_SPACES(var_s1, sp108);

                                if (var_s1 <> 0) then begin
                                    sp108[var_s1 + 1] := chr(0);
                                end else begin
                                    writeln(err, arg:0, " not understood");
                                end;

                                for var_a0 := 3 to var_s1 + 1 do begin
                                    sp15C0[var_a0 - 2] := sp108[var_a0];
                                end;

                            end;
                        
                            otherwise: 
                            default:
                                writeln(err, arg:0, " not understood");
                    end;                    
                end else begin
                    argv(index, sp15C0);
                    
                    SKIP_END_SPACES(var_s1, sp15C0);        
                end;
            
                index := index + 1;                
             until (index >= argc);
        end;

        if (sp15C0[1] = chr(0)) then begin
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
            SKIP_END_SPACES(var_v0_3, spDC0);
            spDC0[var_v0_3 + 1] := chr(0);
        
            rewrite(sp534, spDC0);

            if (sp940[1] = chr(0)) then begin
                for index := 1 to var_s1 - 1 do begin    
                    sp940[index] := sp15C0[index];
                end;
                var_v0_3 := var_s1;
                sp940[var_v0_3] := 'T';
            end else begin
                var_v0_3 := sizeof(sp940) - 1;
                while ((var_v0_3 <> 0) and (sp940[var_v0_3] = ' ')) do begin
                    var_v0_3 := var_v0_3 - 1;
                end;
            end;

            sp940[var_v0_3 + 1] := chr(0);
            if (st_readbinary(sp940, 'r') < 0) then begin
                writeln(err, "Cannot read symbol table file");
                halt(1);
            end;
        end;

        initialize_tree();
        init_ibuffer();
        uini();
        initur(sp15C0);

        if (sp11C0[1] = chr(0)) then begin
            sp11C0 := sp15C0;
            sp11C0[var_s1] := 'G'; {binasm extension}
            var_v0_3 := var_s1;
        end else begin 
           SKIP_END_SPACES(var_v0_3, sp11C0);
        end;

        sp11C0[var_v0_3 + 1] := chr(0);

        if (temp_fname[1] = chr(0)) then begin
            create_temp_file();
        end else begin 
            SKIP_END_SPACES(var_v0_4, temp_fname);
            temp_fname[var_v0_4 + 1] := chr(0);
        end;


        if (sp1DD0[1] <> chr(0)) then begin
            rewrite(temp_file, sp1DD0);
        end;
    

        set_opts(sp518, sp51C);

        if (verbose) then begin
            write(err, "ugen:");
        end;

        clear_sym_tab();
        open_bin_file(temp_fname);
        init_build();

        while (true) do begin
            clear_ibuffer();
            tree_heap_mark := alloc_mark(tree_heap);
            temp_v0_3 := build_tree(verbose);

            if (temp_v0_3 = nil) then break;

            if (debug) then begin
                dump_tree(temp_v0_3, "Build");
            end;

            temp_v0_3 := translate_tree(temp_v0_3);

            if (debug) then begin
                dump_tree(temp_v0_3, "Translate");
            end;

            if (opt_labels <> 0) then begin
            
                if (sp1DD0[1] <> chr(0)) then begin
                    labelopt(temp_v0_3, addr(temp_file), debug, sp516);
                end else begin
                    labelopt(temp_v0_3, addr(err), debug, sp516);
                    
                end;
                
            end;

            func_0044B2EC(temp_v0_3);

            if (sp9C0[1] <> chr(0)) then begin
                inituwrite(sp9C0);
                u_tree(temp_v0_3);
            end;

            init_eval();
            eval(temp_v0_3, 16#48);
            output_inst_bin(ibuffer^[1], pred(i_ptr), ibuffer^[ibuffer_size], ibuffer_size - d_ptr);
            alloc_release(tree_heap, tree_heap_mark);
        end;

        close_bin_file();
        clear_ibuffer();
        emit_vers();
        emit_pic(pic_level);
        output_decls();
        open_bin_file(sp11C0);
        output_inst_bin(ibuffer^[1], pred(i_ptr), ibuffer^[ibuffer_size], ibuffer_size - d_ptr);
        close_bin_file();
        cat_files(sp11C0, temp_fname);
        
        if (not temp_opt) then begin
            unlink_temp_file();
        end;

        if (ascii_out) then begin
            sp11C0[var_v0_3 + 1] := ' ';
            output_inst_ascii(sp11C0, sp534);
        end;

        if (verbose) then begin
            writeln(err);
        end;

        if (has_errors(warn_level)) then begin
            halt(1);
        end;
        
    end;

    return 0;
end.
