#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
char s[N], p[N];
int n, m, nxt[N];

int main()
{
    cin >> (s + 1) >> (p + 1);
    n = strlen(s + 1), m = strlen(p + 1);

    // 求nxt数组
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j && p[i] != p[j + 1])
            j = nxt[j];
        if (p[i] == p[j + 1])
            j++;
        nxt[i] = j;
    }

    // kmp匹配过程
    for (int i = 1, j = 0; i <= n; i++)
    {
        while (j && s[i] != p[j + 1])
            j = nxt[j];
        if (s[i] == p[j + 1])
            j++;
        if (j == m)
        {
            cout << i - m + 1 << endl;
            j = nxt[j];
        }
    }

    for (int i = 1; i <= m; i++)
        cout << nxt[i] << ' ';
    return 0;
}