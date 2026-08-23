{ Original name: frame.p }
#include "common.h"
#include "tree.h"

function frame_offset(node: Ptree): integer;
begin
    if frame_size = 0 then begin
        return node^.u.Offset;
    end;

    if reversed_stack then begin
        return -(frame_size - node^.u.Offset);
    end else begin
        return node^.u.Offset + frame_size;
    end
end;

function frame_offset1(offset: integer): integer;
begin
    if frame_size = 0 then begin
        return offset;
    end;

    if reversed_stack then begin
        return -(frame_size - offset);
    end else begin
        return offset + frame_size;
    end;
end;
