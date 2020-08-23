#include <arch/amd64/interrupts/idt.h>

idt_entry_t _k_idt[IDT_ENTRY_COUNT] __attribute__ ((aligned (16)));
idt_desc_t _k_idt_desc __attribute__ ((aligned (16)));

void idt_init() {
    _k_idt_desc.offset = (uint64_t)&_k_idt;
    _k_idt_desc.size = sizeof(_k_idt);

    // Remplace by memset
    for (int i = 0; i < IDT_ENTRY_COUNT; i++) {
        idt_set_entry(i, 0, 0, 0, 0, 0);
    }
}

void idt_set_entry(int id, uint64_t offset, uint16_t segId, uint8_t ist, uint8_t flags, uint8_t dpl) {
    idt_entry_t* entry = &_k_idt[id];
    entry->offset_l = offset & 0xFFFFFFFF;
    entry->offset_hl = (offset >> 16) & 0xFFFF;
    entry->offset_hh = (offset >> 32) & 0xFFFFFFFF;
    entry->ist = ist;
    entry->selector = segId * sizeof(gdt_entry_t);
    entry->flags = (dpl << 5) | flags;
    entry->_rsv0 = 0;
}

idt_entry_t* idt_get_entry(int id) {
    return &_k_idt[id];
}

void idt_load() {
    asm("xchgw %bx, %bx");
    asm("lidt %0" : : "m"(_k_idt_desc));
}