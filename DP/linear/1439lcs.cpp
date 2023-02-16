#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 10;
int n, len;
int a[MAX], b[MAX];
int m[MAX], f[MAX];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], m[a[i]] = i;
    for (int i = 1; i <= n; i++)
        cin >> b[i], f[i] = INT_MAX;
    len = 0;
    for (int i = 1; i <= n; i++)
    {
        int l = 0, r = len, mid;
        if (m[b[i]] > f[len])
            f[++len] = m[b[i]];
        else
        {
            while (l < r)
            {
                mid = (l + r) >> 1;
                if (f[mid] > m[b[i]])
                    r = mid;
                else
                    l = mid + 1;
            }
            f[l] = min(m[b[i]], f[l]);
        }
    }
    cout << len;
    return 0;
}