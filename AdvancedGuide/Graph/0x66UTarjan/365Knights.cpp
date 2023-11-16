#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1009;
int n, m, no[N][N];
vector<int> g[N];

int tim, dfn[N], low[N], top, stk[N];
int acs[N], col[N], can[N];
bool color(int u, int c) {
    col[u] = c;
    for (int v : g[u])
        if (acs[v] && ((!col[v] && color(v, 3 - c)) || (col[v] && col[v] != 3 - c))) return true;
    return false;
}
void form(int u, int v) {
    vector<int> dcc{u};
    while (stk[top + 1] != v) dcc.emplace_back(stk[top--]);
    for (int i : dcc) acs[i] = 1, col[i] = 0;
    if (color(u, 1))
        for (int i : dcc) can[i] = 1;
    for (int i : dcc) acs[i] = 0;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++tim, stk[++top] = u;
    for (int v : g[u])
        if (!dfn[v]) {
            tarjan(v), low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) form(u, v);
        } else
            low[u] = min(low[u], dfn[v]);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m, n || m) {
        memset(no, 0, sizeof(no));
        for (int i = 1, u, v; i <= m; i++) cin >> u >> v, no[u][v] = no[v][u] = 1;
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (i != j && !no[i][j]) g[i].emplace_back(j);
        tim = top = 0, memset(dfn, 0, sizeof(dfn)), memset(can, 0, sizeof(can));
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) tarjan(i);

        cout << n - accumulate(can + 1, can + n + 1, 0) << '\n';
    }
    return 0;
}