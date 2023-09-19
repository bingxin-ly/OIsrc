#include <bits/stdc++.h>
using namespace std;
using pli = pair<long long, int>;

constexpr int N = 1e6 + 9;
int n, k, a[N], b[N];
long long ans, cnt;

#define ls (p << 1)
#define rs (p << 1 | 1)
int t[N << 2];
void build(int p, int l, int r) {
    if (l == r) return t[p] = a[l], void();
    int m = (l + r) >> 1;
    build(ls, l, m), build(rs, m + 1, r);
    t[p] = min(t[ls], t[rs]);
}
int query(int p, int l, int r, int x, long long v) {
    if (x <= l) {
        if (t[p] > v) return 0;
        if (l == r) return l;
    }
    int m = (l + r) >> 1, ret;
    if (x <= m && (ret = query(ls, l, m, x, v)))
        return ret;
    else
        return query(rs, m + 1, r, x, v);
}

int top, stk[N];
void dfs(int pos, long long res) {
    if (!res && !--cnt) {
        cout << ans << '\n';
        for (int i = 1; i <= top; i++) cout << stk[i] << ' ';
        exit(0);
    }
    for (int i = pos + 1; i <= n; i++) {
        i = query(1, 1, n, i, res);
        if (!i) return;
        stk[++top] = i, dfs(i, res - a[i]), top--;
    }
}
priority_queue<pli, vector<pli>, greater<>> q;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k, k--;
    if (!k) return cout << 0, 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memcpy(b, a, sizeof(a)), sort(b + 1, b + n + 1);

    q.emplace(b[1], 1);
    while (k--) {
        auto [sum, idx] = q.top();
        q.pop();
        if (sum == ans)
            cnt++;
        else
            ans = sum, cnt = 1;
        if (idx != n) {
            sum += b[++idx], q.emplace(sum, idx);
            sum -= b[idx - 1], q.emplace(sum, idx);
        }
    }
    build(1, 1, n), dfs(0, ans);
    return 0;
}