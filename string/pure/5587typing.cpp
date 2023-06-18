#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;
string formal[N], given[N];
long long n, m, cnt;
int main()
{
    string s;
    while (getline(cin, s), s != "EOF")
    {
        n++;
        for (char i : s)
            if (i == '<')
            {
                if (!formal[n].empty())
                    formal[n].pop_back();
            }
            else
                formal[n].push_back(i);
    }
    while (getline(cin, s), s != "EOF")
    {
        if (++m > n)
            continue;
        for (char i : s)
            if (i == '<')
            {
                if (!given[m].empty())
                    given[m].pop_back();
            }
            else
                given[m].push_back(i);
        for (int i = 0; i < min(given[m].size(), formal[m].size()); i++)
            cnt += formal[m][i] == given[m][i];
    }
    cin >> m;
    cout << (long long)(cnt * 60.0 / m + 0.5);
}
