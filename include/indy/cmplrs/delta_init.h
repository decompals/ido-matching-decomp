typedef int (*__runtime_vptp)();

struct __runtime_mptr {
    short d;
    short i;
    __runtime_vptp f;
};

#define DELTA_INIT_OFFSET_TO_D_FIELD 0
#define DELTA_INIT_OFFSET_TO_F_FIELD 4

struct __runtime_vtblinfo {
    short instance_offset;
    short vtable_offset;
    short vbase_offset;
};

struct __runtime_vbaseinfo {
    short vbase_offset;
    short vbase_ptr_offset;
    struct __runtime_classinfo *vbase_info;
};

struct __runtime_classinfo {
    struct __runtime_mptr *vtable;
    struct __runtime_vtblinfo *vtbl_info;
};

