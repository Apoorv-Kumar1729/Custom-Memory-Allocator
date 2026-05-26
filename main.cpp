#include "include/allocator.h"
#include <iostream>

int main() {
    std::cout << "Creating 1024 byte memory pool...\n";
    SimpleAllocator alloc(1024);
    
    std::cout << "\nAllocating 100 bytes...\n";
    void* ptr1 = alloc.allocate(100);
    alloc.print_memory_state();
    
    std::cout << "\nFreeing 100 bytes...\n";
    alloc.deallocate(ptr1);
    alloc.print_memory_state();
    
    return 0;
}
