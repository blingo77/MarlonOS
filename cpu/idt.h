#ifndef IDT_H
#define IDT_H

#include "types.h"

#define KERNEL_CODE_SEGEMNT 0x08    // 0x08 is where the code segement of kernel is ran in the GDT

// How every interrupt gate table is defined
typedef struct  
{
    // The interrupt gate should be exactly 8 bytes

    u16 low_offset;     // the low bits of the handler function address
    u16 selector;       // the kernel segment selector
    u8 always0;         // will always be 0
    u8 flags;
    /*
    Bit  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    -------|---|---|---|---|---|---|---|---|
    Name  | P | DPL  | 0 |  Type   |
    -------|---|---|---|---|---|
    Value | 1 | 0   | 0 |  1 1 1 0 |

    Bit 7 (Present): Indicates if the gate is valid (1) or not (0).
    Bits 6-5 (DPL – Descriptor Privilege Level): Specifies the privilege level required to trigger this interrupt (0 = highest privilege(kernel), 3 = lowest(user)).
    Bit 4 (Storage Segment): 0 for interrupt and trap gates, 1 for other types of gates.
    Bits 3-0 (Gate Type): Indicates the type of gate (14 = 32-bit interrupt gate)
    */

   u16 high_offset; // the high bits of tje handler function address

}__attribute__((packed)) idt_gate_t;  // needs to be exactly 8 bytes so we pack it, so theres no padding

// A pointer to the array of interrupt handlers
// ASM instruction 'lidt will read it
typedef struct idt_register_t
{
    u16 limit;      //represents the size of the IDT in bytes
    u32 base;       // represents the starting memory address of the IDT
}__attribute__((packed)) idt_register_t ;

#define IDT_ENTRIES 256         // max number of entries that the IDT can hold
idt_gate_t idt[IDT_ENTRIES];    // an array of idt_date_t, which holds 256 gate structures
idt_register_t idt_reg;    // stores base address and limit of he idt, which will be loaded into the processors idtr register

void set_idt_gate(int n, u32 handler);
void set_idt();

#endif