#include <common/memory/mmap.h>

int k_mmap_entry_count = 0;

void mmap_init() {
    memset(k_mmap, 0xEF, sizeof(mmap_block_t) * MMAP_MAX_ENTRIES);
}

int mmap_get_id(uintptr_t addr, bool touch) {
    if (touch) {
        for (int i = 0; i < k_mmap_entry_count; i++) {
            if ((uintptr_t)addr + 1 >= (uintptr_t)k_mmap[i].start && ((addr - 1 <= k_mmap[i].end) || addr == 0)) { 
                return i;
            }
        }
        return -1;
    }
    for (int i = 0; i < k_mmap_entry_count; i++) {
        if (addr >= k_mmap[i].start && addr <= k_mmap[i].end) {
            return i;
        }
    }
    return -1;
}

void mmap_insert(mmap_block_t block, int id) {
    memcpy(&k_mmap[id + 1], &k_mmap[id], ((MMAP_MAX_ENTRIES - 1) - id) * sizeof(mmap_block_t));
    k_mmap[id] = block;
    k_mmap_entry_count++;
}

int mmap_remove(int start_id, int end_id) {
    int rmcount = (end_id - start_id) + 1;
    memcpy(&k_mmap[start_id], &k_mmap[end_id + 1], ((MMAP_MAX_ENTRIES - 1) - end_id) * sizeof(mmap_block_t));
    k_mmap_entry_count -= rmcount;
    return rmcount;
}

void mmap_merge(int start_id, int end_id) {
    k_mmap[start_id].end = k_mmap[end_id].end;
    mmap_remove(start_id + 1, end_id);
}

void mmap_split(uintptr_t addr) {
    int id = mmap_get_id(addr, false);
    mmap_block_t upper;
    upper.start = addr;
    upper.end = k_mmap[id].end;
    upper.type = k_mmap[id].type;
    k_mmap[id].end = addr - 1;
    mmap_insert(upper, id + 1);
}

int mmap_get_id_above(uintptr_t addr) {
    for (int i = 0; i < k_mmap_entry_count; i++) {
        if (k_mmap[i].start >= addr) {
            return i;
        }
    }
    return k_mmap_entry_count; // return id after last block
}

int mmap_get_id_under(uintptr_t addr) {
    for (int i = k_mmap_entry_count - 1; i >= 0; i--) {
        if (k_mmap[i].end <= addr) {
            return i;
        }
    }
    return 0; // return id after last block
}

void mmap_define(uintptr_t start, uintptr_t end, mmap_reg_type_t type) {
    if (start >= end) { // Uh...
        return;
    }
    int start_id = mmap_get_id(start, true);
    int end_id = mmap_get_id(end, true);
    if (start_id == -1 && end_id == -1) { // No block covers part of the range
        int above_start_id = mmap_get_id_above(start);
        int above_end_id = mmap_get_id_above(end);
        if (above_start_id != above_end_id) { // If a bloc is present inside the range
            mmap_remove(above_start_id, above_end_id - 1);
        }
        mmap_block_t new;
        new.start = start;
        new.end = end;
        new.type = type;
        mmap_insert(new, above_start_id);
        return;
    }
    else if (start_id >= 0 && end_id == -1) { // Lower part of range is covered by a block
        int under_end_id = mmap_get_id_under(end);
        if (under_end_id != start_id) {  // If a bloc is present inside the range
            mmap_remove(start_id + 1, under_end_id);
        }
        if (type == k_mmap[start_id].type) { // If block is of same type, just merge
            k_mmap[start_id].end = end;
            return;
        }
        k_mmap[start_id].end = start - 1;
        mmap_block_t new;
        new.start = start;
        new.end = end;
        new.type = type;
        mmap_insert(new, start_id + 1);
    }
    else if (start_id == -1 && end_id >= 0) { // Upper part of range is covered by a block
        int above_start_id = mmap_get_id_above(start);
        if (above_start_id + 1 != end_id) { // If a bloc is present inside the range
            mmap_remove(above_start_id, end_id - 1);
        }
        if (type == k_mmap[end_id].type) { // If block is of same type, just merge
            k_mmap[end_id].start = start;
            return;
        }
        k_mmap[end_id].start = end + 1;
        mmap_block_t new;
        new.start = start;
        new.end = end;
        new.type = type;
        mmap_insert(new, end_id);
    }
    else {
        if (k_mmap[start_id].type != type) {
            if (start != k_mmap[start_id].start) {
                mmap_split(start);
                start_id++;
                end_id++;
            }
        }
        if (k_mmap[end_id].type != type && end != k_mmap[end_id].end) {
            mmap_split(end + 1);
            k_mmap[end_id].type = type;
        }
        k_mmap[start_id].type = type;
        if (start_id != end_id) {
            mmap_merge(start_id, end_id);
        }
    }
}

int mmap_get_type(uintptr_t addr) {
    for (int i = 0; i < k_mmap_entry_count; i++) {
        if (addr >= k_mmap[i].start && addr <= k_mmap[i].end) {
            return k_mmap[i].type;
        }
    }
    return -1;
}

size_t mmap_get_usable() {
    size_t amount = 0;
    for (int i = 0; i < k_mmap_entry_count; i++) {
        if (k_mmap[i].type == MMAP_REG_TYPE_AVAILABLE) {
            amount += k_mmap[i].end - k_mmap[i].start;
        }
    }
    return amount;
}

size_t mmap_get_software() {
    size_t amount = 0;
    for (int i = 0; i < k_mmap_entry_count; i++) {
        if (k_mmap[i].type == MMAP_REG_TYPE_SOFTWARE) {
            amount += k_mmap[i].end - k_mmap[i].start;
        }
    }
    return amount;
}

size_t mmap_get_hardware() {
    size_t amount = 0;
    for (int i = 0; i < k_mmap_entry_count; i++) {
        if (k_mmap[i].type == MMAP_REG_TYPE_HARDWARE) {
            amount += k_mmap[i].end - k_mmap[i].start;
        }
    }
    return amount;
}


#ifdef MMAP_DEBUG
void mmap_debug() {
    if (k_mmap_entry_count == 0) {
        printf("The memory map is empty.\n");
        return;
    }
    printf("The memory map currently contains %d items:\n", k_mmap_entry_count);
    //         " <0000> 0x00000000 => 0x00000000 : 00 "
        printf("|  ID  |   Start   |     End     | FLags |\n");
    for (int i = 0; i < k_mmap_entry_count; i++) {
        printf(" <%04d> 0x%08X => 0x%08X : %02x\n", i, k_mmap[i].start, k_mmap[i].end, k_mmap[i].flags);
    }
}
#endif