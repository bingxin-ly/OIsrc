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

priority_queue<long long, vector<long long>, greater<>> heap;
signed main()
{
    int n = input();
    for (int i = 1; i <= n; i++)
        heap.emplace(input());
    long long a, b, ans = 0;
    while (heap.size() > 1)
    {
        a = heap.top(), heap.pop(), b = heap.top(), heap.pop();
        ans += a + b, heap.emplace(a + b);
    }
    write(ans);
    return 0;
}