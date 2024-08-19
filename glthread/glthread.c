#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include "glthread.h"

void initialize_glthread(glthread *gltptr)
{
    gltptr->left = NULL;
    gltptr->right = NULL;
}


void add_after_glthread(glthread *curr_glthread, glthread *new_glthread)
{
    glthread *temp = curr_glthread->right;
    curr_glthread->right = new_glthread;
    new_glthread->left = curr_glthread;
    new_glthread->right = temp;
    if(temp)
        temp->left = new_glthread;
}

void add_before_glthread(glthread *curr_glthread, glthread *new_glthread)
{
    glthread *temp = curr_glthread->left;
    curr_glthread->left = new_glthread;
    new_glthread->right = curr_glthread;
    new_glthread->left = temp;
    if(temp)
        temp->right = new_glthread;
}

void remove_glthread(glthread *curr_glthread)
{
    if(curr_glthread->left)
        curr_glthread->left->right = curr_glthread->right;
    if(curr_glthread->right)
        curr_glthread->right->left = curr_glthread->left;
    curr_glthread->left = NULL;
    curr_glthread->right = NULL;
    free(curr_glthread);
}

void delete_glthread_list(glthread *gltptr)
{
    glthread *temp = gltptr;
    while(temp)
    {
        glthread *temp1 = temp->right;
        free(temp);
        temp = temp1;
    }
}
void *glthread_get_next(glthread *glthread)
{
    return (void *)glthread->right;
}   

unsigned int get_glthread_list_count(glthread *gltptr)
{
     GET_GLTHREAD_LIST_COUNT(gltptr);
}

void add_last_glthread(glthread *gltptr, glthread *new_ptr)
{
    glthread *temp = gltptr;
    while(temp->right)
        temp = temp->right;
    temp->right = new_ptr;
    new_ptr->left = temp;
}

void glthread_priority_insert(glthread *base, glthread *new_glthread, int (*cmp_fn)(void *, void *), unsigned int offset)
{
    glthread *curr = base;
    while(curr->right)
    {
        void *curr_struct = (char *)curr->right - offset;
        if(cmp_fn(curr_struct, (char *)new_glthread - offset) == 1)
            break;
        curr = curr->right;
    }
    add_after_glthread(curr, new_glthread);
}

