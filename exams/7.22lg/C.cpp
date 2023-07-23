// 优化思路：只筛到 sqrt(1e8)
#include <bits/stdc++.h>
using namespace std;

constexpr int W = 1e8 + 5, P = W >> 3;
int tot, vis[W], pri[P];
constexpr int N = 5e5 + 5;
int n, arr[N], cnt[P];

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    if (n == 2)
        return cout << "Yes\n", void();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= tot && arr[i] != 1; j++)
            if (!(arr[i] % pri[j]))
            {
                while (!(arr[i] % pri[j]))
                    arr[i] /= pri[j];
                if (++cnt[j] > 2)
                    return cout << "No\n", void();
            }
    for (int j = 1; j <= tot; j++)
        if (cnt[j] < n && ++cnt[j] > 2)
            return cout << "No\n", void();
    return cout << "Yes\n", void();
}

void sieve(int n)
{
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
            pri[++tot] = i;
        for (int j = 1; j <= tot && i * pri[j] <= n; ++j)
        {
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    sieve(1e8);
    int T;
    cin >> T;
    while (T--)
        solve(), memset(cnt, 0, sizeof(cnt));
    return 0;
}