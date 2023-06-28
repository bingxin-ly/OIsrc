// 最值
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
inline void chkmax(T &a, const T &b) { a = a > b ? a : b; }
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
inline void chkmin(T &a, const T &b) { a = a < b ? a : b; }

// 快速 IO
#include <iostream>
#include <cstdio>

// 非负整数简化版
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}
inline int read()
{
    int o = 1, p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            o = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0',
        c = getchar();
    return o * p;
}
template <typename T>
inline T read(T *p = nullptr)
{
    static T *o = new T;
    !p && (p = o), *p = 0;
    int q = 1, c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            q = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        *p = *p * 10 + c - '0', c = getchar();
    return *p *= q;
}

namespace IO
{
    const int S = (1 << 20) + 5;
    char B[S], *H, *T;
    inline int gc()
    {
        if (H == T)
            T = (H = B) + fread(B, 1, S, stdin);
        return (H == T) ? EOF : *H++;
        // return (H == T) && (T = (H = B) + fread(B, 1, S, stdin), H == T) ? EOF : *H++;
    }
    inline unsigned int input()
    {
        unsigned int x, ch;
        while ((ch = gc()) < '0' || ch > '9')
            ;
        x = ch ^ '0';
        while ((ch = gc()) >= '0' && ch <= '9')
            x = x * 10 + (ch ^ '0');
        return x;
    }
}
using IO::input;

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
        int q = 1, c;
        while ((c = gc()) < '0' || c > '9')
            (c == '-') && (q = -1);
        *p = c ^ '0';
        while ((c = gc()) >= '0' && c <= '9')
            *p = *p * 10 + (c ^ '0');
        return *p *= q;
    }
    template <typename T, typename... Args>
    inline void input(const T *const &p, const Args &...args) { input(p), input(args...); }

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

/* signed main()
{
    int a = input(), b;
    input(&b);
    write(a + b);
    return 0;
} */

inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

// 调试优化
using std::clog;
template <typename T>
inline void log(const T &x, const char c = '\n') { clog << x << c; }
template <typename T, typename... Args>
inline void log(const T &x, const Args &...args) { log(x, ' '), log(args...); }
