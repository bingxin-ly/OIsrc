#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int M = 998244853;
int T, n, tab[] = {0, 0, 1, 7, 4, 2, 0, 8, 10, 18, 22, 20, 28, 68, 88, 108, 188, 200, 208, 288, 688, 888};
void mul(pii &a, pii b) {
    a.first = 1ll * a.first * b.first % M;
    a.second = (1ll * a.second * b.first % M + b.second) % M;
}
pii pow(pii a, int b) {
    pii r(1, 0);
    for (; b; b >>= 1) {
        if (b & 1) mul(r, a);
        mul(a, a);
    }
    return r;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (cin >> T; T; T--) {
        cin >> n;
        if (n <= 21)
            cout << tab[n] << '\n';
        else {
            n -= 21;
            pii res = pow({10, 8}, (n - 1) / 7 + 1);
            long long bas = tab[(n - 1) % 7 + 15];
            bas = (bas * res.first % M + res.second) % M;
            cout << bas << '\n';
        }
    }
    return 0;
}