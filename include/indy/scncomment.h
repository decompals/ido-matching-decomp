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
#ifndef __SCNCOMMENT_H__
#define __SCNCOMMENT_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned cm_tag;
    union {
	unsigned long cm_val;
	unsigned long cm_ptr;
    } cm_un;
} CM;

#define CM_NULL            0x00000000
#define CM_RELOC_NO        0x00000001
#define CM_RELOC_PTR       0x00000002  

struct full_rlc {
    int type;
    unsigned long konst;
    unsigned long vaddr;
    unsigned long dist2lo;
};

#define CM_R_TYPE_NULL      0
#define CM_R_TYPE_ABS       1
#define CM_R_TYPE_REL32     2
#define CM_R_TYPE_WORD      3
#define CM_R_TYPE_GPHI_LO   4
#define CM_R_TYPE_JMPADDR   5
#define CM_R_TYPE_GPHI_LO2  6

/* we don't consider 64 bits rightnow, when we do, we have to extend the */
/* type field                                                            */
#if 0
#define CM_R_TYPE_HI_LO64   7
#define CM_R_TYPE_WORD64    8
#define CM_R_TYPE_REL64     9
#endif


typedef struct {
    char *scn_praw;
    char *rlc_ptr;
    char *cur_rlc_ptr;
    int  rlc_no;
    int  cur_rlc_no;
    unsigned long last_base;
    struct full_rlc rlc_entry;
} cm_struct ;


/* this struct must be the same as next, except for the last item, */
/* which is the constant for the addend */
struct COMPACT_RELOC {
    unsigned addend:  2;
#define        ADDEND_NOCONST  0
#define        ADDEND_CONST    1   /* if an addend included, e.g. sym + k */
#define        ADDEND_BASE     2   /* base of address to be relocated */
    unsigned type:    3;           /* relocation type */
    unsigned del_lo:  8;           /* delta to ref_lo from ref_hi, shifted 2 */
    
    signed del_vaddr: 19;          /* delta addr, from previous entry */
                                   /* to be relocated */
#define        DEL_VADDR_MASK   0xFFFF8000
};


struct COMPACT_RELOC_C {
    struct COMPACT_RELOC _rlc;
    unsigned addend_const;         /* k of addend */
};

struct COMPACT_RELOC_C_BASE {
    struct COMPACT_RELOC _rlc;
    unsigned addend_const;         /* k of addend */
    unsigned base;                 /* base for next delta */
};

struct COMPACT_RELOC_BASE {
    struct COMPACT_RELOC _rlc;
    unsigned base;                 /* base for next delta */
};


union cm_rlc {
    struct COMPACT_RELOC            r;
    struct COMPACT_RELOC_C_BASE    cb;
    struct COMPACT_RELOC_C          c;
    struct COMPACT_RELOC_BASE       b;
};


#define VADDR_OVFL(delta)  (((delta & DEL_VADDR_MASK) != 0) && \
			    ((delta & DEL_VADDR_MASK) != DEL_VADDR_MASK))

#define VADDR_DELTA(delta) (delta & ~DEL_VADDR_MASK)

#ifdef __cplusplus
}
#endif

#endif  /* __SCNCOMMENT_H__ */
