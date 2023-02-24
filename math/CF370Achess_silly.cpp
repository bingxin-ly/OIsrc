#include <bits/stdc++.h>
using namespace std;

struct point
{
    int r, c;
    inline bool operator==(point &other) const
    {
        return (r == other.r) && (c == other.c);
    }
    inline friend bool operator<(const point a, const point b)
    {
        bool flag = a.r < b.r;
        return flag ? flag : (a.c < b.c);
    }

    inline int gh()
    {
        return 10 * r + c;
    }
};
point st, ed;
queue<int> q;
map<int, int> vis;
map<int, int> ans;
int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
int pr, pc, nr, nc;
point tmp;

inline void bfs_king()
{
    q.push(st.gh());
    q.push(ed.gh());
    ans[st.gh()] = 0, ans[ed.gh()] = 1;
    vis[st.gh()] = 1, vis[ed.gh()] = 2;

    while (!q.empty())
    {
        int now, cur = q.front();
        q.pop();
        now = cur;
        tmp = {now / 10, now % 10};
        pr = now / 10, pc = now % 10;

        for (int i = 0; i < 8; i++)
        {
            nr = pr + dx[i];
            nc = pc + dy[i];
            if (nr < 1 || nr > 8 || nc < 1 || nc > 8)
                continue;
            swap(tmp.r, nr), swap(tmp.c, nc);
            now = tmp.gh();

            if (vis[now] == vis[cur])
            {
                swap(tmp.r, nr), swap(tmp.c, nc);
                continue;
            }
            if (vis[now] + vis[cur] == 3)
            {
                cout << ans[cur] + ans[now];
                exit(0);
            }
            ans[now] = ans[cur] + 1;
            vis[now] = vis[cur];
            q.push(now);
            swap(tmp.r, nr), swap(tmp.c, nc);
        }
    }
}
inline void bfs_xiang()
{
    int k1 = st.r - st.c, s1 = st.r + st.c;
    int k2 = ed.r - ed.c, s2 = ed.r + ed.c;
    if (((k1 - k2) % 2) || (s1 - s2) % 2)
        cout << "0 ";
    else if (k1 == k2 || s1 == s2)
        cout << "1 ";
    else
        cout << "2 ";
}
int main()
{
    // freopen("chess.in", "r", stdin);
    // freopen("chess.out", "w", stdout);

    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    st = {r1, c1}, ed = {r2, c2};
    if (st == ed) // special
    {
        puts("0 0 0");
        return 0;
    }

    cout << (bool)abs(r1 - r2) + (bool)abs(c1 - c2) << ' ';

    bfs_xiang();

    bfs_king();
    return 0;
}