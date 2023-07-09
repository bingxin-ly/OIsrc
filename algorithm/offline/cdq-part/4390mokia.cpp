#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

constexpr int N = 2e6 + 9, M = 2e5 + 9;
int n, ans[M];
struct opt
{
    int x, y, qid;
    int a;
} s[M];
namespace fenwick
{
    int t[N];
    inline int lowbit(int x) { return x & -x; }
    inline void add(int p, int v)
    {
        for (; p <= n; p += lowbit(p))
            t[p] += v;
    }
    inline int ask(int p)
    {
        int ret = 0;
        for (; p; p -= lowbit(p))
            ret += t[p];
        return ret;
    }
}

void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid);

    vector<opt> seq;
    for (int i = l; i <= mid; i++)
        if (s[i].a)
            seq.emplace_back(s[i]);
    for (int i = mid + 1; i <= r; i++)
        if (!s[i].a)
            seq.emplace_back(s[i]);
    sort(seq.begin(), seq.end(), [](const opt &a, const opt &b)
         { return a.x < b.x || (!(b.x < a.x) && a.a > b.a); });

    for (const opt &o : seq)
        if (o.a)
            fenwick::add(o.y, o.a);
        else
            ans[abs(o.qid)] += fenwick::ask(o.y) * (o.qid / abs(o.qid));
    for (const opt &o : seq)
        if (o.a)
            fenwick::add(o.y, -o.a);
    cdq(mid + 1, r);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> n;
    n += 1;
    int op, x1, y1, x2, y2,
        i = 0, qid = 0;
    while (cin >> op, op != 3)
        if (op == 1)
        {
            i += 1;
            cin >> s[i].x >> s[i].y >> s[i].a;
            s[i].x += 1, s[i].y += 1;
        }
        else
        {
            qid += 1, cin >> x1 >> y1 >> x2 >> y2;
            x1 += 1, y1 += 1, x2 += 1, y2 += 1;
            s[++i] = {x2, y2, qid, 0}, s[++i] = {x1 - 1, y1 - 1, qid, 0};
            s[++i] = {x1 - 1, y2, -qid, 0}, s[++i] = {x2, y1 - 1, -qid, 0};
        }

    cdq(1, i);

    for (int i = 1; i <= qid; i++)
        cout << ans[i] << endl;
    return 0;
}