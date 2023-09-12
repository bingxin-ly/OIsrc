#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, w[N], c[N], q[N];
long long m, f[N];
multiset<long long> s;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        if (w[i] > m) return cout << -1, 0;
    }
    long long sum = 0;
    for (int i = 1, j = 0; i <= n; i++) {
        sum += w[i];
        while (sum > m) sum -= w[++j];
        c[i] = j;
    }
    int l = 1, r = 0;
    for (int i = 1; i <= n; i++) {
        while (l <= r && q[l] <= c[i]) {
            s.erase(f[q[l]] + w[q[l + 1]]);
            l++;
        }
        while (l <= r && w[q[r]] <= w[i]) {
            s.erase(f[q[r - 1]] + w[q[r]]);
            r--;
        }
        if (l <= r) s.insert(f[q[r]] + w[i]);
        q[++r] = i;
        f[i] = f[c[i]] + w[q[l]];
        if (!s.empty()) f[i] = min(f[i], *s.begin());
    }
    cout << f[n];
    return 0;
}