#include <stdio.h>
#include <string.h>
#define MAXD 510
#define max(a, b) ((a) > (b) ? (a) : (b))

int A[MAXD], B[MAXD], Alen, Blen;
int C[MAXD], D[MAXD]; // 进位数组以及答案
char tmp[MAXD];

void read(int addend[], int *len)
{
    scanf("%s", tmp);
    *len = strlen(tmp);
    for (int i = *len - 1, j = 0; i >= 0; i--, j++)
        addend[j] = tmp[i] - '0';
}
void pls()
{
    int len = max(Alen, Blen);
    for (int i = 0; i < len; i++)
    {
        C[i + 1] = (A[i] + B[i] + C[i]) / 10;
        D[i] = (A[i] + B[i] + C[i]) % 10;
    }
    D[len] = C[len];
    int outlen = D[len] == 0 ? len : len + 1;
    // reverse(D, D + outlen);
    for (int j = outlen - 1; j >= 0; j--)
        printf("%d", D[j]);
}
int main()
{
    read(A, &Alen), read(B, &Blen);
    pls();
    return 0;
}