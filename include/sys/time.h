/*
 * Header for BSD time calls (plus some other stuff)
 *
 *
 * Copyright 1990, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 */
/*
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)time.h	6.4 (Berkeley) 6/24/85
 */

/*	time.h	6.1	83/07/29	*/
#ident	"$Revision: 3.31 $"

#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CLOCK_T
#define _CLOCK_T
typedef long	clock_t;	/* Type returned by clock(3C) */
#endif /* !_CLOCK_T */

/* needed here according to MIPS ABI draft */
#ifndef _TIME_T
#define _TIME_T
typedef	long		time_t;		/* <time> type */
#endif /* !_TIME_T */

#if !defined(_POSIX_SOURCE) || defined(_BSD_TYPES) || defined(_BSD_COMPAT)
#include "sys/types.h"

/*
 * Structure returned by gettimeofday(2) system call,
 * and used in other calls.
 */
struct timeval {
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
};

struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};
#define	DST_NONE	0	/* not on dst */
#define	DST_USA		1	/* USA style dst */
#define	DST_AUST	2	/* Australian style dst */
#define	DST_WET		3	/* Western European dst */
#define	DST_MET		4	/* Middle European dst */
#define	DST_EET		5	/* Eastern European dst */
#define	DST_CAN		6	/* Canada */
#define DST_GB          7       /* Great Britain and Eire */
#define DST_RUM         8       /* Rumania */
#define DST_TUR         9       /* Turkey */
#define DST_AUSTALT     10      /* Australian style with shift in 1986 */


/*
 * Operations on timevals.
 *
 * NB: timercmp does not work for >= or <=.
 */
#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timercmp(tvp, uvp, cmp)	\
	((tvp)->tv_sec cmp (uvp)->tv_sec || \
	 (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
#define	timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_usec = 0

/*
 * Names of the interval timers, and structure
 * defining a timer setting.
 */
#define	ITIMER_REAL	0
#define	ITIMER_VIRTUAL	1
#define	ITIMER_PROF	2

struct	itimerval {
	struct	timeval it_interval;	/* timer interval */
	struct	timeval it_value;	/* current value */
};
#endif /* !defined(_POSIX_SOURCE) */

/*
 * Higher resolution time information
 */
typedef struct timestruc {
	time_t	tv_sec;		/* seconds */
	long	tv_nsec;	/* and nanoseconds */
} timestruc_t;

#if !defined(_KERNEL) && defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE)
#if defined(_MODERN_C)
extern int BSDgettimeofday(struct timeval *tp, struct timezone *tzp);
extern int BSDsettimeofday(struct timeval *tp, struct timezone *tzp);
extern int gettimeofday(struct timeval *tp,...);
extern int settimeofday(struct timeval *tp,...);

/*
 * In order to use the BSD versions of the timeofday calls, you may either:
 *	(1) explicitly call BSDgettimeofday() and BSDsettimeofday()
 *	    in the program,
 * or
 *	(2) set one of the _BSD_TIME or _BSD_COMPAT cpp constants before
 *	    including the time header file. There are 2 methods:
 *		(a) modify the source file, e.g.,
 *			#ifdef sgi
 *			#define _BSD_TIME
 *			#endif
 *			#include <sys/time.h>
 *		(b) use the cc(1) option -D_BSD_TIME or -D_BSD_COMPAT.
 *		   e.g., cc -D_BSD_TIME foo.c -o foo
 * Note that _BSD_COMPAT affects other header files that deal with BSD
 * compatibility.
 */
#if defined(_BSD_TIME) || defined(_BSD_COMPAT)
#define gettimeofday	BSDgettimeofday
#define settimeofday	BSDsettimeofday
#endif	/* _BSD_TIME || _BSD_COMPAT */

extern int adjtime(struct timeval *, struct timeval *);
extern int getitimer(int, struct itimerval *);
extern int setitimer(int, struct itimerval *, struct itimerval *);
#endif 	/* _MODERN_C */
#if !defined(_XOPEN_SOURCE)
#include <time.h>
#endif
#endif 	/* !_KERNEL */

#if defined(_KERNEL)
#include "sys/ktime.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* _SYS_TIME_H */
