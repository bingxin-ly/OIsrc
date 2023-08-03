#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5, P = 1e7;
vector<int> tsk[N];
struct
{
    int ls, rs, cnt;
    long long val;
} t[N << 6];
int idx, rt[N];

#define ls t[p].ls
#define rs t[p].rs
void pushup(int p)
{
    t[p].cnt = t[ls].cnt + t[rs].cnt;
    t[p].val = t[ls].val + t[rs].val;
}
void modify(int &p, int l, int r, int x, int v)
{
    t[++idx] = t[p], p = idx;
    if (l == r)
        return t[p].cnt += v, t[p].val += v * x, void();
    int mid = (l + r) >> 1;
    if (x <= mid)
        modify(ls, l, mid, x, v);
    else
        modify(rs, mid + 1, r, x, v);
    pushup(p);
}
long long query(int p, int l, int r, int x)
{
    if (l == r)
        return 1ll * min(x, t[p].cnt) * l;
    int mid = (l + r) >> 1;
    if (x <= t[ls].cnt)
        return query(ls, l, mid, x);
    else
        return t[ls].val + query(rs, mid + 1, r, x - t[ls].cnt);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int m, n;
    cin >> m >> n;
    for (int i = 1, s, e, p; i <= m; i++)
    {
        cin >> s >> e >> p;
        tsk[s].emplace_back(p), tsk[e + 1].emplace_back(-p);
    }
    for (int i = 1; i <= n; i++)
    {
        rt[i] = rt[i - 1];
        for (int t : tsk[i])
            modify(rt[i], 1, P, abs(t), t / abs(t));
    }
    long long pre = 1;
    for (int x, a, b, c; n--;)
    {
        cin >> x >> a >> b >> c;
        int k = (a * pre + b) % c + 1;
        cout << (pre = query(rt[x], 1, P, k)) << '\n';
    }
    return 0;
}