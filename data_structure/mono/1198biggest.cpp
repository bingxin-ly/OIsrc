#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int m, p;
    cin >> m >> p;
    vector<int> pos, num{0};
    char op;
    int x, t = 0;
    for (int i = 1; i <= m; i++)
    {
        cin >> op >> x;
        if (op == 'A')
        {
            num.emplace_back((x + t) % p);
            while (!pos.empty() && num[pos.back()] < num.back())
                pos.pop_back();
            pos.emplace_back(num.size() - 1);
        }
        else
            cout << (t = num[*lower_bound(pos.begin(), pos.end(), num.size() - x)]) << '\n';
    }
    return 0;
}