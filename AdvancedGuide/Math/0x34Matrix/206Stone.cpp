#include <bits/stdc++.h>
using namespace std;

int n, m, t, o, p, a[10][10], c[10][10];
char s[7], b[11][10];
long long F[70], I[70][70][70];

int idx(int i, int j) { return (i - 1) * m + j; }
void mull(long long a[][70], long long b[][70]) {
    static long long c[70][70];
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= p; i++)
        for (int k = 1; k <= p; k++)
            if (a[i][k])
                for (int j = 1; j <= p; j++)
                    c[i][j] += a[i][k] * b[k][j];
    memcpy(a, c, sizeof(c));
}
void mul(long long a[], long long b[][70]) {
    static long long c[70];
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= p; i++)
        for (int j = 1; j <= p; j++)
            c[i] += a[j] * b[j][i];
    memcpy(a, c, sizeof(c));
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> t >> o;
    for (int i = 1; i <= n; i++) {
        cin >> (s + 1);
        for (int j = 1; j <= m; j++) a[i][j] = s[j] - '0' + 1;
    }
    for (int i = 1; i <= o; i++) cin >> b[i];

    p = n * m + 1;
    for (int k = 1; k <= 60; k++) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                int x = a[i][j], y = c[i][j];
                if (isdigit(b[x][y]))
                    I[k][p][idx(i, j)] = b[x][y] - '0', I[k][idx(i, j)][idx(i, j)] = 1;
                else if (b[x][y] == 'N' && i > 1)
                    I[k][idx(i, j)][idx(i - 1, j)] = 1;
                else if (b[x][y] == 'W' && j > 1)
                    I[k][idx(i, j)][idx(i, j - 1)] = 1;
                else if (b[x][y] == 'S' && i < n)
                    I[k][idx(i, j)][idx(i + 1, j)] = 1;
                else if (b[x][y] == 'E' && j < m)
                    I[k][idx(i, j)][idx(i, j + 1)] = 1;
                c[i][j] = (y + 1) % strlen(b[x]);
            }
        I[k][p][p] = 1;
    }
    memcpy(I[0], I[1], sizeof(I[1]));
    for (int k = 2; k <= 60; k++) mull(I[0], I[k]);

    F[p] = 1;
    for (int i = t / 60; i; i >>= 1) {
        if (i & 1) mul(F, I[0]);
        mull(I[0], I[0]);
    }
    for (int i = 1; i <= t % 60; i++) mul(F, I[i]);
    long long ans = 0;
    for (int i = 1; i < p; i++) ans = max(ans, F[i]);
    cout << ans;
    return 0;
}