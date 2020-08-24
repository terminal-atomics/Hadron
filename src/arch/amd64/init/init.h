#pragma once
#include <arch/amd64/gdt/gdt.h>
#include <arch/amd64/interrupts/interrupts.h>
#include <arch/amd64/vga_basic/vga.h>

start_task(isr_state_t* state);