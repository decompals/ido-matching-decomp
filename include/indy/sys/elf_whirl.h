#ifndef __SYS_ELF_WHIRL_H__
#define __SYS_ELF_WHIRL_H__

/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/sys/RCS/elf_whirl.h,v 1.39 1996/08/26 19:53:06 rshapiro Exp $ */

/* Elf extension for WHIRL object files */

/* Revision Number: Should be incremented whenever INCOMPATIBLE changes are
   made.  This string is put in the ".comment" section.  Refer to ELF
   object file spec. for format */
#define WHIRL_REVISION	"WHIRL::0.28:"

/*
 * sh_info field for section of type SHT_MIPS_WHIRL 
 */

#define WT_NULL		0x0
#define WT_PU_SECTION	0x1	    /* all PU-specific information */
#define WT_GLOBALS	0x2	    /* WHIRL global symbol table */
#define WT_COMP_FLAGS	0x3	    /* compilation flags for this object */
#define WT_STRTAB	0x4	    /* WHIRL string table */
#define WT_CONSTAB	0x5	    /* WHIRL constant table */
#define WT_IPA_SUMMARY	0x6	    /* IPA summary information */
#define WT_DST		0x7	    /* WHIRL Debug Symbol Table */
#define WT_LOCALMAP	0x8	    /* IPAA local map */

/*
 * Special WHIRL section names.
 */
#define MIPS_WHIRL_PU_SECTION	".WHIRL.pu_section"
#define MIPS_WHIRL_GLOBALS	".WHIRL.globals"
#define MIPS_WHIRL_COMP_FLAGS	".WHIRL.flags"
#define MIPS_WHIRL_STRTAB	".WHIRL.strtab"
#define MIPS_WHIRL_CONSTAB	".WHIRL.constab"
#define MIPS_WHIRL_SUMMARY	".WHIRL.summary"
#define MIPS_WHIRL_DST		".WHIRL.dst"
#define MIPS_WHIRL_LOCALMAP	".WHIRL.localmap"

#endif /* __SYS_ELF_WHIRL_H__ */
