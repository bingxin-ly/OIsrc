#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 9;
int n, a[N << 1];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memcpy(a + n + 1, a + 1, n * sizeof(int));
    int i = 1, j = 2;
    while (i <= n && j <= n) {
        int k = 0;
        while (k < n && a[i + k] == a[j + k]) k++;
        if (k == n) break;
        if (a[i + k] < a[j + k]) swap(i, j);
        i = i + k + 1, i += i == j;
    }
    int *b = a + min(i, j);
    for (int i = 0; i < n; i++) cout << b[i] << ' ';
    return 0;
}