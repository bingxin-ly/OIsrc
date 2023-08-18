#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, in[N];
vector<int> g[N];

void solve()
{
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[v].emplace_back(u), in[u] += 1;
    priority_queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i])
            q.emplace(i);
    stack<int> stk;
    while (!q.empty())
    {
        int u = q.top();
        q.pop();
        stk.emplace(u);
        for (int v : g[u])
            if (!--in[v])
                q.emplace(v);
    }
    if ((int)stk.size() != n)
        cout << "Impossible! ";
    else
        while (!stk.empty())
            cout << stk.top() << ' ', stk.pop();
    cout << '\n';
}
void clear()
{
    memset(in, 0, sizeof(in));
    for (int i = 1; i <= n; i++)
        g[i].clear();
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve(), clear();
    return 0;
}