#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1009;
int phi[N];
void euler(int n) {
    iota(phi + 2, phi + n + 1, 2);
    for (int i = 2; i <= n; i++)
        if (phi[i] == i)
            for (int j = i; j <= n; j += i)
                phi[j] = phi[j] / i * (i - 1);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    euler(1000);
    for (int i = 2; i <= 1000; i++) phi[i] += phi[i - 1];
    int c;
    cin >> c;
    for (int i = 1, n; i <= c; i++) cin >> n, cout << i << ' ' << n << ' ' << 2 * phi[n] + 3 << '\n';
    return 0;
}