#ifndef _XLATE_SYMS_H
#define _XLATE_SYMS_H

/****************************************************************************
 * 	     Format and defines for MIPS.Xlate_syms section entries.
 *
 ****************************************************************************/

struct s_xsym {
	__int64_t index;
	__int64_t value;
};
typedef struct s_xsym XSYM, *pXSYM;

extern pXSYM xlate_read_syms(int fd, int *n_syms, char **err);

#define XLATE_SYM_SECTNAME	".MIPS.Xlate_syms"

#define XSYM_MAP		1
#define XSYM_COUNT_OFFSET	2
#define XSYM_COUNT_LENGTH	3
#define XSYM_FPCOUNT_OFFSET	4
#define XSYM_FPCOUNT_LENGTH	5
#define XSYM_FPCOUNT_INDEX	6
#define XSYM_FPCOUNT_FLUSH	7
#define XSYM_PCSMP_OFFSET	8
#define XSYM_PCSMP_LENGTH	9
#define XSYM_PCSMP_START	10
#define XSYM_PCSMP_BINWID	11
#define XSYM_TEMP1_REG		12
#define XSYM_TEMP2_REG		13
#define XSYM_BASE_REG		14
#define XSYM_TEMP4_REG		15
#define XSYM_TEMP4_OFFSET	16
#define XSYM_BASE_PTR		17
#define XSYM_DATA_MOVE		18
#define XSYM_MODE_NAME		19
#define XSYM_MAXPATHBUF		20
#define XSYM_ORIG_TEXT_END	21
#define XSYM_START_FWA		22
#define XSYM_START_LWA		23
#define XSYM_START_BPA		24
#define XSYM_SPROC_BPA		25
#define XSYM_ARGTRACE_OFFSET	26
#define XSYM_ARGTRACE_LENGTH	27

    /*
     * pixie/gnome caliper support.
     */
#define XSYM_ZERO_COUNTS_BEGIN	200
#define XSYM_ZERO_COUNTS_END	201
#define XSYM_WRITE_COUNTS_BEGIN	202
#define XSYM_WRITE_COUNTS_END	203

#endif
