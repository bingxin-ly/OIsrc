#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
vector<int> graph[N];

inline void add(int u, int v)
{
    graph[u].push_back(v);
}

int dcnt, dfn[N], low[N];
// int stk[N], top;
int ccnt, col[N], vis[N];
stack<int> stk;
void tarjan(int cur)
{
    dfn[cur] = low[cur] = ++dcnt;
    // stk[++top] = cur;
    stk.push(cur);
    vis[cur] = true;
    for (auto to : graph[cur])
        if (!dfn[to])
        {
            tarjan(to);
            low[cur] = min(low[cur], low[to]);
        }
        else if (vis[to])
            low[cur] = min(low[cur], low[to]);
    if (low[cur] == dfn[cur])
    {
        int tmp;
        ccnt++;
        do
        {
            // tmp = stk[top--];
            tmp = stk.top(), stk.pop();
            col[tmp] = ccnt;
            vis[tmp] = false;
        } while (tmp != cur);
    }
}

int in[N], out[N];
int main()
{
    int n;
    cin >> n;
    for (int i = 1, v; i <= n; i++)
        while (cin >> v && v)
            add(i, v);

    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
        {
            int u = col[i], v = col[j];
            if (u != v)
                in[v]++, out[u]++;
        }

    int incnt = 0, outcnt = 0;
    for (int i = 1; i <= ccnt; i++)
    {
        if (!in[i])
            incnt++;
        if (!out[i])
            outcnt++;
    }

    cout << incnt << endl
         << (ccnt == 1 ? 0 : max(incnt, outcnt));
    return 0;
}
