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

procedure fill_pseudo(reg1: registers; reg2: registers; reg3: registers; val1: integer; val2: integer; val3: integer); external; { TODO signature }
procedure get_binasm(var b: PBinasm); external;
function stp(symno: integer): PUnkAlpha; external;
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
        fill_pseudo(xr28, gpreg, xr29, 0, 0, 0);
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
        rld_list.data^[nextrld - 1].unk14 := immediate; { NON MATCHING line }
        rld_list.data^[nextrld - 1].unk11 := reg;
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
    ba: ^binasm;
begin
    ba := binasmfyle;

    if ba^.form <> fr then begin
        p_assertion_failed("form = fr\0", "as1parse.p", 1031);
    end;
    emitreg2(asm2op[fasm], ba^.reg1, xnoreg);
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

    if (currsegment = 1) or (currsegment = 2) then begin
        if prev_sdata[currsegment].unk04 then begin
            prev_sdata[currsegment].unk08 := Max(prev_sdata[currsegment].unk08, binasmfyle^.length); { maybe bug? }
        end else begin
            prev_sdata[currsegment].unk0C := seg_ic.data^[currsegmentindex];
            prev_sdata[currsegment].unk04 := true;
            prev_sdata[currsegment].unk08 := v;
        end;
    end;

    if (currsegment = 0) or (currsegment = 2) or (currsegment = 9) or (currsegment = 1) then begin
        prev_align[currsegment].unk08 := Max(prev_align[currsegment].unk08, v);
    end;

    if (currsegment <> 0) and (currsegment <> 15) then begin
        aligning := n > 0;
        definealabel(currsegmentindex, v, 0);
    end else begin
        fill_pseudo(xr11, registers(v), xr0, 0, 0, 0); { TODO arg2 type }
    end;
end;