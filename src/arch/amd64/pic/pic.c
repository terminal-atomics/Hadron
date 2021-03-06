#include <arch/amd64/pic/pic.h>

void pic_init() {
    // TODO: Do commands correctly...
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void pic_ack_master() {
    outb(PIC_M_CMD_PORT,0x20);
}

void pic_ack_slave() {
    outb(PIC_M_CMD_PORT,0x20);
    outb(PIC_S_CMD_PORT,0x20);
}