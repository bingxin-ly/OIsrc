#include <bits/stdc++.h>
using namespace std;

const int P = 13331;
const int M = 998244353; // 有时会卡数据
size_t get_hash(string &str)
{
    size_t hsh = 0;
    for (auto i : str)
        hsh = (hsh * P + i) % M;
    return hsh;
}

int main()
{
    int n;
    cin >> n;
    set<size_t> s;
    string str;
    while (n--)
    {
        cin >> str;
        s.insert(get_hash(str));
    }
    cout << s.size() << endl;
    return 0;
}