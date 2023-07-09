#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\.in");
ofstream fout("D:\\OIsrc\\.out");
#define cin fin
#define cout fout
#undef endl
#endif

constexpr int N = 2e5 + 5;
int n, idx;
long long u, v, ans;
struct
{
    int ls, rs, sum;
} t[N * 20];
void pushup(int p) { t[p].sum = t[t[p].ls].sum + t[t[p].rs].sum; }
int build(int l, int r, int pos)
{
    int p = ++idx;
    if (l == r)
        return t[p].sum += 1, p;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        t[p].ls = build(l, mid, pos);
    else
        t[p].rs = build(mid + 1, r, pos);
    pushup(p);
    return p;
}
int merge(int p, int q, int l, int r)
{
    if (!p || !q)
        return p | q;
    u += 1ll * t[t[p].rs].sum * t[t[q].ls].sum;
    v += 1ll * t[t[p].ls].sum * t[t[q].rs].sum;
    int mid = (l + r) >> 1;
    t[p].ls = merge(t[p].ls, t[q].ls, l, mid);
    t[p].rs = merge(t[p].rs, t[q].rs, mid + 1, r);
    pushup(p);
    return p;
}
// 不用显式建出来树……一个节点只关心左右儿子。吐血，我还开了两棵树，活生生写成树套树
int input()
{
    int x;
    if (cin >> x, x)
        return build(1, n, x);
    int ls = input(), rs = input(), p;
    u = v = 0, p = merge(ls, rs, 1, n);
    ans += min(u, v);
    return p;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    input();
    cout << ans;
    return 0;
}