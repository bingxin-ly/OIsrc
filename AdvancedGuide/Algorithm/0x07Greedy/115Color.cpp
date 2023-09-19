#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1009;
int n, R;
struct {
    int p, s, v;
    double avg;
} t[N];

int find() {
    double avg = 0;
    int ret = -1;
    for (int i = 1; i <= n; i++)
        if (i != R && t[i].avg > avg) avg = t[i].avg, ret = i;
    return ret;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> R;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> t[i].v;
        t[i].s = 1, t[i].avg = t[i].v, ans += t[i].v;
    }
    for (int i = 1, a, b; i < n; i++) cin >> a >> b, t[b].p = a;
    for (int i = 1; i <= n; i++) {
        int o = find(), p = t[o].p;
        ans += t[o].v * t[p].s, t[o].avg = -1;
        for (int j = 1; j <= n; j++)
            if (t[j].p == o) t[j].p = p;
        t[p].v += t[o].v, t[p].s += t[o].s, t[p].avg = 1.0 * t[p].v / t[p].s;
    }
    cout << ans;
    return 0;
}