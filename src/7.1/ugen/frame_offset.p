#include "common.h"
#include "ugen.h"

type
unk_frame_offset_record = Record
    pad: array [0..40] of char;
    unk2C: integer;
end;

var
frame_size: integer;
reversed_stack: extern boolean;

function frame_offset(arg0: ^unk_frame_offset_record): integer;
begin
    if (frame_size = 0) then begin
        return arg0^.unk2C;
    end;
    if (reversed_stack) then begin
        return -(frame_size - arg0^.unk2C);
    end;
    return arg0^.unk2C + frame_size;
end;

function frame_offset1(arg0: integer): integer;
begin
    if (frame_size = 0) then begin
        return arg0;
    end;
    if (reversed_stack) then begin
        return -(frame_size - arg0);
    end;
    return arg0 + frame_size;
end;
