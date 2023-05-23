#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
// ACAM
int cnt, nd[N];
struct node
{
    int son[26], tree[26];
    int fail, end, fa;
    int &operator[](int x) { return son[x]; }
} trie[N];

void get_fail()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (trie[0][i])
            q.push(trie[0][i]);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < 26; i++)
        {
            int &v = trie[u][i];
            if (v)
            {
                trie[v].fail = trie[trie[u].fail][i];
                q.push(v);
            }
            else
                v = trie[trie[u].fail][i];
        }
    }
}

// GRAPH
vector<int> graph[N];
void contact(int u, int v) { graph[u].push_back(v); }

struct query
{
    int x, y, id, ans;
    bool operator<(const query &otr) const { return y < otr.y; }
} q[N];
int ql[N], qr[N];

// FAILTR
int tim, dfn[N], low[N];
namespace BIT
{
    int v[N];
    inline int lowbit(int x) { return x & -x; }
    void add(int p, int x)
    {
        for (; p <= tim; p += lowbit(p))
            v[p] += x;
    }
    int presum(int p)
    {
        int res = 0;
        for (; p; p -= lowbit(p))
            res += v[p];
        return res;
    }
    inline int query(int l, int r) { return presum(r) - presum(l - 1); }
}
void init(int u)
{
    dfn[u] = ++tim;
    for (auto i : graph[u])
        init(i);
    low[u] = tim; // 叶子
}
void dfs(int u)
{
    BIT::add(dfn[u], 1);
    int qid = trie[u].end;
    if (qid)
        for (int i = ql[qid]; i <= qr[qid]; i++)
            q[i].ans = BIT::query(dfn[nd[q[i].x]], low[nd[q[i].x]]);

    for (int i = 0; i < 26; i++)
        if (trie[u].tree[i])
            dfs(trie[u].tree[i]);
    BIT::add(dfn[u], -1);
}

char str[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    cin >> str;
    int now = 0, n = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == 'P')
            nd[++n] = now, trie[now].end = n;
        else if (str[i] == 'B')
            now = trie[now].fa;
        else
        {
            int ch = str[i] - 'a';
            if (!trie[now][ch])
                trie[now][ch] = ++cnt, trie[cnt].fa = now;
            now = trie[now][ch];
        }

    for (int i = 0; i <= cnt; i++)
        for (int j = 0; j < 26; j++)
            trie[i].tree[j] = trie[i][j];

    get_fail();
    for (int i = 1; i <= cnt; i++)
        contact(trie[i].fail, i);
    init(0);

    int qlen;
    cin >> qlen;
    for (int i = 1; i <= qlen; i++)
        cin >> q[i].x >> q[i].y, q[i].id = i;
    sort(q + 1, q + qlen + 1);

    for (int i = 1, pos = 1; i <= qlen; i = pos)
    {
        ql[q[i].y] = i;
        while (q[pos].y == q[i].y)
            pos++;
        qr[q[i].y] = pos - 1;
    }
    dfs(0);
    int ans[N];
    for (int i = 1; i <= qlen; i++)
        ans[q[i].id] = q[i].ans;
    for (int i = 1; i <= qlen; i++)
        cout << ans[i] << '\n';
    return 0;
}