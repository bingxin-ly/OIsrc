#include <bits/stdc++.h>
using namespace std;

const int N = 2.5e5 + 5, K = 505;
struct p
{
    int x, y;
    int m, p, r;
} s[N], q[N];
bool vis[N];
int L[K], R[K], M[K];
inline long long squ(int $) { return 1ll * $ * $; }
inline long long dis(const p &$) { return squ($.x - q[0].x) + squ($.y - q[0].y); }

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> q[0].x >> q[0].y >> q[0].p >> q[0].r >> n;

    for (int i = 1; i <= n; i++)
        cin >> s[i].x >> s[i].y >> s[i].m >> s[i].p >> s[i].r;
    sort(s + 1, s + n + 1, [](p &x, p &y)
         { return x.m < y.m; });

    int len = sqrt(n), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++)
        L[i] = (i - 1) * len + 1, R[i] = i * len;
    R[num] = n;
    for (int i = 1; i <= num; i++)
        M[i] = s[R[i]].m,
        sort(s + L[i], s + R[i] + 1, [](p &x, p &y)
             { return dis(x) < dis(y); });

    int l = 0, r = 0;
    while (l <= r)
    {
        int k = 0;
        for (int i = 1; i <= num && M[i] <= q[l].p; i++)
            k = i;
        for (int i = 1; i <= k; i++)
            while (L[i] <= R[i] && dis(s[L[i]]) <= squ(q[l].r))
            {
                if (!vis[L[i]])
                    vis[L[i]] = true, q[++r] = s[L[i]];
                L[i] += 1;
            }
        if (num != k++)
            for (int i = L[k]; i <= R[k]; i++)
                if (!vis[i] && s[i].m <= q[l].p && dis(s[i]) <= squ(q[l].r))
                    vis[i] = true, q[++r] = s[i];
        l += 1;
    }
    cout << r;
    return 0;
}