#include <common/memory/palloc.h>
#include <dump.h>

size_t palloc_get_order(size_t n) {
    n--;
    n = n | (n >> 1) | (n >> 2) | (n >> 4) | (n >> 8) | (n >> 16) | (n >> 32);
    n++;
    int order;
    for (order = 0; !((n >> order) & 1); order++);
    return order;
}

void palloc_init() {
    for (int i = 0; i < k_mmap_entry_count; i++) {
        mmap_block_t* region = &k_mmap[i];
        if (region->type != MMAP_REG_TYPE_AVAILABLE) {
            continue;
        }
        uintptr_t first_addr = (region->start % PAGE_SIZE) == 0 ? 
            region->start : ((region->start / PAGE_SIZE) + 1) * PAGE_SIZE;
        
        uintptr_t last_addr = (((region->end / PAGE_SIZE) + 1) * PAGE_SIZE) - 1;
        size_t size = (last_addr - first_addr) + 1;
        size_t page_count = size / PAGE_SIZE;

        // Check if the region is at least two pages long
        if (page_count < 2) {
            continue;
        }

        size_t buddy_size = 0;
        for (int i = 0; i < BUDDY_DEPTH; i++) {
            buddy_size += page_count / (1 << i);
        }
        buddy_size = (buddy_size / 8) + 1;
        size_t header_pages = (sizeof(pregion_desc_t) + buddy_size) / PAGE_SIZE;

        pregion_desc_t* desc = (pregion_desc_t*)first_addr;
        desc->page_count = page_count;
        desc->start_addr = first_addr + (header_pages * PAGE_SIZE);

        memset(desc->buddies, 0, buddy_size);        
    }
}

uintptr_t palloc_alloc(size_t count) {
    return 0; // PLACEHOLDER
}

void palloc_free(uintptr_t ptr, size_t count) {

}
