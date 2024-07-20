
// Reads data from port adress
unsigned char port_byte_in(unsigned short port)
{
    unsigned char result;

    /* the inline assembly works backwrds from ASM
     ASM would look like: mov al, dx
     port is stored in dx register and moved into the AL register
     AL is then stored into the result variable
     register DX is reserved for holding port addresses
    */
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));  

    return result;  
}

// writes data to port address
void port_byte_out(unsigned short port, unsigned char data)
{
    /*
    Register AL holds 'data' and register DX holds 'port' 
    */
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port)); // register AL is sent to the I/O port address which is stored in DX
}

unsigned short port_word_in(unsigned short port)
{
    unsigned short result;

    __asm__("in %%dx, %%ax"  : "=a" (result) : "d" (port));
    return result;
}

void port_word_out(unsigned short port, unsigned short data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}