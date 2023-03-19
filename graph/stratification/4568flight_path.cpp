#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10, M = 5e4 + 10, K = 10 + 1;
int n, m, k, s, t;
struct edge
{
    int to, w;
};
vector<edge> graph[N * K * 2];

inline void add(int u, int v, int w = 0)
{
    graph[u].push_back({v, w});
}
int dist[N * K];
bool st[N * K];

typedef pair<int, int> PII;
void dijkstra(int start = 1)
{
    memset(dist, 0x7f, sizeof(dist));
    dist[start] = 0;

    priority_queue<PII, vector<PII>, greater<>> heap;
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
    cin >> n >> m >> k;
    cin >> s >> t;
    for (int i = 1, u, v, c; i <= m; i++)
    {
        cin >> u >> v >> c;
        add(u, v, c), add(v, u, c);
        for (int j = 1; j <= k; j++)
        {
            add(u + (j - 1) * n, v + j * n), add(v + (j - 1) * n, u + j * n);
            add(u + j * n, v + j * n, c), add(v + j * n, u + j * n, c);
        }
    }
    for (int i = 1; i <= k; i++)
        add(t + (i - 1) * n, t + i * n);
    /* 这个预防奇葩数据就相当于检查 i * n + t，
    在中间的层数走到 t 就可以免费走到最上方的 t */

    dijkstra(s);
    cout << dist[t + k * n];
    return 0;
}