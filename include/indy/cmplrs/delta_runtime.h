#ifndef __RUNTIME_H__
#define __RUNTIME_H__
#ifdef __cplusplus
extern "C" {
#endif

#ifdef LARGE_CLASSES
typedef int ClassSize;
#define MAX_VO_SIZE 0x7fffffff
#define MAX_MO_SIZE 0x1fffffff
#define MAX_SVO_SIZE 0x7fffffff
#else
typedef short ClassSize;
#define MAX_VO_SIZE 0x8000
#define MAX_MO_SIZE 0x1000
#define MAX_SVO_SIZE 0x8000
#endif

#ifdef DEBUG
typedef char *__dynamic_vptp;
#else
typedef int (*__dynamic_vptp)();
#endif

#ifdef CALCULATE_MALLOC_INFO
extern char *runtime_malloc(int new_size);
extern char *runtime_realloc(char *ptr, int old_size, int new_size);
#define RUNTIME_MALLOC(sz) runtime_malloc(sz)
#define RUNTIME_REALLOC(ptr, old_sz, new_sz) runtime_realloc((char *) (ptr), old_sz, new_sz)
#else
#define RUNTIME_MALLOC(sz) malloc(sz)
#define RUNTIME_REALLOC(ptr, old_sz, new_sz) realloc((char *) (ptr), new_sz)
#endif

struct delta_hash_table_entry {
    const char *key;
    unsigned int hash_value;
    void *data;
};

struct delta_hash_table{
    int size;
    int number_of_elements;
    struct delta_hash_table_entry *tbl;
};

extern struct delta_hash_table *delta_hashinit(unsigned int size);
extern unsigned int delta_hashmod(struct delta_hash_table *phashtab, const char *pname);
extern int delta_hashlookup(struct delta_hash_table *phashtab, const char *name, void **val);
extern void *delta_hashenter(struct delta_hash_table *phashtab, const char *name, void *data);
extern void delta_deletehashtable(struct delta_hash_table *phashtab);

struct __dynamic_mptr {
    short d;
    short i;
    __dynamic_vptp f;
    struct __specclassinfo *info;
    struct __dynamic_mptr *virtvtbl;
};

#define INVALID_VO_SIZE 1
#define INVALID_MO_SIZE 2
#define INVALID_SVO_SIZE 4
#define INVALID_BASE_CLASSES 8
#define INVALID_INTERNAL_ERROR 16
#define INVALID_UNDEFINED_CLASS 32

/* values for method_type field in __moinfo */

#define __RUNTIME_PURE_VIRTUAL 3
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
    ClassSize mo;
    ClassSize so;
    __dynamic_vptp f;
    ClassSize d;
    char method_type : 3;
    char protection : 2;
    char can_switch_qualifying_class : 2;
    char first : 1;
    char defined : 1;
    char *return_signature;
    struct __classinfo *defining_class;
    struct __classinfo *declaring_class;
    struct __classinfo *qualifying_class;
    ClassSize next;
    ClassSize vptr_offset;
};

struct __vmoinfo {
    char *name;
    __dynamic_vptp f;
};

struct __voinfo {
    char *name;
    ClassSize vo;
    ClassSize sz;
    signed char bitfield_size; /* -1 indicates no bitfield, 0 realign bit field */ 
    char bitfield_pos;
    short entry_index; /* index used for anonymous unions */
    char *class_name;
    char alignment : 3; /* 0 byte, 1 halfword, 2 word, 3 double word */
    char defined : 1;	/* for defined entries this is indicates whether this field is defined in the current class */
                        /* for vo_table entries it is the depth to the root of the class tree */
    char internal_type : 2;
    char protection : 2;
    char can_switch_qualifying_class : 1;
    char first: 1;
    ClassSize next;
    char *type_signature;
    struct __classinfo *defining_class;
    struct __classinfo *qualifying_class;
    struct __virtualinfo *vbase_class;
};

struct __svoinfo {
    char *name;
    char protection : 2;
    char can_switch_qualifying_class : 2;
    char first : 1;
    ClassSize next;
    char *var;	    /* has a value if defined in class */
    char *type_signature;
    struct __classinfo *defining_class;
    struct __classinfo *qualifying_class;
};

struct __coinfo {
    char *name;
    ClassSize mo;
    ClassSize vtbl_mo;
    ClassSize so;
    ClassSize sz;
    char alignment;
    char virt;
    char protection;
    char nondyn;
    struct __classinfo *info;
};

struct __vtableinfo {
    ClassSize vo;
    ClassSize mo;
    ClassSize co;
};

struct __selfvbaseinfo {
    ClassSize vo;
    ClassSize so;
};

struct __virtualinfo {
    char *name;
    struct __classinfo *info;
    ClassSize first;
    ClassSize virtual_vo_offset;	/* instance position of virtual class */
    ClassSize virtual_mo_offset;	/* method position of virtual class */
    ClassSize virtual_vtbl_mo_offset;	/* method position of virtual class */
    ClassSize virtual_svo_offset;
    ClassSize vo_vb_offset;	    /* position of main virtual class ptr */
    ClassSize virtual_vo_table_offset;
    ClassSize virtual_entry_index;
    ClassSize sz;
    char alignment : 3;
    char direct: 1;
    char protection : 2;
};

struct __virtualbaseinfo {
    ClassSize vo_offset;	    /* instance position of defining class */
    ClassSize vo_vb_offset;	    /* position of instance virtual ptr */
    struct __moinfo *mo_info;
    struct __svoinfo *svo_info;
    char from_virtual;
    ClassSize next;
};

struct __classinfo {
    char *name;
    char initialized : 1;
    char stored : 1;
    char nondyn : 1;
    char invalid;
    char alignment;

    ClassSize num_defined_mo_entries;
    ClassSize num_defined_vo_entries;
    ClassSize num_defined_svo_entries;
    ClassSize num_defined_co_entries;
    ClassSize num_defined_virtual_co_entries;

    struct __moinfo *mo_table;
    struct __voinfo *vo_table;
    struct __svoinfo *svo_table;
    struct __vtableinfo *vtable_info;
    struct __selfvbaseinfo *self_base_table;
    struct __coinfo *co_table;
    struct __virtualinfo *virtual_info;
    struct __virtualbaseinfo *vb_info;

    struct delta_hash_table *mo_hash;
    struct delta_hash_table *vo_hash;
    struct delta_hash_table *svo_hash;
      
    void *classSymbol;	/* Hook for C++/WorkShop to store a SymbolPtr */

    ClassSize mo_size;
    ClassSize full_mo_size;
    ClassSize vtbl_mo_size;
    ClassSize full_vtbl_mo_size;

    ClassSize vo_size;
    ClassSize full_vo_size;
    ClassSize vo_table_size;
    ClassSize full_vo_table_size;
    ClassSize remaining_bits;
    ClassSize entry_index;
    ClassSize full_entry_index;

    ClassSize svo_size;
    ClassSize full_svo_size;

    ClassSize vt_size;
    ClassSize full_vt_size;

    ClassSize self_vb_size;
    ClassSize full_self_vb_size;

    ClassSize bc_size;
    ClassSize full_bc_size;

    ClassSize virtual_base_size;

    ClassSize vb_size;

    ClassSize vptr_offset;
    ClassSize self_vbaseptr_offset;

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
extern int __align_data(int currentSize, char alignment);
extern void __initialize_all_stored_classes(void);

extern struct __classinfo *__class_iterate(int (*func)(struct __classinfo *, void *), void *data);

extern void __ldx_free_all_class_info(void);
#ifdef DEBUG
extern void __print_class_information(struct __classinfo *info);
#endif

void __set_callback_function(struct __classinfo *(*rtn)(const char *, void *), void *data);

/* returns classinfo if class already entered , NULL otherwise */
extern struct __classinfo *drt_begin_class_description(const char *name);
extern struct __classinfo *drt_begin_nondyn_class_description(const char *name,
							      long size,
							      long alignment,
							      long vtbl_size);
extern struct __classinfo *drt_end_class_description(void);

extern void drt_enter_base_class(const char *name,
				 char virt,
				 char protection);
extern void drt_enter_nondyn_base_class(const char *name,
					long pos,
					long vtbl_pos,
					char virt,
					char protection);
extern void drt_enter_static_base_class(const char *name,
					char virt,
					char protection,
					long size,
					char alignment);

extern void drt_enter_method(const char *name,
			     __dynamic_vptp f,
			     char method_type,
			     char protection,
			     char *return_type);
extern void drt_enter_method_no_copy(const char *name,
				     __dynamic_vptp f,
				     char method_type,
				     char protection,
				     void *return_type);
extern void drt_enter_nondyn_method(const char *name,
				    __dynamic_vptp f,
				    char method_type,
				    int vtbl_pos,
				    char protection,
				    char *return_type);
extern void drt_enter_nondyn_method_no_copy(const char *name,
					    __dynamic_vptp f,
					    char method_type,
					    int vtbl_pos,
					    char protection,
					    void *return_type);

extern void drt_enter_static_member(const char *name,
				    long size,
				    char *var,
				    char protection,
				    char *type);
extern void drt_enter_static_member_no_copy(const char *name,
					    long size,
					    void *var,
					    char protection,
					    void *type);

extern void drt_enter_member(const char *name,
			     long size,
			     long alignment,
			     const char *class_name,
			     char defined,
			     char internal_type,
			     char protection,
			     char *type);
extern void drt_enter_member_no_copy(const char *name,
				     long size,
				     long alignment,
				     const char *class_name,
				     char defined,
				     char internal_type,
				     char protection,
				     void *type);
extern void drt_enter_nondyn_member(const char *name,
				      long pos,
				      long size,
				      long alignment,
				      char protection,
				      void *type);
extern void drt_enter_nondyn_member_no_copy(const char *name,
					    long pos,
					    long size,
					    long alignment,
					    char protection,
					    void *type);

extern void drt_enter_bitfield_member(const char *name,
				      long size,
				      long alignment,
				      long bitfield_size,
				      char defined,
				      char internal_type,
				      char protection,
				      char *type);
extern void drt_enter_bitfield_member_no_copy(const char *name,
					      long size,
					      long alignment,
					      long bitfield_size,
					      char defined,
					      char internal_type,
					      char protection,
					      void *type);
extern void drt_enter_nondyn_bitfield_member(const char *name,
					     long pos,
					     long size,
					     long alignment,
					     long bitfield_pos,
					     long bitfield_size,
					     char protection,
					     void *type);
extern void drt_enter_nondyn_bitfield_member_no_copy(const char *name,
						     long pos,
						     long size,
						     long alignment,
						     long bitfield_pos,
						     long bitfield_size,
						     char protection,
						     void *type);

extern void drt_begin_anonymous_union(void);
extern void drt_end_anonymous_union(void);

extern void drt_enter_nondyn_vptr(int pos, void *type);
extern void drt_enter_nondyn_vptr_no_copy(int pos, void *type);

extern void drt_enter_nondyn_vbase_ptr(const char *name,
				       int pos,
				       void *type);
extern void drt_enter_nondyn_vbase_ptr_no_copy(const char *name,
					       int pos,
					       void *type);

extern void __set_error_function(int (*rtn)(const char *, struct __classinfo *, void *) , void *data);

extern struct __instance_info *__get_instance(void *ptr, struct __classinfo *declared_info, struct __classinfo *qualified_info, char *instance_name, struct __instance_info *ret_info);

extern struct __method_info *__get_method(void *ptr, struct __classinfo *declared_info, struct __classinfo *qualified_info, char *method_name, struct __method_info *ret_info);

extern struct __static_instance_info *__get_static_instance(struct __classinfo *declared_info, char *instance_name, struct __static_instance_info *ret_info);

extern struct __object_info *__get_vbase_ptr_by_name(void *ptr, struct __classinfo *declared_info, char *virtual_base_name, struct __object_info *ret_info);

extern struct __object_info *__upcast_object_by_name(void *ptr, struct __classinfo *declared_info, char *cast_name, struct __object_info *ret_info);

extern struct __object_info *__upcast_object(void *ptr, struct __classinfo *declared_info, struct __classinfo *cast_info, struct __object_info *ret_info);

struct __object_info {
    void *ptr;
    long offset;      /* Offset to class or offset within virtual base class */
    long full_offset; /* offset including offset to virtual base class */
    long vbaseptr_offset;
    struct __classinfo *info;
};

struct __method_info {
    void *calling_ptr;
    long calling_offset;
    void *passing_ptr;
    long passing_offset;
    long vptr_offset;
    long vbaseptr_offset;
    __dynamic_vptp f;
    struct __moinfo *method;
};

struct __instance_info {
    void *ptr;
    long offset;
    long vbaseptr_offset;
    struct __voinfo *instance;
    int ambig;
};

struct __static_instance_info {
    void *ptr;
    struct __svoinfo *instance;
    int ambig;
};

struct _delta_catalog_malloc_pool_item {
    char *pool;
    int remaining;
    int size;
    struct _delta_catalog_malloc_pool_item *next;
};

struct _delta_catalog {
    struct __classinfo **class_info_table;
    struct delta_hash_table *class_hash;
    long num_of_classes;
    long max_num_of_classes;
    struct _delta_catalog **library_catalogs;
    long num_of_library_catalogs;
    long max_num_of_library_catalogs;
    struct __classinfo *(*fill_in_routine)(const char *, void *);
    void *fill_in_data;
    int (*missing_class_error_proc)(const char *, struct __classinfo *, void *);
    void *missing_class_error_data;
    void *info;
    struct _delta_catalog_malloc_pool_item *pool;
};

extern struct _delta_catalog_malloc_pool_item *delta_int_get_pool_item(int size);

extern struct _delta_catalog *current_catalog;

#ifdef __cplusplus
}
#endif
#endif /* __RUNTIME_H__ */
