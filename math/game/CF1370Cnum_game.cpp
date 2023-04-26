#include <bits/stdc++.h>
using namespace std;

const string WIN = "Ashishgup", LOSE = "FastestFinger";
bool is_prime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2, up = sqrt(n); i <= up; i++)
        if (n % i == 0)
            return false;
    return true;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        if (n == 1)
            cout << LOSE << endl;
        else if (n == 2)
            cout << WIN << endl;
        else if (n % 2)
            cout << WIN << endl;
        else
        {
            int cnt = 0;
            while (n % 2 == 0)
                n /= 2, cnt++;
            if (n == 1)
                cout << LOSE << endl;
            else if (is_prime(n))
                if (cnt == 1)
                    cout << LOSE << endl;
                else
                    cout << WIN << endl;
            else
                cout << WIN << endl;
        }
    }
    return 0;
}