#ifndef ISR_H
#define ISR_H

#include "types.h"

/* 
    ISRs that are reserved for CPU exceptions
    The first 32 or reserved by Intel

    There are extern because they will be used in Assembly
*/

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

typedef struct 
{
    u32 ds;                                 // data segment selector
    u32 edi, esi, ebp, esp, ebx, ecx, eax;  // All gets pushed by pusha in ASM
    u32 int_num, error_code;                //Interrupt number and error code
    u32 eip, cs, eflags, useresp, ss;       // pushed by the processor automatically
}registers_t;

void install_isr();
void isr_handler(registers_t r);

#endif