#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int N = 3e5 + 5, S = 2e3 + 5, K = 1e2 + 5, INF = 0x3f3f3f3f;
int n, m, T, poi[N];
int hed[N], nxt[N << 2], rch[N << 2], val[N << 2], idx;
void link(int u, int v, int w)
{
    nxt[++idx] = hed[u], hed[u] = idx, rch[idx] = v, val[idx] = w;
    nxt[++idx] = hed[v], hed[v] = idx, rch[idx] = u, val[idx] = w;
}

int trs(int i, int j) { return (m + 1) * i + j; }
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> T;
    for (int i = 1, w, p; i < n; i++)
        for (int j = 1; j <= m; j++)
            p = trs(i, j - 1), cin >> w, link(p, p + 1, w);
    for (int i = 1, w, p; i <= n; i++)
        for (int j = 1; j < m; j++)
            p = trs(i - 1, j), cin >> w, link(p, p + m + 1, w);
    for (int i = 1; i <= (n + m) << 1; i++)
        if (i <= m)
            poi[i] = trs(0, i - 1);
        else if (i <= m + n)
            poi[i] = trs(i - m - 1, m);
        else if (i <= 2 * m + n)
            poi[i] = trs(n, 2 * m + n + 1 - i);
        else
            poi[i] = trs(2 * m + 2 * n + 1 - i, 0);
    const int ori = idx;

    while (T--)
    {
        for (int i = 0; i < (n + 1) * (m + 1); i++)
            while (hed[i] > ori)
                hed[i] = nxt[hed[i]];
        idx = ori;

        static int col[S], cst[S], k;
        memset(col, -1, sizeof(col)), memset(cst, 0, sizeof(cst)), cin >> k;
        for (int i = 1, w, p, c; i <= k; i++)
            cin >> w >> p >> c, col[p] = c, cst[p] = w;
        for (int i = 1; i <= (n + m) << 1; i++)
            if (i <= m)
                link(poi[i], poi[i] + 1, cst[i]);
            else if (i <= m + n)
                link(poi[i], poi[i] + m + 1, cst[i]);
            else if (i <= 2 * m + n)
                link(poi[i], poi[i] - 1, cst[i]);
            else
                link(poi[i], poi[i] - m - 1, cst[i]);

        vector<vector<int>> outer;
        int fir = 0, lst = 0;
        for (int i = 1; i <= (n + m) << 1; i++)
        {
            if (col[i] == -1)
                continue;
            if (!fir)
                fir = i;
            else if (col[lst] != col[i])
            {
                vector<int> inner;
                for (int j = lst + 1; j <= i; j++)
                    inner.emplace_back(poi[j]);
                outer.emplace_back(inner);
            }
            lst = i;
        }
        if (col[lst] != col[fir])
        {
            vector<int> inner;
            for (int i = lst + 1; i <= (n + m) << 1; i++)
                inner.emplace_back(poi[i]);
            for (int i = 1; i <= fir; i++)
                inner.emplace_back(poi[i]);
            outer.emplace_back(inner);
        }
        if (outer.empty())
        {
            cout << "0\n";
            continue;
        }

        static int w[K][K], f[K][K];
        memset(w, 0x3f, sizeof(w)), memset(f, 0x3f, sizeof(f)), k = outer.size();
        for (int i = 0; i < k; i += 2)
        {
            static int dis[N];
            memset(dis, 0x3f, sizeof(dis));
            priority_queue<pii, vector<pii>, greater<>> q;
            for (int u : outer[i])
                q.emplace(dis[u] = 0, u);
            while (!q.empty())
            {
                int pre = q.top().first, u = q.top().second;
                q.pop();
                if (pre != dis[u]) continue;
                for (int e = hed[u]; e; e = nxt[e])
                {
                    int v = rch[e], cur = pre + val[e];
                    if (dis[v] > cur) q.emplace(dis[v] = cur, v);
                }
            }
            for (int j = 0; j < k; j++)
            {
                for (int u : outer[j])
                    w[i][j] = min(w[i][j], dis[u]);
                w[j][i] = w[i][j];
            }
        }
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++)
                w[i + k][j] = w[i][j + k] = w[i + k][j + k] = w[i][j];
        for (int i = 1; i <= k << 1; i++)
            f[i][i - 1] = 0;
        for (int i = 2; i <= k; i++)
            for (int l = 1; l <= (k << 1) - i + 1; l++)
            {
                int r = l + i - 1;
                f[l][r] = f[l + 1][r - 1] + w[l][r];
                for (int x = l + 1; x < r; x += 2)
                    f[l][r] = min(f[l][r], f[l][x] + f[x + 1][r]);
            }
        int ans = INF;
        for (int i = 0; i < k; i++)
            ans = min(ans, f[i][i + k - 1]);
        cout << ans << '\n';
    }
    return 0;
}