#include <bits/stdc++.h>
#define int long long
using namespace std;
void write(__int128 x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

constexpr int N = 1e5 + 5;
int n, m, in[N];
vector<int> g[N], res;

struct frac
{
    __int128 p, q;
    frac(int p = 0, int q = 1) : p(p), q(q) {}
    void reduce()
    {
        int d = __gcd(p, q);
        p /= d, q /= d;
    }
    frac operator/(int x)
    {
        frac ret(p, q * x);
        ret.reduce();
        return ret;
    }
    friend void operator+=(frac &x, frac y)
    {
        __int128 m = x.q * y.q / __gcd(x.q, y.q);
        x.p *= m / x.q, y.p *= m / y.q;
        x.p += y.p, x.q = m, x.reduce();
    }
} f[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, c; i <= n; i++)
    {
        cin >> c, g[i].resize(c);
        for (int j = 0; j < c; j++)
            cin >> g[i][j], in[g[i][j]]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i])
            q.emplace(i), f[i] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (!g[u].size())
        {
            res.emplace_back(u);
            continue;
        }
        frac c = f[u] / (int)g[u].size();
        for (int v : g[u])
        {
            f[v] += c;
            if (!--in[v])
                q.emplace(v);
        }
    }
    sort(res.begin(), res.end());
    for (int i : res)
        write(f[i].p), putchar(' '), write(f[i].q), putchar('\n');
    return 0;
}