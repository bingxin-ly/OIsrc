#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 10, MOD = 1e9 + 7;

vector<int> graph[MAX];
int n, k;
int f[MAX][110][2][2], g[110][2][2];
int size[MAX]; // 记录子树大小，dp时剪枝

inline void add(int u, int v)
{
    graph[u].push_back(v);
    graph[v].push_back(u);
}
inline void plss(int &a, ssize_t b)
{
    b %= MOD, a += b, a %= MOD;
}
/* f[u][i + j][0][0] = ∑f[u][i][0][0] * f[v][j][0][1];
 * f[u][i + j][1][0] = ∑f[u][i][1][0] * (f[v][j][0][0] + f[v][j][0][1]);
 * f[u][i + j][0][1] = ∑(f[u][i][0][1] * (f[v][j][0][1] + f[v][j][1][1]) +
 *                       f[u][i][0][0] * f[v][j][1][1]);
 * f[u][i + j][1][1] = ∑(f[u][i][1][0] * (f[v][j][1][0] + f[v][j][1][1]) +
 *                       f[u][i][1][1] * (f[v][j][0][0] + f[v][j][0][1] + f[v][j][1][0] + f[v][j][1][1]));
 */
void dp(int u, int p)
{
    size[u] = f[u][0][0][0] = f[u][1][1][0] = 1;
    for (auto a : graph[u])
    {
        int s = a;
        if (p == s)
            continue;
        dp(s, u);
        for (int i = 0; i <= k; i++)
        {
            g[i][0][0] = f[u][i][0][0], f[u][i][0][0] = 0;
            g[i][0][1] = f[u][i][0][1], f[u][i][0][1] = 0;
            g[i][1][0] = f[u][i][1][0], f[u][i][1][0] = 0;
            g[i][1][1] = f[u][i][1][1], f[u][i][1][1] = 0;
        }

        // for (int b = 0; b <= k; b++)
        //     for (int c = 0; c <= b; c++)
        // for (int b = 0; b <= min(size[u], k); b++)
        //     for (int c = 0; c <= min(size[s], b); c++)
        for (int b = 0; b <= k; b++)
            for (int c = 0; c <= min(size[s], b); c++)
            {
                plss(f[u][b][0][0], g[c][0][0] * (ssize_t)f[s][b - c][0][1]);

                plss(f[u][b][1][0], g[c][1][0] * ((ssize_t)f[s][b - c][0][0] + f[s][b - c][0][1]));

                plss(f[u][b][0][1], g[c][0][1] * ((ssize_t)f[s][b - c][0][1] + f[s][b - c][1][1]));
                plss(f[u][b][0][1], g[c][0][0] * (ssize_t)f[s][b - c][1][1]);

                plss(f[u][b][1][1], g[c][1][0] * ((ssize_t)f[s][b - c][1][0] + f[s][b - c][1][1]));
                plss(f[u][b][1][1], g[c][1][1] * // 四连加有可能溢出！！
                                        ((ssize_t)f[s][b - c][0][0] + f[s][b - c][0][1] + f[s][b - c][1][0] + f[s][b - c][1][1]));
            }
        size[u] += size[s];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1, u, v; i <= n - 1; i++)
        cin >> u >> v, add(u, v);

    dp(1, 0);
    cout << (f[1][k][0][1] + f[1][k][1][1]) % MOD;
    return 0;
}