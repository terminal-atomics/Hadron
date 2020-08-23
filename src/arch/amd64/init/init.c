#include <arch/amd64/gdt/gdt.h>
#include <arch/amd64/interrupts/interrupts.h>
#include <arch/amd64/vga_basic/vga.h>

void err_handler(isr_state_t* state) {

}

void _init() {
    gdt_init();
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0, GDT_FLAG_CODE | GDT_FLAG_C_P | GDT_FLAG_C_G | GDT_FLAG_C_L);
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0, GDT_FLAG_DATA | GDT_FLAG_D_P | GDT_FLAG_D_G | GDT_FLAG_C_L);
    gdt_load();

    vga_init(80, 25);
    vga_set_color(0x07);
    vga_clear();

    vga_println("Hello Hadron! " __TIME__ " " __DATE__);

    interrupts_init();

    vga_println("Interrupts enabled");
}