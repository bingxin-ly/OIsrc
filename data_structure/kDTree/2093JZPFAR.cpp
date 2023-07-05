#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\output\\.in");
ofstream fout("D:\\OIsrc\\output\\.out");
#define cin fin
#define cout fout
#endif

constexpr int N = 1e5 + 5;
inline void ckmax(int &x, int y) { x = x > y ? x : y; }
inline void ckmin(int &x, int y) { x = x < y ? x : y; }
inline long long squ(long long x) { return x * x; }

struct poi
{
    int ls, rs;
    int id, di[2], mx[2], mn[2];
} t[N];

void pushup(int p)
{
    int ls = t[p].ls, rs = t[p].rs;
    for (int i = 0; i <= 1; i++)
    {
        t[p].mx[i] = t[p].mn[i] = t[p].di[i];
        if (ls)
            ckmax(t[p].mx[i], t[ls].mx[i]),
                ckmin(t[p].mn[i], t[ls].mn[i]);
        if (rs)
            ckmax(t[p].mx[i], t[rs].mx[i]),
                ckmin(t[p].mn[i], t[rs].mn[i]);
    }
}
int build(int l, int r)
// kdt方差建树就是 M
{
    int mid = (l + r) >> 1;
    double av1 = 0, av2 = 0, va1 = 0, va2 = 0;
    for (int i = l; i <= r; i++)
        av1 += t[i].di[0], av2 += t[i].di[1];
    av1 /= r - l + 1, av2 /= r - l + 1;
    for (int i = l; i <= r; i++)
        va1 += squ(t[i].di[0] - av1), va2 += squ(t[i].di[1] - av2);
    nth_element(t + l, t + mid, t + r + 1, [d = va1 < va2](const poi &x, const poi &y)
                { return x.di[d] < y.di[d]; });
    t[mid] = t[mid];
    if (l < mid)
        t[mid].ls = build(l, mid - 1);
    if (r > mid)
        t[mid].rs = build(mid + 1, r);
    pushup(mid);
    return mid;
}
#define x first
#define y second
pair<int, int> pos;
struct dat
{
    long long dis;
    int id;
    dat(long long a, int b) : dis(a), id(b) {}
    bool operator<(const dat &o) const { return dis < o.dis || (!(o.dis < dis) && id > o.id); }
    bool operator>(const dat &o) const { return dis > o.dis || (!(o.dis > dis) && id < o.id); }
};
priority_queue<dat, vector<dat>, greater<>> q;
long long calc(int p)
{
    return max(squ(pos.x - t[p].mx[0]), squ(pos.x - t[p].mn[0])) +
           max(squ(pos.y - t[p].mx[1]), squ(pos.y - t[p].mn[1]));
}
void query(int l, int r)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1, ls = t[mid].ls, rs = t[mid].rs;
    long long dis = squ(t[mid].di[0] - pos.x) + squ(t[mid].di[1] - pos.y);
    dat ip{dis, t[mid].id};
    if (q.top() < ip)
        q.pop(), q.emplace(ip);
    long long disl = calc(ls), disr = calc(rs);
    dat il{disl, t[ls].id}, ir{disr, t[rs].id};
    if (q.top() < il && q.top() < ir)
    {
        if (il < ir)
        {
            query(mid + 1, r);
            q.top() < il && (query(l, mid - 1), true);
        }
        else
        {
            query(l, mid - 1);
            q.top() < ir && (query(mid + 1, r), true);
        }
    }
    else if (q.top() < il)
        query(l, mid - 1);
    else if (q.top() < ir)
        query(mid + 1, r);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, k;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t[i].di[0] >> t[i].di[1], t[i].id = i;
    build(1, n);
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> pos.x >> pos.y >> k;
        while (!q.empty())
            q.pop();
        while (k--)
            q.emplace(-1, 0);
        query(1, n);
        cout << q.top().id << '\n';
    }
    return 0;
}