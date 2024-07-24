#include "../drivers/screen.h"
#include "util.h"

void main()
{   
    clear_screen();
    
    for(int i = 0; i < 24; i++)
    {
        char str[255];
        int_to_ascii(i, str);
        kernel_print_at(str, 0, i);
    }

    kernel_print_at("This text forces the kernel to scroll. Row 0 will disappear. ", 60, 24);
    kernel_print("And with this text, the kernel will scroll again, and row 1 will disappear too!");
}