#ifndef TMP_MGR_H
#define TMP_MGR_H
function lookup_temp(index: u8): pointer; external;
function make_new_temp(area_size: integer): pointer; external;
function find_free_temp(area_size: integer): pointer; external;
function temp_offset(index: u8): integer; external;
function temp_usage_count(index: u8): u16; external;
function get_temp_area_size(): integer; external;
procedure init_temps(); external;
procedure spill_to_temp(arg0: registers; area_size: integer); external;
procedure free_temp(index: u8); external;
procedure set_temps_offset(offset: integer); external;
procedure gen_store(arg0: u8; temp_id: integer; arg2: integer); external; 
#endif /* TMP_MGR_H */
