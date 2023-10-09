#include <bits/stdc++.h>
using namespace std;

constexpr int N = 109, M = 1e5 + 9;
int n, m, a[M], w[N][N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> w[i][j];
    for (int k = 1; k <= n; k++)
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++)
                w[u][v] = min(w[u][v], w[u][k] + w[k][v]);
    int ans = 0;
    for (int i = 1; i < m; i++) ans += w[a[i]][a[i + 1]];
    cout << ans;
    return 0;
}