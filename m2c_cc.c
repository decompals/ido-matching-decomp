Warning: missing "jr $ra" in last block (.L00406670).

Bad function call operand .L0040661C
Bad function call operand .L0040661C
s32 creat(s8*, ?);                                  /* extern */
FILE* fdopen(s32, ?*);                              /* extern */
s32 flock(s32, ?);                                  /* extern */
? memcpy(s8*, s8*, u32);                            /* extern */
s8* mktemp(s8*);                                    /* extern */
s32 open(s8*, ?, ?);                                /* extern */
s8* strchr(s8*, u8);                                /* extern */
s32 strcmp(s8*, s8*);                               /* extern */
s8* strdup(s8*);                                    /* extern */
s32 strstr(s8*, ?*);                                /* extern */
s8* strtok(s8*, ?*);                                /* extern */
s32 strtoul(s32, s32*, ?);                          /* extern */

void __start(s32 arg0, s32 arg1, s32 arg2, void* arg6) {
    // Error: Bad function call operand .L0040661C
    // At instruction: bal .L0040661C
    if (M2C_ERROR()) {
        *saved_reg_gp->unk_-7FB8 = arg2;
    }
    *saved_reg_gp->unk_-783C = arg0;
    arg7 = 0;
    *saved_reg_gp->unk_-7840 = arg1;
    saved_reg_gp->unk_-7DE0();
    arg6->unk_-7FB0();
    arg6->unk_-7FB4(arg6->unk_-7EB0(*arg6->unk_-783C, *arg6->unk_-7840, *arg6->unk_-7FB8));
    M2C_BREAK(0);
}

void _mcount(void) {

}

s32 main(s32 argc, s8** argv) {
    s32 sp148;
    s8* sp144;
    s8* sp140;
    s8* sp13C;
    s8* sp138;
    s8* sp134;
    u32 sp130;
    s8* sp12C;
    s8* sp128;
    s8* sp124;
    s32 sp120;
    s32 sp11C;
    s8* sp118;
    s32 sp114;
    s8* sp110;
    s8* sp10C;
    s8* sp108;
    s8* sp104;
    s32 sp100;
    s32 spFC;
    s8* spF8;
    s8* spF4;
    s8 spF0;
    s8* spEC;
    s8* spE8;
    u8 spE7;
    s32 spE0;
    s32 spDC;
    u32 spD8;
    s8* spD4;
    s32 spD0;
    struct stat sp48;
    s32 temp_t6_2;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s3;
    s32 var_s3_10;
    s32 var_s3_9;
    s32 var_v0_5;
    s8* temp_t3;
    s8* temp_v0;
    s8* var_s1;
    s8* var_s1_2;
    s8* var_s1_3;
    s8* var_s1_4;
    s8* var_s1_5;
    s8* var_s2;
    s8* var_s3_2;
    s8* var_s3_3;
    s8* var_s3_5;
    s8* var_s3_6;
    s8* var_s3_7;
    s8* var_s3_8;
    s8* var_v0;
    s8* var_v0_10;
    s8* var_v0_11;
    s8* var_v0_12;
    s8* var_v0_13;
    s8* var_v0_14;
    s8* var_v0_15;
    s8* var_v0_16;
    s8* var_v0_17;
    s8* var_v0_2;
    s8* var_v0_3;
    s8* var_v0_4;
    s8* var_v0_6;
    s8* var_v0_7;
    s8* var_v0_8;
    s8* var_v0_9;
    s8** var_s3_4;
    u8 temp_s3;
    u8 temp_t5;
    u8 temp_t6;
    u8 temp_t8;

    sp148 = 0;
    sp144 = NULL;
    sp140 = NULL;
    progname = *argv;
    if ((ansichoice == 1) || (ansichoice == 2)) {
        CRTX = "acrt1.o";
    } else {
        CRTX = "crt1.o";
    }
    MCRTX = "mcrt1.o";
    m4 = "/usr/bin/m4";
    ratfor = "/usr/bin/ratfor";
    xpg_env = getenv("_XPG");
    if (xpg_env != NULL) {
        xpg_flag = 1;
    }
    mklist(&undefineflags);
    mklist(&cppflags);
    mklist(&ccomflags);
    mklist(&cfeflags);
    mklist(&upasflags);
    mklist(&fcomflags);
    mklist(&upl1flags);
    mklist(&ucobflags);
    mklist(&ulpiflags);
    mklist(&eflflags);
    mklist(&ratforflags);
    mklist(&ujoinflags);
    mklist(&uldflags);
    mklist(&olimitflags);
    mklist(&ldZflags);
    mklist(&acppflags);
    mklist(&cpp2flags);
    mklist(&mpcflags);
    mklist(&accomflags);
    mklist(&uldlibflags);
    mklist(&edisonflags);
    mklist(&prelinkerflags);
    mklist(&pfaflags);
    mklist(&pcaflags);
    mklist(&soptflags);
    mklist(&usplitflags);
    mklist(&umergeflags);
    mklist(&uloopflags);
    mklist(&uopt0flags);
    mklist(&ddoptflags);
    mklist(&optflags);
    mklist(&genflags);
    mklist(&asflags);
    mklist(&as1flags);
    mklist(&ldflags);
    mklist(&nldflags);
    mklist(&ftocflags);
    mklist(&cordflags);
    mklist(&srcfiles);
    mklist(&ufiles);
    mklist(&objfiles);
    mklist(&execlist);
    mklist(&feedlist);
    mklist(&dashlfiles);
    compdirs->unk_4 = mkstr("cc", "/", NULL);
    compdirs->unk_8 = mkstr("pc", "/", NULL);
    compdirs->unk_C = mkstr("f77", "/", NULL);
    compdirs->unk_10 = mkstr("cc", "/", NULL);
    compdirs->unk_14 = mkstr("pl1", "/", NULL);
    compdirs->unk_18 = mkstr("cobol", "/", NULL);
    call_shared = default_call_shared;
    sp13C = getenv("SGI_SVR4");
    if (sp13C != NULL) {
        default_svr4 = 1;
    }
    sp138 = getenv("SGI_CC");
    if (sp138 != NULL) {
        if (__ctype[(u8) *sp138].unk_1 & 8) {
            do {
                sp138 += 1;
            } while (__ctype[(u8) *sp138].unk_1 & 8);
        }
        sp130 = strlen(sp138);
        if ((s32) sp130 <= 0) {
            error(2, NULL, 0, NULL, 0, "Environment variable SGI_CC is empty: ignored\n");
        } else {
            temp_t3 = &sp138[sp130];
            sp134 = temp_t3 - 1;
            if (__ctype[temp_t3->unk_-1].unk_1 & 8) {
                do {
                    sp134 -= 1;
                } while (__ctype[(u8) *sp134].unk_1 & 8);
            }
            sp134 += 1;
            sp134[1] = 0;
            if (strcmp(sp138, "-cckr") == 0) {
                ansichoice = 0;
                cppchoice = 2;
                relocate_passes("p", NULL, NULL);
            } else if (strcmp(sp138, "-ansi") == 0) {
                ansichoice = 1;
                cppchoice = 3;
                relocate_passes("p", NULL, NULL);
            } else if (strcmp(sp138, "-xansi") == 0) {
                ansichoice = 3;
                cppchoice = 3;
                relocate_passes("p", NULL, NULL);
            } else if (strcmp(sp138, "-ansiposix") == 0) {
                ansichoice = 2;
                cppchoice = 3;
                relocate_passes("p", NULL, NULL);
            } else {
                error(2, NULL, 0, NULL, 0, "Environment variable SGI_CC contents unrecognizable and ignored; \"%s\" not one of: -cckr -ansi -xansi -ansiposix\n", sp138);
                sp138 = NULL;
            }
        }
    }
    compiler = 1;
    temp_v0 = strrchr(progname, 0x2F);
    if (temp_v0 == NULL) {
        var_s1 = progname;
    } else {
        var_s1 = temp_v0 + 1;
    }
    compdirs->unk_0 = mkstr(var_s1, "/", NULL);
    if (strncmp(var_s1, "cc", strlen("cc")) == 0) {
        compiler = 1;
        Bstring = &var_s1[strlen("cc")];
    } else if (strncmp(var_s1, "pc", strlen("pc")) == 0) {
        compiler = 2;
        Bstring = &var_s1[strlen("pc")];
    } else if (strncmp(var_s1, "f77", strlen("f77")) == 0) {
        compiler = 3;
        Bstring = &var_s1[strlen("f77")];
    } else if (strncmp(var_s1, "f90", strlen("f90")) == 0) {
        error(1, NULL, 0, NULL, 0, "-32 compilation not supported for ucode\n");
        exit(2);
    } else if (strncmp(var_s1, "as", strlen("as")) == 0) {
        compiler = 4;
        Bstring = &var_s1[strlen("as")];
        strcpy(compdirs->unk_0, compdirs->unk_4);
    } else if (strncmp(var_s1, "pl1", strlen("pl1")) == 0) {
        compiler = 5;
        Bstring = &var_s1[strlen("pl1")];
    } else if (strncmp(var_s1, "cobol", strlen("cobol")) == 0) {
        compiler = 6;
        Bstring = &var_s1[strlen("cobol")];
    } else if (strncmp(var_s1, "ncc", strlen("ncc")) == 0) {
        compiler = 1;
        c_compiler_choice = 1;
        edison_cpp = 1;
        Bstring = &var_s1[strlen("ncc")];
    } else if (strncmp(var_s1, "CC.eh", strlen("CC.eh")) == 0) {
        compiler = 1;
        c_compiler_choice = 2;
        edison_cpp = 1;
        anachronisms = 0;
        cfront_compatible = 0;
        D_1000BF7C = 0;
        exception_handling = 1;
        Bstring = &var_s1[strlen("CC")];
    } else if (strncmp(var_s1, "CC", strlen("CC")) == 0) {
        compiler = 1;
        c_compiler_choice = 2;
        edison_cpp = 1;
        D_1000BF7C = 0;
        Bstring = &var_s1[strlen("CC")];
    } else if (strncmp(var_s1, "NCC", strlen("NCC")) == 0) {
        compiler = 1;
        c_compiler_choice = 2;
        edison_cpp = 1;
        Bstring = &var_s1[strlen("NCC")];
    } else if (strncmp(var_s1, "DCC", strlen("DCC")) == 0) {
        compiler = 1;
        c_compiler_choice = 3;
        edison_cpp = 1;
        Bstring = &var_s1[strlen("DCC")];
        D_1000BF90 = 1;
    }
    Bstring = NULL;
    comp_target_root = getenv("COMP_TARGET_ROOT");
    if (comp_target_root == NULL) {
        comp_target_root = "/";
    } else if (comp_target_root[strlen(comp_target_root)].unk_-1 != 0x2F) {
        comp_target_root = mkstr(comp_target_root, "/", NULL);
    }
    comp_host_root = getenv("TOOLROOT");
    if (comp_host_root == NULL) {
        comp_host_root = "/";
    } else if (comp_host_root[strlen(comp_host_root)].unk_-1 != 0x2F) {
        comp_host_root = mkstr(comp_host_root, "/", NULL);
    }
    aligndir = mkstr(comp_host_root, "lib/align", NULL);
    sp12C = getenv("DCC_STD_PATHS");
    var_s3 = sp12C == NULL;
    if (var_s3 == 0) {
        var_s3 = (u8) *sp12C == 0;
        if (var_s3 == 0) {
            var_s3 = (u8) *sp12C == 0x30;
        }
    }
    D_1000BF8C = var_s3;
    if (D_1000BF8C == 0) {
        D_1000BF90 = D_1000BF8C;
    }
    if (force_use_cfront(argc, argv) != 0) {
        exec_OCC(argc, argv);
    }
    func_00431A3C(argc, argv);
    tmpdir = getenv("TMPDIR");
    if (tmpdir == NULL) {
        tmpdir = "/tmp/";
    } else if (tmpdir[strlen(tmpdir)].unk_-1 != 0x2F) {
        tmpdir = mkstr(tmpdir, "/", NULL);
    }
    passout = mktemp(mkstr(tmpdir, "ctmtstXXXXXX", NULL));
    tmpsfile = fopen(passout, "w");
    if (tmpsfile == NULL) {
        sprintf(perr_msg, "cc: can't write to $TMPDIR: %s", tmpdir);
        perror(perr_msg);
        exit(2);
    } else {
        fclose(tmpsfile);
        unlink(passout);
    }
    var_s0 = 1;
    rls_id_object = getenv("RLS_ID_OBJECT");
    if (argc > 1) {
        do {
            if (strcmp(argv[var_s0], "-non_shared") == 0) {
                non_shared = 1;
                if (Oflag < 3) {
                    Gnum = "8";
                }
            } else if (strcmp(argv[var_s0], "-irix4") == 0) {
                irix4 = 1;
                Gnum = "8";
            } else if (strcmp(argv[var_s0], "-coff") == 0) {
                LD = "old_ld";
                coff_spec = 1;
                kpic_flag = 0;
                Gnum = "8";
            } else if (strcmp(argv[var_s0], "-mips3") == 0) {
                mips3flag = 1;
                Gnum = "8";
                kpic_flag = 0;
            } else if (strcmp(argv[var_s0], "-excpt") == 0) {
                excpt_flag = 1;
                kpic_flag = 0;
                Gnum = "8";
            } else if (strcmp(argv[var_s0], "-abi") == 0) {
                abi_flag = 1;
                mips1flag = 1;
                mips2flag = 0;
            } else if (strcmp(argv[var_s0], "-O3") == 0) {
                Oflag = 3;
            } else if (strcmp(argv[var_s0], "-old_ld") == 0) {
                LD = "old_ld";
                D_1000BF90 = 0;
            }
            var_s0 += 1;
        } while (var_s0 < argc);
    }
    if ((compiler == 1) || (compiler == 2) || (compiler == 3) || (compiler == 4)) {
        docpp = 1;
        default_nocpp = 0;
    } else {
        docpp = 0;
        default_nocpp = 1;
    }
    currcomp = compdirs->unk_0;
    mklist(&dirs_for_nonshared_crtn);
    mklist(&dirs_for_abi_crtn);
    mklist(&dirs_for_crtn);
    var_s0_2 = 1;
    if (argc > 1) {
        do {
            if ((u8) *argv[var_s0_2] == 0x2D) {
                if (strcmp(argv[var_s0_2], "-nostdlib") == 0) {
                    sp148 = 1;
                } else {
                    temp_s3 = argv[var_s0_2]->unk_1;
                    switch (temp_s3) {              /* switch 9; irregular */
                    case 0x45:                      /* switch 9 */
                        if ((argv[var_s0_2]->unk_3 == 0) && ((argv[var_s0_2]->unk_2 == 0x42) || (argv[var_s0_2]->unk_2 == 0x4C))) {
                            if (argv[var_s0_2]->unk_2 == 0x42) {
                                if ((Bflag != 0) && (targetsex != 0)) {
                                    error(1, NULL, 0, NULL, 0, "-EB or -EL must precede any -B flags for ucode compilers.\n");
                                    exit(2);
                                }
                                targetsex = 0;
                            } else {
                                if ((Bflag != 0) && (targetsex != 1)) {
                                    error(1, NULL, 0, NULL, 0, "-EB or -EL must precede any -B flags for ucode compilers.\n");
                                    exit(2);
                                }
                                targetsex = 1;
                            }
                            newrunlib();
                        }
                        break;
                    case 0x4C:                      /* switch 9 */
                        if (argv[var_s0_2].unk_0->unk_2 == 0) {
                            if (((var_s0_2 + 1) >= argc) || (*argv[var_s0_2].unk_4 == 0x2D) || (isdir(argv[var_s0_2].unk_4) == 0)) {
                                sp148 = 1;
                            } else {
                                var_s0_2 += 1;
                                var_v0 = mkstr(argv[var_s0_2], NULL);
                                goto block_125;
                            }
                        } else {
                            var_v0 = mkstr(argv[var_s0_2] + 2, NULL);
block_125:
                            sp128 = var_v0;
                            if (sp128[strlen(sp128)].unk_-1 == 0x2F) {
                                sp128[strlen(sp128)].unk_-1 = 0;
                            }
                            addstr(&dirs_for_crtn, sp128);
                            addstr(&dirs_for_nonshared_crtn, sp128);
                            addstr(&dirs_for_abi_crtn, sp128);
                        }
                        break;
                    }
                }
            }
            var_s0_2 += 1;
        } while (var_s0_2 < argc);
    }
    if (sp148 == 0) {
        if ((non_shared != 0) || (coff_spec != 0) || (mips3flag != 0) || (excpt_flag != 0)) {
            addstr(&dirs_for_nonshared_crtn, mkstr(comp_target_root, "usr/lib/nonshared", NULL));
        } else if (abi_flag != 0) {
            addstr(&dirs_for_abi_crtn, mkstr(comp_target_root, "usr/lib/abi", NULL));
        } else {
            addstr(&dirs_for_crtn, mkstr(comp_target_root, "usr/lib", NULL));
            addstr(&dirs_for_crtn, mkstr(comp_target_root, "lib", NULL));
        }
    }
    relocate_passes(tstring, NULL, Bstring);
    relocate_passes("h", NULL, Bstring);
    if (strcmp("/", comp_target_root) != 0) {
        einclude = mkstr(comp_target_root, "usr/include/CC", NULL);
        include = mkstr(comp_target_root, "usr/include", NULL);
    }
    if (compiler == 1) {
        oldcflag = 0;
    } else {
        cpp_stdflag = "-std0";
    }
    systype = "svr4";
    svr4_systype = 1;
    process_config(argc, argv);
    parse_command(argc - 1, argv + 4);
    func_00431DD8();
    if (D_1000BF74 != 0) {
        if (D_1000BF80 == NULL) {
            D_1000BF80 = "";
        }
        if (D_1000BF78 != 0) {
            var_s3_2 = "-YSv";
        } else {
            var_s3_2 = "-YSz";
        }
        sp144 = mkstr(var_s3_2, D_1000BF80, NULL);
        if (compiler == 1) {
            addstr(&edisonflags, sp144);
        } else {
            if (D_1000BF78 != 0) {
                sp140 = "-cvs_nosrc";
            } else {
                sp140 = "-cvs";
            }
            if ((u8) *D_1000BF80 != 0) {
                sp140 = mkstr(sp140, ",", D_1000BF80, NULL);
            }
            addstr(&fcomflags, sp140);
        }
    }
    if (user_systype == 0) {
        if (fiveflag != 0) {
            var_v0_2 = mkstr(comp_target_root, "usr/5include", NULL);
        } else {
            einclude = mkstr(comp_target_root, "usr/include/CC", NULL);
            var_v0_2 = mkstr(comp_target_root, "usr/include", NULL);
        }
        include = var_v0_2;
        if (Bstring != NULL) {
            relocate_passes("h", NULL, Bstring);
        }
        newrunlib();
    }
    if (((mips2flag != 0) || (mips3flag != 0) || (sixty4bitflag != 0)) && (kpic_flag == 0) && ((non_shared != 0) || (call_shared != 0) || (default_call_shared != 0))) {
        if (non_shared == 0) {
            non_shared = 1;
            old_non_shared = 1;
        }
        default_call_shared = 0;
        call_shared = 0;
        if (non_shared_emitted == 0) {
            addstr(&ldflags, "-non_shared");
            addstr(&cfeflags, "-non_shared");
            non_shared_emitted = 1;
        }
    }
    if ((non_shared != 0) && (non_shared_emitted == 0)) {
        addstr(&ldflags, "-non_shared");
        addstr(&cfeflags, "-non_shared");
        non_shared_emitted = 1;
    } else if (call_shared != 0) {
        addstr(&ldflags, "-call_shared");
        addstr(&cfeflags, "-call_shared");
    }
    if ((Vflag == 0) && (srcfiles.length == 0) && (objfiles.length == 0) && (ufiles.length == 0)) {
        error(1, NULL, 0, NULL, 0, "no source, object or ucode file specified\n");
        exit(2);
    }
    if (w1flag == 1) {
        addstr(&fcomflags, "-w1");
    } else if (w1flag == 2) {
        addstr(&fcomflags, "-w");
    }
    if ((srcexists == 0) && ((cflag != 0) || (Sflag != 0))) {
        error(1, NULL, 0, NULL, 0, "no source file for ucode compilers.\n");
        exit(4);
    }
    if ((mp_flag != 0) && (gflag != 0) && (mp_flag & 1)) {
        mp_flag |= 4;
    }
    if ((cmp_flag != 0) && (gflag != 0) && (cmp_flag & 1)) {
        cmp_flag |= 4;
    }
    if ((ansichoice == 1) || (ansichoice == 2)) {
        CRTX = "acrt1.o";
        crtn_required = 1;
    }
    relocate_passes("r", NULL, NULL);
    if ((B_1000ED30 != 0) && (compiler == 1) && ((ansichoice == 1) || (ansichoice == 2))) {
        error(2, NULL, 0, NULL, 0, "'-lc_s' specified. Shared version of C library does not conform to ANSI X3.159-1989.\n");
    }
    if (Oflag >= 3) {

    }
    if ((kpic_flag != 0) && (strcmp(Gnum, "0") != 0) && (Oflag < 3)) {
        error(2, NULL, 0, NULL, 0, "-KPIC (the default) is only compatible with -G 0 for ucode compilers, changing to -G 0. \n");
        Gnum = "0";
    }
    if ((abi_flag != 0) && (non_shared != 0)) {
        error(2, NULL, 0, NULL, 0, "-non_shared is not compatible with -abi for ucode compilers, changing to -abi.\n");
        non_shared = 0;
        kpic_flag = 1;
        Gnum = "0";
    }
    if ((Oflag >= 3) && (compiler == 4)) {
        error(2, NULL, 0, NULL, 0, "-O3 is not supported for assembly compiles for ucode compilers; changing to -O2.\n");
        Oflag = 2;
        uload = 0;
    }
    get_host_chiptype();
    if (targetsex == 0) {
        addstr(&cppflags, "-D_MIPSEB");
        if ((compiler != 1) || (ansichoice == 0) || (ansichoice == 3)) {
            addstr(&cppflags, "-DMIPSEB");
        }
        if ((compiler == 1) && ((ansichoice == 1) || (ansichoice == 2) || ((ansichoice == 3) && (irix4 == 0)))) {
            addstr(&cppflags, "-D__STDC__=1");
        }
        if ((compiler == 1) && (ansichoice == 2)) {
            addstr(&cppflags, "-D_POSIX_SOURCE=1");
        }
        addstr(&ccomflags, "-EB");
        addstr(&upasflags, "-EB");
        addstr(&fcomflags, "-EB");
        addstr(&upl1flags, "-EB");
        addstr(&ulpiflags, "-EB");
        addstr(&ucobflags, "-EB");
        addstr(&umergeflags, "-EB");
        addstr(&optflags, "-EB");
        addstr(&genflags, "-EB");
        addstr(&asflags, "-EB");
    } else {
        addstr(&cppflags, "-D_MIPSEL");
        addstr(&cppflags, "-D_MIPSEL");
        if ((compiler != 1) || (ansichoice == 0) || (ansichoice == 3)) {
            addstr(&cppflags, "-DMIPSEL");
        }
        if ((compiler == 1) && ((ansichoice == 1) || (ansichoice == 2) || ((ansichoice == 3) && (irix4 == 0)))) {
            addstr(&cppflags, "-D__STDC__=1");
        }
        if ((compiler == 1) && (ansichoice == 2)) {
            addstr(&cppflags, "-D_POSIX_SOURCE=1");
        }
        addstr(&ccomflags, "-EL");
        addstr(&upasflags, "-EL");
        addstr(&fcomflags, "-EL");
        addstr(&upl1flags, "-EL");
        addstr(&ulpiflags, "-EL");
        addstr(&ucobflags, "-EL");
        addstr(&genflags, "-EL");
        addstr(&umergeflags, "-EL");
        addstr(&optflags, "-EL");
        addstr(&asflags, "-EL");
        addstr(&ldflags, "-EL");
    }
    switch (gflag) {                                /* switch 10; irregular */
    case 0:                                         /* switch 10 */
        addstr(&ccomflags, "-Xg0");
        addstr(&upasflags, "-g0");
        addstr(&fcomflags, "-g0");
        addstr(&ulpiflags, "-g0");
        addstr(&uopt0flags, "-g0");
        addstr(&ddoptflags, "-g0");
        addstr(&optflags, "-g0");
        addstr(&umergeflags, "-g0");
        addstr(&uloopflags, "-g0");
        addstr(&genflags, "-g0");
        addstr(&asflags, "-g0");
        addstr(&ldflags, "-g0");
        if (nocode == 0) {
            addstr(&edisonflags, "-Zg0");
        }
        break;
    case 1:                                         /* switch 10 */
        addstr(&edisonflags, "-Zg1");
        addstr(&ccomflags, "-Xg1");
        add_info("-g1");
        break;
    case 2:                                         /* switch 10 */
        addstr(&edisonflags, "-Zg2");
        addstr(&ccomflags, "-Xg2");
        add_info("-g2");
        break;
    case 3:                                         /* switch 10 */
        gflag += 1;
        addstr(&edisonflags, "-Zg3");
        addstr(&ccomflags, "-Xg3");
        add_info("-g3");
        break;
    }
    if ((mp_flag != 0) && (ddoptflag != 0)) {
        error(1, NULL, 0, NULL, 0, "can't use -mp/-pfa with -ddopt\n");
        exit(2);
    }
    if ((mips3flag != 0) && (thirty2bitflag == 0)) {
        error(1, NULL, 0, NULL, 0, "-mips3 implies -64bit for ucode compilers, which is not supported.\n");
        exit(2);
    }
    if ((irix4 != 0) && (compiler == 1) && (c_compiler_choice != 0)) {
        error(1, NULL, 0, NULL, 0, "IRIX4 not supported in Delta-C++\n");
        exit(2);
    }
    if ((irix4 != 0) && (compiler == 3) && (D_1000BF74 != 0)) {
        error(1, NULL, 0, NULL, 0, "IRIX4 and -sa not supported together\n");
        exit(2);
    }
    if (((cflag != 0) || (Sflag != 0) || (nocode != 0) || (Eflag != 0) || (Pflag != 0)) && (make_edison_shlib != 0)) {
        error(1, NULL, 0, NULL, 0, "-shared can be specified only when a link is to be performed for ucode compilers\n");
        exit(2);
    }
    if ((cflag == 0) && (nocode == 0) && (srcfiles.length == 1) && (objfiles.length == 1)) {
        default_template_instantiation_mode = 1;
    }
    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (Fflag != 0) && (smart_build != 0)) {
        error(2, NULL, 0, NULL, 0, "-F and -smart cannot be specified together for ucode compilers: -smart ignored\n");
        smart_build = 0;
    }
    if ((default_template_instantiation_mode != 0) && (force_prelink == 0)) {
        no_prelink = 1;
    }
    if ((compiler == 1) && (c_compiler_choice == 3)) {
        sp124 = getenv("DCC_FORCE_OPT");
        sp120 = 1;
        if (Oflag >= 3) {
            Oflag = 2;
            uload = 0;
        }
        if (sp124 != NULL) {
            temp_t6 = (u8) sp124->unk_0;
            if (((s32) temp_t6 >= 0x30) && ((s32) temp_t6 < 0x34) && (sp124->unk_1 == 0)) {
                sp120 = temp_t6 - 0x30;
            }
        }
        if (sp120 < Oflag) {
            Oflag = sp120;
        }
    }
    addstr(&execlist, "-Dunix");
    if (dmips_emit == 0) {
        if (mips2flag != 0) {
            if (dwopcodeflag != 0) {
                error(1, NULL, 0, NULL, 0, "can't mix -mips2 with -dwopcode for ucode compilers\n");
                exit(2);
            }
            addstr(&execlist, "-Dmips=2");
        }
        if (mips3flag != 0) {
            addstr(&execlist, "-Dmips=3");
        } else {
            addstr(&execlist, "-Dmips=1");
        }
    }
    addstr(&execlist, "-Dhost_mips");
    if (sixty4bitflag != 0) {
        addstr(&ccomflags, "-64bit");
        add_info("-64bit");
        addstr(&ccomflags, "-dwopcode");
        add_info("-dwopcode");
        if (mips3flag == 0) {
            chip_targ = 2;
            mips3flag = 1;
            addstr(&ccomflags, "-mips3");
            add_info("-mips3");
            relocate_passes("M", NULL, NULL);
        }
    } else if (dwopcodeflag != 0) {
        addstr(&ccomflags, "-dwopcode");
        add_info("-dwopcode");
        if (mips3flag == 0) {
            chip_targ = 2;
            mips3flag = 1;
            addstr(&ccomflags, "-mips3");
            add_info("-mips3");
            relocate_passes("M", NULL, NULL);
        }
    }
    switch (Oflag) {                                /* switch 1 */
    case 0:                                         /* switch 1 */
        var_s1 = "-O0";
        break;
    case 1:                                         /* switch 1 */
        var_s1 = "-O1";
        break;
    case 2:                                         /* switch 1 */
        var_s1 = "-O2";
        break;
    case 3:                                         /* switch 1 */
        var_s1 = "-O3";
        break;
    case 4:                                         /* switch 1 */
        var_s1 = "-O4";
        break;
    }
    addstr(&ccomflags, var_s1);
    addstr(&upasflags, var_s1);
    addstr(&fcomflags, var_s1);
    addstr(&upl1flags, var_s1);
    addstr(&ulpiflags, var_s1);
    addstr(&ucobflags, var_s1);
    addstr(&uopt0flags, var_s1);
    addstr(&ddoptflags, var_s1);
    addstr(&optflags, var_s1);
    addstr(&umergeflags, var_s1);
    addstr(&uloopflags, var_s1);
    addstr(&genflags, var_s1);
    addstr(&asflags, var_s1);
    if (compiler == 3) {
        if (automaticflag != 0) {
            addstr(&fcomflags, "-automatic");
        } else {
            addstr(&fcomflags, "-static");
            addstr(&optflags, "-static");
        }
    }
    if (Vflag != 0) {
        whats();
    }
    if (runerror != 0) {
        exit(1);
    }
    if (sigset(2, (void (*)())1) != (void (*)())1) {
        sigset(2, handler);
    }
    if (sigset(0xF, (void (*)())1) != (void (*)())1) {
        sigset(0xF, handler);
    }
    if (sigset(0xD, (void (*)())1) != (void (*)())1) {
        sigset(0xD, handler);
    }
    if ((compiler == 6) && (nolockflag != 0) && (lpilockflag != 0)) {
        error(1, NULL, 0, NULL, 0, "Conflicting flags; -nolock and -lpilock can't both be specified for ucode compilers\n");
        exit(2);
    }
    if ((Oflag >= 3) && (cflag != 0) && (srcfiles.length == 1)) {
        error(2, NULL, 0, NULL, 0, "-c should not be used with ucode -O3 -o32 on a single file; use -j instead to get inter-module optimization.\n");
    }
    if ((srcfiles.length >= 2) && (compiler == 4) && (Eflag == 0) && (Pflag == 0)) {
        error(1, NULL, 0, NULL, 0, "only one source file can be specified with %s for ucode compilers\n", "as");
        exit(2);
    }
    mktempstr();
    var_s0_3 = 0;
    if ((srcfiles.length > 0) || (uload != 0)) {
loop_363:
        nocompileneeded = 0;
        sp118 = NULL;
        longlong_emitted = 0;
        sp11C = D_1000BF74;
        if (var_s0_3 == srcfiles.length) {
            uload = 0;
            if ((runerror == 0) && (Eflag == 0) && (Pflag == 0)) {
                if (uoutfile == NULL) {
                    addstr(&srcfiles, "u.out.?");
                } else if (getsuf(uoutfile) != 0) {
                    addstr(&srcfiles, mksuf(uoutfile, 0x3F));
                } else {
                    addstr(&srcfiles, mkstr(uoutfile, ".?", NULL));
                }
                srcsuf = 0x3F;
                if (((u8) Hchar == 0x73) || ((u8) Hchar == 0x6D) || ((u8) Hchar == 0x6F) || ((u8) Hchar == 0x63) || (Kflag != 0)) {
                    symtab = mksuf(srcfiles.entries[var_s0_3], 0x54);
                    tmpst = 0;
                } else {
                    symtab = tempstr->unk_0;
                    tmpst = 1;
                }
                if ((non_shared != 0) && (non_shared_emitted == 0)) {
                    addstr(&ldflags, "-non_shared");
                    non_shared_emitted = 1;
                }
                execlist.length = 0;
                addstr(&execlist, "uld");
                if ((mips2flag != 0) && (sp148 == 0)) {
                    if (strcmp("/", comp_target_root) != 0) {
                        if (non_shared != 0) {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
                        } else {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
                        }
                    } else if (non_shared != 0) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
                    }
                }
                if ((mips1flag != 0) && (sp148 == 0)) {
                    if (strcmp("/", comp_target_root) != 0) {
                        if (non_shared != 0) {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
                        } else {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
                        }
                    } else if (non_shared != 0) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
                    }
                }
                if (((fiveflag != 0) || (strcmp("/", comp_target_root) != 0)) && (Lflag == 0) && (strcmp("/", comp_target_root) != 0)) {
                    if (non_shared != 0) {
                        addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/nonshared/", currcomp, NULL));
                    } else {
                        addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, NULL));
                    }
                }
                if (svr4_systype != 0) {
                    if (compchoice == 1) {
                        addstr(&execlist, mkstr("-SYSTYPE_SVR4", NULL, NULL));
                    }
                    addstr(&execlist, mkstr("-_SYSTYPE_SVR4", NULL, NULL));
                    if (call_shared != 0) {
                        addstr(&execlist, "-require_dynamic_link");
                        addstr(&execlist, "_rld_new_interface");
                    }
                }
                if ((allBstring != NULL) && ((u8) *allBstring != 0)) {
                    addstr(&execlist, mkstr("-kB", allBstring, NULL));
                }
                addlist(&execlist, &uldflags);
                addlist(&execlist, &ldflags);
                if (irix4 != 0) {
                    addstr(&execlist, mkstr("-L", NULL));
                    if (non_shared != 0) {
                        addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/nonshared/", NULL));
                        crtx = mkstr(comp_host_root, "usr/lib/nonshared/", CRTX, NULL);
                        var_v0_3 = mkstr(comp_host_root, "usr/lib/nonshared/", "crtn.o", NULL);
                    } else {
                        addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/", NULL));
                        crtx = mkstr(comp_host_root, "usr/lib/", CRTX, NULL);
                        var_v0_3 = mkstr(comp_host_root, "usr/lib/", "crtn.o", NULL);
                    }
                    crtn = var_v0_3;
                }
                if (cflag == 0) {
                    addstr(&execlist, crtx);
                } else {
                    addstr(&execlist, "-no_AutoGnum");
                    if (force_rm_dead_code == 0) {
                        addstr(&execlist, "-preserve_dead_code");
                    }
                }
                adduldlist(&execlist, &ufiles, &objfiles);
                if (cflag == 0) {
                    addlist(&execlist, &uldlibflags);
                    if (((compiler == 2) || (haspascal != 0)) && ((addspacedstr(&execlist, newstr(libp)), addspacedstr(&execlist, newstr(libxmalloc)), addspacedstr(&execlist, newstr(libexc)), addspacedstr(&execlist, newstr(libmld)), (default_call_shared != 0)) || (call_shared != 0)) && (systype != NULL) && (strcmp(systype, "svr3") == 0)) {
                        addspacedstr(&execlist, "-lbsd");
                    }
                    if ((compiler == 3) || (hasfortran != 0)) {
                        if (mp_flag != 0) {
                            addstr(&execlist, libI77_mp);
                        }
                        if ((non_shared != 0) || (irix4 != 0)) {
                            addspacedstr(&execlist, newstr(libF77));
                        } else {
                            addspacedstr(&execlist, libftn);
                        }
                        if ((non_shared != 0) || (irix4 != 0)) {
                            addspacedstr(&execlist, newstr(libI77));
                        }
                        if ((non_shared != 0) || (irix4 != 0)) {
                            addspacedstr(&execlist, newstr(libU77));
                        }
                        if ((non_shared != 0) || (irix4 != 0)) {
                            addspacedstr(&execlist, newstr(libisam));
                        }
                    }
                    if (compiler == 5) {
                        addstr(&execlist, libpl1);
                        addstr(&execlist, libxmalloc);
                        addstr(&execlist, "-ltermcap");
                        addstr(&execlist, libexc);
                        addstr(&execlist, libmld);
                    }
                    if (((compiler == 2) || (compiler == 3) || (haspascal != 0) || (hasfortran != 0) || (haspl1 != 0) || (compiler == 5) || (compiler == 6)) && (nonshared != 0)) {
                        addspacedstr(&execlist, newstr(libm));
                    }
                    if (pgflag != 0) {
                        addspacedstr(&execlist, newstr(libgprof));
                    } else if (pflag != 0) {
                        addspacedstr(&execlist, newstr(libprof));
                    }
                    if (cmp_flag & 0x10000) {
                        addstr(&execlist, libc_mp);
                        if (compiler == 1) {
                            addstr(&execlist, "-lkapio");
                        }
                    }
                    if ((run_sopt != 0) && (compiler == 1)) {
                        addstr(&execlist, "-lkapio");
                    }
                    if (compiler == 3) {
                        if (D_1000C130 == 2) {
                            addstr(&execlist, "-lc_s");
                            if (xpg_flag != 0) {
                                addstr(&execlist, "-dont_warn_unused");
                                addstr(&execlist, "-lgen");
                                addstr(&execlist, "-warn_unused");
                            }
                            addstr(&execlist, "-lc");
                        } else {
                            if ((irix4 != 0) && (B_1000ED74 == 0)) {
                                addstr(&execlist, "-lmpc");
                            }
                            if (B_1000ED2C != 0) {
                                addstr(&execlist, "-lc_s");
                            } else if (B_1000ED30 != 0) {
                                addstr(&execlist, "-lc_s");
                            }
                        }
                    } else if (B_1000ED2C != 0) {
                        addstr(&execlist, "-lc_s");
                    }
                    if (sixty4bitflag == 0) {
                        ldw_file = fopen(libdw_path, "r");
                        if (ldw_file != NULL) {
                            addspacedstr(&execlist, newstr(libdw));
                        }
                    }
                    if (xpg_flag != 0) {
                        addstr(&execlist, "-dont_warn_unused");
                        addstr(&execlist, "-lgen");
                        addstr(&execlist, "-warn_unused");
                    }
                    addstr(&execlist, "-lc");
                    if (libm_spec != 0) {
                        addstr(&execlist, "-lm");
                    }
                    if (libfastm_spec != 0) {
                        addstr(&execlist, "-lfastm");
                    }
                }
                if ((cflag == 0) && (crtn_required != 0)) {
                    addstr(&execlist, crtn);
                }
                if (rls_id_object != NULL) {
                    addstr(&execlist, rls_id_object);
                }
                addstr(&execlist, "-ko");
                if (uoutfile != NULL) {
                    passout = uoutfile;
                } else if (((u8) Hchar == 0x75) || (Kflag != 0)) {
                    passout = mksuf(srcfiles.entries[var_s0_3], 0x75);
                } else {
                    passout = tempstr->unk_10;
                }
                addstr(&execlist, passout);
                if (run(uld, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror += 1;
                    if (Kflag == 0) {
                        unlink(passout);
                    }
                } else {
                    passin = passout;
                    if ((ufiles.length == 1) && (srcfiles.length == 2) && ((Oflag == 3) || (Oflag == 4))) {
                        unlink(*ufiles.entries);
                    }
                    if ((u8) Hchar != 0x75) {
                        goto block_1896;
                    }
                }
            }
            goto block_2270;
        }
        if (srcfiles.length >= 2) {
            fprintf(__iob + 0x20, "%s:\n", srcfiles.entries[var_s0_3]);
        }
        if ((NoMoreOptions != 0) && ((u8) *srcfiles.entries[var_s0_3] == 0x2D)) {
            passin = func_00433534(srcfiles.entries[var_s0_3]);
        } else {
            passin = srcfiles.entries[var_s0_3];
        }
        if (compiler != 4) {
            srcsuf = getsuf(srcfiles.entries[var_s0_3]);
            if ((u8) srcsuf == 0x6D) {
                srcsuf = 0x66;
            }
        } else {
            srcsuf = 0x73;
        }
        if (((u8) Hchar == 0x66) || ((u8) Hchar == 0x73) || ((u8) Hchar == 0x6D) || ((u8) Hchar == 0x6F) || ((u8) Hchar == 0x6B) || ((u8) Hchar == 0x63) || (Kflag != 0) || ((u8) srcsuf == 0x42) || ((u8) srcsuf == 0x55) || ((u8) srcsuf == 0x4F) || ((u8) srcsuf == 0x47) || ((u8) srcsuf == 0x53) || ((u8) srcsuf == 0x4D) || ((u8) srcsuf == 0x56) || ((u8) srcsuf == 0x44) || ((u8) srcsuf == 0x51)) {
            tmpst = 0;
            if ((compiler == 4) && (getsuf(srcfiles.entries[var_s0_3]) == 0)) {
                symtab = mkstr(srcfiles.entries[var_s0_3], ".T", NULL);
            } else {
                symtab = mksuf(srcfiles.entries[var_s0_3], 0x54);
            }
        } else {
            tmpst = 1;
            symtab = tempstr->unk_0;
        }
        switch ((s32) (u8) srcsuf) {                /* switch 11; irregular */
        case 0x73:                                  /* switch 11 */
            if ((compiler == 1) && (compdirs->unk_0 != currcomp)) {
                currcomp = compdirs->unk_0;
                relocate_passes("pKfjsmvocabtyz", NULL, NULL);
            }
            /* fallthrough */
        case 0x69:                                  /* switch 11 */
            if ((compiler == 1) && (compdirs->unk_0 != currcomp)) {
                currcomp = compdirs->unk_0;
                relocate_passes("pKfjsmvocabtyz", NULL, NULL);
            }
            /* fallthrough */
        case 0x6:                                   /* switch 11 */
        case 0x63:                                  /* switch 11 */
            if (compiler != 1) {
                if (compdirs->unk_4 != currcomp) {
                    currcomp = compdirs->unk_4;
                    relocate_passes("pKfjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs->unk_0 != currcomp) {
                currcomp = compdirs->unk_0;
                relocate_passes("pKfjsmvocabtyz", NULL, NULL);
            }
            compchoice = 0;
            break;
        case 0x70:                                  /* switch 11 */
            if (compiler != 2) {
                if (compdirs->unk_8 != currcomp) {
                    currcomp = compdirs->unk_8;
                    relocate_passes("pfjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs->unk_0 != currcomp) {
                currcomp = compdirs->unk_0;
                relocate_passes("pfjsmvocabtyz", NULL, NULL);
            }
            break;
        case 0x46:                                  /* switch 11 */
        case 0x66:                                  /* switch 11 */
            if (compiler != 3) {
                if (compdirs->unk_C != currcomp) {
                    currcomp = compdirs->unk_C;
                    relocate_passes("pfjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs->unk_0 != currcomp) {
                currcomp = compdirs->unk_0;
                relocate_passes("pfjsmvocabtyz", NULL, NULL);
            }
            break;
        case 0x1:                                   /* switch 11 */
            if (compiler != 5) {
                if (compdirs->unk_14 != currcomp) {
                    currcomp = compdirs->unk_14;
                    relocate_passes("pfekjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs->unk_0 != currcomp) {
                currcomp = compdirs->unk_0;
                relocate_passes("pfekjsmvocabtyz", NULL, NULL);
            }
            break;
        case 0x2:                                   /* switch 11 */
            if (compiler != 6) {
                if (compdirs->unk_18 != currcomp) {
                    currcomp = compdirs->unk_18;
                    relocate_passes("pfekjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs->unk_0 != currcomp) {
                currcomp = compdirs->unk_0;
                relocate_passes("pfekjsmvocabtyz", NULL, NULL);
            }
            break;
        case 0x3:                                   /* switch 11 */
            if ((compiler != 1) && (compiler != 5) && (compiler != 6)) {
                if ((compdirs->unk_4 != currcomp) && (compdirs->unk_14 != currcomp) && (compdirs->unk_18 != currcomp)) {
                    currcomp = compdirs->unk_4;
                    relocate_passes("pekjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs->unk_0 != currcomp) {
                currcomp = compdirs->unk_0;
                relocate_passes("pfjsmvocabtyz", NULL, NULL);
            }
            break;
        }
        if ((compiler == 3) && (D_1000BF74 != 0) && ((u8) srcsuf != 0x66) && ((u8) srcsuf != 0x46)) {
            D_1000BF74 = 0;
            relocate_passes("f", NULL, NULL);
        }
        if ((D_1000BF74 != 0) && ((compiler == 3) || ((compiler == 1) && (c_compiler_choice != 0)))) {
            record_static_fileset((s32) srcfiles.entries[var_s0_3]);
        }
        if ((compiler == 1) && (c_compiler_choice == 1)) {
            switch (ansichoice) {                   /* switch 12; irregular */
            case 1:                                 /* switch 12 */
            case 2:                                 /* switch 12 */
                edison_type = (s8* )2;
                break;
            case 3:                                 /* switch 12 */
                edison_type = (s8* )1;
                break;
            default:                                /* switch 12 */
            case 0:                                 /* switch 12 */
                edison_type = (s8* )3;
                break;
            }
        }
loop_484:
        if (compchoice == 0) {
            if (irix4 != 0) {
                if (ansichoice == 0) {
                    compchoice = 1;
                } else {
                    compchoice = 2;
                }
            } else if (ansichoice == 0) {
                compchoice = 3;
            } else {
                compchoice = 3;
            }
        }
        if ((Eflag == 0) || ((u8) srcsuf == 0x61)) {
            switch ((s32) (u8) srcsuf) {            /* switch 19; irregular */
            case 0x6:                               /* switch 19 */
            case 0x63:                              /* switch 19 */
                if (oldccomflag != 1) {
                    oldcflag = 0;
                }
                if (docpp == 0) {
                    if (default_nocpp != 0) {
                        goto block_531;
                    }
                    goto block_940;
                }
                goto block_531;
            case 0x69:                              /* switch 19 */
                switch (compiler) {                 /* switch 4 */
                case 0x70:                          /* switch 19 */
                default:                            /* switch 4 */
                    if (stdflag == 0) {
                        if ((docpp == 0) && (default_nocpp == 0)) {
                            goto block_1341;
                        }
                        goto block_531;
                    }
                    goto block_1341;
                }
                break;
            case 0x66:                              /* switch 19 */
                if (docpp != 0) {
                    goto block_531;
                }
                goto block_1505;
            case 0x1:                               /* switch 19 */
                if (docpp != 0) {
                    goto block_531;
                }
                goto block_1388;
            case 0x2:                               /* switch 19 */
                if (docpp != 0) {
                    goto block_531;
                }
                goto block_1453;
            case 0x55:                              /* switch 19 */
                execlist.length = 0;
                addstr(&execlist, "utob");
                addstr(&execlist, srcfiles.entries[var_s0_3]);
                if (Kflag != 0) {
                    passout = mksuf(srcfiles.entries[var_s0_3], 0x42);
                } else {
                    passout = tempstr->unk_4;
                }
                if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                addstr(&execlist, passout);
                if (run(utob, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror += 1;
                    if (Kflag == 0) {
                        unlink(passout);
                    }
                } else {
                    passin = passout;
                    goto block_1729;
                }
                goto block_2270;
            case 0x65:                              /* switch 19 */
            case 0x72:                              /* switch 19 */
            case 0x73:                              /* switch 19 */
                if (mflag != 0) {
                    execlist.length = 0;
                    addstr(&execlist, "m4");
                    addstr(&execlist, passin);
                    if ((compiler == 4) || ((u8) srcsuf == 0x73)) {
                        passout = tempstr->unk_38;
                    } else {
                        passout = mksuf(srcfiles.entries[var_s0_3], 0x70);
                    }
                    if (run(m4, execlist.entries, NULL, passout, NULL) != 0) {
                        runerror += 1;
                        if (Kflag == 0) {
                            unlink(passout);
                        }
                        goto block_2270;
                    }
                    passin = passout;
                    goto block_1491;
                }
block_1491:
                if ((u8) srcsuf != 0x65) {
                    if ((u8) srcsuf != 0x72) {
                        if ((u8) srcsuf == 0x73) {
                            if (docpp == 0) {
                                if (default_nocpp != 0) {
                                    goto block_531;
                                }
                                goto block_2130;
                            }
                            goto block_531;
                        }
                        goto block_1497;
                    }
                    goto block_1498;
                }
block_1497:
                error(1, NULL, 0, NULL, 0, "efl not supported. Cannot use .e files\n");
                exit(2);
block_1498:
                execlist.length = 0;
                addstr(&execlist, "ratfor");
                addlist(&execlist, &ratforflags);
                addstr(&execlist, passin);
                passout = mksuf(srcfiles.entries[var_s0_3], 0x66);
                if (run(ratfor, execlist.entries, NULL, passout, NULL) != 0) {
                    runerror += 1;
                    if (Kflag == 0) {

                    }
                    goto block_2270;
                }
                if (mflag != 0) {
                    unlink(passin);
                }
                passin = passout;
                if (Fflag == 0) {
                    if (docpp == 0) {
                        goto block_1505;
                    }
                    goto block_531;
                }
                goto block_2270;
            case 0x75:                              /* switch 19 */
block_1896:
                execlist.length = 0;
                addstr(&execlist, "usplit");
                if (vflag != 0) {
                    addstr(&execlist, "-v");
                }
                addlist(&execlist, &usplitflags);
                if (((u8) Hchar == 0x73) || (Kflag != 0)) {
                    passout = mksuf(srcfiles.entries[var_s0_3], 0x53);
                    if (regular_not_writeable(passout) == 1) {
                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                        exit(2);
                    }
                } else {
                    passout = tempstr->unk_14;
                }
                addstr(&execlist, "-o");
                addstr(&execlist, passout);
                addstr(&execlist, "-t");
                addstr(&execlist, symtab);
                addstr(&execlist, passin);
                if (run(usplit, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror += 1;
                    if (Kflag == 0) {
                        unlink(passin);
                        unlink(passout);
                    }
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                } else {
                    if ((Kflag == 0) && ((u8) srcsuf != 0x75) && (uoutfile == NULL)) {
                        unlink(passin);
                    }
                    passin = passout;
                    if ((u8) Hchar != 0x73) {
                        goto block_1913;
                    }
                }
                goto block_2270;
            }
        } else {
        case 0x43:                                  /* switch 19 */
        case 0x45:                                  /* switch 19 */
        case 0x46:                                  /* switch 19 */
        case 0x48:                                  /* switch 19 */
        case 0x49:                                  /* switch 19 */
        case 0x4A:                                  /* switch 19 */
        case 0x4B:                                  /* switch 19 */
        case 0x4C:                                  /* switch 19 */
        case 0x4E:                                  /* switch 19 */
        case 0x50:                                  /* switch 19 */
        case 0x52:                                  /* switch 19 */
        case 0x54:                                  /* switch 19 */
        case 0x57:                                  /* switch 19 */
        case 0x58:                                  /* switch 19 */
        case 0x59:                                  /* switch 19 */
        case 0x5A:                                  /* switch 19 */
        case 0x5B:                                  /* switch 19 */
        case 0x5C:                                  /* switch 19 */
        case 0x5D:                                  /* switch 19 */
        case 0x5E:                                  /* switch 19 */
        case 0x5F:                                  /* switch 19 */
        case 0x60:                                  /* switch 19 */
        case 0x61:                                  /* switch 19 */
        case 0x62:                                  /* switch 19 */
        case 0x64:                                  /* switch 19 */
        case 0x67:                                  /* switch 19 */
        case 0x68:                                  /* switch 19 */
        case 0x6A:                                  /* switch 19 */
        case 0x6B:                                  /* switch 19 */
        case 0x6C:                                  /* switch 19 */
        case 0x6D:                                  /* switch 19 */
        case 0x6E:                                  /* switch 19 */
        case 0x6F:                                  /* switch 19 */
        case 0x71:                                  /* switch 19 */
        case 0x74:                                  /* switch 19 */
block_531:
            dmips_emit = 0;
            execlist.length = 0;
            sp114 = cppchoice;
            execlist.length = 0;
            if ((Eflag != 0) && (irix4 == 0)) {
                compchoice = 3;
            } else if ((u8) srcsuf == 0x73) {
                compchoice = 4;
            }
            if (((u8) srcsuf == 0x63) || ((u8) srcsuf == 6) || ((compiler == 1) && (nocode != 0) && (D_1000BF74 != 0) && ((u8) srcsuf == 0x68))) {
                if ((cppchoice != 2) || ((oldcppflag != 0) && (ansichoice != 0))) {
                    cppchoice = 1;
                    relocate_passes("p", NULL, NULL);
                }
            } else if (((u8) srcsuf == 0x68) && (compiler == 1)) {
                if (cppchoice == 0) {
                    cppchoice = 1;
                    relocate_passes("p", NULL, NULL);
                }
            } else if (compiler == 1) {
                if ((Eflag == 0) && (Pflag == 0) && (cppchoice == 3)) {
                    cppchoice = 2;
                    relocate_passes("p", NULL, NULL);
                }
            } else if (cppchoice == 3) {
                cppchoice = 2;
                relocate_passes("p", NULL, NULL);
            }
            if (((compchoice == 3) || (compchoice == 4)) && (run_sopt == 0) && !(cmp_flag & 1) && !(cmp_flag & 8)) {
                addstr(&execlist, cfe);
            } else {
                if (sixty4bitflag != 0) {
                    error(1, NULL, 0, NULL, 0, "-64bit option is not implemented with ccom or accom.\n");
                    exit(2);
                }
                if (c_compiler_choice == 0) {
                    if ((cppchoice != 1) && (cppchoice != 3)) {
                        var_s3_3 = "cpp";
                    } else {
                        var_s3_3 = "acpp";
                    }
                    addstr(&execlist, var_s3_3);
                }
            }
            if (mips_abi == 1) {
                addstr(&execlist, "-D_MIPS_FPSET=16");
                if (mips1flag != 0) {
                    addstr(&execlist, "-D_MIPS_ISA=1");
                } else if (mips2flag != 0) {
                    addstr(&execlist, "-D_MIPS_ISA=2");
                } else if (mips3flag != 0) {
                    addstr(&execlist, "-D_MIPS_ISA=3");
                }
                addstr(&execlist, "-D_ABIO32=1");
                addstr(&execlist, "-D_MIPS_SIM=_ABIO32");
                addstr(&execlist, "-D_MIPS_SZINT=32");
                addstr(&execlist, "-D_MIPS_SZLONG=32");
                addstr(&execlist, "-D_MIPS_SZPTR=32");
            } else if (mips_abi == 2) {
                addstr(&execlist, "-D_MIPS_FPSET=32");
                addstr(&execlist, "-D_MIPS_ISA=_MIPS_ISA_MIPS3");
                addstr(&execlist, "-D_MIPS_SIM=_MIPS_SIM_ABI64");
                addstr(&execlist, "-D_MIPS_SZINT=32");
                addstr(&execlist, "-D_MIPS_SZLONG=64");
                addstr(&execlist, "-D_MIPS_SZPTR=64");
            } else if (mips_abi != 0) {
                error(1, NULL, 0, NULL, 0, "Unknown value for mips_abi: %d.\n", mips_abi);
                exit(2);
            }
            if (c_compiler_choice == 0) {
                if ((emptyIflag != 0) && (compchoice != 3)) {
                    addstr(&execlist, "-nostdinc");
                }
                if (cppchoice == 1) {
                    if ((ansichoice == 0) || (ansichoice == 3)) {
                        addstr(&execlist, "-D__EXTENSIONS__");
                    }
                    if (compchoice != 3) {
                        if (fullwarn != 0) {
                            addstr(&execlist, "-Wall");
                        }
                        if (acpp_traditional != 0) {
                            addstr(&execlist, "-traditional");
                        }
                        addstr(&execlist, "-trigraphs");
                        if (ansichoice != 0) {
                            addstr(&execlist, "-undef");
                            addstr(&execlist, "-p");
                        }
                    }
                }
                if ((cppchoice == 2) && (compchoice == 3)) {
                    addstr(&execlist, "-D__EXTENSIONS__");
                }
            } else {
                addstr(&execlist, "-YE");
                if (edison_type == (s8* )2) {
                    addstr(&execlist, "-a");
                }
                if ((edison_type == (s8* )1) || (edison_type == (s8* )3)) {
                    addstr(&execlist, "-D__EXTENSIONS__");
                }
            }
            if ((s32) (u8) srcsuf >= 7) {
                switch ((s32) (u8) srcsuf) {        /* switch 13; irregular */
                case 0x70:                          /* switch 13 */
                    addstr(&execlist, "-DLANGUAGE_PASCAL");
                    addstr(&execlist, "-D_LANGUAGE_PASCAL");
                    addstr(&execlist, "-Q");
                    break;
                case 0x46:                          /* switch 13 */
                case 0x65:                          /* switch 13 */
                case 0x66:                          /* switch 13 */
                case 0x72:                          /* switch 13 */
                    addstr(&execlist, "-DLANGUAGE_FORTRAN");
                    addstr(&execlist, "-D_LANGUAGE_FORTRAN");
                    break;
                case 0x73:                          /* switch 13 */
                    addstr(&execlist, "-DLANGUAGE_ASSEMBLY");
                    addstr(&execlist, "-D_LANGUAGE_ASSEMBLY");
                    break;
                }
            } else if ((u8) srcsuf != 1) {
                if ((u8) srcsuf != 2) {
                    if ((u8) srcsuf == 6) {
                    case 0x63:                      /* switch 13 */
                    case 0x68:                      /* switch 13 */
                        if (((u8) srcsuf != 0x68) || (D_1000BF74 != 0)) {
                            if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                                addstr(&execlist, "-D_LANGUAGE_C_PLUS_PLUS=1");
                                addstr(&execlist, "-D__cplusplus=1");
                                addstr(&execlist, "-D__ANSI_CPP__=1");
                                if ((compiler == 1) && (c_compiler_choice == 3)) {
                                    addstr(&execlist, "-D_DELTA_EXTENSIONS=1");
                                }
                            } else {
                                if ((ansichoice == 0) || (ansichoice == 3)) {
                                    addstr(&execlist, "-DLANGUAGE_C");
                                }
                                addstr(&execlist, "-D_LANGUAGE_C");
                                if (cmp_flag != 0) {
                                    addstr(&execlist, "-D_LANGUAGE_PWRC");
                                }
                                if (((cmp_flag & 1) || (run_sopt != 0)) && (cppchoice == 1)) {
                                    addstr(&execlist, "-trigraphs");
                                }
                            }
                        }
                    }
                } else {
                    addstr(&execlist, "-DLANGUAGE_COBOL");
                    addstr(&execlist, "-D_LANGUAGE_COBOL");
                }
            } else {
                addstr(&execlist, "-DLANGUAGE_PL1");
                addstr(&execlist, "-D_LANGUAGE_PL1");
            }
            if ((ansichoice == 0) || (ansichoice == 3)) {
                addstr(&execlist, "-D__INLINE_INTRINSICS");
                addstr(&execlist, "-Dsgi");
                if (svr4_systype == 0) {
                    addstr(&execlist, "-DSVR3");
                    addstr(&execlist, "-D__SVR3");
                }
                addstr(&execlist, "-D__sgi");
            } else {
                addstr(&execlist, "-D__sgi");
                if (svr4_systype == 0) {
                    addstr(&execlist, "-D__SVR3");
                }
            }
            if ((compchoice != 3) && (dollar_sign != 0)) {
                if (cppchoice == 1) {
                    addstr(&execlist, "-$");
                } else {
                    addstr(&execlist, "-dollar");
                }
            }
            if ((ansichoice == 0) || (ansichoice == 3)) {
                addstr(&execlist, "-Dunix");
                addstr(&execlist, "-Dmips");
                addstr(&execlist, "-Dhost_mips");
                addstr(&execlist, "-D__unix");
                addstr(&execlist, "-D__host_mips");
                if (irix4 == 0) {
                    if ((svr4_systype != 0) && (ansichoice != 1) && (ansichoice != 2)) {
                        addstr(&execlist, "-D_SVR4_SOURCE");
                    }
                    addstr(&execlist, "-D_MODERN_C");
                    addstr(&execlist, "-D_SGI_SOURCE");
                }
                if (kpic_flag != 0) {
                    addstr(&execlist, "-D_PIC");
                }
                addstr(&execlist, "-D__DSO__");
            } else {
                addstr(&execlist, "-D__unix");
                addstr(&execlist, "-D__host_mips");
                if (irix4 == 0) {
                    if ((svr4_systype != 0) && (ansichoice != 1) && (ansichoice != 2)) {
                        addstr(&execlist, "-D_SVR4_SOURCE");
                    }
                    addstr(&execlist, "-D_MODERN_C");
                }
                if (kpic_flag != 0) {
                    addstr(&execlist, "-D_PIC");
                }
                addstr(&execlist, "-D__DSO__");
            }
            if ((systype != NULL) && (irix4 == 0)) {
                var_s1_2 = systype;
                if ((u8) *var_s1_2 != 0) {
                    do {
                        var_s1_2->unk_0 = toupper((s32) (u8) var_s1_2->unk_0);
                        var_s1_2 += 1;
                    } while (var_s1_2->unk_1 != 0);
                }
                if ((ansichoice == 0) || (ansichoice == 3)) {
                    addstr(&execlist, mkstr("-DSYSTYPE_", systype, NULL));
                }
                addstr(&execlist, mkstr("-D_SYSTYPE_", systype, NULL));
            }
            if (svr4_systype == 0) {
                if ((ansichoice == 0) || (ansichoice == 3)) {
                    addstr(&execlist, "-DSYSTYPE_SYSV");
                }
                addstr(&execlist, "-D_SYSTYPE_SYSV");
            }
            if (sixty4bitflag != 0) {
                addstr(&execlist, "-D__64BIT");
            }
            if (((ansichoice == 0) || (ansichoice == 3)) && (longlong_emitted == 0)) {
                addstr(&execlist, "-D_LONGLONG");
                longlong_emitted = 1;
            }
            if (dmips_emit == 0) {
                if (mips2flag != 0) {
                    if (((call_shared != 0) || (default_call_shared != 0)) && (kpic_flag == 0)) {
                        old_non_shared = 1;
                        non_shared = 1;
                        default_call_shared = 0;
                        call_shared = 0;
                    }
                    addstr(&execlist, "-D__mips=2");
                } else if (mips3flag != 0) {
                    addstr(&execlist, "-D__mips=3");
                } else {
                    addstr(&execlist, "-D__mips=1");
                }
            }
            dmips_emit = 1;
            if (irix4 != 0) {
                include = mkstr("/usr/irix4/", "usr/include", NULL);
            }
            if ((((include != NULL) && ((strcmp(comp_target_root, "/") != 0) || (systype != NULL))) || (fiveflag != 0)) && ((compiler != 1) || (c_compiler_choice == 0)) && ((compiler != 3) || (D_1000BF74 == 0))) {
                addstr(&execlist, "-I");
            }
            addlist(&execlist, &cppflags);
            if (cppchoice == 1) {
                addlist(&execlist, &acppflags);
            }
            addlist(&execlist, &undefineflags);
            if (emptyIflag == 0) {
                if ((abi_flag != 0) && (includeB != NULL)) {
                    addstr(&execlist, mkstr("-I", includeB, NULL));
                }
                if ((einclude != NULL) && (compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                    addstr(&execlist, mkstr("-I", einclude, NULL));
                }
                if (include != NULL) {
                    addstr(&execlist, mkstr("-I", include, NULL));
                }
            }
            if (Pflag != 0) {
                if ((compiler == 4) && (getsuf(srcfiles.entries[var_s0_3]) == 0)) {
                    passout = mkstr(srcfiles.entries[var_s0_3], ".i", NULL);
                } else {
                    passout = mksuf(srcfiles.entries[var_s0_3], 0x69);
                }
            } else if (Eflag != 0) {
                passout = NULL;
            } else if (((u8) Hchar == 0x4B) || (Kflag != 0)) {
                if ((compchoice == 3) && (run_sopt == 0) && (acpp == 0) && (cmp_flag == 0) && (compiler == 1)) {
                    passout = mksuf(srcfiles.entries[var_s0_3], 0x42);
                } else {
                    passout = mksuf(srcfiles.entries[var_s0_3], 0x69);
                }
            } else {
                passout = tempstr->unk_8;
            }
            if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                exit(2);
            }
            if ((compiler == 3) && (D_1000BF74 != 0)) {
                addstr(&execlist, "-K");
                addstr(&execlist, "-E");
                addstr(&execlist, sp144);
            }
            if (c_compiler_choice == 0) {
                addstr(&execlist, passin);
            }
            if (((compchoice != 3) && (compchoice != 4)) || ((compiler != 1) && (compiler != 4)) || (run_sopt != 0) || (cmp_flag & 1) || (cmp_flag & 8) || (acpp != 0) || (oldcppflag != 0)) {
                if ((compiler == 3) && (D_1000BF74 != 0)) {
                    var_s3_4 = &cfe;
                } else {
                    var_s3_4 = &cpp;
                }
                if (run(*var_s3_4, execlist.entries, NULL, passout, NULL) != 0) {
                    runerror += 1;
                    if ((Eflag == 0) && (((((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72)) && (Kflag == 0)) || (((u8) srcsuf == 0x73) && (mflag != 0)))) {
                        unlink(passin);
                    }
                    unlink(passout);
                    cppchoice = sp114;
                    relocate_passes("p", NULL, NULL);
                    goto block_2269;
                }
                goto block_922;
            }
            cppchoice = sp114;
            relocate_passes("p", NULL, NULL);
            if ((((u8) srcsuf != 0x63) && ((u8) srcsuf != 6) && ((compiler != 1) || (nocode == 0) || (D_1000BF74 == 0) || ((u8) srcsuf != 0x68))) || (Pflag != 0) || (Eflag != 0)) {
                if (minus_M == 0) {
                    addstr(&execlist, "-E");
                }
                if ((compiler != 1) || (c_compiler_choice == 0)) {
                    switch ((s32) (u8) srcsuf) {    /* switch 16; irregular */
                    case 0x63:                      /* switch 16 */
                        addstr(&execlist, "-D_LANGUAGE_C");
                        if (oldcflag == 0) {
                            addstr(&execlist, "-D_CFE");
                        }
                        break;
                    case 0x70:                      /* switch 16 */
                        addstr(&execlist, "-DLANGUAGE_PASCAL");
                        addstr(&execlist, "-D_LANGUAGE_PASCAL");
                        addstr(&execlist, "-Q");
                        break;
                    case 0x46:                      /* switch 16 */
                    case 0x65:                      /* switch 16 */
                    case 0x66:                      /* switch 16 */
                    case 0x72:                      /* switch 16 */
                        addstr(&execlist, "-DLANGUAGE_FORTRAN");
                        addstr(&execlist, "-D_LANGUAGE_FORTRAN");
                        break;
                    case 0x73:                      /* switch 16 */
                        addstr(&execlist, "-std0");
                        addstr(&execlist, "-DLANGUAGE_ASSEMBLY");
                        addstr(&execlist, "-D_LANGUAGE_ASSEMBLY");
                        break;
                    case 0x1:                       /* switch 16 */
                        addstr(&execlist, "-DLANGUAGE_PL1");
                        addstr(&execlist, "-D_LANGUAGE_PL1");
                        break;
                    case 0x2:                       /* switch 16 */
                        addstr(&execlist, "-DLANGUAGE_COBOL");
                        addstr(&execlist, "-D_LANGUAGE_COBOL");
                        break;
                    }
                    addstr(&execlist, "-D__unix");
                    if (sixty4bitflag != 0) {
                        addstr(&execlist, "-D__64BIT");
                    }
                    if (((ansichoice == 0) || (ansichoice == 3)) && (longlong_emitted == 0)) {
                        addstr(&execlist, "-D_LONGLONG");
                        longlong_emitted = 1;
                    }
                    if (dmips_emit == 0) {
                        if (mips2flag != 0) {
                            if ((call_shared != 0) || (default_call_shared != 0)) {
                                old_non_shared = 1;
                                non_shared = 1;
                                default_call_shared = 0;
                                call_shared = 0;
                            }
                            addstr(&execlist, "-D__mips=2");
                        } else if (mips3flag != 0) {
                            addstr(&execlist, "-D__mips=3");
                        } else {
                            addstr(&execlist, "-D__mips=1");
                        }
                    }
                    dmips_emit = 1;
                    addstr(&execlist, "-D__host_mips");
                    if (kpic_flag != 0) {
                        addstr(&execlist, "-D_PIC");
                    }
                    addstr(&execlist, "-D__DSO__");
                    if (systype != NULL) {
                        var_s1_3 = systype;
                        if ((u8) *var_s1_3 != 0) {
                            do {
                                var_s1_3->unk_0 = toupper((s32) (u8) var_s1_3->unk_0);
                                var_s1_3 += 1;
                            } while (var_s1_3->unk_1 != 0);
                        }
                    } else {
                        addstr(&execlist, "-D_SYSTYPE_SVR4");
                    }
                }
                if ((Eflag == 0) && (Pflag == 0)) {
                    if ((((include != NULL) && ((strcmp(comp_target_root, "/") != 0) || (systype != NULL))) || (fiveflag != 0)) && (c_compiler_choice == 0)) {
                        addstr(&execlist, "-I");
                    }
                    addlist(&execlist, &cppflags);
                    addlist(&execlist, &undefineflags);
                    if (cpp_stdflag != NULL) {
                        addstr(&execlist, cpp_stdflag);
                    }
                    if (emptyIflag == 0) {
                        if ((abi_flag != 0) && (includeB != NULL)) {
                            addstr(&execlist, mkstr("-I", includeB, NULL));
                        }
                        if (include != NULL) {
                            addstr(&execlist, mkstr("-I", include, NULL));
                        }
                    }
                }
                if (((Pflag != 0) || (Eflag != 0)) && (c_compiler_choice == 0)) {
                    if ((ansichoice == 1) || (ansichoice == 2)) {
                        addstr(&execlist, "-std1");
                    } else if (ansichoice == 3) {
                        addstr(&execlist, "-std");
                    } else if (ansichoice == 0) {
                        addstr(&execlist, "-std0");
                    }
                }
                if ((compiler == 1) && (c_compiler_choice != 0)) {
                    if (vflag != 0) {
                        addstr(&execlist, "-v");
                    }
                    if (fullwarn != 0) {
                        addstr(&execlist, "-Yw");
                    }
                    if (srcfiles.length == 1) {
                        if (outfile != NULL) {
                            sp118 = outfile;
                        } else if (cflag == 0) {
                            sp118 = "a.out";
                        } else {
                            var_v0_4 = mksuf(srcfiles.entries[var_s0_3], 0x6F);
                            goto block_870;
                        }
                    } else {
                        var_v0_4 = mksuf(srcfiles.entries[var_s0_3], 0x6F);
block_870:
                        sp118 = var_v0_4;
                    }
                    addstr(&execlist, mkstr("-YN", sp118, NULL));
                    if (c_compiler_choice != 2) {
                        if (c_compiler_choice == 3) {
                            addstr(&execlist, "-YD");
                        } else if (edison_type == (s8* )3) {
                            addstr(&execlist, "-K");
                        } else {
                            addstr(&execlist, "-m");
                        }
                    }
                    addstr(&execlist, passin);
                }
                if (Pflag != 0) {
                    if ((compiler == 4) && (getsuf(srcfiles.entries[var_s0_3]) == 0)) {
                        passout = mkstr(srcfiles.entries[var_s0_3], ".i", NULL);
                    } else {
                        passout = mksuf(srcfiles.entries[var_s0_3], 0x69);
                    }
                } else if (Eflag != 0) {
                    passout = NULL;
                } else {
                    passout = tempstr->unk_8;
                }
                if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                if (oldcflag == 1) {
                    if (oldcppflag != 0) {
                        var_v0_5 = run(cpp, execlist.entries, NULL, passout, NULL);
                    } else {
                        var_v0_5 = run(cpp, execlist.entries, NULL, passout, NULL);
                    }
                } else if (oldcppflag != 0) {
                    var_v0_5 = run(cpp, execlist.entries, NULL, passout, NULL);
                } else {
                    var_v0_5 = run(cfe, execlist.entries, NULL, passout, NULL);
                }
                retcode = var_v0_5;
                if (retcode != 0) {
                    runerror += 1;
                    if ((Eflag == 0) && (((((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72)) && (Kflag == 0)) || (((u8) srcsuf == 0x73) && (mflag != 0)))) {
                        unlink(passin);
                    }
                    unlink(passout);
                    goto block_2269;
                }
                if ((Pflag == 0) && (Eflag == 0)) {
                    if (((((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72)) && (Kflag == 0)) || (((u8) srcsuf == 0x73) && (mflag != 0))) {
                        unlink(passin);
                    }
                    passin = passout;
                    dmips_emit = 0;
                    switch ((s32) (u8) srcsuf) {    /* switch 17; irregular */
                    case 0x64:                      /* switch 17 */
                    case 0x67:                      /* switch 17 */
                    case 0x68:                      /* switch 17 */
                    case 0x69:                      /* switch 17 */
                    case 0x6A:                      /* switch 17 */
                    case 0x6B:                      /* switch 17 */
                    case 0x6C:                      /* switch 17 */
                    case 0x6D:                      /* switch 17 */
                    case 0x6E:                      /* switch 17 */
                    case 0x6F:                      /* switch 17 */
                    case 0x71:                      /* switch 17 */
block_922:
                        cppchoice = sp114;
                        relocate_passes("p", NULL, NULL);
                        if (c_compiler_choice == 0) {
                            if ((Pflag == 0) && (Eflag == 0)) {
                                if (((((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72)) && (Kflag == 0)) || (((u8) srcsuf == 0x73) && (mflag != 0))) {
                                    unlink(passin);
                                }
                                passin = passout;
                                goto block_932;
                            }
                            goto block_2270;
                        }
block_932:
                        dmips_emit = 0;
                        switch ((s32) (u8) srcsuf) { /* switch 18; irregular */
                        case 0x63:                  /* switch 17 */
                        case 0x63:                  /* switch 18 */
                        case 0x64:                  /* switch 18 */
                        case 0x67:                  /* switch 18 */
                        case 0x68:                  /* switch 18 */
                        case 0x69:                  /* switch 18 */
                        case 0x6A:                  /* switch 18 */
                        case 0x6B:                  /* switch 18 */
                        case 0x6C:                  /* switch 18 */
                        case 0x6D:                  /* switch 18 */
                        case 0x6E:                  /* switch 18 */
                        case 0x6F:                  /* switch 18 */
                        case 0x71:                  /* switch 18 */
                        case 1:                     /* switch 4 */
block_940:
                            if (run_sopt != 0) {
                                if (cmp_flag & 1) {
                                    error(2, NULL, 0, NULL, 0, "-sopt and -pca both specified; -sopt ignored.\n");
                                    goto block_989;
                                }
                                execlist.length = 0;
                                addstr(&execlist, "copt");
                                if ((Oflag >= 2) && (set_loop_unroll == 0)) {
                                    addstr(&optflags, "-loopunroll");
                                    addstr(&optflags, "0");
                                }
                                addstr(&execlist, mkstr("-I=", passin, NULL));
                                if (((u8) Hchar == 0x4B) || (Kflag != 0)) {
                                    var_v0_6 = mksuf(srcfiles.entries[var_s0_3], 0x4D);
                                } else {
                                    var_v0_6 = mkstr(tempstr->unk_7C, "M", NULL);
                                }
                                passout = var_v0_6;
                                addstr(&execlist, mkstr("-CMP=", passout, NULL));
                                addstr(&execlist, "-cp=i");
                                if (ansichoice == 0) {
                                    addstr(&execlist, "-sy=k");
                                }
                                addlist(&execlist, &soptflags);
                                if (run(copt, execlist.entries, NULL, NULL, NULL) != 0) {
                                    runerror += 1;
                                    if ((docpp != 0) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                        unlink(passin);
                                    }
                                    if (((u8) Hchar != 0x4B) || (Kflag != 0)) {
                                        unlink(passout);
                                    }
                                    goto block_2270;
                                }
                                if ((docpp != 0) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                    unlink(passin);
                                }
                                passin = passout;
                                if ((compchoice != 3) || (cmp_flag & 0x10000)) {
                                    if ((u8) Hchar != 0x4B) {
                                        if (((u8) Hchar == 0x4B) || (Kflag != 0)) {
                                            var_v0_7 = mksuf(srcfiles.entries[var_s0_3], 0x49);
                                        } else {
                                            var_v0_7 = mkstr(tempstr->unk_7C, "I", NULL);
                                        }
                                        passout = var_v0_7;
                                        if (vflag != 0) {
                                            addstr(&execlist, "-v");
                                        }
                                        execlist.length = 0;
                                        if ((cppchoice != 1) && (cppchoice != 3)) {
                                            var_s3_5 = "cpp";
                                        } else {
                                            var_s3_5 = "acpp";
                                        }
                                        addstr(&execlist, var_s3_5);
                                        addstr(&execlist, passin);
                                        if (cppchoice != 2) {
                                            cppchoice = 1;
                                        } else {
                                            addstr(&execlist, "-l");
                                        }
                                        if (emptyIflag != 0) {
                                            addstr(&execlist, "-nostdinc");
                                        }
                                        addlist(&execlist, &cpp2flags);
                                        relocate_passes("p", NULL, NULL);
                                        if (run(cpp, execlist.entries, NULL, passout, NULL) != 0) {
                                            runerror += 1;
                                            if (Kflag == 0) {
                                                unlink(passin);
                                            }
                                            unlink(passout);
                                            goto block_2269;
                                        }
                                        if (Kflag == 0) {
                                            unlink(passin);
                                        }
                                        passin = passout;
                                        goto block_1042;
                                    }
                                    goto block_2270;
                                }
                                goto block_1042;
                            }
block_989:
                            if (((u8) Hchar == 0x4B) || (Kflag != 0)) {
                                cmp_flag |= 6;
                            }
                            if (cmp_flag & 1) {
                                if ((Oflag >= 2) && (set_loop_unroll == 0)) {
                                    addstr(&optflags, "-loopunroll");
                                    addstr(&optflags, "0");
                                }
                                execlist.length = 0;
                                addstr(&execlist, "pca");
                                addstr(&execlist, mkstr("-I=", passin, NULL));
                                if (cmp_flag & 4) {
                                    var_v0_8 = mksuf(srcfiles.entries[var_s0_3], 0x4D);
                                } else {
                                    var_v0_8 = mkstr(tempstr->unk_7C, "M", NULL);
                                }
                                passout = var_v0_8;
                                addstr(&execlist, mkstr("-CMP=", passout, NULL));
                                if (cmp_flag & 2) {
                                    var_v0_9 = mksuf(srcfiles.entries[var_s0_3], 0x4C);
                                } else {
                                    var_v0_9 = mkstr(tempstr->unk_7C, "L", NULL);
                                }
                                sp110 = var_v0_9;
                                addstr(&execlist, mkstr("-L=", sp110, NULL));
                                addstr(&execlist, "-lo=ls");
                                addstr(&execlist, "-cp=i");
                                if (ansichoice == 0) {
                                    addstr(&execlist, "-sy=k");
                                }
                                addlist(&execlist, &pcaflags);
                                if (run(pca, execlist.entries, NULL, NULL, NULL) != 0) {
                                    runerror += 1;
                                    if ((docpp != 0) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                        unlink(passin);
                                    }
                                    if (!(cmp_flag & 4)) {
                                        unlink(passout);
                                    }
                                    goto block_2270;
                                }
                                if (!(cmp_flag & 2)) {
                                    unlink(sp110);
                                }
                                if ((docpp != 0) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                    unlink(passin);
                                }
                                passin = passout;
                                if ((u8) Hchar != 0x4B) {
                                    execlist.length = 0;
                                    if ((cppchoice != 1) && (cppchoice != 3)) {
                                        var_s3_6 = "cpp";
                                    } else {
                                        var_s3_6 = "acpp";
                                    }
                                    addstr(&execlist, var_s3_6);
                                    if (((u8) Hchar == 0x4B) || (Kflag != 0)) {
                                        var_v0_10 = mksuf(srcfiles.entries[var_s0_3], 0x49);
                                    } else {
                                        var_v0_10 = mkstr(tempstr->unk_7C, "I", NULL);
                                    }
                                    passout = var_v0_10;
                                    if (vflag != 0) {
                                        addstr(&execlist, "-v");
                                    }
                                    addstr(&execlist, passin);
                                    if (cppchoice != 2) {
                                        cppchoice = 1;
                                    } else {
                                        addstr(&execlist, "-l");
                                    }
                                    if (emptyIflag != 0) {
                                        addstr(&execlist, "-nostdinc");
                                    }
                                    addlist(&execlist, &cpp2flags);
                                    addlist(&execlist, &undefineflags);
                                    relocate_passes("p", NULL, NULL);
                                    if (run(cpp, execlist.entries, NULL, passout, NULL) != 0) {
                                        runerror += 1;
                                        if ((Kflag == 0) && !(cmp_flag & 4)) {
                                            unlink(passin);
                                        }
                                        unlink(passout);
                                        goto block_2269;
                                    }
                                    if ((Kflag == 0) && !(cmp_flag & 4)) {
                                        unlink(passin);
                                    }
                                    passin = passout;
                                    goto block_1042;
                                }
                                goto block_2270;
                            }
                            goto block_1042;
                        case 0x70:                  /* switch 17 */
                        case 0x70:                  /* switch 18 */
                        case 2:                     /* switch 4 */
block_1341:
                            execlist.length = 0;
                            addstr(&execlist, "upas");
                            if (vflag != 0) {
                                addstr(&execlist, "-v");
                            }
                            addstr(&execlist, "-G");
                            addstr(&execlist, Gnum);
                            addlist(&execlist, &upasflags);
                            addstr(&execlist, passin);
                            if ((((u8) Hchar == 0x66) && (ucodeflag == 0)) || (Kflag != 0)) {
                                passout = mksuf(srcfiles.entries[var_s0_3], 0x42);
                                if (regular_not_writeable(passout) == 1) {
                                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                    exit(2);
                                }
                            } else {
                                passout = tempstr->unk_C;
                            }
                            addstr(&execlist, passout);
                            addstr(&execlist, "-t");
                            addstr(&execlist, symtab);
                            if (run(upas, execlist.entries, NULL, NULL, errout) != 0) {
                                if (editflag != 0) {
                                    if (times_edited < edit_cnt_max) {
                                        times_edited += 1;
                                        if (edit_src(editor, srcfiles.entries[var_s0_3], 2) != 0) {
                                            show_err(errout);
                                            exit(1);
                                        }
                                        if ((stdflag == 0) && (docpp != 0) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                            unlink(passin);
                                        }
                                        unlink(passout);
                                        unlink(errout);
                                        unlink(symtab);
                                        passin = srcfiles.entries[var_s0_3];
                                        goto loop_484;
                                    }
                                    show_err(errout);
                                    goto block_1361;
                                }
block_1361:
                                runerror += 1;
                                if ((stdflag == 0) && (docpp != 0) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                    unlink(passin);
                                }
                                if (Kflag == 0) {
                                    unlink(passout);
                                    unlink(symtab);
                                }
                                goto block_2270;
                            }
                            if (editflag != 0) {
                                unlink(errout);
                            }
                            if ((stdflag == 0) && (docpp != 0) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                unlink(passin);
                            }
                            passin = passout;
                            if (((u8) Hchar == 0x66) && (ucodeflag != 0)) {
                                execlist.length = 0;
                                addstr(&execlist, "btou");
                                addstr(&execlist, passin);
                                passout = mksuf(srcfiles.entries[var_s0_3], 0x55);
                                if (regular_not_writeable(passout) == 1) {
                                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                    exit(2);
                                }
                                addstr(&execlist, passout);
                                if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                                    runerror += 1;
                                    if (Kflag == 0) {
                                        unlink(passin);
                                        unlink(passout);
                                    }
                                    if (tmpst != 0) {
                                        unlink(symtab);
                                    }
                                } else if (Kflag == 0) {
                                    unlink(passin);
                                }
                            } else if ((u8) Hchar == 0x66) {

                            } else {
                                goto block_1729;
                            }
                            goto block_2270;
                        case 0x1:                   /* switch 17 */
                        case 0x1:                   /* switch 18 */
                        case 5:                     /* switch 4 */
block_1388:
                            execlist.length = 0;
                            addstr(&execlist, "pl1fe");
                            if (vflag != 0) {
                                addstr(&execlist, "-v");
                            }
                            addlist(&execlist, &upl1flags);
                            addstr(&execlist, passin);
                            if (((u8) Hchar == 0x66) || (Kflag != 0)) {
                                passout = mksuf(srcfiles.entries[var_s0_3], 3);
                                lpi_st = mksuf(srcfiles.entries[var_s0_3], 4);
                            } else {
                                passout = tempstr->unk_40;
                                lpi_st = tempstr->unk_44;
                            }
                            lpi_p1 = tempstr->unk_48;
                            addstr(&execlist, "-o");
                            addstr(&execlist, passout);
                            addstr(&execlist, "-s");
                            addstr(&execlist, lpi_st);
                            addstr(&execlist, "-p");
                            addstr(&execlist, lpi_p1);
                            addstr(&execlist, "-e");
                            addstr(&execlist, pl1err);
                            if (run(upl1, execlist.entries, NULL, errout, NULL) != 0) {
                                if (editflag != 0) {
                                    if (times_edited < edit_cnt_max) {
                                        times_edited += 1;
                                        if (edit_src(editor, srcfiles.entries[var_s0_3], 5) != 0) {
                                            show_err(errout);
                                            exit(1);
                                        }
                                        if ((docpp != 0) && ((u8) srcsuf != 0x69)) {
                                            unlink(passin);
                                        }
                                        unlink(passout);
                                        unlink(errout);
                                        unlink(lpi_st);
                                        unlink(lpi_p1);
                                        passin = srcfiles.entries[var_s0_3];
                                        goto loop_484;
                                    }
                                    show_err(errout);
                                    goto block_1404;
                                }
block_1404:
                                runerror += 1;
                                if ((docpp != 0) && ((u8) srcsuf != 0x69)) {
                                    unlink(passin);
                                }
                                if (Kflag == 0) {
                                    unlink(passout);
                                    unlink(lpi_st);
                                }
                                unlink(lpi_p1);
                                goto block_2269;
                            }
                            if (editflag != 0) {
                                unlink(errout);
                            }
                            unlink(lpi_p1);
                            if ((docpp != 0) && ((u8) srcsuf != 0x69)) {
                                unlink(passin);
                            }
                            if ((u8) Hchar != 0x66) {
                                passin = passout;
                            case 0x3:               /* switch 19 */
block_1417:
                                execlist.length = 0;
                                addstr(&execlist, "ulpi");
                                if (vflag != 0) {
                                    addstr(&execlist, "-v");
                                }
                                addlist(&execlist, &ulpiflags);
                                addstr(&execlist, passin);
                                if ((((u8) Hchar == 0x6B) && (ucodeflag == 0)) || (Kflag != 0)) {
                                    passout = mksuf(srcfiles.entries[var_s0_3], 0x42);
                                } else {
                                    passout = tempstr->unk_C;
                                }
                                if (((u8) srcsuf == 3) || (Kflag != 0)) {
                                    lpi_st = mksuf(srcfiles.entries[var_s0_3], 4);
                                } else {
                                    lpi_st = tempstr->unk_44;
                                }
                                addstr(&execlist, "-s");
                                addstr(&execlist, lpi_st);
                                addstr(&execlist, "-o");
                                addstr(&execlist, passout);
                                addstr(&execlist, "-t");
                                addstr(&execlist, symtab);
                                if (run(ulpi, execlist.entries, NULL, NULL, NULL) != 0) {
                                    runerror += 1;
                                    if ((u8) srcsuf != 3) {
                                        unlink(passin);
                                    }
                                    if (Kflag == 0) {
                                        unlink(passout);
                                        if ((u8) srcsuf != 3) {
                                            unlink(lpi_st);
                                        }
                                    }
                                    if (tmpst != 0) {
                                        unlink(symtab);
                                    }
                                } else {
                                    if (((u8) srcsuf != 3) && (Kflag == 0)) {
                                        unlink(passin);
                                    }
                                    if ((Kflag == 0) && ((u8) srcsuf != 3)) {
                                        unlink(lpi_st);
                                    }
                                    passin = passout;
                                    if (((u8) Hchar == 0x6B) && (ucodeflag != 0)) {
                                        execlist.length = 0;
                                        addstr(&execlist, "btou");
                                        addstr(&execlist, passin);
                                        passout = mksuf(srcfiles.entries[var_s0_3], 0x55);
                                        addstr(&execlist, passout);
                                        if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                                            runerror += 1;
                                            if (Kflag == 0) {
                                                unlink(passin);
                                                unlink(passout);
                                            }
                                            if (tmpst != 0) {
                                                unlink(symtab);
                                            }
                                        } else if (Kflag == 0) {
                                            unlink(passin);
                                        }
                                    } else if ((u8) Hchar == 0x6B) {

                                    } else {
                                        goto block_1729;
                                    }
                                }
                            }
                            goto block_2270;
                        case 0x2:                   /* switch 17 */
                        case 0x2:                   /* switch 18 */
                        case 6:                     /* switch 4 */
block_1453:
                            execlist.length = 0;
                            addstr(&execlist, "cobfe");
                            if (vflag != 0) {
                                addstr(&execlist, "-v");
                            }
                            addlist(&execlist, &ucobflags);
                            addstr(&execlist, passin);
                            if (((u8) Hchar == 0x66) || (Kflag != 0)) {
                                passout = mksuf(srcfiles.entries[var_s0_3], 3);
                                lpi_st = mksuf(srcfiles.entries[var_s0_3], 4);
                            } else {
                                passout = tempstr->unk_40;
                                lpi_st = tempstr->unk_44;
                            }
                            lpi_p1 = tempstr->unk_48;
                            lpi_pd = tempstr->unk_50;
                            lpi_dd = tempstr->unk_4C;
                            addstr(&execlist, "-o");
                            addstr(&execlist, passout);
                            addstr(&execlist, "-s");
                            addstr(&execlist, lpi_st);
                            addstr(&execlist, "-p");
                            addstr(&execlist, lpi_p1);
                            addstr(&execlist, "-pd");
                            addstr(&execlist, lpi_pd);
                            addstr(&execlist, "-dd");
                            addstr(&execlist, lpi_dd);
                            addstr(&execlist, "-e");
                            addstr(&execlist, pl1err);
                            if (run(ucob, execlist.entries, NULL, errout, NULL) != 0) {
                                if (editflag != 0) {
                                    if (times_edited < edit_cnt_max) {
                                        times_edited += 1;
                                        if (edit_src(editor, srcfiles.entries[var_s0_3], 6) != 0) {
                                            show_err(errout);
                                            exit(1);
                                        }
                                        if ((docpp != 0) && ((u8) srcsuf != 0x69)) {
                                            unlink(passin);
                                        }
                                        unlink(passout);
                                        unlink(errout);
                                        unlink(lpi_st);
                                        unlink(lpi_p1);
                                        unlink(lpi_pd);
                                        unlink(lpi_dd);
                                        passin = srcfiles.entries[var_s0_3];
                                        goto loop_484;
                                    }
                                    show_err(errout);
                                    goto block_1469;
                                }
block_1469:
                                runerror += 1;
                                if ((docpp != 0) && ((u8) srcsuf != 0x69)) {
                                    unlink(passin);
                                }
                                if (Kflag == 0) {
                                    unlink(passout);
                                    unlink(lpi_st);
                                }
                                unlink(lpi_p1);
                                unlink(lpi_pd);
                                unlink(lpi_dd);
                                goto block_2269;
                            }
                            if (editflag != 0) {
                                unlink(errout);
                            }
                            if ((docpp != 0) && ((u8) srcsuf != 0x69)) {
                                unlink(passin);
                            }
                            unlink(lpi_p1);
                            unlink(lpi_pd);
                            unlink(lpi_dd);
                            if ((u8) Hchar != 0x66) {
                                passin = passout;
                                goto block_1417;
                            }
                            goto block_2270;
                        case 0x46:                  /* switch 17 */
                        case 0x65:                  /* switch 17 */
                        case 0x66:                  /* switch 17 */
                        case 0x72:                  /* switch 17 */
                        case 0x46:                  /* switch 18 */
                        case 0x65:                  /* switch 18 */
                        case 0x66:                  /* switch 18 */
                        case 0x72:                  /* switch 18 */
                        case 3:                     /* switch 4 */
block_1505:
                            sp100 = 0;
                            spFC = 0;
                            spF0.unk_0 = 0x31;
                            spF0.unk_1 = 0;
                            if (run_sopt != 0) {
                                if (mp_flag & 1) {
                                    error(2, NULL, 0, NULL, 0, "-sopt and -pfa both specified; -sopt ignored.\n");
                                    goto block_1566;
                                }
                                if ((Oflag >= 2) && (set_loop_unroll == 0)) {
                                    addstr(&optflags, "-loopunroll");
                                    addstr(&optflags, "0");
                                }
                                if ((mp_i2flag != 0) && (w1flag != 2)) {
                                    error(2, NULL, 0, NULL, 0, "fopt does not recognize the -i2 option\n");
                                }
                                if ((mp_66flag != 0) && (w1flag != 2)) {
                                    error(2, NULL, 0, NULL, 0, "fopt does not recognize the -66 option\n");
                                }
                                if ((mp_uflag != 0) && (w1flag != 2)) {
                                    error(2, NULL, 0, NULL, 0, "fopt does not recognize the -u option\n");
                                }
                                if ((mp_backslashflag != 0) && (w1flag != 2)) {
                                    error(2, NULL, 0, NULL, 0, "fopt does not support the -backslash option\n");
                                }
                                if (mp_caseflag != 0) {
                                    error(1, NULL, 0, NULL, 0, "fopt does not support the -U option\n");
                                    exit(2);
                                }
                                execlist.length = 0;
                                addstr(&execlist, "fopt");
                                spF4 = mkstr(tempstr->unk_7C, "l", NULL);
                                addstr(&execlist, mkstr("-L=", spF4, NULL));
                                if (((u8) Hchar == 0x4B) || (Kflag != 0)) {
                                    var_v0_11 = mksuf(srcfiles.entries[var_s0_3], 0x6D);
                                } else {
                                    var_v0_11 = mkstr(tempstr->unk_7C, "m", &spF0, NULL);
                                }
                                passout = var_v0_11;
                                addstr(&execlist, mkstr("-F=", passout, NULL));
                                addstr(&execlist, mkstr("-I=", passin, NULL));
                                if (mp_col120flag != 0) {
                                    addstr(&execlist, "-scan=120");
                                }
                                if (mp_extendflag != 0) {
                                    addstr(&execlist, "-scan=132");
                                }
                                if (automaticflag == 0) {
                                    addstr(&execlist, "-save=all");
                                }
                                if (mp_onetripflag != 0) {
                                    addstr(&execlist, "-onetrip");
                                }
                                if (mp_dlinesflag != 0) {
                                    addstr(&execlist, "-dlines");
                                }
                                if (w1flag == 2) {
                                    addstr(&execlist, "-suppress=w");
                                }
                                if (vflag != 0) {
                                    addstr(&execlist, "-lo=lno");
                                }
                                if (irix4 != 0) {
                                    addstr(&execlist, mkstr("-customer=", mksuf(srcfiles.entries[var_s0_3], (s8) (u8) srcsuf), NULL));
                                } else {
                                    addstr(&execlist, mkstr("-original_filename=", mksuf(srcfiles.entries[var_s0_3], (s8) (u8) srcsuf), NULL));
                                }
                                addstr(&execlist, "-include=/usr/include");
                                addstr(&execlist, "-cp=i");
                                addlist(&execlist, &soptflags);
                                if (run(fopt, execlist.entries, NULL, NULL, NULL) != 0) {
                                    runerror += 1;
                                    if (((docpp != 0) || ((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72)) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                        unlink(passin);
                                    }
                                    if (((u8) Hchar != 0x4B) || (Kflag != 0)) {
                                        unlink(passout);
                                    }
                                    unlink(spF4);
                                    goto block_2269;
                                }
                                if (((docpp != 0) || ((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72) || ((u8) srcsuf == 0x46)) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                    unlink(passin);
                                }
                                unlink(spF4);
                                passin = passout;
                                if ((u8) Hchar == 0x4B) {
                                    goto block_2270;
                                }
                                goto block_1660;
                            }
block_1566:
                            if (((u8) Hchar == 0x4B) || (Kflag != 0)) {
                                mp_flag |= 6;
                            }
                            if (mp_flag & 1) {
                                if ((Oflag >= 2) && (set_loop_unroll == 0)) {
                                    addstr(&optflags, "-loopunroll");
                                    addstr(&optflags, "0");
                                }
                                if ((mp_i2flag != 0) && (w1flag != 2)) {
                                    error(2, NULL, 0, NULL, 0, "PFA does not recognize the -i2 option\n");
                                }
                                if ((mp_66flag != 0) && (w1flag != 2)) {
                                    error(2, NULL, 0, NULL, 0, "PFA does not recognize the -66 option\n");
                                }
                                if ((mp_uflag != 0) && (w1flag != 2)) {
                                    error(2, NULL, 0, NULL, 0, "PFA does not recognize the -u option\n");
                                }
                                if ((mp_backslashflag != 0) && (w1flag != 2)) {
                                    error(2, NULL, 0, NULL, 0, "PFA does not support the -backslash option\n");
                                }
                                if (mp_caseflag != 0) {
                                    error(1, NULL, 0, NULL, 0, "PFA does not support the -U option\n");
                                    exit(2);
                                }
loop_1587:
                                execlist.length = 0;
                                addstr(&execlist, "pfa");
                                spF0.unk_0 = spFC + 0x31;
                                if (mp_flag & 2) {
                                    spF8 = mksuf(srcfiles.entries[var_s0_3], 0x6C);
                                    if (spFC < mp_prepass_count) {
                                        var_v0_12 = mkstr(spF8, &spF0, NULL);
                                        goto block_1591;
                                    }
                                } else {
                                    var_v0_12 = mkstr(tempstr->unk_7C, "l", &spF0, NULL);
block_1591:
                                    spF8 = var_v0_12;
                                }
                                addstr(&execlist, mkstr("-L=", spF8, NULL));
                                if (mp_flag & 4) {
                                    passout = mksuf(srcfiles.entries[var_s0_3], 0x6D);
                                    if (spFC < mp_prepass_count) {
                                        var_v0_13 = mkstr(passout, &spF0, NULL);
                                        goto block_1596;
                                    }
                                } else {
                                    var_v0_13 = mkstr(tempstr->unk_7C, "m", &spF0, NULL);
block_1596:
                                    passout = var_v0_13;
                                }
                                addstr(&execlist, mkstr("-F=", passout, NULL));
                                addstr(&execlist, mkstr("-I=", passin, NULL));
                                if (mp_col120flag != 0) {
                                    addstr(&execlist, "-scan=120");
                                }
                                if (mp_extendflag != 0) {
                                    addstr(&execlist, "-scan=132");
                                }
                                if (automaticflag == 0) {
                                    addstr(&execlist, "-save=all");
                                }
                                if (mp_onetripflag != 0) {
                                    addstr(&execlist, "-onetrip");
                                }
                                if (mp_dlinesflag != 0) {
                                    addstr(&execlist, "-dlines");
                                }
                                if (w1flag == 2) {
                                    addstr(&execlist, "-suppress=w");
                                }
                                if (vflag != 0) {
                                    addstr(&execlist, "-lo=lno");
                                } else {
                                    addstr(&execlist, "-lo=lo");
                                }
                                if (mp_flag & 2) {
                                    addstr(&execlist, mkstr("-analysis=", mksuf(srcfiles.entries[var_s0_3], 5), NULL));
                                } else if (irix4 == 0) {
                                    addstr(&execlist, "-noanalysis");
                                }
                                if (irix4 != 0) {
                                    addstr(&execlist, mkstr("-customer=", mksuf(srcfiles.entries[var_s0_3], (s8) (u8) srcsuf), NULL));
                                } else {
                                    addstr(&execlist, mkstr("-original_filename=", mksuf(srcfiles.entries[var_s0_3], (s8) (u8) srcsuf), NULL));
                                }
                                addstr(&execlist, "-include=/usr/include");
                                addstr(&execlist, "-cp=i");
                                if (spFC >= mp_prepass_count) {
                                    addlist(&execlist, &pfaflags);
                                } else {
                                    addstr(&execlist, "-p=1");
                                    addstr(&execlist, "-ur=1");
                                    temp_t6_2 = sp100 + 1;
                                    sp100 = temp_t6_2;
                                    if (strncmp(argv[temp_t6_2], "-pfaprepass,", 0xCU) != 0) {
                                        do {
                                            temp_t7 = sp100 + 1;
                                            sp100 = temp_t7;
                                            if (argv[temp_t7] == NULL) {
                                                error(1, NULL, 0, NULL, 0, "Can't parse -pfaprepass option\n");
                                                exit(2);
                                            }
                                        } while (strncmp(argv[sp100], "-pfaprepass,", 0xCU) != 0);
                                    }
                                    spE8 = &argv[sp100][strlen("-pfaprepass")];
loop_1627:
                                    spEC = spE8 + 1;
                                    if (spE8->unk_1 == 0) {
                                        error(1, NULL, 0, NULL, 0, "Bad pfaprepass syntax: no arg after comma\n");
                                        exit(2);
                                    }
                                    spE8 = spEC + 1;
                                    temp_t8 = spEC->unk_1;
                                    if ((temp_t8 != 0x2C) && (temp_t8 != 0)) {
loop_1631:
                                        spE8 += 1;
                                        temp_t5 = (u8) spE8->unk_0;
                                        if (temp_t5 != 0x2C) {
                                            if (temp_t5 != 0) {
                                                goto loop_1631;
                                            }
                                        }
                                    }
                                    spE7 = (u8) spE8->unk_0;
                                    spE8->unk_0 = 0;
                                    addstr(&execlist, mkstr(spEC, NULL));
                                    if (spE7 != 0) {
                                        spE8->unk_0 = (s8) spE7;
                                        goto loop_1627;
                                    }
                                }
                                if (run(pfa, execlist.entries, NULL, NULL, NULL) != 0) {
                                    runerror += 1;
                                    if (((docpp != 0) || ((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72)) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                        unlink(passin);
                                    }
                                    if (!(mp_flag & 4)) {
                                        unlink(passout);
                                    }
                                    goto block_2270;
                                }
                                if (!(mp_flag & 2)) {
                                    unlink(spF8);
                                }
                                if (spFC == 0) {
                                    if (((docpp != 0) || ((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72) || ((u8) srcsuf == 0x46)) && ((u8) srcsuf != 0x69) && (Kflag == 0)) {
                                        unlink(passin);
                                    }
                                } else if (!(mp_flag & 4)) {
                                    unlink(passin);
                                }
                                temp_t7_2 = spFC + 1;
                                spFC = temp_t7_2;
                                if (mp_prepass_count >= temp_t7_2) {
                                    passin = passout;
                                    goto loop_1587;
                                }
                                passin = passout;
                                if ((u8) Hchar != 0x4B) {
                                    goto block_1660;
                                }
                                goto block_2270;
                            }
block_1660:
                            execlist.length = 0;
                            addstr(&execlist, "fcom");
                            if (alignarg != NULL) {
                                addstr(&execlist, alignarg);
                            }
                            if (align_common > 0) {
                                addstr(&execlist, "-align_common");
                            }
                            if (mp_flag & 0x10000) {
                                addstr(&execlist, "-MP");
                            }
                            if (showdirt_flag != 0) {
                                addstr(&execlist, "-showdirt");
                            }
                            if (vflag != 0) {
                                addstr(&execlist, "-v");
                            }
                            addlist(&execlist, &fcomflags);
                            if (nocode == 0) {
                                addstr(&execlist, mkstr("-XS", symtab, NULL));
                            }
                            var_s2 = NULL;
                            if (nocode != 0) {
                                addstr(&execlist, "-nocode");
                                passout = NULL;
                            } else if ((u8) Hchar == 0x66) {
                                passout = mksuf(srcfiles.entries[var_s0_3], 0x42);
                                if (ucodeflag != 0) {
                                    addstr(&execlist, "-Xu");
                                    var_s2 = mksuf(srcfiles.entries[var_s0_3], 0x55);
                                }
                            } else if (Kflag != 0) {
                                passout = mksuf(srcfiles.entries[var_s0_3], 0x42);
                                if (regular_not_writeable(passout) == 1) {
                                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                    exit(2);
                                }
                            } else {
                                passout = tempstr->unk_C;
                            }
                            if (passout != NULL) {
                                addstr(&execlist, "-t");
                                addstr(&execlist, passout);
                            }
                            if ((docpp != 0) && ((u8) srcsuf != 0x69) && ((u8) srcsuf != 0x6D)) {
                                var_s1_4 = passin;
                            } else {
                                addstr(&execlist, passin);
                                var_s1_4 = NULL;
                            }
                            if (run(fcom, execlist.entries, var_s1_4, var_s2, errout) != 0) {
                                if (editflag != 0) {
                                    if (times_edited < edit_cnt_max) {
                                        times_edited += 1;
                                        if (edit_src(editor, srcfiles.entries[var_s0_3], 3) != 0) {
                                            show_err(errout);
                                            exit(1);
                                        }
                                        if (((docpp != 0) || ((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72)) && ((u8) srcsuf != 0x69) && ((u8) srcsuf != 0x66)) {
                                            unlink(passin);
                                        }
                                        unlink(passout);
                                        unlink(errout);
                                        unlink(symtab);
                                        passin = srcfiles.entries[var_s0_3];
                                        goto loop_484;
                                    }
                                    show_err(errout);
                                    goto block_1701;
                                }
block_1701:
                                runerror += 1;
                                if (((docpp != 0) || (mp_flag & 1) || ((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72)) && ((u8) srcsuf != 0x69) && ((u8) srcsuf != 0x6D) && (Kflag == 0) && !(mp_flag & 4)) {
                                    unlink(passin);
                                }
                                if (Kflag == 0) {
                                    unlink(passout);
                                    unlink(symtab);
                                }
                                goto block_2270;
                            }
                            if (editflag != 0) {
                                unlink(errout);
                            }
                            if (nocode != 0) {
                                if (docpp != 0) {
                                    unlink(passin);
                                }
                            } else {
                                if (((docpp != 0) || (mp_flag & 1) || (run_sopt != 0) || ((u8) srcsuf == 0x65) || ((u8) srcsuf == 0x72) || ((u8) srcsuf == 0x46)) && ((u8) srcsuf != 0x69) && ((u8) srcsuf != 0x6D) && (Kflag == 0) && !(mp_flag & 4)) {
                                    unlink(passin);
                                }
                                passin = passout;
                                if ((u8) Hchar != 0x66) {
                                    goto block_1729;
                                }
                            }
                            goto block_2270;
                        }
                        break;
                    }
                } else {
                    goto block_2270;
                }
            } else {
block_1042:
                if (gflag >= 2) {
                    func_00431D00(srcfiles.entries[var_s0_3]);
                }
                if ((compiler == 1) && (c_compiler_choice != 0)) {
                    if ((docpp == 0) || (oldcppflag != 0) || (run_sopt != 0) || ((u8) srcsuf == 0x69) || (acpp != 0)) {
                        execlist.length = 0;
                        addstr(&execlist, cfe);
                    }
                    if (vflag != 0) {
                        addstr(&execlist, "-v");
                    }
                    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                        if (anachronisms != 0) {
                            addstr(&execlist, "-O");
                        }
                        if (cfront_compatible != 0) {
                            addstr(&execlist, "-b");
                        }
                    }
                    if (nocode != 0) {
                        addstr(&execlist, "-n");
                    }
                    if (Fflag == 0) {
                        addstr(&execlist, "-Zz");
                        addstr(&execlist, "-ZO");
                        addstr(&execlist, mkstr("-ZS", symtab, NULL));
                    }
                    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                        if (Oflag >= 3) {
                            addstr(&execlist, "-Qz");
                        }
                        if (non_shared != 0) {
                            addstr(&execlist, "-Qn");
                        }
                    }
                    if (signedcharflag != 0) {
                        addstr(&execlist, "-s");
                    } else {
                        addstr(&execlist, "-u");
                    }
                    if (fullwarn != 0) {
                        addstr(&execlist, "-Yw");
                    }
                    if (disable_inlines != 0) {
                        addstr(&execlist, "-YJ");
                    }
                    if (c_compiler_choice != 2) {
                        if (c_compiler_choice == 3) {
                            addstr(&execlist, "-YD");
                        } else if (edison_type == (s8* )3) {
                            addstr(&execlist, "-K");
                        } else {
                            addstr(&execlist, "-m");
                        }
                    }
                    if ((u8) srcsuf == 0x69) {
                        addstr(&execlist, "-Yp");
                    }
                    if (smart_build != 0) {
                        addstr(&execlist, mkstr("-YR", sbrepos, NULL));
                    }
                    if (srcfiles.length == 1) {
                        if (outfile != NULL) {
                            sp118 = outfile;
                        } else if (cflag == 0) {
                            sp118 = "a.out";
                        } else {
                            var_v0_14 = mksuf(srcfiles.entries[var_s0_3], 0x6F);
                            goto block_1097;
                        }
                    } else {
                        var_v0_14 = mksuf(srcfiles.entries[var_s0_3], 0x6F);
block_1097:
                        sp118 = var_v0_14;
                    }
                    addstr(&execlist, mkstr("-YN", sp118, NULL));
                    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                        switch (default_template_instantiation_mode) { /* switch 14; irregular */
                        case 0:                     /* switch 14 */
                            break;
                        case 1:                     /* switch 14 */
                            addstr(&execlist, "-tused");
                            break;
                        case 2:                     /* switch 14 */
                            addstr(&execlist, "-tall");
                            break;
                        }
                        if (no_prelink != 0) {
                            addstr(&execlist, "-T");
                        } else {
                            if ((outfile != NULL) && (cflag != 0) && (srcfiles.length == 1)) {
                                sp10C = outfile;
                            } else {
                                sp10C = mksuf(srcfiles.entries[var_s0_3], 0x6F);
                            }
                            sp108 = make_ii_file_name(sp10C);
                            addstr(&execlist, mkstr("-YO", sp108, NULL));
                            free(sp108);
                        }
                        if (auto_template_include == 0) {
                            addstr(&execlist, "-B");
                        }
                    }
                    if (gflag >= 2) {
                        addstr(&execlist, mkstr("-Zc", tempstr->unk_84, NULL));
                    }
                    addstr(&execlist, mkstr("-YG", Gnum, NULL));
                    addlist(&execlist, &edisonflags);
                    if (dollar_sign != 0) {
                        addstr(&execlist, "-$");
                    }
                    if (Fflag != 0) {
                        addstr(&execlist, mkstr("-", NULL));
                    } else {
                        addstr(&execlist, passin);
                    }
                }
                if (compchoice == 3) {
                    if (cmp_flag & 0x10000) {
                        if (((u8) Hchar == 0x4D) || (Kflag != 0) || (cmp_flag & 4)) {
                            var_v0_15 = mksuf(srcfiles.entries[var_s0_3], 0x50);
                        } else {
                            var_v0_15 = mkstr(tempstr->unk_7C, "P", NULL);
                        }
                        passout = var_v0_15;
                        execlist.length = 0;
                        addstr(&execlist, mpc);
                        addstr(&execlist, passin);
                        addstr(&execlist, mkstr("-K", passout, NULL));
                        if ((ansichoice == 1) || (ansichoice == 2)) {
                            addstr(&execlist, "-ansi");
                        } else if (ansichoice == 0) {
                            addstr(&execlist, "-cckr");
                        } else {
                            addstr(&execlist, "-xansi");
                        }
                        addlist(&execlist, &mpcflags);
                        retcode = run(mpc, execlist.entries, NULL, NULL, errout);
                        if (Kflag == 0) {
                            unlink(passin);
                        }
                        if (retcode != 0) {
                            runerror += 1;
                            if (((u8) Hchar != 0x4D) && (Kflag == 0) && !(cmp_flag & 4)) {
                                unlink(passout);
                            }
                            goto block_2270;
                        }
                        if ((u8) Hchar != 0x4D) {
                            passin = passout;
                            goto block_1148;
                        }
                        goto block_2270;
                    }
block_1148:
                    if (((docpp == 0) || (oldcppflag != 0) || (run_sopt != 0) || ((u8) srcsuf == 0x69) || (acpp != 0) || (cmp_flag & 0x10000)) && (c_compiler_choice == 0)) {
                        execlist.length = 0;
                        addstr(&execlist, cfe);
                        addstr(&execlist, passin);
                    }
                    if ((u8) Hchar == 0x66) {
                        if (ucodeflag != 0) {
                            passout = tempstr->unk_C;
                        } else {
                            passout = mksuf(srcfiles.entries[var_s0_3], 0x42);
                        }
                    } else if (((Fflag != 0) && (plusIflag == 0)) || (nocode != 0)) {
                        passout = NULL;
                    } else if (plusIflag != 0) {
                        passout = mksuf(srcfiles.entries[var_s0_3], 7);
                    } else if (Kflag != 0) {
                        passout = mksuf(srcfiles.entries[var_s0_3], 0x42);
                    } else {
                        passout = tempstr->unk_C;
                    }
                    if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                        exit(2);
                    }
                    if (((docpp == 0) || ((u8) srcsuf == 0x69) || (acpp != 0) || (oldcppflag != 0)) && (run_sopt == 0)) {
                        if ((default_nocpp == 0) && (((u8) srcsuf == 0x63) || ((u8) srcsuf == 0x73) || ((u8) srcsuf == 0x70))) {
                            addstr(&execlist, "-nocpp");
                        }
                        if ((u8) srcsuf == var_s0_3) {
                            addstr(&execlist, "-nocpp");
                        }
                    }
                    if (c_compiler_choice == 0) {
                        if (vflag != 0) {
                            addstr(&execlist, "-Xv");
                        }
                        if (compiler == 1) {
                            if ((run_sopt == 0) && !(cmp_flag & 1)) {
                                addstr(&execlist, "-D_CFE");
                                addstr(&execlist, "-Amachine(mips)");
                                addstr(&execlist, "-Asystem(unix)");
                                addlist(&execlist, &accomflags);
                            }
                            addlist(&execlist, &cfeflags);
                            addstr(&execlist, "-G");
                            addstr(&execlist, Gnum);
                        }
                        if ((ansichoice == 1) || (ansichoice == 2)) {
                            addstr(&execlist, "-std1");
                        } else if (ansichoice == 3) {
                            addstr(&execlist, "-std");
                        } else if (ansichoice == 0) {
                            addstr(&execlist, "-std0");
                        }
                        if (prototype_checking_on != 0) {
                            addstr(&execlist, "-Xprototypes");
                        }
                        addstr(&execlist, mkstr("-XS", symtab, NULL));
                        addlist(&execlist, &ccomflags);
                        if (gflag >= 2) {
                            addstr(&execlist, mkstr("-Xcmd:", tempstr->unk_84, NULL));
                        }
                    }
                    if ((run_sopt != 0) || (cmp_flag & 1)) {
                        unlink(tempstr->unk_8);
                    }
                    if (run_sopt != 0) {
                        addlist(&execlist, &undefineflags);
                    }
                    if (Fflag != 0) {
                        var_s3_7 = passin;
                    } else {
                        var_s3_7 = NULL;
                    }
                    retcode = run(cfe, execlist.entries, var_s3_7, passout, errout);
                    if ((smart_build != 0) && (retcode == 0xFA)) {
                        retcode = 0;
                        nocompileneeded = 1;
                        if ((outfile != NULL) && (cflag != 0) && (srcfiles.length == 1)) {
                            sp104 = outfile;
                        } else if (((u8) srcsuf == 0x3F) && ((u8) Hchar != 0x62) && (Kflag == 0)) {
                            sp104 = tempstr->unk_30;
                            tmp_uldobj = tempstr->unk_30;
                        } else {
                            sp104 = mksuf(srcfiles.entries[var_s0_3], 0x6F);
                        }
                        if (touch(sp118) < 0) {
                            runerror += 1;
                        }
                        if ((srcfiles.length != 1) || (cflag != 0)) {
                            goto block_1227;
                        }
                        goto block_2588;
                    }
block_1227:
                    if (Fflag == 0) {
                        if (retcode == 0xFF) {
                            c_inline = 1;
                            addstr(&umergeflags, "-c_inline");
                            goto block_1238;
                        }
                        if (retcode != 0) {
                            runerror += 1;
                            if ((oldcflag == 1) && (docpp != 0) && ((u8) srcsuf != 0x69) && (c_compiler_choice == 0)) {
                                unlink(passin);
                            }
                            if (Kflag == 0) {
                                unlink(passout);
                                unlink(symtab);
                            }
                        } else {
block_1238:
                            if (((run_sopt != 0) && (Kflag == 0)) || (acpp != 0) || (oldcppflag != 0) || (cmp_flag & 0x10000)) {
                                unlink(passin);
                            }
                            if ((NoMoreOptions != 0) && ((u8) *passout == 0x2D)) {
                                passout = func_00433534(passout);
                            }
                            passin = passout;
                            if (((u8) Hchar == 0x66) && (ucodeflag != 0)) {
                                execlist.length = 0;
                                addstr(&execlist, "btou");
                                addstr(&execlist, passin);
                                passout = mksuf(srcfiles.entries[var_s0_3], 0x55);
                                if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                    exit(2);
                                }
                                addstr(&execlist, passout);
                                if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                                    runerror += 1;
                                    if (Kflag == 0) {
                                        unlink(passin);
                                        unlink(passout);
                                    }
                                    if (tmpst != 0) {
                                        unlink(symtab);
                                    }
                                } else if (Kflag == 0) {
                                    unlink(passin);
                                }
                            } else {
                                passin = passout;
                                if ((u8) Hchar != 0x66) {
                                    if ((compiler == 1) && (c_compiler_choice != 0) && ((Eflag != 0) || (nocode != 0) || (nocompileneeded != 0))) {
                                        unlink(passout);
                                    } else {
                                        goto block_1729;
                                    }
                                }
                            }
                        }
                    }
                    goto block_2270;
                }
                execlist.length = 0;
                if (ansichoice != 0) {
                    var_s3_8 = "accom";
                } else {
                    var_s3_8 = "ccom";
                }
                addstr(&execlist, var_s3_8);
                if (vflag != 0) {
                    addstr(&execlist, "-Xv");
                }
                if (cmp_flag & 0x10000) {
                    addstr(&execlist, "-XMP");
                }
                addlist(&execlist, &ccomflags);
                if (dollar_sign != 0) {
                    addstr(&execlist, "-Xdollar");
                }
                if (use_real_fp != 0) {
                    addstr(&execlist, "-Xreal_fp");
                }
                if ((prototype_checking_on != 0) || (ansichoice != 0)) {
                    addstr(&execlist, "-Xprototypes");
                }
                if (ansichoice != 0) {
                    if (ansichoice == 3) {
                        addstr(&execlist, "-Xxansi");
                    } else {
                        addstr(&execlist, "-Xansi");
                    }
                    addlist(&execlist, &accomflags);
                }
                if ((u8) Hchar == 0x66) {
                    if (ucodeflag != 0) {
                        passout = tempstr->unk_C;
                    } else {
                        passout = mksuf(srcfiles.entries[var_s0_3], 0x42);
                    }
                } else if (Kflag != 0) {
                    passout = mksuf(srcfiles.entries[var_s0_3], 0x42);
                } else {
                    passout = tempstr->unk_C;
                }
                if (regular_not_writeable(passout) == 1) {
                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                addstr(&execlist, mkstr("-XS", symtab, NULL));
                if ((Kflag == 0) && (docpp != 0) && ((u8) srcsuf != 0x69)) {
                    var_s1_5 = passin;
                } else {
                    addstr(&execlist, passin);
                    var_s1_5 = NULL;
                }
                retcode = run(ccom, execlist.entries, var_s1_5, passout, errout);
                if (retcode == 0xFF) {
                    c_inline = 1;
                    addstr(&umergeflags, "-c_inline");
                    goto block_1317;
                }
                if (retcode != 0) {
                    if (editflag != 0) {
                        if (times_edited < edit_cnt_max) {
                            times_edited += 1;
                            if (edit_src(editor, srcfiles.entries[var_s0_3], 1) != 0) {
                                show_err(errout);
                                exit(1);
                            }
                            if ((docpp != 0) && ((u8) srcsuf != 0x69)) {
                                unlink(passin);
                            }
                            unlink(passout);
                            unlink(errout);
                            unlink(symtab);
                            passin = srcfiles.entries[var_s0_3];
                            goto loop_484;
                        }
                        show_err(errout);
                        goto block_1311;
                    }
block_1311:
                    runerror += 1;
                    if ((Kflag == 0) && (docpp != 0) && ((u8) srcsuf != 0x69)) {
                        unlink(passin);
                    }
                    if (Kflag == 0) {
                        unlink(passout);
                        unlink(symtab);
                    }
                    goto block_2270;
                }
block_1317:
                if (editflag != 0) {
                    unlink(errout);
                }
                if ((Kflag == 0) && (docpp != 0) && ((u8) srcsuf != 0x69)) {
                    unlink(passin);
                }
                passin = passout;
                if (((u8) Hchar == 0x66) && (ucodeflag != 0)) {
                    execlist.length = 0;
                    addstr(&execlist, "btou");
                    addstr(&execlist, passin);
                    passout = mksuf(srcfiles.entries[var_s0_3], 0x55);
                    if (regular_not_writeable(passout) == 1) {
                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                        exit(2);
                    }
                    addstr(&execlist, passout);
                    if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                        runerror += 1;
                        if (Kflag == 0) {
                            unlink(passin);
                            unlink(passout);
                        }
                        if (tmpst != 0) {
                            unlink(symtab);
                        }
                    } else if (Kflag == 0) {
                        unlink(passin);
                    }
                } else if ((u8) Hchar != 0x66) {
                    if ((compiler == 1) && (c_compiler_choice != 0)) {
                        if ((Eflag == 0) && (nocode == 0)) {
                            if (nocompileneeded != 0) {

                            } else {
                                goto block_1729;
                            }
                        }
                    } else {
                    case 0x42:                      /* switch 19 */
block_1729:
                        if ((Oflag != 3) && (Oflag != 4) && (jflag == 0)) {
                            if (c_inline == 0) {
                                goto block_1933;
                            }
                        case 0x53:                  /* switch 19 */
block_1913:
                            if ((Oflag == 3) || (Oflag == 4) || (c_inline != 0)) {
                                execlist.length = 0;
                                addstr(&execlist, "umerge");
                                if (vflag != 0) {
                                    addstr(&execlist, "-v");
                                }
                                addlist(&execlist, &umergeflags);
                                addstr(&execlist, passin);
                                addstr(&execlist, "-o");
                                if (((u8) Hchar == 0x6D) || (Kflag != 0)) {
                                    passout = mksuf(srcfiles.entries[var_s0_3], 0x4D);
                                    if (regular_not_writeable(passout) == 1) {
                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                        exit(2);
                                    }
                                } else {
                                    passout = tempstr->unk_18;
                                }
                                addstr(&execlist, passout);
                                addstr(&execlist, "-t");
                                addstr(&execlist, symtab);
                                if (run(umerge, execlist.entries, NULL, NULL, NULL) != 0) {
                                    runerror += 1;
                                    if (Kflag == 0) {
                                        if ((u8) srcsuf != 0x53) {
                                            unlink(passin);
                                        }
                                        unlink(passout);
                                        if (tmpst != 0) {
                                            unlink(symtab);
                                        }
                                    }
                                } else {
                                    if ((Kflag == 0) && ((u8) srcsuf != 0x53)) {
                                        unlink(passin);
                                    }
                                    passin = passout;
                                    if ((u8) Hchar != 0x6D) {
                                        goto block_1933;
                                    }
                                }
                            } else {
                                goto block_1933;
                            }
                        } else {
                            execlist.length = 0;
                            addstr(&execlist, "ujoin");
                            if (vflag != 0) {
                                addstr(&execlist, "-v");
                            }
                            addlist(&execlist, &ujoinflags);
                            if ((outfile != NULL) && (jflag != 0) && (srcfiles.length == 1)) {
                                passout = outfile;
                            } else {
                                passout = mksuf(srcfiles.entries[var_s0_3], 0x75);
                            }
                            addstr(&execlist, "-o");
                            addstr(&execlist, passout);
                            addstr(&execlist, passin);
                            addstr(&execlist, symtab);
                            if (run(ujoin, execlist.entries, NULL, NULL, NULL) != 0) {
                                runerror += 1;
                                if (Kflag == 0) {
                                    if ((u8) srcsuf != 0x42) {
                                        unlink(passin);
                                    }
                                    unlink(passout);
                                    if (tmpst != 0) {
                                        unlink(symtab);
                                    }
                                }
                            } else if ((cflag == 0) || (Oflag == 3) || (Oflag == 4)) {
                                if (Kflag == 0) {
                                    if ((u8) srcsuf != 0x42) {
                                        unlink(passin);
                                    }
                                    if (tmpst != 0) {
                                        unlink(symtab);
                                    }
                                }
                                passin = passout;
                            } else {
                            case 0x4D:              /* switch 19 */
block_1933:
                                if (unrollflag != 0) {
                                    execlist.length = 0;
                                    addstr(&execlist, "uloop");
                                    if (vflag != 0) {
                                        addstr(&execlist, "-v");
                                    }
                                    addlist(&execlist, &uloopflags);
                                    addstr(&execlist, passin);
                                    addstr(&execlist, "-o");
                                    if (((u8) Hchar == 0x76) || (Kflag != 0)) {
                                        if (((u8) Hchar == 0x76) || (Kflag != 0)) {
                                            passout = mksuf(srcfiles.entries[var_s0_3], 0x56);
                                            if (regular_not_writeable(passout) == 1) {
                                                error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                exit(2);
                                            }
                                        } else {
                                            passout = tempstr->unk_5C;
                                        }
                                    }
                                    addstr(&execlist, passout);
                                    addstr(&execlist, "-t");
                                    addstr(&execlist, symtab);
                                    if (run(uloop, execlist.entries, NULL, NULL, NULL) != 0) {
                                        runerror += 1;
                                        if (Kflag == 0) {
                                            if ((u8) srcsuf != 0x4D) {
                                                unlink(passin);
                                            }
                                            unlink(passout);
                                            if (tmpst != 0) {
                                                unlink(symtab);
                                            }
                                        }
                                    } else {
                                        if ((Kflag == 0) && ((u8) srcsuf != 0x4D)) {
                                            unlink(passin);
                                        }
                                        passin = passout;
                                        if ((u8) Hchar != 0x76) {
                                            goto block_1953;
                                        }
                                    }
                                } else {
block_1953:
                                    if ((uopt0flag == 1) && (compiler == 3) && (Oflag >= 2)) {
                                        execlist.length = 0;
                                        addstr(&execlist, "uopt0");
                                        if (vflag != 0) {
                                            addstr(&execlist, "-v");
                                        }
                                        addstr(&execlist, "-G");
                                        addstr(&execlist, Gnum);
                                        addlist(&execlist, &uopt0flags);
                                        addstr(&execlist, passin);
                                        if (((u8) Hchar == 0x71) || (Kflag != 0)) {
                                            passout = mksuf(srcfiles.entries[var_s0_3], 0x51);
                                            if (regular_not_writeable(passout) == 1) {
                                                error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                exit(2);
                                            }
                                        } else {
                                            passout = tempstr->unk_70;
                                        }
                                        addstr(&execlist, passout);
                                        addstr(&execlist, "-t");
                                        addstr(&execlist, symtab);
                                        uopt0str = tempstr->unk_74;
                                        addstr(&execlist, tempstr->unk_74);
                                        if (run(uopt0, execlist.entries, NULL, NULL, NULL) != 0) {
                                            runerror += 1;
                                            if (Kflag == 0) {
                                                if (((u8) srcsuf != 0x4D) && ((u8) srcsuf != 0x42) && ((u8) srcsuf != 0x53) && ((u8) srcsuf != 0x51)) {
                                                    unlink(passin);
                                                }
                                                unlink(passout);
                                                if (tmpst != 0) {
                                                    unlink(symtab);
                                                }
                                            }
                                            unlink(uopt0str);
                                        } else {
                                            if ((Kflag == 0) && ((u8) srcsuf != 0x4D) && ((u8) srcsuf != 0x42) && ((u8) srcsuf != 0x53) && ((u8) srcsuf != 0x51)) {
                                                unlink(passin);
                                            }
                                            unlink(uopt0str);
                                            passin = passout;
                                            if ((u8) Hchar != 0x71) {
                                                goto block_1980;
                                            }
                                        }
                                    } else {
block_1980:
                                        if ((ddoptflag == 1) && (compiler == 3) && (Oflag >= 2)) {
                                            execlist.length = 0;
                                            addstr(&execlist, "ddopt");
                                            if (vflag != 0) {
                                                addstr(&execlist, "-v");
                                            }
                                            addstr(&execlist, "-G");
                                            addstr(&execlist, Gnum);
                                            addlist(&execlist, &ddoptflags);
                                            addstr(&execlist, passin);
                                            if ((((u8) Hchar == 0x64) && (ucodeflag == 0)) || (Kflag != 0)) {
                                                passout = mksuf(srcfiles.entries[var_s0_3], 0x44);
                                                if (regular_not_writeable(passout) == 1) {
                                                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                    exit(2);
                                                }
                                            } else {
                                                passout = tempstr->unk_6C;
                                            }
                                            if (ddoptinfo != 0) {
                                                addstr(&execlist, "-e");
                                                if ((((u8) Hchar == 0x64) && (ucodeflag == 0)) || (Kflag != 0)) {
                                                    addstr(&execlist, mksuf(srcfiles.entries[var_s0_3], 0x45));
                                                } else {
                                                    addstr(&execlist, tempstr->unk_68);
                                                }
                                            }
                                            addstr(&execlist, passout);
                                            if (run(ddopt, execlist.entries, NULL, NULL, NULL) != 0) {
                                                runerror += 1;
                                                if (Kflag == 0) {
                                                    if (((u8) srcsuf != 0x42) && ((u8) srcsuf != 0x53) && ((u8) srcsuf != 0x4D) && ((u8) srcsuf != 0x51)) {
                                                        unlink(passin);
                                                    }
                                                    unlink(passout);
                                                    if (tmpst != 0) {
                                                        unlink(symtab);
                                                    }
                                                }
                                                unlink(ddoptstr);
                                            } else {
                                                if ((Kflag == 0) && ((u8) srcsuf != 0x42) && ((u8) srcsuf != 0x53) && ((u8) srcsuf != 0x4D) && ((u8) srcsuf != 0x51)) {
                                                    unlink(passin);
                                                }
                                                unlink(ddoptstr);
                                                passin = passout;
                                                if ((u8) Hchar != 0x64) {
                                                    goto block_2015;
                                                }
                                            }
                                        } else {
                                        case 0x44:  /* switch 19 */
                                        case 0x51:  /* switch 19 */
                                        case 0x56:  /* switch 19 */
block_2015:
                                            if ((Oflag == 2) || (Oflag == 3) || (Oflag == 4)) {
                                                execlist.length = 0;
                                                addstr(&execlist, "uopt");
                                                if (vflag != 0) {
                                                    addstr(&execlist, "-v");
                                                }
                                                addstr(&execlist, "-G");
                                                addstr(&execlist, Gnum);
                                                if ((mp_flag & 0x10000) && (((u8) srcsuf == 0x66) || ((u8) srcsuf == 0x46))) {
                                                    addstr(&execlist, "-noPalias");
                                                }
                                                if (irix4 == 0) {
                                                    if (kpicopt_flag != 0) {
                                                        addstr(&execlist, "-kpicopt");
                                                    }
                                                    if (nokpicopt_flag != 0) {
                                                        addstr(&execlist, "-nokpicopt");
                                                    }
                                                }
                                                addlist(&execlist, &optflags);
                                                addstr(&execlist, passin);
                                                if ((((u8) Hchar == 0x6F) && (ucodeflag == 0)) || (Kflag != 0)) {
                                                    passout = mksuf(srcfiles.entries[var_s0_3], 0x4F);
                                                    if (regular_not_writeable(passout) == 1) {
                                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                        exit(2);
                                                    }
                                                    if (NoMoreOptions != 0) {
                                                        *passout = 0x2D;
                                                        if ((u8) *passout != 0) {
                                                            passout = func_00433534(passout);
                                                        }
                                                    }
                                                } else {
                                                    passout = tempstr->unk_1C;
                                                }
                                                addstr(&execlist, passout);
                                                addstr(&execlist, "-t");
                                                addstr(&execlist, symtab);
                                                optstr = tempstr->unk_20;
                                                addstr(&execlist, tempstr->unk_20);
                                                if (run(opt, execlist.entries, NULL, NULL, NULL) != 0) {
                                                    runerror += 1;
                                                    if (Kflag == 0) {
                                                        if (((u8) srcsuf != 0x42) && ((u8) srcsuf != 0x53) && ((u8) srcsuf != 0x51) && ((u8) srcsuf != 0x44) && ((u8) srcsuf != 0x4D) && ((u8) srcsuf != 0x56)) {
                                                            unlink(passin);
                                                        }
                                                        unlink(passout);
                                                        if (tmpst != 0) {
                                                            unlink(symtab);
                                                        }
                                                    }
                                                    unlink(optstr);
                                                } else {
                                                    if ((Kflag == 0) && ((u8) srcsuf != 0x42) && ((u8) srcsuf != 0x53) && ((u8) srcsuf != 0x51) && ((u8) srcsuf != 0x44) && ((u8) srcsuf != 0x4D) && ((u8) srcsuf != 0x56)) {
                                                        unlink(passin);
                                                    }
                                                    unlink(optstr);
                                                    passin = passout;
                                                    if (((u8) Hchar == 0x6F) && (ucodeflag != 0)) {
                                                        execlist.length = 0;
                                                        addstr(&execlist, "btou");
                                                        addstr(&execlist, passin);
                                                        passout = mksuf(srcfiles.entries[var_s0_3], 0x55);
                                                        addstr(&execlist, passout);
                                                        if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                                                            runerror += 1;
                                                            if (Kflag == 0) {
                                                                unlink(passin);
                                                                unlink(passout);
                                                                if (tmpst != 0) {
                                                                    unlink(symtab);
                                                                }
                                                            }
                                                        } else if (Kflag == 0) {
                                                            unlink(passin);
                                                            if (tmpst != 0) {
                                                                unlink(symtab);
                                                            }
                                                        }
                                                    } else if ((u8) Hchar != 0x6F) {
                                                        goto block_2068;
                                                    }
                                                }
                                            } else {
                                            case 0x4F: /* switch 19 */
block_2068:
                                                execlist.length = 0;
                                                addstr(&execlist, "ugen");
                                                if (vflag != 0) {
                                                    addstr(&execlist, "-v");
                                                }
                                                addstr(&execlist, "-G");
                                                addstr(&execlist, Gnum);
                                                if ((kpic_flag != 0) && (coff_spec == 0) && (irix4 == 0)) {
                                                    if (Oflag >= 3) {
                                                        addstr(&execlist, "-pic1");
                                                    } else {
                                                        addstr(&execlist, "-pic2");
                                                    }
                                                }
                                                addlist(&execlist, &genflags);
                                                addstr(&execlist, passin);
                                                if (Sflag != 0) {
                                                    addstr(&execlist, "-o");
                                                    if (Kflag != 0) {
                                                        addstr(&execlist, mksuf(srcfiles.entries[var_s0_3], 0x47));
                                                    } else {
                                                        binasm = tempstr->unk_24;
                                                        addstr(&execlist, tempstr->unk_24);
                                                    }
                                                    addstr(&execlist, "-l");
                                                    passout = mksuf(srcfiles.entries[var_s0_3], 0x73);
                                                    if (regular_not_writeable(passout) == 1) {
                                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                        exit(2);
                                                    }
                                                    addstr(&execlist, passout);
                                                } else if ((u8) Hchar == 0x63) {
                                                    addstr(&execlist, "-o");
                                                    passout = mksuf(srcfiles.entries[var_s0_3], 0x47);
                                                    if (regular_not_writeable(passout) == 1) {
                                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                        exit(2);
                                                    }
                                                    addstr(&execlist, passout);
                                                } else if (Kflag != 0) {
                                                    addstr(&execlist, "-o");
                                                    passout = mksuf(srcfiles.entries[var_s0_3], 0x47);
                                                    if (regular_not_writeable(passout) == 1) {
                                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                        exit(2);
                                                    }
                                                    addstr(&execlist, passout);
                                                    if (regular_not_writeable(mksuf(srcfiles.entries[var_s0_3], 0x73)) == 1) {
                                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", mksuf(srcfiles.entries[var_s0_3], 0x73));
                                                        exit(2);
                                                    }
                                                    addstr(&execlist, "-l");
                                                    addstr(&execlist, mksuf(srcfiles.entries[var_s0_3], 0x73));
                                                } else {
                                                    addstr(&execlist, "-o");
                                                    passout = tempstr->unk_28;
                                                    if (regular_not_writeable(tempstr->unk_28) == 1) {
                                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                        exit(2);
                                                    }
                                                    addstr(&execlist, passout);
                                                }
                                                addstr(&execlist, "-t");
                                                addstr(&execlist, symtab);
                                                addstr(&execlist, "-temp");
                                                gentmp = tempstr->unk_3C;
                                                addstr(&execlist, tempstr->unk_3C);
                                                if (run(gen, execlist.entries, NULL, NULL, NULL) != 0) {
                                                    runerror += 1;
                                                    if (Kflag == 0) {
                                                        if (((u8) srcsuf != 0x42) && ((u8) srcsuf != 0x4F) && ((u8) srcsuf != 0x51) && ((u8) srcsuf != 0x44) && ((u8) srcsuf != 0x4D) && ((u8) srcsuf != 0x53) && ((u8) srcsuf != 0x56)) {
                                                            unlink(passin);
                                                        }
                                                        unlink(passout);
                                                        if (tmpst != 0) {
                                                            unlink(symtab);
                                                        }
                                                    } else if (Sflag != 0) {
                                                        unlink(binasm);
                                                    }
                                                    unlink(gentmp);
                                                } else {
                                                    unlink(gentmp);
                                                    if (((((u8) srcsuf != 0x42) && ((u8) srcsuf != 0x53) && ((u8) srcsuf != 0x51) && ((u8) srcsuf != 0x44) && ((u8) srcsuf != 0x4D) && ((u8) srcsuf != 0x56)) || (Oflag >= 2)) && ((u8) srcsuf != 0x4F) && (Kflag == 0)) {
                                                        unlink(passin);
                                                    }
                                                    if (Sflag != 0) {
                                                        if (Kflag == 0) {
                                                            if (tmpst != 0) {
                                                                unlink(symtab);
                                                            }
                                                            unlink(binasm);
                                                        }
                                                    } else if ((u8) Hchar != 0x63) {
                                                        passin = passout;
                                                    case 0x73: /* switch 17 */
                                                    case 0x73: /* switch 18 */
block_2130:
                                                        if ((u8) srcsuf == 0x73) {
                                                            execlist.length = 0;
                                                            addstr(&execlist, "as0");
                                                            if (vflag != 0) {
                                                                addstr(&execlist, "-v");
                                                            }
                                                            addstr(&execlist, "-G");
                                                            addstr(&execlist, Gnum);
                                                            addlist(&execlist, &asflags);
                                                            if ((NoMoreOptions != 0) && ((u8) *passin == 0x2D)) {
                                                                passin = func_00433534(passin);
                                                            }
                                                            addstr(&execlist, passin);
                                                            addstr(&execlist, "-o");
                                                            if (((u8) Hchar == 0x61) || (Kflag != 0)) {
                                                                if ((compiler == 4) && (getsuf(srcfiles.entries[var_s0_3]) == 0)) {
                                                                    var_v0_16 = mkstr(srcfiles.entries[var_s0_3], ".G", NULL);
                                                                } else {
                                                                    var_v0_16 = mksuf(srcfiles.entries[var_s0_3], 0x47);
                                                                }
                                                                passout = var_v0_16;
                                                                if (regular_not_writeable(passout) == 1) {
                                                                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                                    exit(2);
                                                                }
                                                            } else {
                                                                passout = tempstr->unk_2C;
                                                                if (regular_not_writeable(tempstr->unk_2C) == 1) {
                                                                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                                    exit(2);
                                                                }
                                                            }
                                                            addstr(&execlist, passout);
                                                            addstr(&execlist, "-t");
                                                            addstr(&execlist, symtab);
                                                            if (run(as0, execlist.entries, NULL, NULL, NULL) != 0) {
                                                                runerror += 1;
                                                                if ((docpp != 0) || (mflag != 0)) {
                                                                    unlink(passin);
                                                                }
                                                                if (Kflag == 0) {
                                                                    unlink(passout);
                                                                    if (tmpst != 0) {
                                                                        unlink(symtab);
                                                                    }
                                                                }
                                                            } else {
                                                                if ((docpp != 0) || (mflag != 0)) {
                                                                    unlink(passin);
                                                                }
                                                                if ((u8) Hchar != 0x61) {
                                                                    passin = passout;
                                                                    goto block_2159;
                                                                }
                                                            }
                                                        } else {
                                                        case 0x47: /* switch 19 */
block_2159:
                                                            execlist.length = 0;
                                                            addstr(&execlist, "as1");
                                                            addstr(&execlist, "-t5_ll_sc_bug");
                                                            if (tfp_flag != 0) {
                                                                addstr(&execlist, "-tfp");
                                                            }
                                                            if (noaliasokflag != 0) {
                                                                addstr(&execlist, "-noaliasok");
                                                            }
                                                            if (alignarg != NULL) {
                                                                addstr(&execlist, alignarg);
                                                            }
                                                            if (align_common > 0) {
                                                                addstr(&execlist, "-align_common");
                                                            }
                                                            if (((compiler == 4) || ((u8) srcsuf == 0x73)) && (kpic_spec == 0) && (irix4 == 0)) {
                                                                addstr(&execlist, "-pic0");
                                                            }
                                                            if (coff_spec != 0) {
                                                                addstr(&execlist, "-coff");
                                                                kpic_flag = 0;
                                                            } else if (kpic_flag != 0) {
                                                                if (irix4 == 0) {
                                                                    if (coff_spec == 0) {
                                                                        addstr(&execlist, "-elf");
                                                                        if (Oflag >= 3) {
                                                                            addstr(&execlist, "-pic1");
                                                                        } else {
                                                                            addstr(&execlist, "-pic2");
                                                                        }
                                                                    } else {
                                                                        addstr(&execlist, "-coff");
                                                                        kpic_flag = 0;
                                                                    }
                                                                }
                                                            } else if (irix4 == 0) {
                                                                if (coff_spec != 0) {
                                                                    addstr(&execlist, "-coff");
                                                                } else {
                                                                    addstr(&execlist, "-elf");
                                                                }
                                                            }
                                                            if (vflag != 0) {
                                                                addstr(&execlist, "-v");
                                                            }
                                                            if ((fullasoptflag == 0) && ((u8) srcsuf == 0x73) && (Oflag >= 2)) {
                                                                addstr(&execlist, "-noglobal");
                                                            }
                                                            addstr(&execlist, "-G");
                                                            addstr(&execlist, Gnum);
                                                            switch (pflag) { /* switch 15; irregular */
                                                            case 0: /* switch 15 */
                                                                addstr(&execlist, "-p0");
                                                                break;
                                                            case 1: /* switch 15 */
                                                                addstr(&execlist, "-p1");
                                                                break;
                                                            }
                                                            addlist(&execlist, &asflags);
                                                            addlist(&execlist, &as1flags);
                                                            if (irix4 == 0) {
                                                                addlist(&execlist, &olimitflags);
                                                            }
                                                            if ((NoMoreOptions != 0) && ((u8) *passin == 0x2D)) {
                                                                passin = func_00433534(passin);
                                                            }
                                                            addstr(&execlist, passin);
                                                            addstr(&execlist, "-o");
                                                            if (compiler == 4) {
                                                                if (outfile != NULL) {
                                                                    passout = outfile;
                                                                } else {
                                                                    passout = "a.out";
                                                                }
                                                            } else if ((outfile != NULL) && (cflag != 0) && ((Oflag == 3) || (srcfiles.length == 1))) {
                                                                passout = outfile;
                                                            } else {
                                                                if (((u8) srcsuf == 0x3F) && ((u8) Hchar != 0x62) && (Kflag == 0)) {
                                                                    if (cflag == 0) {
                                                                        passout = tempstr->unk_30;
                                                                        tmp_uldobj = tempstr->unk_30;
                                                                    } else if (srcfiles.length == 2) {
                                                                        passout = mksuf(*srcfiles.entries, 0x6F);
                                                                        tmp_uldobj = NULL;
                                                                    } else {
                                                                        passout = mksuf(srcfiles.entries[var_s0_3], 0x6F);
                                                                        tmp_uldobj = NULL;
                                                                    }
                                                                } else {
                                                                    passout = mksuf(srcfiles.entries[var_s0_3], 0x6F);
                                                                }
                                                                if (uldobj_place != -1) {
                                                                    set_place(&objfiles, passout, uldobj_place);
                                                                }
                                                            }
                                                            addstr(&execlist, passout);
                                                            addstr(&execlist, "-t");
                                                            addstr(&execlist, symtab);
                                                            if ((ddoptflag == 1) && (compiler == 3) && (ddoptinfo != 0) && (Oflag >= 2)) {
                                                                addstr(&execlist, "-e");
                                                                if ((((u8) Hchar == 0x62) && (ucodeflag == 0)) || (Kflag != 0)) {
                                                                    addstr(&execlist, mksuf(srcfiles.entries[var_s0_3], 0x45));
                                                                } else {
                                                                    addstr(&execlist, tempstr->unk_68);
                                                                }
                                                            }
                                                            if (regular_not_writeable(passout) != 0) {
                                                                unlink(passout);
                                                            }
                                                            if (run(as1, execlist.entries, NULL, NULL, NULL) != 0) {
                                                                runerror += 1;
                                                                if (Kflag == 0) {
                                                                    if ((u8) srcsuf != 0x47) {
                                                                        unlink(passin);
                                                                    }
                                                                    spE0 = regular_file(passout);
                                                                    if (spE0 == 1) {
                                                                        unlink(passout);
                                                                    } else if (spE0 != 0) {
                                                                        error(2, NULL, 0, NULL, 0, "%s does not exist or is not stat(2)-able. Not deleted (if it exists) even though as1 failed.\n", passout);
                                                                    } else {
                                                                        error(2, NULL, 0, NULL, 0, "%s is not a regular file, not deleted even though as1 failed.\n", passout);
                                                                    }
                                                                    if (tmpst != 0) {
                                                                        unlink(symtab);
                                                                    }
                                                                }
                                                                if (tmp_uldobj != NULL) {
                                                                    unlink(tmp_uldobj);
                                                                }
                                                            } else {
                                                                if ((ddoptflag == 1) && (compiler == 3) && (ddoptinfo != 0) && (Oflag >= 2)) {
                                                                    unlink(tempstr->unk_68);
                                                                }
                                                                if (((u8) srcsuf != 0x47) && (Kflag == 0)) {
                                                                    unlink(passin);
                                                                }
                                                                if ((tmpst != 0) && (Kflag == 0)) {
                                                                    unlink(symtab);
                                                                }
                                                                if ((compiler == 3) && (sp11C != 0) && ((u8) srcsuf != 0x66) && ((u8) srcsuf != 0x46)) {
                                                                    D_1000BF74 = sp11C;
                                                                    relocate_passes("f", NULL, NULL);
                                                                }
                                                                if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (no_prelink == 0)) {
                                                                    update_instantiation_info_file(srcfiles.entries[var_s0_3], passout);
block_2269:
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
block_2270:
                var_s0_3 += 1;
                if ((var_s0_3 >= srcfiles.length) && (uload == 0)) {
                    goto block_2272;
                }
                goto loop_363;
            }
        }
    } else {
block_2272:
        srcsuf = 0;
        if (compiler == 4) {
            if (runerror != 0) {
                exit(1);
            } else {
                exit(0);
            }
        }
        if (NoMoreOptions != 0) {
            var_s0_4 = 0;
            if (objfiles.length > 0) {
                do {
                    if (((u8) *objfiles.entries[var_s0_4] == 0x2D) && (strchr(objfiles.entries[var_s0_4], 0x2EU) != NULL)) {
                        objfiles.entries[var_s0_4] = func_00433534(objfiles.entries[var_s0_4]);
                    }
                    var_s0_4 += 1;
                } while (var_s0_4 < objfiles.length);
            }
        }
        if ((cflag == 0) && (Sflag == 0) && (Eflag == 0) && (Pflag == 0) && (jflag == 0) && (runerror == 0) && (objfiles.length != 0) && ((u8) Hchar == 0) && (nocode == 0)) {
            if ((old_non_shared != 0) && (mips2flag != 0) && (kpic_flag == 0)) {
                error(1, NULL, 0, NULL, 0, "can't mix -mips2 with shared for ucode compilers, try using -non_shared\n");
                default_call_shared = 0;
                call_shared = 0;
            }
            if ((old_non_shared != 0) && (mips3flag != 0)) {
                error(1, NULL, 0, NULL, 0, "can't mix ucode 32-bit -mips3 with shared\n");
                default_call_shared = 0;
                call_shared = 0;
                exit(2);
            }
            if ((old_non_shared != 0) && (coff_spec != 0)) {
                error(1, NULL, 0, NULL, 0, "can't mix -coff with shared, try using -non_shared\n");
                default_call_shared = 0;
                call_shared = 0;
                exit(2);
            }
            if ((old_non_shared != 0) && (excpt_flag != 0)) {
                error(1, NULL, 0, NULL, 0, "can't mix -excpt with shared, try using -non_shared\n");
                default_call_shared = 0;
                call_shared = 0;
                exit(2);
            }
            if (((old_non_shared != 0) || (non_shared != 0)) && (make_edison_shlib != 0)) {
                error(1, NULL, 0, NULL, 0, "can't mix -shared with -non_shared\n");
                exit(2);
            }
            if ((cordflag != 0) && (make_edison_shlib != 0)) {
                error(1, NULL, 0, NULL, 0, "can't mix -shared with -cord\n");
                exit(2);
            }
            if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (no_prelink == 0)) {
                execlist.length = 0;
                addstr(&execlist, "edg_prelink");
                addstr(&execlist, "-fSGI");
                addlist(&execlist, &prelinkerflags);
                if ((vflag != 0) || (verbose_prelink != 0)) {
                    addstr(&execlist, "-v");
                }
                add_prelinker_objects(&execlist, &objfiles);
                if (xpg_flag != 0) {
                    add_prelinker_objects(&execlist, &dashlfiles);
                }
                if (run(prelinker, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror += 1;
                } else {
                    goto block_2323;
                }
            } else {
block_2323:
                execlist.length = 0;
                addstr(&execlist, LD);
                if ((kpic_flag != 0) && (irix4 == 0) && (coff_spec == 0)) {
                    addstr(&ldflags, "-KPIC");
                }
                if ((non_shared != 0) && (non_shared_emitted == 0)) {
                    if ((mips2flag == 0) && (mips3flag == 0)) {
                        addstr(&ldflags, "-non_shared");
                        non_shared_emitted = 1;
                    }
                } else if ((call_shared != 0) || (make_edison_shlib != 0)) {
                    if (transitive_link != 0) {
                        addstr(&ldflags, "-transitive_link");
                    } else if (full_transitive_link != 0) {
                        addstr(&ldflags, "-full_transitive_link");
                    } else if (no_transitive_link != 0) {
                        addstr(&ldflags, "-no_transitive_link");
                    }
                }
                if (quickstart_info != 0) {
                    addstr(&ldflags, "-quickstart_info");
                }
                if ((elfflag != 0) && (coff_spec == 0)) {
                    addstr(&execlist, "-elf");
                }
                if (tfp_flag != 0) {
                    addstr(&execlist, "-allow_jump_at_eop");
                }
                if ((compiler == 1) && (c_compiler_choice == 3)) {
                    addstr(&execlist, "-delta");
                }
                if (cordflag != 0) {
                    addstr(&execlist, "-o");
                    passout = tempstr->unk_58;
                    addstr(&execlist, tempstr->unk_58);
                } else if (outfile != NULL) {
                    addstr(&execlist, "-o");
                    addstr(&execlist, outfile);
                }
                if (gethostsex() != targetsex) {
                    if (targetsex == 0) {
                        addstr(&execlist, "-EB");
                    } else {
                        addstr(&execlist, "-EL");
                    }
                }
                if (make_edison_shlib != 0) {
                    addstr(&execlist, "-shared");
                }
                if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                    add_cxx_symbol_options();
                }
                if (irix4 != 0) {
                    addstr(&execlist, mkstr("-L", NULL));
                    if (non_shared != 0) {
                        addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/nonshared/", NULL));
                        crtx = mkstr(comp_host_root, "usr/lib/nonshared/", CRTX, NULL);
                        var_v0_17 = mkstr(comp_host_root, "usr/lib/nonshared/", "crtn.o", NULL);
                    } else {
                        addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/", NULL));
                        crtx = mkstr(comp_host_root, "usr/lib/", CRTX, NULL);
                        var_v0_17 = mkstr(comp_host_root, "usr/lib/", "crtn.o", NULL);
                    }
                    crtn = var_v0_17;
                }
                if (svr4_systype != 0) {
                    if (compchoice == 1) {
                        addstr(&execlist, mkstr("-SYSTYPE_SVR4", NULL, NULL));
                    }
                    addstr(&execlist, mkstr("-_SYSTYPE_SVR4", NULL, NULL));
                    if ((call_shared != 0) || (make_edison_shlib != 0)) {
                        addstr(&execlist, "-require_dynamic_link");
                        addstr(&execlist, "_rld_new_interface");
                        if (ignore_unresolved_flag != 0) {
                            addstr(&execlist, "-ignore_unresolved");
                        } else if (no_unresolved_flag != 0) {
                            addstr(&execlist, "-no_unresolved");
                        } else if ((default_svr4 != 0) || (make_edison_shlib != 0)) {
                            addstr(&execlist, "-ignore_unresolved");
                        } else {
                            addstr(&execlist, "-no_unresolved");
                        }
                    }
                }
                if (fiveflag != 0) {
                    addstr(&execlist, mkstr("-L", runlib, NULL));
                }
                if ((allBstring != NULL) && ((u8) *allBstring != 0)) {
                    addstr(&execlist, mkstr("-B", allBstring, NULL));
                }
                if (cordflag != 0) {
                    addstr(&execlist, "-r");
                    addstr(&execlist, "-d");
                    addstr(&execlist, "-z");
                }
                if (irix4 != 0) {
                    addstr(&execlist, "-G");
                } else {
                    addstr(&execlist, mkstr("-Wx", ",", "-G", NULL));
                }
                addstr(&execlist, Gnum);
                addlist(&execlist, &ldflags);
                addlist(&execlist, &nldflags);
                if ((mips2flag != 0) && (sp148 == 0)) {
                    if (strcmp("/", comp_target_root) != 0) {
                        if (non_shared != 0) {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
                        } else {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
                        }
                    } else if (non_shared != 0) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
                    }
                }
                if ((mips1flag != 0) && (sp148 == 0)) {
                    if (strcmp("/", comp_target_root) != 0) {
                        if (non_shared != 0) {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
                        } else if (abi_flag == 0) {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
                        }
                    } else if (non_shared != 0) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else if (abi_flag == 0) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
                    }
                }
                if (strcmp("/", comp_target_root) != 0) {
                    if (Lflag == 0) {
                        if ((compiler == 1) && (c_compiler_choice == 3)) {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/DCC", currcomp, NULL));
                        }
                        if (non_shared != 0) {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/nonshared/", currcomp, NULL));
                        } else if (abi_flag == 0) {
                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, NULL));
                        }
                    }
                } else if ((Lflag == 0) && (compiler == 1) && (c_compiler_choice == 3)) {
                    addstr(&execlist, mkstr("-L", runlib, "usr/lib/DCC", currcomp, NULL));
                }
                if (make_edison_shlib != 0) {
                    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                        addstr(&execlist, cxx_init);
                    }
                    if ((compiler == 1) && (c_compiler_choice == 3)) {
                        addstr(&execlist, delta_init);
                    }
                    addlist(&execlist, &objfiles);
                    if (xpg_flag != 0) {
                        addlist(&execlist, &dashlfiles);
                    }
                    if (nodeflib == 0) {
                        if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                            var_s3_9 = D_1000BF90 == 0;
                            if (var_s3_9 != 0) {
                                var_s3_9 = strcmp(LD, "old_ld") != 0;
                            }
                            spDC = var_s3_9;
                            if (spDC != 0) {
                                addstr(&execlist, "-dont_warn_unused");
                            }
                            if (exception_handling != 0) {
                                addstr(&execlist, "-lCsup");
                            }
                            addstr(&execlist, "-lC");
                            if (spDC != 0) {
                                addstr(&execlist, "-warn_unused");
                            }
                        }
                        if (xpg_flag != 0) {
                            addstr(&execlist, "-dont_warn_unused");
                            addstr(&execlist, "-lgen");
                            addstr(&execlist, "-warn_unused");
                        }
                        addstr(&execlist, "-lc");
                    }
                } else {
                    addstr(&execlist, "-nocount");
                    addstr(&execlist, crtx);
                    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                        addstr(&execlist, cxx_init);
                    }
                    if ((compiler == 1) && (c_compiler_choice == 3)) {
                        addstr(&execlist, delta_init);
                    }
                    addstr(&execlist, "-count");
                    addlist(&execlist, &objfiles);
                    if (xpg_flag != 0) {
                        addlist(&execlist, &dashlfiles);
                    }
                    addlist(&execlist, &ldZflags);
                    if ((ansichoice == 0) && (compiler == 1) && (irix4 == 0)) {
                        addstr(&execlist, "-cckr");
                    }
                    addstr(&execlist, "-nocount");
                    if (nodeflib == 0) {
                        if ((compiler == 2) || (haspascal != 0)) {
                            addspacedstr(&execlist, libp);
                            addspacedstr(&execlist, libxmalloc);
                            addspacedstr(&execlist, libexc);
                            addspacedstr(&execlist, libmld);
                        }
                        if ((compiler == 3) || (hasfortran != 0)) {
                            if (mp_flag != 0) {
                                addspacedstr(&execlist, libI77_mp);
                            }
                            if ((non_shared != 0) || (irix4 != 0)) {
                                addspacedstr(&execlist, libF77);
                                addspacedstr(&execlist, libm);
                                addspacedstr(&execlist, libU77);
                                if (D_1000C130 != 0) {
                                    spD8 = strlen(libI77);
                                    spD4 = malloc(spD8 + 2);
                                    memcpy(spD4, libI77, spD8);
                                    spD4[spD8] = 0x5F;
                                    spD4[spD8].unk_1 = 0x73;
                                    spD4[spD8].unk_2 = 0;
                                    libI77 = spD4;
                                }
                                addspacedstr(&execlist, libI77);
                                addspacedstr(&execlist, libisam);
                            } else {
                                addspacedstr(&execlist, libftn);
                                addspacedstr(&execlist, libm);
                            }
                        }
                        if (compiler == 5) {
                            addstr(&execlist, libpl1);
                            addspacedstr(&execlist, libxmalloc);
                            addstr(&execlist, "-ltermcap");
                            addspacedstr(&execlist, libexc);
                            addspacedstr(&execlist, libmld);
                        }
                        if ((compiler == 2) || ((hasfortran != 0) && (compiler != 3)) || (haspascal != 0) || (haspl1 != 0) || (compiler == 5) || (compiler == 6)) {
                            addspacedstr(&execlist, libm);
                        }
                        if (pgflag != 0) {
                            addspacedstr(&execlist, libgprof);
                        } else if (pflag != 0) {
                            addspacedstr(&execlist, libprof);
                        }
                        if (sixty4bitflag == 0) {
                            ldw_file = fopen(libdw_path, "r");
                            if (ldw_file != NULL) {
                                addspacedstr(&execlist, libdw);
                            }
                        }
                        if (cmp_flag & 0x10000) {
                            addstr(&execlist, libc_mp);
                            if (compiler == 1) {
                                addstr(&execlist, "-lkapio");
                            }
                        }
                        if ((run_sopt != 0) && (compiler == 1)) {
                            addstr(&execlist, "-lkapio");
                        }
                        if (compiler == 3) {
                            if (D_1000C130 == 2) {
                                addstr(&execlist, "-lc_s");
                                if (xpg_flag != 0) {
                                    addstr(&execlist, "-dont_warn_unused");
                                    addstr(&execlist, "-lgen");
                                    addstr(&execlist, "-warn_unused");
                                }
                                addstr(&execlist, "-lc");
                            } else {
                                if ((irix4 != 0) && (B_1000ED74 == 0)) {
                                    addstr(&execlist, "-lmpc");
                                }
                                if (B_1000ED2C != 0) {
                                    addstr(&execlist, "-lc_s");
                                } else if (B_1000ED30 != 0) {
                                    addstr(&execlist, "-lc_s");
                                }
                                if (xpg_flag != 0) {
                                    addstr(&execlist, "-dont_warn_unused");
                                    addstr(&execlist, "-lgen");
                                    addstr(&execlist, "-warn_unused");
                                }
                                addstr(&execlist, "-lc");
                            }
                        } else {
                            if ((irix4 != 0) && (cmp_flag & 0x10000)) {
                                addstr(&execlist, "-lmpc");
                            }
                            if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                                var_s3_10 = D_1000BF90 == 0;
                                if (var_s3_10 != 0) {
                                    var_s3_10 = strcmp(LD, "old_ld") != 0;
                                }
                                spD0 = var_s3_10;
                                if (spD0 != 0) {
                                    addstr(&execlist, "-dont_warn_unused");
                                }
                                if (exception_handling != 0) {
                                    addstr(&execlist, "-lCsup");
                                }
                                addstr(&execlist, "-lC");
                                if (spD0 != 0) {
                                    addstr(&execlist, "-warn_unused");
                                }
                            }
                            if (B_1000ED2C != 0) {
                                addstr(&execlist, "-lc_s");
                            } else if (B_1000ED30 != 0) {
                                addstr(&execlist, "-lc_s");
                            }
                            if (xpg_flag != 0) {
                                addstr(&execlist, "-dont_warn_unused");
                                addstr(&execlist, "-lgen");
                                addstr(&execlist, "-warn_unused");
                            }
                            addstr(&execlist, "-lc");
                        }
                    }
                    if (crtn_required != 0) {
                        addstr(&execlist, crtn);
                    }
                    if (rls_id_object != NULL) {
                        addstr(&execlist, rls_id_object);
                    }
                }
                passin = NULL;
                if (run(ld, execlist.entries, NULL, NULL, tempstr->unk_80) != 0) {
                    runerror += 1;
                    if (Kflag == 0) {
                        if ((strcmp(LD, "old_ld") == 0) || ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)))) {
                            if (outfile != NULL) {
                                unlink(outfile);
                            } else {
                                unlink("a.out");
                            }
                        }
                        if (tmp_uldobj != NULL) {
                            unlink(tmp_uldobj);
                        }
                    }
                }
                if (tempstr->unk_80 != NULL) {
                    if ((stat(tempstr->unk_80, &sp48) == 0) && (sp48.st_size > 0)) {
                        execlist.length = 0;
                        addstr(&execlist, "c++filt");
                        run(filter, execlist.entries, tempstr->unk_80, NULL, NULL);
                    }
                    unlink(tempstr->unk_80);
                }
                if ((runerror == 0) && (compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                    execlist.length = 0;
                    addstr(&execlist, patch);
                    if (vflag != 0) {
                        addstr(&execlist, "-d");
                    }
                    if (outfile != NULL) {
                        addstr(&execlist, outfile);
                    } else {
                        addstr(&execlist, "a.out");
                    }
                    if (run(patch, execlist.entries, NULL, NULL, NULL) != 0) {
                        runerror += 1;
                    }
                }
                if ((runerror == 0) && (do_strip != 0)) {
                    execlist.length = 0;
                    addstr(&execlist, strip);
                    if (outfile != NULL) {
                        addstr(&execlist, outfile);
                    } else {
                        addstr(&execlist, "a.out");
                    }
                    if (run(strip, execlist.entries, NULL, NULL, NULL) != 0) {
                        runerror += 1;
                    }
                }
            }
block_2588:
            if ((cordflag != 0) && (runerror == 0)) {
                execlist.length = 0;
                addstr(&execlist, "cord");
                if (vflag != 0) {
                    addstr(&execlist, "-v");
                }
                addlist(&execlist, &cordflags);
                if (outfile != NULL) {
                    passout = outfile;
                } else {
                    passout = "a.out";
                }
                addstr(&execlist, "-o");
                addstr(&execlist, passout);
                addstr(&execlist, tempstr->unk_58);
                if (feedlist.length != 0) {
                    addlist(&execlist, &feedlist);
                } else {
                    addstr(&execlist, mkstr(passout, ".fb", NULL));
                }
                if (run(cord, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror += 1;
                    unlink(passout);
                    unlink(tempstr->unk_58);
                } else {
                    unlink(tempstr->unk_58);
                }
            }
            if ((runerror == 0) && (srcfiles.length == 1) && (nobjs == 1) && (Kflag == 0)) {
                unlink(mksuf(*srcfiles.entries, 0x6F));
            }
        }
    }
    if (tmp_uldobj != NULL) {
        unlink(tmp_uldobj);
    }
    if (editflag != 0) {
        unlink(errout);
        if (editflag == 2) {
            unlink(tempstr->unk_64);
        }
    }
    if ((compiler == 1) && (gflag >= 2)) {
        unlink(tempstr->unk_84);
    }
    if (runerror != 0) {
        exit(1);
    }
    return 0;
}

void process_config(s32 argc, s8** argv) {
    s8* sp1144;
    s8* sp1140;
    FILE* sp113C;
    s8 sp13C;
    s32 sp138;
    s32 temp_s0;
    s32 var_s0;
    s8* temp_t7;
    s8* var_s1;
    u8 temp_t7_2;
    u8 temp_t8;

    var_s0 = 1;
    sp1144 = comp_target_root;
    if (argc > 1) {
loop_1:
        if (strcmp(argv[var_s0], "-systype") == 0) {
            temp_s0 = var_s0 + 1;
            if (temp_s0 >= argc) {
                error(1, NULL, 0, NULL, 0, "-systype must have an argument\n");
                exit(2);
            }
            user_systype = 1;
            temp_t7 = argv[temp_s0];
            systype = temp_t7;
            if (strcmp(temp_t7, "svr4") == 0) {
                svr4_systype = 1;
            } else {
                error(1, NULL, 0, NULL, 0, "only systype svr4 allowed\n");
                exit(2);
            }
            if ((strcmp(systype, "svr4") != 0) && (strcmp(systype, "bsd43") != 0) && (strcmp(systype, "svr3") != 0) && (strcmp(systype, "sysv") != 0) && (fopen(strcat("/", systype), "r") == NULL) && (systype_warn == 0)) {
                error(2, NULL, 0, NULL, 0, "This systype doesn't exist on this machine; changed systype to svr3.\n");
                systype_warn = 1;
                systype = "svr3";
            }
            if (svr4_systype == 0) {
                sp1144 = mkstr(comp_target_root, systype, "/", NULL);
            }
        } else {
            var_s0 += 1;
            if (var_s0 < argc) {
                goto loop_1;
            }
        }
    }
    if (user_systype == 0) {
        sp1144 = mkstr(comp_target_root, systype, "/", NULL);
    }
    user_systype = 0;
    sp1140 = mkstr(sp1144, "usr/lib/", currcomp, "comp.config", NULL);
    sp113C = fopen(sp1140, "r");
    if ((sp113C != NULL) && (fgets(&sp13C, 0x1000, sp113C) != NULL)) {
        if ((&sp13C)[strlen(&sp13C)].unk_-1 == 0xA) {
            (&sp13C)[strlen(&sp13C)].unk_-1 = 0;
        }
        var_s1 = &sp13C;
        sp138 = 0;
        if ((u8) *var_s1 != 0) {
            do {
                if (((u8) *var_s1 != 0) && (((u8) *var_s1 == 0x20) || ((u8) *var_s1 == 9))) {
loop_27:
                    temp_t7_2 = var_s1->unk_1;
                    var_s1 += 1;
                    if (temp_t7_2 != 0) {
                        if (((u8) *var_s1 == 0x20) || ((u8) *var_s1 == 9)) {
                            goto loop_27;
                        }
                    }
                }
                if ((u8) *var_s1 != 0) {
                    (&sp38[0])[sp138] = var_s1;
                    sp138 += 1;
                }
                if (((u8) *var_s1 != 0) && ((u8) *var_s1 != 0x20) && ((u8) *var_s1 != 9)) {
loop_35:
                    temp_t8 = var_s1->unk_1;
                    var_s1 += 1;
                    if ((temp_t8 != 0) && ((u8) *var_s1 != 0x20)) {
                        if ((u8) *var_s1 != 9) {
                            goto loop_35;
                        }
                    }
                }
                if ((u8) *var_s1 != 0) {
                    *var_s1 = 0;
                    var_s1 += 1;
                }
            } while ((u8) *var_s1 != 0);
        }
        parse_command(sp138, &sp38[0]);
    }
}

void add_info(s8* str) {
    addstr(&upasflags, str);
    addstr(&fcomflags, str);
    addstr(&ulpiflags, str);
    addstr(&uopt0flags, str);
    addstr(&ddoptflags, str);
    addstr(&optflags, str);
    addstr(&umergeflags, str);
    addstr(&uloopflags, str);
    addstr(&genflags, str);
    addstr(&asflags, str);
    addstr(&ldflags, str);
}

void parse_command(s32 argc, s8** argv) {
    s8* sp15C;
    s8* sp158;
    s8* sp154;
    s8 sp153;
    s32 sp14C;
    s8* sp148;
    s8* sp144;
    s8* sp140;
    s8* sp134;
    s8* sp130;
    s8* sp12C;
    s8* sp128;
    s8* sp124;
    s8* sp120;
    s8* sp11C;
    s8* sp118;
    s32 sp114;
    s32 sp110;
    s8* sp10C;
    s32 sp108;
    s8* sp104;
    s8* sp100;
    s8* spFC;
    struct stat sp74;
    struct_mpflags* sp70;
    struct_mpflags* sp6C;
    s8* sp68;
    s8* sp64;
    s32 sp60;
    s32 sp5C;
    s8* sp58;
    u32 sp54;
    s32 temp_t1_4;
    s32 temp_t4_2;
    s32 temp_t5_7;
    s32 temp_t6_3;
    s32 var_s0;
    s32 var_s1;
    s32 var_t2;
    s32* var_at;
    s32* var_at_2;
    s8* temp_t0;
    s8* temp_t1_2;
    s8* temp_t2;
    s8* temp_t2_2;
    s8* temp_t3_3;
    s8* temp_t4_6;
    s8* temp_t5;
    s8* temp_t5_5;
    s8* temp_t5_6;
    s8* temp_t6_4;
    s8* temp_t6_5;
    s8* temp_t7_5;
    s8* temp_t7_7;
    s8* temp_t8;
    s8* temp_t8_5;
    s8* temp_t9_2;
    s8* temp_t9_3;
    s8* temp_v0;
    s8* temp_v0_2;
    s8* var_s2;
    s8* var_s2_10;
    s8* var_s2_3;
    s8* var_s2_4;
    s8* var_s2_5;
    s8* var_s2_6;
    s8* var_s2_7;
    s8* var_s2_8;
    s8* var_s2_9;
    s8* var_s3;
    s8* var_v0;
    s8* var_v0_2;
    u8 temp_s4;
    u8 temp_s4_2;
    u8 temp_s4_3;
    u8 temp_t1;
    u8 temp_t1_3;
    u8 temp_t2_3;
    u8 temp_t2_4;
    u8 temp_t3;
    u8 temp_t3_2;
    u8 temp_t4;
    u8 temp_t4_3;
    u8 temp_t4_4;
    u8 temp_t4_5;
    u8 temp_t4_7;
    u8 temp_t5_2;
    u8 temp_t5_3;
    u8 temp_t5_4;
    u8 temp_t6;
    u8 temp_t6_2;
    u8 temp_t7;
    u8 temp_t7_2;
    u8 temp_t7_3;
    u8 temp_t7_4;
    u8 temp_t7_6;
    u8 temp_t7_8;
    u8 temp_t8_2;
    u8 temp_t8_3;
    u8 temp_t8_6;
    u8 temp_t9;
    u8* temp_t2_5;
    u8* temp_t8_4;
    u8* var_s2_2;

    var_s1 = saved_reg_s1;
    sp15C = NULL;
    sp158 = NULL;
    sp154 = NULL;
    sp153 = 0;
    sp14C = 1;
    sp148 = getenv("SGI_IRIX4");
    if (sp148 != NULL) {
        irix4 = 1;
        comp_host_root = "/usr/irix4/";
        systype = "";
        elfflag = 0;
        svr4_systype = 0;
        call_shared = 0;
        non_shared = 0;
        old_non_shared = 0;
        default_call_shared = 0;
        Gnum = "8";
        kpic_flag = 0;
        mips_abi = 0;
        runlib = "/usr/irix4/";
        relocate_passes("pKfjrsulmvocabtyz", NULL, NULL);
    }
    var_s0 = 0;
    if (argc > 0) {
        do {
            if (((u8) *argv[var_s0] == 0x2D) && ((NoMoreOptions == 0) || (strchr(argv[var_s0], 0x2EU) == NULL))) {
                temp_t7 = argv[var_s0]->unk_1;
                switch (temp_t7) {                  /* switch 1 */
                case 0x23:                          /* switch 1 */
                    error(2, NULL, 0, NULL, 0, "-# is not supported. Use -v to see compiler passesn");
                    break;
                case 0x31:                          /* switch 1 */
                    if ((compiler == 3) && (argv[var_s0]->unk_2 == 0)) {
                        mp_onetripflag = 1;
                        addstr(&fcomflags, argv[var_s0]);
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x33:                          /* switch 1 */
                    if ((strcmp(argv[var_s0], "-32bit") == 0) || (strcmp(argv[var_s0], "-32") == 0)) {
                        thirty2bitflag = 1;
                        mips_abi = 1;
                    }
                    break;
                case 0x35:                          /* switch 1 */
                    error(2, NULL, 0, NULL, 0, "-5 not supported\n");
                    if (argv[var_s0]->unk_2 == 0) {
                        if (Bflag != 0) {
                            if (fiveflag == 0) {
                                error(1, NULL, 0, NULL, 0, "-5 must precede any -B flags\n");
                                exit(2);
                            }
                        } else {
                            fiveflag += 1;
                            include = mkstr(comp_target_root, "usr/5include", NULL);
                            if (Bstring != NULL) {
                                relocate_passes("h", NULL, Bstring);
                            }
                            newrunlib();
                        }
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x36:                          /* switch 1 */
                    if ((compiler == 3) && (strcmp(argv[var_s0], "-66") == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-64bit") == 0) {
                        error(2, NULL, 0, NULL, 0, "-64bit option is not yet implemented for ucode compilers, ignore\n");
                        sixty4bit_spec = 1;
                        if (swopcodeflag != 0) {
                            error(1, NULL, 0, NULL, 0, "-64bit can not be used with -swopcode for ucode compilers\n");
                            exit(2);
                        }
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x41:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        var_s0 += 1;
                        if (var_s0 < argc) {
                            addstr(&objfiles, "-A");
                            addstr(&objfiles, argv[var_s0]);
                        } else {
                            error(1, NULL, 0, NULL, 0, "ld requires -A to have an argument\n");
                            exit(2);
                            goto block_32;
                        }
                    } else {
block_32:
                        if (strcmp(argv[var_s0], "-AutoGnum") == 0) {
                            addstr(&uldflags, argv[var_s0]);
                            if (strcmp(Gnum, "0") != 0) {
                                Gnum = "0";
                            }
                        } else if (argv[var_s0]->unk_1 == 0x41) {
                            addstr(&cppflags, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-A-") == 0) {
                            addstr(&cppflags, argv[var_s0]);
                        } else {
                            goto block_1537;
                        }
                    }
                    break;
                case 0x42:                          /* switch 1 */
                    if ((argv[var_s0].unk_0->unk_2 == 0) && (var_s0 < (argc - 1)) && ((strcmp(argv[var_s0].unk_4, "static") == 0) || (strcmp(argv[var_s0].unk_4, "dynamic") == 0) || (strcmp(argv[var_s0].unk_4, "symbolic") == 0))) {
                        addstr(&objfiles, argv[var_s0]);
                        var_s0 += 1;
                        addstr(&objfiles, argv[var_s0]);
                    } else {
                        Bflag = 1;
                        temp_t5 = argv[var_s0] + 2;
                        sp144 = temp_t5;
                        relocate_passes(tstring, hstring, temp_t5);
                        if (tstring == NULL) {
                            Bstring = sp144;
                        }
                    }
                    break;
                case 0x43:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        if (compiler == 3) {
                            addstr(&fcomflags, argv[var_s0]);
                        } else if (compiler == 2) {
                            addstr(&upasflags, argv[var_s0]);
                        } else if (compiler == 1) {
                            addstr(&cppflags, argv[var_s0]);
                        } else {
                            goto block_54;
                        }
                    } else {
block_54:
                        if (strncmp(argv[var_s0], "-CG_EMIT:", 5U) == 0) {
                            error(2, NULL, 0, NULL, 0, "-CG_EMIT options are ignored\n");
                        } else {
                            goto block_1537;
                        }
                    }
                    break;
                case 0x44:                          /* switch 1 */
                    if (strncmp(argv[var_s0], "-DEFAULT:", strlen("-DEFAULT:\0-D taken as empty cpp -D, not ld(1) -D hexnum\n\0-D\0ld requires -D to have an argument\n")) != 0) {
                        if (argv[var_s0]->unk_2 == 0) {
                            if ((var_s0 + 1) < argc) {
                                sp140 = malloc(strlen(argv[var_s0].unk_4) + 3);
                                sp140->unk_0 = 0x2D;
                                sp140->unk_1 = 0x44;
                                sp140->unk_2 = 0;
                                addstr(&undefineflags, strcat(sp140, argv[var_s0].unk_4));
                                add_static_opt(mkstr(argv[var_s0].unk_0, argv[var_s0].unk_4, NULL));
                            }
                            var_s0 += 1;
                        } else {
                            addstr(&undefineflags, argv[var_s0]);
                            add_static_opt(argv[var_s0]);
                        }
                    }
                    break;
                case 0x45:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        Eflag += 1;
                        docpp = 1;
                    } else if ((argv[var_s0]->unk_3 == 0) && ((argv[var_s0]->unk_2 == 0x42) || (argv[var_s0]->unk_2 == 0x4C))) {
                        if (argv[var_s0]->unk_2 == 0x42) {
                            if ((Bflag != 0) && (targetsex != 0)) {
                                error(1, NULL, 0, NULL, 0, "-EB or -EL must precede any -B flags for ucode compilers\n");
                                exit(2);
                            }
                            targetsex = 0;
                        } else {
                            if ((Bflag != 0) && (targetsex != 1)) {
                                error(1, NULL, 0, NULL, 0, "-EB or -EL must precede any -B flags for ucode compilers\n");
                                exit(2);
                            }
                            targetsex = 1;
                        }
                        newrunlib();
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x46:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        if (compiler == 3) {
                            Fflag += 1;
                        } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                            cflag = 1;
                            Fflag = 1;
                            default_template_instantiation_mode = 1;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x47:                          /* switch 1 */
                    if (strncmp(argv[var_s0], "-GCM:", 5U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-GCM options are ignored\n");
                    } else if (argv[var_s0]->unk_2 == 0) {
                        if (default_svr4 != 0) {
                            if (dn_flag != 0) {
                                error(1, NULL, 0, NULL, 0, "-G can not be used with -dn \n");
                                exit(2);
                            }
                            G_flag = 1;
                            addstr(&ldflags, argv[var_s0]);
                        } else {
                            var_s0 += 1;
                            if (var_s0 >= argc) {
                                error(1, NULL, 0, NULL, 0, "-G requires a decimal number argument\n");
                                exit(2);
                            }
                            if (Oflag < 3) {
                                Gnum = argv[var_s0];
                            } else {
                                Gnum = "0";
                            }
                            goto block_101;
                        }
                    } else if (default_svr4 == 0) {
                        if (Oflag < 3) {
                            Gnum = argv[var_s0] + 2;
                        } else {
                            Gnum = "0";
                        }
block_101:
                        var_s2 = Gnum;
                        if ((u8) *var_s2 != 0) {
                            do {
                                if (!(__ctype[(u8) var_s2->unk_0].unk_1 & 4)) {
                                    error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", Gnum);
                                    exit(2);
                                }
                                temp_t7_2 = var_s2->unk_1;
                                var_s2 += 1;
                            } while (temp_t7_2 != 0);
                        }
                        if (Gseen_flag == 0) {
                            relocate_passes(tstring, hstring, NULL);
                            Gseen_flag = 1;
                        }
                    }
                    break;
                case 0x48:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        addstr(&cppflags, argv[var_s0]);
                        Eflag += 1;
                    } else if (argv[var_s0]->unk_3 == 0) {
                        temp_t6 = argv[var_s0]->unk_2;
                        var_s2_2 = "fKMdkjusmocab";
                        Hchar = (s8) temp_t6;
                        if ((*var_s2_2 != 0) && (*var_s2_2 != temp_t6)) {
loop_112:
                            temp_t5_2 = var_s2_2->unk_1;
                            var_s2_2 += 1;
                            if (temp_t5_2 != 0) {
                                if (*var_s2_2 != (u8) Hchar) {
                                    goto loop_112;
                                }
                            }
                        }
                        if (*var_s2_2 == 0) {
                            error(1, NULL, 0, NULL, 0, "Unknown character in %s\n", argv[var_s0]);
                            exit(2);
                        }
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x49:                          /* switch 1 */
                    if (argv[var_s0].unk_0->unk_2 == 0) {
                        if (((argv[var_s0].unk_4 != NULL) && (*argv[var_s0].unk_4 == 0x2D)) || (isdir(argv[var_s0].unk_4) == 0)) {
                            emptyIflag += 1;
                        } else {
                            var_s0 += 1;
                            sp134 = mkstr("-I", argv[var_s0], NULL);
                            addstr(&cppflags, sp134);
                            addstr(&cpp2flags, sp134);
                            add_static_opt(mkstr("-I", full_path(argv[var_s0]), NULL));
                        }
                    } else {
                        addstr(&cppflags, argv[var_s0]);
                        addstr(&cpp2flags, argv[var_s0]);
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(mkstr("-I", full_path(argv[var_s0] + 2), NULL));
                    }
                    break;
                case 0x4A:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-Jsfm") != 0) {
                        if (strcmp(argv[var_s0], "-J") == 0) {
                            temp_t2 = argv[var_s0].unk_4;
                            sp12C = temp_t2;
                            sp130 = temp_t2;
                            if ((u8) *temp_t2 != 0) {
                                do {
                                    if (!(__ctype[(u8) *sp130].unk_1 & 4)) {
                                        error(1, NULL, 0, NULL, 0, "non-digit character in -J %s\n", sp12C);
                                        exit(2);
                                    }
                                    sp130 += 1;
                                } while ((u8) sp130[1] != 0);
                            }
                            addstr(&prelinkerflags, argv[var_s0]);
                            addstr(&prelinkerflags, sp12C);
                            var_s0 += 1;
                        } else {
                        case 0x4B:                  /* switch 1 */
                            if (default_svr4 != 0) {
                                temp_t2_2 = argv[var_s0];
                                Kpass = temp_t2_2 + 2;
                                if ((u8) temp_t2_2[2] == 0) {
                                    Kpass = argv[var_s0] + 3;
                                }
                                temp_t3 = (u8) *Kpass;
                                if ((temp_t3 != 0) || (temp_t3 == 0x2C)) {
loop_135:
                                    var_s2_3 = Kpass;
                                    j = 0;
                                    if (((u8) *var_s2_3 != 0x2C) && ((u8) *var_s2_3 != 0)) {
loop_137:
                                        (&Karg)[j] = (s8) (u8) *var_s2_3;
                                        var_s2_3 += 1;
                                        j += 1;
                                        if ((u8) *var_s2_3 != 0x2C) {
                                            if ((u8) *var_s2_3 != 0) {
                                                goto loop_137;
                                            }
                                        }
                                    }
                                    Kpass = var_s2_3;
                                    if (strncmp(&Karg, "minabi", 6U) == 0) {
                                        kminabiflag = 1;
                                        goto block_153;
                                    }
                                    if (strncmp(&Karg, "fpe", 3U) == 0) {
                                        addstr(&ldflags, "-Kfpe");
                                        goto block_153;
                                    }
                                    if (strncmp(&Karg, "sd", 2U) == 0) {
                                        addstr(&ldflags, "-Ksd");
                                        goto block_153;
                                    }
                                    if (strncmp(&Karg, "sz", 2U) == 0) {
                                        addstr(&ldflags, "-Ksz");
                                        goto block_153;
                                    }
                                    if (strncmp(&Karg, "mau", 3U) == 0) {
                                        addstr(&ldflags, "-Kmau");
                                        goto block_153;
                                    }
                                    if (strncmp(&Karg, "PIC", 3U) == 0) {
                                        if (non_shared != 0) {
                                            error(2, NULL, 0, NULL, 0, "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                            kpic_flag = 0;
                                        } else {
                                            kpic_flag = 1;
                                            kpic_spec = 1;
                                        }
block_153:
                                        j = 0;
                                        if ((u32) j < strlen(&Karg)) {
                                            do {
                                                (&Karg)[j] = 0x20;
                                                j += 1;
                                            } while ((u32) j < strlen(&Karg));
                                        }
                                        if (Kpass != NULL) {
                                            temp_t7_3 = (u8) *Kpass;
                                            if ((temp_t7_3 == 0x2C) && (temp_t7_3 != 0)) {
loop_158:
                                                Kpass += 1;
                                                if (Kpass != NULL) {
                                                    temp_t9 = (u8) *Kpass;
                                                    if (temp_t9 == 0x2C) {
                                                        if (temp_t9 != 0) {
                                                            goto loop_158;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        temp_t2_3 = (u8) *Kpass;
                                        if ((temp_t2_3 == 0) && (temp_t2_3 != 0x2C)) {

                                        } else {
                                            goto loop_135;
                                        }
                                    } else {
                                        goto block_1537;
                                    }
                                }
                            } else if (svr4_systype != 0) {
                                temp_t8 = argv[var_s0];
                                Kpass = temp_t8 + 2;
                                if ((u8) temp_t8[2] == 0) {
                                    Kflag += 1;
                                    addstr(&fcomflags, argv[var_s0]);
                                }
                                temp_t7_4 = (u8) *Kpass;
                                if ((temp_t7_4 != 0) || (temp_t7_4 == 0x2C)) {
loop_169:
                                    var_s2_4 = Kpass;
                                    j = 0;
                                    if (((u8) *var_s2_4 != 0x2C) && ((u8) *var_s2_4 != 0)) {
loop_171:
                                        (&Karg)[j] = (s8) (u8) *var_s2_4;
                                        var_s2_4 += 1;
                                        j += 1;
                                        if ((u8) *var_s2_4 != 0x2C) {
                                            if ((u8) *var_s2_4 != 0) {
                                                goto loop_171;
                                            }
                                        }
                                    }
                                    Kpass = var_s2_4;
                                    if (strncmp(&Karg, "minabi", 6U) == 0) {
                                        kminabiflag = 1;
                                        goto block_187;
                                    }
                                    if (strncmp(&Karg, "fpe", 3U) == 0) {
                                        addstr(&ldflags, "-Kfpe");
                                        goto block_187;
                                    }
                                    if (strncmp(&Karg, "sd", 2U) == 0) {
                                        addstr(&ldflags, "-Ksd");
                                        goto block_187;
                                    }
                                    if (strncmp(&Karg, "sz", 2U) == 0) {
                                        addstr(&ldflags, "-Ksz");
                                        goto block_187;
                                    }
                                    if (strncmp(&Karg, "mau", 3U) == 0) {
                                        addstr(&ldflags, "-Kmau");
                                        goto block_187;
                                    }
                                    if (strncmp(&Karg, "PIC", 3U) == 0) {
                                        if (non_shared != 0) {
                                            error(2, NULL, 0, NULL, 0, "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                            kpic_flag = 0;
                                        } else {
                                            kpic_flag = 1;
                                            kpic_spec = 1;
                                        }
block_187:
                                        j = 0;
                                        if ((u32) j < strlen(&Karg)) {
                                            do {
                                                (&Karg)[j] = 0x20;
                                                j += 1;
                                            } while ((u32) j < strlen(&Karg));
                                        }
                                        if (Kpass != NULL) {
                                            temp_t4 = (u8) *Kpass;
                                            if ((temp_t4 == 0x2C) && (temp_t4 != 0)) {
loop_192:
                                                Kpass += 1;
                                                if (Kpass != NULL) {
                                                    temp_t2_4 = (u8) *Kpass;
                                                    if (temp_t2_4 == 0x2C) {
                                                        if (temp_t2_4 != 0) {
                                                            goto loop_192;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        temp_t8_2 = (u8) *Kpass;
                                        if ((temp_t8_2 == 0) && (temp_t8_2 != 0x2C)) {

                                        } else {
                                            goto loop_169;
                                        }
                                    } else {
                                        goto block_1537;
                                    }
                                }
                            } else if (argv[var_s0]->unk_2 != 0) {
                                if (strcmp(argv[var_s0], "-KPIC") == 0) {
                                    if (non_shared != 0) {
                                        error(2, NULL, 0, NULL, 0, "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                        kpic_flag = 0;
                                    } else {
                                        kpic_flag = 1;
                                        kpic_spec = 1;
                                    }
                                } else {
                                    addstr(&ldflags, argv[var_s0]);
                                }
                            } else {
                                Kflag += 1;
                                addstr(&fcomflags, argv[var_s0]);
                            }
                        }
                    }
                    break;
                case 0x4C:                          /* switch 1 */
                    if (argv[var_s0].unk_0->unk_2 == 0) {
                        if (((var_s0 + 1) < argc) && (*argv[var_s0].unk_4 != 0x2D) && (isdir(argv[var_s0].unk_4) != 0)) {
                            var_s0 += 1;
                            sp128 = mkstr(argv[var_s0].unk_-4, argv[var_s0].unk_0, NULL);
                            addstr(&ldflags, sp128);
                            addstr(&prelinkerflags, sp128);
                            Lflag = 1;
                        } else {
                            addstr(&prelinkerflags, mkstr("-YB", NULL));
                            goto block_211;
                        }
                    } else {
block_211:
                        Lflag = 1;
                        addstr(&ldflags, argv[var_s0]);
                        addstr(&prelinkerflags, argv[var_s0]);
                    }
                    break;
                case 0x4D:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0x44) {
                        if (strcmp(argv[var_s0] + 3, "update") == 0) {
                            sp15C = argv[var_s0].unk_4;
                            goto block_225;
                        }
                        if (strcmp(argv[var_s0] + 3, "ignore") == 0) {
                            addstr(&ldflags, argv[var_s0]);
                            addstr(&ldflags, argv[var_s0].unk_4);
                            goto block_224;
                        }
                        if (strcmp(argv[var_s0] + 3, "ignoredir") == 0) {
                            addstr(&ldflags, argv[var_s0]);
                            addstr(&ldflags, argv[var_s0].unk_4);
                            goto block_224;
                        }
                        if (strcmp(argv[var_s0] + 3, "target") == 0) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                sp154 = argv[var_s0].unk_4;
                            } else {
                                addstr(&cppflags, argv[var_s0]);
                                addstr(&cppflags, argv[var_s0].unk_4);
block_224:
                            }
block_225:
                            var_s0 += 1;
                            if (var_s0 >= argc) {
                                error(1, NULL, 0, NULL, 0, "%s must be followed by a file name\n", argv[var_s0].unk_-4);
                                exit(2);
                            }
                        } else {
                            goto block_1537;
                        }
                    } else if (argv[var_s0]->unk_2 == 0) {
                        addstr(&cppflags, argv[var_s0]);
                        Eflag += 1;
                        minus_M += 1;
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x4E:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if (compiler == 3) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x4F:                          /* switch 1 */
                    plain_O = 0;
                    if (argv[var_s0]->unk_2 == 0) {
                        if ((xpg_flag != 0) && (var_s1 == 0x66)) {
                            fprintf(__iob + 0x20, "Error: optlevel should be specified\n");
                            exit(1);
                        }
                        Oflag = 2;
                        plain_O = 1;
                        if (plain_g != 0) {
                            Oflag = 1;
                        }
                        if (((var_s0 + 1) < argc) && (argv[var_s0].unk_4->unk_1 == 0) && ((s32) *argv[var_s0].unk_4 >= 0x30) && ((s32) *argv[var_s0].unk_4 < 0x35)) {
                            sp124 = malloc(strlen(argv[var_s0].unk_4) + 3);
                            sp124->unk_0 = 0x2D;
                            sp124->unk_1 = 0x4F;
                            sp124->unk_2 = 0;
                            Oflag = *argv[var_s0].unk_4 - 0x30;
                            addstr(&fcomflags, strcat(sp124, argv[var_s0].unk_4));
                            var_s0 += 1;
                        }
                    } else if (argv[var_s0]->unk_3 == 0) {
                        if (((s32) argv[var_s0]->unk_2 >= 0x30) && ((s32) argv[var_s0]->unk_2 < 0x35)) {
                            temp_t4_2 = argv[var_s0]->unk_2 - 0x30;
                            Oflag = temp_t4_2;
                            if (temp_t4_2 == 3) {
                                temp_t9_2 = "-Olimit";
                                sp120 = temp_t9_2;
                                sp11C = "5000";
                                Gnum = "0";
                                addstr(&umergeflags, temp_t9_2);
                                addstr(&umergeflags, sp11C);
                                addstr(&optflags, sp120);
                                addstr(&optflags, sp11C);
                                addstr(&ddoptflags, sp120);
                                addstr(&ddoptflags, sp11C);
                                addstr(&uopt0flags, sp120);
                                addstr(&uopt0flags, sp11C);
                                addstr(&olimitflags, sp120);
                                addstr(&olimitflags, sp11C);
                            }
                            if ((Oflag >= 3) && (jflag == 0)) {
                                uload = 1;
                            }
                        } else {
                            goto block_1537;
                        }
                    } else if (strcmp(argv[var_s0], "-Olimit") == 0) {
                        addstr(&umergeflags, argv[var_s0]);
                        addstr(&optflags, argv[var_s0]);
                        addstr(&ddoptflags, argv[var_s0]);
                        addstr(&uopt0flags, argv[var_s0]);
                        addstr(&olimitflags, argv[var_s0]);
                        var_s0 += 1;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-Olimit must have an argument\n");
                            exit(2);
                        }
                        var_s2_5 = argv[var_s0];
                        if ((u8) *var_s2_5 != 0) {
                            do {
                                if (!(__ctype[(u8) var_s2_5->unk_0].unk_1 & 4)) {
                                    error(1, NULL, 0, NULL, 0, "non-digit character in -Olimit %s\n", argv[var_s0]);
                                    exit(2);
                                }
                                temp_t1 = var_s2_5->unk_1;
                                var_s2_5 += 1;
                            } while (temp_t1 != 0);
                        }
                        addstr(&umergeflags, argv[var_s0]);
                        addstr(&optflags, argv[var_s0]);
                        addstr(&ddoptflags, argv[var_s0]);
                        addstr(&uopt0flags, argv[var_s0]);
                        addstr(&olimitflags, argv[var_s0]);
                    } else if (strncmp(argv[var_s0], "-OPT:", 5U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-OPT options are ignored\n");
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x50:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        docpp = 1;
                        addstr(&cppflags, argv[var_s0]);
                        if (Eflag == 0) {
                            Pflag += 1;
                        }
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x51:                          /* switch 1 */
                    if ((strcmp(argv[var_s0], "-Qy") != 0) && (strcmp(argv[var_s0], "-Qn") != 0)) {
                        addstr(&cppflags, argv[var_s0]);
                    }
                    break;
                case 0x52:                          /* switch 1 */
                    if (compiler == 3) {
                        addstr(&ratforflags, argv[var_s0] + 2);
                        add_static_opt(argv[var_s0]);
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x53:                          /* switch 1 */
                    if (strncmp(argv[var_s0], "-SWP:", 5U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-SWP options are ignored\n");
                    } else if (argv[var_s0]->unk_2 == 0) {
                        Sflag += 1;
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x54:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        var_s0 += 1;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-T");
                            addstr(&ldflags, argv[var_s0]);
                        } else {
                            error(1, NULL, 0, NULL, 0, "ld requires -T to have an argument\n");
                            exit(2);
                            goto block_278;
                        }
                    } else {
block_278:
                        if (strncmp(argv[var_s0], "-TARG:", 6U) == 0) {
                            error(2, NULL, 0, NULL, 0, "-TARG options are ignored\n");
                        } else if (strncmp(argv[var_s0], "-TENV:", 6U) == 0) {
                            error(2, NULL, 0, NULL, 0, "-TENV options are ignored\n");
                        } else {
                            goto block_1537;
                        }
                    }
                    break;
                case 0x55:                          /* switch 1 */
                    if ((compiler == 3) && (argv[var_s0]->unk_2 == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                        mp_caseflag = 1;
                    } else if ((argv[var_s0].unk_0->unk_2 == 0) && ((var_s0 + 1) < argc)) {
                        sp118 = malloc(strlen(argv[var_s0].unk_4) + 3);
                        sp118->unk_0 = 0x2D;
                        sp118->unk_1 = 0x55;
                        sp118->unk_2 = 0;
                        addstr(&undefineflags, strcat(sp118, argv[var_s0].unk_4));
                        var_s0 += 1;
                    } else {
                        addstr(&undefineflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    }
                    break;
                case 0x56:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        error(2, NULL, 0, NULL, 0, "-V is not supported.\n");
                    } else if (strcmp(argv[var_s0], "-VS") == 0) {
                        var_s0 += 1;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-VS");
                            addstr(&ldflags, argv[var_s0]);
                        } else {
                            error(1, NULL, 0, NULL, 0, "ld requires -VS to have an argument\n");
                            exit(2);
                            goto block_1537;
                        }
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x57:                          /* switch 1 */
                    temp_t7_5 = argv[var_s0];
                    Wpass = temp_t7_5 + 2;
                    if ((u8) temp_t7_5[2] != 0) {
                        temp_t1_2 = argv[var_s0];
                        Warg = temp_t1_2 + 3;
                        if ((u8) temp_t1_2[3] != 0x2C) {
loop_297:
                            temp_s4 = (u8) Warg->unk_0;
                            Warg += 1;
                            if (temp_s4 != 0) {
                                if ((u8) Warg->unk_0 == 0x2C) {
                                    goto block_299;
                                }
                                goto loop_297;
                            }
                            goto block_1537;
                        }
block_299:
                        if ((u8) Warg->unk_0 == 0x2C) {
                            do {
                                Warg->unk_0 = 0;
                                var_s2_6 = Wpass;
                                Warg += 1;
                                if ((u8) *var_s2_6 != 0) {
                                    do {
                                        temp_t4_3 = (u8) var_s2_6->unk_0;
                                        switch (temp_t4_3) { /* switch 2 */
                                        case 0x70:  /* switch 2 */
                                            addstr(&cppflags, Warg);
                                            break;
                                        case 0x4B:  /* switch 2 */
                                            if (compiler == 3) {
                                                addstr(&pfaflags, Warg);
                                            } else if (compiler == 1) {
                                                addstr(&pcaflags, Warg);
                                            } else {
                                                error(1, NULL, 0, NULL, 0, "-WK only valid in FORTRAN or C compilations.\n");
                                                exit(2);
                                            }
                                            break;
                                        case 0x30:  /* switch 2 */
                                        case 0x66:  /* switch 2 */
                                            switch (compiler) { /* switch 6; irregular */
                                            case 2: /* switch 6 */
                                                addstr(&upasflags, Warg);
                                                break;
                                            case 3: /* switch 6 */
                                                addstr(&fcomflags, Warg);
                                                break;
                                            case 5: /* switch 6 */
                                                addstr(&upl1flags, Warg);
                                                break;
                                            case 6: /* switch 6 */
                                                addstr(&ucobflags, Warg);
                                                break;
                                            default: /* switch 6 */
                                                addstr(&ccomflags, Warg);
                                                addstr(&edisonflags, Warg);
                                                break;
                                            }
                                            break;
                                        case 0x77:  /* switch 2 */
                                            addstr(&prelinkerflags, Warg);
                                            break;
                                        case 0x6B:  /* switch 2 */
                                            addstr(&ulpiflags, Warg);
                                            break;
                                        case 0x6A:  /* switch 2 */
                                            addstr(&ujoinflags, Warg);
                                            break;
                                        case 0x75:  /* switch 2 */
                                            addstr(&uldflags, Warg);
                                            break;
                                        case 0x73:  /* switch 2 */
                                            addstr(&usplitflags, Warg);
                                            break;
                                        case 0x6D:  /* switch 2 */
                                            addstr(&umergeflags, Warg);
                                            break;
                                        case 0x71:  /* switch 2 */
                                            addstr(&uopt0flags, Warg);
                                            break;
                                        case 0x64:  /* switch 2 */
                                            addstr(&ddoptflags, Warg);
                                            break;
                                        case 0x32:  /* switch 2 */
                                            addstr(&optflags, Warg);
                                            break;
                                        case 0x6F:  /* switch 2 */
                                            addstr(&optflags, Warg);
                                            if (strstr(Warg, "loopunroll") != 0) {
                                                set_loop_unroll = 1;
                                            }
                                            break;
                                        case 0x63:  /* switch 2 */
                                            addstr(&genflags, Warg);
                                            break;
                                        case 0x61:  /* switch 2 */
                                            addstr(&asflags, Warg);
                                            break;
                                        case 0x62:  /* switch 2 */
                                            addstr(&asflags, Warg);
                                            break;
                                        case 0x6C:  /* switch 2 */
                                            addstr(&ldflags, Warg);
                                            break;
                                        case 0x79:  /* switch 2 */
                                            addstr(&ftocflags, Warg);
                                            break;
                                        case 0x7A:  /* switch 2 */
                                            addstr(&cordflags, Warg);
                                            break;
                                        case 0x4D:  /* switch 2 */
                                            addstr(&mpcflags, Warg);
                                            break;
                                        case 0x78:  /* switch 2 */
                                            temp_t1_3 = Warg->unk_1;
                                            switch (temp_t1_3) { /* switch 3 */
                                            case 0x47: /* switch 3 */
                                                if (Warg->unk_2 == 0) {
                                                    var_s0 += 1;
                                                    if (var_s0 >= argc) {
                                                        error(1, NULL, 0, NULL, 0, "-G requires a decimal number argument\n");
                                                        exit(2);
                                                    }
                                                    if (Oflag < 3) {
                                                        Gnum = argv[var_s0];
                                                    } else {
                                                        Gnum = "0";
                                                    }
                                                } else if (Oflag < 3) {
                                                    Gnum = Warg + 2;
                                                } else {
                                                    Gnum = "0";
                                                }
                                                var_s3 = Gnum;
                                                if (((u8) *var_s3 != 0x2C) && ((u8) *var_s3 != 0)) {
loop_350:
                                                    if (!(__ctype[(u8) *var_s3].unk_1 & 4)) {
                                                        error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", Gnum);
                                                        exit(2);
                                                    }
                                                    if ((u8) *var_s3 != 0x2C) {
                                                        var_s3 += 1;
                                                    }
                                                    if (((u8) *var_s3 != 0x2C) && ((u8) *var_s3 != 0)) {
                                                        goto loop_350;
                                                    }
                                                }
                                                if (Gseen_flag == 0) {
                                                    Gseen_flag = 1;
                                                    relocate_passes(tstring, hstring, NULL);
                                                }
                                                Warg = var_s3;
                                                break;
                                            case 0x76: /* switch 3 */
                                                temp_t6_2 = Warg->unk_2;
                                                if ((temp_t6_2 == 0) || (temp_t6_2 == 0x2C)) {
                                                    vflag = 1;
                                                    if (getenv("ROOTDIR") != NULL) {
                                                        error(2, NULL, 0, NULL, 0, "ROOTDIR env var ignored, use COMP_TARGET_ROOT and COMP_HOST_ROOT\n");
                                                    }
                                                }
                                                break;
                                            case 0x44: /* switch 3 */
                                                if (argv[var_s0].unk_0->unk_2 == 0) {
                                                    if (((var_s0 + 1) < argc) && ((sp114 = strtoul(argv[var_s0].unk_4, &sp110, 0x10), (strlen(argv[var_s0].unk_4) != (sp110 - argv[var_s0].unk_4))) || ((sp114 == 0) && (argv[var_s0].unk_4 == sp110)) || (*argv[var_s0].unk_4 == 0x2D) || (*argv[var_s0].unk_4 == 0x2B))) {
                                                        error(2, NULL, 0, NULL, 0, "-D taken as empty cpp -D, not ld(1) -D hexnum\n");
                                                    } else {
                                                        var_s0 += 1;
                                                        if (var_s0 < argc) {
                                                            addstr(&ldflags, "-D");
                                                            addstr(&ldflags, argv[var_s0]);
                                                        } else {
                                                            error(1, NULL, 0, NULL, 0, "ld requires -D to have an argument\n");
                                                            exit(2);
                                                            goto block_374;
                                                        }
                                                    }
                                                } else {
                                                case 0x62: /* switch 3 */
block_374:
                                                    temp_t4_4 = Warg->unk_2;
                                                    if ((temp_t4_4 == 0) || (temp_t4_4 == 0x2C)) {
                                                        addstr(&ldflags, mkstr(argv[var_s0], ",", Warg, NULL));
                                                    }
                                                }
                                                break;
                                            case 0x4B: /* switch 3 */
                                                if (strcmp(Warg, "-K") != 0) {
                                                    addstr(&ldflags, mkstr(argv[var_s0], ",", Warg, NULL));
                                                } else {
                                                    Kflag += 1;
                                                }
                                                break;
                                            case 0x41: /* switch 3 */
                                                if (Warg->unk_2 == 0) {
                                                    var_s0 += 1;
                                                    if (var_s0 < argc) {
                                                        addstr(&objfiles, "-A");
                                                    }
                                                    error(1, NULL, 0, NULL, 0, "ld requires -A to have an argument\n");
                                                    exit(2);
                                                }
                                                break;
                                            }
                                            break;
                                        default:    /* switch 2 */
                                            error(1, NULL, 0, NULL, 0, "Unknown pass character in %s\n", argv[var_s0]);
                                            exit(2);
                                            break;
                                        }
                                        temp_t5_3 = var_s2_6->unk_1;
                                        var_s2_6 += 1;
                                    } while (temp_t5_3 != 0);
                                }
                                temp_t4_5 = (u8) Warg->unk_0;
                                if ((temp_t4_5 != 0x2C) && (temp_t4_5 != 0)) {
loop_389:
                                    Warg += 1;
                                    temp_t8_3 = (u8) Warg->unk_0;
                                    if (temp_t8_3 != 0x2C) {
                                        if (temp_t8_3 != 0) {
                                            goto loop_389;
                                        }
                                    }
                                }
                            } while ((u8) Warg->unk_0 == 0x2C);
                        }
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x58:                          /* switch 1 */
                    if (compiler == 1) {
                        if (strcmp(argv[var_s0], "-Xcpluscomm") == 0) {
                            addstr(&ccomflags, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-Xt") == 0) {
                            stdflag = 0;
                            addstr(&ccomflags, "-std0");
                        } else if (strcmp(argv[var_s0], "-Xc") == 0) {
                            stdflag = 1;
                            addstr(&ccomflags, "-std1");
                        } else if (strcmp(argv[var_s0], "-Xa") == 0) {
                            stdflag = 1;
                            addstr(&ccomflags, "-std");
                        } else {
                            goto block_402;
                        }
                    } else {
block_402:
                        if (strcmp(argv[var_s0], "-Xprototypes") == 0) {
                            addstr(&ccomflags, argv[var_s0]);
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                            if ((strcmp(argv[var_s0], "-Xndlocaldata") == 0) || (strcmp(argv[var_s0], "-Xlocaldata") == 0) || (strcmp(argv[var_s0], "-Xndblock") == 0) || (strcmp(argv[var_s0], "-Xblock") == 0) || (strcmp(argv[var_s0], "-Xalignbss") == 0) || (strcmp(argv[var_s0], "-Xnoalignbss") == 0) || (strcmp(argv[var_s0], "-Xcachesize") == 0) || (strcmp(argv[var_s0], "-Xcachelinesize") == 0) || (strcmp(argv[var_s0], "-Xdefmovemax") == 0) || (strcmp(argv[var_s0], "-Xsetalign") == 0) || (strcmp(argv[var_s0], "-Xblockrange") == 0)) {
                                var_s0 += 1;
                                if (var_s0 < argc) {
                                    addstr(&ldflags, argv[var_s0]);
                                } else {
                                    error(1, NULL, 0, NULL, 0, "%s must have an argument\n", argv[var_s0].unk_-4);
                                }
                            }
                        }
                    }
                    break;
                case 0x61:                          /* switch 1 */
                    if ((compiler == 1) && (strcmp(argv[var_s0], "-all") == 0)) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (strcmp(argv[var_s0], "-auto_include") == 0)) {
                        auto_template_include = 1;
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (strcmp(argv[var_s0], "-anach") == 0)) {
                        anachronisms = 1;
                    } else if (strcmp(argv[var_s0], "-ansi") == 0) {
                        if (compchoice == 1) {
                            compchoice = 0;
                        }
                        ansichoice = 1;
                        if (cppchoice != 1) {
                            cppchoice = 3;
                        }
                        relocate_passes("p", NULL, NULL);
                        add_static_opt(argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-ansiposix") == 0) {
                        if (compchoice == 1) {
                            compchoice = 0;
                        }
                        ansichoice = 2;
                        if (cppchoice != 1) {
                            cppchoice = 3;
                        }
                        relocate_passes("p", NULL, NULL);
                        add_static_opt(argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-abi") == 0) {
                        abi_flag = 1;
                        addstr(&cppflags, "-D_ABI_SOURCE");
                        addstr(&asflags, "-abi");
                        addstr(&ldflags, "-abi");
                    } else if (strcmp(argv[var_s0], "-acpp") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        } else {
                            cppchoice = 1;
                            acpp = 1;
                            relocate_passes("p", NULL, NULL);
                        }
                    } else {
                        if (strcmp(argv[var_s0], "-align8") == 0) {
                            align = 8;
                            if (compiler == 3) {
                                align_common += 1;
                            }
                            goto block_464;
                        }
                        if (strcmp(argv[var_s0], "-align16") == 0) {
                            align = 0x10;
                            if (compiler == 3) {
                                align_common += 1;
                            }
                            goto block_464;
                        }
                        if (strcmp(argv[var_s0], "-align32") == 0) {
                            align = 0x20;
                            if (compiler == 3) {
                                align_common += 1;
                            }
                            goto block_464;
                        }
                        if (strcmp(argv[var_s0], "-align64") == 0) {
                            align = 0x40;
                            if (compiler == 3) {
                                align_common += 1;
                            }
                            goto block_464;
                        }
                        if (strcmp(argv[var_s0], "-align_common") == 0) {
                            align_common = 1;
                        } else {
block_464:
                            if (compiler == 3) {
                                if ((strcmp(argv[var_s0], "-align8") == 0) || (strcmp(argv[var_s0], "-align16") == 0) || (strcmp(argv[var_s0], "-align32") == 0) || (strcmp(argv[var_s0], "-align64") == 0)) {
                                    addstr(&fcomflags, argv[var_s0]);
                                    addstr(&genflags, argv[var_s0]);
                                    addstr(&asflags, argv[var_s0]);
                                } else if (strcmp(argv[var_s0], "-automatic") == 0) {
                                    automaticflag = 1;
                                } else {
                                    goto block_472;
                                }
                            } else {
block_472:
                                if ((compiler == 6) && (strcmp(argv[var_s0], "-ansi") == 0)) {
                                    ansiflag = 1;
                                } else if ((compiler == 2) && (strcmp(argv[var_s0], "-apc") == 0)) {
                                    addstr(&upasflags, argv[var_s0]);
                                    addstr(&genflags, argv[var_s0]);
                                } else if (strcmp(argv[var_s0], "-align8") == 0) {
                                    align = 8;
                                    alignarg = savestr(argv[var_s0], 0U);
                                } else if (strcmp(argv[var_s0], "-align16") == 0) {
                                    align = 0x10;
                                    alignarg = savestr(argv[var_s0], 0U);
                                } else if (strcmp(argv[var_s0], "-align32") == 0) {
                                    align = 0x20;
                                    alignarg = savestr(argv[var_s0], 0U);
                                } else if (strcmp(argv[var_s0], "-align64") == 0) {
                                    align = 0x40;
                                    alignarg = savestr(argv[var_s0], 0U);
                                } else if (strcmp(argv[var_s0], "-ajeop") == 0) {
                                    addstr(&ldflags, argv[var_s0]);
                                    addstr(&cordflags, "-no_r4000_fix");
                                } else {
                                    goto block_1537;
                                }
                            }
                        }
                    }
                    break;
                case 0x62:                          /* switch 1 */
                    if ((argv[var_s0]->unk_2 == 0) || (strcmp(argv[var_s0], "-bestGnum") == 0)) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-bytereclen") == 0) {
                        addstr(&fcomflags, argv[var_s0]);
                    } else {
                        if (strcmp(argv[var_s0], "-backslash") == 0) {
                            mp_backslashflag = 1;
                            docpp = 0;
                        }
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    }
                    break;
                case 0x63:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        cflag += 1;
                    } else if (strcmp(argv[var_s0], "-cckr") == 0) {
                        ansichoice = 0;
                        if (cppchoice != 1) {
                            cppchoice = 2;
                        }
                        add_static_opt(argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-cfe") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        } else {
                            compchoice = 3;
                            relocate_passes("p", NULL, NULL);
                        }
                    } else if (strcmp(argv[var_s0], "-common") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        } else {
                            addstr(&accomflags, "-Xcommon");
                        }
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (strcmp(argv[var_s0], "-cfront") == 0)) {
                        cfront_compatible = 1;
                    } else if (strcmp(argv[var_s0], "-cachesz") == 0) {
                        addstr(&ddoptflags, argv[var_s0]);
                        var_s0 += 1;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-cachesz must have an argument\n");
                            exit(2);
                        }
                        var_s2_7 = Gnum;
                        if ((u8) *var_s2_7 != 0) {
                            do {
                                if (!(__ctype[(u8) var_s2_7->unk_0].unk_1 & 4)) {
                                    error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", argv[var_s0]);
                                    exit(2);
                                }
                                temp_t5_4 = var_s2_7->unk_1;
                                var_s2_7 += 1;
                            } while (temp_t5_4 != 0);
                        }
                        addstr(&ddoptflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-cplus") == 0) {
                        cplusflag = 1;
                        addstr(&ccomflags, "-cplus");
                    } else if (strcmp(argv[var_s0], "-cpp") == 0) {
                        error(2, NULL, 0, NULL, 0, "-cpp is default\n");
                    } else if (strcmp(argv[var_s0], "-cord") == 0) {
                        cordflag = 1;
                    } else if (strcmp(argv[var_s0], "-coff") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                        coff_spec = 1;
                        if (default_call_shared == 1) {
                            if (non_shared == 0) {
                                old_non_shared = 1;
                                non_shared = 1;
                            }
                            default_call_shared = 0;
                            call_shared = 0;
                        }
                    } else if ((strcmp(argv[var_s0], "-call_shared") == 0) && ((strcmp(argv[var_s0], "-count") == 0) || (strcmp(argv[var_s0], "-countall") == 0))) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-call_shared") == 0) {
                        non_shared = 0;
                        call_shared = 1;
                    } else if (strcmp(argv[var_s0], "-crt0") == 0) {
                        CRTX = "crt0.o";
                        MCRTX = "mcrt0.o";
                        crtn_required = 0;
                        relocate_passes("r", NULL, NULL);
                    } else if (strcmp(argv[var_s0], "-crt1") == 0) {
                        if ((ansichoice == 1) || (ansichoice == 2)) {
                            CRTX = "acrt1.o";
                        } else {
                            CRTX = "crt1.o";
                        }
                        MCRTX = "mcrt1.o";
                        crtn_required = 1;
                        relocate_passes("r", NULL, NULL);
                    } else if ((compiler == 2) && (strcmp(argv[var_s0], "-casesense") == 0)) {
                        addstr(&upasflags, argv[var_s0]);
                    } else if ((compiler == 3) && (strcmp(argv[var_s0], "-change_const") == 0)) {
                        addstr(&fcomflags, "-change_const");
                    } else if ((compiler == 3) && ((strcmp(argv[var_s0], "-col120") == 0) || (strcmp(argv[var_s0], "-col72") == 0) || (strcmp(argv[var_s0], "-chararg1") == 0) || (strcmp(argv[var_s0], "-chunk") == 0) || (strcmp(argv[var_s0], "-check_bounds") == 0))) {
                        if (strcmp(argv[var_s0], "-col120") == 0) {
                            mp_col120flag = 1;
                        }
                        if (strcmp(argv[var_s0], "-check_bounds") == 0) {
                            addstr(&fcomflags, "-C");
                        } else if (strncmp(argv[var_s0], "-chunk=", strlen("-chunk=")) == 0) {
                            sp10C = &argv[var_s0][strlen("-chunk=")];
                            if ((u8) *sp10C != 0) {
                                do {
                                    temp_t2_5 = &__ctype[(u8) *sp10C];
                                    if (temp_t2_5->unk_1 & 1) {
                                        *sp10C = (s8) temp_t2_5->unk_102;
                                    } else {
                                        *sp10C = (s8) (u8) *sp10C;
                                    }
                                    sp10C += 1;
                                } while ((u8) *sp10C != 0);
                            }
                            addstr(&fcomflags, mkstr("-mp_chunk=", &argv[var_s0][strlen("-chunk=")], NULL));
                        } else {
                            addstr(&fcomflags, argv[var_s0]);
                            if (strncmp(argv[var_s0], "-col", 4U) == 0) {
                                add_static_opt(argv[var_s0]);
                            }
                        }
                    } else if ((compiler == 6) && (strcmp(argv[var_s0], "-comp_trunc") == 0)) {
                        addstr(&ucobflags, argv[var_s0]);
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-check_registry") == 0)) {
                        var_s0 += 1;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-check_registry requires a filename argument\n");
                            exit(2);
                        }
                        addstr(&ldflags, argv[var_s0].unk_-4);
                        addstr(&ldflags, argv[var_s0]);
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x64:                          /* switch 1 */
                    if ((compiler == 1) && (strcmp(argv[var_s0], "-dollar") == 0)) {
                        addstr(&pcaflags, "-dollar");
                        addstr(&mpcflags, "-dollar");
                        addstr(&soptflags, "-dollar");
                        addstr(&cfeflags, "-Xdollar");
                        add_static_opt(argv[var_s0]);
                        dollar_sign += 1;
                    } else if (argv[var_s0]->unk_2 == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-ddoptinfo") == 0) {
                        ddoptinfo = 1;
                    } else if ((strcmp(argv[var_s0], "-dy") == 0) || (strcmp(argv[var_s0], "-dn") == 0)) {
                        if (G_flag != 0) {
                            error(1, NULL, 0, NULL, 0, "-dn can not be used with -G \n");
                            exit(2);
                        }
                        dn_flag = 1;
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-ddopt") == 0) {
                        ddoptflag = 1;
                    } else if ((compiler == 3) && (strcmp(argv[var_s0], "-d_lines") == 0)) {
                        mp_dlinesflag = 1;
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    } else if ((compiler == 5) && (strcmp(argv[var_s0], "-defext") == 0)) {
                        addstr(&ulpiflags, argv[var_s0]);
                    } else if ((compiler == 6) && ((strcmp(argv[var_s0], "-dline") == 0) || (strcmp(argv[var_s0], "-defext") == 0))) {
                        addstr(&ucobflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-delay_load") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-default_delay_load") == 0)) {
                        addstr(&ldflags, argv[var_s0]);
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x65:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-excpt") == 0) {
                        error(1, NULL, 0, NULL, 0, "-excpt is not supported in svr4 env.\n");
                        exit(2);
                    }
                    if (compiler == 1) {
                        if (strcmp(argv[var_s0], "-elf") == 0) {
                            addstr(&ldflags, argv[var_s0]);
                        } else if ((strcmp(argv[var_s0], "-export") == 0) || (strcmp(argv[var_s0], "-exports") == 0)) {
                            addstr(&objfiles, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-exported_symbol") == 0) {
                            var_s0 += 1;
                            if ((var_s0 >= argc) || ((u8) *argv[var_s0] == 0x2D)) {
                                error(1, NULL, 0, NULL, 0, "-exported_symbol requires a symbol argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0].unk_-4);
                            addstr(&ldflags, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-exports_file") == 0) {
                            var_s0 += 1;
                            if ((var_s0 >= argc) || ((u8) *argv[var_s0] == 0x2D)) {
                                error(1, NULL, 0, NULL, 0, "-exports_file requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0].unk_-4);
                            addstr(&ldflags, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-exclude") == 0) {
                            var_s0 += 1;
                            if ((var_s0 >= argc) || ((u8) *argv[var_s0] == 0x2D)) {
                                error(1, NULL, 0, NULL, 0, "-exclude requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&objfiles, argv[var_s0].unk_-4);
                            addstr(&objfiles, argv[var_s0]);
                        } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (strcmp(argv[var_s0], "-exceptions") == 0)) {
                            if ((compiler != 1) || (c_compiler_choice != 3)) {
                                exception_handling = 1;
                                relocate_passes("f", NULL, NULL);
                                if (access(cfe, 0x10) == -1) {
                                    exception_handling = 0;
                                    relocate_passes("f", NULL, NULL);
                                    goto block_1537;
                                }
                            } else {
                                goto block_1537;
                            }
                        } else {
                            goto block_643;
                        }
                    } else {
block_643:
                        if (argv[var_s0]->unk_2 == 0) {
                            var_s0 += 1;
                            if (var_s0 < argc) {
                                addstr(&ldflags, "-e");
                                addstr(&ldflags, argv[var_s0]);
                            } else {
                                error(1, NULL, 0, NULL, 0, "ld requires -e to have an argument\n");
                                exit(2);
                                goto block_647;
                            }
                        } else {
block_647:
                            if (strcmp(argv[var_s0], "-exact_version") == 0) {
                                addstr(&ldflags, argv[var_s0]);
                            } else if (strcmp(argv[var_s0], "-elf") == 0) {
                                elfflag = 1;
                                elf_spec = 1;
                                addstr(&asflags, argv[var_s0]);
                                addstr(&ldflags, argv[var_s0]);
                            } else if ((compiler == 3) && (strcmp(argv[var_s0], "-extend_source") == 0)) {
                                mp_extendflag = 1;
                                addstr(&fcomflags, argv[var_s0]);
                                add_static_opt(argv[var_s0]);
                            } else if ((compiler == 3) && (strcmp(argv[var_s0], "-expand_include") == 0)) {
                                addstr(&fcomflags, argv[var_s0]);
                            } else if (strncmp(argv[var_s0], "-edit", 5U) == 0) {
                                if (argv[var_s0]->unk_5 == 0) {
                                    edit_cnt_max = 0x100;
                                } else if ((__ctype[argv[var_s0]->unk_5].unk_1 & 4) && (argv[var_s0]->unk_6 == 0)) {
                                    edit_cnt_max = argv[var_s0]->unk_5 - 0x30;
                                } else {
                                    error(1, NULL, 0, NULL, 0, "the correct -edit option sybtax is -edit[0-9]\n");
                                    exit(2);
                                }
                                editflag = 1;
                                editor = getenv("EDITOR");
                                if (editor != NULL) {
                                    var_s2_8 = editor;
                                    if (strlen(var_s2_8) >= 5U) {
loop_666:
                                        if (strncmp(var_s2_8, "emacs", 5U) == 0) {
                                            editflag = 2;
                                        } else {
                                            var_s2_8 += 1;
                                            if (strlen(var_s2_8) >= 5U) {
                                                goto loop_666;
                                            }
                                        }
                                    }
                                }
                                if ((editflag == 1) && (editor == NULL)) {
                                    editor = "vi";
                                }
                                xserver = getenv("DISPLAY");
                                if ((ioctl(2, 0x40047477, &sp108) == 0) && (getpgrp() == sp108) && (xserver == 0)) {
                                    editflag = 0;
                                    error(2, NULL, 0, NULL, 0, "%s ignored for background compile in non-X environment\n", argv[var_s0]);
                                }
                            } else {
                                goto block_1537;
                            }
                        }
                    }
                    break;
                case 0x66:                          /* switch 1 */
                    if ((strcmp(argv[var_s0], "-full_transtive_link") == 0) || (strcmp(argv[var_s0], "-full_transitive_link") == 0)) {
                        full_transitive_link = 1;
                        transitive_link = 0;
                        no_transitive_link = 0;
                    } else if (strcmp(argv[var_s0], "-feedback") == 0) {
                        var_s0 += 1;
                        if (var_s0 < argc) {
                            addstr(&feedlist, argv[var_s0]);
                        } else {
                            error(1, NULL, 0, NULL, 0, "-feedback must have an argument\n");
                            exit(2);
                            goto block_683;
                        }
                    } else {
block_683:
                        if (strcmp(argv[var_s0], "-fullasopt") == 0) {
                            fullasoptflag = 1;
                        } else if ((compiler == 1) && (strcmp(argv[var_s0], "-force_load") == 0)) {
                            addstr(&objfiles, argv[var_s0]);
                        } else if ((strcmp(argv[var_s0], "-fullwarn") == 0) && (fullwarn = 1, (compiler == 1))) {
                            addstr(&accomflags, "-Xfullwarn");
                            addstr(&cfeflags, "-verbose");
                            addstr(&cfeflags, "-wimplicit");
                        } else if (strcmp(argv[var_s0], "-framepointer") == 0) {
                            if (compiler == 1) {
                                addstr(&ccomflags, argv[var_s0]);
                            } else if (compiler == 2) {
                                addstr(&upasflags, argv[var_s0]);
                            } else if (compiler == 3) {
                                addstr(&fcomflags, argv[var_s0]);
                            } else {
                                goto block_1537;
                            }
                        } else if ((compiler == 1) && (strcmp(argv[var_s0], "-float") == 0)) {
                            addstr(&pcaflags, "-float");
                            addstr(&soptflags, "-float");
                            addstr(&ccomflags, "-Xfloat");
                        } else if (((compiler != 4) && (compiler != 2)) || (strcmp(argv[var_s0], "-float") != 0)) {
                            if (compiler == 6) {
                                if (strcmp(argv[var_s0], "-fsc74") == 0) {
                                    addstr(&ucobflags, argv[var_s0]);
                                } else if (argv[var_s0]->unk_2 == 0) {
                                    var_s0 += 1;
                                    if ((var_s0 < argc) && (addstr(&ucobflags, "-f"), (argv[var_s0]->unk_1 == 0)) && ((s32) (u8) *argv[var_s0] >= 0x31) && ((s32) (u8) *argv[var_s0] < 0x35)) {
                                        addstr(&ucobflags, argv[var_s0]);
                                    } else {
                                        error(1, NULL, 0, NULL, 0, "-f requires an argument of 1, 2, 3 or 4\n");
                                        exit(2);
                                        goto block_714;
                                    }
                                } else {
                                    goto block_1537;
                                }
                            } else {
block_714:
                                if (argv[var_s0]->unk_2 == 0) {
                                    var_s0 += 1;
                                    if (var_s0 < argc) {
                                        addstr(&ldflags, "-f");
                                        addstr(&ldflags, argv[var_s0]);
                                    } else {
                                        error(1, NULL, 0, NULL, 0, "ld requires -f to have an argument\n");
                                        exit(2);
                                        goto block_1537;
                                    }
                                } else {
                                    goto block_1537;
                                }
                            }
                        }
                    }
                    break;
                case 0x67:                          /* switch 1 */
                    plain_g = 0;
                    if (argv[var_s0]->unk_2 == 0) {
                        gflag = 2;
                        plain_g = 1;
                        if (plain_O != 0) {
                            Oflag = 1;
                        }
                    } else if ((argv[var_s0]->unk_3 == 0) && ((s32) argv[var_s0]->unk_2 >= 0x30) && ((s32) argv[var_s0]->unk_2 < 0x34)) {
                        temp_t6_3 = argv[var_s0]->unk_2 - 0x30;
                        gflag = temp_t6_3;
                        if (temp_t6_3 == 2) {
                            plain_g = 1;
                            if (plain_O != 0) {
                                Oflag = 1;
                            }
                        }
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x68:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-hostcache") == 0) {
                        addstr(&ddoptflags, argv[var_s0]);
                    } else if (strncmp(argv[var_s0], "-help", 5U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-help is ignored.\n");
                    } else if (compiler == 1) {
                        if (strcmp(argv[var_s0], "-hides") == 0) {
                            addstr(&objfiles, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-hidden_symbol") == 0) {
                            var_s0 += 1;
                            if ((var_s0 >= argc) || ((u8) *argv[var_s0] == 0x2D)) {
                                error(1, NULL, 0, NULL, 0, "-hidden_symbol requires a symbol argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0].unk_-4);
                            addstr(&ldflags, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-hides_file") == 0) {
                            var_s0 += 1;
                            if ((var_s0 >= argc) || ((u8) *argv[var_s0] == 0x2D)) {
                                error(1, NULL, 0, NULL, 0, "-hides_file requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0].unk_-4);
                            addstr(&ldflags, argv[var_s0]);
                        } else {
                            goto block_744;
                        }
                    } else {
block_744:
                        temp_t5_5 = argv[var_s0] + 2;
                        hstring = temp_t5_5;
                        if (hstring[strlen(temp_t5_5)].unk_-1 != 0x2F) {
                            hstring = mkstr(hstring, "/", NULL);
                        }
                    }
                    break;
                case 0x69:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        var_s0 += 1;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-i");
                            addstr(&ldflags, argv[var_s0]);
                        } else {
                            error(1, NULL, 0, NULL, 0, "ld requires -i to have an argument\n");
                            exit(2);
                            goto block_750;
                        }
                    } else {
block_750:
                        if (strcmp(argv[var_s0], "-inline_to") == 0) {
                            addstr(&umergeflags, argv[var_s0]);
                            var_s0 += 1;
                            if (var_s0 >= argc) {
                                error(1, NULL, 0, NULL, 0, "-inline_to must have an argument\n");
                                exit(2);
                            }
                            var_s2_9 = Gnum;
                            if ((u8) *var_s2_9 != 0) {
                                do {
                                    if (!(__ctype[(u8) var_s2_9->unk_0].unk_1 & 4)) {
                                        error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", argv[var_s0]);
                                        exit(2);
                                    }
                                    temp_t7_6 = var_s2_9->unk_1;
                                    var_s2_9 += 1;
                                } while (temp_t7_6 != 0);
                            }
                            addstr(&umergeflags, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-ignore_unresolved") == 0) {
                            ignore_unresolved_flag = 1;
                        } else if (strcmp(argv[var_s0], "-ignore_minor") == 0) {
                            addstr(&objfiles, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-irix4") == 0) {
                            irix4 = 1;
                            comp_host_root = "/usr/irix4/";
                            Gnum = "8";
                            systype = "";
                            elfflag = 0;
                            svr4_systype = 0;
                            kpic_flag = 0;
                            default_call_shared = 0;
                            call_shared = 0;
                            non_shared = 0;
                            old_non_shared = 0;
                            mips_abi = 0;
                            relocate_passes("pKfjrsulmvocabtyz", NULL, NULL);
                            add_static_opt(argv[var_s0]);
                        } else if (((compiler == 3) && ((strcmp(argv[var_s0], "-i2") == 0) || (strcmp(argv[var_s0], "-i4") == 0))) || (strcmp(argv[var_s0], "-i8") == 0)) {
                            if ((argv[var_s0]->unk_2 == 0x32) || (argv[var_s0]->unk_2 == 0x38)) {
                                mp_i2flag = 1;
                            }
                            addstr(&fcomflags, argv[var_s0]);
                        } else if (compiler == 5) {
                            if (strcmp(argv[var_s0], "-ipath") == 0) {
                                var_s0 += 1;
                                if (var_s0 < argc) {
                                    addstr(&upl1flags, "-ipath");
                                    addstr(&upl1flags, argv[var_s0]);
                                } else {
                                    error(1, NULL, 0, NULL, 0, "-ipath must have an argument\n");
                                    exit(2);
                                    goto block_777;
                                }
                            } else {
block_777:
                                if (strcmp(argv[var_s0], "-isuffix") == 0) {
                                    var_s0 += 1;
                                    if (var_s0 < argc) {
                                        addstr(&upl1flags, "-isuffix");
                                        addstr(&upl1flags, argv[var_s0]);
                                    } else {
                                        error(1, NULL, 0, NULL, 0, "-isuffix must have an argument\n");
                                        exit(2);
                                        goto block_1537;
                                    }
                                } else {
                                    goto block_1537;
                                }
                            }
                        } else {
                            goto block_1537;
                        }
                    }
                    break;
                case 0x6A:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        jflag += 1;
                        uload = 0;
                    } else if (strcmp(argv[var_s0], "-jalr") == 0) {
                        addstr(&genflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-jmpopt") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x6B:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-keep") == 0) {
                        Kflag += 1;
                    } else if (strcmp(argv[var_s0], "-kpicopt") == 0) {
                        kpicopt_flag = 1;
                    } else {
                        temp_s4_2 = argv[var_s0]->unk_2;
                        switch (temp_s4_2) {        /* switch 7; irregular */
                        case 0x6F:                  /* switch 7 */
                            var_s0 += 1;
                            if ((var_s0 < argc) && ((temp_t7_7 = argv[var_s0], uoutfile = temp_t7_7, var_s1 = getsuf(temp_t7_7) & 0xFF, (var_s1 == 0x63)) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) || (var_s1 == 0x72) || (var_s1 == 0x65) || (var_s1 == 6) || (var_s1 == 0x73) || (var_s1 == 1) || (var_s1 == 2))) {
                                error(1, NULL, 0, NULL, 0, "-ko would overwrite %s\n", argv[var_s0]);
                                exit(2);
                            }
                            break;
                        case 0x70:                  /* switch 7 */
                            var_s0 += 1;
                            if (var_s0 < argc) {
                                addstr(&uldflags, "-kp");
                                addstr(&uldflags, argv[var_s0]);
                            }
                            break;
                        case 0x75:                  /* switch 7 */
                            var_s0 += 1;
                            if (var_s0 < argc) {
                                addstr(&uldflags, "-ku");
                                addstr(&uldflags, argv[var_s0]);
                            }
                            break;
                        default:                    /* switch 7 */
                            addstr(&ufiles, argv[var_s0]);
                            break;
                        }
                    }
                    break;
                case 0x6C:                          /* switch 1 */
                    if (strcmp("isting", argv[var_s0] + 2) == 0) {
                        addstr(&fcomflags, argv[var_s0]);
                    } else {
                        if ((argv[var_s0]->unk_2 == 0x6D) && (argv[var_s0]->unk_3 == 0)) {
                            lmflag += 1;
                            goto block_823;
                        }
                        if ((argv[var_s0].unk_0->unk_2 == 0) && ((var_s0 + 1) < argc)) {
                            sp104 = malloc(strlen(argv[var_s0].unk_4) + 3);
                            sp104->unk_0 = 0x2D;
                            sp104->unk_1 = 0x6C;
                            sp104->unk_2 = 0;
                            if (xpg_flag != 0) {
                                addstr(&dashlfiles, strcat(sp104, argv[var_s0].unk_4));
                            } else {
                                addstr(&objfiles, strcat(sp104, argv[var_s0].unk_4));
                            }
                            var_s0 += 1;
                        } else {
block_823:
                            if (xpg_flag != 0) {
                                addstr(&dashlfiles, argv[var_s0]);
                            } else {
                                addstr(&objfiles, argv[var_s0]);
                            }
                            if (strcmp(argv[var_s0], "-lgl_s") == 0) {
                                B_1000ED2C += 1;
                                addstr(&objfiles, "-lX11_s");
                            }
                            if (strcmp(argv[var_s0], "-lc_s") == 0) {
                                B_1000ED30 += 1;
                            }
                        }
                    }
                    break;
                case 0x6D:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-multigot") == 0) {
                        addstr(&nldflags, argv[var_s0]);
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-mp") == 0)) {
                        cmp_flag |= 0x10008;
                        if (Bflag != 0) {
                            error(1, NULL, 0, NULL, 0, "'-mp' must preceed any -B flags.\n");
                            exit(2);
                        }
                        relocate_passes("fY", NULL, NULL);
                    } else if (argv[var_s0]->unk_2 == 0) {
                        if ((compiler == 4) || (compiler == 3)) {
                            mflag += 1;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                        if (compiler == 3) {
                            add_static_opt(argv[var_s0]);
                        }
                    } else if (compiler == 6) {
                        if (strcmp(argv[var_s0], "-mfext") == 0) {
                            addstr(&ucobflags, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-map") == 0) {
                            addstr(&ucobflags, argv[var_s0]);
                        } else {
                            goto block_849;
                        }
                    } else {
block_849:
                        if (strcmp(argv[var_s0], "-mips1") == 0) {
                            chip_targ = 0;
                            mips1flag = 1;
                            mips2flag = 0;
                            if (dwopcodeflag != 0) {
                                error(1, NULL, 0, NULL, 0, "can't mix -mips1 with -dwopcode\n");
                                exit(2);
                            }
                            if (mips2_spec_flag != 0) {
                                error(2, NULL, 0, NULL, 0, "-mips1 conflicts with -mips2; using last value (mips1)\n");
                                mips2_spec_flag = 0;
                            }
                        } else if (strcmp(argv[var_s0], "-mips2") == 0) {
                            if ((mips1flag != 0) || (mips3flag != 0)) {
                                error(2, NULL, 0, NULL, 0, "-mips2 conflicts with -mips1; using last value (mips2)\n");
                            }
                            mips1flag = 0;
                            mips2flag = 1;
                            mips2_spec_flag = 1;
                            relocate_passes("M", NULL, NULL);
                        } else if (strcmp(argv[var_s0], "-mips3") == 0) {
                            mips1flag = 0;
                            mips2flag = 0;
                            if (mips2_spec_flag != 0) {
                                error(1, NULL, 0, NULL, 0, "can't mix -mips3 with -mips[1,2]\n");
                                exit(2);
                            }
                            if ((compiler == 4) || (compiler == 1)) {
                                error(2, NULL, 0, NULL, 0, "-mips3 should not be used for ucode 32-bit compiles\n");
                            } else {
                                error(1, NULL, 0, NULL, 0, "-mips3 cannot be used for ucode 32-bit compiles\n");
                                exit(2);
                            }
                            chip_targ = 2;
                            mips3flag = 1;
                            dwopcodeflag = 1;
                            relocate_passes("M", NULL, NULL);
                            if (non_shared_emitted == 0) {
                                addstr(&ldflags, "-non_shared");
                                addstr(&cfeflags, "-non_shared");
                                non_shared_emitted = 1;
                            }
                            addstr(&ccomflags, argv[var_s0]);
                            addstr(&upasflags, argv[var_s0]);
                            addstr(&fcomflags, argv[var_s0]);
                            addstr(&upl1flags, argv[var_s0]);
                            addstr(&ucobflags, argv[var_s0]);
                            addstr(&ulpiflags, argv[var_s0]);
                            addstr(&eflflags, argv[var_s0]);
                            addstr(&ratforflags, argv[var_s0]);
                            addstr(&ddoptflags, argv[var_s0]);
                            addstr(&optflags, argv[var_s0]);
                            addstr(&genflags, argv[var_s0]);
                            addstr(&asflags, argv[var_s0]);
                            addstr(&ldflags, argv[var_s0]);
                            addstr(&ftocflags, argv[var_s0]);
                        } else {
                            if (strcmp(argv[var_s0], "-mips4") == 0) {
                                error(1, NULL, 0, NULL, 0, "-mips4 cannot be used for ucode 32-bit compiles\n");
                                exit(2);
                            }
                            if (compiler == 3) {
                                if ((argv[var_s0]->unk_2 == 0x70) && (argv[var_s0]->unk_3 == 0)) {
                                    mp_flag |= 0x10000;
                                } else if (strncmp(argv[var_s0], "-mp_keep", strlen("-mp_keep")) == 0) {
                                    if (argv[var_s0]->unk_8 != 0) {
                                        error(1, NULL, 0, NULL, 0, " Unknown flag: %s\n", argv[var_s0]);
                                        exit(2);
                                    }
                                    mp_flag |= 0x10000;
                                    showdirt_flag = 1;
                                } else if (strncmp(argv[var_s0], "-mp_schedtype=", strlen("-mp_schedtype=")) == 0) {
                                    sp100 = &argv[var_s0][strlen("-mp_schedtype=")];
                                    if ((u8) *sp100 != 0) {
                                        do {
                                            temp_t8_4 = &__ctype[(u8) *sp100];
                                            if (temp_t8_4->unk_1 & 1) {
                                                *sp100 = (s8) temp_t8_4->unk_102;
                                            } else {
                                                *sp100 = (s8) (u8) *sp100;
                                            }
                                            sp100 += 1;
                                        } while ((u8) *sp100 != 0);
                                    }
                                    addstr(&fcomflags, argv[var_s0]);
                                } else {
                                    goto block_1537;
                                }
                            } else {
                                goto block_1537;
                            }
                        }
                    }
                    break;
                case 0x6E:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-nokpicopt") == 0) {
                        nokpicopt_flag = 1;
                    } else if (strcmp(argv[var_s0], "-no_unresolved") == 0) {
                        no_unresolved_flag = 1;
                    } else if (strcmp(argv[var_s0], "-no_transitive_link") == 0) {
                        transitive_link = 0;
                        full_transitive_link = 0;
                        no_transitive_link = 1;
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (strcmp(argv[var_s0], "-no_exceptions") == 0)) {
                        if ((compiler != 1) || (c_compiler_choice != 3)) {
                            exception_handling = 0;
                            relocate_passes("f", NULL, NULL);
                        } else {
                            goto block_1537;
                        }
                    } else if (strcmp(argv[var_s0], "-new_ld") == 0) {
                        if (D_1000BF94 != 0) {
                            error(1, NULL, 0, NULL, 0, "malformed or unknown option: -new_ld\n");
                            exit(2);
                        } else if ((compiler == 1) && (c_compiler_choice == 3)) {
                            error(1, NULL, 0, NULL, 0, "-new_ld not supported for DCC\n");
                            exit(2);
                        } else {
                            LD = "ld";
                            D_1000BF90 = 0;
                        }
                        relocate_passes("l", NULL, NULL);
                    } else if (strcmp(argv[var_s0], "-noinline") == 0) {
                        addstr(&umergeflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-nouopt0") == 0) {
                        uopt0flag = 0;
                    } else if (strcmp(argv[var_s0], "-noaliasok") == 0) {
                        noaliasokflag = 1;
                    } else if (strcmp(argv[var_s0], "-nostdinc") == 0) {
                        emptyIflag = 1;
                        add_static_opt(argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-nostdlib") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                        addstr(&prelinkerflags, mkstr("-YB", NULL));
                    } else if (strcmp(argv[var_s0], "-nodeflib") == 0) {
                        nodeflib = 1;
                    } else if (strcmp(argv[var_s0], "-noprototypes") == 0) {
                        prototype_checking_on = 0;
                    } else if ((argv[var_s0]->unk_2 == 0) || (strcmp(argv[var_s0], "-nocount") == 0) || (strcmp(argv[var_s0], "-nN") == 0) || (strcmp(argv[var_s0], "-nojmpopt") == 0)) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-non_shared") == 0) {
                        old_non_shared = 0;
                        non_shared = 1;
                        default_call_shared = 0;
                        call_shared = 0;
                        kpic_flag = 0;
                        if (non_shared_emitted == 0) {
                            addstr(&ldflags, "-non_shared");
                            addstr(&cfeflags, "-non_shared");
                            non_shared_emitted = 1;
                        }
                    } else if (strcmp(argv[var_s0], "-no_archive") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-no_mpc") == 0) {
                        B_1000ED74 = 1;
                    } else if ((compiler == 3) && ((strcmp(argv[var_s0], "-noextend_source") == 0) || (strcmp(argv[var_s0], "-noi4") == 0) || (strcmp(argv[var_s0], "-noisam") == 0) || (strcmp(argv[var_s0], "-noexpopt") == 0) || (strcmp(argv[var_s0], "-noequivauto") == 0) || (strcmp(argv[var_s0], "-nof77") == 0))) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    } else if (compiler == 6) {
                        if (strcmp(argv[var_s0], "-nolock") == 0) {
                            nolockflag = 1;
                        } else if ((strcmp(argv[var_s0], "-nomfdata") == 0) || (strcmp(argv[var_s0], "-normdata") == 0)) {
                            addstr(&ucobflags, argv[var_s0]);
                        } else {
                            goto block_1537;
                        }
                    } else if (strcmp(argv[var_s0], "-nocpp") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        } else {
                            docpp = 0;
                            add_static_opt(argv[var_s0]);
                        }
                    } else if ((compiler == 3) || ((compiler == 1) && (c_compiler_choice != 0))) {
                        if (strcmp(argv[var_s0], "-nocode") == 0) {
                            nocode = 1;
                            cflag = 1;
                        } else if (strcmp(argv[var_s0], "-no_prelink") == 0) {
                            no_prelink = 1;
                        } else if (strcmp(argv[var_s0], "-no_auto_include") == 0) {
                            auto_template_include = 0;
                            add_static_opt(argv[var_s0]);
                        } else {
                            goto block_961;
                        }
                    } else {
block_961:
                        if (strcmp(argv[var_s0], "-none") == 0) {
                            addstr(&objfiles, argv[var_s0]);
                        } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (strcmp(argv[var_s0], "-nofilt") == 0)) {
                            nofilt = 1;
                            add_static_opt(argv[var_s0]);
                        } else if ((compiler == 1) && (c_compiler_choice == 3) && (strncmp(argv[var_s0], "-no_delta", 9U) == 0)) {
                            if (argv[var_s0]->unk_9 == 0) {
                                spFC = "-YDN";
                            } else if (strcmp(argv[var_s0] + 9, "_expr") == 0) {
                                spFC = "-YDE";
                            } else if (strcmp(argv[var_s0] + 9, "_include") == 0) {
                                spFC = "-YDI";
                            } else {
                                spFC = NULL;
                            }
                            if (spFC != NULL) {
                                if (var_s0 >= (argc - 1)) {
                                    error(1, NULL, 0, NULL, 0, "%s must have an argument\n", argv[var_s0]);
                                    exit(2);
                                }
                                var_s0 += 1;
                                if ((u8) *argv[var_s0].unk_0 == 0x2D) {
                                    error(1, NULL, 0, NULL, 0, "%s must have an argument\n", argv[var_s0].unk_-4);
                                    exit(2);
                                }
                                addstr(&edisonflags, mkstr(spFC, argv[var_s0], NULL));
                                add_static_opt(argv[var_s0].unk_-4);
                                add_static_opt(argv[var_s0]);
                            } else {
                                goto block_1537;
                            }
                        } else {
                            goto block_1537;
                        }
                    }
                    break;
                case 0x6F:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-old_rl") == 0) {
                        addstr(&fcomflags, "-old_rl");
                    } else if (strcmp(argv[var_s0], "-oldcpp") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        } else {
                            oldcppflag = 1;
                            if ((compiler == 1) && (tpflag != 0)) {
                                relocate_passes(tstring, hstring, Bstring);
                            }
                        }
                    } else if (strcmp(argv[var_s0], "-old_ld") == 0) {
                        if (D_1000BF94 != 0) {
                            error(1, NULL, 0, NULL, 0, "malformed or unknown option: -old_ld\n");
                            exit(2);
                        } else {
                            LD = "old_ld";
                            relocate_passes("l", NULL, NULL);
                        }
                    } else if (strcmp(argv[var_s0], "-o32") == 0) {
                        thirty2bitflag = 1;
                        mips_abi = 1;
                        if (var_s0 >= (argc - 1)) {
                            func_00431B38(var_s0 + 1, 1);
                        }
                    } else if (strcmp(argv[var_s0], "-objectlist") == 0) {
                        if ((argv[var_s0].unk_4 != NULL) && (*argv[var_s0].unk_4 != 0x2D)) {
                            addstr(&objfiles, argv[var_s0].unk_0);
                            var_s0 += 1;
                            addstr(&objfiles, argv[var_s0]);
                        } else {
                            error(1, NULL, 0, NULL, 0, "-objectlist must be given a file argument\n");
                        }
                    } else if (argv[var_s0]->unk_2 == 0) {
                        var_s0 += 1;
                        if (var_s0 < argc) {
                            temp_t9_3 = argv[var_s0];
                            outfile = temp_t9_3;
                            var_s1 = getsuf(temp_t9_3) & 0xFF;
                            if (((var_s1 == 0x63) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) || (var_s1 == 0x72) || (var_s1 == 0x65) || ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (var_s1 == 6)) || (var_s1 == 0x73) || (var_s1 == 1) || (var_s1 == 2)) && (stat(outfile, &sp74) == 0)) {
                                error(1, NULL, 0, NULL, 0, "-o %s resembles the name of a source file, disallowed\n", argv[var_s0]);
                                exit(2);
                            }
                            B_1000ECCC = mkstr(outfile, NULL);
                            func_00431B38(var_s0, 2);
                        } else {
                            error(1, NULL, 0, NULL, 0, "-o must have an argument\n");
                            exit(2);
                            goto block_1024;
                        }
                    } else {
block_1024:
                        if ((compiler == 3) && (strcmp(argv[var_s0], "-onetrip") == 0)) {
                            addstr(&fcomflags, "-1");
                            mp_onetripflag = 1;
                        } else {
                            goto block_1537;
                        }
                    }
                    break;
                case 0x70:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-prototypes") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        } else {
                            prototype_checking_on = 1;
                        }
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-pedantic") == 0)) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        } else {
                            addstr(&acppflags, "-p");
                        }
                    } else if (strcmp(argv[var_s0], "-pfa") == 0) {
                        mp_flag |= 0x10001;
                        if ((var_s0 + 1) < argc) {
                            sp70 = mpflags;
                            if ((mpflags->unk_0 != NULL) && (strcmp(argv[var_s0].unk_4, mpflags->unk_0) != 0)) {
loop_1042:
                                sp70 += 8;
                                temp_t6_4 = sp70->unk_0;
                                if (temp_t6_4 != NULL) {
                                    if (strcmp(argv[var_s0].unk_4, temp_t6_4) != 0) {
                                        goto loop_1042;
                                    }
                                }
                            }
                            if (sp70->unk_0 != NULL) {
                                var_s0 += 1;
                                mp_flag |= sp70->unk_4;
                            }
                        }
                    } else if (strncmp(argv[var_s0], "-pfaprepass,", 0xCU) == 0) {
                        mp_flag |= 0x10001;
                        mp_prepass_count += 1;
                    } else if (strcmp(argv[var_s0], "-pca") == 0) {
                        cmp_flag |= 0x10001;
                        if (Bflag != 0) {
                            error(1, NULL, 0, NULL, 0, "-pca must preceed any -B flags.\n");
                            exit(2);
                        }
                        relocate_passes("fKY", NULL, NULL);
                        if ((var_s0 + 1) < argc) {
                            sp6C = cmpflags;
                            if ((cmpflags->unk_0 != NULL) && (strcmp(argv[var_s0].unk_4, cmpflags->unk_0) != 0)) {
loop_1054:
                                sp6C += 8;
                                temp_t8_5 = sp6C->unk_0;
                                if (temp_t8_5 != NULL) {
                                    if (strcmp(argv[var_s0].unk_4, temp_t8_5) != 0) {
                                        goto loop_1054;
                                    }
                                }
                            }
                            if (sp6C->unk_0 != NULL) {
                                var_s0 += 1;
                                cmp_flag |= sp6C->unk_4;
                            }
                        }
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                        if (strncmp(argv[var_s0], "-pt", 3U) == 0) {
                            temp_t6_5 = argv[var_s0] + 3;
                            sp68 = temp_t6_5;
                            if (strcmp(temp_t6_5, "v") == 0) {
                                verbose_prelink += 1;
                            } else if (strcmp(sp68, "none") == 0) {
                                default_template_instantiation_mode = 0;
                            } else if (strcmp(sp68, "used") == 0) {
                                default_template_instantiation_mode = 1;
                            } else if ((strcmp(sp68, "a") == 0) || (strcmp(sp68, "all") == 0)) {
                                default_template_instantiation_mode = 2;
                            } else if ((u8) *sp68 == 0x65) {
                                if ((strcmp(sp68 + 1, ".c") != 0) && (strcmp(sp68 + 1, ".cc") != 0) && (strcmp(sp68 + 1, ".c++") != 0) && (strcmp(sp68 + 1, ".C") != 0) && (strcmp(sp68 + 1, ".cxx") != 0) && (strcmp(sp68 + 1, ".CXX") != 0) && (strcmp(sp68 + 1, ".cpp") != 0) && (strcmp(sp68 + 1, ".CPP") != 0)) {
                                    error(2, NULL, 0, NULL, 0, "unsupported suffix in %s\n", argv[var_s0]);
                                }
                            } else {
                                error(2, NULL, 0, NULL, 0, "ignored unsupported option %s\n", argv[var_s0]);
                            }
                        } else if (strcmp(argv[var_s0], "-prelink") == 0) {
                            force_prelink = 1;
                        } else {
                            goto block_1084;
                        }
                    } else {
block_1084:
                        if (argv[var_s0]->unk_2 == 0) {
                            pflag = 1;
                            goto block_1093;
                        }
                        if (strcmp(argv[var_s0], "-pg") == 0) {
                            var_t2 = 1;
                            pflag = 1;
                            var_at = &pgflag;
                            goto block_1092;
                        }
                        if ((argv[var_s0]->unk_3 == 0) && ((s32) argv[var_s0]->unk_2 >= 0x30) && ((s32) argv[var_s0]->unk_2 < 0x34)) {
                            var_at = &pflag;
                            var_t2 = argv[var_s0]->unk_2 - 0x30;
block_1092:
                            *var_at = var_t2;
block_1093:
                            if ((pflag == 0) || (pflag == 1)) {
                                if (Bflag != 0) {
                                    error(1, NULL, 0, NULL, 0, "-p0 or -p1 must precede any -B flags\n");
                                    exit(2);
                                }
                            } else {
                                error(1, NULL, 0, NULL, 0, "%s has been superseded, see prof (1) and pixie (1)\n", argv[var_s0]);
                                exit(2);
                            }
                            relocate_passes("rn", NULL, NULL);
                        } else {
                            goto block_1537;
                        }
                    }
                    break;
                case 0x71:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-quickstart_info") == 0) {
                        quickstart_info = 1;
                    } else if (strcmp(argv[var_s0], "-ql") != 0) {
                        if (strcmp(argv[var_s0], "-qp") == 0) {

                        } else {
                            goto block_1537;
                        }
                    }
                    break;
                case 0x72:                          /* switch 1 */
                    if ((strcmp(argv[var_s0], "-r4000") == 0) || (strcmp(argv[var_s0], "-r6000") == 0)) {
                        addstr(&asflags, argv[var_s0]);
                    } else if (argv[var_s0]->unk_2 == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-require_minor") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-rm_dead_code") == 0) {
                        force_rm_dead_code = 1;
                    } else if ((strcmp(argv[var_s0], "-rpath") == 0) && (argv[var_s0].unk_4 != NULL) && (*argv[var_s0].unk_4 != 0x2D)) {
                        addstr(&ldflags, argv[var_s0].unk_0);
                        var_s0 += 1;
                        addstr(&ldflags, argv[var_s0]);
                    } else if ((strcmp(argv[var_s0], "-rdata_shared") == 0) || (strcmp(argv[var_s0], "-rdata_writable") == 0)) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if ((compiler == 3) && (strcmp(argv[var_s0], "-r8") == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                    } else if ((compiler == 6) && ((strcmp(argv[var_s0], "-range") == 0) || (strcmp(argv[var_s0], "-rmansi") == 0) || (strcmp(argv[var_s0], "-rmext") == 0))) {
                        addstr(&ucobflags, argv[var_s0]);
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x73:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                            do_strip = 1;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                    } else if (strcmp(argv[var_s0], "-strictIEEE") == 0) {
                        addstr(&optflags, argv[var_s0]);
                    } else if ((((compiler == 1) && (c_compiler_choice != 0)) || (compiler == 3)) && (strncmp(argv[var_s0], "-sa", 3U) == 0) && ((argv[var_s0]->unk_3 == 0) || (argv[var_s0]->unk_3 == 0x2C))) {
                        D_1000BF74 = 1;
                        if ((argv[var_s0]->unk_3 == 0x2C) && (argv[var_s0]->unk_4 != 0)) {
                            sp64 = strtok(argv[var_s0] + 4, ",");
                            if (sp64 != NULL) {
                                do {
                                    if (strcmp(sp64, "nosrc") == 0) {
                                        D_1000BF78 = 1;
                                    } else if (D_1000BF80 != NULL) {
                                        error(1, NULL, 0, NULL, 0, "Static analysis directory already specified\n");
                                    } else {
                                        D_1000BF80 = sp64;
                                        if (sp64[strlen(sp64)].unk_-1 != 0x2F) {
                                            D_1000BF80 = mkstr(sp64, "/", NULL);
                                        }
                                    }
                                    sp64 = strtok(NULL, ",");
                                } while (sp64 != NULL);
                            }
                        }
                    } else if ((((compiler == 1) && (c_compiler_choice != 0)) || (compiler == 3)) && (strncmp(argv[var_s0], "-sa_fs", 6U) == 0) && ((argv[var_s0]->unk_6 == 0) || (argv[var_s0]->unk_6 == 0x2C))) {
                        if (argv[var_s0]->unk_6 == 0x2C) {
                            var_v0 = mkstr(argv[var_s0] + 7, NULL);
                        } else {
                            var_v0 = mkstr("cvstatic.fileset", NULL);
                        }
                        D_1000BF84 = var_v0;
                        D_1000BF88 += 1;
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-set_version") == 0)) {
                        var_s0 += 1;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-set_version requires an argument\n");
                            exit(2);
                        }
                        addstr(&ldflags, argv[var_s0].unk_-4);
                        addstr(&ldflags, argv[var_s0]);
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-soname") == 0)) {
                        var_s0 += 1;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-soname requires an argument\n");
                            exit(2);
                        }
                        addstr(&ldflags, argv[var_s0].unk_-4);
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-systype") == 0) {
                        var_s0 += 1;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-systype must have an argument\n");
                            exit(2);
                        }
                        if (user_systype != 0) {
                            if (strcmp(systype, argv[var_s0]) != 0) {
                                error(1, NULL, 0, NULL, 0, "only one -systype option allowed\n");
                                exit(2);
                            } else {
                                multiple_systype = 1;
                            }
                        }
                        systype = argv[var_s0];
                        user_systype = 1;
                        if ((Bflag != 0) && (systype_seen == 0)) {
                            error(1, NULL, 0, NULL, 0, "-systype must precede any -B flags\n");
                            exit(2);
                        } else {
                            systype_seen = 1;
                        }
                        if (multiple_systype == 0) {
                            if (strcmp(systype, "svr4") == 0) {
                                svr4_systype = 1;
                                if (elfflag == 0) {
                                    addstr(&asflags, "-elf");
                                    addstr(&ldflags, "-elf");
                                }
                                elfflag = 1;
                            } else {
                                error(1, NULL, 0, NULL, 0, "Only systype svr4 allowed\n");
                                exit(2);
                            }
                            if ((strcmp(systype, "svr4") != 0) && (strcmp(systype, "bsd43") != 0) && (strcmp(systype, "svr3") != 0) && (strcmp(systype, "sysv") != 0) && (fopen(strcat("/", systype), "r") == NULL)) {
                                if (systype_warn == 0) {
                                    error(2, NULL, 0, NULL, 0, "This systype doesn't exist on this machine; changed systype to svr3.\n");
                                }
                                systype = "svr3";
                            }
                            if (svr4_systype == 0) {
                                comp_target_root = mkstr(comp_target_root, systype, "/", NULL);
                            }
                            if (fiveflag != 0) {
                                var_v0_2 = mkstr(comp_target_root, "usr/5include", NULL);
                            } else {
                                einclude = mkstr(comp_target_root, "usr/include/CC", NULL);
                                var_v0_2 = mkstr(comp_target_root, "usr/include", NULL);
                            }
                            include = var_v0_2;
                            if (Bstring != NULL) {
                                relocate_passes("h", NULL, Bstring);
                            }
                            newrunlib();
                        }
                        add_static_opt(argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-swopcode") == 0) {
                        if ((dwopcodeflag != 0) || (sixty4bitflag != 0)) {
                            error(1, NULL, 0, NULL, 0, "-swopcode can not be used with -dwopcode/-64bit\n");
                            exit(2);
                        }
                        swopcodeflag = 1;
                    } else if ((argv[var_s0]->unk_2 == 0x6F) && (argv[var_s0]->unk_3 == 0x70) && (argv[var_s0]->unk_4 == 0x74)) {
                        if ((compiler != 1) && (compiler != 3)) {
                            error(2, NULL, 0, NULL, 0, "-sopt only available with Fortran and C; option ignored.\n");
                        } else if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        } else {
                            temp_t0 = argv[var_s0];
                            Warg = temp_t0 + 5;
                            if ((u8) temp_t0[5] == 0x2C) {
                                do {
                                    Warg->unk_0 = 0;
                                    temp_t4_6 = Warg + 1;
                                    Warg = temp_t4_6;
                                    addstr(&soptflags, temp_t4_6);
                                    temp_t3_2 = (u8) Warg->unk_0;
                                    if ((temp_t3_2 != 0x2C) && (temp_t3_2 != 0)) {
loop_1225:
                                        Warg += 1;
                                        temp_t8_6 = (u8) Warg->unk_0;
                                        if (temp_t8_6 != 0x2C) {
                                            if (temp_t8_6 != 0) {
                                                goto loop_1225;
                                            }
                                        }
                                    }
                                } while ((u8) Warg->unk_0 == 0x2C);
                            }
                            run_sopt = 1;
                        }
                    } else if (strcmp(argv[var_s0], "-show") == 0) {
                        vflag = 1;
                    } else if (strcmp(argv[var_s0], "-showt") == 0) {
                        time_flag = 1;
                    } else if (strcmp(argv[var_s0], "-show0") == 0) {
                        vflag = 1;
                        execute_flag = 0;
                    } else if (strcmp(argv[var_s0], "-showm") == 0) {
                        memory_flag += 1;
                    } else if (strcmp(argv[var_s0], "-show_defaults") == 0) {
                        execute_flag = 0;
                        exit(0);
                    } else {
                        temp_t1_4 = compiler == 1;
                        if (temp_t1_4 != 0) {
                            if ((temp_t1_4 != 0) && (c_compiler_choice != 0) && (strncmp(argv[var_s0], "-smart", 6U) == 0)) {
                                if ((argv[var_s0]->unk_6 == 0x2C) && (argv[var_s0]->unk_7 != 0)) {
                                    sbrepos = argv[var_s0] + 7;
                                } else {
                                    sbrepos = NULL;
                                }
                                add_static_opt(argv[var_s0]);
                                smart_build = 1;
                            } else if (strcmp(argv[var_s0], "-shared") == 0) {
                                call_shared = 0;
                                make_edison_shlib += 1;
                            } else if (strcmp(argv[var_s0], "-std0") == 0) {
                                stdflag = 0;
                                addstr(&ccomflags, argv[var_s0]);
                            } else if ((strcmp(argv[var_s0], "-std") == 0) || (strcmp(argv[var_s0], "-std1") == 0)) {
                                stdflag = 1;
                                addstr(&ccomflags, argv[var_s0]);
                            } else if (strcmp(argv[var_s0], "-signed") == 0) {
                                addstr(&pcaflags, "-signed");
                                addstr(&soptflags, "-signed");
                                addstr(&ccomflags, "-Xsigned");
                                if ((compiler == 1) && (c_compiler_choice != 0)) {
                                    signedcharflag = 1;
                                }
                            } else {
                                goto block_1259;
                            }
                        } else {
block_1259:
                            if ((compiler == 4) && ((strcmp(argv[var_s0], "-std") == 0) || (strcmp(argv[var_s0], "-std0") == 0) || (strcmp(argv[var_s0], "-std1") == 0))) {
                                stdflag = 1;
                                addstr(&ccomflags, argv[var_s0]);
                            } else if (compiler == 3) {
                                if (strcmp(argv[var_s0], "-std") == 0) {
                                    addstr(&fcomflags, argv[var_s0]);
                                } else if (strcmp(argv[var_s0], "-static") == 0) {
                                    automaticflag = 0;
                                } else if (strncmp(argv[var_s0], "-share_", 7U) == 0) {
                                    if (strcmp(argv[var_s0] + 7, "io") == 0) {
                                        D_1000C130 = 1;
                                    } else if (strcmp(argv[var_s0] + 7, "all") == 0) {
                                        D_1000C130 = 2;
                                    } else {
                                        goto block_1274;
                                    }
                                } else {
                                    goto block_1274;
                                }
                            } else {
block_1274:
                                if ((compiler == 2) && (strcmp(argv[var_s0], "-std") == 0)) {
                                    stdflag = 1;
                                    addstr(&upasflags, argv[var_s0]);
                                } else if ((compiler == 6) && ((strcmp(argv[var_s0], "-supp_cob85") == 0) || (strcmp(argv[var_s0], "-supp_cod") == 0) || (strcmp(argv[var_s0], "-supp_rm") == 0))) {
                                    addstr(&ucobflags, argv[var_s0]);
                                } else if ((compiler == 4) && (strcmp(argv[var_s0], "-signed") == 0)) {

                                } else {
                                    goto block_1537;
                                }
                            }
                        }
                    }
                    break;
                case 0x74:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-transitive_link") == 0) {
                        full_transitive_link = 0;
                        transitive_link = 1;
                        no_transitive_link = 0;
                    } else if (strcmp(argv[var_s0], "-trapuv") == 0) {
                        trapuv_flag = 1;
                        addstr(&upasflags, argv[var_s0]);
                        addstr(&fcomflags, argv[var_s0]);
                        addstr(&upl1flags, argv[var_s0]);
                        addstr(&ucobflags, argv[var_s0]);
                        addstr(&ulpiflags, argv[var_s0]);
                        addstr(&eflflags, argv[var_s0]);
                        addstr(&ratforflags, argv[var_s0]);
                        addstr(&genflags, argv[var_s0]);
                        addstr(&asflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-tfp") == 0) {
                        tfp_flag = 1;
                    } else if (strcmp(argv[var_s0], "-traditional") == 0) {
                        acpp_traditional += 1;
                    } else {
                        temp_t5_6 = argv[var_s0] + 2;
                        tstring = temp_t5_6;
                        strcat(alltstring, temp_t5_6);
                    }
                    break;
                case 0x5A:                          /* switch 1 */
                    temp_t7_8 = argv[var_s0]->unk_2;
                    switch (temp_t7_8) {            /* switch 4 */
                    case 0x41:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                        break;
                    case 0x43:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                        break;
                    case 0x46:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                        break;
                    case 0x4E:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                        break;
                    case 0x50:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                        break;
                    case 0x55:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                        break;
                    case 0x66:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                        break;
                    case 0x69:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                        break;
                    case 0x52:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                        break;
                    case 0x47:                      /* switch 4 */
                        addstr(&ldZflags, "-ZG");
                        break;
                    case 0x71:                      /* switch 4 */
                        vflag = 1;
                        break;
                    case 0x67:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "-Zg is obsolete and is ignored.\n");
                        if (compiler == 1) {
                            error(2, NULL, 0, NULL, 0, "perhaps replace -Zg with -lgl_s. See your graphics documentation.\n");
                        }
                        if ((hasfortran != 0) || (compiler == 3)) {
                            error(2, NULL, 0, NULL, 0, "perhaps replace -Zg with -lfgl -lgl_s  See f77(1).\n");
                        }
                        if ((haspascal != 0) || (compiler == 2)) {
                            error(2, NULL, 0, NULL, 0, "perhaps replace -Zg with -lpgl /usr/lib/p2cstr.o -lgl_s  See pc(1).\n");
                        }
                        break;
                    case 0x72:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "-Zr is obsolete and is ignored.\n");
                        break;
                    case 0x76:                      /* switch 4 */
                        stdflag = 1;
                        addstr(&ccomflags, "-std");
                        addstr(&upasflags, "-std");
                        addstr(&fcomflags, "-std");
                        addstr(&upl1flags, "-std");
                        addstr(&ucobflags, "-std");
                        break;
                    case 0x7A:                      /* switch 4 */
                        error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                        break;
                    default:                        /* switch 4 */
                        error(1, NULL, 0, NULL, 0, "Unknown character in %s\n", argv[var_s0]);
                        exit(2);
                        break;
                    }
                    break;
                case 0x2D:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        if (xpg_flag != 0) {
                            NoMoreOptions += 1;
                        }
                    } else {
                        temp_s4_3 = argv[var_s0]->unk_2;
                        switch (temp_s4_3) {        /* switch 8; irregular */
                        case 0x6E:                  /* switch 8 */
                            error(2, NULL, 0, NULL, 0, "%s is default\n", argv[var_s0]);
                            break;
                        case 0x78:                  /* switch 8 */
                            error(2, NULL, 0, NULL, 0, "%s is default\n", argv[var_s0]);
                            break;
                        default:                    /* switch 8 */
                            error(1, NULL, 0, NULL, 0, "Unknown character in %s\n", argv[var_s0]);
                            exit(2);
                            break;
                        }
                    }
                    break;
                case 0x75:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-uopt0") != 0) {
                        if (argv[var_s0]->unk_2 == 0) {
                            if (compiler == 3) {
                                mp_uflag = 1;
                                addstr(&fcomflags, argv[var_s0]);
                                add_static_opt(argv[var_s0]);
                            } else {
                                var_s0 += 1;
                                if (var_s0 < argc) {
                                    addstr(&objfiles, "-u");
                                    addstr(&objfiles, argv[var_s0]);
                                } else {
                                    error(1, NULL, 0, NULL, 0, "ld requires -u to have an argument\n");
                                    exit(2);
                                    goto block_1335;
                                }
                            }
                        } else {
block_1335:
                            if (strcmp(argv[var_s0], "-unroll") == 0) {
                                error(1, NULL, 0, NULL, 0, "This flag is no longer supported\n");
                                exit(2);
                                goto block_1340;
                            }
                            if ((compiler == 3) && (strcmp(argv[var_s0], "-usefpidx") == 0)) {
                                addstr(&fcomflags, argv[var_s0]);
                            } else {
block_1340:
                                if (strcmp(argv[var_s0], "-use_readwrite_const") == 0) {
                                    if ((compiler == 1) && (c_compiler_choice != 0)) {
                                        addstr(&edisonflags, "-Yr0");
                                    } else {
                                        addstr(&accomflags, "-use_readwrite_const");
                                    }
                                } else if (strcmp(argv[var_s0], "-use_readonly_const") == 0) {
                                    if ((compiler == 1) && (c_compiler_choice != 0)) {
                                        addstr(&edisonflags, "-Yr1");
                                    } else {
                                        addstr(&accomflags, "-use_readonly_const");
                                    }
                                } else if ((compiler == 1) && (strcmp(argv[var_s0], "-update_registry") == 0)) {
                                    var_s0 += 1;
                                    if (var_s0 >= argc) {
                                        error(1, NULL, 0, NULL, 0, "-update_registry requires a filename argument\n");
                                        exit(2);
                                    }
                                    addstr(&ldflags, argv[var_s0].unk_-4);
                                    addstr(&ldflags, argv[var_s0]);
                                } else {
                                    goto block_1537;
                                }
                            }
                        }
                    }
                    break;
                case 0x76:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        if (default_svr4 == 0) {
                            vflag = 1;
                            time_flag = 1;
                        }
                    } else if (compiler == 1) {
                        if (strcmp(argv[var_s0], "-volatile") == 0) {
                            error(2, NULL, 0, NULL, 0, "-volatile is no longer supported; use the volatile qualifier instead\n");
                        } else if (strcmp(argv[var_s0], "-varargs") == 0) {
                            addstr(&ccomflags, "-Xvarargs");
                        } else if (strcmp(argv[var_s0], "-verbose") == 0) {
                            addstr(&ccomflags, "-verbose");
                        } else {
                            goto block_1365;
                        }
                    } else {
block_1365:
                        if ((compiler == 3) && ((strncmp(argv[var_s0], "-vms", 4U) == 0) || (strcmp(argv[var_s0], "-varargs") == 0))) {
                            addstr(&fcomflags, argv[var_s0]);
                            add_static_opt(argv[var_s0]);
                        } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (strcmp(argv[var_s0], "-v2") == 0)) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                            }
                        } else {
                            goto block_1537;
                        }
                    }
                    break;
                case 0x77:                          /* switch 1 */
                    if ((compiler == 1) && (strncmp(argv[var_s0], "-wlint", 6U) == 0)) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        } else {
                            addstr(&ccomflags, argv[var_s0]);
                        }
                    } else if (strcmp(argv[var_s0], "-woff") == 0) {
                        var_s0 += 1;
                        if (var_s0 < argc) {
                            if (strcmp(argv[var_s0], "options") == 0) {
                                sp14C = 0;
                            } else if (((s32) (u8) *argv[var_s0] < 0x30) || ((s32) (u8) *argv[var_s0] >= 0x3A)) {
                                error(2, NULL, 0, NULL, 0, "-woff requires a comma-separated list of error numbers - ignored\n");
                                var_s0 -= 1;
                            } else {
                                addstr(&accomflags, mkstr("-Xwoff", argv[var_s0], NULL));
                                addstr(&edisonflags, mkstr("-YW", argv[var_s0], NULL));
                            }
                        } else {
                            error(1, NULL, 0, NULL, 0, "-woff requires a warning number (or a list of them)\n");
                            exit(2);
                            goto block_1391;
                        }
                    } else {
block_1391:
                        if ((argv[var_s0]->unk_2 == 0x31) && (argv[var_s0]->unk_3 == 0)) {
                            if (compiler != 3) {
                                error(2, NULL, 0, NULL, 0, "Unknown flag: %s\n", argv[var_s0]);
                            } else {
                                w1flag = 1;
                            }
                        } else if ((argv[var_s0]->unk_2 == 0x30) && (argv[var_s0]->unk_3 == 0)) {
                            if (compiler != 3) {
                                error(2, NULL, 0, NULL, 0, "Unknown flag: %s\n", argv[var_s0]);
                            } else {
                                w1flag = 0;
                            }
                        } else if (argv[var_s0]->unk_2 == 0x36) {
                            if ((compiler == 3) && (argv[var_s0]->unk_2 == 0x36)) {
                                mp_66flag = 1;
                            }
                            addstr(&fcomflags, argv[var_s0]);
                        } else if ((argv[var_s0]->unk_2 != 0) && (compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        } else if ((argv[var_s0]->unk_2 == 0) || ((argv[var_s0]->unk_3 == 0) && ((argv[var_s0]->unk_2 == 0x31) || (argv[var_s0]->unk_2 == 0x32) || (argv[var_s0]->unk_2 == 0x33)))) {
                            addstr(&cppflags, argv[var_s0]);
                            addstr(&ccomflags, argv[var_s0]);
                            addstr(&edisonflags, argv[var_s0]);
                            w1flag = 2;
                            addstr(&upasflags, argv[var_s0]);
                            addstr(&upl1flags, argv[var_s0]);
                            addstr(&ucobflags, argv[var_s0]);
                            addstr(&ulpiflags, argv[var_s0]);
                            addstr(&uldflags, argv[var_s0]);
                            addstr(&uopt0flags, argv[var_s0]);
                            addstr(&ddoptflags, argv[var_s0]);
                            addstr(&uloopflags, argv[var_s0]);
                            addstr(&optflags, argv[var_s0]);
                            addstr(&genflags, argv[var_s0]);
                            addstr(&ldflags, argv[var_s0]);
                            addstr(&asflags, argv[var_s0]);
                            addstr(&ldflags, argv[var_s0]);
                            addstr(&ftocflags, argv[var_s0]);
                        } else {
                            goto block_1537;
                        }
                    }
                    break;
                case 0x79:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 != 0) {
                        addstr(&objfiles, argv[var_s0]);
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x78:                          /* switch 1 */
                    if (strcmp(argv[var_s0], "-xansi") == 0) {
                        if (compchoice == 1) {
                            compchoice = 0;
                        }
                        ansichoice = 3;
                        cppchoice = 3;
                        relocate_passes("p", NULL, NULL);
                        add_static_opt(argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-xgot") == 0) {
                        addstr(&asflags, "-big_got");
                    } else if (argv[var_s0]->unk_2 == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else {
                        goto block_1537;
                    }
                    break;
                case 0x7A:                          /* switch 1 */
                    if (argv[var_s0]->unk_2 == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else {
                        goto block_1537;
                    }
                    break;
                }
            } else if (((u8) *argv[var_s0] == 0x2B) && (compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                temp_t4_7 = argv[var_s0]->unk_1;
                switch (temp_t4_7) {                /* switch 5 */
                case 0x70:                          /* switch 5 */
                    var_at_2 = &anachronisms;
                    if (argv[var_s0]->unk_2 == 0) {
                        goto block_1441;
                    }
                    if (argv[var_s0]->unk_2 == 0x70) {
                        anachronisms = 0;
                        var_at_2 = &cfront_compatible;
                        goto block_1441;
                    }
                    var_at_2 = &anachronisms;
                    if (argv[var_s0]->unk_2 == 0x61) {
                        goto block_1441;
                    }
                    var_at_2 = &cfront_compatible;
                    if (argv[var_s0]->unk_2 == 0x63) {
block_1441:
                        *var_at_2 = 0;
                    }
                    add_static_opt(argv[var_s0]);
                    break;
                case 0x77:                          /* switch 5 */
                    fullwarn = 1;
                    break;
                case 0x76:                          /* switch 5 */
                    vflag = 1;
                    break;
                case 0x64:                          /* switch 5 */
                    disable_inlines = 1;
                    break;
                case 0x65:                          /* switch 5 */
                    if ((compiler == 1) && (c_compiler_choice != 0)) {
                        error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                    } else {
                    case 0x49:                      /* switch 5 */
                        cflag = 1;
                        plusIflag = 1;
                        Fflag = 1;
                        default_template_instantiation_mode = 1;
                    }
                    break;
                default:                            /* switch 5 */
                default:                            /* switch 1 */
block_1537:
                    if (sp14C != 0) {
                        error(1, NULL, 0, NULL, 0, "malformed or unknown option: %s\n", argv[var_s0]);
                        exit(2);
                    } else {
                        error(2, NULL, 0, NULL, 0, "malformed or unknown option: %s\n", argv[var_s0]);
                    }
                    break;
                }
            } else {
                var_s1 = getsuf(argv[var_s0]) & 0xFF;
                if (var_s1 == 0x6D) {
                    var_s1 = 0x66;
                }
                if (var_s1 == 0x70) {
                    haspascal = 1;
                }
                if (var_s1 == 0x66) {
                    hasfortran = 1;
                }
                if (var_s1 == 1) {
                    haspl1 = 1;
                }
                if ((var_s1 == 0x63) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) || (var_s1 == 0x72) || (var_s1 == 0x65) || (var_s1 == 0x42) || (var_s1 == 0x55) || (var_s1 == 0x73) || (var_s1 == 0x4F) || (var_s1 == 0x47) || (var_s1 == 0x53) || (var_s1 == 0x4D) || (var_s1 == 0x56) || (var_s1 == 0x69) || (var_s1 == 1) || (var_s1 == 0x44) || (var_s1 == 3) || (var_s1 == 2) || (var_s1 == 0x75) || (var_s1 == 6) || ((compiler == 1) && (nocode != 0) && (D_1000BF74 != 0) && (var_s1 == 0x68)) || (Eflag != 0) || (compiler == 4)) {
                    srcexists += 1;
                    if (((u8) *argv[var_s0] == 0x2D) && (NoMoreOptions == 0)) {
                        sp60 = 1;
                        if (argv[var_s0]->unk_1 == 0x2D) {
                            do {
                                sp60 += 1;
                            } while ((u8) argv[var_s0][sp60] == 0x2D);
                        }
                        argv[var_s0] = &argv[var_s0][sp60];
                    }
                    sp5C = 1;
                    if (argc >= 2) {
                        do {
                            temp_t3_3 = argv[sp5C];
                            if ((temp_t3_3->unk_1 == 0x6A) && (strcmp(temp_t3_3, "-j") == 0)) {
                                jflag += 1;
                            }
                            temp_t5_7 = sp5C + 1;
                            sp5C = temp_t5_7;
                        } while (temp_t5_7 < argc);
                    }
                    if (((Oflag == 3) || (Oflag == 4)) && (jflag == 0) && ((var_s1 == 0x63) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) || (var_s1 == 0x72) || (var_s1 == 0x65) || (var_s1 == 0x42) || (var_s1 == 0x55) || (var_s1 == 0x69) || (var_s1 == 1) || (var_s1 == 3) || (var_s1 == 2) || (var_s1 == 6) || (var_s1 == 0x75) || (var_s1 == 0x44))) {
                        if (var_s1 != 0x75) {
                            addstr(&srcfiles, argv[var_s0]);
                            var_s2_10 = mksuf(argv[var_s0], 0x75);
                        } else {
                            var_s2_10 = argv[var_s0];
                        }
                        uload = 1;
                        if (uldobj_place == -1) {
                            uldobj_place = save_place(&objfiles);
                        }
                        if (nodup(&ufiles, var_s2_10) != 0) {
                            addstr(&ufiles, var_s2_10);
                        }
                        temp_v0 = mksuf(argv[var_s0], 0x6F);
                        if (nodup(&objfiles, temp_v0) != 0) {
                            sp158 = temp_v0;
                        }
                    } else if ((Eflag == 0) && (compiler != 4)) {
                        addstr(&srcfiles, argv[var_s0]);
                        temp_v0_2 = mksuf(argv[var_s0], 0x6F);
                        if (nodup(&objfiles, temp_v0_2) != 0) {
                            addstr(&objfiles, temp_v0_2);
                            sp158 = temp_v0_2;
                            nobjs += 1;
                        }
                    } else {
                        addstr(&srcfiles, argv[var_s0]);
                    }
                } else if (var_s1 == 0x62) {
                    if (((Oflag == 3) || (Oflag == 4)) && (jflag == 0)) {
                        if (uldobj_place == -1) {
                            uldobj_place = save_place(&objfiles);
                        }
                        addstr(&ufiles, argv[var_s0]);
                        uload = 1;
                    }
                } else {
                    addstr(&objfiles, argv[var_s0]);
                    if (var_s1 == 0x6F) {
                        nobjs += 1;
                    }
                }
                func_00431B38(var_s0 + 1, 1);
            }
            var_s0 += 1;
        } while (var_s0 < argc);
    }
    if (sp15C != NULL) {
        if (srcfiles.length == 1) {
            sp58 = strdup(*srcfiles.entries);
            if (sp58 == NULL) {
                sp58 = sp158;
            } else {
                sp54 = strlen(sp58);
                if (((s32) sp54 >= 3) && (sp58[sp54].unk_-2 == 0x2E)) {
                    if (Eflag != 0) {
                        sp58[sp54].unk_-1 = 0x69;
                    } else if (Sflag != 0) {
                        sp58[sp54].unk_-1 = 0x73;
                    } else if (jflag != 0) {
                        sp58[sp54].unk_-1 = 0x75;
                    } else {
                        sp58[sp54].unk_-2 = 0;
                    }
                }
            }
        }
        if (((compiler == 1) && (c_compiler_choice != 0)) || ((compiler == 3) && (D_1000BF74 != 0))) {
            if ((srcfiles.length == 1) && ((outfile != NULL) || (cflag == 0))) {
                addstr(&ldflags, "-MDignore");
                addstr(&ldflags, sp158);
            }
            addstr(&cppflags, mkstr("-YM", sp15C, NULL));
            if (sp154 != NULL) {
                addstr(&cppflags, mkstr("-Yt", sp154, NULL));
            }
            addstr(&ldflags, "-MDupdate");
            addstr(&ldflags, sp15C);
        } else {
            if ((srcfiles.length == 1) && ((outfile != NULL) || (cflag == 0))) {
                addstr(&cppflags, "-MDtarget");
                if (outfile != NULL) {
                    addstr(&cppflags, outfile);
                } else {
                    addstr(&cppflags, sp58);
                }
                addstr(&ldflags, "-MDignore");
                addstr(&ldflags, sp158);
            }
            addstr(&cppflags, "-MDupdate");
            addstr(&cppflags, sp15C);
            if (Oflag == 3) {
                addstr(&uldflags, "-MDtarget");
                if (outfile != NULL) {
                    addstr(&uldflags, outfile);
                } else if (cflag != 0) {
                    addstr(&uldflags, "u.out.o");
                } else {
                    addstr(&uldflags, "a.out");
                }
                addstr(&uldflags, "-MDupdate");
                addstr(&uldflags, sp15C);
            } else {
                addstr(&ldflags, "-MDupdate");
                addstr(&ldflags, sp15C);
            }
        }
    }
    if (mips2flag != 0) {
        addstr(&ccomflags, "-mips2");
        addstr(&upasflags, "-mips2");
        addstr(&fcomflags, "-mips2");
        addstr(&upl1flags, "-mips2");
        addstr(&ucobflags, "-mips2");
        addstr(&ulpiflags, "-mips2");
        addstr(&eflflags, "-mips2");
        addstr(&ratforflags, "-mips2");
        addstr(&ujoinflags, "-mips2");
        addstr(&usplitflags, "-mips2");
        addstr(&umergeflags, "-mips2");
        addstr(&uloopflags, "-mips2");
        addstr(&optflags, "-mips2");
        addstr(&genflags, "-mips2");
        addstr(&asflags, "-mips2");
        addstr(&ldflags, "-mips2");
        addstr(&ftocflags, "-mips2");
    }
}

void get_host_chiptype(void) {

}

void error(s32 arg0, s8* arg1, s32 arg2, s8* arg3, s32 arg4, s8* arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, ...) {
    u32 sp34;
    s32 sp30;
    s32 temp_t3;

    if ((Vflag == 0) && (D_1000C1D8 == NULL)) {
        D_1000C1D8 = strrchr(progname, 0x2F);
        if (D_1000C1D8 == NULL) {
            D_1000C1D8 = progname;
        } else {
            D_1000C1D8 += 1;
        }
        sp34 = strlen(D_1000C1D8);
        D_1000C1DC = malloc(sp34 + 2);
        if (D_1000C1DC == NULL) {
            fprintf(__iob + 0x20, "%s: Error: error (), %d: Out of memory\n", D_1000C1D8, 0x3414);
            if (errno < sys_nerr) {
                fprintf(__iob + 0x20, "%s: %s\n", D_1000C1D8, sys_errlist[errno]);
            }
            exit(1);
        }
        sp30 = 0;
        if ((s32) sp34 > 0) {
            do {
                D_1000C1DC[sp30] = 0x20;
                temp_t3 = sp30 + 1;
                sp30 = temp_t3;
            } while (temp_t3 < (s32) sp34);
        }
        D_1000C1DC[sp30] = 0;
    }
    if (arg0 == 5) {
        fprintf(__iob + 0x20, "%s: ", D_1000C1DC);
    } else {
        fprintf(__iob + 0x20, "%s: %s: ", D_1000C1D8, D_1000C1E0[arg0]);
    }
    if (arg1 != NULL) {
        if (arg2 != 0) {
            fprintf(__iob + 0x20, "%s, line %d: ", arg1, arg2);
        } else {
            fprintf(__iob + 0x20, "%s: ", arg1);
        }
    }
    if (arg3 != NULL) {
        if (arg4 != 0) {
            fprintf(__iob + 0x20, "%s, line %d: ", arg3, arg4);
        } else {
            fprintf(__iob + 0x20, "%s: ", arg3);
        }
    }
    if (arg5 == NULL) {
        arg5 = "";
    }
    fprintf(__iob + 0x20, arg5, arg6, arg7, arg8, arg9, argA, argB);
}

void relocate_passes(s8* arg0, s8* arg1, s8* arg2) {
    s8* var_s1;
    s8* var_s2;
    s8* var_s2_10;
    s8* var_s2_11;
    s8* var_s2_12;
    s8* var_s2_2;
    s8* var_s2_3;
    s8* var_s2_4;
    s8* var_s2_5;
    s8* var_s2_6;
    s8* var_s2_7;
    s8* var_s2_8;
    s8* var_s2_9;
    s8* var_s3;
    s8* var_s3_2;
    s8* var_s3_3;
    s8* var_s3_4;
    s8* var_s3_5;
    s8* var_s3_6;
    s8* var_v0;
    s8* var_v0_10;
    s8* var_v0_11;
    s8* var_v0_12;
    s8* var_v0_2;
    s8* var_v0_3;
    s8* var_v0_4;
    s8* var_v0_5;
    s8* var_v0_6;
    s8* var_v0_7;
    s8* var_v0_8;
    s8* var_v0_9;
    u8 temp_t4;
    u8 temp_t7;

    currcomp = "";
    if (arg2 == NULL) {
        arg2 = Bstring;
    }
    if (arg0 == NULL) {
        var_s1 = "hpfekjusmvodqcablyzrP1EXCOnMFISUtKYwx";
        allBstring = arg2;
    } else {
        var_s1 = arg0;
    }
    if ((strcmp(Gnum, "0") == 0) && (compose_first_G0 != 0)) {
        compose_first_G0 = 0;
        compose_G0_libs("PE1COMFIUSXnW");
    }
    if ((u8) *var_s1 != 0) {
        do {
            if ((arg1 != NULL) || (strchr(alltstring, (u8) var_s1->unk_0) == NULL)) {
                temp_t4 = (u8) var_s1->unk_0;
                switch (temp_t4) {
                case 0x68:
                    if (includeB != NULL) {
                        free(includeB);
                    }
                    if (eincludeB != NULL) {
                        free(eincludeB);
                    }
                    if ((arg0 != NULL) || ((arg2 != NULL) && ((u8) *arg2 != 0))) {
                        if (arg1 != NULL) {
                            if (fiveflag != 0) {
                                includeB = mkstr(arg1, "usr/5include", arg2, NULL);
                            } else if (abi_flag != 0) {
                                includeB = mkstr(arg1, "usr/include/abi", arg2, NULL);
                            } else {
                                eincludeB = mkstr(arg1, "usr/include/CC", arg2, NULL);
                                includeB = mkstr(arg1, "usr/include", arg2, NULL);
                            }
                        } else if (fiveflag != 0) {
                            includeB = mkstr(comp_target_root, "usr/5include", arg2, NULL);
                        } else if (abi_flag != 0) {
                            includeB = mkstr(comp_target_root, "usr/include/abi", arg2, NULL);
                        } else {
                            eincludeB = mkstr(comp_target_root, "usr/include/CC", arg2, NULL);
                            includeB = mkstr(comp_target_root, "usr/include", arg2, NULL);
                        }
                    } else {
                        includeB = NULL;
                    }
                    break;
                case 0x70:
                    if (cpp != NULL) {
                        free(cpp);
                    }
                    if (arg1 != NULL) {
                        if ((cppchoice != 1) && (cppchoice != 3)) {
                            var_s2 = "cpp";
                        } else {
                            var_s2 = "acpp";
                        }
                        cpp = mkstr(arg1, var_s2, arg2, NULL);
                    } else {
                        if ((cppchoice != 1) && (cppchoice != 3)) {
                            var_s2_2 = "cpp";
                        } else {
                            var_s2_2 = "acpp";
                        }
                        cpp = mkstr(comp_host_root, "usr/lib/", currcomp, var_s2_2, arg2, NULL);
                    }
                    break;
                case 0x66:
                    if (mpc != NULL) {
                        free(mpc);
                    }
                    if (ccom != NULL) {
                        free(ccom);
                    }
                    if (cfe != NULL) {
                        free(cfe);
                    }
                    if (upas != NULL) {
                        free(upas);
                    }
                    if (fcom != NULL) {
                        free(fcom);
                    }
                    if (upl1 != NULL) {
                        free(upl1);
                    }
                    if (ucob != NULL) {
                        free(ucob);
                    }
                    if (arg1 != NULL) {
                        if (cmp_flag & 0x10000) {
                            mpc = mkstr(arg1, "mpc", arg2, NULL);
                        }
                        if (ansichoice != 0) {
                            var_s2_3 = "accom";
                        } else {
                            var_s2_3 = "ccom";
                        }
                        ccom = mkstr(arg1, var_s2_3, arg2, NULL);
                        if ((c_compiler_choice != 0) || ((compiler == 3) && (D_1000BF74 != 0))) {
                            if (exception_handling != 0) {
                                var_s3 = "edgcpfe.eh";
                            } else {
                                var_s3 = "edgcpfe";
                            }
                            var_s2_4 = var_s3;
                        } else {
                            var_s2_4 = "cfe";
                        }
                        cfe = mkstr(arg1, var_s2_4, arg2, NULL);
                        upas = mkstr(arg1, "upas", arg2, NULL);
                        fcom = mkstr(arg1, "fcom", arg2, NULL);
                        upl1 = mkstr(arg1, "pl1fe", arg2, NULL);
                        ucob = mkstr(arg1, "cobfe", arg2, NULL);
                    } else {
                        if (cmp_flag & 0x10000) {
                            mpc = mkstr(comp_host_root, "usr/lib/", currcomp, "mpc", arg2, NULL);
                        }
                        if (ansichoice != 0) {
                            var_s2_5 = "accom";
                        } else {
                            var_s2_5 = "ccom";
                        }
                        ccom = mkstr(comp_host_root, "usr/lib/", currcomp, var_s2_5, arg2, NULL);
                        if (((compiler == 1) && (c_compiler_choice != 0)) || ((compiler == 3) && (D_1000BF74 != 0))) {
                            if ((c_compiler_choice != 0) || ((compiler == 3) && (D_1000BF74 != 0))) {
                                if (exception_handling != 0) {
                                    var_s3_2 = "edgcpfe.eh";
                                } else {
                                    var_s3_2 = "edgcpfe";
                                }
                                var_s2_6 = var_s3_2;
                            } else {
                                var_s2_6 = "cfe";
                            }
                            var_v0 = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, var_s2_6, arg2, NULL);
                        } else {
                            if ((c_compiler_choice != 0) || ((compiler == 3) && (D_1000BF74 != 0))) {
                                if (exception_handling != 0) {
                                    var_s3_3 = "edgcpfe.eh";
                                } else {
                                    var_s3_3 = "edgcpfe";
                                }
                                var_s2_7 = var_s3_3;
                            } else {
                                var_s2_7 = "cfe";
                            }
                            var_v0 = mkstr(comp_host_root, "usr/lib/", currcomp, var_s2_7, arg2, NULL);
                        }
                        cfe = var_v0;
                        upas = mkstr(comp_host_root, "usr/lib/", currcomp, "upas", arg2, NULL);
                        fcom = mkstr(comp_host_root, "usr/lib/", currcomp, "fcom", arg2, NULL);
                        upl1 = mkstr(comp_host_root, "usr/lib/", currcomp, "pl1fe", arg2, NULL);
                        ucob = mkstr(comp_host_root, "usr/lib/", currcomp, "cobfe", arg2, NULL);
                    }
                    break;
                case 0x65:
                    if (pl1err != NULL) {
                        free(pl1err);
                    }
                    if (arg1 != NULL) {
                        pl1err = mkstr(arg1, "pl1error", arg2, NULL);
                    } else {
                        pl1err = mkstr(comp_host_root, "usr/lib/", currcomp, "pl1error", arg2, NULL);
                    }
                    break;
                case 0x6B:
                    if (ulpi != NULL) {
                        free(ulpi);
                    }
                    if (arg1 != NULL) {
                        ulpi = mkstr(arg1, "ulpi", arg2, NULL);
                    } else {
                        ulpi = mkstr(comp_host_root, "usr/lib/", currcomp, "ulpi", arg2, NULL);
                    }
                    break;
                case 0x6A:
                    if (ujoin != NULL) {
                        free(ujoin);
                    }
                    if (arg1 != NULL) {
                        ujoin = mkstr(arg1, "ujoin", arg2, NULL);
                    } else {
                        ujoin = mkstr(comp_host_root, "usr/lib/", currcomp, "ujoin", arg2, NULL);
                    }
                    break;
                case 0x75:
                    if (uld != NULL) {
                        free(uld);
                    }
                    if (arg1 != NULL) {
                        uld = mkstr(arg1, "uld", arg2, NULL);
                    } else {
                        uld = mkstr(comp_host_root, "usr/lib/", currcomp, "uld", arg2, NULL);
                    }
                    break;
                case 0x73:
                    if (usplit != NULL) {
                        free(usplit);
                    }
                    if (arg1 != NULL) {
                        usplit = mkstr(arg1, "usplit", arg2, NULL);
                    } else {
                        usplit = mkstr(comp_host_root, "usr/lib/", currcomp, "usplit", arg2, NULL);
                    }
                    break;
                case 0x71:
                    if (uopt0 != NULL) {
                        free(uopt0);
                    }
                    if (arg1 != NULL) {
                        uopt0 = mkstr(arg1, "uopt0", arg2, NULL);
                    } else {
                        uopt0 = mkstr(comp_host_root, "usr/lib/", currcomp, "uopt0", arg2, NULL);
                    }
                    break;
                case 0x64:
                    if (ddopt != NULL) {
                        free(ddopt);
                    }
                    if (arg1 != NULL) {
                        ddopt = mkstr(arg1, "ddopt", arg2, NULL);
                    } else {
                        ddopt = mkstr(comp_host_root, "usr/lib/", currcomp, "ddopt", arg2, NULL);
                    }
                    break;
                case 0x6D:
                    if (umerge != NULL) {
                        free(umerge);
                    }
                    if (arg1 != NULL) {
                        umerge = mkstr(arg1, "umerge", arg2, NULL);
                    } else {
                        umerge = mkstr(comp_host_root, "usr/lib/", currcomp, "umerge", arg2, NULL);
                    }
                    break;
                case 0x76:
                    if (uloop != NULL) {
                        free(uloop);
                    }
                    if (arg1 != NULL) {
                        uloop = mkstr(arg1, "uloop", arg2, NULL);
                    } else {
                        uloop = mkstr(comp_host_root, "usr/lib/", currcomp, "uloop", arg2, NULL);
                    }
                    break;
                case 0x6F:
                    if (opt != NULL) {
                        free(opt);
                    }
                    if (arg1 != NULL) {
                        opt = mkstr(arg1, "uopt", arg2, NULL);
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (D_1000BF8C != 0)) {
                        opt = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "uopt", arg2, NULL);
                    } else {
                        opt = mkstr(comp_host_root, "usr/lib/", currcomp, "uopt", arg2, NULL);
                    }
                    break;
                case 0x63:
                    if (gen != NULL) {
                        free(gen);
                    }
                    if (arg1 != NULL) {
                        gen = mkstr(arg1, "ugen", arg2, NULL);
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (D_1000BF8C != 0)) {
                        gen = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "ugen", arg2, NULL);
                    } else {
                        gen = mkstr(comp_host_root, "usr/lib/", currcomp, "ugen", arg2, NULL);
                    }
                    break;
                case 0x61:
                    if (as0 != NULL) {
                        free(as0);
                    }
                    if (arg1 != NULL) {
                        as0 = mkstr(arg1, "as0", arg2, NULL);
                    } else {
                        as0 = mkstr(comp_host_root, "usr/lib/", currcomp, "as0", arg2, NULL);
                    }
                    break;
                case 0x62:
                    if (as1 != NULL) {
                        free(as1);
                    }
                    if (arg1 != NULL) {
                        as1 = mkstr(arg1, "as1", arg2, NULL);
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (D_1000BF8C != 0)) {
                        as1 = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "as1", arg2, NULL);
                    } else {
                        as1 = mkstr(comp_host_root, "usr/lib/", currcomp, "as1", arg2, NULL);
                    }
                    break;
                case 0x77:
                    if (prelinker != NULL) {
                        free(prelinker);
                    }
                    if (arg1 != NULL) {
                        prelinker = mkstr(arg1, "edg_prelink", arg2, NULL);
                    } else {
                        prelinker = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "edg_prelink", arg2, NULL);
                    }
                    break;
                case 0x6C:
                    if (ld != NULL) {
                        free(ld);
                    }
                    if (patch != NULL) {
                        free(patch);
                    }
                    if (filter != NULL) {
                        free(filter);
                    }
                    if (arg1 != NULL) {
                        ld = mkstr(arg1, LD, arg2, NULL);
                        patch = mkstr(arg1, "c++patch", arg2, NULL);
                        filter = mkstr(arg1, "c++filt", arg2, NULL);
                    } else {
                        if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (D_1000BF90 != 0)) {
                            var_v0_2 = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, LD, arg2, NULL);
                        } else if (irix4 != 0) {
                            var_v0_2 = mkstr(comp_host_root, "usr/bin/", currcomp, LD, arg2, NULL);
                        } else {
                            var_v0_2 = mkstr(comp_host_root, "usr/lib/", currcomp, LD, arg2, NULL);
                        }
                        ld = var_v0_2;
                        patch = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "c++patch", arg2, NULL);
                        filter = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "c++filt", arg2, NULL);
                    }
                    break;
                case 0x74:
                    if (btou != NULL) {
                        free(btou);
                    }
                    if (utob != NULL) {
                        free(utob);
                    }
                    if (arg1 != NULL) {
                        btou = mkstr(arg1, "btou", arg2, NULL);
                        utob = mkstr(arg1, "utob", arg2, NULL);
                    } else {
                        btou = mkstr(comp_host_root, "usr/lib/", currcomp, "btou", arg2, NULL);
                        utob = mkstr(comp_host_root, "usr/lib/", currcomp, "utob", arg2, NULL);
                    }
                    break;
                case 0x78:
                    if (strip != NULL) {
                        free(strip);
                    }
                    if (arg1 != NULL) {
                        strip = mkstr(arg1, "strip", arg2, NULL);
                    } else {
                        strip = mkstr(comp_host_root, "usr/bin/", currcomp, "strip", arg2, NULL);
                    }
                    break;
                case 0x79:
                    if (ftoc != NULL) {
                        free(ftoc);
                    }
                    if (arg1 != NULL) {
                        ftoc = mkstr(arg1, "ftoc", arg2, NULL);
                    } else {
                        ftoc = mkstr(comp_host_root, "usr/lib/", currcomp, "ftoc", arg2, NULL);
                    }
                    break;
                case 0x7A:
                    if (cord != NULL) {
                        free(cord);
                    }
                    if (arg1 != NULL) {
                        cord = mkstr(arg1, "cord", arg2, NULL);
                    } else {
                        cord = mkstr(comp_host_root, "usr/bin/", currcomp, "cord", arg2, NULL);
                    }
                    break;
                case 0x72:
                    if (arg1 != NULL) {
                        if (pflag != 0) {
                            crtx = mkstr(arg1, MCRTX, arg2, NULL);
                            if (exception_handling != 0) {
                                var_s2_8 = "c++init_eh.o";
                            } else {
                                var_s2_8 = "c++init.o";
                            }
                            cxx_init = mkstr(arg1, var_s2_8, arg2, NULL);
                            delta_init = mkstr(arg1, "delta_init.o", arg2, NULL);
                            crtn = mkstr(arg1, "crtn.o", arg2, NULL);
                        } else {
                            crtx = mkstr(arg1, CRTX, arg2, NULL);
                            if (exception_handling != 0) {
                                var_s2_9 = "c++init_eh.o";
                            } else {
                                var_s2_9 = "c++init.o";
                            }
                            cxx_init = mkstr(arg1, var_s2_9, arg2, NULL);
                            delta_init = mkstr(arg1, "delta_init.o", arg2, NULL);
                            crtn = mkstr(arg1, "crtn.o", arg2, NULL);
                        }
                    } else if (pflag != 0) {
                        if (abi_flag != 0) {
                            crtx = func_0042FD7C(mkstr(MCRTX, arg2, NULL), dirs_for_abi_crtn.entries);
                            crtn = func_0042FD7C(mkstr("crtn.o", arg2, NULL), dirs_for_abi_crtn.entries);
                            if (exception_handling != 0) {
                                var_s3_4 = "c++init_eh.o";
                            } else {
                                var_s3_4 = "c++init.o";
                            }
                            cxx_init = func_0042FD7C(mkstr(var_s3_4, arg2, NULL), dirs_for_abi_crtn.entries);
                            delta_init = func_0042FD7C(mkstr("delta_init.o", arg2, NULL), dirs_for_abi_crtn.entries);
                        } else if (non_shared != 0) {
                            crtx = func_0042FD7C(mkstr(MCRTX, arg2, NULL), dirs_for_nonshared_crtn.entries);
                            crtn = func_0042FD7C(mkstr("crtn.o", arg2, NULL), dirs_for_nonshared_crtn.entries);
                            if (exception_handling != 0) {
                                var_s3_5 = "c++init_eh.o";
                            } else {
                                var_s3_5 = "c++init.o";
                            }
                            cxx_init = func_0042FD7C(mkstr(var_s3_5, arg2, NULL), dirs_for_nonshared_crtn.entries);
                            delta_init = func_0042FD7C(mkstr("delta_init.o", arg2, NULL), dirs_for_nonshared_crtn.entries);
                        } else {
                            crtx = func_0042FD7C(mkstr(MCRTX, arg2, NULL), dirs_for_crtn.entries);
                            crtn = func_0042FD7C(mkstr("crtn.o", arg2, NULL), dirs_for_crtn.entries);
                            if (exception_handling != 0) {
                                var_s3_6 = "c++init_eh.o";
                            } else {
                                var_s3_6 = "c++init.o";
                            }
                            cxx_init = func_0042FD7C(mkstr(var_s3_6, arg2, NULL), dirs_for_crtn.entries);
                            delta_init = func_0042FD7C(mkstr("delta_init.o", arg2, NULL), dirs_for_crtn.entries);
                        }
                    } else if (abi_flag != 0) {
                        crtx = func_0042FD7C(CRTX, dirs_for_abi_crtn.entries);
                        crtn = func_0042FD7C("crtn.o", dirs_for_abi_crtn.entries);
                        if (exception_handling != 0) {
                            var_s2_10 = "c++init_eh.o";
                        } else {
                            var_s2_10 = "c++init.o";
                        }
                        cxx_init = func_0042FD7C(var_s2_10, dirs_for_abi_crtn.entries);
                        delta_init = func_0042FD7C("delta_init.o", dirs_for_abi_crtn.entries);
                    } else if (non_shared != 0) {
                        crtx = func_0042FD7C(CRTX, dirs_for_nonshared_crtn.entries);
                        crtn = func_0042FD7C("crtn.o", dirs_for_nonshared_crtn.entries);
                        if (exception_handling != 0) {
                            var_s2_11 = "c++init_eh.o";
                        } else {
                            var_s2_11 = "c++init.o";
                        }
                        cxx_init = func_0042FD7C(var_s2_11, dirs_for_nonshared_crtn.entries);
                        delta_init = func_0042FD7C("delta_init.o", dirs_for_nonshared_crtn.entries);
                    } else {
                        crtx = func_0042FD7C(CRTX, dirs_for_crtn.entries);
                        crtn = func_0042FD7C("crtn.o", dirs_for_crtn.entries);
                        if (exception_handling != 0) {
                            var_s2_12 = "c++init_eh.o";
                        } else {
                            var_s2_12 = "c++init.o";
                        }
                        cxx_init = func_0042FD7C(var_s2_12, dirs_for_crtn.entries);
                        delta_init = func_0042FD7C("delta_init.o", dirs_for_crtn.entries);
                    }
                    break;
                case 0x50:
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                            var_v0_3 = mkstr("-L", arg1, "-B", arg2, LibP, NULL);
                        } else {
                            var_v0_3 = mkstr("-L", arg1, LibP, NULL);
                        }
                        libp = var_v0_3;
                        libp_b = mkstr(arg1, "libp.b", arg2, NULL);
                    } else {
                        libp = "-lp";
                        if (non_shared != 0) {
                            libp_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libp.b", arg2, NULL);
                        } else {
                            libp_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libp.b", arg2, NULL);
                        }
                    }
                    break;
                case 0x31:
                    if (arg1 != NULL) {
                        libpl1 = mkstr(arg1, LibPl1, arg2, NULL);
                        libpl1_b = mkstr(arg1, "libpl1.b", arg2, NULL);
                    } else {
                        libpl1 = "-lpl1";
                        if (non_shared != 0) {
                            libpl1_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libpl1.b", arg2, NULL);
                        } else {
                            libpl1_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libpl1.b", arg2, NULL);
                        }
                    }
                    break;
                case 0x45:
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                            libexc = mkstr("-L", arg1, "-B", arg2, LibExc, NULL);
                            var_v0_4 = mkstr("-L", arg1, "-B", arg2, LibMld, NULL);
                        } else {
                            libexc = mkstr("-L", arg1, LibExc, NULL);
                            var_v0_4 = mkstr("-L", arg1, LibMld, NULL);
                        }
                        libmld = var_v0_4;
                        libexc_b = mkstr(arg1, "libexc.b", arg2, NULL);
                    } else {
                        if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                            libexc = mkstr("-L", "-B", arg2, LibExc, NULL);
                            libmld = mkstr("-L", "-B", arg2, LibMld, NULL);
                        } else {
                            libexc = "-lexc";
                            libmld = "-lmld";
                        }
                        if (non_shared != 0) {
                            libexc_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libexc.b", arg2, NULL);
                        } else {
                            libexc_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libexc.b", arg2, NULL);
                        }
                    }
                    break;
                case 0x57:
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                            var_v0_5 = mkstr("-L", arg1, "-B", arg2, LibDw, NULL);
                        } else {
                            var_v0_5 = mkstr("-L", arg1, LibDw, NULL);
                        }
                        libdw = var_v0_5;
                        libdw_path = mkstr(arg1, "libdw.a", arg2, NULL);
                        libdw_b = mkstr(arg1, "libdw.b", arg2, NULL);
                    } else {
                        if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                            if (non_shared != 0) {
                                var_v0_6 = mkstr("-L", comp_target_root, "usr/lib/nonshared/", currcomp, " -B", arg2, LibDw, 0);
                            } else {
                                var_v0_6 = mkstr("-L", comp_target_root, "usr/lib/", currcomp, " -B", arg2, LibDw, 0);
                            }
                        } else if (non_shared != 0) {
                            var_v0_6 = mkstr("-L", comp_target_root, "usr/lib/", currcomp, LibDw, NULL);
                        } else {
                            var_v0_6 = mkstr("-L", comp_target_root, "usr/lib/", currcomp, LibDw, NULL);
                        }
                        libdw = var_v0_6;
                        if (non_shared != 0) {
                            libdw_path = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libdw.a", arg2, NULL);
                            libdw_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libdw.b", arg2, NULL);
                        } else {
                            libdw_path = mkstr(comp_target_root, "usr/lib/", currcomp, "libdw.a", arg2, NULL);
                            libdw_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libdw.b", arg2, NULL);
                        }
                    }
                    break;
                case 0x58:
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                            var_v0_7 = mkstr("-L", arg1, " -B", arg2, LibXmalloc, NULL);
                        } else {
                            var_v0_7 = mkstr("-L", arg1, LibXmalloc, NULL);
                        }
                        libxmalloc = var_v0_7;
                        libxmalloc_b = mkstr(arg1, "libxmalloc.b", arg2, NULL);
                    } else {
                        libxmalloc = "-lxmalloc";
                        if (non_shared != 0) {
                            libxmalloc_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libxmalloc.b", arg2, NULL);
                        } else {
                            libxmalloc_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libxmalloc.b", arg2, NULL);
                        }
                    }
                    break;
                case 0x4F:
                    if (arg1 != NULL) {
                        libsort = mkstr(arg1, LibSort, arg2, NULL);
                        libsort_b = mkstr(arg1, "libsort.b", arg2, NULL);
                    } else {
                        libsort = "-lsort";
                        if (non_shared != 0) {
                            libsort_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libsort.b", arg2, NULL);
                        } else {
                            libsort_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libsort.b", arg2, NULL);
                        }
                    }
                    break;
                case 0x6E:
                    if (pflag != 0) {
                        if (arg1 != NULL) {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                libprof = mkstr("-L", arg1, " -B", arg2, LibProf1, NULL);
                                libgprof = mkstr("-L", arg1, " -B", arg2, LibGProf1, NULL);
                            } else {
                                libprof = mkstr("-L", arg1, LibProf1, NULL);
                                libgprof = mkstr("-L", arg1, LibGProf1, NULL);
                            }
                        } else if (non_shared != 0) {
                            libprof = func_0042FD7C("libprof.a", dirs_for_nonshared_crtn.entries);
                            libgprof = func_0042FD7C("libgprof.a", dirs_for_nonshared_crtn.entries);
                        } else {
                            libprof = func_0042FD7C("libprof.a", dirs_for_crtn.entries);
                            libgprof = func_0042FD7C("libgprof.a", dirs_for_crtn.entries);
                        }
                    }
                    break;
                case 0x4D:
                    if (arg1 != NULL) {
                        switch (chip_targ) {        /* switch 2; irregular */
                        default:                    /* switch 2 */
                        case 0:                     /* switch 2 */
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                var_v0_8 = mkstr(arg1, " -B", arg2, LibM, NULL);
                            } else {
                                var_v0_8 = mkstr("-L", arg1, LibM, NULL);
                            }
                            libm = var_v0_8;
                            libm_b = mkstr(arg1, "libm.b", arg2, NULL);
                            break;
                        case 1:                     /* switch 2 */
                            libm = mkstr(arg1, "libm_mips2.a", arg2, NULL);
                            libm_b = mkstr(arg1, "libm_mips2.b", arg2, NULL);
                            break;
                        case 2:                     /* switch 2 */
                            libm = mkstr(arg1, "libm_mips3.a", arg2, NULL);
                            libm_b = mkstr(arg1, "libm_mips3.b", arg2, NULL);
                            break;
                        }
                    } else {
                        switch (chip_targ) {        /* switch 1; irregular */
                        default:                    /* switch 1 */
                        case 0:                     /* switch 1 */
                            libm = "-lm";
                            if (non_shared != 0) {
                                libm_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm.b", arg2, NULL);
                            } else {
                                libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm.b", arg2, NULL);
                            }
                            break;
                        case 1:                     /* switch 1 */
                            if (non_shared != 0) {
                                libm = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips2.a", arg2, NULL);
                                libm_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips2.b", arg2, NULL);
                            } else {
                                libm = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips2.a", arg2, NULL);
                                libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips2.b", arg2, NULL);
                            }
                            break;
                        case 2:                     /* switch 1 */
                            if (non_shared != 0) {
                                libm = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips3.a", arg2, NULL);
                                libm_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips3.b", arg2, NULL);
                            } else {
                                libm = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips3.a", arg2, NULL);
                                libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips3.b", arg2, NULL);
                            }
                            break;
                        }
                    }
                    break;
                case 0x46:
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                            var_v0_9 = mkstr("-L", arg1, " -B", arg2, LibF77, NULL);
                        } else {
                            var_v0_9 = mkstr("-L", arg1, LibF77, NULL);
                        }
                        libF77 = var_v0_9;
                        libF77_b = mkstr(arg1, "libF77.b", arg2, NULL);
                    } else {
                        libftn = "-lftn";
                        libF77 = "-lF77";
                        if (non_shared != 0) {
                            libF77_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libF77.b", arg2, NULL);
                        } else {
                            libF77_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libF77.b", arg2, NULL);
                        }
                    }
                    break;
                case 0x49:
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                            var_v0_10 = mkstr("-L", arg1, " -B", arg2, LibI77, NULL);
                        } else {
                            var_v0_10 = mkstr("-L", arg1, LibI77, NULL);
                        }
                        libI77 = var_v0_10;
                        libI77_b = mkstr(arg1, "libI77.b", arg2, NULL);
                    } else {
                        libI77 = "-lI77";
                        if (non_shared != 0) {
                            libI77_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libI77.b", arg2, NULL);
                        } else {
                            libI77_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libI77.b", arg2, NULL);
                        }
                    }
                    break;
                case 0x53:
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                            var_v0_11 = mkstr("-L", arg1, " -B", arg2, LibIsam, NULL);
                        } else {
                            var_v0_11 = mkstr("-L", arg1, LibIsam, NULL);
                        }
                        libisam = var_v0_11;
                        libisam_b = mkstr(arg1, "libisam.b", arg2, NULL);
                    } else {
                        libisam = "-lisam";
                        if (non_shared != 0) {
                            libisam_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libisam.b", arg2, NULL);
                        } else {
                            libisam_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libisam.b", arg2, NULL);
                        }
                    }
                    break;
                case 0x55:
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                            var_v0_12 = mkstr("-L", arg1, " -B", arg2, LibU77, NULL);
                        } else {
                            var_v0_12 = mkstr("-L", arg1, LibU77, NULL);
                        }
                        libU77 = var_v0_12;
                        libU77_b = mkstr(arg1, "libU77.b", arg2, NULL);
                    } else {
                        libU77 = "-lU77";
                        if (non_shared != 0) {
                            libU77_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libU77.b", arg2, NULL);
                        } else {
                            libU77_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libU77.b", arg2, NULL);
                        }
                    }
                    break;
                case 0x4B:
                    if (arg1 != NULL) {
                        fopt = mkstr(arg1, "fopt", arg2, NULL);
                        copt = mkstr(arg1, "copt", arg2, NULL);
                        pfa = mkstr(arg1, "pfa", arg2, NULL);
                        pca = mkstr(arg1, "pca", arg2, NULL);
                    } else {
                        fopt = mkstr(comp_host_root, "usr/lib/", "fopt", arg2, NULL);
                        copt = mkstr(comp_host_root, "usr/lib/", "copt", arg2, NULL);
                        pfa = mkstr(comp_host_root, "usr/lib/", "pfa", arg2, NULL);
                        pca = mkstr(comp_host_root, "usr/lib/", "pca", arg2, NULL);
                    }
                    break;
                case 0x59:
                    if (arg1 != NULL) {
                        libI77_mp = mkstr(arg1, "libI77_mp.a", arg2, NULL);
                        libc_mp = mkstr(arg1, "libc_mp.a", arg2, NULL);
                    } else {
                        libI77_mp = "-lI77_mp";
                        libc_mp = "-lc_mp";
                    }
                    break;
                default:
                    error(1, NULL, 0, NULL, 0, "Unknown character in -t%c\n", (s32) (u8) var_s1->unk_0);
                    exit(2);
                    break;
                }
            }
            temp_t7 = var_s1->unk_1;
            var_s1 += 1;
        } while (temp_t7 != 0);
    }
}

void newrunlib(void) {
    if (fiveflag != 0) {
        runlib_base = "usr/5lib";
    } else if (irix4 != 0) {
        runlib_base = "/usr/irix4/";
    } else {
        runlib_base = "/";
    }
    if (gethostsex() == targetsex) {
        runlib = runlib_base;
    } else if (targetsex == 0) {
        runlib = "eb/";
    } else {
        runlib = "el/";
    }
    relocate_passes("rP1EXCOnMFISU", NULL, NULL);
}

void compose_G0_libs(s8* arg0) {
    s8* var_v0;
    s8** var_at;
    u8 temp_t9;

    if ((u8) *arg0 != 0) {
        do {
            temp_t9 = (u8) *arg0;
            switch (temp_t9) {
            case 0x50:
                var_v0 = mkstr(LibP, "_G0", NULL);
                var_at = &LibP;
block_16:
                *var_at = var_v0;
                break;
            case 0x45:
                var_v0 = mkstr(LibExc, "_G0", NULL);
                var_at = &LibExc;
                goto block_16;
            case 0x31:
                var_v0 = mkstr(LibPl1, "_G0", NULL);
                var_at = &LibPl1;
                goto block_16;
            case 0x43:
                var_v0 = mkstr(LibCob, "_G0", NULL);
                var_at = &LibCob;
                goto block_16;
            case 0x4F:
                var_v0 = mkstr(LibSort, "_G0", NULL);
                var_at = &LibSort;
                goto block_16;
            case 0x4D:
                var_v0 = mkstr(LibM, "_G0", NULL);
                var_at = &LibM;
                goto block_16;
            case 0x46:
                var_v0 = mkstr(LibF77, "_G0", NULL);
                var_at = &LibF77;
                goto block_16;
            case 0x49:
                var_v0 = mkstr(LibI77, "_G0", NULL);
                var_at = &LibI77;
                goto block_16;
            case 0x55:
                var_v0 = mkstr(LibU77, "_G0", NULL);
                var_at = &LibU77;
                goto block_16;
            case 0x53:
                var_v0 = mkstr(LibIsam, "_G0", NULL);
                var_at = &LibIsam;
                goto block_16;
            case 0x57:
                var_v0 = mkstr(LibDw, "_G0", NULL);
                var_at = &LibDw;
                goto block_16;
            case 0x58:
                var_v0 = mkstr(LibXmalloc, "_G0", NULL);
                var_at = &LibXmalloc;
                goto block_16;
            case 0x6E:
                var_v0 = mkstr(LibProf1, "_G0", NULL);
                var_at = &LibProf1;
                goto block_16;
            }
            arg0 += 1;
        } while ((u8) arg0[1] != 0);
    }
}

void compose_reg_libs(s8* arg0) {
    s8* var_v0;
    s8** var_at;
    u8 temp_t9;

    if ((u8) *arg0 != 0) {
        do {
            temp_t9 = (u8) *arg0;
            switch (temp_t9) {
            case 0x50:
                var_v0 = mkstr("libp", ".a", NULL);
                var_at = &LibP;
block_15:
                *var_at = var_v0;
                break;
            case 0x45:
                var_v0 = mkstr("libexc", ".a", NULL);
                var_at = &LibExc;
                goto block_15;
            case 0x31:
                var_v0 = mkstr("libpl1", ".a", NULL);
                var_at = &LibPl1;
                goto block_15;
            case 0x43:
                var_v0 = mkstr("libcob", ".a", NULL);
                var_at = &LibCob;
                goto block_15;
            case 0x4F:
                var_v0 = mkstr("libsort", ".a", NULL);
                var_at = &LibSort;
                goto block_15;
            case 0x4D:
                var_v0 = mkstr("libm", ".a", NULL);
                var_at = &LibM;
                goto block_15;
            case 0x46:
                var_v0 = mkstr("libF77", ".a", NULL);
                var_at = &LibF77;
                goto block_15;
            case 0x49:
                var_v0 = mkstr("libI77", ".a", NULL);
                var_at = &LibI77;
                goto block_15;
            case 0x55:
                var_v0 = mkstr("libU77", ".a", NULL);
                var_at = &LibU77;
                goto block_15;
            case 0x53:
                var_v0 = mkstr("libisam", ".a", NULL);
                var_at = &LibIsam;
                goto block_15;
            case 0x6E:
                LibProf1 = mkstr("libprof", ".a", NULL);
                var_v0 = mkstr("libgprof", ".a", NULL);
                var_at = &LibGProf1;
                goto block_15;
            case 0x58:
                var_v0 = mkstr("libxmalloc", ".a", NULL);
                var_at = &LibXmalloc;
                goto block_15;
            }
            arg0 += 1;
        } while ((u8) arg0[1] != 0);
    }
}

s8* mkstr(s8* arg0, f64 arg1, s8* arg2, s8* arg3) {
    f64 sp60;
    f64 sp58;
    void* sp48;
    s32 temp_t1;
    s32 temp_t3;
    s32 temp_t8;
    s32 temp_t9;
    s8* temp_v0;
    s8* var_s1;
    s8* var_s1_2;
    u32 temp_s3;
    u32 var_s2;
    void* temp_t5;
    void* temp_t7;

    temp_t7 = &arg0 - 1;
    temp_t9 = (s32) (temp_t7 + 3) & ~3;
    sp48 = temp_t7;
    sp60 = arg0;
    sp58 = arg1;
    sp48 = temp_t9 + 4;
    var_s1 = *temp_t9;
    var_s2 = 1;
    if (var_s1 != NULL) {
        do {
            temp_s3 = strlen(var_s1);
            temp_t3 = (s32) (sp48 + 3) & ~3;
            sp48 = temp_t3 + 4;
            var_s1 = *temp_t3;
            var_s2 += temp_s3;
        } while (var_s1 != NULL);
    }
    temp_v0 = malloc(var_s2);
    if (temp_v0 == NULL) {
        error(1, NULL, 0, "mkstr ()", 0x38BC, "out of memory\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
    }
    temp_t5 = &arg0 - 1;
    *temp_v0 = 0;
    temp_t8 = (s32) (temp_t5 + 3) & ~3;
    sp48 = temp_t5;
    sp48 = temp_t8 + 4;
    var_s1_2 = *temp_t8;
    if (var_s1_2 != NULL) {
        do {
            strcat(temp_v0, var_s1_2);
            temp_t1 = (s32) (sp48 + 3) & ~3;
            sp48 = temp_t1 + 4;
            var_s1_2 = *temp_t1;
        } while (var_s1_2 != NULL);
    }
    return temp_v0;
}

void mklist(list* arg0) {
    s8** temp_v0;

    temp_v0 = malloc(0x50U);
    arg0->entries = temp_v0;
    if (temp_v0 == NULL) {
        error(1, NULL, 0, "mklist ()", 0x38E1, "out of memory\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
    }
    arg0->capacity = 0x14;
    arg0->length = 0;
    *arg0->entries = NULL;
}

void addstr(list* arg0, s8* str) {
    s32 temp_t7;
    s8** temp_v0;

    temp_t7 = arg0->capacity;
    if ((arg0->length + 1) >= temp_t7) {
        temp_v0 = realloc(arg0->entries, (temp_t7 * 4) + 0x50);
        arg0->entries = temp_v0;
        if (temp_v0 == NULL) {
            error(1, NULL, 0, "addstr()", 0x3903, "out of memory\n");
            if (errno < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity += 0x14;
    }
    arg0->entries[arg0->length] = str;
    arg0->length += 1;
    arg0->entries[arg0->length] = NULL;
}

void addspacedstr(list* arg0, s8* str) {
    s8* sp34;
    s32 temp_t1;
    s8** temp_v0;

    sp34 = str;
    do {
        sp34 = strchr(sp34, 0x20U);
        if (sp34 != NULL) {
            *sp34 = 0;
            sp34 += 1;
        }
        temp_t1 = arg0->capacity;
        if ((arg0->length + 1) >= temp_t1) {
            temp_v0 = realloc(arg0->entries, (temp_t1 * 4) + 0x50);
            arg0->entries = temp_v0;
            if (temp_v0 == NULL) {
                error(1, NULL, 0, "addspacedstr()", 0x392F, "out of memory\n");
                if (errno < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                exit(1);
            }
            arg0->capacity += 0x14;
        }
        arg0->entries[arg0->length] = str;
        arg0->length += 1;
        arg0->entries[arg0->length] = NULL;
        str = sp34;
    } while (sp34 != NULL);
}

s8* newstr(s8* src) {
    s8* sp34;

    sp34 = malloc(strlen(src) + 1);
    if (sp34 != NULL) {
        strcpy(sp34, src);
    } else {
        error(1, NULL, 0, NULL, 0, "newstr: unable to malloc for string %s\n", src);
        exit(2);
    }
    return sp34;
}

s32 save_place(list* arg0) {
    s32 sp34;
    s32 temp_t7;
    s8** temp_v0;

    temp_t7 = arg0->capacity;
    if ((arg0->length + 1) >= temp_t7) {
        temp_v0 = realloc(arg0->entries, (temp_t7 * 4) + 0x50);
        arg0->entries = temp_v0;
        if (temp_v0 == NULL) {
            error(1, NULL, 0, "save_place()", 0x3967, "out of memory\n");
            if (errno < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity += 0x14;
    }
    sp34 = arg0->length;
    arg0->length += 1;
    arg0->entries[arg0->length] = NULL;
    return sp34;
}

void set_place(list* arg0, s8* str, s32 place) {
    if ((place < 0) || (place >= arg0->length)) {
        error(0, NULL, 0, "set_place ()", 0x3986, "place out of range");
        exit(1);
    }
    arg0->entries[place] = str;
}

void addlist(list* arg0, list* arg1) {
    s32 sp34;
    s32 temp_t0;
    s32 temp_t7;
    s8* temp_t2;
    s8** temp_v0;

    temp_t7 = arg0->capacity;
    if ((arg0->length + arg1->length + 1) >= temp_t7) {
        temp_v0 = realloc(arg0->entries, ((temp_t7 + arg1->capacity) * 4) + 0x50);
        arg0->entries = temp_v0;
        if (temp_v0 == NULL) {
            error(1, NULL, 0, "addlist ()", 0x39A4, "out of memory\n");
            if (errno < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity = arg0->capacity + arg1->capacity + 0x14;
    }
    sp34 = 0;
    if (arg1->length > 0) {
        do {
            temp_t2 = arg1->entries[sp34];
            if (temp_t2 != NULL) {
                arg0->entries[arg0->length] = temp_t2;
                arg0->length += 1;
            }
            temp_t0 = sp34 + 1;
            sp34 = temp_t0;
        } while (temp_t0 < arg1->length);
    }
    arg0->entries[arg0->length] = NULL;
}

void adduldlist(list* arg0, list* arg1, list* arg2) {
    s32 sp3C;
    s32 sp38;
    s32 temp_t3;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t9;
    s8* temp_t6;
    s8* temp_t9_2;
    s8** temp_v0;

    temp_t7 = arg0->capacity;
    if ((arg0->length + arg1->length + arg2->length + 1) >= temp_t7) {
        temp_v0 = realloc(arg0->entries, ((temp_t7 + arg1->capacity + arg2->capacity) * 4) + 0x50);
        arg0->entries = temp_v0;
        if (temp_v0 == NULL) {
            error(1, NULL, 0, "addlist ()", 0x39CB, "out of memory\n");
            if (errno < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity = arg0->capacity + (arg1->capacity + arg2->capacity) + 0x14;
    }
    sp3C = 0;
    if ((arg2->length > 0) && (*arg2->entries != NULL)) {
loop_8:
        arg0->entries[arg0->length] = arg2->entries[sp3C];
        arg0->length += 1;
        temp_t3 = sp3C + 1;
        sp3C = temp_t3;
        if (temp_t3 < arg2->length) {
            if (arg2->entries[temp_t3] != NULL) {
                goto loop_8;
            }
        }
    }
    sp38 = 0;
    if (arg1->length > 0) {
        do {
            temp_t6 = arg1->entries[sp38];
            if (temp_t6 != NULL) {
                arg0->entries[arg0->length] = temp_t6;
                arg0->length += 1;
            }
            temp_t9 = sp38 + 1;
            sp38 = temp_t9;
        } while (temp_t9 < arg1->length);
    }
    if (sp3C < arg2->length) {
        do {
            temp_t9_2 = arg2->entries[sp3C];
            if (temp_t9_2 != NULL) {
                arg0->entries[arg0->length] = temp_t9_2;
                arg0->length += 1;
            }
            temp_t8 = sp3C + 1;
            sp3C = temp_t8;
        } while (temp_t8 < arg2->length);
    }
    arg0->entries[arg0->length] = NULL;
}

s32 nodup(list* arg0, s8* str) {
    s32 var_s0;
    s8* temp_s1;

    var_s0 = 0;
    if (arg0->length > 0) {
loop_1:
        temp_s1 = arg0->entries[var_s0];
        if ((temp_s1 != NULL) && (strcmp(temp_s1, str) == 0)) {
            return 0;
        }
        var_s0 += 1;
        if (var_s0 >= arg0->length) {
            goto block_5;
        }
        goto loop_1;
    }
block_5:
    return 1;
}

s8 getsuf(s8* path) {
    s32 sp34;
    s32 sp30;
    u8 sp2F;
    s8* sp28;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t5;
    s32 temp_t6;
    u8 temp_t4;
    u8 temp_t7;

    sp34 = 0;
    sp28 = path;
    temp_t7 = (u8) path->unk_0;
    path += 1;
    sp2F = temp_t7;
    if (temp_t7 != 0) {
        do {
            if (sp2F == 0x2F) {
                sp34 = 0;
                sp28 = path;
            } else {
                sp34 += 1;
            }
            temp_t4 = (u8) path->unk_0;
            path += 1;
            sp2F = temp_t4;
        } while (temp_t4 != 0);
    }
    if (sp34 < 3) {
        goto block_24;
    }
    if (path->unk_-3 == 0x2E) {
        if (path->unk_-2 == 0x43) {
            return 6;
        }
        return (s8) path->unk_-2;
    }
    temp_t2 = sp34 - 2;
    sp30 = temp_t2;
    if (temp_t2 > 0) {
loop_12:
        if ((u8) sp28[sp30] != 0x2E) {
            temp_t6 = sp30 - 1;
            sp30 = temp_t6;
            if (temp_t6 > 0) {
                goto loop_12;
            }
        }
    }
    if (sp30 == 0) {
        goto block_24;
    }
    temp_t0 = sp30;
    sp30 = 0;
    sp28 = &sp28[temp_t0] + 1;
    if (suffixes->unk0 != NULL) {
loop_17:
        if (strcmp(sp28, suffixes[sp30].unk0) == 0) {
            return (s8) suffixes[sp30].unk_7;
        }
        temp_t5 = sp30 + 1;
        sp30 = temp_t5;
        if (suffixes[temp_t5].unk0 == NULL) {
            goto block_20;
        }
        goto loop_17;
    }
block_20:
    if (strcmp(sp28, "for") == 0) {
        return 0x66;
    }
    if (strcmp(sp28, "FOR") == 0) {
        return 0x46;
    }
block_24:
    return 0;
}

s8* mksuf(s8* path, s8 value) {
    s32 sp54;
    s32 sp50;
    u32 sp4C;
    s8* sp48;
    s8* sp44;
    s8* sp40;
    s8* sp3C;
    u8 sp3B;
    s32 temp_t0;
    s32 temp_t4;
    s32 temp_t7;
    s8* temp_t7_3;
    s8* temp_t9;
    struct _struct_suffixes_0x8* temp_t2;
    u8 temp_s0;
    u8 temp_t2_2;
    u8 temp_t7_2;

    sp3C = NULL;
    if ((s32) (u8) value < 8) {
        sp54 = 0;
        if (suffixes->unk0 != NULL) {
loop_2:
            temp_t2 = &suffixes[sp54];
            if (temp_t2->unk4 == (u8) value) {
                sp3C = temp_t2->unk0;
            } else {
                temp_t7 = sp54 + 1;
                sp54 = temp_t7;
                if (suffixes[temp_t7].unk0 != NULL) {
                    goto loop_2;
                }
            }
        }
        if (sp3C == NULL) {
            error(0, NULL, 0, "mksuf ()", 0x3A5A, "passed an unknown suffix value: %s\n", (s32) (u8) value);
            exit(4);
        }
        sp4C = strlen(sp3C);
    } else {
        sp4C = 0;
    }
    sp54 = 0;
    sp48 = savestr(path, sp4C);
    sp44 = sp48;
    sp40 = sp48;
    temp_t7_2 = (u8) *sp48;
    sp44 = sp48 + 1;
    sp3B = temp_t7_2;
    if (temp_t7_2 != 0) {
        do {
            if (sp3B == 0x2F) {
                sp54 = 0;
                sp40 = sp44;
            } else {
                sp54 += 1;
            }
            temp_t2_2 = (u8) sp44->unk_0;
            sp44 += 1;
            sp3B = temp_t2_2;
        } while (temp_t2_2 != 0);
    }
    if ((sp54 >= 3) && (sp44->unk_-3 == 0x2E)) {
        if ((s32) (u8) value < 8) {
            strcpy(sp44 - 2, sp3C);
        } else {
            sp44->unk_-2 = (u8) value;
            sp44->unk_-1 = 0;
        }
    } else {
        temp_t4 = sp54 - 2;
        sp50 = temp_t4;
        if (temp_t4 > 0) {
loop_20:
            if ((u8) sp40[sp50] != 0x2E) {
                temp_t0 = sp50 - 1;
                sp50 = temp_t0;
                if (temp_t0 > 0) {
                    goto loop_20;
                }
            }
        }
        if (sp50 == 0) {
            error(1, NULL, 0, "mksuf ()", 0x3A81, "Bad file name, no suffix: %s\n", path);
            exit(4);
        }
        temp_t9 = &sp40[sp50] + 1;
        sp40 = temp_t9;
        if ((s32) (u8) value < 8) {
            strcpy(temp_t9, sp3C);
        } else {
            sp40->unk_0 = (s8) (u8) value;
            sp40->unk_1 = 0;
        }
    }
    sp44 = sp48;
    if ((u8) *sp48 != 0) {
        do {
            temp_s0 = (u8) *sp48;
            temp_t7_3 = sp48 + 1;
            sp48 = temp_t7_3;
            if (temp_s0 == 0x2F) {
                sp44 = temp_t7_3;
            }
        } while ((u8) *sp48 != 0);
    }
    return sp44;
}

s8* savestr(s8* src, u32 extra_length) {
    s8* sp34;

    sp34 = malloc(strlen(src) + extra_length + 1);
    if (sp34 == NULL) {
        error(1, NULL, 0, "savestr ()", 0x3AA6, "out of memory\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
    }
    strcpy(sp34, src);
    return sp34;
}

void mktempstr(void) {
    tempstr->unk_0 = mktemp(mkstr(tmpdir, "ctmstXXXXXX", NULL));
    tempstr->unk_4 = mktemp(mkstr(tmpdir, "ctmuXXXXXX", NULL));
    tempstr->unk_8 = mktemp(mkstr(tmpdir, "ctmpXXXXXX", NULL));
    tempstr->unk_C = mktemp(mkstr(tmpdir, "ctmfXXXXXX", NULL));
    tempstr->unk_10 = mktemp(mkstr(tmpdir, "ctmluXXXXXX", NULL));
    tempstr->unk_14 = mktemp(mkstr(tmpdir, "ctmsXXXXXX", NULL));
    tempstr->unk_18 = mktemp(mkstr(tmpdir, "ctmmXXXXXX", NULL));
    tempstr->unk_1C = mktemp(mkstr(tmpdir, "ctmoXXXXXX", NULL));
    tempstr->unk_20 = mktemp(mkstr(tmpdir, "ctmosXXXXXX", NULL));
    tempstr->unk_24 = mktemp(mkstr(tmpdir, "ctmcbXXXXXX", NULL));
    tempstr->unk_28 = mktemp(mkstr(tmpdir, "ctmcXXXXXX", NULL));
    tempstr->unk_2C = mktemp(mkstr(tmpdir, "ctmaXXXXXX", NULL));
    tempstr->unk_30 = mktemp(mkstr(tmpdir, "ctmbXXXXXX", NULL));
    tempstr->unk_34 = mktemp(mkstr(tmpdir, "ctmlXXXXXX", NULL));
    tempstr->unk_38 = mktemp(mkstr(tmpdir, "ctmm4XXXXXX", NULL));
    tempstr->unk_3C = mktemp(mkstr(tmpdir, "ctmgtXXXXXX", NULL));
    tempstr->unk_40 = mktemp(mkstr(tmpdir, "ctmilXXXXXX", NULL));
    tempstr->unk_44 = mktemp(mkstr(tmpdir, "ctmltXXXXXX", NULL));
    tempstr->unk_48 = mktemp(mkstr(tmpdir, "ctmp1XXXXXX", NULL));
    tempstr->unk_50 = mktemp(mkstr(tmpdir, "ctmpdXXXXXX", NULL));
    tempstr->unk_4C = mktemp(mkstr(tmpdir, "ctmddXXXXXX", NULL));
    tempstr->unk_54 = mktemp(mkstr(tmpdir, "ctmloXXXXXX", NULL));
    tempstr->unk_58 = mktemp(mkstr(tmpdir, "ctmciXXXXXX", NULL));
    tempstr->unk_5C = mktemp(mkstr(tmpdir, "ctmvXXXXXX", NULL));
    tempstr->unk_60 = mktemp(mkstr(tmpdir, "ctmerrXXXXXX", NULL));
    tempstr->unk_64 = mktemp(mkstr(tmpdir, "ctmemXXXXXX", NULL));
    tempstr->unk_68 = mktemp(mkstr(tmpdir, "ctmeXXXXXX", NULL));
    tempstr->unk_6C = mktemp(mkstr(tmpdir, "ctmdXXXXXX", NULL));
    tempstr->unk_70 = mktemp(mkstr(tmpdir, "ctmqXXXXXX", NULL));
    tempstr->unk_74 = mktemp(mkstr(tmpdir, "ctmqsXXXXXX", NULL));
    tempstr->unk_78 = mktemp(mkstr(tmpdir, "ctmelfXXXXX", NULL));
    tempstr->unk_7C = mktemp(mkstr(tmpdir, "ctmkXXXXXX", NULL));
    tempstr->unk_84 = mktemp(mkstr(tmpdir, "ctmcmdXXXXXX", NULL));
    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (nofilt == 0) && (access(filter, 0x10) == 0)) {
        tempstr->unk_80 = mktemp(mkstr(tmpdir, "ctmfiltXXXXXX", NULL));
        return;
    }
    tempstr->unk_80 = NULL;
}

s32 run(s8* arg0, s8** arg1, s8* arg2, s8* arg3, s8* arg4) {
    s8** spA4;
    s32 spA0;
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    s32 sp90;
    s32 sp8C;
    void (*sp88)();
    void (*sp84)();
    s32 sp80;
    s32 sp7C;
    s8* sp78;
    s32 sp74;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t4;
    s32 temp_t6;
    s32 var_s0;
    s8* temp_a2;

    if (vflag != 0) {
        fprintf(__iob + 0x20, "%s ", arg0);
        spA4 = arg1 + 4;
        if (arg1->unk_4 != 0) {
            do {
                temp_a2 = *spA4;
                spA4 += 4;
                fprintf(__iob + 0x20, "%s ", temp_a2);
            } while (*spA4 != NULL);
        }
        if (arg2 != NULL) {
            fprintf(__iob + 0x20, "< %s ", arg2);
        }
        if (arg3 != NULL) {
            fprintf(__iob + 0x20, "> %s ", arg3);
        }
        fprintf(__iob + 0x20, "\n");
    }
    if (time_flag != 0) {
        settimes();
    }
    if (execute_flag == 0) {
        goto block_81;
    }
    if ((memory_flag != 0) && (pipe(Pipe) < 0)) {
        error(1, NULL, 0, NULL, 0, "pipe failed for -showm");
        return -1;
    }
    spA0 = fork();
    if (spA0 == -1) {
        error(1, NULL, 0, NULL, 0, "no more processes\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        return -1;
    }
    if (spA0 == 0) {
        if (memory_flag != 0) {
            my_psema();
        }
        if (arg2 != NULL) {
            sp94 = open(arg2, 0);
            if (sp94 == -1) {
                error(1, NULL, 0, NULL, 0, "can't open input file: %s\n", arg2);
                if (errno < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                cleanup();
                exit(1);
            }
            dup2(sp94, (s32) __iob->_file);
        }
        if (arg3 != NULL) {
            sp90 = creat(arg3, 0x1FF);
            if (sp90 == -1) {
                error(1, NULL, 0, NULL, 0, "can't create output file: %s\n", arg3);
                if (errno < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                cleanup();
                exit(1);
            }
            dup2(sp90, (s32) __iob->unk_1D);
        }
        if (arg4 != NULL) {
            sp8C = creat(arg4, 0x1FF);
            if (sp8C == -1) {
                error(1, NULL, 0, NULL, 0, "can't create error file: %s\n", arg4);
                if (errno < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                cleanup();
                exit(1);
            }
            dup2(sp8C, (s32) __iob->unk_2D);
        }
        execvp(arg0, arg1);
        sp78 = func_00430414(arg0, 1);
        if ((errno == 2) && (sp78 != NULL)) {
            error(1, NULL, 0, NULL, 0, "%s is not installed (could not find %s).\n", sp78, arg0);
        } else {
            sp78 = func_00430414(arg0, 0);
            if ((errno == 2) && (sp78 != NULL)) {
                error(1, NULL, 0, NULL, 0, "%s may not be installed (could not find %s).\n", sp78, arg0);
            } else {
                error(1, NULL, 0, NULL, 0, "can't find or exec: %s\n", arg0);
                if (errno < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
            }
        }
        cleanup();
        return exit(1);
    }
    sp84 = sigset(2, (void (*)())1);
    sp88 = sigset(0xF, (void (*)())1);
    if (memory_flag != 0) {
        sp74 = stop_on_exit(spA0);
        sp7C = ioctl(sp74, 0x71F9, &mapbuf_desc);
        if (sp7C < 0) {
            perror("PIOCMAP_SGI");
            kill(spA0, 9);
            return -1;
        }
        var_s0 = 0x10;
        if (0x10 != 0) {
            do {
                var_s0 -= 1;
                (&sp34[0])[var_s0] = 0;
            } while (var_s0 != 0);
        }
        if (ioctl(sp74, 0x7114, &sp34[0]) < 0) {
            perror("PIOCSEXIT");
            kill(spA0, 9);
            return -1;
        }
        ioctl(sp74, 0x7104, 0);
        close(sp74);
        goto block_58;
    }
block_58:
    sp9C = wait(&sp80);
    if (sp9C != spA0) {
loop_59:
        if (sp9C == -1) {
            return -1;
        }
        sp9C = wait(&sp80);
        if (sp9C == spA0) {
            goto block_62;
        }
        goto loop_59;
    }
block_62:
    sigset(2, sp84);
    sigset(0xF, sp88);
    if (time_flag != 0) {
        dotime(arg0);
    }
    if (memory_flag != 0) {
        print_mem(arg0, sp7C);
    }
    temp_t0 = sp80;
    if ((temp_t0 & 0xFF) == 0x7F) {
        temp_t1 = (temp_t0 >> 8) & 0xFF;
        if (temp_t1 != 0) {
            sp98 = temp_t1;
            fprintf(__iob + 0x20, "STOPPED signal received from: %s ", arg0);
            fprintf(__iob + 0x20, " (Signal %d) ", sp98);
            fprintf(__iob + 0x20, " Process  %d abandoned\n", sp9C);
            return sp98;
        }
    }
    temp_t4 = sp80;
    if (!(temp_t4 & 0xFF)) {
        return (temp_t4 >> 8) & 0xFF;
    }
    temp_t6 = sp80;
    if (((temp_t6 & 0xFF) > 0) && !((temp_t6 >> 8) & 0xFF)) {
        sp98 = temp_t6 & 0x7F;
        fprintf(__iob + 0x20, "Fatal error in: %s ", arg0);
        printf(" child died due to signal %d.\n", sp98);
        if (sp98 == 9) {
            printf("Probably caused by running out of swap space -- check /usr/adm/SYSLOG.\n");
            exit(sp98);
        }
        if (sp98 == 2) {
            cleanup();
            exit(3);
        }
        fprintf(__iob + 0x20, "Fatal error in: %s ", arg0);
        fprintf(__iob + 0x20, " Signal %d ", sp98);
        if (sp80 & 0x80) {
            fprintf(__iob + 0x20, "- core dumped\n");
        } else {
            fprintf(__iob + 0x20, "\n");
        }
        return exit(sp98);
    }
block_81:
    return 0;
}

s32 edit_src(s8* arg0, s8* arg1, s32 arg2) {
    s8 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    void (*sp48)();
    void (*sp44)();
    s32 sp40;
    s32 temp_t7;

    sp54 = fork();
    if (sp54 == -1) {
        error(1, NULL, 0, NULL, 0, "fork to edit failed\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        return -1;
    }
    if (sp54 == 0) {
        if (editflag == 2) {
            get_lino(&sp58, arg1, arg2);
            execlp(arg0, arg0, &sp58, arg1, "-l", tempstr->unk_64, "-f", "err-window", 0);
        } else if (xserver == 0) {
            execlp(arg0, arg0, "+1", errout, arg1, 0);
        } else {
            execlp("xterm", "xterm", "-display", xserver, "-ls", "-e", arg0, "+1", errout, arg1, 0);
        }
        error(1, NULL, 0, NULL, 0, "failed to exec: %s\n", arg0);
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        return exit(1);
    }
    sp44 = sigset(2, (void (*)())1);
    sp48 = sigset(0xF, (void (*)())1);
    sp50 = wait(&sp40);
    if (sp50 != sp54) {
loop_14:
        if (sp50 == -1) {
            return -1;
        }
        sp50 = wait(&sp40);
        if (sp50 == sp54) {
            goto block_17;
        }
        goto loop_14;
    }
block_17:
    sigset(2, sp44);
    sigset(0xF, sp48);
    temp_t7 = sp40 & 0xFF;
    sp4C = temp_t7;
    if ((temp_t7 != 0) && (temp_t7 != 2)) {
        fprintf(__iob + 0x20, "Fatal error in: %s ", arg0);
        printf(" Signal %d ", sp4C);
        if (sp40 & 0x80) {
            fprintf(__iob + 0x20, "- core dumped\n");
        } else {
            fprintf(__iob + 0x20, "\n");
        }
        cleanup();
        exit(sp4C);
    }
    if (sp4C == 2) {
        cleanup();
        exit(3);
    }
    return sp40 & 0xFF00;
}

void get_lino(s8* arg0, s8* arg1, s32 arg2) {
    s32 sp83C;
    s32 sp838;
    s8* sp834;
    s8* sp830;
    s8 sp30;
    s8* temp_t2;
    s8* temp_t3;
    s8* temp_t8;
    s8* temp_t9;
    u32 temp_s1;

    sp834 = arg0;
    *arg0 = 0x2B;
    sp834 += 1;
    sp83C = open(errout, 0);
    sp838 = read(sp83C, &sp30, 0x800U);
    close(sp83C);
    if (sp838 < 0x800) {
        (&sp30)[sp838] = 0;
    } else {
        sp30.unk_7FF = 0;
    }
    switch (arg2) {
    case 1:
    case 2:
        sp830 = &sp30;
        if ((u32) &sp30 < (u32) &(&sp30)[sp838]) {
loop_6:
            if ((strncmp(sp830, ": Error: ", 9U) == 0) && (sp830 = strchr(sp830, 0x2CU), (sp830 != NULL)) && (temp_s1 = strlen(arg1), (strncmp(sp830 - temp_s1, arg1, strlen(arg1)) == 0)) && (strncmp(sp830, ", line ", 7U) == 0)) {
                sp830 += 7;
                if ((__ctype[(u8) sp830[7]].unk_1 & 4) && ((sp834 - arg0) < 0xB)) {
loop_12:
                    sp834->unk_0 = (s8) (u8) *sp830;
                    sp830 += 1;
                    sp834 += 1;
                    if (__ctype[(u8) *sp830].unk_1 & 4) {
                        if ((sp834 - arg0) >= 0xB) {

                        } else {
                            goto loop_12;
                        }
                    }
                }
            } else {
                temp_t8 = sp830 + 1;
                sp830 = temp_t8;
                if ((u32) temp_t8 >= (u32) &(&sp30)[sp838]) {

                } else {
                    goto loop_6;
                }
            }
        }
        break;
    case 3:
        sp830 = &sp30;
        if ((u32) &sp30 < (u32) &(&sp30)[sp838]) {
loop_18:
            if (strncmp(sp830, "Error on line ", 0xEU) == 0) {
                sp830 += 0xE;
                if ((__ctype[(u8) sp830[0xE]].unk_1 & 4) && ((sp834 - arg0) < 0xB)) {
loop_21:
                    sp834->unk_0 = (s8) (u8) *sp830;
                    sp830 += 1;
                    sp834 += 1;
                    if (__ctype[(u8) *sp830].unk_1 & 4) {
                        if ((sp834 - arg0) >= 0xB) {

                        } else {
                            goto loop_21;
                        }
                    }
                }
            } else {
                temp_t3 = sp830 + 1;
                sp830 = temp_t3;
                if ((u32) temp_t3 >= (u32) &(&sp30)[sp838]) {

                } else {
                    goto loop_18;
                }
            }
        }
        break;
    case 5:
    case 6:
        sp830 = &sp30;
        if ((u32) &sp30 < (u32) &(&sp30)[sp838]) {
loop_27:
            if (strncmp(sp830, "ERROR ", 6U) == 0) {
                sp830 += 6;
            } else {
                temp_t2 = sp830 + 1;
                sp830 = temp_t2;
                if ((u32) temp_t2 < (u32) &(&sp30)[sp838]) {
                    goto loop_27;
                }
            }
        }
        if ((u32) sp830 < (u32) &(&sp30)[sp838]) {
loop_31:
            if (strncmp(sp830, " LINE ", 6U) == 0) {
                sp830 += 6;
                if ((__ctype[(u8) sp830[6]].unk_1 & 4) && ((sp834 - arg0) < 0xB)) {
loop_34:
                    sp834->unk_0 = (s8) (u8) *sp830;
                    sp830 += 1;
                    sp834 += 1;
                    if (__ctype[(u8) *sp830].unk_1 & 4) {
                        if ((sp834 - arg0) >= 0xB) {

                        } else {
                            goto loop_34;
                        }
                    }
                }
            } else {
                temp_t9 = sp830 + 1;
                sp830 = temp_t9;
                if ((u32) temp_t9 < (u32) &(&sp30)[sp838]) {
                    goto loop_31;
                }
            }
        }
        break;
    }
    if ((u32) (arg0 + 1) < (u32) sp834) {
        sp834->unk_0 = 0;
        return;
    }
    sp834->unk_0 = 0x31;
    sp834->unk_1 = 0;
}

void show_err(s8* path) {
    ? sp10000;
    ? sp20;
    s32 temp_t6;

    sp10000.unk_28 = path;
    sp10000.unk_24 = open(sp10000.unk_28, 0);
    sp10000.unk_20 = read(sp10000.unk_24, &sp20, 0x10000U);
    close(sp10000.unk_24);
    temp_t6 = sp10000.unk_20;
    if (temp_t6 < 0x10000) {
        *(temp_t6 + &sp20) = 0;
    } else {
        sp20.unk_FFFF = 0;
    }
    fprintf(__iob + 0x20, "%s\n", &sp20);
}

void handler(void) {
    cleanup();
    exit(3);
}

void cleanup(void) {
    s8 sp27;

    if (Kflag == 0) {
        if (passout != NULL) {
            unlink(passout);
        }
        if ((passin != NULL) && ((sp27 = getsuf(passin), ((u8) sp27 == 0)) || (((u8) sp27 != (u8) srcsuf) && ((u8) sp27 != 0x6D))) && (Eflag == 0)) {
            unlink(passin);
        }
        if ((tmpst != 0) && (symtab != NULL)) {
            unlink(symtab);
        }
        if (lpi_st != NULL) {
            unlink(lpi_st);
        }
        if (lpi_p1 != NULL) {
            unlink(lpi_p1);
        }
        if (lpi_pd != NULL) {
            unlink(lpi_pd);
        }
        if (lpi_dd != NULL) {
            unlink(lpi_dd);
        }
        if (uopt0str != NULL) {
            unlink(uopt0str);
        }
        if (ddoptstr != NULL) {
            unlink(ddoptstr);
        }
        if (optstr != NULL) {
            unlink(optstr);
        }
        if (gentmp != NULL) {
            unlink(gentmp);
        }
        if (binasm != NULL) {
            unlink(binasm);
        }
        if (linkorder != NULL) {
            unlink(linkorder);
        }
        if (tmp_uldobj != NULL) {
            unlink(tmp_uldobj);
        }
        if (editflag != 0) {
            unlink(errout);
            if (editflag == 2) {
                unlink(tempstr->unk_64);
            }
        }
        if (compiler == 1) {
            unlink(tempstr->unk_84);
        }
    }
}

void whats(void) {
    s32 sp24;

    sp24 = runerror;
    if (compiler == 2) {
        printf("%s  (%s)\n", progname, "pc");
    } else if (compiler == 4) {
        printf("%s  (%s)\n", progname, "as");
    } else if (compiler == 3) {
        printf("%s  (%s)\n", progname, "f77");
    } else if (compiler == 5) {
        printf("%s  (%s)\n", progname, "pl1");
    } else if (compiler == 6) {
        printf("%s  (%s)\n", progname, "cobol");
    } else {
        printf("%s  (%s)\n", progname, "cc");
    }
    printf("\tMips Computer Systems %d.%d\n", 7, 0xA);
}

void settimes(void) {
    time0 = times(&tm0);
}

void dotime(s8* programName) {
    s32 sp6C;
    s32 sp68;
    f64 sp60;
    f64 sp58;
    struct tms sp48;
    f64 temp_ft1;
    f64 temp_ft3;

    sp6C = times(&sp48);
    sp68 = sp6C - time0;
    temp_ft3 = (f64) ((((s32) sp48 + sp48.tms_cutime) - tm0.tms_utime) - tm0.tms_cutime) / 100.0;
    temp_ft1 = (f64) (((sp48.tms_stime + sp48.tms_cstime) - tm0.tms_stime) - tm0.tms_cstime) / 100.0;
    sp60 = temp_ft3;
    sp58 = temp_ft1;
    fprintf(__iob + 0x20, "%s phase time: %.2fu %.2fs %u:%04.1f %.0f%%\n", programName, temp_ft3, temp_ft1, sp68 / 6000, (f64) (sp68 % 6000) / 100.0, ((temp_ft3 + temp_ft1) / ((f64) sp68 / 100.0)) * 100.0);
}

s8* func_0042FD7C(s8* name, s8** dirs) {
    s32 sp34;
    s8* sp30;
    s8* var_v0;
    s8** temp_t5;

    if (*dirs != NULL) {
loop_1:
        if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (sp30 = mkstr(*dirs, "/DCC", runlib, name, NULL), sp34 = open(sp30, 0, 0), (sp34 >= 0))) {
            close(sp34);
        } else {
            sp30 = mkstr(*dirs, runlib, name, NULL);
            sp34 = open(sp30, 0, 0);
            if (sp34 >= 0) {
                close(sp34);
            } else {
                temp_t5 = dirs + 4;
                dirs = temp_t5;
                if (*temp_t5 == NULL) {
                    goto block_9;
                }
                goto loop_1;
            }
        }
    } else {
block_9:
        if (abi_flag != 0) {
            var_v0 = mkstr("/", "usr/lib/abi", runlib, name, NULL);
        } else if (non_shared != 0) {
            var_v0 = mkstr("/", "usr/lib/nonshared", runlib, name, NULL);
        } else {
            var_v0 = mkstr("/", "usr/lib", runlib, name, NULL);
        }
        sp30 = var_v0;
    }
    return sp30;
}

s32 isdir(s8* path) {
    s32 spAC;
    struct stat sp24;

    spAC = stat(path, &sp24);
    if (spAC == -1) {
        goto block_4;
    }
    if ((sp24.st_mode & 0xF000) == 0x4000) {
        return 1;
    }
block_4:
    return 0;
}

s32 regular_not_writeable(s8* arg0) {
    s32 sp24;

    if (regular_file(arg0) != 1) {
        return 0;
    }
    sp24 = open(arg0, 2, 0x1FF);
    if (sp24 >= 0) {
        close(sp24);
        return 0;
    }
    return 1;
}

s32 regular_file(s8* path) {
    s32 spAC;
    struct stat sp24;

    spAC = stat(path, &sp24);
    if (spAC == -1) {
        return -1;
    }
    if ((sp24.st_mode & 0xF000) != 0x8000) {
        return 0;
    }
    return 1;
}

s8* basename(s8* path) {
    ?* temp_t8;
    s8* temp_v0;
    s8* var_s0;
    u8 temp_t1;
    u8 temp_t2;
    u8 temp_t3;

    if ((path == NULL) || ((u8) *path == 0)) {
        temp_t8 = ".";
        B_1000E5E0->unk_0 = (s8) temp_t8->unk_0;
        B_1000E5E0->unk_1 = (u8) temp_t8->unk_1;
        return B_1000E5E0;
    }
    temp_v0 = strcpy(B_1000E5E0, path);
    var_s0 = &temp_v0[strlen(temp_v0)];
    if (var_s0 != B_1000E5E0) {
        temp_t1 = var_s0->unk_-1;
        var_s0 -= 1;
        if (temp_t1 == 0x2F) {
loop_5:
            var_s0->unk_0 = 0;
            if (var_s0 != B_1000E5E0) {
                temp_t2 = var_s0->unk_-1;
                var_s0 -= 1;
                if (temp_t2 == 0x2F) {
                    goto loop_5;
                }
            }
        }
    }
    if (var_s0 != B_1000E5E0) {
loop_8:
        temp_t3 = var_s0->unk_-1;
        var_s0 -= 1;
        if (temp_t3 == 0x2F) {
            var_s0 += 1;
        } else if (var_s0 != B_1000E5E0) {
            goto loop_8;
        }
    }
    return var_s0;
}

s8* dirname(s8* path) {
    ?* temp_t3;
    ?* temp_t4;
    ?* temp_t8;
    ?* temp_t8_2;
    s8* temp_v0;
    s8* var_s0;
    u8 temp_t1;
    u8 temp_t2;
    u8 temp_t2_2;
    u8 temp_t7;

    if ((path == NULL) || ((u8) *path == 0)) {
        temp_t8 = ".";
        B_1000E5E0->unk_0 = (s8) temp_t8->unk_0;
        B_1000E5E0->unk_1 = (u8) temp_t8->unk_1;
        return B_1000E5E0;
    }
    temp_v0 = strcpy(B_1000E5E0, path);
    var_s0 = &temp_v0[strlen(temp_v0)];
    if (var_s0 != B_1000E5E0) {
        temp_t1 = var_s0->unk_-1;
        var_s0 -= 1;
        if (temp_t1 == 0x2F) {
loop_5:
            if (var_s0 != B_1000E5E0) {
                temp_t2 = var_s0->unk_-1;
                var_s0 -= 1;
                if (temp_t2 == 0x2F) {
                    goto loop_5;
                }
            }
        }
    }
    if ((var_s0 == B_1000E5E0) && ((u8) *var_s0 == 0x2F)) {
        temp_t4 = "/";
        B_1000E5E0->unk_0 = (s8) temp_t4->unk_0;
        B_1000E5E0->unk_1 = (u8) temp_t4->unk_1;
        return B_1000E5E0;
    }
    if (var_s0 != B_1000E5E0) {
loop_11:
        temp_t7 = var_s0->unk_-1;
        var_s0 -= 1;
        if (temp_t7 == 0x2F) {
            if (var_s0 == B_1000E5E0) {
                temp_t8_2 = "/";
                B_1000E5E0->unk_0 = (s8) temp_t8_2->unk_0;
                B_1000E5E0->unk_1 = (u8) temp_t8_2->unk_1;
                return B_1000E5E0;
            }
            if ((u8) *var_s0 == 0x2F) {
                do {
                    temp_t2_2 = var_s0->unk_-1;
                    var_s0 -= 1;
                } while (temp_t2_2 == 0x2F);
            }
            var_s0[1] = 0;
            return B_1000E5E0;
        }
        if (var_s0 == B_1000E5E0) {
            goto block_18;
        }
        goto loop_11;
    }
block_18:
    temp_t3 = ".";
    B_1000E5E0->unk_0 = (s8) temp_t3->unk_0;
    B_1000E5E0->unk_1 = (u8) temp_t3->unk_1;
    return B_1000E5E0;
}

s8* func_00430414(s8* arg0, s32 arg1) {
    s32 sp2C;
    s32 sp28;
    s8* sp24;
    s8* sp20;
    s32 temp_t7;

    if (arg1 != 0) {
        sp24 = arg0;
    } else {
        sp24 = strrchr(arg0, 0x2F);
        if (sp24 != NULL) {
            sp24 += 1;
        }
    }
    sp28 = 0x14;
    sp2C = 0;
loop_5:
    if (arg1 != 0) {
        sp20 = prod_name[sp2C].unk4;
    } else {
        sp20 = prod_name[sp2C].unk0;
    }
    if (strcmp(sp24, sp20) == 0) {
        return prod_name[sp2C].unk8;
    }
    temp_t7 = sp2C + 1;
    sp2C = temp_t7;
    if (temp_t7 >= sp28) {
        return NULL;
    }
    goto loop_5;
}

s32 force_use_cfront(s32 argc, s8** argv) {
    s32 sp2C;
    s8* sp28;
    s32 sp24;
    s32 temp_t0;

    sp28 = getenv("USE_CFRONT");
    sp24 = 0;
    if ((sp28 != NULL) && ((u8) *sp28 != 0x30)) {
        return 1;
    }
    sp2C = 1;
    if (argc >= 2) {
loop_4:
        if (strcmp(argv[sp2C], "-exceptions") == 0) {
            D_1000BF7C = 1;
        }
        if ((D_1000BF7C == 0) && (exception_handling == 0) && ((strcmp(argv[sp2C], "-F") == 0) || (strcmp(argv[sp2C], "-Fc") == 0))) {
            return 1;
        }
        if ((strcmp(argv[sp2C], "-use_cfront") == 0) || (strcmp(argv[sp2C], "-v2") == 0) || (strcmp(argv[sp2C], "+I") == 0) || (strncmp(argv[sp2C], "-.", 2U) == 0)) {
            return 1;
        }
        temp_t0 = sp2C + 1;
        sp2C = temp_t0;
        if (temp_t0 >= argc) {
            goto block_17;
        }
        goto loop_4;
    }
block_17:
    return 0;
}

void exec_OCC(s32 argc, s8** argv) {
    s8 spB8;

    sprintf(&spB8, "%susr/bin/OCC", comp_host_root);
    *argv = &spB8;
    execv(&spB8, argv);
    error(2, NULL, 0, NULL, 0, "could not exec %s", &spB8);
}

s32 add_cxx_symbol_options(void) {
    addstr(&execlist, "-cxx");
    if ((D_1000BF90 == 0) && (strcmp(LD, "old_ld") != 0)) {
        addstr(&execlist, "-woff");
        addstr(&execlist, "134");
    }
    return 0;
}

void init_curr_dir(void) {
    if (D_1000C2F0 == NULL) {
        D_1000C2F0 = strrchr(progname, 0x2F);
        if (D_1000C2F0 == NULL) {
            D_1000C2F0 = progname;
        } else {
            D_1000C2F0 += 1;
        }
    }
    if (D_1000C1D0 == NULL) {
        D_1000C1D0 = getcwd(NULL, 0x400U);
        if (D_1000C1D0 == NULL) {
            D_1000C1D0 = getenv("PWD");
            if (D_1000C1D0 == NULL) {
                D_1000C1D0 = ".";
            }
        }
        if (strncmp(D_1000C1D0, "/tmp_mnt", 8U) == 0) {
            D_1000C1D0 += 8;
        }
    }
}

s8* full_path(s8* relative_path) {
    s8* sp24;
    s8* var_v0;

    init_curr_dir();
    if ((u8) *relative_path == 0x2F) {
        var_v0 = mkstr(relative_path, NULL);
    } else {
        var_v0 = mkstr(D_1000C1D0, "/", relative_path, NULL);
    }
    sp24 = var_v0;
    return var_v0;
}

void add_static_opt(s8* opt) {
    if (D_1000BF88 == 0) {
        addstr(&staticopts, opt);
    }
}

void record_static_fileset(s32 arg0) {
    s32 sp28E4;                                     /* compiler-managed */
    FILE* sp28E0;
    FILE* sp28DC;
    s32 sp28D8;
    s8 spD8;
    s8* spD4;
    u32 spD0;
    s8 spBC;
    struct stat sp34;
    s32 temp_t0;
    s32 temp_t0_2;
    s8* var_v0;

    sprintf(&spBC, ".%d", getpid());
    if (D_1000BF80 == NULL) {
        D_1000BF80 = "";
    }
    if (D_1000BF84 == NULL) {
        D_1000BF84 = mkstr("cvstatic.fileset", NULL);
    }
    if (((u8) *D_1000BF84 == 0x2F) || ((u8) *D_1000BF80 == 0)) {
        var_v0 = mkstr(D_1000BF84, NULL);
    } else {
        var_v0 = mkstr(D_1000BF80, D_1000BF84, NULL);
    }
    D_1000C2E8 = var_v0;
    D_1000C2EC = mkstr(tmpdir, "cvstatic.fileset", &spBC, NULL);
    spD4 = full_path((s8* ) arg0);
    spD0 = strlen(spD4);
    if (vflag != 0) {
        fprintf(__iob + 0x20, "Static fileset: %s %s", spD4, D_1000C2F0);
        sp28E4 = 0;
        if (staticopts.length > 0) {
            do {
                fprintf(__iob + 0x20, " %s", staticopts.entries[sp28E4]);
                temp_t0 = sp28E4 + 1;
                sp28E4 = temp_t0;
            } while (temp_t0 < staticopts.length);
        }
        fprintf(__iob + 0x20, "\n");
    }
    sp28E0 = fopen(D_1000C2EC, "w+");
    if (sp28E0 == NULL) {
        error(1, NULL, 0, "record_static_fileset", 0, "could not open cvstatic fileset temp file %s\n", D_1000C2EC);
        perror(D_1000C2F0);
        cleanup();
        exit(1);
    }
    sp28D8 = open(D_1000C2E8, 0x102, 0x1FF);
    if (sp28D8 < 0) {
        error(1, NULL, 0, "record_static_fileset", 0, "could not open or create cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }
    if (flock(sp28D8, 2) < 0) {
        error(1, NULL, 0, "record_static_fileset", 0, "error in locking cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }
    if (fstat(sp28D8, &sp34) < 0) {
        error(1, NULL, 0, "record_static_fileset", 0, "could not fstat cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }
    if (sp34.st_size == 0) {
        fprintf(sp28E0, "-cvstatic\n");
    }
    sp28DC = fdopen(sp28D8, "r+");
    if (sp28DC == NULL) {
        error(1, NULL, 0, "record_static_fileset", 0, "could not fdopen cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }
    if (fgets(&spD8, 0x2800, sp28DC) != NULL) {
        do {
            if ((strncmp(&spD8, spD4, spD0) != 0) || !(__ctype[(u8) (&spD8)[spD0]].unk_1 & 8)) {
                fputs(&spD8, sp28E0);
            }
        } while (fgets(&spD8, 0x2800, sp28DC) != NULL);
    }
    fprintf(sp28E0, "%s %s", spD4, D_1000C2F0);
    sp28E4 = 0;
    if (staticopts.length > 0) {
        do {
            fprintf(sp28E0, " %s", staticopts.entries[sp28E4]);
            temp_t0_2 = sp28E4 + 1;
            sp28E4 = temp_t0_2;
        } while (temp_t0_2 < staticopts.length);
    }
    fprintf(sp28E0, "\n");
    free(spD4);
    rewind(sp28DC);
    rewind(sp28E0);
    ftruncate((s32) sp28DC->_file, 0);
    sp28E4 = fread(&spD8, 1U, 0x2800U, sp28E0);
    if ((s32) sp28E4 > 0) {
        do {
            if (fwrite(&spD8, 1U, sp28E4, sp28DC) != sp28E4) {
                error(1, NULL, 0, "record_static_fileset", 0, "error in writing cvstatic fileset file %s\n", D_1000C2E8);
                perror(D_1000C2F0);
                unlink(D_1000C2EC);
                cleanup();
                exit(1);
            }
            sp28E4 = fread(&spD8, 1U, 0x2800U, sp28E0);
        } while ((s32) sp28E4 > 0);
    }
    fclose(sp28DC);
    fclose(sp28E0);
    unlink(D_1000C2EC);
    free(D_1000C2E8);
    free(D_1000C2EC);
}

s32 touch(s8* arg0) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s8* sp30;
    u32 temp_s1;

    sp3C = time(NULL);
    init_curr_dir();
    if (vflag != 0) {
        fprintf(__iob + 0x20, "%s: touch %s\n", D_1000C2F0, arg0);
    }
    sp38 = sp3C;
    sp34 = sp3C;
    if (utime(arg0, (struct utimbuf* ) &sp34) < 0) {
        temp_s1 = strlen(arg0);
        sp30 = malloc(strlen(D_1000C2F0) + temp_s1 + 0xA);
        sprintf(sp30, "%s: touch %s", D_1000C2F0, arg0);
        perror(sp30);
        free(sp30);
        return -1;
    }
    return 0;
}

void add_prelinker_objects(list* arg0, list* arg1) {
    s32 sp24;
    s32 temp_t0;
    s32 temp_t6;
    s8* temp_t3;
    u8 temp_t5;

    sp24 = 0;
    if (arg1->length > 0) {
        do {
            temp_t3 = arg1->entries[sp24];
            if (((u8) temp_t3->unk_0 == 0x2D) && (temp_t5 = temp_t3->unk_1, (temp_t5 != 0x6C)) && (temp_t5 != 0x4C)) {
                if (strcmp(arg1->entries[sp24], "-nostdlib") == 0) {
                    addstr(arg0, mkstr("-YB", NULL));
                } else if (strcmp(arg1->entries[sp24], "-objectlist") == 0) {
                    addstr(arg0, mkstr("-YO=", arg1->entries[sp24].unk_4, NULL));
                    sp24 += 1;
                } else if (strcmp(arg1->entries[sp24], "-B") == 0) {
                    temp_t0 = sp24 + 1;
                    sp24 = temp_t0;
                    if (strcmp(arg1->entries[temp_t0], "static") == 0) {
                        addstr(arg0, mkstr("-Bstatic", NULL));
                    } else if (strcmp(arg1->entries[sp24], "dynamic") == 0) {
                        addstr(arg0, mkstr("-Bdynamic", NULL));
                    }
                }
            } else {
                addstr(arg0, arg1->entries[sp24]);
            }
            temp_t6 = sp24 + 1;
            sp24 = temp_t6;
        } while (temp_t6 < arg1->length);
    }
}

u32 quoted_length(s8* arg0, s32* arg1) {
    u32 spC;
    u8 spB;
    s8* var_a0;

    spC = 0;
    *arg1 = 0;
    var_a0 = arg0 + 1;
    spB = (u8) *arg0;
    if (spB != 0) {
        do {
            if ((*arg1 == 0) && ((spB == 0x27) || (spB == 0x7C) || (spB == 0x26) || (spB == 0x2A) || (spB == 0x3F) || (spB == 0x5B) || (spB == 0x5D) || (spB == 0x3B) || (spB == 0x21) || (spB == 0x28) || (spB == 0x29) || (spB == 0x5E) || (spB == 0x3C) || (spB == 0x3E) || ((s32) spB < 0x21) || (spB == 9) || (spB == 0x22) || (spB == 0x5C) || (spB == 0x60) || (spB == 0x24))) {
                *arg1 = 1;
                spC += 2;
            }
            if ((spB == 0x22) || (spB == 0x5C) || (spB == 0x60) || (spB == 0x24)) {
                spC += 1;
            }
            var_a0 += 1;
            spC += 1;
            spB = var_a0->unk_-1;
        } while (spB != 0);
    }
    return spC;
}

u32 quote_shell_arg(s8* arg0, s8* arg1) {
    u8 sp2F;
    s32 sp28;
    u32 sp24;
    u8 temp_t2;
    u8 temp_t4;

    sp28 = 0;
    sp24 = quoted_length(arg0, &sp28);
    if (sp28 != 0) {
        *arg1 = 0x22;
        arg1 += 1;
    }
    temp_t2 = (u8) *arg0;
    arg0 += 1;
    sp2F = temp_t2;
    if (temp_t2 != 0) {
        do {
            if ((sp2F == 0x22) || (sp2F == 0x5C) || (sp2F == 0x60) || (sp2F == 0x24)) {
                *arg1 = 0x5C;
                arg1 += 1;
            }
            *arg1 = (s8) sp2F;
            arg1 += 1;
            temp_t4 = (u8) *arg0;
            arg0 += 1;
            sp2F = temp_t4;
        } while (temp_t4 != 0);
    }
    if (sp28 != 0) {
        *arg1 = 0x22;
        arg1 += 1;
    }
    return sp24;
}

void func_00431A3C(s32 argc, s8** argv) {
    s32 sp24;
    s32 temp_t2;
    s8* temp_t2_2;
    s8** temp_v0;

    B_1000E4C0 = argc;
    temp_v0 = malloc((argc * 4) + 4);
    sp24 = 0;
    B_1000E4C4 = temp_v0;
    if (argc > 0) {
        do {
            temp_t2_2 = argv[sp24];
            if (temp_t2_2 != NULL) {
                B_1000E4C4[sp24] = strdup(temp_t2_2);
            } else {
                B_1000E4C4[sp24] = NULL;
            }
            temp_t2 = sp24 + 1;
            sp24 = temp_t2;
        } while (temp_t2 < argc);
    }
    B_1000E4C4[B_1000E4C0] = NULL;
}

void func_00431B38(s32 first, s32 count) {
    s32 sp4;
    s32 temp_t2;

    sp4 = 0;
    if (count > 0) {
        do {
            B_1000E4C4[first + sp4] = NULL;
            temp_t2 = sp4 + 1;
            sp4 = temp_t2;
        } while (temp_t2 < count);
    }
}

void func_00431B88(FILE* arg0, s8* arg1, s32 arg2) {
    if (arg2 != 0) {
        fputs("CMDLINE=", arg0);
    }
    fprintf(arg0, "%s ", progname);
    if (cflag == 0) {
        fputs("-c ", arg0);
    }
    if ((srcfiles.length == 1) && (cflag != 0) && (B_1000ECCC != NULL)) {
        fprintf(arg0, "-o %s ", B_1000ECCC);
    }
    fprintf(arg0, "%s %s\n", B_1000ECDC, arg1);
    if (arg2 != 0) {
        fputs("PWD=", arg0);
    }
    fprintf(arg0, "%s\n", D_1000C1D0);
    if (arg2 != 0) {
        fputs("----\n", arg0);
    }
}

void func_00431D00(s8* arg0) {
    FILE* sp34;

    sp34 = fopen(tempstr->unk_84, "w");
    if (sp34 != NULL) {
        init_curr_dir();
        func_00431B88(sp34, arg0, 0);
        fclose(sp34);
        return;
    }
    error(2, NULL, 0, NULL, 0, "cannot open commandfile '%s'\n", tempstr->unk_84);
}

void func_00431DD8(void) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s8* sp24;
    s32 temp_t2_2;
    s32 temp_t7;
    s8* temp_t2;
    s8* temp_t6;
    s8* temp_t9;

    sp34 = 0;
    sp30 = 0;
    sp2C = 0;
    sp28 = 1;
    if (B_1000E4C0 >= 2) {
        do {
            temp_t2 = B_1000E4C4[sp28];
            if (temp_t2 != NULL) {
                sp34 = sp34 + quoted_length(temp_t2, &sp2C) + 1;
            }
            temp_t7 = sp28 + 1;
            sp28 = temp_t7;
        } while (temp_t7 < B_1000E4C0);
    }
    sp24 = malloc(sp34 + 1);
    B_1000ECDC = sp24;
    sp28 = 1;
    if (B_1000E4C0 >= 2) {
        do {
            temp_t6 = B_1000E4C4[sp28];
            if (temp_t6 != NULL) {
                temp_t9 = &sp24[quote_shell_arg(temp_t6, sp24)];
                sp24 = temp_t9;
                *temp_t9 = 0x20;
                sp24 += 1;
            }
            temp_t2_2 = sp28 + 1;
            sp28 = temp_t2_2;
        } while (temp_t2_2 < B_1000E4C0);
    }
    if ((u32) B_1000ECDC < (u32) sp24) {
        sp24->unk_-1 = 0;
        return;
    }
    sp24->unk_0 = 0;
}

void skip_old_ii_controls(FILE* arg0) {
    s32 sp54;
    s32 sp50;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;

    sp50 = 0;
    if (__us_rsthread_stdio != 0) {
        sp54 = __semgetc(arg0);
    } else {
        arg0->_cnt -= 1;
        if (arg0->_cnt < 0) {
            var_s0 = __filbuf(arg0);
        } else {
            var_s0 = (s32) *arg0->_ptr;
            arg0->_ptr += 1;
        }
        sp54 = var_s0;
    }
    if (sp54 != -1) {
loop_7:
        if (sp54 == 0x2D) {
            if (__us_rsthread_stdio != 0) {
                var_s0_2 = __semgetc(arg0);
            } else {
                arg0->_cnt -= 1;
                if (arg0->_cnt < 0) {
                    var_s1 = __filbuf(arg0);
                } else {
                    var_s1 = (s32) *arg0->_ptr;
                    arg0->_ptr += 1;
                }
                var_s0_2 = var_s1;
            }
            sp54 = var_s0_2;
            if (sp54 == 0x2D) {
                if (__us_rsthread_stdio != 0) {
                    var_s2 = __semgetc(arg0);
                } else {
                    arg0->_cnt -= 1;
                    if (arg0->_cnt < 0) {
                        var_s3 = __filbuf(arg0);
                    } else {
                        var_s3 = (s32) *arg0->_ptr;
                        arg0->_ptr += 1;
                    }
                    var_s2 = var_s3;
                }
                sp54 = var_s2;
                if (sp54 == 0x2D) {
                    if (__us_rsthread_stdio != 0) {
                        var_s4 = __semgetc(arg0);
                    } else {
                        arg0->_cnt -= 1;
                        if (arg0->_cnt < 0) {
                            var_s5 = __filbuf(arg0);
                        } else {
                            var_s5 = (s32) *arg0->_ptr;
                            arg0->_ptr += 1;
                        }
                        var_s4 = var_s5;
                    }
                    sp54 = var_s4;
                    if (sp54 == 0x2D) {
                        sp50 = 1;
                    }
                }
            }
        }
        if ((sp54 != 0xA) && (sp54 != -1)) {
loop_32:
            if (__us_rsthread_stdio != 0) {
                sp54 = __semgetc(arg0);
            } else {
                arg0->_cnt -= 1;
                if (arg0->_cnt < 0) {
                    var_s0_3 = __filbuf(arg0);
                } else {
                    var_s0_3 = (s32) *arg0->_ptr;
                    arg0->_ptr += 1;
                }
                sp54 = var_s0_3;
            }
            if ((sp54 != 0xA) && (sp54 != -1)) {
                goto loop_32;
            }
        }
        if (sp50 == 0) {
            if (sp54 == 0xA) {
                if (__us_rsthread_stdio != 0) {
                    sp54 = __semgetc(arg0);
                } else {
                    arg0->_cnt -= 1;
                    if (arg0->_cnt < 0) {
                        var_s0_4 = __filbuf(arg0);
                    } else {
                        var_s0_4 = (s32) *arg0->_ptr;
                        arg0->_ptr += 1;
                    }
                    sp54 = var_s0_4;
                }
            }
            if (sp54 != -1) {
                goto loop_7;
            }
        }
    }
    if (sp54 == -1) {
        rewind(arg0);
    }
}

s8* make_ii_file_name(s8* arg0) {
    s8* sp2C;
    u32 sp28;
    ?* temp_t1;
    s8* temp_t8;

    sp2C = basename(arg0);
    sp28 = strlen(sp2C);
    sp2C = mkstr(sp2C, "   ", NULL);
    temp_t8 = &sp2C[sp28];
    if ((temp_t8->unk_-2 == 0x2E) && (temp_t8->unk_-1 == 0x6F)) {
        temp_t1 = "ii";
        temp_t8->unk_-1 = (u8) temp_t1->unk_0;
        temp_t8->unk_0 = (s8) temp_t1->unk_1;
        temp_t8->unk_1 = (u8) temp_t1->unk_2;
    } else {
        sp2C[sp28] = (unaligned s32) *".ii";
    }
    return mkstr(dirname(arg0), "/ii_files/", sp2C, NULL);
}

void update_instantiation_info_file(s8* arg0, s8* arg1) {
    s8* sp54;
    s8* sp50;
    FILE* sp4C;
    FILE* sp48;
    s32 sp44;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;

    sp54 = make_ii_file_name(arg1);
    sp50 = mkstr(sp54, ".NEW", NULL);
    sp4C = fopen(sp54, "r");
    if (sp4C != NULL) {
        init_curr_dir();
        if (vflag != 0) {
            fprintf(__iob + 0x20, "%s: update_instantiation_info_file %s\n", D_1000C2F0, sp54);
        }
        sp48 = fopen(sp50, "w");
        if (sp48 == NULL) {
            error(1, NULL, 0, "update_instantiation_info_file", 0, "error in creating file %s\n", sp50);
            perror(D_1000C2F0);
            cleanup();
            exit(1);
        }
        skip_old_ii_controls(sp4C);
        func_00431B88(sp48, arg0, 1);
        if (__us_rsthread_stdio != 0) {
            var_s0 = __semgetc(sp4C);
        } else {
            sp4C->_cnt -= 1;
            if (sp4C->_cnt < 0) {
                var_s1 = __filbuf(sp4C);
            } else {
                var_s1 = (s32) *sp4C->_ptr;
                sp4C->_ptr += 1;
            }
            var_s0 = var_s1;
        }
        sp44 = var_s0;
        if (sp44 != -1) {
            do {
                if (__us_rsthread_stdio != 0) {
                    __semputc(sp44, sp48);
                } else {
                    sp48->_cnt -= 1;
                    if (sp48->_cnt < 0) {
                        __flsbuf(sp44, sp48);
                    } else {
                        *sp48->_ptr = (u8) sp44;
                        sp48->_ptr += 1;
                    }
                }
                if (__us_rsthread_stdio != 0) {
                    var_s0_2 = __semgetc(sp4C);
                } else {
                    sp4C->_cnt -= 1;
                    if (sp4C->_cnt < 0) {
                        var_s1_2 = __filbuf(sp4C);
                    } else {
                        var_s1_2 = (s32) *sp4C->_ptr;
                        sp4C->_ptr += 1;
                    }
                    var_s0_2 = var_s1_2;
                }
                sp44 = var_s0_2;
            } while (sp44 != -1);
        }
        fclose(sp4C);
        fclose(sp48);
        if (rename(sp50, sp54) < 0) {
            error(1, NULL, 0, "update_instantiation_info_file", 0, "error in renaming %s to %s\n", sp50, sp54);
            perror(D_1000C2F0);
            cleanup();
            exit(1);
        }
    }
    free(sp54);
    free(sp50);
}

s32 stop_on_exit(s32 arg0) {
    s32 sp29C;
    s8 sp288;
    ? sp68;
    s32 sp64;
    s32 var_s0;

    sp64 = 0;
    sprintf(&sp288, "/proc/%-d", arg0);
    sp29C = open(&sp288, 0x402);
    if (sp29C == -1) {
        perror("Opening /proc");
        kill(arg0, 9);
        exit(1);
    }
    var_s0 = 0x10;
    if (0x10 != 0) {
        do {
            var_s0 -= 1;
            (&sp24[0])[var_s0] = 0;
        } while (var_s0 != 0);
    }
    sp24[0] |= 2;
    if (ioctl(sp29C, 0x7112, &sp24[0]) < 0) {
        perror("PIOCSENTRY");
        kill(arg0, 9);
        exit(1);
    }
    my_vsema();
    if (ioctl(sp29C, 0x7103, &sp68) < 0) {
        perror("PIOCWSTOP");
        kill(arg0, 9);
        exit(1);
    }
    if (sp6C != 3) {
        perror("program halted prematurely");
        kill(arg0, 9);
        exit(1);
    }
    if (sp6E != 2) {
        perror("program halted in wrong system call");
        kill(arg0, 9);
        exit(1);
    }
    if (sp148 != 0) {
        perror("unknown problem\n");
        exit(1);
    }
    return sp29C;
}

void my_psema(void) {
    ? sp27;
    s32 sp20;

    close(Pipe->unk_4);
    sp20 = read(Pipe->unk_0, &sp27, 1U) != 1;
    if (sp20 != 0) {
        perror("read on pipe failed");
        exit(1);
    }
    close(Pipe->unk_0);
}

void my_vsema(void) {
    ? sp27;

    close(Pipe->unk_0);
    if (write(Pipe->unk_4, &sp27, 1U) != 1) {
        perror("write on pipe failed");
        exit(1);
    }
    close(Pipe->unk_4);
}

void print_mem(s8* arg0, s32 count) {
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    u32 sp64;
    u32 sp60;
    u32 sp5C;
    u32 sp58;
    u32 sp54;
    u32 sp50;
    u32 sp4C;
    u32 sp48;
    s32 sp44;
    prmap_sgi_t* temp_t0;
    prmap_sgi_t* temp_t2;
    prmap_sgi_t* temp_t3;
    prmap_sgi_t* temp_t6;
    prmap_sgi_t* temp_t9;
    s32 temp_t1;
    s32 temp_t4;
    s32 temp_t6_2;

    sp44 = memory_flag > 1;
    sp48 = 0;
    sp4C = 0;
    sp50 = 0;
    sp54 = 0;
    sp58 = 0;
    sp5C = 0;
    sp60 = 0;
    sp64 = 0;
    sp68 = getpagesize();
    sp74 = 0;
    if (count > 0) {
        do {
            sp70 = 0;
            temp_t2 = &mapbuf[sp74];
            temp_t4 = temp_t2->pr_mflags & 0xFFFF;
            sp6C = temp_t4;
            if (temp_t4 == 0x80D) {
                sp70 = 1;
                sp64 += temp_t2->pr_vsize * sp68;
            }
            if (sp6C == 0xD) {
                sp70 = 1;
                sp54 += mapbuf[sp74].pr_vsize * sp68;
            }
            if (sp6C == 0x2003) {
                temp_t6 = &mapbuf[sp74];
                if ((u32) temp_t6->pr_vaddr < 0x10000000U) {
                    sp70 = 1;
                    sp50 += temp_t6->pr_vsize * sp68;
                }
            }
            if ((sp6C == 3) || (sp6C == 1) || (sp6C == 0xB) || (sp6C == 9)) {
                temp_t9 = &mapbuf[sp74];
                if ((u32) temp_t9->pr_vaddr < 0x10000000U) {
                    sp70 = 1;
                    sp48 += temp_t9->pr_vsize * sp68;
                }
            }
            temp_t6_2 = sp6C & ~0x800;
            sp6C = temp_t6_2;
            if (temp_t6_2 == 0x2003) {
                temp_t0 = &mapbuf[sp74];
                if ((u32) temp_t0->pr_vaddr >= 0x10000000U) {
                    sp70 = 1;
                    sp60 += temp_t0->pr_vsize * sp68;
                }
            }
            if (sp6C == 0x2013) {
                temp_t3 = &mapbuf[sp74];
                if ((u32) temp_t3->pr_vaddr >= 0x10000000U) {
                    sp70 = 1;
                    sp5C += temp_t3->pr_vsize * sp68;
                }
            }
            if (sp6C == 0x23) {
                sp70 = 1;
                sp58 += mapbuf[sp74].pr_vsize * sp68;
            }
            if (sp70 == 0) {
                fprintf(__iob + 0x20, "-showm: Unidentified: segment %d\n", sp74);
            }
            if ((sp44 != 0) || (sp70 == 0)) {
                fprintf(__iob + 0x20, "pr_vaddr[%d]= %lx\n", sp74, mapbuf[sp74].pr_vaddr);
                fprintf(__iob + 0x20, "pr_size[%d]= %lx\n", sp74, mapbuf[sp74].pr_size);
                fprintf(__iob + 0x20, "pr_off[%d]= %lx\n", sp74, mapbuf[sp74].pr_off);
                fprintf(__iob + 0x20, "pr_mflags[%d]= %lx\n", sp74, mapbuf[sp74].pr_mflags);
                fprintf(__iob + 0x20, "pr_vsize[%d]= %lx\n", sp74, mapbuf[sp74].pr_vsize);
                fprintf(__iob + 0x20, "pr_psize[%d]= %lx\n", sp74, mapbuf[sp74].pr_psize);
                fprintf(__iob + 0x20, "pr_wsize[%d]= %lx\n", sp74, mapbuf[sp74].pr_wsize);
                fprintf(__iob + 0x20, "pr_rsize[%d]= %lx\n", sp74, mapbuf[sp74].pr_rsize);
                fprintf(__iob + 0x20, "pr_msize[%d]= %lx\n", sp74, mapbuf[sp74].pr_msize);
                fprintf(__iob + 0x20, "pr_dev[%d]= %lx\n", sp74, mapbuf[sp74].pr_dev);
                fprintf(__iob + 0x20, "pr_ino[%d]= %lx\n", sp74, mapbuf[sp74].pr_ino);
                fprintf(__iob + 0x20, "\n");
            }
            temp_t1 = sp74 + 1;
            sp74 = temp_t1;
        } while (temp_t1 < count);
    }
    fprintf(__iob + 0x20, "%s phase mem: %dT %dD %dB %dS %dt %dd %db %dm= %dK\n", arg0, sp64 >> 0xA, sp60 >> 0xA, sp5C >> 0xA, sp58 >> 0xA, sp54 >> 0xA, sp50 >> 0xA, sp4C >> 0xA, sp48 >> 0xA, (u32) (sp64 + sp60 + sp5C + sp58 + sp54 + sp50 + sp4C + sp48) >> 0xA);
    if (sp44 != 0) {
        fprintf(__iob + 0x20, "text_size= %d Kbytes\n", sp64 >> 0xA);
        fprintf(__iob + 0x20, "data_size= %d Kbytes\n", sp60 >> 0xA);
        fprintf(__iob + 0x20, "brk_size= %d Kbytes\n", sp5C >> 0xA);
        fprintf(__iob + 0x20, "stack_size= %d Kbytes\n", sp58 >> 0xA);
        fprintf(__iob + 0x20, "so_text_size= %d Kbytes\n", sp54 >> 0xA);
        fprintf(__iob + 0x20, "so_data_size= %d Kbytes\n", sp50 >> 0xA);
        fprintf(__iob + 0x20, "so_brk_size= %d Kbytes\n", sp4C >> 0xA);
        fprintf(__iob + 0x20, "mmap_size= %d Kbytes\n", sp48 >> 0xA);
        fprintf(__iob + 0x20, "TOTAL_SIZE= %d Kbytes\n", (u32) (sp64 + sp60 + sp5C + sp58 + sp54 + sp50 + sp4C + sp48) >> 0xA);
    }
}

s8* func_00433534(s8* arg0) {
    s8* sp24;
    s8* temp_v0;

    temp_v0 = malloc(strlen(arg0) + 3);
    sp24 = temp_v0;
    sp24->unk_0 = 0x2D;
    sp24->unk_1 = 0x2D;
    sp24->unk_2 = 0;
    strcat(sp24, arg0);
    return temp_v0;
}

s32 gethostsex(void) {
    s32 sp4;
    s32 var_v0;

    sp4 = 1;
    var_v0 = 0;
    if ((s8) sp4 == 1) {
        var_v0 = 1;
    }
    return var_v0;
}
