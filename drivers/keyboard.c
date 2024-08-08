#include "keyboard.h"
#include "port.h"
#include "screen.h"
#include "../cpu/isr.h"
#include "../libc/mem.h"
#include "../libc/string.h"
#include "../kernel/kernel.h"

#define ENTER 0x1c
#define BACKSPACE 0x0E
#define SCANCODE_MAX 57

static char key_buffer[256];

const char *sc_name[] = {
        "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
        "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"
};

const char sc_ascii[] = {
        '?', '?', '1', '2', '3', '4', '5', '6',     
        '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '
};

static void keyboard_callback(regs_t regs)
{
    // Scancode -> data from the keyboard 

    // The PIC puts the scancode in port 0x60

    u8 scancode = port_byte_in(0x60);
 
    if(scancode > SCANCODE_MAX)
    {
        return;
    }

    if(scancode == BACKSPACE)
    {
        backspace(key_buffer);
        kernelPrint_backspace();
    }
    else if(scancode == ENTER)
    {
        kernel_print('\n');
        user_input(key_buffer);
        key_buffer[0] = '\0';
    }
    else
    {
        char letter = sc_ascii[(int) scancode];
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kernel_print(str);
    }
}

void init_keyboard()
{
    // sets the keyboard_callback to be the ISR for IRQ1
    register_int_handler(IRQ1, keyboard_callback);
}

