#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, z[N], nxt[N], cnt[N];
char s[N];
signed main()
{
    scanf("%s", s + 1), n = strlen(s + 1);
    z[1] = n;
    for (int i = 2, l = 0, r = 0; i <= n; i++)
    {
        z[i] = i <= r ? min(z[i - l + 1], r - i + 1) : 0;
        while (s[1 + z[i]] == s[i + z[i]])
            z[i] += 1;
        if (r < i + z[i] - 1)
            r = i + z[i] - 1, l = i;
        cnt[z[i]] += 1;
    }
    for (int i = n - 1; i; i--)
        cnt[i] += cnt[i + 1];
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j && s[j + 1] != s[i])
            j = nxt[j];
        nxt[i] = j += s[j + 1] == s[i];
    }
    stack<int> prt;
    for (int i = n; i; i = nxt[i])
        prt.emplace(i);
    printf("%d\n", (int)prt.size());
    while (!prt.empty())
        printf("%d %d\n", prt.top(), cnt[prt.top()] + 1), prt.pop();
    return 0;
}