#ifndef TREE_H
#define TREE_H
#include "common.h"
#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"
#include "cmplrs/binasm.h"
type tree  = packed record
  /* 0x0 */  op1: ^tree;
  /* 0x4 */  op2: ^tree;
  /* 0x8 */  next: ^tree;
  /* 0xC */  prior: ^tree;
  /* 0x10 */ unk10: cardinal;
  /* 0x14 */ ref_count: u16;
  /* 0x16 */ unk16: u8;
  /* 0x17 */ unk17: u8;
  /* 0x18 */ unk18: u8;
  case integer of
    0 : (
        reg: first(registers)..last(registers);
        visited: boolean;
        ref_count2: u8;
      );
    1 : /* 0x20 */ ( u: BCrec);
    2:             (
                    unk1C: integer;
                    unk20: u16;
                    unk22: u16;
                    unk24: integer;
                    unk28: integer;
                    unk2C: integer;
                    unk30: integer;
                    unk34: integer;);
end;
#endif /* TREE_H */
