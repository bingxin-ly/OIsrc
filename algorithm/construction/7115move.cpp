#include <bits/stdc++.h>
using namespace std;

constexpr int N = 55, M = 405, OPT = 820005;
int L[OPT], R[OPT], tot, n, m;
int a[N][M], cnt[N], p[N];
void move(int x, int y)
{
    ++tot;
    L[tot] = x, R[tot] = y;
    a[y][++cnt[y]] = a[x][cnt[x]--];
}
int count(int x, int y)
{
    int ret = 0;
    for (int i = 1; i <= m; i++)
        ret += a[x][i] == y;
    return ret;
}
int top(int x) { return a[x][cnt[x]]; }
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cnt[i] = m;
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    }
    cnt[n + 1] = 0;
    for (int i = 1; i <= n + 1; i++)
        p[i] = i;
    for (int cur = n; cur >= 3; cur--)
    {
        int lim = count(p[1], cur);
        for (int i = 1; i <= lim; i++)
            move(p[cur], p[cur + 1]);
        for (int i = 1; i <= m; i++)
            if (top(p[1]) == cur)
                move(p[1], p[cur]);
            else
                move(p[1], p[cur + 1]);
        for (int i = 1; i <= m - lim; i++)
            move(p[cur + 1], p[1]);
        for (int i = 1; i <= m; i++)
            if (top(p[2]) == cur || cnt[p[1]] == m)
                move(p[2], p[cur + 1]);
            else
                move(p[2], p[1]);
        swap(p[1], p[cur]), swap(p[2], p[cur + 1]);
        for (int k = 1; k < cur; k++)
        {
            lim = count(p[k], cur);
            for (int i = 1; i <= lim; i++)
                move(p[cur], p[cur + 1]);
            for (int i = 1; i <= m; i++)
                if (top(p[k]) == cur)
                    move(p[k], p[cur]);
                else
                    move(p[k], p[cur + 1]);
            swap(p[k], p[cur + 1]), swap(p[k], p[cur]);
        }
        for (int i = 1; i < cur; i++)
            while (top(p[i]) == cur)
                move(p[i], p[cur + 1]);
        for (int i = 1; i < cur; i++)
            while (cnt[p[i]] < m)
                move(p[cur], p[i]);
    }
    int lim = count(p[1], 1);
    for (int i = 1; i <= lim; i++)
        move(p[2], p[3]);
    for (int i = 1; i <= m; i++)
        if (top(p[1]) == 1)
            move(p[1], p[2]);
        else
            move(p[1], p[3]);
    for (int i = 1; i <= lim; i++)
        move(p[2], p[1]);
    for (int i = 1; i <= m - lim; i++)
        move(p[3], p[1]);
    while (cnt[p[3]])
        move(p[3], p[2]);
    for (int i = 1; i <= m - lim; i++)
        move(p[1], p[3]);
    for (int i = 1; i <= m; i++)
        if (top(p[2]) == 1)
            move(p[2], p[1]);
        else
            move(p[2], p[3]);
    cout << tot << '\n';
    for (int i = 1; i <= tot; i++)
        cout << L[i] << ' ' << R[i] << '\n';
    return 0;
}