#ifndef LIT_MGR_H
#define LIT_MGR_H

procedure reset_pool(); external;
procedure output_pool(); external;
function add_to_pool(var u: Bcrec; labelno: integer): integer; external;

#endif /* LIT_MGR_H */
