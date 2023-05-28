#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

const int N = 5e5 + 10;
inline int max(const int &a, const int &b) { return b > a ? b : a; }
#define ls p << 1
#define rs (p << 1 | 1)
int val[N << 3], tag[N << 3]; // 由于一段区间的两个节点是分别存的，要开 8 倍大！！
inline void pushup(int p) { val[p] = max(val[ls], val[rs]); }
inline void pushdown(int p)
{
    if (tag[p])
    {
        tag[ls] += tag[p], val[ls] += tag[p];
        tag[rs] += tag[p], val[rs] += tag[p];
        tag[p] = 0;
    }
}
void modify(int p, int l, int r, int ql, int qr, int v)
{
    if (ql <= l && r <= qr)
        return val[p] += v, tag[p] += v, void();

    pushdown(p);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        modify(ls, l, mid, ql, qr, v);
    if (qr > mid)
        modify(rs, mid + 1, r, ql, qr, v);
    pushup(p);
}
inline int query() { return val[1]; }

struct line
{
    int l, r, len;
    line(int l_, int r_) : l(l_), r(r_) { len = r - l; }
    inline bool operator<(const line &otr) const { return len < otr.len; }
};
vector<line> lines;
vector<int> points;

signed main()
{
    const int n = read(), m = read();
    for (int i = 1, u, v; i <= n; i++)
    {
        u = read(), v = read(), lines.emplace_back(u, v);
        points.emplace_back(u), points.emplace_back(v);
    }

    sort(lines.begin(), lines.end());
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    for (auto &i : lines)
    {
        i.l = lower_bound(points.begin(), points.end(), i.l) - points.begin() + 1;
        i.r = lower_bound(points.begin(), points.end(), i.r) - points.begin() + 1;
    }

    int tmp = 0, ans = INT_MAX;
    for (const auto &i : lines)
    {
        modify(1, 1, points.size(), i.l, i.r, 1);
        while (query() >= m)
        {
            ans = min(ans, i.len - lines[tmp].len);
            modify(1, 1, points.size(), lines[tmp].l, lines[tmp].r, -1);
            tmp++;
        }
    }

    printf("%d", ans != INT_MAX ? ans : -1);
    return 0;
}