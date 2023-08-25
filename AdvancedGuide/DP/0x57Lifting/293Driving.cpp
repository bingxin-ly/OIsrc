#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5, INF = 0x3f3f3f3f;
signed main()
{
    static int n, h[N];
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    static int ner[N], sec[N];
    {
        multiset<pair<int, int>> nxt{{INF, 0}, {INF, 0}, {~INF, 0}, {~INF, 0}};
        multiset<pair<int, int>>::iterator pos, ppre, pre, suf, ssuf;
        for (int i = n; i >= 1; i--)
        {
            pos = nxt.emplace(h[i], i);
            suf = ++pos, ssuf = ++suf, --suf, --pos;
            pre = --pos, ppre = --pre, ++pre, ++pos;
            if (pre->first != ~INF && abs(pre->first - h[i]) <= abs(suf->first - h[i]))
                ner[i] = pre->second,
                sec[i] = abs(ppre->first - h[i]) <= abs(suf->first - h[i])
                             ? ppre->second
                             : suf->second;
            else
                ner[i] = suf->second,
                sec[i] = pre->first != ~INF && abs(pre->first - h[i]) <= abs(ssuf->first - h[i])
                             ? pre->second
                             : ssuf->second;
        }
    }
    static int f[18][N][2], a[18][N][2], b[18][N][2];
    static const int lg = __lg(n) - 1;
    {
        for (int j = 1; j <= n; j++)
            f[0][j][0] = ner[j], f[0][j][1] = sec[j];
        for (int j = 1; j <= n; j++)
            f[1][j][0] = f[0][f[0][j][0]][1], f[1][j][1] = f[0][f[0][j][1]][0];
        for (int i = 2; i <= lg; i++)
            for (int j = 1; j <= n; j++)
                f[i][j][0] = f[i - 1][f[i - 1][j][0]][0],
                f[i][j][1] = f[i - 1][f[i - 1][j][1]][1];
    }
    {
        for (int j = 1; j <= n; j++)
            a[0][j][0] = abs(h[j] - h[ner[j]]), a[0][j][1] = 0;
        for (int j = 1; j <= n; j++)
            a[1][j][0] = a[0][j][0], a[1][j][1] = a[0][f[0][j][1]][0];
        for (int i = 2; i <= lg; i++)
            for (int j = 1; j <= n; j++)
                a[i][j][0] = a[i - 1][j][0] + a[i - 1][f[i - 1][j][0]][0],
                a[i][j][1] = a[i - 1][j][1] + a[i - 1][f[i - 1][j][1]][1];
    }
    {
        for (int j = 1; j <= n; j++)
            b[0][j][0] = 0, b[0][j][1] = abs(h[j] - h[sec[j]]);
        for (int j = 1; j <= n; j++)
            b[1][j][0] = b[0][f[0][j][0]][1], b[1][j][1] = b[0][j][1];
        for (int i = 2; i <= lg; i++)
            for (int j = 1; j <= n; j++)
                b[i][j][0] = b[i - 1][j][0] + b[i - 1][f[i - 1][j][0]][0],
                b[i][j][1] = b[i - 1][j][1] + b[i - 1][f[i - 1][j][1]][1];
    }
    auto calc = [&](int s, int x, int &A, int &B)
    {
        A = 0, B = 0;
        for (int i = lg; i >= 0; i--)
            if (f[i][s][1] && A + B + a[i][s][1] + b[i][s][1] <= x)
                A += b[i][s][1], B += a[i][s][1], s = f[i][s][1];
    };
    {
        int s, x, a, b;
        double pre, cur;
        s = 1, cin >> x;
        calc(s, x, a, b), pre = b ? 1.0 * a / b : INF;
        for (int j = 2; j <= n; j++)
        {
            calc(j, x, a, b), cur = b ? 1.0 * a / b : INF;
            if (cur < pre || abs(pre - cur) < 1e-6 && h[j] > h[s])
                pre = cur, s = j;
        }
        cout << s << '\n';
    }
    {
        int m;
        cin >> m;
        for (int i = 1, s, x, a, b; i <= m; i++)
            cin >> s >> x, calc(s, x, a, b), cout << a << ' ' << b << '\n';
    }
    return 0;
}