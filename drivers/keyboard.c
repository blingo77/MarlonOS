#include "keyboard.h"
#include "port.h"
#include "screen.h"
#include "../cpu/isr.h"
#include "../libc/mem.h"
#include "../libc/string.h"

static void keyboard_callback(regs_t regs)
{
    // Scancode -> data from the keyboard 

    // The PIC puts the scancode in port 0x60

    u8 scancode = port_byte_in(0x60);
    char *sc_ascii;
    int_to_ascii(scancode, sc_ascii);
    kernel_print("Keyboard scancode: ");
    kernel_print(sc_ascii);
    kernel_print(", ");
    print_letter(scancode);
    kernel_print("\n");
}

void init_keyboard()
{
    // sets the keyboard_callback to be the ISR for IRQ1
    register_int_handler(IRQ1, keyboard_callback);
}

void print_letter(u8 scancode){
        switch (scancode) {
        case 0x0:
            kernel_print("ERROR");
            break;
        case 0x1:
            kernel_print("ESC");
            break;
        case 0x2:
            kernel_print("1");
            break;
        case 0x3:
            kernel_print("2");
            break;
        case 0x4:
            kernel_print("3");
            break;
        case 0x5:
            kernel_print("4");
            break;
        case 0x6:
            kernel_print("5");
            break;
        case 0x7:
            kernel_print("6");
            break;
        case 0x8:
            kernel_print("7");
            break;
        case 0x9:
            kernel_print("8");
            break;
        case 0x0A:
            kernel_print("9");
            break;
        case 0x0B:
            kernel_print("0");
            break;
        case 0x0C:
            kernel_print("-");
            break;
        case 0x0D:
            kernel_print("+");
            break;
        case 0x0E:
            kernel_print("Backspace");
            break;
        case 0x0F:
            kernel_print("Tab");
            break;
        case 0x10:
            kernel_print("Q");
            break;
        case 0x11:
            kernel_print("W");
            break;
        case 0x12:
            kernel_print("E");
            break;
        case 0x13:
            kernel_print("R");
            break;
        case 0x14:
            kernel_print("T");
            break;
        case 0x15:
            kernel_print("Y");
            break;
        case 0x16:
            kernel_print("U");
            break;
        case 0x17:
            kernel_print("I");
            break;
        case 0x18:
            kernel_print("O");
            break;
        case 0x19:
            kernel_print("P");
            break;
		case 0x1A:
			kernel_print("[");
			break;
		case 0x1B:
			kernel_print("]");
			break;
		case 0x1C:
			kernel_print("ENTER");
			break;
		case 0x1D:
			kernel_print("LCtrl");
			break;
		case 0x1E:
			kernel_print("A");
			break;
		case 0x1F:
			kernel_print("S");
			break;
        case 0x20:
            kernel_print("D");
            break;
        case 0x21:
            kernel_print("F");
            break;
        case 0x22:
            kernel_print("G");
            break;
        case 0x23:
            kernel_print("H");
            break;
        case 0x24:
            kernel_print("J");
            break;
        case 0x25:
            kernel_print("K");
            break;
        case 0x26:
            kernel_print("L");
            break;
        case 0x27:
            kernel_print(";");
            break;
        case 0x28:
            kernel_print("'");
            break;
        case 0x29:
            kernel_print("`");
            break;
		case 0x2A:
			kernel_print("LShift");
			break;
		case 0x2B:
			kernel_print("\\");
			break;
		case 0x2C:
			kernel_print("Z");
			break;
		case 0x2D:
			kernel_print("X");
			break;
		case 0x2E:
			kernel_print("C");
			break;
		case 0x2F:
			kernel_print("V");
			break;
        case 0x30:
            kernel_print("B");
            break;
        case 0x31:
            kernel_print("N");
            break;
        case 0x32:
            kernel_print("M");
            break;
        case 0x33:
            kernel_print(",");
            break;
        case 0x34:
            kernel_print(".");
            break;
        case 0x35:
            kernel_print("/");
            break;
        case 0x36:
            kernel_print("Rshift");
            break;
        case 0x37:
            kernel_print("Keypad *");
            break;
        case 0x38:
            kernel_print("LAlt");
            break;
        case 0x39:
            kernel_print("Spc");
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (scancode <= 0x7f) {
                kernel_print("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                kernel_print("key up ");
                print_letter(scancode - 0x80);
            } else kernel_print("Unknown key up");
            break;
    }
}