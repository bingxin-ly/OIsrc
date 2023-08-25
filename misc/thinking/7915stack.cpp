#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 5;
int n, a[N];
char res[N];

bool process(int l1, int r1, int l2, int r2)
{
    for (int i = 1; i < n >> 1; i++)
        if (l1 <= r1 && (l1 < r1 && a[l1] == a[r1] || l2 <= r2 && a[l1] == a[l2]))
        {
            if (l1 < r1 && a[l1] == a[r1])
                ++l1, --r1, res[i] = 'L', res[n - i - 1] = 'L';
            else
                ++l1, ++l2, res[i] = 'L', res[n - i - 1] = 'R';
        }
        else if (l2 <= r2 && (l1 <= r1 && a[r2] == a[r1] || (l2 < r2 && a[l2] == a[r2])))
        {
            if (l1 <= r1 && a[r2] == a[r1])
                --r2, --r1, res[i] = 'R', res[n - i - 1] = 'L';
            else
                --r2, ++l2, res[i] = 'R', res[n - i - 1] = 'R';
        }
        else
            return false;
    return true;
}
void solve()
{
    cin >> n, n <<= 1;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int p1 = 1, p2 = n;
    while (a[++p1] != a[1])
        ;
    while (a[--p2] != a[n])
        ;
    if (process(2, p1 - 1, p1 + 1, n))
        cout << 'L' << (res + 1) << "L\n";
    else if (process(1, p2 - 1, p2 + 1, n - 1))
        cout << 'R' << (res + 1) << "L\n";
    else
        cout << "-1\n";
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve(), memset(res, 0, sizeof(res));
    return 0;
}