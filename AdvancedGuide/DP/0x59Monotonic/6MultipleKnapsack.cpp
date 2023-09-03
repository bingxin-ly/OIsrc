#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e3 + 5, M = 2e4 + 5;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    static int n, m, v[N], w[N], s[N];
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i] >> s[i];
    static int f[M], q[M];
    for (int i = 1; i <= n; i++)
        for (int u = 0; u < v[i]; u++)
        {
            static auto calc = [&](int i, int u, int k)
            { return f[u + k * v[i]] - k * w[i]; };
            int l = 1, r = 0, p = (m - u) / v[i];
            for (int k = p - 1; k >= max(p - s[i], 0); k--)
            {
                while (l <= r && calc(i, u, q[r]) <= calc(i, u, k))
                    r--;
                q[++r] = k;
            }
            for (; p >= 0; p--)
            {
                while (l <= r && q[l] > p - 1)
                    l++;
                if (l <= r)
                    f[u + p * v[i]] = max(f[u + p * v[i]], calc(i, u, q[l]) + p * w[i]);
                if (p - s[i] - 1 >= 0)
                {
                    while (l <= r && calc(i, u, q[r]) <= calc(i, u, p - s[i] - 1))
                        r--;
                    q[++r] = p - s[i] - 1;
                }
            }
        }
    cout << f[m];
    return 0;
}