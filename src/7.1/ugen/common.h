#ifndef COMMON_H
#define COMMON_H
type
	u16 = 0..65535 ;
	u8 =  0..255 of char;
	s8 = -128..127;

ugen_report  = (
      Fix,
      Info,
      Warn,
      Error,
      Internal
);

mips_isa = (
    ISA_MIPS1,
    ISA_MIPS2,
    ISA_MIPS3
);


#endif /* COMMON_H */
