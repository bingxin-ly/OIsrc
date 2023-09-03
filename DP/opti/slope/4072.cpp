#include <bits/stdc++.h>
#define K(j) (2 * s[j])
#define X(k) (s[k])
#define Y(k) (g[k] + s[k] * s[k])
using namespace std;

constexpr int N = 3e3 + 5, M = 3e4 + 5;
int n, m, s[N], q[N];
long long f[M], g[M];
double slope(int i, int j) { return 1.0 * (Y(j) - Y(i)) / (X(j) - X(i)); }
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> s[i], s[i] += s[i - 1], g[i] = s[i] * s[i];
    for (int i = 2, l, r; i <= m; i++) {
        l = r = 1, q[1] = i - 1;
        for (int j = i; j <= n; j++) {
            while (l < r && slope(q[l], q[l + 1]) <= K(j)) l++;
            f[j] = g[q[l]] + (s[j] - s[q[l]]) * (s[j] - s[q[l]]);
            while (l < r && slope(q[r - 1], q[r]) >= slope(q[r - 1], j)) r--;
            q[++r] = j;
        }
        memcpy(g, f, sizeof(f));
    }
    cout << m * f[n] - s[n] * s[n] << '\n';
    return 0;
}