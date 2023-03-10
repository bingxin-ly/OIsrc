#include <bits/stdc++.h>
using namespace std;

int main()
{
    int q;
    cin >> q;
    size_t n;
    while (q--)
    {
        cin >> n;
        cout << (n != 1 ? n * (n - 1) : 1) << endl;
    }
    return 0;
}