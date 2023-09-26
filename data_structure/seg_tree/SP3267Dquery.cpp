#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e4 + 9;
struct {
    int ls, rs, val;
} t[N << 5];
int n, m, a[N], idx, rot[N], pre[N];

void update(int &p, int l, int r, int x, int v) {
    t[++idx] = t[p], p = idx;
    if (l == r) return t[p].val += v, void();
    int mid = (l + r) >> 1;
    if (x <= mid)
        update(t[p].ls, l, mid, x, v);
    else
        update(t[p].rs, mid + 1, r, x, v);
    t[p].val = t[t[p].ls].val + t[t[p].rs].val;
}
int query(int p, int l, int r, int x) {
    if (l == r) return t[p].val;
    int mid = (l + r) >> 1;
    if (x <= mid)
        return t[t[p].rs].val + query(t[p].ls, l, mid, x);
    else
        return query(t[p].rs, mid + 1, r, x);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> nums(a + 1, a + n + 1);
    sort(nums.begin(), nums.end()), nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin() + 1;
        rot[i] = rot[i - 1];
        if (pre[a[i]])
            update(rot[i], 1, n, pre[a[i]], -1);
        update(rot[i], 1, n, pre[a[i]] = i, 1);
    }

    cin >> m;
    for (int l, r; m--;)
        cin >> l >> r, cout << query(rot[r], 1, n, l) << '\n';
    return 0;
}