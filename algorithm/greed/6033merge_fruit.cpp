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
        int c;
        while ((c = gc()) < '0' || c > '9')
            ;
        *p = c ^ '0';
        while ((c = gc()) >= '0' && c <= '9')
            *p = *p * 10 + (c ^ '0');
        return *p;
    }
    template <typename T, typename... Args>
    inline void input(T *p, Args... args) { input(p), input(args...); }

    template <typename T>
    inline void write(T x)
    {
        if (x < 0)
            putchar('-'), x = -x;
        if (x > 9)
            write(x / 10);
        putchar(x % 10 + '0');
    }
}
using IO::input;
using IO::write;

int cnt[100010];
queue<long long> q1, q2;
inline long long supply()
{
    long long ret;
    if (q1.empty())
        ret = q2.front(), q2.pop();
    else if (q2.empty())
        ret = q1.front(), q1.pop();
    else
        q1.front() < q2.front() ? (ret = q1.front(), q1.pop()) : (ret = q2.front(), q2.pop());
    return ret;
}
signed main()
{
    int n = input();
    for (int i = 1; i <= n; i++)
        cnt[input()] += 1;
    for (int i = 1; i <= 1e5; i++)
        for (int j = 1; j <= cnt[i]; j++)
            q1.emplace(i);

    long long a, b, ans = 0;
    while (--n)
    {
        a = supply(), b = supply();
        ans += a + b, q2.emplace(a + b);
    }
    cout << ans;
    return 0;
}