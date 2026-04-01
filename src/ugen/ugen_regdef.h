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

{Float point registers }
    const fpr_fv0   = xfr0;   /* floating point return value */
    const fpr_fv0f  = xfr1;
    const fpr_fv1   = xfr2;   /* floating point return value */
    const fpr_fv1f  = xfr3;

    const fpr_ft0   = xfr4;   /* caller saved temporaries */
    const fpr_ft0f  = xfr5;
    const fpr_ft1   = xfr6;
    const fpr_ft1f  = xfr7;
    const fpr_ft2   = xfr8;
    const fpr_ft2f  = xfr9;
    const fpr_ft3   = xfr10;
    const fpr_ft3f  = xfr11;

    const fpr_fa0   = xfr12;  /* floating point arguments */
    const fpr_fa0f  = xfr13;
    const fpr_fa1   = xfr14;
    const fpr_fa1f  = xfr15;

    const fpr_ft4   = xfr16;  /* caller saved temporaries */
    const fpr_ft4f  = xfr17;
    const fpr_ft5   = xfr18;
    const fpr_ft5f  = xfr19;

    const fpr_fs0   = xfr20;  /* callee saved */
    const fpr_fs0f  = xfr21;
    const fpr_fs1   = xfr22;
    const fpr_fs1f  = xfr23;
    const fpr_fs2   = xfr24;
    const fpr_fs2f  = xfr25;
    const fpr_fs3   = xfr26;
    const fpr_fs3f  = xfr27;
    const fpr_fs4   = xfr28;
    const fpr_fs4f  = xfr29;
    const fpr_fs5   = xfr30;
    const fpr_fs5f  = xfr31;
#endif /* UGEN_REGDEF_H */