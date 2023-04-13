/* Copyright (C) 1989 Silicon Graphics, Inc. All rights reserved.  */
/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991, 1990 MIPS Computer Systems, Inc.      |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 252.227-7013.  |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Avenue                               |
 * |         Sunnyvale, California 94088-3650, USA             |
 * |-----------------------------------------------------------|
 */
/*
 * Command Response Packet interface for visual debuggers.
 */
#ifndef __VDCOMRES_H__
#define	__VDCOMRES_H__

#ifdef __cplusplus
extern "C" {
#endif

#define	CRPMAGIC	0xdeadbeef	/* command packet identifier */
#define	CRPBUFLEN	512		/* program output buffer length */
#define	CRPNAMLEN	80		/* maximum channel/name length */

/*
 * Command response packets.  These are sent from the debugger to
 * the command response machine.  These are the only data types
 * sent from the debugger after its initial comeup messages.
 */
typedef struct _com_res {
#ifdef DEBUGGER
    unsigned long   magic;		/* Magic number to find it. */
#endif
    unsigned char   command;		/* command type code */
    char	    channel[CRPNAMLEN];	/* channel name */
    unsigned	    stop;		/* stop number */
    char	    file[CRPNAMLEN];	/* file name */
    unsigned	    lineno;		/* line number */
    char	    msg[CRPBUFLEN];	/* message text */
} CommandResponsePkt;

/*
 * Command Packet Types
 */
#define	x_file		 0
#define	x_stopin	 1
#define	x_stopat	 2
#define	x_run		 3
#define	x_rerun		 4
#define	x_cont		 5
#define	x_step		 6
#define	x_next		 7
#define	x_use		 8
#define	x_func		 9
#define	x_prompt	10
#define	x_trace		11

#define	x_up		12
#define	x_down		13
#define	x_updown	14
#define	x_delete	15
#define	x_break		16

#define x_ready		29
#define	x_unknown	30
#define	x_debugger	31

#define	x_null		99

/*
 * Everyday, ordinary text being displayed to user (like dbx startup
 * messages) should come in with a command `x_unknown', probably with
 * channel set to "unknown".
 *
 * ALWAYS send current active filename, the name that would be printed
 * if the user were to type file\n in dbx.  Send this with as many
 * of the different commands as possible.  In fact, always make an attempt
 * to fill out every field in the packet with as much information as
 * is valid and known as possible.  This'll prevent a lot of packet
 * redesign in the future ...
 */

#ifdef __cplusplus
}
#endif

#endif /* __VDCOMRES_H__ */
