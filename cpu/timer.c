#include "timer.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "isr.h"
#include "../libc/function.h"

u32 tick = 0;

static void timer_callback(regs_t reg)
{
    tick++;
}

void init_timer(u32 freq)
{
    // freq is in Hz

    // install the timer_callback function
    register_int_handler(IRQ0, timer_callback);   // sets timer_callback to be the ISR for IRQ0

    /* Get the PIT value: hardware clock at 1193180 Hz */
    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);

    // PITs control port -> 0x43
    // operate in square wave mode -> 0x36
    port_byte_out(0x43, 0x36); /* Command port */

    // PITs data port -> 0x40
    // we send the low and high to the data port, setting the timers interval
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}