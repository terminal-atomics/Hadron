#include <dump.h>

char rtn[3];

char* dump_hex_byte(uint8_t n) {
	char _HEX_ALPHABET_[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	rtn[2] = 0;
    rtn[1] = _HEX_ALPHABET_[(n >> 0) & 0x0F];
    rtn[0] = _HEX_ALPHABET_[(n >> 4) & 0x0F];
    return rtn;
}

void dump_hex_word(uint64_t n) {
	vga_print(dump_hex_byte((n >> 52) & 0xFF));
    vga_print(dump_hex_byte((n >> 48) & 0xFF));
	vga_print(dump_hex_byte((n >> 40) & 0xFF));
    vga_print(dump_hex_byte((n >> 32) & 0xFF));
	vga_print(dump_hex_byte((n >> 24) & 0xFF));
    vga_print(dump_hex_byte((n >> 16) & 0xFF));
    vga_print(dump_hex_byte((n >> 8) & 0xFF));
    vga_print(dump_hex_byte((n >> 0) & 0xFF));
}