#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, c, nxt[N];
char s[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n, n) {
        cin >> (s + 1);
        nxt[1] = 0;
        for (int i = 2, j = 0; i <= n; i++) {
            while (j && s[i] != s[j + 1]) j = nxt[j];
            j += s[i] == s[j + 1], nxt[i] = j;
        }
        cout << "Test case #" << ++c << "\n";
        for (int i = 1; i <= n; i++)
            if (!(i % (i - nxt[i])) && i / (i - nxt[i]) > 1)
                cout << i << ' ' << i / (i - nxt[i]) << '\n';
        cout << '\n';
    }
    return 0;
}