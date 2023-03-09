// 不会，植物，百乐
#include <bits/stdc++.h>
using namespace std;

vector<size_t> v;
// map<size_t, int> pows;

void init()
{
    const size_t mx = 1e18;
    const size_t up = pow(mx, 1.0 / 3);
    for (size_t i = 2, cnt; i <= up; i++)
    {
        cnt = 2;
        size_t s = i * i;
        while (s <= mx / i)
        {
            s *= i;
            // pows[s] = ++cnt;
            size_t t = sqrt(s);
            if (t * t != s)
                v.push_back(s);
        }
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}
size_t calc(size_t n)
{
    size_t idx = lower_bound(v.begin(), v.end(), n) - v.begin();
    if (idx < v.size() && v[idx] > n)
        idx--;
    if (idx == v.size())
        idx--;
    return (size_t)sqrt(n) + idx;
}
int main()
{
    int q;
    cin >> q;
    init();
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << calc(r) - calc(l - 1) << endl;
    }
    return 0;
}
