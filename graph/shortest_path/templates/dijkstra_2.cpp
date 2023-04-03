#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10, M = 5e5 + 10;
typedef pair<int, int> PII;
vector<PII> graph[N];

int dist[N], vis[N];
void dijkstra(int s, int n)
{
    for (int i = 1; i <= n; i++)
        dist[i] = INT_MAX;
    dist[s] = 0;

    priority_queue<PII, vector<PII>, greater<>> heap;
    heap.push({0, s});

    while (!heap.empty())
    {
        auto t = heap.top();
        heap.pop();
        auto dis = t.first, ver = t.second;

        if (vis[ver])
            continue;
        vis[ver] = true;

        for (auto i : graph[ver])
        {
            int j = i.first;
            if (dist[j] > dis + i.second)
            {
                dist[j] = dis + i.second;
                heap.push({dist[j], j});
            }
        }
    }
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, graph[u].push_back({v, w});

    dijkstra(s, n);

    for (int i = 1; i <= n; i++)
        cout << dist[i] << ' ';
    return 0;
}
