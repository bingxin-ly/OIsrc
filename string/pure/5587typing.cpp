#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<string> formal, given;
    string s;
    while (cin >> s, s != "EOF")
        formal.emplace_back(s);
    while (cin >> s, s != "EOF")
        given.emplace_back(s);

    int ans = 0;
    for (int l = 0; l < formal.size(); l++)
        for (int p = 0; p < formal[l].size(); p++)
            if (given[l][p] == formal[l][p])
                ans++;

    int time;
    cin >> time;
    printf("%.0f", 1.0 * ans / time * 60);
    return 0;
}