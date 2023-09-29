#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, cnt[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n / i; j++) cnt[i * j] += 1;
    cout << accumulate(cnt + 1, cnt + n + 1, 0ll);
    return 0;
}