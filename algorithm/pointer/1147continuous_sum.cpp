#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

signed main()
{
    int m(read()), sum, i, j;
    sum = i = j = 1;
    while (i < m)
    {
        if (sum < m)
            sum += ++j;
        else if (sum >= m)
        {
            if (sum == m)
                printf("%d %d\n", i, j);
            sum -= i++;
        }
    }
    return 0;
}