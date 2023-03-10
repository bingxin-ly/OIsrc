#include <cstdio>
#include <cstring>

int i, j, v;
bool a[10];
int main()
{
    for (i = 192; i <= 327; i++, memset(a, 0, sizeof(a)))
    {
        v = 0;
        a[i % 10] = a[i / 10 % 10] = a[i / 100] =
            a[i * 2 % 10] = a[i * 2 / 10 % 10] = a[i * 2 / 100] =
                a[i * 3 % 10] = a[i * 3 / 10 % 10] = a[i * 3 / 100] = 1;
        for (j = 1; j <= 9; j++)
            v += a[j];
        if (v == 9)
            printf("%d %d %d\n", i, i * 2, i * 3);
    }
    return 0;
}
