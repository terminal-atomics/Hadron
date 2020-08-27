#pragma once
#include <stdint.h>
#include <common/memory/mmap.h>

#define PAGE_SIZE       0x1000
#define BUDDY_DEPTH     8       // 4kb -> 512kb

struct pregion_desc {
    uintptr_t start_addr;
    size_t page_count;
    uint8_t buddies[];
};
typedef struct pregion_desc pregion_desc_t;

void palloc_init();
uintptr_t palloc_alloc(size_t count);
void palloc_free(uintptr_t ptr, size_t count);