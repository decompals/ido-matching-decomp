#include "common_p.h"

function emit_dword_item(arg0: cardinal; arg1: cardinal; arg2: PSymbol): PSymbol; external;
procedure parse_dli_dla; external;
function stp(symno: integer): PSymbol; external;
function emit_pool_const(arg0: UnkFPStruct; arg1: boolean; arg2: boolean; arg3: segments): integer; external;
function get_fp_string(size: integer): PFilename; external;
procedure string_to_fpoverlay(arg0: GString; arg1: UnknownEnum; var arg2: UnkFPStruct; var arg3: boolean; var arg4: boolean); external;
function short_s(arg0: integer): integer; external;
function short_d(arg0: integer; arg1: integer): integer; external;
procedure emitfli(op: opcodes; reg1: registers; arg2: integer); external;
function generate_as_immediate(fasm: asmcodes; reg1: registers; arg2: integer; arg3: integer): boolean; external;
function emit_fp_const(arg0: UnkFPStruct; arg1: boolean; arg2: boolean; arg3: UnknownEnum; var arg4: integer): PSymbol; external;

var
    { extern }
    isa: extern mips_isa;
    multirelocinstr_list: extern ARRAY_OF(MultiRelocRec);
    nextmultirelocinstr: extern integer;
    storeops: extern set of opcodes;
    s_pool_symbol: extern PSymbol;
    d_pool_symbol: extern PSymbol;
    knownregs: extern set of registers;
    gp_symbol: extern PSymbol;

    { .data }
    gp_symbol_name : Identname := "_gp\0";
    size_to_alignment : array [0..8] of 1..8 := [1, 1, 2, 4, 4, 8, 8, 8, 8];
    addr_to_alignment : array [0..7] of 1..8 := [3, 0, 1, 0, 2, 0, 1, 0];
    emagic_names: array [1..12] of Identname := [
        "_etext\0",
        "_end\0",
        "_edata\0",
        "_fbss\0",
        "_fdata\0",
        "_ftext\0",
        "_gp\0",
        "_procedure_table\0",
        "_procedure_table_size\0",
        "etext\0",
        "end\0",
        "edata\0"
    ];
    

procedure basereg_error();
begin    
    PostError("register must differ from base", emptystring, ErrorLevel_1);
end;

procedure setup_tempreg(arg0: integer;
                        arg1: registers;
                        arg2: registers;
                        var arg3: PSymbol;
                        var arg4: integer;
                        var arg5: RldType;
                        arg6: boolean;
                        arg7: asmcodes);
    function func_0045C2AC(arg0: boolean; arg1: registers; arg2: PSymbol; arg3: integer): boolean;

        function func_0045C154(arg0: integer; arg1: integer; arg2: integer; arg3: integer; arg4: segments): boolean;
        var
            alignment: integer;
            
            function func_0045C134(arg0: integer; arg1: integer): integer;
            begin
                arg1 := arg0 + arg1;
                if arg1 < 0 then begin
                    arg1 := arg1 - alignment + 1;
                end;
                return arg1;
            end;
            
        begin
            if (arg4 = seg_4) or (arg4 = seg_3) then begin
                if arg3 = 0 then begin
                    return False;
                end;
                alignment := size_to_alignment[min(arg3, 8)];
                arg2 := 0;
            end else if (arg4 = seg_data) or (arg4 = seg_sdata) then begin
                alignment := 16;
            end else begin
                return arg0 = arg1;
            end;
    
            arg0 :=func_0045C134(arg2, arg0);
            arg1 :=func_0045C134(arg2, arg1);
            return (arg0 div alignment) = (arg1 div alignment);
        end;

    
    begin
        if (optflag <= 0) or
           not (opts.unk_00[2]) or
           (pre_reorder_peepholes.unk_00 < 0) or
           (arg0 <> pre_reorder_peepholes.unk_0D) or
           (arg1 <> pre_reorder_peepholes.unk_0C) or
           (arg2 <> pre_reorder_peepholes.unk_04) or
           not func_0045C154(arg3, pre_reorder_peepholes.unk_08, arg2^.unk10, arg2^.unk28, ARRAY_AT(memory, arg2^.unk30).unk_08) then begin
            return False;
        end;

        if defined_in_between(xr1, bbindex, pre_reorder_peepholes.unk_00) then begin
            return False;
        end;

        if (arg1 <> xnoreg) and defined_in_between(arg1, bbindex, pre_reorder_peepholes.unk_00) then begin
            return False;
        end;

        opts.unk_08[2] := opts.unk_08[2] + 1;

        return True;
    end;
    
begin
    arg5 := RLD_TYPE_3;
    
    if (arg1 = xr1) and ((picflag = 0) or ((picflag = 1) and (arg3 <> nil) and (is_dso_static(arg3^.unk18) = true))) then begin
        if not atflag then begin
            macro_error();
        end;

        if not arg6 and func_0045C2AC(arg0 >= 2, arg2, arg3, arg4) then begin
            if (arg6 or (arg0 >= 2) and (bitand(arg4, 4 * arg0 - 1) <> 0)) then begin
                arg4 := arg4 - pre_reorder_peepholes.unk_08;
                arg3 := nil;
            end else begin
                arg4 := disp(false, arg4);
            end;
            
            return;
        end;
    end;

    if (picflag = 2) or ((picflag = 1) and not ((arg3 <> nil) and is_dso_static(arg3^.unk18))) then begin
        if not atflag then begin
            macro_error();
        end;

        if (arg4 > 16#7FFF) or (arg4 < -16#8000) then begin
            PostError("offset in PIC code cannot exceed 16 signed bits", emptystring, ErrorLevel_1);
        end;

        restore_gp();

        if islocalsym(arg3) then begin
            emitloadstore(asm2op[zlw], arg1, disp(true, arg4), gpreg);
            _setrld(arg3, RLD_TYPE_15, bbindex + proc_instr_base);
        end else begin
            if big_got then begin
                emitalui(op_zlui, arg1, xr0, 0);
                _setrld(arg3, RLD_TYPE_22, bbindex + proc_instr_base);
                emitalu3(op_zaddu, arg1, arg1, gpreg);
                emitloadstore(asm2op[zlw], arg1, 0, arg1);
                _setrld(arg3, RLD_TYPE_23, bbindex + proc_instr_base);
            end else begin
                emitloadstore(asm2op[zlw], arg1, 0, gpreg);
                _setrld(arg3, RLD_TYPE_15, bbindex + proc_instr_base);
            end;

            arg5 := RLD_TYPE_0;
        end;

        if not reorderflag and (isa < ISA_MIPS2) then begin
            emitnop(1);
            pinstruction^[bbindex].unk22 := false;
        end;        
    end else if arg7 = zdla then begin
        emitalui(op_zlui, arg1, xr0, disp(true, arg4));
        _setrld(arg3, RLD_TYPE_4, bbindex + proc_instr_base);
        emitalui(op_zlui, arg1, arg1, disp(true, arg4));
        _setrld(arg3, RLD_TYPE_5, bbindex + proc_instr_base);
        emitalui(op_zlui, arg1, arg1, disp(true, arg4));
        _setrld(arg3, RLD_TYPE_2, bbindex + proc_instr_base);
    end else begin
        emitalui(op_zlui, arg1, xr0, disp(true, arg4));
        if (arg2 = xr29) and adjust_frame_by_ld and ((arg4 >= known_framesize) or (arg4 <= -known_framesize)) then begin
            request_multi_relocinst(bbindex + proc_instr_base);
            ARRAY_GROW(multirelocinstr_list, nextmultirelocinstr);
            ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_08 := bbindex + proc_instr_base;
            ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_00 := sp_addu_index;
            nextmultirelocinstr := nextmultirelocinstr + 1;
            arg5 := RLD_TYPE_0;
        end else begin
            _setrld(arg3, RLD_TYPE_2, bbindex + proc_instr_base);
        end;
    end;

    if (arg2 <> xnoreg) and (arg2 <> xr0) then begin
        emitalu3(op_zaddu, arg1, arg1, arg2);
    end;

    if arg1 = xr1 then begin
        pre_reorder_peepholes.unk_04 := arg3;
        pre_reorder_peepholes.unk_08 := arg4;
        pre_reorder_peepholes.unk_0C := arg2;
        pre_reorder_peepholes.unk_0D := arg0 >= 2;
    end;

    if (arg6 or (arg0 >= 2) and (bitand(arg4, 4 * arg0 - 1) <> 0)) then begin
        emitalui(op_zaddiu, arg1, arg1, disp(false, arg4));
        if arg5 <> RLD_TYPE_0 then begin
            _setrld(arg3, RLD_TYPE_3, bbindex + proc_instr_base);
        end;
        arg4 := 0;
        arg3 := nil;
    end else begin
        arg4 := disp(false, arg4);
    end;

    if arg1 = xr1 then begin
        pre_reorder_peepholes.unk_00 := bbindex;
    end;
end;

function check_if_gp_relative(arg0: PSymbol; arg1: integer): boolean;
    function func_0045CCDC(arg0: PSymbol): boolean;
    var
        i: integer;
    begin
        for i := 1 to 12 do begin
            if strcmp(pointer(arg0^.unk0C.c), l_addr(emagic_names[i])) = 0 then begin
                return True;
            end;
        end;
        return False;
    end;
begin
    if (arg0 = s_pool_symbol) or (arg0 = d_pool_symbol) then begin
        return True;
    end;
    
    if picflag >= 2 then begin
        return False;
    end;

    if picflag = 1 then begin
        if arg0^.unk3C then begin
            return False;
        end;
        if arg0^.unk34 = 'C' then begin
            return False;
        end;
        if (arg0^.unk34 = 'V') and not arg0^.unk37 then begin
            arg0^.unk34 := 'U';
            return False;
        end;
    end;

    if func_0045CCDC(arg0) then begin
        return False;
    end;

    if (arg1 < -16#8000) or (arg1 > 16#7FFF) then begin
        return False;
    end;

    if (ARRAY_AT(memory, arg0^.unk30).unk_08 <> seg_sdata) and
       (ARRAY_AT(memory, arg0^.unk30).unk_08 <> seg_3) and
       (not(arg0^.unk34 in ['C', 'V']) or (arg0^.unk28 > gprelsize) or (arg0^.unk28 <= 0)) and
       not ((arg0^.unk34 = 'V') and (ARRAY_AT(memory, arg0^.unk30).unk_08 = seg_13)) and 
       (arg0^.unk34 <> 'E') then begin
        return False;
    end;
    
    if not ((arg1 >= -16) and (arg1 <= arg0^.unk28 + 16)) and
       not((ARRAY_AT(memory, arg0^.unk30).unk_08 = seg_sdata) and (arg0^.unk10 + arg1 >= 0) and (arg0^.unk10 + arg1 < ARRAY_AT(seg_ic, 1))) and
       not((ARRAY_AT(memory, arg0^.unk30).unk_08 = seg_3) and (arg0^.unk10 + arg1 >= 0) and (arg0^.unk10 + arg1 < ARRAY_AT(seg_ic, 3))) then begin
        if opts.unk_1E then begin
            if arg0^.unk34 = 'C' then begin
                PostError("Bss offset exceeded $gp padding threshold", emptystring, ErrorLevel_2);
            end else if arg0^.unk34 = 'V' then begin
                PostError("Extern offset exceeds $gp padding threshold", emptystring, ErrorLevel_2);
            end;
        end;
        
        return False;
    end;

    arg0^.unk36 := 1;
    return True;
end;

function is_gp_relative(arg0: PSymbol; arg1: integer; arg2: registers; var arg3: registers): boolean;
begin
    if not check_if_gp_relative(arg0, arg1) then begin
        return False;
    end;

    restore_gp();

    if (arg2 <> xnoreg) and (arg2 <> xr0) then begin
        if not atflag then begin
            macro_error();
        end;
        emitalu3(op_zaddu, xr1, arg2, gpreg);
        arg3 := xr1;
    end else begin
        arg3 := gpreg;
    end;
    
    return True;
end;

procedure genfpmultiple(arg0: asmcodes;
                        arg1: registers;
                        arg2: PSymbol;
                        arg3: integer;
                        arg4: registers;
                        words: integer;
                        arg6: boolean;
                        arg7: boolean);
var
    spD4: integer;
    spD3: registers;
    spD2: registers;
    spD1: registers;
    spD0: registers;
    spCF: registers;
    spCC: opcodes;
    spCB: RldType;
    unused: integer;
begin
    spD4 := arg3;
    spD3 := arg1;
    
    if not (arg1 in [xfr0..xfr31]) then begin
        PostError("operand 1 should be fp reg", emptystring, ErrorLevel_1);
        return;
    end;

    if words = 2 then begin
        if bigendian and not moxieflag and not arg6 then begin
            spD2 := arg1;
            spD3 := succ(arg1);
        end else begin
            spD2 := succ(arg1);
        end;
    end else if words = 4 then begin
        if bigendian and not moxieflag then begin
            spD0 := arg1;
            spD1 := succ(spD0);
            spD2 := succ(spD1);
            spD3 := succ(spD2);
        end else begin
            spD2 := succ(arg1);
            spD1 := succ(spD2);
            spD0 := succ(spD1);
        end;
    end else if words <> 1 then begin
        p_assertion_failed("words = 1\0", "parsera.p", 592);
    end;

    if arg6 and (words = 2) then begin
        if arg0 = fl_d then begin
            spCC := op_zldc1;
        end else begin
            spCC := op_zsdc1;
        end;

        words := 1;
    end else if arg0 in [fl_s, fl_d, fl_e] then begin
        spCC := op_zlwc1;
    end else begin
        spCC := op_zswc1;
    end;

    if (arg4 = xr29) and adjust_frame_by_ld and not((arg3 < known_framesize) and (arg3 > -known_framesize)) then begin
        setup_tempreg(words, xr1, arg4, arg2, spD4, spCB, False, arg0);
        if words < 2 then begin
            emitloadstore(spCC, spD3, disp(false, spD4), xr1);
            request_multi_relocinst(bbindex + proc_instr_base);
            ARRAY_AT(multirelocinstr_list, nextmultirelocinstr - 1).unk_0C := bbindex + proc_instr_base;
            ARRAY_AT(multirelocinstr_list, nextmultirelocinstr - 1).unk_04 := sp_addu_index + 1;
            return;
        end;

        emitloadstore(spCC, spD3, spD4, xr1);
        request_multi_relocinst(bbindex + proc_instr_base);
        ARRAY_AT(multirelocinstr_list, nextmultirelocinstr - 1).unk_0C := bbindex + proc_instr_base;
        ARRAY_AT(multirelocinstr_list, nextmultirelocinstr - 1).unk_04 := sp_addu_index + 1;

        emitloadstore(spCC, spD2, spD4 + 4, xr1);
        request_multi_relocinst(bbindex + proc_instr_base);
        ARRAY_GROW(multirelocinstr_list, nextmultirelocinstr);
        ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_0C := bbindex + proc_instr_base;
        ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_00 := 0;
        ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_04 := sp_addu_index + 1;
        nextmultirelocinstr := nextmultirelocinstr + 1;

        if words = 4 then begin
            emitloadstore(spCC, spD1, spD4 + 8, xr1);
            request_multi_relocinst(bbindex + proc_instr_base);
            ARRAY_GROW(multirelocinstr_list, nextmultirelocinstr);
            ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_0C := bbindex + proc_instr_base;
            ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_00 := 0;
            ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_04 := sp_addu_index + 1;
            nextmultirelocinstr := nextmultirelocinstr + 1;
    
            emitloadstore(spCC, spD0, spD4 + 12, xr1);
            request_multi_relocinst(bbindex + proc_instr_base);
            ARRAY_GROW(multirelocinstr_list, nextmultirelocinstr);
            ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_0C := bbindex + proc_instr_base;
            ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_00 := 0;
            ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_04 := sp_addu_index + 1;
            nextmultirelocinstr := nextmultirelocinstr + 1;
        end;
    end else if (arg2 <> nil) and not arg7 then begin
        if is_gp_relative(arg2, arg3, arg4, spCF) then begin
            emitloadstore(spCC, spD3, arg3, spCF);
            _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);

            if words >= 2 then begin
                if spD3 = spCF then begin
                    basereg_error();
                end;
                emitloadstore(spCC, spD2, arg3 + 4, spCF);
                _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);

                if words = 4 then begin
                    if (spD2 = spCF) or (spD1 = spCF) then begin
                        basereg_error();
                    end;
                    emitloadstore(spCC, spD1, arg3 + 8, spCF);
                    _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
                    emitloadstore(spCC, spD0, arg3 + 12, spCF);
                    _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
                end;
            end;
        end else begin
            setup_tempreg(words, xr1, arg4, arg2, spD4, spCB, False, arg0);
            if words < 2 then begin
                emitloadstore(spCC, spD3, disp(false, spD4), xr1);
                _setrld(arg2, spCB, bbindex + proc_instr_base);
                return;
            end;

            emitloadstore(spCC, spD3, spD4, xr1);
            if arg2 <> nil then begin
                _setrld(arg2, spCB, bbindex + proc_instr_base);
            end;

            emitloadstore(spCC, spD2, spD4 + 4, xr1);
            if arg2 <> nil then begin
                _setrld(arg2, spCB, bbindex + proc_instr_base);
            end;

            if words = 4 then begin
                emitloadstore(spCC, spD1, spD4 + 8, xr1);
                if arg2 <> nil then begin
                    _setrld(arg2, spCB, bbindex + proc_instr_base);
                end;
    
                emitloadstore(spCC, spD0, spD4 + 12, xr1);
                if arg2 <> nil then begin
                    _setrld(arg2, spCB, bbindex + proc_instr_base);
                end;
            end;
        end;
    end else if (arg3 < -16#8000) or (arg3 > 16#7FFF - 4) then begin
        if not atflag then begin
            macro_error();
        end;

        emitalui(op_zlui, xr1, xr0, disp(true, arg3));
        if (arg4 <> xnoreg) and (arg4 <> xr0) then begin
            emitalu3(op_zaddu, xr1, xr1, arg4);
        end;

        emitloadstore(spCC, spD3, disp(false, arg3), xr1);
        _setrld(arg2, RLD_TYPE_3, bbindex + proc_instr_base);

        if words >= 2 then begin
            if arg3 = 16#7FFF - 3 then begin
                emitalui(op_zaddiu, xr1, xr1, disp(false, 4));
                emitloadstore(spCC, spD2, disp(false, arg3), xr1);
            end else begin
                emitloadstore(spCC, spD2, disp(false, arg3 + 4), xr1);
            end;
            _setrld(arg2, RLD_TYPE_3, bbindex + proc_instr_base);

            if words = 4 then begin
                if arg3 = 16#7FFF - 7 then begin
                    emitalui(op_zaddiu, xr1, xr1, disp(false, 8));
                    emitloadstore(spCC, spD1, disp(false, arg3), xr1);
                    _setrld(arg2, RLD_TYPE_3, bbindex + proc_instr_base);
                    emitloadstore(spCC, spD0, disp(false, arg3 + 4), xr1);
                    _setrld(arg2, RLD_TYPE_3, bbindex + proc_instr_base);
                end else begin
                    emitloadstore(spCC, spD1, disp(false, arg3 + 8), xr1);
                    _setrld(arg2, RLD_TYPE_3, bbindex + proc_instr_base);
                    if arg3 = 16#7FFF - 11 then begin
                        emitalui(op_zaddiu, xr1, xr1, disp(false, 4));
                        emitloadstore(spCC, spD0, disp(false, arg3 + 8), xr1);
                    end else begin
                        emitloadstore(spCC, spD0, disp(false, arg3 + 12), xr1);
                    end;
                    _setrld(arg2, RLD_TYPE_3, bbindex + proc_instr_base);
                end;
            end;
        end;
    end else begin
        if arg4 = xnoreg then begin
            arg4 := xr0;
        end;

        if arg7 and (arg2 <> nil) then begin
            if words >= 2 then begin
                loadimmed(0, xr1, arg2);
                emitalu3(op_zaddu, xr1, xr1, arg4);
                emitloadstore(spCC, spD3, 0, xr1);
                emitloadstore(spCC, spD2, 4, xr1);
                if words = 4 then begin
                    emitloadstore(spCC, spD1, 8, xr1);
                    emitloadstore(spCC, spD0, 12, xr1);
                end;
            end else begin
                emitloadstore(spCC, spD3, 0, arg4);
                _setrld(arg2, RLD_TYPE_9, bbindex + proc_instr_base);
            end;
        end else begin
             emitloadstore(spCC, spD3, arg3, arg4);
             if words >= 2 then begin
                emitloadstore(spCC, spD2, arg3 + 4, arg4);
                if words = 4 then begin
                    emitloadstore(spCC, spD1, arg3 + 8, arg4);
                    emitloadstore(spCC, spD0, arg3 + 12, arg4);
                end;
            end;
        end;
    end;
end;

procedure enforce_destreg(arg0: registers; arg1: integer);
begin
    if bitand(ord(arg0), arg1 - 1) <> 0 then begin
        PostError("Improperly aligned register", emptystring, ErrorLevel_2);
    end;
end;

procedure do_parseafra({arg0: asmcodes; arg1: registers; arg2: PSymbol; arg3: integer; arg4: registers});
var
    sp77: registers;
    sp76: registers;
    sp75: registers;
    sp74: RldType;
    sp70: integer;

    function func_0045E41C(): registers;
    begin
        if (arg4 <> arg1) and
           (arg1 in [xr1..xr31]) and
           not (asm2op[arg0] in (storeops + [op_zlwl, op_zlwr])) then begin
            func_0045E41C := arg1;
        end else begin
            func_0045E41C := xr1;
            if not atflag then begin
                macro_error();
            end;
        end;
    end;
begin
    if (arg0 = zcache) or (arg0 = zpref) then begin
        sp75 := arg1;
    end;

    if arg0 = zlgota then begin
        if picflag = 0 then begin
            PostError("lgota can only be used in PIC mode", emptystring, ErrorLevel_1);
        end else if not((arg2 <> nil) and (arg3 = 0) and (arg4 = xnoreg)) then begin
            PostError("lgota takes an global symbol without offset or base register", emptystring, ErrorLevel_1);
        end else if islocalsym(arg2) then begin
            PostError("lgota only takes a global symbol", emptystring, ErrorLevel_1);
        end else begin
            restore_gp();
            emitalui(op_zaddiu, arg1, gpreg, 0);
            _setrld(arg2, RLD_TYPE_15, bbindex + proc_instr_base);
        end;
    end else if arg2 <> nil then begin
        if is_gp_relative(arg2, arg3, arg4, sp77) then begin
            if arg0 = zdla then begin
                emitalui(op_zdaddiu, arg1, sp77, arg3);
            end else if arg0 = zla then begin
                emitalui(op_zaddiu, arg1, sp77, arg3);
            end else if (arg0 = zcache) or (arg0 = zpref) then begin
                emitcache(asm2op[arg0], sp77, arg3, sp75);
            end else begin
                emitloadstore(asm2op[arg0], arg1, arg3, sp77);
            end;
            _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
        end else if (arg0 = zla) and ((picflag = 2) or (picflag = 1) and not ((arg2 <> nil) and is_dso_static(arg2^.unk18))) then begin
            restore_gp();
            if islocalsym(arg2) then begin
                if not atflag then begin
                    macro_error();
                end;

                if (arg3 < -16#8000) or (arg3 > 16#7FFF) then begin
                    sp76 := func_0045E41C();
                    
                    emitloadstore(asm2op[zlw], sp76, 0, gpreg);
                    _setrld(arg2, RLD_TYPE_15, bbindex + proc_instr_base);

                    if not reorderflag and (isa < ISA_MIPS2) then begin
                        emitnop(1);
                        pinstruction^[bbindex].unk22 := false;
                    end;

                    if (arg4 <> xnoreg) and (arg4 <> xr0) then begin
                        emitalu3(op_zaddu, arg1, sp76, arg4);
                    end else if arg1 <> sp76 then begin
                        emitalu3(op_zor, arg1, sp76, xr0);
                    end;

                    emitalui(op_zaddiu, arg1, arg1, disp(false, arg3));
                    _setrld(arg2, RLD_TYPE_3, bbindex + proc_instr_base);
                    emitalui(op_zlui, xr1, xr0, disp(true, arg3));
                    emitalu3(op_zaddu, arg1, xr1, arg1);
                end else begin
                    sp70 := disp(true, arg3);
                    if sp70 > 16#8012 then begin
                        sp70 := sp70 - 16#10000;
                    end;
                    sp76 := func_0045E41C();

                    emitloadstore(asm2op[zlw], sp76, sp70, gpreg);
                    _setrld(arg2, RLD_TYPE_15, bbindex + proc_instr_base);

                    if not reorderflag and (isa < ISA_MIPS2) then begin
                        emitnop(1);
                        pinstruction^[bbindex].unk22 := false;
                    end;

                    if (arg4 <> xnoreg) and (arg4 <> xr0) then begin
                        emitalu3(op_zaddu, sp76, sp76, arg4);
                    end;

                    emitalui(op_zaddiu, arg1, sp76, disp(false, arg3));
                    _setrld(arg2, RLD_TYPE_3, bbindex + proc_instr_base);
                end;
            end else begin
                sp76 := func_0045E41C();

                if big_got then begin
                    emitalui(op_zlui, sp76, xr0, 0);
                    _setrld(arg2, RLD_TYPE_22, bbindex + proc_instr_base);
                    emitalu3(op_zaddu, sp76, sp76, gpreg);
                    emitloadstore(op_zlw, sp76, 0, sp76);
                    _setrld(arg2, RLD_TYPE_23, bbindex + proc_instr_base);
                end else begin
                    emitloadstore(asm2op[zlw], sp76, 0, gpreg);
                    _setrld(arg2, RLD_TYPE_15, bbindex + proc_instr_base);
                end;

                if not reorderflag and (isa < ISA_MIPS2) and (((arg4 <> xnoreg) and (arg4 <> xr0)) or (arg3 <> 0)) then begin
                    emitnop(1);
                    pinstruction^[bbindex].unk22 := false;
                end;

                if (arg4 <> xnoreg) and (arg4 <> xr0) then begin
                    emitalu3(op_zaddu, arg1, sp76, arg4);
                end else if arg1 <> sp76 then begin
                    emitalu3(op_zor, arg1, sp76, xr0);
                end;

                if (arg3 < -16#8000) or (arg3 > 16#7FFF) then begin
                    if not atflag then begin
                        macro_error();
                    end;

                    emitalui(op_zlui, xr1, xr0, disp(true, arg3));
                    emitalui(op_zaddiu, xr1, xr1, disp(false, arg3));
                    emitalu3(op_zaddu, arg1, xr1, arg1);
                end else if arg3 <> 0 then begin
                    emitalui(op_zaddiu, arg1, arg1, arg3);
                end;
            end;
        end else begin
            sp76 := func_0045E41C();
            setup_tempreg(1, sp76, arg4, arg2, arg3, sp74, False, arg0);
            if arg0 = zdla then begin
                emitalui(op_zdaddiu, arg1, sp76, disp(False, arg3));
            end else if arg0 = zla then begin
                emitalui(op_zaddiu, arg1, sp76, disp(False, arg3));
            end else if (arg0 = zcache) or (arg0 = zpref) then begin
                emitcache(asm2op[arg0], sp76, disp(False, arg3), sp75);
            end else begin
                emitloadstore(asm2op[arg0], arg1, disp(False, arg3), sp76);
            end;
            _setrld(arg2, sp74, bbindex + proc_instr_base);
        end;
    end else if (arg0 <> zcache) and (arg0 <> zpref) and ((arg3 < -16#8000) or (arg3 > 16#7FFF)) then begin
        sp76 := func_0045E41C();
        if (arg4 <> xnoreg) and (arg4 <> xr0) and (arg3 < 16#FFFF) and (arg3 > 0) then begin
            emitalui(op_zaddiu, sp76, arg4, 16#7FFF);
            if arg0 = zla then begin
                emitalui(op_zaddiu, arg1, sp76, arg3 - 16#7FFF);
            end else begin
                emitloadstore(asm2op[arg0], arg1, arg3 - 16#7FFF, sp76);
            end;
        end else begin
            emitalui(op_zlui, sp76, xr0, disp(true, arg3));
            
            if (arg4 <> xnoreg) and (arg4 <> xr0) then begin
                emitalu3(op_zaddu, sp76, sp76, arg4);
            end;
            
            if arg0 = zla then begin
                emitalui(op_zaddiu, arg1, sp76, disp(False, arg3));
            end else begin
                emitloadstore(asm2op[arg0], arg1, disp(False, arg3), sp76);
            end;
        end;
    end else if arg0 = zla then begin
        emitalui(op_zaddiu, arg1, arg4, arg3);
    end else if (arg0 = zcache) or (arg0 = zpref) then begin
        emitcache(asm2op[arg0], arg4, arg3, sp75);
    end else begin
        emitloadstore(asm2op[arg0], arg1, arg3, arg4);
    end;
end;

procedure gendouble(arg0: asmcodes;
                    arg1: registers;
                    arg2: PSymbol;
                    arg3: integer;
                    arg4: registers;
                    arg5: boolean);
var
    sp4C: integer;
    a2: integer;
    sp44: integer;
    sp43: registers;
    sp42: registers;
    sp41: registers;
    a1: registers;
    sp3F: registers;
    sp3E: registers;    
    sp3C: opcodes;
    sp3B: boolean;
    sp3A: RldType;

    procedure func_0045F430(var arg0: registers; var arg1: boolean);
    begin
        arg0 := xr1;
        arg1 := False;
        
        if not(sp3C in storeops) and not atflag then begin
            if arg4 <> sp42 then begin
                arg0 := sp42;
            end else if arg4 <> sp43 then begin
                arg0 := sp43;
                arg1 := True;
            end
        end;
    end;
begin
    sp4C := arg3;
    sp43 := arg1;
    sp42 := succ(arg1);

    if arg0 = zld then begin
        sp3C := op_zlw;
    end else begin
        sp3C := op_zsw;
    end;

    if (arg2 <> nil) and not arg5 then begin
        if is_gp_relative(arg2, arg3, arg4, sp3E) then begin
            if arg1 = sp3E then begin
                basereg_error();
            end;
            emitloadstore(sp3C, arg1, arg3, sp3E);
            _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
            emitloadstore(sp3C, sp42, arg3 + 4, sp3E);
            _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
        end else begin
            func_0045F430(sp41, sp3B);
            setup_tempreg(2, sp41, arg4, arg2, sp4C, sp3A, False, arg0);

            if sp3B then begin
                a2 := sp4C + 4;
                sp44 := sp4C;
                a1 := sp42;
                sp3F := sp43;
            end else begin
                a2 := sp4C;
                sp44 := sp4C + 4;
                a1 := sp43;
                sp3F := sp42;
            end;

            emitloadstore(sp3C, a1, a2, sp41);
            if arg2 <> nil then begin
                _setrld(arg2, sp3A, bbindex + proc_instr_base);
            end;

            emitloadstore(sp3C, sp3F, sp44, sp41);
            if arg2 <> nil then begin
                _setrld(arg2, sp3A, bbindex + proc_instr_base);
            end;
        end;
    end else if (arg3 < -16#8000) or (arg3 > 16#7FFF - 3) then begin
        func_0045F430(sp41, sp3B);

        if (sp41 = xr1) and not atflag then begin
            macro_error();
        end;

        emitalui(op_zlui, sp41, xr0, disp(True, sp4C));
        if (arg4 <> xnoreg) and (arg4 <> xr0) then begin
            emitalu3(op_zaddu, sp41, sp41, arg4);
        end;

        if sp3B then begin
            emitloadstore(sp3C, sp42, disp(False, sp4C + 4), sp41);
            emitloadstore(sp3C, sp43, disp(False, sp4C), sp41);
        end else begin
            emitloadstore(sp3C, sp43, disp(False, sp4C), sp41);
            if sp4C = 16#7FFF - 3 then begin
                emitalui(op_zaddiu, sp41, sp41, disp(False, 4));
                emitloadstore(sp3C, sp43, disp(False, sp4C), sp41);
            end else begin
                emitloadstore(sp3C, sp42, disp(False, sp4C + 4), sp41);
            end;
        end;
    end else begin
        if (arg4 = xnoreg) or (arg4 = xr0) then begin
            arg4 := xr0;
        end;

        if arg5 and (arg2 <> nil) then begin
            func_0045F430(sp41, sp3B);

            if (sp41 = xr1) and not atflag then begin
                macro_error();
            end;

            loadimmed(0, sp41, arg2);
            emitalu3(op_zaddu, sp41, sp41, arg4);

            if sp43 = arg4 then begin
                emitloadstore(sp3C, sp42, 4, sp41);
                emitloadstore(sp3C, sp43, 0, sp41);
            end else begin
                emitloadstore(sp3C, sp43, 0, sp41);
                emitloadstore(sp3C, sp42, 4, sp41);
            end;
        end else begin
            if arg1 = arg4 then begin
                emitloadstore(sp3C, sp42, arg3 + 4, arg4);
                emitloadstore(sp3C, arg1, arg3, arg4);
            end else begin
                emitloadstore(sp3C, arg1, arg3, arg4);
                emitloadstore(sp3C, sp42, arg3 + 4, arg4);
            end;
        end;
    end;
end;

{ 
    Not matching function
    only stack diff
    url: https://decomp.me/scratch/sxuBO
    score: 24 (99.99%)
}

procedure parseafra(fasm: asmcodes);
var
    spDF: registers;
    spDE: registers;
    spD8: integer;
    spD4: PSymbol;
    spD3: Alignment;
    spD2: boolean;
    a2: PUnkALpha;     
    a0: integer;

    function func_0045FB50(arg0: registers; arg1: integer; arg2: PSymbol): Alignment;
    var
        v1: integer;
    begin
        if (arg0 <> xnoreg) and not(arg0 in knownregs) then begin
            return opts.unk_1C;
        end;

        if arg2 = nil then begin
            v1 := arg1;
        end else if (ARRAY_AT(memory, arg2^.unk30).unk_08 = seg_4) or
                    (ARRAY_AT(memory, arg2^.unk30).unk_08 = seg_3) or
                    (opts.unk_1D and ((arg2^.unk34 = 'C') or (arg2^.unk34 = 'E'))) then begin
            v1 := size_to_alignment[min(arg2^.unk10, 8)] + arg1;
        end else if (ARRAY_AT(memory, arg2^.unk30).unk_08 = seg_data) or
                    (ARRAY_AT(memory, arg2^.unk30).unk_08 = seg_sdata) then begin
            v1 := arg2^.unk10 + 16 + arg1;
        end else begin
            return opts.unk_1C;
        end;

        return Alignment(max(ord(opts.unk_1C), ord(addr_to_alignment[v1 mod 8])));
    end; 

    procedure func_00460194(arg0: asmcodes; arg1: registers; arg2: PUnkALpha; arg3: integer; arg4: registers; arg5: registers; arg6: boolean);
    var
        spD0: integer;
        spCC: integer;
        spCA: opcodes;
        spC9: registers;
        spC8: registers;
        spC7: RldType;

        procedure func_0045FD94(arg0: asmcodes; arg1: registers; arg2: PUnkALpha; arg3: RldType; arg4: integer; arg5: registers; arg6: registers; arg7: boolean);
        var
            spC8: integer;
            spC4: integer;
            spC3: registers;
            spC0: opcodes;
            v0: integer;

            procedure func_0045FCA0(arg0: integer);
            begin
                emitloadstore(spCA, arg1, spC8 + arg0, arg5);
                if arg2 <> nil then begin
                    _setrld(arg2, arg3, bbindex + proc_instr_base);
                end;
                emitloadstore(spC0, arg1, spC4 + arg0, arg5);
                if arg2 <> nil then begin
                    _setrld(arg2, arg3, bbindex + proc_instr_base);
                end;
            end;
        begin
            if arg0 in [zulw, zusw, zulwu] then begin
                v0 := 3;
            end else begin
                v0 := 7;
            end;
    
            if bigendian then begin
                spC4 := v0 + arg4;
                spC8 := arg4;
            end else begin
                spC4 := arg4;
                spC8 := v0 + arg4;
            end;
    
            if (arg0 = zulw) or (arg0 = zulwu) then begin
                spCA := op_zlwl;
                spC0 := op_zlwr;
            end else if arg0 = zusw then begin
                spCA := op_zswl;
                spC0 := op_zswr;
            end else if arg0 = zuld then begin
                spCA := op_zldl;
                spC0 := op_zldr;
            end else begin
                spCA := op_zsdl;
                spC0 := op_zsdr;
            end;

            if arg6 <> xnoreg then begin
                if arg7 and bigendian and not moxieflag then begin
                    spC3 := arg6;
                    arg6 := succ(arg6);
                end else begin
                    spC3 := succ(arg6);
                end;

                if arg0 <> zulw then begin
                    emitmvcoproc(op_zmfc1, arg1, arg6);
                end;
                func_0045FCA0(0);
                if arg0 = zulw then begin
                    emitmvcoproc(op_zmtc1, arg1, arg6);
                end;

                if arg7 then begin
                    if arg0 <> zulw then begin
                        emitmvcoproc(op_zmfc1, arg1, spC3);
                    end;
                    func_0045FCA0(4);
                    if arg0 = zulw then begin
                        emitmvcoproc(op_zmtc1, arg1, spC3);
                    end;
                end;
            end else begin
                func_0045FCA0(0);

                if arg0 = zulwu then begin
                    if arg7 then begin
                        p_assertion_failed("double = false\0", "parsera.p", 1360);
                    end;

                    emitshift(op_zdsll, arg1, arg1, 32);
                    emitshift(op_zdsrl, arg1, arg1, 32);
                end;

                if arg7 then begin
                    arg1 := succ(arg1);
                    func_0045FCA0(4);
                end;
            end;
        end;
    begin
        spD0 := arg3;

        if arg2 <> nil then begin
            if is_gp_relative(arg2, arg3, arg4, spC9) then begin
                if arg1 = gpreg then begin
                    basereg_error();
                end;

                if arg0 in [zulw, zusw, zuld, zusd, zulwu] then begin
                    func_0045FD94(arg0, arg1, arg2, RLD_TYPE_1, arg3, spC9, arg5, arg6);
                end else begin
                    if bigendian then begin
                        spCC := arg3 + 1;
                    end else begin
                        spCC := arg3;
                        spD0 := arg3 + 1;
                    end;

                    if not atflag then begin
                        macro_error();
                    end;

                    if arg0 in [zulh, zulhu] then begin
                        if arg0 = zulh then begin
                            spCA := op_zlb;
                        end else begin
                            spCA := op_zlbu;
                        end;

                        emitloadstore(spCA, arg1, spD0, spC9);
                        _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
                        emitloadstore(op_zlbu, xr1, spCC, spC9);
                        _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
                        emitshift(op_zsll, arg1, arg1, 8);
                        emitalu3(op_zor, arg1, arg1, xr1);
                    end else if arg0 = zush then begin
                        emitloadstore(op_zsb, arg1, spCC, spC9);
                        _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
                        if spC9 = xr1 then begin
                            spC8 := arg1;
                        end else begin
                            spC8 := xr1;
                        end;
                        emitshift(op_zsrl, spC8, arg1, 8);
                        emitloadstore(op_zsb, spC8, spD0, spC9);
                        _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
                        if spC9 = xr1 then begin
                            emitloadstore(op_zlbu, xr1, spCC, spC9);
                            _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
                            emitshift(op_zsll, arg1, arg1, 8);
                            emitalu3(op_zor, arg1, arg1, xr1);
                        end;
                    end else begin
                        p_assertion_failed("false\0", "parsera.p", 1424);
                    end;
                end;
            end else begin
                setup_tempreg(2, xr1, arg4, arg2, spD0, spC7, True, arg0);
                if arg0 in [zulw, zusw, zuld, zusd, zulwu] then begin
                    func_0045FD94(arg0, arg1, arg2, spC7, spD0, xr1, arg5, arg6);
                end else begin
                    if bigendian then begin
                        spCC := spD0 + 1;
                    end else begin
                        spCC := spD0;
                        spD0 := spD0 + 1;
                    end;

                    if arg0 in [zulh, zulhu] then begin
                        if arg0 = zulh then begin
                            spCA := op_zlb;
                        end else begin
                            spCA := op_zlbu;
                        end;

                        emitloadstore(spCA, arg1, spD0, xr1);
                        if arg2 <> nil then begin
                            _setrld(arg2, spC7, bbindex + proc_instr_base);
                        end;
                        emitloadstore(op_zlbu, xr1, spCC, xr1);
                        if arg2 <> nil then begin
                            _setrld(arg2, spC7, bbindex + proc_instr_base);
                        end;
                        emitshift(op_zsll, arg1, arg1, 8);
                        emitalu3(op_zor, arg1, arg1, xr1);
                    end else if arg0 = zush then begin
                        emitloadstore(op_zsb, arg1, spCC, xr1);
                        if arg2 <> nil then begin
                            _setrld(arg2, spC7, bbindex + proc_instr_base);
                        end;
                        emitshift(op_zsrl, arg1, arg1, 8);
                        emitloadstore(op_zsb, arg1, spD0, xr1);
                        if arg2 <> nil then begin
                            _setrld(arg2, spC7, bbindex + proc_instr_base);
                        end;
                        emitloadstore(op_zlbu, xr1, spCC, xr1);
                        if arg2 <> nil then begin
                            _setrld(arg2, spC7, bbindex + proc_instr_base);
                        end;
                        emitshift(op_zsll, arg1, arg1, 8);
                        emitalu3(op_zor, arg1, arg1, xr1);
                    end else begin
                        p_assertion_failed("false\0", "parsera.p", 1470);
                    end;
                end;
            end;
        end else begin
            if (arg3 < -16#8000) or (arg3 > 16#7FFC - 4 * integer(arg6 or (arg0 in [zuld, zusd]))) then begin
                if not atflag then begin
                    macro_error();
                end;
    
                emitalui(op_zlui, xr1, xr0, disp(True, arg3));
                if (arg4 <> xnoreg) and (arg4 <> xr0) then begin
                    emitalu3(op_zaddu, xr1, xr1, arg4);
                end;
                emitalui(op_zaddiu, xr1, xr1, disp(False, arg3));
    
                if arg0 in [zulw, zusw, zuld, zusd, zulwu] then begin
                    func_0045FD94(arg0, arg1, nil, RLD_TYPE_0, 0, xr1, arg5, arg6);
                end else begin
                    if bigendian then begin
                        spD0 := 0;
                        spCC := 1;
                    end else begin
                        spD0 := 1;
                        spCC := 0;
                    end;
    
                    if arg0 in [zulh, zulhu] then begin
                        if arg0 = zulh then begin
                            spCA := op_zlb;
                        end else begin
                            spCA := op_zlbu;
                        end;
    
                        emitloadstore(spCA, arg1, spD0, xr1);
                        emitloadstore(op_zlbu, xr1, spCC, xr1);
                        emitshift(op_zsll, arg1, arg1, 8);
                        emitalu3(op_zor, arg1, arg1, xr1);
                    end else if arg0 = zush then begin
                        emitloadstore(op_zsb, arg1, spCC, xr1);
                        emitshift(op_zsrl, arg1, arg1, 8);
                        emitloadstore(op_zsb, arg1, spD0, xr1);
                        emitloadstore(op_zlbu, xr1, spCC, xr1);
                        emitshift(op_zsll, arg1, arg1, 8);
                        emitalu3(op_zor, arg1, arg1, xr1);
                    end else begin
                        p_assertion_failed("false\0", "parsera.p", 1520);
                    end;
                end;
            end else begin
                if (arg4 = xnoreg) or (arg4 = xr0) then begin
                    arg4 := xr0;
                end;

                if arg0 in [zulw, zusw, zuld, zusd, zulwu] then begin
                    if arg1 = arg4 then begin
                        if not atflag then begin
                            macro_error();
                        end;
                        emitalu3(op_zaddu, xr1, arg4, xr0);
                        arg4 := xr1;
                    end;

                    func_0045FD94(arg0, arg1, nil, RLD_TYPE_0, arg3, arg4, arg5, arg6);
                end else begin
                    if bigendian then begin
                        spCC := arg3 + 1;
                    end else begin
                        spCC := arg3;
                        spD0 := arg3 + 1;
                    end;

                    if not atflag then begin
                        macro_error();
                    end;

                    if arg0 in [zulh, zulhu] then begin
                        if arg0 = zulh then begin
                            spCA := op_zlb;
                        end else begin
                            spCA := op_zlbu;
                        end;

                        emitloadstore(spCA, xr1, spD0, arg4);
                        emitloadstore(op_zlbu, arg1, spCC, arg4);
                        emitshift(op_zsll, xr1, xr1, 8);
                        emitalu3(op_zor, arg1, arg1, xr1);
                    end else if arg0 = zush then begin
                        emitloadstore(op_zsb, arg1, spCC, arg4);
                        emitshift(op_zsrl, xr1, arg1, 8);
                        emitloadstore(op_zsb, xr1, spD0, arg4);
                    end else begin
                        p_assertion_failed("false\0", "parsera.p", 1561);
                    end;
                end;
            end;
        end;
    end;

    procedure func_00461230(arg0: asmcodes; arg1: registers; arg2: PUnkALpha; arg3: integer; arg4: registers; arg5: integer);
    var
        spC3: registers;
    begin
        if (arg0 = fl_s) or (arg0 = fl_d) then begin
            arg0 := zulw;
        end else begin
            arg0 := zusw;
        end;

        if ((arg2 <> nil) and is_gp_relative(arg2, arg3, arg4, spC3) or
           (arg2 = nil) and (arg3 >= -16#8000) and (arg3 <= 16#7FFF)) then begin
            if arg4 = gpreg then begin
                p_assertion_failed("lbase <> GPReg\0", "parsera.p", 1592);
            end;

            if not atflag then begin
                macro_error();
            end;

            func_00460194(arg0, xr1, arg2, arg3, arg4, arg1, arg5 > 1);
        end else begin
            if picflag > 0 then begin
                PostError("internal error: genfpunaligned clobbers gp in pic or abicalls mode", emptystring, ErrorLevel_1);
            end;

            func_00460194(arg0, gpreg, arg2, arg3, arg4, arg1, arg5 > 1);
            if gp_symbol = nil then begin
                gp_symbol := enter_undef_sym(l_addr(gp_symbol_name));
            end;

            do_parseafra(zla, gpreg, gp_symbol, 0, xnoreg);
        end;
    end;

    function func_004615B8(arg0: Alignment; arg1: Alignment): boolean;
    begin
        return (arg0 >= opts.unk_1C) and (arg0 < arg1);
    end;

    procedure func_004615F0(arg0: Alignment; arg1: asmcodes);
    begin
        if func_004615B8(spD3, arg0) then begin
            func_00460194(arg1, spDF, spD4, spD8, spDE, xnoreg, False);
        end else begin
            do_parseafra(fasm, spDF, spD4, spD8, spDE);
        end;
    end;

    procedure func_004616A4(arg0: asmcodes;
                            arg1: registers;
                            arg2: PSymbol;
                            arg3: integer;
                            arg4: registers);
    var
        vvvvv: integer;
    begin
        if binasmfyle^.formextn = frcprel then begin
            case arg0 of
                zld,
                zsd:
                begin
                    if isa < ISA_MIPS3 then begin
                        enforce_destreg(arg1, 2);
                        if func_004615B8(spD3, ALIGNMENT_3) and (spD3 < ALIGNMENT_2) then begin
                            if arg0 = zld then begin
                                arg0 := zulw;
                            end else begin
                                arg0 := zusw;
                            end;
                            func_00460194(arg0, arg1, arg2, arg3, arg4, xnoreg, True);
                        end else begin
                            gendouble(arg0, arg1, arg2, arg3, arg4, True);
                        end;
                    end else begin
                        if arg0 = zld then begin
                            func_004615F0(ALIGNMENT_3, zuld);
                        end else begin
                            func_004615F0(ALIGNMENT_3, zusd);
                        end;
                    end;
                end;
                
                fl_s,
                fs_s:
                begin
                    if (spD3 = ALIGNMENT_1) or (spD3 = ALIGNMENT_0) then begin
                        PostError(" Cannot do floating-point load on unaligned data", emptystring, ErrorLevel_2);
                    end;

                    if func_004615B8(spD3, ALIGNMENT_2) then begin
                        func_00461230(arg0, arg1, arg2, arg3, arg4, 1);
                    end else begin
                        genfpmultiple(arg0, arg1, arg2, arg3, arg4, 1, isa >= ISA_MIPS2, True);
                    end;
                end;

                fl_d,
                fs_d:
                begin
                    if (spD3 = ALIGNMENT_1) or (spD3 = ALIGNMENT_0) then begin
                        PostError(" Cannot do floating-point load on unaligned data", emptystring, ErrorLevel_2);
                    end;

                    if isa < ISA_MIPS3 then begin
                        enforce_destreg(arg1, 2);
                    end;

                    if func_004615B8(spD3, ALIGNMENT_3) then begin
                        if (spD3 <= ALIGNMENT_1) then begin
                            func_00461230(arg0, arg1, arg2, arg3, arg4, 2);
                            return;
                        end else begin
                            spD2 := False;
                        end;
                    end else begin
                        spD2 := isa >= ISA_MIPS2;
                    end;
                    genfpmultiple(arg0, arg1, arg2, arg3, arg4, 2, spD2, True);
                end;

                fl_e,
                fs_e:
                begin
                    if isa >= ISA_MIPS3 then begin
                        enforce_destreg(arg1, 2);
                    end else begin
                        enforce_destreg(arg1, 4);
                    end;

                    if func_004615B8(spD3, ALIGNMENT_3) then begin
                        PostError("Cannot correct .e alignment", emptystring, ErrorLevel_2);
                    end;

                    genfpmultiple(arg0, arg1, arg2, arg3, arg4, 4, isa >= ISA_MIPS2, True);
                end;

                otherwise:
                begin
                    if (arg4 = xr29) and adjust_frame_by_ld and ((arg3 >= known_framesize) or (arg3 <= -known_framesize)) then begin
                        emitalui(op_zlui, xr1, xr0, 0);
                        request_multi_relocinst(bbindex + proc_instr_base);
                        ARRAY_GROW(multirelocinstr_list, nextmultirelocinstr);
                        ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_08 := bbindex + proc_instr_base;
                        ARRAY_AT(multirelocinstr_list, nextmultirelocinstr).unk_00 := sp_addu_index;
                        nextmultirelocinstr := nextmultirelocinstr + 1;

                        emitalu3(op_zaddu, xr1, xr1, arg4);
                        emitloadstore(asm2op[arg0], arg1, disp(False, arg3), xr1);
                        request_multi_relocinst(bbindex + proc_instr_base);
                        ARRAY_AT(multirelocinstr_list, nextmultirelocinstr - 1).unk_0C := bbindex + proc_instr_base;
                        ARRAY_AT(multirelocinstr_list, nextmultirelocinstr - 1).unk_04 := sp_addu_index + 1;
                    end else begin
                        emitloadstore(asm2op[arg0], arg1, disp(False, arg3), arg4);
                        _setrld(arg2, RLD_TYPE_9, bbindex + proc_instr_base);
                        ARRAY_AT(rld_list, cardinal(nextrld) - 1).unk08 := arg2;
                    end;
                end;
            end;
        end else begin
            if not(asm2op[arg0] <> op_macro) then begin
                p_assertion_failed("asm2op[fasm] <> macro\0", "parsera.p", 1738);
            end;

            if binasmfyle^.formextn = fralo then begin
                emitloadstore(asm2op[arg0], arg1, disp(False, arg3), arg4);
                if arg2 <> nil then begin
                    _setrld(arg2, RLD_TYPE_14, bbindex + proc_instr_base);
                    ARRAY_AT(rld_list, cardinal(nextrld) - 1).unk14 := arg3;
                    ARRAY_AT(rld_list, cardinal(nextrld) - 1).unk11 := arg4;
                end;
            end else if binasmfyle^.formextn = frgprel then begin
                emitloadstore(asm2op[arg0], arg1, arg3, arg4);
                _setrld(arg2, RLD_TYPE_1, bbindex + proc_instr_base);
            end else begin
                PostError("illegal formextn value", emptystring, ErrorLevel_1);
            end;
        end;
    end;
begin
    with binasmfyle^ do begin
        spD4 := nil;
        spDF := reg1;
        current_mem_tag := mem_tag;
        spD8 := immediate;
        
        if symno <> 0 then begin
            spD4 := stp(symno);
            spD4^.unk3D := true;
        end;
    end;
    
    with binasmfyle^ do begin
        spDE := reg2;
    
        if (fasm = zdla) and diag_flag then begin
            if not((spDE = xnoreg) or (spDE = xr0)) then begin
                p_assertion_failed("(lbase = xnoreg) or (lbase = xr0)\0", "parsera.p", 1771);
            end;
            emitalui(op_zlui, spDF, xr0, 0);
            _setrld(spD4, RLD_TYPE_4, bbindex + proc_instr_base);
            emitalui(op_zori, spDF, spDF, 0);
            _setrld(spD4, RLD_TYPE_5, bbindex + proc_instr_base);
            emitshift(op_zdsll, spDF, spDF, 16);
            emitalui(op_zori, spDF, spDF, disp(true, spD8));
            _setrld(spD4, RLD_TYPE_2, bbindex + proc_instr_base);
            emitshift(op_zdsll, spDF, spDF, 16);
            emitalui(op_zdaddiu, spDF, spDF, disp(false, spD8));
            _setrld(spD4, RLD_TYPE_3, bbindex + proc_instr_base);
            return;
        end;
        
        if formextn <> franone then begin
            spD3 := func_0045FB50(spDE, spD8, spD4);
            func_004616A4(fasm, spDF, spD4, spD8, spDE);
            return;
        end;

        if sixtyfour_bit and (spD4 <> nil) and not check_if_gp_relative(spD4, spD8) then begin
            if not atflag then begin
                macro_error();
            end;

            if spD8 < 0 then begin
                a0 := -1;
            end else begin
                a0 := 0;
            end;
            a2 := emit_dword_item(a0, spD8, spD4);

            if (fasm = zla) or (fasm = zdla) then begin
                if (spDE = xnoreg) or (spDE = xr0) then begin
                    do_parseafra(zld, spDF, a2, 0, xnoreg);
                end else begin
                    do_parseafra(zld, xr1, a2, 0, xnoreg);
                    emitalu3(op_zdaddu, spDF, xr1, spDE);
                end;
                return;
            end;

            
            do_parseafra(zld, xr1, a2, 0, xnoreg);
            spD4 := nil;
            if not((spDE = xnoreg) or (spDE = xr0)) then begin
                emitalu3(op_zdaddu, xr1, xr1, spDE);
            end;

            spD8 := 0;
            spDE := xr1;
        end;

        spD3 := func_0045FB50(spDE, spD8, spD4);

        case fasm of
            zlh:
            begin
                func_004615F0(ALIGNMENT_1, zulh);
                return;
            end;
            
            zlhu:
            begin
                func_004615F0(ALIGNMENT_1, zulhu);
                return;
            end;
            
            zlw:
            begin
                func_004615F0(ALIGNMENT_2, zulw);
                return;
            end;
            
            zsh:
            begin
                func_004615F0(ALIGNMENT_1, zush);
                return;
            end;
            
            zsw:
            begin
                func_004615F0(ALIGNMENT_2, zusw);
                return;
            end;

            zld,
            zsd:
            begin
                if isa < ISA_MIPS3 then begin
                    enforce_destreg(spDF, 2);

                    if func_004615B8(spD3, ALIGNMENT_3) and (spD3 <= ALIGNMENT_1) then begin
                        if fasm = zld then begin
                            fasm := zulw;
                        end else begin
                            fasm := zusw;
                        end;
                        func_00460194(fasm, spDF, spD4, spD8, spDE, xnoreg, True);
                    end else begin
                        gendouble(fasm, spDF, spD4, spD8, spDE, False);
                    end;
                end else begin
                    if fasm = zld then begin
                        func_004615F0(ALIGNMENT_3, zuld);
                    end else begin
                        func_004615F0(ALIGNMENT_3, zusd);
                    end;
                end;
                return;
            end;

            fl_s,
            fs_s:
            begin
                if (spD3 = ALIGNMENT_1) or (spD3 = ALIGNMENT_0) then begin
                    PostError(" Cannot do floating-point load on unaligned data", emptystring, ErrorLevel_2);
                end;

                if func_004615B8(spD3, ALIGNMENT_2) then begin
                    func_00461230(fasm, spDF, spD4, spD8, spDE, 1);
                end else begin
                    genfpmultiple(fasm, spDF, spD4, spD8, spDE, 1, isa >= ISA_MIPS2, FALSE);
                end;
                return;
            end;

            fl_d,
            fs_d:
            begin
                if (spD3 = ALIGNMENT_1) or (spD3 = ALIGNMENT_0) then begin
                    PostError(" Cannot do floating-point load on unaligned data", emptystring, ErrorLevel_2);
                end;

                if isa < ISA_MIPS3 then begin
                    enforce_destreg(spDF, 2);
                end;

                if func_004615B8(spD3, ALIGNMENT_3) then begin
                    if (spD3 < ALIGNMENT_2) then begin
                        func_00461230(fasm, spDF, spD4, spD8, spDE, 2);
                        return;
                    end else begin
                        spD2 := False;
                    end;
                end else begin
                    spD2 := isa >= ISA_MIPS2;
                end;
                genfpmultiple(fasm, spDF, spD4, spD8, spDE, 2, spD2, False);
                return;
            end;

            fl_e,
            fs_e:
            begin
                if isa >= ISA_MIPS3 then begin
                    enforce_destreg(spDF, 2);
                end else begin
                    enforce_destreg(spDF, 4);
                end;

                if func_004615B8(spD3, ALIGNMENT_3) then begin
                    PostError("Cannot correct .e alignment", emptystring, ErrorLevel_2);
                end;

                genfpmultiple(fasm, spDF, spD4, spD8, spDE, 4, isa >= ISA_MIPS2, False);
                return;
            end;

            zulw,
            zulh,
            zulhu,
            zusw,
            zush,
            zulwu,
            zuld,
            zusd:
            begin
                func_00460194(fasm, spDF, spD4, spD8, spDE, xnoreg, False);
                return;
            end;
            
            zdla:
            begin
                parse_dli_dla();
                return;
            end;

            zldc1,
            zldc2,
            zsdc1,
            zsdc2:
            begin
                if isa < ISA_MIPS3 then begin
                    enforce_destreg(spDF, 2);
                end;

                if isa < ISA_MIPS2 then begin
                    PostError("coproc doubles not implemented", emptystring, ErrorLevel_1);
                    return;
                end;
            end;

            otherwise: ;
            
        end;
    end;
    
    do_parseafra(fasm, spDF, spD4, spD8, spDE);
end;

{ 
    Not matching function
    only stack diff
    url: https://decomp.me/scratch/WfVCq
    score: 24 (99.96%)
}

procedure parseafri_fp(fasm: asmcodes);
var
    sp104: GString;
    unused: integer;
    spFC: PSymbol;
    spEC: binasm;
    spD8: UnkFPStruct;
    spD4: integer;
    spD3: UnknownEnum;
    spCC: integer;
    spCB: boolean;
    spCA: boolean;
    spC4: boolean;
    v0: integer;
    
    procedure func_0046303C(fasm: asmcodes; arg1: UnkFPStruct; var arg2: binasm);
    begin
        if (arg1.unk_00[1] = 0) and (arg1.unk_00[2] = 0) then begin
            if (fasm = fli_d) and (isa >= ISA_MIPS2) then begin
                if dwopcode then begin
                    emitmvcoproc(op_zdmtc1, xr0, arg2.reg1);
                end else begin
                    genfpmultiple(fl_d, arg2.reg1, d_pool_symbol, emit_pool_const(arg1, spCB, spCA, seg_6), xr0, 2, isa >= ISA_MIPS2, False);
                end;
            end else begin
                emitmvcoproc(op_zmtc1, xr0, arg2.reg1);
                if fasm = fli_d then begin
                    emitmvcoproc(op_zmtc1, xr0, succ(arg2.reg1));
                end;
            end;
        end else begin
            if fasm = fli_s then begin
                genfpmultiple(fl_s, arg2.reg1, s_pool_symbol, emit_pool_const(arg1, spCB, spCA, seg_5), xr0, 1, isa >= ISA_MIPS2, False);
            end else begin
                genfpmultiple(fl_d, arg2.reg1, d_pool_symbol, emit_pool_const(arg1, spCB, spCA, seg_6), xr0, 2, isa >= ISA_MIPS2, False);
            end;
        end;
    end;
begin

    spD8.unk_00[1] := 0;
    spD8.unk_00[2] := 0;

    if fasm = fli_e then begin
        PostError("li.e not yet supported", emptystring, ErrorLevel_1);
        fasm := fli_d;
    end;

    spEC := binasmfyle^;
    sp104.f := get_fp_string(spEC.immediate);

    if fasm = fli_s then begin
        spD3 := UNK_ENUM_13;
    end else begin
        spD3 := UNK_ENUM_11;
    end;

    string_to_fpoverlay(sp104, spD3, spD8, spCB, spCA);

    spC4 := (spEC.reg1 >= xfr0) and (spEC.reg1 <= xfr30);

    if float_li_flag and spC4 then begin
        if fasm = fli_s then begin
            v0 := short_s(spD8.unk_00[1]);
        end else begin
            v0 := short_d(spD8.unk_00[1], spD8.unk_00[2]);
        end;
        if v0 <> 1024 then begin
            emitfli(asm2op[fasm], spEC.reg1, v0);
            return;
        end;
    end;

    if fp_pool_flag and spC4 and (gprelsize >= 4 + 4 * integer(fasm = fli_d)) then begin
        func_0046303C(fasm, spD8, spEC);
        return;
    end;

    if generate_as_immediate(fasm, spEC.reg1, spD8.unk_00[1], spD8.unk_00[2]) then begin
        return;
    end;

    if fasm = fli_s then begin
        fasm := fl_s;
        spD4 := 1;
        spD3 := UNK_ENUM_13;
    end else begin
        fasm := fl_d;
        spD4 := 2;
        spD3 := UNK_ENUM_11;
        if isa < ISA_MIPS3 then begin
            spD4 := 2;
            spD3 := UNK_ENUM_11;
            enforce_destreg(spEC.reg1, 2);
        end;
    end;

    spFC := emit_fp_const(spD8, spCB, spCA, spD3, spCC);

    if spC4 then begin
        genfpmultiple(fasm, spEC.reg1, spFC, 0, xr0, spD4, isa >= ISA_MIPS2, False);
    end else begin
        if not(fasm = fl_d) then begin
            p_assertion_failed("fasm = fl_d\0", "parsera.p", 2144);
        end;

        if isa < ISA_MIPS3 then begin
            gendouble(zld, spEC.reg1, spFC, 0, xnoreg, false);
        end else begin
            do_parseafra(zld, spEC.reg1, spFC, 0, xnoreg);
        end;
    end;

    dispose(sp104.z);
end;