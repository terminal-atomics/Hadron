#pragma once
#include <arch/amd64/gdt/gdt.h>
#include <arch/amd64/tasking/tss.h>
#include <arch/amd64/interrupts/interrupts.h>
#include <arch/amd64/vga_basic/vga.h>
#include <arch/amd64/paging/paging.h>
#include <dump.h>
#include <common/multiboot/multiboot.h>
#include <common/memory/mmap.h>
#include <common/memory/palloc.h>
#include <common/memory/liballoc.h>
#include <arch/amd64/tasking/tasking.h>
#include <common/scheduler/scheduler.h>
#include <common/kernel/kernel.h>


void _init();

// Kernel size detection for mmap
extern void _kernel_code_start();
extern void _kernel_code_end();
extern void _stack_bottom();
extern void _stack_top();