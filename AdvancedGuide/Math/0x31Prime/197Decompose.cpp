#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, v[N];
vector<int> pri;
void sieve() {
    fill(v, v + n + 1, 1), v[0] = v[1] = 0;
    for (int i = 2; i <= n; i++)
        if (v[i]) {
            pri.emplace_back(i);
            for (int j = i; j <= n / i; j++) v[i * j] = 0;
        }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n, sieve();
    for (int p : pri) {
        if (n / p == 0) break;
        cout << p << ' ';
        long long cnt = 0, num = 1;
        for (int i = 1; i <= __lg(n); i++)
            num *= p, cnt += n / num;
        cout << cnt << '\n';
    }
    return 0;
}