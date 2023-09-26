#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, m, idx, son[N][26], tag[N];

void insert(char *s) {
    int p = 0;
    for (int i = 0, j = strlen(s); i < j; i++) {
        int u = s[i] - '0';
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
    tag[p] = 1;
}
void query(char *s) {
    int p = 0;
    for (int i = 0, j = strlen(s); i < j; i++) {
        int u = s[i] - '0';
        if (!son[p][u]) return cout << "WRONG\n", void();
        p = son[p][u];
    }
    if (!tag[p])
        cout << "WRONG\n";
    else if (tag[p] == 1)
        cout << "OK\n", tag[p] = 2;
    else
        cout << "REPEAT\n";
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    char s[60];
    for (int i = 1; i <= n; i++) cin >> s, insert(s);
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> s, query(s);
    return 0;
}