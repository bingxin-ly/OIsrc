#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int T, n, a[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (cin >> T; T--;) {
        cin >> n;
        for (int l = 1, r = 1; r <= n; r++) {
            cin >> a[r];
            while (a[l] < r - l + 1) l++;
            cout << r - l + 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}