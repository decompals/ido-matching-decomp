#ifndef SYMBOL_H
#define SYMBOL_H
procedure output_entry_point(arg0: integer); external;
function get_sym_kind(arg0: integer): integer; external;
procedure set_mtag(arg0: integer; var cur_mtag: integer); external;
function get_mtag(arg0: integer): integer; external;
#endif
