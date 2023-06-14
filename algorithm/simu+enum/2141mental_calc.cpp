#include <bits/stdc++.h>
using namespace std;

int arr[100], ans[100];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);
    n = unique(arr, arr + n) - arr;
    reverse(arr, arr + n);
    for (int i = 0; i < n - 2; i++)
        for (int j = i + 1; j < n - 1; j++)
            for (int k = j + 1; k < n; k++)
                if (arr[i] == arr[j] + arr[k])
                    ans[i] = 1;
    int cnt = 0;
    for (auto i : ans)
        cnt += i;
    cout << cnt << endl;
    return 0;
}