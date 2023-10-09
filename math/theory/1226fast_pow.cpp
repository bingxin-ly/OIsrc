#include <bits/stdc++.h>
using namespace std;

int pow(int a, int b, int p) {
    int r = 1 % p;
    for (a %= p; b; b >>= 1) {
        if (b & 1) r = 1ll * r * a % p;
        a = 1ll * a * a % p;
    }
    return r;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int a, b, p;
    cin >> a >> b >> p;
    cout << a << '^' << b << " mod " << p << '=' << pow(a, b, p);
    return 0;
}