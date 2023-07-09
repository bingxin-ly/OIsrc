#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

constexpr int N = 2e6 + 5; // 值域相关
int n, m, k;
struct que
{
    int l, r, qid;
} q[N];
int xum[N], cnt[N];
long long res, ans[N];
inline void add(int x) { res += cnt[xum[x] ^ k], cnt[xum[x]] += 1; }
inline void del(int x) { cnt[xum[x]] -= 1, res -= cnt[xum[x] ^ k]; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    int len = sqrt(n);
    for (int i = 1; i <= n; i++)
        cin >> xum[i], xum[i] ^= xum[i - 1];
    for (int i = 1; i <= m; i++)
        cin >> q[i].l >> q[i].r, q[i].l -= 1, q[i].qid = i;
    sort(q + 1, q + m + 1, [len](const que &x, const que &y)
         {  int i = x.l / len, j = y.l / len;
            return i < j || (!(j < i) && ((i & 1) ? (x.r < y.r) : (x.r > y.r))); });

    int i = 0, j = 1;
    for (int k = 1; k <= m; k++)
    {
        int l = q[k].l, r = q[k].r;
        while (j > l)
            add(--j);
        while (j < l)
            del(j++);
        while (i < r)
            add(++i);
        while (i > r)
            del(i--);
        ans[q[k].qid] = res;
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << endl;
    return 0;
}