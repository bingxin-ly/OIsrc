#include <bits/stdc++.h>
using namespace std;

const int N = 20010, M = 200010;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int color[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool dfs(int u, int c, int limit)
{
    color[u] = c;
    for (int i = h[u]; ~i; i = ne[i])
    {
        if (w[i] <= limit)
            continue;
        int j = e[i];
        if (color[j])
        {
            if (color[j] == c)
                return false;
        }
        else if (!dfs(j, 3 - c, limit))
            return false;
    }

    return true;
}

bool check(int limit)
{
    memset(color, 0, sizeof color);

    for (int i = 1; i <= n; i++)
        if (color[i] == 0)
            if (!dfs(i, 1, limit))
                return false;
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h);
    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }

    int l = 0, r = 1e9;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }

    printf("%d\n", l);
    return 0;
}