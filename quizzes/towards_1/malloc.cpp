#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstdlib> 
#include <iostream>

// void* custom(size_t size, size_t alignment) 
// {
//     void* ptr = NULL;
//     void* original_ptr = NULL;

//     size_t total_size = size + alignment - 1;

//     original_ptr = malloc(total_size);

//     ptr = (void*)((uintptr_t)(original_ptr + alignment - 1) & ~(alignment - 1));
    
//     ((void**)ptr)[-1] = original_ptr;

//     return ptr;
// }

// void aligned_free(void* ptr) 
// {
//     if (ptr != NULL) 
//     {
//         void* original_ptr = ((void**)ptr)[-1];
//         free(original_ptr);
//     }
// }

int main() 
{

    int memory = 13;
    int align = 16;
    int shift = memory + align - 1;
    int offset = align - 1 + sizeof(void *);

    // void * ptr = malloc(shift);
    // void * result = (void*)(((size_t)ptr + shift) & (~15lu));

    void* ptr = malloc(shift); 
    void* result_t = (void*)((size_t)ptr + shift);
    void* result = (void*)(((size_t)ptr + shift) & (~0x0F));

    // ((void**)result)[-1] = ptr;


    printf("%p\n", ptr);
    printf("%p\n", result_t);
    printf("%p\n", result);
    std::cout << ((char*)ptr - (char*)result_t) << std::endl;
    std::cout << ((char*)ptr - (char*)result) << std::endl;

    free(ptr);

    
    return 0;
}
