#include <iostream>
#include <algorithm>
using namespace std;

int m, n, ans;
int l, r;
int a[1005], b[1005];
int main()
{
    cin >> m >> n;
    l = r = 0;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        if (a[x] == 0)
        {
            ans++, r++;
            b[r] = x;
            a[x] = 1;
            if (r > m)
            {
                l++;
                a[b[l]] = 0;
            }
        }
    }
    cout << ans;
    return 0;
}
