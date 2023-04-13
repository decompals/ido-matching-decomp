#ifndef __FB_H__
#define __FB_H__

#include <sys/types.h>
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
typedef __uint64_t	FB_offset;
typedef __uint64_t	FB_xword;
typedef __uint32_t	FB_word;
typedef unsigned short	FB_half;

/* file header:  must be at the beginning of the file */
typedef struct {
    char	fb_ident[16];	    /* ident string */
    FB_word	fb_size;	    /* size in bytes of the all the section
				       headers */
    FB_offset	fb_shoff;	    /* file offset to section header */
    FB_word	fb_entsize;	    /* size of each section header */
    FB_half	fb_major_version;   /* major version number */
    FB_half	fb_minor_version;   /* minor version number */
    FB_word     fb_str_index;	    /* string index of the section header */
    FB_word	fb_align;	    /* alignment */
    FB_xword	fb_reserved[4];	    /* not used for now */
} FB_header;

#define FB_IDENT_STR	"!!SGIfeedback!!" /* 15 bytes + null termination */

#define FB_MAJOR_REV	0	    /* major version number */
#define FB_MINOR_REV	0	    /* minor version number */

/* section header table: must be 8-byte aligned */
typedef struct {
    FB_offset	sh_shoff;	    /* file offset of this section */
				    /* file offset must be 8-byte aligned */
    FB_word	sh_size;	    /* size in bytes of this section */
    FB_half	sh_type;	    /* type id of this section */
    FB_half	sh_entsize;	    /* size of each record */
    FB_word	sh_flags;	    /* misc info */
    FB_word	sh_align;	    /* alignment of the section */
    FB_word	sh_reserved[3];	    /* reserved */
} FB_sec_header;

#define FB_SHT_NULL	0
#define FB_SHT_STR	1	    /* string table */
#define FB_SHT_PROC	2	    /* procedure */
#define FB_SHT_CALL	3	    /* call-site */
#define FB_SHT_BB	4	    /* basic block */
#define FB_SHT_NUM      5	    /* Number of sections including NULL */

/* describes one procedure */
typedef struct fb_per_proc {
    FB_word	p_start_line;	    /* starting line number */
    FB_word	p_invocations;      /* proc invocation count */
    FB_xword	p_cycles;	    /* cycles based on pixie BB counts */
    FB_offset	p_filename_off;     /* section offset to the filename string */
    FB_offset	p_procname_off;     /* section offset to the procedure name */
	/* proc call info */
    FB_word	p_call_index;       /* index into the CALL section */
    FB_word	p_call_num;         /* number of callers to this proc */
	/* bb info */
    FB_word	p_bb_index;	    /* index into the BB section */
    FB_word	p_bb_num;	    /* number of bb's in this proc */
	/* reserved */
    FB_word	p_reserved[2];   /* reserved */
} FB_per_proc;

/* describes one point-of-call */
typedef struct fb_per_call {
    FB_word	c_relative_line; /* from begin of procedure */
    FB_word	c_invocations;   /* invocation count */
    FB_word	c_caller_idex;   /* index into the proc array */
} FB_per_call;

/* describes one basic block */
typedef struct fb_per_bb {
    FB_word	bb_relative_line;   /* from begin of procedure */
    FB_word	bb_freq;	    /* execution count */
    FB_half	bb_column;          /* column number*/
    FB_half     bb_unused;	    /* available for future use */
} FB_per_bb;
#endif
