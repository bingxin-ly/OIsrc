#include <iostream>
using namespace std;

constexpr int M = 3e5 + 9;
int n, m, l[M], r[M], s[M];
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i], l[i]--;
        for (int j = 1, k; j <= l[i]; j = k + 1) {
            k = min(l[i] / (l[i] / j), r[i] / (r[i] / j));
            if (l[i] / j < r[i] / j)
                s[j]++, s[k + 1]--;
        }
        s[l[i] + 1]++, s[r[i] + 1]--;
    }
    for (int i = 1; i <= m; ++i)
        cout << (s[i] += s[i - 1]) << '\n';
    return 0;
}