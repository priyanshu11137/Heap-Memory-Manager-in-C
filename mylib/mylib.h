#ifndef __MYLIB__   
#define __MYLIB__

#include <stdint.h>
#include "glthread/glthread.h"
#include <stddef.h> /*for size_t*/

#define MAX_SIZE_STRUCT_NAME 32
static int SYSTEM_PAGE_SIZE = 0;

typedef struct page_struct {
    char name[MAX_SIZE_STRUCT_NAME];
    uint32_t size;
} page_struct_t;

typedef struct page_family {
    struct page_family *next;
    struct page_family *prev;
    page_struct_t first_struct[0];  // Flexible array member
} page_family_t;

#define MAX_PAGE_STRUCTS_PER_PAGE \
    ((SYSTEM_PAGE_SIZE - offsetof(page_family_t, first_struct)) / sizeof(page_struct_t))

#define ITERATE_VM_PAGE_FAMILY_BEGIN(page_family_head, curr) \
    { \
        uint32_t count = 0; \
        for (curr = &(page_family_head)->first_struct[0]; \
             curr->size && count < MAX_PAGE_STRUCTS_PER_PAGE; \
             curr++, count++) {

#define ITERATE_VM_PAGE_FAMILY_END() \
        } \
    }

static page_family_t *page_family_head = NULL;

#endif /* __MYLIB__ */