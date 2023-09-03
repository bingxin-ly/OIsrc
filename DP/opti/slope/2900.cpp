#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e4 + 5;
int n, q[N];
long long f[N], X[N], Y[N];
double slope(int i, int j) {
    return 1.0 * (f[j] - f[i]) / (Y[i + 1] - Y[j + 1]);
}
pair<int, int> p[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i].first >> p[i].second;
    sort(p + 1, p + n + 1);
    int m = 0;
    for (int i = 1; i <= n; i++) {
        while (m && Y[m] <= p[i].second) m--;
        X[++m] = p[i].first, Y[m] = p[i].second;
    }
    int l = 1, r = 1;
    for (int i = 1; i <= m; i++) {
        while (l < r && slope(q[l], q[l + 1]) <= X[i]) l++;
        f[i] = f[q[l]] + Y[q[l] + 1] * X[i];
        while (l < r && slope(q[r - 1], q[r]) >= slope(q[r - 1], i)) r--;
        q[++r] = i;
    }
    cout << f[m];
    return 0;
}