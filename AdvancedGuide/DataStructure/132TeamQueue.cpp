#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, m, c, a[N];
queue<int> q[1009];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n, n) {
        cout << "Scenario #" << ++c << '\n';
        while (!q[0].empty()) q[0].pop();
        for (int i = 1; i <= n; i++) {
            cin >> m;
            while (!q[i].empty()) q[i].pop();
            for (int j = 1, k; j <= m; j++) cin >> k, a[k] = i;
        }

        char s[10];
        while (true) {
            cin >> s;
            if (s[0] == 'S')
                break;
            else if (s[0] == 'E') {
                cin >> m;
                if (q[a[m]].empty()) q[0].emplace(a[m]);
                q[a[m]].emplace(m);
            } else {
                m = q[0].front();
                cout << q[m].front() << '\n', q[m].pop();
                if (q[m].empty()) q[0].pop();
            }
        }
        cout << '\n';
    }
    return 0;
}