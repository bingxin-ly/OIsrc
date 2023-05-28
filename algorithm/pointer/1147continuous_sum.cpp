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
    while (j < m)
    {
        if (sum < m)
            sum += ++j;
        else
        {
            if (sum == m)
                printf("%d %d\n", i, j);
            sum -= i++;
            assert(i <= j); // 因为这道题给定数列就是1 ~ m，过于简单，所以不会有这种情况
            if (i > j) // 防止 i 超过 j，在数列中的某一个数就有可能超过 m 的情况下
                sum = i, j++; // 我们就把 i, j 重置到这个位置即可
        }
    }
    return 0;
}