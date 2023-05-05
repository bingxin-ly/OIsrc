// 最值
#define max(_a, _b) ((_a > _b) ? _a : _b)
#define chkmax(_a, _b) _a = ((_b > _a) ? _b : _a)
#undef chkmax
template <typename T>
inline void chkmax(T &a, T b) { a = max(a, b); }
#define min(_a, _b) ((_a < _b) ? _a : _b)
#define chkmin(_a, _b) _a = ((_b < _a) ? _b : _a)
#undef chkmin
template <typename T>
inline void chkmin(T &a, T b)
{
    a = min(a, b);
}

// 快读 & 快输
#define get(_) _ = read()
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
int read()
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
void write(int x)
{
    if (x < 0)
        putchar('-'),
            x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

// 调试优化
#include <iostream>
using std::clog;

template <class T>
inline void log(const T &x, const char c = '\n')
{
    clog << x << c;
}
template <class T, class... Args>
inline void log(const T &x, const Args &...args)
{
    log(x, ' '), log(args...);
}
