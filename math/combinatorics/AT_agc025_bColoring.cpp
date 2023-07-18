#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 3e5 + 5, MOD = 998244353;
int n, fac[N];

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
int C(int n, int m)
{
    if (n < m)
        return 0;
    return fac[n] * power(fac[m], MOD - 2) % MOD * power(fac[n - m], MOD - 2) % MOD;
}
void init()
{
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % MOD;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int a, b, k, ans = 0;
    cin >> n >> a >> b >> k;
    init();
    for (int i = 0; i <= n; i++)
        if (a * i <= k && (k - a * i) % b == 0)
            (ans += C(n, i) * C(n, (k - a * i) / b) % MOD) %= MOD;
    cout << ans;
    return 0;
}