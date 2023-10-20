#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1009, M = 5009;
int n, m, a[N];
struct {
    int u, v, w;
} b[M];
int idx, hed[N], nxt[M], ver[M];
double val[M];
void link(int u, int v, double w) {
    ver[++idx] = v, val[idx] = w, nxt[idx] = hed[u], hed[u] = idx;
}
int in[N], len[N];
double dis[N];
bool ok() {
    queue<int> q;
    for (int i = 1; i <= n; i++) dis[i] = len[i] = 0, q.emplace(i), in[i] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop(), in[u] = false;
        for (int i = hed[u]; i; i = nxt[i]) {
            int v = ver[i];
            double w = val[i];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w, len[v] = len[u] + 1;
                if (len[v] >= n) return 1;
                if (!in[v]) q.emplace(v), in[v] = 1;
            }
        }
    }
    return 0;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i].u >> b[i].v >> b[i].w;
    double l = 0, r = 1e6;
    while (r - l > 1e-4) {
        double s = (l + r) / 2;
        memset(hed, 0, sizeof(hed)), idx = 0;
        for (int i = 1; i <= m; i++)
            link(b[i].u, b[i].v, s * b[i].w - a[b[i].u]);
        ok() ? l = s : r = s;
    }
    cout << fixed << setprecision(2) << r;
    return 0;
}