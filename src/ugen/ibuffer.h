#ifndef IBUFFER_H
#define IBUFFER_H
type
    BinasmArray = array[1..1] of binasm;

var
    d_ptr: cardinal;
    old_d_ptr: cardinal;
    i_ptr: cardinal;
    old_i_ptr: cardinal;
    ibuffer: ^BinasmArray;
    ibuffer_size: cardinal;

#endif /* IBUFFER_H */
