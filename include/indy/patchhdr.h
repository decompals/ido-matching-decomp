/****************************************************************/
/*	Copyright (c) 1992, Silicon Graphics, Incorporated	*/
/*			All Rights Reserved			*/
/****************************************************************/
/* $Revision: 1.3 $ */

/*******************************************************************/
/*								   */
/*  This file contains the description of new data which is being  */
/*  put into the end of the .init section.  It consists of a set   */
/*  of patches to code in the .text section.  Each patch is given  */
/*  as a pair - 'address/value'.  It is stored in the .init section*/
/*  with the patchhdr structure at the very end preceeded by the   */
/*  patch pairs.  This facilites exec looking for the magic value. */
/*								   */
/*  This patch capability was created to allow a single executable */
/*  to run on both R3000 and R4000 2.x systems (which have known   */
/*  instruction bugs).						   */
/*								   */
/*  Two flag bits in the file header f_flags field indicate to     */
/*  exec if the executable is "safe" to run, either because the    */
/*  code is "pure" or it contains a .patch section.		   */
/*								   */
/*******************************************************************/

#ifndef __PATCHHDR_H__
#define __PATCHHDR_H__

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))

struct patchhdr {
	long	p_version;	/* patch version number		     */
	long	p_count;	/* count of address/value pairs      */
	long	p_filler;	/* filler			     */
	long	p_magic;	/* magic value = "Mbug"		     */
	};

struct patchpair {
	long	p_address;	/* patch address		     */
	long	p_value;	/* patch value			     */
	};

#define R4K_JR_CLEAN    0x0200	/* jr clean bit    (filehdr.f_flags) */
#define R4K_FPDIV_CLEAN 0x0400	/* fpdiv clean bit (filehdr.f_flags) */

#define	R4K_PATCH_MAGIC 0x4D627567	/* magic value = "Mbug"	     */

#endif /* _LANGUAGE_C */

#ifdef _LANGUAGE_PASCAL

type
  patchhdr = packed record
      p_version : long;		/* patch version number 	     */
      p_count   : long;		/* count of address/value pairs      */
      p_filler  : long;		/* filler			     */
      p_magic   : long;		/* magic value = "Mbug"		     */
    end {record};

type
  patchpair = packed record
      p_address : long; 	/* patch version number 	     */
      p_value   : long;		/* count of address/value pairs      */
    end {record};

#define R4K_JR_CLEAN    16#0200	/* jr clean bit    (filehdr.f_flags) */
#define R4K_FPDIV_CLEAN 16#0400	/* fpdiv clean bit (filehdr.f_flags) */

#define	R4K_PATCH_MAGIC 16#4D627567	/* magic value = "Mbug"	     */

#endif /* _LANGUAGE_PASCAL */

#ifdef __cplusplus
}
#endif

#endif /* ifndef __PATCHHDR_H__ */
