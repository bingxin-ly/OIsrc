#include <bits/stdc++.h>
using namespace std;

struct node {
    int son[26], fail, end;
    int &operator[](int x) { return son[x]; }
} trie[10501];  // 这里的范围，是模板串的数量 * 模板串的长度最大值，即 150 * 70
int cnt;

void insert(const char *s, int pos) {
    int u = 0;
    for (int i = 0; s[i]; i++) {
        int ch = s[i] - 'a';
        if (!trie[u][ch])
            trie[u][ch] = ++cnt;
        u = trie[u][ch];
    }
    trie[u].end = pos;
}
void mkfail() {  // bfs过程
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (trie[0][i])
            q.push(trie[0][i]);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < 26; i++) {
            int &v = trie[u][i];
            if (v) {
                trie[v].fail = trie[trie[u].fail][i];
                q.push(v);
            } else
                v = trie[trie[u].fail][i];
        }
    }
}

struct result {
    int num, pos;
    string val;
    bool operator<(const result &otr) const {
        return num == otr.num ? pos < otr.pos : num > otr.num;
    }
} ans[151];  // 这里的范围，是单次测试数据中模板串的个数

void query(const char *s) {  // 统计贡献
    int u = 0;
    for (int i = 0; s[i]; i++) {
        int ch = s[i] - 'a';
        u = trie[u][ch];
        for (int tmp = u; tmp; tmp = trie[tmp].fail)
            ans[trie[tmp].end].num++;
    }
}

char str[1000001];  // 这里的范围，是最长的字符串
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    while (cin >> n, n) {
        memset(trie, 0, sizeof(trie)), cnt = 0;
        for (int i = 1; i <= n; i++)
            cin >> str, ans[i] = {0, i, str}, insert(str, i);
        mkfail();
        cin >> str;
        query(str);
        sort(ans + 1, ans + n + 1);
        cout << ans[1].num << '\n'
             << ans[1].val << '\n';
        for (int i = 2; i <= n; i++)
            if (ans[i].num == ans[i - 1].num)
                cout << ans[i].val << '\n';
            else
                break;
    }
    return 0;
}