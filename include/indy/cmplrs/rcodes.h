/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */

/*
 * Return Codes used by the compiler phases,
 * used to communicate between the driver and its children.
 */

#ifndef __RCODES_H
#define __RCODES_H

#ifdef INCLUDE_ID
static char *rcodes_h_id="$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/rcodes.h,v 1.4 1996/03/28 01:14:48 mpm Exp $";
#endif

/* 
 * Ucode return codes
 */
#define EXEC_UMERGE	255	/* call umerge */

/*
 * Mongoose return codes
 */

#define RC_OKAY			0	/* executed successfully */
#define RC_INTERNAL_ERROR	1	/* a compiler error */
#define RC_USER_ERROR		2	/* a user error */
#define RC_NORECOVER_USER_ERROR	4	/* a user error can't recover from */
#define RC_UNIMPLEMENTED_ERROR	8	/* uses an unimplemented feature */
#define RC_NEED_INLINER		16	/* flag that we need the inliner */
#define RC_SYSTEM_ERROR		32	/* a O/S or environment error */
#define RC_OVERFLOW_ERROR	64	/* an overflow error; try recompiling */

#endif
