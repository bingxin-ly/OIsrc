#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 9;
int n, a[N], m, b[N], c[N], I[N], w[3 * N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (int i = (cin >> n, 1); i <= n; i++) cin >> a[i];
    for (int i = (cin >> m, 1); i <= m; i++) cin >> b[i];
    for (int i = 1; i <= m; i++) cin >> c[i];
    vector<int> v(n + 2 * m);
    memcpy(&v[0], a + 1, n << 2), memcpy(&v[n], b + 1, m << 2),
        memcpy(&v[n + m], c + 1, m << 2);
    sort(v.begin(), v.end()), v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    for (int i = 1; i <= m; i++)
        b[i] = lower_bound(v.begin(), v.end(), b[i]) - v.begin() + 1;
    for (int i = 1; i <= m; i++)
        c[i] = lower_bound(v.begin(), v.end(), c[i]) - v.begin() + 1;
    for (int i = 1; i <= n; i++) w[a[i]]++;
    int i = 1;
    for (int j = 2; j <= m; j++)
        if (w[b[j]] > w[b[i]] || (w[b[j]] == w[b[i]] && w[c[j]] > w[c[i]])) i = j;
    cout << i;
    return 0;
}