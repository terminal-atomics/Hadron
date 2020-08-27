#pragma once
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <dump.h>

//#define MMAP_DEBUG

#define MMAP_MAX_ENTRIES            1024

enum mmap_reg_type {
    MMAP_REG_TYPE_AVAILABLE,
    MMAP_REG_TYPE_HARDWARE,
    MMAP_REG_TYPE_SOFTWARE
};
typedef enum mmap_reg_type mmap_reg_type_t;

struct mmap_block {
    uintptr_t start;
    uintptr_t end;
    mmap_reg_type_t type;
};
typedef struct mmap_block mmap_block_t;

mmap_block_t k_mmap[MMAP_MAX_ENTRIES];
int k_mmap_entry_count;

void mmap_init();
void mmap_define(uintptr_t start, uintptr_t end, mmap_reg_type_t type);
int mmap_get_type(uintptr_t addr);
int mmap_get_id(uintptr_t addr, bool touch);
size_t mmap_get_usable();
size_t mmap_get_software();
size_t mmap_get_hardware();

#ifdef MMAP_DEBUG
void mmap_debug();
#endif