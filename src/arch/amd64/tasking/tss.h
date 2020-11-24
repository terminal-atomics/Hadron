#pragma once
#include <stdint.h>
#include <string.h>

struct tss {
    uint32_t _rsv0;
    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t _rsv1;
    uint64_t ist1;
    uint64_t ist2;
    uint64_t ist3;
    uint64_t ist4;
    uint64_t ist5;
    uint64_t ist6;
    uint64_t ist7;
    uint64_t _rsv2;
    uint16_t _rsv3;
    uint16_t iopb_offset;
}__attribute__((packed));
typedef struct tss tss_t;

tss_t k_tss __attribute__ ((aligned (0x1000)));

void tss_load(size_t desc);
void tss_install(size_t desc);