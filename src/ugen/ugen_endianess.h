#ifndef UGEN_ENDIANESS_H
#define UGEN_ENDIANESS_H
var
  lsb_first: boolean;

#define UGEN_LITTLE_ENDIAN lsb_first
#define UGEN_BIG_ENDIAN not lsb_first
#endif /* UGEN_ENDIANESS_H */
