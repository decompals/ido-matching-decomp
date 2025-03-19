#include "cmplrs/stinfc.h"
#include "cmplrs/usys.h"
#include "cmplrs/binasm.h"
#include "array.h"

type
    Byte = 0..16#FF;
    short = 0..16#FFFF;

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
    
    PBinasm = ^binasm;
    FileOfBinasm = File of binasm;

    ErrorLevel = (
        ErrorLevel_0,
        ErrorLevel_1,
        ErrorLevel_2
    );

    opcodes = (
        op_macro, op_znop, op_zsll, op_zsrl, op_zsra, op_zsllv, op_zsrlv, op_zsrav, { 0 - 7 }
        op_zjr, op_zjalr, op_zsyscall, op_zbreak, op_zmfhi, op_zmthi, op_zmflo, op_zmtlo, { 8 - 15 }
        op_zmult, op_zmultu, op_zdiv, op_zdivu, op_zadd, op_zaddu, op_zsub, op_zsubu, { 16 - 23 }
        op_zand, op_zor, op_zxor, op_znor, op_zslt, op_zsltu, op_ztlt, op_ztltu, { 24 - 31 }
        op_ztge, op_ztgeu, op_zteq, op_ztne, op_zdadd, op_zdaddu, op_zdsub, op_zdsubu, { 32 - 39 }
        op_zdsll, op_zdsrl, op_zdsra, op_zdsll32, op_zdsrl32, op_zdsra32, op_zdsllv, op_zdsrlv, { 40 - 47 }
        op_zdsrav, op_zdmult, op_zdmultu, op_zddiv, op_zddivu, op_zbltz, op_zbgez, op_zbltzal, { 48 - 55 }
        op_zbgezal, op_zbc0f, op_zbc0t, op_zbc1f, op_zbc1t, op_zbc2f, op_zbc2t, op_zbltzl, { 56 - 63 }
        op_zbgezl, op_zbltzall, op_zbgezall, op_zbc0fl, op_zbc0tl, op_zbc1fl, op_zbc1tl, op_zbc2fl, { 64 - 71 }
        op_zbc2tl, op_zj, op_zjal, op_zbeq, op_zbne, op_zblez, op_zbgtz, op_zbeql, { 72 - 79 }
        op_zbnel, op_zblezl, op_zbgtzl, op_zaddi, op_zaddiu, op_zslti, op_zsltiu, op_zandi, { 80 - 87 }
        op_zori, op_zxori, op_zlui, op_ztlti, op_ztltiu, op_ztgei, op_ztgeiu, op_zteqi, { 88 - 95 }
        op_ztnei, op_zdaddi, op_zdaddiu, op_zc0, op_zc1, op_zc2, op_zlb, op_zlh, { 96 - 103 }
        op_zlwl, op_zlw, op_zlbu, op_zlhu, op_zlwr, op_zsb, op_zsh, op_zswl, { 104 - 111 }
        op_zsw, op_zswr, op_zll, op_zlwc1, op_zlwc2, op_zsc, op_zswc1, op_zswc2, { 112 - 119 }
        op_zlwu, op_zld, op_zsd, op_zldc1, op_zldc2, op_zsdc1, op_zsdc2, op_zldl, { 120 - 127 }
        op_zldr, op_zlld, op_zsdl, op_zsdr, op_zscd, op_zlsc1, op_zssc1, op_zmovf, { 128 - 135 }
        op_zmovt, op_zmovn, op_zmovz, op_zmfc0, op_zmfc1, op_zmfc2, op_zcfc1, op_zmtc0, { 136 - 143 }
        op_zmtc1, op_zmtc2, op_zctc1, op_zrfe, op_ztlbr, op_ztlbwi, op_ztlbwr, op_ztlbp, { 144 - 151 }
        op_zsync, op_zdmtc1, op_zdmfc1, op_zdmtc0, op_zdmfc0, op_zdmtc2, op_zdmfc2, op_zcache, { 152 - 159 }
        op_fadd_s, op_fadd_d, op_fadd_e, op_fsub_s, op_fsub_d, op_fsub_e, op_fmul_s, op_fmul_d, { 160 - 167 }
        op_fmul_e, op_fdiv_s, op_fdiv_d, op_fdiv_e, op_fsqrt_s, op_fsqrt_d, op_fsqrt_e, op_fabs_s, { 168 - 175 }
        op_fabs_d, op_fabs_e, op_fmov_s, op_fmov_d, op_fmov_e, op_fneg_s, op_fneg_d, op_fneg_e, { 176 - 183 }
        op_fcvt_s_d, op_fcvt_s_e, op_fcvt_s_w, op_fcvt_d_s, op_fcvt_d_e, op_fcvt_d_w, op_fcvt_e_s, op_fcvt_e_d, { 184 - 191 }
        op_fcvt_e_w, op_fcvt_w_s, op_fcvt_w_d, op_fcvt_w_e, op_fc_f_s, op_fc_f_d, op_fc_f_e, op_fc_un_s, { 192 - 199 }
        op_fc_un_d, op_fc_un_e, op_fc_eq_s, op_fc_eq_d, op_fc_eq_e, op_fc_ueq_s, op_fc_ueq_d, op_fc_ueq_e, { 200 - 207 }
        op_fc_olt_s, op_fc_olt_d, op_fc_olt_e, op_fc_ult_s, op_fc_ult_d, op_fc_ult_e, op_fc_ole_s, op_fc_ole_d, { 208 - 215 }
        op_fc_ole_e, op_fc_ule_s, op_fc_ule_d, op_fc_ule_e, op_fc_sf_s, op_fc_sf_d, op_fc_sf_e, op_fc_ngle_s, { 216 - 223 }
        op_fc_ngle_d, op_fc_ngle_e, op_fc_seq_s, op_fc_seq_d, op_fc_seq_e, op_fc_ngl_s, op_fc_ngl_d, op_fc_ngl_e, { 224 - 231 }
        op_fc_lt_s, op_fc_lt_d, op_fc_lt_e, op_fc_nge_s, op_fc_nge_d, op_fc_nge_e, op_fc_le_s, op_fc_le_d, { 232 - 239 }
        op_fc_le_e, op_fc_ngt_s, op_fc_ngt_d, op_fc_ngt_e, op_zcfc0, op_zcfc2, op_zctc0, op_zctc2, { 240 - 247 }
        op_fli_s, op_fli_d, op_fli_e, op_zround_w_s, op_zround_w_d, op_zround_w_e, op_ztrunc_w_s, op_ztrunc_w_d, { 248 - 255 }
        op_ztrunc_w_e, op_zceil_w_s, op_zceil_w_d, op_zceil_w_e, op_zfloor_w_s, op_zfloor_w_d, op_zfloor_w_e, op_zround_l_s, { 256 - 263 }
        op_ztrunc_l_s, op_zceil_l_s, op_zfloor_l_s, op_zround_l_d, op_ztrunc_l_d, op_zceil_l_d, op_zfloor_l_d, op_zround_l_e, { 264 - 271 }
        op_ztrunc_l_e, op_zceil_l_e, op_zfloor_l_e, op_fcvt_l_s, op_fcvt_l_d, op_fcvt_l_e, op_fcvt_l_w, op_fcvt_s_l, { 272 - 279 }
        op_fcvt_d_l, op_fcvt_e_l, op_fcvt_w_l, op_zeret, op_fmadd_s, op_fmadd_d, op_fmadd_e, op_fmsub_s, { 280 - 287 }
        op_fmsub_d, op_fmsub_e, op_fnmadd_s, op_fnmadd_d, op_fnmadd_e, op_fnmsub_s, op_fnmsub_d, op_fnmsub_e, { 288 - 295 }
        op_frecip_s, op_frecip_d, op_frsqrt_s, op_frsqrt_d, op_fmovf_s, op_fmovf_d, op_fmovt_s, op_fmovt_d, { 296 - 303 }
        op_fmovn_s, op_fmovn_d, op_fmovz_s, op_fmovz_d, op_zlwxc1, op_zldxc1, op_zswxc1, op_zsdxc1, { 304 - 311 }
        op_zpfetch, op_zdctr, op_zdctw, op_ztlbw, op_zpref, op_ztlbr1, op_ztlbp1, op_zbc3f, { 312 - 319 }
        op_zbc3t, op_zc3, op_zlwc3, op_zswc3, op_zmfc3, op_zmtc3, op_zcfc3, op_zctc3, { 320 - 327 }
        op_zmfpc, op_zmtpc, op_zmfps, op_zmtps { 328 - 331 }
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

    UnkPiInstr_Record = Record;
        rfd: cardinal;
        unk4: integer;
        unk8: integer;
        unkC: integer;
        unk10: integer;
        unk14: integer;
        unk18: integer;
        unk1C: integer;
        unk20: boolean;
        unk21: boolean;
        unk22: boolean;
        unk23: boolean;
        unk24: opcodes;
    end;
    UnkPiInstr_Array = array [0..15] of UnkPiInstr_Record;

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
        { 0x34 } unk34: char;
        { 0x35 } unk35: Byte;
        { 0x36 } unk36: Byte;
        { 0x37 } unk37: boolean;
        { 0x38 } unk38: boolean;
        { 0x39 } unk39: boolean;
        { 0x3A } unk3A: boolean;
        { 0x3B } unk3B: boolean;
        { 0x3C } unk3C: boolean;
        { 0x3D } unk3D: boolean;
        { 0x3D } unk3E: boolean;
        { 0x3D } unk3F: registers;
        { 0x40 } unk40: registers;
        { 0x44 } unk44: integer;
        { 0x48 } unk48: integer;
        { 0x4C } unk4C: integer;
        { 0x50 } unk50: integer;
        { 0x54 } unk54: integer;
        { 0x58 } unk58: integer;
        { 0x5C } currfile: integer;
        { 0x60 } currline: integer;
    end;

    PUnkAlpha = ^UnkAlpha;

    RldRec = Record
        { 0x00 } unk00: integer;
        { 0x04 } unk04: integer;
        { 0x08 } unk08: ^UnkAlpha;
        { 0x0C } unk0C: integer;
        { 0x10 } unk10: byte;
        { 0x11 } unk11: registers;
        { 0x14 } unk14: integer;
    end;

    ARRAY_DECLARE(RldRec);

    PreReorderPeepholesRec = record
        unk_00: integer;
        unk_04: integer;
        unk_08: integer;
        unk_0C: integer;
        unk_10: integer;
        unk_14: packed array [1..32] of char;
    end;

    segments = (
        seg_text,
        seg_sdata,
        seg_data,
        seg_3,
        seg_4,
        seg_5,
        seg_6,
        seg_7,
        seg_8,
        seg_rdata,
        seg_10,
        seg_11,
        seg_12,
        seg_13,
        seg_14,
        seg_15,
        seg_16,
        seg_17,
        seg_18,
        seg_19,
        seg_20
    );

    PrevSDataType = Record
        { 0x00 } unk00: integer;
        { 0x04 } unk04: boolean;
        { 0x08 } unk08: integer;
        { 0x0C } unk0C: integer;
        { 0x10 } unk10: integer;
    end;

    ARRAY_DECLARE(integer);
    ARRAY_DECLARE(short);
    ARRAY_DECLARE(char);

    MemoryUnion = record
    case integer of
        1: (b: ARRAY_OF(char););
        2: (h: ARRAY_OF(short));
        4: (w: ARRAY_OF(integer));
    end;

    MemoryRec = record
        unk_00: MemoryUnion;
        unk_08: segments;
        unk_09: packed array [1..32] of char;
    end;
    ARRAY_DECLARE(MemoryRec);

    PdrRec = record
        next: ^PdrRec;
        unk04: integer;
        unk08: integer;
        unk0C: integer;
        unk10: PUnkAlpha;
        unk14: PUnkAlpha;
    end;

    OptRecord = record;
        unk_00: array[1..5] of boolean;
        unk_08: array[1..5] of integer;
        unk_1C: Byte;
        unk_1D: boolean;
        unk_1E: boolean;
    end;

var
    emptystring: extern GString;
    gpreg: extern registers;
    reorderflag: extern boolean;
    pinstruction: extern ^UnkPiInstr_Array;
    binasmfyle: extern PBinasm;
    asm2op: extern array [first(asmcodes)..last(asmcodes)] of opcodes;
    bbindex: extern integer;
    endofbasicb: extern boolean;
    cia_binasm_name: extern GString;
    outname: extern GString;
    mainpath: extern GString;
    cia_bfile: extern File of binasm;
    in_cia_binasm: extern boolean;
    diag_flag: extern boolean;
    proc_instr_base: extern integer;
    rld_list: extern ARRAY_OF(RldRec);
    nextrld: extern integer;
    atflag: extern boolean;
    bigendian: extern boolean;
    moxieflag: extern boolean;
    picflag: extern integer;
    big_got: extern boolean;
    branchops: extern set of opcodes;
    pre_reorder_peepholes: extern PreReorderPeepholesRec;
    currsegment: extern segments;
    prev_sdata: extern array[seg_sdata..seg_data] of PrevSDataType;
    prev_align: extern array[seg_text..seg_20] of PrevSDataType;
    seg_ic: extern ARRAY_OF(integer);
    aligning: extern boolean;
    currsegmentindex: extern integer;
    realsegments: extern set of segments;
    memory: extern ARRAY_OF(MemoryRec);
    gprelsize: extern integer;
    firstusertextseg: extern integer;
    lastusertextseg: extern integer;
    nextlabelchain: extern ARRAY_OF(integer);
    currtextindex: extern integer;
    excpt_opt: extern boolean;
    currfunc_hasedata: extern boolean;
    is_nonleaf: extern boolean;
    sexchange: extern boolean;
    currfunc_sym: extern ^UnkAlpha;
    lastinstr: extern itype;
    pendinginstr: extern boolean;
    adjust_frame_by_ld: extern boolean;
    currentline: extern integer;
    debugflag: extern integer;
    verbose: extern boolean;
    currentfile: extern integer;
    currentent: extern integer;
    currentent_name: extern GString;
    initial_loc: extern boolean;
    optflag: extern integer;
    fromas0: extern boolean;
    saw_pic_flag: extern boolean;
    saw_cap_g: extern boolean;
    first_pdr: extern ^PdrRec;
    last_pdr: extern ^PdrRec;
    macroflag: extern boolean;
    has_noreorder: extern boolean;
    non_reorg_flag: extern cardinal;
    transform_flag: extern boolean;
    opts: extern OptRecord;
    volatileflag: extern boolean;
    movableflag: extern boolean;
    shftaddr: extern integer;
    sixtyfour_bit: extern boolean;
    elf_flag: extern boolean;
    gp_disp_address: extern PUnkAlpha;
    gp_disp_sym: extern st_string;
    profileflag: extern integer;
    binasm_file: extern FileOfBinasm;
    last_bb: extern array [1..3] of Byte;
    known_framesize: extern integer;
    max_arg_build: extern integer;
    ent_pending: extern boolean;
    gjaldef: extern aligned_regset;
    gjallive: extern aligned_regset;
    gjrlive: extern aligned_regset;
    restext: extern boolean;
    liveset: extern integer;
    binlive: extern cardinal;
    fltlive: extern cardinal;
    asm2asmformat: extern array [first(asmcodes)..last(asmcodes)] of asmformat;
    br_likely_ops: extern set of opcodes;
    num_pseudo: extern integer;
    
procedure ltoa(arg0: integer; arg1: ^char); external;
procedure PostError(arg0: String; arg1: GString; arg2: ErrorLevel); external;
procedure p_assertion_failed(arg0: String; arg1: String; arg2: cardinal); external;
procedure definealabel(arg0: integer; arg1: integer; arg2: integer); external;
function grow_array(var arg0: integer; arg1: cardinal; arg2: cardinal; arg3: pointer; arg4: boolean): pointer; external;
function strlen(p : ^Filename): integer; external;
function strcpy(dst : ^Filename; src: ^Filename): pointer; external;
function xmalloc(size: integer): pointer; external;
function l_addr(var value: st_string): pointer; external;
function enter_undef_sym(ptr: pointer): PUnkAlpha; external;
function idn_for_data(): integer; external;
procedure defineasym(arg0: integer; arg1: PUnkAlpha; arg2: integer); external;
function ll_load_immed(arg0: integer; arg1: integer; arg2: registers): boolean; external;
procedure do_parseafra(arg0: asmcodes; arg1: registers; arg2: PUnkAlpha; arg3: integer; arg4: registers); external;
function fixup_symno(symno: integer): integer; external;
procedure fixup_preceding_labels(align: integer); external;
procedure parsefpconst(which: itype); external;
procedure parse_mtag(tagnumber: integer; tagtype: integer); external;
procedure parse_malias(memtag1: integer; memtag2: integer); external;
procedure init_multi_relocinst(); external;
procedure init_malias_table(); external;
procedure initbb(var index: integer); external;
procedure parseafrrr(fasm: asmcodes); external;
procedure parseafra(fasm: asmcodes); external;
procedure parseafri_fp(fasm: asmcodes); external;
