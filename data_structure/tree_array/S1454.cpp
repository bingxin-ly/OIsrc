#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 10, MOD = 1e9 + 7;
int h[N], e[N], ne[N], idx;
int n, m, q;
long long p[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

long long qmi(long long a, long long k, long long p) {
    long long res = 1;
    while (k) {
        if (k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

long long sum[N];

struct query {
    int x, y;
    int op, id;
    long long p;
    bool operator<(query& x) const {
        if (y != x.y) return y < x.y;
        return id < x.id;
    }
} ch[N];
int tt;

long long ans[N];

struct ta {
    long long c[N];
#define lowbit(x) x & -x
    void add(int x, long long v) {
        for (; x <= n; x += lowbit(x)) c[x] = (c[x] + v) % MOD;
    }

    long long query(int x) {
        long long res = 0;
        for (; x; x -= lowbit(x)) res = (res + c[x]) % MOD;
        return res;
    }
} bit;

int main() {
    memset(h, -1, sizeof h);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        long long a, b;
        cin >> a >> b;
        p[i] = a * qmi(b, MOD - 2, MOD) % MOD;
        sum[i] = (sum[i - 1] + p[i]) % MOD;
    }

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
        if (a > b) swap(a, b);
        ch[++tt] = {a, b, 0, 0, p[a] * p[b] % MOD};
    }

    for (int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        ans[i] = (sum[r] - sum[l - 1] + MOD) % MOD;
        ch[++tt] = {l - 1, l - 1, -1, i, 0};
        ch[++tt] = {r,     l - 1,  1, i, 0};
        ch[++tt] = {l - 1, r,      1, i, 0};
        ch[++tt] = {r,     r,     -1, i, 0};
    }

    sort(ch + 1, ch + tt + 1);
    for (int i = 1; i <= tt; i++) {
        if (ch[i].op == 0) {
            bit.add(ch[i].x, ch[i].p);
        } else {
            ans[ch[i].id] = (ans[ch[i].id] + ch[i].op * bit.query(ch[i].x) + MOD) % MOD;
        }
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    return 0;
}
