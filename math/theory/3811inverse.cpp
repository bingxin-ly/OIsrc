#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 3e6 + 9;
int n, p, inv[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> p;
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
    for (int i = 1; i <= n; i++) cout << inv[i] << '\n';
    return 0;
}