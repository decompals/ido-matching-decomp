#include "cmplrs/stinfc.h"
#include "common.h"
#include "report.h"
#include "tree.h"
#include "tree_utils.h"
#include "emit.h"
#include "ibuffer.h"
#include "reg_mgr.h"
#include "symbol.h"
#include "val_util.h"
#include "ugen_regdef.h"

procedure home_parameters(arg0: cardinal; arg1: integer); forward;
procedure gen_reg_save_restore(arg0: integer; arg1: integer; arg2: integer; arg3: integer; arg4: boolean; arg5: integer; arg6: integer); forward;
procedure gen_reg_save(arg0: integer; arg1: integer; arg2: integer; arg3: integer); forward;
procedure demit_mask(arg0: itype; arg1: integer; arg2: integer); forward;
procedure demit_frame(arg0: integer; arg1: registers; arg2: registers); forward;
procedure emit_file(arg0: integer; arg1: boolean); forward;
procedure emit_optimize_level(arg0: integer); forward;

var
    ascii_out: boolean;
    basicint: u8;
    excpt: boolean;
    frame_pointer: registers;
    framesz_relocatable: boolean;
    home_vararg_reg: boolean;
    i_ptrs_for_gp_offset: array[1..20] of integer;
    init_dynmem: boolean;
    isa: mips_isa;
    max_stack: integer;
    mscoff: boolean;
    n_fp_parm_regs: integer;
    n_parm_regs: integer;
    n_saved_fp_regs: integer;
    n_saved_regs: integer;
    num_i_ptr_indexes: integer;
    olevel: u8;
    pic_level: integer;
    reversed_stack: boolean;
    saved_regs: set of registers;
    stack_limit_bn: integer;
    use_cpalias: boolean;
    uses_gp: boolean;

procedure gen_entry_exit(
    arg0: integer; { symbol number for function? }
    arg1: boolean; { is_global? }
    arg2: integer;
    arg3: cardinal; { stack size? }
    arg4: integer;
    arg5: boolean;
    arg6: integer;
    arg7: integer;
    arg8: boolean;
    arg9: boolean;
    argA: boolean;
    argB: integer;
    argC: integer;
    argD: boolean;
    argE: integer;
    arg10: Valu;
    arg12: integer;
    arg13: integer;
    arg14: integer);
var
    pad1: integer;
    pad2: u8;
    spC2: registers;
    spC1: registers;
    spBC: integer;
    spBB: registers;
begin
    if arg10.Ival <> 0 then begin
        demit_itext(arg10);
    end else begin
        demit_dir0(itext, 0);
    end;
    demit_dir1(ialign, 0, 2);
    if ascii_out then begin
        emit_file(arg6, true);
    end;
    if arg1 then begin
        demit_dir0(iglobal, arg0);
    end;
    demit_dir2(iloc, 0, arg6, arg7);
    demit_dir1(ient, arg0, arg2);
    output_entry_point(arg0);
    emit_optimize_level(olevel);
    if (pic_level = 1) or ((pic_level = 2) and (not arg5 or (u8(olevel) < 2) or uses_gp or (i_ptr >= 1000))) then begin
        emit_cpload(gpr_t9, 0, arg0, false);
    end;
    if arg3 = 0 then begin
        argE := 0;
    end;
    if init_dynmem and (arg3 <> 0) then begin
        spC2 := get_free_reg(0, 1);
        spC1 := get_free_reg(0, 1);
        demit_ri(zli, spC2, -16#5A5A6, franone);
        demit_rr(zmove, spC1, gpr_sp);
    end;
    if arg3 <> 0 then begin
        if max_stack <> -1 then begin
            if arg3 >= max_stack then begin
                get_reg(gpr_t8, 0, 1);
                demit_rr(zmove, gpr_t9, gpr_ra);
                demit_ri(zli, gpr_t8, arg3, franone);
                demit_regmask(ilivereg, 16#C0, 0);
                demit_a(zjal, stack_limit_bn, 0);
                demit_rrr(zsubu, gpr_sp, gpr_sp, gpr_t8);
                free_reg(gpr_t8);
                demit_rr(zmove, gpr_ra, gpr_t9);
            end else begin
                demit_ri(zsubu, gpr_sp, arg3, franone);
                demit_rob_(zsw, gpr_zero, 0, gpr_sp, franone);
            end;
        end else if reversed_stack then begin
            demit_ri(zaddu, gpr_sp, arg3, franone);
        end else begin
            demit_ri(zsubu, gpr_sp, arg3, franone);
        end;
    end;
    spBB := gpr_s7;
    if argA then begin
        if stack_limit_bn = 0 then begin
            report_error(Internal, 193, "entry_exit.p", "stack limit block number not found");
        end else begin
            spBB := gpr_t0;
            demit_ra(zlw, gpr_t0, stack_limit_bn, 0);
        end;
    end;
    if (arg3 <> 0) and arg9 then begin
        if isa = ISA_MIPS2 then begin
            if reversed_stack then begin
                demit_rri(ztltu, spBB, gpr_sp, 9);
            end else begin
                demit_rri(ztltu, gpr_sp, spBB, 9);
            end;
        end else begin
            spBC := gen_label_id();
            if reversed_stack then begin
                demit_rrll(zbleu, gpr_sp, spBB, spBC);
            end else begin
                demit_rrll(zbgeu, gpr_sp, spBB, spBC);
            end;
            demit_i(zbreak, 9);
            ddefine_label(spBC);
        end;
    end;
    if init_dynmem and (arg3 <> 0) then begin
        spBC := gen_label_id();
        ddefine_label(spBC);
        if reversed_stack then begin
            demit_rob_(zsw, spC2, 0, spC1, franone);
            demit_rob_(zsw, spC2, 4, spC1, franone);
            demit_ri(zaddu, spC1, 8, franone);
        end else begin
            demit_ri(zsubu, spC1, 8, franone);
            demit_rob_(zsw, spC2, 0, spC1, franone);
            demit_rob_(zsw, spC2, 4, spC1, franone);
        end;
        demit_rrll(zbne, spC1, gpr_sp, spBC);
        free_reg(spC2);
        free_reg(spC1);
    end;
    gen_reg_save_restore(arg3, arg4, argC, argE, arg8, arg13, arg14);
    if argA then begin
        demit_rr(zmove, gpr_s7, spBB);
    end;
    if (arg3 <> 0) and not arg8 then begin
        if excpt then begin
            define_label(gen_label_id());
        end;
        if reversed_stack then begin
            emit_ri_(zsubu, gpr_sp, arg3, franone);
        end else begin
            emit_ri_(zaddu, gpr_sp, arg3, franone);
        end;
    end;
    if arg12 = -1 then begin
        emit_r(zj, gpr_ra);
    end;
    demit_frame(arg3, frame_pointer, gpr_ra);
    if framesz_relocatable then begin
        if reversed_stack then begin
            demit_ri(zaddu, gpr_sp, argB, frcprel);
        end else begin
            demit_ri(zsubu, gpr_sp, argB, frcprel);
        end;
    end;
    if excpt then begin
        if argD then begin
            demit_dir1(iprologue, 0, 1);
        end else begin
            demit_dir1(iprologue, 0, 0);
        end;
    end;
end;

procedure gen_entry(arg0: integer; arg1: integer; arg2: integer; arg3: integer; arg4: integer; arg5: integer);
var
    sp2C: integer;
    sp2B: registers;
    sp2A: registers;
    temp_v0: integer;
begin
    emit_dir0(iglobal, arg0);
    emit_dir1(iaent, arg0, arg1);
    emit_dir0(ilabel, arg0);
    if pic_level > 0 then begin
        emit_cpload(gpr_t9, 0, arg0, true);
    end;
    if arg2 = 0 then begin
        arg5 := 0;
    end;
    if init_dynmem and (arg2 <> 0) then begin
        sp2B := get_free_reg(0, 1);
        sp2A := get_free_reg(0, 1);
        emit_ri_(zli, sp2B, -16#5A5A6, franone);
        emit_rr(zmove, sp2A, gpr_sp);
    end;
    if arg2 <> 0 then begin
        if reversed_stack then begin
            if frame_pointer <> gpr_sp then begin
                demit_rr(zmove, frame_pointer, gpr_sp);
            end;
            emit_ri_(zaddu, gpr_sp, arg2, franone);
        end else begin
            emit_ri_(zsubu, gpr_sp, arg2, franone);
        end;
    end;
    if init_dynmem and (arg2 <> 0) then begin
        sp2C := gen_label_id();
        define_label(sp2C);
        if reversed_stack then begin
            emit_rob(zsw, sp2B, 0, sp2A, 0);
            emit_rob(zsw, sp2B, 4, sp2A, 0);
            emit_ri_(zaddu, sp2A, 8, franone);
        end else begin
            emit_ri_(zsubu, sp2A, 8, franone);
            emit_rob(zsw, sp2B, 0, sp2A, 0);
            emit_rob(zsw, sp2B, 4, sp2A, 0);
        end;
        emit_rrll(zbne, sp2A, gpr_sp, sp2C);
        free_reg(sp2B);
        free_reg(sp2A);
    end;
    gen_reg_save(arg2, arg3, arg5, arg4);
    if home_vararg_reg then begin
        emit_rob(zsd, gpr_a0, arg2, gpr_sp, 0);
        emit_rob(zsd, gpr_a2, arg2 + 8, gpr_sp, 0);
    end;
end;

procedure clear_saved_regs();
begin
    saved_regs := [];
end;

function is_empty_saved_regs(): boolean;
begin
    return saved_regs = [];
end;

procedure home_parameters{(arg0: cardinal; arg1: integer)};
var
    var_s0: integer;
    var_s4: integer;
    var_s2: registers;
    var_s3: asmcodes;
    var_v1: asmcodes;
    var_s0_2: integer;
begin
    var_s2 := gpr_a0;
    var_s4 := 0;
    while var_s4 <> n_parm_regs do begin
        if basicint = 0 then begin
            if (var_s2 in saved_regs) or home_vararg_reg then begin
                if reversed_stack then begin
                    demit_rob_(zsw, var_s2, -(arg0 + var_s4 * 4) - 4, gpr_sp, franone);
                end else begin
                    demit_rob_(zsw, var_s2, arg0 + var_s4 * 4, gpr_sp, franone);
                end;
            end;
        end else begin
            if (var_s2 in saved_regs) or home_vararg_reg then begin
                if reversed_stack then begin
                    demit_rob_(zsd, var_s2, -(arg0 + var_s4 * 8) - 8, gpr_sp, franone);
                end else begin
                    demit_rob_(zsd, var_s2, arg0 + var_s4 * 4, gpr_sp, franone);
                end;
            end;
        end;
        var_s4 := var_s4 + 1;
        var_s2 := succ(var_s2);
    end;
    var_s2 := xfr12;
    var_s0 := 0;
    var_v1 := znop;
    var_s4 := 0;
    while var_s4 <> n_fp_parm_regs do begin
        var_s3 := fs_s;
        if var_s2 in saved_regs then begin
            if reversed_stack then begin
                demit_rob_(fs_s, var_s2, -(arg0 + var_s0) - 4, gpr_sp, franone);
                if succ(var_s2) in saved_regs then begin
                    demit_rob_(fs_s, succ(var_s2), -(arg0 + var_s0) - 8, gpr_sp, franone);
                    var_s0 := var_s0 + 4;
                end;
            end else begin
                if succ(var_s2) in saved_regs then begin
                    var_s3 := fs_d;
                end;
                if (var_s3 = fs_d) and (var_v1 = fs_s) then begin
                    var_s0 := ((var_s0 + 7) div 8) * 8;
                end;
                demit_rob_(var_s3, var_s2, arg0 + var_s0, gpr_sp, franone);
            end;
        end;
        var_s4 := var_s4 + 1;
        var_s2 := succ(succ(var_s2));
        if var_s3 = fs_d then begin
            var_s0 := var_s0 + 8;
        end else begin
            var_s0 := var_s0 + 4;
        end;
        var_v1 := var_s3;
    end;
    if arg1 <> -1 then begin
        var_s0_2 := rshift(cardinal(arg1 & 16#FFFF0000), 16);
        if var_s0_2 <> 0 then begin
            if (arg1 & integer(16#FFFF)) = 0 then begin
                if reversed_stack then begin
                    demit_rob_(fs_s, xfr12, -(arg0 - var_s0_2) - 4, gpr_sp, franone);
                    demit_rob_(fs_s, xfr13, -(arg0 - var_s0_2) - 8, gpr_sp, franone);
                end else begin
                    demit_rob_(fs_d, xfr12, arg0 - var_s0_2, gpr_sp, franone);
                end;
            end;
            var_s0_2 := var_s0_2 + 8;
            if reversed_stack then begin
                demit_rob_(fs_s, xfr14, -(arg0 - var_s0_2) - 4, gpr_sp, franone);
                demit_rob_(fs_s, xfr15, -(arg0 - var_s0_2) - 8, gpr_sp, franone);
            end else begin
                demit_rob_(fs_d, xfr14, arg0 - var_s0_2, gpr_sp, franone);
            end;
        end;
    end;
end;

procedure gen_reg_save_restore{(
    arg0: integer;
    arg1: integer;
    arg2: integer;
    arg3: integer;
    arg4: boolean;
    arg5: integer;
    arg6: integer)};
var
    var_s1: integer;
    var_s0: registers;
    temp_v0: integer;
    sp48: integer;
    sp44: integer;
    sp40: integer;
    sp3C: integer;
    sp3B: boolean;
    sp3A: boolean;
    i: cardinal;
begin
    sp48 := 0;
    if reversed_stack then begin
        temp_v0 := arg1 + arg2 + arg3;
        var_s1 := arg0 - temp_v0;
        sp40 := temp_v0 - 4;
    end else begin
        temp_v0 := arg1 + arg2;
        var_s1 := arg0 - temp_v0;
        sp40 := -4 - temp_v0;
    end;
    sp44 := 0;
    if arg6 <> -1 then begin
        sp48 := lshift(1, ord(gpr_ra));
        sp40 := arg6;
        if basicint = 0 then begin
            demit_rob_(zsw, gpr_ra, arg0 + arg6, gpr_sp, franone);
        end else begin
            demit_rob_(zsd, gpr_ra, arg0 + arg6, gpr_sp, franone);
        end;
    end else if gpr_ra in saved_regs then begin
        sp48 := lshift(1, ord(gpr_ra));
        if reversed_stack then begin
            if basicint = 0 then begin
                var_s1 := var_s1 + 4;
                demit_rob_(zsw, gpr_ra, -var_s1, gpr_sp, franone);
            end else begin
                var_s1 := var_s1 + 8;
                demit_rob_(zsd, gpr_ra, -var_s1, gpr_sp, franone);
            end;
        end else begin
            if basicint = 0 then begin
                var_s1 := var_s1 - 4;
                demit_rob_(zsw, gpr_ra, var_s1, gpr_sp, franone);
            end else begin
                var_s1 := var_s1 - 8;
                demit_rob_(zsd, gpr_ra, var_s1, gpr_sp, franone);
            end;
        end;
    end;
    if gpr_s8 in saved_regs then begin
        if reversed_stack then begin
            if basicint = 0 then begin
                var_s1 := var_s1 + 4;
                demit_rob_(zsw, gpr_s8, -var_s1, gpr_sp, franone);
            end else begin
                var_s1 := var_s1 + 8;
                demit_rob_(zsd, gpr_s8, -var_s1, gpr_sp, franone);
            end;
        end else begin
            if basicint = 0 then begin
                var_s1 := var_s1 - 4;
                demit_rob_(zsw, gpr_s8, var_s1, gpr_sp, franone);
            end else begin
                var_s1 := var_s1 - 8;
                demit_rob_(zsd, gpr_s8, var_s1, gpr_sp, franone);
            end;
        end;
        sp48 := bitor(sp48, lshift(1, ord(gpr_s8)));
    end;
    if pic_level > 0 then begin
        if gpr_gp in saved_regs then begin
            if reversed_stack then begin
                var_s1 := var_s1 + 4;
                demit_dir0(icprestore, -var_s1);
                while num_i_ptr_indexes <> 0 do begin
                    ibuffer^[i_ptrs_for_gp_offset[num_i_ptr_indexes]].immediate := -var_s1;
                    num_i_ptr_indexes := num_i_ptr_indexes - 1;
                end;
            end else begin
                var_s1 := var_s1 - 4;
                demit_dir0(icprestore, var_s1);
                while num_i_ptr_indexes <> 0 do begin
                    ibuffer^[i_ptrs_for_gp_offset[num_i_ptr_indexes]].immediate := var_s1;
                    num_i_ptr_indexes := num_i_ptr_indexes - 1;
                end;
            end;
            sp48 := bitor(sp48, lshift(1, ord(gpr_gp)));
        end else if use_cpalias then begin
            demit_cpalias(gpr_s8);
        end;
    end;
    home_parameters(arg0, arg5);
    i := 0;
    var_s0 := registers(ord(gpr_s0) + n_saved_regs - 1);
    while i <> n_saved_regs do begin
        if var_s0 in saved_regs then begin
            sp48 := bitor(sp48, lshift(1, ord(var_s0)));
            if reversed_stack then begin
                if basicint = 0 then begin
                    var_s1 := var_s1 + 4;
                    demit_rob_(zsw, var_s0, -var_s1, gpr_sp, franone);
                end else begin
                    var_s1 := var_s1 + 8;
                    demit_rob_(zsd, var_s0, -var_s1, gpr_sp, franone);
                end;
            end else begin
                if basicint = 0 then begin
                    var_s1 := var_s1 - 4;
                    demit_rob_(zsw, var_s0, var_s1, gpr_sp, franone);
                end else begin
                    var_s1 := var_s1 - 8;
                    demit_rob_(zsd, var_s0, var_s1, gpr_sp, franone);
                end;
            end;
        end;
        i := i + 1;
        var_s0 := pred(var_s0);
    end;
    i := 0;
    var_s0 := registers(ord(xfr20) + (n_saved_fp_regs - i - 1) * 2);
    sp3B := true;
    sp3A := false;
    if ((var_s1 div 4) & 1) <> 0 then begin
        var_s1 := var_s1 - 4;
        sp3A := true;
    end;
    while i <> n_saved_fp_regs do begin
        if var_s0 in saved_regs then begin
            sp44 := bitor(sp44, lshift(3, ord(var_s0)));
            if reversed_stack then begin
                var_s1 := var_s1 + 8;
                demit_rob_(fs_d, var_s0, -var_s1, gpr_sp, franone);
                if sp3B then begin
                    sp3C := arg0 - var_s1;
                    sp3B := false;
                end;
            end else begin
                var_s1 := var_s1 - 8;
                demit_rob_(fs_d, var_s0, var_s1, gpr_sp, franone);
                if sp3B then begin
                    sp3C := var_s1 - arg0;
                    sp3B := false;
                end;
            end;
        end;
        i := i + 1;
        var_s0 := registers(ord(var_s0) - 2);
    end;
    if frame_pointer <> gpr_sp then begin
        if not reversed_stack then begin
            demit_rr(zmove, frame_pointer, gpr_sp);
        end;
        if not arg4 then begin
            emit_rr(zmove, gpr_sp, frame_pointer);
        end;
    end;
    i := 0;
    var_s0 := registers(ord(xfr20) + i * 2);
    while i <> n_saved_fp_regs do begin
        if var_s0 in saved_regs then begin
            if reversed_stack then begin
                emit_rob(fl_d, var_s0, -var_s1, frame_pointer, 0);
                var_s1 := var_s1 - 8;
            end else begin
                emit_rob(fl_d, var_s0, var_s1, frame_pointer, 0);
                var_s1 := var_s1 + 8;
            end;
        end;
        i := i + 1;
        var_s0 := registers(ord(var_s0) + 2);
    end;
    if sp3A then begin
        var_s1 := var_s1 + 4;
    end;
    i := 0;
    var_s0 := gpr_s0;
    while i <> n_saved_regs do begin
        if basicint = 0 then begin
            if var_s0 in saved_regs then begin
                if reversed_stack then begin
                    emit_rob(zlw, var_s0, -var_s1, frame_pointer, 0);
                    var_s1 := var_s1 - 4;
                end else begin
                    emit_rob(zlw, var_s0, var_s1, frame_pointer, 0);
                    var_s1 := var_s1 + 4;
                end;
            end;
        end else begin
            if var_s0 in saved_regs then begin
                if reversed_stack then begin
                    emit_rob(zld, var_s0, -var_s1, frame_pointer, 0);
                    var_s1 := var_s1 - 8;
                end else begin
                    emit_rob(zld, var_s0, var_s1, frame_pointer, 0);
                    var_s1 := var_s1 + 8;
                end;
            end;
        end;
        i := i + 1;
        var_s0 := succ(var_s0);
    end;
    if (pic_level > 0) and (gpr_gp in saved_regs) then begin
        if reversed_stack then begin
            var_s1 := var_s1 - 4;
        end else begin
            var_s1 := var_s1 + 4;
        end;
    end;
    if arg6 <> -1 then begin
        sp48 := bitor(sp48, lshift(1, ord(gpr_ra)));
        if basicint = 0 then begin
            emit_rob(zlw, gpr_ra, arg0 + arg6, gpr_sp, 0);
        end else begin
            emit_rob(zld, gpr_ra, arg0 + arg6, gpr_sp, 0);
        end;
        if gpr_s8 in saved_regs then begin
            if reversed_stack then begin
                if basicint = 0 then begin
                    emit_rob(zlw, gpr_s8, -var_s1, frame_pointer, 0);
                end else begin
                    emit_rob(zld, gpr_s8, -var_s1, frame_pointer, 0);
                end;
            end else begin
                if basicint = 0 then begin
                    emit_rob(zlw, gpr_s8, var_s1, frame_pointer, 0);
                end else begin
                    emit_rob(zld, gpr_s8, var_s1, frame_pointer, 0);
                end;
            end;
        end;
    end else if reversed_stack then begin
        if gpr_ra in saved_regs then begin
            if gpr_s8 in saved_regs then begin
                if basicint = 0 then begin
                    emit_rob(zlw, gpr_ra, -var_s1 + 4, frame_pointer, 0);
                    emit_rob(zlw, gpr_s8, -var_s1, frame_pointer, 0);
                end else begin
                    emit_rob(zld, gpr_ra, -var_s1 + 8, frame_pointer, 0);
                    emit_rob(zld, gpr_s8, -var_s1, frame_pointer, 0);
                end;
            end else begin
                if basicint = 0 then begin
                    emit_rob(zlw, gpr_ra, -var_s1, frame_pointer, 0);
                end else begin
                    emit_rob(zld, gpr_ra, -var_s1, frame_pointer, 0);
                end;
            end;
        end else if gpr_s8 in saved_regs then begin
            if basicint = 0 then begin
                emit_rob(zlw, gpr_s8, -var_s1, frame_pointer, 0);
            end else begin
                emit_rob(zld, gpr_s8, -var_s1, frame_pointer, 0);
            end;
        end;
    end else begin
        if gpr_ra in saved_regs then begin
            if gpr_s8 in saved_regs then begin
                if basicint = 0 then begin
                    emit_rob(zlw, gpr_ra, var_s1 + 4, frame_pointer, 0);
                    emit_rob(zlw, gpr_s8, var_s1, frame_pointer, 0);
                end else begin
                    emit_rob(zld, gpr_ra, var_s1 + 8, frame_pointer, 0);
                    emit_rob(zld, gpr_s8, var_s1, frame_pointer, 0);
                end;
            end else begin
                if basicint = 0 then begin
                    emit_rob(zlw, gpr_ra, var_s1, frame_pointer, 0);
                end else begin
                    emit_rob(zld, gpr_ra, var_s1, frame_pointer, 0);
                end;
            end;
        end else if gpr_s8 in saved_regs then begin
            if basicint = 0 then begin
                emit_rob(zlw, gpr_s8, var_s1, frame_pointer, 0);
            end else begin
                emit_rob(zld, gpr_s8, var_s1, frame_pointer, 0);
            end;
        end;
    end;
    demit_mask(imask, sp48, sp40);
    demit_mask(ifmask, sp44, sp3C);
end;

procedure gen_reg_save{(arg0: integer; arg1: integer; arg2: integer; arg3: integer)};
var
    var_s0: registers;
    var_s1: integer;
    i: integer;
begin
    if reversed_stack then begin
        var_s1 := ((arg0 - arg1) - arg3) - arg2;
    end else begin
        var_s1 := (arg0 - arg1) - arg3;
    end;
    if gpr_ra in saved_regs then begin
        if reversed_stack then begin
            if basicint = 0 then begin
                var_s1 := var_s1 + 4;
                emit_rob(zsw, gpr_ra, -var_s1, gpr_sp, 0);
            end else begin
                var_s1 := var_s1 + 8;
                emit_rob(zsd, gpr_ra, -var_s1, gpr_sp, 0);
            end;
        end else begin
            if basicint = 0 then begin
                var_s1 := var_s1 - 4;
                emit_rob(zsw, gpr_ra, var_s1, gpr_sp, 0);
            end else begin
                var_s1 := var_s1 - 8;
                emit_rob(zsd, gpr_ra, var_s1, gpr_sp, 0);
            end;
        end;
    end;
    if gpr_s8 in saved_regs then begin
        if reversed_stack then begin
            if basicint = 0 then begin
                var_s1 := var_s1 + 4;
                emit_rob(zsw, gpr_s8, -var_s1, gpr_sp, 0);
            end else begin
                var_s1 := var_s1 + 8;
                emit_rob(zsd, gpr_s8, -var_s1, gpr_sp, 0);
            end;
        end else begin
            if basicint = 0 then begin
                var_s1 := var_s1 - 4;
                emit_rob(zsw, gpr_s8, var_s1, gpr_sp, 0);
            end else begin
                var_s1 := var_s1 - 8;
                emit_rob(zsd, gpr_s8, var_s1, gpr_sp, 0);
            end;
        end;
    end;
    if (pic_level > 0) and (gpr_gp in saved_regs) then begin
        if reversed_stack then begin
            var_s1 := var_s1 + 4;
            emit_dir0(icprestore, -var_s1);
            while num_i_ptr_indexes <> 0 do begin
                ibuffer^[i_ptrs_for_gp_offset[num_i_ptr_indexes]].immediate := -var_s1;
                num_i_ptr_indexes := num_i_ptr_indexes - 1;
            end;
        end else begin
            var_s1 := var_s1 - 4;
            emit_dir0(icprestore, var_s1);
            while num_i_ptr_indexes <> 0 do begin
                ibuffer^[i_ptrs_for_gp_offset[num_i_ptr_indexes]].immediate := var_s1;
                num_i_ptr_indexes := num_i_ptr_indexes - 1;
            end;
        end;
    end else if use_cpalias then begin
        emit_cpalias(gpr_s8);
    end;
    i := 0;
    var_s0 := registers(ord(gpr_s0) + n_saved_regs - 1);
    while i <> n_saved_regs do begin
        if var_s0 in saved_regs then begin
            if reversed_stack then begin
                if basicint = 0 then begin
                    var_s1 := var_s1 + 4;
                    emit_rob(zsw, var_s0, -var_s1, gpr_sp, 0);
                end else begin
                    var_s1 := var_s1 + 8;
                    emit_rob(zsd, var_s0, -var_s1, gpr_sp, 0);
                end;
            end else begin
                if basicint = 0 then begin
                    var_s1 := var_s1 - 4;
                    emit_rob(zsw, var_s0, var_s1, gpr_sp, 0);
                end else begin
                    var_s1 := var_s1 - 8;
                    emit_rob(zsd, var_s0, var_s1, gpr_sp, 0);
                end;
            end;
        end;
        i := i + 1;
        var_s0 := pred(var_s0);
    end;
    i := 0;
    var_s0 := registers(ord(xfr20) + (n_saved_fp_regs - i - 1) * 2);
    if ((var_s1 div 4) & 1) <> 0 then begin
        var_s1 := var_s1 - 4;
    end;
    while i <> n_saved_fp_regs do begin
        if var_s0 in saved_regs then begin
            if reversed_stack then begin
                var_s1 := var_s1 + 8;
                emit_rob(fs_d, var_s0, -var_s1, gpr_sp, 0);
            end else begin
                var_s1 := var_s1 - 8;
                emit_rob(fs_d, var_s0, var_s1, gpr_sp, 0);
            end;
        end;
        i := i + 1;
        var_s0 := registers(ord(var_s0) - 2);
    end;
    if frame_pointer <> gpr_sp then begin
        emit_rr(zmove, frame_pointer, gpr_sp);
    end;
end;

procedure demit_mask{(arg0: itype; arg1: integer; arg2: integer)};
var
    sp20: binasm;
begin
    if arg1 <> 0 then begin
        sp20.symno := 0;
        sp20.instr := arg0;
        sp20.regmask := arg1;
        sp20.regoffset := arg2;
        append_d(sp20);
    end;
end;

procedure demit_frame{(arg0: integer; arg1: registers; arg2: registers)};
var
    sp20: binasm;
begin
    sp20.instr := iframe;
    sp20.symno := 0;
    sp20.frameoffset := arg0;
    sp20.framereg := arg1;
    sp20.pcreg := arg2;
    append_d(sp20);
end;

procedure emit_file{(arg0: integer; arg1: boolean)};
var
    sp108: Filename;
    temp_v0: pst_string;
    i: integer;
    var_s3: cardinal;
    var_v0: integer;
    var_v1: integer;
    spE4: binasm;
begin
    if arg0 = 0 then begin
        if not mscoff then begin
            report_error(Warn, 1055, 'entry_exit.p', 'file number missing');
        end;
    end else begin
        spE4.symno := arg0;
        spE4.instr := ifile;
        if arg0 = 0 then begin
            arg0 := 2;
        end;
        temp_v0 := st_str_idn(arg0);
        for i := 1 to Filenamelen do begin
            sp108[i] := ' ';
        end;
        i := 1;
        while temp_v0^[i] <> char(0) do begin
            sp108[i] := temp_v0^[i];
            i := i + 1;
        end;
        spE4.length := i - 1;
        if arg1 then begin
            append_d(spE4);
        end else begin
            append_i(spE4);
        end;
        if spE4.length <> 0 then begin
            for var_s3 := 1 to (spE4.length - 1) div 16 + 1 do begin
                spE4.data := '';
                for var_v0 := 1 to 16 do begin
                    var_v1 := lshift(var_s3, 4) - 16 + var_v0;
                    { @bug: reads spE4.length after it is overwritten by character data. This data gets }
                    { interpreted as a very large number so this if-condition is always true in practice }
                    if var_v1 <= spE4.length then begin
                        spE4.data[var_v0] := sp108[var_v1];
                    end else begin
                        break;
                    end;
                end;
                if arg1 then begin
                    append_d(spE4);
                end else begin
                    append_i(spE4);
                end;
            end;
        end;
    end;
end;

procedure emit_optimize_level{(arg0: integer)};
var
    sp20: binasm;
begin
    sp20.instr := ioption;
    sp20.opt_int_value := arg0;
    sp20.symno := 0;
    sp20.option := o_optimize;
    append_d(sp20);
end;
