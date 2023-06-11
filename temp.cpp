#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7, N = 1e5 + 10;
int n, m, k;
int x[N], y[N], s[N];
int pow(int a, int b)
{
    if (b == -1)
        return 0;
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = 1ll * res * a % mod;
        b >>= 1;
        a = 1ll * a * a % mod;
    }
    return res;
}
map<int, int> mp;
int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m >> k;
    if (k == 0)
        return cout << (pow(2, n) + pow(2, m) - 2) % mod, 0;
    char ch;
    for (int i = 1; i <= k; i++)
        cin >> ch >> x[i] >> y[i], s[i] = (ch == '+');
    int v = n;
    for (int i = 1; i <= k; i++)
        if (!mp.count(x[i]))
            mp[x[i]] = (y[i] ^ s[i]) & 1, v--;
        else if (mp[x[i]] != ((y[i] ^ s[i]) & 1))
        {
            v = -1;
            break;
        }
    int ans = pow(2, v);
    v = m;
    mp.clear();
    for (int i = 1; i <= k; i++)
        if (!mp.count(y[i]))
            mp[y[i]] = ((x[i] ^ s[i]) & 1), v--;
        else if (mp[y[i]] != ((x[i] ^ s[i]) & 1))
        {
            v = -1;
            break;
        }
    ans = (1ll * ans + pow(2, v)) % mod;
    int t = (x[1] + y[1] + s[1]) & 1, c = 1;
    for (int i = 2; i <= k; i++)
        if (t != ((x[i] + y[i] + s[i]) & 1))
        {
            c = 0;
            break;
        }
    cout << (ans - c + mod) % mod;
    return 0;
}
