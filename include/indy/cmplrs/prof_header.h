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
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/prof_header.h,v 7.5 1992/05/11 09:48:26 davea Exp $ */
/* Definition of the header for a "mon.out" profile data file, or for */
/* a "bbcounts/bbaddrs" pair of files.				      */
#define BBADDRS_MAGIC 0x0f0e0010
#define BBCOUNTS_MAGIC 0x0f0e0011
#define ICOUNTS_MAGIC 0x0f0e0012

#ifdef _STATIC_SHARED_LIBRARIES
#define BBADDRS_MAGIC_2 0x0f0e0020 /* Shared library version, for pixie */
#define BBCOUNTS_MAGIC_2 0x0f0e0021 /* Shared library version, for pixie*/
#endif

#define ADDHASH(v, w) \
	((v) = ((v) << 5) ^ ((v) >> (32-5)) ^ (w))

#define MAGIC 0x0f0e0000
#define HAS_PC_SAMPLES 1
#define HAS_INV_COUNTS 2
#define HAS_BB_COUNTS 4

struct prof_header {
   /* A magic number which tells "mprof" what data to expect in the
     profile output file, using the "define"s above */
   int p_opt_value;
   /* Lower and upper limits of pc values for pc-sampling */
   char *low_pc;
   char *high_pc;
   /* Size of the pc-sampling array, bytes */
   int pc_buf_size;
   /* Size of the bb-counting array, bytes */
   int count_buf_size;
   };

#define BB_SCALE 2	/* bb array is always half the size of text segment */
#define SAMPLE_PERIOD 10.0e-3 /* interval between pc samples in seconds */


#ifdef _STATIC_SHARED_LIBRARIES
/* pixie, pixstats and prof 4.0.1.  Silicon Graphics. */
/* The following is the data structure in the a.out.pixie file
   which immediately precedes _P_pixiemap.
*/
struct pix_segment_map_s {
	unsigned px_counts_offset; /* stack offset of counts for this file */
	unsigned px_count_size;   /* length in words of counts area  for this*/
		/* in pixie, count_size is n_basic_blocks */
	unsigned px_text_high_addr; /* 1 above highest valid text address */
	unsigned px_text_low_addr;  /* lowest valid text address */
				    /* the range above is used to determine
				       which addresses belong to this count
                                       region
				    */
	unsigned px_map_address; /* vm addr of the map for this */
	unsigned px_idtrace; 	/* 0, no idtrace  1 itrace 3 i & dtrace */
	unsigned px_unused[10];
	unsigned px_reg_uses[32]; /* use counts per register */
	unsigned px_3way_regs[32]; /* each element non-zero if that register is
				      used in a 3way */
	unsigned px_tempreg1;		/* register number, is 31 */
	unsigned px_tempreg1_offset;    /* stack offset of user r31 */
	unsigned px_tempreg2;		/* register number */
	unsigned px_tempreg2_offset;    /* stack offset of user tempreg2 */
	unsigned px_tempreg3;		/* register number of data pointer */
	unsigned px_tempreg3_offset;    /* stack offset of user tempreg1 */
	unsigned px_n_instructions;	/* size of the original text */
};

/* 	The following is the leading set of data values in the
	.Addrs file. Following it is the data.
*/
struct pix_addrs_data_s {
	unsigned pa_magic;
	unsigned pa_text_hash; /* hash of original text */
	unsigned pa_counts_offset;
};

/* 	The following is the leading set of data values in the .Counts
	file.   Note it has a variable array pc_counts_info (which cannot
	be declared properly in C) whose actual number of elements is
	pc_number_of_records.

	The idea is that each  px_counts_offset gives a base from the
	end of the pc_counts_info array to the counts for one
	text section.   Matched with the .Addrs and a.out.pixie
	on pc_offset.  And px_count_size gives the size, in words, of
	the respective counts area.

	There can be unused areas in the actual Counts (but probably
	will not be).
	
	The Counts themselves are simply the run-time stack array
	written to disk in one write.
*/
struct pix_counts_data_s {
	unsigned pc_magic;  	      /* Counts magic number */
	unsigned pc_text_hash;	      /* hash of original text */
	unsigned pc_number_of_records;/* number of elements in following array*/
		/* fakes a variable size array here */
	struct pix_segment_map_s  pc_counts_info[1];
};
#endif
/*

A "mon.out" file consists of:

   struct prof_header the_header;
   unsigned pc_buffer[the_header.pc_buf_size];
   unsigned count_buffer[the_header.count_buf_size];

A "bbaddrs" file consists of:

   unsigned magic = BBADDRS_MAGIC;
   unsigned hash;
   unsigned addrs[n + 1];

A "bbcounts" file consists of:

   unsigned magic = BBCOUNTS_MAGIC;
   unsigned hash;
   unsigned count[n];

If the executable contains .init and .fini sections in addition to .text,
pixie and prof treat them as one continuous .text section.

To compute the hash, apply ADDHASH(hash, word) to each word of the text
section of the pre-pixie executable file. The addrs array gives the start
of each basic block, expressed as a word offset from the beginning of the
text. These offsets appear in increasing order.  The last element of the
array is the size of the text in words. The count array gives the number
of times the corresponding basic block was executed.

If any basic-block address in the addrs array is zero, then the
corresponding element of the count array is a branch-taken count.

*/
