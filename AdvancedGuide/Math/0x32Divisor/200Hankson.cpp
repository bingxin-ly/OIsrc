#include <bits/stdc++.h>
using namespace std;

vector<int> pri;
bitset<50000> vis;
void sieve(int n) {
    for (int i = 2; i <= n; i++)
        if (!vis[i]) {
            pri.emplace_back(i);
            for (int j = i; j <= n / i; j++) vis[i * j] = 1;
        }
}
int decomp(int &x, int p) {
    int c = 0;
    while (!(x % p)) c += 1, x /= p;
    return c;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    sieve(sqrt(2e9));
    int n;
    cin >> n;
    for (int a, b, c, d; n--;) {
        cin >> a >> c >> b >> d;
        int ans = 1;
        auto calc = [&](int p) {
            int ma = decomp(a, p), mb = decomp(b, p), mc = decomp(c, p), md = decomp(d, p);
            if ((ma > mc && mb < md && mc == md) ||
                (ma > mc && mb == md && mc <= md) ||
                (ma == mc && mb < md && mc <= md))
                return ans *= 1;
            else if (ma == mc && mb == md && mc <= md)
                return ans *= (md - mc + 1);
            else
                return ans = 0;
        };
        for (int p : pri)
            if (!calc(p)) break;
        if (d != 1) calc(d);
        if (a != 1) calc(a);
        cout << ans << '\n';
    }
    return 0;
}