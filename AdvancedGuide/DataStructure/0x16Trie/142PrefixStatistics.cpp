#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, m, t, cnt[N], son[N][26];

void insert(char *s) {
    int p = 0;
    for (int i = 0, j = strlen(s); i < j; i++) {
        int c = s[i] - 'a';
        if (!son[p][c]) son[p][c] = ++t;
        p = son[p][c];
    }
    cnt[p] += 1;
}
int search(char *s) {
    int p = 0, r = 0;
    for (int i = 0, j = strlen(s); i < j; i++) {
        p = son[p][s[i] - 'a'];
        if (!p) return r;
        r += cnt[p];
    }
    return r;
}

char str[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> str, insert(str);
    for (int i = 1; i <= m; i++) cin >> str, cout << search(str) << '\n';
    return 0;
}