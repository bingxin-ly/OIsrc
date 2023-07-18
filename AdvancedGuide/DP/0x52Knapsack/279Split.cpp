#include <bits/stdc++.h>
using namespace std;

namespace normal
{
    unsigned f[4005][4005], MOD = 2147483648U;
    signed main()
    {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        int n;
        cin >> n;
        for (int i = 0; i <= n; i++)
            f[i][0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                (f[i][j] += f[i - 1][j]) %= MOD;
            for (int j = i; j <= n; j++)
                (f[i][j] += f[i][j - i]) %= MOD;
        }
        cout << (f[n][n] - 1 + MOD) % MOD; // 我不要条件判断
        return 0;
    }
}
namespace roll
{
    unsigned f[4005], MOD = 2147483648U;
    signed main()
    {
        int n;
        cin >> n;
        f[0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++)
                (f[j] += f[j - i]) %= MOD;
        cout << (f[n] - 1 + MOD) % MOD;
        return 0;
    }
}
signed main() { return roll::main(); }