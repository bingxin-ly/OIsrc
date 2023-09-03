#include <bits/stdc++.h>
using namespace std;

int n, tab[6][8], mem[6][6][8], ans[6][3];
bool equal(int x, int y, int z) { return x == y && y == z; }
bool remove() {
    bool suc = 0, del[6][8];
    memset(del, 0, sizeof(del));
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++) {
            if (i - 1 >= 1 && i + 1 <= 5 && tab[i][j] &&
                tab[i - 1][j] == tab[i][j] && tab[i][j] == tab[i + 1][j])
                suc = del[i - 1][j] = del[i][j] = del[i + 1][j] = 1;
            if (j - 1 >= 1 && j + 1 <= 7 && tab[i][j] &&
                tab[i][j - 1] == tab[i][j] && tab[i][j] == tab[i][j + 1])
                suc = del[i][j - 1] = del[i][j] = del[i][j + 1] = 1;
        }
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++)
            if (del[i][j]) tab[i][j] = 0;
    return suc;
}
void fall() {
    for (int i = 1; i <= 5; i++) {
        int c = 0;
        for (int j = 1; j <= 7; j++)
            if (tab[i][j])
                swap(tab[i][j], tab[i][j - c]);
            else
                c++;
    }
}
void modify(int x, int y, int o) {
    swap(tab[x][y], tab[x + o][y]), fall();
    while (remove()) fall();
}
void dfs(int x) {
    if (!(tab[1][1] + tab[2][1] + tab[3][1] + tab[4][1] + tab[5][1])) {
        for (int i = 1; i <= n; i++)
            cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << '\n';
        exit(0);
    }
    if (x == n + 1) return;
    memcpy(mem[x], tab, sizeof(tab));
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++) {
            if (!tab[i][j]) continue;
            if (i + 1 <= 5 && tab[i][j] != tab[i + 1][j]) {
                modify(i, j, 1);
                ans[x][0] = i - 1, ans[x][1] = j - 1, ans[x][2] = 1;
                dfs(x + 1);
                memcpy(tab, mem[x], sizeof(mem[x]));
                memset(ans[x], 0, sizeof(ans[x]));
            }
            if (i - 1 >= 1 && !tab[i - 1][j]) {
                modify(i, j, -1);
                ans[x][0] = i - 1, ans[x][1] = j - 1, ans[x][2] = -1;
                dfs(x + 1);
                memcpy(tab, mem[x], sizeof(mem[x]));
                memset(ans[x], 0, sizeof(ans[x]));
            }
        }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= 5; i++)
        for (int j = 1, x; cin >> x, x; j++) tab[i][j] = x;

    dfs(1);
    cout << -1;
    return 0;
}