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

struct mark
{
    int ACs, time;

    bool operator<(const mark &b) const
    {
        return ACs == b.ACs ? time < b.time : ACs > b.ACs;
    }
    bool operator<=(const mark &b) const
    {
        return ACs == b.ACs ? time <= b.time : ACs >= b.ACs;
    }
} people[100010];

struct node
{
    node *ls, *rs;
    mark val;
    int size, pri;

    explicit node(mark x) : val(x), size(1)
    {
        ls = rs = nullptr;
        pri = rand();
    }
} *root;

void update(node *u)
{
    u->size = (u->ls ? u->ls->size : 0) + (u->rs ? u->rs->size : 0) + 1;
}

void split(node *u, mark x, node *&L, node *&R)
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
void insert(mark x)
{
    node *L, *R;
    split(root, x, L, R);
    root = merge(merge(L, new node(x)), R);
}

void del(mark x)
{
    node *L, *R, *p;
    mark y = x;
    y.time--;
    split(root, x, L, R);
    split(L, y, L, p);
    p = merge(p->ls, p->rs);
    root = merge(merge(L, p), R);
}

int rnk(mark x)
{
    node *L, *R;
    x.time--;
    split(root, x, L, R);
    int ans = L ? L->size : 0;
    root = merge(L, R);
    return ans;
}

typedef unsigned int ui;
ui rand_num(ui &seed, ui last, const ui m)
{
    seed = seed * 17 + last;
    return seed % m + 1;
}
ui seed, last = 7;
inline void write(int x)
{
    if (x < 10)
    {
        putchar(x + 48);
        return;
    }
    write(x / 10), write(x % 10);
}

int main()
{
    int T = read();
    while (T--)
    {
        int m = read(), n = read();
        seed = read();
        root = nullptr;
        for (int i = 1; i <= m; i++)
            people[i].ACs = people[i].time = 0,
            insert(people[i]);
        while (n--)
        {
            auto commit = rand_num(seed, last, m), time = rand_num(seed, last, m);
            auto &per = people[commit];
            del(per);
            per.ACs++, per.time += time;
            insert(per);
            write(last = rnk(per)), putchar('\n');
        }
    }
    return 0;
}
