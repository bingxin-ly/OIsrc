#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0}, gol[5][5];
bool check(int cur[5][5]) {
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            if (cur[i][j] != gol[i][j]) return false;
    return true;
}
int trans(int cur[5][5]) {
    int val = 0;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++) (val *= 16) += cur[i][j];
    return val;
}
struct state {
    int zx, zy, tab[5][5];
    state(int x, int y, int cur[5][5]) : zx(x), zy(y) {
        memcpy(tab, cur, sizeof(tab));
    }
};
queue<state> q;
unordered_map<int, int> vis, ans;
void bfs() {
    int tab[5][5];
    while (!q.empty()) {
        state o = q.front();
        q.pop(), memcpy(tab, o.tab, sizeof(tab));
        int px = o.zx, py = o.zy, pre = trans(o.tab), cur;
        if (ans[pre] == 51) {
            cout << "No";
            return;
        }
        for (int i = 0; i < 4; i++) {
            int nx = px + dx[i], ny = py + dy[i];
            if (nx < 1 || nx > 4 || ny < 1 || ny > 4) continue;
            swap(tab[px][py], tab[nx][ny]);
            cur = trans(tab);
            if (vis[cur] == vis[pre]) {
                swap(tab[px][py], tab[nx][ny]);
                continue;
            }
            if (vis[cur] + vis[pre] == 3) {
                cout << ans[cur] + ans[pre];
                return;
            }
            ans[cur] = ans[pre] + 1, vis[cur] = vis[pre],
            q.emplace(nx, ny, tab);
            swap(tab[px][py], tab[nx][ny]);
        }
    }
}
signed main() {
    freopen("puzzle.in", "r", stdin);
    freopen("puzzle.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int zx = 0, zy = 0, tab[5][5];
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++) {
            cin >> tab[i][j], gol[i][j] = (i - 1) * 4 + j;
            if (!tab[i][j]) zx = i, zy = j;
        }
    gol[4][4] = 0;
    if (check(tab)) {
        return cout << 0, 0;
    }
    q.emplace(zx, zy, tab), q.emplace(4, 4, gol);
    ans[trans(tab)] = 0, ans[trans(gol)] = 1;
    vis[trans(tab)] = 1, vis[trans(gol)] = 2;
    bfs();
    return 0;
}
