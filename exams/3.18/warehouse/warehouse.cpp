#include <bits/stdc++.h>
using namespace std;
typedef long long big;

const int N = 1e5 + 10;

int n, m, cnt[N];
struct edge
{
    int to, w;
};
vector<edge> graph[N];

inline void add(int u, int v, int w)
{
    graph[u].push_back({v, w});
}

int dist[N];
bool st[N];

void spfa(int s)
{
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    st[s] = true;

    queue<int> q;
    q.push(s);

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        st[t] = false;

        for (auto v : graph[t])
        {
            int j = v.to;
            if (dist[j] > (dist[t] + v.w))
            {
                dist[j] = dist[t] + v.w;
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
    ios::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++)
    {
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }

    for (int i = 1; i <= n; i++)
    {
        spfa(i);
        big ans = 0;

        for (int j = 1; j <= n; j++)
            if (j != i)
                ans += (dist[j] ^ m);
        cout << ans << endl;
    }
    return 0;
}
