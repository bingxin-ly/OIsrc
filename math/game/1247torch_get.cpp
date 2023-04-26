#include <bits/stdc++.h>
using namespace std;

int n, a[int(5e5 + 10)];
int main()
{
    cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        cin >> a[i], cnt ^= a[i];
    if (!cnt)
        cout << "lose", exit(0);
    for (int i = 1; i <= n; i++)
        if ((cnt ^ a[i]) < a[i])
        {
            cout << a[i] - (cnt ^ a[i]) << ' ' << i << endl;
            for (int j = 1; j <= n; j++)
                if (j != i)
                    cout << a[j] << ' ';
                else
                    cout << (cnt ^ a[j]) << ' ';
            break;
        }
    return 0;
}