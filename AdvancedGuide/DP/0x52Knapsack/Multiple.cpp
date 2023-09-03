#include <bits/stdc++.h>
using namespace std;

namespace force
{
    constexpr int N = 105;
    int v[N], w[N], s[N], f[N];
    signed main()
    {
        int n, m;
        cin >> n >> m;
        memset(f, ~0x3f, sizeof(f));
        f[0] = 0;
        for (int i = 1; i <= n; i++)
            cin >> v[i] >> w[i] >> s[i];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= s[i]; j++)
                for (int k = m; k >= v[i]; k--)
                    f[k] = max(f[k], f[k - v[i]] + w[i]);
        int ans = 0;
        for (int j = 1; j <= m; j++)
            ans = max(ans, f[j]);
        cout << ans;
        return 0;
    }
}
namespace binary
{
    // 每个物品最多有 2000个，即最多拆成 11个，又有 1000个物品，所以 1.1e4大小
    constexpr int N = 11005, M = 2005;
    int cnt, v[N], w[N], f[M];
    signed main()
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1, a, b, c; i <= n; i++)
        {
            cin >> a >> b >> c;
            for (int s = 1; s <= c; c -= s, s <<= 1)
                v[++cnt] = a * s, w[cnt] = b * s;
            if (c > 0)
                v[++cnt] = a * c, w[cnt] = b * c;
        }
        memset(f, ~0x3f, sizeof(f));
        f[0] = 0;
        for (int i = 1; i <= cnt; i++)
            for (int j = m; j >= v[i]; j--)
                f[j] = max(f[j], f[j - v[i]] + w[i]);
        cout << f[m];
        return 0;
    }
}
namespace std
{
    constexpr int N = 2005;
    int n, m, f[N];

    // 用一个拆出来的物品把 DP 的体积数组更新一遍
    void update(int v, int w)
    {
        for (int j = m; j >= v; j--)
            f[j] = max(f[j], f[j - v] + w);
    }

    int main()
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            int v, w, c;
            cin >> v >> w >> c;
            // 二进制拆分
            for (int k = 1; k <= c; k <<= 1)
            {
                c -= k;
                update(k * v, k * w);
            }
            // 剩余部分
            if (c > 0)
                update(c * v, c * w);
        }
        cout << f[m];
    }
}
signed main() { return binary::main(); }