#include <bits/stdc++.h>
using namespace std;

string fr, to, s1, s2;
unordered_multimap<string, string> mp;
unordered_set<string> vis;
void bfs()
{
    queue<pair<string, int>> q;
    q.emplace(fr, 0);
    while (!q.empty())
    {
        auto [str, step] = q.front();
        q.pop();

        if (step > 10)
            cout << "NO ANSWER!", exit(0);
        if (str == to)
            cout << step, exit(0);
        for (const auto &[pa, rp] : mp)
        {
            size_t it = 0;
            while ((it = str.find(pa, it)) != string::npos)
            {
                string cpy = str;
                cpy.replace(it, pa.size(), rp); // 第二个参数填 number

                if (!vis.count(cpy)) // 用来去重
                    q.emplace(cpy, step + 1), vis.insert(cpy);
                it++;
            }
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> fr >> to;
    while (cin >> s1 >> s2)
        mp.insert({s1, s2});
    bfs();
    cout << "NO ANSWER!";
    return 0;
}