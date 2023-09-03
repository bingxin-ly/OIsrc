#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 5;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    static long long n, S, T[N], C[N];
    cin >> n >> S;
    for (int i = 1; i <= n; i++)
        cin >> T[i] >> C[i], T[i] += T[i - 1], C[i] += C[i - 1];
    static long long f[N];
    memset(f, 0x3f, sizeof(f)), f[0] = 0;
    static int q[N];
    int t = 1; // q[1] = 0
    auto binsearch = [&](int i, int k)
    {
        if (t == 1)
            return q[1];
        int L = 1, R = t;
        while (L < R)
        {
            int m = (L + R) >> 1;
            if (f[q[m + 1]] - f[q[m]] <= k * (C[q[m + 1]] - C[q[m]]))
                L = m + 1;
            else
                R = m;
        }
        return q[L];
    };
    for (int i = 1; i <= n; i++)
    {
        int p = binsearch(i, S + T[i]);
        f[i] = f[p] - (S + T[i]) * C[p] + T[i] * C[i] + S * C[n];
        while (1 < t && (__int128)(f[q[t]] - f[q[t - 1]]) * (C[i] - C[q[t]]) >= (__int128)(f[i] - f[q[t]]) * (C[q[t]] - C[q[t - 1]]))
            t--;
        q[++t] = i;
    }
    cout << f[n];
    return 0;
}