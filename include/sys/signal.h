/* Copyright (C) 1989-1992 Silicon Graphics, Inc. All rights reserved.  */
/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _SYS_SIGNAL_H
#define _SYS_SIGNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#ident	"$Revision: 3.97 $"

/* ANSI C Notes:
 *
 * - THE IDENTIFIERS APPEARING OUTSIDE OF #ifdef's IN THIS
 *   standard header ARE SPECIFIED BY ANSI!  CONFORMANCE WILL BE ALTERED
 *   IF ANY NEW IDENTIFIERS ARE ADDED TO THIS AREA UNLESS THEY ARE IN ANSI's
 *   RESERVED NAMESPACE. (i.e., unless they are prefixed by __[a-z] or
 *   _[A-Z].  For external objects, identifiers with the prefix _[a-z]
 *   are also reserved.)
 *
 * - Section 4.7 indicates that identifiers beginning with SIG or SIG_
 *   followed by an upper-case letter are added to the reserved namespace
 *   when including <signal.h>.
 * POSIX Notes:
 *	Alas, POSIX permits SIG_ but not SIG
 */

/*
 * Signal numbers have changed between IRIX4 and SVR4 ABI
 */

/*
 * SVR4 ABI numbers
 */
#define	SIGHUP	1	/* hangup */
#define	SIGINT	2	/* interrupt (rubout) */
#define	SIGQUIT	3	/* quit (ASCII FS) */
#define	SIGILL	4	/* illegal instruction (not reset when caught)*/
#ifndef _POSIX_SOURCE
#define	SIGTRAP	5	/* trace trap (not reset when caught) */
#define	SIGIOT	6	/* IOT instruction */
#endif
#define SIGABRT 6	/* used by abort, replace SIGIOT in the  future */
#ifndef _POSIX_SOURCE
#define	SIGEMT	7	/* EMT instruction */
#endif
#define	SIGFPE	8	/* floating point exception */
#define	SIGKILL	9	/* kill (cannot be caught or ignored) */
#ifndef _POSIX_SOURCE
#define	SIGBUS	10	/* bus error */
#endif
#define	SIGSEGV	11	/* segmentation violation */
#define	SIGSYS	12	/* bad argument to system call */
#define	SIGPIPE	13	/* write on a pipe with no one to read it */
#define	SIGALRM	14	/* alarm clock */
#define	SIGTERM	15	/* software termination signal from kill */
#define	SIGUSR1	16	/* user defined signal 1 */
#define	SIGUSR2	17	/* user defined signal 2 */
#ifndef _POSIX_SOURCE
#define	SIGCLD	18	/* death of a child */
#endif
#define SIGCHLD 18	/* 4.3BSD's/POSIX name */
#ifndef _POSIX_SOURCE
#define	SIGPWR	19	/* power-fail restart */
#define	SIGWINCH 20	/* window size changes */
#define	SIGURG	21	/* urgent condition on IO channel */
#define SIGPOLL 22	/* pollable event occurred */
#define	SIGIO	22	/* input/output possible signal */
#endif /* _POSIX_SOURCE */
#define	SIGSTOP	23	/* sendable stop signal not from tty */
#define	SIGTSTP	24	/* stop signal from tty */
#define	SIGCONT	25	/* continue a stopped process */
#define	SIGTTIN	26	/* to readers pgrp upon background tty read */
#define	SIGTTOU	27	/* like TTIN for output if (tp->t_local&LTOSTOP) */
#ifndef _POSIX_SOURCE
#define SIGVTALRM 28	/* virtual time alarm */
#define SIGPROF	29	/* profiling alarm */
#define SIGXCPU	30	/* Cpu time limit exceeded */
#define SIGXFSZ	31	/* Filesize limit exceeded */
#ifdef _KERNEL 
#define	_IRIX4_KERN_SIGIO	32 /* for irix4 abi only */
#else
#define	SIG32	32	/* Reserved for kernel usage */
#endif
#endif


#if  !defined(_XOPEN_SOURCE)
/* Posix 1003.1b signals */
#define SIGRTMIN	49	/* Posix 1003.1b signals */
#define SIGRTMAX	64	/* Posix 1003.1b signals */

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
#if (_MIPS_SZPTR == 32)
typedef union sigval {
	int	sival_int;
	void	*sival_ptr;
} sigval_t;
#endif
#if (_MIPS_SZPTR == 64)
typedef union sigval {
	long	sival_int;
	void	*sival_ptr;
} sigval_t;
#endif
#ifdef  _ABI_SOURCE

typedef union notifyinfo {
	int	nisigno;			/* signal info */
	void	(*nifunc) (union sigval); 	/* callback data */
} notifyinfo_t;

typedef struct sigevent {
	int			sigev_notify;
	notifyinfo_t		sigev_notifyinfo;
	sigval_t		sigev_value;
	unsigned long		sigev_reserved[13];
	unsigned long		sigev_pad[6];
} sigevent_t;
#define sigev_func	sigev_notifyinfo.nifunc
#define sigev_signo	sigev_notifyinfo.nisigno

#define SIGEV_NONE	128
#define SIGEV_SIGNAL	129
#define SIGEV_CALLBACK	130

#else
typedef struct sigevent {
	int		sigev_signo;
	union sigval	sigev_value;
} sigevent_t;
#endif /* _ABI_SOURCE */
#endif	/* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */
#endif /* !_XOPEN_SOURCE */

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#if defined(_LANGUAGE_C_PLUS_PLUS)
/*
 * C++ user's who want/need additional arguments should cast their
 * function to (SIG_PF)
 */
#define _sigargs	...
#else
#define _sigargs	
#endif /* _LANGUAGE_C_PLUS_PLUS) */

/*
 * Almost everyone has gone to a void return type. This lets
 * old programs define this and get the old 'int' behviour
 */
#ifndef __sigret_t
#define	__sigret_t	void
#endif

typedef __sigret_t	(*SIG_PF) (_sigargs);

#if defined(_BSD_COMPAT) || defined(_BSD_SIGNALS)
/*
 * The next section contains declarations and typedefs for the BSD signal
 * library routines built on top of the POSIX system calls.  Two of them,
 * signal() and sigpause(), share names with their SysV counterparts, yet
 * have different semantics.  By default, the SysV versions are used.
 * In order to use the BSD versions, you may either:
 *  1) explicitly call BSDsignal() and BSDsigpause() in the program, or
 *  2) set one of the _BSD_SIGNALS or _BSD_COMPAT cpp constants before
 *     including the signal header file. There are 2 methods:
 *     a) modify the source file, e.g.,
 *	    #ifdef sgi
 *          #define _BSD_SIGNALS
 *          #endif
 *          #include <signal.h>
 *     b) use the cc(1) option -D_BSD_SIGNALS or -D_BSD_COMPAT.
 *        e.g., cc -D_BSD_SIGNALS foo.c -o foo
 * Note that _BSD_COMPAT affects other header files that deal with BSD
 * compatibility.
 */

struct sigvec {
  __sigret_t (*sv_handler)(_sigargs);	/* SIG_DFL, SIG_IGN, or *fn */
  int sv_mask;		/* mask to use during handler execution	*/
  int sv_flags;		/* see signal options below */
};


#define SV_ONSTACK	0x0001
#define SV_INTERRUPT	0x0002		/* not supported */
#define sv_onstack	sv_flags	/* compatibility with BSD */

#define NUMBSDSIGS	(32)  /* can't be expanded */
/* Convert signal number to bit mask representation */
#define sigmask(sig)	(1L << ((sig)-1))

#define signal		BSDsignal
#define sigpause	BSDsigpause

extern int	sigpause(int);
extern int	sigvec(int,struct sigvec *, struct sigvec *);
struct sigstack;
extern int	sigstack(struct sigstack *, struct sigstack *);
extern int	sigblock(int);
extern int	sigsetmask(int);
extern int	killpg(int, int);
extern int	kill(int, int);
#endif /* BSD */

#define SIG_ERR		((SIG_PF)-1)
#define	SIG_IGN		((SIG_PF)1)
#define SIG_HOLD	((SIG_PF)2)
#define	SIG_DFL		((SIG_PF)0)

#ifndef _KERNEL
extern __sigret_t	(*signal(int,__sigret_t (*)(_sigargs)))(_sigargs);
#endif

#if defined(_SVR4_SOURCE) || defined(_POSIX_SOURCE) || defined(_XOPEN_SOURCE)
#include <sys/types.h>

typedef struct {                /* signal set type */
        __uint32_t sigbits[4];
} sigset_t;

typedef struct sigaction {
	int sa_flags;			/* see below for values		*/
	__sigret_t (*sa_handler)(_sigargs);	/* SIG_DFL, SIG_IGN, or *fn */
	sigset_t sa_mask;		/* additional set of sigs to be	*/
					/* blocked during handler execution */
	int sa_resv[2];
} sigaction_t;

/*
 * Definitions for the "how" parameter to sigprocmask():
 *
 * The parameter specifies whether the bits in the incoming mask are to be
 * added to the presently-active set for the process, removed from the set,
 * or replace the active set.
 */
#define SIG_NOP		0	/* Not using 0 will catch some user errors. */
#define SIG_BLOCK	1
#define SIG_UNBLOCK	2	
#define SIG_SETMASK	3
#define SIG_SETMASK32	256	/* SGI added so that BSD sigsetmask won't 
				   affect the upper 32 sigal set */

/* definitions for the sa_flags field */
/*
 * IRIX5/SVR4 ABI definitions
 */
#define SA_ONSTACK	0x00000001	/* handle this signal on sigstack */
#define SA_RESETHAND    0x00000002	/* reset handler */
#define SA_RESTART      0x00000004	/* restart interrupted system call */
#define SA_SIGINFO      0x00000008	/* provide siginfo to handler */
#define SA_NODEFER      0x00000010	/* do not block current signal */
/* The next 2 are only meaningful for SIGCHLD */
#define SA_NOCLDWAIT    0x00010000	/* don't save zombie children */
#define SA_NOCLDSTOP	0x00020000	/* if set don't send SIGCLD	*/
					/* to parent when child stop	*/

/* IRIX5 additions */
#define _SA_BSDCALL	0x10000000	/* don't scan for dead children when */
					/* setting SIGCHLD */
					/* SJCTRL bit in proc struct.	*/


#endif /* _SVR4_SOURCE || _POSIX_SOURCE || _XOPEN_SOURCE */

#if defined(_SVR4_SOURCE) && !defined(_POSIX_SOURCE) 

/* sigaltstack info */
#define MINSIGSTKSZ	512
#define SIGSTKSZ	8192

struct sigaltstack {
	char	*ss_sp;
	int	ss_size;
	int	ss_flags;
};
typedef struct sigaltstack stack_t;

/* defines for ss_flags */
#define SS_ONSTACK	0x00000001
#define SS_DISABLE	0x00000002

#endif /* _SVR4_SOURCE && !_POSIX_SOURCE */

#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
/*
 * Information pushed on stack when a signal is delivered. This is used by
 * the kernel to restore state following execution of the signal handler.
 * It is also made available to the handler to allow it to properly restore
 * state if a non-standard exit is performed.
 *
 * sc_regmask is examined by the kernel when doing sigreturn()'s
 * and indicates which registers to restore from sc_regs
 * bit 0 == 1 indicates that all coprocessor state should be restored
 *	for each coprocessor that has been used
 * bits 1 - 31 == 1 indicate registers 1 to 31 should be restored by
 *	sigcleanup from sc_regs.
 */

/*
 * The IRIX5 version
 * sigcontext is not part of the ABI - so this version is used to
 * handle 32 and 64 bit applications - it is a constant size regardless
 * of compilation mode, and always returns 64 bit register values
 */
typedef struct sigcontext {
	__uint32_t	sc_regmask;	/* regs to restore in sigcleanup */
	__uint32_t	sc_status;	/* cp0 status register */
	__uint64_t	sc_pc;		/* pc at time of signal */
	/*
	 * General purpose registers
	 */
	__uint64_t	sc_regs[32];	/* processor regs 0 to 31 */
	/*
	 * Floating point coprocessor state
	 */
	__uint64_t	sc_fpregs[32];	/* fp regs 0 to 31 */
	__uint32_t	sc_ownedfp;	/* fp has been used */
	__uint32_t	sc_fpc_csr;	/* fpu control and status reg */
	__uint32_t	sc_fpc_eir;	/* fpu exception instruction reg */
					/* implementation/revision */
	__uint32_t	sc_ssflags;	/* signal stack state to restore */
	__uint64_t	sc_mdhi;	/* Multiplier hi and low regs */
	__uint64_t	sc_mdlo;
	/*
	 * System coprocessor registers at time of signal
	 */
	__uint64_t	sc_cause;	/* cp0 cause register */
	__uint64_t	sc_badvaddr;	/* cp0 bad virtual address */
	__uint64_t	sc_triggersave;	/* state of graphics trigger (SGI) */
	sigset_t	sc_sigset;	/* signal mask to restore */
	__uint64_t	sc_pad[32];
} sigcontext_t;

#if !defined(_KERNEL) && !defined(_KMEMUSER)
/* minor compatibility - sc_mask is the first 32 bits (for BSD sigsetmask) */
#define sc_mask	sc_sigset.sigbits[0]
#endif
/*
 * Structure used in BSD sigstack call.
 */
struct sigstack {
	char	*ss_sp;			/* signal stack pointer */
	int	ss_onstack;		/* current status */
};

#if _LINT
#undef SIG_ERR
#define SIG_ERR (void(*)())0
#undef SIG_IGN
#define	SIG_IGN	(void (*)())0
#undef SIG_HOLD
#define	SIG_HOLD (void (*)())0
#endif /* _LINT */

#endif /* _SGI_SOURCE && !_POSIX_SOURCE */

#else /* !(_LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS) */

/* Define these for ASSEMBLY and FORTRAN */
#define SIG_ERR         (-1)
#define SIG_IGN         (1)
#define SIG_HOLD        (2)
#define SIG_DFL         (0)

#endif /* !(_LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS) */


#if defined(_XOPEN_SOURCE) && defined(_VSX) 
#define NSIG            65      /* valid signal numbers are from 1 to NSIG-1 */
#endif /* _XOPEN_SOURCE */

#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
#define NSIG            65      /* valid signal numbers are from 1 to NSIG-1 */
#define MAXSIG		(NSIG-1)    /* actual # of signals */
#define	NUMSIGS		(NSIG-1)    /* for POSIX array sizes, true # of sigs */

#define	BRK_USERBP	0	/* user bp (used by debuggers) */
#define	BRK_KERNELBP	1	/* kernel bp (used by prom) */
#define	BRK_ABORT	2	/* abort(3) uses to cause SIGIOT */
#define	BRK_BD_TAKEN	3	/* for taken bd emulation */
#define	BRK_BD_NOTTAKEN	4	/* for not taken bd emulation */
#define	BRK_SSTEPBP	5	/* user bp (used by debuggers) */
#define	BRK_OVERFLOW	6	/* overflow check */
#define	BRK_DIVZERO	7	/* divide by zero check */
#define	BRK_RANGE	8	/* range error check */
#define	BRK_MULOVF	1023	/* multiply overflow detected */
#endif /* _SGI_SOURCE && !_POSIX_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* !_SYS_SIGNAL_H */
