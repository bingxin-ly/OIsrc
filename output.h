#include <initializer_list>
#define r(i, n, k) for (int i = n; i < k; i++) //'<' inside instead of '<='
void output(std::initializer_list<int> il, bool endl = true)
{
    for (auto i : il)
        std::cout << i << ' ';
    if (endl)
        std::cout << std::endl;
}