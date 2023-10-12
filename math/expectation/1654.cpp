#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n;
double p[N], x1[N], x2[N], x3[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) {
        x1[i] = (x1[i - 1] + 1) * p[i];
        x2[i] = (x2[i - 1] + 2 * x1[i - 1] + 1) * p[i];
        x3[i] = x3[i - 1] + (3 * x2[i - 1] + 3 * x1[i - 1] + 1) * p[i];
    }
    cout << fixed << setprecision(1) << x3[n];
    return 0;
}