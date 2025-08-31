#ifndef LIT_MGR_H
#define LIT_MGR_H
procedure reset_pool(); external;
procedure select_data_section(dataSize: integer); external;
procedure emit_list(list: ^Literal; vtype: ValType); external;
procedure output_pool(); external;
function new_lit(var val: Valu; labelno: integer): pointer; external;
procedure add_to_list_no_check(var lit: PLiteral; var val: Valu;  labelno: Integer); external;
function valu_equ(var val1: Valu; var val2: Valu): boolean; external;
function add_to_list(var lit: PLiteral; var val: Valu; labelno: integer): integer; external;
function add_to_pool(var u: Bcrec; labelno: integer): integer; external;
#endif /* LIT_MGR_H */
