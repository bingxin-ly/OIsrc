#include <bits/stdc++.h>
using namespace std;

const int MAX = 3e2 + 10;
int n, m, f[MAX][MAX];
int head[MAX], cnt;

struct edge
{
    int pre, to;
} edges[MAX];
vector<edge> courses[MAX];

void add(int u, int v)
{
    edges[++cnt].pre = head[u];
    edges[cnt].to = v;
    head[u] = cnt;
}
void dp(int u)
{
    for (int i = head[u]; i; i = edges[i].pre)
    {
        int son = edges[i].to;
        dp(son);
        for (int j = m + 1; j > 0; j--)
            for (int k = 0; k < j; k++)
                f[u][j] = max(f[u][j], f[son][k] + f[u][j - k]);
    }
}
void solve(int u)
{
    for (int i = head[u]; i; i = edges[i].pre)
        solve(edges[i].to);

    for (int i = head[u]; i; i = edges[i].pre)
        for (int j = m, son = edges[i].to; j > 0; j--)
            for (int k = 0; k < j; ++k)
                f[u][j] = max(f[u][j], f[u][j - k] + f[son][k]);
}

int main()
{
    cin >> n >> m;
    int pre, credit;
    for (int i = 1; i <= n; i++)
    {
        cin >> pre >> credit;
        f[i][1] = credit;
        add(pre, i);
    }
    dp(0);
    cout << f[0][m + 1] << endl;
    /* m++;
    solve(0);
    cout << f[0][m] << endl; */
    return 0;
}
