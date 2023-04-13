#ifndef __COMPACT_RELOC_H__
#define __COMPACT_RELOC_H__

#ifdef __cplusplus
extern "C" {
#endif

#if 1
/* Old compact relocation format for pre-4.00 compilers */

#include <sgidefs.h>

typedef struct {
    unsigned cm_tag;
    union {
	__uint32_t cm_val;
	__uint32_t cm_ptr;
    } cm_un;
} CM;

#define CM_NULL            0x00000000
#define CM_RELOC_NO        0x00000001
#define CM_RELOC_PTR       0x00000002  

struct full_rlc {
    int type;
    __uint32_t konst;
    __uint32_t vaddr;
    __uint32_t dist2lo;
};

#define CM_R_TYPE_NULL      0
#define CM_R_TYPE_ABS       1
#define CM_R_TYPE_REL32     2
#define CM_R_TYPE_WORD      3
#define CM_R_TYPE_GPHI_LO   4
#define CM_R_TYPE_GOTHI_LO  5
#define CM_R_TYPE_JMPADDR   5	/* this is obsolete and should go away */
#define CM_R_TYPE_GPHI_LO2  6
#define CM_R_TYPE_HI_LO	    7

typedef struct {
    char *scn_praw;
    char *rlc_ptr;
    char *cur_rlc_ptr;
    __uint32_t  rlc_no;
    __uint32_t  cur_rlc_no;
    __uint32_t last_base;
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
    __uint32_t addend_const;         /* k of addend */
};

struct COMPACT_RELOC_C_BASE {
    struct COMPACT_RELOC _rlc;
    __uint32_t addend_const;         /* k of addend */
    __uint32_t base;                 /* base for next delta */
};

struct COMPACT_RELOC_BASE {
    struct COMPACT_RELOC _rlc;
    __uint32_t base;                 /* base for next delta */
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

#else /* _OLD_COMPACT_RELOC_FORMAT_ */

/* Compact relocation format used by v4.00 and newer compilers */

/*
 * Header structure for .MIPS.compact_rel
 * section.
 */
#pragma pack(1)
struct cm64_header {
    __uint64_t	cmh_vaddr;	    /* addr of the 1st cmr_targ  */
    unsigned	cmh_version :8;	    /* record format version */
    unsigned	cmh_extra   :24;    /* unused; should be zero */
};

struct cm32_header {
    __uint32_t	cmh_vaddr;	    /* addr of the 1st cmr_targ  */
    unsigned	cmh_version :8;	    /* record format version */
    unsigned	cmh_extra   :24;    /* unused; should be zero */
};

/*
 * Packages the first three fields
 * of a compact relocation record.
 */
struct cm_rel {
    unsigned	cmr_extra_type:5;   /* encode the # of extra fields */
#define CM_REL_NULL	    0	    /* no extra field */
#define CM_REL_PAIR	    1	    /* has disp. to corresponding pair */
#define CM_REL_WATCH	    2	    /* has sect. offset of watched addr. */
#define CM_REL_W_INDEX	    4	    /* sect. index for watched addr > 6 bits */

    unsigned	cmr_rel_type:5;	    /* compact relocation type */
#define CM_R_TYPE_NULL      0
#define CM_R_TYPE_REL32     2 
#define CM_R_TYPE_WORD      3 
#define CM_R_TYPE_GPHI_LO   4
#define CM_R_TYPE_GOTHI_LO  5

    unsigned	cmr_watch_index:6;  /* sect. index for watched addr */
};
#pragma pack(0)

/*
 * Passed back by utility to get the
 * next compact relocation record. I
 * include both the full watch address
 * and it's section offset because I'm
 * not sure this utility will have access 
 * to the section table.
 */
struct cm_rel_full {
    __psunsigned_t	cmrf_loc_addr;
    __psunsigned_t	cmrf_pair_addr;
    __psunsigned_t	cmrf_watch_addr;
    __psunsigned_t	cmrf_watch_offset;
    __uint32_t		cmrf_watch_index;
    __uint32_t		cmrf_rel_type;
};

#endif /* _OLD_COMPACT_RELOC_FORMAT_ */
    
#ifdef __cplusplus
}
#endif

#endif  /* __COMPACT_RELOC_H__ */
