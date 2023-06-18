#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<string> strs;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        strs.push_back(s);
    }

    sort(strs.begin(), strs.end(), [](const string &a, const string &b)
         {  int tot = min(a.size(), b.size()); 
            for (int i = 0; i < tot; i ++)
                if (a[i] != b[i])  
                    return a[i] > b[i]; 
            string c = a + b, d = b + a;
            return c > d; });

    string ans;
    for (const auto &i : strs)
        ans.append(i);

    cout << ans;
    return 0;
}