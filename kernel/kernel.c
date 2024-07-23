#include "../drivers/screen.h"

void main()
{   
    clear_screen();
    kernel_print_at("X", 1, 6);
    kernel_print_at("This text spans multiple lines", 75, 10);
    kernel_print_at("There is a line\nbreak", 0, 20);
    kernel_print("There is a line\nbreak");
    kernel_print_at("What happens when we run out of space?", 45, 24);
}