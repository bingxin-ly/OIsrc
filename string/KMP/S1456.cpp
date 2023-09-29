#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 10, M = 998244353;
int h[N], e[N << 1], ne[N << 1], idx;
char s[N];
long long f[N];
int fa[23][N];
int nxt[N];
long long ans = 1;
int n, k;

struct query {
    int id, x, op;
};
vector<query> qu[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int find(int x) {
    int p = x;
    for (int i = 21; i >= 0; i--)
        if (2 * fa[i][p] >= x + 1)
            p = fa[i][p];
    return p;
}

int buc[N];
void dfs(int u, int fat) {
    buc[2 * u % k]++;
    for (auto t : qu[u]) {
        int id = t.id, x = t.x, op = t.op;
        f[id] = (f[id] + op * buc[x]) % M;
    }
    for (int i = h[u]; i != -1; i = ne[i]) {
        int v = e[i];
        if (v == fat) continue;
        dfs(v, u);
    }
    buc[2 * u % k]--;
}

int main() {
    memset(h, -1, sizeof h);

    cin >> (s + 1) >> k, n = strlen(s + 1);
    fa[0][1] = 0;
    add(0, 1), add(1, 0);
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[j + 1] != s[i]) j = nxt[j];
        if (s[j + 1] == s[i]) j++;
        nxt[i] = j, fa[0][i] = j;
        add(j, i), add(i, j);
    }

    for (int i = 1; i <= 21; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];

    for (int i = 1; i <= n; i++) {
        qu[i].push_back({i, i % k, 1});
        qu[fa[0][find(i)]].push_back({i, i % k, -1});
    }

    dfs(0, 0);

    for (int i = 1; i <= n; i++) {
        ans = (ans * (f[i] + 1)) % M;
    }

    cout << ans << endl;

    return 0;
}
