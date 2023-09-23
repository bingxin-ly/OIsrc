#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 9, P = 131;
int n, sa[N];
char s[N];
unsigned long long p[N], h[N];

bool check(int l, int l1, int l2) {
    int r1 = l1 + l - 1, r2 = l2 + l - 1;
    return h[r1] - h[l1 - 1] * p[l] == h[r2] - h[l2 - 1] * p[l];
}
int lcp(int i, int j) {
    if (i > j) swap(i, j);
    int l = 0, p = 1;
    while (p) {
        if (j + l + p - 1 <= n && check(l + p, i, j))
            l += p, p <<= 1;
        else
            p >>= 1;
    }
    return l;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> s, n = strlen(s), h[0] = s[0] - 'a' + 1, p[0] = 1;
    for (int i = 1; i < n; i++)
        h[i] = h[i - 1] * P + (s[i] - 'a' + 1), p[i] = p[i - 1] * P;
    iota(sa, sa + n, 0), sort(sa, sa + n, [](int i, int j) {
        int l = lcp(i, j);
        return s[i + l] < s[j + l];
    });
    for (int i = 0; i < n; i++) cout << sa[i] << ' ';
    cout << "\n0 ";
    for (int i = 1; i < n; i++) cout << lcp(sa[i], sa[i - 1]) << ' ';
    return 0;
}