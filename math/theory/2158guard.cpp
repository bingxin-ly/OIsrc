#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 4e4 + 9;
int phi[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n, n -= 1;
    if (!n) return cout << 0, 0;
    iota(phi + 1, phi + n + 1, 1);
    for (int i = 2; i <= n; i++)
        if (phi[i] == i)
            for (int j = i; j <= n; j += i)
                phi[j] = phi[j] / i * (i - 1);
    cout << 2 * accumulate(phi + 1, phi + n + 1, 0) + 1;
    return 0;
}