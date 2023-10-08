#include <bits/stdc++.h>
#define long long long
using namespace std;

long a, b, x, y;
void exgcd(long a, long b, long &x, long &y) {
    if (!b) return x = 1, y = 0, void();
    exgcd(b, a % b, y, x), y -= a / b * x;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> a >> b, exgcd(a, b, x, y), cout << (x % b + b) % b;
    return 0;
}