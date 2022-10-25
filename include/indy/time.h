#ifndef __TIME_H__
#define __TIME_H__
#ifdef __cplusplus
extern "C" {
#endif
#ident "$Revision: 1.28 $"
/*
*
* Copyright 1992, Silicon Graphics, Inc.
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
/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <sys/types.h>

#if (defined(_POSIX_4SOURCE) || defined(_SGI_SOURCE)) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
typedef struct timespec {
	time_t	tv_sec;		/* seconds */
	long	tv_nsec;	/* and nanoseconds */
} timespec_t;

typedef struct itimerspec {
	struct timespec it_interval;	/* timer period */
	struct timespec it_value;	/* timer expiration */
} itimerspec_t;

extern int nanosleep(const struct timespec *, struct timespec *);
#endif	/* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */
#endif /* _POSIX_4SOURCE || _SGI_SOURCE */

#ifndef NULL
#define NULL	0
#endif

#if !defined(_SIZE_T) && !defined(_SIZE_T_)
#define _SIZE_T
#if (_MIPS_SZLONG == 32)
typedef unsigned int	size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long	size_t;
#endif
#endif 

#ifndef _CLOCK_T
#define _CLOCK_T
typedef long 	clock_t;
#endif 
#ifndef _TIME_T
#define _TIME_T
typedef long 	time_t;
#endif /* !_TIME_T */

#define CLOCKS_PER_SEC		1000000



struct	tm {	/* see ctime(3) */
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
};

extern clock_t clock(void);			
extern double difftime(time_t, time_t);		
extern time_t mktime(struct tm *);		
extern time_t time(time_t *);			
extern char *asctime(const struct tm *);		
extern char *ctime (const time_t *);		
extern struct tm *gmtime(const time_t *);		
extern struct tm *localtime(const time_t *);	
extern size_t strftime(char *, size_t, const char *, const struct tm *);

#if defined(_SVR4_SOURCE) || defined(_POSIX_SOURCE) || defined(_XOPEN_SOURCE)
extern void tzset(void);

extern char *tzname[2];

#ifndef CLK_TCK
#define CLK_TCK	sysconf(3)	/* clock ticks per second */
				/* 3 is _SC_CLK_TCK */
#endif
#endif

#if (defined(_SVR4_SOURCE) && !defined(_POSIX_SOURCE)) || defined(_XOPEN_SOURCE)
extern long timezone;
extern int daylight;
#endif


#if defined(_SVR4_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
extern int cftime(char *, char *, const time_t *);
extern int ascftime(char *, const char *, const struct tm *);
extern long altzone;
extern struct tm *getdate(const char *);
extern int getdate_err;
#endif

#if (defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)) || defined(_SGI_REENTRANT_FUNCTIONS)

extern char *asctime_r(const struct tm *, char *, int);
extern char *ctime_r(const time_t *, char *, int);
extern struct tm *gmtime_r(const time_t *, struct tm *);
extern struct tm *localtime_r(const time_t *, struct tm *);
#endif

#ifdef __cplusplus
}
#endif
#endif /* !__TIME_H__ */
