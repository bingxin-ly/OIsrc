#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef unsigned int ui;
typedef pair<ui, ui> UIpair;
ui rand_num(ui &seed, ui last, const ui m)
{
    seed = seed * 17 + last;
    return seed % m + 1;
}
ui last = 7;
UIpair get_rand(ui &seed, const ui m)
{
    UIpair res;
    last = res.x = rand_num(seed, last, m);
    last = res.y = rand_num(seed, last, m);
    return res;
}

struct node
{
    node *ls, *rs;
    UIpair val;
    int size, pri;

    explicit node(UIpair x) : val(x), size(1)
    {
        ls = rs = nullptr;
        pri = rand();
    }
} *root;

void update(node *u)
{
    u->size = (u->ls ? u->ls->size : 0) + (u->rs ? u->rs->size : 0) + 1;
}

void split(node *u, UIpair x, node *&L, node *&R)
{
    if (!u)
        return L = R = nullptr, void();
    if (x >= u->val)
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

UIpair operator-(const UIpair &a, const int &b)
{
    return (UIpair){a.x, a.y - b};
}

int rnk(UIpair x)
{
    node *L, *R;
    split(root, x - 1, L, R);
    int ans = R ? R->size : 0;
    root = merge(L, R);
    return ans;
}

void inorder(node *u)
{
    if (!u)
        return;
    inorder(u->ls);
    printf("{%d, %d}\n", u->val.x, u->val.y);
    inorder(u->rs);
}
void debug(node *u)
{
    inorder(u), puts("");
}

unordered_map<ui, UIpair> bastards;
int main()
{
    int T;
    cin >> T;
    node *p, *L, *R;
    while (T--)
    {
        ui m, n, seed;
        cin >> m >> n >> seed;
        while (n--)
        {
            auto person = get_rand(seed, m);
            auto &marks = bastards[person.x];
            marks.x += 1, marks.y += person.y;
            // printf("ori: "), debug(root);
            split(root, marks, L, R), split(L, marks - 1, L, p);
            if (p)
                p->val = marks;
            else
                p = new node(marks);
            // printf("p: "), debug(p);
            root = merge(merge(L, p), R);
            // printf("root: "), debug(root);
            cout << rnk(marks) - 1 << endl;
        }
    }
    return 0;
}
