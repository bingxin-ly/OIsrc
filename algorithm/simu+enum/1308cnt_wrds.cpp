#include <bits/stdc++.h>
using namespace std;

int main()
{
    string p, str;
    getline(cin, p), getline(cin, str);
    for (auto &i : p)
        i = tolower(i);
    for (auto &i : str)
        i = tolower(i);
    p = ' ' + p + ' ', str = ' ' + str + ' ';
    if (str.find(p) == string::npos)
        cout << -1, exit(0);
    int a = str.find(p), b = a, s = 0;
    while (b != string::npos)
        s++, b = str.find(p, b + 1);
    cout << s << ' ' << a << endl;
    return 0;
}