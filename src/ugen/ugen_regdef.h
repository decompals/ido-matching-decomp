#ifndef UGEN_REGDEF_H
#define UGEN_REGDEF_H

{ General purpose registers }
    const gpr_zero    =     xr0;	/* wired zero */
    const gpr_at	  =  xr1;	/* assembler temp */
    const gpr_v0	  =  xr2;	/* return value */
    const gpr_v1	  =  xr3;
    const gpr_a0	  =  xr4;	/* argument registers */
    const gpr_a1	  =  xr5;
    const gpr_a2	  =  xr6;
    const gpr_a3	  =  xr7;
    const gpr_t0	  =  xr8;	/* caller saved */
    const gpr_t1	  =  xr9;
    const gpr_t2	  =  xr10;
    const gpr_t3	  =  xr11;
    const gpr_t4	  =  xr12;	/* caller saved - 32 bit env arg reg 64 bit */
    const gpr_ta0	  =   xr12;	/* caller saved in 32 bit - arg regs in 64 bit */
    const gpr_t5	  =  xr13;
    const gpr_ta1	  =   xr13;
    const gpr_t6	  =  xr14;
    const gpr_ta2	  =   xr14;
    const gpr_t7	  =  xr15;
    const gpr_ta3	  =   xr15;
    const gpr_s0	  =  xr16;	/* callee saved */
    const gpr_s1	  =  xr17;
    const gpr_s2	  =  xr18;
    const gpr_s3	  =  xr19;
    const gpr_s4	  =  xr20;
    const gpr_s5	  =  xr21;
    const gpr_s6	  =  xr22;
    const gpr_s7	  =  xr23;
    const gpr_t8	  =  xr24;	/* code generator */
    const gpr_t9	  =  xr25;
    const gpr_jp	  =  xr25;	/* PIC jump register */
    const gpr_k0	  =  xr26;	/* kernel temporary */
    const gpr_k1	  =  xr27;
    const gpr_gp	  =  xr28;	/* global pointer */
    const gpr_sp	  =  xr29;	/* stack pointer */
    const gpr_fp	  =  xr30;	/* frame pointer */
    const gpr_s8	  =  xr30;	/* calle saved */
    const gpr_ra	  =  xr31;	/* return address */

#endif /* UGEN_REGDEF_H */