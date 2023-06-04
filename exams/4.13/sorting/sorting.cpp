#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n, tot[2];
        tot[0] = tot[1] = 0;
        cin >> n;
        for (long long i = 0, tmp; i < n; i++)
            cin >> tmp, tot[i % 2] += tmp;
        cout << (n % 2 || tot[0] <= tot[1] ? "YES" : "NO") << endl;
    }
    return 0;
}