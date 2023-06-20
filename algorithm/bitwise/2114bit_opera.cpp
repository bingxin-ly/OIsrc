#include <bits/stdc++.h>
using namespace std;

int n;
pair<char, int> ops[100005];
int calc(int bit, int num)
{
    for (int i = 1; i <= n; i++)
    {
        int x = ops[i].second >> bit & 1;
        if (ops[i].first == 'A')
            num &= x;
        else if (ops[i].first == 'O')
            num |= x;
        else
            num ^= x;
    }
    return num;
}
signed main()
{
    int m;
    cin >> n >> m;
    char s[4];
    for (int i = 1, x; i <= n; i++)
        cin >> s >> x, ops[i] = {s[0], x};

    int val = 0, ans = 0;
    for (int bit = 29; bit >= 0; bit--)
    {
        int zero = calc(bit, 0), one = calc(bit, 1);
        if (val + (1 << bit) <= m && zero < one)
            val += (1 << bit), ans += one << bit;
        else
            ans += zero << bit;
    }
    cout << ans;
    return 0;
}