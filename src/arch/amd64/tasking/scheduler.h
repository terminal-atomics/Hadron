#pragma once
#include <stdint.h>
#include <common/memory/liballoc.h>
#include <arch/amd64/interrupts/interrupts.h>
#include <arch/amd64/interrupts/idt.h>
#include <arch/amd64/paging/paging.h>
#include <arch/amd64/init/init.h>

enum task_priv {
    TASK_PRIV_SUPERVISOR,
    TASK_RRIV_USER,
};
typedef enum task_priv task_priv_t;

struct task_state {
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
}__attribute__((packed));
typedef struct task_state task_state_t;

struct task {
    struct task* next;
    struct task* previous;
    task_state_t state;
    task_priv_t priv;
}__attribute__((packed));
typedef struct task task_t;



void scheduler_start();
task_t* scheduler_create_task(uintptr_t entry, task_state_t state, task_priv_t priv);
void scheduler_remove_task(task_t* task);
void scheduler_yield();

extern void scheduler_yield_handler();