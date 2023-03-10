int n;               // 总点数
int dist[N], cnt[N]; // dist[x]存储1号点到x的最短距离，cnt[x]存储1到x的最短路中经过的点数
bool st[N];          // 存储每个点是否在队列中

// 如果存在负环，则返回true，否则返回false。
bool spfa()
{
    // 不需要初始化dist数组
    // 原理：如果某条最短路径上有n个点（除了自己），那么加上自己之后一共有n+1个点，由抽屉原理一定有两个点相同，所以存在环。

    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        q.push(i);
        st[i] = true;
    }

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        st[t] = false;

        for (auto i : graph[t])
        {
            int j = i.to;
            if (dist[j] > dist[t] + i.w)
            {
                dist[j] = dist[t] + i.w;
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n)
                    return true; // 如果从1号点到x的最短路中包含至少n个点（不包括自己），则说明存在环
                if (!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    return false;
}

// 另一种可能的实现，某种程度上适用更广
bool spfa(int s)
{
    queue<int> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, vis[s] = true;
    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if (dis[v] > dis[u] + e[i].w)
            {
                dis[v] = dis[u] + e[i].w;
                if (!vis[v])
                {
                    vis[v] = 1, tot[v]++;
                    if (tot[v] == n + 1)
                        return true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}
