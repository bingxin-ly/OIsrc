#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    int ans = 0;
    while (cin >> s)
        ans += s.size();
    cout << ans;
    return 0;
}