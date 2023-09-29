#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, c, p[N];
bool check(int x) {
    int sum = 0, pre = p[1];
    for (int i = 2; i <= n; i++) {
        if (p[i] - pre >= x)
            sum++, pre = p[i];
        if (sum >= c)
            return true;
    }
    if (sum + 1 < c) return false;
    return true;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> c;
    for (int i = 1; i <= n; i++) cin >> p[i];
    sort(p + 1, p + n + 1);
    int l = 1e9, r = p[n] - p[1];
    for (int i = 2; i <= n; i++) l = min(l, p[i] - p[i - 1]);
    while (l <= r) {
        int m = (l + r) >> 1;
        check(m) ? l = m + 1 : r = m - 1;
    }
    cout << r;
    return 0;
}