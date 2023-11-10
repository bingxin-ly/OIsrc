#include <bits/stdc++.h>
using namespace std;

constexpr int N = 109;
int n, k, s[N];
double p, f[N][N], sa[N][N], sb[N][N], sab[N][N];
int num(int x) { return x * (x + 1) / 2; }
void init() {
    for (int a = 1; a <= n; a++)
        for (int b = 1; b <= n; b++)
            f[a][b] = f[a][b] * p * (num(n - b) + num(a - 1) + num(b - a - 1));
}
void calc() {
    memset(sa, 0, sizeof(sa));
    memset(sb, 0, sizeof(sb));
    memset(sab, 0, sizeof(sab));
    for (int a = 1; a <= n; a++)
        for (int b = 1; b <= n; b++) {
            sa[a][b] += f[a][b], sb[b][a] += f[a][b];
            if (a > b) sab[a - b][b] += f[a][b];
        }
    for (int k = 1; k <= 2; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                sa[i][j] += sa[i][j - 1];
                sb[i][j] += sb[i][j - 1];
                sab[i][j] += sab[i][j - 1];
            }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k, k = min(k, 1000);
    for (int i = 1; i <= n; i++) cin >> s[i];

    p = 2. / (n * (n + 1));
    for (int a = 1; a <= n; a++)
        for (int b = 1; b <= n; b++) f[a][b] = s[a] > s[b];
    calc();

    for (int i = 1; i <= k; i++) {
        init();
        for (int a = 1; a <= n; a++)
            for (int b = a + 1; b <= n; b++) {
                f[a][b] += p * (sb[b][b - 1] - sb[b][b - a - 1] - sb[b][a - 1]);
                f[a][b] += p * (sab[b - a][a + n - b] - sab[b - a][n - b] - sab[b - a][a - 1]);
                f[a][b] += p * (sa[a][n] - sa[a][a + n - b] - sa[a][b - 1] + sa[a][a - 1]);
            }
        for (int a = 1; a <= n; a++)
            for (int b = 1; b < a; b++) f[a][b] = 1 - f[b][a];
        calc();
    }

    double ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) ans += f[i][j];
    cout << fixed << setprecision(10) << ans;
    return 0;
}