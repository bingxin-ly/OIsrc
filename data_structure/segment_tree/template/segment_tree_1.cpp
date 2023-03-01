// 区间求和区间加
#include <bits/stdc++.h>
#define ls (node << 1)
#define rs (node << 1 | 1)
using namespace std;

const int MAX = 5e5 + 10;
int n, m, src[MAX];
size_t seg_tree[4 * MAX], lazy[MAX];

inline void push_up(int node) // 也可以理解成push_to_here
{
    seg_tree[node] = seg_tree[ls] + seg_tree[rs];
}
void build(int node, int l, size_t r)
{
    if (l == r)
    {
        seg_tree[node] = src[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    push_up(node);
}
void push_down(int l, size_t r, int node)
{
    lazy[ls] += lazy[node], lazy[rs] += lazy[node];
    int mid = (l + r) >> 1;
    seg_tree[ls] += (mid - l + 1) * lazy[node], seg_tree[rs] += (r - mid) * lazy[node];
    lazy[node] = 0;
}
size_t query(int ql, size_t qr, int node = 1, int ll = 1, size_t rr = n) // 区间查询
{
    if (ll > qr || rr < ql)
        return 0;
    if (ql <= ll && rr <= qr)
        return seg_tree[node];
    push_down(ll, rr, node);
    int mid = (ll + rr) >> 1;
    return query(ql, qr, ls, ll, mid) + query(ql, qr, rs, mid + 1, rr);
}
void add(int ql, size_t qr, int val, int node = 1, int gl = 1, size_t gr = n) // 区间加
{
    if (gl > qr || gr < ql)
        return;
    if (ql <= gl && gr <= qr)
    {
        lazy[node] += val, seg_tree[node] += (gr - gl + 1) * val;
        return;
    }
    push_down(gl, gr, node);
    int mid = (gl + gr) >> 1;
    add(ql, qr, val, ls, gl, mid), add(ql, qr, val, rs, mid + 1, gr);
    push_up(node);
}
inline void add_singal(int qpoint, int val, int node = 1, int gl = 1, size_t gr = n) // 单点加
{
    add(qpoint, qpoint, val, node, gl, gr);
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> src[i];
    build(1, 1, n);
    int op, a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> op;
        if (op == 1)
            cin >> a >> b >> c,
                add(a, b, c);
        else
            cin >> a >> b,
                cout << query(a, b) << endl;
    }
    return 0;
}