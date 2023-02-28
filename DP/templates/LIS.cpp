#include <bits/stdc++.h>
using namespace std;

const int MAX = 6e3;
int arr[MAX], f[MAX], ans;

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i], f[i] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= i - 1; j++)
        {
            if (arr[j] < arr[i])
                f[i] = max(f[i], f[j] + 1), ans = max(ans, f[i]);
        }
    }
    cout << ans << endl;
    return 0;
}