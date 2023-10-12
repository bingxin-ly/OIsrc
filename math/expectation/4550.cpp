#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 9;
double f[N], g[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = n - 1; i >= 0; i--) {
        f[i] = f[i + 1] + 1. * n / (n - i);
        g[i] = g[i + 1] + f[i + 1] + f[i] * i / (n - i) + 1. * n / (n - i);
    }
    cout << fixed << setprecision(2) << g[0];
    return 0;
}