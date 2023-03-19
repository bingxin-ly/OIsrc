#include <cstdio>
int read()
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
        p = p * 10 + c - '0',
        c = getchar();
    return o * p;
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
