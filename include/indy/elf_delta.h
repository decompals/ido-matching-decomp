#ifndef __ELF_DELTA_H__
#define __ELF_DELTA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <elf.h>

/*      Copyright (c) 1990, 1991 UNIX System Laboratories, Inc. */
/*      Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T   */
/*        All Rights Reserved   */
/*      THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF          */
/*      UNIX System Laboratories, Inc.                          */
/*      The copyright notice above does not evidence any        */
/*      actual or intended publication of such source code.     */
/*
 * Copyright 1992 Silicon Graphics,  Inc.
 * ALL RIGHTS RESERVED
 * 
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
 * The copyright notice above does not evidence any  actual  or
 * intended  publication of this source code and material is an
 * unpublished work by Silicon  Graphics,  Inc.  This  material
 * contains CONFIDENTIAL INFORMATION that is the property and a
 * trade secret of Silicon Graphics, Inc. Any use,  duplication
 * or  disclosure  not  specifically  authorized  in writing by
 * Silicon Graphics is  strictly  prohibited.  THE  RECEIPT  OR
 * POSSESSION  OF  THIS SOURCE CODE AND/OR INFORMATION DOES NOT
 * CONVEY ANY RIGHTS TO REPRODUCE, DISCLOSE OR  DISTRIBUTE  ITS
 * CONTENTS,  OR  TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT
 * MAY DESCRIBE, IN WHOLE OR IN PART.
 * 
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND
 * Use, duplication or disclosure by the Government is  subject
 * to  restrictions  as  set  forth  in  FAR 52.227.19(c)(2) or
 * subparagraph (c)(1)(ii) of the Rights in Technical Data  and
 * Computer  Software  clause  at  DFARS 252.227-7013 and/or in
 * similar or successor clauses in the FAR, or the DOD or  NASA
 * FAR  Supplement.  Unpublished  --  rights reserved under the
 * Copyright Laws of the United States. Contractor/manufacturer
 * is Silicon Graphics, Inc., 2011 N. Shoreline Blvd., Mountain
 * View, CA 94039-7311
 */

#define DELTA32_EMPTY_SYM 0xffffff
/*
 * Class information structure
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct
{
	Elf32_Word	ci_name;
	Elf32_Word	ci_info;
} Delta32_ClassInfo;
#endif /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

#define DELTA32_CI_SIZE		(sizeof(Delta32_ClassInfo))

#define	DELTA32_ICI_TYPE(i)	((i)>>24)
#define	DELTA32_ICI_ALIGN(i)	(((i)>>16)&0xff)
#define	DELTA32_ICI_SYM(i)	((i)&0xffffff)
#define	DELTA32_ICI_ASIZE(i)	((i)&0xffff)
#define	DELTA32_ICI_BSIZE(i)	(((i)>>8)&0xff)
#define	DELTA32_ICI_BFSIZE(i)	((i)&0xff)

#define DELTA32_CI_NAME(ci)     ((ci)->ci_name)
#define DELTA32_CI_INFO(ci)     ((ci)->ci_info)
#define DELTA32_CI_TYPE(ci)     DELTA32_ICI_TYPE((ci)->ci_info)
#define DELTA32_CI_ALIGN(ci)    DELTA32_ICI_ALIGN((ci)->ci_info)
#define DELTA32_CI_SYM(ci)      DELTA32_ICI_SYM((ci)->ci_info)
#define DELTA32_CI_ASIZE(ci)    DELTA32_ICI_ASIZE((ci)->ci_info)
#define DELTA32_CI_BSIZE(ci)    DELTA32_ICI_BSIZE((ci)->ci_info)
#define DELTA32_CI_BFSIZE(ci)   DELTA32_ICI_BFSIZE((ci)->ci_info)

#define	DELTA32_ICI_SET_TYPE(i,v)   (i = (((i)&0xffffff)|((v)<<24)))
#define	DELTA32_ICI_SET_ALIGN(i,v)  (i = (((i)&0xff00ffff)|(((v)&0xff)<<16)))
#define	DELTA32_ICI_SET_SYM(i,v)    (i = (((i)&0xff000000)|((v)&0xffffff)))
#define	DELTA32_ICI_SET_ASIZE(i,v)  (i = (((i)&0xffff0000)|((v)&0xffff)))
#define	DELTA32_ICI_SET_BSIZE(i,v)  (i = (((i)&0xffff00ff)|(((v)&0xff)<<8)))
#define	DELTA32_ICI_SET_BFSIZE(i,v) (i = (((i)&0xffffff00)|((v)&0xff)))

#define DELTA32_CI_SET_NAME(ci,v)   ((ci)->ci_name = (v))
#define DELTA32_CI_SET_INFO(ci,v)   ((ci)->ci_info = (v))
#define	DELTA32_CI_SET_TYPE(ci,v)   DELTA32_ICI_SET_TYPE((ci)->ci_info,v)
#define	DELTA32_CI_SET_ALIGN(ci,v)  DELTA32_ICI_SET_ALIGN((ci)->ci_info,v)
#define	DELTA32_CI_SET_SYM(ci,v)    DELTA32_ICI_SET_SYM((ci)->ci_info,v)
#define	DELTA32_CI_SET_ASIZE(ci,v)  DELTA32_ICI_SET_ASIZE((ci)->ci_info,v)
#define	DELTA32_CI_SET_BSIZE(ci,v)  DELTA32_ICI_SET_BSIZE((ci)->ci_info,v)
#define	DELTA32_CI_SET_BFSIZE(ci,v) DELTA32_ICI_SET_BFSIZE((ci)->ci_info,v)

#define CI_BEGIN		0
#define CI_CLASS_INFO		1
#define CI_END			2
#define CI_DATA			3
#define CI_CLASS_DATA		4
#define CI_CLASS_DATA_CLASS	5
#define CI_BITFIELD_DATA	6
#define CI_STATIC_DATA		7
#define	CI_FUNCTION		8
#define CI_VIRTUAL_FUNCTION	9
#define CI_STATIC_FUNCTION	10
#define CI_BASE			11
#define CI_VIRTUAL_BASE		12
#define CI_STATIC_BASE		13
#define	CI_STATIC_VIRTUAL_BASE	14
#define	CI_PUBLIC		15
#define	CI_PROTECTED		16
#define	CI_PRIVATE		17
#define	CI_BEGIN_ANON_UNION	18
#define	CI_END_ANON_UNION	19
#define CI_PURE_VIRTUAL_FUNCTION 20
#define	CI_VPTR			21
#define	CI_VBASEPTR		22
#define	CI_EXTRA		23
#define CI_NONDYN_CLASS_INFO	24

#define	CI_EMPTY_ENTRY		0xff

/*
 *
 * There are three types of this record.  All types have one byte
 * of ci_info reserved to specify type.
 *
 * S:	TYPE; SYM
 * A: 	TYPE; ALIGN; ASIZE
 * B:	TYPE; ALIGN; BSIZE; BFSIZE
 *
 * TYPE			Type	Comment
 *
 * BEGIN		S	Indx to END+1
 * CLASS_INFO		S	Indx to DeltaSym
 * END			S	Indx to BEGIN
 * DATA			A
 * CLASS_DATA		A
 * CLASS_DATA_CLASS	S	Indx to DeltaSym
 * BITFIELD_DATA	B
 * STATIC_DATA		S	Indx to dynsym
 * FUNCTION		S	Indx to dynsym
 * VIRTUAL_FUNCTION	S	Indx to dynsym	
 * STATIC_FUNCTION	S	Indx to dynsym
 * BASE			S	Indx to DSym
 * VIRTUAL_BASE		S	Indx to DSym
 * STATIC_BASE		A
 *
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct
{
	Elf32_Word	ds_name;
	Elf32_Word	ds_info;
	Elf32_Addr	ds_value;
} Delta32_Sym;
#endif /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

/*
 * Macros to decode the ds_info field.
 */

#define DELTA32_DS_SIZE		(sizeof(Delta32_Sym))
#define DELTA32_DS_CONTBIT      0x80

#define	DELTA32_IDS_TYPE(i)	((i)&0x7f)
#define	DELTA32_IDS_CONT(i)	((i)&DELTA32_DS_CONTBIT)
#define	DELTA32_IDS_CLSNDX(i)	((i)>>8)

#define DELTA32_DS_NAME(ds)     ((ds)->ds_name)
#define DELTA32_DS_INFO(ds)     ((ds)->ds_info)
#define DELTA32_DS_VALUE(ds)    ((ds)->ds_value)
#define DELTA32_DS_TYPE(ds)     DELTA32_IDS_TYPE((ds)->ds_info)
#define DELTA32_DS_CONT(ds)     DELTA32_IDS_CONT((ds)->ds_info)
#define DELTA32_DS_CLSNDX(ds)   DELTA32_IDS_CLSNDX((ds)->ds_info)

#define	DELTA32_IDS_SET_TYPE(i,v)	(i = (((i)&0xffffff80)|((v)&0x7f)))
#define	DELTA32_IDS_SET_CONT(i,v)	(i = (((i)&0xffffff7f)|(((v!=0)?1:0)<<7)))
#define	DELTA32_IDS_SET_CLSNDX(i,v)	(i = (((i)&0xff)|((v)<<8)))

#define DELTA32_DS_SET_NAME(ds,v)     ((ds)->ds_name = (v))
#define DELTA32_DS_SET_INFO(ds,v)     ((ds)->ds_info = (v))
#define DELTA32_DS_SET_VALUE(ds,v)    ((ds)->ds_value = (v))
#define DELTA32_DS_SET_TYPE(ds,v)     DELTA32_IDS_SET_TYPE((ds)->ds_info,v)
#define DELTA32_DS_SET_CONT(ds,v)     DELTA32_IDS_SET_CONT((ds)->ds_info,v)
#define DELTA32_DS_SET_CLSNDX(ds,v)   DELTA32_IDS_SET_CLSNDX((ds)->ds_info,v)

/* put DS_TYPE values here */

#define	DS_OFFSET	0   /* Offset to member */
#define	DS_VFUNCOFF	1   /* offset in virtual function table for member function */
#define	DS_CLSIZE	2   /* Size of the class */
#define	DS_STMEM	3   /* Static member variable */
#define	DS_CLALIGN	4   /* Alignment of the class */
#define	DS_VBSOFF	5   /* Offset to virtual base class pointer */
#define	DS_CLOFF	6   /* Offset to base class */
#define	DS_LFTSFT	7   /* Left shift for bit fields */
#define	DS_RHTSFT	8   /* Right shift for bit fields */
#define	DS_INVSFT	9   /* Inverse shift for bit fields */
#define	DS_FLDMSK      10   /* Bit field mask - right shifted */
#define	DS_IFLDMSK     11   /* Bit field mask - in place */
#define	DS_FUNC	       12   /* Member function */
#define	DS_THISOFF     13   /* This offset when calling a member function */
#define	DS_VTHISOFF    14   /* This offset when calling a virtual member function */
#define	DS_VPTROFF     15   /* Offset to vptr for calling virtual member function */
#define	DS_VDATAOFF    16   /* Offset to data field in virtual function table */
#define	DS_PMINIT1     17   /* Word 1 of initialization of pointer to member function */
#define	DS_PMINIT2     18   /* Word 2 of initialization of pointer to member function */
#define	DS_PMINIT3     19   /* Word 3 of initialization of pointer to member function */
#define	DS_PMDATA      20   /* Initialization of pointer to data member */
#define	DS_BGNBLK      21   /* Begining of block that contains local class instances */
#define	DS_LCLINST     22   /* Local instance */
#define	DS_ENDBLK      23   /* End of block that contains local class instances */
#define	DS_QUAL	       24   /* Qualifier entry */
#define	DS_VALUE       25   /* Value entry for ptr to member function */
#define	DS_QVALUE      26   /* Qualified Value entry for ptr to member function */
#define	DS_VCLSOFF      27   /* Offset to virtual base class */
#define	DS_VBSPFUN     28   /* Offset to virtual base pointer when calling specified function */
#define	DS_VBSPINST    29   /* Offset to virtual base pointer when accessing specified instance member */

#define	DS_EMPTY_ENTRY	0x7f

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct
{
	Elf32_Word	cn_info;
	Elf32_Word	cn_count;
	Elf32_Word	cn_symndx;
} Delta32_ClassInstance;
#endif /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */
/*
 * Macros to decode the cn_info field.
 */

#define DELTA32_CN_SIZE		(sizeof(Delta32_ClassInstance))

#define DELTA32_ICN_TYPE(i)     ((i)&0xff)
#define DELTA32_ICN_CLSNDX(i)   ((i)>>8)

#define DELTA32_CN_INFO(cn)     ((cn)->cn_info)
#define DELTA32_CN_TYPE(cn)     DELTA32_ICN_TYPE((cn)->cn_info)
#define DELTA32_CN_CLSNDX(cn)   DELTA32_ICN_CLSNDX((cn)->cn_info)
#define DELTA32_CN_COUNT(cn)    ((cn)->cn_count)
#define DELTA32_CN_SYMNDX(cn)   ((cn)->cn_symndx)

#define DELTA32_ICN_SET_TYPE(i,v)     (i = (((i)&0xffffff00)|((v)&0xff)))
#define DELTA32_ICN_SET_CLSNDX(i,v)   (i = (((i)&0xff)|((v)<<8)))

#define DELTA32_CN_SET_INFO(cn,v)     ((cn)->cn_info = (v))
#define	DELTA32_CN_SET_TYPE(cn,v)     DELTA32_ICN_SET_TYPE((cn)->cn_info,(v))
#define DELTA32_CN_SET_CLSNDX(cn,v)   DELTA32_ICN_SET_CLSNDX((cn)->cn_info,(v))
#define DELTA32_CN_SET_COUNT(cn,v)    ((cn)->cn_count = (v))
#define DELTA32_CN_SET_SYMNDX(cn,v)   ((cn)->cn_symndx = (v))


/* put CN_TYPE values here */

#define CN_INSTANCE  0		/* class instances */
#define CN_RT_INFO   1		/* runtime class info */
#define	CN_LOCAL_INSTANCE 2	/* local class instance */

#define CN_EMPTY_ENTRY 0xff

#define CXX_DELTA_VERSION 1

#ifdef __cplusplus
}
#endif

#endif /* __ELF_DELTA_H */
