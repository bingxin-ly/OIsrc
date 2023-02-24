#include <bits/stdc++.h>
using namespace std;

const int MAX = 8;

void solve(string in, string after)
{
    if (in.size() <= 0)
        return;
    char ch = after[after.size() - 1];
    cout << ch;
    int k = in.find(ch);
    solve(in.substr(0, k), after.substr(0, k));
    solve(in.substr(k + 1), after.substr(k, in.size() - k - 1));
}

int main()
{
    string mid, last;
    cin >> mid >> last;
    solve(mid, last);
    return 0;
}