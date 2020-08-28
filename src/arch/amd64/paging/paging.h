#pragma once
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <common/memory/palloc.h>

#define PAGING_ADDR_MASK        0xFFFFFFFFFF000
#define PAGING_PML4_INDX(i)     (((i) >> 39) & 0b111111111)
#define PAGING_PDP_INDX(i)      (((i) >> 30) & 0b111111111)
#define PAGING_PD_INDX(i)       (((i) >> 21) & 0b111111111)
#define PAGING_PT_INDX(i)       (((i) >> 12) & 0b111111111)
#define PAGING_PAGE_INDX(i)     ((i) & 0b111111111111)

#define PAGING_STRUCT_PT_MASK   0xFF8000000000
#define PAGING_STRUCT_PD_MASK   0xFF0000000000
#define PAGING_STRUCT_PDP_MASK  0xFF7FC0000000

#define PAGING_PT_PTR(ptr)      ((((ptr) >> 9) & ~0b111) | 0xFF8000000000)
#define PAGING_PD_PTR(ptr)      ((((ptr) >> 18) & ~0b111) | 0xFF0000000000)
#define PAGING_PDP_PTR(ptr)     ((((ptr) >> 27) & ~0b111) | 0xFF7FC0000000)

#define PAGING_FLAG_P           (1 << 0)
#define PAGING_FLAG_RW          (1 << 1)
#define PAGING_FLAG_US          (1 << 2)
#define PAGING_FLAG_PWT         (1 << 3)
#define PAGING_FLAG_PCD         (1 << 4)
#define PAGING_FLAG_A           (1 << 5)
#define PAGING_FLAG_D           (1 << 6)
#define PAGING_FLAG_PAT         (1 << 7)
#define PAGING_FLAG_G           (1 << 8)

struct paging_ctx {
    uint64_t pml4[512]__attribute__((aligned(0x1000)));
    uint64_t dummy_table[512]__attribute__((aligned(0x1000)));
    bool kernel;
};
typedef struct paging_ctx paging_ctx_t;

extern paging_ctx_t paging_k_ctx;

void paging_init(paging_ctx_t* ctx);
void paging_install(paging_ctx_t* ctx);
void paging_map(paging_ctx_t* ctx, uint64_t virt, uint64_t phy, size_t count, uint16_t flags);
void paging_unmap(paging_ctx_t* ctx, uint64_t virt, uint64_t phy, size_t count);
bool paging_is_mapped(paging_ctx_t* ctx, uint64_t virt, size_t count);
void paging_premap(paging_ctx_t* ctx, uint64_t virt, uint64_t phy, size_t count, uint16_t flags);

// DO NOT USE OUTSIDE OF THE PAGING IMPLEMENTATION
int paging_inc_tbl_ec(uint64_t* tbl_e);
int paging_dec_tbl_ec(uint64_t* tbl_e);
void paging_refresh(uint64_t ptr);