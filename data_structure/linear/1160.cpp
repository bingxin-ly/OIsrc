#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, prv[N], nxt[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 2, k, p; i <= n; i++) {
        cin >> k >> p;
        if (!p) {
            prv[i] = prv[k], nxt[i] = k;
            nxt[prv[k]] = i, prv[k] = i;
        } else {
            prv[i] = k, nxt[i] = nxt[k];
            prv[nxt[k]] = i, nxt[k] = i;
        }
    }
    cin >> m;
    for (int x; m--;) {
        cin >> x;
        if (!prv[x] && !nxt[x]) continue;
        prv[nxt[x]] = prv[x], nxt[prv[x]] = nxt[x];
        prv[x] = nxt[x] = 0;
    }
    int hed = nxt[0];
    while (hed) cout << hed << ' ', hed = nxt[hed];
    return 0;
}