#ifndef UGEN_H
#define UGEN_H
var
	(* Ugen options *)
	print_warnings: boolean;
	current_line: cardinal;
	debug_ugen: boolean;
	opcode_arch: boolean;
	glevel: u8;
	ignore_vreg: u8;
	olevel: u8;
	opt_cse: u8;
	opt_labels: boolean;
	opt_parms: u8;
	tail_call_opt: u8;


#endif /* UGEN_H */
