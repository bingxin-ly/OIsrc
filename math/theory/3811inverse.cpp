#include <iostream>
using namespace std;
int inv[(int)4e6];
void write(int x)
{
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    ios::sync_with_stdio(false);
    size_t n, p;
    scanf("%d %d", &n, &p);

    inv[1] = 1, puts("1");
    for (int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p,
        write(inv[i]), putchar('\n');
    return 0;
}
