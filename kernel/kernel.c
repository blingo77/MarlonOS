#include "../drivers/port.h"

/*
    For explantion reasons assume cursor position is row = 12, col = 5
*/
void main()
{   
    // Retrieve the cursor position from VGA control register(0x3d4) for row and col bytes

    port_byte_out(0x3d4, 14);   // 14 requests high byte which is the row
    // the data is returned into the VGA data register (0x3d5)

    // We get the highbyte now by getting it from the VGA Data register (0x3d5)
    int pos = port_byte_in(0x3d5);  // pos = 0x000c
    pos = pos << 8;                 // bits shifted left, pos = 0x0c00

    
    port_byte_out(0x3d4, 15);  // 15 requests low byte which is the column
    // the data is returned into the VGA data register (0x3d5)

    // get low byte now by adding it to our pos variable
    pos += port_byte_in(0x3d5);     //bits added, 0x0c00 + 0x0c05 = 0xc05

    int offset_from_vga = pos * 2;  // offset of 2 because each character cell in VGA text mode
                                    // occupies 2 bytes of memory

    char *vga = 0xb8000;    // VGA text mode memory address

    vga[offset_from_vga] = 'E';
    vga[offset_from_vga + 1] = 0xCA; //the byte is split into two, the C is the background color, A is the font color


}