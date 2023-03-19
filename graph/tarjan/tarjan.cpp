void tarjan(int cur)
{
    dfn[cur] = low[cur] = ++dcnt;
    stk[++stop] = cur;
    vis[cur] = true;
    for (register int i = head[cur]; i; i = e[i].nxt)
    {
        int to = e[i].to;
        if (!dfn[to])
        {
            tarjan(to);
            low[cur] = min(low[cur], low[to]);
        }
        else if (vis[to])
        {
            low[cur] = min(low[cur], low[to]);
        }
    }
    if (low[cur] == dfn[cur])
    {
        int tmp;
        ctot++;
        do
        {
            tmp = stk[stop--];
            col[tmp] = ctot;
            vis[tmp] = false;
        } while (tmp != cur);
    }
}
... for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i);
