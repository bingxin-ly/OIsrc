#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1009;
int n, m, v[N][N], w[N][N], s[N], f[N];
vector<pair<int, int> > g[N];

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m >> n;
    for (int i = 1, a, b, c; i <= n; i++)
        cin >> a >> b >> c, g[c].emplace_back(a, b);
    for (int i = 1; !g[i].empty(); i++) {
        s[i] = g[i].size();
        for (int j = 0; j < s[i]; j++)
            v[i][j] = g[i][j].first, w[i][j] = g[i][j].second;
    }
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 0; k < s[i]; k++)
                if (j >= v[i][k])
                    f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
    cout << f[m];
    return 0;
}