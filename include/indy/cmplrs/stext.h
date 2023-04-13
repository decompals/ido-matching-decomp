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
/* $Header */
extern int st_readbinary (/* filename, how */);
extern int st_readst (/* fn, how, filebase, pchdr, flags */);
extern void st_writebinary (/* filename, flags */);
extern void st_writest (/* fn, flags */);
extern void st_shifttq (/* iaux, tq */);
extern long st_iaux_copyty (/* ifd, psym */);
extern void st_changeaux (/* iaux, aux */);
extern void st_addtq (/* iaux, tq */);
extern void st_changeauxrndx (/* iaux, ifd, index */);
extern long st_auxbtadd (/* bt */);
extern long st_auxisymadd (/* isym */);
extern long st_auxrndxadd (/* ifd, index */);
extern long st_auxbtsize (/* iaux, width */);
extern long st_auxrndxadd_idn (/* idn */);
extern void st_addcontinued(/* iaux */);
extern char *st_mlang_ascii [];
extern char *st_mst_ascii [];
extern char *st_msc_ascii [];
extern char *st_mbt_ascii [];
extern char *st_mtq_ascii [];
extern void st_dump (/* fd, flags */);
extern void st_printfd (/* fd, ifd, flags */);
extern long st_currentifd (/*  */);
extern long st_ifdmax (/*  */);
extern void st_setfd (/* index */);
extern void st_fdadd (/* filename, lang, merge, glevel */);
extern long st_symadd (/* iss, value, st, sc, index */);
extern long st_auxadd (/* aux */);
extern long st_pdadd (/* isym */);
extern long st_lineadd (/* lineno */);
extern long st_stradd(/*  cp  */);   
extern pSYMR st_psym_ifd_isym (/* ifd, isym */);
extern pAUXU st_paux_ifd_iaux (/* ifd, iaux */);
extern pLINER st_pline_ifd_iline (/* ifd, iline */);
extern pAUXU st_paux_iaux (/* iaux */);
extern pPDR st_ppd_ifd_isym (/* ifd, isym */);
extern long st_ifd_pcfd (/* pcfd1 */);
extern pCFDR st_pcfd_ifd (/* ifd */);
extern char *st_str_iss (/* iss */);
extern char *st_str_ifd_iss (/* ifd, iss */);
extern char * st_malloc (/* ptr,size,itemsize,basesize */);
extern long st_filebegin (/* filename, lang, merge, glevel */);
extern void st_endallfiles(/*  */);
extern long st_fileend (/* idn */);
extern long st_textblock(/*  */);
extern long st_blockbegin(/* iss, value, sc */);
extern long st_blockend(/* size */);
extern void st_blockpop (/*  */);
extern long st_procend(/* idn */);
extern long st_procbegin (/* idn */);
extern char *st_sym_idn (/* idn,sc,st,value,index */);
extern char *st_str_idn (/* idn */);
extern long st_fglobal_idn (/* idn */);
extern pSYMR st_psym_idn_offset (/* idn, offset */);
extern void st_fixextindex(/* idn, index */);
extern void st_fixextsc(/* idn, sc */);
extern long st_pdadd_idn  (/* idn */);
extern st_fixiss (/* idn, iss */);
extern st_changedn (/* idn, rfd, index */);
extern pCHDRR st_cuinit (/*  */);
extern void st_setchdr(/* pchdr */);
extern pCHDRR st_currentpchdr(/*  */);
extern void st_free (/*  */);
extern long st_extadd (/* iss, value, st, sc, index */);
extern long st_extstradd(/* cp */);   
extern char *st_str_extiss (/* iss */);
extern long st_idn_index_fext (/* index, fext */);
extern long st_idn_dn (/* dn */);
extern long st_idn_rndx (/* rndx */);
extern RNDXR st_rndx_idn (/* idn */);
extern pDNR st_pdn_idn (/* idn */);
extern void st_setidn (/* idndest, idnsrc */);
extern pEXTR st_pext_dn (/* dn */);
extern pEXTR st_pext_iext (/* index */);
extern long st_iextmax (/*  */);
