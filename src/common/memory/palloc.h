#pragma once
#include <stdint.h>
#include <common/memory/mmap.h>
#include <arch/amd64/paging/paging.h>

#define PAGE_SIZE       0x1000
#define BUDDY_DEPTH     8       // 4kb -> 512kb

struct pregion_desc {
    uintptr_t start_addr;
    size_t page_count;
    size_t max_order;
    uint8_t* buddy_order_ptr[BUDDY_DEPTH];
    uint8_t buddies[];
};
typedef struct pregion_desc pregion_desc_t;

void palloc_init_region(uintptr_t start, uintptr_t end, bool paging_ready);
uintptr_t palloc_alloc(size_t count);
void palloc_free(uintptr_t ptr, size_t count);

size_t palloc_get_order(size_t n);
void palloc_bit_fill(uint8_t* ptr, uintptr_t offset, size_t count);
void palloc_bit_clear(uint8_t* ptr, uintptr_t offset, size_t count);
uintptr_t palloc_bit_find(uint8_t* ptr, size_t count, size_t max);