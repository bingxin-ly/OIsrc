#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 9;
int n, m, p[N];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m, iota(p + 1, p + n + 1, 1);
    for (int z, x, y; m--;) {
        cin >> z >> x >> y;
        x = find(x), y = find(y);
        if (z == 1)
            p[x] = y;
        else
            cout << (x == y ? "Y\n" : "N\n");
    }
    return 0;
}