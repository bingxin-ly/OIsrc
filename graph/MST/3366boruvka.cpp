#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e3 + 5, M = 2e5 + 5;
int n, m, u[M], v[M], w[M];
int bst[N];

int p[N];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> u[i] >> v[i] >> w[i];
    iota(p + 1, p + n + 1, 1);
    int cnt = 0, sum = 0, cop = 0;
    while (!cop) {
        cop = 1, memset(bst, 0, sizeof(bst));
        for (int i = 1; i <= m; i++) {
            int x = find(u[i]), y = find(v[i]);
            if (x == y) continue;
            if (!bst[x] || w[i] < w[bst[x]]) bst[x] = i;
            if (!bst[y] || w[i] < w[bst[y]]) bst[y] = i;
        }
        for (int i = 1; i <= n; i++)
            if (bst[i]) {
                int x = find(u[bst[i]]), y = find(v[bst[i]]);
                if (x == y) continue;
                cnt += 1, sum += w[bst[i]], p[x] = y, cop = 0;
            }
    }
    if (cnt == n - 1)
        cout << sum;
    else
        cout << "orz";
    return 0;
}