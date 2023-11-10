#include <bits/stdc++.h>
using namespace std;

char str[251];
int n, k, lim, res;
pair<int, int> num[251];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> (str + 1) >> k, n = strlen(str + 1);
    for (int i = 1; i <= n; i++) num[i] = {str[i] - '0', i};
    sort(num + 1, num + n + 1);
    for (int i = n - k; i; i--)
        for (int j = 1; j <= n; j++)
            if (num[j].second > lim && n - num[j].second >= i - 1) {
                res = res * 10 + num[j].first, lim = num[j].second;
                break;
            }
    cout << res;
    return 0;
}