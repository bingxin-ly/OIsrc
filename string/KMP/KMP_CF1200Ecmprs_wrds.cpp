#include <bits/stdc++.h>
#include "KMP.h"
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    string words[n + 1];
    for (int i = 1; i <= n; i++)
        cin >> words[i];
    string ans = words[1];
    for (int i = 1; i < n; i++)
    {
        int l = find_occurences(words[i], words[i + 1])[0];
        words[i].erase(0, l);
        ans += words[i];
    }
    cout << ans << endl;
    return 0;
}