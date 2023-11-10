#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, w[N], p[N], s[N];
long long ans;
struct E {
    int u, v, w;
} e[N];
int get(int x) { return x == p[x] ? x : p[x] = get(p[x]); }
void solve(long long c) {
    iota(p + 1, p + n + 1, 1), fill(s + 1, s + n + 1, 1);
    for (int i = 1; i < n; i++)
        e[i].w = c > 0 ? max(w[e[i].u], w[e[i].v]) : min(w[e[i].u], w[e[i].v]);
    sort(e + 1, e + n, [c](E x, E y) { return c > 0 ? x.w < y.w : x.w > y.w; });
    for (int i = 1; i < n; i++) {
        int x = get(e[i].u), y = get(e[i].v);
        ans += c * s[x] * s[y] * e[i].w, s[x] += s[y], p[y] = x;
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i < n; i++) cin >> e[i].u >> e[i].v;
    solve(1), solve(-1);
    cout << ans;
    return 0;
}