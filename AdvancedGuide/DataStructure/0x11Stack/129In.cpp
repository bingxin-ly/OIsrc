#include <bits/stdc++.h>
using namespace std;

int n, cnt, top, stk[21];
vector<int> out;
void dfs(int i) {
    if (i == n + 1) {
        if (++cnt > 20) exit(0);
        for (int x : out) cout << x;
        for (int x = top; x; x--) cout << stk[x];
        cout << '\n';
        return;
    }
    if (top)
        out.emplace_back(stk[top--]), dfs(i), stk[++top] = out.back(), out.pop_back();
    stk[++top] = i, dfs(i + 1), top--;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    dfs(1);
    return 0;
}