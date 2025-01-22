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


#endif /* COMMON_H */
