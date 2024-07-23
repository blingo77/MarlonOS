#include "port.h"
#include "screen.h"

/* Function Declarations */
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

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