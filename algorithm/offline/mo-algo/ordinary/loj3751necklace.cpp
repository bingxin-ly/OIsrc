#include <bits/stdc++.h>
using namespace std;
namespace IO
{
    const int S = 1 << 20;
    char B[S], *H = B, *T = B;
    inline int gc() { return (H == T) && (T = (H = B) + fread(B, 1, S, stdin), H == T) ? EOF : *H++; }
    template <typename T = int>
    inline T input(T *p = nullptr)
    {
        static T *o = new T;
        !p && (p = o), *p = 0;
        int /* q = 1,  */ c;
        while ((c = gc()) < '0' || c > '9')
            /* (c == '-') && (q = -1) */;
        *p = c ^ '0';
        while ((c = gc()) >= '0' && c <= '9')
            *p = *p * 10 + (c ^ '0');
        return *p /*  *= q */;
    }
    template <typename T, typename... Args>
    inline void input(T *p, Args... args) { input(p), input(args...); }

    template <typename T>
    inline void write(T x)
    {
        (x < 0) && (putchar('-'), x = -x);
        (x > 9) && (write(x / 10), true);
        putchar(x % 10 + '0');
    }
}
using IO::input;
using IO::write;

constexpr int N = 5e4 + 5, M = 2e5 + 5, S = 1e6 + 5;
int n, m, len, res;
int s[N], ans[M], cnt[S];
struct
{
    int id, l, r;
} q[M];
inline int pos(int $) { return ($ - 1) / len + 1/* $ / len */; }
inline void add(int x) { res += !cnt[x], cnt[x] += 1; }
inline void del(int x) { cnt[x] -= 1, res -= !cnt[x]; }

signed main()
{
    input(&n);
    for (int i = 1; i <= n; i++)
        input(s + i);
    input(&m);
    len = n / sqrt(m);
    for (int i = 1; i <= m; i++)
        q[i].id = i, input(&q[i].l, &q[i].r);
    sort(q + 1, q + m + 1, [](const auto &x, const auto &y)
         {  int i = pos(x.l), j = pos(y.l);
            return i < j || (!(j < i) && ((x.r > y.r) ^ (i & 1))); });

    int i = 0, j = 1;
    for (int k = 1; k <= m; k++)
    {
        int l = q[k].l, r = q[k].r;
        while (i < r)
            add(s[++i]);
        while (i > r)
            del(s[i--]);
        while (j < l)
            del(s[j++]);
        while (j > l)
            add(s[--j]);
        ans[q[k].id] = res;
    }

    for (int i = 1; i <= m; i++)
        write(ans[i]), putchar('\n');
    return 0;
}