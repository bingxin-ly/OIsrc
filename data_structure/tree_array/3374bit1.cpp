#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, m, a[N], s[N], t[N];
void build_t() {
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + a[i];
        t[i] = s[i] - s[i - (i & -i)];
        /* 求原数组前缀和，再更新树状数组 O(n) */
    }
}
void build_m() {
    for (int i = 1; i <= n; i++) {
        t[i] += a[i];
        int j = i + (i & -i);
        if (j <= n)
            t[j] += t[i];
        /*每一个节点的值是由所有与自己直接相连的儿子的值求和得到的。
        因此可以倒着考虑贡献，即每次确定完儿子的值后，用自己的值更新自己的直接父亲*/
    }
}
void insert(int p, int v) {
    while (p <= n) t[p] += v, p += p & -p;
}
int presum(int p) {
    int r = 0;
    while (p) r += t[p], p -= p & -p;
    return r;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) cin >> x, insert(i, x);
    for (int o, x, y; m--;) {
        cin >> o >> x >> y;
        if (o == 1)
            insert(x, y);
        else
            cout << presum(y) - presum(x - 1) << '\n';
    }
    return 0;
}