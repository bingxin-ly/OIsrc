#include <bits/stdc++.h>
#define chk_max(a, b) a = (a < b ? tree[i][j] = k, b : a)
using namespace std;

const int MAX = 50;
int n, tree[MAX][MAX], f[MAX][MAX];
size_t ans;

void print_ans(int l, int r)
{
    if (l > r)
        return;
    cout << tree[l][r] << ' ';
    print_ans(l, tree[l][r] - 1);
    print_ans(tree[l][r] + 1, r);
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> f[i][i], tree[i][i] = i;
    for (int len = 1; len < n; len++)
        for (int i = 1, j = i + len; j <= n; i++, j++)
        {
            f[i][j] = f[i + 1][j] + f[i][i];
            tree[i][j] = i;
            for (int k = i + 1; k < j; k++)
                chk_max(f[i][j], f[i][k - 1] * f[k + 1][j] + f[k][k]);
        }
    cout << f[1][n] << endl;
    print_ans(1, n);
    return 0;
}