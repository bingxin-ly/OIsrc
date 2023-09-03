#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;
int n, t[1005];
int lowbit(int x) { return x & -x; }
void insert(int p, int v)
{
    for (; p <= n + 1; p += lowbit(p))
        (t[p] += v) %= MOD;
}
int query(int p, int ret = 0)
{
    for (; p; p -= lowbit(p))
        (ret += t[p]) %= MOD;
    return ret;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    for (int $ = 1; $ <= T; $++)
    {
        static int m, s[1005], c[1005];
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> s[i];
        memcpy(c, s, sizeof(s)), sort(c + 1, c + n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = lower_bound(c + 1, c + n + 1, s[i]) - c + 1;
        static int f[1005][1005];
        s[0] = f[0][0] = 1;
        for (int i = 1; i <= m; i++)
        {
            memset(t, 0, sizeof(t));
            insert(s[0], f[i - 1][0]);
            for (int j = 1; j <= n; j++)
                f[i][j] = query(s[j] - 1), insert(s[j], f[i - 1][j]);
        }
        int ans = 0;
        for (int j = 1; j <= n; j++)
            (ans += f[m][j]) %= MOD;
        cout << "Case #" << $ << ": " << ans << '\n';
    }
    return 0;
}