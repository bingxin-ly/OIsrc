#include <bits/stdc++.h>
using namespace std;

constexpr int N = 109;
int n, m, idx[N], nxt[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) idx[i] = i, nxt[i] = i + 1;
    nxt[n] = 1;
    int cur = 1;
    while (n--) {
        for (int i = 1; i < m; i++) cur = nxt[cur];
        cout << idx[cur] << ' ';
        idx[cur] = idx[nxt[cur]], nxt[cur] = nxt[nxt[cur]];
    }
    return 0;
}