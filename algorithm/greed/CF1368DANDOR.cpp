#include <bits/stdc++.h>
using namespace std;

int n, b[20];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        for (int j = 0; j < 20; j++) b[j] += a >> j & 1;
    }
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        long long ans = 0;
        for (int j = 0; j < 20; j++)
            if (b[j]) b[j] -= 1, ans += 1 << j;
        res += ans * ans;
    }
    cout << res;
    return 0;
}