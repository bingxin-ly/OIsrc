#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\.in");
ofstream fout("D:\\OIsrc\\.out");
#define cin fin
#define cout fout
#endif
#define int long long

constexpr int N = 2e5 + 5;
int n, f, arr[N];
struct segtr
{
    int val, tag;
} t[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
inline void pushup(int p)
{
    t[p].val = t[ls].val + t[rs].val;
}
inline void pushdown(int p, int l, int r)
{
    if (t[p].tag)
    {
        int mid = (l + r) >> 1;
        t[ls].val += (mid - l + 1) * t[p].tag, t[ls].tag += t[p].tag;
        t[rs].val += (r - mid) * t[p].tag, t[rs].tag += t[p].tag;
        t[p].tag = 0;
    }
}
void build(int p, int l, int r)
{
    if (l == r)
        return t[p].val = arr[l], void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p);
}
int ql, qr, v;
void change(int p, int l, int r)
{
    if (ql <= l && r <= qr)
        return t[p].tag += v, t[p].val += (r - l + 1) * v, void();
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        change(ls, l, mid);
    if (qr > mid)
        change(rs, mid + 1, r);
    pushup(p);
}
int query(int p, int l, int r)
{
    if (ql <= l && r <= qr)
        return t[p].val;
    pushdown(p, l, r);
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid)
        res += query(ls, l, mid);
    if (qr > mid)
        res += query(rs, mid + 1, r);
    pushup(p);
    return res;
}
void inorder(int p, int l, int r)
{
    if (l == r)
        return cout << l << '-' << r << ' ' << t[p].val << endl, void();
    int mid = (l + r) >> 1;
    inorder(ls, l, mid);
    cout << l << '-' << r << ' ' << t[p].val << endl;
    inorder(rs, mid + 1, r);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> f;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    build(1, 1, n);
    for (int op; f--;)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> ql >> qr >> v;
            change(1, 1, n);
            break;
        case 2:
            cin >> v, ql = qr = 1;
            change(1, 1, n);
            break;
        case 3:
            cin >> v, ql = qr = 1, v = -v;
            // 减少 k，人家说的可还是正数啊
            change(1, 1, n);
            break;
        case 4:
            cin >> ql >> qr;
            cout << query(1, 1, n) << '\n';
            break;
        case 5:
            ql = qr = 1;
            cout << query(1, 1, n) << '\n';
            break;
        }
    }
    return 0;
}