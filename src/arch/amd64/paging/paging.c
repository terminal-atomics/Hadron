#include <arch/amd64/paging/paging.h>

paging_ctx_t paging_k_ctx;

void paging_init(paging_ctx_t* ctx, bool kernel) {
    memset(ctx->pml4, 0, 0x1000);
    memset(ctx->dummy_table, 0, 0x1000);
    ctx->pml4[511] = (uint64_t)&ctx->pml4 | PAGING_FLAG_P | PAGING_FLAG_RW;
    ctx->pml4[510] = (uint64_t)&ctx->dummy_table | PAGING_FLAG_P | PAGING_FLAG_RW;

    // map first entry to the PML4 and last entry to itself
    ctx->dummy_table[0] = (uint64_t)&ctx->pml4 | PAGING_FLAG_P | PAGING_FLAG_RW;
    ctx->dummy_table[511] = (uint64_t)&ctx->dummy_table | PAGING_FLAG_P | PAGING_FLAG_RW;
}

void paging_install(paging_ctx_t* ctx) {
    asm("mov %rax, %cr3" : : "a"(ctx->pml4));
}

void paging_map(paging_ctx_t* ctx, uint64_t virt, uint64_t phy, size_t count, uint16_t flags) {
    uint64_t* pml4;
    uint64_t* pdp;
    uint64_t* pd;
    uint64_t* pt;
    uint64_t* pml4_e;
    uint64_t* pdp_e;
    uint64_t* pd_e;
    uint64_t* pt_e;
    pml4 = &ctx->pml4;
    pml4_e = &pml4[PAGING_PML4_INDX(virt)];

    if (ctx == &paging_k_ctx) {
        pdp = PAGING_PDP_PTR(virt);
        pd = PAGING_PD_PTR(virt);
        pt = PAGING_PT_PTR(virt);

        if (*pml4_e == 0) {
            *pml4_e = (0 /* ALLOCATOR HERE */) | PAGING_FLAG_P | PAGING_FLAG_RW;
            memset(pdp, 0, 0x1000);
        }

        pdp_e = &pdp[PAGING_PDP_INDX(virt)];
        if (*pdp_e == 0) {
            *pdp_e = (0 /* ALLOCATOR HERE */) | PAGING_FLAG_P | PAGING_FLAG_RW;
            memset(pd, 0, 0x1000);

            // Increment the number of pd in pdp
            paging_inc_tbl_ec(pml4_e);
        }

        pd_e = &pd[PAGING_PDP_INDX(virt)];
        if (*pd_e == 0) {
            *pd_e = (0 /* ALLOCATOR HERE */) | PAGING_FLAG_P | PAGING_FLAG_RW;
            memset(pt, 0, 0x1000);

            // Increment the number of pt in pd
            paging_inc_tbl_ec(pdp_e);
        }

        pt_e = &pt[PAGING_PDP_INDX(virt)];
        if (*pt_e == 0) {
            *pt_e = (0 /* ALLOCATOR HERE */) | PAGING_FLAG_P | flags;

            // Increment the number of pages in pt
            paging_inc_tbl_ec(pd_e);
        }
    }
    else {
        if (*pml4_e == 0) {
            uint64_t new_tbl = 0; /* ALLOCATOR HERE */

            // Map table in the kernel's address space
            paging_map(&paging_k_ctx, new_tbl, new_tbl, 1, PAGING_FLAG_RW);
            memset(new_tbl, 0, 0x1000);
            *pml4_e = new_tbl | PAGING_FLAG_P | PAGING_FLAG_RW;
        }

        pdp = *pml4_e & PAGING_ADDR_MASK;
        pdp_e = &pdp[PAGING_PDP_INDX(virt)];
        if (*pdp_e == 0) {
            uint64_t new_tbl = 0; /* ALLOCATOR HERE */

            // Map table in the kernel's address space
            paging_map(&paging_k_ctx, new_tbl, new_tbl, 1, PAGING_FLAG_RW);
            memset(new_tbl, 0, 0x1000);
            *pdp_e = new_tbl | PAGING_FLAG_P | PAGING_FLAG_RW;

            // Increment the number of pd in pdp
            paging_inc_tbl_ec(pml4_e);
        }

        pd = *pdp_e & PAGING_ADDR_MASK;
        pd_e = &pd[PAGING_PD_INDX(virt)];
        if (*pd_e == 0) {
            uint64_t new_tbl = 0; /* ALLOCATOR HERE */

            // Map table in the kernel's address space
            paging_map(&paging_k_ctx, new_tbl, new_tbl, 1, PAGING_FLAG_RW);
            memset(new_tbl, 0, 0x1000);
            *pd_e = new_tbl | PAGING_FLAG_P | PAGING_FLAG_RW;

            // Increment the number of pt in pd
            paging_inc_tbl_ec(pdp_e);
        }

        pt = *pd_e & PAGING_ADDR_MASK;
        pt_e = &pt[PAGING_PD_INDX(virt)];
        if (*pt_e == 0) {
            uint64_t new_tbl = 0; /* ALLOCATOR HERE */

            // Map table in the kernel's address space
            paging_map(&paging_k_ctx, new_tbl, new_tbl, 1, PAGING_FLAG_RW);
            memset(new_tbl, 0, 0x1000);
            *pt_e = new_tbl | PAGING_FLAG_P | flags;

            // Increment the number of pages in pt
            paging_inc_tbl_ec(pd_e);
        }
    }
}

void paging_unmap(paging_ctx_t* ctx, uint64_t virt, uint64_t phy, size_t count) {
    uint64_t* pml4;
    uint64_t* pdp;
    uint64_t* pd;
    uint64_t* pt;
    uint64_t* pml4_e;
    uint64_t* pdp_e;
    uint64_t* pd_e;
    uint64_t* pt_e;
    pml4 = &ctx->pml4;
    pml4_e = &pml4[PAGING_PML4_INDX(virt)];

    if (ctx == &paging_k_ctx) {
        pdp = PAGING_PDP_PTR(virt);
        pd = PAGING_PD_PTR(virt);
        pt = PAGING_PT_PTR(virt);
        pdp_e = &pdp[PAGING_PDP_INDX(virt)];
        pd_e = &pdp[PAGING_PD_INDX(virt)];
        pt_e = &pdp[PAGING_PT_INDX(virt)];
    }
    else {
        pdp = *pml4_e & PAGING_ADDR_MASK;
        pdp_e = &pdp[PAGING_PDP_INDX(virt)];
        pd = *pdp_e & PAGING_ADDR_MASK;
        pd_e = &pd[PAGING_PD_INDX(virt)];
        pt = *pd_e & PAGING_ADDR_MASK;
        pt_e = &pt[PAGING_PD_INDX(virt)];
    }

    // Remove entry from pt and delete if empty
    *pt_e = 0;
    if (paging_dec_tbl_ec(pd_e) == 0) {
        /* DEALLOC(pd_e & PAGING_ADDR_MASK) */
        pd_e = 0;
        if (paging_dec_tbl_ec(pdp_e) == 0) {
            /* DEALLOC(pdp_e & PAGING_ADDR_MASK) */
            pdp_e = 0;
            if (paging_dec_tbl_ec(pml4_e) == 0) {
                /* DEALLOC(pml4_e & PAGING_ADDR_MASK) */
                pml4_e = 0;
            }
        }
    }
}

bool paging_is_mapped(paging_ctx_t* ctx, uint64_t virt, size_t count) {
    
}

int paging_inc_tbl_ec(uint64_t* tbl_e) {
    uint16_t nc = ((*tbl_e >> 52) & 0b111111111) + 1;
    *tbl_e = (*tbl_e & 0xE00FFFFFFFFFFFFF) | (nc << 52);
    return nc;
}

int paging_dec_tbl_ec(uint64_t* tbl_e) {
    uint16_t nc = ((*tbl_e >> 52) & 0b111111111) - 1;
    *tbl_e = (*tbl_e & 0xE00FFFFFFFFFFFFF) | (nc << 52);
    return nc;
}