#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
struct node
{
    int son[26], fail, end;
    int &operator[](int x) { return son[x]; }
} trie[N];
int cnt, siz[N], ans[N];

void insert(const char *s, int pos)
{
    int now = 0;
    for (int i = 0; s[i]; i++)
    {
        int ch = s[i] - 'a';
        if (!trie[now][ch])
            trie[now][ch] = ++cnt;
        now = trie[now][ch];
        siz[now]++;
    }
    ans[pos] = now;
}

vector<int> idx;
void get_fail()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (trie[0][i])
            q.push(trie[0][i]), idx.emplace_back(trie[0][i]);

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
                q.push(v), idx.emplace_back(v);
            }
            else
                v = trie[trie[now].fail][i];
        }
    }
}

void solve()
{
    for (int i = cnt - 1; i >= 0; i--)
        siz[trie[idx[i]].fail] += siz[idx[i]];
}

char str[N];
signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> str, insert(str, i);
    get_fail();
    solve();
    for (int i = 1; i <= n; i++)
        cout << siz[ans[i]] << '\n';
    return 0;
}