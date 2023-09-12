#include <bits/stdc++.h>
using namespace std;

constexpr int N = 13, M = 1 << 12, INF = 0x3f3f3f3f;
int n, m, w[N][N], f[N][M];
int expd[M], road[M][N];
vector<int> vad[M], cst[M];

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    memset(w, 0x3f, sizeof(w));
    for (int i = 1, u, v, z; i <= m; i++) {
        cin >> u >> v >> z;
        w[u][v] = w[v][u] = min(w[u][v], z);
    }
    memset(road, 0x3f, sizeof(road));
    for (int i = 0; i < 1 << n; i++) {
        expd[i] = i;
        for (int u = 1; u <= n; u++)
            if (i >> (u - 1) & 1) {
                road[i][u] = 0;
                for (int v = 1; v <= n; v++)
                    if (w[u][v] != INF)
                        expd[i] |= 1 << (v - 1), road[i][v] = min(road[i][v], w[u][v]);
            }
    }
    for (int j = 0; j < 1 << n; j++)
        for (int k = j - 1; k; k = (k - 1) & j)
            if ((j & expd[k]) == j) {
                vad[j].emplace_back(k);
                int sum = 0;
                for (int p = 1; p <= n; p++)
                    if ((j ^ k) >> (p - 1) & 1) sum += road[k][p];
                cst[j].emplace_back(sum);
            }
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++) f[1][1 << (i - 1)] = 0;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j < 1 << n; j++)
            for (int p = 0; p < (int)vad[j].size(); p++) {
                int k = vad[j][p];
                f[i][j] = min(f[i][j], f[i - 1][k] + (i - 1) * cst[j][p]);
            }
    int ans = INF;
    for (int i = 1; i <= n; i++) ans = min(ans, f[i][(1 << n) - 1]);
    cout << ans;
    return 0;
}