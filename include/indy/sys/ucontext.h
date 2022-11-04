/* Copyright (C) 1989-1992 Silicon Graphics, Inc. All rights reserved.  */

/*
 * ucontext - used in /proc, sigsetjmp, signal handlers
 * NOTE: in 32 bit MIPS I mode this structure is 128 words long - the same as
 * a SIGJMPBUF
 * Another version works for MIPS II/III and assumes all 64 bit
 * registers
 * The large version is always used the /proc
 */
#ifndef _SYS__UCONTEXT_H
#define _SYS__UCONTEXT_H
#ident "$Revision: 1.14 $"

#ifdef __cplusplus
extern "C" {
#endif

#include "signal.h"

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/*
 * SVR4 ABI version - 128 words long
 */
#if (_MIPS_ISA == _MIPS_ISA_MIPS1 || _MIPS_ISA == _MIPS_ISA_MIPS2) &&\
	(_MIPS_FPSET == 16) && !defined(_EXTENDED_CONTEXT)

#define NGREG	36
typedef unsigned int greg_t;

typedef greg_t gregset_t[NGREG];

typedef struct fpregset {
	union {
		double		fp_dregs[16];
		float		fp_fregs[32];
		unsigned int	fp_regs[32];
	} fp_r;
	unsigned int 	fp_csr;
	unsigned int	fp_pad;
} fpregset_t;

typedef struct {
	gregset_t	gregs;	/* general register set */
	fpregset_t 	fpregs;	/* floating point register set */
} mcontext_t;

typedef struct ucontext {
	unsigned long	uc_flags;
	struct ucontext	*uc_link;
	sigset_t   	uc_sigmask;
	stack_t 	uc_stack;
	mcontext_t 	uc_mcontext;
	long		uc_filler[47];
	/* SGI specific */
	int		uc_triggersave;	/* state of graphic trigger */
} ucontext_t;

#endif

/*
 * 64 bit version - for 64 bit applications and /proc
 * All but struct ucontext is a fixed size regardless of how the
 * app is compiled.
 * Struct is 128 64 bit words long
 */
#if (_MIPS_ISA == _MIPS_ISA_MIPS3 || _MIPS_ISA == _MIPS_ISA_MIPS4 ||\
	_MIPS_FPSET == 32 || defined(_EXTENDED_CONTEXT))

/* In extended mode, include status register */
#define NGREG	37
typedef machreg_t greg_t;

typedef greg_t gregset_t[NGREG];

typedef struct fpregset {
	union {
		double		fp_dregs[32];
#ifdef	_MIPSEB
		struct {
			__uint32_t	_fp_fill;
			float		_fp_fregs;
		} fp_fregs[32];
#else
		struct {
			float		_fp_fregs;
			__uint32_t	_fp_fill;
		} fp_fregs[32];
#endif
		machreg_t	fp_regs[32];
	} fp_r;
	__uint32_t 	fp_csr;
	__uint32_t	fp_pad;
} fpregset_t;

typedef struct {
	gregset_t	gregs;	/* general register set */
	fpregset_t 	fpregs;	/* floating point register set */
} mcontext_t;

typedef struct ucontext {
	unsigned long	uc_flags;
	struct ucontext	*uc_link;
	sigset_t   	uc_sigmask;
	stack_t 	uc_stack;
	mcontext_t 	uc_mcontext;
	int		uc_triggersave;	/* SGI: state of graphic trigger */
	long		uc_filler[48];
} ucontext_t;

#endif /* _MIPS_ISA ... */

#define GETCONTEXT	0
#define SETCONTEXT	1

#endif /* _LANGUAGE_C */

/* 
 * values for uc_flags
 * these are implementation dependent flags, that should be hidden
 * from the user interface, defining which elements of ucontext
 * are valid, and should be restored on call to setcontext
 */

#define	UC_SIGMASK	001	/* uc_sigmask */
#define	UC_STACK	002	/* uc_stack */
#define	UC_CPU		004	/* uc_mcontext.gregs? */
#define	UC_MAU		010	/* uc_mcontext.fpregs? */

#define UC_MCONTEXT	(UC_CPU|UC_MAU)

/* 
 * UC_ALL specifies the default context
 */

#define UC_ALL		(UC_SIGMASK|UC_STACK|UC_MCONTEXT)

#define	CTX_R0		0
#define	CTX_AT		1
#define	CTX_V0		2
#define	CTX_V1		3
#define	CTX_A0		4
#define	CTX_A1		5
#define	CTX_A2		6
#define	CTX_A3		7
#define	CTX_T0		8
#define	CTX_T1		9
#define	CTX_T2		10
#define	CTX_T3		11
#define	CTX_T4		12
#define	CTX_T5		13
#define	CTX_T6		14
#define	CTX_T7		15
#define	CTX_S0		16
#define	CTX_S1		17
#define	CTX_S2		18
#define	CTX_S3		19
#define	CTX_S4		20
#define	CTX_S5		21
#define	CTX_S6		22
#define	CTX_S7		23
#define	CTX_T8		24
#define	CTX_T9		25
#define	CTX_K0		26
#define	CTX_K1		27
#define	CTX_GP		28
#define	CTX_SP		29
#define	CTX_S8		30
#define	CTX_RA		31
#define	CTX_MDLO	32
#define	CTX_MDHI	33
#define	CTX_CAUSE	34
#define	CTX_EPC		35
#define CTX_SR		36

/* defines for PS ABI compatibility */
#define	CXT_R0		CTX_R0
#define	CXT_AT		CTX_AT
#define	CXT_V0		CTX_V0
#define	CXT_V1		CTX_V1
#define	CXT_A0		CTX_A0
#define	CXT_A1		CTX_A1
#define	CXT_A2		CTX_A2
#define	CXT_A3		CTX_A3
#define	CXT_T0		CTX_T0
#define	CXT_T1		CTX_T1
#define	CXT_T2		CTX_T2
#define	CXT_T3		CTX_T3
#define	CXT_T4		CTX_T4
#define	CXT_T5		CTX_T5
#define	CXT_T6		CTX_T6
#define	CXT_T7		CTX_T7
#define	CXT_S0		CTX_S0
#define	CXT_S1		CTX_S1
#define	CXT_S2		CTX_S2
#define	CXT_S3		CTX_S3
#define	CXT_S4		CTX_S4
#define	CXT_S5		CTX_S5
#define	CXT_S6		CTX_S6
#define	CXT_S7		CTX_S7
#define	CXT_T8		CTX_T8
#define	CXT_T9		CTX_T9
#define	CXT_K0		CTX_K0
#define	CXT_K1		CTX_K1
#define	CXT_GP		CTX_GP
#define	CXT_SP		CTX_SP
#define	CXT_S8		CTX_S8
#define	CXT_RA		CTX_RA
#define	CXT_MDLO	CTX_MDLO
#define	CXT_MDHI	CTX_MDHI
#define	CXT_CAUSE	CTX_CAUSE
#define	CXT_EPC		CTX_EPC
#define CXT_SR		CTX_SR


#ifdef __cplusplus
}
#endif
#endif /* ! _SYS__UCONTEXT_H */
