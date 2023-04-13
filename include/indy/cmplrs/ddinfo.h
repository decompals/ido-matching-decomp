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
#ifndef __DDINFO_H
#define __DDINFO_H

#ifdef INCLUDE_ID
static char *skel_h_id="$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/ddinfo.h,v 1.2 1992/06/26 14:22:49 daveb Exp $";
#endif

typedef enum
{
	dd_LOOP_INDEPENDENT,
	dd_TRUE,
	dd_ANTI,
	dd_CONTROL,
	dd_OUTPUT,
	dd_INPUT
} DEP_KIND;

#endif
