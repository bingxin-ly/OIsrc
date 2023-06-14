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
struct node
{
    node *ls, *rs;
    long long val, sum;
    int size, pri;

    explicit node(int x) : size(1)
    {
        val = sum = x;
        ls = rs = nullptr;
        pri = rand();
    }
} *root;

void update(node *u)
{
    u->size = (u->ls ? u->ls->size : 0) + (u->rs ? u->rs->size : 0) + 1;
    u->sum = (u->ls ? u->ls->sum : 0) + (u->rs ? u->rs->sum : 0) + u->val;
}

// 权值分裂
void split(node *u, int x, node *&L, node *&R)
{
    if (!u)
        return L = R = nullptr, void();
    if (u->val <= x)
    {
        L = u;
        split(u->rs, x, u->rs, R);
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
        L->rs = merge(L->rs, R);
        update(L);
        return L;
    }
    else
    {
        R->ls = merge(L, R->ls);
        update(R);
        return R;
    }
}

void insert(int x)
{
    node *L, *R;
    split(root, x, L, R);
    root = merge(merge(L, new node(x)), R);
}

void del(int x)
{
    node *L, *R, *p;
    split(root, x, L, R);
    split(L, x - 1, L, p);
    p = merge(p->ls, p->rs);
    root = merge(merge(L, p), R);
}

int main()
{
    int n = read(), m = read();
    vector<int> ori(n);
    while (n--)
        root = merge(root, new node(0));

    while (m--)
    {
        char op;
        scanf("%s", &op);
        long long a = read(), b = read();
        node *p, *L, *R;
        if (op == 'U')
        {
            del(ori[a - 1]);
            insert(ori[a - 1] = b);
        }
        else
        {
            split(root, b, L, R), split(L, 0, L, p);
            printf("%s\n", (p ? p->sum : 0) >= b * (a - (R ? R->size : 0)) ? "TAK" : "NIE");
            root = merge(merge(L, p), R);
        }
    }
    return 0;
}