#include <bits/stdc++.h>
using namespace std;
string str, cutstr;

string get_backstr(string str)
{
    reverse(str.begin(), str.end());
    string ret = str.begin().base();
    return ret;
}
vector<int> prefix_fun(string &s)
{
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main()
{
    int loop;
    cin >> loop;
    while (loop--)
    {
        cin >> str;
        int l = 0, r = str.size() - 1;
        while (str[l] == str[r] && l < r)
            l++, r--;
        cutstr = str.substr(l, r - l + 1);
        string t1 = cutstr + "$" + get_backstr(cutstr),
               t2 = get_backstr(cutstr) + "$" + cutstr;
        auto pre1 = prefix_fun(t1), pre2 = prefix_fun(t2);
        cout << str.substr(0, l);
        if (pre1[t1.size() - 1] > pre2[t2.size() - 1])
            cout << t1.substr(0, pre1[t1.size() - 1]);
        else
            cout << t2.substr(0, pre2[t2.size() - 1]);
        cout << str.substr(r + 1, str.size() - 1) << endl;
    }
    return 0;
}