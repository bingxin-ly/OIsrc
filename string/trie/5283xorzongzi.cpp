#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e7 + 10;
struct node
{
    int id, rk, w;
    bool operator<(const node &o) const { return w < o.w; }
};
priority_queue<node> q;
int tot, trie[N][2], size[N];
int s[N];

void insert(int x)
{
    int u = 0;
    for (int i = 31; i >= 0; i--)
    {
        int ch = (x >> i) & 1;
        size[u]++;
        if (!trie[u][ch])
            trie[u][ch] = ++tot;
        u = trie[u][ch];
    }
    size[u]++;
}

int query(int x, int rk)
{
    int u = 0, ans = 0;
    for (int i = 31; i >= 0; i--)
    {
        int ch = (x >> i) & 1;
        if (!trie[u][ch ^ 1])
            u = trie[u][ch];
        else if (rk <= size[trie[u][ch ^ 1]])
            u = trie[u][ch ^ 1], ans |= 1ll << i;
        else
            rk -= size[trie[u][ch ^ 1]], u = trie[u][ch];
    }
    return ans;
}

signed main()
{
    int n, m;
    scanf("%lld%lld", &n, &m), m <<= 1;
    for (int i = 1, x; i <= n; i++)
        scanf("%lld", &x), s[i] = s[i - 1] ^ x;
    for (int i = 0; i <= n; i++)
        insert(s[i]);
    for (int i = 0; i <= n; i++)
        q.push({i, 1, query(s[i], 1)});

    int ans = 1;
    for (int i = 1; i <= m; i++)
    {
        auto t = q.top();
        q.pop();
        ans += t.w;

        if (t.rk < n)
            q.push({t.id, t.rk + 1, query(s[t.id], t.rk + 1)});
    }
    cout << (ans >> 1) << endl;
    return 0;
}