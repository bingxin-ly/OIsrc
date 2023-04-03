#include <bits/stdc++.h>
#define ls (rt << 1)
#define rs ((rt << 1) | 1)
typedef long long ll;
using namespace std;

const int N = 1e5 + 10;
ll arr[N], segtr[4 * N], lazy[4 * N];
void pushup(int rt) { segtr[rt] = segtr[ls] + segtr[rs]; }
void pushdown(int rt, int l, int r)
{
    int mid = (l + r) >> 1;
    segtr[ls] += (mid - l + 1) * lazy[rt], segtr[rs] += (r - mid) * lazy[rt];

    lazy[ls] += lazy[rt], lazy[rs] += lazy[rt];
    lazy[rt] = 0;
}

void build(int rt, int l, int r)
{
    if (l == r)
       return segtr[rt] = arr[l], void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(rt);
}
ll query(int rt, int l, int r, const int ll, const int rr)
{
    if (l > rr || r < ll)
        return 0;
    if (ll <= l && r <= rr)
        return segtr[rt];

    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    return query(ls, l, mid, ll, rr) + query(rs, mid + 1, r, ll, rr);
}
void modify(int rt, int l, int r, const int ll, const int rr, const int val)
{
    if (l > rr || r < ll)
        return;
    if (ll <= l && r <= rr)
    {
        segtr[rt] += (r - l + 1) * val;
        lazy[rt] += val;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    modify(ls, l, mid, ll, rr, val), modify(rs, mid + 1, r, ll, rr, val);
    pushup(rt);
}

int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    build(1, 1, n);
    for (int i = 1, op; i <= m; i++)
    {
        cin >> op;
        int x, y, k;
        if (op == 1)
        {
            cin >> x >> y >> k;
            modify(1, 1, n, x, y, k);
        }
        else
        {
            cin >> x >> y;
            cout << query(1, 1, n, x, y) << endl;
        }
    }
    return 0;
}