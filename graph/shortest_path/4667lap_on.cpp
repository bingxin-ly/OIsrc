#pragma GCC optimize(2) // 这个版本要O2优化
#include <bits/stdc++.h>
using namespace std;

const int MAX = 5e2 + 10;

int n, m, cnt, sum, tot;
char chars[MAX];
int head[4 * MAX * MAX], dist[4 * MAX * MAX];
int mark[MAX][MAX];

struct edge
{
    int next, w, v;
} e[4 * MAX * MAX];

void add(int u, int v, int w)
{
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
    e[++cnt].v = u;
    e[cnt].w = w;
    e[cnt].next = head[v], head[v] = cnt;
}
// typedef pair<int, int> node;
struct node
{
    int first, second;
    bool operator<(const node &rhs) const
    {
        return second > rhs.second;
    }
};
void Dijkstra()
{
    sum = (m + 1) * (n + 1);
    priority_queue<node> q;
    for (int i = 1; i <= sum; i++)
        dist[i] = INT_MAX;
    dist[1] = 0;
    q.push((node){1, dist[1]});
    while (!q.empty())
    {
        node x = q.top();
        q.pop();
        int u = x.first;
        if (x.second != dist[u])
            continue;
        for (int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v, w = e[i].w;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                q.push((node){v, dist[v]});
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n + 1; ++i)
        for (int j = 1; j <= m + 1; ++j)
            mark[i][j] = ++tot;

    for (int i = 1; i <= n; ++i)
    {
        cin >> chars;
        for (int j = 1; j <= m; ++j)
        {
            add(mark[i][j], mark[i + 1][j + 1], chars[j - 1] == '/'),
                add(mark[i + 1][j], mark[i][j + 1], chars[j - 1] == '\\');
        }
    }
    Dijkstra();

    if (dist[sum] == INT_MAX)
        cout << "NO SOLUTION";
    else
        cout << dist[sum];
    return 0;
}