#include <bits/stdc++.h>
using namespace std;
#define N 500005
int n;
int nxt[N];
int f[N], h[N];
char s[N];
signed main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    nxt[0] = -1;
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j != -1 && s[i] != s[j + 1])
            j = nxt[j];
        nxt[i] = ++j;
    }
    f[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        f[i] = i;
        if (h[f[nxt[i]]] >= i - nxt[i])
            f[i] = f[nxt[i]];
        h[f[i]] = i;
    }
    cout << f[n];
    return 0;
}