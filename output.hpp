#include <iostream>
#include <initializer_list>
using std::clog;

void output(std::initializer_list<int> il, bool endl = true)
{
    for (auto i : il)
        clog << i << ' ';
    if (endl)
        clog << std::endl;
}

template <class T>
inline void log(const T &x, const char c = '\n')
{
    std::clog << x << c;
}
template <class T, class... Args>
inline void log(const T &x, const Args &...args)
{
    log(x, ' '), log(args...);
}