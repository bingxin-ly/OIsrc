#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 10;
int n, ans;
size_t nxt[MAX];
char str[MAX];

void get_nxt()
{
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j && str[i] != str[j + 1])
            j = nxt[j];
        if (str[i] == str[j + 1])
            j++;
        nxt[i] = j;
    }

}

int main()
{
    cin >> n >> str + 1;
    get_nxt();
    for (int i = 1; i <= n; i++)
    {
        if (nxt[i] == 0) ans = i;
    }
    cout << ans << endl;
    return 0;
}
