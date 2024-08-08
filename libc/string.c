
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}


int strLen(char s[])
{
    int i = 0;
    while(s[i] != '\0')
    {
        i++;
    }
    return i;
}

void reverse(char s[])
{
    int c, j;

    // sets up two pointers and swaps them stopping half way through the string
    for(int i = 0, j = strLen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void backspace(char s[])
{
    int len = strLen(s);
    s[len - 1] = '\0';
}

void append(char s[], char n)
{
    int len = strLen(s);
    s[len] = n;             // adds the character specified in n and adds it to the back of the string
    s[len + 1] = '\0';      // adds '\0' to the end of the string
}

int strcmp(char s1[], char s2[])
{
    int i = 0;
    for(i = 0; s1[i] == s2[i]; i++)
    {
        if(s1[i] == '\0')
        {
            // return 0 if both strings are equal
            return 0;
        }
    }
    // returns a negaive if s1 is lexicographically less than s2
    // returns a positive if s1 is lexicographically greater than s2
    return s1[i] - s2[i];

}