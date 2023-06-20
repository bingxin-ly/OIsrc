#include <bits/stdc++.h>
using namespace std;

string str;

bool decomp(int n)
{
    if (n < 2)
        return str.push_back(n + '0'), n == 1;
    vector<int> val;
    for (int i = 31; i >= 0; i--)
        if (n & (1 << i))
            val.push_back(i);

    for (int i = 0; i < val.size(); i++)
    {
        if (i)
            str.push_back('+');
        str.push_back('2'), str.push_back('(');
        if (decomp(val[i]))
            str.pop_back(), str.pop_back();
        else
            str.push_back(')');
    }
    return false;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    decomp(n);
    cout << str;
    return 0;
}