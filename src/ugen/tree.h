#ifndef TREE_H
#define TREE_H
#include "common.h"
#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"
#include "cmplrs/binasm.h"
type
  Ptree = ^tree;
  tree = packed record
    { Pointer Fields }
    { 0x00 } op1: ^tree; { Left }
    { 0x04 } op2: ^tree; { Right }
    { 0x08 } next: ^tree; { Next }
    { 0x0C } prior: ^tree; { More like prev }
    
    { Data Fields }
    { 0x10 } unk10: 0..16#FFFFFF; { Node ID }
    { 0x14 } ref_count: u16;
    { 0x16 } unk16: u8;
    { 0x17 } mark: u8;
    { 0x18 } unk18: u8;
    { 0x19[1..7] } reg: first(registers)..last(registers);
    { 0x19[0] } visited: boolean;
    { 0x1A } ref_count2: u8;
    { 0x20 } u: Bcrec;
end;

#endif /* TREE_H */
