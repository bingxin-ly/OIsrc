#include <bits/stdc++.h>
#define K(i) (2 * a * s[i])
#define X(j) (s[j])
#define B(i) (f[i] - a * s[i] * s[i] - b * s[i] - c)
#define Y(j) (f[j] + a * s[j] * s[j] - b * s[j])
using namespace std;

constexpr int N = 1e6 + 5;
int n, a, b, c, q[N];
long long s[N], f[N];
double slope(int i, int j) { return 1.0 * ((Y(i) - Y(j)) / (X(i) - X(j))); }
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> a >> b >> c;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1];
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        while (l < r && slope(q[l], q[l + 1]) > K(i)) l++;
        f[i] = -(K(i) * X(q[l]) - Y(q[l]) - a * s[i] * s[i] - b * s[i] - c);
        while (l < r && slope(q[r - 1], q[r]) <= slope(q[r], i)) r--;
        q[++r] = i;
    }
    cout << f[n];
    return 0;
}