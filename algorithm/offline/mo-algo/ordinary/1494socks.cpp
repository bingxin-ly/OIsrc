#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e4 + 5;
int n, m, len;
int s[N], res, cnt[N];
pair<int, int> ans[N];
struct
{
    int id, l, r;
} q[N];
inline void add(int x) { res += cnt[x], cnt[x] += 1; }
inline void del(int x) { cnt[x] -= 1, res -= cnt[x]; }

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    len = n / sqrt(m);
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    for (int i = 1; i <= m; i++)
        q[i].id = i, cin >> q[i].l >> q[i].r;
    sort(q + 1, q + m + 1, [](const auto &x, const auto &y)
         {  int i = x.l / len, j = y.l / len;
            return i < j || (!(j < i) && ((i & 1) ? (x.r < y.r) : (x.r > y.r))); });

    int i = 0, j = 1;
    for (int k = 1; k <= m; k++)
    {
        int l = q[k].l, r = q[k].r;
        if (l == r)
            continue;
        while (i < r)
            add(s[++i]);
        while (j > l)
            add(s[--j]);
        while (i > r)
            del(s[i--]);
        while (j < l)
            del(s[j++]);
        ans[q[k].id] = {res, (r - l + 1ll) * (r - l) >> 1};
    }

    for (int k = 1; k <= m; k++)
    {
        int nume = ans[k].first, deno = ans[k].second;
        if (!deno)
        {
            cout << "0/1\n";
            continue;
        }
        int gcd = __gcd(nume, deno);
        cout << nume / gcd << '/' << deno / gcd << '\n';
    }
    return 0;
}