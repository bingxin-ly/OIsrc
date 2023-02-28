// 打算正反两个最长上升子序列
#include <bits/stdc++.h>
using namespace std;

const int MAX = 110;
int arr[MAX], f[MAX], rf[MAX];
int n, ans;

void get_lis(int *to)
{
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i - 1; j++)
            if (arr[j] < arr[i])
                to[i] = max(to[i], to[j] + 1);
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i], f[i] = 1, rf[i] = 1;
    get_lis(f);
    reverse(arr + 1, arr + n + 1);
    get_lis(rf);
    reverse(rf + 1, rf + n + 1);
    // for (int i = 1; i <= n; i++)
    //     cout << f[i] << ' ' << rf[i] << endl;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i] + rf[i] - 1);
        // cout << f[i] << ' ' << rf[i] << ' ' << ans << endl;
    cout << n - ans << endl;
    return 0;
}