#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, a[N], idx, rt[N];
struct {
    int ls, rs, val;
} t[N * 18];

void insert(int &p, int l, int r, int pos, int dlt) {
    t[++idx] = t[p], p = idx;
    if (l == r) return t[p].val += dlt, void();
    int mid = (l + r) >> 1;
    if (pos <= mid)
        insert(t[p].ls, l, mid, pos, dlt);
    else
        insert(t[p].rs, mid + 1, r, pos, dlt);
    t[p].val = t[t[p].ls].val + t[t[p].rs].val;
}
int query(int p, int q, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int lsiz = t[t[p].ls].val - t[t[q].ls].val;
    if (k <= lsiz)
        return query(t[p].ls, t[q].ls, l, mid, k);
    else
        return query(t[p].rs, t[q].rs, mid + 1, r, k - lsiz);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    vector<int> b;
    for (int i = 1; i <= n; i++) cin >> a[i], b.emplace_back(a[i]);
    sort(b.begin(), b.end()), b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
        insert(rt[i] = rt[i - 1], 1, b.size(), a[i], 1);
    }
    for (int i = 1, l, r, k; i <= m; i++) {
        cin >> l >> r >> k;
        cout << b[query(rt[r], rt[l - 1], 1, b.size(), k) - 1] << '\n';
    }
    return 0;
}