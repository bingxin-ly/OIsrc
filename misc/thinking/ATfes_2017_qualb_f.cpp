#include <bits/stdc++.h>
using namespace std;

signed main()
{
    int a, b, c;
    cin >> a >> b >> c;
    multiset<string> s;
    while (a--)
        s.insert("a");
    while (b--)
        s.insert("b");
    while (c--)
        s.insert("c");

    while (s.size() > 1)
    {
        auto st = s.begin(), ed = --s.end();
        s.insert(*st + *ed), s.erase(st), s.erase(ed);
    }
    cout << *s.begin();
    return 0;
}