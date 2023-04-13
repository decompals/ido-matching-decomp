#ifndef __DELTA_H__
#define __DELTA_H__
#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#include "delta_internal.h"

typedef struct _delta_catalog	*delta_catalog_ptr;
typedef struct __classinfo	*delta_class_ptr;
typedef struct _delta_base	*delta_base_ptr;
typedef struct _delta_data	*delta_data_ptr;
typedef struct _delta_method	*delta_method_ptr;
typedef struct _delta_cast	*delta_cast_ptr;

typedef enum _delta_access delta_access;
typedef enum _delta_alignment delta_alignment;

#define DELTA_DATA_NOT_A_BITFIELD 255

#define DELTA_ACCESS_PUBLIC    _DELTA_ACCESS_PUBLIC
#define DELTA_ACCESS_PROTECTED _DELTA_ACCESS_PROTECTED
#define DELTA_ACCESS_PRIVATE   _DELTA_ACCESS_PRIVATE
#define DELTA_ACCESS_UNKNOWN   _DELTA_ACCESS_UNKNOWN

#define DELTA_BYTE_ALIGNED     _DELTA_BYTE_ALIGNED
#define DELTA_HALF_ALIGNED     _DELTA_HALF_ALIGNED
#define DELTA_WORD_ALIGNED     _DELTA_WORD_ALIGNED
#define DELTA_DOUBLE_ALIGNED   _DELTA_DOUBLE_ALIGNED

#define delta_alignment_in_bytes(align_const)	((int) align_const)

/* Catalog Setting Routines */

extern delta_catalog_ptr delta_get_class_catalog (void *info);
extern delta_catalog_ptr delta_set_current_class_catalog (delta_catalog_ptr catalog);
extern void delta_delete_current_catalog (void);
extern void delta_add_library_catalog(delta_catalog_ptr catalog);
extern void delta_remove_library_catalog(delta_catalog_ptr catalog);

#define delta_get_info_for_current_catalog()	(current_catalog->info)
#define delta_get_info_for_catalog(c)		((c)->info)

/* Class Extraction */

extern delta_class_ptr
       delta_get_class_information (const char *name, int init);

extern long delta_class_size (delta_class_ptr class_ptr);

extern delta_alignment delta_class_alignment (delta_class_ptr class_ptr);

#define delta_class_name(p)			((p)->name)

/* Base Class Extraction */

extern void delta_base_iterate (delta_class_ptr class_ptr,
				int (*func) (delta_class_ptr,
					     delta_base_ptr,
					     void *),
				void *data);

#define delta_base_name(p)			((p)->base_class->name)
#define delta_base_class_ptr(p)			((p)->base_class)
#define delta_base_is_virtual(p)		((p)->is_virtual)
#define delta_base_offset(p)			((p)->offset)
#define delta_base_vbase_ptr_offset(p)		((p)->vbase_ptr_offset)
#define delta_base_access(p)			((p)->access)

/* Data Extraction */

extern delta_data_ptr
       delta_get_data_member (const char *name,
			      delta_class_ptr declared_class,
			      delta_class_ptr qualified_class,
			      delta_data_ptr ret_info);

extern void delta_data_iterate (delta_class_ptr class_ptr,
				int (*func) (delta_class_ptr,
				             delta_data_ptr,
					     void *),
				void *data);

/* Iterates through all data member with the same name, includes the main member
    which must be the main element */

extern void delta_related_data_iterate(delta_class_ptr class_ptr,
					delta_data_ptr main_member,
					int (*func) (delta_class_ptr,
						     delta_data_ptr,
						     void *),
					void *data);

#define delta_data_is_static(p)			((p)->is_static)
#define	delta_data_is_main_element(p)		((p)->is_main_element)
#define delta_data_name(p)			((p)->name)
#define delta_data_var_ptr(p)			((p)->var_ptr)
#define delta_data_virtual_base_class_offset(p)	((p)->vbase_offset)
#define delta_data_byte_offset(p)		((p)->offset)
#define delta_data_byte_size(p)			((p)->size)
#define delta_data_bit_field_size(p)		((p)->bit_field_size)
#define delta_data_bit_field_position(p)	((p)->bit_field_position)
#define delta_data_info(p)			((p)->info)
#define delta_data_qualified_class(p)		((p)->qualified_class)
#define delta_data_declaring_class(p)		((p)->declaring_class)
#define delta_data_access(p)			((p)->access)

/* Method Extraction */

extern delta_method_ptr
       delta_get_method (const char *name,
			 delta_class_ptr declared_class,
			 delta_class_ptr qualfied_class,
			 delta_method_ptr ret_info);

extern void delta_method_iterate (delta_class_ptr class_ptr,
				  int (*func) (delta_class_ptr,
					       delta_method_ptr,
					       void *),
				  void *data);

/* Iterates through all member functions with the same name, includes the main member
    which must be the main element */

extern void delta_related_method_iterate(delta_class_ptr class_ptr,
					  delta_method_ptr main_member,
					  int (*func) (delta_class_ptr,
						       delta_method_ptr,
						       void *),
					  void *data);

#define delta_method_is_static(p)		((p)->is_static)
#define	delta_method_is_main_element(p)		((p)->is_main_element)
#define delta_method_name(p)			((p)->name)
#define delta_method_is_virtual(p)		((p)->is_virtual)
#define delta_method_virtual_base_offset(p)	/* TODO */
#define delta_method_function_ptr(p)		((p)->function_ptr)
#define delta_method_this_offset(p)		((p)->this_offset)
#define delta_method_vptr_offset(p)		((p)->vptr_offset)
#define delta_method_vtable_offset(p)		((p)->vtable_offset)
#define delta_method_info(p)			((p)->info)
#define delta_method_qualified_class(p)		((p)->qualified_class)
#define delta_method_declaring_class(p)		((p)->declaring_class)
#define delta_method_defining_class(p)		((p)->defining_class)
#define delta_method_access(p)			((p)->access)

#ifdef __cplusplus
}
#endif
#endif /* __DELTA_H__ */
