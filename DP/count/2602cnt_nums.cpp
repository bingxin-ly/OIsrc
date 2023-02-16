#include <bits/stdc++.h>
// 对于 30% 的数据，保证 a≤b≤10^6；
// 对于 100% 的数据，保证 1≤a≤b≤10^12。
#define int ssize_t // long long! The reason for 30pts!!
using namespace std;

int get(vector<int> num, int l, int r)
{
    int res = 0;
    for (int i = l; i >= r; i--)
        res = 10 * res + num[i];
    return res;
}
int pow10(int x)
{
    int res = 1;
    while (x--)
        res *= 10;
    return res;
    /* if (!x)
        return 1;
    return 10 * pow10(x - 1); */
}
int count(int n, int x)
{
    if (!n)
        return 0;

    vector<int> num;
    while (n)
        num.push_back(n % 10),
            n /= 10;
    n = num.size();

    int res = 0;
    for (int i = n - 1 - !x; i >= 0; i--)
    {
        if (i < n - 1)
        {
            res += get(num, n - 1, i + 1) * pow10(i);
            if (!x)
                res -= pow10(i);
        }

        if (num[i] == x)
            res += get(num, i - 1, 0) + 1;
        else if (num[i] > x)
            res += pow10(i);
    }
    return res;
}

signed main()
{
    int a, b;
    cin >> a >> b;

    for (int i = 0; i < 10; i++)
        cout << count(b, i) - count(a - 1, i) << ' ';
    cout << endl;
    /* while (cin >> a >> b)
    {
        if (a > b)
            swap(a, b);

        for (int i = 0; i < 10; i++)
            cout << count(b, i) - count(a - 1, i) << ' ';
        cout << endl;
    } */
    return 0;
}