#ifndef PROTOS_H
#define PROTOS_H
extern void func_00405574(s32 arg0); //static
extern void EnterSym(s32 arg0, struct sym** arg1, s32 arg2);
extern s32 LookUp(s32*, void**);
extern void nexttoken();
extern s32 opLookUp(s8*, struct sym**);
extern void posterror(char* arg0, char* arg1, s32 arg2);
extern void put_binasmfyle();
extern s32 sym_define(s32, u32, s32);
extern void GetItem(s32* arg0, s32* arg1);
extern void Parsestmt(void);
extern void do_dot_end(s32 arg0);
extern void sym_init(s32 arg0);
#endif
