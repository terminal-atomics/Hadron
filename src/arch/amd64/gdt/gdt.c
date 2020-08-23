#include <arch/amd64/gdt/gdt.h>

gdt_entry_t _k_gdt[GDT_ENTRY_COUNT] __attribute__ ((aligned (16)));
gdt_desc_t _k_gdt_desc __attribute__ ((aligned (16)));

void gdt_init() {
    _k_gdt_desc.offset = (uint64_t)&_k_gdt;
    _k_gdt_desc.size = sizeof(_k_gdt);

    // Remplace by memset
    for (int i = 0; i < GDT_ENTRY_COUNT; i++) {
        gdt_set_entry(i, 0, 0, 0, 0);
    }
}

void gdt_set_entry(int id, uint32_t base, uint32_t limit, uint8_t dpl, uint16_t flags) {
    gdt_entry_t* entry = &_k_gdt[id];
    entry->base_l = base & 0xFFFF;
    entry->base_hl = (base >> 16) & 0xFF;
    entry->base_hh = (base >> 24) & 0xFF;
    entry->limit_l = limit & 0xFFFF;
    entry->flags_limit_h = (((limit >> 16) & 0xF) << 8) | ((dpl && 3) << 5) | flags;
}

gdt_entry_t* get_get_entry(int id) {
    return &_k_gdt[id];
}

void gdt_load() {
    asm("lgdt %0" : : "m"(_k_gdt_desc));
    _gdt_reload_segments();
}