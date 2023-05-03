#ifndef PROTOS_H
#define PROTOS_H

extern int stores_to_memory(void** arg0);
extern int func_0041BB98(int arg0);
extern void ltoa(const char* src, char* dest);
extern void call_name_and_line(s32);

extern void st_error(const char* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void st_warning(const char* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void st_printf_2(const char* str, int arg1);
extern void st_printf_3(const char* str, int arg1, int arg2);
extern void st_internal(const char* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

extern int l_addr(int arg0);
extern int s_addr(int arg0);
extern int e_addr(int arg0);

extern int recalloc(s32, s32, s32);                            /* extern */
extern int xfree(void *ptr);


#endif //PROTOS_H
