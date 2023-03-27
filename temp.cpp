#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 1e5 * 2 + 10;
struct edge
{
    int to, w;
};
vector<edge> graph[N];

inline void add(int u, int v, int w = 1)
{
    graph[u].push_back({v, w});
}

int dist[N];
bool st[N];

typedef pair<int, int> PII;
void dijkstra(int start)
{
    memset(dist, 0x3f, sizeof(dist));
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
void SPFA(int s)
{
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    st[s] = true;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        st[t] = false;
        for (auto i : graph[t])
        {
            int j = i.to;
            if (dist[j] > dist[t] + i.w)
            {
                dist[j] = dist[t] + i.w;
                if (!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}
int main()
{
    freopen("hack", "r", stdin);
    int n, m, s;
    cin >> n >> m >> s;
    clock_t st = clock();
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, add(u, v, w);
    dijkstra(1);
    cout << dist[n] << endl
         << "cost " << clock() - st << endl;
    return 0;
}
