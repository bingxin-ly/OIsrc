#include <bits/stdc++.h>
#define ls (rt << 1)
#define rs (rt << 1 | 1)
typedef long long loong;
using namespace std;

const int N = 1e5 + 10;
loong arr[N];
class seg_tree
{
    // loong segtr[4 * N], lazy[4 * N]; // crash in the win env
    loong *segtr = new loong[4 * N](), *lazy = new loong[4 * N]();
    void pushup(int rt) { segtr[rt] = segtr[ls] + segtr[rs]; }
    void pushdown(int rt, int l, int r)
    {
        int mid = (l + r) >> 1;
        segtr[ls] += (mid - l + 1) * lazy[rt], segtr[rs] += (r - mid) * lazy[rt];

        lazy[ls] += lazy[rt], lazy[rs] += lazy[rt];
        lazy[rt] = 0;
    }

public:
    void build(int rt, int l, int r)
    {
        if (l == r)
            return segtr[rt] = arr[l], void();
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        pushup(rt);
    }
    loong query(int rt, int l, int r, const int loong, const int rr)
    {
        if (l > rr || r < loong)
            return 0;
        if (loong <= l && r <= rr)
            return segtr[rt];

        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        return query(ls, l, mid, loong, rr) + query(rs, mid + 1, r, loong, rr);
    }
    void modify(int rt, int l, int r, const int loong, const int rr, const int val)
    {
        if (l > rr || r < loong)
            return;
        if (loong <= l && r <= rr)
        {
            segtr[rt] += (r - l + 1) * val;
            lazy[rt] += val;
            return;
        }
        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        modify(ls, l, mid, loong, rr, val), modify(rs, mid + 1, r, loong, rr, val);
        pushup(rt);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    seg_tree segt;
    segt.build(1, 1, n);
    for (int i = 1, op; i <= m; i++)
    {
        cin >> op;
        int x, y, k;
        if (op == 1)
        {
            cin >> x >> y >> k;
            segt.modify(1, 1, n, x, y, k);
        }
        else
        {
            cin >> x >> y;
            cout << segt.query(1, 1, n, x, y) << endl;
        }
    }
    return 0;
}