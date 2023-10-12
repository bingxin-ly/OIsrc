#include <bits/stdc++.h>
using namespace std;

constexpr int M = 1e9 + 7;
int qmi(int a, long long b) {
    int r = 1;
    for (/* a %= p, b %= φ(p) */; b; b >>= 1) {
        if (b & 1) r = 1ll * r * a % M;
        a = 1ll * a * a % M;
    }
    return r;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    long long w, k;
    cin >> w >> k >> k;
    cout << w * qmi(qmi(2, k), M - 2) % M;
    return 0;
}