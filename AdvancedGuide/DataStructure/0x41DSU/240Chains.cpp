#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1.5e5 + 9;
int n, k, p[N];
int get(int x) { return x == p[x] ? x : p[x] = get(p[x]); }
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k, iota(p + 1, p + 3 * n + 1, 1);
    int cnt = 0;
    for (int d, x, y; k--;) {
        cin >> d >> x >> y;
        if (x > n || y > n)
            cnt += 1;
        else if (d == 1) {
            if (get(x + n) == get(y) || get(y + n) == get(x))
                cnt += 1;
            else
                p[get(x)] = get(y), p[get(x + n)] = get(y + n), p[get(x + n + n)] = get(y + n + n);
        } else {
            if (x == y || get(x) == get(y) || get(y + n) == get(x))
                cnt += 1;
            else
                p[get(x + n)] = get(y), p[get(x)] = get(y + n + n), p[get(x + n + n)] = get(y + n);
        }
    }
    cout << cnt;
    return 0;
}