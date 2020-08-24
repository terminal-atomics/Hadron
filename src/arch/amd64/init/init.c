#include <arch/amd64/init/init.h>

char *exception_messages[] ={
    "Division By Zero",
    "Debug <test>",
    "Non Maskable Interrupt",
    "Break Point",
    "Into Detect Overflow",
    "Out of bounds Exception",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS Exception",
    "Segment not present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignement Check Exception",
    "Machine Check Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void err_handler(isr_state_t* state) {
    vga_print("Error: ");
    vga_println(exception_messages[state->int_no]);

    while (1) {
        asm("nop");
    }
}

void kbd(isr_state_t* state) {
    vga_println("KEY!");
    inb(0x60);
    pic_ack_master();
}

void _init() {
    gdt_init();
    gdt_set_entry(1, 0, 0, 0, GDT_FLAG_CODE);
    gdt_set_entry(2, 0, 0, 0, GDT_FLAG_DATA);
    gdt_load();

    vga_init(80, 25);
    vga_set_color(0x07);
    vga_clear();

    vga_println("Hello Hadron! " __TIME__ " " __DATE__);

    // TODO: Finish the PIT
    interrupts_init();

    for (int i = 0; i < 32; i++) {
        interrupts_bind_handler(i, err_handler);
    }

    interrupts_bind_handler(33, kbd);

    interrupts_enable();

    vga_println("Interrupts enabled");

    while(1);
}