# 🧠 Custom Memory Allocator in C

This project implements a custom dynamic memory allocator in C using a fixed-size memory pool. It mimics standard functions like `malloc`, `calloc`, and `free`, while showcasing block management, memory reuse, and fragmentation control.

---

## 📁 Files

- `malloc.c` – Custom allocator implementation using a static memory pool
- `sample.c` – Demo program to test allocations, deallocations, and block status

---

## 🚀 How It Works

🧱 1. Memory Pool init_memory_pool()
🧩 2. Memory Block Structure  Block()
✂️ 3. Block Splitting split_block()
🧵 4. Allocation my_malloc()
🧽 5. Zero-Init Allocation my_calloc()
🗑️ 6. Freeing Memory my_free()
🧬 7. Merging Blocks merge_blocks()
🔍 8. Debugging with memory_status()

### 📦 Memory Model

- Allocator manages a 1 MB static memory pool (`char memory_pool[1048576]`)
- Memory is handled in blocks defined by the `Block` struct:
  ```c
  typedef struct Block {
      size_t size;
      int free;
      struct Block *next;
  } Block;
Each block includes:

size: Usable size
free: 1 if available, 0 if used
next: Pointer to the next block

🔧 Core Functions

Function	Description
my_malloc()	Allocates a block of memory
my_calloc()	Allocates and zeroes memory
my_free()	Frees a block and merges if possible
memory_status()	Prints current block state
split_block()	Splits large free blocks
merge_blocks()	Merges adjacent free blocks


🛠️ How to Compile & Run

gcc sample.c -o memalloc
./memalloc


📌 Sample Output

Allocating 100 bytes...
[SPLIT] Block at 0x... split:
--> Allocated block: size = 100
--> New free block at 0x...: size = ...
Block 1 | Addr: 0x... | Size: 100 | USED
Block 2 | Addr: 0x... | Size: ... | FREE
...
You’ll see:

Live updates of memory status

Block allocations and deallocations

Splitting and merging in action

🧪 Demo Flow

Allocates multiple blocks
Frees some and reallocates
Tests zero-initialized memory using my_calloc
Displays memory state after each operation
