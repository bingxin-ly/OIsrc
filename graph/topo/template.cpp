queue<int> q;

bool toposort()
{
    // d[i] 存储点i的入度
    for (int i = 1; i <= n; i++)
        if (!d[i])
            q.push(i);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto i : graph[u])
        {
            int j = i.to;
            if (!--d[j])
                q.push(j);
        }
    }

    // 如果所有点都入队了，说明存在拓扑序列；否则不存在拓扑序列。
    return q.size() == n;
}
