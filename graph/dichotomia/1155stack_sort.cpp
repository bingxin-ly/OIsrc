#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1009;
int n, p[N], mnv[N], col[N];
vector<int> g[N];

int pos = 1;
stack<int> s[2];

bool pop(int id) {
    if (!s[id].empty() && s[id].top() == pos) {
        cout << (id ? 'd' : 'b') << ' ', s[id].pop(), ++pos;
        return true;
    }
    return false;
}

void push(int cur, int id) {
    if (id == 1)
        while (pop(0))
            ;
    while (!s[id].empty() && s[id].top() < cur)
        if (!pop(id)) pop(id ^ 1);
    if (id == 1)
        while (pop(0))
            ;
    s[id].push(cur);
    cout << (id ? 'c' : 'a') << ' ';
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i];
    mnv[n + 1] = n + 1;
    for (int i = n; i >= 1; i--) mnv[i] = min(mnv[i + 1], p[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (mnv[j + 1] < p[i] && p[i] < p[j])
                g[i].emplace_back(j), g[j].emplace_back(i), col[i] = col[j] = -1;
    for (int i = 1; i <= n; i++)
        if (!~col[i]) {
            queue<int> q;
            q.emplace(i), col[i] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : g[u]) {
                    if (~col[v] && col[v] != (col[u] ^ 1)) return cout << 0, 0;
                    if (!~col[v]) q.emplace(v);
                    col[v] = col[u] ^ 1;
                }
            }
        }
    for (int i = 1; i <= n; i++) push(p[i], col[i]);
    bool flag = true;
    while (flag) {
        flag = false;
        while (pop(0)) flag = true;
        while (pop(1)) flag = true;
    }
    return 0;
}