#include <bits/stdc++.h>
#define int long long
using namespace std;

void exgcd(int a, int b, int &x, int &y) {
    if (!b) return x = 1, y = 0, void();
    exgcd(b, a % b, y, x), y -= a / b * x;
}
int CRT(int n, int *b, int *p) {
    int M = 1, X = 0;
    for (int i = 1; i <= n; i++) M *= p[i];
    for (int i = 1; i <= n; i++) {
        int m = M / p[i], x, y;
        exgcd(m, p[i], x, y);
        (X += b[i] * m * x % M) %= M;
    }
    return (X + M) % M;
}
signed main() {
    int n, p[11], b[11];
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i] >> b[i];
    cout << CRT(n, b, p);
    return 0;
}