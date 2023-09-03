#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e3 + 5;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    static int n, S, T[N], C[N];
    cin >> n >> S;
    for (int i = 1; i <= n; i++)
        cin >> T[i] >> C[i], T[i] += T[i - 1], C[i] += C[i - 1];
    static long long f[N];
    memset(f, 0x3f, sizeof(f)), f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            f[i] = min(f[i], f[j] + 1ll * T[i] * (C[i] - C[j]) + 1ll * S * (C[n] - C[j]));
    cout << f[n];
    return 0;
}