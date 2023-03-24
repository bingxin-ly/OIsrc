#include <bits/stdc++.h>
using namespace std;

int main()
{
    random_device rd;
    // uniform_int_distribution<int> dist(0, 9);
    // cout << dist(rd) << endl;

    mt19937 rand(rd()); // time(0)
    for (int i = 1; i <= 100; i++)
        cout << rand() << endl;
    return 0;
}
