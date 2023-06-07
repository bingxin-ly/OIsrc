#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int a[N];
vector<int> graph[N];
priority_queue<int> q[N];

void merge(int x, int y)
{
    if (q[x].size() < q[y].size())
        swap(q[x], q[y]);
    vector<int> t;
    while (q[y].size())
    {
        t.push_back(max(q[x].top(), q[y].top()));
        q[x].pop(), q[y].pop();
    }
    while (t.size())
        q[x].push(t.back()), t.pop_back();
}

void dfs(int u)
{
    for (auto i : graph[u])
        dfs(i), merge(u, i);
    q[u].push(a[u]);
}
signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 2, x; i <= n; i++)
        cin >> x, graph[x].push_back(i);

    dfs(1);
    long long ans = 0;
    while (q[1].size())
        ans += q[1].top(), q[1].pop();
    cout << ans;
    return 0;
}