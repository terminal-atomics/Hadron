#pragma once
#include <common/multiboot/multiboot.h>
#include <arch/amd64/vga_basic/vga.h>
#include <arch/amd64/tasking/tss.h>
#include <common/std/mutex.h>

void kmain(multiboot_info_t* mb_info);