#pragma once
#include <stdint.h>
#include <arch/amd64/vga_basic/vga.h>

char* dump_hex_byte(uint8_t n);
void dump_hex_word(uint64_t n);