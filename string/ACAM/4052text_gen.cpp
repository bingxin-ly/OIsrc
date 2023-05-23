#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5, MOD = 1e4 + 7;
struct node
{
    int son[26], fail, end;
    int &operator[](int x) { return son[x]; }
} trie[N];
int tot, f[N][N];

void insert(const char *s)
{
    int now = 0;
    for (int i = 0; s[i]; i++)
    {
        int ch = s[i] - 'A';
        if (!trie[now][ch])
            trie[now][ch] = ++tot;
        now = trie[now][ch];
    }
    trie[now].end = true;
}

void get_fail()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (trie[0][i])
            q.push(trie[0][i]);

    while (!q.empty())
    {
        int now = q.front();
        q.pop();

        for (int i = 0; i < 26; i++)
        {
            int &v = trie[now][i];
            if (v)
            {
                trie[v].fail = trie[trie[now].fail][i];
                trie[v].end |= trie[trie[trie[now].fail][i]].end;
                q.push(v);
            }
            else
                v = trie[trie[now].fail][i];
        }
    }
}

char s[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> s, insert(s);
    get_fail();

    f[0][0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = 0; j <= tot; j++)
            for (int c = 0; c < 26; c++)
                if (!trie[trie[j][c]].end)
                    (f[i][trie[j][c]] += f[i - 1][j]) %= MOD;

    int ans = 0;
    for (int i = 0; i <= tot; i++)
        (ans += f[m][i]) %= MOD;
    int sum = 1;
    for (int i = 1; i <= m; i++)
        (sum *= 26) %= MOD;
    cout << (sum - ans + MOD) % MOD;
    return 0;
}