#include <bits/stdc++.h>
using namespace std;

const int N = 5e1 + 5, M = 1e3 + 10, K = 5e1 + 1;
int n, m, k;
struct edge
{
    int to, w;
};
vector<edge> graph[N * K];

inline void add(int u, int v, int w = 1)
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
    for (int i = 1, x, y, z; i <= m; i++)
    {
        cin >> x >> y >> z;
        for (int j = 0; j <= k; j++)
            add(j * n + x, j * n + y, z), add(j * n + y, j * n + x, z);
        for (int j = 0; j < k; j++)
            add(j * n + x, (j + 1) * n + y, z / 2), add(j * n + y, (j + 1) * n + x, z / 2);
    }

    dijkstra();
    int min = INT_MAX;
    for (int i = 0; i <= k; i++)
        if (min > dist[i * n + n])
            min = dist[i * n + n];
    cout << min;
    return 0;
}
