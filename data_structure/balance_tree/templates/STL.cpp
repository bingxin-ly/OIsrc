#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

// rope 神！
int main()
{
    rope<int> tr;
    unordered_map<int, string> mp;
    string s;

    int n, cnt = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s, mp[cnt] = s,
                  tr.append(cnt++);

    cin >> n;
    for (int i = 1, pos; i <= n; i++)
        cin >> s >> pos, mp[cnt] = s,
                         tr.insert(pos, cnt++);

    cin >> n;
    for (int i = 1, pos; i <= n; i++)
        cin >> pos,
            cout << mp[tr[pos]] << endl;
    return 0;
}