#ifndef REG_MGR_H
#define REG_MGR_H
#include "cmplrs/binasm.h"
type
unk_rgmr_rec = Record
    pad: array [0..16#17] of char;
    temp_index: s8;
end;

function kind_of_register(arg0: registers): integer; external;
function content_of(arg0: registers): pointer; external;
function usage_count(reg: registers): u16; external; {Forward doesn't seem to be working?}
#endif /* REG_MGR_H */
