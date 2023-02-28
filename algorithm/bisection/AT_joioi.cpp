#include <bits/stdc++.h>
using namespace std;

int n;
char s[1000010];

bool check(int mid)
{
    int is, os, cnt;
    is = os = cnt = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] == 'J' && os)
            os--, cnt++;
        if (s[i] == 'O' && is)
            is--, os++;
        if (s[i] == 'I')
            if (cnt + os + is < mid)
            {
                is++;
            }
            else if (os)
            {
                os--, cnt++;
            }
    }
    return cnt >= mid;
}
int main()
{
    scanf("%d\n%s", &n, s);
    int l = 0, r = n / 3, mid;
    while (l < r)
    {
        mid = (l + r + 1) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
    cout << l << endl;
    return 0;
}