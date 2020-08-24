#pragma once
#include <stdint.h>

#define GDT_ENTRY_COUNT 64

// Most flags and fields are ignores
#define GDT_FLAG_CODE   0b0010000010011000
#define GDT_FLAG_DATA   0b0010000010010010

struct gdt_entry {
    uint16_t limit_l;
    uint16_t base_l;
    uint8_t base_hl;
    uint16_t flags_limit_h;
    uint8_t base_hh;
}__attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

struct gdt_desc {
    uint16_t size;
    uint64_t offset;
}__attribute__((packed));
typedef struct gdt_desc gdt_desc_t;

void gdt_init();
void gdt_set_entry(int id, uint32_t base, uint32_t limit, uint8_t dpl, uint16_t flags);
gdt_entry_t* get_get_entry(int id);
void gdt_load();

extern void _gdt_reload_segments();