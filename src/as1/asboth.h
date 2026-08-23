#ifndef ASBOTH_H
#define ASBOTH_H
procedure p_assertion_failed(arg0: String; arg1: String; arg2: cardinal); external;
procedure PostError(arg0: error_str; arg1: GString; arg2: ErrorLevel); external;
function grow_array(var capacity_count: cardinal; new_count: integer; width: cardinal; ptr: pointer; clear_mem: boolean): pointer; external;
#endif /* ASBOTH_H */
