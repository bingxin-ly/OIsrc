#include <bits/stdc++.h>
using namespace std;
int m;
vector<int> head[110];
queue<int> qu;
bool vis[110];
int dep[110];

void add(int x, int y)
{
    head[x].push_back(y);
}
void bfs(int n)
{
    qu.push(n);
    dep[n] = 1;
    vis[n] = true;
    while (!qu.empty())
    {
        int u = qu.front();
        qu.pop();
        cout << dep[u] << ' ' << u << endl;
        int sz = head[u].size();
        for (int i = 0; i < sz; i++)
        {
            int v = head[u][i];
            if (!vis[v])
            {
                qu.push(v);
                dep[v] = dep[u] + 1;
                vis[v] = true;
            }
        }
    }
}

int main()
{
    cin >> m;
    for (int i = 0, u, v; i < m; i++)
    {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    int s;
    cin >> s;
    bfs(s);
    return 0;
}