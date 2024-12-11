#include "linklist.h"

char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/linklist.c,v 1.1 1992/07/29 18:45:02 wsj Exp $";

LinkedList* link_start(MemCtx* mem, int size) {
    LinkedList* ll = mem_alloc(mem, sizeof(LinkedList), 4);

    ll->mem = mem;
    ll->elem_size = size;
    return ll;
}

void* get_link_elem(LinkedList* ll) {
    unsigned int i;
    void* retval = ll->free_list;
    
    if (ll->free_list != NULL) {
        int* ptr = (int*)ll->free_list;
        // fill element with zeroes
        ll->free_list = ll->free_list->next;
        for (i = 0; i < ll->elem_size >> 2; i++) {
            *ptr++ = NULL;
        }
    } else {
        retval = mem_alloc(ll->mem, ll->elem_size, 8); 
    }

    return retval;
}

void* link_pop(LinkedList* ll) {
    LinkedListEntry* next_used;
    LinkedListEntry* used_el;

    used_el = ll->used_list;
    next_used = used_el->next;
    used_el->next = ll->free_list;
    ll->free_list = used_el;
    ll->used_list = next_used;

    return next_used;
}

void free_link_list(LinkedList* ll) {
    if (ll->free_list != NULL && ll->used_list != NULL) {
        LinkedListEntry* previous = ll->used_list;
        LinkedListEntry* used_ptr = ll->used_list->next;        

        while (used_ptr != NULL) {
            previous = used_ptr;
            used_ptr = used_ptr->next;
        }

        previous->next = ll->free_list;
        ll->free_list = ll->used_list;
        ll->used_list = NULL;
    } else if (ll->used_list != NULL) {
        ll->free_list = ll->used_list;
        ll->used_list = NULL;
    }
}