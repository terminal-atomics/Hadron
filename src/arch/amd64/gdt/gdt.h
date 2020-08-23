#pragma once
#include <stdint.h>

#define GDT_ENTRY_COUNT 64

#define GDT_FLAG_CODE   (3 << 3)
#define GDT_FLAG_C_A    (1 << 0)
#define GDT_FLAG_C_R    (1 << 1)
#define GDT_FLAG_C_C    (1 << 2)
#define GDT_FLAG_C_P    (1 << 7)
#define GDT_FLAG_C_AVL  (1 << 12)
#define GDT_FLAG_C_L    (1 << 13)
#define GDT_FLAG_C_D    (1 << 14)
#define GDT_FLAG_C_G    (1 << 15)

#define GDT_FLAG_DATA   (2 << 3)
#define GDT_FLAG_D_A    (1 << 0)
#define GDT_FLAG_D_W    (1 << 1)
#define GDT_FLAG_D_E    (1 << 2)
#define GDT_FLAG_D_P    (1 << 7)
#define GDT_FLAG_D_AVL  (1 << 12)
#define GDT_FLAG_D_D    (1 << 14)
#define GDT_FLAG_D_G    (1 << 15)

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