#include <bits/stdc++.h>
#include "KMP.h"
using namespace std;

int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    for (auto i : find_occurences(s1, s2))
        cout << i + 1 << endl;
    vector<int> next = prefix_fun(s2);
    for (auto i : next)
        cout << i << ' ';
}