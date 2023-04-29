#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

long long k, p;
ll mul(ll a, ll b)
{
    ll ans = 0;
    while (b)
    {
        if (b & 1)
            ans = (ans + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return ans;
}

unordered_map<ll, ll> mp;
inline ll BSGS(ll y, ll z)
{
    y = ((y % p) + p) % p;
    z = ((z % p) + p) % p;
    ll m = ceil(sqrt(p));
    mp[1] = 0;
    ll n = 1, t = 1;
    for (ll i = 1; i <= m; ++i)
        n = mul(n, y), mp[mul(n, z)] = i;

    for (ll i = 1; i <= m; ++i)
    {
        t = mul(t, n);
        if (mp.count(t))
            return m * i - mp[t];
    }
    return -1;
}

int main()
{
    cin >> k >> p;
    cout << BSGS(10, 9 * k + 1);
    return 0;
}