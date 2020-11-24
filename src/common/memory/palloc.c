#include <common/memory/palloc.h>
#include <dump.h>

size_t palloc_get_order(size_t n) {
    n--;
    n |= (n >> 1);
    n |= (n >> 2);
    n |= (n >> 4);
    n |= (n >> 8);
    n |= (n >> 16);
    n |= (n >> 32);
    n++;
    int order;
    for (order = 0; !((n >> order) & 1) && n > 0; order++);
    return order;
}

void palloc_init_region(uintptr_t start, uintptr_t end, bool paging_ready) {
    for (int i = 0; i < k_mmap_entry_count; i++) {
        mmap_block_t* region = &k_mmap[i];
        if (region->type != MMAP_REG_TYPE_AVAILABLE) {
            continue;
        }
        if (region->start < start || region->start > end) {
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

        pregion_desc_t* desc = (pregion_desc_t*)first_addr;

        // Calculate the number of pages needed by the header
        size_t buddy_size = 0;
        for (int i = 0; i < BUDDY_DEPTH; i++) {
            buddy_size += ((page_count / (1 << i)) / 8) + 1;
        }
        size_t header_pages = ((sizeof(pregion_desc_t) + buddy_size) / PAGE_SIZE) + 1;
        size_t available_pages = page_count - header_pages;

        // If paging is ready, the header needs to be mapped
        if (paging_ready) {
            paging_map(&paging_k_ctx, first_addr, first_addr, header_pages, PAGING_FLAG_RW);
        }

        // calculate max order and fill buddy table
        desc->max_order = BUDDY_DEPTH - 1;
        desc->buddy_order_ptr[0] = &desc->buddies[0];
        size_t buddy_ptr = 0;
        for (int i = 0; i < BUDDY_DEPTH; i++) {
            if (available_pages / (1 << i) == 0) {
                desc->max_order = i - 1;
                break;
            }
            desc->buddy_order_ptr[i] = &desc->buddies[buddy_ptr];
            buddy_ptr += ((page_count / (1 << i)) / 8) + 1;
        }

        // Fill in the rest of the info and clear buddies
        desc->page_count = available_pages;
        desc->start_addr = first_addr + (header_pages * PAGE_SIZE);
        memset(desc->buddies, 0, buddy_size);
    }

    // This next segment is only for when paging isn't enabled
    if (paging_ready) {
        return;
    }

    // Allocator should be functional at this point
    // This means we can safely map the header pages
    for (int i = 0; i < k_mmap_entry_count; i++) {
        mmap_block_t* region = &k_mmap[i];
        if (region->type != MMAP_REG_TYPE_AVAILABLE) {
            continue;
        }
        if (region->start < start || region->start > end) {
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

        // Calculate the number of pages needed by the header
        size_t buddy_size = 0;
        for (int i = 0; i < BUDDY_DEPTH; i++) {
            buddy_size += ((page_count / (1 << i)) / 8) + 1;
        }
        size_t header_pages = ((sizeof(pregion_desc_t) + buddy_size) / PAGE_SIZE) + 1;

        paging_premap(&paging_k_ctx, first_addr, first_addr, header_pages, PAGING_FLAG_RW);
    }    
}

uintptr_t palloc_alloc(size_t count) {
    size_t opti_order = palloc_get_order(count);
    if (opti_order >= BUDDY_DEPTH) {
        opti_order = BUDDY_DEPTH - 1;
    }

    // Search through all memory regions
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

        // Check if the region is big enough for the allocation
        pregion_desc_t* desc = (pregion_desc_t*)first_addr;
        if (desc->page_count < count) {
            continue;
        }

        // Calculate maximum buddy order
        size_t order = opti_order > desc->max_order ? desc->max_order : opti_order;
        size_t order_bs = 1 << order;
        size_t buddy_count = (count % order_bs == 0) ? (count / order_bs) : ((count / order_bs) + 1);

        // Search
        uintptr_t offset = palloc_bit_find(desc->buddy_order_ptr[order], buddy_count, desc->page_count / order_bs);
        if (offset == ~(uintptr_t)0) {
            continue;
        }
        uintptr_t page_offset = offset * order_bs;

        // Mark order 0 buddies used
        palloc_bit_fill(desc->buddy_order_ptr[0], page_offset, count);

        // Update higher order buddies
        for (size_t ord = 1; ord < desc->max_order + 1; ord++) {
            size_t block_count = count / (1 << ord);
            uintptr_t block_offset = page_offset / (1 << ord);
            palloc_bit_fill(desc->buddy_order_ptr[ord], block_offset, block_count == 0 ? 1 : block_count);
        }

        return desc->start_addr + (page_offset * PAGE_SIZE);
    }

    return ~(uintptr_t)0;
}

void palloc_free(uintptr_t ptr, size_t count) {
    (void)ptr;
    (void)count;
    vga_println("<========== UH OH, FREE NOT IMPLEMENTED!!!!! ==========>");
}

void palloc_bit_fill(uint8_t* ptr, uintptr_t offset, size_t count) {   
    uintptr_t end = offset + count;
    for (uintptr_t i = offset; i < end; i++) {
        ptr[i / 8] |= 1 << (i % 8);
    }
}

void palloc_bit_clear(uint8_t* ptr, uintptr_t offset, size_t count) {
    uintptr_t end = offset + count;
    for (uintptr_t i = offset; i < end; i++) {
        ptr[i / 8] &= ~(1 << (i % 8));
    }
}

uintptr_t palloc_bit_find(uint8_t* ptr, size_t count, size_t max) {
    size_t continuous = 0;
    for (uintptr_t i = 0; i < max; i++) {
        
        if (ptr[i / 8] & (1 << (i % 8))) {
            continuous = 0;
        }
        else {
            continuous++;
        }
        if (continuous == count) {
            return i - (count - 1);
        }
    }
    return ~(uintptr_t)0;
}