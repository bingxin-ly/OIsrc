#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
long long k;
int n, a[N], p, ans[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    vector<int> p1, p2;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 0 || a[i] == 2)
            p1.push_back(i);
        else
            p2.push_back(i);
    }

    int i = 0, j = 0;
    while (i < (int)p1.size() && j < (int)p2.size()) {
        if (a[p1[i]] < a[p2[j]]) {
            int need = max(0, p1[i] - p - 1);
            if (k >= need)
                ans[++p] = p1[i++], k -= need;
            else
                ans[++p] = p2[j++];
        } else {
            int need = max(0, p2[j] - p - 1);
            if (k >= need)
                ans[++p] = p2[j++], k -= need;
            else
                ans[++p] = p1[i++];
        }
    }

    while (i < (int)p1.size()) ans[++p] = p1[i++];
    while (j < (int)p2.size()) ans[++p] = p2[j++];
    for (int i = 1; i <= p; i++) cout << a[ans[i]] << ' ';
    return 0;
}