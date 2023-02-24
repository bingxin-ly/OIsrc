#include <iostream>
#include <string>
using namespace std;

char work(string s)
{
    if (s.length() > 1)
    {
        cout << work(s.substr(0, s.length() / 2));
        cout << work(s.substr(s.length() / 2, s.length() / 2));
    }
    if (s == string(s.length(), '0'))
        return 'B';
    else if (s == string(s.length(), '1'))
        return 'I';
    else
        return 'F';
}

int main()
{
    int n;
    string s;
    cin >> n >> s;
    cout << work(s);
    return 0;
}
