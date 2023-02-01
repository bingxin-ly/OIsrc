#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1.1e7 + 10;
char str[MAXN << 1];
int f[MAXN << 1], n, out;

int get_longest_palindrome()
{
    int center = 0, mx = 0;
    // string max_str;
    for (int i = 1; i < n - 1; i++)
    {
        if (i < mx)
            f[i] = min(mx - i, f[2 * center - i]);
        else
            f[i] = 1;
        while (str[i - f[i]] == str[i + f[i]])
            f[i]++;
        if (i + f[i] > mx)
            mx = i + f[i], center = i;
        out = max(out, f[i] - 1);
    }
    return out;
}
int main()
{
    ios::sync_with_stdio(false);
    memset(str, '#', sizeof str);
    str[0] = '$';
    char c;
    int i = 1;
    while (cin >> c)
        str[2 * i] = c, i++;
    str[2 * i] = '^';
    n = 2 * i + 1;
    cout << get_longest_palindrome();
    return 0;
}