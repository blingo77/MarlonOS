void mem_copy(char *source, char *copy, int num_bytes)
{
    /*  HOW mem_copy works:
        Lower Addresses  ----------------------------------------> Higher Addresses
        |   |   |   |   |   |   |   |   |   |   |   |   |   |   | 
        1000 1001 1002 1003 1004 1005 1006 1007 1008 1009 1010 1011 1012 1013 1014 1015

        1. (copy + i) -> (1000 + 1) = (1001)
        2. *(1001) -> '*' grabs the value at the memory address
        3. *(copy + i) = *(source + i) -> We store what ever source was into *copy
    */
    for(int i = 0; i < num_bytes; i++)
    {
        *(copy + i) = *(source + i);        //
    }
}

void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    /* TODO: implement "reverse" */
}