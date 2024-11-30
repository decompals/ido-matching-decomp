#ifndef REG_MGR_H
#define REG_MGR_H

type
unk_rgmr_rec = Record
    pad: array [0..16#17] of char;
    temp_index: s8;
end;

function kind_of_register(arg0: u8): integer; external;
function content_of(arg0: u8): pointer; external;
#endif /* REG_MGR_H */
