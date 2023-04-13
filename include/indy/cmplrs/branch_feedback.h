#ifndef _BRANCH_FEEDBACK_H
#define _BRANCH_FEEDBACK_H

/*
	branch.h
		
	Hold format of feed back file generated for cord2 

	Format:

	--------------------------------
	|	identifier             |
	|    3 bytes id, 1 byte ver    |
	--------------------------------
	|            seg 0             |
	--------------------------------
	|            seg 1             |
	--------------------------------
	...
	--------------------------------
	|                              |
	|    branch entries (seg 0)    |
	|                              |
	--------------------------------
	|			       |
	|    gprof entries (seg 0)     |
	|                              |
	--------------------------------
	--------------------------------
	|                              |
	|    branch entries (seg 1)    |
	|                              |
	--------------------------------
	|			       |
	|    gprof entries (seg 1)     |
	|                              |
	--------------------------------
	....
	....


	The header points off to the first segment header, where
	all the segment headers are stored as an array. Each
	segment header has pointers to both its branch information
	and its gprof information. 

	The branch information is sorted by instruction offset 
	of branch site, and the gprof information is sorted
	by caller site. There could be multiple occurances of 
	a caller site, since a caller site can call different 
	targets. 


*/

#define BR_VERSION 	1

#define BR_NIDENT	4
#define BR_MAG0		0x7f
#define BR_MAG1		'B'
#define BR_MAG2		'r'

#define IS_BRFILE(hdr) \
	( ((hdr).h_id[0] == BR_MAG0) && \
	  ((hdr).h_id[1] == BR_MAG1) && \
	  ((hdr).h_id[2] == BR_MAG2))

#define IS_CORRECT_VERSION(hdr) \
	((hdr).h_id[3] == BR_VERSION)

typedef struct br_hdr_s {
    unsigned char 	h_id[BR_NIDENT];    /* identifier */
    __uint32_t		h_hdr_size;	    /* size of this header */
    __uint32_t		h_seg_size;	    /* size of seg hdr */
    __uint32_t		h_br_entry_size;    /* size of a branch entry */
    __uint32_t		h_gprof_entry_size; /* size of a gprof entry */
    __uint32_t		h_num_segs;
    __uint32_t		h_seg_ptr;	    /* file offset to first */
} br_hdr;

typedef struct br_seg_s {
    __uint32_t		s_checksum;
    __uint64_t		s_text_low;
    __uint64_t		s_text_high;
    __uint32_t		s_num_br;      /* number of entries for 
					     branch taken/not taken */
    __uint32_t		s_num_gprof;   /* number of gprof entries */
    __uint32_t		s_br_ptr;      /* file offset to branch info */
    __uint32_t		s_gprof_ptr;   /* file offset to gprof info */
} br_seg;

typedef struct br_branch_entry_s {
    __uint32_t		b_ioffset;     /* instruction offset */
    __uint32_t		b_taken;       /* Number of times taken */
    __uint32_t		b_not_taken;   /* Number of times not taken */
} br_branch_entry;

typedef struct br_gprof_entry_s {
    __uint32_t		g_ioffset;     /* instruction offset */
    __uint32_t		g_targ_ioffset;/* callee offset (MAX_UINT if
					  external call */
    __uint32_t		g_num_calls;   /* number of calls from this 
					  site */
} br_gprof_entry;

#endif /* ifndef _BRANCH_FEEDBACK_H */
