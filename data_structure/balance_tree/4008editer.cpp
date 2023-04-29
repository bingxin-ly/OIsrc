// 排名树，FHQ实现 P4008文本编辑器
#include <bits/stdc++.h>
using namespace std;

struct node
{
    node *ls, *rs;
    char val;
    int pri, size;

    explicit node(char x) : val(x), size(1)
    {
        ls = rs = nullptr;
        pri = rand();
    }

    int lssz() const { return ls ? ls->size : 0; }
    int rssz() const { return rs ? rs->size : 0; }
} *root;

void update(node *u)
{
    u->size = u->lssz() + u->rssz() + 1;
}

// 排名分裂
void split(node *u, int x, node *&L, node *&R)
{
    if (!u)
        return L = R = nullptr, void();
    if (u->lssz() + 1 <= x) // modified
    {
        L = u;
        split(u->rs, x - u->lssz() - 1, u->rs, R); // modified
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

void inorder(node *u)
{
    if (!u)
        return;
    inorder(u->ls);
    printf("%c", u->val);
    inorder(u->rs);
}

int main()
{
    int n;
    cin >> n;
    int len, pos = 0;
    node *p, *L, *R;
    while (n--)
    {
        char opt[10];
        cin >> opt;
        switch (opt[0])
        {
        case 'M':
            cin >> pos;
            break;
        case 'I':
            cin >> len;
            split(root, pos, L, R);
            for (int i = 1; i <= len; i++)
            {
                char ch = getchar();
                while (ch < 32 || ch > 126)
                    ch = getchar();
                L = merge(L, new node(ch));
            }
            root = merge(L, R);
            break;
        case 'D':
            cin >> len;
            split(root, pos + len, L, R), split(L, pos, L, p); // note
            root = merge(L, R);
            break;
        case 'G':
            cin >> len;
            split(root, pos + len, L, R), split(L, pos, L, p); // note
            inorder(p), puts("");
            root = merge(merge(L, p), R);
            break;
        case 'P':
            pos--;
            break;
        case 'N':
            pos++;
            break;
        }
    }
    return 0;
}