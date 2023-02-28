#include <bits/stdc++.h>
using namespace std;

const int MAX = 5 * 1e5 + 10;
char s[MAX];
int n, nxt[MAX], f[MAX], ton[MAX];

int main()
{
    cin >> s + 1;
    n = strlen(s + 1);
    nxt[0] = -1;
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j != -1 && s[i] != s[j + 1])
            j = nxt[j];
        nxt[i] = ++j;
    }
    f[1] = 1;
    ton[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        f[i] = i;
        if (ton[f[nxt[i]]] >= i - nxt[i])
            f[i] = f[nxt[i]];
        ton[f[i]] = i;
    }
    cout << f[n];
    return 0;
}