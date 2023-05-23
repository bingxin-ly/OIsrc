#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<int> divisor;
signed main()
{
    int N;
    cin >> N;
    if (N <= 5)
    {
        if (N <= 4)
            puts("0"), exit(0);
        else
            puts("1 4"), exit(0);
    }
    for (int i = 2, up = sqrt(N); i <= up; i++)
        if (N % i == 0)
        {
            if (i % 2)
                divisor.emplace_back(i);
            if (i != N / i && N / i % 2)
                divisor.emplace_back(N / i);
        }
    if (N % 2)
        divisor.emplace_back(N);
    sort(divisor.begin(), divisor.end());

    cout << divisor.size() << ' ';
    for (auto i : divisor)
        cout << N / i * (i - 1) << ' ';
    return 0;
}