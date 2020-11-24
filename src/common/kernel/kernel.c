#include <common/kernel/kernel.h>

mutex_t* mtx;

void test_worker() {
    while (1) {
        mutex_lock(mtx);
        vga_println("thread 1");
        mutex_unlock(mtx);
        scheduler_yield();
    }
}

void test_userspace_worker() {
    while(1) {
        asm("int $0x52");
        asm("int $0x42");
    }
}

void test_syscall() {
    mutex_lock(mtx);
    vga_println("syscall!");
    mutex_unlock(mtx);
}

void kmain(multiboot_info_t* mb_info) {
    (void)mb_info;
    vga_println("Hello 2 :)");

    mtx = mutex_create();

    interrupts_bind_handler(0x52, test_syscall);

    // Get context switching and isr handler code info
    uintptr_t ctx_sw_begin = (uintptr_t)tasking_ctx_switch_begin;
    uintptr_t ctx_sw_end = (uintptr_t)tasking_ctx_switch_end;
    size_t ctx_sw_size = ((ctx_sw_end >> 12) - (ctx_sw_begin >> 12)) + 1;

    uintptr_t isr_begin = (uintptr_t)isr_handlers_begin;
    uintptr_t isr_end = (uintptr_t)isr_handlers_end;
    size_t isr_size = ((isr_end >> 12) - (isr_begin >> 12)) + 1;

    // Allocate a process stack and kernel stack
    uintptr_t user_stack = palloc_alloc(1);
    uintptr_t user_kernel_stack = palloc_alloc(1);

    dump_hex_word(user_stack); vga_println("");
    dump_hex_word(user_kernel_stack); vga_println("");

    // Create paging context
    paging_ctx_t* user_ctx = paging_create_context();

    // Create task state
    task_t* state = tasking_prepare_task((uintptr_t)test_userspace_worker, (uintptr_t)user_stack + 0x1000, (uintptr_t)user_kernel_stack + 0x1000, user_ctx, TASK_PRIV_USER);

    // Map user stack, kernel stack, code, gdt, idt, isrs, tss, task state and ctx switch code in user process
    paging_map(user_ctx, user_stack, user_stack, 1, PAGING_FLAG_RW | PAGING_FLAG_US);
    paging_map(user_ctx, user_kernel_stack, user_kernel_stack, 1, PAGING_FLAG_RW);
    paging_map(user_ctx, (uintptr_t)test_userspace_worker, (uintptr_t)test_userspace_worker, 1, PAGING_FLAG_RW | PAGING_FLAG_US);
    paging_map(user_ctx, ctx_sw_begin, ctx_sw_begin, ctx_sw_size, PAGING_FLAG_RW);
    paging_map(user_ctx, (uintptr_t)state, (uintptr_t)state, 1, PAGING_FLAG_RW); // TODO: Map two if across page boundry
    paging_map(user_ctx, (uintptr_t)&k_gdt, (uintptr_t)&k_gdt, 1, PAGING_FLAG_RW);
    paging_map(user_ctx, (uintptr_t)&k_idt, (uintptr_t)&k_idt, 1, PAGING_FLAG_RW);
    paging_map(user_ctx, (uintptr_t)&k_tss, (uintptr_t)&k_tss, 1, PAGING_FLAG_RW);
    paging_map(user_ctx, (uintptr_t)isr_begin, (uintptr_t)isr_begin, isr_size, PAGING_FLAG_RW);

    // Map user and kernel stack in kernel
    paging_map(&paging_k_ctx, user_stack, user_stack, 1, PAGING_FLAG_RW);
    paging_map(&paging_k_ctx, user_kernel_stack, user_kernel_stack, 1, PAGING_FLAG_RW);


    /*
        ===== TODO =====
        - Remove invlpg for non kernel contexts (it's fucking useless...)
    */

    // Add it to the thread list
    scheduler_create_thread(state);

    while(1) {
        mutex_lock(mtx);
        vga_println("Hello World!");
        mutex_unlock(mtx);
        scheduler_yield();
    }

    while(1);
}