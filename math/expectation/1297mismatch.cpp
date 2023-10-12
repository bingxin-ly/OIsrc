#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e7 + 9;
int n, A, B, C, a[N];
int main() {
    scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
    for (int i = 2; i <= n; i++)
        a[i] = ((long long)a[i - 1] * A + B) % 100000001;
    for (int i = 1; i <= n; i++)
        a[i] = a[i] % C + 1;

    double ans = 0;
    ans += 1.0 / max(a[1], a[n]);
    for (int i = 2; i <= n; i++)
        ans += 1.0 / max(a[i], a[i - 1]);
    printf("%.3lf", ans);
    return 0;
}