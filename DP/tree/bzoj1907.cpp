#include <bits/stdc++.h>
using namespace std;

constexpr int N = 10009;
int T, n, f[N][3];
vector<int> g[N];
void dp(int u, int p) {
    int sum = 0, chn = 0;
    for (int v : g[u])
        if (v != p) {
            dp(v, u);
            if (f[v][1] < f[v][2])
                sum += f[v][2];
            else
                sum += f[v][1], chn += 1;
        }
    f[u][1] = f[u][2] = sum;
    if (chn >= 1) f[u][1] += 1;
    if (chn >= 2) f[u][2] += 2;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (cin >> T; T--;) {
        cin >> n;
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1, u, v; i < n; i++)
            cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
        dp(1, 0);
        cout << n - max(f[1][1], f[1][2]) << '\n';
    }
    return 0;
}