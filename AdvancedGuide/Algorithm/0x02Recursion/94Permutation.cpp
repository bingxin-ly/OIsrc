#include <bits/stdc++.h>
using namespace std;

int n, num[20], vis[20];
void dfs(int x) {
    if (x == n + 1) {
        for (int i = 1; i <= n; i++)
            cout << num[i] << ' ';
        cout << '\n';
        return;
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            num[x] = i, vis[i] = true, dfs(x + 1);
            vis[i] = false;
        }
}
signed main() {
    cin >> n, dfs(1);
    return 0;
}