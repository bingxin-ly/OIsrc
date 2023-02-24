#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 10;

struct edge
{
    int to, w;
};
vector<edge> graph[MAX];
int dist[MAX];
bool st[MAX];

inline void add(int a, int b, // 新建一条a->b的边
                int w = 1)    // 边权为w
{
    graph[a].push_back({b, w});
}

typedef pair<int, int> int_pair;
void dijkstra(int start = 1)
{
    for (int i = 0; i < MAX; i++)
        dist[i] = INT_MAX;
    dist[start] = 0;

    priority_queue<int_pair, vector<int_pair>, greater<>> heap;
    heap.push({0, start});

    while (!heap.empty())
    {
        auto t = heap.top();
        heap.pop();
        int distance = t.first, ver = t.second;
        if (st[ver])
            continue;
        st[ver] = true;

        for (auto i : graph[ver])
        {
            int j = i.to;
            if (dist[j] > distance + i.w)
            {
                dist[j] = distance + i.w;
                heap.push({dist[j], j});
            }
        }
    }
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    int u, v, w;
    while (m--)
    {
        cin >> u >> v >> w;
        add(u, v, w);
    }
    dijkstra(s);
    for (int i = 1; i <= n; i++)
        cout << dist[i] << ' ';
    return 0;
}