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

struct stack_frame {
    struct stack_frame* previous_frame;
    uint64_t rip;
};
typedef struct stack_frame stack_frame_t;

void err_handler(isr_state_t* state) {
    vga_print("\n\nError: ");
    vga_println(exception_messages[state->int_no]);

    vga_println("\nStack trace:");

    // Trace back error on call stack
    vga_print("-> ");
    dump_hex_word(state->rip);
    vga_println("");
    stack_frame_t* frame = (stack_frame_t*)state->rbp;
    for (;frame != 0; frame = frame->previous_frame) {
        vga_print("-> ");
        dump_hex_word(frame->rip);
        vga_println("");
    }

    while (1) {
        asm("nop");
    }
}

void kbd(isr_state_t* state) {
    (void)state;
    vga_println("KEY!");
    inb(0x60);
}

void bruh() {
    int* test = (int*)0x10000000;
    *test = 420;
}

void _init(uint32_t mb_magic, multiboot_info_t* mb_info) {
    vga_init(80, 25);
    vga_set_color(0x07);
    vga_clear();

    if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        (void)mb_info;
        vga_println("Wrong bootload magic :/");
        while (1);
    }

    vga_println("Hello Hadron! " __TIME__ " " __DATE__);

    gdt_init();
    gdt_set_entry(1, 0, 0, 0, GDT_FLAG_CODE);
    gdt_set_entry(2, 0, 0, 0, GDT_FLAG_DATA);
    gdt_load();

    // TODO: Finish the PIT
    interrupts_init();

    for (int i = 0; i < 32; i++) {
        interrupts_bind_handler(i, err_handler);
    }
    interrupts_bind_handler(33, kbd);

    interrupts_enable();

    mmap_init();
    
    // Define memory map from grub data
    int entry_count = mb_info->mmap_length / sizeof(mmap_ent_t);
    mmap_ent_t* entries = (mmap_ent_t*)(uintptr_t)mb_info->mmap_addr;
    for (int i = 0; i < entry_count; i++) {
        uintptr_t start = (uintptr_t)entries[i].addr_low | ((uintptr_t)entries[i].addr_high << 32);
        uintptr_t end = start + ((uintptr_t)entries[i].len_low | ((uintptr_t)entries[i].len_high << 32)) - 1;
        if (entries[i].type == 1) { // If entry indicated free ram, mark as such
            mmap_define(start, end, MMAP_REG_TYPE_AVAILABLE);
        }
        else {
            mmap_define(start, end, MMAP_REG_TYPE_HARDWARE);
        }
    }

    mmap_define(&_kernel_code_start, & _kernel_code_end, MMAP_REG_TYPE_SOFTWARE);

    vga_print("Total usable: ");
    dump_hex_word(mmap_get_usable());
    vga_println("");

    for (int i = 0; i < k_mmap_entry_count; i++) {
        switch (k_mmap[i].type) {
            case MMAP_REG_TYPE_AVAILABLE:
                vga_print("AVAIL: ");
                break;
            case MMAP_REG_TYPE_HARDWARE:
                vga_print("HARDW: ");
                break;
            case MMAP_REG_TYPE_SOFTWARE:
                vga_print("SOFTW: ");
                break;
        }
        
        dump_hex_word(k_mmap[i].start);
        vga_print(" -> ");
        dump_hex_word(k_mmap[i].end);
        vga_println("");
    }

    //paging_init(&paging_k_ctx);

    //palloc_init();

    while(1);
}