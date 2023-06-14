#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 10;
int M, tr[N];

#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p)
{
    tr[p] = 1ll * tr[ls] * tr[rs] % M;
}
void change(int p, int l, int r, int pos, int x)
{
    if (l == r)
        return tr[p] = x, void();

    int mid = (l + r) >> 1;
    if (pos <= mid)
        change(ls, l, mid, pos, x);
    else
        change(rs, mid + 1, r, pos, x);
    pushup(p);
}

void solve()
{
    int q;
    cin >> q >> M;
    // for (int &i : tr)
    //     i = 1;
    fill(tr + 1, tr + (q << 2) + 1, 1);
    for (int i = 1, opt, x; i <= q; i++)
    {
        cin >> opt >> x;
        if (opt == 1)
            change(1, 1, q, i, x % M);
        else
            change(1, 1, q, x, 1);
        cout << tr[1] << '\n';
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t;
    for (cin >> t; t--;)
        solve();
    return 0;
}