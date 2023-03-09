#include <bits/stdc++.h>
using namespace std;

queue<int> q;
map<int, int> vis;
map<int, int> ans;
int st, ed = 123804765;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
short table[4][4], px, py, nx, ny;

void bfs()
{
    if (st == ed)
        return cout << 0, void();

    q.push(st), q.push(ed);
    ans[st] = 0, ans[ed] = 1;
    vis[st] = 1, vis[ed] = 2;
    while (!q.empty())
    {
        ssize_t now, cur = q.front();
        q.pop();
        now = cur;
        for (int i = 3; i >= 1; i--)
            for (int j = 3; j >= 1; j--)
            {
                table[i][j] = now % 10, now /= 10;
                if (table[i][j] == 0)
                    px = i, py = j;
            }
        for (int i = 0; i < 4; i++)
        {
            nx = px + dx[i], ny = py + dy[i];
            if (nx < 1 || nx > 3 || ny < 1 || ny > 3)
                continue;
            swap(table[px][py], table[nx][ny]);
            now = 0;
            for (int p = 1; p <= 3; p++)
                for (int j = 1; j <= 3; j++)
                    now = now * 10 + table[p][j];
            if (vis[now] == vis[cur])
            {
                swap(table[px][py], table[nx][ny]);
                continue;
            }
            if (vis[now] + vis[cur] == 3)
            {
                cout << ans[cur] + ans[now];
                return;
            }
            ans[now] = ans[cur] + 1;
            vis[now] = vis[cur];
            q.push(now);
            swap(table[px][py], table[nx][ny]);
        }
    }
}
int main()
{
    cin >> st;
    bfs();
    return 0;
}