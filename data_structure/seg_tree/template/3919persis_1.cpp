#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, m, arr[N];
struct {
    int ls, rs, val;
} t[N << 5];
int idx, rt[N];

void build(int &p, int l, int r) {
    p = ++idx;
    if (l == r) return t[p].val = arr[l], void();
    int mid = (l + r) >> 1;
    build(t[p].ls, l, mid), build(t[p].rs, mid + 1, r);
}
int pos, val;
void modify(int &p, int l, int r) {
    t[++idx] = t[p], p = idx;
    if (l == r) return t[p].val = val, void();
    int mid = (l + r) >> 1;
    if (pos <= mid)
        modify(t[p].ls, l, mid);
    else
        modify(t[p].rs, mid + 1, r);
}
int query(int p, int l, int r) {
    if (l == r) return t[p].val;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return query(t[p].ls, l, mid);
    else
        return query(t[p].rs, mid + 1, r);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(rt[0], 1, n);

    for (int i = 1, ver, op; i <= m; i++) {
        cin >> ver >> op >> pos;
        if (op == 1)
            cin >> val, modify(rt[i] = rt[ver], 1, n);
        else
            cout << query(rt[i] = rt[ver], 1, n) << '\n';
    }
    return 0;
}