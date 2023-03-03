// 区间乘区间加线段树
#include <bits/stdc++.h>
#define ls (node << 1)
#define rs (node << 1 | 1)
using namespace std;

const int MAX = 1e5 + 10;
int n, m, p, src[MAX];
size_t segtr[4 * MAX];
size_t addtg[MAX], multg[MAX];

inline void push_up(int node) // 也可以理解成push_to_here,值的简单加和
{
    segtr[node] = segtr[ls] + segtr[rs];
}
void build(int node, int l, int r)
{
    addtg[node] = 0, multg[node] = 1;
    if (l == r)
        segtr[node] = src[l];
    else
    {
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        push_up(node);
    }
    segtr[node] %= p;
}
void push_down(int node, int l, int r)
{
    int mid = (l + r) >> 1;
    {
        // 更新线段树上的值
        // 儿子的值=此刻儿子的值*爸爸的乘法lazytag+儿子的区间长度*爸爸的加法
        segtr[ls] = (segtr[ls] * multg[node] + addtg[node] * (mid - l + 1)) % p;
        segtr[rs] = (segtr[rs] * multg[node] + addtg[node] * (r - mid)) % p;
    }
    // 重新维护一遍lazytag
    {
        // 乘法
        multg[ls] = (multg[ls] * multg[node]) % p;
        multg[rs] = (multg[rs] * multg[node]) % p;
    }
    {
        // 加法
        addtg[ls] = (addtg[ls] * multg[node] + addtg[node]) % p;
        addtg[rs] = (addtg[rs] * multg[node] + addtg[node]) % p;
    }
    multg[node] = 1, addtg[node] = 0;
}
size_t query(int ql, int qr, int node = 1, int l = 1, int r = n) // 区间查询
{
    if (l > qr || r < ql)
        return 0;
    if (ql <= l && r <= qr)
        return segtr[node];
    push_down(node, l, r);
    int mid = (l + r) >> 1;
    return query(ql, qr, ls, l, mid) + query(ql, qr, rs, mid + 1, r);
}
/*void add(int ql, int qr, int val, int node = 1, int l = 1, int r = n) // 区间加
{
    if (l > qr || r < ql)
        return;
    if (ql <= l && r <= qr)
    {
        addtg[node] += val, segtr[node] += (r - l + 1) * val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) >> 1;
    add(ql, qr, val, ls, l, mid), add(ql, qr, val, rs, mid + 1, r);
    push_up(node);
}*/
void add(int node, int l, int r, int stdl, int stdr, long long k)
{
    if (r < stdl || stdr < l)
    {
        return;
    }
    if (l <= stdl && stdr <= r)
    {
        addtg[node] = (addtg[node] + k) % p;
        segtr[node] = (segtr[node] + k * (stdr - stdl + 1)) % p;
        return;
    }
    push_down(node, stdl, stdr);
    int m = (stdl + stdr) / 2;
    add(node * 2, l, r, stdl, m, k);
    add(node * 2 + 1, l, r, m + 1, stdr, k);
    segtr[node] = (segtr[ls] + segtr[rs]) % p;
    return;
}
inline void add_single(int qpoint, int val, int node = 1, int gl = 1, int gr = n) // 单点加
{
    add(qpoint, qpoint, val, node, gl, gr);
}
void multiply(int node, int ql, int qr, int l, int r, int val)
{
    if (qr < l || r < ql)
        return;
    if (ql <= l && r <= qr)
    {
        segtr[node] = (segtr[node] * val) % p;
        multg[node] = (multg[node] * val) % p;
        addtg[node] = (addtg[node] * val) % p;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) >> 1;
    multiply(ls, ql, qr, l, mid, val), multiply(rs, ql, qr, mid + 1, r, val);
    // add(ql, qr, val, ls, l, mid), add(ql, qr, val, rs, mid + 1, r);
    push_up(node);
    segtr[node] %= p;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++)
        cin >> src[i];
    build(1, 1, n);
    int op, a, b, c;
    while (m--)
    {
        int chk;
        scanf("%d", &chk);
        int x, y;
        long long k;
        if (chk == 1)
        {
            scanf("%d%d%lld", &x, &y, &k);
            multiply(1, 1, n, x, y, k);
        }
        else if (chk == 2)
        {
            scanf("%d%d%lld", &x, &y, &k);
            add(1, 1, n, x, y, k);
        }
        else
        {
            scanf("%d%d", &x, &y);
            printf("%lld\n", query(1, 1, n, x, y));
        }
    }
    return 0;
}