#include <bits/stdc++.h>
using namespace std;

constexpr int N = 13, M = 531441, INF = 0x3f3f3f3f,
              pw[13] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441};
int n, m, w[N][N], f[2][M], zero[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    memset(w, 0x3f, sizeof(w));
    for (int i = 1, u, v, z; i <= m; i++) {
        cin >> u >> v >> z;
        w[u][v] = w[v][u] = min(w[u][v], z);
    }
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++) f[1][pw[i - 1]] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < pw[n]; j++) {
            if (f[i & 1][j] == INF) continue;
            int s = j, one = 0, zro = 0;
            for (int p = 1, k = j; p <= n; p++, k /= 3)
                if (k % 3 == 2)
                    s -= pw[p - 1];
                else if (k % 3 == 1)
                    one = p;
                else
                    zero[zro++] = p;
            f[(i + 1) & 1][s] = min(f[(i + 1) & 1][s], f[i & 1][j]);

            if (one) {
                int u = one;
                while (zro--) {
                    int v = zero[zro];
                    if (w[u][v] == INF) continue;
                    s = j + 2 * pw[v - 1];
                    f[i & 1][s] = min(f[i & 1][s], f[i & 1][j] + i * w[u][v]);
                }

                s = j + pw[u - 1];
                f[i & 1][s] = min(f[i & 1][s], f[i & 1][j]);
            }
            f[i & 1][j] = 0x3f3f3f3f;
        }
    }
    int s = 0;
    for (int i = 1; i <= n; i++) s += pw[i - 1];
    cout << f[(n + 1) & 1][s];
    return 0;
}