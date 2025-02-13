#include <stdlib.h>

#define INVALID_ADDR -1

typedef struct AddressPair {
    /* 0x00 */ int start;
    /* 0x04 */ int end;
    /* 0x08 */ struct AddressPair* next;
} AddressPair; // size = 0x0C

// .data
AddressPair* notransforms = NULL;
static AddressPair* D_1001B4C4 = NULL;

void add_address_pair(AddressPair** list, int start, int end) {
    AddressPair* ap;

    ap = malloc(sizeof(AddressPair));

    if (start != INVALID_ADDR) {
        ap->start = start;
    }
    if (end != INVALID_ADDR) {
        ap->end = end;
    }
    
    ap->next = *list;
    *list = ap;
}

void set_address_pair(AddressPair* ap, int start, int end) {
    if (start != INVALID_ADDR) {
        ap->start = start;
    }
    if (end != INVALID_ADDR) {
        ap->end = end;
    }
}

static void func_0040D0E8(AddressPair** list) {
    AddressPair* v0;
    AddressPair* v1;
    AddressPair* next;

    for (v0 = *list, v1 = NULL; v0 != NULL && v0->next != NULL;) {
        next = v0->next;
        v0->next = v1;
        v1 = v0;
        v0 = next;
    }

    if (v0 != NULL) {
        v0->next = v1;
        *list = v0;
    }
}

static void func_0040D138(AddressPair** list) {
    AddressPair* s0;
    AddressPair* next;

    for (s0 = *list; s0 != NULL && s0->next != NULL;) {
        if (s0->end == s0->next->start) {
            next = s0->next;
            s0->end = next->end;
            s0->next = next->next;
            free(next);
        } else {
            s0 = s0->next;
        }
    }
}

void finish_address_pairs(AddressPair** list) {
    func_0040D0E8(list);
    func_0040D138(list);
}

int number_address_pairs(AddressPair* first) {
    AddressPair* ptr;
    int count;

    for (ptr = first, count = 0; ptr != NULL; ptr = ptr->next) {
        count++;
    }
    return count;
}

AddressPair* first_address_pair(AddressPair* ap) {
    return D_1001B4C4 = ap;
}

AddressPair* next_address_pair(void) {
    return D_1001B4C4 = D_1001B4C4->next;
}

int current_address_pair_start(void) {
    return D_1001B4C4->start;
}

unsigned int current_address_pair_length(void) {
    return (D_1001B4C4->end - D_1001B4C4->start) / 4;
}