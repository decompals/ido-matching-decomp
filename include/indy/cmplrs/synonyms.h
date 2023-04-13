/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991, 1990 MIPS Computer Systems, Inc.      |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 252.227-7013.  |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Avenue                               |
 * |         Sunnyvale, California 94088-3650, USA             |
 * |-----------------------------------------------------------|
 */
#ifndef __sgi
/* allow the synonyms after .weakext works! -- gb */
#define exception_dispatcher __exception_dispatcher
#define set_unhandled_exception __set_unhandled_exception
#define find_rpd __find_rpd
#define unwind __unwind
#define exc_setjmp __exc_setjmp
#define exc_resume __exc_resume

#define Continue _Continue
#define LastChance _LastChance
#define RtlRaiseStatus _RtlRaiseStatus
#define RtlRaiseException _RtlRaiseException
#define DispatchException _DispatchException
#define RtlUnwind _RtlUnwind
#define find_rtfunc __find_rtfunc
#define virtual_unwind __virtual_unwind
#define find_framePtr __find_framePtr
#define set_staticlink __set_staticlink
#define get_sp __get_sp
#endif


/* libm pragma weak defines for *.c files */
#define acosh  __acosh
#define asinh  __asinh
#define atanh __atanh
#define cbrt  __cbrt
#define exp__E  __exp__E
#define erf __erf
#define erfc __erfc
#define fexpm1  __fexpm1
#define expm1f  __expm1f
#define flog1p  __flog1p
#define log1pf  __log1pf
#ifndef __sgi
#define fmodf __fmodf
#endif
#define fpow  __fpow
#ifndef __sgi
#define powf  __powf
#endif
#define j0  __j0
#define j1  __j1
#define jn  __jn
#define gamma  __gamma
#define lgamma  __lgamma
#define asym  __asym
#define neg  __neg
#define pos  __pos
#define log__L __log__L
#define set_arg_val  __set_arg_val
#define gamma_err_val  __gamma_err_val
#define hypot_err_val  __hypot_err_val
#define set_res_val  __set_res_val
#define set_err_val  __set_err_val
#define set_exp_val  __set_exp_val
#define set_sinh_val  __set_sinh_val
#define y0  __y0
#define y1  __y1
#define yn  __yn
#define matherr  __matherr

/* added by sgi */
#define set_arg_val  __set_arg_val
#define gamma_err_val  __gamma_err_val
#define hypot_err_val  __hypot_err_val
#define set_res_val  __set_res_val
#define set_err_val  __set_err_val
#define set_exp_val  __set_exp_val
#define log1p __log1p
#define copysign __copysign
#define expm1 __expm1

