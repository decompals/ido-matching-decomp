#ifndef __RUNTIME_H__
#define __RUNTIME_H__
#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEBUG
typedef char *__dynamic_vptp;
#else
typedef int (*__dynamic_vptp)();
#endif

struct __dynamic_mptr {
    short d;
    short i;
    __dynamic_vptp f;
    struct __specclassinfo *info;
    struct __dynamic_mptr *virtvtbl;
};

/* values for method_type field in __moinfo */

#define __RUNTIME_STATIC 2
#define __RUNTIME_VIRTUAL 1
#define __RUNTIME_NONVIRTUAL 0

/* values for protection fields */

#define __RUNTIME_PUBLIC 2
#define __RUNTIME_PROTECTED 1
#define __RUNTIME_PRIVATE 0

/* values for internal_type field in __voinfo */

#define __RUNTIME_REG 0
#define __RUNTIME_VPTR 1
#define __RUNTIME_VCLASS_PTR 2

/* values for virt field in __coinfo */

#define __RUNTIME_PARENT_CLASS 0
#define __RUNTIME_VIRTUAL_CLASS 1
#define __RUNTIME_ANCESTOR_CLASS 2
#define __RUNTIME_THIS_CLASS 3

/* values for can_switch_qualifying_class */

#define __RUNTIME_FIXED_QUAL 0
#define __RUNTIME_CHANGE_QUAL 1
#define __RUNTIME_NO_QUAL 2

struct __moinfo {
    char *name;
    short mo;
    short so;
    __dynamic_vptp f;
    struct __specclassinfo *info;
    short d;
    char method_type;
    char protection;
    char internally_generated;
    char can_switch_qualifying_class;
    char *return_signature;
    struct __classinfo *defining_class;
    struct __classinfo *declaring_class;
    struct __classinfo *qualifying_class;
    short next;
};

struct __vmoinfo {
    char *name;
    __dynamic_vptp f;
};

struct __voinfo {
    char *name;
    short vo;
    short sz;
    char alignment; /* 0 byte, 1 halfword, 2 word, 3 double word */
    signed char bitfield_size; /* -1 indicates no bitfield, 0 realign bit field */ 
    char bitfield_pos;
    char *class_name;
    char defined;	/* for defined entries this is indicates whether this field is defined in the current class */
                        /* for vo_table entries it is the depth to the root of the class tree */
    char internal_type;
    char protection;
    char can_switch_qualifying_class;
    char *type_signature;
    struct __classinfo *defining_class;
    struct __classinfo *qualifying_class;
    short next;
};

struct __svoinfo {
    char *name;
    short svo;
    char protection;
    char can_switch_qualifying_class;
    char *var;	    /* has a value if defined in class */
    char *type_signature;
    struct __classinfo *defining_class;
    struct __classinfo *qualifying_class;
    short next;
};

struct __coinfo {
    char *name;
    short mo;
    short so;
    short sso;
    short sz;
    char alignment;
    char virt;
    char protection;
    struct __classinfo *info;
};

struct __vtableinfoentry {
    short vo;
    short mo;
    short co;
};

struct __vtableinfo {
    struct __dynamic_mptr *vtbl;
    struct __vtableinfoentry *offsets;
};

struct __virtualbaseinfo {
    char *name;
    short vo_offset;	    /* instance position of defining class */
    short mo_offset;	    /* method poistion of defining class */
    short svo_offset;
    short vo_vb_offset;	    /* position of instance virtual ptr */
    short mo_vb_offset;	    /* position of method virtual ptr */
    short svo_vb_offset;
    short virtual_vo_offset;	/* instance position of virtual class */
    short virtual_mo_offset;	/* method position of virtual class */
    short virtual_svo_offset;
    short virtual_vo_table_offset;
    struct __moinfo *mo_info;
    struct __svoinfo *svo_info;
    struct __virtualbaseinfo *next;
    struct __classinfo *info;
    char first;
    char isBase;	    /* non-zero if base offset, 2 if brand new offset */
    short sz;
    char alignment;
};

struct __classinfo {
    char *name;
    char initialized;
    char stored;

    short num_defined_mo_entries;
    short num_defined_vmo_entries;
    short num_defined_vo_entries;
    short num_defined_svo_entries;
    short num_defined_co_entries;
    short num_defined_virtual_co_entries;

    struct __moinfo **defined_mo_table;
    struct __vmoinfo *defined_vmo_table;
    struct __voinfo **defined_vo_table;
    struct __svoinfo **defined_svo_table;
    struct __coinfo **defined_co_table;

    unsigned short *class_depth;
    char alignment;

    void *(*nw)(unsigned int);
    __dynamic_vptp ctor;
    __dynamic_vptp ctor2;
    __dynamic_vptp dtor;
    __dynamic_vptp as;

    short mo_size;
    short full_mo_size;
    short max_mo_size;
    struct __moinfo *mo_table;

    short vo_size;
    short full_vo_size;
    short vo_table_size;
    short full_vo_table_size;
    short max_vo_table_size;
    short remaining_bits;
    struct __voinfo *vo_table;

    short svo_size;
    short full_svo_size;
    short max_svo_size;
    struct __svoinfo *svo_table;

    short vt_size;
    short full_vt_size;
    short max_vt_size;
    struct __vtableinfo *vtable_info;

    short bc_size;
    short max_bc_size;
    struct __coinfo *co_table;

    short vb_size;
    short max_vb_size;
    struct __virtualbaseinfo *vb_info;

    char **static_table;

    short vptr_offset;

    short unknown_mo_list_size;
    short max_unknown_mo_list_size;
    short *unknown_mo;
    short unknown_vo_list_size;
    short max_unknown_vo_list_size;
    short *unknown_vo;
    short unknown_svo_list_size;
    short max_unknown_svo_list_size;
    short *unknown_svo;

    void *classSymbol;	/* Hook for C++/WorkShop to store a SymbolPtr */
};

struct __specclassinfo
{
    struct __classinfo *cinfo;
    struct __dynamic_mptr **sprtbl;
    short size;
};

#define __LDX_DYNAMICS 0
#define __LDX_NO_DYNAMICS 1
#define __LDX_READ_ERROR 2

extern void __initialize_delta_runtime(int can_free);
extern void __reset_delta_runtime(void);

extern int __extract_classinfo_from_file_descriptor(int fildes);
extern int __extract_classinfo(char *filename);

extern struct __classinfo *__get_class_information(const char *name, int init);
extern int __store_class_information(struct __classinfo *info);
extern void __initialize_class(struct __classinfo *info);
extern short __align_data(short currentSize, char alignment);
extern void __initialize_all_stored_classes(void);

extern struct __classinfo *__class_iterate(int (*func)(struct __classinfo *, void *), void *data);

extern void __ldx_free_all_class_info(void);
#ifdef DEBUG
extern void __print_class_information(struct __classinfo *info);
#endif

void __set_callback_funrtion(struct __classinfo *(*rtn)(const char *, void *), void *data);

extern struct __classinfo *drt_begin_class_description(char *name); /* returns classinfo if class already entered , NULL otherwise */
extern struct __classinfo *drt_end_class_description(void);
extern void drt_enter_base_class(char *name, char virt, char protection);
extern void drt_enter_method(char *name, __dynamic_vptp f, char method_type, char protection, char *return_type);
extern void drt_enter_member(char *name, long sz, long alignment, char *class_name, char defined, char internal_type, char protection, char *type);
extern void drt_enter_bitfield_member(char *name, long sz, long alignment, long bitfield_size, char defined, char internal_type, char protection, char *type);
extern void drt_enter_static_member(char *name, long sz, char *var, char protection, char *type);
extern void drt_enter_static_base_class(char *name, char virt, char protection, long sz, char alignament);


struct __object_info {
    void *ptr;
    long offset;
    struct __classinfo *info;
};

struct __method_info {
    void *calling_ptr;
    long calling_offset;
    void *passing_ptr;
    long passing_offset;
    __dynamic_vptp f;
    struct __moinfo *method;
};

struct __instance_info {
    void *ptr;
    long offset;
    struct __voinfo *instance;
    int ambig;
};

struct __static_instance_info {
    void *ptr;
    struct __svoinfo *instance;
    int ambig;
};

#ifdef __cplusplus
}
#endif
#endif /* __RUNTIME_H__ */
