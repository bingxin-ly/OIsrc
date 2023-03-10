#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> int_pair;
const int MAX = 1e5 + 10;

int dist[MAX], cnt[MAX], mod = 100003;
vector<int_pair> graph[MAX];
bool st[MAX];

inline void add(int a, int b, // 新建一条a->b的边
                int w = 1)    // 边权为w
{
    graph[a].push_back({b, w});
    graph[b].push_back({a, w});
}
void dijkstra(int start = 1)
{
    for (int i = 0; i < MAX; i++)
        dist[i] = INT_MAX;
    dist[start] = 0;
    cnt[1] = 1;

    priority_queue<int_pair, vector<int_pair>, greater<>> heap;
    heap.push({0, start});

    while (!heap.empty())
    {
        auto t = heap.top();
        heap.pop();
        int distance = t.first, idx = t.second;
        if (st[idx])
            continue;
        st[idx] = true;

        for (auto i : graph[idx])
        {
            int j = i.first;
            if (dist[j] > distance + i.second)
            {
                dist[j] = distance + i.second;
                cnt[j] = cnt[idx];
                heap.push({dist[j], j});
            }
            else if (dist[j] == distance + i.second)
                cnt[j] += cnt[idx], cnt[j] %= mod;
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    int u, v;
    while (m--)
    {
        cin >> u >> v;
        add(u, v);
    }
    dijkstra();
    for (int i = 1; i <= n; i++)
        cout << cnt[i] << endl;
    return 0;
}