#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int head[N], idx = 1;
struct
{
    int to, nxt;
} edge[N << 1];
inline void add(int u, int v)
{
    edge[++idx] = {v, head[u]};
    head[u] = idx;
}

int cnt[N], color[N], son[N], size[N], ans[N], heavy, sum;
void dfs1(int u, int p) // 预处理子树大小
{
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (v == p)
            continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
void cal(int u, int p, int val) // 计算答案
{
    if (!cnt[color[u]])
        ++sum; // 在当前树中统计这种颜色
    cnt[color[u]] += val;
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (v == p || v == heavy) // 避开根的重儿子
            continue;
        cal(v, u, val);
    }
}
void dsu(int u, int p, bool keep) // 启发式合并的主体。keep 为 false 表示这次操作由轻边遍历得到，需要清空
{
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (v == p || v == son[u])
            continue;
        dsu(v, u, false); // 轻儿子
    }
    if (son[u])
        dsu(son[u], u, true), heavy = son[u]; // 重儿子
    cal(u, p, 1);
    heavy = 0;    // 重新扫描轻儿子，二次统计
    ans[u] = sum; // 那么现在的颜色数就是u的信息
    if (!keep)    // 清空当前的统计数
    {
        cal(u, p, -1);
        sum = 0;
    }
}
int main()
{
    cout << (1 << -1) << endl;
    /* int n;
    cin >> n;
    int u, v;
    for (int i = 1; i < n; ++i)
    {
        read(u), read(v);
        insert(u, v), insert(v, u);
    }
    for (int i = 1; i <= n; ++i)
        read(color[i]);
    dfs1(1, 0);
    dsu(1, 0, 1);

    int m;
    cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        read(v);
        printf("%d\n", ans[v]);
    } */
    return 0;
}