#ifndef __SYM_AUX_H__
#define __SYM_AUX_H__

/*
 * This file contains structures that reference data structures
 * defined in <sym.h>. These can be look upon as extensions to
 * the existing structures.
 */

	/*****************************************

    There will be one structure for each static function where there
    exists exception handling information. These structures will make
    up a table packaged in the following section:

	sh_name;	.MIPS.pdr_exception
	sh_type;	SHT_MIPS_PDR_EXCEPTION
	sh_flags;	SHF_MIPS_NOSTRIP
	sh_addr;	0
	sh_offset;	offset in .o
	sh_size;	sh_entsize * (number of entrys)
	sh_link;	index to associated string table
	sh_info;	0
	sh_addralign;	4
	sh_entsize;	12 -> sizeof(struct exception_pdr)

	 *****************************************/
typedef struct exception_pdr {
	unsigned ep_pdr;	 /* Index into the pdr array of the mdebug
				    section for the function in question. */
	unsigned ep_sec_index; /* Index of section where exception routine
				    resides. */
	unsigned ep_sec_offset;/* Offset from beginning of ep_sect_index
				    section that exception routine resides. */
} PDR_AUX, *pPDR_AUX;

#endif /* !__SYM_AUX_H__ */
