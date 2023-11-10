#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 9;
long long n, q, f[N], g[N];
stack<int> s;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        if (c == '(')
            s.emplace(i);
        else if (!s.empty())
            f[i] = f[s.top() - 1] + 1, s.pop();
        g[i] = g[i - 1] + f[i];
    }
    for (int l, r; q--;) {
        cin >> l >> l >> r;
        cout << g[r] - g[l - 1] - f[l - 1] * (f[r] - f[l - 1]) << '\n';
    }
    return 0;
}