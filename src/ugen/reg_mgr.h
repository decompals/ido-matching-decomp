#ifndef REG_MGR_H
#define REG_MGR_H
type
unk_rgmr_rec = Record
    pad: array [0..16#17] of char;
    temp_index: s8;
end;

function kind_of_register(arg0: registers): integer; external;
function content_of(arg0: registers): pointer; external;
function usage_count(reg: registers): u16; external;
procedure get_reg(a0: registers; a1: integer; a2: integer); external;
procedure free_reg(a0: registers); external;
function get_free_reg(a0: integer; a1: integer): registers; external;

#endif /* REG_MGR_H */
