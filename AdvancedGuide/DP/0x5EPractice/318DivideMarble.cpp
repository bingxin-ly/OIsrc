/* 注意是可行性问题！无优解劣解之分
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1.2e5 + 5;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    static int c[7], u[N << 1], f[N];
    while (true)
    {
        int sum = 0;
        for (int i = 1; i <= 6; i++)
            cin >> c[i], sum += c[i] * i;
        if (!sum)
            break;
        if (sum & 1)
        {
            cout << "Can't\n";
            continue;
        }
        memset(f, 0, sizeof(f)), f[0] = 1, sum >>= 1;
        for (int i = 1; i <= 6; i++)
        {
            memset(u, 0, sizeof(u));
            for (int j = i; j <= sum; j++)
                if (!f[j] && f[j - i] && u[j - i] < c[i])
                    f[j] = 1, u[j] = u[j - i] + 1;
        }
        cout << (f[sum] ? "Can\n" : "Can't\n");
    }
    return 0;
}