#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 10;
int n, maxn, times[MAX];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        maxn = max(maxn, x);
        for (int i = 1, up = sqrt(x); i <= up; i++)
            if (x % i == 0)
            {
                times[i]++;
                if (x != i * i)
                    times[x / i]++; // 另一个对面的质数
            }
    }
    int x = maxn;
    for (int k = 1; k <= n; k++)
    {
        while (times[x] < k)
            x--;
        cout << x << endl;
    }
    return 0;
}