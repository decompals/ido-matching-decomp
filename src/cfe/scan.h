#ifndef SCAN_H
#define SCAN_H

int cpp_line_ptr(char* arg0, char* arg1, int arg2);
int scan();
struct ParseSymbol* mk_parse_symb(struct Symbol* symb, int id, int arg2);

#endif
