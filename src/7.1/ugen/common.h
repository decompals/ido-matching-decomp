#ifndef COMMON_H
#define COMMON_H
type
	u16 = 0..65535 ;
	u8 =  0..255 of char;
	s8 = -128..127;

function new(size: cardinal; zero: integer): pointer; external;

#endif /* COMMON_H */
