#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int T, n, m, q, ans;
vector<pair<int, int> > A[N];
vector<int> B[N];

int tim, dfn[N], low[N];
int top, stk[N], cnt, col[N];
void tarjan(int u, int p) {
    dfn[u] = low[u] = ++tim, stk[++top] = u;
    for (const auto &[v, s] : A[u])
        if (!dfn[v]) {
            tarjan(v, s), low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]) {
                cnt += 1;
                while (stk[top] != v) col[stk[top--]] = cnt;
                col[stk[top--]] = cnt;
            }
        } else if (s != p)
            low[u] = min(low[u], dfn[v]);
}
int p[N], fa[N], dep[N], del[N];
int get(int x) { return x == p[x] ? x : p[x] = get(p[x]); }
void dfs(int u) {
    for (int v : B[u])
        if (!dep[v]) dep[v] = dep[u] + 1, fa[v] = u, dfs(v);
}
void calc(int a, int b) {
    a = get(a), b = get(b);
    while (a != b) {
        if (dep[a] < dep[b]) swap(a, b);
        ans -= 1, a = p[a] = get(fa[a]);
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m, n || m) {
        for (int i = 1, u, v; i <= m; i++)
            cin >> u >> v, A[u].emplace_back(v, i), A[v].emplace_back(u, i);

        tarjan(1, 0), ans = cnt, cnt += 1;
        while (top) col[stk[top--]] = cnt;

        for (int u = 1; u <= n; u++)
            for (const auto &[v, _] : A[u])
                if (col[u] != col[v]) B[col[u]].emplace_back(col[v]);
        dep[1] = 1, dfs(1);

        cin >> q;
        cout << "Case " << ++T << ":\n";
        iota(p + 1, p + cnt + 1, 1);
        for (int a, b; q--;) {
            cin >> a >> b, a = col[a], b = col[b];
            if (a != b) calc(a, b);
            cout << ans << '\n';
        }
        cout << '\n';

        for (int i = 1; i <= n; i++) A[i].clear();
        for (int i = 1; i <= cnt; i++) B[i].clear();
        tim = cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(dep, 0, sizeof(dep));
        memset(del, 0, sizeof(del));
    }
    return 0;
}