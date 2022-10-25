/**************************************************************************
 *									  *
 * 		 Copyright (C) 1990-1992 Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)wait.h	7.4 (Berkeley) 1/27/88
 */
#ifndef __SYS_WAIT_H__
#define __SYS_WAIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#ident "$Revision: 1.37 $"

/*
 * This file holds definitions relevent to the wait system call.
 * Some of the options here are available only through the ``wait3''
 * entry point; the old entry point with one argument has more fixed
 * semantics, never returning status of unstopped children, hanging until
 * a process terminates if any are outstanding, and never returns
 * detailed information about process resource utilization.
 */
#if !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)

/*
 * Structure of the information in the first word returned by both
 * wait and wait3.  If w_stopval==_WSTOPPED, then the second structure
 * describes the information returned, else the first.  See WUNTRACED below.
 */
typedef union wait	{
	int	w_status;		/* used in syscall */
	/*
	 * Terminated process status.
	 */
	struct {
#ifdef _MIPSEL
		unsigned int	w_Termsig:7,	/* termination signal */
				w_Coredump:1,	/* core dump indicator */
				w_Retcode:8,	/* exit code if w_termsig==0 */
				w_Filler:16;	/* upper bits filler */
#endif
#ifdef _MIPSEB
		unsigned int	w_Filler:16,	/* upper bits filler */
				w_Retcode:8,	/* exit code if w_termsig==0 */
				w_Coredump:1,	/* core dump indicator */
				w_Termsig:7;	/* termination signal */
#endif
	} w_T;
	/*
	 * Stopped process status.  Returned
	 * only for traced children unless requested
	 * with the WUNTRACED option bit.
	 */
	struct {
#ifdef _MIPSEL
		unsigned int	w_Stopval:8,	/* == W_STOPPED if stopped */
				w_Stopsig:8,	/* signal that stopped us */
				w_Filler:16;	/* upper bits filler */
#endif
#ifdef _MIPSEB
		unsigned int	w_Filler:16,	/* upper bits filler */
				w_Stopsig:8,	/* signal that stopped us */
				w_Stopval:8;	/* == W_STOPPED if stopped */
#endif
	} w_S;
} wait_t;
#define	w_termsig	w_T.w_Termsig
#define w_coredump	w_T.w_Coredump
#define w_retcode	w_T.w_Retcode
#define w_stopval	w_S.w_Stopval
#define w_stopsig	w_S.w_Stopsig

#define _WAITCAST(w)	(*(union wait *)&(w))	/* for 4.0 compat */
#define _W_INT(w)	(*(int *)&(w))  /* convert union wait to int */
#else
#define _W_INT(i)	(i)
#endif /* !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE) */
#define	_WSTOPPED	0177	/* value of s.stopval if process is stopped */

/*
 * Option bits for the second argument of wait3.  WNOHANG causes the
 * wait to not hang if there are no stopped or terminated processes, rather
 * returning an error indication in this case (pid==0).  WUNTRACED
 * indicates that the caller should receive status about untraced children
 * which stop due to signals.  If children are stopped and a wait without
 * this option is done, it is as though they were still running... nothing
 * about them is returned.
 */
#define WNOHANG		0100	

#if !defined(_POSIX_SOURCE)
#define WEXITED         0001    
#define WTRAPPED        0002   
#define WSTOPPED        0004    /* wait for processes stopped by signals */
#define WCONTINUED      0010    /* wait for processes continued */
#define WNOWAIT         0200    /* non destructive form of wait */

#define WOPTMASK        (WEXITED|WTRAPPED|WSTOPPED|WCONTINUED|WNOHANG|WNOWAIT)

#define WSTOPFLG                0177
#define WCONTFLG                0177777
#define WCOREFLAG               0200
#define WSIGMASK                0177

#define WWORD(stat)             (_W_INT(stat)&0177777)
#define WIFCONTINUED(stat)	(WWORD(stat)==WCONTFLG)
#define WCOREDUMP(stat)		(_W_INT(stat) & WCOREFLAG)
#endif /* !defined(_POSIX_SOURCE) */

#define	WUNTRACED	0004	 /* for POSIX */

#define WIFEXITED(stat)         ((_W_INT(stat)&0377)==0)
#define WIFSIGNALED(stat)       ((_W_INT(stat)&0377)>0&&((_W_INT(stat)>>8)&0377)==0)
#define WIFSTOPPED(stat)        ((_W_INT(stat)&0377)==_WSTOPPED&&((_W_INT(stat)>>8)&0377)!=0)

#define WEXITSTATUS(stat)	((_W_INT(stat)>>8)&0377)
#define WTERMSIG(stat)		(_W_INT(stat)&0177)
#define WSTOPSIG(stat)		((_W_INT(stat)>>8)&0377)

#include <sys/types.h>

#ifndef _POSIX_SOURCE
#include <sys/procset.h>	/* for idtype_t */
#include <sys/signal.h>		/* siginfo.h needs it */
#include <sys/siginfo.h>	
#include <sys/resource.h>	
#endif /* _POSIX_SOURCE */

#ifdef _KERNEL
union rval;
extern int waitsys(idtype_t, id_t, k_siginfo_t *, int, struct rusage *,
                   union rval *);
#else /* _KERNEL */

#ifdef _MODERN_C

extern pid_t waitpid(pid_t, int *, int);

#ifdef _BSD_COMPAT
/* old style BSD pgms can't decide whether the arg is a union wait or an int */
extern int wait();
#else
extern pid_t wait(int *);
#endif

#if !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE) 
#ifdef _BSD_COMPAT
extern int wait3();
#else
extern pid_t wait3(int *, int, struct rusage *);
#endif
extern int waitid(idtype_t, id_t, siginfo_t *, int);
#endif /* !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE) */

#else 	/* _MODERN_C */

extern pid_t waitpid();
extern pid_t wait();
#if !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE) 
extern int wait3();
extern int waitid();
#endif /* !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE) */

#endif 	/* _MODERN_C */

#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __SYS_WAIT_H__ */
