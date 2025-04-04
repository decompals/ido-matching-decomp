#ifndef VAL_UTIL_H
#define VAL_UTIL_H

type
    ValType = (
        ValType_Null,
        ValType_Byte,
        ValType_Half,
        ValType_Word,
        ValType_Dword,
        ValType_Float,
        ValType_Double,
        ValType_Ascii,
        ValType_Label,
        ValType_Set
    );

procedure emit_val(arg0: integer; vtype: ValType; var value: Valu; rep: cardinal); external;
procedure emit_label_val(arg0: integer; symno: integer; value: integer; size: cardinal); external;
function find_val_type(dtype: Datatype; size: integer): ValType; external;

#endif /* VAL_UTIL_H */
