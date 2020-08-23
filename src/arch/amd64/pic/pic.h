#pragma once
#include <arch/amd64/io/io.h>

#define PIC_M_CMD_PORT      0x20
#define PIC_M_DATA_PORT     0x21
#define PIC_S_CMD_PORT      0xA0
#define PIC_S_DATA_PORT     0xA1

void pic_init();