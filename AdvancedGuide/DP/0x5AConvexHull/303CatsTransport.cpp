#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, p, D[N], q[N];
long long W[N], S[N], f[N], g[N];
double slope(int i, int j) {
    return 1.0 * ((g[j] + S[j]) - (g[i] + S[i])) / (j - i);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> p;
    for (int i = 2; i <= n; i++) cin >> D[i], D[i] += D[i - 1];
    for (int i = 1, H, T; i <= m; i++) cin >> H >> T, W[i] = T - D[H];
    sort(W + 1, W + m + 1);
    for (int i = 1; i <= m; i++) S[i] = S[i - 1] + W[i];

    memset(g, 0x3f, sizeof(g)), g[0] = 0;
    for (int i = 1; i <= p; i++) {
        int l = 1, r = 1;
        for (int j = 1; j <= m; j++) {
            while (l < r && slope(q[l], q[l + 1]) <= W[j]) l++;
            f[j] = g[q[l]] + W[j] * (j - q[l]) - (S[j] - S[q[l]]);
            // if (g[j] + S[j] >= 0x3f3f3f3f3f3f3f3f) continue; Unnecessary
            while (l < r && slope(q[r - 1], q[r]) >= slope(q[r - 1], j)) r--;
            q[++r] = j;
        }
        memcpy(g, f, sizeof(f));
    }
    cout << f[m];
    return 0;
}