#include <bits/stdc++.h>
using namespace std;

constexpr int N = (1 << 20) + 5;
char s[N];
int n, bef[30], aft[30];
int all, pre, suf;

namespace fenwick
{
    int t[30];
    void insert(int p)
    {
        while (p <= 27)
            t[p]++, p += p & -p;
    }
    int query(int p)
    {
        int ret = 0;
        while (p)
            ret += t[p], p -= p & -p;
        return ret;
    }
}
using namespace fenwick;

int z[N];
void Z()
{
    z[1] = n;
    int l = 0, r = 0;
    for (int i = 2; i <= n; i++)
    {
        z[i] = i <= r ? min(z[i - l + 1], r - i + 1) : 0;
        while (s[1 + z[i]] == s[i + z[i]])
            z[i] += 1;
        if (r < i + z[i] - 1)
            r = i + z[i] - 1, l = i;
    }
}
void solve()
{
    cin >> (s + 1), n = strlen(s + 1);
    Z();
    for (int i = 1; i <= n; i++)
    {
        aft[s[i] - 'a']++;
        if (i + z[i] - 1 == n)
            z[i]--;
    }
    for (int i = 0; i < 26; i++)
        all += aft[i] & 1;
    suf = all;
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        aft[s[i] - 'a'] & 1 ? suf-- : suf++;
        aft[s[i] - 'a']--;
        bef[s[i] - 'a'] & 1 ? pre-- : pre++;
        bef[s[i] - 'a']++;
        if (i != 1 && i != n)
        {
            int t = z[i + 1] / i + 1;
            // cerr << z[i + 1] << ' ' << i << ' ' << t << endl;
            ans += 1ll * (t / 2) * query(all + 1) +
                   1ll * (t - t / 2) * query(suf + 1);
        }
        insert(pre + 1);
    }
    cout << ans << '\n';
}
void clear()
{
    memset(bef, 0, sizeof(bef));
    memset(aft, 0, sizeof(aft));
    memset(t, 0, sizeof(t));
    all = pre = suf = 0;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve(), clear();
    return 0;
}