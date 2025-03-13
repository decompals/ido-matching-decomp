#include "common.i"

var
    { .data }
    last_globl_symno: integer := 0;
    label_size: integer := 0;

    need_cprestore: boolean;
    cpalias_set: boolean;
    cpalias_pending: boolean;
    cprestore_offset: integer;
    framereg_for_cprestore: registers;
    cpalias_register: registers;
    branchpending: boolean;
    frame_ptr: registers;
    fpop_src3: registers;
    currfunc_start: integer;
    currfunc_end: integer;
    currfunc_handle: integer;
    currfunc_data: integer;
    currfunc_prolog: integer;
    lastsymno: integer;
    lastdata: integer;
    lexicallevel: integer;
    ignore_frames: boolean;
    saw_option_pic: boolean;
    which_ent: array [false..true] of integer;

procedure fill_pseudo(arg0: integer; arg1: integer; arg2: integer; arg3: integer; arg4: PUnkALpha; arg5: integer); external; { TODO signature }
procedure st_pseudo(arg0: integer; arg1: integer; arg2: integer; arg3: registers; arg4: integer; arg5: integer; arg6: integer); external; { TODO signature }
procedure fill_ascii_pseudo(var str: st_string; size: integer; arg2: boolean); external;
procedure get_binasm(var b: PBinasm); external;
function stp(symno: integer): PUnkAlpha; external;
procedure enterstp(symno: integer); external;
procedure enterlabel(symno: integer; var sym: PUnkAlpha); external;
procedure entersym(symno: integer; var sym: PUnkAlpha); external;
procedure _setrld(sym: PUnkAlpha; arg1: integer; arg2: integer); external;
procedure loadimmed(arg0: integer; arg1: registers; arg2: PUnkAlpha); external;
procedure emitloadstore(op: opcodes; reg1: registers; offset: integer; reg2: registers); external;
procedure emitalui(op: opcodes; reg1: registers; reg2: registers; imm: integer); external;
procedure emitreg2(op: opcodes; reg1: registers; reg2: registers); external;
procedure emitalu3(op: opcodes; reg1: registers; reg2: registers; reg3: registers); external;
procedure emitfpop(op: opcodes; reg1: registers; reg2: registers; reg3: registers); external;
procedure emitspec(op: opcodes; arg1: integer); external;
procedure emitbene(op: opcodes; reg1: registers; reg2: registers; sym: PUnkAlpha; imm: integer); external;
procedure emitbcond(op: opcodes; reg1: registers; sym: PUnkAlpha; imm: integer); external;
procedure emitjump(op: opcodes; arg1: integer; arg2: integer); external;
procedure emitnop(count: integer); external;
procedure emitmvcoproc(op: opcodes; reg1: registers; reg2: registers); external;
procedure emitcoproc(op: opcodes; arg1: integer); external;
function call_as0(var arg0: Filename; var arg1: Filename; var arg2: Filename) : integer; external;
function is_dso_static(arg0: integer): boolean; external;
function islocalsym(arg0: PUnkAlpha): boolean; external;
function power2(arg0: integer): integer; external;
procedure enter_symbol(name: ^Filename; size: integer; arg2: integer); external;
procedure reenter_symbol(name: ^Filename; size: integer); external;
procedure add_data_to_gp_table(seg: segments; arg1: integer); external;
function st_add_deltasym(sc: integer; arg1: integer; index: integer): integer; external;
function pseudo_type(arg0: integer): integer; external;
procedure save_cur_proc_id(var arg0: Filename); external;
procedure call_name_and_line(arg0: integer); external;
procedure byte_at_a_time(segm: integer; arg1: integer; arg2: integer; arg3: integer); external;

procedure macro_error;
begin
    PostError("macro instruction used $at", emptystring, ErrorLevel_2);
end;
{ required to match caseerror }
{ #line 100 "as1parse.p" }

function disp(arg0: boolean; arg1: cardinal): cardinal;
begin
    if arg0 then begin
        if (bitand(arg1, 16#8000) <> 0) then begin
            disp := bitand(rshift(arg1, 16) + 1, 16#FFFF);
        end else begin
            disp := bitand(rshift(arg1, 16), 16#FFFF);
        end;
    end else begin
        if (bitand(arg1, 16#8000) <> 0) then begin
            disp := bitand(arg1, 16#FFFF) - 16#10000;
        end else begin
            disp := bitand(arg1, 16#FFFF);
        end;
    end;
end;

procedure restore_gp;
begin
    if need_cprestore then begin
        if (cprestore_offset >= -16#8000) and (cprestore_offset <= 16#7FFF) then begin
            emitloadstore(op_zlw, gpreg, cprestore_offset, framereg_for_cprestore);
        end else if (cprestore_offset >= 16#8000) and (cprestore_offset < 16#FFFF) then begin
            emitalui(op_zaddiu, gpreg, framereg_for_cprestore, 16#7FFF);
            emitloadstore(op_zlw, gpreg, cprestore_offset - 16#7FFF, gpreg);
        end else begin
            emitalui(op_zlui, gpreg, xr0, disp(true, cprestore_offset));
            emitalu3(op_zaddu, gpreg, gpreg, framereg_for_cprestore);
            emitloadstore(op_zlw, gpreg, disp(false, cprestore_offset), gpreg);
        end;
        need_cprestore := false;
    end;
end;

procedure init_cpalias;
begin
    if cpalias_set and cpalias_pending then begin
        emitalu3(op_zor, cpalias_register, xr0, xr28);
        gpreg := cpalias_register;
        cpalias_pending := false;
        fill_pseudo(28, integer(gpreg), 29, 0, nil, 0);
    end;
end;

procedure parseaf(fasm: asmcodes);
var
    ba: ^binasm;
begin
    ba := binasmfyle;

    if fasm = znop then begin
        if reorderflag then begin
            PostError("nop must be inside .set noreorder section", emptystring, ErrorLevel_2);    
        end;
        emitnop(1);
        pinstruction^[bbindex].unk22 := false;
    end else begin
        if (ba^.form = fi) then begin
            emitspec(asm2op[fasm], ba^.imm);
        end else begin
            emitspec(asm2op[fasm], 0);
        end;
    end;

    endofbasicb := (fasm <> znop);
end;

procedure parsecia;
var
    length: integer;
    i: integer;
    offset: integer;
    buffer: GString;
begin
    
    length := binasmfyle^.immediate;
    endofbasicb := true;
    new(buffer.f);
    
    offset := 0;
    get_binasm(binasmfyle);    
    while length > 16 do begin
        for i := 1 to 16 do begin
            buffer.f^[i + offset] := binasmfyle^.data[i];
        end;
        offset := offset + i - 1;
        length := length - 16;
        get_binasm(binasmfyle);
    end;

    for i := 1 to length do begin
        buffer.f^[i + offset] := binasmfyle^.data[i];
    end;
    buffer.f^[offset + i] := chr(0);

    new(cia_binasm_name.f);
    cia_binasm_name.f^ := outname.f^;

    if (call_as0(mainpath.f^, cia_binasm_name.f^, buffer.f^) = 0) then begin
        reset(cia_bfile, cia_binasm_name.f^);
        in_cia_binasm := true;
    end;
end;

procedure parseafri(fasm: asmcodes);
var
    reg: registers;
    immediate: integer;
    sym: PUnkAlpha;
    ba: ^binasm;
begin
    ba := binasmfyle;

    if fasm = zcia then begin
        parsecia();
        return;
    end;
    
    immediate := ba^.immediate;
    reg := ba^.reg1;    

    if diag_flag and (ba^.form = frri) then begin
        if fasm <> zlui then begin
            p_assertion_failed("fasm = zlui\0", "as1parse.p", 264);
        end;
        emitalui(op_zlui, reg, ba^.reg2, bitand(rshift(immediate, 16), 16#FFFF)); { ba^.imm ??? }
        return;
    end;
    
    if ba^.form <> fri then begin
        p_assertion_failed("form = fri\0", "as1parse.p", 269);
    end;

    if ba^.formextn = frahi then begin
        if fasm <> zlui then begin
            p_assertion_failed("fasm = zlui\0", "as1parse.p", 271);
        end;
        sym := nil;
        if ba^.symno <> 0 then begin
            sym := stp(ba^.symno);
        end;
        emitalui(op_zlui, reg, xr0, disp(true, immediate));
        if sym <> nil then begin
            _setrld(sym, 13, bbindex + proc_instr_base);
        end;
        ARRAY_AT(rld_list, nextrld - 1).unk14 := immediate; { NON MATCHING LINE }
        ARRAY_AT(rld_list, nextrld - 1).unk11 := reg;
        return;
    end;

    if ba^.formextn = frcprel then begin
        if fasm <> zli then begin
            p_assertion_failed("fasm = zli\0", "as1parse.p", 283);
        end;
        if ba^.symno = 0 then begin
            p_assertion_failed("symno <> 0\0", "as1parse.p", 285);
        end;
        loadimmed(immediate, reg, stp(ba^.symno));
    end else if (fasm = zlui) and (immediate = 0) then begin
        emitalui(op_zlui, reg, xr0, immediate);
    end else begin
        loadimmed(immediate, reg, nil);
    end;
end;

procedure parseafrrl(fasm: asmcodes; arg1: boolean);
var
    reg1: registers;
    reg2: registers;
    spCD: registers;
    spCC: registers;    
    sym: PUnkAlpha;
    spC6: opcodes;
    spC5: boolean;
    spC0: integer;
    spBC: integer;
    ba: ^binasm;
begin
    if cpalias_set then begin
        init_cpalias();
    end else begin
        restore_gp();
    end;

    ba := binasmfyle;
    
    branchpending := true;
    reg1 := ba^.reg1;

    if ba^.reg1 in [xfr0..xfr31] then begin
        p_assertion_failed("not (reg1 in [xfr0..xfr31])\0", "as1parse.p", 350);
    end;

    sym := nil;
    if (ba^.formextn = frrel1) then begin
        spBC := ba^.mem_tag;
    end else if (ba^.formextn = frrel2) then begin
        spBC := -ba^.mem_tag - 1;
    end else if arg1 then begin
        spBC := ba^.symno;
    end else begin
        sym := stp(ba^.symno);
        spBC := 0;
    end;

    if ba^.form = frrl then begin
        spC5 := false;
        spC0 := 0;
        reg2 := ba^.reg2;
    end else if ba^.form = fril then begin
        reg2 := xnoreg;
        spC0 := ba^.immediate;        
        spC5 := true;
    end else begin
        p_assertion_failed("false\0", "as1parse.p", 376);
    end;

    case fasm of
        zbeq,
        zbne,
        zbeql,
        zbnel:
            if spC5 then begin
                if spC0 = 0 then begin
                    emitbene(asm2op[fasm], reg1, xr0, sym, spBC);
                end else begin
                    if not atflag then begin
                        macro_error();
                    end;
                    loadimmed(spC0, xr1, nil);
                    emitbene(asm2op[fasm], reg1, xr1, sym, spBC);
                end;
            end else begin
                emitbene(asm2op[fasm], reg1, reg2, sym, spBC);
            end;
        zbge,
        zbgeu,
        zbgt,
        zbgtu,
        zble,
        zbleu,
        zblt,
        zbltu,
        zblel,
        zbleul,
        zbgtl,
        zbgtul,
        zbltl,
        zbltul,
        zbgel,
        zbgeul:
            begin
                if reg2 = xr0 then begin
                    reg2 := xnoreg;
                    spC5 := true;
                    spC0 := 0;
                end else if (reg1 = xr0) and (ba^.form = frrl) then begin
                    reg1 := reg2;
                    reg2 := xnoreg;
                    spC5 := true;
                    spC0 := 0;
                    case fasm of
                        zbge: fasm := zble;
                        zbgt: fasm := zblt;
                        zble: fasm := zbge;
                        zblt: fasm := zbgt;
                        zbgeu: fasm := zbleu;
                        zbgtu: fasm := zbltu;
                        zbleu: fasm := zbgeu;
                        zbltu: fasm := zbgtu;
                        zbgel: fasm := zblel;
                        zbgtl: fasm := zbltl;
                        zblel: fasm := zbgel;
                        zbltl: fasm := zbgtl;
                        zbgeul: fasm := zbleul;
                        zbgtul: fasm := zbltul;
                        zbleul: fasm := zbgeul;
                        zbltul: fasm := zbgtul;
                        otherwise:
                    end;
                end;
                
                if spC5 and (spC0 <> 0) then begin
                    case fasm of
                        zbge:
                            if spC0 = 1 then begin
                                fasm := zbgt;
                                spC0 := 0;
                            end;
                        zbgeu:
                            if spC0 = 1 then begin
                                fasm := zbgtu;
                                spC0 := 0;
                            end;
                        zblt:
                            if spC0 = 1 then begin
                                fasm := zble;
                                spC0 := 0;
                            end;
                        zbltu:
                            if spC0 = 1 then begin
                                fasm := zbleu;
                                spC0 := 0;
                            end;
                        zble:
                            if spC0 = 16#7FFFFFFF then begin
                                emitbene(op_zbeq, xr0, xr0, sym, spBC);
                                return;
                            end else begin
                                fasm := zblt;
                                spC0 := spC0 + 1;
                            end;
                        zbleu:
                            if spC0 = -1 then begin
                                emitbene(op_zbeq, xr0, xr0, sym, spBC);
                                return;
                            end else begin
                                fasm := zbltu;
                                spC0 := spC0 + 1;
                            end;
                        zbgt:
                            begin
                                fasm := zbge;
                                if spC0 = 16#7FFFFFFF then begin
                                    return;
                                end;
                                spC0 := spC0 + 1;
                            end;
                        zbgtu:
                            begin
                                fasm := zbgeu;
                                if spC0 = -1 then begin
                                    return;
                                end;
                                { t9 := spC0; }
                                spC0 := spC0 + 1;
                            end;
                        zbgel:
                            begin
                                if spC0 = 1 then begin
                                    fasm := zbgtl;
                                    spC0 := 0;
                                end;
                            end;
                        zbgeul:
                            begin
                                if spC0 = 1 then begin
                                    fasm := zbgtul;
                                    spC0 := 0;
                                end;
                            end;
                        zbltl:
                            begin
                                if spC0 = 1 then begin
                                    fasm := zblel;
                                    spC0 := 0;
                                end;
                            end;
                        zbltul:
                            begin
                                if spC0 = 1 then begin
                                    fasm := zbleul;
                                    spC0 := 0;
                                end;
                            end;
                        zblel:
                            if spC0 = 16#7FFFFFFF then begin
                                emitbene(op_zbeql, xr0, xr0, sym, spBC);
                                return;
                            end else begin
                                fasm := zbltl;
                                spC0 := spC0 + 1;
                            end;
                        zbleul:
                            if spC0 = -1 then begin
                                emitbene(op_zbeql, xr0, xr0, sym, spBC);
                                return;
                            end else begin
                                fasm := zbltul;
                                spC0 := spC0 + 1;
                            end;
                        zbgtl:
                            begin
                                fasm := zbgel;
                                if spC0 = 16#7FFFFFFF then begin
                                    return;
                                end;
                                spC0 := spC0 + 1;
                            end;
                        zbgtul:
                            begin
                                fasm := zbgeul;
                                if spC0 = -1 then begin
                                    return;
                                end;
                                { t9 := spC0; }
                                spC0 := spC0 + 1;                                
                            end;
                        otherwise:
                    end;
                end;

                if spC5 and (spC0 = 0) then begin
                    case fasm of
                        zbge: spC6 := op_zbgez;
                        zbgt: spC6 := op_zbgtz;
                        zble: spC6 := op_zblez;
                        zblt: spC6 := op_zbltz;
                        zbgeu:
                            begin
                                spC6 := op_zbeq;
                                reg1 := xr0;
                            end;
                        zbgtu: spC6 := op_zbne;
                        zbleu: spC6 := op_zbeq;
                        zbltu: spC6 := op_znop;
                        zbgel: spC6 := op_zbgezl;
                        zbgtl: spC6 := op_zbgtzl;
                        zblel: spC6 := op_zblezl;
                        zbltl: spC6 := op_zbltzl;
                        zbgeul:
                            begin
                                spC6 := op_zbeql;
                                reg1 := xr0;
                            end;
                        zbgtul: spC6 := op_zbnel;
                        zbleul: spC6 := op_zbeql;
                        zbltul: spC6 := op_znop;
                        otherwise:
                    end;

                    if spC6 in [op_zbeq, op_zbne, op_zbeql, op_zbnel] then begin
                        emitbene(spC6, reg1, xr0, sym, spBC);
                    end else if spC6 <> op_znop then begin
                        emitbcond(spC6, reg1, sym, spBC);
                    end;
                    return;
                end;

                if fasm in [zbgeu, zbgtu, zbleu, zbltu, zbgeul, zbgtul, zbleul, zbltul] then begin
                    spC6 := op_zsltu;
                end else begin
                    spC6 := op_zslt;
                end;

                if fasm in [zbgt, zbgtu, zble, zbleu, zbgtl, zbgtul, zblel, zbleul] then begin
                    if spC5 then begin
                        p_assertion_failed("not limmediate\0", "as1parse.p", 569);
                    end;
                    spCC := reg1;
                    spCD := reg2;
                end else begin
                    spCD := reg1;
                    if not spC5 then begin
                        spCC := reg2;
                    end else if (spC0 < -16#8000) or (spC0 > 16#7FFF) then begin
                        spC5 := false;
                        loadimmed(spC0, xr1, nil);
                        spCC := xr1;
                    end;
                end;

                if spC5 then begin
                    if spC6 = op_zslt then begin
                        emitalui(op_zslti, xr1, spCD, spC0);
                    end else begin
                        emitalui(op_zsltiu, xr1, spCD, spC0);
                    end;
                end else begin
                    emitalu3(spC6, xr1, spCD, spCC);
                end;

                if not atflag then begin
                    macro_error();
                end;

                if fasm in [zbge, zbgeu, zble, zbleu] then begin
                    emitbene(op_zbeq, xr1, xr0, sym, spBC);
                end else if fasm in [zbgt, zbgtu, zblt, zbltu] then begin
                    emitbene(op_zbne, xr1, xr0, sym, spBC);
                end else if fasm in [zblel, zbleul, zbgel, zbgeul] then begin
                    emitbene(op_zbeql, xr1, xr0, sym, spBC);
                end else if fasm in [zbgtl, zbgtul, zbltl, zbltul] then begin
                    emitbene(op_zbnel, xr1, xr0, sym, spBC);
                end else begin
                    p_assertion_failed("false\0", "as1parse.p", 603);
                end;
            end;
    end;
end;

procedure parseafrr(fasm: asmcodes);
var
    spCF: registers;
    spCE: registers;
    ba: ^binasm;

    procedure func_004516D4();
    var
        fpreg1: registers;
        fpreg2: registers;
    begin
        if bigendian and not moxieflag then begin
            fpreg1 := succ(spCE);
            fpreg2 := spCE;
        end else begin
            fpreg1 := spCE;
            fpreg2 := succ(spCE);
        end;
        emitmvcoproc(asm2op[fasm], spCF, fpreg1);
        emitmvcoproc(asm2op[fasm], succ(spCF), fpreg2);
    end;

begin
    ba := binasmfyle;

    if (ba^.form <> frr) and (ba^.form <> fr) then begin
        p_assertion_failed("(form = frr) or (form = fr)\0", "as1parse.p", 683);
    end;

    if not(fasm in [zmfc1, zmtc1, zmfc1_d, zmtc1_d])then begin
        if ba^.reg1 in [xfr0..xfr31] then begin
            p_assertion_failed(" not(reg1 in [xfr0.. xfr31])\0", "as1parse.p", 685);
        end;
    end;

    spCF := ba^.reg1;
    if ba^.form = frr then begin
        spCE := ba^.reg2;
    end else begin
        spCE := ba^.reg1;
    end;

    case fasm of
        zabs,
        zdabs:
            begin
                emitbcond(op_zbgez, spCE, nil, 2);
                pinstruction^[bbindex].unk22 := false;

                if spCE <> spCF then begin
                    if fasm = zabs then begin
                        emitalu3(op_zaddu, spCF, spCE, xr0);
                    end else begin
                        emitalu3(op_zdaddu, spCF, spCE, xr0);
                    end;
                end else begin
                    emitnop(1);
                end;
                pinstruction^[bbindex].unk22 := false;

                if fasm = zabs then begin
                    emitalu3(op_zsub, spCF, xr0, spCE);
                end else begin
                    emitalu3(op_zdsub, spCF, xr0, spCE);
                end;
                pinstruction^[bbindex].unk22 := false;
            end;
        zneg: emitalu3(op_zsub, spCF, xr0, spCE);
        znegu: emitalu3(op_zsubu, spCF, xr0, spCE);
        zdneg: emitalu3(op_zdsub, spCF, xr0, spCE);
        zdnegu: emitalu3(op_zdsubu, spCF, xr0, spCE);
        zmult,
        zmultu,
        zdmult,
        zdmultu:
            begin
                if fasm = zmult then begin
                    emitalu3(op_zmult, xr0, spCF, spCE);
                end else if fasm = zmultu then begin
                    emitalu3(op_zmultu, xr0, spCF, spCE);
                end else if fasm = zdmult then begin
                    emitalu3(op_zdmult, xr0, spCF, spCE);
                end else begin
                    emitalu3(op_zdmultu, xr0, spCF, spCE);
                end;
                if reorderflag then begin
                    emitnop(2);
                end;
            end;
        znot: emitalu3(op_znor, spCF, spCE, xr0);
        zmove:
            begin
                emitalu3(op_zor, spCF, spCE, xr0);
                if spCE = frame_ptr then begin
                    frame_ptr := spCF;
                end;
            end;
        zmfc0,
        zmfc1,
        zmfc2,
        zmfc3,
        zmtc0,
        zmtc1,
        zmtc2,
        zmtc3,
        zdmtc0,
        zdmfc0,
        zdmtc1,
        zdmfc1,
        zdmtc2,
        zdmfc2,
        zcfc0,
        zcfc1,
        zcfc2,
        zcfc3,
        zctc0,        
        zctc1,        
        zctc2,
        zctc3,
        zmfpc,
        zmtpc,
        zmfps,
        zmtps:
            emitmvcoproc(asm2op[fasm], spCF, spCE);
        zmtc1_d,
        zmfc1_d:
            func_004516D4();
    end;
end;

procedure parseafa(fasm: asmcodes);
var
    spCF: registers;
    spC8: integer;
    spC4: PUnkAlpha;
    spC3: boolean;
    ba: ^binasm;
begin
    spC3 := false;
    ba := binasmfyle;
    branchpending := true;

    if picflag = 1 then begin
        spC4 := stp(ba^.symno);
        if (spC4 <> nil) and (is_dso_static(spC4^.unk18) = true) then begin
            spC3 := true;
        end;
    end;

    if ba^.form = fa then begin
        if (fasm = zjal) and ((picflag = 2) or ((picflag = 1) and not spC3)) then begin
            restore_gp();
            spC4 := stp(ba^.symno);

            if islocalsym(spC4) then begin
                emitloadstore(asm2op[zlw], xr25, disp(true, ba^.immediate), gpreg);
                _setrld(spC4, 15, bbindex + proc_instr_base);
                if not reorderflag then begin
                    emitnop(1);
                    pinstruction^[bbindex].unk22 := false;
                end;
                emitalui(op_zaddiu, xr25, xr25, disp(false, ba^.immediate));
                _setrld(spC4, 3, bbindex + proc_instr_base);
            end else begin
                if big_got then begin
                    emitalui(op_zlui, xr25, xr0, 0);
                    _setrld(spC4, 24, bbindex + proc_instr_base);
                    emitalu3(op_zaddu, xr25, xr25, gpreg);
                    emitloadstore(op_zlw, xr25, 0, xr25);
                    _setrld(spC4, 25, bbindex + proc_instr_base);
                end else begin
                    emitloadstore(op_zlw, xr25, 0, gpreg);
                    _setrld(spC4, 16, bbindex + proc_instr_base);
                end;
                if not reorderflag then begin
                    emitnop(1);
                    pinstruction^[bbindex].unk22 := false;
                end;
            end;

            ba^.form := fr;
            spCF := xr25;
            spC8 := 0;

            if cpalias_set then begin
                if cpalias_pending then begin
                    init_cpalias();
                end;
                emitalu3(op_zor, xr28, xr0, gpreg);
            end;
        end else begin
            spC8 := ba^.immediate;
            if (picflag = 1) and spC3 then begin
                spC8 := spC8 + 12;
            end;
            spCF := xnoreg;
            if ba^.symno <> 0 then begin
                spC4 := stp(ba^.symno);
            end else begin
                spC4 := nil;
            end;
        end;
    end else if ba^.form = fr then begin
        if (ba^.reg1 <> xr31) or (fasm = zjal) then begin
            if cpalias_set then begin
                if cpalias_pending then begin
                    init_cpalias();
                end;
                emitalu3(op_zor, xr28, xr0, gpreg);
            end else begin
                restore_gp();
            end;
        end;

        spC8 := 0;
        spC4 := nil;
        spCF := ba^.reg1;
    end else begin
        p_assertion_failed("false\0", "as1parse.p", 834);
    end;

    if spCF <> xnoreg then begin
        if fasm = zj then begin
            emitreg2(op_zjr, spCF, xnoreg);
        end else begin
            if binasmfyle^.reg2 = xnoreg then begin
                binasmfyle^.reg2 := xr31;
            end;
            if binasmfyle^.reg2 = spCF then begin
                PostError("JAL should not use $31 alone or any register twice", emptystring, ErrorLevel_2);
            end;
            emitreg2(op_zjalr, spCF, binasmfyle^.reg2);
        end;
    end else if (picflag = 2) or ((picflag = 1) and not spC3) then begin
        if spC8 <> 0 then begin
            PostError("j instructions cannot have offsets in PIC mode", emptystring, ErrorLevel_1);
        end;
        if not islocalsym(spC4) then begin
            PostError("j instruction to external symbol not allowed in PIC mode", spC4^.unk0C, ErrorLevel_1);
        end;
        emitbene(asm2op[zbeqz], xr0, xr0, spC4, 0);
    end else begin
        if fasm = zj then begin
            emitjump(op_zj, 0, spC8);
        end else begin
            emitjump(op_zjal, 0, spC8);
        end;
        if spC4 <> nil then begin
            _setrld(spC4, 6, bbindex + proc_instr_base);
        end;
    end;

    if ((picflag = 2) or ((picflag = 1) and not spC3)) and (fasm <> zj) and (cprestore_offset <> -1) then begin
        need_cprestore := true;
    end;
end;

procedure parseafrl(fasm: asmcodes);
var
    spCF: registers;
    spC8: PUnkAlpha;
    spC4: integer;
    spC0: ^binasm;
begin
    if cpalias_set then begin
        init_cpalias();
    end else begin
        restore_gp();
    end;
    branchpending := true;
    spC0 := binasmfyle;

    if not(asm2op[fasm] in branchops) then begin
        p_assertion_failed("asm2op[fasm] in branchops\0", "as1parse.p", 922);
    end;
    if spC0^.form <> frl then begin
        p_assertion_failed("form = frl\0", "as1parse.p", 923);
    end;

    spCF := spC0^.reg1;
    if spC0^.reg1 in [xfr0..xfr31] then begin
        p_assertion_failed("not (reg1 in [xfr0..xfr31])\0", "as1parse.p", 925);
    end;
    spC8 := nil;
    spC4 := 0;

    if (spC0^.formextn = frrel1) then begin
        spC4 := spC0^.mem_tag;
    end else if (spC0^.formextn = frrel2) then begin
        spC4 := -spC0^.mem_tag - 1;
    end else begin
        spC8 := stp(spC0^.symno);
    end;

    if fasm in [zbeqz, zbnez, zbeqzl, zbnezl] then begin
        emitbene(asm2op[fasm], spCF, xr0, spC8, spC4);
    end else begin
        if fasm = zbal then begin
            spCF := xr0;
        end;
        emitbcond(asm2op[fasm], spCF, spC8, spC4);
    end;
end;

procedure parseafl(fasm: asmcodes);
var
    spC8: PUnkAlpha;
    spC4: integer;
    spC0: ^binasm;
begin
    if cpalias_set then begin
        init_cpalias();
    end else begin
        restore_gp();
    end;
    branchpending := true;
    spC0 := binasmfyle;

    spC8 := nil;
    if (spC0^.formextn = frrel1) then begin
        spC4 := spC0^.mem_tag;
    end else if (spC0^.formextn = frrel2) then begin
        spC4 := -spC0^.mem_tag - 1;
    end else begin
        spC8 := stp(spC0^.symno);
        spC4 := 0;
    end;

    if fasm = zb then begin
        emitbene(op_zbeq, xr0, xr0, spC8, spC4);
    end else begin
        if spC0^.form = frl then begin
            emitbcond(asm2op[fasm], spC0^.reg1, spC8, spC4);
        end else begin
            emitbcond(asm2op[fasm], xfcc0, spC8, spC4);
        end;        
    end;
end;

procedure parseaforrr(fasm: asmcodes);
var
    ba: ^binasm;
begin
    ba := binasmfyle;
    emitcoproc(asm2op[fasm], ba^.immediate);
end;

procedure parseafr(fasm: asmcodes);
var
    reg1: registers;
    ba: ^binasm;
begin
    ba := binasmfyle;
    
    if ba^.form <> fr then begin
        p_assertion_failed("form = fr\0", "as1parse.p", 1031);
    end;

    reg1 := ba^.reg1;
    emitreg2(asm2op[fasm], reg1, xnoreg);
    pre_reorder_peepholes.unk_10 := bbindex;
end;

procedure parseafrrrr(fasm: asmcodes);
var
    ba: ^binasm;
begin
    ba := binasmfyle;
    fpop_src3 := ba^.reg4;
    emitfpop(asm2op[fasm], ba^.reg1, ba^.reg2, ba^.reg3);
end;

procedure parsealign;
var
    n: integer;
    v: integer;
begin
    n := binasmfyle^.length;
    v := power2(n);

    if (currsegment = seg_sdata) or (currsegment = seg_data) then begin
        if prev_sdata[currsegment].unk04 then begin
            prev_sdata[currsegment].unk08 := Max(prev_sdata[currsegment].unk08, binasmfyle^.length); { maybe bug? }
        end else begin
            prev_sdata[currsegment].unk0C := ARRAY_AT(seg_ic, currsegmentindex);
            prev_sdata[currsegment].unk04 := true;
            prev_sdata[currsegment].unk08 := v;
        end;
    end;

    if (currsegment = seg_text) or (currsegment = seg_data) or (currsegment = seg_rdata) or (currsegment = seg_sdata) then begin
        prev_align[currsegment].unk08 := Max(prev_align[currsegment].unk08, v);
    end;

    if (currsegment <> seg_text) and (currsegment <> seg_15) then begin
        aligning := n > 0;
        definealabel(currsegmentindex, v, 0);
    end else begin
        fill_pseudo(11, v, 0, 0, nil, 0);
    end;
end;

procedure parseascii(arg0: boolean);
var
    i, j, k: integer;
    buffer: st_string;
begin
    if not(currsegment in realsegments) then begin
        p_assertion_failed("currsegment in realsegments\0", "as1parse.p", 1091);
    end;

    if (currsegment <> seg_text) and (currsegment <> seg_15) then begin
        definealabel(currsegmentindex, 1, 0);
    end;

    k := 0;
    j := 17;

    for i := 1 to binasmfyle^.length do begin
        if j = 17 then begin
            get_binasm(binasmfyle);
            j := 1;
        end;

        if (currsegment <> seg_text) and (currsegment <> seg_15) then begin
            ARRAY_GROW(ARRAY_AT(memory, currsegmentindex).unk_00.b, ARRAY_AT(seg_ic, currsegmentindex));
            ARRAY_AT(ARRAY_AT(memory, currsegmentindex).unk_00.b, ARRAY_AT(seg_ic, currsegmentindex)) := binasmfyle^.data[j];
            ARRAY_AT(seg_ic, currsegmentindex) := ARRAY_AT(seg_ic, currsegmentindex) + 1;
        end else begin
            if k >= 128 then begin
                fill_ascii_pseudo(buffer, 128, false);
                k := 0;
            end;
            k := k + 1;
            buffer[k] := binasmfyle^.data[j];
        end;
        j := j + 1;
    end;

    if (currsegment = seg_text) or (currsegment = seg_15) then begin
        if (k > 0) or arg0 then begin
            fill_ascii_pseudo(buffer, k, arg0);
        end;
    end;

    if arg0 then begin
        if (currsegment <> seg_text) and (currsegment <> seg_15) then begin
            ARRAY_GROW(ARRAY_AT(memory, currsegmentindex).unk_00.b, ARRAY_AT(seg_ic, currsegmentindex));
            ARRAY_AT(ARRAY_AT(memory, currsegmentindex).unk_00.b, ARRAY_AT(seg_ic, currsegmentindex)) := chr(0);
            ARRAY_AT(seg_ic, currsegmentindex) := ARRAY_AT(seg_ic, currsegmentindex) + 1;
        end;
    end;
end;

procedure remember_symbol_size(symno: integer; size: integer);
var
    sym: PUnkAlpha;
begin
    if symno <> 0 then begin
        sym := stp(symno);
        label_size := label_size + size;
        reenter_symbol(sym^.unk0C.f, label_size);
    end;
end;

procedure parsebyte;
var
    count: integer;
    c: integer;
    ba: ^binasm;
begin
    remember_symbol_size(last_globl_symno, 1);
    ba := binasmfyle;

    if (currsegment = seg_text) or (currsegment = seg_15) then begin
        fill_pseudo(16, ba^.replicate, ba^.expression, 0, nil, 0);
        return;
    end;

    definealabel(currsegmentindex, 1, 0);

    if not(currsegment in realsegments) then begin
        p_assertion_failed("currsegment in realsegments\0", "as1parse.p", 1156);
    end;

    c := ba^.expression;
    c := bitand(c, 16#FF);
    
    count := ba^.replicate;
    if count > 0 then begin
        repeat
            ARRAY_GROW(ARRAY_AT(memory, currsegmentindex).unk_00.b, ARRAY_AT(seg_ic, currsegmentindex));
            ARRAY_AT(ARRAY_AT(memory, currsegmentindex).unk_00.b, ARRAY_AT(seg_ic, currsegmentindex)) := chr(c);
            ARRAY_AT(seg_ic, currsegmentindex) := ARRAY_AT(seg_ic, currsegmentindex) + 1;
            count := count - 1;
        until count = 0;
    end;
end;

procedure parsecomm(which: itype);
var
    spC4: PUnkAlpha;
    spC0: integer;
    spBC: integer;
    ba: ^binasm;
begin
    ba := binasmfyle;
    spC0 := ba^.length;
    spC4 := stp(ba^.symno);
    spBC := ba^.rep; { ?? }

    enter_symbol(spC4^.unk0C.f, ba^.length, spBC);

    if (picflag <> 1) or not spC4^.unk3C then begin
        if not(spC4^.unk34 in ['D', 'U', 'u']) then begin
            PostError("redefinition of symbol", spC4^.unk0C, ErrorLevel_1);
            return;
        end;

        case which of
            icomm:
                begin
                    spC4^.unk34 := 'C';
                    spC4^.unk30 := 12;
                    if spBC = 1 then begin
                        spC4^.unk34 := 'E';
                    end;
                end;
            ilcomm:
                begin
                    if spC4^.unk34 = 'u' then begin
                        spC4^.unk34 := 'b';
                    end else begin
                        spC4^.unk34 := 'B';
                    end;

                    if (picflag > 0) and (spC4^.unk35 <> 0) then begin
                        spC4^.unk30 := 4;
                    end else if (spC0 <= gprelsize) and (spC0 > 0) then begin
                        spC4^.unk30 := 3;
                    end else if spBC = 1 then begin
                        spC4^.unk30 := 3;
                    end else begin
                        spC4^.unk30 := 4;
                    end;
                end;
            iextern:
                begin
                    if (spC0 <= gprelsize) and (spC0 > 0) then begin
                        spC4^.unk30 := 13;
                        spC4^.unk34 := 'V';
                    end else if spBC = 1 then begin
                        spC4^.unk30 := 13;
                        spC4^.unk34 := 'V';
                    end else begin
                        spC4^.unk30 := 12;
                        spC4^.unk34 := 'U';
                    end;
                end;
            otherwise:
                if which <> iextern then begin
                    p_assertion_failed("which = iextern\0", "as1parse.p", 1242);
                end;
        end;
    end;

    if (which = icomm) or (which = iextern) then begin
        spC4^.unk35 := 1;
    end;

    if which = ilcomm then begin
        spC4^.unk37 := true;
    end;

    spC4^.unk28 := spC0;
    last_globl_symno := 0;
    label_size := 0;
end;

{ TODO match this }
procedure parseseg(seg: segments);
var
    length: integer;
    i: integer;
    j: integer;
begin
    if (currsegment = seg_sdata) or (currsegment = seg_data) then begin
        add_data_to_gp_table(currsegment, 1);
    end;

    currsegment := seg;
    currsegmentindex := ord(seg);

    length := binasmfyle^.length;
    if (seg = seg_text) and (length <> 0) then begin
        currsegment := seg_15;
        
        get_binasm(binasmfyle);

        if lastusertextseg = -1 then begin
            lastusertextseg := firstusertextseg;
            currsegmentindex := firstusertextseg;

            for i := 1 to length do begin
                ARRAY_AT(memory, currsegmentindex).unk_09[i] := binasmfyle^.data[i];
            end;
            ARRAY_AT(memory, currsegmentindex).unk_09[i] := chr(0);
        end else begin
            currsegmentindex := -1;
            for j := firstusertextseg to lastusertextseg do begin
                for i := 1 to length do begin
                    if ARRAY_AT(memory, j).unk_09[i] <> binasmfyle^.data[i] then begin
                        break;
                    end;
                end;

                if i > length then begin
                    currsegmentindex := j;
                    break; { j := lastusertextseg + 1; }
                end;
            end;

            if currsegmentindex = -1 then begin
                { create new segment }
                lastusertextseg := lastusertextseg + 1;
                currsegmentindex := lastusertextseg;
                ARRAY_GROW(memory, currsegmentindex);
                ARRAY_GROW(seg_ic, currsegmentindex);
                ARRAY_GROW(nextlabelchain, currsegmentindex);

                for i := 1 to length do begin
                    ARRAY_AT(memory, currsegmentindex).unk_09[i] := binasmfyle^.data[i];
                end;
                ARRAY_AT(memory, currsegmentindex).unk_09[i] := chr(0);
                ARRAY_AT(memory, currsegmentindex).unk_08 := seg_15;
                ARRAY_AT(memory, currsegmentindex).unk_00.b.size := 0;

                ARRAY_AT(seg_ic, currsegmentindex) := 0;
                ARRAY_AT(nextlabelchain, currsegmentindex) := 0;
            end;
        end;
    end;

    if (currsegment = seg_text) or (currsegment = seg_15) then begin
        currtextindex := currsegmentindex;
    end;

    endofbasicb := true;
    aligning := true;
    label_size := 0;
end;

procedure create_function_table;
    procedure func_00454458(arg0: integer; arg1: cardinal; arg2: boolean);
    var
        s0: cardinal;
        rld: ^RldRec;
    begin
        if sexchange then begin
            arg1 := bitand(lshift(arg1, 24), 16#FF000000) + 
                    bitand(rshift(arg1, 24), 16#000000FF) +
                    bitand(lshift(arg1,  8), 16#00FF0000) + 
                    bitand(rshift(arg1,  8), 16#0000FF00);
        end;

        s0 := ARRAY_AT(seg_ic, ord(seg_8));
        if bitand(s0, 3) <> 0 then begin
            s0 := bitand(s0 + 3, 16#FFFFFFFC);
        end;

        ARRAY_GROW(ARRAY_AT(memory, ord(seg_8)).unk_00.b, s0);
        ARRAY_AT(ARRAY_AT(memory, ord(seg_8)).unk_00.w, s0) := arg1; { TODO }
        ARRAY_AT(seg_ic, ord(seg_8)) := s0 + 4;

        if arg2 then begin
            rld := addr(ARRAY_AT(rld_list, nextrld));
            ARRAY_GROW(rld_list, nextrld);
            rld^.unk00 := 0;
            rld^.unk04 := s0;
            currfunc_sym^.unk30 := currtextindex;

            if arg0 <> 0 then begin
                rld^.unk08 := stp(arg0);
            end else begin
                rld^.unk08 := currfunc_sym;
            end;

            rld^.unk08^.unk20 := rld^.unk08^.unk20 + 1;
            rld^.unk0C := 8;
            rld^.unk10 := 8;
            nextrld := nextrld + 1;
        end;
    end;
begin
    if excpt_opt then begin
        currfunc_end := ARRAY_AT(seg_ic, currtextindex);
        func_00454458(0, currfunc_start, true);
        func_00454458(0, currfunc_end, true);
        func_00454458(currfunc_handle, 0, currfunc_hasedata);
        func_00454458(currfunc_data, 0, currfunc_hasedata);
        func_00454458(0, currfunc_prolog, true);

        is_nonleaf := false;
        currfunc_hasedata := false;
        currfunc_start := 0;
        currfunc_end := 0;
        currfunc_prolog := 0;
        currfunc_handle := 0;
        currfunc_data := 0;
    end;
end;

procedure parseedata;
var
    ba: ^binasm;
begin
    if excpt_opt then begin
        ba := binasmfyle;
        if ba^.flag = 0 then begin
            parseseg(seg_7);
        end else begin
            enterstp(ba^.edata);
            lastsymno := ba^.symno;
            lastdata := ba^.edata;
            lastinstr := iedata;
            pendinginstr := true;
            endofbasicb := true;
        end;
    end;
end;

procedure parsealloc;
var
    temp: integer;
    ba: ^binasm;
begin
    ba := binasmfyle;
    if not adjust_frame_by_ld then begin
        p_assertion_failed("adjust_frame_by_ld\0", "as1parse.p", 1386);
    end;
    temp := st_add_deltasym(27, 0, ba^.symno); { lclinst ? }
    enterstp(temp);
end;

procedure parseprologue;
begin
    if excpt_opt then begin
        endofbasicb := true;
        fill_pseudo(20, binasmfyle^.lexlevel, 0, 0, nil, 0);
    end;
end;

{ NON_MATCHING, regalloc }
procedure parseend(which: itype);
var
    sp84: PUnkAlpha;
    sp80: integer;
    ba: ^binasm;
    ptr: pointer; 
    
begin
    ba := binasmfyle;

    if (bbindex = 0) or
       (which in [iend, ient, iaent]) or
       not((pinstruction^[bbindex].rfd = 16#7FFFFFFF) and (pseudo_type(bbindex) in [23, 24, 25, 26])) or
       not((currsegment = seg_text) or (currsegment = seg_15)) then
    begin
        if not((currsegment = seg_text) or (currsegment = seg_15)) then begin
            definealabel(currsegmentindex, 1, 0);
        end;

        endofbasicb := true;
        lastinstr := which;
        lastsymno := ba^.symno;
        pendinginstr := true;

        if (which = ient) or (which = iaent) then begin
            sp84 := stp(ba^.symno);
            save_cur_proc_id(sp84^.unk0C.f^);

            if verbose and (sp84^.unk0C.f^[1] <> chr(0)) then begin
                call_name_and_line(3);
                if sp84^.unk0C.f^[1] <> chr(0) then begin
                    Write(err, sp84^.unk0C.f^:strlen(sp84^.unk0C.f), ' ');
                end;
                Flush(err);
            end;
        end;

        if which = ient then begin
            if (debugflag > 0) and (currentfile = -1) then begin
                PostError(".loc should precede .ent when using -g", emptystring, ErrorLevel_2);
            end;
            ignore_frames := false;
            currentent := ba^.symno;
            currentent_name.f := xmalloc(strlen(sp84^.unk0C.f));
            ptr := strcpy(currentent_name.f, sp84^.unk0C.f);
            sp84^.unk0C := currentent_name;                    
            lexicallevel := 0;
            cprestore_offset := -1;
            cpalias_pending := false;
        end else if which = iend then begin
            ignore_frames := false;
            cprestore_offset := -1;
            cpalias_pending := false;
            need_cprestore := false;
        end;
    end else begin
        case which of
            ibgnb: sp80 := 23;
            iendb: sp80 := 24;
            ilab:
                begin
                    if cpalias_set then begin
                        init_cpalias();
                    end;
                    sp84 := stp(ba^.symno);
                    enterlabel(ba^.symno, sp84);
                    sp80 := 25;
                end;
        end;
        fill_pseudo(sp80, ba^.symno, currentline, debugflag, sp84, 0);
    end;
end;

procedure parserepeat;
begin
    PostError(".repeat allowed only in as0", emptystring, ErrorLevel_1);
end;

procedure parseendrep;
begin
    PostError(".endr allowed only in as0", emptystring, ErrorLevel_1);
end;

{ NON_MATCHING }
procedure parsefile;
var
    i, count: integer;
begin
    count := (binasmfyle^.length + 15) div 16;
    for i := 1 to count do begin
        get_binasm(binasmfyle);
    end;
end;

procedure parseloc(var arg0: boolean);
var
    tmp: boolean;
    sym: PUnkALpha;
begin
    if (currsegment = seg_text) or (currsegment = seg_15) then begin
        if (bbindex <> 0) and
            (((binasmfyle^.filenumber <> currentfile) and not initial_loc) or
            ((optflag > 0) and reorderflag and not(debugflag in [0,3]))) then
        begin
            endofbasicb := true;
            arg0 := true;
            tmp := initial_loc;
        end else begin
            currentline := binasmfyle^.linenumber;
            currentfile := binasmfyle^.filenumber;
            if fromas0 then begin
                sym := stp(currentfile);
                if sym <> nil then begin
                    sym^.unk34 := 'F';
                end;
            end;
            tmp := initial_loc;
        end;
        
        if tmp then begin
            initial_loc := false;
        end;
    end;
end;

procedure parseglobl;
var
    sym: PUnkALpha;
    ba: ^binasm;
begin
    ba := binasmfyle;
    sym := stp(ba^.symno);
    last_globl_symno := ba^.symno;
    label_size := 0;
    if sym^.unk34 = ' ' then begin
        sym^.unk34 := 'U';
    end else if sym^.unk34 = 'u' then begin
        sym^.unk34 := 'U';
    end else if sym^.unk34 = 'b' then begin
        sym^.unk34 := 'B';
    end else if sym^.unk34 = 'd' then begin
        sym^.unk34 := 'D';
    end else if sym^.unk34 = 't' then begin
        sym^.unk34 := 'T';
    end;
    sym^.unk35 := 1;
end;

procedure parseweakext;
var
    sym: PUnkALpha;
    ba: ^binasm;
begin
    ba := binasmfyle;
    sym := stp(ba^.symno);
    sym^.unk3C := true;
    sym^.unk44 := ba^.lexlevel;
end;

procedure parseglobabs;
var
    sym: PUnkALpha;
    ba: ^binasm;
begin
    ba := binasmfyle;
    sym := stp(ba^.symno);
    sym^.unk34 := 'A';
    sym^.unk10 := binasmfyle^.length;
    sym^.unk35 := 1;
end;

procedure parse_option;
var
    str: GString;
    pdr: ^PdrRec;
begin
    if (binasmfyle^.option = o_optimize) and (binasmfyle^.opt_int_value >= 0) and (binasmfyle^.opt_int_value <= 4) then begin
        if optflag <> binasmfyle^.opt_int_value then begin
            new(str.o);
            ltoa(binasmfyle^.opt_int_value, str.c);
            PostError("Binasm file dictates -O", str, ErrorLevel_2);
            dispose(str.o);
        end;
        optflag := binasmfyle^.opt_int_value;
    end else if (binasmfyle^.option = o_pic) and (binasmfyle^.opt_int_value >= 0) and (binasmfyle^.opt_int_value <= 3) then begin
        if saw_pic_flag and (picflag <> binasmfyle^.opt_int_value) then begin
            new(str.o);
            ltoa(binasmfyle^.opt_int_value, str.c);
            PostError("Binasm file dictates -pic", str, ErrorLevel_2);
            dispose(str.o);
        end;

        if saw_option_pic then begin
            PostError("Multiple .option pic specified, ignored.", emptystring, ErrorLevel_2);
        end else begin
            saw_option_pic := true;
            picflag := binasmfyle^.opt_int_value;
            if (picflag = 2) and saw_cap_g and (gprelsize <> 0) then begin
                PostError(".option pic2 implies -G 0.  -G flag ignored", emptystring, ErrorLevel_2);
                gprelsize := 0;
            end;
        end;
    end else if (binasmfyle^.option = o_exception_info) then begin
        new(pdr);
        if (last_pdr = nil) and (first_pdr = nil) then begin
            first_pdr := pdr;
            last_pdr := pdr;
        end else begin
            last_pdr^.next := pdr;
        end;
        pdr^.next := nil;
        pdr^.unk0C := binasmfyle^.opt_int_value;
        pdr^.unk10 := stp(currentent);
        pdr^.unk14 := stp(binasmfyle^.opt_int_value);
        last_pdr := pdr;
    end else begin
        PostError("Unsupported option in binasm file", emptystring, ErrorLevel_0);
    end;
end;

procedure parse_alias(which: itype);
    function func_00455984(reg: registers): boolean;
    var
        ret: boolean;
    begin
        if reg <= xr31 then begin
            ret := true;
        end else begin
            PostError(".noalias and .alias require gp registers", emptystring, ErrorLevel_1);
            ret := false;
        end;
        return ret;
    end;
begin
    if func_00455984(binasmfyle^.basereg1) and func_00455984(binasmfyle^.basereg2) then begin
        fill_pseudo(integer(which = inoalias) + 27, ord(binasmfyle^.basereg1), ord(binasmfyle^.basereg2), 0, nil, 0);
    end;
end;

procedure parseset(var arg0: boolean);
var
    ba: ^binasm;
begin
    ba := binasmfyle;
    case set_value(ba^.length) of
        set_reorder:
            begin
                if not(reorderflag) and (bbindex <> 0) then begin
                    endofbasicb := true;
                    arg0 := true;
                end else begin
                    reorderflag := true;
                    if not macroflag then begin
                        PostError("reorder requires macro", emptystring, ErrorLevel_2);
                    end;
                end;
            end;
        set_noreorder:
            begin
                has_noreorder := true;
                if non_reorg_flag = 0 then begin
                    non_reorg_flag := 16#4000;
                end;
                if reorderflag and (bbindex <> 0) then begin
                    endofbasicb := true;
                    arg0 := true;
                end else begin
                    reorderflag := false;
                end;
            end;
        set_transform:
            if not(transform_flag) and (bbindex <> 0) then begin
                endofbasicb := true;
                arg0 := true;
            end else begin
                transform_flag := true;
            end;
        set_notransform:
            if transform_flag and (bbindex <> 0) then begin
                endofbasicb := true;
                arg0 := true;
            end else begin
                transform_flag := false;
            end;
        set_macro:
            begin
                macroflag := true;
            end;
        set_nomacro:
            begin
                macroflag := false;
                if reorderflag then begin
                    PostError("nomacro requires noreorder", emptystring, ErrorLevel_2);
                end;
            end;
        set_at:
            begin
                atflag := true;
            end;
        set_noat:
            begin
                atflag := false;
            end;
        set_volatile:
            begin
                if non_reorg_flag = 0 then begin
                    non_reorg_flag := 16#4000;
                end;
                volatileflag := true;
            end;
        set_novolatile:
            begin
                volatileflag := false;
            end;
        set_move:
            begin
                movableflag := true;
            end;
        set_nomove:
            begin
                if non_reorg_flag = 0 then begin
                    non_reorg_flag := 16#4000;
                end;
                movableflag := false;
                PostError(".set nomove is obsolete", emptystring, ErrorLevel_2);
            end;
        set_bopt:
            begin
                opts.unk_00[5] := true;
            end;
        set_nobopt:
            begin
                opts.unk_00[5] := false;
            end;
        set_reposition,
        set_noreposition:
    end;
end;

{ NON_MATCHING }
procedure parsespace;
var
    counter: integer;
    ba: ^binasm;
begin
    ba := binasmfyle;

    if (currsegment = seg_text) or (currsegment = seg_15) then begin
        fill_pseudo(13, ba^.length, 0, 0, nil, 0);
        return;
    end;

    definealabel(currsegmentindex, 1, 0);
    if not(currsegment in realsegments) then begin
        p_assertion_failed("currsegment in realsegments\0", "as1parse.p", 1813);
    end;

    if ba^.length > 0 then begin

        counter := ba^.length;
        repeat
            ARRAY_GROW(ARRAY_AT(memory, currsegmentindex).unk_00.b, ARRAY_AT(seg_ic, currsegmentindex));
            if ARRAY_AT(memory, currsegmentindex).unk_00.b.data = nil then begin
                PostError("could not allocate enough memory for .space", emptystring, ErrorLevel_1);
                halt(1);
            end;
            ARRAY_AT(ARRAY_AT(memory, currsegmentindex).unk_00.b, ARRAY_AT(seg_ic, currsegmentindex)) := chr(0);
            ARRAY_AT(seg_ic, currsegmentindex) := ARRAY_AT(seg_ic, currsegmentindex) + 1;
            counter := counter - 1;
        until counter = 0;
    end;
end;

{ not matching }
procedure doword(arg0: integer; arg1: integer; arg2: cardinal; arg3: PUnkALpha; arg4: integer; arg5: boolean);
var
    s0: Byte;
    spF3: boolean;
    s2: cardinal;
    rld: ^RldRec;
begin
    definealabel(arg4, arg0, 0);

    if arg0 = 2 then begin
        s0 := 1;
        if shftaddr = 1 then begin
            arg2 := rshift(integer(arg2), 1);
        end;
        arg2 := bitand(arg2, 16#FFFF);
        if sexchange then begin
            arg2 := bitand(lshift(arg2,  8), 16#FF00) + 
                    bitand(rshift(arg2,  8), 16#00FF);
        end;
    end else begin
        s0 := 2;
        if sexchange then begin
            arg2 := bitand(lshift(arg2, 24), 16#FF000000) + 
                    bitand(rshift(arg2, 24), 16#000000FF) +
                    bitand(lshift(arg2,  8), 16#00FF0000) + 
                    bitand(rshift(arg2,  8), 16#0000FF00);
        end;
    end;

    if not(ARRAY_AT(memory, arg4).unk_08 in realsegments) then begin
        p_assertion_failed("MEM_ACCESS(segm, seg) in realsegments\0", "as1parse.p", 1858);
    end;

    if bitand(ARRAY_AT(seg_ic, arg4), arg0 - 1) <> 0 then begin
        spF3 := true;
        if aligning and (s0 <= opts.unk_1C) then begin
            if arg0 = 2 then begin
                PostError(".half not on halfword boundary", emptystring, ErrorLevel_1);
            end else begin
                PostError(".word not on word boundary", emptystring, ErrorLevel_1);
            end;
        end;
    end else begin
        spF3 := false;
    end;

    if arg1 > 0 then begin
        repeat
            s2 := ARRAY_AT(seg_ic, arg4);
            if arg3 <> nil then begin
                ARRAY_GROW(rld_list, nextrld);
                { if nextrld >= rld_list.size then
                    rld_list.data := grow_array(rld_list.size, nextrld, sizeof(ARRAY_AT(rld_list, 0)), rld_list.data, false); }
                rld := addr(ARRAY_AT(rld_list, nextrld));

                rld^.unk00 := 0;
                rld^.unk04 := s2;
                rld^.unk08 := arg3;
                
                arg3^.unk20 := arg3^.unk20 + 1;
                arg3^.unk3D := true;

                rld^.unk0C := arg4;

                if arg0 = 2 then begin
                    if shftaddr = 1 then begin
                        rld^.unk10 := 12;
                    end else begin
                        rld^.unk10 := 10;
                    end;
                end else begin
                    if arg5 then begin
                        rld^.unk10 := 18;
                        if not islocalsym(arg3) then begin
                            PostError(".gpword expression references global symbol", emptystring, ErrorLevel_1);
                        end;
                    end else begin
                        rld^.unk10 := 8;
                    end;
                end;

                nextrld := nextrld + 1;
            end;

            if spF3 then begin
                byte_at_a_time(arg4, arg2, s2, arg0);
                shftaddr := 0;
            end else begin
                ARRAY_GROW(ARRAY_AT(memory, arg4).unk_00.b, s2);
                shftaddr := 0;
                if arg0 = 2 then begin
                    ARRAY_AT(ARRAY_AT(memory, arg4).unk_00.h, s2 div 2) := arg2;
                end else begin
                    ARRAY_AT(ARRAY_AT(memory, arg4).unk_00.w, s2 div 4) := arg2;
                end;
            end;

            ARRAY_AT(seg_ic, arg4) := s2 + arg0;
            arg1 := arg1 - 1;
        until arg1 = 0;
    end;
end;

{ not matching }
procedure dodword(arg0: integer; arg1: integer; arg2: cardinal; arg22: cardinal; arg3: PUnkALpha; arg5: integer);
var
    
    spF3: boolean;
    tempval: cardinal;
    unused: integer;
    s2: cardinal;
    rld: ^RldRec;
begin
    definealabel(arg5, arg0, 0);
    if sexchange then begin
        tempval := bitand(lshift(arg2, 24), 16#FF000000) + 
                   bitand(rshift(arg2, 24), 16#000000FF) +
                   bitand(lshift(arg2,  8), 16#00FF0000) + 
                   bitand(rshift(arg2,  8), 16#0000FF00);
        arg2 := bitand(lshift(arg22, 24), 16#FF000000) + 
                bitand(rshift(arg22, 24), 16#000000FF) +
                bitand(lshift(arg22,  8), 16#00FF0000) + 
                bitand(rshift(arg22,  8), 16#0000FF00);
        arg22 := tempval;
    end;

    if not(ARRAY_AT(memory, arg5).unk_08 in realsegments) then begin
        p_assertion_failed("MEM_ACCESS(segm, seg) in realsegments\0", "as1parse.p", 1858);
    end;

    if bitand(ARRAY_AT(seg_ic, arg5), arg0 - 1) <> 0 then begin
        spF3 := true;
        PostError(".dword not on double-word boundary", emptystring, ErrorLevel_1);
    end else begin
        spF3 := false;
    end;

    if not(spF3) and (arg1 > 0) then begin
        repeat
            s2 := ARRAY_AT(seg_ic, arg5);
            if arg3 <> nil then begin
                ARRAY_GROW(rld_list, nextrld);
                { if nextrld >= rld_list.size then
                    rld_list.data := grow_array(rld_list.size, nextrld, sizeof(ARRAY_AT(rld_list, 0)), rld_list.data, false); }
                rld := addr(ARRAY_AT(rld_list, nextrld));

                rld^.unk00 := 0;
                rld^.unk04 := s2;
                rld^.unk08 := arg3;
                arg3^.unk20 := arg3^.unk20 + 1;
                rld^.unk0C := arg5;

                if sixtyfour_bit and elf_flag then begin
                    rld^.unk10 := 7;
                end else if sexchange then begin
                    rld^.unk10 := 8;
                end else begin
                    rld^.unk10 := 7;
                end;
                nextrld := nextrld + 1;
            end;

            ARRAY_GROW(ARRAY_AT(memory, arg5).unk_00.b, s2);
            ARRAY_AT(ARRAY_AT(memory, arg5).unk_00.w, s2 div 4) := arg2;
            
            if not (sixtyfour_bit and elf_flag) and (arg3 <> nil) then begin
                ARRAY_GROW(rld_list, nextrld);
                { if nextrld >= rld_list.size then
                    rld_list.data := grow_array(rld_list.size, nextrld, sizeof(ARRAY_AT(rld_list, 0)), rld_list.data, false); }
                rld := addr(ARRAY_AT(rld_list, nextrld));

                rld^.unk00 := 0;
                rld^.unk04 := s2;
                rld^.unk08 := arg3;
                arg3^.unk20 := arg3^.unk20 + 1;
                rld^.unk0C := arg5;

                if sexchange then begin
                    rld^.unk10 := 8;
                end else begin
                    rld^.unk10 := 7;
                end;
                nextrld := nextrld + 1;
            end;

            ARRAY_GROW(ARRAY_AT(memory, arg5).unk_00.b, s2 + 4);
            ARRAY_AT(ARRAY_AT(memory, arg5).unk_00.w, (s2 + 4) div 4) := arg22;

            ARRAY_AT(seg_ic, arg5) := s2 + 4 + arg0;            
            arg1 := arg1 - 1;
        until arg1 = 0;
    end;
end;


procedure parsecpload;
var
    reg: registers;
    saved_flag: integer;
begin
    if reorderflag then begin
        PostError(".cpload must be inside noreorder", emptystring, ErrorLevel_1);
    end;

    if picflag > 0 then begin
        saved_flag := profileflag;
        profileflag := 0;
        if gp_disp_address = nil then begin
            gp_disp_address := enter_undef_sym(l_addr(gp_disp_sym));
        end;
        reg := binasmfyle^.reg1;

        emitalui(op_zlui, xr28, xr0, disp(true, 0));
        _setrld(gp_disp_address, 2, bbindex + proc_instr_base);
        emitalui(op_zaddiu, xr28, xr28, disp(false, 0));
        _setrld(gp_disp_address, 3, bbindex + proc_instr_base);
        emitalu3(op_zaddu, xr28, xr28, reg);

        profileflag := saved_flag;
    end;
end;

procedure parsecpadd;
var
    reg: registers;
begin
    if picflag = 2 then begin
        reg := binasmfyle^.reg1;
        if not cpalias_set or cpalias_pending then begin
            emitalu3(op_zaddu, reg, reg, xr28);
        end else begin
            emitalu3(op_zaddu, reg, reg, cpalias_register);
        end;
    end;
end;

procedure parsecprestore;
begin
    if ((binasmfyle^.instr = icprestore) and cpalias_set) or ((binasmfyle^.instr = icpalias) and (cprestore_offset <> -1)) then begin
        PostError("Both .cpalias and .cprestore used in the same .ent/.end pair", emptystring, ErrorLevel_1);
    end;

    if (binasmfyle^.instr = icprestore) and (cprestore_offset <> -1) and (cprestore_offset <> binasmfyle^.length) then begin
        PostError(".cprestore offsets do not match between .ent/.end pair", emptystring, ErrorLevel_1);
    end;

    if (binasmfyle^.instr = icpalias) and cpalias_set and (cpalias_register <> binasmfyle^.reg1) then begin
        PostError(".cpalias registers do not match between .ent/.end pair", emptystring, ErrorLevel_1);
    end;

    if picflag > 0 then begin
        if binasmfyle^.instr = icprestore then begin
            cprestore_offset := binasmfyle^.length;
            if (cprestore_offset >= -16#8000) and (cprestore_offset <= 16#7FFF) then begin
                emitloadstore(op_zsw, xr28, cprestore_offset, xr29);
            end else if not atflag then begin
                macro_error();
            end else if (cprestore_offset >= 16#8000) and (cprestore_offset < 16#FFFF) then begin
                emitalui(op_zaddiu, xr1, xr29, 16#7FFF);
                emitloadstore(op_zsw, xr28, cprestore_offset - 16#7FFF, xr1);
            end else begin
                emitalui(op_zlui, xr1, xr0, disp(true, cprestore_offset));
                emitalu3(op_zaddu, xr1, xr1, xr29);
                emitloadstore(op_zsw, xr28, disp(false, cprestore_offset), xr1);
            end;
        end else begin
            cpalias_set := true;
            cpalias_pending := true;
            cpalias_register := binasmfyle^.reg1;
        end;
    end;
end;

{ not matching }
procedure parseword(arg0: cardinal);
var
    sp3C: PUnkAlpha;
    sp38: integer;
    sp34: integer;
    ba: ^binasm;
    sp2C: boolean; 
begin
    remember_symbol_size(last_globl_symno, arg0);
    ba := binasmfyle;

    if ba^.symno <> 0 then begin
        sp3C := stp(ba^.symno);
    end else begin
        sp3C := nil;
    end;

    sp2C := (ba^.instr = igpword) and (picflag = 2);
    if not((currsegment = seg_text) or (currsegment = seg_15)) then begin
        if arg0 > 4 then begin
            sp34 := ba^.expression;
            get_binasm(binasmfyle);
            dodword(arg0, ba^.replicate, sp34, binasmfyle^.expression, sp3C, currsegmentindex);
        end else begin
            doword(arg0, ba^.replicate, ba^.expression, sp3C, currsegmentindex, sp2C);
        end;
    end else if arg0 > 4 then begin
        sp34 := ba^.expression;
        get_binasm(binasmfyle);
        fill_pseudo(18, ba^.replicate, sp34, binasmfyle^.expression, sp3C, 0);
    end else if (arg0 = 2) and (shftaddr = 1) then begin
        fill_pseudo(17, 0, 1, 0, nil, 0);
        shftaddr := 0;
    end else if sp2C then begin
        fill_pseudo(22, ba^.replicate, ba^.expression, arg0, sp3C, 0);
    end else begin
        fill_pseudo(15, ba^.replicate, ba^.expression, arg0, sp3C, 0);
    end;
end;

function emit_dword_item(arg0: cardinal; arg1: cardinal; arg2: PUnkAlpha): PUnkAlpha;
var
    saved_segment: segments;
    saved_segment_index: integer;
    sym: PUnkAlpha;
    symno: integer;    
begin
    saved_segment := currsegment;
    saved_segment_index := currsegmentindex;
    currsegment := seg_rdata;
    currsegmentindex := ord(seg_rdata);    

    symno := idn_for_data();
    enterstp(symno);
    enterlabel(symno, sym);
    defineasym(symno, sym, currsegmentindex);
    dodword(8, 1, arg0, arg1, arg2, ord(seg_rdata));

    currsegment := saved_segment;
    currsegmentindex := saved_segment_index;    

    return sym;
end;

procedure parse_dli_dla;
var
    spCC: integer;
    s0: integer;
    spC4: PUnkAlpha;
    spC3: registers;
    s1: registers;
begin
    spC4 := nil;
    s1 := xnoreg;

    if binasmfyle^.form = fri then begin
        spCC := binasmfyle^.immediate;
        get_binasm(binasmfyle);
        s0 := binasmfyle^.immediate;
        spC3 := binasmfyle^.reg1;

        if binasmfyle^.form <> fri then begin
            p_assertion_failed("binasmfyle^.form <> fri\0", "as1parse.p", 2186);
        end;

        if ll_load_immed(spCC, s0, spC3) then begin
            return;
        end;
    end else begin
        s0 := binasmfyle^.immediate;
        spC3 := binasmfyle^.reg1;
        s1 := binasmfyle^.reg2;

        if s0 < 0 then begin
            spCC := -1;
        end else begin
            spCC := 0;
        end;

        if binasmfyle^.symno <> 0 then begin
            spC4 := stp(binasmfyle^.symno);
            spC4^.unk3D := true;
        end else if (s1 <> xnoreg) and (s1 <> xr0) and (s0 >= -16#8000) and (s0 <= 16#7FFF) then begin
            emitalui(op_zdaddiu, spC3, s1, s0);
            return;
        end;
    end;

    do_parseafra(zld, spC3, emit_dword_item(spCC, s0, spC4), 0, xnoreg);
    if (s1 <> xnoreg) and (s1 <> xr0) then begin
        emitalu3(op_zdaddu, spC3, spC3, s1);
    end;
end;

procedure parsestmt;
var
    spFC: PUnkAlpha;
    spF8: integer;
    spF4: integer;
    spE4: binasm;
    spE3: boolean;
    spE2: boolean;
    ba: ^binasm;
    instr: itype;
begin
    endofbasicb := false;
    branchpending := false;

    { spE4 := 0; }

    if pendinginstr then begin
        pendinginstr := false;
        if not fromas0 then begin
            if lastinstr = iedata then begin
                fill_pseudo(19, lastsymno, lastdata, 0, nil, 0);
            end else begin
                case lastinstr of
                    ient, iaent: spF4 := which_ent[lastinstr = iaent];
                    iend: spF4 := 2;
                    ibgnb: spF4 := 23;
                    iendb: spF4 := 24;
                    ilab:
                        begin
                            enterlabel(lastsymno, spFC);
                            spF4 := 25;
                        end;
                end;

                fill_pseudo(spF4, lastsymno, currentline, debugflag, spFC, 0);
                if lastinstr = iend then begin
                    return;
                end;
            end;
        end;
    end;

    lastinstr := ilabel;

    while not eof(binasm_file) do begin
        ba := binasmfyle;
        spE4 := binasmfyle^;

        if (spE4.symno <> 0) and (binasmfyle^.instr <> iend) then begin
            if in_cia_binasm then begin
                spE4.symno := fixup_symno(spE4.symno);
                binasmfyle^.symno := spE4.symno;
            end;

            enterstp(spE4.symno);
        end;

        instr := ba^.instr;
        if ((currsegment = seg_text) or (currsegment = seg_15)) and (picflag > 0) and
           (instr in [iascii, iasciiz, ibyte, idouble, ifloat, ihalf, ispace, iword, iextended]) then
        begin
            PostError("Cannot use data generating directives in .text. Use the .rdata section instead.", emptystring, ErrorLevel_1);
        end;

        if ((currsegment = seg_text) or (currsegment = seg_15)) and (bbindex > 0) and
           (ba^.instr in [ialign, iascii, iasciiz, ibyte, idouble, ifloat, ihalf, ispace, iword, iextended]) then
        begin
            if ba^.instr = ialign then begin
                fixup_preceding_labels(power2(ba^.length));
            end else if (ba^.instr = idouble) or (ba^.instr = iextended) then begin
                fixup_preceding_labels(8);
            end;

            spE3 := true;
            last_bb[3] := 0;
            endofbasicb := true;
        end else begin
            spE3 := false;

            case ba^.instr of
                ialign: parsealign();
                iascii: parseascii(false);
                iasciiz: parseascii(true);
                ibyte: parsebyte();
                icomm: parsecomm(icomm);
                iextern: parsecomm(iextern);
                idata: parseseg(seg_data);
                isdata: parseseg(seg_sdata);
                irdata: parseseg(seg_rdata);
                iedata: parseedata();
                ifloat,
                idouble,
                iextended:
                    begin
                        if ba^.instr = ifloat then begin
                            remember_symbol_size(last_globl_symno, 4);
                        end else begin
                            remember_symbol_size(last_globl_symno, 8);
                        end;
                        parsefpconst(ba^.instr);
                    end;
                ifile: parsefile();
                iglobal: parseglobl();
                iweakext: parseweakext();
                iglobabs: parseglobabs();
                ihalf: parseword(2);
                ilabel:
                    begin
                        label_size := 0;
                        if last_globl_symno <> ba^.symno then begin
                            last_globl_symno := 0;
                        end;
                        if cpalias_set then begin
                            init_cpalias();
                        end;

                        if (bbindex > 0) and not((pinstruction^[bbindex].rfd = 16#7FFFFFFF) and (pseudo_type(bbindex) = 26)) then begin
                            endofbasicb := true;
                            return;
                        end;

                        last_bb[3] := 0;
                        enterlabel(ba^.symno, spFC);
                        if (currsegment = seg_text) or (currsegment = seg_15) then begin
                            fill_pseudo(26, ba^.symno, currentline, debugflag, spFC, 0);
                        end else begin
                            defineasym(ba^.symno, spFC, currsegmentindex);
                        end;
                    end;
                ilcomm: parsecomm(ilcomm);
                ioption: parse_option();
                ialias, inoalias: parse_alias(ba^.instr);
                iloopno: fill_pseudo(21, binasmfyle^.loopnum, binasmfyle^.lflag, 0, nil, 0);
                iset: parseset(spE3);
                iasm0: fromas0 := true;
                ispace: parsespace();
                isym: entersym(ba^.symno, spFC);
                itext: parseseg(seg_text);
                imtag: parse_mtag(ba^.tagnumber, ba^.tagtype);
                imalias: parse_malias(ba^.memtag1, ba^.memtag2);
                iword, igpword: parseword(4);
                idword: parseword(8);
                ient,
                iaent:
                    begin
                        adjust_frame_by_ld := false;
                        known_framesize := -1;
                        max_arg_build := -1;
                        frame_ptr := xr29;
                        init_multi_relocinst();

                        if ba^.instr = ient then begin
                            init_malias_table();
                        end else if ba^.instr = iaent then begin
                            ignore_frames := true;
                            if ent_pending then begin
                                bbindex := bbindex + 1;
                                initbb(bbindex);
                                bbindex := bbindex - 1;
                            end;
                        end;

                        ent_pending := true;
                        last_bb[3] := 0;
                        parseend(ba^.instr);
                    end;
                iprologue: parseprologue();
                iend, ibgnb, iendb, ilab: parseend(ba^.instr);
                irep: parserepeat();
                iendrep: parseendrep();
                imask:
                    if not ignore_frames then begin
                        if not fromas0 then begin
                            fill_pseudo(7, ba^.regmask, ba^.regoffset, debugflag, nil, 0);
                        end else begin
                            spFC := stp(currentent);
                            if spFC = nil then begin
                                PostError(".mask without .ent", emptystring, ErrorLevel_1);
                            end else begin
                                spFC^.unk3A := true;
                                spFC^.unk4C := ba^.regmask;
                                spFC^.unk50 := ba^.regoffset;
                            end;
                        end;
                    end;
                ifmask:
                    if not ignore_frames then begin
                        if not fromas0 then begin
                            fill_pseudo(8, ba^.regmask, ba^.regoffset, debugflag, nil, 0);
                        end else begin
                            spFC := stp(currentent);
                            if spFC = nil then begin
                                PostError(".mask without .ent", emptystring, ErrorLevel_1);
                            end else begin
                                spFC^.unk3B := true;
                                spFC^.unk54 := ba^.regmask;
                                spFC^.unk58 := ba^.regoffset;
                            end;
                        end;
                    end;
                ivreg:
                    if debugflag > 0 then begin
                        st_pseudo(6, ba^.symno, ba^.immediate, ba^.reg1, 0, debugflag, 0);
                    end;
                iloc: parseloc(spE3);
                iverstamp:
                    if ba^.majornumber <> 7 then begin
                        PostError("version stamps wrong in binasm file", emptystring, ErrorLevel_2);
                    end;
                iframe:
                    if not ignore_frames then begin
                        if fromas0 then begin
                            spFC := stp(currentent);
                            if spFC = nil then begin
                                PostError(".frame without .ent", emptystring, ErrorLevel_1);
                            end else begin
                                spFC^.unk39 := true;
                                spFC^.unk48 := ba^.frameoffset;
                                spFC^.unk3F := ba^.framereg;
                                spFC^.unk40 := ba^.pcreg;
                            end;
                        end else begin
                            if ba^.pcreg <> xnoreg then begin
                                fill_pseudo(9, ord(ba^.framereg), ba^.frameoffset, debugflag, nil, ord(ba^.pcreg));
                            end else begin
                                fill_pseudo(9, ord(ba^.framereg), ba^.frameoffset, debugflag, nil, 0);
                            end;
                        end;

                        framereg_for_cprestore := ba^.framereg;
                    end;
                icpload:
                    begin
                        if not((currsegment = seg_text) or (currsegment = seg_15)) then begin
                            PostError(".cpload can only be placed in text", emptystring, ErrorLevel_1);
                        end;
                        parsecpload();
                    end;
                icpadd: parsecpadd();
                icprestore,
                icpalias:
                    begin
                        if not((currsegment = seg_text) or (currsegment = seg_15)) then begin
                            PostError(".cprestore or .cpalias can only be placed in text", emptystring, ErrorLevel_1);
                        end;
                        parsecprestore();
                    end;
                igjaldef: gjaldef := [ar0..afr31] - ba^.gjmask;
                igjallive: gjallive := ba^.gjmask;
                igjrlive: gjrlive := ba^.gjmask;
                ishift_addr: shftaddr := 1;
                irestext: restext := true;
                ilivereg:
                    if reorderflag and (optflag > 0) then begin
                        liveset := 1;
                        binlive := ba^.gpmask;
                        fltlive := ba^.fpmask;
                    end;
                ialloc: parsealloc();
                iocode:
                    begin
                        if not((currsegment = seg_text) or (currsegment = seg_15)) then begin
                            PostError("Code can only be placed in text", emptystring, ErrorLevel_1);
                        end;

                        if ba^.op = zbad then begin
                            PostError("Internal Error: Bad instruction opcode", emptystring, ErrorLevel_1);
                            endofbasicb := true;
                            get_binasm(binasmfyle);
                            return;
                        end;

                        spF8 := bbindex;
                        spE2 := branchpending;

                        case asm2asmformat[ba^.op] of
                            af: parseaf(ba^.op);
                            afa: parseafa(ba^.op);
                            afr: parseafr(ba^.op);
                            afrr: parseafrr(ba^.op);
                            afrrr: parseafrrr(ba^.op);
                            afra: parseafra(ba^.op);
                            afri: parseafri(ba^.op);
                            afri_fp: parseafri_fp(ba^.op);
                            afl: parseafl(ba^.op);
                            afrl: parseafrl(ba^.op);
                            afrrl: parseafrrl(ba^.op, false);
                            aforrr: parseaforrr(ba^.op);
                            dli_dla: parse_dli_dla();
                            afrrrr: parseafrrrr(ba^.op);
                            otherwise: p_assertion_failed("false\0", "as1parse.p", 264);
                        end;

                        if spE2 then begin
                            endofbasicb := true;
                            pinstruction^[bbindex].unk22 := false;
                            if bbindex <> spF8 + 1 then begin
                                PostError("Macro instruction used in branch delay slot", emptystring, ErrorLevel_2);
                            end;
                        end else if not macroflag then begin
                            if bbindex <> spF8 + 1 then begin
                                PostError("Macro instruction used", emptystring, ErrorLevel_2);
                            end;
                        end;

                        if branchpending and reorderflag then begin
                            emitnop(1);
                            endofbasicb := true;
                            branchpending := false;
                            if pinstruction^[bbindex - 1].unk24 in br_likely_ops then begin
                                pinstruction^[bbindex].unk22 := false;
                            end;
                        end;

                        if liveset = 2 then begin
                            fill_pseudo(29, binlive, fltlive, 0, nil, 0);
                            liveset := 0;
                        end;
                    end;
                otherwise: p_assertion_failed("false\0", "as1parse.p", 264);
            end;

            if ((currsegment = seg_sdata) or (currsegment = seg_data)) and
                (ba^.instr in [iascii, iasciiz, ibyte, idouble, ifloat, ihalf, ispace, iword, iextended]) then
            begin
                prev_sdata[currsegment].unk04 := false;
            end;
        end;

        if not spE3 then begin
            get_binasm(binasmfyle);
        end;

        if bbindex > num_pseudo + 280 then begin
            endofbasicb := true;
        end;

        if endofbasicb then begin
            return;
        end;
    end;
end;