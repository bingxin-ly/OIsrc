#include <bits/stdc++.h>
#include <utility>
using namespace std;

struct node
{
    node *ls, *rs;
    string val;
    int pri, size;

    explicit node(string x) : val(std::move(x)), size(1)
    {
        ls = rs = nullptr;
        pri = rand();
    }
} *root;

void update(node *u)
{
    u->size = (u->ls ? u->ls->size : 0) + (u->rs ? u->rs->size : 0) + 1;
}

void split(node *u, int x, node *&L, node *&R)
{
    if (!u)
        return L = R = nullptr, void();
    int less = (u->ls ? u->ls->size : 0) + 1;
    if (x >= less)
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

vector<string> seq;
void inorder(node *u)
{
    if (!u)
        return;
    inorder(u->ls);
    seq.push_back(u->val);
    inorder(u->rs);
}

int main()
{
    // build
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        root = merge(root, new node(s));
    }

    // modify
    int m;
    cin >> m;
    node *L, *R;
    for (int i = 1; i <= m; i++)
    {
        string s;
        int pos;
        cin >> s >> pos;
        split(root, pos, L, R);
        root = merge(merge(L, new node(s)), R);
    }

    // query
    inorder(root);
    int q;
    cin >> q;
    for (int i = 1, pos; i <= q; i++)
        cin >> pos,
            cout << seq[pos] << endl;
    return 0;
}
