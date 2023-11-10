#include <bits/stdc++.h>
#define lb(x) lower_bound(num.begin(), num.end(), x) - num.begin() + 1
using namespace std;

constexpr int N = 1e4 + 9;
int m, a[N][3], fa[N], d[N];
int get(int x) {
    if (x == fa[x]) return x;
    int r = get(fa[x]);
    return d[x] ^= d[fa[x]], fa[x] = r;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m >> m;
    vector<int> num;
    for (int i = 1, l, r; i <= m; i++) {
        string s;
        cin >> l >> r >> s;
        num.emplace_back(a[i][0] = l - 1);
        num.emplace_back(a[i][1] = r);
        a[i][2] = s == "odd";
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    iota(fa + 1, fa + num.size() + 1, 1);
    for (int i = 1; i <= m; i++) {
        int x = lb(a[i][0]), y = lb(a[i][1]), p = get(x), q = get(y);
        if (p == q) {
            if (a[i][2] != d[x] ^ d[y]) return cout << i - 1, 0;
        } else {
            fa[p] = q, d[p] = d[x] ^ d[y] ^ a[i][2];
        }
    }
    cout << m;
    return 0;
}