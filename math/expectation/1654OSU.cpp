#include <bits/stdc++.h>
using namespace std;

double ex, el, el2, P;

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%lf", &P);
        ex = ex + P * (3 * el2 + 3 * el + 1);
        el2 = P * (el2 + 2 * el + 1);
        el = P * (el + 1);
    }
    printf("%.1f", ex);
    return 0;
}
