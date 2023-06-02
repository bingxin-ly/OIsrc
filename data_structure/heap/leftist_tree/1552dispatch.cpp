#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int idx, head[N], edge[N], nxt[N];
void add(int u, int v) { edge[++idx] = v, nxt[idx] = head[u], head[u] = idx; }
int heap[N], siz[N], sum[N], ls[N], rs[N], dis[N]{-1};
int sa[N], lead[N];
int n, m, ans;

int merge(int x, int y)
{
    if (!x || !y)
        return x | y;

    // 大根堆
    if (sa[x] < sa[y])
        swap(x, y);
    rs[x] = merge(rs[x], y);
    if (dis[ls[x]] < dis[rs[x]])
        swap(ls[x], rs[x]);
    dis[x] = dis[rs[x]] + 1;
    return x;
}
void dfs(int u)
{
    heap[u] = u;
    siz[u] = 1, sum[u] = sa[u];
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        dfs(v);
        heap[u] = merge(heap[u], heap[v]);
        siz[u] += siz[v], sum[u] += sum[v];
    }
    while (sum[u] > m)
    {
        siz[u] -= 1, sum[u] -= sa[heap[u]];
        heap[u] = merge(ls[heap[u]], rs[heap[u]]);
    }
    ans = max(ans, lead[u] * siz[u]);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, p; i <= n; i++)
        cin >> p >> sa[i] >> lead[i], add(p, i);

    dfs(1);

    cout << ans;
    return 0;
}