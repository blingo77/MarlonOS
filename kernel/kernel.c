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
    
    asm volatile("sti");
    
    init_timer(50);

    init_keyboard();
}