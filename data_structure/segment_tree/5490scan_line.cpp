#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 8e5 + 10;
struct scanline
{
    int y, x1, x2, io;
    bool operator<(const scanline &o) const { return y < o.y; }
} line[N];

int width[N], tag[N], xx[N];

#define ls p << 1
#define rs p << 1 | 1
void pushup(int p, int l, int r)
{
    if (tag[p])
        width[p] = xx[r] - xx[l];
    else if (l + 1 == r)
        width[p] = 0;
    else
        width[p] = width[ls] + width[rs];
}
void update(int p, int l, int r, int ql, int qr, int io)
{
    if (ql <= l && r <= qr)
    {
        tag[p] += io, pushup(p, l, r);
        return;
    }
    if (l + 1 == r)
        return;

    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(ls, l, mid, ql, qr, io);
    if (qr > mid)
        update(rs, mid, r, ql, qr, io); // 不是 mid + 1！！注意不是 mid + 1！
    pushup(p, l, r);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, cnt = 0;
    cin >> n;
    for (int x1, y1, x2, y2; n--;)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        line[++cnt] = {y1, x1, x2, 1}, xx[cnt] = x1;
        line[++cnt] = {y2, x1, x2, -1}, xx[cnt] = x2;
    }
    sort(xx + 1, xx + cnt + 1), sort(line + 1, line + cnt + 1);
    int num = unique(xx + 1, xx + cnt + 1) - xx - 1;

    int ans = 0;
    for (int i = 1, l, r; i <= cnt; i++)
    {
        ans += width[1] * (line[i].y - line[i - 1].y);
        l = lower_bound(xx + 1, xx + num + 1, line[i].x1) - xx;
        r = lower_bound(xx + 1, xx + num + 1, line[i].x2) - xx;
        update(1, 1, num, l, r, line[i].io);
    }
    cout << ans;
    return 0;
}