#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, q, b[5], p[5]{0, 2, 3, 4679, 35617};
int pow(int a, int b, int p) {
    int r = 1;
    for (; b; b >>= 1) {
        if (b & 1) r = r * a % p;
        a = a * a % p;
    }
    return r;
}
int fac[36000];
int C(int n, int m, int p) {
    return n >= m ? fac[n] * pow(fac[m], p - 2, p) * pow(fac[n - m], p - 2, p) % p : 0;
}
int lucas(int n, int m, int p) {
    return m ? C(n % p, m % p, p) * lucas(n / p, m / p, p) % p : 1;
}
int CRT() {
    int M = 999911658, X = 0;
    for (int i = 1; i <= 4; i++) {
        int m = M / p[i];
        (X += b[i] * m * pow(m, p[i] - 2, p[i]) % M) %= M;
    }
    return (X + M) % M;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> q;
    if (!(q % 999911659)) return cout << 0, 0;
    vector<int> v;
    for (int i = 1, u = sqrt(n); i <= u; i++)
        if (!(n % i)) {
            v.emplace_back(i);
            if (i * i != n) v.emplace_back(n / i);
        }
    for (int i = 1; i <= 4; i++) {
        fac[0] = 1;
        for (int j = 1; j < p[i]; j++) fac[j] = fac[j - 1] * j % p[i];
        for (int d : v) (b[i] += lucas(n, d, p[i])) %= p[i];
    }
    cout << pow(q, CRT(), 999911659);
    return 0;
}