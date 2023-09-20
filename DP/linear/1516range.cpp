#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, k, l[N], r[N], w[N];
long long sum, f[N];
vector<int> num, itv[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i] >> w[i], sum += w[i];
        num.emplace_back(l[i]), num.emplace_back(r[i]);
    }
    sort(num.begin(), num.end()), num.erase(unique(num.begin(), num.end()), num.end());
    for (int i = 1; i <= n; i++) {
        l[i] = lower_bound(num.begin(), num.end(), l[i]) - num.begin() + 1;
        r[i] = lower_bound(num.begin(), num.end(), r[i]) - num.begin() + 1;
        itv[l[i]].emplace_back(i);
    }
    n = num.size();
    for (int i = 1; i <= n; i++) {
        long long res = 0;
        priority_queue<int, vector<int>, greater<> > q;
        for (int j = i; j; j--) {
            for (int v : itv[j]) {
                if (r[v] <= i) q.emplace(w[v]), res += w[v];
                if (q.size() > k) res -= q.top(), q.pop();
            }
            f[i] = max(f[i], f[j - 1] + res);
        }
        f[i] = max(f[i], f[i - 1]);
    }
    cout << sum - f[n];
    return 0;
}