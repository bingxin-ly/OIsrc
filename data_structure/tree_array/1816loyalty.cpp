#include <bits/stdc++.h>
using namespace std;

// 使用树状数组计算区间最小值~
const int N = 1e5 + 10;
int n, src[N], tr[N];

inline int lowbit(int x) { return x & -x; }
void modify(int p, int x)
{
    for (; tr[p] > x && p <= n; p += lowbit(p))
        tr[p] = x;
}
int query(int l, int r)
{
    if (l == r)
        return src[l];
    if (r - lowbit(r) > l)
        return min(query(l, r - lowbit(r)), tr[r]);
    else
        return min(query(l, r - 1), src[r]);
}

signed main()
{
    memset(tr, 0x7f, sizeof tr);
    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> src[i], modify(i, src[i]);
    for (int l, r; m--;)
        cin >> l >> r, cout << query(l, r) << ' ';
    return 0;
}