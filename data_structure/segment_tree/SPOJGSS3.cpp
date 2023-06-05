#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10, M = N * 5;
int arr[N], sum[M], v[M], lv[M], rv[M];

void copy(int p, int f) { sum[p] = sum[f], lv[p] = lv[f], rv[p] = rv[f], v[p] = v[f]; }
void pushup(int p, int ls, int rs)
{
    if (!ls || !rs)
        copy(p, ls ? ls : rs);
    sum[p] = sum[ls] + sum[rs];

    lv[p] = max(lv[ls], sum[ls] + lv[rs]);
    rv[p] = max(rv[ls] + sum[rs], rv[rs]);
    v[p] = max({v[ls], rv[ls] + lv[rs], v[rs]});
}
#define ls p << 1
#define rs p << 1 | 1
void build(int p, int l, int r)
{
    if (l == r)
        return sum[p] = v[p] = lv[p] = rv[p] = arr[l], void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p, ls, rs);
}
void modify(int p, int l, int r, int pos, int x)
{
    if (l == r)
        return sum[p] = v[p] = lv[p] = rv[p] = x, void();

    int mid = (l + r) >> 1;
    if (pos <= mid)
        modify(ls, l, mid, pos, x);
    else
        modify(rs, mid + 1, r, pos, x);
    pushup(p, ls, rs);
}
int cnt;
int query(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return p;

    int mid = (l + r) >> 1;
    int ret = ++cnt, lt = 0, rt = 0;
    if (ql <= mid)
        lt = query(ls, l, mid, ql, qr);
    if (qr > mid)
        rt = query(rs, mid + 1, r, ql, qr);
    pushup(ret, lt, rt);
    return ret;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, q;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    build(1, 1, n);

    cin >> q;
    for (int op, x, y; q--;)
    {
        cin >> op >> x >> y;
        if (!op)
            modify(1, 1, n, x, y);
        else
            cnt = N << 2, cout << v[query(1, 1, n, x, y)] << endl;
    }
    return 0;
}