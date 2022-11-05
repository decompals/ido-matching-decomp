/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _SYS_TTYDEV_H
#define _SYS_TTYDEV_H

/*	@(#)ttydev.h 2.6 88/02/08 SMI; from UCB 4.3 83/05/18	*/

/*
 * Terminal definitions related to underlying hardware.
 */

/*
 * Speeds
 */
#define	B0	0
#define	B50	0000001		/* not supported */
#define	B75	0000002
#define	B110	0000003
#define	B134	0000004
#define	B150	0000005
#define	B200	0000006		/* not supported */
#define	B300	0000007
#define	B600	0000010
#define	B1200	0000011
#define	B1800	0000012		/* not supported */
#define	B2400	0000013
#define	B4800	0000014
#define	B9600	0000015
#define	B19200	0000016
#define	EXTA	0000016
#define	B38400	0000017
#define	EXTB	0000017

#endif /*_SYS_TTYDEV_H */
