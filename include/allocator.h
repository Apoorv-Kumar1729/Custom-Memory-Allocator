#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>

// Basic metadata header
struct BlockHeader {
    size_t size;
    bool is_free;
    BlockHeader* next;
};

class SimpleAllocator {
private:
    void* heap_start;
    size_t total_size;
    BlockHeader* head;

public:
    SimpleAllocator(size_t size);
    ~SimpleAllocator();

    void* allocate(size_t size);
    void deallocate(void* ptr);
    void print_memory_state(); 
};

#endif
