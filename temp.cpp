#include <bits/stdc++.h>
using namespace std;

template <>
vector<int> &vector<int>::operator=(const vector<int> &src)
{
    for (auto i : src)
        this->emplace_back(i);
    return *this;
}

signed main()
{
    vector<int> a, b{0};
    a = b;
    return 0;
}