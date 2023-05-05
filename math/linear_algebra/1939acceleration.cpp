#include <bits/stdc++.h>
using namespace std;

const int P = 1e9 + 7;
struct matrix
{
    int n, m;
    long long **val;
    matrix(int _n, int _m) : n(_n), m(_m)
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

matrix fpow(matrix a, long long k)
{
    matrix res = matrix::get_unit(a.n);
    while (k)
    {
        if (k & 1)
            res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        if (n <= 3)
        {
            puts("1");
            continue;
        }
        matrix mat(3, 3);
        mat[0][0] = mat[0][2] = mat[1][0] = mat[2][1] = 1;
        cout << fpow(mat, n)[1][0] << endl;
    }
    return 0;
}