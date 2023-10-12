#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
struct node {
    int son[26], fail, end;
    int &operator[](int x) { return son[x]; }
} trie[N];

int cnt;
void insert(const char *s) {
    int u = 0;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!trie[u][c]) trie[u][c] = ++cnt;
        u = trie[u][c];
    }
    trie[u].end++;
}
void mkfail()  // bfs过程
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (trie[0][i]) q.push(trie[0][i]);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < 26; i++)
            if (trie[u][i]) {
                trie[trie[u][i]].fail = trie[trie[u].fail][i];
                q.push(trie[u][i]);
            } else
                trie[u][i] = trie[trie[u].fail][i];
    }
}
int query(const char *s) {
    int u = 0, ans = 0;
    for (int i = 0; s[i]; i++) {
        int tmp = u = trie[u][s[i] - 'a'];
        while (tmp && trie[tmp].end != -1) {
            ans += trie[tmp].end, trie[tmp].end = -1;
            tmp = trie[tmp].fail;
        }
    }
    return ans;
}

char str[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    while (n--) cin >> str, insert(str);
    mkfail();
    cin >> str, cout << query(str) << '\n';
    return 0;
}