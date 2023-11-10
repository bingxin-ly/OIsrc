#include <bits/stdc++.h>
using namespace std;
using pdl = pair<double, long long>;

constexpr int N = 21;
long long n, com[N][N];
double A, B, C, D, pa[N], pb[N], pc[N], pd[N], ans;
priority_queue<pdl, vector<pdl>, greater<> > q;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> A >> B >> C >> D, pa[0] = pb[0] = pc[0] = pd[0] = 1;
    for (int i = 1; i <= n; i++) {
        pa[i] = pa[i - 1] * A, pb[i] = pb[i - 1] * B,
        pc[i] = pc[i - 1] * C, pd[i] = pd[i - 1] * D;
    }
    for (int i = 0; i <= n; i++) {
        com[i][0] = 1;
        for (int j = 1; j <= i; j++) com[i][j] = com[i - 1][j] + com[i - 1][j - 1];
    }
    for (int a = 0; a <= n; a++)
        for (int b = 0; b <= n; b++)
            for (int c = 0; c <= n; c++)
                for (int d = 0; d <= n; d++)
                    if (a + b + c + d == n)
                        q.emplace(pa[a] * pb[b] * pc[c] * pd[d],
                                  com[n][a] * com[n - a][b] * com[n - a - b][c]);
    while (true) {
        auto p = q.top();
        q.pop();
        if (q.empty() && p.second == 1) break;
        if (p.second > 1) {
            if (p.second & 1) q.emplace(p.first, 1);
            q.emplace(2 * p.first, p.second >> 1), ans += p.first * (p.second >> 1 << 1);
        } else {
            auto pp = q.top();
            q.pop();
            q.emplace(p.first + pp.first, 1), ans += p.first + pp.first;
            if (pp.second > 1) q.emplace(pp.first, pp.second - 1);
        }
    }
    cout << fixed << setprecision(6) << ans;
    return 0;
}