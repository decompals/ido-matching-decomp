#include "common.i"

{ global types }

type
    FileOfBinasm = File of binasm;

    mipsformats = (
        mipsfmt_0, mipsfmt_1, mipsfmt_2, mipsfmt_3,
        mipsfmt_4, mipsfmt_5, mipsfmt_6, mipsfmt_7,
        mipsfmt_8, mipsfmt_9, mipsfmt_10
    );

    asmformat = (
        af,
        afra,
        afri,
        afrrr,
        afrr,
        afa,
        afrrl,
        afrl,
        afl,
        aforrr,
        afr,
        afri_fp,
        af_12, { unused ? }
        af_13, { unused ? }
        dli_dla,
        af_15, { unused ? }
        afrrrr
	);

    severity_levels = (
        severity_level_0,
        severity_level_1,
        severity_level_2,
        severity_level_3,
        severity_level_4
    );

    Reorg_Enum = (
        Reorg_Val_0,
        Reorg_Val_1,
        Reorg_Val_2,
        Reorg_Val_3,
        Reorg_Val_4,
        Reorg_Val_5,
        Reorg_Val_6,
        Reorg_Val_7,
        Reorg_Val_8,
        Reorg_Val_9,
        Reorg_Val_10,
        Reorg_Val_11,
        Reorg_Val_12,
        Reorg_Val_13
    );

    mips_isa = (
        ISA_UNSPEC,
        ISA_MIPS1,
        ISA_MIPS2,
        ISA_MIPS3,
        ISA_MIPS4
    );

    options = (
        option__EB,
        option__EL,
        option__G,
        option__K,
        option__M,
        option__NR,
        option__O,
        option__O0,
        option__O1,
        option__O2,
        option__O3,
        option__O4,
        option__Olimit,
        option__R,
        option__RD,
        option__T,
        option_e,
        option_fli,
        option_f,
        option_f0,
        option_f1,
        option_f2,
        option_f3,
        option_f4,
        option_g,
        option_g0,
        option_g1,
        option_g2,
        option_g3,
        option_l,
        option_o,
        option_p,
        option_p0,
        option_p1,
        option_p2,
        option_p3,
        option_r,
        option_t,
        option_v,
        option_w,
        option_w1,
        option_w2,
        option_w3,
        option_no_const_opts,
        option_no_lui_opts,
        option_no_div_rem_opts,
        option_no_at_compression,
        option_no_branch_target,
        option_mips1,
        option_mips2,
        option_mips3,
        option_mips4,
        option_nopool,
        option_align8,
        option_align16,
        option_align32,
        option_align64,
        option_align_common,
        option_gp_warn,
        option_non_pic,
        option_r3000,
        option_r4000,
        option_r6000,
        option_r6000LHU,
        option_r6000LWL,
        option_trapuv,
        option_nopeep,
        option_peepdbg,
        option_noswpipe,
        option_swpdbg,
        option_nosymregs,
        option_noxbb,
        option_aggr_xbb,
        option_xbbdbg,
        option_newhilo,
        option_domtag,
        option_fpstall_nop,
        option_noglobal,
        option_nobopt,
        option_dwalign,
        option_excpt,
        option_diag,
        option_mednat,
        option_dwopcode,
        option_64bit,
        option_fp32regs,
        option_extsyms,
        option_pic0,
        option_pic1,
        option_pic2,
        option_big_got,
        option_coff,
        option_elf,
        option_mscoff,
        option_mscoffT,
        option_multi_issue,
        option_nonzero_scnbase,
        option_new_mdebug,
        option_abi,
        option_tfprev10,
        option_force_branch_fixup,
        option_r4200,
        option_r4600,
        option_tfp,
        option_t5_r31,
        option_t5_mtc1,
        option_t5_muldiv,
        option_t5_ll_sc_bug,
        option_r4300_mul
    );

    OptRecord = record;
        unk_00: array[1..5] of boolean;
        unk_08: array[1..5] of integer;
        unk_1C: Byte;
        unk_1D: boolean;
        unk_1E: boolean;
    end;

    MemoryRec = record;
        unk_00: integer;
        unk_04: integer;
        unk_08: Byte;
        unk_0C: integer;
        unk_10: integer;
        unk_14: integer;
        unk_18: integer;
        unk_1C: integer;
        unk_20: integer;
        unk_24: integer;
        unk_28: integer;
    end;
    MemoryRecArr = array [0..0] of MemoryRec;
    MemoryRecArray = record;
        data: ^MemoryRecArr;
        size: cardinal;
    end;

    SymTabRecArr = array [0..0] of PUnkAlpha;
    SymTabRecArray = record
        data: ^SymTabRecArr;
        size: cardinal;
    end;

{ global variables }

var
    template: array [first(opcodes)..last(opcodes)] of cardinal;
    opcodeformat: array [first(opcodes)..last(opcodes)] of mipsformats;
    asm2asmformat: array [first(asmcodes)..last(asmcodes)] of asmformat;
    gp_tables: array [0..15] of pointer;
    gprelsize: integer;
    br_always_ops: set of opcodes;
    br_likely_ops: set of opcodes;
    storeops: set of opcodes;
    alu3ops: set of opcodes;
    trapops: set of opcodes;
    fpops: set of opcodes;
    c0123_moves: set of opcodes;
    mark2ops: set of opcodes;
    mark3ops: set of opcodes;
    mark4ops: set of opcodes;
    hilo_defs: set of opcodes;
    c0_ops: set of opcodes;
    c3_ops: set of opcodes;
    gp_fp_moves: set of opcodes;
    regnum: array [first(registers)..last(registers)] of integer;
    knownregs: set of registers;
    shftaddr: integer;
    memory: MemoryRecArray;
    nextlabelchain: IntegerArray;
    multireloc_list: IntegerArray;
    multirelocinstr_list: IntegerArray;
    sym_tab: SymTabRecArray;
    neg_sym_tab: SymTabRecArray;
    isa: mips_isa;
    opts: OptRecord;
    s_pool_symbol: PUnkAlpha;
    d_pool_symbol: PUnkAlpha;
    currfunc_sym: ^UnkAlpha;
    nopinserted: integer;
    new_hilo: boolean;
    fpstall_nop: boolean;
    nopsremaining: integer;
    transform_flag: boolean;
    macroflag: boolean;
    non_pic_flag: boolean;
    num_issue: integer;
    mscoff: boolean;
    force_branch_fixup: boolean;
    mscoff1: boolean;
    volatileflag: boolean;
    movableflag: boolean;
    keepflag: boolean;
    deferred_line_no: integer;
    has_noreorder: boolean;
    dwalign: boolean;
    r6000_lhu_flag: boolean;
    float_li_flag: boolean;
    unsafe_opt: boolean;
    xbb_opt: boolean;
    peep_opt: boolean;
    swpipe_opt: boolean;
    do_mtag: boolean;
    branch_opt: boolean;
    symregs_opt: boolean;
    global_opt: boolean;
    initial_loc: boolean;
    ent_pending: boolean;
    last_bb: array [1..3] of Byte;
    is_nonleaf: boolean;
    currfunc_hasedata: boolean;
    currentline: integer;
    currentent: integer;
    currentent_name: integer;
    swpipe_debug: integer;
    first_pdr: integer;
    excpt_opt: boolean;
    last_pdr: integer;
    currentfile: integer;
    savelastloc: boolean;
    lastsym: integer;
    peep_debug: integer;
    lastic: integer;
    lastsegment: segments;
    realsegments: set of segments;
    lastrld: integer;
    nextmultireloc: integer;
    nextmultirelocinstr: integer;
    severity: severity_levels;
    tracereorder: boolean;
    reorder: boolean;
    debugflag: integer;
    profileflag: integer;
    sexchange: boolean;
    optflag: integer;
    elf_flag: boolean;
    abi_flag: boolean;
    isbigendianhost: boolean;
    pendinginstr: boolean;
    notandm: boolean;
    xbb_debug: integer;
    listingflag: boolean;
    fp_pool_flag: boolean;
    verbose: boolean;
    warnexitflag: boolean;
    saw_cap_g: boolean;
    gp_disp_address: integer;
    saw_pic_flag: boolean;
    maybe_r4000: boolean;
    cprestore_offset: integer;
    t5_jal: boolean;
    t5_mtc1: boolean;
    t5_muldiv: boolean;
    t5_ll_sc_bug: boolean;
    tfp_rev10: boolean;
    mednat: boolean;
    new_mdebug: boolean;
    dwopcode: boolean;
    r4300_mul: boolean;
    fp_hack_flag: 0..4; { TODO enum ? }
    mcount_address: pointer;
    mcount_sym: integer;
    lastinstr: itype;
    olimit_value: integer;
    gprmask: cardinal;
    fprmask: cardinal;
    liveset: integer;
    real_delays: boolean;
    fromas0: boolean;
    fixup_count: integer;
    use_ddopt_info: boolean;
    nonzero_scnbase: boolean;
    firstusertextseg: integer;
    lastusertextseg: integer;
    xpg_flag: boolean;
    nowarnflag: boolean;
    sixtyfour_bit: boolean;
    fp32regs: boolean;
    binasm_file: FileOfBinasm;
    

{ external functions }

function memset(x: pointer; y: integer; z: integer): pointer; external;
function xmalloc(size: integer): pointer; external;
procedure new_error(); external;
function atol(arg0: ^Identname): integer; external;
function getenv(var arg0: String): integer; external;
procedure get_sstring(arg0: integer; arg1: GString); external;
procedure get_lstring(arg0: integer; arg1: GString); external;
procedure ltoa(arg0: integer; arg1: ^char); external;
procedure init_reorg_state(arg0: Reorg_Enum); external;
function which_opt(arg0: GString): options; external;
function grow_array(var arg0: integer; arg1: integer; arg2: cardinal; arg3: pointer; arg4: boolean): pointer; external;
function init_gp_table(size: integer): pointer; external;
procedure dd_initialize(var arg0: Filename); external;
function negative_file_opt(s: GString): boolean; external;
procedure st_asinit(var arg0: Filename; arg1: integer); external;
function ms_readsym(var arg0: Filename): integer; external;
procedure init_j_def_live(); external;
procedure init_inst_heap(); external;
procedure call_perror(arg0: integer; str: GString); external;
procedure init_binasm(); external;
procedure dd_close(); external;
procedure wrobj(); external;
function strlen(p : ^Filename): integer; external;
procedure parsestmt(); external;
procedure restore_gp(); external;
function filesize(var f: FileOfBinasm): integer; external;
function l_addr(var value: integer): pointer; external;
function enter_undef_sym(ptr: pointer): pointer; external;
procedure traverse_bb(); external;
procedure create_function_table(); external;
procedure flush_line_no(); external;

program main;
var
    j: integer;
    input_fname: GString;
    string2: GString;
    t_opt_string: GString;
    e_opt_string: GString;
    xpg_string: String;
    i: integer;
    
procedure init_all();
var
    j: integer;
    index: integer;
    reorg: Reorg_Enum;
    arg: GString;
    sym: ^UnkAlpha;
    pad2: integer;
    spB8: record
            case integer of
                1: (w:integer);
                2: (s:0..65535);
            end;    
    pad3: integer;
    pad4: integer;
    one: integer;

    
    
    procedure set_mips_inst_template(fop: opcodes; tmpl: cardinal; fmt: mipsformats);
    begin
        template[fop] := tmpl;
        opcodeformat[fop] := fmt;
    end;
    
    procedure register_asmcode(fasm: asmcodes; fmt: asmformat; op: opcodes);
    begin
        asm2op[fasm] := op;
        asm2asmformat[fasm] := fmt;
    end;
    
    function func_00440E8C(): boolean;
    var
        i: integer;
        ret: boolean;
    begin
        ret := true;
        for i := 0 to 15 do begin
            if (i in [1,3]) then begin
                gp_tables[i] := init_gp_table(gprelsize);
                if (gp_tables[i] = nil) then begin
                    ret := false;
                end;
            end else begin
                gp_tables[i] := nil;
            end;
        end;
    
        for i := 1 to 2 do begin
            prev_sdata[i].unk00 := 0;
            prev_sdata[i].unk0C := 0;
            prev_sdata[i].unk04 := false;
            prev_sdata[i].unk08 := 1;            
            prev_sdata[i].unk10 := 1;
        end;
        return ret;
    end;
    
    function func_00440F68(arg0: opcodes): opcodes;
    begin
        if (isa >= ISA_MIPS2) then begin
            func_00440F68 := arg0;
        end else begin
            func_00440F68 := op_macro;
        end;
    end;
    
    procedure func_00440FA0(var arg0: PUnkAlpha; arg1: Byte);
    begin
        new(arg0);
        arg0 := memset(arg0, 0, sizeof(UnkAlpha));
        arg0^.unk30 := arg1;
        arg0^.unk37 := true;
    end;
    
begin
    new(emptystring.z);
    emptystring.z^[1] := chr(0);
    new(t_opt_string.f);
    t_opt_string.f^[1] := chr(0);
    new(string2.f);
    string2.f^[1] := chr(0);
    new(input_fname.f);
    input_fname.f^[1] := chr(0);
    new(outname.f);
    outname.o^ := "b.out\0";
    new(e_opt_string.f);
    e_opt_string.f^[1] := chr(0);

    one := 1; { required to match }

    nopinserted := 0;
    nopsremaining := 0;
    endofbasicb := false;
    reorderflag := true;
    transform_flag := true;
    macroflag := true;
    atflag := true;
    volatileflag := false;
    movableflag := true;
    keepflag := false;
    deferred_line_no := -1;

    for j := 1 to 5 do begin
        opts.unk_08[j] := 0;
        opts.unk_00[j] := true;            
    end;
    opts.unk_1C := 3;
    opts.unk_1D := false;
    opts.unk_1E := false;
    
    has_noreorder := false;
    dwalign := false;
    ent_pending := false;

    last_bb[1] := 0;
    last_bb[2] := 0;
    last_bb[3] := 0;
    
    unsafe_opt := false;
    xbb_opt := true;
    peep_opt := true;
    swpipe_opt := true;
    branch_opt := true;
    symregs_opt := true;
    global_opt := true;
    initial_loc := true;
    currsegment := 0;
    is_nonleaf := false;
    currfunc_hasedata := false;

    new(currfunc_sym);
    currfunc_sym^.unk37 := true;
    currfunc_sym^.unk35 := 0;
    currfunc_sym^.unk30 := 0;

    realsegments := [0, 1, 2, 5, 6, 9, 15];
    
    currentline := 0;
    currentent := 0;
    currentent_name := 0;
    first_pdr := 0;
    last_pdr := 0;
    currentfile := -1;
    savelastloc := false;
    lastsym := 0;
    aligning := true;
    lastic := 0;
    lastsegment := 0;
    lastrld := 0;
    nextrld := one;
    nextmultireloc := one;
    nextmultirelocinstr := one;
    severity := severity_level_4;
    tracereorder := false;
    reorder := false;
    debugflag := 0;
    profileflag := 1;
    moxieflag := false;
    optflag := 1;
    elf_flag := true;
    abi_flag := false;
    gprelsize := 8;
    spB8.w := 1;
    isbigendianhost := (spB8.s = 0);
    verbose := false;
    bigendian := isbigendianhost;
    pendinginstr := false;
    notandm := true;        
    listingflag := false;
    isa := ISA_UNSPEC;
    fp_pool_flag := true;
    saw_cap_g := false;
    picflag := 0;
    big_got := false;
    gp_disp_address := 0;
    saw_pic_flag := false;
    maybe_r4000 := true;
    cprestore_offset := -1;
    reorg := Reorg_Val_0;
    
    func_00440FA0(s_pool_symbol, 5);
    func_00440FA0(d_pool_symbol, 6);

    float_li_flag := false;
    tfp_rev10 := false;
    t5_jal := false;
    t5_mtc1 := false;
    t5_muldiv := false;
    t5_ll_sc_bug := false;
    r4300_mul := false;
    fp_hack_flag := 4;
    gp_fp_moves := [op_zlwc1, op_zswc1, op_zldc1, op_zsdc1, op_zlsc1, op_zssc1,
                    op_zmfc1, op_zcfc1, op_zmtc1, op_zctc1, op_zdmtc1, op_zdmfc1];
    fromas0 := false;
    real_delays := false;
    gprmask := 0;
    fprmask := 0;
    fixup_count := 0;
    liveset := 0;
    olimit_value := 500;
    peep_debug := 0;
    firstusertextseg := 15;
    lastusertextseg := -1;

    memory.size := 16;
    memory.data := xmalloc(memory.size * sizeof(MemoryRec));
    if (memory.data = nil) then begin
        new_error();
    end;

    seg_ic.size := 16;
    seg_ic.data := xmalloc(seg_ic.size * 4);
    if (seg_ic.data = nil) then begin
        new_error();
    end;

    nextlabelchain.size := 16;
    nextlabelchain.data := xmalloc(nextlabelchain.size * 4);
    if (nextlabelchain.data = nil) then begin
        new_error();
    end;

    rld_list.size := 0;
    multireloc_list.size := 0;
    multirelocinstr_list.size := 0;

    for j := 0 to 15 do begin
        memory.data^[j].unk_04 := 0;
        memory.data^[j].unk_08 := j;
        seg_ic.data^[j] := 0;
        nextlabelchain.data^[j] := 0;
    end;            

    sym_tab.size := 0;
    neg_sym_tab.size := 0;
    new(mainpath.f);
    get_sstring(0, mainpath);
    new(arg.o);
    index := 1;
    if (argc >= 2) then begin
        repeat
            get_lstring(index, arg);
            if (arg.o^[1] = '-') then begin
                case (which_opt(arg)) of 
                    option_r3000:
                        begin
                            reorg := Reorg_Val_1;
                            maybe_r4000 := false;
                        end;
                    option_mips1: isa := ISA_MIPS1;
                    option_mips2: isa := ISA_MIPS2;
                    option_mips3: isa := ISA_MIPS3;
                    option_r4000: reorg := Reorg_Val_3;
                    option_r4200: reorg := Reorg_Val_4;
                    option_r4600: reorg := Reorg_Val_5;
                    option_tfp: reorg := Reorg_Val_11;
                    option_t5_r31: t5_jal := true;
                    option_t5_mtc1: t5_mtc1 := true;
                    option_t5_muldiv: t5_muldiv := true;
                    option_t5_ll_sc_bug: t5_ll_sc_bug := true;
                    option_r6000:
                        begin
                            reorg := Reorg_Val_6;
                            maybe_r4000 := false;
                        end;
                    option_mips4:
                        begin
                            isa := ISA_MIPS4;
                            maybe_r4000 := false;
                        end;
                    option_nopeep: peep_opt := false;
                    option_peepdbg:
                        begin
                            index := index + 1;
                            get_lstring(index, arg);
                            peep_debug := atol(arg.o);
                        end;
                    option_noswpipe: swpipe_opt := false;
                    option_swpdbg:
                        begin
                            index := index + 1;
                            get_lstring(index, arg);
                            swpipe_debug := atol(arg.o);
                        end;
                    option_nosymregs: symregs_opt := false;
                    option_noxbb: xbb_opt := false;
                    option_aggr_xbb: unsafe_opt := true;
                    option_xbbdbg:
                        begin
                            index := index + 1;
                            get_lstring(index, arg);
                            xbb_debug := atol(arg.o);
                        end;
                    option_newhilo: new_hilo := true;
                    option_domtag: do_mtag := true;
                    option_fpstall_nop: fpstall_nop := true;
                    option_noglobal: global_opt := false;
                    option_nobopt: branch_opt := false;
                    option_dwalign: dwalign := true;
                    option_excpt:
                        begin
                            excpt_opt := true;
                            realsegments := [0, 1, 2, 5, 6, 7, 8, 9, 15];
                        end;
                    option_r6000LHU: r6000_lhu_flag := true;
                    option_fli: float_li_flag := true;
                    option_f: fp_hack_flag := 3;
                    option_f0: fp_hack_flag := 0;
                    option_f1: fp_hack_flag := 1;
                    option_f2: fp_hack_flag := 2;
                    option_f3: fp_hack_flag := 3;
                    option_f4: fp_hack_flag := 4;
                    option_w,
                    option_w1:
                        begin
                            nowarnflag := true;
                            warnexitflag := false;
                        end;
                    option_w2:
                        begin
                            nowarnflag := false;
                            warnexitflag := true;
                        end;
                    option_w3:
                        begin
                            nowarnflag := true;
                            warnexitflag := true;
                        end;
                    option__K: keepflag := true;
                    option__M: moxieflag := true;
                    option__O0: optflag := 0;
                    option__O1: optflag := 1;
                    option__O, option__O2: optflag := 2;
                    option__O3: optflag := 3;
                    option__O4: optflag := 4;
                    option__Olimit:
                        begin
                            index := index + 1;
                            get_lstring(index, arg);
                            olimit_value := atol(arg.o);
                        end;
                    option_e:
                        begin
                            index := index + 1;
                            get_sstring(index, e_opt_string);
                            dd_initialize(e_opt_string.f^);
                            use_ddopt_info := true;
                        end;
                    option_g0: debugflag := 0;
                    option_g1: debugflag := 1;
                    option_g, option_g2: debugflag := 2;
                    option_g3: debugflag := 3;
                    option_p0: profileflag := 0;
                    option_p1: profileflag := 1;
                    option_p, option_p2: profileflag := 2;
                    option_p3: profileflag := 3;
                    option_r: reorder := true;
                    option__RD: real_delays := true;
                    option__NR: reorderflag := false;
                    option__R: tracereorder := true;
                    option_l: listingflag := true;
                    option__EB: bigendian := true;
                    option__EL: bigendian := false;
                    option_v:
                        begin
                            verbose := true;
                            Write(err, 'as1: ');
                            Flush(err);
                        end;
                    option_t:
                        begin
                            index := index + 1;
                            get_sstring(index, t_opt_string);
                        end;
                    option__G:
                        begin
                            index := index + 1;
                            get_lstring(index, arg);
                            gprelsize := atol(arg.o);
                            if (gprelsize <> 0) then begin
                                saw_cap_g := true;
                            end;
                        end;
                    option_o:
                        begin
                            index := index + 1;
                            get_sstring(index, outname);
                        end;
                    option_no_const_opts: opts.unk_00[1] := false;
                    option_no_lui_opts: opts.unk_00[2] := false;
                    option_no_div_rem_opts: opts.unk_00[3] := false;
                    option_no_at_compression: opts.unk_00[4] := false;
                    option_no_branch_target: opts.unk_00[5] := false;
                    option_gp_warn: opts.unk_1E := true;
                    option_non_pic:
                        begin
                            non_pic_flag := true;
                            picflag := 0;
                        end;
                    option_pic0:
                        begin
                            picflag := 0;
                            saw_pic_flag := true;
                        end;
                    option_pic1:
                        begin
                            picflag := 1;
                            saw_pic_flag := true;
                        end;
                    option_pic2:
                        begin
                            picflag := 2;
                            saw_pic_flag := true;
                            if (saw_cap_g and (gprelsize <> 0)) then begin
                                PostError("-pic2 implies -G 0. -G flag ignored", emptystring, ErrorLevel_2);
                            end;
                            gprelsize := 0;
                        end;
                    option_big_got: big_got := true;
                    option_align_common: opts.unk_1D := true;
                    option_nopool: fp_pool_flag := false;
                    option_diag: diag_flag := true;
                    option_mednat: mednat := true;
                    option_dwopcode: dwopcode := true;
                    option_64bit:
                        begin
                            sixtyfour_bit := true;
                            dwopcode := true;
                            fp32regs := true;
                        end;
                    option_fp32regs: fp32regs := true;
                    option_coff: elf_flag := false;
                    option_elf: elf_flag := true;
                    option_mscoff: mscoff := true;
                    option_mscoffT: mscoff1 := true;
                    option_multi_issue:
                        begin
                            index := index + 1;
                            reorg := Reorg_Val_10; get_lstring(index, arg);
                            num_issue := atol(arg.o);
                        end;
                    option_nonzero_scnbase: nonzero_scnbase := true;
                    option_new_mdebug: new_mdebug := true;
                    option_abi: abi_flag := true;
                    option_tfprev10: tfp_rev10 := true;
                    option_r4300_mul: r4300_mul := true;
                    option_force_branch_fixup: force_branch_fixup := true;
                    option_align8,
                    option_align16,
                    option_align32,
                    option_align64,
                    option_trapuv: ; { no action }
                    otherwise:
                        if (xpg_flag and negative_file_opt(arg)) then begin
                            if (input_fname.f^[1] = chr(0)) then begin
                                get_sstring(index, string2);
                                for i := 3 to 1024 do
                                    input_fname.f^[i - 2] := string2.f^[i];
                            end else begin
                                PostError("too many file names on command line", emptystring, ErrorLevel_2);
                            end;
                        end else begin
                            PostError("unknown option", arg, ErrorLevel_2);
                        end;
                end;
            end else if (input_fname.f^[1] = chr(0)) then begin
                get_sstring(index, input_fname);
            end else begin
                PostError("too many file names on command line", emptystring, ErrorLevel_2);
            end;
            index := index + 1;
        until (index >= argc);
    end;

    dispose(arg.o);
    if (input_fname.o^[1] = chr(0)) then begin
        input_fname.o^ := "binasm\0";
    end;

    if ((profileflag >= 2) and (debugflag <= 0)) then begin
        debugflag := 3;
    end;

    global_opt := global_opt and (optflag >= 2) and (debugflag in [0,3]);
    if not global_opt then begin
        peep_opt := false;
        symregs_opt := false;
        swpipe_opt := false;
        xbb_opt := false;
    end;

    init_reorg_state(reorg);
    sexchange := (isbigendianhost <> bigendian);

    br_always_ops := [op_zbltz, op_zbgez, op_zbltzal, op_zbgezal, op_zbc0f,
                      op_zbc0t, op_zbc1f, op_zbc1t, op_zbc2f, op_zbc2t,
                      op_zbeq, op_zbne, op_zblez, op_zbgtz, op_zbc3f, op_zbc3t];
    br_likely_ops := [op_zbltzl, op_zbgezl, op_zbltzall, op_zbgezall, op_zbc0fl,
                      op_zbc0tl, op_zbc1fl, op_zbc1tl, op_zbc2fl, op_zbc2tl,
                      op_zbeql, op_zbnel, op_zblezl, op_zbgtzl];
    branchops := br_always_ops + br_likely_ops;
    storeops := [op_zsb, op_zsh, op_zswl, op_zsw, op_zswr,
                 op_zsc, op_zswc1, op_zswc2, op_zsd, op_zsdc1,
                 op_zsdc2, op_zsdl, op_zsdr, op_zscd, op_zssc1, op_zswc3];
    alu3ops := [op_zsllv, op_zsrlv, op_zsrav, op_zmult, op_zmultu,
                op_zdiv, op_zdivu, op_zadd, op_zaddu, op_zsub,
                op_zsubu, op_zand, op_zor, op_zxor, op_znor,
                op_zslt, op_zsltu, op_ztlt, op_ztltu, op_ztge,
                op_ztgeu, op_zteq, op_ztne, op_zdadd, op_zdaddu,
                op_zdsub, op_zdsubu, op_zdsll, op_zdsrl, op_zdsra,
                op_zdsll32, op_zdsrl32, op_zdsra32, op_zdsllv, op_zdsrlv,
                op_zdsrav, op_zdmult, op_zdmultu, op_zddiv, op_zddivu,
                op_zmovf, op_zmovt, op_zmovn, op_zmovz, op_zlwxc1,
                op_zldxc1, op_zswxc1, op_zsdxc1, op_zpfetch];
    trapops := [op_ztlt, op_ztltu, op_ztge, op_ztgeu, op_zteq, op_ztne];
    fpops := [op_fadd_s, op_fadd_d, op_fadd_e, op_fsub_s, op_fsub_d,
              op_fsub_e, op_fmul_s, op_fmul_d, op_fmul_e, op_fdiv_s,
              op_fdiv_d, op_fdiv_e, op_fsqrt_s, op_fsqrt_d, op_fsqrt_e,
              op_fabs_s, op_fabs_d, op_fabs_e, op_fmov_s, op_fmov_d,
              op_fmov_e, op_fneg_s, op_fneg_d, op_fneg_e,op_fcvt_s_d,
              op_fcvt_s_e, op_fcvt_s_w, op_fcvt_d_s, op_fcvt_d_e, op_fcvt_d_w,
              op_fcvt_e_s, op_fcvt_e_d, op_fcvt_e_w, op_fcvt_w_s, op_fcvt_w_d,
              op_fcvt_w_e, op_fc_f_s, op_fc_f_d, op_fc_f_e, op_fc_un_s,
              op_fc_un_d, op_fc_un_e, op_fc_eq_s, op_fc_eq_d, op_fc_eq_e,
              op_fc_ueq_s, op_fc_ueq_d, op_fc_ueq_e, op_fc_olt_s, op_fc_olt_d,
              op_fc_olt_e, op_fc_ult_s, op_fc_ult_d, op_fc_ult_e, op_fc_ole_s,
              op_fc_ole_d, op_fc_ole_e, op_fc_ule_s, op_fc_ule_d, op_fc_ule_e,
              op_fc_sf_s, op_fc_sf_d, op_fc_sf_e, op_fc_ngle_s, op_fc_ngle_d,
              op_fc_ngle_e, op_fc_seq_s, op_fc_seq_d, op_fc_seq_e, op_fc_ngl_s,
              op_fc_ngl_d, op_fc_ngl_e, op_fc_lt_s, op_fc_lt_d, op_fc_lt_e,
              op_fc_nge_s, op_fc_nge_d, op_fc_nge_e, op_fc_le_s, op_fc_le_d,
              op_fc_le_e, op_fc_ngt_s, op_fc_ngt_d, op_fc_ngt_e, op_zround_w_s,
              op_zround_w_d, op_zround_w_e, op_ztrunc_w_s, op_ztrunc_w_d, op_ztrunc_w_e,
              op_zceil_w_s, op_zceil_w_d, op_zceil_w_e, op_zfloor_w_s, op_zfloor_w_d,
              op_zfloor_w_e, op_zround_l_s, op_ztrunc_l_s, op_zceil_l_s, op_zfloor_l_s,
              op_zround_l_d, op_ztrunc_l_d, op_zceil_l_d, op_zfloor_l_d, op_zround_l_e,
              op_ztrunc_l_e, op_zceil_l_e, op_zfloor_l_e, op_fcvt_l_s, op_fcvt_l_d,
              op_fcvt_l_e, op_fcvt_l_w, op_fcvt_s_l, op_fcvt_d_l, op_fcvt_e_l,
              op_fcvt_w_l, op_fmadd_s, op_fmadd_d, op_fmadd_e, op_fmsub_s,
              op_fmsub_d, op_fmsub_e, op_fnmadd_s, op_fnmadd_d, op_fnmadd_e,
              op_fnmsub_s, op_fnmsub_d, op_fnmsub_e, op_frecip_s, op_frecip_d,
              op_frsqrt_s, op_frsqrt_d, op_fmovf_s, op_fmovf_d, op_fmovt_s,
              op_fmovt_d, op_fmovn_s, op_fmovn_d, op_fmovz_s, op_fmovz_d];
    c0123_moves := [op_zmfc0, op_zmfc1, op_zmfc2, op_zcfc1, op_zmtc0,
                    op_zmtc1, op_zmtc2, op_zctc1, op_zdmtc1, op_zdmfc1,
                    op_zdmtc0, op_zdmfc0, op_zdmtc2, op_zdmfc2, op_zcfc0,
                    op_zcfc2, op_zctc0, op_zctc2, op_zmfc3, op_zmtc3,
                    op_zcfc3, op_zctc3, op_zmfpc, op_zmtpc, op_zmfps, op_zmtps];
    mark2ops := [op_ztlt, op_ztltu, op_ztge, op_ztgeu, op_zteq,
                 op_ztne, op_zbltzl, op_zbgezl, op_zbltzall, op_zbgezall,
                 op_zbc0fl, op_zbc0tl, op_zbc1fl, op_zbc1tl, op_zbc2fl,
                 op_zbc2tl, op_zbeql, op_zbnel, op_zblezl, op_zbgtzl,
                 op_ztlti, op_ztltiu, op_ztgei, op_ztgeiu, op_zteqi,
                 op_ztnei, op_zll, op_zsc, op_zldc1, op_zldc2,
                 op_zsdc1, op_zsdc2, op_zcache, op_zeret];
    mark3ops := [op_zdadd, op_zdaddu, op_zdsub, op_zdsubu, op_zdsll,
                 op_zdsrl, op_zdsra, op_zdsll32, op_zdsrl32, op_zdsra32,
                 op_zdsllv, op_zdsrlv, op_zdsrav, op_zdmult, op_zdmultu,
                 op_zddiv, op_zddivu, op_zdaddi, op_zdaddiu, op_zlwu,
                 op_zld, op_zsd, op_zldl, op_zldr, op_zlld,
                 op_zsdl, op_zsdr, op_zscd, op_zdmtc1, op_zdmfc1,
                 op_zdmtc0, op_zdmfc0, op_zdmtc2, op_zdmfc2, op_zround_l_s,
                 op_ztrunc_l_s, op_zceil_l_s, op_zfloor_l_s, op_zround_l_d, op_ztrunc_l_d,
                 op_zceil_l_d, op_zfloor_l_d, op_zround_l_e, op_ztrunc_l_e, op_zceil_l_e,
                 op_zfloor_l_e, op_fcvt_l_s, op_fcvt_l_d, op_fcvt_l_e, op_fcvt_l_w,
                 op_fcvt_s_l, op_fcvt_d_l, op_fcvt_e_l, op_fcvt_w_l];
    mark4ops := [op_zmovf, op_zmovt, op_zmovn, op_zmovz, op_fmadd_s, op_fmadd_d, op_fmadd_e, op_fmsub_s, op_fmsub_d, op_fmsub_e, op_fnmadd_s, op_fnmadd_d, op_fnmadd_e, op_fnmsub_s, op_fnmsub_d, op_fnmsub_e, op_frecip_s, op_frecip_d, op_frsqrt_s, op_frsqrt_d, op_fmovf_s, op_fmovf_d, op_fmovt_s, op_fmovt_d, op_fmovn_s, op_fmovn_d, op_fmovz_s, op_fmovz_d, op_zlwxc1, op_zldxc1, op_zswxc1, op_zsdxc1, op_zpfetch, op_zpref, op_ztlbr1, op_ztlbp1, op_zmfpc, op_zmtpc, op_zmfps, op_zmtps];
    hilo_defs := [op_zmthi, op_zmtlo, op_zmult, op_zmultu, op_zdiv,
                  op_zdivu, op_zdmult, op_zdmultu, op_zddiv, op_zddivu];
    c0_ops := [op_zbc0f, op_zbc0t, op_zc0, op_zmfc0, op_zmtc0,
               op_ztlbr, op_ztlbwi, op_ztlbwr, op_ztlbp, op_zdmtc0,
               op_zdmfc0, op_zcache, op_zdctr, op_zdctw, op_ztlbw,
               op_ztlbr1, op_ztlbp1, op_zmfpc, op_zmtpc, op_zmfps, op_zmtps];
    c3_ops := [op_zbc3f, op_zbc3t, op_zc3, op_zlwc3, op_zswc3, op_zmfc3, op_zmtc3, op_zcfc3, op_zctc3];

    register_asmcode(zabs, afrr, op_macro);
    register_asmcode(zadd, afrrr, op_zadd);
    register_asmcode(zaddu, afrrr, op_zaddu);
    register_asmcode(zaddou, afrrr, op_zaddu);
    register_asmcode(zand, afrrr, op_zand);
    register_asmcode(zb, afl, op_macro);
    register_asmcode(zbc0f, afl, op_zbc0f);
    register_asmcode(zbc0t, afl, op_zbc0t);
    register_asmcode(zbc1f, afl, op_zbc1f);
    register_asmcode(zbc1t, afl, op_zbc1t);
    register_asmcode(zbc2f, afl, op_zbc2f);
    register_asmcode(zbc2t, afl, op_zbc2t);
    register_asmcode(zbc0fl, afl, op_zbc0fl);
    register_asmcode(zbc0tl, afl, op_zbc0tl);
    register_asmcode(zbc1fl, afl, op_zbc1fl);
    register_asmcode(zbc1tl, afl, op_zbc1tl);
    register_asmcode(zbc2fl, afl, op_zbc2fl);
    register_asmcode(zbc2tl, afl, op_zbc2tl);
    register_asmcode(zbeq, afrrl, op_zbeq);
    register_asmcode(zbeqz, afrl, op_zbeq);
    register_asmcode(zbne, afrrl, op_zbne);
    register_asmcode(zbnez, afrl, op_zbne);
    register_asmcode(zble, afrrl, op_macro);
    register_asmcode(zbleu, afrrl, op_macro);
    register_asmcode(zblez, afrl, op_zblez);
    register_asmcode(zbgt, afrrl, op_macro);
    register_asmcode(zbgtu, afrrl, op_macro);
    register_asmcode(zbgtz, afrl, op_zbgtz);
    register_asmcode(zblt, afrrl, op_macro);
    register_asmcode(zbltu, afrrl, op_macro);
    register_asmcode(zbltz, afrl, op_zbltz);
    register_asmcode(zbltzal, afrl, op_zbltzal);
    register_asmcode(zbge, afrrl, op_macro);
    register_asmcode(zbgeu, afrrl, op_macro);
    register_asmcode(zbgez, afrl, op_zbgez);
    register_asmcode(zbgezal, afrl, op_zbgezal);
    register_asmcode(zbal, afrl, op_zbgezal); { why? }
    register_asmcode(zbeql, afrrl, op_zbeql);
    register_asmcode(zbeqzl, afrl, op_zbeql);
    register_asmcode(zbnel, afrrl, op_zbnel);
    register_asmcode(zbnezl, afrl, op_zbnel);
    register_asmcode(zblel, afrrl, op_macro);
    register_asmcode(zbleul, afrrl, op_macro);
    register_asmcode(zblezl, afrl, op_zblezl);
    register_asmcode(zbgtl, afrrl, op_macro);
    register_asmcode(zbgtul, afrrl, op_macro);
    register_asmcode(zbgtzl, afrl, op_zbgtzl);
    register_asmcode(zbltl, afrrl, op_macro);
    register_asmcode(zbltul, afrrl, op_macro);
    register_asmcode(zbltzl, afrl, op_zbltzl);
    register_asmcode(zbltzall, afrl, op_zbltzall);
    register_asmcode(zbgel, afrrl, op_macro);
    register_asmcode(zbgeul, afrrl, op_macro);
    register_asmcode(zbgezl, afrl, op_zbgezl);
    register_asmcode(zbgezall, afrl, op_zbgezall);
    register_asmcode(zbreak, af, op_zbreak);
    register_asmcode(zcia, afri, op_macro);
    register_asmcode(zc0, aforrr, op_zc0);
    register_asmcode(zc1, aforrr, op_zc1);
    register_asmcode(zc2, aforrr, op_zc2);
    register_asmcode(zdiv, afrrr, op_zdiv);
    register_asmcode(zdivu, afrrr, op_zdivu);
    register_asmcode(zj, afa, op_zj);
    register_asmcode(zjal, afa, op_zjal);
    register_asmcode(zla, afra, op_macro);
    register_asmcode(zlb, afra, op_zlb);
    register_asmcode(zlbu, afra, op_zlbu);
    register_asmcode(zlh, afra, op_zlh);
    register_asmcode(zlhu, afra, op_zlhu);
    register_asmcode(zli, afri, op_macro);
    register_asmcode(zlw, afra, op_zlw);
    register_asmcode(zll, afra, op_zll);
    register_asmcode(zlwc1, afra, op_zlwc1);
    register_asmcode(zlwc2, afra, op_zlwc2);
    register_asmcode(zlwl, afra, op_zlwl);
    register_asmcode(zlwr, afra, op_zlwr);
    register_asmcode(zmfc0, afrr, op_zmfc0);
    register_asmcode(zmfc1, afrr, op_zmfc1);
    register_asmcode(zmfc1_d, afrr, op_zmfc1);
    register_asmcode(zmfc2, afrr, op_zmfc2);
    register_asmcode(zcfc0, afrr, op_zcfc0);
    register_asmcode(zcfc1, afrr, op_zcfc1);
    register_asmcode(zcfc2, afrr, op_zcfc2);
    register_asmcode(zmfhi, afr, op_zmfhi);
    register_asmcode(zmflo, afr, op_zmflo);
    register_asmcode(zmove, afrr, op_macro);
    register_asmcode(zmtc0, afrr, op_zmtc0);
    register_asmcode(zmtc1, afrr, op_zmtc1);
    register_asmcode(zmtc1_d, afrr, op_zmtc1);
    register_asmcode(zmtc2, afrr, op_zmtc2);
    register_asmcode(zctc0, afrr, op_zctc0);
    register_asmcode(zctc1, afrr, op_zctc1);
    register_asmcode(zctc2, afrr, op_zctc2);
    register_asmcode(zmthi, afr, op_zmthi);
    register_asmcode(zmtlo, afr, op_zmtlo);
    register_asmcode(zmul, afrrr, op_macro);
    register_asmcode(zmulo, afrrr, op_macro);
    register_asmcode(zmulou, afrrr, op_macro);
    register_asmcode(zmult, afrr, op_zmult);
    register_asmcode(zmultu, afrr, op_zmultu);
    register_asmcode(zneg, afrr, op_macro);
    register_asmcode(znegu, afrr, op_macro);
    register_asmcode(znop, af, op_znop);
    register_asmcode(znor, afrrr, op_znor);
    register_asmcode(znot, afrr, op_macro);
    register_asmcode(zor, afrrr, op_zor);
    register_asmcode(zrem, afrrr, op_zdiv);
    register_asmcode(zremu, afrrr, op_zdivu);
    register_asmcode(zrfe, af, op_zrfe);
    register_asmcode(zrol, afrrr, op_macro);
    register_asmcode(zror, afrrr, op_macro);
    register_asmcode(zsb, afra, op_zsb);
    register_asmcode(zseq, afrrr, op_macro);
    register_asmcode(zsge, afrrr, op_macro);
    register_asmcode(zsgeu, afrrr, op_macro);
    register_asmcode(zsgt, afrrr, op_macro);
    register_asmcode(zsgtu, afrrr, op_macro);
    register_asmcode(zsh, afra, op_zsh);
    register_asmcode(zsle, afrrr, op_macro);
    register_asmcode(zsleu, afrrr, op_macro);
    register_asmcode(zsll, afrrr, op_zsll);
    register_asmcode(zslt, afrrr, op_macro);
    register_asmcode(zsltu, afrrr, op_macro);
    register_asmcode(zsne, afrrr, op_macro);
    register_asmcode(zsra, afrrr, op_zsra);
    register_asmcode(zsrl, afrrr, op_zsrl);
    register_asmcode(zsllv, afrrr, op_zsllv);
    register_asmcode(zsrlv, afrrr, op_zsrlv);
    register_asmcode(zsrav, afrrr, op_zsrav);
    register_asmcode(zsub, afrrr, op_zsub);
    register_asmcode(zsubu, afrrr, op_zsubu);
    register_asmcode(zsubou, afrrr, op_zsubu);
    register_asmcode(zsw, afra, op_zsw);
    register_asmcode(zsc, afra, op_zsc);
    register_asmcode(zswc1, afra, op_zswc1);
    register_asmcode(zswc2, afra, op_zswc2);
    register_asmcode(zswl, afra, op_zswl);
    register_asmcode(zswr, afra, op_zswr);
    register_asmcode(zsyscall, af, op_zsyscall);
    register_asmcode(zxor, afrrr, op_zxor);
    register_asmcode(ztlbr, af, op_ztlbr);
    register_asmcode(ztlbwi, af, op_ztlbwi);
    register_asmcode(ztlbwr, af, op_ztlbwr);
    register_asmcode(ztlbp, af, op_ztlbp);
    register_asmcode(ztlbr1, af, op_ztlbr1);
    register_asmcode(ztlbp1, af, op_ztlbp1);
    register_asmcode(zsync, af, op_zsync);
    register_asmcode(zld, afra, func_00440F68(op_zld));
    register_asmcode(zsd, afra, func_00440F68(op_zsd));
    register_asmcode(zldc1, afra, func_00440F68(op_zldc1));
    register_asmcode(zldc2, afra, func_00440F68(op_zldc2));
    register_asmcode(zsdc1, afra, func_00440F68(op_zsdc1));
    register_asmcode(zsdc2, afra, func_00440F68(op_zsdc2));
    register_asmcode(zaddi, afrrr, op_zaddi);
    register_asmcode(zaddiu, afrrr, op_zaddiu);
    register_asmcode(zslti, afrrr, op_zslti);
    register_asmcode(zsltiu, afrrr, op_zsltiu);
    register_asmcode(zandi, afrrr, op_zandi);
    register_asmcode(zori, afrrr, op_zori);
    register_asmcode(zxori, afrrr, op_zxori);
    register_asmcode(zlui, afri, op_zlui);
    register_asmcode(zulw, afra, op_macro);
    register_asmcode(zulh, afra, op_macro);
    register_asmcode(zulhu, afra, op_macro);
    register_asmcode(zusw, afra, op_macro);
    register_asmcode(zush, afra, op_macro);
    register_asmcode(zdli, dli_dla, op_macro);
    register_asmcode(zdla, afra, op_macro);
    register_asmcode(zlgota, afra, op_macro);

    set_mips_inst_template(op_zadd, 16#00000020, mipsfmt_3);
    set_mips_inst_template(op_zaddi, 16#20000000, mipsfmt_0);
    set_mips_inst_template(op_zaddiu, 16#24000000, mipsfmt_0);
    set_mips_inst_template(op_zaddu, 16#00000021, mipsfmt_3);
    set_mips_inst_template(op_zand, 16#00000024, mipsfmt_3);
    set_mips_inst_template(op_zandi, 16#30000000, mipsfmt_0);
    set_mips_inst_template(op_zbc0f, 16#41000000, mipsfmt_2);
    set_mips_inst_template(op_zbc0t, 16#41010000, mipsfmt_2);
    set_mips_inst_template(op_zbc1f, 16#45000000, mipsfmt_2);
    set_mips_inst_template(op_zbc1t, 16#45010000, mipsfmt_2);
    set_mips_inst_template(op_zbc2f, 16#49000000, mipsfmt_2);
    set_mips_inst_template(op_zbc2t, 16#49010000, mipsfmt_2);
    set_mips_inst_template(op_zbc0fl, 16#41020000, mipsfmt_2);
    set_mips_inst_template(op_zbc0tl, 16#41030000, mipsfmt_2);
    set_mips_inst_template(op_zbc1fl, 16#45020000, mipsfmt_2);
    set_mips_inst_template(op_zbc1tl, 16#45030000, mipsfmt_2);
    set_mips_inst_template(op_zbc2fl, 16#49020000, mipsfmt_2);
    set_mips_inst_template(op_zbc2tl, 16#49030000, mipsfmt_2);
    set_mips_inst_template(op_zbeq, 16#10000000, mipsfmt_1);
    set_mips_inst_template(op_zbne, 16#14000000, mipsfmt_1);
    set_mips_inst_template(op_zblez, 16#18000000, mipsfmt_2);
    set_mips_inst_template(op_zbgtz, 16#1C000000, mipsfmt_2);
    set_mips_inst_template(op_zbltz, 16#04000000, mipsfmt_2);
    set_mips_inst_template(op_zbltzal, 16#04100000, mipsfmt_2);
    set_mips_inst_template(op_zbgez, 16#04010000, mipsfmt_2);
    set_mips_inst_template(op_zbgezal, 16#04110000, mipsfmt_2);
    set_mips_inst_template(op_zbeql, 16#50000000, mipsfmt_1);
    set_mips_inst_template(op_zbnel, 16#54000000, mipsfmt_1);
    set_mips_inst_template(op_zblezl, 16#58000000, mipsfmt_2);
    set_mips_inst_template(op_zbgtzl, 16#5C000000, mipsfmt_2);
    set_mips_inst_template(op_zbltzl, 16#04020000, mipsfmt_2);
    set_mips_inst_template(op_zbltzall, 16#04120000, mipsfmt_2);
    set_mips_inst_template(op_zbgezl, 16#04030000, mipsfmt_2);
    set_mips_inst_template(op_zbgezall, 16#04130000, mipsfmt_2);
    set_mips_inst_template(op_zbreak, 16#0000000D, mipsfmt_3);
    set_mips_inst_template(op_zc0, 16#42000000, mipsfmt_5);
    set_mips_inst_template(op_zc1, 16#46000000, mipsfmt_5);
    set_mips_inst_template(op_zc2, 16#4A000000, mipsfmt_5);
    set_mips_inst_template(op_zdiv, 16#0000001A, mipsfmt_3);
    set_mips_inst_template(op_zdivu, 16#0000001B, mipsfmt_3);
    set_mips_inst_template(op_zjal, 16#0C000000, mipsfmt_4);
    set_mips_inst_template(op_zjalr, 16#00000009, mipsfmt_3);
    set_mips_inst_template(op_zj, 16#08000000, mipsfmt_4);
    set_mips_inst_template(op_zjr, 16#00000008, mipsfmt_3);
    set_mips_inst_template(op_zlb, 16#80000000, mipsfmt_6);
    set_mips_inst_template(op_zlbu, 16#90000000, mipsfmt_6);
    set_mips_inst_template(op_zlh, 16#84000000, mipsfmt_6);
    set_mips_inst_template(op_zlhu, 16#94000000, mipsfmt_6);
    set_mips_inst_template(op_zlui, 16#3C000000, mipsfmt_0);
    set_mips_inst_template(op_zlw, 16#8C000000, mipsfmt_6);
    set_mips_inst_template(op_zld, 16#DC000000, mipsfmt_6);
    set_mips_inst_template(op_zll, 16#C0000000, mipsfmt_6);
    set_mips_inst_template(op_zlwc1, 16#C4000000, mipsfmt_6);
    set_mips_inst_template(op_zlwc2, 16#C8000000, mipsfmt_6);
    set_mips_inst_template(op_zlwl, 16#88000000, mipsfmt_6);
    set_mips_inst_template(op_zlwr, 16#98000000, mipsfmt_6);
    set_mips_inst_template(op_zmfhi, 16#00000010, mipsfmt_3);
    set_mips_inst_template(op_zmflo, 16#00000012, mipsfmt_3);
    set_mips_inst_template(op_zldc1, 16#D4000000, mipsfmt_6);
    set_mips_inst_template(op_zldc2, 16#D8000000, mipsfmt_6);
    set_mips_inst_template(op_zsdc1, 16#F4000000, mipsfmt_6);
    set_mips_inst_template(op_zsdc2, 16#F8000000, mipsfmt_6);
    set_mips_inst_template(op_zmfc0, 16#40000000, mipsfmt_5);
    set_mips_inst_template(op_zmfc1, 16#44000000, mipsfmt_5);
    set_mips_inst_template(op_zmfc2, 16#48000000, mipsfmt_5);
    set_mips_inst_template(op_zcfc0, 16#40400000, mipsfmt_5);
    set_mips_inst_template(op_zcfc1, 16#44400000, mipsfmt_5);
    set_mips_inst_template(op_zcfc2, 16#48400000, mipsfmt_5);
    set_mips_inst_template(op_zmtc0, 16#40800000, mipsfmt_5);
    set_mips_inst_template(op_zmtc1, 16#44800000, mipsfmt_5);
    set_mips_inst_template(op_zmtc2, 16#48800000, mipsfmt_5);
    set_mips_inst_template(op_zctc0, 16#40C00000, mipsfmt_5);
    set_mips_inst_template(op_zctc1, 16#44C00000, mipsfmt_5);
    set_mips_inst_template(op_zctc2, 16#48C00000, mipsfmt_5);
    set_mips_inst_template(op_zmthi, 16#00000011, mipsfmt_3);
    set_mips_inst_template(op_zmtlo, 16#00000013, mipsfmt_3);
    set_mips_inst_template(op_zmult, 16#00000018, mipsfmt_3);
    set_mips_inst_template(op_zmultu, 16#00000019, mipsfmt_3);
    set_mips_inst_template(op_znor, 16#00000027, mipsfmt_3);
    set_mips_inst_template(op_zor, 16#00000025, mipsfmt_3);
    set_mips_inst_template(op_zori, 16#34000000, mipsfmt_0);
    set_mips_inst_template(op_zrfe, 16#42000010, mipsfmt_5);
    set_mips_inst_template(op_ztlbr, 16#42000001, mipsfmt_5);
    set_mips_inst_template(op_ztlbwi, 16#42000002, mipsfmt_5);
    set_mips_inst_template(op_ztlbwr, 16#42000006, mipsfmt_5);
    set_mips_inst_template(op_ztlbp, 16#42000008, mipsfmt_5);
    set_mips_inst_template(op_ztlbr1, 16#43000001, mipsfmt_5);
    set_mips_inst_template(op_ztlbp1, 16#43000008, mipsfmt_5);
    set_mips_inst_template(op_zsync, 16#0000000F, mipsfmt_3);
    set_mips_inst_template(op_zsb, 16#A0000000, mipsfmt_6);
    set_mips_inst_template(op_zsh, 16#A4000000, mipsfmt_6);
    set_mips_inst_template(op_zsll, 16#00000000, mipsfmt_3);
    set_mips_inst_template(op_zsllv, 16#00000004, mipsfmt_3);
    set_mips_inst_template(op_zsub, 16#00000022, mipsfmt_3);
    set_mips_inst_template(op_zsubu, 16#00000023, mipsfmt_3);
    set_mips_inst_template(op_zslt, 16#0000002A, mipsfmt_3);
    set_mips_inst_template(op_zsltu, 16#0000002B, mipsfmt_3);
    set_mips_inst_template(op_ztge, 16#00000030, mipsfmt_3);
    set_mips_inst_template(op_ztgeu, 16#00000031, mipsfmt_3);
    set_mips_inst_template(op_ztlt, 16#00000032, mipsfmt_3);
    set_mips_inst_template(op_ztltu, 16#00000033, mipsfmt_3);
    set_mips_inst_template(op_zteq, 16#00000034, mipsfmt_3);
    set_mips_inst_template(op_ztne, 16#00000036, mipsfmt_3);
    set_mips_inst_template(op_ztgei, 16#04080000, mipsfmt_9);
    set_mips_inst_template(op_ztgeiu, 16#04090000, mipsfmt_9);
    set_mips_inst_template(op_ztlti, 16#040A0000, mipsfmt_9);
    set_mips_inst_template(op_ztltiu, 16#040B0000, mipsfmt_9);
    set_mips_inst_template(op_zteqi, 16#040C0000, mipsfmt_9);
    set_mips_inst_template(op_ztnei, 16#040E0000, mipsfmt_9);
    set_mips_inst_template(op_zslti, 16#28000000, mipsfmt_0);
    set_mips_inst_template(op_zsltiu, 16#2C000000, mipsfmt_0);
    set_mips_inst_template(op_zsra, 16#00000003, mipsfmt_3);
    set_mips_inst_template(op_zsrav, 16#00000007, mipsfmt_3);
    set_mips_inst_template(op_zsrl, 16#00000002, mipsfmt_3);
    set_mips_inst_template(op_zsrlv, 16#00000006, mipsfmt_3);
    set_mips_inst_template(op_zsw, 16#AC000000, mipsfmt_6);
    set_mips_inst_template(op_zsd, 16#FC000000, mipsfmt_6);
    set_mips_inst_template(op_zsc, 16#E0000000, mipsfmt_6);
    set_mips_inst_template(op_zswc1, 16#E4000000, mipsfmt_6);
    set_mips_inst_template(op_zswc2, 16#E8000000, mipsfmt_6);
    set_mips_inst_template(op_zswl, 16#A8000000, mipsfmt_6);
    set_mips_inst_template(op_zswr, 16#B8000000, mipsfmt_6);
    set_mips_inst_template(op_zsyscall, 16#0000000C, mipsfmt_3);
    set_mips_inst_template(op_zxor, 16#00000026, mipsfmt_3);
    set_mips_inst_template(op_zxori, 16#38000000, mipsfmt_0);

    register_asmcode(fli_s, afri_fp, op_fli_s);
    register_asmcode(fli_d, afri_fp, op_fli_d);
    register_asmcode(fli_e, afri_fp, op_fli_e);
    register_asmcode(fl_s, afra, op_macro);
    register_asmcode(fl_d, afra, op_macro);
    register_asmcode(fl_e, afra, op_macro);
    register_asmcode(fs_s, afra, op_macro);
    register_asmcode(fs_d, afra, op_macro);
    register_asmcode(fs_e, afra, op_macro);
    register_asmcode(fadd_s, afrrr, op_fadd_s);
    register_asmcode(fadd_d, afrrr, op_fadd_d);
    register_asmcode(fadd_e, afrrr, op_fadd_e);
    register_asmcode(fsub_s, afrrr, op_fsub_s);
    register_asmcode(fsub_d, afrrr, op_fsub_d);
    register_asmcode(fsub_e, afrrr, op_fsub_e);
    register_asmcode(fmul_s, afrrr, op_fmul_s);
    register_asmcode(fmul_d, afrrr, op_fmul_d);
    register_asmcode(fmul_e, afrrr, op_fmul_e);
    register_asmcode(fdiv_s, afrrr, op_fdiv_s);
    register_asmcode(fdiv_d, afrrr, op_fdiv_d);
    register_asmcode(fdiv_e, afrrr, op_fdiv_e);
    register_asmcode(fsqrt_s, afrrr, op_fsqrt_s);
    register_asmcode(fsqrt_d, afrrr, op_fsqrt_d);
    register_asmcode(fsqrt_e, afrrr, op_fsqrt_e);
    register_asmcode(fmov_s, afrrr, op_fmov_s);
    register_asmcode(fmov_d, afrrr, op_fmov_d);
    register_asmcode(fmov_e, afrrr, op_fmov_e);
    register_asmcode(fabs_s, afrrr, op_fabs_s);
    register_asmcode(fabs_d, afrrr, op_fabs_d);
    register_asmcode(fabs_e, afrrr, op_fabs_e);
    register_asmcode(fneg_s, afrrr, op_fneg_s);
    register_asmcode(fneg_d, afrrr, op_fneg_d);
    register_asmcode(fneg_e, afrrr, op_fneg_e);
    register_asmcode(fcvt_s_d, afrrr, op_fcvt_s_d);
    register_asmcode(fcvt_s_e, afrrr, op_fcvt_s_e);
    register_asmcode(fcvt_s_w, afrrr, op_fcvt_s_w);
    register_asmcode(fcvt_d_s, afrrr, op_fcvt_d_s);
    register_asmcode(fcvt_d_e, afrrr, op_fcvt_d_e);
    register_asmcode(fcvt_d_w, afrrr, op_fcvt_d_w);
    register_asmcode(fcvt_e_s, afrrr, op_fcvt_e_s);
    register_asmcode(fcvt_e_d, afrrr, op_fcvt_e_d);
    register_asmcode(fcvt_e_w, afrrr, op_fcvt_e_w);
    register_asmcode(fcvt_w_s, afrrr, op_fcvt_w_s);
    register_asmcode(fcvt_w_d, afrrr, op_fcvt_w_d);
    register_asmcode(fcvt_w_e, afrrr, op_fcvt_w_e);
    register_asmcode(fc_f_s, afrrr, op_fc_f_s);
    register_asmcode(fc_f_d, afrrr, op_fc_f_d);
    register_asmcode(fc_f_e, afrrr, op_fc_f_e);
    register_asmcode(fc_un_s, afrrr, op_fc_un_s);
    register_asmcode(fc_un_d, afrrr, op_fc_un_d);
    register_asmcode(fc_un_e, afrrr, op_fc_un_e);
    register_asmcode(fc_eq_s, afrrr, op_fc_eq_s);
    register_asmcode(fc_eq_d, afrrr, op_fc_eq_d);
    register_asmcode(fc_eq_e, afrrr, op_fc_eq_e);
    register_asmcode(fc_ueq_s, afrrr, op_fc_ueq_s);
    register_asmcode(fc_ueq_d, afrrr, op_fc_ueq_d);
    register_asmcode(fc_ueq_e, afrrr, op_fc_ueq_e);
    register_asmcode(fc_olt_s, afrrr, op_fc_olt_s);
    register_asmcode(fc_olt_d, afrrr, op_fc_olt_d);
    register_asmcode(fc_olt_e, afrrr, op_fc_olt_e);
    register_asmcode(fc_ult_s, afrrr, op_fc_ult_s);
    register_asmcode(fc_ult_d, afrrr, op_fc_ult_d);
    register_asmcode(fc_ult_e, afrrr, op_fc_ult_e);
    register_asmcode(fc_ole_s, afrrr, op_fc_ole_s);
    register_asmcode(fc_ole_d, afrrr, op_fc_ole_d);
    register_asmcode(fc_ole_e, afrrr, op_fc_ole_e);
    register_asmcode(fc_ule_s, afrrr, op_fc_ule_s);
    register_asmcode(fc_ule_d, afrrr, op_fc_ule_d);
    register_asmcode(fc_ule_e, afrrr, op_fc_ule_e);
    register_asmcode(fc_sf_s, afrrr, op_fc_sf_s);
    register_asmcode(fc_sf_d, afrrr, op_fc_sf_d);
    register_asmcode(fc_sf_e, afrrr, op_fc_sf_e);
    register_asmcode(fc_ngle_s, afrrr, op_fc_ngle_s);
    register_asmcode(fc_ngle_d, afrrr, op_fc_ngle_d);
    register_asmcode(fc_ngle_e, afrrr, op_fc_ngle_e);
    register_asmcode(fc_seq_s, afrrr, op_fc_seq_s);
    register_asmcode(fc_seq_d, afrrr, op_fc_seq_d);
    register_asmcode(fc_seq_e, afrrr, op_fc_seq_e);
    register_asmcode(fc_ngl_s, afrrr, op_fc_ngl_s);
    register_asmcode(fc_ngl_d, afrrr, op_fc_ngl_d);
    register_asmcode(fc_ngl_e, afrrr, op_fc_ngl_e);
    register_asmcode(fc_lt_s, afrrr, op_fc_lt_s);
    register_asmcode(fc_lt_d, afrrr, op_fc_lt_d);
    register_asmcode(fc_lt_e, afrrr, op_fc_lt_e);
    register_asmcode(fc_nge_s, afrrr, op_fc_nge_s);
    register_asmcode(fc_nge_d, afrrr, op_fc_nge_d);
    register_asmcode(fc_nge_e, afrrr, op_fc_nge_e);
    register_asmcode(fc_le_s, afrrr, op_fc_le_s);
    register_asmcode(fc_le_d, afrrr, op_fc_le_d);
    register_asmcode(fc_le_e, afrrr, op_fc_le_e);
    register_asmcode(fc_ngt_s, afrrr, op_fc_ngt_s);
    register_asmcode(fc_ngt_d, afrrr, op_fc_ngt_d);
    register_asmcode(fc_ngt_e, afrrr, op_fc_ngt_e);
    if (isa >= ISA_MIPS2) then begin
        register_asmcode(zround_w_s, afrrr, op_zround_w_s);
        register_asmcode(zround_w_d, afrrr, op_zround_w_d);
        register_asmcode(zround_w_e, afrrr, op_zround_w_e);
        register_asmcode(zroundu_w_s, afrrr, op_zround_w_s);
        register_asmcode(zroundu_w_d, afrrr, op_zround_w_d);
        register_asmcode(zroundu_w_e, afrrr, op_zround_w_e);
        register_asmcode(ztrunc_w_s, afrrr, op_ztrunc_w_s);
        register_asmcode(ztrunc_w_d, afrrr, op_ztrunc_w_d);
        register_asmcode(ztrunc_w_e, afrrr, op_ztrunc_w_e);
        register_asmcode(ztruncu_w_s, afrrr, op_ztrunc_w_s);
        register_asmcode(ztruncu_w_d, afrrr, op_ztrunc_w_d);
        register_asmcode(ztruncu_w_e, afrrr, op_ztrunc_w_e);
        register_asmcode(zceil_w_s, afrrr, op_zceil_w_s);
        register_asmcode(zceil_w_d, afrrr, op_zceil_w_d);
        register_asmcode(zceil_w_e, afrrr, op_zceil_w_e);
        register_asmcode(zceilu_w_s, afrrr, op_zceil_w_s);
        register_asmcode(zceilu_w_d, afrrr, op_zceil_w_d);
        register_asmcode(zceilu_w_e, afrrr, op_zceil_w_e);
        register_asmcode(zfloor_w_s, afrrr, op_zfloor_w_s);
        register_asmcode(zfloor_w_d, afrrr, op_zfloor_w_d);
        register_asmcode(zfloor_w_e, afrrr, op_zfloor_w_e);
        register_asmcode(zflooru_w_s, afrrr, op_zfloor_w_s);
        register_asmcode(zflooru_w_d, afrrr, op_zfloor_w_d);
        register_asmcode(zflooru_w_e, afrrr, op_zfloor_w_e);
    end else begin
        register_asmcode(zround_w_s, afrrr, op_fcvt_w_s);
        register_asmcode(zround_w_d, afrrr, op_fcvt_w_d);
        register_asmcode(zround_w_e, afrrr, op_fcvt_w_e);
        register_asmcode(zroundu_w_s, afrrr, op_fcvt_w_s);
        register_asmcode(zroundu_w_d, afrrr, op_fcvt_w_d);
        register_asmcode(zroundu_w_e, afrrr, op_fcvt_w_e);
        register_asmcode(ztrunc_w_s, afrrr, op_fcvt_w_s);
        register_asmcode(ztrunc_w_d, afrrr, op_fcvt_w_d);
        register_asmcode(ztrunc_w_e, afrrr, op_fcvt_w_e);
        register_asmcode(ztruncu_w_s, afrrr, op_fcvt_w_s);
        register_asmcode(ztruncu_w_d, afrrr, op_fcvt_w_d);
        register_asmcode(ztruncu_w_e, afrrr, op_fcvt_w_e);
        register_asmcode(zceil_w_s, afrrr, op_fcvt_w_s);
        register_asmcode(zceil_w_d, afrrr, op_fcvt_w_d);
        register_asmcode(zceil_w_e, afrrr, op_fcvt_w_e);
        register_asmcode(zceilu_w_s, afrrr, op_fcvt_w_s);
        register_asmcode(zceilu_w_d, afrrr, op_fcvt_w_d);
        register_asmcode(zceilu_w_e, afrrr, op_fcvt_w_e);
        register_asmcode(zfloor_w_s, afrrr, op_fcvt_w_s);
        register_asmcode(zfloor_w_d, afrrr, op_fcvt_w_d);
        register_asmcode(zfloor_w_e, afrrr, op_fcvt_w_e);
        register_asmcode(zflooru_w_s, afrrr, op_fcvt_w_s);
        register_asmcode(zflooru_w_d, afrrr, op_fcvt_w_d);
        register_asmcode(zflooru_w_e, afrrr, op_fcvt_w_e);
    end;
    register_asmcode(ztlt, afrrr, op_ztlt);
    register_asmcode(ztltu, afrrr, op_ztltu);
    register_asmcode(ztge, afrrr, op_ztge);
    register_asmcode(ztgeu, afrrr, op_ztgeu);
    register_asmcode(zteq, afrrr, op_zteq);
    register_asmcode(ztne, afrrr, op_ztne);

    set_mips_inst_template(op_fadd_s, 16#46000000, mipsfmt_8);
    set_mips_inst_template(op_fadd_d, 16#46200000, mipsfmt_8);
    set_mips_inst_template(op_fadd_e, 16#46400000, mipsfmt_8);
    set_mips_inst_template(op_fsub_s, 16#46000001, mipsfmt_8);
    set_mips_inst_template(op_fsub_d, 16#46200001, mipsfmt_8);
    set_mips_inst_template(op_fsub_e, 16#46400001, mipsfmt_8);
    set_mips_inst_template(op_fmul_s, 16#46000002, mipsfmt_8);
    set_mips_inst_template(op_fmul_d, 16#46200002, mipsfmt_8);
    set_mips_inst_template(op_fmul_e, 16#46400002, mipsfmt_8);
    set_mips_inst_template(op_fdiv_s, 16#46000003, mipsfmt_8);
    set_mips_inst_template(op_fdiv_d, 16#46200003, mipsfmt_8);
    set_mips_inst_template(op_fdiv_e, 16#46400003, mipsfmt_8);
    set_mips_inst_template(op_fsqrt_s, 16#46000004, mipsfmt_8);
    set_mips_inst_template(op_fsqrt_d, 16#46200004, mipsfmt_8);
    set_mips_inst_template(op_fsqrt_e, 16#46400004, mipsfmt_8);
    set_mips_inst_template(op_fabs_s, 16#46000005, mipsfmt_8);
    set_mips_inst_template(op_fabs_d, 16#46200005, mipsfmt_8);
    set_mips_inst_template(op_fabs_e, 16#46400005, mipsfmt_8);
    set_mips_inst_template(op_fneg_s, 16#46000007, mipsfmt_8);
    set_mips_inst_template(op_fneg_d, 16#46200007, mipsfmt_8);
    set_mips_inst_template(op_fneg_e, 16#46400007, mipsfmt_8);
    set_mips_inst_template(op_fmov_s, 16#46000006, mipsfmt_8);
    set_mips_inst_template(op_fmov_d, 16#46200006, mipsfmt_8);
    set_mips_inst_template(op_fmov_e, 16#46400006, mipsfmt_8);
    set_mips_inst_template(op_fcvt_s_d, 16#46200020, mipsfmt_8);
    set_mips_inst_template(op_fcvt_s_e, 16#46400020, mipsfmt_8);
    set_mips_inst_template(op_fcvt_s_w, 16#46800020, mipsfmt_8);
    set_mips_inst_template(op_fcvt_d_s, 16#46000021, mipsfmt_8);
    set_mips_inst_template(op_fcvt_d_e, 16#46400021, mipsfmt_8);
    set_mips_inst_template(op_fcvt_d_w, 16#46800021, mipsfmt_8);
    set_mips_inst_template(op_fcvt_e_s, 16#46000022, mipsfmt_8);
    set_mips_inst_template(op_fcvt_e_d, 16#46200022, mipsfmt_8);
    set_mips_inst_template(op_fcvt_e_w, 16#46800022, mipsfmt_8);
    set_mips_inst_template(op_fcvt_w_s, 16#46000024, mipsfmt_8);
    set_mips_inst_template(op_fcvt_w_d, 16#46200024, mipsfmt_8);
    set_mips_inst_template(op_fcvt_w_e, 16#46400024, mipsfmt_8);
    set_mips_inst_template(op_fc_f_s, 16#46000030, mipsfmt_8);
    set_mips_inst_template(op_fc_f_d, 16#46200030, mipsfmt_8);
    set_mips_inst_template(op_fc_f_e, 16#46400030, mipsfmt_8);
    set_mips_inst_template(op_fc_un_s, 16#46000031, mipsfmt_8);
    set_mips_inst_template(op_fc_un_d, 16#46200031, mipsfmt_8);
    set_mips_inst_template(op_fc_un_e, 16#46400031, mipsfmt_8);
    set_mips_inst_template(op_fc_eq_s, 16#46000032, mipsfmt_8);
    set_mips_inst_template(op_fc_eq_d, 16#46200032, mipsfmt_8);
    set_mips_inst_template(op_fc_eq_e, 16#46400032, mipsfmt_8);
    set_mips_inst_template(op_fc_ueq_s, 16#46000033, mipsfmt_8);
    set_mips_inst_template(op_fc_ueq_d, 16#46200033, mipsfmt_8);
    set_mips_inst_template(op_fc_ueq_e, 16#46400033, mipsfmt_8);
    set_mips_inst_template(op_fc_olt_s, 16#46000034, mipsfmt_8);
    set_mips_inst_template(op_fc_olt_d, 16#46200034, mipsfmt_8);
    set_mips_inst_template(op_fc_olt_e, 16#46400034, mipsfmt_8);
    set_mips_inst_template(op_fc_ult_s, 16#46000035, mipsfmt_8);
    set_mips_inst_template(op_fc_ult_d, 16#46200035, mipsfmt_8);
    set_mips_inst_template(op_fc_ult_e, 16#46400035, mipsfmt_8);
    set_mips_inst_template(op_fc_ole_s, 16#46000036, mipsfmt_8);
    set_mips_inst_template(op_fc_ole_d, 16#46200036, mipsfmt_8);
    set_mips_inst_template(op_fc_ole_e, 16#46400036, mipsfmt_8);
    set_mips_inst_template(op_fc_ule_s, 16#46000037, mipsfmt_8);
    set_mips_inst_template(op_fc_ule_d, 16#46200037, mipsfmt_8);
    set_mips_inst_template(op_fc_ule_e, 16#46400037, mipsfmt_8);
    set_mips_inst_template(op_fc_sf_s, 16#46000038, mipsfmt_8);
    set_mips_inst_template(op_fc_sf_d, 16#46200038, mipsfmt_8);
    set_mips_inst_template(op_fc_sf_e, 16#46400038, mipsfmt_8);
    set_mips_inst_template(op_fc_ngle_s, 16#46000039, mipsfmt_8);
    set_mips_inst_template(op_fc_ngle_d, 16#46200039, mipsfmt_8);
    set_mips_inst_template(op_fc_ngle_e, 16#46400039, mipsfmt_8);
    set_mips_inst_template(op_fc_seq_s, 16#4600003A, mipsfmt_8);
    set_mips_inst_template(op_fc_seq_d, 16#4620003A, mipsfmt_8);
    set_mips_inst_template(op_fc_seq_e, 16#4640003A, mipsfmt_8);
    set_mips_inst_template(op_fc_ngl_s, 16#4600003B, mipsfmt_8);
    set_mips_inst_template(op_fc_ngl_d, 16#4620003B, mipsfmt_8);
    set_mips_inst_template(op_fc_ngl_e, 16#4640003B, mipsfmt_8);
    set_mips_inst_template(op_fc_lt_s, 16#4600003C, mipsfmt_8);
    set_mips_inst_template(op_fc_lt_d, 16#4620003C, mipsfmt_8);
    set_mips_inst_template(op_fc_lt_e, 16#4640003C, mipsfmt_8);
    set_mips_inst_template(op_fc_nge_s, 16#4600003D, mipsfmt_8);
    set_mips_inst_template(op_fc_nge_d, 16#4620003D, mipsfmt_8);
    set_mips_inst_template(op_fc_nge_e, 16#4640003D, mipsfmt_8);
    set_mips_inst_template(op_fc_le_s, 16#4600003E, mipsfmt_8);
    set_mips_inst_template(op_fc_le_d, 16#4620003E, mipsfmt_8);
    set_mips_inst_template(op_fc_le_e, 16#4640003E, mipsfmt_8);
    set_mips_inst_template(op_fc_ngt_s, 16#4600003F, mipsfmt_8);
    set_mips_inst_template(op_fc_ngt_d, 16#4620003F, mipsfmt_8);
    set_mips_inst_template(op_fc_ngt_e, 16#4640003F, mipsfmt_8);
    set_mips_inst_template(op_zround_w_s, 16#4600000C, mipsfmt_8);
    set_mips_inst_template(op_zround_w_d, 16#4620000C, mipsfmt_8);
    set_mips_inst_template(op_zround_w_e, 16#4640000C, mipsfmt_8);
    set_mips_inst_template(op_ztrunc_w_s, 16#4600000D, mipsfmt_8);
    set_mips_inst_template(op_ztrunc_w_d, 16#4620000D, mipsfmt_8);
    set_mips_inst_template(op_ztrunc_w_e, 16#4640000D, mipsfmt_8);
    set_mips_inst_template(op_zceil_w_s, 16#4600000E, mipsfmt_8);
    set_mips_inst_template(op_zceil_w_d, 16#4620000E, mipsfmt_8);
    set_mips_inst_template(op_zceil_w_e, 16#4640000E, mipsfmt_8);
    set_mips_inst_template(op_zfloor_w_s, 16#4600000F, mipsfmt_8);
    set_mips_inst_template(op_zfloor_w_d, 16#4620000F, mipsfmt_8);
    set_mips_inst_template(op_zfloor_w_e, 16#4640000F, mipsfmt_8);
    set_mips_inst_template(op_fli_s, 16#46000026, mipsfmt_8);
    set_mips_inst_template(op_fli_d, 16#46200026, mipsfmt_8);
    set_mips_inst_template(op_fli_e, 16#46400026, mipsfmt_8);

    register_asmcode(zldl, afra, op_zldl);
    register_asmcode(zldr, afra, op_zldr);
    register_asmcode(zlld, afra, op_zlld);
    register_asmcode(zsdl, afra, op_zsdl);
    register_asmcode(zsdr, afra, op_zsdr);
    register_asmcode(zscd, afra, op_zscd);
    register_asmcode(zdaddi, afrrr, op_zdaddi);
    register_asmcode(zdaddiu, afrrr, op_zdaddiu);
    register_asmcode(zdadd, afrrr, op_zdadd);
    register_asmcode(zdaddu, afrrr, op_zdaddu);
    register_asmcode(zdsub, afrrr, op_zdsub);
    register_asmcode(zdsubu, afrrr, op_zdsubu);
    register_asmcode(zdsll, afrrr, op_zdsll);
    register_asmcode(zdsrl, afrrr, op_zdsrl);
    register_asmcode(zdsra, afrrr, op_zdsra);
    register_asmcode(zdsllv, afrrr, op_zdsllv);
    register_asmcode(zdsrlv, afrrr, op_zdsrlv);
    register_asmcode(zdsrav, afrrr, op_zdsrav);
    register_asmcode(zdmult, afrr, op_zdmult);
    register_asmcode(zdmultu, afrr, op_zdmultu);
    register_asmcode(zddiv, afrrr, op_zddiv);
    register_asmcode(zddivu, afrrr, op_zddivu);
    register_asmcode(zlsc1, afra, op_zlsc1);
    register_asmcode(zssc1, afra, op_zssc1);
    register_asmcode(zdmtc1, afrr, op_zdmtc1);
    register_asmcode(zdmfc1, afrr, op_zdmfc1);
    register_asmcode(zdmtc0, afrr, op_zdmtc0);
    register_asmcode(zdmfc0, afrr, op_zdmfc0);
    register_asmcode(zdmtc2, afrr, op_zdmtc2);
    register_asmcode(zdmfc2, afrr, op_zdmfc2);
    register_asmcode(zlwu, afra, op_zlwu);
    register_asmcode(zeret, af, op_zeret);
    register_asmcode(fcvt_l_s, afrrr, op_fcvt_l_s);
    register_asmcode(fcvt_l_d, afrrr, op_fcvt_l_d);
    register_asmcode(fcvt_l_e, afrrr, op_fcvt_l_e);
    register_asmcode(fcvt_l_w, afrrr, op_fcvt_l_w);
    register_asmcode(fcvt_s_l, afrrr, op_fcvt_s_l);
    register_asmcode(fcvt_d_l, afrrr, op_fcvt_d_l);
    register_asmcode(fcvt_e_l, afrrr, op_fcvt_e_l);
    register_asmcode(fcvt_w_l, afrrr, op_fcvt_w_l);
    register_asmcode(zround_l_s, afrrr, op_zround_l_s);
    register_asmcode(ztrunc_l_s, afrrr, op_ztrunc_l_s);
    register_asmcode(zceil_l_s, afrrr, op_zceil_l_s);
    register_asmcode(zfloor_l_s, afrrr, op_zfloor_l_s);
    register_asmcode(zround_l_d, afrrr, op_zround_l_d);
    register_asmcode(ztrunc_l_d, afrrr, op_ztrunc_l_d);
    register_asmcode(zceil_l_d, afrrr, op_zceil_l_d);
    register_asmcode(zfloor_l_d, afrrr, op_zfloor_l_d);
    register_asmcode(zround_l_e, afrrr, op_zround_l_e);
    register_asmcode(ztrunc_l_e, afrrr, op_ztrunc_l_e);
    register_asmcode(zceil_l_e, afrrr, op_zceil_l_e);
    register_asmcode(zfloor_l_e, afrrr, op_zfloor_l_e);
    register_asmcode(zcache, afra, op_zcache);
    register_asmcode(zuld, afra, op_macro);
    register_asmcode(zusd, afra, op_macro);
    register_asmcode(zdabs, afrr, op_macro);
    register_asmcode(zdneg, afrr, op_macro);
    register_asmcode(zdnegu, afrr, op_macro);
    register_asmcode(zdmul, afrrr, op_macro);
    register_asmcode(zdmulo, afrrr, op_macro);
    register_asmcode(zdmulou, afrrr, op_macro);
    register_asmcode(zdrem, afrrr, op_zddiv);
    register_asmcode(zdremu, afrrr, op_zddivu);
    register_asmcode(zdrol, afrrr, op_macro);
    register_asmcode(zdror, afrrr, op_macro);
    register_asmcode(zdaddou, afrrr, op_zdaddu);
    register_asmcode(zdsubou, afrrr, op_zdsubu);
    register_asmcode(zulwu, afra, op_macro);
    register_asmcode(zmovf, afrrr, op_zmovf);
    register_asmcode(zmovt, afrrr, op_zmovt);
    register_asmcode(zmovn, afrrr, op_zmovn);
    register_asmcode(zmovz, afrrr, op_zmovz);
    register_asmcode(fmadd_s, afrrrr, op_fmadd_s);
    register_asmcode(fmadd_d, afrrrr, op_fmadd_d);
    register_asmcode(fmadd_e, afrrrr, op_fmadd_e);
    register_asmcode(fmsub_s, afrrrr, op_fmsub_s);
    register_asmcode(fmsub_d, afrrrr, op_fmsub_d);
    register_asmcode(fmsub_e, afrrrr, op_fmsub_e);
    register_asmcode(fnmadd_s, afrrrr, op_fnmadd_s);
    register_asmcode(fnmadd_d, afrrrr, op_fnmadd_d);
    register_asmcode(fnmadd_e, afrrrr, op_fnmadd_e);
    register_asmcode(fnmsub_s, afrrrr, op_fnmsub_s);
    register_asmcode(fnmsub_d, afrrrr, op_fnmsub_d);
    register_asmcode(fnmsub_e, afrrrr, op_fnmsub_e);
    register_asmcode(frecip_s, afrrr, op_frecip_s);
    register_asmcode(frecip_d, afrrr, op_frecip_d);
    register_asmcode(frsqrt_s, afrrr, op_frsqrt_s);
    register_asmcode(frsqrt_d, afrrr, op_frsqrt_d);
    register_asmcode(fmovf_s, afrrr, op_fmovf_s);
    register_asmcode(fmovf_d, afrrr, op_fmovf_d);
    register_asmcode(fmovt_s, afrrr, op_fmovt_s);
    register_asmcode(fmovt_d, afrrr, op_fmovt_d);
    register_asmcode(fmovn_s, afrrr, op_fmovn_s);
    register_asmcode(fmovn_d, afrrr, op_fmovn_d);
    register_asmcode(fmovz_s, afrrr, op_fmovz_s);
    register_asmcode(fmovz_d, afrrr, op_fmovz_d);
    register_asmcode(zlwxc1, afrrr, op_zlwxc1);
    register_asmcode(zldxc1, afrrr, op_zldxc1);
    register_asmcode(zswxc1, afrrr, op_zswxc1);
    register_asmcode(zsdxc1, afrrr, op_zsdxc1);
    register_asmcode(zpfetch, afrrr, op_zpfetch);
    register_asmcode(zpref, afra, op_zpref);
    register_asmcode(zdctr, af, op_zdctr);
    register_asmcode(zdctw, af, op_zdctw);
    register_asmcode(ztlbw, af, op_ztlbw);

    set_mips_inst_template(op_zeret, 16#42000018, mipsfmt_5);
    set_mips_inst_template(op_fcvt_l_s, 16#46000025, mipsfmt_8);
    set_mips_inst_template(op_fcvt_l_d, 16#46200025, mipsfmt_8);
    set_mips_inst_template(op_fcvt_l_e, 16#46400025, mipsfmt_8);
    set_mips_inst_template(op_fcvt_l_w, 16#46800025, mipsfmt_8);
    set_mips_inst_template(op_fcvt_s_l, 16#46A00020, mipsfmt_8);
    set_mips_inst_template(op_fcvt_d_l, 16#46A00021, mipsfmt_8);
    set_mips_inst_template(op_fcvt_e_l, 16#46A00022, mipsfmt_8);
    set_mips_inst_template(op_fcvt_w_l, 16#46A00024, mipsfmt_8);
    set_mips_inst_template(op_zround_l_s, 16#46000008, mipsfmt_8);
    set_mips_inst_template(op_ztrunc_l_s, 16#46000009, mipsfmt_8);
    set_mips_inst_template(op_zceil_l_s, 16#4600000A, mipsfmt_8);
    set_mips_inst_template(op_zfloor_l_s, 16#4600000B, mipsfmt_8);
    set_mips_inst_template(op_zround_l_d, 16#46200008, mipsfmt_8);
    set_mips_inst_template(op_ztrunc_l_d, 16#46200009, mipsfmt_8);
    set_mips_inst_template(op_zceil_l_d, 16#4620000A, mipsfmt_8);
    set_mips_inst_template(op_zfloor_l_d, 16#4620000B, mipsfmt_8);
    set_mips_inst_template(op_zround_l_e, 16#46400008, mipsfmt_8);
    set_mips_inst_template(op_ztrunc_l_e, 16#46400009, mipsfmt_8);
    set_mips_inst_template(op_zceil_l_e, 16#4640000A, mipsfmt_8);
    set_mips_inst_template(op_zfloor_l_e, 16#4640000B, mipsfmt_8);
    set_mips_inst_template(op_zldl, 16#68000000, mipsfmt_6);
    set_mips_inst_template(op_zldr, 16#6C000000, mipsfmt_6);
    set_mips_inst_template(op_zlld, 16#D0000000, mipsfmt_6);
    set_mips_inst_template(op_zsdl, 16#B0000000, mipsfmt_6);
    set_mips_inst_template(op_zsdr, 16#B4000000, mipsfmt_6);
    set_mips_inst_template(op_zscd, 16#F0000000, mipsfmt_6);
    set_mips_inst_template(op_zdaddi, 16#60000000, mipsfmt_0);
    set_mips_inst_template(op_zdaddiu, 16#64000000, mipsfmt_0);
    set_mips_inst_template(op_zdadd, 16#0000002C, mipsfmt_3);
    set_mips_inst_template(op_zdaddu, 16#0000002D, mipsfmt_3);
    set_mips_inst_template(op_zdsub, 16#0000002E, mipsfmt_3);
    set_mips_inst_template(op_zdsubu, 16#0000002F, mipsfmt_3);
    set_mips_inst_template(op_zdsll, 16#00000038, mipsfmt_3);
    set_mips_inst_template(op_zdsrl, 16#0000003A, mipsfmt_3);
    set_mips_inst_template(op_zdsra, 16#0000003B, mipsfmt_3);
    set_mips_inst_template(op_zdsll32, 16#0000003C, mipsfmt_3);
    set_mips_inst_template(op_zdsrl32, 16#0000003E, mipsfmt_3);
    set_mips_inst_template(op_zdsra32, 16#0000003F, mipsfmt_3);
    set_mips_inst_template(op_zdsllv, 16#00000014, mipsfmt_3);
    set_mips_inst_template(op_zdsrlv, 16#00000016, mipsfmt_3);
    set_mips_inst_template(op_zdsrav, 16#00000017, mipsfmt_3);
    set_mips_inst_template(op_zdmult, 16#0000001C, mipsfmt_3);
    set_mips_inst_template(op_zdmultu, 16#0000001D, mipsfmt_3);
    set_mips_inst_template(op_zddiv, 16#0000001E, mipsfmt_3);
    set_mips_inst_template(op_zddivu, 16#0000001F, mipsfmt_3);
    set_mips_inst_template(op_zlsc1, 16#CC000000, mipsfmt_6);
    set_mips_inst_template(op_zssc1, 16#EC000000, mipsfmt_6);
    set_mips_inst_template(op_zdmtc1, 16#44A00000, mipsfmt_5);
    set_mips_inst_template(op_zdmfc1, 16#44200000, mipsfmt_5);
    set_mips_inst_template(op_zdmtc0, 16#40A00000, mipsfmt_5);
    set_mips_inst_template(op_zdmfc0, 16#40200000, mipsfmt_5);
    set_mips_inst_template(op_zdmtc2, 16#48A00000, mipsfmt_5);
    set_mips_inst_template(op_zdmfc2, 16#48200000, mipsfmt_5);
    set_mips_inst_template(op_zlwu, 16#9C000000, mipsfmt_6);
    set_mips_inst_template(op_zcache, 16#BC000000, mipsfmt_10);
    set_mips_inst_template(op_zmovf, 16#00000001, mipsfmt_5);
    set_mips_inst_template(op_zmovt, 16#00010001, mipsfmt_5);
    set_mips_inst_template(op_zmovz, 16#0000000A, mipsfmt_5);
    set_mips_inst_template(op_zmovn, 16#0000000B, mipsfmt_5);
    set_mips_inst_template(op_fmadd_s, 16#4C000020, mipsfmt_8);
    set_mips_inst_template(op_fmadd_d, 16#4C000021, mipsfmt_8);
    set_mips_inst_template(op_fmadd_e, 16#4C000022, mipsfmt_8);
    set_mips_inst_template(op_fmsub_s, 16#4C000028, mipsfmt_8);
    set_mips_inst_template(op_fmsub_d, 16#4C000029, mipsfmt_8);
    set_mips_inst_template(op_fmsub_e, 16#4C00002A, mipsfmt_8);
    set_mips_inst_template(op_fnmadd_s, 16#4C000030, mipsfmt_8);
    set_mips_inst_template(op_fnmadd_d, 16#4C000031, mipsfmt_8);
    set_mips_inst_template(op_fnmadd_e, 16#4C000032, mipsfmt_8);
    set_mips_inst_template(op_fnmsub_s, 16#4C000038, mipsfmt_8);
    set_mips_inst_template(op_fnmsub_d, 16#4C000039, mipsfmt_8);
    set_mips_inst_template(op_fnmsub_e, 16#4C00003A, mipsfmt_8);
    set_mips_inst_template(op_frecip_s, 16#46000015, mipsfmt_8);
    set_mips_inst_template(op_frecip_d, 16#46200015, mipsfmt_8);
    set_mips_inst_template(op_frsqrt_s, 16#46000016, mipsfmt_8);
    set_mips_inst_template(op_frsqrt_d, 16#46200016, mipsfmt_8);
    set_mips_inst_template(op_fmovf_s, 16#46000011, mipsfmt_8);
    set_mips_inst_template(op_fmovf_d, 16#46200011, mipsfmt_8);
    set_mips_inst_template(op_fmovt_s, 16#46010011, mipsfmt_8);
    set_mips_inst_template(op_fmovt_d, 16#46210011, mipsfmt_8);
    set_mips_inst_template(op_fmovz_s, 16#46000012, mipsfmt_8);
    set_mips_inst_template(op_fmovz_d, 16#46200012, mipsfmt_8);
    set_mips_inst_template(op_fmovn_s, 16#46000013, mipsfmt_8);
    set_mips_inst_template(op_fmovn_d, 16#46200013, mipsfmt_8);
    set_mips_inst_template(op_zlwxc1, 16#4C000000, mipsfmt_5);
    set_mips_inst_template(op_zldxc1, 16#4C000001, mipsfmt_5);
    set_mips_inst_template(op_zswxc1, 16#4C000008, mipsfmt_5);
    set_mips_inst_template(op_zsdxc1, 16#4C000009, mipsfmt_5);
    set_mips_inst_template(op_zpfetch, 16#4C00000F, mipsfmt_5);
    set_mips_inst_template(op_zpref, 16#CC000000, mipsfmt_6);
    set_mips_inst_template(op_zdctr, 16#43000009, mipsfmt_5);
    set_mips_inst_template(op_zdctw, 16#4300000A, mipsfmt_5);
    set_mips_inst_template(op_ztlbw, 16#43000002, mipsfmt_5);

    register_asmcode(zbc3f, afl, op_zbc3f);
    register_asmcode(zbc3t, afl, op_zbc3t);
    register_asmcode(zc3, aforrr, op_zc3);
    register_asmcode(zlwc3, afra, op_zlwc3);
    register_asmcode(zswc3, afra, op_zswc3);
    register_asmcode(zmfc3, afrr, op_zmfc3);
    register_asmcode(zmtc3, afrr, op_zmtc3);
    register_asmcode(zcfc3, afrr, op_zcfc3);
    register_asmcode(zctc3, afrr, op_zctc3);

    set_mips_inst_template(op_zbc3f, 16#4D000000, mipsfmt_2);
    set_mips_inst_template(op_zbc3t, 16#4D010000, mipsfmt_2);
    set_mips_inst_template(op_zc3, 16#4E000000, mipsfmt_5);
    set_mips_inst_template(op_zlwc3, 16#CC000000, mipsfmt_6);
    set_mips_inst_template(op_zswc3, 16#EC000000, mipsfmt_6);
    set_mips_inst_template(op_zmfc3, 16#4C000000, mipsfmt_5);
    set_mips_inst_template(op_zmtc3, 16#4C800000, mipsfmt_5);
    set_mips_inst_template(op_zcfc3, 16#4C400000, mipsfmt_5);
    set_mips_inst_template(op_zctc3, 16#4CC00000, mipsfmt_5);

    register_asmcode(zmfpc, afrr, op_zmfpc);
    register_asmcode(zmtpc, afrr, op_zmtpc);
    register_asmcode(zmfps, afrr, op_zmfps);
    register_asmcode(zmtps, afrr, op_zmtps);

    set_mips_inst_template(op_zmfpc, 16#4000C801, mipsfmt_5);
    set_mips_inst_template(op_zmtpc, 16#4080C801, mipsfmt_5);
    set_mips_inst_template(op_zmfps, 16#4000C800, mipsfmt_5);
    set_mips_inst_template(op_zmtps, 16#4080C800, mipsfmt_5);
    
    regnum[xnoreg] := 0;
    for j := 0 to 31 do begin
        regnum[registers(j)] := j;
    end;
    for j := 32 to 63 do begin
        regnum[registers(j)] := j - 32;
    end;

    gpreg := xr28;
    knownregs := [xr0, xr28, xr29];
    bbindex := 0;
    shftaddr := 0;

    if not func_00440E8C() then begin
        PostError("Preparing gp-tables", emptystring, ErrorLevel_0);
    end;

    init_j_def_live();
end;

procedure func_00449724();
var
    i: integer;
begin
    bbindex := 0;
    init_inst_heap();
    lastsegment := currsegment;
    if not(currsegment in realsegments) then begin
        p_assertion_failed("CurrSegment in realsegments\0", "as1main.p", 1637);
    end;
    lastic := seg_ic.data^[currsegmentindex];
    pre_reorder_peepholes.unk_00 := -1;
    pre_reorder_peepholes.unk_10 := -1;
    for i := 1 to 32 do begin
        pre_reorder_peepholes.unk_14[i] := chr(0);
    end;        
    endofbasicb := false;
end;



procedure func_00449B98();
var
    i: integer;
    procedure func_004498E8(arg0: ^UnkAlpha; arg1: integer);
    var
        v0: integer;
        s1: ^UnkKappa;
        a0: ^UnkKappa;
    begin
        if (arg0 <> nil) and not arg0^.unk37 then begin
            if (arg0^.unk2C <> nil) then begin
                currentline := arg0^.currline;
                currentfile := arg0^.currfile;
                if (arg0^.unk0C.f^[1] <> chr(0)) then begin
                    if ((arg0^.unk0C.f^[1] >= '0') and (arg0^.unk0C.f^[1] <= '9')) then begin
                        v0 := 1;
                        while (v0 <= 1024) and (arg0^.unk0C.f^[v0] <> '$') do begin
                            v0 := v0 + 1;
                        end;
                        if (arg0^.unk0C.f^[v0] = '$') then
                            arg0^.unk0C.f^[v0] := chr(0);
                    end else begin
                        s1 := arg0^.unk2C;
                        fixup_count := fixup_count - 1;
                        while (s1 <> nil) do begin
                            if (nextrld >= rld_list.size) then begin
                                rld_list.data := grow_array(rld_list.size, nextrld, sizeof(RldRec), rld_list.data, false);
                            end;
                            
                            rld_list.data^[nextrld].unk00 := 0;
                            rld_list.data^[nextrld].unk04 := s1^.unk00;
                            rld_list.data^[nextrld].unk10 := 17;
                            rld_list.data^[nextrld].unk08 := arg0;                            
                            nextrld := nextrld + 1;
                            arg0^.unk20 := arg0^.unk20 + 1;
                            a0 := s1;
                            s1 := s1^.next;
                            dispose(a0);
                        end;
                    end;
                end else begin
                    new(arg0^.unk0C.o);
                    ltoa(arg1, arg0^.unk0C.c);
                end;
                PostError("Label referenced but not defined", arg0^.unk0C, ErrorLevel_1);
            end;
        end;
    end;
begin
    PostError("Not all branch-label symbols were defined", emptystring, ErrorLevel_1);

    for i := 0 to sym_tab.size - 1 do begin
        func_004498E8(sym_tab.data^[i], i);
    end;

    for i := 0 to neg_sym_tab.size - 1 do begin
        func_004498E8(neg_sym_tab.data^[i], -i);
    end;

    if (fixup_count <> 0) then begin
        PostError("Not all local branch-label symbols were defined", emptystring, ErrorLevel_1);
    end;
end;

procedure func_00449DCC();
var
    len: integer;
    i: integer;
    sp6B: char;
    sp6A: char;        
begin
    if (mscoff) then begin
        sp6B := 'S';
        sp6A := 'Y';
    end else begin
        sp6B := '.';
        sp6A := 'T';
    end;

    if (t_opt_string.f^[1] = chr(0)) then begin
        len := strlen(input_fname.f);
        if (len >= 1022) then begin
            PostError("File name too long on command line", input_fname, ErrorLevel_1);
            halt(1);
        end;

        for i := 1 to len do begin
            t_opt_string.f^[i] := input_fname.f^[i];
        end;

        if (len >= 3) and (input_fname.f^[len] = 'G') and (input_fname.f^[len - 1] = '.') then begin
            t_opt_string.f^[len - 1] := sp6B;
            t_opt_string.f^[len] := sp6A;
        end else begin
            len := len + 1;
            t_opt_string.f^[len] := sp6B;
            len := len + 1;
            t_opt_string.f^[len] := sp6A;
        end;
        
        t_opt_string.f^[len + 1] := chr(0);
    end;

    if not mscoff then begin
        if (st_readbinary(t_opt_string.st^, 'a') = -2) then begin
            call_perror(1, t_opt_string);
        end else begin
            t_opt_string.f^[1] := chr(0);
            st_asinit(t_opt_string.f^, debugflag);
        end;
    end else if (ms_readsym(t_opt_string.f^) = -1) then begin
        call_perror(1, t_opt_string);
    end;
end;

procedure func_0044A0C0();
var
    i: integer;
begin
    if (t_opt_string.f^[1] <> chr(0)) then begin
        PostError("Because file contains iasm0 directive, -t option is ignored", input_fname, ErrorLevel_2);
    end;
    
    st_cuinit();
    for i := 1 to strlen(outname.f) + 1 do begin
        t_opt_string.f^[i] := outname.f^[i];
    end;
    st_asinit(t_opt_string.f^, debugflag);
end;

begin { start of main }
    xpg_flag := false;
    xpg_string := "_XPG";
    xpg_string[5] := chr(0);
    if (getenv(xpg_string) <> 0) then begin
        xpg_flag := TRUE;
    end;

    init_all();
    reset(binasm_file, input_fname.f^);

    if Eof(binasm_file) and (Filesize(binasm_file) <> 0) then begin
        call_perror(1, input_fname);
        return 0;
    end;
    
    init_binasm();
    if (binasmfyle^.instr = iasm0) then begin
        func_0044A0C0();
    end else if (binasmfyle^.instr = iverstamp) then begin
        func_00449DCC();
    end else begin
        PostError("Obsolete or corrupt binasm file ", input_fname, ErrorLevel_1);
    end;

    if (severity >= severity_level_2) and not eof(binasm_file) then begin
        if (profileflag >= 2) then begin 
            mcount_address := enter_undef_sym(l_addr(mcount_sym));
        end;

        repeat 
            func_00449724();
            restore_gp();
            parsestmt();

            for j := 1 to bbindex do begin
                if (pinstruction^[j].rfd <> 16#7FFFFFFF) then begin
                    if (isa < ISA_MIPS2) and (pinstruction^[j].unk24 in mark2ops) then begin
                        PostError("Mips2  opcode used without -mips2", emptystring, ErrorLevel_2);
                    end;

                    if (isa < ISA_MIPS3) and (pinstruction^[j].unk24 in mark3ops) then begin
                        PostError("Mips3 opcode used without -mips3", emptystring, ErrorLevel_2);
                    end;

                    if (isa < ISA_MIPS4) and (pinstruction^[j].unk24 in mark4ops) then begin
                        PostError("Mips4 opcode used without -mips4", emptystring, ErrorLevel_2);
                    end;

                    if (isa <> ISA_MIPS1) and (pinstruction^[j].unk24 in c3_ops) then begin  
                        PostError("Coprocessor 3 instructions are valid only for -mips1 (R2000/R3000)  ", emptystring, ErrorLevel_2);
                    end;
                    
                end;
            end;

            if eof(binasm_file) or (lastinstr = iend) and not pendinginstr then begin
                traverse_bb();
            end;
        until eof(binasm_file) and not pendinginstr;
    
        if is_nonleaf then begin
            create_function_table();
        end;
    end;

    flush_line_no();
    definealabel(0, 1, 1);
    definealabel(1, 1, 1);
    definealabel(2, 1, 1);
    definealabel(9, 1, 1);

    if (lastusertextseg <> -1) then begin
        for j := firstusertextseg to lastusertextseg do begin
            definealabel(j, 1, 1);
        end;
    end;

    if (severity >= severity_level_2) then begin
        if (fixup_count > 0) then begin
            func_00449B98();
        end else if (fixup_count <> 0) then begin
            p_assertion_failed("fixup_count = 0\0", "as1main.p", 1914);
        end;
    end;

    if use_ddopt_info then begin
        dd_close();
    end;

    if (severity >= severity_level_2) then begin
        if not elf_flag then begin
            nonzero_scnbase := true;
        end;
        wrobj();
    end;

    if verbose then begin
        writeln(err);
    end;

    if (severity <= severity_level_1) or warnexitflag and (severity <= severity_level_2) then begin
        halt(1);
    end;
    return 0;
end.
