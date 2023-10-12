#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 9;
int n;
char s[N];
double p[N], x1[N], x2[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> (s + 1);
    for (int i = 1; i <= n; i++)
        p[i] = s[i] != '?' ? s[i] == 'o' ? 1 : 0 : 0.5;
    for (int i = 1; i <= n; i++) {
        x1[i] = (x1[i - 1] + 1) * p[i];
        x2[i] = x2[i - 1] + (2 * x1[i - 1] + 1) * p[i];
    }
    cout << fixed << setprecision(4) << x2[n];
    return 0;
}