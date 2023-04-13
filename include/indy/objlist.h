#ifndef __OBJLIST_H
#define __OBJLIST_H
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
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/RCS/objlist.h,v 1.1 1993/06/17 21:24:04 gischer Exp $ */

typedef struct {
        Elf32_Word      oi_magic; /* to distinguish from old obj struct */
	Elf32_Word	oi_size; /* size in bytes of this struct */
	Elf32_Addr	oi_next; /* next record in doubly-linked list */
	Elf32_Addr	oi_prev; /* previous record */
	Elf32_Addr	oi_ehdr; /* address of ELF header in memory */
	Elf32_Addr	oi_orig_ehdr;/* QS address of ELF header */
	Elf32_Addr	oi_pathname; /* pathname as mapped by rld */
	Elf32_Word	oi_pathname_len; /* strlen(pathname) */
} Elf32_Obj_Info;

typedef struct {
        Elf64_Word      oi_magic; /* to distinguish from old obj struct */
	Elf64_Word	oi_size; /* size in bytes of this struct */
	Elf64_Addr	oi_next; /* next record in doubly-linked list */
	Elf64_Addr	oi_prev; /* previous record */
	Elf64_Addr	oi_ehdr; /* address of ELF header in memory */
	Elf64_Addr	oi_orig_ehdr;/* QS address of ELF header */
	Elf64_Addr	oi_pathname; /* pathname as mapped by rld */
	Elf64_Word	oi_pathname_len; /* strlen(pathname) */
} Elf64_Obj_Info;

/* We want dbx, pcs and libexc to be able to tell the new
 * obj struct from the old.  Therefore, since the old one
 * has a pointer in the first 4 bytes, we ensure that the
 * first 4 bytes of the new one cannot be an address.
 * First and foremost, this is accomplished by setting
 * the sign bit, since that indicates kernel space.  I believe
 * that any application will have to know that it is in
 * 64 bit mode before it gets this far.
 */
#define NEW_OBJ_INFO_MAGIC 0xffffffff
#endif

