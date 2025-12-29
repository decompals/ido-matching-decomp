#include "common.h"
#include "tree.h"
#include "tree_utils.h"
#include "emit.h"
#include "reg_mgr.h"
#include "ugen_regdef.h"

var
    lsb_first: boolean;
    opcode_arch: u8;

procedure emit_branch_rrll(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: ^tree);

    procedure func_0041AF70(arg0: registers; arg1: registers; arg2: integer);
    begin
        emit_rrll(zbne, arg0, arg1, arg2);
        emit_rrll(zbne, succ(arg0), succ(arg1), arg2);
    end;
    
    procedure func_0041AFE4(arg0: registers; arg1: registers; arg2: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rrll(zbne, arg0, arg1, sp20);
        emit_rrll(zbeq, succ(arg0), succ(arg1), arg2);
        define_label(sp20);
    end;
    
    procedure func_0041B07C(arg0: registers; arg1: registers; arg2: integer);
    var
        sp30: integer;
    begin
        sp30 := gen_label_id();
        if lsb_first then begin
            emit_rrll(zbgt, succ(arg0), succ(arg1), arg2);
            emit_rrll(zblt, succ(arg0), succ(arg1), sp30);
            emit_rrll(zbgtu, arg0, arg1, arg2);
        end else begin
            emit_rrll(zbgt, arg0, arg1, arg2);
            emit_rrll(zblt, arg0, arg1, sp30);
            emit_rrll(zbgtu, succ(arg0), succ(arg1), arg2);
        end;
        define_label(sp30);
    end;
    
    procedure func_0041B1BC(arg0: registers; arg1: registers; arg2: integer);
    var
        sp30: integer;
    begin
        sp30 := gen_label_id();
        if lsb_first then begin
            emit_rrll(zbgtu, succ(arg0), succ(arg1), arg2);
            emit_rrll(zbltu, succ(arg0), succ(arg1), sp30);
            emit_rrll(zbgtu, arg0, arg1, arg2);
        end else begin
            emit_rrll(zbgtu, arg0, arg1, arg2);
            emit_rrll(zbltu, arg0, arg1, sp30);
            emit_rrll(zbgtu, succ(arg0), succ(arg1), arg2);
        end;
        define_label(sp30);
    end;
    
    procedure func_0041B2FC(arg0: registers; arg1: registers; arg2: integer);
    var
        sp30: integer;
    begin
        sp30 := gen_label_id();
        if lsb_first then begin
            emit_rrll(zblt, succ(arg0), succ(arg1), arg2);
            emit_rrll(zbgt, succ(arg0), succ(arg1), sp30);
            emit_rrll(zbltu, arg0, arg1, arg2);
        end else begin
            emit_rrll(zblt, arg0, arg1, arg2);
            emit_rrll(zbgt, arg0, arg1, sp30);
            emit_rrll(zbltu, succ(arg0), succ(arg1), arg2);
        end;
        define_label(sp30);
    end;
    
    procedure func_0041B43C(arg0: registers; arg1: registers; arg2: integer);
    var
        sp30: integer;
    begin
        sp30 := gen_label_id();
        if lsb_first then begin
            emit_rrll(zbltu, succ(arg0), succ(arg1), arg2);
            emit_rrll(zbgtu, succ(arg0), succ(arg1), sp30);
            emit_rrll(zbltu, arg0, arg1, arg2);
        end else begin
            emit_rrll(zbltu, arg0, arg1, arg2);
            emit_rrll(zbgtu, arg0, arg1, sp30);
            emit_rrll(zbltu, succ(arg0), succ(arg1), arg2);
        end;
        define_label(sp30);
    end;
    
    procedure func_0041B57C(arg0: registers; arg1: registers; arg2: integer);
    var
        sp30: integer;
    begin
        sp30 := gen_label_id();
        if lsb_first then begin
            emit_rrll(zblt, succ(arg0), succ(arg1), arg2);
            emit_rrll(zbgt, succ(arg0), succ(arg1), sp30);
            emit_rrll(zbleu, arg0, arg1, arg2);
        end else begin
            emit_rrll(zblt, arg0, arg1, arg2);
            emit_rrll(zbgt, arg0, arg1, sp30);
            emit_rrll(zbleu, succ(arg0), succ(arg1), arg2);
        end;
        define_label(sp30);
    end;
    
    procedure func_0041B6BC(arg0: registers; arg1: registers; arg2: integer);
    var
        sp30: integer;
    begin
        sp30 := gen_label_id();
        if lsb_first then begin
            emit_rrll(zbltu, succ(arg0), succ(arg1), arg2);
            emit_rrll(zbgtu, succ(arg0), succ(arg1), sp30);
            emit_rrll(zbleu, arg0, arg1, arg2);
        end else begin
            emit_rrll(zbltu, arg0, arg1, arg2);
            emit_rrll(zbgtu, arg0, arg1, sp30);
            emit_rrll(zbleu, succ(arg0), succ(arg1), arg2);
        end;
        define_label(sp30);
    end;
    
    procedure func_0041B7FC(arg0: registers; arg1: registers; arg2: integer);
    var
        sp30: integer;
    begin
        sp30 := gen_label_id();
        if lsb_first then begin
            emit_rrll(zbgt, succ(arg0), succ(arg1), arg2);
            emit_rrll(zblt, succ(arg0), succ(arg1), sp30);
            emit_rrll(zbgeu, arg0, arg1, arg2);
        end else begin
            emit_rrll(zbgt, arg0, arg1, arg2);
            emit_rrll(zblt, arg0, arg1, sp30);
            emit_rrll(zbgeu, succ(arg0), succ(arg1), arg2);
        end;
        define_label(sp30);
    end;
    
    procedure func_0041B93C(arg0: registers; arg1: registers; arg2: integer);
    var
        sp30: integer;
    begin
        sp30 := gen_label_id();
        if lsb_first then begin
            emit_rrll(zbgtu, succ(arg0), succ(arg1), arg2);
            emit_rrll(zbltu, succ(arg0), succ(arg1), sp30);
            emit_rrll(zbgeu, arg0, arg1, arg2);
        end else begin
            emit_rrll(zbgtu, arg0, arg1, arg2);
            emit_rrll(zbltu, arg0, arg1, sp30);
            emit_rrll(zbgeu, succ(arg0), succ(arg1), arg2);
        end;
        define_label(sp30);
    end;

begin
    if (opcode_arch = 0) and (arg4^.u.Dtype in [Idt, Kdt, Wdt]) then begin
        case arg0 of
            zbne: func_0041AF70(arg1, arg2, arg3);
            zbeq: func_0041AFE4(arg1, arg2, arg3);
            zbgt: func_0041B07C(arg1, arg2, arg3);
            zbgtu: func_0041B1BC(arg1, arg2, arg3);
            zblt: func_0041B2FC(arg1, arg2, arg3);
            zbltu: func_0041B43C(arg1, arg2, arg3);
            zble: func_0041B57C(arg1, arg2, arg3);
            zbleu: func_0041B6BC(arg1, arg2, arg3);
            zbge: func_0041B7FC(arg1, arg2, arg3);
            zbgeu: func_0041B93C(arg1, arg2, arg3);
            otherwise emit_rrll(arg0, arg1, arg2, arg3);
        end;
    end else begin
        emit_rrll(arg0, arg1, arg2, arg3);
    end;
end;

procedure emit_branch_rill(arg0: asmcodes; arg1: registers; arg2: integer; arg3: integer; arg4: integer; arg5: ^tree);
var
    sp30: Valu;
    temp_s0: registers;

    procedure func_0041BCC0(arg0: registers; arg1: integer; arg2: integer; arg3: integer);
    begin
        emit_rill(zbne, arg0, arg1, arg3);
        emit_rill(zbne, succ(arg0), arg2, arg3);
    end;
    
    procedure func_0041BD30(arg0: registers; arg1: integer; arg2: integer; arg3: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zbne, arg0, arg1, sp20);
        emit_rill(zbeq, succ(arg0), arg2, arg3);
        define_label(sp20);
    end;
    
    procedure func_0041BDC8(arg0: registers; arg1: integer; arg2: integer; arg3: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zbgt, arg0, arg1, arg3);
        emit_rill(zblt, arg0, arg1, sp20);
        emit_rill(zbgtu, succ(arg0), arg2, arg3);
        define_label(sp20);
    end;
    
    procedure func_0041BE80(arg0: registers; arg1: integer; arg2: integer; arg3: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zbgtu, arg0, arg1, arg3);
        emit_rill(zbltu, arg0, arg1, sp20);
        emit_rill(zbgtu, succ(arg0), arg2, arg3);
        define_label(sp20);
    end;
    
    procedure func_0041BF38(arg0: registers; arg1: integer; arg2: integer; arg3: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zbgt, arg0, arg1, arg3);
        emit_rill(zblt, arg0, arg1, sp20);
        emit_rill(zbgeu, succ(arg0), arg2, arg3);
        define_label(sp20);
    end;
    
    procedure func_0041BFF0(arg0: registers; arg1: integer; arg2: integer; arg3: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zbgtu, arg0, arg1, arg3);
        emit_rill(zbltu, arg0, arg1, sp20);
        emit_rill(zbgeu, succ(arg0), arg2, arg3);
        define_label(sp20);
    end;
    
    procedure func_0041C0A8(arg0: registers; arg1: integer; arg2: integer; arg3: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zblt, arg0, arg1, arg3);
        emit_rill(zbgt, arg0, arg1, sp20);
        emit_rill(zbltu, succ(arg0), arg2, arg3);
        define_label(sp20);
    end;
    
    procedure func_0041C160(arg0: registers; arg1: integer; arg2: integer; arg3: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zbltu, arg0, arg1, arg3);
        emit_rill(zbgtu, arg0, arg1, sp20);
        emit_rill(zbltu, succ(arg0), arg2, arg3);
        define_label(sp20);
    end;
    
    procedure func_0041C218(arg0: registers; arg1: integer; arg2: integer; arg3: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zblt, arg0, arg1, arg3);
        emit_rill(zbgt, arg0, arg1, sp20);
        emit_rill(zbleu, succ(arg0), arg2, arg3);
        define_label(sp20);
    end;
    
    procedure func_0041C2D0(arg0: registers; arg1: integer; arg2: integer; arg3: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zbltu, arg0, arg1, arg3);
        emit_rill(zbgtu, arg0, arg1, sp20);
        emit_rill(zbleu, succ(arg0), arg2, arg3);
        define_label(sp20);
    end;

begin
    if (opcode_arch = 0) and (arg5^.u.Dtype in [Idt, Kdt, Wdt]) then begin
        case arg0 of
            zbne: func_0041BCC0(arg1, arg2, arg3, arg4);
            zbeq: func_0041BD30(arg1, arg2, arg3, arg4);
            zbgt: func_0041BDC8(arg1, arg2, arg3, arg4);
            zbgtu: func_0041BE80(arg1, arg2, arg3, arg4);
            zblt: func_0041C0A8(arg1, arg2, arg3, arg4);
            zbltu: func_0041C160(arg1, arg2, arg3, arg4);
            zble: func_0041C218(arg1, arg2, arg3, arg4);
            zbleu: func_0041C2D0(arg1, arg2, arg3, arg4);
            zbge: func_0041BF38(arg1, arg2, arg3, arg4);
            zbgeu: func_0041BFF0(arg1, arg2, arg3, arg4);
            otherwise emit_rill(arg0, arg1, arg3, arg4);
        end;
    end else if (opcode_arch = 1) and (arg2 <> 0) then begin
        sp30.dwval_h := arg2;
        sp30.dwval_l := arg3;
        temp_s0 := get_free_reg(0, 1);
        free_reg(temp_s0);
        emit_rii(zdli, temp_s0, sp30);
        emit_rrll(arg0, arg1, temp_s0, arg4);
    end else begin
        emit_rill(arg0, arg1, arg3, arg4);
    end;
end;

procedure emit_trap_rri(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: ^tree);

    procedure func_0041C694(arg0: registers; arg1: registers; arg2: integer);
    begin
        emit_rri_(ztne, arg0, arg1, arg2, franone);
        emit_rri_(ztne, succ(arg0), succ(arg1), arg2, franone);
    end;
    
    procedure func_0041C710(arg0: registers; arg1: registers; arg2: integer);
    var
        sp28: integer;
    begin
        sp28 := gen_label_id();
        emit_rrll(zbne, arg0, arg1, sp28);
        emit_rri_(zteq, succ(arg0), succ(arg1), arg2, franone);
        define_label(sp28);
    end;
    
    procedure func_0041C7AC(arg0: registers; arg1: registers; arg2: integer);
    var
        sp28: integer;
    begin
        sp28 := gen_label_id();
        emit_rri_(ztlt, arg0, arg1, arg2, franone);
        emit_rrll(zbgt, arg0, arg1, sp28);
        emit_rri_(ztltu, succ(arg0), succ(arg1), arg2, franone);
        define_label(sp28);
    end;
    
    procedure func_0041C86C(arg0: registers; arg1: registers; arg2: integer);
    var
        sp28: integer;
    begin
        sp28 := gen_label_id();
        emit_rri_(ztltu, arg0, arg1, arg2, franone);
        emit_rrll(zbgtu, arg0, arg1, sp28);
        emit_rri_(zbltu, succ(arg0), succ(arg1), arg2, franone);
        define_label(sp28);
    end;
    
    procedure func_0041C92C(arg0: registers; arg1: registers; arg2: integer);
    var
        sp28: integer;
    begin
        sp28 := gen_label_id();
        emit_rri_(ztlt, arg1, arg0, arg2, franone);
        emit_rrll(zblt, arg0, arg1, sp28);
        emit_rri_(ztgeu, succ(arg0), succ(arg1), arg2, franone);
        define_label(sp28);
    end;
    
    procedure func_0041C9EC(arg0: registers; arg1: registers; arg2: integer);
    var
        sp28: integer;
    begin
        sp28 := gen_label_id();
        emit_rri_(ztltu, arg1, arg0, arg2, franone);
        emit_rrll(zbltu, arg0, arg1, sp28);
        emit_rri_(ztgeu, succ(arg0), succ(arg1), arg2, franone);
        define_label(sp28);
    end;

begin
    if (opcode_arch = 0) and (arg4^.u.Dtype in [Idt, Kdt, Wdt]) then begin
        case arg0 of
            ztne: func_0041C694(arg1, arg2, arg3);
            zteq: func_0041C710(arg1, arg2, arg3);
            ztge: func_0041C92C(arg1, arg2, arg3);
            ztgeu: func_0041C9EC(arg1, arg2, arg3);
            ztlt: func_0041C7AC(arg1, arg2, arg3);
            ztltu: func_0041C86C(arg1, arg2, arg3);
            otherwise emit_rri_(arg0, arg1, arg2, arg3, franone);
        end;
    end else begin
        emit_rri_(arg0, arg1, arg2, arg3, franone);
    end;
end;

procedure emit_trap_ri(arg0: asmcodes; arg1: registers; arg2: integer; arg3: integer; arg4: ^tree);

    procedure func_0041CC60(arg0: registers; arg1: integer; arg2: integer);
    begin
        emit_ri_(ztne, arg0, arg1, franone);
        emit_ri_(ztne, succ(arg0), arg2, franone);
    end;
    
    procedure func_0041CCD0(arg0: registers; arg1: integer; arg2: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zbne, arg0, arg1, sp20);
        emit_ri_(zteq, succ(arg0), arg2, franone);
        define_label(sp20);
    end;
    
    procedure func_0041CD64(arg0: registers; arg1: integer; arg2: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_ri_(ztlt, arg0, arg1, franone);
        emit_rill(zbgt, arg0, arg1, sp20);
        emit_ri_(ztltu, succ(arg0), arg2, franone);
        define_label(sp20);
    end;
    
    procedure func_0041CE18(arg0: registers; arg1: integer; arg2: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_ri_(ztltu, arg0, arg1, franone);
        emit_rill(zbgtu, arg0, arg1, sp20);
        emit_ri_(zbltu, succ(arg0), arg2, franone);
        define_label(sp20);
    end;
    
    procedure func_0041CECC(arg0: registers; arg1: integer; arg2: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zblt, arg0, arg1, sp20);
        emit_ri_(ztne, arg0, arg1, franone);
        emit_ri_(ztgeu, succ(arg0), arg2, franone);
        define_label(sp20);
    end;
    
    procedure func_0041CF80(arg0: registers; arg1: integer; arg2: integer);
    var
        sp20: integer;
    begin
        sp20 := gen_label_id();
        emit_rill(zbltu, arg0, arg1, sp20);
        emit_ri_(ztne, arg0, arg1, franone);
        emit_ri_(ztgeu, succ(arg0), arg2, franone);
        define_label(sp20);
    end;

begin
    if (opcode_arch = 0) and (arg4^.u.Dtype in [Idt, Kdt, Wdt]) then begin
        case arg0 of
            ztne: func_0041CC60(arg1, arg2, arg3);
            zteq: func_0041CCD0(arg1, arg2, arg3);
            ztge: func_0041CECC(arg1, arg2, arg3);
            ztgeu: func_0041CF80(arg1, arg2, arg3);
            ztlt: func_0041CD64(arg1, arg2, arg3);
            ztltu: func_0041CE18(arg1, arg2, arg3);
            otherwise emit_ri_(arg0, arg1, arg3, franone);
        end;
    end else begin
        emit_ri_(arg0, arg1, arg3, franone);
    end;
end;

procedure dw_emit_rrr(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers; arg4: ^tree);
var
    sp27: registers;

    procedure func_0041D1E8(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers);
    var
        var_s2: registers;
        var_s3: registers;
    begin
        if arg1 = arg3 then begin
            var_s3 := arg3;
            var_s2 := arg2;
        end else begin
            var_s3 := arg2;
            var_s2 := arg3;
        end;
        emit_dir0(iset, ord(set_noat));
        if lsb_first then begin
            emit_rrr(zaddu, arg1, var_s3, var_s2);
            emit_rrr(zsltu, xr1, arg1, var_s2);
            emit_rrr(arg0, succ(arg1), xr1, succ(var_s3));
            emit_rrr(arg0, succ(arg1), succ(arg1), succ(var_s2));
        end else begin
            emit_rrr(zaddu, succ(arg1), succ(var_s3), succ(var_s2));
            emit_rrr(zsltu, xr1, succ(arg1), succ(var_s2));
            emit_rrr(arg0, arg1, xr1, var_s3);
            emit_rrr(arg0, arg1, arg1, var_s2);
        end;
        emit_dir0(iset, ord(set_at));
    end;
    
    procedure func_0041D39C(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers);
    begin
        emit_dir0(iset, ord(set_noat));
        if lsb_first then begin
            emit_rrr(zsltu, xr1, arg2, arg3);
            emit_rrr(zsubu, arg1, arg2, arg3);
            emit_rrr(arg0, succ(arg1), succ(arg2), succ(arg3));
            emit_rrr(arg0, succ(arg1), succ(arg1), xr1);
        end else begin
            emit_rrr(zsltu, xr1, succ(arg2), succ(arg3));
            emit_rrr(zsubu, succ(arg1), succ(arg2), succ(arg3));
            emit_rrr(arg0, arg1, arg2, arg3);
            emit_rrr(arg0, arg1, arg1, xr1);
        end;
        emit_dir0(iset, ord(set_at));
    end;
    
    procedure func_0041D534(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers);
    var
        sp43: registers;
        sp42: registers;
        sp41: registers;
        sp3C: integer;
        sp38: integer;
        sp34: integer;
        sp33: registers;
    begin
        sp43 := get_free_reg(0, 1);
        free_reg(sp43);
        sp42 := get_free_reg(0, 1);
        free_reg(sp42);
        sp41 := get_free_reg(0, 1);
        free_reg(sp41);
        sp3C := gen_label_id();
        sp38 := gen_label_id();
        sp34 := gen_label_id();
        sp33 := arg3;
        emit_rri_(zsll, sp43, arg3, 26, franone);
        emit_rll(zbgez, sp43, sp3C);
        if lsb_first then begin
            emit_rrr(zsll, succ(arg1), arg2, arg3);
            emit_ri_(zli, arg1, 0, franone);
            emit_ll(zb, sp34);
            define_label(sp3C);
            emit_rrr(zsll, succ(arg1), succ(arg2), arg3);
            emit_rll(zbeqz, sp43, sp38);
            emit_rr(znegu, sp42, arg3);
            emit_rrr(zsrl, sp41, arg2, sp42);
            emit_rrr(zor, succ(arg1), succ(arg1), sp41);
            define_label(sp38);
            emit_rrr(zsll, arg1, arg2, arg3);
        end else begin
            if arg4^.op2^.u.Dtype in [Idt, Kdt, Wdt] then begin
                sp33 := succ(arg3);
            end;
            emit_rrr(zsll, arg1, succ(arg2), sp33);
            emit_ri_(zli, succ(arg1), 0, franone);
            emit_ll(zb, sp34);
            define_label(sp3C);
            emit_rrr(zsll, arg1, arg2, sp33);
            emit_rll(zbeqz, sp43, sp38);
            emit_rr(znegu, sp42, sp33);
            emit_rrr(zsrl, sp41, succ(arg2), sp42);
            emit_rrr(zor, arg1, arg1, sp41);
            define_label(sp38);
            emit_rrr(zsll, succ(arg1), succ(arg2), sp33);
        end;
        define_label(sp34);
    end;
    
    procedure func_0041D958(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers);
    var
        sp43: registers;
        sp42: registers;
        sp41: registers;
        sp3C: integer;
        sp38: integer;
        sp34: integer;
        sp33: registers;
    begin
        sp43 := get_free_reg(0, 1);
        free_reg(sp43);
        sp42 := get_free_reg(0, 1);
        free_reg(sp42);
        sp41 := get_free_reg(0, 1);
        free_reg(sp41);
        sp3C := gen_label_id();
        sp38 := gen_label_id();
        sp34 := gen_label_id();
        sp33 := arg3;
        emit_rri_(zsll, sp43, arg3, 26, franone);
        emit_rll(zbgez, sp43, sp3C);
        if lsb_first then begin
            emit_rrr(arg0, arg1, succ(arg2), arg3);
            if arg0 = zsra then begin
                emit_rri_(zsra, succ(arg1), succ(arg2), 31, franone);
            end else begin
                emit_ri_(zli, succ(arg1), 0, franone);
            end;
            emit_ll(zb, sp34);
            define_label(sp3C);
            emit_rrr(zsrl, arg1, arg2, arg3);
            emit_rll(zbeqz, sp43, sp38);
            emit_rr(znegu, sp42, arg3);
            emit_rrr(zsll, sp41, succ(arg2), sp42);
            emit_rrr(zor, arg1, arg1, sp41);
            define_label(sp38);
            emit_rrr(arg0, succ(arg1), succ(arg2), arg3);
        end else begin
            if arg4^.op2^.u.Dtype in [Idt, Kdt, Wdt] then begin
                sp33 := succ(arg3);
            end;
            emit_rrr(arg0, succ(arg1), arg2, sp33);
            if arg0 = zsra then begin
                emit_rri_(zsra, arg1, arg2, 31, franone);
            end else begin
                emit_ri_(zli, arg1, 0, franone);
            end;
            emit_ll(zb, sp34);
            define_label(sp3C);
            emit_rrr(zsrl, succ(arg1), succ(arg2), sp33);
            emit_rll(zbeqz, sp43, sp38);
            emit_rr(znegu, sp42, sp33);
            emit_rrr(zsll, sp41, arg2, sp42);
            emit_rrr(zor, succ(arg1), succ(arg1), sp41);
            define_label(sp38);
            emit_rrr(arg0, arg1, arg2, sp33);
        end;
        define_label(sp34);
    end;
    
    procedure func_0041DDE0(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers);
    begin
        emit_dir0(iset, ord(set_noat));
        emit_rrr(zxor, xr1, arg2, arg3);
        emit_rrr(zxor, arg1, succ(arg2), succ(arg3));
        if arg0 = zseq then begin
            emit_rrr(zor, arg1, arg1, xr1);
            emit_rri_(zsltiu, arg1, arg1, 1, franone);
        end else begin
            emit_rrr(zor, arg1, arg1, xr1);
            emit_rrr(zsltu, arg1, gpr_zero, arg1);
        end;
        emit_dir0(iset, ord(set_at));
    end;
    
    procedure func_0041DF18(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers);
    var
        sp30: integer;
    begin
        sp30 := gen_label_id();
        if lsb_first then begin
            emit_rrr(zsgtu, arg1, succ(arg2), succ(arg3));
            emit_rrll(zbne, succ(arg2), succ(arg3), sp30);
            emit_rrr(arg0, arg1, arg2, arg3);
        end else begin
            emit_rrr(zsgtu, arg1, arg2, arg3);
            emit_rrll(zbne, arg2, arg3, sp30);
            emit_rrr(arg0, arg1, succ(arg2), succ(arg3));
        end;
        define_label(sp30);
    end;
    
    procedure func_0041E05C(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers);
    var
        sp38: integer;
        sp36: asmcodes;
    begin
        if arg0 = zsge then begin
            sp36 := zsgeu;
        end else begin
            sp36 := zsgtu;
        end;
        sp38 := gen_label_id();
        if lsb_first then begin
            emit_rrr(zsgt, arg1, succ(arg2), succ(arg3));
            emit_rrll(zbne, succ(arg2), succ(arg3), sp38);
            emit_rrr(sp36, arg1, arg2, arg3);
        end else begin
            emit_rrr(zsgt, arg1, arg2, arg3);
            emit_rrll(zbne, arg2, arg3, sp38);
            emit_rrr(sp36, arg1, succ(arg2), succ(arg3));
        end;
        define_label(sp38);
    end;
    
    procedure func_0041E1C0(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers);
    var
        sp30: integer;
    begin
        sp30 := gen_label_id();
        if lsb_first then begin
            emit_rrr(zsltu, arg1, succ(arg2), succ(arg3));
            emit_rrll(zbne, succ(arg2), succ(arg3), sp30);
            emit_rrr(arg0, arg1, arg2, arg3);
        end else begin
            emit_rrr(zsltu, arg1, arg2, arg3);
            emit_rrll(zbne, arg2, arg3, sp30);
            emit_rrr(arg0, arg1, succ(arg2), succ(arg3));
        end;
        define_label(sp30);
    end;
    
    procedure func_0041E304(arg0: asmcodes; arg1: registers; arg2: registers; arg3: registers);
    var
        sp38: integer;
        sp36: asmcodes;
    begin
        if arg0 = zslt then begin
            sp36 := zsltu;
        end else begin
            sp36 := zsleu;
        end;
        sp38 := gen_label_id();
        if lsb_first then begin
            emit_rrr(zslt, arg1, succ(arg2), succ(arg3));
            emit_rrll(zbne, succ(arg2), succ(arg3), sp38);
            emit_rrr(sp36, arg1, arg2, arg3);
        end else begin
            emit_rrr(zslt, arg1, arg2, arg3);
            emit_rrll(zbne, arg2, arg3, sp38);
            emit_rrr(sp36, arg1, succ(arg2), succ(arg3));
        end;
        define_label(sp38);
    end;

begin
    if (opcode_arch = 0) and (arg4^.u.Dtype in [Idt, Kdt, Wdt]) then begin
        case arg0 of
            zand, znor, zor, zxor: begin
                emit_rrr(arg0, arg1, arg2, arg3);
                emit_rrr(arg0, succ(arg1), succ(arg2), succ(arg3));
            end;
            zadd, zaddu, zaddou:
                func_0041D1E8(arg0, arg1, arg2, arg3);
            zsub, zsubu, zsubou:
                func_0041D39C(arg0, arg1, arg2, arg3);
            zsll:
                func_0041D534(arg0, arg1, arg2, arg3);
            zsra, zsrl:
                func_0041D958(arg0, arg1, arg2, arg3);
            zseq, zsne:
                func_0041DDE0(arg0, arg1, arg2, arg3);
            zsge, zsgeu, zsgt, zsgtu, zsle, zsleu, zslt, zsltu: begin
                if (arg1 = arg2) or (arg1 = arg3) then begin
                    sp27 := xr1;
                    emit_dir0(iset, ord(set_noat));
                end else begin
                    sp27 := arg1;
                end;
                case arg0 of
                    zsgeu, zsgtu:
                        func_0041DF18(arg0, sp27, arg2, arg3);
                    zsge, zsgt:
                        func_0041E05C(arg0, sp27, arg2, arg3);
                    zsleu, zsltu:
                        func_0041E1C0(arg0, sp27, arg2, arg3);
                    zsle, zslt:
                        func_0041E304(arg0, sp27, arg2, arg3);
                end;
                if sp27 = xr1 then begin
                    emit_rr(zmove, arg1, xr1);
                    emit_dir0(iset, ord(set_at));
                end;
            end;
            otherwise
                emit_rrr(arg0, arg1, arg2, arg3);
        end;
    end else begin
        emit_rrr(arg0, arg1, arg2, arg3);
    end;
end;

procedure dw_emit_rri(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer; arg5: ^tree);
var
    sp38: Valu;
    sp37: registers;
    
    procedure func_0041E800(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer);
    var
        sp2B: registers;
        sp2A: registers;
        sp29: registers;
        sp28: registers;
    begin
        if lsb_first then begin
            sp2B := succ(arg1);
            sp2A := arg1;
            sp29 := succ(arg2);
            sp28 := arg2;
        end else begin
            sp2B := arg1;
            sp2A := succ(arg1);
            sp29 := arg2;
            sp28 := succ(arg2);
        end;
        if (arg3 = 0) and (arg4 < 16#8000) and (arg4 >= -16#8000) then begin
            emit_rri_(zaddu, sp2A, sp28, arg4, franone);
            emit_dir0(iset, ord(set_noat));
            emit_rri_(zsltu, xr1, sp2A, arg4, franone);
            emit_rrr(arg0, sp2B, sp29, xr1);
            emit_dir0(iset, ord(set_at));
            return;
        end;
        emit_dir0(iset, ord(set_noat));
        emit_ri_(zli, xr1, arg4, franone);
        emit_rrr(zaddu, sp2A, sp28, xr1);
        emit_rrr(zsltu, xr1, sp2A, xr1);
        emit_rrr(arg0, sp2B, sp29, xr1);
        emit_dir0(iset, ord(set_at));
        emit_ri_(arg0, sp2B, arg3, franone);
    end;
    
    procedure func_0041EA00(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer);
    var
        sp2B: registers;
        sp2A: registers;
        sp29: registers;
        sp28: registers;
    begin
        if lsb_first then begin
            sp2B := succ(arg1);
            sp2A := arg1;
            sp29 := succ(arg2);
            sp28 := arg2;
        end else begin
            sp2B := arg1;
            sp2A := succ(arg1);
            sp29 := arg2;
            sp28 := succ(arg2);
        end;
        if (arg3 = 0) and (arg4 < 16#8000) and (arg4 >= -16#8000) then begin
            emit_dir0(iset, ord(set_noat));
            emit_rri_(zsltu, xr1, sp28, arg4, franone);
            emit_rri_(zsubu, sp2A, sp28, arg4, franone);
            emit_rrr(arg0, sp2B, sp29, xr1);
            emit_dir0(iset, ord(set_at));
            return;
        end;
        emit_dir0(iset, ord(set_noat));
        emit_ri_(zli, xr1, arg4, franone);
        emit_rrr(zsltu, xr1, sp28, xr1);
        emit_rrr(arg0, sp2B, sp29, xr1);
        emit_dir0(iset, ord(set_at));
        emit_rri_(zsubu, sp2A, sp28, arg4, franone);
        emit_ri_(arg0, sp2B, arg3, franone);
    end;
    
    procedure func_0041EC08(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer);
    begin
        arg3 := arg3 & 63;
        if arg3 = 64 then begin
            emit_ri_(zli, arg1, 0, franone);
            emit_ri_(zli, succ(arg1), 0, franone);
        end else if arg3 >= 32 then begin
            if lsb_first then begin
                emit_ri_(zli, arg1, 0, franone);
                emit_rri_(arg0, succ(arg1), arg2, arg3 - 32, franone);
            end else begin
                emit_ri_(zli, succ(arg1), 0, franone);
                emit_rri_(arg0, arg1, succ(arg2), arg3 - 32, franone);
            end;
        end else begin
            if lsb_first then begin
                emit_rri_(arg0, succ(arg1), succ(arg2), arg3, franone);
                emit_rri_(arg0, arg1, arg2, 32 - arg3, franone);
                emit_rrr(zor, succ(arg1), succ(arg1), arg1);
                emit_rri_(arg0, arg1, arg2, arg3, franone);
            end else begin
                emit_rri_(arg0, arg1, arg2, arg3, franone);
                emit_rri_(arg0, succ(arg1), succ(arg2), 32 - arg3, franone);
                emit_rrr(zor, arg1, arg1, succ(arg1));
                emit_rri_(arg0, succ(arg1), succ(arg2), arg3, franone);
            end;
        end;
    end;
    
    procedure func_0041EE78(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer);
    var
        sp38: integer;
    begin
        arg3 := arg3 & 63;
        if arg3 = 64 then begin
            emit_ri_(zli, arg1, 0, franone);
            emit_ri_(zli, succ(arg1), 0, franone);
        end else if arg3 >= 32 then begin
            sp38 := gen_label_id();
            if lsb_first then begin
                emit_ri_(zli, succ(arg1), 0, franone);
                emit_rll(zbgez, succ(arg2), sp38);
                emit_ri_(zli, succ(arg1), -1, franone);
                define_label(sp38);
                emit_rri_(arg0, arg1, succ(arg2), arg3 - 32, franone);
            end else begin
                emit_ri_(zli, arg1, 0, franone);
                emit_rll(zbgez, arg2, sp38);
                emit_ri_(zli, arg1, -1, franone);
                define_label(sp38);
                emit_rri_(arg0, succ(arg1), arg2, arg3 - 32, franone);
            end;
        end else begin
            if lsb_first then begin
                emit_rri_(zsrl, arg1, arg2, arg3, franone);
                emit_rri_(zsll, succ(arg1), succ(arg2), 32 - arg3, franone);
                emit_rrr(zor, arg1, arg1, succ(arg1));
                emit_rri_(arg0, succ(arg1), succ(arg2), arg3, franone);
            end else begin
                emit_rri_(zsrl, succ(arg1), succ(arg2), arg3, franone);
                emit_rri_(zsll, arg1, arg2, 32 - arg3, franone);
                emit_rrr(zor, succ(arg1), succ(arg1), arg1);
                emit_rri_(arg0, arg1, arg2, arg3, franone);
            end;
        end;
    end;
    
    procedure func_0041F194(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer);
    begin
        emit_ri_(zli, arg1, arg4, franone);
        if lsb_first then begin
            emit_rrr(zxor, arg1, arg1, arg2);
        end else begin
            emit_rrr(zxor, arg1, arg1, succ(arg2));
        end;
        emit_dir0(iset, ord(set_noat));
        emit_ri_(zli, xr1, arg3, franone);
        if lsb_first then begin
            emit_rrr(zxor, xr1, xr1, succ(arg2));
        end else begin
            emit_rrr(zxor, xr1, xr1, arg2);
        end;
        if arg0 = zseq then begin
            emit_rrr(zor, arg1, arg1, xr1);
            emit_rri_(zsltiu, arg1, arg1, 1, franone);
        end else begin
            emit_rrr(zor, arg1, arg1, xr1);
            emit_rrr(zsltu, arg1, gpr_zero, arg1);
        end;
        emit_dir0(iset, ord(set_at));
    end;
    
    procedure func_0041F368(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer);
    var
        temp_s0: integer;
    begin
        temp_s0 := gen_label_id();
        if lsb_first then begin
            emit_rri_(zsgtu, arg1, succ(arg2), arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zbltu, succ(arg2), arg3, temp_s0);
            emit_rri_(arg0, arg1, arg2, arg4, franone);
        end else begin
            emit_rri_(zsgtu, arg1, arg2, arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zbltu, arg2, arg3, temp_s0);
            emit_rri_(arg0, arg1, succ(arg2), arg4, franone);
        end;
        define_label(temp_s0);
    end;
    
    procedure func_0041F4F0(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer);
    var
        temp_s0: integer;
    begin
        temp_s0 := gen_label_id();
        if lsb_first then begin
            emit_rri_(zsgt, arg1, succ(arg2), arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zblt, succ(arg2), arg3, temp_s0);
            emit_rri_(zsgeu, arg1, arg2, arg4, franone);
        end else begin
            emit_rri_(zsgt, arg1, arg2, arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zblt, arg2, arg3, temp_s0);
            emit_rri_(zsgeu, arg1, succ(arg2), arg4, franone);
        end;
        define_label(temp_s0);
    end;
    
    procedure func_0041F678(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer);
    var
        temp_s0: integer;
    begin
        temp_s0 := gen_label_id();
        if lsb_first then begin
            emit_rri_(zsgt, arg1, succ(arg2), arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zblt, succ(arg2), arg3, temp_s0);
            emit_rri_(zsgtu, arg1, arg2, arg4, franone);
        end else begin
            emit_rri_(zsgt, arg1, arg2, arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zblt, arg2, arg3, temp_s0);
            emit_rri_(zsgtu, arg1, succ(arg2), arg4, franone);
        end;
        define_label(temp_s0);
    end;
    
    procedure func_0041F800(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer);
    var
        temp_s0: integer;
    begin
        temp_s0 := gen_label_id();
        if lsb_first then begin
            emit_rri_(zslt, arg1, succ(arg2), arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zbgt, succ(arg2), arg3, temp_s0);
            emit_rri_(zsleu, arg1, arg2, arg4, franone);
        end else begin
            emit_rri_(zslt, arg1, arg2, arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zbgt, arg2, arg3, temp_s0);
            emit_rri_(zsleu, arg1, succ(arg2), arg4, franone);
        end;
        define_label(temp_s0);
    end;
    
    procedure func_0041F988(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer);
    var
        temp_s0: integer;
    begin
        temp_s0 := gen_label_id();
        if lsb_first then begin
            emit_rri_(zslt, arg1, succ(arg2), arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zbgt, succ(arg2), arg3, temp_s0);
            emit_rri_(zsltu, arg1, arg2, arg4, franone);
        end else begin
            emit_rri_(zslt, arg1, arg2, arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zbgt, arg2, arg3, temp_s0);
            emit_rri_(zsltu, arg1, succ(arg2), arg4, franone);
        end;
        define_label(temp_s0);
    end;
    
    procedure func_0041FB10(arg0: asmcodes; arg1: registers; arg2: registers; arg3: integer; arg4: integer);
    var
        temp_s0: integer;
    begin
        temp_s0 := gen_label_id();
        if lsb_first then begin
            emit_rri_(zsltu, arg1, succ(arg2), arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zbgtu, succ(arg2), arg3, temp_s0);
            emit_rri_(arg0, arg1, arg2, arg4, franone);
        end else begin
            emit_rri_(zsltu, arg1, arg2, arg3, franone);
            emit_rll(zbgtz, arg1, temp_s0);
            emit_rill(zbgtu, arg2, arg3, temp_s0);
            emit_rri_(arg0, arg1, succ(arg2), arg4, franone);
        end;
        define_label(temp_s0);
    end;

begin
    if (opcode_arch = 0) and (arg5^.u.Dtype in [Idt, Kdt, Wdt]) then begin
        case arg0 of
            zand: begin
                if lsb_first then begin
                    emit_rri_(arg0, arg1, arg2, arg4, franone);
                    if arg3 = 0 then begin
                        emit_rr(zmove, succ(arg1), gpr_zero);
                    end else begin
                        emit_rri_(arg0, succ(arg1), succ(arg2), arg3, franone);
                    end;
                end else begin
                    if arg3 = 0 then begin
                        emit_rr(zmove, arg1, gpr_zero);
                    end else begin
                        emit_rri_(arg0, arg1, arg2, arg3, franone);
                    end;
                    emit_rri_(arg0, succ(arg1), succ(arg2), arg4, franone);
                end;
            end;
            zor, zxor: begin
                if lsb_first then begin
                    emit_rri_(arg0, arg1, arg2, arg4, franone);
                    if arg3 = 0 then begin
                        emit_rr(zmove, succ(arg1), succ(arg2));
                    end else begin
                        emit_rri_(arg0, succ(arg1), succ(arg2), arg3, franone);
                    end;
                end else begin
                    if arg3 = 0 then begin
                        emit_rr(zmove, arg1, arg2);
                    end else begin
                        emit_rri_(arg0, arg1, arg2, arg3, franone);
                    end;
                    emit_rri_(arg0, succ(arg1), succ(arg2), arg4, franone);
                end;
            end;
            znor: begin
                if lsb_first then begin
                    emit_rri_(arg0, arg1, arg2, arg4, franone);
                    if arg3 = 0 then begin
                        emit_rr(znot, succ(arg1), succ(arg2));
                    end else begin
                        emit_rri_(arg0, succ(arg1), succ(arg2), arg3, franone);
                    end;
                end else begin
                    if arg3 = 0 then begin
                        emit_rr(znot, arg1, arg2);
                    end else begin
                        emit_rri_(arg0, arg1, arg2, arg3, franone);
                    end;
                    emit_rri_(arg0, succ(arg1), succ(arg2), arg4, franone);
                end;
            end;
            zadd, zaddu, zaddou:
                func_0041E800(arg0, arg1, arg2, arg3, arg4);
            zsub, zsubu, zsubou:
                func_0041EA00(arg0, arg1, arg2, arg3, arg4);
            zsll:
                func_0041EC08(arg0, arg1, arg2, arg4);
            zsra, zsrl:
                func_0041EE78(arg0, arg1, arg2, arg4);
            zseq, zsne:
                func_0041F194(arg0, arg1, arg2, arg3, arg4);
            zsgeu, zsgtu:
                func_0041F368(arg0, arg1, arg2, arg3, arg4);
            zsge:
                func_0041F4F0(arg0, arg1, arg2, arg3, arg4);
            zsgt:
                func_0041F678(arg0, arg1, arg2, arg3, arg4);
            zsleu, zsltu:
                func_0041FB10(arg0, arg1, arg2, arg3, arg4);
            zsle:
                func_0041F800(arg0, arg1, arg2, arg3, arg4);
            zslt:
                func_0041F988(arg0, arg1, arg2, arg3, arg4);
            otherwise
                emit_rri_(arg0, arg1, arg2, arg4, franone);
        end;
    end else if (opcode_arch = 1) and (arg3 <> 0) then begin
        sp38.dwval_h := arg3;
        sp38.dwval_l := arg4;
        sp37 := get_free_reg(0, 1);
        free_reg(sp37);
        emit_rii(zdli, sp37, sp38);
        emit_rrr(arg0, arg1, arg2, sp37);
    end else begin
        emit_rri_(arg0, arg1, arg2, arg4, franone);
    end;
end;
#endif

procedure dw_emit_rr(arg0: asmcodes; arg1: registers; arg2: registers; arg3: ^tree);

    procedure func_00420360(arg0: asmcodes; arg1: registers; arg2: registers);
    begin
        emit_dir0(iset, ord(set_noat));
        if lsb_first then begin
            emit_rri_(zseq, xr1, arg2, 0, franone);
            emit_rr(znegu, arg1, arg2);
            emit_rr(znot, succ(arg1), succ(arg2));
            if arg0 = zneg then begin
                emit_rrr(zadd, succ(arg1), succ(arg1), xr1);
            end else begin
                emit_rrr(zaddu, succ(arg1), succ(arg1), xr1);
            end;
        end else begin
            emit_rri_(zseq, xr1, succ(arg2), 0, franone);
            emit_rr(znegu, succ(arg1), succ(arg2));
            emit_rr(znot, arg1, arg2);
            if arg0 = zneg then begin
                emit_rrr(zadd, arg1, arg1, xr1);
            end else begin
                emit_rrr(zaddu, arg1, arg1, xr1);
            end;
        end;
        emit_dir0(iset, ord(set_at));
    end;
    
    procedure func_00420524(arg0: asmcodes; arg1: registers; arg2: registers);
    begin
        emit_rr(arg0, arg1, arg2);
        emit_rr(arg0, succ(arg1), succ(arg2));
    end;
    
    procedure func_00420590(arg0: asmcodes; arg1: registers; arg2: registers);
    var
        sp30: integer;
    begin
        dw_emit_rr(zmove, arg1, arg2, arg3);
        sp30 := gen_label_id();
        emit_branch_rill(zbge, arg2, 0, 0, sp30, arg3);
        dw_emit_rr(znegu, arg1, arg2, arg3);
        define_label(sp30);
    end;
    
    procedure func_00420654(arg0: asmcodes; arg1: registers; arg2: registers);
    begin
        emit_rr(arg0, arg1, arg2);
        emit_rr(arg0, succ(arg1), succ(arg2));
    end;

begin
    if (opcode_arch = 0) and (arg3^.u.Dtype in [Idt, Kdt, Wdt]) then begin
        case arg0 of
            zneg, znegu: func_00420360(arg0, arg1, arg2);
            znot: func_00420524(arg0, arg1, arg2);
            zabs: func_00420590(arg0, arg1, arg2);
            zmove: func_00420654(arg0, arg1, arg2);
            otherwise emit_rr(arg0, arg1, arg2);
        end;
    end else begin
        emit_rr(arg0, arg1, arg2);
    end;
end;
