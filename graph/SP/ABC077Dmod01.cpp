#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int k, dis[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> k;
    deque<int> q;
    q.emplace_back(1);
    memset(dis, 0x3f, sizeof(dis)), dis[1] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        if (!u)
            cout << dis[u], exit(0);
        int v = (u + 1) % k;
        if (dis[v] > dis[u] + 1)
            dis[v] = dis[u] + 1, q.emplace_back(v);
        v = 10 * u % k;
        if (dis[v] > dis[u])
            dis[v] = dis[u], q.emplace_front(v);
    }
    return 0;
}