#include <stdio.h>
#include <string.h>

#define MAX 5009
#define MAX2 100009
int h[MAX], e[MAX2], ne[MAX2], ww[MAX2], idx,
    tot[MAX], dis[MAX], vis[MAX],
    n, m, cnt,
    qu[2000000], hhead, ttail = -1;

void read(int *x)
{
    int o = 1, p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            o = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        p = (p << 3) + (p << 1) + c - '0',
        c = getchar();
    *x = (o * p);
}
void write(int x)
{
    if (x < 0)
        putchar('-'),
            x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
void addedge(int u, int v, int w)
{
    e[++idx] = v,
    ww[idx] = w,
    ne[idx] = h[u],
    h[u] = idx;
}
int spfa(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, vis[s] = 1,
    qu[++ttail] = s;

    while (hhead <= ttail)
    {
        int u = qu[hhead++];
        vis[u] = 0;
        for (register int i = h[u]; i; i = ne[i])
        {
            int v = e[i];
            if (dis[v] > dis[u] + ww[i])
            {
                dis[v] = dis[u] + ww[i];
                if (!vis[v])
                {
                    vis[v] = 1, ++tot[v];
                    if (tot[v] == n + 1)
                        return 1;
                    qu[++ttail] = v;
                }
            }
        }
    }
    return 0;
}
int main()
{
    read(&n), read(&m);
    for (register int i = 1; i <= n; ++i)
        addedge(0, i, 0); // 虚点0
    int v, u, w;
    for (register int i = 1; i <= m; ++i)
    {
        read(&v), read(&u), read(&w);
        addedge(u, v, w);
    }
    if (spfa(0))
        puts("NO");
    else
        for (register int i = 1; i <= n; ++i)
            write(dis[i]), putchar(' ');
    return 0;
}
