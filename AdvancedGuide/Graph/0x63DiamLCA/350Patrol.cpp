#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, k;
int idx = 1, hed[N], nxt[N << 1], ver[N << 1], len[N << 1];
void link(int u, int v) {
    ver[++idx] = v, len[idx] = 1, nxt[idx] = hed[u], hed[u] = idx;
}
int dis[N], pre[N];
int bfs(int s) {
    memset(dis, -1, sizeof(dis));
    queue<int> q;
    q.emplace(s), dis[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = hed[u]; i; i = nxt[i]) {
            int v = ver[i];
            if (dis[v] == -1)
                dis[v] = dis[u] + 1, pre[v] = i, q.emplace(v);
        }
    }
    int p = s;
    for (int i = 1; i <= n; i++)
        if (dis[i] > dis[p]) p = i;
    return p;
}
int L2;
void dp(int u, int p) {
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = ver[i], w = len[i];
        if (v == p) continue;
        dp(v, u);
        L2 = max(L2, dis[v] + dis[u] + w);
        dis[u] = max(dis[u], dis[v] + w);
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, link(u, v), link(v, u);
    int p = bfs(1), q = bfs(p), L1 = dis[q];
    if (k == 1)
        cout << 2 * (n - 1) - L1 + 1;
    else {
        while (q != p) {
            len[pre[q]] = len[pre[q] ^ 1] = -1;
            q = ver[pre[q] ^ 1];
        }
        memset(dis, 0, sizeof(dis)), dp(1, 0);
        cout << 2 * (n - 1) - L1 + 1 - L2 + 1;
    }
    return 0;
}