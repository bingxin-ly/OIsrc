#include <bits/stdc++.h>
using namespace std;

const int P = 1e4;
struct matrix
{
    int n, m;
    long long **val;
    matrix(int _n = 52, int _m = 52) : n(_n), m(_m)
    {
        val = new long long *[n];
        for (int i = 0; i < n; i++)
            val[i] = new long long[m]();
    }

    static matrix get_unit(int n)
    {
        matrix res(n, n);
        for (int i = 0; i < n; i++)
            res[i][i] = 1;
        return res;
    }

    long long *operator[](int x) { return val[x]; }
    matrix operator*(matrix b)
    {
        int n = this->n, k = this->m, m = b.m;
        matrix res(n, m), bb(b.n, b.m);
        for (int i = 0; i < k; i++)
            for (int j = 0; j < m; j++)
                bb[i][j] = b[j][i];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int l = 0; l < k; l++)
                    res[i][j] = (res[i][j] + val[i][l] * bb[j][l] % P) % P;
        return res;
    }
    friend istream &operator>>(istream &in, matrix &mat)
    {
        for (int i = 0; i < mat.n; i++)
            for (int j = 0; j < mat.m; j++)
                in >> mat.val[i][j];
        return in;
    }

    friend ostream &operator<<(ostream &out, const matrix &mat)
    {
        for (int i = 0; i < mat.n; i++, putchar('\n'))
            for (int j = 0; j < mat.m; j++)
                out << mat.val[i][j] << ' ';
        return out;
    }
};

matrix fpow(matrix ori, long long k)
{
    matrix res = matrix::get_unit(ori.n);
    while (k)
    {
        if (k & 1)
            res = res * ori;
        ori = ori * ori;
        k >>= 1;
    }
    return res;
}

int tmp[50];
matrix ori[14];
int main()
{
    int n, m, st, ed, k;
    cin >> n >> m >> st >> ed >> k;
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        for (int j = 1; j <= 12; j++)
        {
            matrix &mat = ori[j];
            mat.n = mat.m = n;
            mat[u][v] = mat[v][u] = 1;
        }
    }
    ori[0] = matrix::get_unit(n);

    // 读入鳄鱼
    int fish;
    cin >> fish;
    while (fish--)
    {
        int t;
        cin >> t;
        for (int i = 0; i < t; i++)
            cin >> tmp[i];
        tmp[t] = tmp[0];
        for (int i = 1; i <= 12; i++)
            for (int j = 0; j < n; j++)
                ori[i][j][tmp[(i - 1) % t + 1]] = 0;
    }

    // 让我们开始吧
    for (int i = 1; i <= 12; i++)
        ori[0] = ori[0] * ori[i];
    matrix ans = fpow(ori[0], k / 12);
    for (int i = 1; i <= k % 12; i++)
        ans = ans * ori[i];
    cout << ans[st][ed] << endl;
    return 0;
}