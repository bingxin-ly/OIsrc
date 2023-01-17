#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "output.h"
#endif
using namespace std;

const int MX = 110;
struct node
{
    int x, y, height;
    bool operator>(const node &other) const
    {
        return height > other.height;
    }
    bool operator<(const node &other) const
    {
        return height < other.height;
    }
};
int g[MX][MX], f[MX][MX];
int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
priority_queue<node, vector<node>, greater<>> pq;
int main()
{
    int R, C;
    cin >> R >> C;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            int height;
            cin >> height;
            pq.push((node){i, j, height});
            g[i][j] = height;
            f[i][j] = 1;
        }
    }
    while (!pq.empty())
    {
        node t = pq.top();
        pq.pop();
        for (int i = 0; i < 4; i++)
        {
            int x = t.x + dx[i];
            int y = t.y + dy[i];
            if (x < 0 || y < 0 || x >= R || y >= C)
                continue;
            if (g[x][y] < t.height)
            {
                // cout << (g[x][y]) << ' ' << (t.height) << endl;
                f[t.x][t.y] = max(f[t.x][t.y], f[x][y] + 1);
                // f[x][y] = max(f[x][y], f[t.x][t.y] + 1);
                // output({t.x + 1, t.y + 1, f[t.x][t.y]});
            }
        }
    }
    int ans = 0;// 局部变量赋初值！！！
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            ans = max(ans, f[i][j]);
    cout << ans << endl;
    return 0;
}