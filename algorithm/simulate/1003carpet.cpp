#include <bits/stdc++.h>
using namespace std;

struct carpet
{
    int a, b, x, y;
    int id;
};

int main()
{
    int n;
    cin >> n;
    vector<carpet> vec;
    for (int i = 1, a, b, x, y; i <= n; i++)
        cin >> a >> b >> x >> y,
            vec.push_back({a, b, x, y, i});
    reverse(vec.begin(), vec.end());

    int x, y;
    cin >> x >> y;
    for (auto &i : vec)
        if (x >= i.a && y >= i.b && x <= i.a + i.x && y <= i.b + i.y)
            cout << i.id << endl, exit(0);
    cout << -1 << endl;
    return 0;
}