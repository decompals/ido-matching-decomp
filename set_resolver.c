#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
typedef enum  Uopcode   {
	Uabs,	Uadd,	Uadj,	Uaent,	Uand,	Uaos,	Uasym,	Ubgn,
	Ubgnb,	Ubsub,	Ucg1,	Ucg2,	Uchkh,	Uchkl,	Uchkn,	Uchkt,
	Ucia,	Uclab,	Uclbd,	Ucomm,	Ucsym,	Uctrl,	Ucubd,	Ucup,
	Ucvt,	Ucvtl,	Udec,	Udef,	Udif,	Udiv,	Udup,	Uend,
	Uendb,	Uent,	Ueof,	Uequ,	Uesym,	Ufill,	Ufjp,	Ufsym,
	Ugeq,	Ugrt,	Ugsym,	Uhsym,	Uicuf,	Uidx,	Uiequ,	Uigeq,
	Uigrt,	Uijp,	Uilda,	Uildv,	Uileq,	Uiles,	Uilod,	Uinc,
	Uineq,	Uinit,	Uinn,	Uint,	Uior,	Uisld,	Uisst,	Uistr,
	Uistv,	Uixa,	Ulab,	Ulbd,	Ulbdy,	Ulbgn,	Ulca,	Ulda,
	Uldap,	Uldc,	Uldef,	Uldsp,	Ulend,	Uleq,	Ules,	Ulex,
	Ulnot,	Uloc,	Ulod,	Ulsym,	Ultrm,	Umax,	Umin,	Umod,
	Umov,	Umovv,	Umpmv,	Umpy,	Umst,	Umus,	Uneg,	Uneq,
	Unop,	Unot,	Uodd,	Uoptn,	Upar,	Updef,	Upmov,	Upop,
	Uregs,	Urem,	Uret,	Urlda,	Urldc,	Urlod,	Urnd,	Urpar,
	Urstr,	Usdef,	Usgs,	Ushl,	Ushr,	Usign,	Usqr,	Usqrt,	
	Ussym,	Ustep,	Ustp,	Ustr,	Ustsp,	Usub,	Uswp,	Utjp,	
	Utpeq,	Utpge,	Utpgt,	Utple,	Utplt,	Utpne,	Utyp,	Uubd,	
	Uujp,	Uunal,	Uuni,	Uvreg,	Uxjp,	Uxor,	Uxpar,  Umtag,
	Ualia,	Uildi,  Uisti,  Uirld,	Uirst,	Uldrc,	Umsym,	Urcuf,
        Uksym,	Uosym,  Uirlv,  uirsv, size
    }Uopcode;


const char *uopcodeString(Uopcode op)
{
    static const char *names[] = {
        "Uabs","Uadd","Uadj","Uaent","Uand","Uaos","Uasym","Ubgn",
        "Ubgnb","Ubsub","Ucg1","Ucg2","Uchkh","Uchkl","Uchkn","Uchkt",
        "Ucia","Uclab","Uclbd","Ucomm","Ucsym","Uctrl","Ucubd","Ucup",
        "Ucvt","Ucvtl","Udec","Udef","Udif","Udiv","Udup","Uend",
        "Uendb","Uent","Ueof","Uequ","Uesym","Ufill","Ufjp","Ufsym",
        "Ugeq","Ugrt","Ugsym","Uhsym","Uicuf","Uidx","Uiequ","Uigeq",
        "Uigrt","Uijp","Uilda","Uildv","Uileq","Uiles","Uilod","Uinc",
        "Uineq","Uinit","Uinn","Uint","Uior","Uisld","Uisst","Uistr",
        "Uistv","Uixa","Ulab","Ulbd","Ulbdy","Ulbgn","Ulca","Ulda",
        "Uldap","Uldc","Uldef","Uldsp","Ulend","Uleq","Ules","Ulex",
        "Ulnot","Uloc","Ulod","Ulsym","Ultrm","Umax","Umin","Umod",
        "Umov","Umovv","Umpmv","Umpy","Umst","Umus","Uneg","Uneq",
        "Unop","Unot","Uodd","Uoptn","Upar","Updef","Upmov","Upop",
        "Uregs","Urem","Uret","Urlda","Urldc","Urlod","Urnd","Urpar",
        "Urstr","Usdef","Usgs","Ushl","Ushr","Usign","Usqr","Usqrt",
        "Ussym","Ustep","Ustp","Ustr","Ustsp","Usub","Uswp","Utjp",
        "Utpeq","Utpge","Utpgt","Utple","Utplt","Utpne","Utyp","Uubd",
        "Uujp","Uunal","Uuni","Uvreg","Uxjp","Uxor","Uxpar","Umtag",
        "Ualia","Uildi","Uisti","Uirld","Uirst","Uldrc","Umsym","Urcuf",
        "Uksym","Uosym","Uirlv","uirsv","size"
    };

    if (op >= 0 && op < size)
        return names[op];

    return "Unknown Uopcode";
}
bool isMemberOfSet(int member,
                   int* set,
                   int valToSubstract,
                   int valToCompare)
{
    int index = member - valToSubstract;

    /* Bounds check */
    if ((unsigned int)index >= (unsigned int)valToCompare) {
        return false;
    }

    /* Select 32-bit word */
    int wordIndex = index >> 5;          /* index / 32 */
    int bitIndex  = index & 31;          /* index % 32 */

    uint32_t word = (uint32_t)set[wordIndex];

    /* MSB-first bit ordering */
    uint32_t mask = 1u << (31 - bitIndex);

    return (word & mask) != 0;
}

static int D_100162D0[2] = {0x0C010000, 0x00100000};
static int D_100162D8[5] = {0x00008100, 0x00080000, 0, 0, 0x00000100};
static int D_10016170[5] = { 0x801010, 0x80000000, 0x10000, 0x10004000, 0x400000 };
static int D_10016184[4] = { 0x11004001, 0x60000000, 0x20000000, 0x20 };
static int D_10016194[5] = { 0x801010, 0x80000000, 0x20014000, 0x90004000, 0x400000 };
static int D_100161A8[3] = { 0x10000000, 0x40000000, 0x20000000 };
static int D_100161B4[3] = { 0x10000000, 0x40000000, 0x20000000 };
static int D_100161C0[5] = { 0x10000000, 0x40000000, 0x20000000, 0, 0x80000 };
static int D_100161D4[7] = { 0x800011, 0x80000000, 0x10000, 0x10000020, 0, 0, 0 };
static int D_1001699C[3] = {2, 0, 0x10};
static int D_1001255C[5] = { 0x201, 0x2080, 0x10, 0, 0 };

int main() {
    int opc;

    printf("[");
    for (opc = 0; opc < size; opc++) {
        if (isMemberOfSet(opc, D_1001255C, 0x20, 0x60)) {
            printf("%s, ", uopcodeString(opc), opc);
        }
    }
    printf("]\n");
}
