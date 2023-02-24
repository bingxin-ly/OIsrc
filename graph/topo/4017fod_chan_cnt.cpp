#include <bits/stdc++.h>
using namespace std;

const int MOD = 80112002;
const int MAXN = 5e3 + 10, MAXM = 5e5 + 10;

int n, m, ans;
int in[MAXN], out[MAXN], f[MAXN];
queue<int> q;
int h[MAXN], e[MAXM], ne[MAXM], idx;

void add(int a, int b)
{
    e[++idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
}

int main()
{
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        add(u, v);
        out[u]++, in[v]++;
    }
    for (int i = 1; i <= n; i++)
        if (!in[i])
        {
            f[i] = 1;
            q.push(i);
        }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = h[u]; i; i = ne[i])
        {
            int v = e[i];
            f[v] += f[u];
            f[v] %= MOD;
            in[v]--;
            if (!in[v])
            {
                if (!out[v])
                    ans += f[v], ans %= MOD;
                else
                    q.push(v);
            }
        }
    }
    cout << ans;
}
