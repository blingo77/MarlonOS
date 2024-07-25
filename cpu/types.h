#ifndef TYPES_H
#define TYPE_H

/*
    int -> 4 bytes -> 32 bits
    short -> 2 bytes -> 16 bits
    char -> 1 byte -> 8 bits
*/

typedef unsigned int    u32;
typedef signed   int    s32;

typedef unsigned short  u16;
typedef signed   short  s16;

typedef unsigned char   u8;
typedef signed   char   s8;

#define low_16(address) (u16)((address) & 0xffff)   // & 0xffff -> masks the upper 16 bits, keeping only the lower 16 bits
#define high_16(address) (u16)(((address) >> 16) & 0xffff)  // shifts bits 16 times to the right, then masks the upper 16 bits. 
                                                            // this gives us the high 16 bits
#endif