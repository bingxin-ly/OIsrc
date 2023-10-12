#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> day{
    {"MON", 1}, {"TUE", 2}, {"WED", 3}, {"THU", 4}, {"FRI", 5}, {"SAT", 6}, {"SUN", 7}};
constexpr int N = 309;
int n, m, a[N][N], b[N];
int exgcd(int a, int b, int &x, int &y) {
    if (!b) return x = 1, y = 0, a;
    int d = exgcd(b, a % b, y, x);
    return y -= a / b * x, d;
}
void solve() {
    memset(a, 0, sizeof(a));
    for (int i = 1, k; i <= m; i++) {
        string st, ed;
        cin >> k >> st >> ed;
        b[i] = (day[ed] - day[st] + 1) % 7;
        for (int x; k--;) cin >> x, (a[i][x] += 1) %= 7;
    }
    int w = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = w + 1; j <= m; j++)
            if (a[j][i]) {
                w++, swap(a[w], a[j]), swap(b[w], b[j]);
                break;
            }
        if (!a[w][i]) continue;
        for (int j = 1; j <= m; j++) {
            if (w == j || !a[j][i]) continue;
            int z = a[j][i];
            for (int k = 1; k <= n; k++) a[j][k] = (a[j][k] * a[w][i] - a[w][k] * z) % 7;
            b[j] = (b[j] * a[w][i] - b[w] * z) % 7;
        }
    }
    for (int i = w + 1; i <= m; i++)
        if (b[i] %= 7) return cout << "Inconsistent data.\n", void();
    if (w < n) return cout << "Multiple solutions.\n", void();
    for (int i = 1; i <= n; i++) {
        int x, y, d = exgcd(a[i][i], 7, x, y);
        if (b[i] % d) return cout << "Inconsistent data.\n", void();
        cout << ((x * b[i] / d - 3) % 7 + 7) % 7 + 3 << ' ';
    }
    cout << '\n';
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m && n && m) solve();
    return 0;
}