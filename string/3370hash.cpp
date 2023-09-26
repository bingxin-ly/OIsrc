#include <bits/stdc++.h>
using namespace std;

constexpr long long P = 128, MOD = 1e15 + 37;
long long BKDR(char *s) {
    long long hash = 0;
    for (int i = 0, j = strlen(s); i < j; i++)
        hash = (hash * P + s[i]) % MOD;
    return hash;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    set<long long> vis;
    char s[1509];
    int n;
    cin >> n;
    while (n--) cin >> s, vis.emplace(BKDR(s));
    cout << vis.size();
    return 0;
}