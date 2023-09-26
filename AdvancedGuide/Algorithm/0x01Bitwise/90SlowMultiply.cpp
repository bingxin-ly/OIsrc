#include <bits/stdc++.h>
using namespace std;

long long mul(long long a, long long b, long long p) {
    long long res = 0;
    for (; b; b >>= 1) {
        if (b & 1) res = (res + a) % p;
        a = (a + a) % p;
    }
    return res;
}

signed main() {
    long long a, b, p;
    cin >> a >> b >> p;
    cout << mul(a, b, p);
    return 0;
}