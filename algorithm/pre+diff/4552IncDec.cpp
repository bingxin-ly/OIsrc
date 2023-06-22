#include <bits/stdc++.h>
using namespace std;

// 求出原序列的差分序列 D 之后
// 将 S[2...n] 全部变为 0 所需的最少的步数
// 和可以使 S[1] 变为多少种不同的数
const int N = 1e5 + 10;
int S[N], D[N];

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> S[i];

    long long x = 0, y = 0;
    for (int i = 2; i <= n; i++)
    {
        D[i] = S[i] - S[i - 1];
        if (D[i] > 0)
            x += D[i];
        else
            y -= D[i];
    }
    cout << max(x, y) << '\n'
         << abs(x - y) + 1;
    return 0;
}