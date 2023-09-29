#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, v[N];
vector<int> pri;
void sieve(int n) {
    fill(v, v + n + 1, 1), v[0] = v[1] = 0;
    for (int i = 2; i <= n; i++)
        if (v[i]) {
            pri.emplace_back(i);
            for (int j = i; j <= n / i; j++) v[i * j] = 0;
        }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    sieve(sqrt(INT_MAX));
    int L, R;
    while (cin >> L >> R) {
        memset(v, 1, sizeof(v));
        if (L == 1) v[0] = 0;
        for (int p : pri)
            for (int i = max((L - 1) / p + 1, 2); i <= R / p; i++)
                v[i * p - L] = 0;
        vector<int> num;
        for (unsigned i = L; i <= (unsigned)R; i++)
            if (v[i - L]) num.emplace_back(i);
        if (num.size() < 2) {
            cout << "There are no adjacent primes.\n";
            continue;
        }
        int ner = 1e6, far = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        for (int i = 1; i < (int)num.size(); i++) {
            int dis = num[i] - num[i - 1];
            if (ner > dis) ner = dis, x1 = num[i - 1], y1 = num[i];
            if (far < dis) far = dis, x2 = num[i - 1], y2 = num[i];
        }
        cout << x1 << ',' << y1 << " are closest, " << x2 << ',' << y2 << " are most distant.\n";
    }
    return 0;
}