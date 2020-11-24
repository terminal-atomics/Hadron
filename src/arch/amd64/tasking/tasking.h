#pragma once
#include <stdint.h>
#include <common/memory/liballoc.h>
#include <arch/amd64/interrupts/interrupts.h>
#include <arch/amd64/interrupts/idt.h>
#include <arch/amd64/paging/paging.h>

enum task_priv {
    TASK_PRIV_KERNEL,
    TASK_PRIV_USER,
    _TASK_PRIV_COUNT
};
typedef enum task_priv task_priv_t;

struct task {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rbp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
    uint64_t cr3;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
    uint64_t k_rsp;
    uint8_t cpl;
}__attribute__((packed));
typedef struct task task_t;

extern task_t* tasking_current_task;

void tasking_init();
void tasking_start();
void tasking_yield();
task_t* tasking_prepare_task(uintptr_t entry, uintptr_t stack_ptr, uintptr_t k_stack_ptr, paging_ctx_t* paging_ctx, task_priv_t priv);

extern void tasking_ctx_switch();
extern void tasking_ctx_switch_int();
extern uintptr_t tasking_kernel_cr3;

extern void tasking_ctx_switch_begin();
extern void tasking_ctx_switch_end();

extern void tasking_dummy_isr_test();