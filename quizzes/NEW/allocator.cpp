#include <iostream>
#include <cstring>
#include <cstdlib>

void* Allocate(size_t size, size_t align)
{
    size_t total_size = size + (align);
    size_t offset = (align - 1);
    void* base_ptr = malloc(total_size);

    size_t user_ptr = ((size_t)base_ptr + (align - 1)) & (~offset);
    

    size_t padding = (size_t)base_ptr - user_ptr;

    *((size_t*)user_ptr - 1) = padding;

    return (void*)user_ptr;
}

void Deallocate(void * mem)
{
    size_t padding = *((size_t*)mem - 1);

    void* original_ptr = static_cast<char*>(mem) - padding;

    free(original_ptr);
}

int main()
{
    void * ptr = (char*)Allocate(33, 3);



    std::cout << (size_t)ptr % 3 << std::endl;



    Deallocate(ptr);



    return 0;
}
