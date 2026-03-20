#ifndef REG_MGR_H
#define REG_MGR_H
type
    unk_rgmr_rec = Record
        pad: array [0..16#17] of char;
        temp_index: s8;
    end;

    RegKind = (
        /* 0 */ no_reg,
        /* 1 */ i_reg, 
        /* 2 */ f_reg,
        /* 3 */ d_reg,
        /* 4 */ x_reg, 
        /* 5 */ q_reg,
        /* 6 */ di_reg,
        /* 7 */ di_s_reg 
    );

    Register = Record;
        unk0: ^Tree;
        usage_count: u16;
        unk6: registers;
        reg_available: boolean;
        reg_kind: RegKind;
        unk9: registers;
    end;

function kind_of_register(arg0: registers): RegKind; external;
function content_of(arg0: registers): pointer; external;
function usage_count(reg: registers): u16; external;
procedure get_reg(arg0: registers; arg1: ^tree; arg2: u16); external;
procedure free_reg(arg0: registers); external;
procedure free_fp_reg(arg0: registers; arg1: RegKind); external;
function get_free_reg(arg0: ^tree; arg1: u16): registers; external;
function get_free_fp_reg(arg0: ^tree; arg1: RegKind; arg2: u16): registers; external;
procedure force_free_reg(arg0: registers); external;
procedure get_fp_reg(arg0: registers; arg1: ^tree; arg2: RegKind; arg3: u16); external;
function is_available(arg0: registers): boolean; external;
function free_reg_is_available(): boolean; external;
procedure remove_from_fp_free_list(arg0: registers; arg1: RegKind); external;
procedure remove_from_free_list(arg0: registers); external;
procedure move_to_end_fp_list(arg0: registers); external;
procedure move_to_end_gp_list(arg0: registers); external;
procedure init_regs(); external;
procedure check_no_used(); external;
procedure add_to_free_list(arg0: registers); external;
procedure inc_usage(arg0: registers; arg1: u16); external;
procedure get_fp_reg1(arg0: registers; arg1: ^tree; arg2: RegKind; arg3: u16); external;
procedure get_reg1(arg0: registers; arg1: ^tree; arg2: u16); external;
procedure fill_reg(reg: registers; contents: ^tree; usage_count: u16; reg_kind: RegKind); external;

#endif /* REG_MGR_H */
