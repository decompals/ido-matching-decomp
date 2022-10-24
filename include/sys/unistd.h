/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/* WARNING: This is an implementation-specific header,
** its contents are not guaranteed. Applications
** should include <unistd.h> and not this header.
*/

#ifndef _SYS_UNISTD_H
#define _SYS_UNISTD_H


/* command names for POSIX sysconf */

#define _SC_ARG_MAX             1
#define _SC_CHILD_MAX           2
#define _SC_CLK_TCK             3
#define _SC_NGROUPS_MAX         4
#define _SC_OPEN_MAX            5
#define _SC_JOB_CONTROL         6
#define _SC_SAVED_IDS           7
#define _SC_VERSION             8
#define _SC_PASS_MAX		9
#define _SC_LOGNAME_MAX		10
#define _SC_PAGESIZE		11
#define _SC_XOPEN_VERSION 	12
#define _SC_NACLS_MAX   13
#define _SC_NPROC_CONF  14
#define _SC_NPROC_ONLN  15
#define _SC_STREAM_MAX  16
#define _SC_TZNAME_MAX  17
#ifndef _ABI_SOURCE
#define _SC_AIO_MAX		18
#define _SC_AIO_LISTIO_MAX	19
#endif /* !_ABI_SOURCE */
#define _SC_RTSIG_MAX		20
#define _SC_SIGQUEUE_MAX	21
#ifndef  _ABI_SOURCE
#define _SC_ASYNCHRONOUS_IO	22
#endif  /* !_ABI_SOURCE */
#define _SC_REALTIME_SIGNALS	23
#define _SC_PRIORITIZED_IO	24
#define _SC_ACL			25
#define _SC_AUDIT		26	
#define _SC_INF			27
#define _SC_MAC			28
#define _SC_CAP			29
#define _SC_IP_SECOPTS		30
#define	_SC_KERN_POINTERS	31

#ifdef _ABI_SOURCE
#define _SC_ASYNCHRONOUS_IO	64	/* is POSIX AIO supported */
#define _SC_ABI_ASYNCHRONOUS_IO	65	/* is ABI AIO supported */
#define _SC_AIO_LISTIO_MAX	66	/* max items in single listio call */
#define _SC_AIO_MAX		67	/* total outstanding AIO operations */
#define _SC_AIO_PRIO_DELTA_MAX	68
#endif /* _ABI_SOURCE */
/* command names for POSIX pathconf */

#define _PC_LINK_MAX            1	/* maximum number of links */
#define _PC_MAX_CANON           2	/* maximum bytes in a line */
					/* for canoical processing */
#define _PC_MAX_INPUT           3	/* maximum bytes stored in */
					/* the input queue */
#define _PC_NAME_MAX            4	/* longest component name */
#define _PC_PATH_MAX            5	/* longest path name */
#define _PC_PIPE_BUF            6	/* maximum number of bytes that can */
					/* be written atomiclly to a pipe */
#define _PC_CHOWN_RESTRICTED    7	/* chown restricted */
#define _PC_NO_TRUNC            8	/* truncation enabled */
#define _PC_VDISABLE            9	/* spec. character functions disabled */
#if defined(_ABI_SOURCE) || defined (_KERNEL)
#define _PC_ASYNC_IO		64	/* Can this file do POSIX AIO? */
#define _PC_ABI_ASYNC_IO	65	/* Can this file do ABI AIO */
#define _PC_ABI_AIO_XFER_MAX	66	/* biggest ABI AIO xfer for this file */
#endif /* _ABI_SOURCE || _KERNEL */

#ifndef _POSIX_VERSION
#define _POSIX_VERSION	199009L
#endif

#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE 0 /* Disable special character functions */
#endif

#ifndef _XOPEN_VERSION
#define _XOPEN_VERSION 3
#endif
#if defined(_ABI_SOURCE) 
#ifndef  _POSIX_ASYNCHRONOUS_IO
#define  _POSIX_ASYNCHRONOUS_IO 1
#endif /*  _POSIX_ASYNCHRONOUS_IO */
#endif /* _ABI_SOURCE */
#if defined(_KERNEL) && !defined(_STANDALONE)

/*
 * Argument structs for pathconf and fpathconf syscalls, also called by
 * syssgi for Irix 4 ABI compatibility.
 */
struct pathconfa {
	char *fname;
	sysarg_t name;
};

struct fpathconfa {
	sysarg_t fdes;
	sysarg_t name;
};

union rval;
int pathconf(struct pathconfa *, union rval *);
int fpathconf(struct fpathconfa *, union rval *);
int sysconf(int, union rval *);
#endif	/* _KERNEL */

#endif	/* _SYS_UNISTD_H */
