#include <bits/stdc++.h>
using namespace std;
const int N = 1005, M = 1000005;
int ver[M * 2], nxt[M * 2], head[N], tot;
int dfn[N], low[N], s[N], c[N], v[N], n, m, num, top, cnt, root;
bool hate[N][N], able[N];

void add(int x, int y) {
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}

bool dfs(int x, int color) {
    v[x] = color;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (c[y] && ((!v[y] && dfs(y, 3 - color)) || (v[y] && v[y] != 3 - color)))
            return true;
    }
    return false;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++num, s[++top] = x;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {  // 树边
            tarjan(y);
            low[x] = min(low[x], low[y]);
            if (dfn[x] <= low[y]) {
                vector<int> dcc{x};
                while (s[top + 1] != y) dcc.push_back(s[top--]);
                for (int i : dcc) c[i] = 1, v[i] = 0;
                if (dfs(x, 1))
                    for (int i : dcc) able[i] = 1;
                for (int i : dcc) c[i] = 0;
            }
        } else
            low[x] = min(low[x], dfn[y]);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\src\\.in", "r", stdin);
    freopen("D:\\src\\.out", "w", stdout);
#endif
    while (cin >> n >> m && n) {
        tot = 1, memset(head, 0, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(c, 0, sizeof(c));
        memset(able, 0, sizeof(able));
        num = top = cnt = root = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                hate[i][j] = false;
        for (int i = 1; i <= m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            hate[x][y] = hate[y][x] = true;
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (i != j && !hate[i][j]) add(i, j);
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) tarjan(i);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            if (!able[i]) ans++;
        cout << ans << endl;
    }
}