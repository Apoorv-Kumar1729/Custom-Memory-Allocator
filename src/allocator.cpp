#include "../include/allocator.h"
#include <sys/mman.h>
#include <iostream>

// Align memory to 8 bytes for CPU safety
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
#define HEADER_SIZE ALIGN(sizeof(BlockHeader))

SimpleAllocator::SimpleAllocator(size_t size) {
    total_size = ALIGN(size);
    
    // Request memory from Linux
    heap_start = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    if (heap_start == MAP_FAILED) {
        std::cerr << "mmap failed!" << std::endl;
        exit(1);
    }

    // Initialize the first giant free block
    head = (BlockHeader*)heap_start;
    head->size = total_size - HEADER_SIZE;
    head->is_free = true;
    head->next = nullptr;
}

SimpleAllocator::~SimpleAllocator() {
    munmap(heap_start, total_size);
}

void* SimpleAllocator::allocate(size_t size) {
    if (size == 0) return nullptr;
    
    size_t aligned_size = ALIGN(size);
    BlockHeader* curr = head;
    
    // Simple First-Fit search
    while (curr != nullptr) {
        if (curr->is_free && curr->size >= aligned_size) {
            // Found a block! Mark it as used.
            // (Intentional flaw: We don't split the block, causing internal fragmentation)
            curr->is_free = false;
            
            // Return the memory address just after the header
            return (char*)curr + HEADER_SIZE; 
        }
        curr = curr->next;
    }
    
    return nullptr; // Out of memory
}

void SimpleAllocator::deallocate(void* ptr) {
    if (!ptr) return;
    
    // Step backward in memory to find the header
    BlockHeader* block = (BlockHeader*)((char*)ptr - HEADER_SIZE);
    
    // Mark it as free 
    // (Intentional flaw: We don't merge adjacent free blocks, causing external fragmentation)
    block->is_free = true; 
}

void SimpleAllocator::print_memory_state() {
    BlockHeader* curr = head;
    std::cout << "--- Memory List ---" << std::endl;
    while (curr != nullptr) {
        std::cout << "Block Size: " << curr->size 
                  << " | Free: " << (curr->is_free ? "Yes" : "No") << std::endl;
        curr = curr->next;
    }
}
