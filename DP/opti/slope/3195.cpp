#include <bits/stdc++.h>
#define K(i) (2 * s[i])
#define X(j) (s[j])
#define B(i) (f[i] - s[i] * s[i] + 2 * L * s[i] - L * L)
#define Y(j) (f[j] + s[j] * s[j] + 2 * L * s[j])
using namespace std;

constexpr int N = 5e4 + 5;
long long n, L, s[N], q[N], f[N];
double slope(int i, int j) { return 1.0 * (Y(j) - Y(i)) / (X(j) - X(i)); }
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> L, L += 1;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1] + 1;
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        while (l < r && slope(q[l], q[l + 1]) <= K(i)) l++;
        // f[i] = Y(q[l]) - K(i) * X(q[l]) + s[i] * s[i] - 2 * L * s[i] + L * L;
        f[i] = f[q[l]] + (s[i] - s[q[l]] - L) * (s[i] - s[q[l]] - L);
        // 已经知道 j 了为啥不套朴素式子？
        while (l < r && slope(q[r - 1], q[r]) >= slope(q[r - 1], i)) r--;
        q[++r] = i;
    }
    cout << f[n];
    return 0;
}