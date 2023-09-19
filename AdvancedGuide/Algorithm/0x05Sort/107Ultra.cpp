#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, a[N], b[N];
long long cnt;
void MergeSort(int l, int r) {
    if (l >= r) return;
    int m = (l + r) >> 1;
    MergeSort(l, m), MergeSort(m + 1, r);
    int o = l, p = l, q = m + 1;
    while (p <= m && q <= r)
        if (a[p] <= a[q])
            b[o++] = a[p++];
        else
            b[o++] = a[q++], cnt += m - p + 1;
    while (p <= m) b[o++] = a[p++];
    while (q <= r) b[o++] = a[q++];
    memcpy(a + l, b + l, (r - l + 1) << 2);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++) cin >> a[i];
        cnt = 0, MergeSort(1, n);
        cout << cnt << '\n';
    }
    return 0;
}