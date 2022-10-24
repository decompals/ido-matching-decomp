/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)resource.h	7.1 (Berkeley) 6/4/86
 */
#ifndef _SYS_RESOURCE_H
#define _SYS_RESOURCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>

/*
 * Process priority specifications to get/setpriority.
 */
#define	PRIO_MIN	-20
#define	PRIO_MAX	20

#define	PRIO_PROCESS	0
#define	PRIO_PGRP	1
#define	PRIO_USER	2

/*
 * Resource utilization information.
 */

#define	RUSAGE_SELF	0
#define	RUSAGE_CHILDREN	-1

struct	rusage {
	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
	long	ru_maxrss;
#define	ru_first	ru_ixrss
	long	ru_ixrss;		/* integral shared memory size */
	long	ru_idrss;		/* integral unshared data " */
	long	ru_isrss;		/* integral unshared stack " */
	long	ru_minflt;		/* page reclaims */
	long	ru_majflt;		/* page faults */
	long	ru_nswap;		/* swaps */
	long	ru_inblock;		/* block input operations */
	long	ru_oublock;		/* block output operations */
	long	ru_msgsnd;		/* messages sent */
	long	ru_msgrcv;		/* messages received */
	long	ru_nsignals;		/* signals received */
	long	ru_nvcsw;		/* voluntary context switches */
	long	ru_nivcsw;		/* involuntary " */
#define	ru_last		ru_nivcsw
};

/*
 * Resource limits
 */
#define	RLIMIT_CPU	0		/* cpu time in milliseconds */
#define	RLIMIT_FSIZE	1		/* maximum file size */
#define	RLIMIT_DATA	2		/* data size */
#define	RLIMIT_STACK	3		/* stack size */
#define	RLIMIT_CORE	4		/* core file size */
#define RLIMIT_NOFILE	5		/* file descriptors */
#define RLIMIT_VMEM	6		/* maximum mapped memory */
#define	RLIMIT_RSS	7		/* resident set size */
#define RLIMIT_AS	RLIMIT_VMEM

#define	RLIM_NLIMITS	8		/* number of resource limits */

#ifdef _KERNEL
#define RLIM_INFINITY	0x7fffffffffffffffLL
#define	RLIM32_INFINITY	0x7fffffff
#else /* _KERNEL */
#if (_MIPS_SZLONG == 32)
#define	RLIM_INFINITY	0x7fffffff
#else
#define	RLIM_INFINITY	0x7fffffffffffffffLL
#endif /* _MIPS_SZLONG == 32 */
#endif /* _KERNEL */

#define	RLIM64_INFINITY	0x7fffffffffffffffLL

#ifndef _KERNEL
typedef unsigned long rlim_t;
#else
typedef __uint64_t rlim_t;
#endif

typedef __uint64_t rlim64_t;

struct rlimit {
	rlim_t	rlim_cur;		/* current (soft) limit */
	rlim_t	rlim_max;		/* maximum value for rlim_cur */
};

struct rlimit64 {
	rlim64_t	rlim_cur;
	rlim64_t	rlim_max;		
};		

#ifdef _KERNEL

#include <sys/types.h>

/*
 * Convert the given 32 bit limit spec to RLIM_INFINITY if it
 * is specified as RLIM32_INFINITY.
 */
#define	RLIM32_CONV(x)	(((x) == RLIM32_INFINITY) ? RLIM_INFINITY : (x))

extern void ruadd(struct rusage *, struct rusage *);
extern struct rlimit rlimits[];

struct irix5_rlimit {
	app32_ulong_t	rlim_cur;
	app32_ulong_t	rlim_max;
};

#else	/* !_KERNEL */

extern int getrlimit(int, struct rlimit *);
extern int setrlimit(int, const struct rlimit *);
#ifdef _SGI_SOURCE
extern int getrlimit64(int, struct rlimit64 *);
extern int setrlimit64(int, const struct rlimit64 *);
extern int getpriority(int, int);
extern int setpriority(int, int, int);
extern int getrusage(int, struct rusage *);
#endif	/* _SGI_SOURCE */

#endif /* !_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_RESOURCE_H */
