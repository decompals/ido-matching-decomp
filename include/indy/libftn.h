/*
  This file is used to define the interface to libftn for use by
  mfef77-generated C code.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <cmplrs/fio.h>
#include <cmplrs/host.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/times.h>
#include <ulocks.h>
#include <sys/param.h>
#include <isam.h>

typedef union
{       float pf;
        double pd;
        long double pld;
} ufloat;
typedef union
{       short is;
        signed char ic;         /* BN-8190. Change "char" to "signed char" */
        int ii;
#if defined(_LONGLONG)
        long long ill;
#else
        long ill;
#endif
} uinteger;

/*
  Constants used by the generated C code.
*/

extern int _con1;
extern int _con2;
extern int _con3;
extern int _con4;
extern int _con5;
extern int _con6;
extern int _con7;
extern int _con8;
extern int _con9;
extern int _con10;
extern int _con11;
extern int _con12;
extern int _con13;
extern int _con14;
extern int _con18;
extern int _con19;

extern long _lcon1;

/*
  Complex defnitions and routines (for frts.c).
*/

struct _cpx_float {float r, i;};
struct _cpx_double {double r, i;};
struct _cpx_long_double {long double r, i;};

extern struct _cpx_float _cpx_float(float r, float i);
extern struct _cpx_float _cpx_make_float_from_double(struct _cpx_double d);
extern struct _cpx_float _cpx_make_float_from_long_double(struct _cpx_long_double q);
extern struct _cpx_double _cpx_double(double r, double i);
extern struct _cpx_double _cpx_make_double_from_float(struct _cpx_float f);
extern struct _cpx_double _cpx_make_double_from_long_double(struct _cpx_long_double q);
extern struct _cpx_float _xnegate_float(struct _cpx_float a);
extern struct _cpx_double _xnegate_double(struct _cpx_double a);
extern struct _cpx_float _xadd_float(struct _cpx_float a, struct _cpx_float b);
extern struct _cpx_double _xadd_double(struct _cpx_double a, struct _cpx_double b);
extern struct _cpx_float _xsubtract_float(struct _cpx_float a, struct _cpx_float b);
extern struct _cpx_double _xsubtract_double(struct _cpx_double a, struct _cpx_double b);
extern struct _cpx_float _xmultiply_float(struct _cpx_float a, struct _cpx_float b);
extern struct _cpx_double _xmultiply_double(struct _cpx_double a, struct _cpx_double b);
extern struct _cpx_float _xdivide_float(struct _cpx_float a, struct _cpx_float b);
extern struct _cpx_double _xdivide_double(struct _cpx_double a, struct _cpx_double b);
extern struct _cpx_long_double _cpx_long_double(long double r, long double i);
extern struct _cpx_long_double _cpx_make_long_double_from_float(struct _cpx_float f);
extern struct _cpx_long_double _cpx_make_long_double_from_double(struct _cpx_double d);
extern struct _cpx_long_double _xnegate_long_double(struct _cpx_long_double a);
extern struct _cpx_long_double _xadd_long_double(struct _cpx_long_double a, struct _cpx_long_double b);
extern struct _cpx_long_double _xsubtract_long_double(struct _cpx_long_double a, struct _cpx_long_double b);
extern struct _cpx_long_double _xmultiply_long_double(struct _cpx_long_double a, struct _cpx_long_double b);
extern struct _cpx_long_double _xdivide_long_double(struct _cpx_long_double a, struct _cpx_long_double b);
extern int _xeq_float(struct _cpx_float a, struct _cpx_float b);
extern int _xeq_double(struct _cpx_double a, struct _cpx_double b);
extern int _xeq_long_double(struct _cpx_long_double a, struct _cpx_long_double b);
extern int _xne_float(struct _cpx_float a, struct _cpx_float b);
extern int _xne_double(struct _cpx_double a, struct _cpx_double b);
extern int _xne_long_double(struct _cpx_long_double a, struct _cpx_long_double b);

/*
  Character concatenation routine for mfef77 -> C.
*/
extern char *_concat(char *, int , int *, char *, int, char *, int);

/*
  Character concatenation routine.
*/
void s_cat(char *, char *rpp[], int rnp[], int *, int);
void s_cat2(char *, int, char *, char *, int, int);

/*
  Character compare routine.
*/
extern int32 s_cmp(register string, register string, fsize_t, fsize_t);

/*
  Character copy routine.
*/
extern void s_copy(char *, char *, int, int);

/*
  Routines for MAX/MIN variants.  TODO: inline in C using macros.
*/
extern int __jmax(int, ...);
extern long long __kmax(int, ...);
extern float __rmax(int, ...);
extern double __dmax(int, ...);
extern long double __qmax(int, ...);
extern float __ajmax0(int, ...);
extern float __akmax0(int, ...);
extern int __jmax1(int, ...);
extern long long __kmax1(int, ...);

extern int __jmin(int, ...);
extern long long __kmin(int, ...);
extern float __rmin(int, ...);
extern double __dmin(int, ...);
extern long double __qmin(int, ...);
extern float __ajmin0(int, ...);
extern float __akmin0(int, ...);
extern int __jmin1(int, ...);
extern long long __kmin1(int, ...);

/*
  Routines for exponentiation.
*/
extern short pow_hh(short *, short *);
extern int pow_ii(int *, int *);
extern int pow_il(int *, long long *);
extern long long pow_li(long long *, int *);
extern long long pow_ll(long long *, long long *);
extern int __powii(int *, int *);
extern int __powil(int, long long);
extern long long __powli(long long, int);
extern long long __powll(long long, long long);
extern float __powri(float, int);
extern float __powrl(float, long long);
extern double __powdi(double, int);
extern double __powdl(double, long long);

/*
  Standard libftn intrinsic routines.
*/
extern float r_acos(float *);
extern double d_acos(double *);
extern long double __qacos(long double);
extern long double __q_acos(long double *);
extern float r_acosd(float *);
extern double d_acosd(double *);
extern long double __q_acosd(long double *);
extern float r_asin(float *);
extern double d_asin(double *);
extern long double __qasin(long double);
extern long double __q_asin(long double *);
extern float r_asind(float *);
extern double d_asind(double *);
extern long double __q_asind(long double *);
extern float r_atan(float *);
extern double d_atan(double *);
extern long double __qatan(long double);
extern long double __q_atan(long double *);
extern float r_atand(float *);
extern double d_atand(double *);
extern long double __q_atand(long double *);
extern float r_atn2(float *, float *);
extern double d_atn2(double *, double *);
extern long double __qatan2(long double, long double);
extern long double __q_atn2(long double *, long double *);
extern float r_atn2d(float *, float *);
extern double d_atn2d(double *, double *);
extern long double __q_atn2d(long double *, long double *);
extern long double __qatan2d(long double, long double);
extern float r_cos(float *);
extern double d_cos(double *);
extern long double __qcos(long double);
extern long double __q_cos(long double *);
extern struct _cpx_float c_cos_(struct _cpx_float *);
extern struct _cpx_double z_cos_(struct _cpx_double *);
extern struct _cpx_long_double __cq_cos(struct _cpx_long_double *);
extern float r_cosd(float *);
extern double d_cosd(double *);
extern long double __q_cosd(long double *);
extern float r_cosh(float *);
extern double d_cosh(double *);
extern long double __qcosh(long double);
extern long double __q_cosh(long double *);
extern float r_exp(float *);
extern double d_exp(double *);
extern long double __qexp(long double);
extern long double __q_exp(long double *);
extern struct _cpx_float c_exp_(struct _cpx_float *);
extern struct _cpx_double z_exp_(struct _cpx_double *);
extern struct _cpx_long_double __cq_exp(struct _cpx_long_double *);
extern struct _cpx_long_double __cqexp(struct _cpx_long_double);
extern float r_log(float *);
extern double d_log(double *);
extern long double __qlog(long double);
extern long double __q_log(long double *);
extern struct _cpx_float c_log_(struct _cpx_float *);
extern struct _cpx_double z_log_(struct _cpx_double *);
extern struct _cpx_long_double __cq_log(struct _cpx_long_double *);
extern float r_lg10(float *);
extern double d_lg10(double *);
extern long double __qlog10(long double);
extern long double __q_lg10(long double *);
extern float r_sin(float *);
extern double d_sin(double *);
extern long double __qsin(long double);
extern long double __q_sin(long double *);
extern struct _cpx_float c_sin_(struct _cpx_float *);
extern struct _cpx_double z_sin_(struct _cpx_double *);
extern struct _cpx_long_double __cq_sin(struct _cpx_long_double *);
extern float r_sind(float *);
extern double d_sind(double *);
extern long double __q_sind(long double *);
extern float r_sinh(float *);
extern double d_sinh(double *);
extern long double __qsinh(long double);
extern long double __q_sinh(long double *);
extern float r_sqrt(float *);
extern double d_sqrt(double *);
extern long double __qsqrt(long double);
extern long double __q_sqrt(long double *);
extern struct _cpx_float c_sqrt_(struct _cpx_float *);
extern struct _cpx_double z_sqrt_(struct _cpx_double *);
extern struct _cpx_long_double __cq_sqrt(struct _cpx_long_double *);
extern float r_tan(float *);
extern double d_tan(double *);
extern long double __qtan(long double);
extern long double __q_tan(long double *);
extern float r_tand(float *);
extern double d_tand(double *);
extern long double __q_tand(long double *);
extern float r_tanh(float *);
extern double d_tanh(double *);
extern long double __qtanh(long double);
extern long double __q_tanh(long double *);
extern float r_abs(float *);
extern double d_abs(double *);
extern long double __qabs(long double);
extern long double __q_abs(long double *);
extern float c_abs_(struct _cpx_float *);
extern double z_abs_(struct _cpx_double *);
extern long double __cq_abs(struct _cpx_long_double *);
extern short h_abs(short *);
extern int i_abs(int *);
extern long long l_abs(long long *);
extern struct _cpx_float r_cnjg_(struct _cpx_float *);
extern struct _cpx_double d_cnjg_(struct _cpx_double *);
extern struct _cpx_long_double __cq_conjg(struct _cpx_long_double *);
extern float r_dim(float *, float *);
extern double d_dim(double *, double *);
extern long double __qdim(long double *, long double *);
extern short h_dim(short *, short *);
extern int i_dim(int *, int *);
extern long long l_dim(long long *, long long *);
extern double d_prod(float *, float *);
extern float r_imag(struct _cpx_float *);
extern double d_imagalt(struct _cpx_float *);
extern double d_imag(struct _cpx_double *);
extern long double __cq_imag(struct _cpx_long_double *);
extern short __iirint(float *);
extern int __jirint(float *);
extern long long __kirint(float *);
extern float r_int(float *);
extern double d_int(double *);
extern long double __qint(long double);
extern long double __q_int(long double *);
extern short __iidint(double *);
extern int __jidint(double *);
extern long long __kidint(double *);
extern short __iiqint(long double *);
extern int __jiqint(long double *);
extern long long __kiqint(long double *);
extern short h_mod(short *, short *);
extern int i_mod(int *, int *);
extern long long l_mod(long long *, long long *);
extern float r_mod(float *, float *);
extern double d_mod(double *, double *);
extern long double __qmod(long double, long double);
extern long double __q_mod(long double *, long double *);
extern short h_nint(float *);
extern int i_nint(float *);
extern long long l_nint(float *);
extern float r_nint(float *);
extern double d_nint(double *);
extern long double __qnint(long double);
extern long double __q_nint(long double *);
extern short h_dnnt(double *);
extern int i_dnnt(double *);
extern long long l_dnnt(double *);
extern short __iiqnnt(long double);
extern short __ii_qnnt(long double *);
extern int __jiqnnt(long double);
extern int __ji_qnnt(long double *);
extern long long __kiqnnt(long double);
extern long long __ki_qnnt(long double *);
extern float r_sign(float *, float *);
extern double d_sign(double *, double *);
extern long double __qsign(long double, long double);
extern long double __q_sign(long double *, long double *);
extern short h_sign(short *, short *);
extern int i_sign(int *, int *);
extern long long l_sign(long long *, long long *);
extern signed char btest_b(signed char *, signed char *);
extern short btest_h(short *, short *);
extern int btest_l(int *, int *);
extern long long btest_ll(long long *, long long *);
extern signed char and_b(signed char *, signed char *);
extern int and_l(int *, int *);
extern short and_h(short *, short *);
extern long long and_ll(long long *, long long *);
extern signed char bclr_b(signed char *, signed char *);
extern short bclr_h(short *, short *);
extern int bclr_l(int *, int *);
extern long long bclr_ll(long long *, long long *);
extern signed char bext_b(signed char *, signed char *, signed char *);
extern short bext_h(short *, short *, short *);
extern int bext_l(int *, int *, int *);
extern long long bext_ll(long long *, long long *, long long *);
extern signed char bset_b(signed char *, signed char *);
extern short bset_h(short *, short *);
extern int bset_l(int *, int *);
extern long long bset_ll(long long *, long long *);
extern signed char xor_b(signed char *, signed char *);
extern short xor_h(short *, short *);
extern int xor_l(int *, int *);
extern long long xor_ll(long long *, long long *);
extern signed char or_b(signed char *, signed char *);
extern short or_h(short *, short *);
extern int or_l(int *, int *);
extern long long or_ll(long long *, long long *);
extern signed char shft_b(signed char *, signed char *);
extern short shft_h(short *, short *);
extern int shft_l(int *, int *);
extern long long shft_ll(long long *, long long *);
extern signed char shftc_b(signed char *, signed char *, signed char *);
extern short shftc_h(short *, short *, short *);
extern int shftc_l(int *, int *, int *);
extern long long shftc_ll(long long *, long long *, long long *);
extern signed char not_b(signed char *);
extern short not_h(short *);
extern int not_l(int *);
extern long long not_ll(long long *);
extern short h_indx(char *, char *, int, int);
extern int i_indx(char *, char *, int, int);
extern long long l_indx(char *, char *, int, int);
extern short h_len(char *, int);
extern int i_len(char *, int);
extern long long l_len(char *, int);
extern int l_ge(char *, char *, int, int);
extern int l_gt(char *, char *, int, int);
extern int l_le(char *, char *, int, int);
extern int l_lt(char *, char *, int, int);
extern int mp_numthreads(void);
extern void mvbits_long(int *, int *, int *, int *, int *);
extern void mvbits_byte(signed char *, signed char *, signed char *, signed char *, signed char *);
extern void mvbits_short(short *, short *, short *, short *, short *);
extern void mvbits_long_long(long long *, long long *, long long *, long long *, long long *);
extern struct _cpx_float r_cis(float *);
extern struct _cpx_double d_cis(double *);
extern struct _cpx_long_double q_cis(long double *);

/* additional functions in libF77, many are probably not used */
typedef struct { float real, imag; } complex;
typedef struct { double dreal, dimag; } dcomplex;
typedef struct { long double qreal, qimag; } qcomplex;

/* extern long SGI_isetsp_(int *numargs, void* *local_fp) */
extern void __argmnt( int64 *__vcnt, int32 *chararg1, int32 *nargs );
extern void __getadr( int64 *__vcnt, int32 *n, long *iaddr);
extern void __getcln( int64 *__vcnt, int32 *n, int32 *iclen);
extern int32 __nullok( int64 *__vcnt, int32 *n, long *iaddr);
extern void __xetarg( int64 *__vcnt, int32 *n, int32 *len, void *iarg);
extern void __retour( int64 *__vcnt, int32 *nargs, ... );
extern void __cmplx1_q(complex *result, long double *u);
extern void __cmplx2_q(complex *result, long double *u, long double *v);
extern void __cmplx_cq(complex *result, qcomplex *u);
extern void __cq_add(qcomplex *result, qcomplex *x, qcomplex *y);
extern void __cq_div(qcomplex *, qcomplex *, qcomplex *);
extern int __cq_eq(qcomplex *x, qcomplex *y);
extern int32_t __cq_int(qcomplex *u);
extern void __cq_mul(qcomplex *, qcomplex *, qcomplex *);
extern int __cq_ne(qcomplex *x, qcomplex *y);
extern void __cq_neg(qcomplex *result, qcomplex *x);
extern long double __cq_real(qcomplex *u);
extern void __cq_sub(qcomplex *result, qcomplex *x, qcomplex *y);
extern void __dcmplx1_q(dcomplex *result, long double *u);
extern void __dcmplx2_q(dcomplex *result, long double *u, long double *v);
extern void __dcmplx_cq(dcomplex *result, qcomplex *u);
extern int32_t __j_qmax1(double  uhi, double  ulo, double  vhi, double  vlo);
extern int32_t __j_qmin1(double  uhi, double  ulo, double  vhi, double  vlo);
extern long double __pow_qi(double ahi, double alo, int n);
extern long double __pow_ql(double ahi, double alo, long long n);
extern long double __q_c(complex *u);
extern long double __q_dim( long double *u, long double *v );
extern long double __q_max1(double, double, double, double);
extern long double __q_min1(double, double, double, double);
extern long double __q_prod(double *u, double *v);
extern long double __qprod(double, double);
extern long double __q_z(dcomplex *u);
extern void __qcmplx1_d(qcomplex *result, double *u);
extern void __qcmplx1_i(qcomplex *result, short *u) ;
extern void __qcmplx1_j(qcomplex *result, int *u);
extern void __qcmplx1_k(qcomplex *result, long long *u) ;
extern void __qcmplx1_q(qcomplex *result, long double *u);
extern void __qcmplx1_r(qcomplex *result, float *u);
extern void __qcmplx2_d(qcomplex *result, double *u, double *v);
extern void __qcmplx2_i(qcomplex *result, short *u, short *v);
extern void __qcmplx2_j(qcomplex *result, int *u, int *v);
extern void __qcmplx2_k(qcomplex *result, long long *u, long long *v);
extern void __qcmplx2_q(qcomplex *result, long double *u, long double *v);
extern void __qcmplx2_r(qcomplex *result, float *u, float *v);
extern void __qcmplx_c(qcomplex *result, complex *u);
extern void __qcmplx_z(qcomplex *result, dcomplex *u);
extern void argmnt_(int32 *narg ) ;
extern void b_pad(char *, int32);
extern void c_cos(complex *r, complex *z);
extern void c_div(complex *, complex *, complex *);
extern complex c_div_(complex *, complex *);
extern void c_exp(complex *r, complex *z);
extern void c_log(complex *r, complex *z);
extern void c_sin(complex *r, complex *z);
extern void c_sqrt(complex *r, complex *z);
extern void check_vararg_error(void);
extern void d_cnjg(dcomplex *r, dcomplex *z);
extern double derf_(double *x);
extern double derfc_(double *x);
extern void ef1asc_(char *a, int32 *la, char *b, int32 *lb);
extern int32 ef1cmc_(char *a, int32 *la, char *b, int32 *lb);
extern float erf_(float *x);
extern float erfc_(float *x);
extern void f_abort(void);
extern void free_varg_();
extern void getadr_(int32 *argno, int32 *argadr );
extern int16 h_lentrim(string s, fsize_t len);
extern int16 hl_ge(string a, string b, fsize_t la, fsize_t lb);
extern int16 hl_gt(string a, string b, fsize_t la, fsize_t lb);
extern int16 hl_le(string a, string b, fsize_t la, fsize_t lb);
extern int16 hl_lt(string a, string b, fsize_t la, fsize_t lb);
extern int32 i_lentrim(string s, fsize_t len);
extern int32 * init_arg_();
extern int32 irand_(void);
extern char * kai_mhalloc( size_t len );
extern int64 l_lentrim(string s, fsize_t len);
extern int32 lnblnk_(string s, fsize_t len) ;
extern int main(int argc,char **argv,char **arge);
extern clock_t mclock_(void);
extern int32 narcar_(int32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern int32 nargum_(uint32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern int32 nartab_(uint32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern int32 nchara_(int32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern int32 nretca_(int32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern int32   ntabca_(int32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern int32 ntabch_(int32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern int32 nullok_(int32 *argno, int32 *adr);
extern void outstr_(string s, fsize_t n);
extern struct _cpx_float pow_cif_(struct _cpx_float *a, int32 *b);
extern struct _cpx_float pow_clf_(struct _cpx_float *a, int64 *b);
extern double_t pow_dd(double_t *ap, double_t *bp);
extern struct _cpx_double pow_zif_(struct _cpx_double *a, int32 *b) ;
extern struct _cpx_double pow_zlf_(struct _cpx_double *a, int64 *b);
extern struct _cpx_double pow_zz_(struct _cpx_double *a, struct _cpx_double *b);
extern void r_cnjg(complex *r, complex *z);
extern void reset_comargs__() ;
extern void retour_(int32 *arg1,  ... );
extern uint32 risc_return_(uint32 *);
extern void rretrg_(uint32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern void rretur_(uint32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern uint32 rretvr_(uint32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern string s_cat_kai(string strings[], fsize_t lengths[], int32 count, fsize_t *result_len);
extern void s_cat_tmp(char **lp,char *rpp[],int32 rnp[],int32 *np,int32 *ntemp);
extern void s_paus(string s, fsize_t n);
extern void s_rnge(char *varn, int32 offset, char *procn, int32 line)      ;
extern void s_srng(char *varn, int32 lower, int32 upper, char *procn, int32 line);
extern void s_stop(string s, fsize_t n);
extern int32 set_arg_arr(uint32 **,uint32 *,uint32 *);
extern void set_args(uint32 *, uint32 *);
extern void set_varg_();
extern void subout(char *varn, int32 offset, char *procn, int32 line);
extern void tabarg_(uint32 *father_frame, int32 dum1, int32 dum2, int32 dum3);
extern void xetarg_(int32 *argno, int32 *len, char *buff );
extern double_t z_abs(dcomplex *);
extern void z_cos(dcomplex *, dcomplex *);
extern void z_div(dcomplex *, dcomplex *, dcomplex *);
extern dcomplex z_div_(dcomplex *, dcomplex *);
extern void z_exp(dcomplex *, dcomplex *);
extern void z_log(dcomplex *, dcomplex *);
extern void z_sin(dcomplex *, dcomplex *);
extern void z_sqrt(dcomplex *, dcomplex *);

extern float __c8abs(float, float);
extern complex __ccos(float, float);
extern complex __cdiv(float, float, float, float);
extern complex __cexp(float, float);
extern complex __clog(float, float);
extern complex __csin(float, float);
extern complex __csqrt(float, float);
extern long double __cqabs(long double, long double);
extern qcomplex __qconjg(long double, long double);
extern qcomplex __cqcos(long double, long double);
extern qcomplex __cqdiv(long double, long double, long double, long double);
extern qcomplex __cqlog(long double, long double);
extern qcomplex __cqpow(long double, long double, long double, long double);
extern qcomplex __cqsin(long double, long double);
extern qcomplex __cqsqrt(long double, long double);
extern dcomplex __dconjg(double, double);
extern complex __powcc(float, float, float, float);
extern complex __powci(float, float, int);
extern complex __powcl(float, float, long long);
extern qcomplex __powcqi(long double, long double, int);
extern qcomplex __powcql(long double, long double, long long);
extern dcomplex __powzi(double, double, int);
extern dcomplex __powzl(double, double, long long);
extern dcomplex __powzz(double, double, double, double);
extern complex __rconjg(float, float);
extern double __zabs(double, double);
extern dcomplex __zcos(double, double);
extern dcomplex __zdiv(double, double, double, double);
extern dcomplex __zexp(double, double);
extern dcomplex __zlog(double, double);
extern dcomplex __zsin(double, double);
extern dcomplex __zsqrt(double, double);

extern void date_vms(void *);
extern void idate_(void *);
extern void idate_short(short *, short *, short *);
extern void idate_long(int *, int *, int *);
extern void idate_long_long(long long *, long long *, long long *);
extern void exit_noargs(void);
extern void exit_short(short *);
extern void exit_long(int *);
extern void exit_long_long(long long *);
extern float secnds_vms(float *);
extern double dsecnds_vms(double *);
extern void time_vms(void *);
extern void errsns_short(short *, short *, short *, short *, short *);
extern void errsns_long(int *, int *, int *, int *, int *);
extern void errsns_long_long(long long *, long long *, long long *, long long *, long long *);

/* functions in libI77 */
extern ftnint __f77_f_back(alist *);
extern ftnint f_back64(alist *);
extern ftnint __f77_f_back64(alist *);
extern ftnint __f77_f_back64_mp(alist *);
extern void get_cilist64( cilist64 *a64, cilist *a );
extern void get_inlist64(inlist64 *dst, inlist *src);
extern void get_icilist64(icilist64 *dst, icilist *src);
extern void get_olist64(olist64 *dst, olist *src);
extern int f_clos(cllist *);
extern int f_clos64(cllist *);
extern int f_clos64_mp(cllist *);
extern ftnint t_runc(unit *, flag);
extern int s_rdfe(cilist *);
extern int s_rdfe_mp(cilist *, unit **);
extern int s_wdfe(cilist *);
extern int s_wdfe_mp(cilist *, unit **);
extern int e_rdfe();
extern int e_rdfe_mp(unit **); 
extern int e_wdfe();
extern int e_wdfe_mp(unit **);
extern int s_rdfe64(cilist64 *);
extern int s_rdfe64_mp(cilist64 *, unit **);
extern int s_wdfe64(cilist64 *);
extern int s_wdfe64_mp(cilist64 *, unit **);
extern int e_rdfe64(); 
extern int e_rdfe64_mp(unit **);
extern int e_wdfe64();
extern int e_wdfe64_mp(unit **);
extern int y_rsk(unit *);
extern int yrd_SL(unit *);  
extern int y_ungetc(unit *, int);
extern int y_getc(unit *);  
extern int y_gets(unit *, char *, int, char);
extern int y_putc(unit *, XINT, char, char *);
extern int y_rev(unit *); 
extern int y_end(unit *);
extern int y_wSL(unit *); 
extern int   f_find(flist *);
extern int   s_rdue(cilist *);
extern int   s_wdue(cilist *);
extern int   e_rdue(void);
extern int   e_wdue(void);
extern int   f_find_mp(flist *);
extern int   s_rdue_mp(cilist *, unit **);
extern int   s_wdue_mp(cilist *, unit **);
extern int   e_rdue_mp(unit **);
extern int   e_wdue_mp(unit **);
extern int   f_find64(flist64 *);
extern int   s_rdue64(cilist64 *);
extern int   s_wdue64(cilist64 *);
extern int   e_rdue64(void);
extern int   e_wdue64(void);
extern int   f_find64_mp(flist64 *);
extern int   s_rdue64_mp(cilist64 *, unit **);
extern int   s_wdue64_mp(cilist64 *, unit **);
extern int   e_rdue64_mp(unit **);
extern int   e_wdue64_mp(unit **);
extern char *ecvt_mp(double, int, int *, int *, char *);
extern char *fcvt_mp(double, int, int *, int *, char *);
extern char *qecvt_mp(long double, int, int *, int *, char *);
extern char *qfcvt_mp(long double, int, int *, int *, char *);
extern int  f_end(alist *);
extern int  f_end_mp(alist *);
extern int  f_end64(alist *);
extern int  f_end64_mp(alist *);
extern void f77fatal(unit *, int, char *);
extern void f_init(void);
extern int  f77canseek(FILE *);
extern void s_abort(int);
extern void perror_(char *, int);
extern void gerror_(char *, int);
extern int _fio_du_open(char *, char *);
extern int _fio_du_write(unit *,char *, XINT, XINT64, int);
extern int _fio_du_flush(int);
extern int _fio_du_read(unit *,char *, XINT, XINT64, int);
extern int _fio_du_close(int);
extern int   pars_f(unit *, char *);
extern int   ne_d(unit *, char *, char **);
extern int   e_d(unit *, char *, char **);
extern int   op_gen(unit *, int, long, long, int);
extern int   en_fio(unit **);
extern int   do_fio(ftnint *, ftnint *, char *, ftnlen);
extern int   do_fio_1dim(ftnint *, char *, flex *, ftnint *,ftnint *, ftnint *,ftnlen, ftnlen);
extern int   do_fio_mp(ftnint *, ftnint *, char *, unit **, ftnlen);
extern int      test_type(int op, ftnint type);
extern void  fmt_bg(unit *);
extern char  *ap_end(unit *, char *);
extern int   do_fioi4(unsigned int);
extern int   do_fioi8(long long);
extern int   do_fior4(float);
extern int   do_fio8(double);
extern int   do_f4f8(void *, ftnlen);
extern int   do_fioi4_mp(unsigned int, unit *);
extern int   do_fioi8_mp(long long, unit *);
extern int   do_fior4_mp(float, unit *);
extern int   do_fio8_mp(double, unit *);  
extern int   do_f4f8_mp(ftnint *, void *, unit *, ftnlen);
extern int   do_fio64(ftnint *, XINT *, char *, ftnlen);
extern int   do_fio64_1dim(ftnint *, char *, flex *, XINT *,XINT *, XINT *, ftnlen, ftnlen); 
extern int   do_fio64_mp(ftnint *, XINT *, char *, unit **, ftnlen);
extern int   do_fioxa4(char *, XINT);
extern int   do_fioxa8(char *, XINT);
extern int   do_fioxh1(char *, XINT, XINT);
extern int   do_fioxi1(char *, XINT);
extern int   do_fioxi2(char *, XINT);
extern int   do_fioxi4(char *, XINT);
extern int   do_fioxi8(char *, XINT);
extern int   do_fioxl1(char *, XINT);
extern int   do_fioxl2(char *, XINT);
extern int   do_fioxl4(char *, XINT);
extern int   do_fioxl8(char *, XINT);
extern int   do_fioxr4(char *, XINT);
extern int   do_fioxr8(char *, XINT);
extern int   do_fioxr16(char *, XINT);
extern int   do_fioxc4(char *, XINT);
extern int   do_fioxc8(char *, XINT);
extern int   do_fioxc16(char *, XINT);
extern int   do_fioxa4v(ftnint);
extern int   do_fioxa8v(ftnll);
extern int   do_fioxh1v(char);
extern int   do_fioxi1v(char);
extern int   do_fioxi2v(short);
extern int   do_fioxi4v(ftnint);
extern int   do_fioxi8v(ftnll);
extern int   do_fioxl1v(char);
extern int   do_fioxl2v(short);
extern int   do_fioxl4v(ftnint);
extern int   do_fioxl8v(ftnll);
extern int   do_fioxr4v(float);
extern int   do_fioxr8v(double);
extern int   do_fioxr16v(long double);
extern int   do_fioxc4v(float, float);
extern int   do_fioxc8v(double, double);
extern int   do_fioxc16v(long double, long double);
extern char *icvt(int, int *, int *, char *);
extern char *llcvt(ftnll , int *, int *, char *);
extern char *ozcvt(unsigned char *, int , int *, int, char * );
extern char *bcvt(unsigned char *, int , int *, char * );
extern int idxopen(unit *, char *, int, flag);
extern int idxclose(unit *, flag);
extern int idxread(unit *);     
extern void s_idxwrite(unit *);
extern int idxwrite(unit *);
extern int idxrewrite(unit *);
extern int dokey(int, int);
extern int f_del(alist *); 
extern int f_del_mp(alist *a);
extern int f_unl(alist *);
extern int f_unl_mp(alist *a);
extern int s_xsue(cilist *);
extern int s_xsue_mp(cilist *, unit **);
extern int s_xsle(cilist *);
extern int s_xsle_mp(cilist *, unit **);
extern int s_xsfe(cilist *);
extern int s_xsfe_mp(cilist *, unit **);
extern int e_xsue(void);
extern int e_xsue_mp(unit **);
extern int f_del64(alist *);
extern int f_del64_mp(alist *a); 
extern int f_unl64(alist *);    
extern int f_unl64_mp(alist *a);
extern int s_xsue64(cilist64 *);
extern int s_xsue64_mp(cilist64 *, unit **);
extern int s_xsle64(cilist64 *);
extern int s_xsle64_mp(cilist64 *, unit **);
extern int s_xsfe64(cilist64 *);
extern int s_xsfe64_mp(cilist64 *, unit **);
extern int e_xsue64(void);
extern int e_xsue64_mp(unit **);
extern int z_ungetc(unit *, int);
extern int z_getc(unit *);
extern int z_gets(unit *, char *, int, char);
extern int z_putc(unit *, XINT, char, char *);
extern int z_wnew(unit *);
extern int z_rnew(unit *);
extern int s_wsfi(icilist *);
extern int s_wsfi_mp(icilist *, unit**);
extern int z_rSL(unit *);
extern int z_wSL(unit *);
extern int y_ierr(unit *);
extern int e_rsfi();
extern int e_wsfi();
extern int e_rsfi_mp(unit **);
extern int e_wsfi_mp(unit **);
extern int s_wsfi64(icilist64 *);
extern int s_wsfi64_mp(icilist64 *, unit**);
extern int e_rsfi64();
extern int e_wsfi64();
extern int e_rsfi64_mp(unit **); 
extern int e_wsfi64_mp(unit **);
extern int c_si(icilist64 *, unit *);
extern int f_inqu0(inlist *, int *);
extern int f_inqu0_mp(inlist *, int *);
extern int f_inqu064(inlist64 *, int *);
extern int f_inqu064_mp(inlist64 *, int *);
extern int f_inqu064x (inlist64 *, XINT);
extern int setcilist(cilist *, int, char *, int, int, int);
extern int setolist(olist *, int, char *, char *, char *, int, char *, int);
extern int stcllist(cllist *, int, char *, int);
extern int setalist(alist *, int, int); 
extern int setcilist64(cilist64 *, ftnint, char *, XINT64, int, int);
extern int setolist64(olist64 *, ftnint, char *, char *, char *,int,char *,int);
extern int s_wsle(cilist *);
extern int s_wsle_mp(cilist *, unit **);
extern int s_wsli(icilist *);
extern int s_wsli_mp(icilist *, unit **);
extern int e_wsle(void);
extern int e_wsle_mp(unit **);
extern int e_xsle(void);
extern int e_xsle_mp(unit **);  
extern int e_wsli(void);
extern int e_wsli_mp(void);
extern int t_putc(unit *, XINT, char, char *);
extern int lwrt_I(unit *, uinteger *, int, int, int);
extern int lwrt_L(unit *, uinteger *, int, int, int);
extern int lwrt_A(unit *, char *, ftnlen, int);
extern int lwrt_G(unit *, ufloat *, int, int, int, int, int, int, int);
extern int lwrt_C(unit *, ufloat *, ufloat *, int, int, int, int, int, int);
extern int l_write(unit *, XINT *, flex *, ftnlen, ftnint);
extern int do_Lio(ftnint *, ftnint *, flex *, ftnlen);
extern int do_Lio_1dim(ftnint *, flex *, flex *, ftnint *, ftnint *, ftnint *, ftnlen, ftnlen);
extern int __kai_do_lio(ftnint *, ftnint *, flex *, ftnlen);
extern int __kai_do_lio_mp(ftnint *, ftnint *, flex *, unit **, ftnlen);
extern int do_Lio_mp(ftnint *, ftnint *, flex *, unit **, ftnlen);
extern int do_lio(ftnint *type, ftnint *number, flex *ptr, ftnlen len);
extern int __kai_do_lio_1dim(ftnint *, flex *, flex *, ftnint *,ftnint *, ftnint *, ftnlen, ftnlen);
extern int c_le(cilist64 *, unit**);
extern void c_li(icilist64 *);
extern int s_wsle64(cilist64 *a);
extern int s_wsle64_mp(cilist64 *a, unit **fu);
extern int s_wsli64(icilist64 *a);
extern int s_wsli64_mp(icilist64 *a, unit **fu);
extern int do_Lio64(ftnint *type, XINT *number, flex *ptr, ftnlen len);
extern int do_lio64(ftnint *type, XINT *number, flex *ptr, ftnlen len);
extern int do_Lio64_1dim(ftnint *type, flex *ptr,flex *do_idx, XINT *lb, XINT *ub, XINT *step,ftnlen len, ftnlen idxlen);
extern int __kai_do_lio64_1dim(ftnint *type, flex *ptr,flex *do_idx, XINT *lb, XINT *ub, XINT *step,ftnlen len, ftnlen idxlen);
extern int do_Lio64_mp(ftnint *type, XINT *number, flex *ptr,unit **fu, ftnlen len);
extern int __kai_do_lio64(ftnint *type, XINT *number, flex *ptr, ftnlen len);
extern int __kai_do_lio64_1dim(ftnint *type, flex *ptr,flex *do_idx, XINT *lb,XINT *ub, XINT *step,ftnlen len, ftnlen idxlen);
extern int __kai_do_lio64_mp(ftnint *type, XINT *number, flex *ptr,unit **fu, ftnlen len);
extern int   do_lioxa4(char *, XINT);
extern int   do_lioxa8(char *, XINT);
extern int   do_lioxh1(char *, XINT, XINT);
extern int   do_lioxi1(char *, XINT);
extern int   do_lioxi2(char *, XINT);
extern int   do_lioxi4(char *, XINT);
extern int   do_lioxi8(char *, XINT);
extern int   do_lioxl1(char *, XINT);
extern int   do_lioxl2(char *, XINT);
extern int   do_lioxl4(char *, XINT);
extern int   do_lioxl8(char *, XINT);
extern int   do_lioxr4(char *, XINT);
extern int   do_lioxr8(char *, XINT);
extern int   do_lioxr16(char *, XINT);
extern int   do_lioxc4(char *, XINT);
extern int   do_lioxc8(char *, XINT);
extern int   do_lioxc16(char *, XINT);
extern int   do_lioxa4v(ftnint);
extern int   do_lioxa8v(ftnll);
extern int   do_lioxh1v(char);
extern int   do_lioxi1v(char);
extern int   do_lioxi2v(short);
extern int   do_lioxi4v(ftnint);
extern int   do_lioxi8v(ftnll);
extern int   do_lioxl1v(char);
extern int   do_lioxl2v(short);
extern int   do_lioxl4v(ftnint);
extern int   do_lioxl8v(ftnll);
extern int   do_lioxr4v(float);
extern int   do_lioxr8v(double);
extern int   do_lioxr16v(long double);
extern int   do_lioxc4v(float, float);
extern int   do_lioxc8v(double, double);
extern int   do_lioxc16v(long double, long double);
extern int e_wsle64(void);
extern int e_wsle64_mp(unit **);
extern int e_xsle64(void);
extern int e_xsle64_mp(unit **);  
extern int e_wsli64(void);
extern int e_wsli64_mp(void);
extern int t_gets(unit *, char *, int, char);
extern int t_getc(unit *);
extern int t_ungetc(unit *, int);
extern int e_rsle(void);
extern int e_rsle_mp(unit **);
extern int e_rsli(void);
extern int e_rsli_mp(unit **);
extern int l_read(unit *, XINT *, flex *, ftnlen, ftnint);
extern int s_rsle(cilist *);
extern int s_rsle_mp(cilist *, unit**);
extern int s_rsli(icilist *);
extern int s_rsli_mp(icilist *, unit **);
extern int s_rsle64(cilist64 *a);
extern int s_rsle64_mp(cilist64 *a, unit **fu);
extern int s_rsli64(icilist64 *a);
extern int s_rsli64_mp(icilist64 *a, unit **fu);
extern int e_rsle64(void);
extern int e_rsle64_mp(unit **);
extern int e_rsli64(void);
extern int e_rsli64_mp(unit **);
extern int s_rsne(cilist *);
extern int s_rsNe(cilist *);
extern int s_rsNe_mp(cilist *, unit **);
extern int s_wsne(cilist *);
extern int s_wsNe(cilist *);
extern int s_wsne_mp(cilist *pnlarg, unit **fu);
extern int s_wsNe_mp(cilist *, unit **);
extern int __kai_s_rsne(cilist *);
extern int __kai_s_wsne(cilist *);
extern int __kai_s_rsne_mp(cilist *, unit **);
extern int __kai_s_wsne_mp(cilist *, unit **);
extern int s_rsNe64(cilist64 *pnlarg);
extern int s_rsNe64_mp(cilist64 *pnlarg, unit **fu);
extern int s_wsNe64(cilist64 *pnlarg);
extern int s_wsNe64_mp(cilist64 *pnlarg, unit **fu);
extern int __kai_s_rsne64(cilist64 *pnlarg);
extern int __kai_s_rsne64_mp(cilist64 *pnlarg, unit **fu);
extern int __kai_s_wsne64(cilist64 *pnlarg);
extern int __kai_s_wsne64_mp(cilist64 *pnlarg, unit **fu);
extern int f_open1(olist *, int *);
extern int f_open0(olist *, int *);
extern int fk_open(int, int, ftnint);
extern int absent(char *, int);
extern int inc_var(ftnintu *, ftnint, int);
extern int set_var(ftnintu *, ftnint, int, long long);
extern int f_dfnf(struct dfnf_struct *);
extern int f_dfnf1(struct dfnf_struct *, ftnint *);
extern int f_duped(olist64 *, unit *, unit **);
extern int f_open064(olist64 *a, int *mask);
extern int f_open064_mp(olist64 *a, int *mask);
extern int f_open064x (olist64 *a, XINT xmask);
extern int s_rsfi(icilist *);
extern int s_rsfi_mp(icilist *, unit **);
extern int __s_rsfi_com(icilist64 *a, unit **fu, int f90sw);
extern int rd_ed(unit *, struct f77syl *, char *, ftnlen, ftnint);
extern int rd_ned(unit *, struct f77syl *);
extern int rd_I(unit *, uinteger *, long, ftnlen);
extern int rd_OZ(unit *, unsigned char *, long, ftnlen, int);
extern int rd_Q(unit *, uinteger *, ftnlen);
extern int rd_L(unit *, uinteger *, long, ftnlen);
extern int rd_F(unit *, ufloat *, long, long, ftnlen);
extern int rd_A(unit *, char *, ftnlen);
extern int rd_AW(unit *, char *, long, ftnlen);
extern int rd_H(unit *, long);
extern int rd_POS(unit *, char *);
extern int rd_B(unit *ftnunit, unsigned char *n, long w, ftnlen len);
extern int s_rsfi64(icilist64 *a);
extern int s_rsfi64_mp(icilist64 *a, unit **fu);
extern int f_rew(alist *);
extern int f_rew64(alist *a);
extern int f_rew64_mp(alist *a);
extern int s_rsfe(cilist *);
extern int s_rsfe_mp(cilist *, unit **);
extern int xrd_SL(unit *);
extern int x_ungetc(unit *, int);
extern int x_gets(unit *, char *, int, char);
extern int x_getc(unit *);
extern int x_endp(unit *);
extern int x_rev(unit *);
extern int s_rsfe64(cilist64 *a);
extern int s_rsfe64_mp(cilist64 *a, unit **fu);
extern int e_rsfe(void); 
extern int e_rsfe_mp(unit **); 
extern int c_sfe(cilist64 *a, unit **fu);
extern int e_wsfe(void);
extern int e_wsfe_mp(unit **);
extern int e_xsfe(void);
extern int e_xsfe_mp(unit **);
extern int e_wsue(void);
extern int e_wsue_mp(unit **);
extern int e_rsfe64(void);
extern int e_rsfe64_mp(unit **);
extern int e_wsfe64(void);
extern int e_wsfe64_mp(unit **);
extern int e_xsfe64(void);
extern int e_xsfe64_mp(unit **);
extern int e_wsue64(void);
extern int e_wsue64_mp(unit **);
extern int do_ui(unit *, XINT *, char *, ftnlen);
extern int s_rsue(cilist *);
extern int s_rsue_mp(cilist *, unit**);
extern int s_wsue(cilist *);
extern int s_wsue_mp(cilist *, unit **);
extern int e_rsue(void);
extern int e_rsue_mp(unit**);
extern int unf_position(FILE *, unit *);
extern int wsue(cilist64 *a, unit **fu);
extern int c_sue(cilist64 *a, unit **fu);
extern int s_rsue64(cilist64 *a);
extern int s_rsue64_mp(cilist64 *a, unit **fu);
extern int s_wsue64(cilist64 *a);
extern int s_wsue64_mp(cilist64 *a, unit **fu); 
extern int e_rsue64(void);  
extern int e_rsue64_mp(unit**);
extern int flush_(ftnint *);
extern int do_us(unit *, XINT *, char *, ftnlen);
extern int s_usrecsize(int);
extern int do_uio_1dim(char *, flex *, ftnint *, ftnint *, ftnint *, ftnlen, ftnlen);
extern void set_do_idx( flex *idx, ftnlen len, ftnll val );
extern int do_uio(ftnint *, char *, ftnlen);
extern int do_uio_mp(ftnint *, char *, unit **, ftnlen);
extern int do_ud(unit *, XINT *, char *, ftnlen);
extern int check_buflen(unit *, XINT);
extern int do_uio64_1dim(char *, flex *, XINT *, XINT *, XINT *, ftnlen, ftnlen);
extern int do_uio64(XINT *number, char *ptr, ftnlen len);
extern int do_uio64_mp(XINT *number, char *ptr, unit **fu, ftnlen len);
extern int   do_uioxa4(char *, XINT);
extern int   do_uioxa8(char *, XINT);
extern int   do_uioxh1(char *, XINT, XINT);
extern int   do_uioxi1(char *, XINT);
extern int   do_uioxi2(char *, XINT);
extern int   do_uioxi4(char *, XINT);
extern int   do_uioxi8(char *, XINT);
extern int   do_uioxl1(char *, XINT);
extern int   do_uioxl2(char *, XINT);
extern int   do_uioxl4(char *, XINT);
extern int   do_uioxl8(char *, XINT);
extern int   do_uioxr4(char *, XINT);
extern int   do_uioxr8(char *, XINT);
extern int   do_uioxr16(char *, XINT);
extern int   do_uioxc4(char *, XINT);
extern int   do_uioxc8(char *, XINT);
extern int   do_uioxc16(char *, XINT);
extern int   do_uioxa4v(ftnint);
extern int   do_uioxa8v(ftnll);
extern int   do_uioxh1v(char);
extern int   do_uioxi1v(char);
extern int   do_uioxi2v(short);
extern int   do_uioxi4v(ftnint);
extern int   do_uioxi8v(ftnll);
extern int   do_uioxl1v(char);
extern int   do_uioxl2v(short);
extern int   do_uioxl4v(ftnint);
extern int   do_uioxl8v(ftnll);
extern int   do_uioxr4v(float);
extern int   do_uioxr8v(double);
extern int   do_uioxr16v(long double);
extern int   do_uioxc4v(float, float);
extern int   do_uioxc8v(double, double);
extern int   do_uioxc16v(long double, long double);
extern int g_char(char *, ftnlen, char *);
extern int b_char(char *, char *, ftnlen);
extern int up_low(char);
extern unit *map_luno(ftnint);
extern unit *find_luno(ftnint);
extern int f77nowreading(unit *);
extern int f77nowwriting(unit *);
extern int f77inode(char *, ino_t *);
extern char *_I90_uppercase( char *, char * );
extern int call_vfmt( int * );
extern int wrt_I(unit *, uinteger *, int, ftnlen);
extern int wrt_LL(unit *, uinteger *, int);
extern int wrt_L(unit *, uinteger *, int, ftnlen);
extern int wrt_G(unit *, void *, int, int, int, int, ftnlen, ftnint, flag);
extern int w_ed(unit *, struct f77syl *, char *, ftnlen, ftnint);
extern int w_ned(unit *, struct f77syl *);
extern int wsfe(cilist64 *, unit **, int);
extern int s_wsfe(cilist *);
extern int s_wsfe_mp(cilist *, unit **);
extern int x_putc(unit *, XINT, char, char *);
extern int x_wSL(unit *);
extern int x_wEND(unit *);
extern int xw_end(unit *);
extern int xw_rev(unit *);
extern int s_wsfe64(cilist64 *a);
extern int s_wsfe64_mp(cilist64 *a, unit **fu);
extern void __set_f77vms_flag_( unsigned short flag_arr[]);
extern long _fio_get_pos(int fd);
extern void _fio_seq_pos( int fd, unit *ftnunit );
extern void _fio_set_seek( int fd, long int offset, int from);
extern int      _type_f(int);
extern int do_Lio64_mp_1dim(ftnint *type, flex *ptr,flex *do_idx, XINT *lb,XINT *ub, XINT *step,unit **fu, ftnlen len, ftnlen idxlen);
extern int __kai_do_lio64_mp_1dim(ftnint *type, flex *ptr,flex *do_idx, XINT *lb,XINT *ub, XINT *step,unit **fu, ftnlen len, ftnlen idxlen);
extern int do_fio64_mp_1dim(  ftnint *type, char *ptr, flex *do_idx, XINT *lb, XINT *ub, XINT *step, unit **fu, ftnlen len, ftnlen idxlen);
extern int do_uio64_mp_1dim( char *ptr, flex *do_idx, XINT *lb, XINT *ub, XINT *step, unit **fu, ftnlen len, ftnlen idxlen);
extern void f_dconn(ftnint luno);
extern void f_exit(void);
extern int f_inqu(inlist *a);
extern int f_inqu_unix(inlist *a);
extern int f_inqu_vms(inlist *a);
extern int f_open(olist *a);
extern int f_open_unix(olist *a);
extern int f_open_vms(olist *a);
extern __int32_t fcntl_( __int32_t *fd, __int32_t *locktype, struct flock *fl);
extern void flush_connected_units(void);
extern __int32_t lockf_( __int32_t *luno, __int32_t *func, size_t *size);
extern __int32_t maplun_( int *luno );
extern int setbuf_( __int32_t *luno, char *buf );
extern int setbuffer_( __int32_t *luno, char *buf, int *size );
extern int setlinebuf_( __int32_t *luno );
extern int setvbuf_( __int32_t *luno, char *buf, int *type, size_t *size);

/* prototypes from libisam */


struct decimal
    {
    short dec_exp;              /* exponent base 100            */
    short dec_pos;              /* sign: 1=pos, 0=neg, -1=null  */
    short dec_ndgts;            /* number of significant digits */
    char  dec_dgts[16];    /* actual digits base 100       */
    }; 
typedef struct decimal dec_t;

typedef union FixedDec
        {     
        unsigned int fdwords[3];
        unsigned char fdbytes[12];
        } FIX_DEC, *X_DEC;

#define KEYSIZE    512          /* max length of a key          */
struct item
    {
    short it_flags;             /* flag bits                    */
    short it_totlen;            /* total length                 */
    short it_keylen;            /* key length                   */
    unsigned it_dupnum;         /* duplicate number             */
    int it_ptr;         /* pointer                      */
    short it_leadcnt;           /* leading count                */
    short it_trailcnt;          /* trailing blanks count        */
    char it_key[KEYSIZE];       /* key value                    */
    };

struct dict
    {
    char d_magic[2];            /* magic number = BTMAGIC       */
    char d_dummy1[4];           /* reserved bytes = 2,2,4,4     */
    char d_idxsize[2];          /* size of index record         */
    char d_nkeys[2];            /* number of keys defined       */
    char d_cflag[1];            /* compression flag bits        */
    char d_dflag[1];            /* duplicates flag bits         */
    char d_version[1];          /* file version number          */
    char d_recsize[2];          /* data record size             */
    char d_keysnode[4];         /* key's description node       */
    char d_dummy2[6];
    char d_freedata[4];         /* free data file record list   */
    char d_freenode[4];         /* free b-tree node list        */
    char d_nextdata[4];         /* next data file record        */
    char d_nextnode[4];         /* next b-tree node             */
    char d_transaction[4];      /* transaction number           */
    char d_uniqid[4];           /* next available unique id     */
    char d_audit[4];            /* audit trail info             */
    };

struct xrloc
    {
    int xr_logtype;                     /* log record type */
    int xr_size;                        /* log record size */
    int xr_loc;                 /* location in log file */
    struct xrloc *xr_next;              /* next log rec in transaction */
    };


struct txlist
    {
    int tx_xid;                         /* transaction id */
    struct xrloc *tx_nextrec;           /* next log rec in transaction */
    struct txlist *tx_next;             /* next transaction */
    }; 

#ifdef BSD
#define CREATLOCK
#endif 
 
#ifdef SYSV
#define SYS5LOCK
#endif

struct ifile
    {  
    short f_flags;
    short f_ucount;             /* number of opens              */
    short f_xlkcnt;             /* number of exclusive opens    */
    short f_flkcnt;             /* number of file locks         */
    struct reclist *f_wlock;    /* list of rec write locks      */
    struct reclist *f_rlock;    /* list of rec read locks       */
    dev_t f_dev;                /* V202 device number of file   */
    ino_t f_inum;               /* V202 inode number of file    */
#ifdef SEMLOCK
    short f_semid;              /* SYSTEM V semaphore ident     */
#endif /* SEMLOCK */
    int f_version;              /* transaction version number   */
#ifdef ISKERNEL                 /* V104 */
    struct inode *f_datfd;      /* data inode ptr               */
    struct inode *f_idxfd;      /* index inode ptr              */
    struct inode *f_audfd;      /* audit inode ptr              */
#else
    short f_datfd;              /* data file fd                 */
    short f_idxfd;              /* index file fd                */
    short f_audfd;              /* audit file fd                */
#endif
#ifdef CREATLOCK
    short f_lokfd;              /* lock file fd                 */
    char f_lnkname[PATHSIZE];   /* name of link file            */
#endif
    short f_datsize;            /* data record size             */
    short f_idxsize;            /* index record size            */
#ifdef SHMLOCK
    struct smfile *f_smfile;    /* ptr to common file info      */
#else
    struct dict f_dict;         /* isam dictionary header       */
#endif /* SHMLOCK */
#ifdef ISVOPEN
     char f_fname[PATHSIZE];    /* name of file                 */
     short f_omode;             /* open mode                    */
     short f_vrefcnt;           /* reference cnt for vopens     */
#endif /* ISVOPEN */
#ifdef MEMLOCK
    struct lock f_locks;        /* in memory lock table         */
#define locks   filep->f_locks  
#endif
    };

struct tree
    {
    int t_node;         /* btree node number            */
    short t_offset;             /* offset into node             */
    short t_nextoff;            /* offset of next item in node  */
    short t_used;               /* number bytes used in node    */
    }; 

#define NTREES     10           /* max b-tree level             */

struct iopen
    {
    short o_flags;              /* status flags                 */
    short o_procid;             /* process id number            */
    short o_userid;             /* user id number               */
    short o_mode;               /* open file mode               */
    int  o_version;             /* transaction version number   */
#ifdef ISKERNEL
    struct kobuf *o_kopenp;     /* cross-link for kernel buffer */
#endif /* ISKERNEL */
    struct ifile *o_filep;      /* file descriptor pointer      */
    struct keydesc o_curkey;    /* current key descriptor       */
    struct item o_curitem;      /* current item value           */
    struct tree o_trees[NTREES];/* current tree path            */
    struct reclist *o_tmpfree;  /* temporary free record list   */
    short o_trlev;              /* current tree level           */
    short o_trleaf;             /* tree level of leaf node      */
    short o_trflags;            /* tree flags                   */
#ifdef sgi
    char o_hostname[MAXHOSTNAMELEN+20]; /* current hostname */  
#endif
    }; 

extern int lddecimal(register char *, register int, register dec_t *);
extern void stdecimal(register dec_t *, register char *, register int);
extern int decload(register dec_t *, int, int, char *, register int);
extern void decround(register dec_t *, register int);
extern void dectrunc(register dec_t *, int);
extern int decprec(register dec_t *);
extern int deccmp(register dec_t *, register dec_t *);
extern void deccopy(dec_t *, dec_t *);
extern int dectoasc(register dec_t *, register char *, int, int);
extern int deccvasc(register char *, int, dec_t *);
extern char *dececvt(dec_t *, int, int *, int *);
extern char *decfcvt(dec_t *, int, int *, int *);
extern int dectoint(dec_t *, int *);
extern void deccvint(int, dec_t *);
extern int dectolong(dec_t *, int *);
extern int deccvlong(register int , dec_t *);
extern int dectoflt(dec_t *, float *);
extern int dectodbl(dec_t *, double *);
extern int deccvflt(double, register dec_t *);
extern int deccvdbl(double, register dec_t *);
extern int decadd(dec_t *, dec_t *, dec_t *);
extern int decsub(dec_t *, register dec_t *, dec_t *);
extern int decmul(dec_t *, dec_t *, dec_t *);
extern int decdiv(dec_t *, dec_t *, dec_t *);
extern void bycopy(register char *, register char *, register int );
extern void wdcopy(register char *, register char *, register int );
extern void byfill(register char *, register int , register int );
extern int bycmpr(register char *, register char *, register int );
extern int ldlong(register char *);
extern void stlong(register int, register char *);
extern int isaudit(int , char *, int );
extern int audopen(void);
extern void audoutput(char , int , char *);
extern void btposition(struct keydesc *, int);
extern int btcurrent(void);
extern void btsearch(struct item *, register struct keydesc *, int, int);
extern void btmove(struct keydesc *, int );
extern void btdups(register struct keydesc *, register int );
extern void bfinit(void);
extern struct buff *bfread(int);
extern struct buff *bfgetclr(int);
extern struct buff *bfgetblk(int);
extern void bfrelease(register struct buff *);
extern void bfdwrite(register struct buff *); 
extern void bfwrite(register struct buff *);
extern void bfmapaddr(struct buff *, int *, int *, int *);
extern void bfflush(struct ifile *);
extern void bfignor(struct ifile *);
extern int isbuild(char *, int , register struct keydesc *, register int );
extern int isaddindex(int , register struct keydesc *);
extern int isdelindex(int , register struct keydesc *);
extern int iserase(register char *);
extern int isremlock(register char *);
extern int isrename(register char *, register char *);
extern int iscluster(int, register struct keydesc *);
extern int isbnew(register int isfd, struct keydesc *, register int *, char *);
extern int ismkname(char *, char *, int tflag);
extern char *isbname(char *);
extern char *ismktemp(register char *);
extern int iscmpede(X_DEC , X_DEC , int );
extern int iscollate(int , char *);
extern int clkeycheck(struct keydesc *);
extern int clcompare(int , register char *, register char *, int );
extern int clchktype(int );
extern int itcompare( struct item *, struct item *, struct keydesc *, int );
extern int itpack( register struct item *, char *, int , register struct keydesc *);
extern int itunpack( char *, int , register struct item *, register struct keydesc *);
extern int itpress( register struct item *, register struct item *, struct keydesc *, int flag);
extern int itprevious( char *, int , struct item *, register struct keydesc *);
extern void itcopy(struct item *, struct item *, struct keydesc *);
extern void itmake(char *, struct item *, struct keydesc *);
extern int kysearch(struct keydesc *, int );
extern int kycompare(register struct keydesc *, struct keydesc *);
extern void kypack(register struct keydesc *, register char *);
extern void kyunpack( register char *, register struct keydesc *);
extern int kylegal( register struct keydesc *, register int );
extern void kycopy( struct keydesc *, struct keydesc *);
extern int kyadd( struct keydesc *); 
extern int kydelete( struct keydesc *); 
extern int islock(int );
extern int isunlock(int );
extern int lksemaphore(int );
extern int lkopenlock(int );
extern void lkrelease(void);
extern int lkrecord( int , register int ); 
extern int lkfile(int );
extern int lkloglog(int );
extern int lkread(void);
extern int lkwrite(void);
extern int locking(int , int , int );   
extern int btadditem( struct item *, register struct keydesc *);
extern int btdelitem( register struct item *, register struct keydesc *);
extern void btinsert( struct item *, register struct keydesc *, register struct item *);
extern int btlarge(void);
extern void btremove(register struct keydesc *, register struct item *, register struct item *);
extern int isopen(char *, register int );
extern void issetsu(register int );
extern int iscleanup(void);
extern int isclose(int );
extern int isrelease(int );
extern int isflush(int );
extern int isenter( register int , register int );
extern int isexit(void);
extern void isbatch(int );
extern int isuniqueid(int , int *);
extern int issetunique(int , int );
extern int isindexinfo( int , struct keydesc *, register int );
extern int iststindex( int , struct keydesc *); 
extern int dictread(void);
extern int dictwrite(void);
extern void dictmodify(void);
extern int mktemprec(int );
extern int isread( int , char *, register int );
extern int isstart( int , struct keydesc *, int , char *, int );
extern void kposition( char *, int , int );
extern int isrecover(void);  
extern int rollforward(struct txlist *, int );
extern void freetx(int );
extern int redo(char *, int , struct txlist *);
extern int lgclfile(char *);
extern int isgetnext(int , char **);
extern int chktrans(char *, struct txlist **, int *);
extern int stlogrec(struct xrloc **, int , int , int );
extern int rmglbfile(struct txlist *, char *);
extern int ISADDR(void);
extern int ismaxfds;
extern int allocopen(void);
extern int freeopen(struct iopen *);
extern struct ifile *allocfile(char *, register int);
extern void freefile(register struct ifile *);
extern void initsem(struct ifile *); 
extern int allocrec(int);
extern int getdatnode(int, int);
extern void freerec(int, int);
extern int makefile(char *, int);
extern int getfileid(char *, dev_t *, ino_t *);
extern int dataread(char *, int);
extern int datawrite(char *, int); 
extern int datadelete(int);
extern int datacheck(int); 
extern int dataxfer(int, char *, int);
extern int dataread(register char *, int);
extern int datawrite(register char *, int);
extern int datadelete(int);
extern int error(char *msg);
extern int rlinsert(struct reclist **, register int);
extern int rldelete(struct reclist **, register int);
extern int rlcheck(struct reclist **, register int);
extern int ckfilname(char *);
extern int mkidxname(register char *, register char *);
extern int mkdatname(register char *, register char *);
extern int mklokname(register char *, register char *);
extern int mksemname(dev_t, ino_t, register char *);
extern int isvclose(int);
extern int vclose(void); 
extern void stcat(register char *, register char *);
extern int stcmpr(register char *, register char *s2);
extern void stcopy(register char *, register char *);
extern int stleng( register char *);
extern void ldchar(register char *, register int , register char *);
extern void stchar(register char *, register char *, register int );
extern int byleng(register char *, int );
extern double ldfltnull(char *, short *);
extern void stfltnull( double , register char * , short );
extern double ldfloat(register char *);
extern void stfloat(double ,register char *);
extern double lddblnull( char * , short * );
extern void stdblnull( double , register char * , short  );
extern double lddbl(register char *);
extern void stdbl(double ,register char *);
extern int validate(void);
extern int untrp(void);
extern void snverify( int (*)(), int (*)(), int (*)(), int (*)());  
extern void windw( int (*)(), int (*)(), int (*)(), int (*)());  
extern void snchk(int one, int two);
extern void lister(int one, int two);
extern int real(void);
extern int windf(void);
extern int demo(void);
extern int windt(void);
extern char *windz(void);
extern int wrong(void);
extern int windx(void);
extern int snbadmsg(void); 
extern int isatol(register char *s);
extern int iswrite(int , char *);
extern int iswrcurr(int , char *);
extern void wrtrecord(int , char *, int , int );
extern int isrewrite(int , char *);
extern int isrewcurr(int , char *);
extern int isrewrec(int , int , char *);
extern void rewrecord(int , char *, char *, int , int );
extern int isdelete(int , char *);
extern int isdelcurr(int );
extern int isdelrec(int , int );
extern void delrecord(int , char *, int );
extern int getrecord(char *, int ); 
extern int getcurrent(int , int );
extern int getlogtype(char *);
extern int writelog(char *, int , int );
extern int readlog(char *, int , int );
extern int getrisfd(int );
extern char *isgetprev(int , int );
extern int txclose(register int);
extern void stkeyparts( struct keydesc *, char *, int *);
extern void ldkeyparts( char *, struct keydesc *);
extern int islogopen(char *);   
extern int islogclose(void);
extern void issusplog(void);
extern void isresumlog(void);
extern int isbegin(void);
extern int iscommit(void);
extern int isrollback(void);
extern int islogbuild( char *, int , struct keydesc *, int );
extern int islogerase(char *);  
extern int islogidx( int , int , struct keydesc *);
extern int iswimage(int , int , int , int , char *, char *);
extern int lgdelete(register char *);
extern int lgrename(char *);
extern int lgsavept(short , char *);
extern int lgopfile( int , char *, int , char );
extern int isloguid(int , int , char );
extern int islogfile(int , int , char *, int );
extern int islogrename(char *, char *);
extern int lgsetuniqid(register char *);
extern int lgredoidx(char *, int );
extern int lgupdate(register char *, int );
extern int lginsert(register char *, int );
extern int getdatrec(register int );
extern int lgsavept(short , char *);
extern void prdbversion(char *head, int (*print)(), int (*die)());
