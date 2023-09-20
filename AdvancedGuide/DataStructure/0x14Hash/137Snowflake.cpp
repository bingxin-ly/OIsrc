#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9, MOD = 99991;
int n, snw[N][6];
int idx, hed[N], nxt[N];

int hashfunc(int *s) {
    int sum = 0, mul = 1;
    for (int i = 0; i < 6; i++) {
        sum = (sum + s[i]) % MOD;
        mul = 1ll * mul * s[i] % MOD;
    }
    return (sum + mul) % MOD;
}
bool equal(int *a, int *b) {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            bool eq = 1;
            for (int k = 0; k < 6; k++) eq &= a[(i + k) % 6] == b[(j + k) % 6];
            if (eq) return true;
            eq = 1;
            for (int k = 0; k < 6; k++) eq &= a[(i + k) % 6] == b[(j - k + 6) % 6];
            if (eq) return true;
        }
    return false;
}
bool insert(int *s) {
    int val = hashfunc(s);
    for (int i = hed[val]; i; i = nxt[i])
        if (equal(snw[i], s)) return true;
    memcpy(snw[++idx], s, 24), nxt[idx] = hed[val], hed[val] = idx;
    return false;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, s[6]; i <= n; i++) {
        for (int j = 0; j < 6; j++) cin >> s[j];
        if (insert(s)) return cout << "Twin snowflakes found.", 0;
    }
    cout << "No two snowflakes are alike.";
    return 0;
}