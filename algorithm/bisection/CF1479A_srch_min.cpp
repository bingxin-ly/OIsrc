#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> vec(n + 2);
    vec[0] = INT_MAX, vec[n + 1] = INT_MAX;
    int l = 1, r = n, mid;
    while (l < r)
    {
        mid = (l + r) / 2;
        cout << "? " << mid << endl
             << "? " << mid + 1 << endl;
        cin >> vec[mid] >> vec[mid + 1];
        if (vec[mid] < vec[mid + 1])
            r = mid;
        else
            l = mid + 1;
    }
    cout << "! " << l << endl;
}