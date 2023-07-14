#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    istream_iterator<int> in(cin), eof;
    vector<int> dat(in, eof), dn, up;
    dn.emplace_back(dat.front());
    for (int i = 1; i < dat.size(); ++i)
    {
        if (dn.back() >= dat[i])
            dn.emplace_back(dat[i]);
        else
            *upper_bound(dn.begin(), dn.end(), dat[i], greater<int>()) = dat[i];
    }
    up.emplace_back(dat.front());
    for (int i = 1; i < dat.size(); ++i)
    {
        if (up.back() < dat[i])
            up.emplace_back(dat[i]);
        else
            *lower_bound(up.begin(), up.end(), dat[i]) = dat[i];
    }
    cout << dn.size() << '\n' << up.size();
    return 0;
}