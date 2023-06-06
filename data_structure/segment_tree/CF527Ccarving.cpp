#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10, M = N << 2;
int mx[2][M], lm[2][M], rm[2][M];
bool none[2][M];

inline int max(int a, int b) { return a > b ? a : b; }
inline int max(int a, int b, int c) { return max(max(a, b), c); }

#define ls p << 1
#define rs p << 1 | 1

#define lmx lm[m]
#define rmx rm[m]
#define mxn mx[m]
void pushup(int p, bool m)
{
    if (none[m][ls])
        lmx[p] = lmx[ls] + lmx[rs];
    else
        lmx[p] = lmx[ls];

    if (none[m][rs])
        rmx[p] = rmx[rs] + rmx[ls];
    else
        rmx[p] = rmx[rs];

    mxn[p] = max(mxn[ls], mxn[rs], rmx[ls] + lmx[rs]);
    none[m][p] = none[m][ls] && none[m][rs];
}
void build(int p, bool m, int l, int r)
{
    if (l == r)
        return mxn[p] = lmx[p] = rmx[p] = 1, none[m][p] = true, void();
    int mid = (l + r) >> 1;
    build(ls, m, l, mid), build(rs, m, mid + 1, r);
    pushup(p, m);
}
void modify(int p, bool m, int l, int r, int pos)
{
    if (l == r)
        return mxn[p] = lmx[p] = rmx[p] = 0, none[m][p] = false, void();

    int mid = (l + r) >> 1;
    if (pos <= mid)
        modify(ls, m, l, mid, pos);
    else
        modify(rs, m, mid + 1, r, pos);
    pushup(p, m);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int w, h, q;
    cin >> w >> h >> q;
    build(1, true, 1, w - 1), build(1, false, 1, h - 1);

    char op;
    for (int x; q--;)
    {
        cin >> op >> x;
        if (op == 'H')
            modify(1, false, 1, h - 1, x);
        else
            modify(1, true, 1, w - 1, x);
        cout << (mx[1][1] + 1) * (mx[0][1] + 1) << '\n';
    }
    return 0;
}