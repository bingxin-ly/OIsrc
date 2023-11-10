#include <bits/stdc++.h>
#define lb(v, x) lower_bound(v.begin(), v.end(), x) - v.begin() + 1
using namespace std;

constexpr int N = 2e5 + 9;
int T, n, rel[N][3], p[N];
int get(int x) { return x == p[x] ? x : p[x] = get(p[x]); }
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (cin >> T; T--;) {
        cin >> n;
        vector<int> ele;
        for (int i = 1; i <= n; i++)
            cin >> rel[i][0] >> rel[i][1] >> rel[i][2],
                ele.emplace_back(rel[i][0]), ele.emplace_back(rel[i][1]);
        sort(ele.begin(), ele.end());
        ele.erase(unique(ele.begin(), ele.end()), ele.end());
        iota(p + 1, p + ele.size() + 1, 1);
        for (int i = 1; i <= n; i++) {
            rel[i][0] = lb(ele, rel[i][0]), rel[i][1] = lb(ele, rel[i][1]);
            if (rel[i][2]) p[get(rel[i][0])] = get(rel[i][1]);
        }
        bool ok = true;
        for (int i = 1; i <= n; i++)
            if (!rel[i][2] && get(rel[i][0]) == get(rel[i][1])) ok = false;
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}