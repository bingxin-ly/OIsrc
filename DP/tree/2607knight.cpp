#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

// 前向星存边（妥协了/kk）
int idx, head[N];
pair<int, int> graph[N * 2];
auto add = [](int u, int v)
{ graph[idx].first = v, graph[idx].second = head[u], head[u] = idx++; };

int power[N];

int x1, x2, cir_now, vis[N];
void fdcir(int u, int pre)
{
    vis[u] = true;
    for (int i = head[u]; ~i; i = graph[i].second)
    {
        if ((i ^ 1) == pre) // 不是兄弟边
            continue;
        int to = graph[i].first;
        if (vis[to])
        {
            x1 = u, x2 = to;
            cir_now = i;
            continue;
        }
        fdcir(to, i);
    }
}

ssize_t f[N][2];
void dfs(int u, int pre)
{
    f[u][0] = 0;
    f[u][1] = power[u];
    for (int i = head[u]; ~i; i = graph[i].second)
    {
        if ((i ^ 1) == pre) // 不是兄弟边
            continue;
        if (i == cir_now || (i ^ 1) == cir_now)
            continue;

        int to = graph[i].first;
        dfs(to, i);
        f[u][1] += f[to][0];
        f[u][0] += max(f[to][1], f[to][0]);
    }
}
int main()
{
    memset(head, -1, sizeof(head));

    int n;
    cin >> n;
    for (int i = 1, hate; i <= n; i++)
    {
        cin >> power[i] >> hate;
        add(i, hate), add(hate, i);
    }

    ssize_t ans = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
        {
            fdcir(i, -2);
            dfs(x1, -1);
            ssize_t tmp = f[x1][0];
            dfs(x2, -1);
            tmp = max(tmp, f[x2][0]);
            ans += tmp;
        }
    cout << ans;
    return 0;
}