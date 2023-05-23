#include <bits/stdc++.h>
using namespace std;

const int N = 1510, MOD = 1e9 + 7;
struct node
{
    int son[10], fail;
    int &operator[](int x) { return son[x]; }
} trie[N];
int cnt, fa[N], f[N][N][2], ed[N];

void insert(const char *s)
{
    int now = 0;
    for (int i = 0; s[i]; i++)
    {
        int ch = s[i] - '0';
        if (!trie[now][ch])
            trie[now][ch] = ++cnt;
        now = trie[now][ch];
    }
    ed[now] = true;
}

void get_fail()
{
    queue<int> q;
    for (int i = 0; i < 10; i++)
        if (trie[0][i])
            q.push(trie[0][i]);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < 10; i++)
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
    trie[0][0] = 0; // 防止n中有前导0
}

char s[N], tmp[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> s >> m;
    n = strlen(s);
    for (int i = 1; i <= m; i++)
        cin >> tmp, insert(tmp);
    get_fail();

    f[n][0][1] = 1;
    for (int i = n; i >= 1; i--)
        for (int j = 0; j <= cnt; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                int to = trie[j][k];
                if (!ed[to])
                    (f[i - 1][to][0] += f[i][j][0]) %= MOD;
            }
            for (int k = 0; k <= s[n - i] - '0'; k++)
            {
                int to = trie[j][k];
                if (!ed[to])
                    (f[i - 1][to][k == s[n - i] - '0'] += f[i][j][1]) %= MOD;
            }
        }
    int ans = -1;
    for (int i = 0; i <= cnt; i++)
        (((ans += f[0][i][0]) %= MOD) += f[0][i][1]) %= MOD;
    cout << ans;
    return 0;
}