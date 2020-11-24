#include <arch/amd64/tasking/tss.h>
#include <arch/amd64/gdt/gdt.h>

void tss_load(size_t desc) {
    memset(&k_tss, 0, sizeof(tss_t));
    k_tss.iopb_offset = sizeof(tss_t);
    gdt_set_sys_entry(desc, (uint64_t)&k_tss, sizeof(tss_t), 0, GDT_SYS_SEG_TYPE_TSS_A);
}

void tss_install(size_t desc) {
    asm("ltr %%ax" : : "a"(desc * 8));
}