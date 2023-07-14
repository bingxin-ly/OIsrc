#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 5;
int n, m, v[N], w[N], c[N], f[N];

int parse(const string &s)
{
    int h = 0, m = 0, p = s.find(':'), l = s.size();
    for (int i = 0; i < p; i++)
        h = h * 10 + (s[i] - '0');
    for (int i = p + 1; i < l; i++)
        m = m * 10 + (s[i] - '0');
    return h * 60 + m;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string s, t;
    cin >> s >> t >> n;
    m = parse(t) - parse(s);
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i] >> c[i], c[i] += !c[i] * 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 0; k <= c[i] && v[i] * k <= j; k++)
                f[j] = max(f[j], f[j - v[i] * k] + w[i] * k);
    cout << f[m];
    return 0;
}