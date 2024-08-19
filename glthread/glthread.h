#ifndef __GLTHREAD__
#define __GLTHREAD__

typedef struct glthread{
    struct glthread *left;
    struct glthread *right;
} glthread;

typedef struct glthread_{
    glthread *head;
    unsigned int offset;
} glthread_;

#define IS_GLTHREAD_LIST_EMPTY(gltptr) \
    (gltptr->right==NULL) && (gltptr->left==NULL)

#define get_glthread_for_struct(function_name,struct_name,field_name,gltptr) \
    static inline struct_name * function_name(glthread *gltptr){ \
        return (struct_name *)((char *)(gltptr) - (char *)&(((struct_name *)0)->field_name)); \
    }   
#define GLTHREAD_USER_DATA_OFFSET(gltptr, offset) \
    (void *)((char *)(gltptr) - offset)

#define GET_GLTHREAD_LIST_COUNT(gltptr) \
    unsigned int count = 0; \
    while(gltptr!=NULL) { \
        count++; \
        gltptr = gltptr->right; \
    } \
    return count;  

void add_before_glthread(glthread *old_ptr, glthread *new_ptr);
void add_after_glthread(glthread *old_ptr, glthread *new_ptr);
void add_last_glthread(glthread *base, glthread *new_ptr);
void remove_glthread(glthread *gltptr);
void initialize_glthread(glthread *gltptr);
void delete_glthread_list(glthread *gltptr);
unsigned int get_glthread_list_count(glthread *gltptr);
void *glthread_get_next(glthread *glthread);    
void glthread_priority_insert(glthread *base, glthread *new_glthread, int (*cmp_fn)(void *, void *), unsigned int offset);


#endif
