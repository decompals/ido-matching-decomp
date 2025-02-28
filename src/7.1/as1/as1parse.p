#include "common.i"

var
    need_cprestore: boolean;
    cpalias_set: boolean;
    cpalias_pending: boolean;
    cprestore_offset: integer;
    framereg_for_cprestore: registers;
    cpalias_register: registers;
    branchpending: boolean;

procedure fill_pseudo(reg1: registers; reg2: registers; reg3: registers; val1: integer; val2: integer; val3: integer); external; { TODO signature }
procedure get_binasm(var b: PBinasm); external;
function stp(symno: integer): PUnkAlpha; external;
procedure _setrld(sym: PUnkAlpha; arg1: integer; arg2: integer); external;
procedure loadimmed(arg0: integer; arg1: registers; arg2: PUnkAlpha); external;

{ forward declarations }
procedure emitloadstore(op: opcodes; reg1: registers; offset: integer; reg2: registers); external;
procedure emitalui(op: opcodes; reg1: registers; reg2: registers; imm: integer); external;
procedure emitalu3(op: opcodes; reg1: registers; reg2: registers; reg3: registers); external;
procedure emitspec(op: opcodes; arg1: integer); external;
procedure emitnop(arg0: boolean); external;
function call_as0(var arg0: Filename; var arg1: Filename; var arg2: Filename) : integer; external;

procedure macro_error;
begin
    PostError("macro instruction used $at", emptystring, ErrorLevel_2);
end;

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
        emitnop(true);
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
        return
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
    ba: ^binasm;
    reg1: registers;
    sym: PUnkAlpha;
begin
    if cpalias_set then begin
        init_cpalias();
    end else begin
        restore_gp();
    end;

    ba := binasmfyle;
    branchpending := true;
    reg1 := ba^.reg1;

    if reg1 in [xfr0..xfr31] then begin
        p_assertion_failed("not reg1 in [xfr0..xfr31]\0", "as1parse.p", 285);
    end;

    sym := nil;
    
end;