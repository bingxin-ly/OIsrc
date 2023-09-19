#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3005;
int c, l, mnv[N], mxn[N], cnt[N], I[N], ans;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> c >> l;
    for (int i = 1; i <= c; i++) cin >> mnv[i] >> mxn[i];
    for (int i = 1, spf, cov; i <= l; i++) cin >> spf >> cov, cnt[spf] += cov;
    iota(I + 1, I + c + 1, 1);
    sort(I + 1, I + c + 1, [](int i, int j) { return mnv[i] > mnv[j]; });
    for (int i = 1; i <= c; i++) {
        for (int j = mxn[I[i]]; j >= mnv[I[i]]; j--)
            if (cnt[j]) {
                ans++, cnt[j]--;
                break;
            }
    }
    cout << ans;
    return 0;
}