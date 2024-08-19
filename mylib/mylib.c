#include<stdio.h>
#include<memory.h>
#include<unistd.h> /*for page size*/
#include<sys/mman.h>/*for mmap() function call to allocate memory*/
#include<assert.h>
#include "mylib/mylib.h"

static size_t SYSTEM_PAGE_SIZE = 0; 

void init_system_page_size(){
    SYSTEM_PAGE_SIZE = getpagesize();
}

static void *allocate_system_page(int num_pages){
    char *ptr = mmap(NULL, num_pages*SYSTEM_PAGE_SIZE, PROT_READ|PROT_WRITE, 
                     MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    assert(ptr != MAP_FAILED);
    memset(ptr, 0, num_pages*SYSTEM_PAGE_SIZE);
    return (void *)ptr;
}

static void deallocate_system_page(void *ptr, int num_pages){
    int rc = munmap(ptr, num_pages*SYSTEM_PAGE_SIZE);
    assert(rc == 0);
}

int main(int argc, char **argv){
    init_system_page_size();
    void *addr1 = allocate_system_page(1);
    void *addr2 = allocate_system_page(1);
    printf("addr1 = %p\n addr2=%p\n", addr1,addr2);
    
    return 0;
}