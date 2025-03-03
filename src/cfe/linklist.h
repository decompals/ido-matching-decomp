#ifndef LINKLIST_H
#define LINKLIST_H

#include "mem.h"

typedef struct LinkedListEntry {
    /* 0x00 */ struct LinkedListEntry* next;
} LinkedListEntry; // variable size

typedef struct LinkedList {
    /* 0x00 */ LinkedListEntry* used_list;
    /* 0x04 */ LinkedListEntry* free_list;
    /* 0x08 */ MemCtx* mem;
    /* 0x0C */ unsigned int elem_size;
} LinkedList; // size = 0x10

LinkedList* link_start(MemCtx* mem, int size);
void* link_pop(LinkedList* ll);
void* get_link_elem(LinkedList* ll);
void free_link_list(LinkedList* ll);

#endif
