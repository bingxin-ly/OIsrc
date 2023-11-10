#include <bits/stdc++.h>
#define lb(x) lower_bound(num.begin(), num.end(), x) - num.begin() + 1
using namespace std;

constexpr int N = 2e4 + 9;
int n, m, a[N][3], p[N];
int get(int x) { return x == p[x] ? x : p[x] = get(p[x]); }
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m >> m;
    vector<int> num;
    for (int i = 1, l, r; i <= m; i++) {
        string s;
        cin >> l >> r >> s;
        num.emplace_back(a[i][0] = l - 1);
        num.emplace_back(a[i][1] = r);
        a[i][2] = s == "odd";
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    n = num.size(), iota(p + 1, p + 2 * n + 1, 1);
    for (int i = 1; i <= m; i++) {
        int x = lb(a[i][0]), xx = x + n, y = lb(a[i][1]), yy = y + n;
        if (!a[i][2]) {
            if (get(x) == get(yy)) return cout << i - 1, 0;
            p[get(x)] = get(y), p[get(xx)] = get(yy);
        } else {
            if (get(x) == get(y)) return cout << i - 1, 0;
            p[get(x)] = get(yy), p[get(xx)] = get(y);
        }
    }
    cout << m;
    return 0;
}