#include <bits/stdc++.h>
using namespace std;

int n, s[730][730];
void build(int x, int a, int b) {
    int m = pow(3, x - 1), k = pow(3, x - 2);
    for (int i = 1; i <= m; i++) s[a + i][b + i] = 1;
    for (int i = 1; i <= m; i++) s[a + i][b + m - i + 1] = 1;
    if (x == 1) return;
    build(x - 1, a, b), build(x - 1, a + 2 * k, b);
    build(x - 1, a + k, b + k);
    build(x - 1, a, b + 2 * k), build(x - 1, a + 2 * k, b + 2 * k);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n, ~n) {
        memset(s, 0, sizeof(s));
        build(n, 0, 0);
        int m = pow(3, n - 1);
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) cout << (s[i][j] ? 'X' : ' ');
            cout << '\n';
        }
        cout << "-\n";
    }
    return 0;
}