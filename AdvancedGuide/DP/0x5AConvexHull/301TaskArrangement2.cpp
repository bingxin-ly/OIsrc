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
    int l = 1, r = 1; // q[1] = 0
    for (int i = 1; i <= n; i++)
    {
        while (l < r && f[q[l + 1]] - f[q[l]] <= (S + T[i]) * (C[q[l + 1]] - C[q[l]]))
            l++;
        f[i] = f[q[l]] - (S + T[i]) * C[q[l]] + T[i] * C[i] + S * C[n];
        while (l < r && (f[q[r]] - f[q[r - 1]]) * (C[i] - C[q[r]]) >= (f[i] - f[q[r]]) * (C[q[r]] - C[q[r - 1]]))
            r--;
        q[++r] = i;
    }
    cout << f[n];
    return 0;
}