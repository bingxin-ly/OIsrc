#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 5;
char s[N];
int n, sa[N], rk[N], bc[N], id[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> (s + 1), n = strlen(s + 1);
    int m = 1 << 7;
    for (int i = 1; i <= n; i++)
        rk[i] = s[i], bc[rk[i]] += 1;
    for (int i = 1; i <= m; i++)
        bc[i] += bc[i - 1];
    for (int i = n; i >= 1; i--)
        sa[bc[rk[i]]--] = i;
    for (int w = 1, p = 0;; m = p, p = 0, w <<= 1)
    {
        for (int i = n - w + 1; i <= n; i++)
            id[++p] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w)
                id[++p] = sa[i] - w;
        memset(bc, 0, (m + 1) * sizeof(int));
        vector<int> cpy(rk, rk + n + 1);
        p = 0;
        for (int i = 1; i <= n; i++)
            bc[rk[i]] += 1;
        for (int i = 1; i <= m; i++)
            bc[i] += bc[i - 1];
        for (int i = n; i >= 1; i--)
            sa[bc[rk[id[i]]]--] = id[i];
        for (int i = 1; i <= n; i++)
            rk[sa[i]] =
                p += cpy[sa[i - 1]] != cpy[sa[i]] ||
                     cpy[sa[i - 1] + w] != cpy[sa[i] + w];
        if (p == n)
            break;
    }
    for (int i = 1; i <= n; i++)
        cout << sa[i] << ' ';
    return 0;
}