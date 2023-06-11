// LibreOJ 数列分块入门
#include <bits/stdc++.h>
using namespace std;
namespace IO
{
    const int S = 1e9;
    char B[S], *H = B, *T = B;
    inline int gc() { return (H == T) && (T = (H = B) + fread(B, 1, S, stdin), H == T) ? EOF : *H++; }
    template <typename T = int>
    inline T input(T *p = nullptr)
    {
        static T *o = new T;
        !p && (p = o), *p = 0;
        int q = 1, c;
        while ((c = gc()) < '0' || c > '9')
            (c == '-') && (q = -1);
        *p = c ^ '0';
        while ((c = gc()) >= '0' && c <= '9')
            *p = *p * 10 + (c ^ '0');
        return *p *= q;
    }
    template <typename T, typename... Args>
    inline void input(T *p, Args... args) { input(p), input(args...); }
}
using IO::input;

const int N = 5e4 + 10;
int id[N], len;
long long arr[N], tag[N], sum[N];

void add(int l, int r, long long x)
{
    int st = id[l], ed = id[r];
    if (st == ed)
    {
        for (int i = l; i <= r; i++)
            arr[i] += x, sum[st] += x;
        return;
    }

    for (int i = l; id[i] == st; i++)
        arr[i] += x, sum[st] += x;
    for (int i = st + 1; i <= ed - 1; i++)
        tag[i] += x, sum[i] += len * x;
    for (int i = r; id[i] == ed; i--)
        arr[i] += x, sum[ed] += x;
}

long long query(int l, int r, long long p)
{
    int st = id[l], ed = id[r];
    long long ans = 0;
    if (st == ed)
    {
        for (int i = l; i <= r; i++)
            (ans += arr[i] + tag[st]) %= p;
        return ans;
    }

    for (int i = l; id[i] == st; i++)
        (ans += arr[i] + tag[st]) %= p;
    for (int i = st + 1; i <= ed - 1; i++)
        (ans += sum[i]) %= p;
    for (int i = r; id[i] == ed; i--)
        (ans += arr[i] + tag[ed]) %= p;
    return ans;
}

signed main()
{
    int n = input();
    len = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        input(arr + i);
        id[i] = (i - 1) / len + 1; // 分块主要体现
        sum[id[i]] += arr[i];
    }
    for (int i = 1, op, l, r, c; i <= n; i++)
    {
        input(&op, &l, &r, &c);
        if (!op)
            add(l, r, c);
        else
            printf("%lld\n", query(l, r, c + 1));
    }
    return 0;
}