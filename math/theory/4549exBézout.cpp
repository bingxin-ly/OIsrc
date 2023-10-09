#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (!a || !b) return abs(a | b);
    return gcd(b, a % b);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, a, b;
    cin >> n >> a;
    while (--n) cin >> b, a = gcd(a, b);
    cout << a;
    return 0;
}