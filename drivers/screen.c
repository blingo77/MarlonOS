#include "port.h"
#include "screen.h"

/* Function Declarations */
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);
void set_cursor_offset(int offset);
int get_cursor_offset();
int print_char(char c, int col, int row, char attribute);

int print_char(char c, int col, int row, char attribute)
{
    unsigned char *video_mem = (unsigned char*) VID_MEM_ADDRESS;
    if(!attribute) attribute = WHITE_ON_BLACK;

    // FOR ERROR CHECKING
    if (col >= MAX_COLS || row >= MAX_ROWS)
    {
        video_mem[2 * (MAX_COLS) * (MAX_ROWS) - 2] = 'E';           // sets the character byte to an E
        video_mem[2 * (MAX_COLS) * (MAX_ROWS) - 1] = RED_ON_WHITE;  // sets the attribute byte to red font and white foreground
    }

    int offset;
    if(col >= 0 && row >=0)
    { 
        offset = get_offset(col, row);
    }
    else { offset = get_cursor_offset(); }

    if(c == '\n')                           // if the character is a new line 
    {
        row = get_offset_row(offset);       // gets the row currently at
        offset = get_offset(0, row + 1);    // adds 1 to go the next row and goes to column 0, setting offset to the new
    }
    else
    {
        video_mem[offset] = c;              // Sets the character byte to the character
        video_mem[offset + 1] = attribute;  // Sets the attribute byte to the attribute declared ealier
        offset += 2;                        // adds two, to move to next character cell position
    }

    set_cursor_offset(offset);              // updates the cursor position after a character is printed

    return offset;
}

int get_cursor_offset()
{
    port_byte_out(SCREEN_CONTROL_REGISTER, 14);                     // Requesting the high byte
    int cursor_offset = port_byte_in(SCREEN_DATA_REGISTER) << 8;    // retrieve the high byte and shift it left in the offset

    port_byte_out(SCREEN_CONTROL_REGISTER, 15);                     // request the low byte
    cursor_offset += port_byte_in(SCREEN_DATA_REGISTER);            // add the low byte into the cursor offset

    return cursor_offset * 2;   // multiplies the position by the size of the character cell
}

void clear_screen()
{
    int screen_size = MAX_COLS * MAX_ROWS;
    char *screen = VID_MEM_ADDRESS;

    for(int i = 0; i < screen_size; i++)
    {
        screen[i * 2] = ' ';                // Sets the character byte to a blank 
        screen[i * 2 + 1] = WHITE_ON_BLACK; // Sets the attribute byte to white font and black foreground
    }
}

void set_cursor_offset(int offset)
{
    /* positions the text cursor on a VGA display*/

    offset /= 2;        // get the character cell position instead of byte offset

    port_byte_out(SCREEN_CONTROL_REGISTER, 14);                          // requesting to modify the high byte 
    port_byte_out(SCREEN_DATA_REGISTER, (unsigned char)(offset >> 8));   // Modifys the highbyte
    port_byte_out(SCREEN_CONTROL_REGISTER, 15);                          // requests the low byte
    port_byte_out(SCREEN_DATA_REGISTER, (unsigned char)(offset & 0xff)); // modifys the low byte
}

int get_offset(int col, int row)
{

    /* 
     calculates the memory offset(address) for a given position
     at the specified column and row.
    */

    return 2 * (row * MAX_COLS + col);      // multiplied by 2 because of the character cell being 2 bytes  
}

int get_offset_row(int offset)
{
    /* 
     calcualtes the row number from a given offset.
    */

    return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset)
{
    /* 
     calcualtes the column number from a given offset.
    */

    return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}

/*
GET OFFSET FORMULA EXAMPLES -> ROW = 10, COL = 6:

get_offset(6,10):
    offset = 2 * (10 * 80 + 6)
    offset = 2 * (800 + 6)
    offset = 2 * 806
    offset = 1612

get_offset_row(1612):
    row = 1612 / (2 * 80)
    row = 1612 / 160
    row = 10

get_offset_col(1612):
    col = (1612 - (get_offset_row(offset) -> 10 * 2 * 80)) / 2      // THE ROW IS 10
    col = (1612 - 1600) / 2
    col = 12 / 2
    col = 6
*/