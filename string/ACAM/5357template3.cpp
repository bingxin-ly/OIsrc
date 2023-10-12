#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
struct node
{
    int son[26], fail, end, ans;
    int &operator[](int x) { return son[x]; }
} trie[N];
int cnt, mp[N];

void insert(const char *s, int pos)
{
    int now = 0;
    for (int i = 0; s[i]; i++)
    {
        int ch = s[i] - 'a';
        if (!trie[now][ch])
            trie[now][ch] = ++cnt;
        now = trie[now][ch];
    }
    if (!trie[now].end) // 相同模式串去重
        trie[now].end = pos;
    mp[pos] = trie[now].end;
}

int in[N]; // 作为AC自动机的拓扑优化
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
                in[trie[v].fail]++;
                q.push(v);
            }
            else
                v = trie[trie[u].fail][i];
        }
    }
}

int ans[N];
void query(const char *s)
{
    int now = 0;
    for (int i = 0; s[i]; i++)
    {
        int ch = s[i] - 'a';
        now = trie[now][ch];
        // for (int tmp = now; tmp; tmp = trie[tmp].fail)
        //     ans[trie[tmp].end]++; // 暴力跳
        trie[now].ans++;
    }
}

void topo()
{
    queue<int> q;
    for (int i = 1; i <= cnt; i++)
        if (!in[i])
            q.push(i);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        ans[trie[u].end] = trie[u].ans;
        int v = trie[u].fail;
        in[v]--;
        trie[v].ans += trie[u].ans;

        if (!in[v])
            q.push(v);
    }
}

char str[10 * N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> str, insert(str, i);
    get_fail();

    cin >> str, query(str), topo();
    for (int i = 1; i <= n; i++)
        cout << ans[mp[i]] << '\n';
    return 0;
}