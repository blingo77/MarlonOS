/* Info for VGA Text Mode */
#define MAX_ROWS 25
#define MAX_COLS 80
#define VID_MEM_ADDRESS 0xb8000
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

/* Screen I/O ports */
#define SCREEN_CONTROL_REGISTER 0x3d4
#define SCREEN_DATA_REGISTER 0x3d5 

void clear_screen();
void kernel_print_at(char *message, int col, int row );
void kernel_print(char *message);