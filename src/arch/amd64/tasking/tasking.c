#include <arch/amd64/tasking/tasking.h>

task_t tasking_dummy_task;
task_t* tasking_current_task = NULL;

void tasking_init() {
    tasking_kernel_cr3 = (uint64_t)paging_k_ctx.pml4;
    tasking_current_task = &tasking_dummy_task;
}

void tasking_start() {
    idt_set_entry(0x42, (uint64_t)tasking_ctx_switch, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 3);
    idt_set_entry(INT_IRQ_BASE, (uint64_t)tasking_ctx_switch_int, 1, 0, IDT_FLAG_P | IDT_GATE_TYPE_INT, 3); // tasking_ctx_switch_int
    asm("int $0x42");
}

void tasking_yield() {
    asm("int $0x42");
}

task_t* tasking_prepare_task(uintptr_t entry, uintptr_t stack_ptr, uintptr_t k_stack_ptr, paging_ctx_t* paging_ctx, task_priv_t priv) {
    task_t* state = (task_t*)malloc(sizeof(task_t));
    state->rip = entry;
    state->rsp = stack_ptr;
    state->cr3 = (uint64_t)paging_ctx->pml4;
    state->cs = priv == TASK_PRIV_KERNEL ? 0x08 : 0x1B;
    state->ss = priv == TASK_PRIV_KERNEL ? 0x10 : 0x23;
    state->rflags = (1 << 9); // Interrupts enabled
    state->cpl = priv;
    state->k_rsp = k_stack_ptr;
    return state;
}