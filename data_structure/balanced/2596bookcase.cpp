#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 10;
int n, m;
struct node
{
    int l, r;
    int siz, key, val;
    int fa;
} t[N];
int cnt, root;

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
}

inline int create(int val)
{
    t[++cnt].siz = 1;
    t[cnt].key = rand();
    t[cnt].val = val;
    return cnt;
}

inline int merge(int x, int y)
{
    if (!x || !y)
        return x | y;
    if (t[x].key < t[y].key)
    {
        t[x].r = merge(t[x].r, y);
        t[t[x].r].fa = x;
        pushup(x);
        return x;
    }
    else
    {
        t[y].l = merge(x, t[y].l);
        t[t[y].l].fa = y;
        pushup(y);
        return y;
    }
}

inline void split(int p, int siz, int &x, int &y, int faa = 0, int fab = 0)
{
    if (!p)
        return x = y = 0, void();
    if (t[t[p].l].siz + 1 > siz)
    {
        t[p].fa = fab;
        y = p;
        split(t[p].l, siz, x, t[y].l, faa, p);
    }
    else
    {
        t[p].fa = faa;
        x = p;
        split(t[p].r, siz - t[t[p].l].siz - 1, t[x].r, y, p, fab);
    }
    pushup(p);
}

inline int find(int x)
{
    int p = x, res = t[t[x].l].siz + 1;
    while (p != root && x)
    {
        if (t[t[p].fa].r == p)
            res += t[t[t[p].fa].l].siz + 1;
        p = t[p].fa;
    }
    return res;
}

int pos[N];

int main()
{
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        root = merge(root, create(x));
        pos[x] = i;
    }

    int s, tt, x, y, z, x1, y1;
    while (m--)
    {
        char op[10];
        scanf("%s%d", op, &s);
        if (op[0] == 'T')
        {
            int rk = find(pos[s]);
            split(root, rk - 1, x, y);
            split(y, 1, y, z);
            root = merge(merge(y, x), z);
        }
        else if (op[0] == 'B')
        {
            int rk = find(pos[s]);
            split(root, rk - 1, x, y);
            split(y, 1, y, z);
            root = merge(merge(x, z), y);
        }
        else if (op[0] == 'I')
        {
            cin >> tt;
            int rk = find(pos[s]);
            split(root, rk - 1, x, y);
            split(y, 1, y, z);
            root = merge(x, z);
            split(root, rk + tt - 1, x1, y1);
            root = merge(merge(x1, y), y1);
        }
        else if (op[0] == 'A')
        {
            int rk = find(pos[s]);
            printf("%d\n", rk - 1);
        }
        else
        {
            split(root, s - 1, x, y);
            split(y, 1, y, z);
            printf("%d\n", t[y].val);
            root = merge(merge(x, y), z);
        }
    }
    return 0;
}