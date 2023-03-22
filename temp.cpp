#include <cstdio>
#include <stack>
#define MAXN 10005
#define MAXM 5000005
using namespace std;
int n;
int index, low[MAXN], dfn[MAXN];
stack<int> s;
int f[MAXN];
int scc_cnt, scc[MAXN];
int In, Out, in[MAXN], out[MAXN];
int max(int x, int y) { return x > y ? x : y; }
struct graph
{
    int tot, hd[MAXN];
    int nxt[MAXM], to[MAXM];
    void add(int x, int y)
    {
        tot++;
        nxt[tot] = hd[x];
        hd[x] = tot;
        to[tot] = y;
    }
} g;
void Tarjan(int x)
{
    dfn[x] = low[x] = ++index;
    s.push(x);
    f[x] = true;
    for (int i = g.hd[x]; i; i = g.nxt[i])
        if (!dfn[g.to[i]])
        {
            Tarjan(g.to[i]);
            low[x] = min(low[x], low[g.to[i]]);
        }
        else if (f[g.to[i]])
            low[x] = min(low[x], dfn[g.to[i]]);
    if (dfn[x] == low[x])
    {
        scc[x] = ++scc_cnt;
        while (s.top() != x)
        {
            scc[s.top()] = scc_cnt;
            f[s.top()] = false;
            s.pop();
        }
        f[x] = false;
        s.pop();
    }
    return;
} // 板子，不多说。
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int v;
        while (scanf("%d", &v) && v)
            g.add(i, v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i); // 先做Tarjan
    for (int i = 1; i <= n; i++)
        for (int j = g.hd[i]; j; j = g.nxt[j])
        {
            int u = scc[i], v = scc[g.to[j]];
            if (v != u) // 不在同一个强连通分量里
            {
                in[v]++;
                out[u]++;
                // 记录他们的入度和出度
            }
        }
    for (int i = 1; i <= scc_cnt; i++)
    {
        if (!in[i])
            In++;
        if (!out[i])
            Out++;
        // 分别记录入度为0的点的数量和出度为0的点的数量
    }
    printf("%d\n", In); // 第一问
    if (scc_cnt == 1)
        printf("0");
    else
        printf("%d", max(In, Out));
    // 第二问，记得特判
    return 0;
}
