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
    vga_set_color(0x04);
    vga_print("\n\nPANIC: ");
    vga_print(exception_messages[state->int_no]);
    vga_print(" (");
    dump_hex_word(state->err_code);
    vga_println(")");

    // Dump registers
    vga_print("CR0: ");
    dump_hex_word(state->cr0);
    vga_print("    CR2:    ");
    dump_hex_word(state->cr2);

    vga_print("\nCR3: ");
    dump_hex_word(state->cr2);
    vga_print("    CR4:    ");
    dump_hex_word(state->cr4);

    vga_print("\nRAX: ");
    dump_hex_word(state->rax);
    vga_print("    RBX:    ");
    dump_hex_word(state->rbx);

    vga_print("\nRCX: ");
    dump_hex_word(state->rcx);
    vga_print("    RDX:    ");
    dump_hex_word(state->rdx);

    vga_print("\nRBP: ");
    dump_hex_word(state->rbp);
    vga_print("    RDI:    ");
    dump_hex_word(state->rdi);

    vga_print("\nRSI: ");
    dump_hex_word(state->rsi);
    vga_print("    R8:     ");
    dump_hex_word(state->r8);

    vga_print("\nR9:  ");
    dump_hex_word(state->r9);
    vga_print("    R10:    ");
    dump_hex_word(state->r10);

    vga_print("\nR11: ");
    dump_hex_word(state->r11);
    vga_print("    R12:    ");
    dump_hex_word(state->r12);

    vga_print("\nR13: ");
    dump_hex_word(state->r13);
    vga_print("    R14:    ");
    dump_hex_word(state->r14);

    vga_print("\nR15: ");
    dump_hex_word(state->r15);
    vga_print("    RSP:    ");
    dump_hex_word(state->rsp);

    vga_print("\nRIP: ");
    dump_hex_word(state->rip);
    vga_print("    RFLAGS: ");
    dump_hex_word(state->rflags);

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

void syscall_handler(isr_state_t* state) {
    (void)state;
    vga_println("Syscall!");
}

void test_func() {
    while(1);
}

void _init(uint32_t mb_magic, multiboot_info_t* mb_info) {
    vga_init(80, 25);
    vga_set_color(0x07);
    vga_clear();

    if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        (void)mb_info;
        vga_println("Wrong bootload magic:");
        dump_hex_word(mb_magic);
        while (1);
    }

    vga_println("Hello Hadron! " __TIME__ " " __DATE__);

    // Setup GDT
    gdt_init();
    gdt_set_entry(1, 0, 0, 0, GDT_FLAG_CODE); // Kernel code
    gdt_set_entry(2, 0, 0, 0, GDT_FLAG_DATA); // Kernel data
    gdt_set_entry(3, 0, 0, 3, GDT_FLAG_CODE); // Userspace code
    gdt_set_entry(4, 0, 0, 3, GDT_FLAG_DATA); // Userspace data

    // Setup TSS
    tss_load(5);

    // Load GDT
    gdt_load();

    // Install TSS
    tss_install(5);

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

    // Mark kernel in mmap
    mmap_define((uintptr_t)_kernel_code_start, (uintptr_t)_kernel_code_end, MMAP_REG_TYPE_SOFTWARE);

    // Mark mutliboot info in mmap
    mmap_define((uintptr_t)mb_info, (uintptr_t)mb_info + sizeof(multiboot_info_t) - 1, MMAP_REG_TYPE_SOFTWARE);
    mmap_define(mb_info->mmap_addr, mb_info->mmap_length - 1, MMAP_REG_TYPE_SOFTWARE);

    vga_print("Total usable: ");
    dump_hex_word(mmap_get_usable());
    vga_println("");

    // Display MMAP
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
 
    // Initialize the paging system
    paging_init(&paging_k_ctx);

    // Init temporarily mapped regions
    palloc_init_region(0, 0x3FFFFFFF, false);

    // Premap all software regions
    for (int i = 0; i < k_mmap_entry_count; i++) {
        if (k_mmap[i].type != MMAP_REG_TYPE_SOFTWARE) {
            continue;
        }
        uintptr_t start_page = k_mmap[i].start / 0x1000;
        uintptr_t end_page = k_mmap[i].end / 0x1000;
        paging_premap(&paging_k_ctx, k_mmap[i].start, k_mmap[i].start, end_page - start_page + 1, PAGING_FLAG_RW);
    }

    // Map VGA VRAM
    paging_premap(&paging_k_ctx, 0xB8000, 0xB8000, 1, PAGING_FLAG_RW);

    // Enable new paging (yikes...)
    paging_install(&paging_k_ctx);

    // // Init the rest of the memory regions
    palloc_init_region(0x40000000, 0xFFFFFFFFFFFFFFFF, true);

    // Init tasking and scheduler
    tasking_init();
    scheduler_init();

    task_t* state = tasking_prepare_task((uintptr_t)kmain, (uintptr_t)_stack_top, (uintptr_t)_stack_top, &paging_k_ctx, TASK_PRIV_KERNEL);
    scheduler_create_thread(state);

    tasking_start();

    while(1);
}