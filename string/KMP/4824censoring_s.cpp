#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 10;
int slen, plen, nxt[MAX];
char s[MAX], p[MAX];
int f[MAX], stk[MAX], top;

int main()
{
    cin >> s + 1 >> p + 1;
    slen = strlen(s + 1), plen = strlen(p + 1);
    for (int i = 2, pos = 0; i <= plen; i++)
    {
        while (pos && p[i] != p[pos + 1])
            pos = nxt[pos];
        if (p[i] == p[pos + 1])
            pos++;
        nxt[i] = pos;
    }
    for (int i = 1, pos = 0; i <= slen; i++)
    {
        while (pos && s[i] != p[pos + 1])
            pos = nxt[pos];
        if (s[i] == p[pos + 1])
            pos++;
        f[i] = pos;
        stk[++top] = i;
        if (pos == plen)
        {
            top -= plen;
            pos = f[stk[top]];
        }
    }
    for (int i = 1; i <= top; i++)
        putchar(s[stk[i]]);
    return 0;
}