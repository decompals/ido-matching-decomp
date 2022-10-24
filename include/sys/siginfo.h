/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _SYS_SIGINFO_H
#define _SYS_SIGINFO_H

#ident "$Revision: 1.13 $"

#ifdef __cplusplus
extern "C" {
#endif
#include <sys/signal.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
#include <sys/types.h>
#endif	/* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */

/*
 * This header is included in wait.h so must be POSIX/ANSI safe
 */
#if !defined(_POSIX_SOURCE)
/*
 * negative signal codes are reserved for future use for user generated
 * signals 
 */

#define SI_FROMUSER(sip)	((sip)->si_code <= 0)
#define SI_FROMKERNEL(sip)	((sip)->si_code > 0)


/* 
 * SIGILL signal codes 
 */

#define	ILL_ILLOPC	1	/* illegal opcode */
#define	ILL_ILLOPN	2	/* illegal operand */
#define	ILL_ILLADR	3	/* illegal addressing mode */
#define	ILL_ILLTRP	4	/* illegal trap */
#define	ILL_PRVOPC	5	/* privileged opcode */
#define	ILL_PRVREG	6	/* privileged register */
#define	ILL_COPROC	7	/* co-processor */
#define	ILL_BADSTK	8	/* bad stack */
#define NSIGILL		8

/* 
 * SIGFPE signal codes 
 */

#define	FPE_INTDIV	1	/* integer divide by zero */
#define	FPE_INTOVF	2	/* integer overflow */
#define	FPE_FLTDIV	3	/* floating point divide by zero */
#define	FPE_FLTOVF	4	/* floating point overflow */
#define	FPE_FLTUND	5	/* floating point underflow */
#define	FPE_FLTRES	6	/* floating point inexact result */
#define	FPE_FLTINV	7	/* invalid floating point operation */
#define FPE_FLTSUB	8	/* subscript out of range */
#define NSIGFPE		8

/* 
 * SIGSEGV signal codes 
 */

#define	SEGV_MAPERR	1	/* address not mapped to object */
#define	SEGV_ACCERR	2	/* invalid permissions */
#define NSIGSEGV	2

/* 
 * SIGBUS signal codes 
 */

#define	BUS_ADRALN	1	/* invalid address alignment */
#define	BUS_ADRERR	2	/* non-existent physical address */
#define	BUS_OBJERR	3	/* object specific hardware error */
#define NSIGBUS		3

/* 
 * SIGTRAP signal codes 
 */

#define TRAP_BRKPT	1	/* process breakpoint */
#define TRAP_TRACE	2	/* process trace */
#define NSIGTRAP	2

/* 
 * SIGCLD signal codes 
 */

#define	CLD_EXITED	1	/* child has exited */
#define	CLD_KILLED	2	/* child was killed */
#define	CLD_DUMPED	3	/* child has coredumped */
#define	CLD_TRAPPED	4	/* traced child has stopped */
#define	CLD_STOPPED	5	/* child has stopped on signal */
#define	CLD_CONTINUED	6	/* stopped child has continued */
#define NSIGCLD		6

/*
 * SIGPOLL signal codes
 */

#define POLL_IN		1	/* input available */
#define	POLL_OUT	2	/* output buffers available */
#define	POLL_MSG	3	/* output buffers available */
#define	POLL_ERR	4	/* I/O error */
#define	POLL_PRI	5	/* high priority input available */
#define	POLL_HUP	6	/* device disconnected */
#define NSIGPOLL	6
#endif /* !_POSIX_SOURCE */
#define SI_MAXSZ	128
#define SI_PAD		((SI_MAXSZ / sizeof(__int32_t)) - 3)

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
/*
 * ABI version of siginfo
 * Some elements change size in the 64 bit environment
 */
typedef struct siginfo {
	int	si_signo;		/* signal from signal.h	*/
	int 	si_code;		/* code from above	*/
	int	si_errno;		/* error from errno.h	*/
	union {

		int	_pad[SI_PAD];	/* for future growth	*/

		struct {			/* kill(), SIGCLD	*/
			pid_t	_pid;		/* process ID		*/
			union {
				struct {
					uid_t	_uid;
				} _kill;
				struct {
					clock_t _utime;
					int _status;
					clock_t _stime;
				} _cld;
			} _pdata;
		} _proc;			

		struct {	/* SIGSEGV, SIGBUS, SIGILL and SIGFPE	*/
			caddr_t	_addr;		/* faulting address	*/
		} _fault;

		struct {			/* SIGPOLL, SIGXFSZ	*/
		/* fd not currently available for SIGPOLL */
			int	_fd;	/* file descriptor	*/
			int	_band;
		} _file;
#if !defined (_XOPEN_SOURCE)
		union sigval	_value;
#define si_value	_data._value
#endif

	} _data;

} siginfo_t;
#if !defined(_POSIX_SOURCE)
#define si_pid		_data._proc._pid
#define si_status	_data._proc._pdata._cld._status
#define si_stime	_data._proc._pdata._cld._stime
#define si_utime	_data._proc._pdata._cld._utime
#define si_uid		_data._proc._pdata._kill._uid
#define si_addr		_data._fault._addr
#define si_fd		_data._file._fd
#define si_band		_data._file._band
#endif /* !_POSIX_SOURCE */
#if !defined(_XOPEN_SOURCE)
/* for si_code, things that we use now */
#define SI_USER		0	/* user generated signal */
#define SI_KILL		SI_USER		/* kill system call */
#define SI_QUEUE	-1		/* sigqueue system call */
#define SI_ASYNCIO	-2		/* posix 1003.1b aio */
#endif /*  !_XOPEN_SOURCE */

#endif	/* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */


#ifdef __cplusplus
}
#endif

#endif	/* _SYS_SIGINFO_H */
