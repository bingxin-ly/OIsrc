#include <bits/stdc++.h>
using namespace std;

constexpr int N = 6e5 + 9;
int n, m, idx, s[N], rt[N];
int trie[N * 24][2], late[N * 24];
void insert(int i, int k, int p, int q) {
    if (k < 0) return late[q] = i, void();
    int c = s[i] >> k & 1;
    if (p) trie[q][c ^ 1] = trie[p][c ^ 1];
    trie[q][c] = ++idx;
    insert(i, k - 1, trie[p][c], trie[q][c]);
    late[q] = max(late[trie[q][0]], late[trie[q][1]]);
}
int query(int i, int v, int k, int lim) {
    if (k < 0) return s[late[i]] ^ v;
    int c = v >> k & 1;
    if (late[trie[i][c ^ 1]] >= lim)
        return query(trie[i][c ^ 1], v, k - 1, lim);
    else
        return query(trie[i][c], v, k - 1, lim);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    late[0] = -1, insert(0, 23, 0, rt[0] = ++idx);
    for (int i = 1, x; i <= n; i++) {
        cin >> x, s[i] = s[i - 1] ^ x;
        insert(i, 23, rt[i - 1], rt[i] = ++idx);
    }
    char c;
    for (int i = 1, l, r, x; i <= m; i++) {
        cin >> c;
        if (c == 'A') {
            cin >> x, n += 1, s[n] = s[n - 1] ^ x;
            insert(n, 23, rt[n - 1], rt[n] = ++idx);
        } else {
            cin >> l >> r >> x;
            cout << query(rt[r - 1], x ^ s[n], 23, l - 1) << '\n';
        }
    }
    return 0;
}