#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"

procedure abort();
begin
    halt(-1);
end;

procedure openstdout(var f: Text);
begin
end;

procedure opnstdin(var f: Text);
begin
end;

procedure openinput(var f: Text; fname: Filename);
begin
    reset(f, fname);
end;

procedure openoutput(var f: Text; fname: Filename);
begin
    rewrite(f, fname);
end;

function getclock(): integer;
begin
    getclock := clock(1);
end;

function eopage(var f: text): boolean;
begin
    eopage := f^ = chr(12);
end;

procedure readpage(var f: Text);
begin
    get(f);
end;

procedure printdate(var fil: text);
begin

end;

procedure printtime(var fil: text);
begin

end;
