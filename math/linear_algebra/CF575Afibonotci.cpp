#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e4 + 10;
int p, n, s[N];
struct matrix
{
    int val[2][2];
    matrix(int a = 0, int b = 0, int c = 0, int d = 0)
    {
        val[0][0] = a, val[0][1] = b,
        val[1][0] = c, val[1][1] = d;
    }

    int *operator[](int x) { return val[x]; }
    friend matrix operator*(matrix a, matrix b)
    {
        return matrix((a[0][0] * b[0][0] + a[0][1] * b[1][0]) % p,
                      (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % p,
                      (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % p,
                      (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % p);
    }
    friend ostream &operator<<(ostream &out, const matrix &mat)
    {
        for (int i = 0; i < 2; i++, putchar('\n'))
            for (int j = 0; j < 2; j++)
                out << mat.val[i][j] << ' ';
        return out;
    }
} const UNIT(1, 0, 0, 1);
matrix fpow(matrix a, int k)
{
    matrix res = UNIT;
    while (k)
    {
        if (k & 1)
            res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}
struct node
{
    int l, r;
    matrix val;
} nd[N << 2];

void pushup(int p)
{
    nd[p].val = nd[p << 1].val * nd[p << 1 | 1].val;
}

void build(int p, int l, int r)
{
    nd[p].l = l, nd[p].r = r;
    if (l == r)
    {
        nd[p].val = matrix(0, s[l], 1, s[(l + 1) % n]);
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void update(int p, int x, bool y, int v)
{
    if (nd[p].l == nd[p].r)
    {
        nd[p].val[y][1] = v;
        return;
    }
    int mid = (nd[p].l + nd[p].r) >> 1;
    update(p << 1 | (x > mid), x, y, v);
    pushup(p);
}

matrix query(int p, int l, int r)
{
    if (l > r)
        return UNIT;
    if (nd[p].l >= l && nd[p].r <= r)
        return nd[p].val;
    int mid = (nd[p].l + nd[p].r) >> 1;
    matrix ans = UNIT;
    if (l <= mid)
        ans = ans * query(p << 1, l, r);
    if (r > mid)
        ans = ans * query(p << 1 | 1, l, r);
    return ans;
}

pair<int, int> v[N];
vector<pair<int, pair<bool, int>>> vv;
signed main()
{
    int k, m;
    cin >> k >> p >> n;
    for (int i = 0; i < n; i++)
        cin >> s[i];
    cin >> m;
    for (int i = 1; i <= m; i++)
        cin >> v[i].first >> v[i].second;
    vv.push_back({-n, {0, 0}}), vv.push_back({0x3f3f3f3f3f3f3f3f, {0, 0}});
    for (int i = 1; i <= m; i++)
    {
        vv.push_back({v[i].first, {0, v[i].second}});
        if (v[i].first)
            vv.push_back({v[i].first - 1, {1, v[i].second}});
    }
    sort(vv.begin(), vv.end());
    build(1, 0, n - 1);
    int las = 0;
    matrix res = UNIT;
    for (int i = 1, ii; i < vv.size(); i = ii + 1)
    {
        ii = i;
        while (ii + 1 < vv.size() && vv[ii + 1].first / n == vv[i].first / n)
            ii++;
        if (vv[i].first / n >= k / n)
        {
            las = vv[i - 1].first / n;
            break;
        }
        res = res * fpow(query(1, 0, n - 1), vv[i].first / n - 1 - vv[i - 1].first / n);
        for (int j = i; j <= ii; j++)
            update(1, vv[j].first % n, vv[j].second.first, vv[j].second.second);
        res = res * query(1, 0, n - 1);
        for (int j = i; j <= ii; j++)
            update(1, vv[j].first % n, vv[j].second.first, vv[j].second.first ? s[(vv[j].first + 1) % n] : s[vv[j].first % n]);
    }
    res = res * fpow(query(1, 0, n - 1), k / n - 1 - las);
    for (int i = 0; i < vv.size(); i++)
        if (vv[i].first / n == k / n)
            update(1, vv[i].first % n, vv[i].second.first, vv[i].second.second);
    res = res * query(1, 0, k % n - 1);
    cout << res[1][0];
    return 0;
}
