#include <bits/stdc++.h>
using namespace std;

int len, num;
int tmp[200005], top;
vector<int> vec[500];

pair<int, int> query(int pos)
{
    int idx = 1;
    while (pos > vec[idx].size())
        pos -= vec[idx].size(), idx++;
    return {idx, pos - 1}; // 这里是已经减过 1 的下标
}
void rebuild()
{
    top = 0;
    for (int i = 1; i <= num; i++)
    {
        for (auto j = vec[i].begin(); j < vec[i].end(); j++)
            tmp[++top] = *j;
        vec[i].clear();
    }
    len = sqrt(top);
    for (int i = 1; i <= top; i++)
        vec[(i - 1) / len + 1].emplace_back(tmp[i]);
    num = (top - 1) / len + 1;
}
void insert(int pos, int v)
{
    auto t = query(pos);
    vec[t.first].insert(vec[t.first].begin() + t.second, v);
    if (vec[t.first].size() > 20ul * len)
        rebuild();
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    len = sqrt(n), num = (n - 1) / len + 1; // 很新的统计个数的方法
    for (int i = 1, x; i <= n; i++)
        cin >> x, vec[(i - 1) / len + 1].emplace_back(x);

    for (int op, l, r, c; n--;)
    {
        cin >> op >> l >> r >> c;
        if (!op)
            insert(l, r);
        else
        {
            auto t = query(r);
            cout << vec[t.first][t.second] << '\n';
        }
    }
    return 0;
}