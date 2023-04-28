#include <bits/stdc++.h>
#define chkmin(a, b) b < a ? a = b : a
using namespace std;

const int N = 2e5 + 10;

int n, p, fr[N], to[N], f[N];
struct board
{
    int x, y, mpy, idx;
    bool operator<(const board &o) const
    {
        return x == o.x ? y < o.y : x < o.x;
    }
} bs[N];

int tr[N];
void add(int x, int val)
{
    for (; x <= p * 2; x += (x & -x))
        chkmin(tr[x], val);
}
int query(int x)
{
    int res = 0;
    for (; x; x -= (x & -x))
        chkmin(res, tr[x]);
    return res;
}

int main()
{
    cin >> n >> p;
    for (int i = 1; i <= p; i++)
    {
        cin >> bs[i].x >> bs[i].y;
        cin >> bs[i + p].x >> bs[i + p].y;
        bs[i].idx = bs[i + p].idx = i;
    }
    // 离散化跳板
    sort(bs + 1, bs + p * 2 + 1, [](board a, board b)
         { return a.y < b.y; });
    bs[0].y = -1;
    for (int i = 1; i <= p * 2; i++)
        bs[i].mpy = bs[i - 1].mpy + (bs[i - 1].y != bs[i].y);

    sort(bs + 1, bs + p * 2 + 1);
    for (int i = 1; i <= p * 2; i++)
        if (fr[bs[i].idx])
            to[bs[i].idx] = i;
        else
            fr[bs[i].idx] = i;

    // 状态转移：f_i=dp_i−x_i−x_j=dp_k−x_i−y_i=f_k+x_k+y_k−x_i−y_i
    int res = 0;
    for (int i = 1; i <= p * 2; i++)
    {
        chkmin(f[i], query(bs[i].mpy));
        if (fr[bs[i].idx] == i)
            chkmin(f[to[bs[i].idx]], f[i] + bs[i].x + bs[i].y - bs[to[bs[i].idx]].x - bs[to[bs[i].idx]].y);
        add(bs[i].mpy, f[i]);
        chkmin(res, f[i]);
    }
    cout << res + n + n << endl;
    return 0;
}
