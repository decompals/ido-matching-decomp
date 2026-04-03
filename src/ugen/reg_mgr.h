#ifndef REG_MGR_H
#define REG_MGR_H

type
    RegKind = (
        no_reg,
        i_reg, { integer, gpr }
        f_reg, { float, fpr }
        d_reg, { double, fpr }
        x_reg, { extended ? unused }
        q_reg, { quad ? unused }
        di_reg, { first register for holding 64-bit value }
        di_s_reg { second register for holding 64-bit value }
        );

    Register = record;
        content: PTree;             { The tree node to which the register is assigned }
        usage_count: u16; 
        next: registers;            { Link in the register list }
        reg_available: boolean;     { is free to assign to a tree node }
        reg_kind: RegKind;
        dw_link: registers;
    end;

var
    regs: array [registers] of Register;

function kind_of_register(reg: registers): RegKind; external;
procedure init_regs(); external;
procedure fill_reg(reg: registers; content: PTree; usage_count: u16; reg_kind: RegKind); external;
procedure get_reg(reg: registers; node: PTree; usage_count: u16); external;
procedure get_reg1(reg: registers; node: PTree; usage_count: u16); external;
procedure get_fp_reg(reg: registers; node: PTree; kind: RegKind; usage_count: u16); external;
procedure get_fp_reg1(reg: registers; node: PTree; kind: RegKind; usage_count: u16); external;
function free_reg_is_available(): boolean; external;
function get_free_reg(node: PTree; usage_count: u16): registers; external;
function get_free_fp_reg(node: PTree; kind: RegKind; usage_count: u16): registers; external;
function content_of(reg: registers): PTree; external;
procedure inc_usage(reg: registers; usage_count: u16); external;
procedure free_reg(reg: registers); external;
procedure free_fp_reg(reg: registers; kind: RegKind); external;
procedure force_free_reg(reg: registers); external;
procedure add_to_free_list(reg: registers); external;
procedure add_to_fp_free_list(reg: registers; kind: RegKind); external;
procedure remove_from_free_list(reg: registers); external;
procedure remove_from_fp_free_list(reg: registers; kind: RegKind); external;
function is_available(reg: registers): boolean; external;
procedure check_no_used(); external;
function usage_count(reg: registers): u16; external;
procedure move_to_end_fp_list(reg: registers); external;
procedure move_to_end_gp_list(reg: registers); external;

#endif /* REG_MGR_H */
