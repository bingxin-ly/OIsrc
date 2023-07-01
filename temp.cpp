#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 10;
int n, m, Q, x, y;
struct FHQ
{
    int tot;
    int stk[N], top = 0, last;
    int root[N], Root;

    struct Tree
    {
        int L, R, key;  // 左右断电
        int l, r, size; // 值域
    } tr[N << 1];

    inline void update(int x)
    {
        tr[x].size = tr[tr[x].L].size + tr[tr[x].R].size + tr[x].r - tr[x].l + 1;
    }

    inline void get_size(int pos)
    {
        if (tr[pos].L)
            get_size(tr[pos].L);
        if (tr[pos].R)
            get_size(tr[pos].R);
        update(pos);
    }

    inline void build()
    {
        for (int i = 1; i <= n; i++)
        {
            root[i] = i;
            tr[++tot] = (Tree){0, 0, rand(), (i - 1) * m + 1, i * m - 1, m - 1};
        }

        for (int i = 1; i <= n; i++)
        {
            tr[++tot] = (Tree){0, 0, rand(), i * m, i * m, 1};
            last = 0;
            while (top && tr[tot].key > tr[stk[top]].key)
                last = stk[top--];
            tr[tot].L = last;
            tr[stk[top]].R = tot;
            stk[++top] = tot;
        }
        Root = stk[1];
        get_size(Root);
    }

    inline void splitl(int pos, int k, int &x, int &y)
    {
        if (!pos)
        {
            x = y = 0;
            return;
        }
        if (k <= tr[tr[pos].L].size + tr[pos].r - tr[pos].l + 1)
        {
            y = pos;
            splitl(tr[pos].L, k, x, tr[pos].L);
        }
        else
        {
            x = pos;
            splitl(tr[pos].R, k - (tr[tr[pos].L].size + tr[pos].r - tr[pos].l + 1), tr[pos].R, y);
        }
        update(pos);
    }

    inline void splitr(int pos, int k, int &x, int &y)
    {
        if (!pos)
        {
            x = y = 0;
            return;
        }
        if (k <= tr[tr[pos].L].size)
        {
            y = pos;
            splitr(tr[pos].L, k, x, tr[pos].L);
        }
        else
        {
            x = pos;
            splitr(tr[pos].R, k - (tr[tr[pos].L].size + tr[tr[pos].L].r - tr[tr[pos].L].l + 1), tr[pos].R, y);
        }
        update(pos);
    }

    inline int merge(int x, int y)
    {
        if (!(x && y))
            return x | y;
        if (tr[x].key > tr[y].key)
        {
            tr[x].R = merge(tr[x].R, y);
            update(x);
            return x;
        }
        else
        {
            tr[y].L = merge(x, tr[y].L);
            update(y);
            return y;
        }
    }

    inline void splitTree(int p, int k, int &L, int &M, int &R)
    {
        L = M = R = 0;
        if (k > 1)
        {
            tr[++tot] = (Tree){0, 0, rand(), tr[p].l, tr[p].l + k - 2, k - 1};
            L = tot;
        }
        if (k < tr[p].size)
        {
            tr[++tot] = (Tree){0, 0, rand(), tr[p].l + k, tr[p].r, tr[p].r - tr[p].l - k + 1};
            R = tot;
        }
        tr[++tot] = (Tree){0, 0, rand(), tr[p].l + k - 1, tr[p].l + k - 1, 1};
        M = tot;
    }

} fhq;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> Q;

    fhq.build();
    for (int i = 1; i <= Q; i++)
    {
        cin >> x >> y;
        if (y != m)
        {
            int a, b, c, d, e, f, g; // 直接拆
            fhq.splitl(fhq.root[x], y, a, b);
            fhq.splitr(b, 1, b, c);
            fhq.splitTree(b, y - fhq.tr[a].size, d, e, f);

            cout << (fhq.tr[e].l) << '\n';

            a = fhq.merge(a, d); // 得合上
            c = fhq.merge(f, c);

            fhq.splitl(fhq.Root, x, d, f); // 然后再更新
            fhq.splitr(f, 1, f, g);
            fhq.root[x] = fhq.merge(fhq.merge(a, c), f);
            fhq.Root = fhq.merge(fhq.merge(d, g), e);
        }

        else // 特殊情况特殊处理
        {
            int a, b, c;

            fhq.splitl(fhq.Root, x, a, b);
            fhq.splitr(b, 1, b, c);

            cout << (fhq.tr[b].l) << '\n';

            fhq.Root = fhq.merge(fhq.merge(a, c), b);
        }
    }

    return 0;
}