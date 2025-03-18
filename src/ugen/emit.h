#ifndef EMIT_H
#define EMIT_H
procedure save_i_ptrs(); external;
procedure restore_i_ptrs(); external;
procedure init_ibuffer(); external;
function create_local_label(a0: integer): integer; external;
procedure emit_vers(); external;
procedure emit_rob(a0: asmcodes; a1: registers; a2: integer; a3: registers; a4: integer); external;
{ emit_rab }
{ emit_rrab }
procedure emit_rllb(a0: asmcodes; a1: registers; a2: integer; a3: integer; a4: registers); external;
procedure emit_ra(a0: asmcodes; a1: registers; a2: integer; a3: integer; a4: integer); external;
procedure emit_ri_(a0: asmcodes; a1: registers; a2: integer; a3: integer); external;
procedure emit_rii(a0: asmcodes; a1: registers; a2: Valu); external;
procedure emit_rfi(a0: asmcodes; a1: registers; var a2: Valu); external;
procedure emit_rrfi(a0: asmcodes; a1: registers; a2: integer); external;
procedure emit_rrr(a0: asmcodes; a1: registers; a2: registers; a3: registers); external;
procedure emit_rri_(a0: asmcodes; a1: registers; a2: registers; a3: integer; a4: integer); external;
procedure emit_rrri(a0: asmcodes; a1: registers; a2: registers; a3: integer); external;
procedure emit_rr(a0: asmcodes; a1: registers; a2: registers); external;
procedure emit_a(a0: asmcodes; a1: integer; a2: integer; a3: integer); external;
procedure emit_r(a0: asmcodes; a1: registers); external;
procedure emit_i(a0: asmcodes; a1: integer); external;
{ emit_rrl }
procedure emit_rrll(a0: asmcodes; a1: registers; a2: registers; a3: integer); external;
{ emit_rl }
procedure emit_rll(a0: asmcodes; a1: registers; a2: integer); external;
{ emit_l }
procedure emit_ll(a0: asmcodes; a1: integer); external;
{ emit_ril }
procedure emit_rill(a0: asmcodes; a1: registers; a2: integer; a3: integer); external;
procedure define_label(a0: integer); external;
procedure emit_itext(var a0: Valu); external;
procedure demit_itext(var a0: Valu); external;
procedure emit_dir0(a0: itype; a1: integer); external;
procedure emit_dir1(a0: itype; a1: integer; a2: integer); external;
procedure emit_dir2(a0: itype; a1: integer; a2: integer; a3: u16); external;
procedure emit_alias(a0: itype; a1: registers; a2: registers); external;
procedure emit_regmask(a0: itype; a1: integer; a2: integer); external;
procedure emit_loopno(a0: integer; a1: u16); external;
procedure emit_dir_ll(a0: integer; a1: integer); external;
procedure demit_rob_(a0: asmcodes; a1: registers; a2: integer; a3: registers; a4: integer); external;
procedure demit_ri(a0: asmcodes; a1: registers; a2: integer; a3: integer); external;
procedure demit_rr(a0: asmcodes; a1: registers; a2: registers); external;
procedure demit_a(a0: asmcodes; a1: integer; a2: integer); external;
procedure demit_regmask(a0: itype; a1: integer; a2: integer); external;
procedure demit_rrr(a0: asmcodes; a1: registers; a2: registers; a3: registers); external;
procedure demit_rri(a0: asmcodes; a1: registers; a2: registers; a3: integer); external;
procedure demit_rrll(a0: asmcodes; a1: registers; a2: registers; a3: integer); external;
procedure demit_i(a0: asmcodes; a1: integer); external;
procedure demit_ra(a0: asmcodes; a1: registers; a2: integer; a3: integer); external;
procedure demit_dir0(a0: itype; a1: integer); external;
procedure demit_dir1(a0: itype; a1: integer; a2: integer); external;
procedure demit_dir2(a0: itype; a1: integer; a2: integer; a3: u16); external;
procedure demit_edata(arg0: integer; arg1: integer; arg2: integer); external;
procedure demit_weakext(arg0: integer; arg1: integer); external;
procedure emit_cpload(a0: registers; a1: integer; a2: integer; a3: integer); external;
procedure ddefine_label(a0: integer); external;
procedure define_exception_label(a0: integer); external;
procedure append_i(var a0: binasm); external;
procedure append_d(var a0: binasm); external;
procedure clear_ibuffer(); external;
procedure emit_vreg(a0: registers; a1: integer; a2: integer); external;
procedure emit_pic(arg0: u8); external;
procedure demit_cpalias(a0: registers); external;
procedure emit_cpalias(a0: registers); external;
procedure emit_cpadd(a0: registers); external;
#endif /* EMIT_H */
