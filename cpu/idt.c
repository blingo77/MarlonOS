#include "idt.h"
#include "../kernel/util.h"

void set_idt_gate(int n, u32 handler)
{
    idt[n].low_offset = low_16(handler);
    idt[n].selector = KERNEL_CODE_SEGEMNT;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;                    // 0x8E -> 10001110, look at idt.h to see what each bit does
    idt[n].high_offset = high_16(handler);
}

void set_idt()
{
    idt_register.base = (u32) &idt;     // sets the base to the memory address of the idt array
    idt_register.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_register)); 

    /*
        lidtl loads the register into idtr with the value at the memory address in %0
        &idt_register will be placed in a register indicated by "r",
        then %0 will be replaced by that register
    */
}