#pragma once

#define INT8_MIN        (-128)
#define INT16_MIN       (-32767-1)
#define INT32_MIN       (-2147483647-1)
#define INT64_MIN       (-__INT64_C(9223372036854775807)-1)

#define INT8_MAX        (127)
#define INT16_MAX       (32767)
#define INT32_MAX       (2147483647)
#define INT64_MAX       (__INT64_C(9223372036854775807))

#define UINT8_MAX       (255)
#define UINT16_MAX      (65535)
#define UINT32_MAX      (4294967295U)
#define UINT64_MAX      (__UINT64_C(18446744073709551615))

#define NULL            0

#define BLOCK_COUNT(e_cnt, b_sz)    (((e_cnt) / (b_sz)) + ((e_cnt) % (b_sz) > 0 ? 1 : 0))

typedef signed char             int8_t;
typedef short int               int16_t;
typedef int                     int32_t;
typedef long int                int64_t;

typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long int  uint64_t;

#ifdef __x86_64__
typedef uint64_t                uintptr_t;
typedef uint64_t                size_t;
#else
typedef uint32_t                uintptr_t;
typedef uint32_t                size_t;
#endif

// Endianess
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define BE_UINT16(n) (n)
#define BE_UINT32(n) (n)
#define LE_UINT16(n) ((((n) >> 8) & 0xFF) | (((n) & 0xFF) << 8))
#define LE_UINT32(n) ((((n) >> 24) & 0xFF) | (((n) >> 16) & 0xFF) << 8) | (((n) >> 8) & 0xFF) << 16) | (((n) & 0xFF) << 24))
#else
#define LE_UINT16(n) (n)
#define LE_UINT32(n) (n)
#define BE_UINT16(n) ((((n) >> 8) & 0xFF) | (((n) & 0xFF) << 8))
#define BE_UINT32(n) ((((n) >> 24) & 0xFF) | (((n) >> 16) & 0xFF) << 8) | (((n) >> 8) & 0xFF) << 16) | (((n) & 0xFF) << 24))
#endif