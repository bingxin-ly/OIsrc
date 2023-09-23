#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, ans, idx, son[N << 5][2];

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) { // 从高位考虑
        int u = x >> i & 1;
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
}
int search(int x) {
    int p = 0, r = 0;
    for (int i = 30; i >= 0; i--) {
        int u = x >> i & 1;
        if (son[p][u ^ 1])
            p = son[p][u ^ 1], r |= 1 << i;
        else
            p = son[p][u];
    }
    return r;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, x; i <= n; i++)
        cin >> x, ans = max(ans, search(x)), insert(x);
    cout << ans;
    return 0;
}