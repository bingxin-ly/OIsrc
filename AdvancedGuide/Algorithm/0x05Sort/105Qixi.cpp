#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, t, R[N], C[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> t;
    for (int i = 1, x, y; i <= t; i++) cin >> x >> y, R[x]++, C[y]++;
    bool row = t % n == 0, col = t % m == 0;
    long long ans = 0;
    if (row) {
        int num = t / n;
        for (int i = 1; i <= n; i++) R[i] -= num, R[i] += R[i - 1];
        sort(R + 1, R + n + 1);
        int mid = (1 + n) >> 1;
        nth_element(R + 1, R + mid, R + n + 1);
        for (int i = 1; i <= n; i++) ans += abs(R[i] - R[mid]);
    }
    if (col) {
        int num = t / m;
        for (int i = 1; i <= m; i++) C[i] -= num, C[i] += C[i - 1];
        sort(C + 1, C + m + 1);
        int mid = (1 + m) >> 1;
        nth_element(C + 1, C + mid, C + m + 1);
        for (int i = 1; i <= m; i++) ans += abs(C[i] - C[mid]);
    }
    if (row && col)
        cout << "both " << ans;
    else if (row || col)
        cout << (row ? "row " : "column ") << ans;
    else
        cout << "impossible";
    return 0;
}