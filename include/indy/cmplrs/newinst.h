/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/newinst.h,v 7.14 1996/07/16 00:01:21 mpm Exp $ */
#define fli_op 0x26

/* this should eventually go into sys/inst.h */
/* rt field of cop opcodes */
#define bcf_op          0x00
#define bct_op          0x01
#define bcfl_op         0x02
#define bctl_op         0x03


#define S_FMT (cop_op+s_fmt)
#define D_FMT (cop_op+d_fmt)
#define W_FMT (cop_op+w_fmt)
#define E_FMT (cop_op+e_fmt)
#define L_FMT (cop_op+l_fmt)
#define Q_FMT (cop_op+q_fmt)
#define PS_FMT (cop_op+ps_fmt)

#define CASE_STORES \
	case sb_op: \
	case sh_op: \
	case sw_op: \
	case sc_op: \
	case swl_op: \
	case swr_op: \
	case sd_op: \
	case swc1_op: \
	case sdc1_op: \
	case swc2_op: \
	case sdc2_op: \
	case sdl_op: \
	case sdr_op: \
	case scd_op

/* what about {s,l}{w,d}xc1, which is part of cop1x_op? */

#define CASE_LOADS \
	case lb_op: \
	case lbu_op: \
	case lh_op: \
	case lhu_op: \
	case lw_op: \
	case lwu_op: \
	case lwl_op: \
	case lwr_op: \
	case ll_op: \
	case ld_op: \
	case ldl_op: \
	case ldr_op: \
	case lld_op: \
	case lwc1_op: \
	case ldc1_op: \
	case lwc2_op: \
	case ldc2_op


#define CASE_FCMP \
	case fcmp_op+0: \
	case fcmp_op+1: \
	case fcmp_op+2: \
	case fcmp_op+3: \
	case fcmp_op+4: \
	case fcmp_op+5: \
	case fcmp_op+6: \
	case fcmp_op+7: \
	case fcmp_op+8: \
	case fcmp_op+9: \
	case fcmp_op+10: \
	case fcmp_op+11: \
	case fcmp_op+12: \
	case fcmp_op+13: \
	case fcmp_op+14: \
	case fcmp_op+15


#define _is_inst_move(_inst)  \
    (_inst.r_format.opcode == spec_op &&  \
     (_inst.r_format.func == addu_op ||  \
      _inst.r_format.func == daddu_op ||  \
      _inst.r_format.func == or_op) &&  \
     _inst.r_format.rt == 0)

#define _is_inst_uncondbr(_inst) \
    (_inst.i_format.opcode == beq_op &&  \
     _inst.i_format.rs == 0 &&  \
     _inst.i_format.rt == 0)


#define _is_inst_branch_and_link(_inst)  \
    (_inst.i_format.opcode == bcond_op &&  \
     (_inst.i_format.rt == bltzal_op ||  \
      _inst.i_format.rt == bgezal_op ||  \
      _inst.i_format.rt == bltzall_op ||  \
      _inst.i_format.rt == bgezall_op))


#define _is_inst_branch(_inst)  \
    (_inst.i_format.opcode == beq_op ||  \
     _inst.i_format.opcode == bne_op ||  \
     _inst.i_format.opcode == blez_op ||  \
     _inst.i_format.opcode == bgtz_op ||  \
     _inst.i_format.opcode == beql_op ||  \
     _inst.i_format.opcode == bnel_op ||  \
     _inst.i_format.opcode == blezl_op ||  \
     _inst.i_format.opcode == bgtzl_op ||  \
     (_inst.i_format.opcode == bcond_op && \
      (_inst.i_format.rt == bltz_op ||  \
       _inst.i_format.rt == bgez_op ||  \
       _inst.i_format.rt == bltzl_op ||  \
       _inst.i_format.rt == bgezl_op ||  \
       _inst.i_format.rt == bltzal_op ||  \
       _inst.i_format.rt == bgezal_op ||  \
       _inst.i_format.rt == bltzall_op ||  \
       _inst.i_format.rt == bgezall_op)) ||  \
     ((_inst.i_format.opcode == cop0_op ||  \
       _inst.i_format.opcode == cop1_op ||  \
       _inst.i_format.opcode == cop3_op ||  \
       _inst.i_format.opcode == cop2_op) &&  \
      _inst.i_format.rs == bc_op))
