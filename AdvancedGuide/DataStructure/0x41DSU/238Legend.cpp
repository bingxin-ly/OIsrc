#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e4 + 9;
int T, p[N], d[N], s[N];
int get(int x) {
    if (x == p[x]) return x;
    int r = get(p[x]);
    return d[x] += d[p[x]], p[x] = r;
}
void merge(int x, int y) {
    x = get(x), y = get(y);
    if (x != y) p[x] = y, d[x] = s[y], s[y] += s[x];
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    iota(p + 1, p + 30001, 1), fill(s + 1, s + 30001, 1);
    cin >> T;
    char c;
    for (int i, j; T--;) {
        cin >> c >> i >> j;
        if (c == 'M')
            merge(i, j);
        else {
            int x = get(i), y = get(j);
            cout << (x == y ? abs(d[i] - d[j]) - (i != j) : -1) << '\n';
        }
    }
    return 0;
}