#ifndef IBUFFER_H
#define IBUFFER_H
type
    BinasmArray = array[1..1] of binasm;

var
    d_ptr: extern cardinal;
    old_d_ptr: extern cardinal;
    i_ptr: extern cardinal;
    old_i_ptr: extern cardinal;
    ibuffer: extern ^BinasmArray;
    ibuffer_size: extern cardinal;

#endif /* IBUFFER_H */
