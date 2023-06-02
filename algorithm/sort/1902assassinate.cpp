#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;
int n, m, p[N][N], vis[N][N];

typedef pair<int, int> point;
#define x first
#define y second
int dx[] = {1, 0, -1, 0},
    dy[] = {0, 1, 0, -1};
bool bfs(int x, int y, int maxn)
{
    queue<point> q;
    q.push({x, y});
    vis[x][y] = true;

    while (!q.empty())
    {
        int xx = q.front().x, yy = q.front().y;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = xx + dx[i], ny = yy + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m ||
                vis[nx][ny] || p[nx][ny] > maxn)
                continue;
            vis[nx][ny] = true;
            if (nx == n)
                return true;
            else
                q.push({nx, ny});
        }
    }
    return false;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> p[i][j];

    int l = 0, r = 1001;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        memset(vis, 0, sizeof(vis));
        if (bfs(1, 1, mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << l << endl;
    return 0;
}