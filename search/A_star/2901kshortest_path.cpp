#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10, M = 1e6 + 10;
int n, m, k;

vector<pair<int, int>> pos[N], neg[N];

int dist[N], vis[N];
void SPFA()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    vis[1] = true;

    queue<int> q;
    q.push(1);

    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        vis[t] = false;
        for (auto i : neg[t])
        {
            int j = i.first;
            if (dist[j] > dist[t] + i.second)
            {
                dist[j] = dist[t] + i.second;
                if (!vis[j])
                {
                    q.push(j);
                    vis[j] = true;
                }
            }
        }
    }
}

struct node
{
    int pos;
    long long len;
    bool operator<(const node &otr) const { return len + dist[pos] > otr.len + dist[otr.pos]; }
};
void A_star()
{
    priority_queue<node> q;
    q.push({n, 0});

    while (!q.empty())
    {
        node u = q.top();
        q.pop();

        if (u.pos == 1)
        {
            cout << u.len << endl;
            if ((--k) == 0)
                return;
        }
        for (auto i : pos[u.pos])
            q.push({i.first, u.len + i.second});
    }
}

int main()
{
    cin >> n >> m >> k;
    for (int i = 1, u, v, w; i <= m; i++)
    {
        cin >> u >> v >> w;
        pos[u].push_back({v, w});
        neg[v].push_back({u, w});
    }

    SPFA();

    A_star();

    while (k--)
        cout << -1 << endl;
    return 0;
}