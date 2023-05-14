#include <bits/stdc++.h>
using namespace std;

int main()
{
    int l = 1, r = 1e9;
    while (true)
    {
        int mid = (l + r) >> 1, res;
        cout << mid << endl;
        cin >> res;
        switch (res)
        {
        case 0:
            return 0;
        case 1:
            r = mid - 1;
            break;
        case -1:
            l = mid + 1;
            break;
        }
    }
    return 0;
}