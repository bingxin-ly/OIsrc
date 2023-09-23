#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9, P = 131;
char s[N];
unsigned long long h[N], p[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> (s + 1), n = strlen(s + 1), p[0] = 1;
    for (int i = 1; i <= n; i++) h[i] = h[i - 1] * P + (s[i] - 'a' + 1), p[i] = p[i - 1] * P;
    cin >> m;
    for (int l1, r1, l2, r2; m--;) {
        cin >> l1 >> r1 >> l2 >> r2;
        cout << (h[r1] - h[l1 - 1] * p[r1 - l1 + 1] == h[r2] - h[l2 - 1] * p[r2 - l2 + 1]
                     ? "Yes\n"
                     : "No\n");
    }
    return 0;
}