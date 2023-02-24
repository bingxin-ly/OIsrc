#include <bits/stdc++.h>

using namespace std;

const int N = 2e5;

int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool st[N];
queue<int> q;

void add(int u, int v, int c)
{
    e[++idx] = v;
    w[idx] = c;
    ne[idx] = h[u];
    h[u] = idx;
}

int SPFA(int s)
{
    memset(dist, ~0x3f, sizeof(dist));
    dist[s] = 0;
    st[s] = true;
    q.push(s);
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        st[t] = false;
        for (int i = h[t]; i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] < dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])
                {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }

    return dist[n] == ~0x3f3f3f3f ? -1 : dist[n];
}

int main()
{
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, add(u, v, w);

    cout << SPFA(1);

    return 0;
}