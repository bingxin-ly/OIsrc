// 区间加线段树
#include <bits/stdc++.h>
#define ls (node << 1)
#define rs (node << 1 | 1)
using namespace std;

const int MAX = 5e4 + 10;
int n, m;
size_t segtr[4 * MAX], lazy[MAX];

inline void push_up(int node) // 也可以理解成push_to_here
{
    segtr[node] = segtr[ls] + segtr[rs];
}
void build(int node, int l, size_t r)
{
    if (l == r)
    {
        segtr[node] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    push_up(node);
}
void push_down(int l, size_t r, int node)
{
    segtr[ls] = segtr[rs]  = 0;
    // lazy[ls] += lazy[node], lazy[rs] += lazy[node];
    // int mid = (l + r) >> 1;
    // segtr[ls] += (mid - l + 1) * lazy[node], segtr[rs] += (r - mid) * lazy[node];
    // lazy[node] = 0;
}
size_t query(int len, int node = 1, int l = 1, size_t r = n) // 区间查询
{
    if (segtr[node] >= len)
        return r;
    push_down(l, r, node);
    int mid = (l + r) >> 1;
    return query(len - segtr[node], rs, mid + 1, r);
}
void add(int ql, size_t qr, int val, int node = 1, int gl = 1, size_t gr = n) // 区间加
{
    if (gl > qr || gr < ql)
        return;
    if (ql <= gl && gr <= qr)
    {
        lazy[node] += val, segtr[node] += (gr - gl + 1) * val;
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

void modify(int l, int r, int node = 1, int gl = 1, size_t gr = n)
{
    if (segtr[node] <= r - l + 1)
    {
        lazy[node] = 0, segtr[node] -= r - l + 1;
        return;
    }
    push_down(gl, gr, node);

}
void quit(int l, int len)
{
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    build(1, 1, n);
    int op, a, b;
    while (m--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> a;
            int len = a, r = query(a), l = query(a) - a + 1;
            cout << l << endl;
            modify(l, r);
        }
        else
            cin >> a >> b,
                quit(a, b);
    }
    return 0;
}