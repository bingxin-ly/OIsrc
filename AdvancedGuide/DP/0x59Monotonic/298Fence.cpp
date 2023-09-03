#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1.6e4 + 5, M = 105;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    static int n, m, L[M], P[M], S[M], p[M];
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> L[i] >> P[i] >> S[i];
    iota(p + 1, p + m + 1, 1);
    sort(p + 1, p + m + 1, [](int i, int j)
         { return S[i] < S[j]; });
    static int f[M][N], q[N];
    function<int(int, int)> calc = [&](int i, int k)
    { return f[i - 1][k] - P[p[i]] * k; };
    for (int i = 1; i <= m; i++)
    {
        int l = 1, r = 0;
        for (int k = max(0, S[p[i]] - L[p[i]]); k <= S[p[i]] - 1; k++)
        {
            while (l <= r && calc(i, q[r]) <= calc(i, k))
                r--;
            q[++r] = k;
        }
        for (int j = 1; j <= n; j++)
        {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (j >= S[p[i]])
            {
                while (l <= r && q[l] < j - L[p[i]])
                    l++;
                if (l <= r)
                    f[i][j] = max(f[i][j], calc(i, q[l]) + P[p[i]] * j);
            }
        }
    }
    cout << f[m][n];
    return 0;
}