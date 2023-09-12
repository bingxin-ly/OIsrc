#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
bool vis[N];
long long n, h, r, X[N], Y[N], Z[N];
long long squ(long long $) { return $ * $; }
long long dis(int i, int j) {
    return squ(X[i] - X[j]) + squ(Y[i] - Y[j]) + squ(Z[i] - Z[j]);
}
void solve() {
    cin >> n >> h >> r;
    for (int i = 1; i <= n; i++) cin >> X[i] >> Y[i] >> Z[i];

    memset(vis, 0, sizeof(vis));
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (r >= -Z[i] && Z[i] <= r) q.emplace(i), vis[i] = 1;
    bool suc = false;
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        if (Z[i] + r >= h) {
            suc = true;
            break;
        }

        for (int j = 1; j <= n; j++) {
            if (vis[j]) continue;
            if (dis(i, j) <= squ(r * 2)) vis[j] = 1, q.emplace(j);
        }
    }
    cout << (suc ? "Yes\n" : "No\n");
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}