#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e3 + 5, W = 2e5 + 5, MOD = 1e9 + 7;
int power(int a, int b, int p = MOD)
{
    int res = 1 % p;
    for (; b; b >>= 1)
    {
        if (b & 1)
            res = 1ll * res * a % p;
        a = 1ll * a * a % p;
    }
    return res;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    static long long fac[W], inv[W];
    function<int(int, int)> C;
    {
        fac[0] = inv[0] = 1;
        for (int i = 1; i < W; i++)
            fac[i] = fac[i - 1] * i % MOD, inv[i] = power(fac[i], MOD - 2);
        C = [](int n, int m)
        { return fac[n] * inv[m] % MOD * inv[n - m] % MOD; };
    }
    static int H, W, n;
    static struct blc
    {
        int x, y;
    } p[N];
    cin >> H >> W >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y;
    p[n + 1] = {H, W};
    sort(p + 1, p + n + 1, [](blc a, blc b)
         { return a.x < b.x || (a.x == b.x && a.y < b.y); });
    static long long f[N];
    for (int i = 1; i <= n + 1; i++)
    {
        f[i] = C(p[i].x - 1 + p[i].y - 1, p[i].x - 1);
        for (int j = 1; j < i; j++)
            if (p[j].y <= p[i].y)
                (f[i] -= f[j] * C(p[i].x - p[j].x + p[i].y - p[j].y, p[i].x - p[j].x) % MOD) %= MOD;
    }
    cout << (f[n + 1] + MOD) % MOD;
    return 0;
}