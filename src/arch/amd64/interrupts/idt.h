#pragma once
#include <stdint.h>
#include <arch/amd64/gdt/gdt.h>

#define IDT_ENTRY_COUNT 256

#define IDT_GATE_TYPE_LDT       2
#define IDT_GATE_TYPE_TSS_A     9
#define IDT_GATE_TYPE_TSS_B     11
#define IDT_GATE_TYPE_CALL      12
#define IDT_GATE_TYPE_INT       14
#define IDT_GATE_TYPE_TRAP      15
#define IDT_FLAG_Z              (1 << 4)
#define IDT_FLAG_P              (1 << 7)

struct idt_entry {
    uint16_t offset_l;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t offset_hl;
    uint32_t offset_hh;
    uint32_t _rsv0;
}__attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt_desc {
    uint16_t size;
    uint64_t offset;
}__attribute__((packed));
typedef struct idt_desc idt_desc_t;

idt_entry_t k_idt[IDT_ENTRY_COUNT] __attribute__ ((aligned (0x1000)));

void idt_init();
void idt_set_entry(int id, uint64_t offset, uint16_t segId, uint8_t ist, uint8_t flags, uint8_t dpl);
idt_entry_t* idt_get_entry(int id);
void idt_load();