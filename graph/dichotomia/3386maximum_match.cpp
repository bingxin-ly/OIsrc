#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1009;
vector<int> g[N];

bool vis[N];
int match[N];
bool find(int u) {
    for (int v : g[u])
        if (!vis[v]) {
            vis[v] = true;
            if (!match[v] || find(match[v]))
                return match[v] = u, true;
        }
    return false;
}
int main() {
    int n, m, e;
    cin >> n >> m >> e;
    for (int i = 1, u, v; i <= e; i++) {
        cin >> u >> v;
        v += n, g[u].push_back(v);
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, false, sizeof(vis));
        res += find(i);
    }
    cout << res;
    return 0;
}