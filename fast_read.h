// c/c++ 都可以用，但c++用未免怪怪的
#include <stdio.h>
void read(int *x)
{
    int o = 1, p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            o = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        p = (p << 3) + (p << 1) + c - '0',
        c = getchar();
    *x = (o * p);
}
void write(int x)
{
    if (x < 0)
        putchar('-'),
            x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
