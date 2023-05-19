#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <bitset>
#define N 500003
#define M 20000003
#define inf 0x3f3f3f3f
#define int long long
using namespace std;

struct node
{
    int val, flag;
    node(int val = 0, int flag = 0) : val(val), flag(flag) {}
};

int a[N], phi[M], pr[M];
int n, q;
bitset<M> vis;

inline void read(int &x);
void print(int x);
inline node power(int a, int t, int p);
void init();
node solve(int l, int r, int p);
inline void add(int l, int r, int x);
inline void qwq(int i, int x);
inline int query(int i);
inline int lowbit(int x);

signed main()
{
    init();
    int l, r, op, x, t;
    node ans;
    read(n), read(q);
    for (int i = 1; i <= n; ++i)
    {
        read(t);
        add(i, i, t);
    }
    while (q--)
    {
        read(op), read(l), read(r), read(x);
        if (op == 1)
            add(l, r, x);
        else
        {
            ans = solve(l, r, x);
            print(ans.val);
            putchar('\n');
        }
    }
}

node solve(int l, int r, int p)
{
    int ph, al = query(l);
    node res;
    if (p == 1)
        return node(0, 1);
    if (al == 1)
        return node(1, 0);
    if (l == r)
        return al < p ? node(al, 0) : node(al % p, 1);
    ph = phi[p];
    res = solve(l + 1, r, ph);
    if (res.flag)
        res.val += ph;
    return power(al, res.val, p);
}

inline void init()
{
    int cnt = 0;
    phi[1] = 1;
    for (register int i = 2; i <= 20000000; ++i)
    {
        if (!vis[i])
        {
            pr[++cnt] = i;
            phi[i] = i - 1;
        }
        for (register int j = 1; j <= cnt; ++j)
        {
            int t = i * pr[j];
            if (t > 20000000)
                break;
            vis[t] = 1;
            if (i % pr[j] == 0)
            {
                phi[t] = phi[i] * pr[j];
                break;
            }
            phi[t] = phi[i] * (pr[j] - 1);
        }
    }
}

inline node power(int a, int t, int p)
{
    node res = node(1, 0);
    if (a >= p)
    {
        a %= p;
        res.flag = 1;
    }
    while (t)
    {
        if (t & 1)
            res.val *= a;
        if (res.val >= p)
        {
            res.flag = 1;
            res.val %= p;
        }
        a *= a;
        if (a >= p)
        {
            res.flag = 1;
            a %= p;
        }
        t >>= 1;
    }
    return res;
}

inline void read(int &x)
{
    x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
}

void print(int x)
{
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

inline void add(int l, int r, int x)
{
    qwq(l, x);
    qwq(r + 1, -x);
}

inline void qwq(int i, int x)
{
    while (i <= n)
    {
        a[i] += x;
        i += lowbit(i);
    }
}

inline int query(int i)
{
    int res = 0;
    while (i)
    {
        res += a[i];
        i -= lowbit(i);
    }
    return res;
}

inline int lowbit(int x)
{
    return x & (-x);
}
