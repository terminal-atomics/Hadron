#include <arch/amd64/tasking/scheduler.h>

task_t* scheduler_current_task;
uintptr_t scheduler_kernel_cr3;

void scheduler_start(uintptr_t first, task_state_t state, task_priv_t priv) {
    scheduler_current_task = (task_t*)malloc(sizeof(task_t));
    scheduler_current_task->state = state;
    scheduler_current_task->priv = priv;
    scheduler_current_task->next = scheduler_current_task;
    scheduler_current_task->previous = scheduler_current_task;

    scheduler_current_task->state.cr3 = &paging_k_ctx.pml4;
    scheduler_current_task->state.cs = 0x08;
    scheduler_current_task->state.ss = 0x10;
    scheduler_current_task->state.rflags = (1 << 9); // Interrupts enabled ofc
    scheduler_current_task->state.rsp = _stack_top; // Keep same stack

    scheduler_kernel_cr3 = &paging_k_ctx.pml4;

    idt_set_entry(0x42, scheduler_yield_handler, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_TRAP, 3);
    
    scheduler_yield();
}

task_t* scheduler_create_task(uintptr_t entry, task_state_t state, task_priv_t priv) {
    
}

void scheduler_remove_task(task_t* task) {

}

void scheduler_yield() {
    asm("xchgw %bx, %bx");
    asm("int $0x42");
}