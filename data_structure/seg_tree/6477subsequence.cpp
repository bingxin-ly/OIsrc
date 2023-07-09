#include <bits/stdc++.h>
using namespace std;
namespace IO
{
    const int S = 1 << 20;
    char B[S], *H = B, *T = B;
    inline int gc() { return (H == T) && (T = (H = B) + fread(B, 1, S, stdin), H == T) ? EOF : *H++; }
    inline int input(int &p)
    {
        static int c;
        p = 0;
        while ((c = gc()) < '0' || c > '9')
            ;
        p = c ^ '0';
        while ((c = gc()) >= '0' && c <= '9')
            p = p * 10 + (c ^ '0');
        return p;
    }

    inline void write(int x)
    {
        (x < 0) && (putchar('-'), x = -x);
        (x > 9) && (write(x / 10), true);
        putchar(x % 10 + '0');
    }
}
using IO::input;
using IO::write;

constexpr int N = 1e6 + 5, MOD = 1e9 + 7;
int n, arr[N], lst[N];
struct
{
    int squ, sum, tag;
} t[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p)
{
    t[p].squ = (t[ls].squ + t[rs].squ) % MOD;
    t[p].sum = (t[ls].sum + t[rs].sum) % MOD;
}
void pushdown(int p, int l, int r)
{
    if (t[p].tag)
    {
        int mid = (l + r) >> 1, val = t[p].tag;
        (t[ls].squ += (2ll * t[ls].sum * val % MOD + 1ll * val * val * (mid - l + 1) % MOD) % MOD) %= MOD;
        (t[ls].sum += 1ll * (mid - l + 1) * val % MOD) %= MOD;
        (t[ls].tag += val) %= MOD;

        (t[rs].squ += (2ll * t[rs].sum * val % MOD + 1ll * val * val * (r - mid) % MOD) % MOD) %= MOD;
        (t[rs].sum += 1ll * (r - mid) * val % MOD) %= MOD;
        (t[rs].tag += val) %= MOD;

        t[p].tag = 0;
    }
}
void update(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
    {
        (t[p].squ += (2ll * t[p].sum % MOD + (r - l + 1)) % MOD) %= MOD;
        (t[p].sum += r - l + 1) %= MOD;
        (t[p].tag += 1) %= MOD;
        return;
    }
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(ls, l, mid, ql, qr);
    if (qr > mid)
        update(rs, mid + 1, r, ql, qr);
    pushup(p);
}

signed main()
{
    input(n);
    for (int i = 1; i <= n; i++)
        input(arr[i]);
    vector<int> nums(arr + 1, arr + n + 1);
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (int i = 1; i <= n; i++)
        arr[i] = lower_bound(nums.begin(), nums.end(), arr[i]) - nums.begin();

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        update(1, 1, n, lst[arr[i]] + 1, i), lst[arr[i]] = i;
        (ans += t[1].squ) %= MOD;
    }
    write(ans);
    return 0;
}