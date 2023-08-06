#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 5, MOD = 19930726;
int n, R[N], d[N];
char s[N];
long long k;

int power(int a, int b, int p = MOD)
{
    int res = 1;
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
    cin >> n >> k >> (s + 1), s[0] = '!', s[n + 1] = '@';
    for (int i = 1, c = 0, r = 0; i <= n; i++)
    {
        R[i] = i <= r ? min(R[2 * c - i], r - i + 1) : 1;
        while (s[i - R[i]] == s[i + R[i]])
            R[i] += 1;
        d[2 * R[i] - 1] += 1;
        if (r < i + R[i] - 1)
            r = i + R[i] - 1, c = i;
    }
    for (int i = n - 1; i; i--)
        d[i] += d[i + 1];

    long long ans = 1;
    for (int i = n; i && k; i--)
    {
        if (!(i & 1))
            continue;
        int dec = d[i] < k ? d[i] : k;
        (ans *= power(i, dec)) %= MOD, k -= dec;
    }
    cout << ans;
    return 0;
}