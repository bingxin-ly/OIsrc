#include <bits/stdc++.h>
using namespace std;

int P;
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
    int p, q, a1, a2, n;
    cin >> p >> q >> a1 >> a2 >> n >> P;
    // P = 99;
    if (n <= 2)
        cout << (n == 1 ? a1 : a2), exit(0);
    matrix base(2, 2), mat(1, 2);
    base[0][1] = q, base[1][0] = 1, base[1][1] = p;
    mat[0][0] = a1, mat[0][1] = a2;
    cout << (mat * fpow(base, n - 1))[0][0] << endl;
    return 0;
}