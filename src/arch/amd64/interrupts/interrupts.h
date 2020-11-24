#pragma once
#include <arch/amd64/interrupts/idt.h>
#include <arch/amd64/interrupts/isr.h>
#include <arch/amd64/pic/pic.h>
#include <stdbool.h>

#define INT_IRQ_BASE    32

struct isr_state {
    uint64_t cr4;
    uint64_t cr3;
    uint64_t cr2;
    uint64_t cr0;
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
    uint64_t int_no;
    uint64_t err_code;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
}__attribute__((packed));
typedef struct isr_state isr_state_t;

void interrupts_init();
bool interrupts_is_bound(int id);
void interrupts_bind_handler(int id, void (*handler)(isr_state_t*));
void interrupts_unbind_handler(int id);
void interrupts_enable();
void interrupts_disable();
void _c_dummy_isr(isr_state_t* state);

extern void isr_handlers_begin();
extern void isr_handlers_end();