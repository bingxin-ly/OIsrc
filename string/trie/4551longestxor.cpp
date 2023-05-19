#include <vector>
#include <iostream>
using namespace std;

const int N = 2e6 + 10;
vector<pair<int, int> > graph[N];
int tot, sum[N], son[N][2];

void pre(int u, int fa)
{
    for (int i = 0; i < graph[u].size(); i++)
    {
        int v = graph[u][i].first, w = graph[u][i].second;
        if (v != fa)
            sum[v] = sum[u] ^ w, pre(v, u);
    }
}

void build(int val, int x)
{
    for (int i = (1 << 30); i; i >>= 1)
    {
        bool c = val & i;
        if (!son[x][c])
            son[x][c] = ++tot;
        x = son[x][c];
    }
}

int query(int val, int x)
{
    int ans = 0;
    for (int i = (1 << 30); i; i >>= 1)
    {
        bool c = val & i;
        if (son[x][!c])
            ans += i, x = son[x][!c];
        else
            x = son[x][c];
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(v, w)),
            graph[v].push_back(make_pair(u, w));
    }
    pre(1, 0);
    for (int i = 1; i <= n; i++)
        build(sum[i], 0);

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, query(sum[i], 0));
    cout << ans;
    return 0;
}