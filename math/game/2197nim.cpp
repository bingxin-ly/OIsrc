#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T, n, a, b;
    for (cin >> T; T; T--) {
        cin >> n >> a;
        while (--n) cin >> b, a ^= b;
        cout << (a ? "Yes\n" : "No\n");
    }
    return 0;
}