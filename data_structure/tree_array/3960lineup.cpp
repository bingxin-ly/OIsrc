#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 5, M = 9e5 + 5;
long long n, m, q;
long long I[N], row[N], col[N];

int hed[N], len[N], len2[N];
long long arr[M], ans[N];

int bit[M];
void insert(int *arr, int siz, int p, int v) {
    while (p <= siz) arr[p] += v, p += p & -p;
}
int binary(int *arr, int siz, int v) {
    int l = 1, r, sum, pos;
    while (l <= siz && arr[l] < v) l <<= 1, pos = l;
    r = l, sum = arr[l >>= 1];
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (mid > siz || arr[mid] + sum >= v)
            r = mid, pos = mid;
        else
            l = mid, sum += arr[l];
    }
    return pos = r;
}

int top, stk[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1; i <= q; i++) cin >> row[i] >> col[i], I[i] = i;
    sort(I + 1, I + q + 1, [](int i, int j) { return row[i] != row[j] ? row[i] < row[j] : i < j; });
    for (int i = 1; i <= m - 1; i++) insert(bit, m - 1, i, 1);
    for (int i = 1; i <= n; i++) len[i] = m - 1;

    for (int i = 1; i <= q; i++) {
        if (row[I[i]] != row[I[i - 1]])
            while (top) insert(bit, m - 1, stk[top--], 1);
        if (col[I[i]] > len[row[I[i]]]) continue;
        int p = binary(bit, m - 1, col[I[i]]);
        ans[I[i]] = (row[I[i]] - 1) * m + p;
        insert(bit, m - 1, p, -1);
        stk[++top] = p, len[row[I[i]]]--;
    }

    int iter = 0;
    for (int i = 1; i <= n; i++) {
        while (iter <= q && row[I[iter]] < i) iter++;
        hed[i] = iter - 1;
    }
    hed[n + 1] = q;
    memset(bit, 0, sizeof(bit));
    for (int i = 1; i <= n; i++) len[i] = 0, len2[i] = m - 1;
    len[n + 1] = n;
    for (int i = 1; i <= n; i++) insert(bit + hed[n + 1], n + q, i, 1), arr[q + i] = i * m;
    for (int i = 1; i <= q; i++)
        if (ans[i]) {
            int p = binary(bit + hed[n + 1], n + q, row[i]);
            insert(bit + hed[n + 1], n + q, p, -1), insert(bit + hed[n + 1], n + q, ++len[n + 1], 1);
            arr[hed[n + 1] + len[n + 1]] = ans[i];
            insert(bit + hed[row[i]], hed[row[i] + 1] - hed[row[i]], ++len[row[i]], 1);
            arr[hed[row[i]] + len[row[i]]] = arr[hed[n + 1] + p], len2[row[i]]--;
        } else {
            int p = binary(bit + hed[n + 1], n + q, row[i]);
            insert(bit + hed[n + 1], n + q, p, -1), insert(bit + hed[n + 1], n + q, ++len[n + 1], 1);
            if (col[i] == m)
                ans[i] = arr[hed[n + 1] + p];
            else {
                int pp =
                    binary(bit + hed[row[i]], hed[row[i] + 1] - hed[row[i]], col[i] - len2[row[i]]);
                insert(bit + hed[row[i]], hed[row[i] + 1] - hed[row[i]], pp, -1);
                ans[i] = arr[hed[row[i]] + pp];
                insert(bit + hed[row[i]], hed[row[i] + 1] - hed[row[i]], ++len[row[i]], 1);
                arr[hed[row[i]] + len[row[i]]] = arr[hed[n + 1] + p];
            }
            arr[hed[n + 1] + len[n + 1]] = ans[i];
        }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    return 0;
}