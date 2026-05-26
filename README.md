# Simple POSIX Memory Allocator

## Overview
A foundational dynamic memory allocator written in C++. This project bypasses the standard `<cstdlib>` memory functions (`malloc`/`free`) and interacts directly with the Linux virtual memory system using `mmap`.

It currently implements a basic First-Fit search over a linked list of memory blocks.

## Current Limitations & Future Work
This is currently a base implementation designed to explore POSIX system calls and pointer arithmetic. It has intentional unoptimized edge cases that I plan to address in Phase 2:
* **Internal Fragmentation:** The `allocate` function does not currently split oversized blocks. If a user asks for 16 bytes and a 1024-byte block is found, the whole block is consumed.
* **External Fragmentation:** The `deallocate` function simply toggles a boolean flag. It does not coalesce (merge) adjacent free blocks yet.

## Building and Running
```bash
g++ main.cpp src/allocator.cpp -o allocator
./allocator
