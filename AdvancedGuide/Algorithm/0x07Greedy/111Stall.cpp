#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int N = 5e4 + 9;
int n, c, s[N];
struct C {
    int a, b, i;
} a[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].a >> a[i].b, a[i].i = i;
    sort(a + 1, a + n + 1, [](C x, C y) { return x.a < y.a; });
    priority_queue<pii, vector<pii>, greater<>> q;
    for (int i = 1; i <= n; i++) {
        if (!q.empty() && q.top().first < a[i].a)
            s[a[i].i] = q.top().second, q.pop();
        else
            s[a[i].i] = ++c;
        q.emplace(a[i].b, s[a[i].i]);
    }
    cout << c << '\n';
    for (int i = 1; i <= n; i++) cout << s[i] << '\n';
    return 0;
}