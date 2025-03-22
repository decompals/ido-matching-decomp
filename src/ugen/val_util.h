#ifndef VAL_UTIL_H
#define VAL_UTIL_H
procedure emit_val(arg0: integer; arg1: u8; var arg2: Valu; arg3: cardinal); external;
procedure emit_label_val(arg0: integer; arg1: integer; arg2: integer; arg3: cardinal); external;
function find_val_type(dtype: Datatype; size: cardinal): u8; external;
#endif /* VAL_UTIL_H */
