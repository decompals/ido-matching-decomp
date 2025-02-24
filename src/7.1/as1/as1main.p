#include "cmplrs/stinfc.h"
#include "cmplrs/usys.h"
#include "cmplrs/binasm.h"

{ global types }

type
    Byte = 0..16#FF;
    ZeroString = packed array[1..4] of char;
    GString = record
        case integer of
        1: (st: ^st_string;);
        2: (f: ^Filename;);
        3: (s: ^String;);
        4: (z: ^ZeroString;);
        5: (o: ^Identname;);
        6: (c: ^char;);
    end;

    FileOfBinasm = File of binasm;

    opcodes = (
        op_000, op_001, op_002, op_003, op_004, op_005, op_006, op_007,
        op_008, op_009, op_00A, op_00B, op_00C, op_00D, op_00E, op_00F,
        op_010, op_011, op_012, op_013, op_014, op_015, op_016, op_017,
        op_018, op_019, op_01A, op_01B, op_01C, op_01D, op_01E, op_01F,
        op_020, op_021, op_022, op_023, op_024, op_025, op_026, op_027,
        op_028, op_029, op_02A, op_02B, op_02C, op_02D, op_02E, op_02F,
        op_030, op_031, op_032, op_033, op_034, op_035, op_036, op_037,
        op_038, op_039, op_03A, op_03B, op_03C, op_03D, op_03E, op_03F,
        op_040, op_041, op_042, op_043, op_044, op_045, op_046, op_047,
        op_048, op_049, op_04A, op_04B, op_04C, op_04D, op_04E, op_04F,
        op_050, op_051, op_052, op_053, op_054, op_055, op_056, op_057,
        op_058, op_059, op_05A, op_05B, op_05C, op_05D, op_05E, op_05F,
        op_060, op_061, op_062, op_063, op_064, op_065, op_066, op_067,
        op_068, op_069, op_06A, op_06B, op_06C, op_06D, op_06E, op_06F,
        op_070, op_071, op_072, op_073, op_074, op_075, op_076, op_077,
        op_078, op_079, op_07A, op_07B, op_07C, op_07D, op_07E, op_07F,
        op_080, op_081, op_082, op_083, op_084, op_085, op_086, op_087,
        op_088, op_089, op_08A, op_08B, op_08C, op_08D, op_08E, op_08F,
        op_090, op_091, op_092, op_093, op_094, op_095, op_096, op_097,
        op_098, op_099, op_09A, op_09B, op_09C, op_09D, op_09E, op_09F,
        op_0A0, op_0A1, op_0A2, op_0A3, op_0A4, op_0A5, op_0A6, op_0A7,
        op_0A8, op_0A9, op_0AA, op_0AB, op_0AC, op_0AD, op_0AE, op_0AF,
        op_0B0, op_0B1, op_0B2, op_0B3, op_0B4, op_0B5, op_0B6, op_0B7,
        op_0B8, op_0B9, op_0BA, op_0BB, op_0BC, op_0BD, op_0BE, op_0BF,
        op_0C0, op_0C1, op_0C2, op_0C3, op_0C4, op_0C5, op_0C6, op_0C7,
        op_0C8, op_0C9, op_0CA, op_0CB, op_0CC, op_0CD, op_0CE, op_0CF,
        op_0D0, op_0D1, op_0D2, op_0D3, op_0D4, op_0D5, op_0D6, op_0D7,
        op_0D8, op_0D9, op_0DA, op_0DB, op_0DC, op_0DD, op_0DE, op_0DF,
        op_0E0, op_0E1, op_0E2, op_0E3, op_0E4, op_0E5, op_0E6, op_0E7,
        op_0E8, op_0E9, op_0EA, op_0EB, op_0EC, op_0ED, op_0EE, op_0EF,
        op_0F0, op_0F1, op_0F2, op_0F3, op_0F4, op_0F5, op_0F6, op_0F7,
        op_0F8, op_0F9, op_0FA, op_0FB, op_0FC, op_0FD, op_0FE, op_0FF,
        op_100, op_101, op_102, op_103, op_104, op_105, op_106, op_107,
        op_108, op_109, op_10A, op_10B, op_10C, op_10D, op_10E, op_10F,
        op_110, op_111, op_112, op_113, op_114, op_115, op_116, op_117,
        op_118, op_119, op_11A, op_11B, op_11C, op_11D, op_11E, op_11F,
        op_120, op_121, op_122, op_123, op_124, op_125, op_126, op_127,
        op_128, op_129, op_12A, op_12B, op_12C, op_12D, op_12E, op_12F,
        op_130, op_131, op_132, op_133, op_134, op_135, op_136, op_137,
        op_138, op_139, op_13A, op_13B, op_13C, op_13D, op_13E, op_13F,
        op_140, op_141, op_142, op_143, op_144, op_145, op_146, op_147,
        op_148, op_149, op_14A, op_14B, op_14C, op_14D, op_14E, op_14F,
        op_150, op_151, op_152, op_153, op_154, op_155, op_156, op_157,
        op_158, op_159, op_15A, op_15B, op_15C, op_15D, op_15E, op_15F
	);

    opformats = (
        opfmt_0, opfmt_1, opfmt_2, opfmt_3,
        opfmt_4, opfmt_5, opfmt_6, opfmt_7,
        opfmt_8, opfmt_9, opfmt_10
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

    UnkKappa = record
        unk00: integer;
        next: ^UnkKappa;
    end;

    UnkAlpha = record
        { 0x00 } unk00: Byte;
        { 0x04 } unk04: integer;
        { 0x08 } unk08: integer;
        { 0x0C } unk0C: GString;
        { 0x10 } unk10: integer;
        { 0x14 } unk14: integer;
        { 0x18 } unk18: integer;
        { 0x1C } unk1C: integer;
        { 0x20 } unk20: integer;
        { 0x24 } unk24: integer;
        { 0x28 } unk28: integer;
        { 0x2C } unk2C: ^UnkKappa;
        { 0x30 } unk30: integer;
        { 0x34 } unk34: Byte;
        { 0x35 } unk35: Byte;
        { 0x36 } unk36: Byte;
        { 0x37 } unk37: boolean;
        { 0x38 } unk38: integer;
        { 0x3C } unk3C: integer;
        { 0x40 } unk40: integer;
        { 0x44 } unk44: integer;
        { 0x48 } unk48: integer;
        { 0x4C } unk4C: integer;
        { 0x50 } unk50: integer;
        { 0x54 } unk54: integer;
        { 0x58 } unk58: integer;
        { 0x5C } unk5C: integer;
        { 0x60 } unk60: integer;
    end;

    PUnkAlpha = ^UnkAlpha;

    PrevSDataType = Record
        { 0x00 } unk00: integer;
        { 0x04 } unk04: Byte;
        { 0x08 } unk08: integer;
        { 0x0C } unk0C: integer;
        { 0x10 } unk10: integer;
    end;

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

    ErrorLevel = (
        ErrorLevel_0,
        ErrorLevel_1,
        ErrorLevel_2
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

    segments = 0..20; { TODO enum }

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

    IntegerArr = array [0..0] of integer;
    IntegerArray = record;
        data: ^IntegerArr;
        size: cardinal;
    end;

    RldRec = Record
        { 0x00 } unk00: integer;
        { 0x04 } unk04: integer;
        { 0x08 } unk08: ^UnkAlpha;
        { 0x0C } unk0C: integer;
        { 0x10 } unk10: byte;
        { 0x14 } unk14: integer;
    end;

    RldListArr = array [0..0] of RldRec;
    RldListArray = record
        data: ^RldListArr;
        size: cardinal;
    end;

    SymTabRecArr = array [0..0] of PUnkAlpha;
    SymTabRecArray = record
        data: ^SymTabRecArr;
        size: cardinal;
    end;

    PreReorderPeepholesRec = record
        unk_00: integer;
        unk_04: integer;
        unk_08: integer;
        unk_0C: integer;
        unk_10: integer;
        unk_14: packed array [1..32] of char;
    end;

    UnkPiInstr_Record = Record;
        rfd: cardinal;
        unk4: integer;
        unk8: integer;
        unkC: integer;
        unk10: integer;
        unk14: integer;
        unk18: integer;
        unk1C: integer;
        unk20: integer;
        unk24: opcodes;
    end;
    UnkPiInstr_Array = array [0..15] of UnkPiInstr_Record;

{ global variables }

var
    template: array [first(opcodes)..last(opcodes)] of cardinal;
    opcodeformat: array [first(opcodes)..last(opcodes)] of opformats;
    asm2op: array [first(asmcodes)..last(asmcodes)] of opcodes;
    asm2asmformat: array [first(asmcodes)..last(asmcodes)] of asmformat;
    gp_tables: array [0..15] of pointer;
    gprelsize: integer;
    prev_sdata: array[1..2] of PrevSDataType;
    br_always_ops: set of opcodes;
    br_likely_ops: set of opcodes;
    branchops: set of opcodes;
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
    gpreg: registers;
    knownregs: set of registers;
    bbindex: integer;
    shftaddr: integer;
    memory: MemoryRecArray;
    seg_ic: IntegerArray;
    nextlabelchain: IntegerArray;
    rld_list: RldListArray;
    multireloc_list: IntegerArray;
    multirelocinstr_list: IntegerArray;
    sym_tab: SymTabRecArray;
    neg_sym_tab: SymTabRecArray;
    pre_reorder_peepholes: PreReorderPeepholesRec;
    isa: mips_isa;
    outname: GString;
    emptystring: GString;
    mainpath: GString;
    opts: OptRecord;
    s_pool_symbol: PUnkAlpha;
    d_pool_symbol: PUnkAlpha;
    currfunc_sym: ^UnkAlpha;
    nopinserted: integer;
    new_hilo: boolean;
    diag_flag: boolean;
    fpstall_nop: boolean;
    nopsremaining: integer;
    endofbasicb: boolean;
    reorderflag: boolean;
    transform_flag: boolean;
    macroflag: boolean;
    atflag: boolean;
    non_pic_flag: boolean;
    num_issue: integer;
    picflag: integer;
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
    currsegment: segments;
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
    aligning: boolean;
    lastic: integer;
    lastsegment: segments;
    realsegments: set of segments;
    lastrld: integer;
    nextrld: integer;
    nextmultireloc: integer;
    nextmultirelocinstr: integer;
    severity: severity_levels;
    tracereorder: boolean;
    reorder: boolean;
    debugflag: integer;
    profileflag: integer;
    moxieflag: boolean;
    sexchange: boolean;
    optflag: integer;
    elf_flag: boolean;
    abi_flag: boolean;
    bigendian: boolean;
    isbigendianhost: boolean;
    pendinginstr: boolean;
    notandm: boolean;
    xbb_debug: integer;
    listingflag: boolean;
    fp_pool_flag: boolean;
    verbose: boolean;
    warnexitflag: boolean;
    saw_cap_g: boolean;
    big_got: boolean;
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
    binasmfyle: ^binasm;
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
    currsegmentindex: integer;
    binasm_file: FileOfBinasm;
    pinstruction: ^UnkPiInstr_Array;

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
procedure PostError(arg0: String; arg1: GString; arg2: ErrorLevel); external;
function grow_array(var arg0: integer; arg1: integer; arg2: cardinal; arg3: pointer; arg4: boolean): pointer; external;
function init_gp_table(size: integer): pointer; external;
procedure dd_initialize(var arg0: Filename); external;
function negative_file_opt(s: GString): boolean; external;
procedure exit(code: integer); external;
procedure st_asinit(var arg0: Filename; arg1: integer); external;
function ms_readsym(var arg0: Filename): integer; external;
procedure init_j_def_live(); external;
procedure init_inst_heap(); external;
procedure call_perror(arg0: integer; str: GString); external;
procedure init_binasm(); external;
procedure definealabel(arg0: integer; arg1: integer; arg2: integer); external;
procedure dd_close(); external;
procedure wrobj(); external;
procedure p_assertion_failed(arg0: String; arg1: String; arg2: cardinal); external;
function strlen(p : ^Filename): integer; external;
procedure parsestmt(); external;
procedure restore_gp(); external;
function filesize(var f: FileOfBinasm): integer; external;
function l_addr(ptr: pointer): pointer; external;
function enter_undef_sym(ptr: pointer): pointer; external;
procedure traverse_bb(); external;
procedure create_function_table(); external;
procedure flush_line_no(); external;

program main;
var
    j: integer;
    string1: GString;
    string2: GString;
    string3: GString;
    string4: GString;
    sp104: String; { sp104 - sp154 }
    i: integer;
    
procedure func_00441024();
var
    j: integer;
    index: integer;
    var_s7: Reorg_Enum;
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
    
    procedure func_00440E20(fop: opcodes; tmpl: cardinal; fmt: opformats);
    begin
        template[fop] := tmpl;
        opcodeformat[fop] := fmt;
    end;
    
    procedure func_00440E54(fasm: asmcodes; fmt: asmformat; op: opcodes);
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
            prev_sdata[i].unk04 := 0;
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
            func_00440F68 := op_000;
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
    new(string3.f);
    string3.f^[1] := chr(0);
    new(string2.f);
    string2.f^[1] := chr(0);
    new(string1.f);
    string1.f^[1] := chr(0);
    new(outname.f);
    outname.o^ := "b.out\0"; { need to make it 32 bytes long }
    new(string4.f);
    string4.f^[1] := chr(0);

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
    var_s7 := Reorg_Val_0;
    
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
    gp_fp_moves := [op_073, op_076, op_07B, op_07D, op_085, op_086, op_08C, op_08E, op_090, op_092, op_099, op_09A];
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
                    option_r3000: { after mips options ? }
                        begin
                            var_s7 := Reorg_Val_1;
                            maybe_r4000 := false;
                        end;
                    option_mips1: isa := ISA_MIPS1;
                    option_mips2: isa := ISA_MIPS2;
                    option_mips3: isa := ISA_MIPS3;
                    option_r4000: var_s7 := Reorg_Val_3;
                    option_r4200: var_s7 := Reorg_Val_4;
                    option_r4600: var_s7 := Reorg_Val_5;
                    option_tfp: var_s7 := Reorg_Val_11;
                    option_t5_r31: t5_jal := true;
                    option_t5_mtc1: t5_mtc1 := true;
                    option_t5_muldiv: t5_muldiv := true;
                    option_t5_ll_sc_bug: t5_ll_sc_bug := true;
                    option_r6000:
                        begin
                            var_s7 := Reorg_Val_6;
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
                            get_sstring(index, string4);
                            dd_initialize(string4.f^);
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
                            get_sstring(index, string3);
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
                            var_s7 := Reorg_Val_10; get_lstring(index, arg);
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
                            if (string1.f^[1] = chr(0)) then begin
                                get_sstring(index, string2);
                                for i := 3 to 1024 do
                                    string1.f^[i - 2] := string2.f^[i];
                            end else begin
                                PostError("too many file names on command line", emptystring, ErrorLevel_2);
                            end;
                        end else begin
                            PostError("unknown option", arg, ErrorLevel_2);
                        end;
                end;
            end else if (string1.f^[1] = chr(0)) then begin
                get_sstring(index, string1);
            end else begin
                PostError("too many file names on command line", emptystring, ErrorLevel_2);
            end;
            index := index + 1;
        until (index >= argc);
    end;

    dispose(arg.o);
    if (string1.o^[1] = chr(0)) then begin
        string1.o^ := "binasm\0";
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

    init_reorg_state(var_s7);
    sexchange := (isbigendianhost <> bigendian);

    br_always_ops := [op_035..op_03E, op_04B..op_04E, op_13F, op_140];
    br_likely_ops := [op_03F..op_048, op_04F..op_052];
    branchops := br_always_ops + br_likely_ops;
    storeops := [op_06D..op_071, op_075..op_077, op_07A, op_07D, op_07E, op_082..op_084, op_086, op_143];
    alu3ops := [op_005..op_007, op_010..op_034, op_087..op_08A, op_134..op_138];
    trapops := [op_01E..op_023];
    fpops := [op_0A0..op_0F3, op_0FB..op_11A, op_11C..op_133];
    c0123_moves := [op_08B..op_092, op_099..op_09E, op_0F4..op_0F7, op_144..op_14B];
    mark2ops := [op_01E..op_023, op_03F..op_048, op_04F..op_052, op_05B..op_060, op_072, op_075, op_07B..op_07E, op_09F, op_11B];
    mark3ops := [op_024..op_034, op_061, op_062, op_078..op_07A, op_07F..op_084, op_099..op_09E, op_107..op_11A];
    mark4ops := [op_087..op_08A, op_11C..op_138, op_13C..op_13E, op_148..op_14B];
    hilo_defs := [op_00D, op_00F..op_013, op_031..op_034];
    c0_ops := [op_039, op_03A, op_063, op_08B, op_08F, op_094..op_097, op_09B, op_09C, op_09F, op_139..op_13B, op_13D, op_13E, op_148..op_14B];
    c3_ops := [op_13F..op_147];

    func_00440E54(zabs, afrr, op_000);
    func_00440E54(zadd, afrrr, op_014);
    func_00440E54(zaddu, afrrr, op_015);
    func_00440E54(zaddou, afrrr, op_015);
    func_00440E54(zand, afrrr, op_018);
    func_00440E54(zb, afl, op_000);
    func_00440E54(zbc0f, afl, op_039);
    func_00440E54(zbc0t, afl, op_03A);
    func_00440E54(zbc1f, afl, op_03B);
    func_00440E54(zbc1t, afl, op_03C);
    func_00440E54(zbc2f, afl, op_03D);
    func_00440E54(zbc2t, afl, op_03E);
    func_00440E54(zbc0fl, afl, op_043);
    func_00440E54(zbc0tl, afl, op_044);
    func_00440E54(zbc1fl, afl, op_045);
    func_00440E54(zbc1tl, afl, op_046);
    func_00440E54(zbc2fl, afl, op_047);
    func_00440E54(zbc2tl, afl, op_048);
    func_00440E54(zbeq, afrrl, op_04B);
    func_00440E54(zbeqz, afrl, op_04B);
    func_00440E54(zbne, afrrl, op_04C);
    func_00440E54(zbnez, afrl, op_04C);
    func_00440E54(zble, afrrl, op_000);
    func_00440E54(zbleu, afrrl, op_000);
    func_00440E54(zblez, afrl, op_04D);
    func_00440E54(zbgt, afrrl, op_000);
    func_00440E54(zbgtu, afrrl, op_000);
    func_00440E54(zbgtz, afrl, op_04E);
    func_00440E54(zblt, afrrl, op_000);
    func_00440E54(zbltu, afrrl, op_000);
    func_00440E54(zbltz, afrl, op_035);
    func_00440E54(zbltzal, afrl, op_037);
    func_00440E54(zbge, afrrl, op_000);
    func_00440E54(zbgeu, afrrl, op_000);
    func_00440E54(zbgez, afrl, op_036);
    func_00440E54(zbgezal, afrl, op_038);
    func_00440E54(zbal, afrl, op_038);
    func_00440E54(zbeql, afrrl, op_04F);
    func_00440E54(zbeqzl, afrl, op_04F);
    func_00440E54(zbnel, afrrl, op_050);
    func_00440E54(zbnezl, afrl, op_050);
    func_00440E54(zblel, afrrl, op_000);
    func_00440E54(zbleul, afrrl, op_000);
    func_00440E54(zblezl, afrl, op_051);
    func_00440E54(zbgtl, afrrl, op_000);
    func_00440E54(zbgtul, afrrl, op_000);
    func_00440E54(zbgtzl, afrl, op_052);
    func_00440E54(zbltl, afrrl, op_000);
    func_00440E54(zbltul, afrrl, op_000);
    func_00440E54(zbltzl, afrl, op_03F);
    func_00440E54(zbltzall, afrl, op_041);
    func_00440E54(zbgel, afrrl, op_000);
    func_00440E54(zbgeul, afrrl, op_000);
    func_00440E54(zbgezl, afrl, op_040);
    func_00440E54(zbgezall, afrl, op_042);
    func_00440E54(zbreak, af, op_00B);
    func_00440E54(zcia, afri, op_000);
    func_00440E54(zc0, aforrr, op_063);
    func_00440E54(zc1, aforrr, op_064);
    func_00440E54(zc2, aforrr, op_065);
    func_00440E54(zdiv, afrrr, op_012);
    func_00440E54(zdivu, afrrr, op_013);
    func_00440E54(zj, afa, op_049);
    func_00440E54(zjal, afa, op_04A);
    func_00440E54(zla, afra, op_000);
    func_00440E54(zlb, afra, op_066);
    func_00440E54(zlbu, afra, op_06A);
    func_00440E54(zlh, afra, op_067);
    func_00440E54(zlhu, afra, op_06B);
    func_00440E54(zli, afri, op_000);
    func_00440E54(zlw, afra, op_069);
    func_00440E54(zll, afra, op_072);
    func_00440E54(zlwc1, afra, op_073);
    func_00440E54(zlwc2, afra, op_074);
    func_00440E54(zlwl, afra, op_068);
    func_00440E54(zlwr, afra, op_06C);
    func_00440E54(zmfc0, afrr, op_08B);
    func_00440E54(zmfc1, afrr, op_08C);
    func_00440E54(zmfc1_d, afrr, op_08C);
    func_00440E54(zmfc2, afrr, op_08D);
    func_00440E54(zcfc0, afrr, op_0F4);
    func_00440E54(zcfc1, afrr, op_08E);
    func_00440E54(zcfc2, afrr, op_0F5);
    func_00440E54(zmfhi, afr, op_00C);
    func_00440E54(zmflo, afr, op_00E);
    func_00440E54(zmove, afrr, op_000);
    func_00440E54(zmtc0, afrr, op_08F);
    func_00440E54(zmtc1, afrr, op_090);
    func_00440E54(zmtc1_d, afrr, op_090);
    func_00440E54(zmtc2, afrr, op_091);
    func_00440E54(zctc0, afrr, op_0F6);
    func_00440E54(zctc1, afrr, op_092);
    func_00440E54(zctc2, afrr, op_0F7);
    func_00440E54(zmthi, afr, op_00D);
    func_00440E54(zmtlo, afr, op_00F);
    func_00440E54(zmul, afrrr, op_000);
    func_00440E54(zmulo, afrrr, op_000);
    func_00440E54(zmulou, afrrr, op_000);
    func_00440E54(zmult, afrr, op_010);
    func_00440E54(zmultu, afrr, op_011);
    func_00440E54(zneg, afrr, op_000);
    func_00440E54(znegu, afrr, op_000);
    func_00440E54(znop, af, op_001);
    func_00440E54(znor, afrrr, op_01B);
    func_00440E54(znot, afrr, op_000);
    func_00440E54(zor, afrrr, op_019);
    func_00440E54(zrem, afrrr, op_012);
    func_00440E54(zremu, afrrr, op_013);
    func_00440E54(zrfe, af, op_093);
    func_00440E54(zrol, afrrr, op_000);
    func_00440E54(zror, afrrr, op_000);
    func_00440E54(zsb, afra, op_06D);
    func_00440E54(zseq, afrrr, op_000);
    func_00440E54(zsge, afrrr, op_000);
    func_00440E54(zsgeu, afrrr, op_000);
    func_00440E54(zsgt, afrrr, op_000);
    func_00440E54(zsgtu, afrrr, op_000);
    func_00440E54(zsh, afra, op_06E);
    func_00440E54(zsle, afrrr, op_000);
    func_00440E54(zsleu, afrrr, op_000);
    func_00440E54(zsll, afrrr, op_002);
    func_00440E54(zslt, afrrr, op_000);
    func_00440E54(zsltu, afrrr, op_000);
    func_00440E54(zsne, afrrr, op_000);
    func_00440E54(zsra, afrrr, op_004);
    func_00440E54(zsrl, afrrr, op_003);
    func_00440E54(zsllv, afrrr, op_005);
    func_00440E54(zsrlv, afrrr, op_006);
    func_00440E54(zsrav, afrrr, op_007);
    func_00440E54(zsub, afrrr, op_016);
    func_00440E54(zsubu, afrrr, op_017);
    func_00440E54(zsubou, afrrr, op_017);
    func_00440E54(zsw, afra, op_070);
    func_00440E54(zsc, afra, op_075);
    func_00440E54(zswc1, afra, op_076);
    func_00440E54(zswc2, afra, op_077);
    func_00440E54(zswl, afra, op_06F);
    func_00440E54(zswr, afra, op_071);
    func_00440E54(zsyscall, af, op_00A);
    func_00440E54(zxor, afrrr, op_01A);
    func_00440E54(ztlbr, af, op_094);
    func_00440E54(ztlbwi, af, op_095);
    func_00440E54(ztlbwr, af, op_096);
    func_00440E54(ztlbp, af, op_097);
    func_00440E54(ztlbr1, af, op_13D);
    func_00440E54(ztlbp1, af, op_13E);
    func_00440E54(zsync, af, op_098);
    func_00440E54(zld, afra, func_00440F68(op_079));
    func_00440E54(zsd, afra, func_00440F68(op_07A));
    func_00440E54(zldc1, afra, func_00440F68(op_07B));
    func_00440E54(zldc2, afra, func_00440F68(op_07C));
    func_00440E54(zsdc1, afra, func_00440F68(op_07D));
    func_00440E54(zsdc2, afra, func_00440F68(op_07E));
    func_00440E54(zaddi, afrrr, op_053);
    func_00440E54(zaddiu, afrrr, op_054);
    func_00440E54(zslti, afrrr, op_055);
    func_00440E54(zsltiu, afrrr, op_056);
    func_00440E54(zandi, afrrr, op_057);
    func_00440E54(zori, afrrr, op_058);
    func_00440E54(zxori, afrrr, op_059);
    func_00440E54(zlui, afri, op_05A);
    func_00440E54(zulw, afra, op_000);
    func_00440E54(zulh, afra, op_000);
    func_00440E54(zulhu, afra, op_000);
    func_00440E54(zusw, afra, op_000);
    func_00440E54(zush, afra, op_000);
    func_00440E54(zdli, dli_dla, op_000);
    func_00440E54(zdla, afra, op_000);
    func_00440E54(zlgota, afra, op_000);

    func_00440E20(op_014, 16#00000020, opfmt_3);
    func_00440E20(op_053, 16#20000000, opfmt_0);
    func_00440E20(op_054, 16#24000000, opfmt_0);
    func_00440E20(op_015, 16#00000021, opfmt_3);
    func_00440E20(op_018, 16#00000024, opfmt_3);
    func_00440E20(op_057, 16#30000000, opfmt_0);
    func_00440E20(op_039, 16#41000000, opfmt_2);
    func_00440E20(op_03A, 16#41010000, opfmt_2);
    func_00440E20(op_03B, 16#45000000, opfmt_2);
    func_00440E20(op_03C, 16#45010000, opfmt_2);
    func_00440E20(op_03D, 16#49000000, opfmt_2);
    func_00440E20(op_03E, 16#49010000, opfmt_2);
    func_00440E20(op_043, 16#41020000, opfmt_2);
    func_00440E20(op_044, 16#41030000, opfmt_2);
    func_00440E20(op_045, 16#45020000, opfmt_2);
    func_00440E20(op_046, 16#45030000, opfmt_2);
    func_00440E20(op_047, 16#49020000, opfmt_2);
    func_00440E20(op_048, 16#49030000, opfmt_2);
    func_00440E20(op_04B, 16#10000000, opfmt_1);
    func_00440E20(op_04C, 16#14000000, opfmt_1);
    func_00440E20(op_04D, 16#18000000, opfmt_2);
    func_00440E20(op_04E, 16#1C000000, opfmt_2);
    func_00440E20(op_035, 16#04000000, opfmt_2);
    func_00440E20(op_037, 16#04100000, opfmt_2);
    func_00440E20(op_036, 16#04010000, opfmt_2);
    func_00440E20(op_038, 16#04110000, opfmt_2);
    func_00440E20(op_04F, 16#50000000, opfmt_1);
    func_00440E20(op_050, 16#54000000, opfmt_1);
    func_00440E20(op_051, 16#58000000, opfmt_2);
    func_00440E20(op_052, 16#5C000000, opfmt_2);
    func_00440E20(op_03F, 16#04020000, opfmt_2);
    func_00440E20(op_041, 16#04120000, opfmt_2);
    func_00440E20(op_040, 16#04030000, opfmt_2);
    func_00440E20(op_042, 16#04130000, opfmt_2);
    func_00440E20(op_00B, 16#0000000D, opfmt_3);
    func_00440E20(op_063, 16#42000000, opfmt_5);
    func_00440E20(op_064, 16#46000000, opfmt_5);
    func_00440E20(op_065, 16#4A000000, opfmt_5);
    func_00440E20(op_012, 16#0000001A, opfmt_3);
    func_00440E20(op_013, 16#0000001B, opfmt_3);
    func_00440E20(op_04A, 16#0C000000, opfmt_4);
    func_00440E20(op_009, 16#00000009, opfmt_3);
    func_00440E20(op_049, 16#08000000, opfmt_4);
    func_00440E20(op_008, 16#00000008, opfmt_3);
    func_00440E20(op_066, 16#80000000, opfmt_6);
    func_00440E20(op_06A, 16#90000000, opfmt_6);
    func_00440E20(op_067, 16#84000000, opfmt_6);
    func_00440E20(op_06B, 16#94000000, opfmt_6);
    func_00440E20(op_05A, 16#3C000000, opfmt_0);
    func_00440E20(op_069, 16#8C000000, opfmt_6);
    func_00440E20(op_079, 16#DC000000, opfmt_6);
    func_00440E20(op_072, 16#C0000000, opfmt_6);
    func_00440E20(op_073, 16#C4000000, opfmt_6);
    func_00440E20(op_074, 16#C8000000, opfmt_6);
    func_00440E20(op_068, 16#88000000, opfmt_6);
    func_00440E20(op_06C, 16#98000000, opfmt_6);
    func_00440E20(op_00C, 16#00000010, opfmt_3);
    func_00440E20(op_00E, 16#00000012, opfmt_3);
    func_00440E20(op_07B, 16#D4000000, opfmt_6);
    func_00440E20(op_07C, 16#D8000000, opfmt_6);
    func_00440E20(op_07D, 16#F4000000, opfmt_6);
    func_00440E20(op_07E, 16#F8000000, opfmt_6);
    func_00440E20(op_08B, 16#40000000, opfmt_5);
    func_00440E20(op_08C, 16#44000000, opfmt_5);
    func_00440E20(op_08D, 16#48000000, opfmt_5);
    func_00440E20(op_0F4, 16#40400000, opfmt_5);
    func_00440E20(op_08E, 16#44400000, opfmt_5);
    func_00440E20(op_0F5, 16#48400000, opfmt_5);
    func_00440E20(op_08F, 16#40800000, opfmt_5);
    func_00440E20(op_090, 16#44800000, opfmt_5);
    func_00440E20(op_091, 16#48800000, opfmt_5);
    func_00440E20(op_0F6, 16#40C00000, opfmt_5);
    func_00440E20(op_092, 16#44C00000, opfmt_5);
    func_00440E20(op_0F7, 16#48C00000, opfmt_5);
    func_00440E20(op_00D, 16#00000011, opfmt_3);
    func_00440E20(op_00F, 16#00000013, opfmt_3);
    func_00440E20(op_010, 16#00000018, opfmt_3);
    func_00440E20(op_011, 16#00000019, opfmt_3);
    func_00440E20(op_01B, 16#00000027, opfmt_3);
    func_00440E20(op_019, 16#00000025, opfmt_3);
    func_00440E20(op_058, 16#34000000, opfmt_0);
    func_00440E20(op_093, 16#42000010, opfmt_5);
    func_00440E20(op_094, 16#42000001, opfmt_5);
    func_00440E20(op_095, 16#42000002, opfmt_5);
    func_00440E20(op_096, 16#42000006, opfmt_5);
    func_00440E20(op_097, 16#42000008, opfmt_5);
    func_00440E20(op_13D, 16#43000001, opfmt_5);
    func_00440E20(op_13E, 16#43000008, opfmt_5);
    func_00440E20(op_098, 16#0000000F, opfmt_3);
    func_00440E20(op_06D, 16#A0000000, opfmt_6);
    func_00440E20(op_06E, 16#A4000000, opfmt_6);
    func_00440E20(op_002, 16#00000000, opfmt_3);
    func_00440E20(op_005, 16#00000004, opfmt_3);
    func_00440E20(op_016, 16#00000022, opfmt_3);
    func_00440E20(op_017, 16#00000023, opfmt_3);
    func_00440E20(op_01C, 16#0000002A, opfmt_3);
    func_00440E20(op_01D, 16#0000002B, opfmt_3);
    func_00440E20(op_020, 16#00000030, opfmt_3);
    func_00440E20(op_021, 16#00000031, opfmt_3);
    func_00440E20(op_01E, 16#00000032, opfmt_3);
    func_00440E20(op_01F, 16#00000033, opfmt_3);
    func_00440E20(op_022, 16#00000034, opfmt_3);
    func_00440E20(op_023, 16#00000036, opfmt_3);
    func_00440E20(op_05D, 16#04080000, opfmt_9);
    func_00440E20(op_05E, 16#04090000, opfmt_9);
    func_00440E20(op_05B, 16#040A0000, opfmt_9);
    func_00440E20(op_05C, 16#040B0000, opfmt_9);
    func_00440E20(op_05F, 16#040C0000, opfmt_9);
    func_00440E20(op_060, 16#040E0000, opfmt_9);
    func_00440E20(op_055, 16#28000000, opfmt_0);
    func_00440E20(op_056, 16#2C000000, opfmt_0);
    func_00440E20(op_004, 16#00000003, opfmt_3);
    func_00440E20(op_007, 16#00000007, opfmt_3);
    func_00440E20(op_003, 16#00000002, opfmt_3);
    func_00440E20(op_006, 16#00000006, opfmt_3);
    func_00440E20(op_070, 16#AC000000, opfmt_6);
    func_00440E20(op_07A, 16#FC000000, opfmt_6);
    func_00440E20(op_075, 16#E0000000, opfmt_6);
    func_00440E20(op_076, 16#E4000000, opfmt_6);
    func_00440E20(op_077, 16#E8000000, opfmt_6);
    func_00440E20(op_06F, 16#A8000000, opfmt_6);
    func_00440E20(op_071, 16#B8000000, opfmt_6);
    func_00440E20(op_00A, 16#0000000C, opfmt_3);
    func_00440E20(op_01A, 16#00000026, opfmt_3);
    func_00440E20(op_059, 16#38000000, opfmt_0);

    func_00440E54(fli_s, afri_fp, op_0F8);
    func_00440E54(fli_d, afri_fp, op_0F9);
    func_00440E54(fli_e, afri_fp, op_0FA);
    func_00440E54(fl_s, afra, op_000);
    func_00440E54(fl_d, afra, op_000);
    func_00440E54(fl_e, afra, op_000);
    func_00440E54(fs_s, afra, op_000);
    func_00440E54(fs_d, afra, op_000);
    func_00440E54(fs_e, afra, op_000);
    func_00440E54(fadd_s, afrrr, op_0A0);
    func_00440E54(fadd_d, afrrr, op_0A1);
    func_00440E54(fadd_e, afrrr, op_0A2);
    func_00440E54(fsub_s, afrrr, op_0A3);
    func_00440E54(fsub_d, afrrr, op_0A4);
    func_00440E54(fsub_e, afrrr, op_0A5);
    func_00440E54(fmul_s, afrrr, op_0A6);
    func_00440E54(fmul_d, afrrr, op_0A7);
    func_00440E54(fmul_e, afrrr, op_0A8);
    func_00440E54(fdiv_s, afrrr, op_0A9);
    func_00440E54(fdiv_d, afrrr, op_0AA);
    func_00440E54(fdiv_e, afrrr, op_0AB);
    func_00440E54(fsqrt_s, afrrr, op_0AC);
    func_00440E54(fsqrt_d, afrrr, op_0AD);
    func_00440E54(fsqrt_e, afrrr, op_0AE);
    func_00440E54(fmov_s, afrrr, op_0B2);
    func_00440E54(fmov_d, afrrr, op_0B3);
    func_00440E54(fmov_e, afrrr, op_0B4);
    func_00440E54(fabs_s, afrrr, op_0AF);
    func_00440E54(fabs_d, afrrr, op_0B0);
    func_00440E54(fabs_e, afrrr, op_0B1);
    func_00440E54(fneg_s, afrrr, op_0B5);
    func_00440E54(fneg_d, afrrr, op_0B6);
    func_00440E54(fneg_e, afrrr, op_0B7);
    func_00440E54(fcvt_s_d, afrrr, op_0B8);
    func_00440E54(fcvt_s_e, afrrr, op_0B9);
    func_00440E54(fcvt_s_w, afrrr, op_0BA);
    func_00440E54(fcvt_d_s, afrrr, op_0BB);
    func_00440E54(fcvt_d_e, afrrr, op_0BC);
    func_00440E54(fcvt_d_w, afrrr, op_0BD);
    func_00440E54(fcvt_e_s, afrrr, op_0BE);
    func_00440E54(fcvt_e_d, afrrr, op_0BF);
    func_00440E54(fcvt_e_w, afrrr, op_0C0);
    func_00440E54(fcvt_w_s, afrrr, op_0C1);
    func_00440E54(fcvt_w_d, afrrr, op_0C2);
    func_00440E54(fcvt_w_e, afrrr, op_0C3);
    func_00440E54(fc_f_s, afrrr, op_0C4);
    func_00440E54(fc_f_d, afrrr, op_0C5);
    func_00440E54(fc_f_e, afrrr, op_0C6);
    func_00440E54(fc_un_s, afrrr, op_0C7);
    func_00440E54(fc_un_d, afrrr, op_0C8);
    func_00440E54(fc_un_e, afrrr, op_0C9);
    func_00440E54(fc_eq_s, afrrr, op_0CA);
    func_00440E54(fc_eq_d, afrrr, op_0CB);
    func_00440E54(fc_eq_e, afrrr, op_0CC);
    func_00440E54(fc_ueq_s, afrrr, op_0CD);
    func_00440E54(fc_ueq_d, afrrr, op_0CE);
    func_00440E54(fc_ueq_e, afrrr, op_0CF);
    func_00440E54(fc_olt_s, afrrr, op_0D0);
    func_00440E54(fc_olt_d, afrrr, op_0D1);
    func_00440E54(fc_olt_e, afrrr, op_0D2);
    func_00440E54(fc_ult_s, afrrr, op_0D3);
    func_00440E54(fc_ult_d, afrrr, op_0D4);
    func_00440E54(fc_ult_e, afrrr, op_0D5);
    func_00440E54(fc_ole_s, afrrr, op_0D6);
    func_00440E54(fc_ole_d, afrrr, op_0D7);
    func_00440E54(fc_ole_e, afrrr, op_0D8);
    func_00440E54(fc_ule_s, afrrr, op_0D9);
    func_00440E54(fc_ule_d, afrrr, op_0DA);
    func_00440E54(fc_ule_e, afrrr, op_0DB);
    func_00440E54(fc_sf_s, afrrr, op_0DC);
    func_00440E54(fc_sf_d, afrrr, op_0DD);
    func_00440E54(fc_sf_e, afrrr, op_0DE);
    func_00440E54(fc_ngle_s, afrrr, op_0DF);
    func_00440E54(fc_ngle_d, afrrr, op_0E0);
    func_00440E54(fc_ngle_e, afrrr, op_0E1);
    func_00440E54(fc_seq_s, afrrr, op_0E2);
    func_00440E54(fc_seq_d, afrrr, op_0E3);
    func_00440E54(fc_seq_e, afrrr, op_0E4);
    func_00440E54(fc_ngl_s, afrrr, op_0E5);
    func_00440E54(fc_ngl_d, afrrr, op_0E6);
    func_00440E54(fc_ngl_e, afrrr, op_0E7);
    func_00440E54(fc_lt_s, afrrr, op_0E8);
    func_00440E54(fc_lt_d, afrrr, op_0E9);
    func_00440E54(fc_lt_e, afrrr, op_0EA);
    func_00440E54(fc_nge_s, afrrr, op_0EB);
    func_00440E54(fc_nge_d, afrrr, op_0EC);
    func_00440E54(fc_nge_e, afrrr, op_0ED);
    func_00440E54(fc_le_s, afrrr, op_0EE);
    func_00440E54(fc_le_d, afrrr, op_0EF);
    func_00440E54(fc_le_e, afrrr, op_0F0);
    func_00440E54(fc_ngt_s, afrrr, op_0F1);
    func_00440E54(fc_ngt_d, afrrr, op_0F2);
    func_00440E54(fc_ngt_e, afrrr, op_0F3);
    if (isa >= ISA_MIPS2) then begin
        func_00440E54(zround_w_s, afrrr, op_0FB);
        func_00440E54(zround_w_d, afrrr, op_0FC);
        func_00440E54(zround_w_e, afrrr, op_0FD);
        func_00440E54(zroundu_w_s, afrrr, op_0FB);
        func_00440E54(zroundu_w_d, afrrr, op_0FC);
        func_00440E54(zroundu_w_e, afrrr, op_0FD);
        func_00440E54(ztrunc_w_s, afrrr, op_0FE);
        func_00440E54(ztrunc_w_d, afrrr, op_0FF);
        func_00440E54(ztrunc_w_e, afrrr, op_100);
        func_00440E54(ztruncu_w_s, afrrr, op_0FE);
        func_00440E54(ztruncu_w_d, afrrr, op_0FF);
        func_00440E54(ztruncu_w_e, afrrr, op_100);
        func_00440E54(zceil_w_s, afrrr, op_101);
        func_00440E54(zceil_w_d, afrrr, op_102);
        func_00440E54(zceil_w_e, afrrr, op_103);
        func_00440E54(zceilu_w_s, afrrr, op_101);
        func_00440E54(zceilu_w_d, afrrr, op_102);
        func_00440E54(zceilu_w_e, afrrr, op_103);
        func_00440E54(zfloor_w_s, afrrr, op_104);
        func_00440E54(zfloor_w_d, afrrr, op_105);
        func_00440E54(zfloor_w_e, afrrr, op_106);
        func_00440E54(zflooru_w_s, afrrr, op_104);
        func_00440E54(zflooru_w_d, afrrr, op_105);
        func_00440E54(zflooru_w_e, afrrr, op_106);
    end else begin
        func_00440E54(zround_w_s, afrrr, op_0C1);
        func_00440E54(zround_w_d, afrrr, op_0C2);
        func_00440E54(zround_w_e, afrrr, op_0C3);
        func_00440E54(zroundu_w_s, afrrr, op_0C1);
        func_00440E54(zroundu_w_d, afrrr, op_0C2);
        func_00440E54(zroundu_w_e, afrrr, op_0C3);
        func_00440E54(ztrunc_w_s, afrrr, op_0C1);
        func_00440E54(ztrunc_w_d, afrrr, op_0C2);
        func_00440E54(ztrunc_w_e, afrrr, op_0C3);
        func_00440E54(ztruncu_w_s, afrrr, op_0C1);
        func_00440E54(ztruncu_w_d, afrrr, op_0C2);
        func_00440E54(ztruncu_w_e, afrrr, op_0C3);
        func_00440E54(zceil_w_s, afrrr, op_0C1);
        func_00440E54(zceil_w_d, afrrr, op_0C2);
        func_00440E54(zceil_w_e, afrrr, op_0C3);
        func_00440E54(zceilu_w_s, afrrr, op_0C1);
        func_00440E54(zceilu_w_d, afrrr, op_0C2);
        func_00440E54(zceilu_w_e, afrrr, op_0C3);
        func_00440E54(zfloor_w_s, afrrr, op_0C1);
        func_00440E54(zfloor_w_d, afrrr, op_0C2);
        func_00440E54(zfloor_w_e, afrrr, op_0C3);
        func_00440E54(zflooru_w_s, afrrr, op_0C1);
        func_00440E54(zflooru_w_d, afrrr, op_0C2);
        func_00440E54(zflooru_w_e, afrrr, op_0C3);
    end;
    func_00440E54(ztlt, afrrr, op_01E);
    func_00440E54(ztltu, afrrr, op_01F);
    func_00440E54(ztge, afrrr, op_020);
    func_00440E54(ztgeu, afrrr, op_021);
    func_00440E54(zteq, afrrr, op_022);
    func_00440E54(ztne, afrrr, op_023);

    func_00440E20(op_0A0, 16#46000000, opfmt_8);
    func_00440E20(op_0A1, 16#46200000, opfmt_8);
    func_00440E20(op_0A2, 16#46400000, opfmt_8);
    func_00440E20(op_0A3, 16#46000001, opfmt_8);
    func_00440E20(op_0A4, 16#46200001, opfmt_8);
    func_00440E20(op_0A5, 16#46400001, opfmt_8);
    func_00440E20(op_0A6, 16#46000002, opfmt_8);
    func_00440E20(op_0A7, 16#46200002, opfmt_8);
    func_00440E20(op_0A8, 16#46400002, opfmt_8);
    func_00440E20(op_0A9, 16#46000003, opfmt_8);
    func_00440E20(op_0AA, 16#46200003, opfmt_8);
    func_00440E20(op_0AB, 16#46400003, opfmt_8);
    func_00440E20(op_0AC, 16#46000004, opfmt_8);
    func_00440E20(op_0AD, 16#46200004, opfmt_8);
    func_00440E20(op_0AE, 16#46400004, opfmt_8);
    func_00440E20(op_0AF, 16#46000005, opfmt_8);
    func_00440E20(op_0B0, 16#46200005, opfmt_8);
    func_00440E20(op_0B1, 16#46400005, opfmt_8);
    func_00440E20(op_0B5, 16#46000007, opfmt_8);
    func_00440E20(op_0B6, 16#46200007, opfmt_8);
    func_00440E20(op_0B7, 16#46400007, opfmt_8);
    func_00440E20(op_0B2, 16#46000006, opfmt_8);
    func_00440E20(op_0B3, 16#46200006, opfmt_8);
    func_00440E20(op_0B4, 16#46400006, opfmt_8);
    func_00440E20(op_0B8, 16#46200020, opfmt_8);
    func_00440E20(op_0B9, 16#46400020, opfmt_8);
    func_00440E20(op_0BA, 16#46800020, opfmt_8);
    func_00440E20(op_0BB, 16#46000021, opfmt_8);
    func_00440E20(op_0BC, 16#46400021, opfmt_8);
    func_00440E20(op_0BD, 16#46800021, opfmt_8);
    func_00440E20(op_0BE, 16#46000022, opfmt_8);
    func_00440E20(op_0BF, 16#46200022, opfmt_8);
    func_00440E20(op_0C0, 16#46800022, opfmt_8);
    func_00440E20(op_0C1, 16#46000024, opfmt_8);
    func_00440E20(op_0C2, 16#46200024, opfmt_8);
    func_00440E20(op_0C3, 16#46400024, opfmt_8);
    func_00440E20(op_0C4, 16#46000030, opfmt_8);
    func_00440E20(op_0C5, 16#46200030, opfmt_8);
    func_00440E20(op_0C6, 16#46400030, opfmt_8);
    func_00440E20(op_0C7, 16#46000031, opfmt_8);
    func_00440E20(op_0C8, 16#46200031, opfmt_8);
    func_00440E20(op_0C9, 16#46400031, opfmt_8);
    func_00440E20(op_0CA, 16#46000032, opfmt_8);
    func_00440E20(op_0CB, 16#46200032, opfmt_8);
    func_00440E20(op_0CC, 16#46400032, opfmt_8);
    func_00440E20(op_0CD, 16#46000033, opfmt_8);
    func_00440E20(op_0CE, 16#46200033, opfmt_8);
    func_00440E20(op_0CF, 16#46400033, opfmt_8);
    func_00440E20(op_0D0, 16#46000034, opfmt_8);
    func_00440E20(op_0D1, 16#46200034, opfmt_8);
    func_00440E20(op_0D2, 16#46400034, opfmt_8);
    func_00440E20(op_0D3, 16#46000035, opfmt_8);
    func_00440E20(op_0D4, 16#46200035, opfmt_8);
    func_00440E20(op_0D5, 16#46400035, opfmt_8);
    func_00440E20(op_0D6, 16#46000036, opfmt_8);
    func_00440E20(op_0D7, 16#46200036, opfmt_8);
    func_00440E20(op_0D8, 16#46400036, opfmt_8);
    func_00440E20(op_0D9, 16#46000037, opfmt_8);
    func_00440E20(op_0DA, 16#46200037, opfmt_8);
    func_00440E20(op_0DB, 16#46400037, opfmt_8);
    func_00440E20(op_0DC, 16#46000038, opfmt_8);
    func_00440E20(op_0DD, 16#46200038, opfmt_8);
    func_00440E20(op_0DE, 16#46400038, opfmt_8);
    func_00440E20(op_0DF, 16#46000039, opfmt_8);
    func_00440E20(op_0E0, 16#46200039, opfmt_8);
    func_00440E20(op_0E1, 16#46400039, opfmt_8);
    func_00440E20(op_0E2, 16#4600003A, opfmt_8);
    func_00440E20(op_0E3, 16#4620003A, opfmt_8);
    func_00440E20(op_0E4, 16#4640003A, opfmt_8);
    func_00440E20(op_0E5, 16#4600003B, opfmt_8);
    func_00440E20(op_0E6, 16#4620003B, opfmt_8);
    func_00440E20(op_0E7, 16#4640003B, opfmt_8);
    func_00440E20(op_0E8, 16#4600003C, opfmt_8);
    func_00440E20(op_0E9, 16#4620003C, opfmt_8);
    func_00440E20(op_0EA, 16#4640003C, opfmt_8);
    func_00440E20(op_0EB, 16#4600003D, opfmt_8);
    func_00440E20(op_0EC, 16#4620003D, opfmt_8);
    func_00440E20(op_0ED, 16#4640003D, opfmt_8);
    func_00440E20(op_0EE, 16#4600003E, opfmt_8);
    func_00440E20(op_0EF, 16#4620003E, opfmt_8);
    func_00440E20(op_0F0, 16#4640003E, opfmt_8);
    func_00440E20(op_0F1, 16#4600003F, opfmt_8);
    func_00440E20(op_0F2, 16#4620003F, opfmt_8);
    func_00440E20(op_0F3, 16#4640003F, opfmt_8);
    func_00440E20(op_0FB, 16#4600000C, opfmt_8);
    func_00440E20(op_0FC, 16#4620000C, opfmt_8);
    func_00440E20(op_0FD, 16#4640000C, opfmt_8);
    func_00440E20(op_0FE, 16#4600000D, opfmt_8);
    func_00440E20(op_0FF, 16#4620000D, opfmt_8);
    func_00440E20(op_100, 16#4640000D, opfmt_8);
    func_00440E20(op_101, 16#4600000E, opfmt_8);
    func_00440E20(op_102, 16#4620000E, opfmt_8);
    func_00440E20(op_103, 16#4640000E, opfmt_8);
    func_00440E20(op_104, 16#4600000F, opfmt_8);
    func_00440E20(op_105, 16#4620000F, opfmt_8);
    func_00440E20(op_106, 16#4640000F, opfmt_8);
    func_00440E20(op_0F8, 16#46000026, opfmt_8);
    func_00440E20(op_0F9, 16#46200026, opfmt_8);
    func_00440E20(op_0FA, 16#46400026, opfmt_8);

    func_00440E54(zldl, afra, op_07F);
    func_00440E54(zldr, afra, op_080);
    func_00440E54(zlld, afra, op_081);
    func_00440E54(zsdl, afra, op_082);
    func_00440E54(zsdr, afra, op_083);
    func_00440E54(zscd, afra, op_084);
    func_00440E54(zdaddi, afrrr, op_061);
    func_00440E54(zdaddiu, afrrr, op_062);
    func_00440E54(zdadd, afrrr, op_024);
    func_00440E54(zdaddu, afrrr, op_025);
    func_00440E54(zdsub, afrrr, op_026);
    func_00440E54(zdsubu, afrrr, op_027);
    func_00440E54(zdsll, afrrr, op_028);
    func_00440E54(zdsrl, afrrr, op_029);
    func_00440E54(zdsra, afrrr, op_02A);
    func_00440E54(zdsllv, afrrr, op_02E);
    func_00440E54(zdsrlv, afrrr, op_02F);
    func_00440E54(zdsrav, afrrr, op_030);
    func_00440E54(zdmult, afrr, op_031);
    func_00440E54(zdmultu, afrr, op_032);
    func_00440E54(zddiv, afrrr, op_033);
    func_00440E54(zddivu, afrrr, op_034);
    func_00440E54(zlsc1, afra, op_085);
    func_00440E54(zssc1, afra, op_086);
    func_00440E54(zdmtc1, afrr, op_099);
    func_00440E54(zdmfc1, afrr, op_09A);
    func_00440E54(zdmtc0, afrr, op_09B);
    func_00440E54(zdmfc0, afrr, op_09C);
    func_00440E54(zdmtc2, afrr, op_09D);
    func_00440E54(zdmfc2, afrr, op_09E);
    func_00440E54(zlwu, afra, op_078);
    func_00440E54(zeret, af, op_11B);
    func_00440E54(fcvt_l_s, afrrr, op_113);
    func_00440E54(fcvt_l_d, afrrr, op_114);
    func_00440E54(fcvt_l_e, afrrr, op_115);
    func_00440E54(fcvt_l_w, afrrr, op_116);
    func_00440E54(fcvt_s_l, afrrr, op_117);
    func_00440E54(fcvt_d_l, afrrr, op_118);
    func_00440E54(fcvt_e_l, afrrr, op_119);
    func_00440E54(fcvt_w_l, afrrr, op_11A);
    func_00440E54(zround_l_s, afrrr, op_107);
    func_00440E54(ztrunc_l_s, afrrr, op_108);
    func_00440E54(zceil_l_s, afrrr, op_109);
    func_00440E54(zfloor_l_s, afrrr, op_10A);
    func_00440E54(zround_l_d, afrrr, op_10B);
    func_00440E54(ztrunc_l_d, afrrr, op_10C);
    func_00440E54(zceil_l_d, afrrr, op_10D);
    func_00440E54(zfloor_l_d, afrrr, op_10E);
    func_00440E54(zround_l_e, afrrr, op_10F);
    func_00440E54(ztrunc_l_e, afrrr, op_110);
    func_00440E54(zceil_l_e, afrrr, op_111);
    func_00440E54(zfloor_l_e, afrrr, op_112);
    func_00440E54(zcache, afra, op_09F);
    func_00440E54(zuld, afra, op_000);
    func_00440E54(zusd, afra, op_000);
    func_00440E54(zdabs, afrr, op_000);
    func_00440E54(zdneg, afrr, op_000);
    func_00440E54(zdnegu, afrr, op_000);
    func_00440E54(zdmul, afrrr, op_000);
    func_00440E54(zdmulo, afrrr, op_000);
    func_00440E54(zdmulou, afrrr, op_000);
    func_00440E54(zdrem, afrrr, op_033);
    func_00440E54(zdremu, afrrr, op_034);
    func_00440E54(zdrol, afrrr, op_000);
    func_00440E54(zdror, afrrr, op_000);
    func_00440E54(zdaddou, afrrr, op_025);
    func_00440E54(zdsubou, afrrr, op_027);
    func_00440E54(zulwu, afra, op_000);
    func_00440E54(zmovf, afrrr, op_087);
    func_00440E54(zmovt, afrrr, op_088);
    func_00440E54(zmovn, afrrr, op_089);
    func_00440E54(zmovz, afrrr, op_08A);
    func_00440E54(fmadd_s, afrrrr, op_11C);
    func_00440E54(fmadd_d, afrrrr, op_11D);
    func_00440E54(fmadd_e, afrrrr, op_11E);
    func_00440E54(fmsub_s, afrrrr, op_11F);
    func_00440E54(fmsub_d, afrrrr, op_120);
    func_00440E54(fmsub_e, afrrrr, op_121);
    func_00440E54(fnmadd_s, afrrrr, op_122);
    func_00440E54(fnmadd_d, afrrrr, op_123);
    func_00440E54(fnmadd_e, afrrrr, op_124);
    func_00440E54(fnmsub_s, afrrrr, op_125);
    func_00440E54(fnmsub_d, afrrrr, op_126);
    func_00440E54(fnmsub_e, afrrrr, op_127);
    func_00440E54(frecip_s, afrrr, op_128);
    func_00440E54(frecip_d, afrrr, op_129);
    func_00440E54(frsqrt_s, afrrr, op_12A);
    func_00440E54(frsqrt_d, afrrr, op_12B);
    func_00440E54(fmovf_s, afrrr, op_12C);
    func_00440E54(fmovf_d, afrrr, op_12D);
    func_00440E54(fmovt_s, afrrr, op_12E);
    func_00440E54(fmovt_d, afrrr, op_12F);
    func_00440E54(fmovn_s, afrrr, op_130);
    func_00440E54(fmovn_d, afrrr, op_131);
    func_00440E54(fmovz_s, afrrr, op_132);
    func_00440E54(fmovz_d, afrrr, op_133);
    func_00440E54(zlwxc1, afrrr, op_134);
    func_00440E54(zldxc1, afrrr, op_135);
    func_00440E54(zswxc1, afrrr, op_136);
    func_00440E54(zsdxc1, afrrr, op_137);
    func_00440E54(zpfetch, afrrr, op_138);
    func_00440E54(zpref, afra, op_13C);
    func_00440E54(zdctr, af, op_139);
    func_00440E54(zdctw, af, op_13A);
    func_00440E54(ztlbw, af, op_13B);

    func_00440E20(op_11B, 16#42000018, opfmt_5);
    func_00440E20(op_113, 16#46000025, opfmt_8);
    func_00440E20(op_114, 16#46200025, opfmt_8);
    func_00440E20(op_115, 16#46400025, opfmt_8);
    func_00440E20(op_116, 16#46800025, opfmt_8);
    func_00440E20(op_117, 16#46A00020, opfmt_8);
    func_00440E20(op_118, 16#46A00021, opfmt_8);
    func_00440E20(op_119, 16#46A00022, opfmt_8);
    func_00440E20(op_11A, 16#46A00024, opfmt_8);
    func_00440E20(op_107, 16#46000008, opfmt_8);
    func_00440E20(op_108, 16#46000009, opfmt_8);
    func_00440E20(op_109, 16#4600000A, opfmt_8);
    func_00440E20(op_10A, 16#4600000B, opfmt_8);
    func_00440E20(op_10B, 16#46200008, opfmt_8);
    func_00440E20(op_10C, 16#46200009, opfmt_8);
    func_00440E20(op_10D, 16#4620000A, opfmt_8);
    func_00440E20(op_10E, 16#4620000B, opfmt_8);
    func_00440E20(op_10F, 16#46400008, opfmt_8);
    func_00440E20(op_110, 16#46400009, opfmt_8);
    func_00440E20(op_111, 16#4640000A, opfmt_8);
    func_00440E20(op_112, 16#4640000B, opfmt_8);
    func_00440E20(op_07F, 16#68000000, opfmt_6);
    func_00440E20(op_080, 16#6C000000, opfmt_6);
    func_00440E20(op_081, 16#D0000000, opfmt_6);
    func_00440E20(op_082, 16#B0000000, opfmt_6);
    func_00440E20(op_083, 16#B4000000, opfmt_6);
    func_00440E20(op_084, 16#F0000000, opfmt_6);
    func_00440E20(op_061, 16#60000000, opfmt_0);
    func_00440E20(op_062, 16#64000000, opfmt_0);
    func_00440E20(op_024, 16#0000002C, opfmt_3);
    func_00440E20(op_025, 16#0000002D, opfmt_3);
    func_00440E20(op_026, 16#0000002E, opfmt_3);
    func_00440E20(op_027, 16#0000002F, opfmt_3);
    func_00440E20(op_028, 16#00000038, opfmt_3);
    func_00440E20(op_029, 16#0000003A, opfmt_3);
    func_00440E20(op_02A, 16#0000003B, opfmt_3);
    func_00440E20(op_02B, 16#0000003C, opfmt_3);
    func_00440E20(op_02C, 16#0000003E, opfmt_3);
    func_00440E20(op_02D, 16#0000003F, opfmt_3);
    func_00440E20(op_02E, 16#00000014, opfmt_3);
    func_00440E20(op_02F, 16#00000016, opfmt_3);
    func_00440E20(op_030, 16#00000017, opfmt_3);
    func_00440E20(op_031, 16#0000001C, opfmt_3);
    func_00440E20(op_032, 16#0000001D, opfmt_3);
    func_00440E20(op_033, 16#0000001E, opfmt_3);
    func_00440E20(op_034, 16#0000001F, opfmt_3);
    func_00440E20(op_085, 16#CC000000, opfmt_6);
    func_00440E20(op_086, 16#EC000000, opfmt_6);
    func_00440E20(op_099, 16#44A00000, opfmt_5);
    func_00440E20(op_09A, 16#44200000, opfmt_5);
    func_00440E20(op_09B, 16#40A00000, opfmt_5);
    func_00440E20(op_09C, 16#40200000, opfmt_5);
    func_00440E20(op_09D, 16#48A00000, opfmt_5);
    func_00440E20(op_09E, 16#48200000, opfmt_5);
    func_00440E20(op_078, 16#9C000000, opfmt_6);
    func_00440E20(op_09F, 16#BC000000, opfmt_10);
    func_00440E20(op_087, 16#00000001, opfmt_5);
    func_00440E20(op_088, 16#00010001, opfmt_5);
    func_00440E20(op_08A, 16#0000000A, opfmt_5);
    func_00440E20(op_089, 16#0000000B, opfmt_5);
    func_00440E20(op_11C, 16#4C000020, opfmt_8);
    func_00440E20(op_11D, 16#4C000021, opfmt_8);
    func_00440E20(op_11E, 16#4C000022, opfmt_8);
    func_00440E20(op_11F, 16#4C000028, opfmt_8);
    func_00440E20(op_120, 16#4C000029, opfmt_8);
    func_00440E20(op_121, 16#4C00002A, opfmt_8);
    func_00440E20(op_122, 16#4C000030, opfmt_8);
    func_00440E20(op_123, 16#4C000031, opfmt_8);
    func_00440E20(op_124, 16#4C000032, opfmt_8);
    func_00440E20(op_125, 16#4C000038, opfmt_8);
    func_00440E20(op_126, 16#4C000039, opfmt_8);
    func_00440E20(op_127, 16#4C00003A, opfmt_8);
    func_00440E20(op_128, 16#46000015, opfmt_8);
    func_00440E20(op_129, 16#46200015, opfmt_8);
    func_00440E20(op_12A, 16#46000016, opfmt_8);
    func_00440E20(op_12B, 16#46200016, opfmt_8);
    func_00440E20(op_12C, 16#46000011, opfmt_8);
    func_00440E20(op_12D, 16#46200011, opfmt_8);
    func_00440E20(op_12E, 16#46010011, opfmt_8);
    func_00440E20(op_12F, 16#46210011, opfmt_8);
    func_00440E20(op_132, 16#46000012, opfmt_8);
    func_00440E20(op_133, 16#46200012, opfmt_8);
    func_00440E20(op_130, 16#46000013, opfmt_8);
    func_00440E20(op_131, 16#46200013, opfmt_8);
    func_00440E20(op_134, 16#4C000000, opfmt_5);
    func_00440E20(op_135, 16#4C000001, opfmt_5);
    func_00440E20(op_136, 16#4C000008, opfmt_5);
    func_00440E20(op_137, 16#4C000009, opfmt_5);
    func_00440E20(op_138, 16#4C00000F, opfmt_5);
    func_00440E20(op_13C, 16#CC000000, opfmt_6);
    func_00440E20(op_139, 16#43000009, opfmt_5);
    func_00440E20(op_13A, 16#4300000A, opfmt_5);
    func_00440E20(op_13B, 16#43000002, opfmt_5);

    func_00440E54(zbc3f, afl, op_13F);
    func_00440E54(zbc3t, afl, op_140);
    func_00440E54(zc3, aforrr, op_141);
    func_00440E54(zlwc3, afra, op_142);
    func_00440E54(zswc3, afra, op_143);
    func_00440E54(zmfc3, afrr, op_144);
    func_00440E54(zmtc3, afrr, op_145);
    func_00440E54(zcfc3, afrr, op_146);
    func_00440E54(zctc3, afrr, op_147);

    func_00440E20(op_13F, 16#4D000000, opfmt_2);
    func_00440E20(op_140, 16#4D010000, opfmt_2);
    func_00440E20(op_141, 16#4E000000, opfmt_5);
    func_00440E20(op_142, 16#CC000000, opfmt_6);
    func_00440E20(op_143, 16#EC000000, opfmt_6);
    func_00440E20(op_144, 16#4C000000, opfmt_5);
    func_00440E20(op_145, 16#4C800000, opfmt_5);
    func_00440E20(op_146, 16#4C400000, opfmt_5);
    func_00440E20(op_147, 16#4CC00000, opfmt_5);

    func_00440E54(zmfpc, afrr, op_148);
    func_00440E54(zmtpc, afrr, op_149);
    func_00440E54(zmfps, afrr, op_14A);
    func_00440E54(zmtps, afrr, op_14B);

    func_00440E20(op_148, 16#4000C801, opfmt_5);
    func_00440E20(op_149, 16#4080C801, opfmt_5);
    func_00440E20(op_14A, 16#4000C800, opfmt_5);
    func_00440E20(op_14B, 16#4080C800, opfmt_5);
    
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
                currentline := arg0^.unk60;
                currentfile := arg0^.unk5C;
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
    sp70: integer;
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

    if (string3.f^[1] = chr(0)) then begin
        sp70 := strlen(string1.f);
        if (sp70 >= 1022) then begin
            PostError("File name too long on command line", string1, ErrorLevel_1);
            exit(1);
        end;

        for i := 1 to sp70 do begin
            string3.f^[i] := string1.f^[i];
        end;

        if ((sp70 >= 3) and (string1.f^[sp70] = 'G') and (string1.f^[sp70 - 1] = '.')) then begin
            string3.f^[sp70 - 1] := sp6B;
            string3.f^[sp70] := sp6A;
        end else begin
            sp70 := sp70 + 1;
            string3.f^[sp70] := sp6B;
            sp70 := sp70 + 1;
            string3.f^[sp70] := sp6A;
        end;
        
        string3.f^[sp70 + 1] := chr(0);
    end;

    if not(mscoff) then begin
        if (st_readbinary(string3.st^, 'a') = -2) then begin
            call_perror(1, string3);
        end else begin
            string3.f^[1] := chr(0);
            st_asinit(string3.f^, debugflag);
        end;
    end else if (ms_readsym(string3.f^) = -1) then begin
        call_perror(1, string3);
    end;
end;

procedure func_0044A0C0();
var
    i: integer;
begin
    if (string3.f^[1] <> chr(0)) then begin
        PostError("Because file contains iasm0 directive, -t option is ignored", string1, ErrorLevel_2);
    end;
    
    st_cuinit();
    for i := 1 to strlen(outname.f) + 1 do begin
        string3.f^[i] := outname.f^[i];
    end;
    st_asinit(string3.f^, debugflag);
end;

begin { start of main }
    xpg_flag := false;
    sp104 := "_XPG";
    sp104[5] := chr(0);
    if (getenv(sp104) <> 0) then begin
        xpg_flag := TRUE;
    end;

    func_00441024();
    reset(binasm_file, string1.f^);

    if (Eof(binasm_file) and (Filesize(binasm_file) <> 0)) then begin
        call_perror(1, string1);
        return 0;
    end;
    
    init_binasm();
    if (binasmfyle^.instr = iasm0) then begin
        func_0044A0C0();
    end else if (binasmfyle^.instr = iverstamp) then begin
        func_00449DCC();
    end else begin
        PostError("Obsolete or corrupt binasm file ", string1, ErrorLevel_1);
    end;

    if ((severity >= severity_level_2) and not(eof(binasm_file))) then begin
        if (profileflag >= 2) then begin 
            mcount_address := enter_undef_sym(l_addr(addr(mcount_sym)));
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

            if (eof(binasm_file) or (lastinstr = iend) and not pendinginstr) then begin
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

    if (use_ddopt_info) then begin
        dd_close();
    end;

    if (severity >= severity_level_2) then begin
        if (not elf_flag) then begin
            nonzero_scnbase := true;
        end;
        wrobj();
    end;

    if verbose then begin
        writeln(err);
    end;

    if ((severity <= severity_level_1) or (warnexitflag and (severity <= severity_level_2))) then begin
        halt(1);
    end;
    return 0;
end.