#include <bits/stdc++.h>
using namespace std;
using pdi = pair<double, int>;

constexpr int N = 4e4, M = 1e5 + 10,
              MODX = 39989, MODY = 1e9;
constexpr double eps = 1e-7;

struct line
{
    double k, b;
} lis[M];
int t[N << 2], cnt;
double calc(int i, int x) { return lis[i].k * x + lis[i].b; }
int cmp(double x, double y)
{
    if (x - y > eps)
        return 1;
    else if (y - x > eps)
        return -1;
    else
        return 0;
}

#define ls (p << 1)
#define rs (p << 1 | 1)
void spread(int p, int l, int r, int g)
{
    int &f = t[p],
        mid = (l + r) >> 1;
    int cres = cmp(calc(g, mid), calc(f, mid));
    if (cres > 0 || (!cres && g < f))
        swap(f, g);
    int cmpl = cmp(calc(g, l), calc(f, l));
    if (cmpl > 0 || (!cmpl && g < f))
        spread(ls, l, mid, g);
    int cmpr = cmp(calc(g, r), calc(f, r));
    if (cmpr > 0 || (!cmpr && g < f))
        spread(rs, mid + 1, r, g);
}
void update(int p, int l, int r, int ql, int qr, int idx)
{
    if (ql <= l && r <= qr)
        return spread(p, l, r, idx);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(ls, l, mid, ql, qr, idx);
    if (qr > mid)
        update(rs, mid + 1, r, ql, qr, idx);
}
void insert(int x0, int y0, int x1, int y1)
{
    cnt += 1;
    if (x0 == x1)
        lis[cnt].k = 0, lis[cnt].b = max(y0, y1);
    else
        lis[cnt].k = 1.0 * (y1 - y0) / (x1 - x0), lis[cnt].b = y0 - lis[cnt].k * x0;
    update(1, 1, MODX, x0, x1, cnt);
}
pdi pmax(pdi x, pdi y)
{
    int cres = cmp(x.first, y.first);
    if (cres > 0)
        return x;
    else if (cres < 0)
        return y;
    else
        return x.second < y.second ? x : y;
}
pdi query(int p, int l, int r, int x)
{
    pdi ret = {calc(t[p], x), t[p]};
    if (l == r)
        return ret;
    int mid = (l + r) >> 1;
    if (x <= mid)
        ret = pmax(ret, query(ls, l, mid, x));
    else
        ret = pmax(ret, query(rs, mid + 1, r, x));
    return ret;
}

#define parX(_x) _x = (_x + lst - 1) % MODX + 1
#define parY(_y) _y = (_y + lst - 1) % MODY + 1
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int m, lst = 0;
    cin >> m;
    int op, x0, y0, x1, y1, k;
    while (m--)
    {
        cin >> op;
        if (!op)
        {
            cin >> k;
            parX(k);
            cout << (lst = query(1, 1, MODX, k).second) << '\n';
        }
        else
        {
            cin >> x0 >> y0 >> x1 >> y1;
            parX(x0), parY(y0), parX(x1), parY(y1);
            if (x0 > x1)
                swap(x0, x1), swap(y0, y1);
            insert(x0, y0, x1, y1);
        }
    }
    return 0;
}