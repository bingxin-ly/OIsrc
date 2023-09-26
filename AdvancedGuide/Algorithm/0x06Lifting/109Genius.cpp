#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, m, a[N], b[N], c[N];
long long t;

long long squ(int $) { return 1ll * $ * $; };
void merge(const int a[], int al, const int b[], int bl, int c[]) {
    int i = 0, j = 0, k = 0;
    while (i < al && j < bl)
        if (a[i] <= b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    while (i < al) c[k++] = a[i++];
    while (j < bl) c[k++] = b[j++];
}
long long calc(int l, int mid, int r) {
    memcpy(b + mid, a + mid, (r - mid + 1) * sizeof(int));
    sort(b + mid, b + r + 1);
    merge(b + l, mid - l, b + mid, r - mid + 1, c + l);
    long long s = 0;
    int *x = c + l, *y = c + r;
    for (int i = 1; i <= m && x < y; i++, x++, y--)
        s += squ(*y - *x);
    return s;
}
void solve() {
    cin >> n >> m >> t;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int seg = 0;
    for (int l = 1, r = 1; r <= n; l = ++r) {
        int p = 1;
        b[l] = a[l];
        while (p)
            if (r + p <= n && calc(l, r + 1, r + p) <= t) {
                r += p, p <<= 1;
                memcpy(b + l, c + l, (r - l + 1) * sizeof(int));
            } else
                p >>= 1;
        seg += 1;
    }
    cout << seg << '\n';
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int k;
    cin >> k;
    while (k--) solve();
    return 0;
}