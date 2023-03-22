#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10, M = 1e5 + 10;

int n, m, dfncnt;
int dfn[N], low[N];
int dist[N], pw[N];
int col[N], in[N], vis[N];
struct edge
{
    int from, to, next;
} oldG[M], newG[M];
int ocnt, ncnt, oh[N], nh[N];

void aold(int u, int v)
{
    oldG[++ocnt].next = oh[u];
    oldG[ocnt].from = u;
    oldG[ocnt].to = v;
    oh[u] = ocnt;
}
void anew(int u, int v)
{
    newG[++ncnt].next = nh[u];
    newG[ncnt].from = u;
    newG[ncnt].to = v;
    nh[u] = ncnt;
}

int top, stk[N];
void tarjan(int cur)
{
    dfn[cur] = low[cur] = ++dfncnt;
    stk[++top] = cur;
    vis[cur] = true;
    for (int i = oh[cur]; i; i = oldG[i].next)
    {
        int v = oldG[i].to;
        if (!dfn[v])
        {
            tarjan(v);
            low[cur] = min(low[cur], low[v]);
        }
        else if (vis[v])
            low[cur] = min(low[cur], low[v]);
    }
    if (dfn[cur] == low[cur])
    {
        int tmp;
        while (true)
        {
            tmp = stk[top--];
            col[tmp] = cur;
            vis[tmp] = false;
            if (cur == tmp)
                break;
            pw[cur] += pw[tmp];
        }
    }
}

void topo()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (col[i] == i && !in[i])
            q.push(i), dist[i] = pw[i];

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = nh[u]; i; i = newG[i].next)
        {
            int v = newG[i].to;
            dist[v] = max(dist[v], dist[u] + pw[v]);
            if (!--in[v])
                q.push(v);
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> pw[i];
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, aold(u, v);

    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= m; i++)
    {
        int x = col[oldG[i].from],
            y = col[oldG[i].to];
        if (x != y)
        {
            anew(x, y);
            in[y]++;
        }
    }

    topo();

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dist[i]);
    cout << ans;
    return 0;
}
