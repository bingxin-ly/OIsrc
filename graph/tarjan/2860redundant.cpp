#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 10, M = 1e4 + 10;
int idx, head[N];
pair<int, int> e[M << 1];
auto add = [](int u, int v)
{ e[idx].first = v, e[idx].second = head[u], head[u] = idx++; };

int dcnt, dfn[N], low[N];
int stk[N], top;
int ccnt, col[N], vis[M << 1];
void tarjan(int cur)
{
    dfn[cur] = low[cur] = ++dcnt;
    stk[++top] = cur;
    for (int i = head[cur]; ~i; i = e[i].second)
        if (!vis[i])
        {
            vis[i] = vis[i ^ 1] = true;
            int to = e[i].first;
            if (!dfn[to])
            {
                tarjan(to);
                low[cur] = min(low[cur], low[to]);
            }
            else
                low[cur] = min(low[cur], dfn[to]);
        }
    if (low[cur] == dfn[cur])
    {
        /* int tmp;
        ccnt++;
        do
        {
            tmp = stk[top--];
            col[tmp] = ccnt;
            vis[tmp] = false;
        } while (tmp != cur); */
        col[cur] = ++ccnt;
        while (stk[top] != cur)
            col[stk[top]] = ccnt, top--;
        top--;
    }
}

int u[M], v[M], du[N];
int main()
{
    memset(head, -1, sizeof(head));

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> u[i] >> v[i];
        add(u[i], v[i]), add(v[i], u[i]);
    }

    // tarjan
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);

    for (int i = 1; i <= m; i++)
        if (col[u[i]] != col[v[i]])
            du[col[u[i]]]++, du[col[v[i]]]++;

    int ans = 0;
    for (int i = 1; i <= ccnt; i++)
        if (du[i] == 1)
            ans++;
    cout << ((ans + 1) >> 1);
    return 0;
}