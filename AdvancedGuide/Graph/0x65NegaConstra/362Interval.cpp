#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e4 + 9;
int n;
vector<pair<int, int> > *g = new vector<pair<int, int> >[N]() + 1;

int *dis = new int[N]() + 1, *in = new int[N]() + 1;
void spfa() {
    memset(dis, ~0x3f, N << 2), dis[-1] = 0;
    queue<int> q;
    q.emplace(-1), in[-1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop(), in[u] = 0;
        for (const auto &[v, w] : g[u])
            if (dis[v] < dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!in[v]) q.emplace(v), in[v] = 1;
            }
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v, w; i <= n; i++)
        cin >> u >> v >> w, g[u - 1].emplace_back(v, w);
    for (int i = 0; i <= 50000; i++)
        g[i - 1].emplace_back(i, 0), g[i].emplace_back(i - 1, -1);
    spfa();
    cout << dis[50000];
    return 0;
}