#ifndef __ERRNO_H__
#define __ERRNO_H__
#ifdef __cplusplus
extern "C" {
#endif
#ident "$Revision: 1.22 $"
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



/*
 * Error codes
 */

#include <sys/errno.h>

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))

#if !defined(_SGI_MP_SOURCE)
extern int errno;
#endif

#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
extern char *   sys_errlist[];
extern int      sys_nerr;

extern int      oserror(void);
extern int      setoserror(int);
extern int      goserror(void);

#if defined(_SGI_MP_SOURCE)
#define errno	(*__oserror())
extern int      *__oserror(void);
#endif

#endif /* _SGI_SOURCE && !_POSIX_SOURCE && !_XOPEN_SOURCE */

#endif /* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */
#ifdef __cplusplus
}
#endif
#endif /* !__ERRNO_H__ */
