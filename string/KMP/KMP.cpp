#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10, M = 1e6 + 10;

int slen, plen, nxt[M];
char s[N], p[M];

int main()
{
    // s[]是长文本，p[]是模式串
    cin >> (s + 1) >> (p + 1);
    slen = strlen(s + 1), plen = strlen(p + 1);

    // 求nxt数组
    for (int i = 2, pos = 0; i <= plen; i++)
    {
        while (pos && p[i] != p[pos + 1])
            pos = nxt[pos];
        if (p[i] == p[pos + 1])
            pos++;
        nxt[i] = pos;
    }

    // kmp匹配过程
    for (int i = 1, pos = 0; i <= slen; i++)
    {
        while (pos && s[i] != p[pos + 1])
            pos = nxt[pos];
        if (s[i] == p[pos + 1])
            pos++;
        if (pos == plen)
        {
            printf("%d\n", i - pos + 1);
            pos = nxt[pos];
        }
    }
    for (int i = 1; i <= plen; i++)
        cout << nxt[i] << ' ';
    return 0;
}