#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e3 + 10;
int n, seq1[MAX], seq2[MAX];
int f[MAX][MAX];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> seq1[i];
    for (int i = 1; i <= n; i++)
        cin >> seq2[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (seq1[i] == seq2[j])
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
    cout << f[n][n];
    return 0;
}