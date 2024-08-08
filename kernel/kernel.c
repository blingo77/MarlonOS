#include "../drivers/screen.h"
#include "../libc/mem.h"
#include "../libc/string.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void main()
{   
    install_isr();    
    install_irq();
    
    clear_screen();
    
    kernel_print("Type something, it will go through the kernel\n"
        "Type END to halt the CPU\n> ");
}

void user_input(char *input)
{
    if(strcmp(input, "END") == 0)
    {
        kernel_print("Stopping CPU. BYE! \n");
        asm volatile("hlt");    // hlt stops the cpu
    }
    else
    {
        kernel_print("\n>You said: ");
        kernel_print(input);
        kernel_print("\n>");
    }
}