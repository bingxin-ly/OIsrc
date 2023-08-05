#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 5;
int n, m, nxt[N];
char s[N], p[N];
signed main()
{
    scanf("%s%s", s + 1, p + 1), n = strlen(s + 1), m = strlen(p + 1);
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j && p[j + 1] != p[i])
            j = nxt[j];
        j += p[j + 1] == p[i];
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++)
    {
        while (j && p[j + 1] != s[i])
            j = nxt[j];
        j += p[j + 1] == s[i];
        if (j == m)
            printf("%d\n", i - m + 1), j = nxt[j];
    }
    for (int i = 1; i <= m; i++)
        printf("%d ", nxt[i]);
    return 0;
}