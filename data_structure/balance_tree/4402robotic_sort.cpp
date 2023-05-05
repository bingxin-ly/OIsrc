// P4402 & P3165 & UVA1402 & SPOJ-CERC07S
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

const int INF = 0x3fffffff, N = 1e6 + 10;
struct node
{
    node *ls, *rs;
    int val, minn;
    int pri, size, lazy;

    explicit node(int x) : size(1), lazy(0)
    {
        ls = rs = nullptr;
        val = minn = x;
        pri = rand();
    }
} *root;

void update(node *u)
{
    u->size = (u->ls ? u->ls->size : 0) + (u->rs ? u->rs->size : 0) + 1;
    u->minn = min(min(u->ls ? u->ls->minn : INF, u->rs ? u->rs->minn : INF), u->val);
}

void pushdown(node *u)
{
    if (u->lazy)
    {
        swap(u->ls, u->rs);
        if (u->ls)
            u->ls->lazy ^= 1;
        if (u->rs)
            u->rs->lazy ^= 1;
        u->lazy = 0;
    }
}

// 排名分裂
void split(node *u, int x, node *&L, node *&R)
{
    if (!u)
        return L = R = nullptr, void();
    pushdown(u);
    int less = (u->ls ? u->ls->size : 0) + 1;
    if (less <= x)
    {
        L = u;
        split(u->rs, x - less, u->rs, R);
    }
    else
    {
        R = u;
        split(u->ls, x, L, u->ls);
    }
    update(u);
}

node *merge(node *L, node *R)
{
    if (!L || !R)
        return L ? L : R;
    if (L->pri > R->pri)
    {
        pushdown(L);
        L->rs = merge(L->rs, R);
        update(L);
        return L;
    }
    else
    {
        pushdown(R);
        R->ls = merge(L, R->ls);
        update(R);
        return R;
    }
}

int fnd(node *u, int minn, int cnt)
{
    pushdown(u);
    if ((u->ls ? u->ls->minn : INF) > minn &&
        (u->rs ? u->rs->minn : INF) > minn)
        return cnt + (u->ls ? u->ls->size : 0) + 1;
    else if ((u->ls ? u->ls->minn : INF) < (u->rs ? u->rs->minn : INF))
        return fnd(u->ls, minn, cnt);
    else
        return fnd(u->rs, minn, cnt + (u->ls ? u->ls->size : 0) + 1);
}

void inorder(node *u)
{
    if (!u)
        return;
    pushdown(u);
    inorder(u->ls);
    cout << u->val << ' ';
    inorder(u->rs);
}

int a[N], b[N], cnt[N];
int main()
{
    int n;
    while (cin >> n, n)
    {
        memset(b, 0, sizeof(b)), memset(a, 0, sizeof(a)), memset(cnt, 0, sizeof(cnt)), root = nullptr;
        for (int i = 1; i <= n; i++)
            b[i] = a[i] = read();

        sort(b + 1, b + n + 1);
        for (int i = 1; i <= n; i++)
            a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b,
            a[i] += cnt[a[i]]++;
        for (int i = 1; i <= n; i++)
            root = merge(root, new node(a[i]));

        for (int i = 1; i <= n; i++)
        {
            int pos = fnd(root, root->minn, 0);
            node *p, *L, *R;
            split(root, pos, L, R), split(L, pos - 1, L, p);
            if (L)
                L->lazy ^= 1;
            root = merge(L, R);
            printf("%d%c", pos + i - 1, i == n ? '\n' : ' ');
        }
    }
    return 0;
}
