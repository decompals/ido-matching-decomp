
typedef union
#ifdef __cplusplus
	YYSTYPE
#endif
 {
	int location;
	TreeNode* node; 
	struct TokenIdentifier identifier;
	struct DeclSpec declspec;
	struct Declarator declarator;
	struct TreeNodeList list;
} YYSTYPE;
extern YYSTYPE yylval;
# define IDENTIFIER 257
# define SIZEOF 258
# define ALIGNOF 259
# define CLASSOF 260
# define UNALIGN 261
# define STRING 262
# define WSTRING 263
# define CONSTANT 264
# define PTR_OP 265
# define INC_OP 266
# define DEC_OP 267
# define LEFT_OP 268
# define RIGHT_OP 269
# define LE_OP 270
# define AND_OP 271
# define OR_OP 272
# define GE_OP 273
# define NE_OP 274
# define EQ_OP 275
# define MUL_ASSIGN 276
# define DIV_ASSIGN 277
# define REM_ASSIGN 278
# define ADD_ASSIGN 279
# define SUB_ASSIGN 280
# define LEFT_ASSIGN 281
# define RIGHT_ASSIGN 282
# define AND_ASSIGN 283
# define XOR_ASSIGN 284
# define OR_ASSIGN 285
# define TYPEDEF 286
# define EXTERN 287
# define STATIC 288
# define AUTO 289
# define REGISTER 290
# define CHAR 291
# define SHORT 292
# define INT 293
# define LONG 294
# define LONGLONG 295
# define SIGNED 296
# define UNSIGNED 297
# define FLOAT 298
# define DOUBLE 299
# define CONST 300
# define VOLATILE 301
# define VOID 302
# define STRUCT 303
# define UNION 304
# define ENUM 305
# define ELLIPSIS 306
# define TYPE_IDENT 307
# define CASE 308
# define DEFAULT 309
# define IF 310
# define ELSE 311
# define SWITCH 312
# define WHILE 313
# define DO 314
# define FOR 315
# define GOTO 316
# define LEAVE 317
# define CONTINUE 318
# define BREAK 319
# define RETURN 320
# define TRY 321
# define EXCEPT 322
# define FINALLY 323
# define __PRAGMA 324
# define CLASS 325
# define VIRTUAL 326
# define PROTECTED 327
# define PUBLIC 328
# define PRIVATE 329
# define COLONCOLON 330
# define COLCOLSTAR 331
# define OPERATOR 332
# define THIS 333
# define MEMDOT_OP 334
# define MEMPTR_OP 335
# define NEW 336
# define DELETE 337
# define INLINE 338
# define FRIEND 339
