#include <bits/stdc++.h>
using namespace std;

constexpr int N = 21;
int n, w[N];
double p[N], f[1 << N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i] >> w[i];
    for (int i = (1 << n) - 2; i >= 0; i--) {
        double pro = 0, sum = 0;
        for (int j = 1; j <= n; j++)
            if (!(i >> (j - 1) & 1))
                pro += p[j], sum += p[j] * f[i | 1 << (j - 1)];
        f[i] = (sum + 1) / pro;
    }
    cout << accumulate(w + 1, w + n + 1, 0ll) << '\n'
         << fixed << setprecision(3) << f[0];
    return 0;
}