#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, a[N], t[N];
void add(int p, int v) {
    for (; p <= n; p += p & -p) t[p] += v;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 2; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        t[i] += 1;
        if (i + (i & -i) <= n) t[i + (i & -i)] += t[i];
    }
    for (int i = n; i >= 1; i--) {
        int pos = 0, sum = 0;
        for (int j = __lg(n); j >= 0; j--)
            if (pos + (1 << j) <= n && sum + t[pos + (1 << j)] <= a[i])
                sum += t[pos + (1 << j)], pos += 1 << j;
        a[i] = pos + 1, add(a[i], -1);
    }
    for (int i = 1; i <= n; i++) cout << a[i] << '\n';
    return 0;
}