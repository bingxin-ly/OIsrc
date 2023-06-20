#include <bits/stdc++.h>
using namespace std;

int n;
string tab[10][10];
unordered_map<char, int> num;

bool check(int i, int j)
{
    int a = 0;
    for (auto c : tab[i][j])
        a = a * (n - 1) + num[c];
    int b = num[tab[i][0][0]] + num[tab[j][0][0]];
    return a == b;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> tab[i][0];
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> tab[i][j];
            num[tab[i][0][0]] += tab[i][j].size() >= 2;
        }
    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= n; j++)
            if (!check(i, j))
                cout << "ERROR!", exit(0);
    for (int i = 2; i <= n; i++)
        cout << tab[i][0] << '=' << num[tab[i][0][0]] << ' ';
    cout << "\n"
         << n - 1;
    return 0;
}