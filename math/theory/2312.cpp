#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 9, MOD = 1e9 + 7;
int n, m, a[N];
void input(int &p) {
    static int c, o;
    p = 0, o = 1, c = getchar();
    while (c < '0' || c > '9') (c == '-') && (o = -1), c = getchar();
    while (c >= '0' && c <= '9') p = (p * 10ll + c - '0') % MOD, c = getchar();
    p *= o;
}
bool calc(long long x) {
    int sum = 0;
    for (int i = n; i; i--) sum = (sum + a[i]) * x % MOD;
    sum = (sum + a[0]) % MOD;
    return !sum;
}
signed main() {
    input(n), input(m);
    for (int i = 0; i <= n; i++) input(a[i]);
    vector<int> sol;
    for (int i = 1; i <= m; i++)
        if (calc(i)) sol.emplace_back(i);
    cout << sol.size() << '\n';
    for (int i : sol) cout << i << '\n';
    return 0;
}