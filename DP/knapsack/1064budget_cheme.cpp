#include <bits/stdc++.h>
using namespace std;

constexpr int N = 65, M = 3.2e4 + 5;
int n, m, v[N], w[N];
int b[N], f[M];
vector<int> apd[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m >> n;
    for (int i = 1, p; i <= n; i++)
        cin >> v[i] >> w[i] >> p, b[i] = p, apd[p].emplace_back(i);

    for (int i = 1; i <= n; i++)
    {
        if (b[i])
            continue;
        for (int j = m; j >= 0; j--)
        {
            int p1, p2;
            if (apd[i].size() >= 2)
            {
                p1 = apd[i][0], p2 = apd[i][1];
                if (j >= v[i] + v[p1] + v[p2])
                    f[j] = max(f[j], f[j - v[i] - v[p1] - v[p2]] + v[i] * w[i] + v[p1] * w[p1] + v[p2] * w[p2]);
                if (j >= v[i] + v[p2])
                    f[j] = max(f[j], f[j - v[i] - v[p2]] + v[i] * w[i] + v[p2] * w[p2]);
            }
            if (apd[i].size() >= 1)
            {
                p1 = apd[i][0];
                if (j >= v[i] + v[p1])
                    f[j] = max(f[j], f[j - v[i] - v[p1]] + v[i] * w[i] + v[p1] * w[p1]);
            }
            if (j >= v[i])
                f[j] = max(f[j], f[j - v[i]] + v[i] * w[i]);
        }
    }
    cout << f[m];
    return 0;
}