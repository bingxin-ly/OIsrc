#include <bits/stdc++.h>
using namespace std;
int A[600], B[600], Alen, Blen;
int C[600], D[600];

void read(int a[], int &len)
{
    int i = 0;
    string s;
    getline(cin, s);
    stringstream ss(s);
    char temp;
    while (ss >> temp)
    {
        a[i] = temp - '0';
        i++;
    }
    len = i;
    reverse(a, a + len);
}
void pls(int a[], int b[], int alen, int blen)
{
    int len = max(alen, blen);
    for (int i = 0; i < len; i++)
    {
        C[i + 1] = (a[i] + b[i] + C[i]) / 10;
        D[i] = (A[i] + B[i] + C[i]) % 10;
    }
    D[len] = C[len];
    int outlen = D[len] == 0 ? len : len + 1;
    reverse(D, D + outlen);
    for (int j = 0; j < outlen; j++)
    {
        cout << D[j];
    }
}
int main()
{
    read(A, Alen);
    read(B, Blen);
    pls(A, B, Alen, Blen);
    return 0;
}