#include <bits/stdc++.h>
// 好用的 mod，像 python一样
#define mod(_, _p) ((_ % _p + _p) % _p)
typedef long long loong;
using namespace std;

const int N = 1e8;
// gcd & lcm
inline int gcd(int a, int b) // Euclidean algorithm
{
    return !b ? a : gcd(b, a % b);
    // return __gcd(a, b); ——C++ 14
    // return std::gcd(a, b); ——C++ 17 in <numeric>
}
// lcm(x,y) = xy/gcd(x,y)
inline int lcm(int a, int b) { return (a * b) / gcd(a, b); }

// 分解质（只）因数
vector<int> breakdown(int n)
{
    vector<int> result;
    for (int i = 2, up = sqrt(n); i <= up; i++)
        if (n % i == 0) // 如果 i 能够整除 n，说明 i 为 n 的一个质因子
        {
            while (n % i == 0)
                n /= i;
            result.push_back(i);
        }
    if (n != 1) // 说明再经过操作之后 n 留下了一个素数
        result.push_back(n);
    return result;
}
/*  对于一个数n，n = p1^a1 * p2^a2 * ... * pk ^ ak1
    则其约数个数为 (a1 + 1)(a2 + 1)...(ak + 1)
    https://img-blog.csdnimg.cn/9af18991f0b44982af18aa73ccbf251e.png
    https://img-blog.csdnimg.cn/903dee1c9d7045a78b2b761f1b5e14f2.png */

// 欧拉函数（单个）：在分解质因数过程中求
int phi(int n)
{
    int ans = n;
    for (int i = 2, up = sqrt(n); i <= up; i++)
        if (!(n % i))
        {
            // ans = ans / i * (i - 1);
            ans -= ans / i; // zhx yyds
            while (!(n % i))
                n /= i; // 把质因子是 i的所有情况消掉
        }
    if (n > 1) // 如果除完神奇的发现它自己是质数
        ans -= ans / n;
    return ans;
}

// 素数筛法：暴力、埃氏筛、欧拉筛
// 因为我们在这里都致力于解决这些问题，所以全局的变量：is_prime, primes

bool is_prime[N];
/* 这种称为 **位级压缩** 的方法会使这些位的操作复杂化。
任何位上的读写操作都需要多次算术运算，最终会使算法变慢。 折中：char */
int primes[N];

// 暴力
bool isprime(int n)
{
    if (n < 2)
        return 0;
    for (int i = 2, up = sqrt(n); i <= up; ++i)
        if (n % i == 0)
            return false;
    return true;
}

// 埃氏筛
void sieve(int n) {
    fill(is_prime, is_prime + n + 1, true), is_prime[0] = is_prime[1] = false;
    for (int i = 2, u = sqrt(n); i <= u; i++)
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i) is_prime[j] = false;
}
int eratosthenes(int n)
{
    int cnt = 0;
    // for (int i = 0; i <= n; ++i)
    //     is_prime[i] = 1;
    memset(is_prime, true, (n + 1) /* size通常为 1 */ * sizeof(*is_prime));
    // 让我们先假定所有数都是质数

    is_prime[0] = is_prime[1] = false;
    for (int i = 2, up = sqrt(n); i <= up; ++i)
        /* √n也可（换成up）, 但这样primes会受影响，
        比如100，筛到10即可处理出所有的质数，但11也就不会加到primes里面
        可能要手动处理了（悲） */
        if (is_prime[i])
        {
            // primes[cnt]是i,后置自增运算代表当前素数数量，前置后置自己可以调
            primes[++cnt] = i;
            if (1ll * i * i <= n) // 意义不明的判断/kk
                for (int j = i * i; j <= n; j += i)
                    // 因为从 2 到 i - 1 的倍数我们之前筛过了, 比如 i * 2已经被 2 * i筛过了
                    // 这里直接从 i 的倍数开始，提高了运行速度
                    is_prime[j] = false; // 是i的倍数的均不是素数
        }
    return cnt;
}

bool vis[N];
// 欧拉筛（线性筛），比较常用。所以加一个全局变量应该配得上/hanx
/* 考虑让每个数 x 的最小质因子 p, 让 x 被 (x / p) * p 筛掉 */
void euler(int n)
{
    int cnt = 0;
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
            primes[cnt++] = i; // 注意++
        for (int j = 0; j < cnt && 1ll * i * primes[j] <= n; ++j)
        {
            // if (1ll * i * primes[j] > n)
            //     break;
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0)
                /* i % primes[j] == 0 换言之，i 之前被 primes[j] 筛过了
                由于 primes 里面质数是从小到大的，所以 i乘上其他的质数的结果一定会被
                primes[j]的倍数筛掉，就不需要在这里先筛一次，所以这里直接 break掉就好了 */
                break;
        }
    }
}

// 欧拉函数：通过欧拉筛在筛质数的同时计算出phi值
int phis[N];
int euler_phi(int n)
{
    int cnt = 0;
    // for (int i = 1; i <= n; i++)
    //     is_prime[i] = true;
    memset(is_prime, true, n + 1);
    is_prime[1] = is_prime[0] = false;
    phis[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i])
            primes[++cnt] = i,   // 刚才是后置++现在又是后置++了
                phis[i] = i - 1; // 质数的特殊情况下等于 i - 1
        for (int j = 1, d = i * primes[j]; j <= cnt && d <= n; j++)
        {
            d = i * primes[j];
            is_prime[d] = false;
            phis[d] = phis[i] *
                      (i % primes[j] ? /* phis[primes[j]] */ primes[j] - 1 : primes[j]);
        }
    }
}

// 费马小定理：若 (a,n)，则 a ^ phi(n) ≡ 1 (mod n)

// Bézout's lemma，一个关于最大公约数的定理
// 设 a,b∈ Z∗，则存在整数 x, y, 使得 ax+by=gcd(a,b)

// 扩展欧几里得
// https://img-blog.csdnimg.cn/4e0adc662dd14f509a8204356370c647.png
int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
        return x = 1, y = 0, a;
    /* int d = exgcd(b, a % b, x, y);
    int tmp = x;
    x = y;
    y = tmp - (a / b) * y; */
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
void exgcd(int a, int b, loong &x, loong &y)
{
    if (!b)
        return x = 1, y = 0, void();
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

// 求乘法逆元：在模意义下的倒数
auto inverse = [](int a, int p)
{ int x, y; exgcd(a, p, x, y); return (x % p + p) % p; };

// 带模快速幂
int fast_pow(size_t a, int k, int m)
{
    a %= m;
    size_t res = 1;
    while (k)
    {
        if (k & 1)
            res = res * a % m;
        a = a * a % m;
        k >>= 1;
    }
    return res;
}
auto inverse = [](int a, int p)
{ return fast_pow(a, p - 2, p); }; // x是a在mod p下的逆元

// 求一段连续区间的乘法逆元（递推）
void get_inverses(int n, const int p)
{
    int inv[n + 1];
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
}

// 线性同余方程求解 ax ≡ b (mod n) Congruence equation
bool solve(int a, int b, int c, int &x, int &y)
{
    int d = exgcd(a, b, x, y);
    if (c % d)
        return false;
    int k = c / d;
    x *= k, y *= k;
    return true;
}

// 中国剩余定理 CRT
/*  1.计算所有模数的积 n；
    2.对于第 i 个方程：
        a.计算 m_i = n / n_i；
        b.计算 m_i 在模 n_i 意义下的 逆元 m_i ^ -1；
        c.计算 c_i = m_i * m_i ^ -1（不要对 n_i 取模）。
    3.方程组在模 n 意义下的唯一解为：
    x = sum{i=1 -> K} a_i * c_i (mod n)。*/
// 数据大记得开ssize_t
int CRT(int k, int *rs, // 余数
        int *ps)        // 模数
{
    int n = 1, ans = 0;
    for (int i = 1; i <= k; i++)
        n = n * ps[i];
    for (int i = 1; i <= k; i++)
    {
        int m = n / ps[i], b, y;
        exgcd(m, ps[i], b, y); // b * m mod ps[i] = 1
        ans = (ans + rs[i] * m * b % n) % n;
    }
    // return (ans % n + n) % n;
    return mod(ans, n);
}

/*  x ≡ a1 (mod m1)、x ≡ a2 (mod m2);
    x = m1 * p + a1 = m2 * q + a2;
    m1 * p - m2 * q = a2 - a1 */
/*  解不定方程：可以通过裴蜀定理判断有没有解，
    可以用扩展欧几里得算法(exgcd)给出(k1,k2)的整个解系 */
/*  k1p1 - k2p2 = (r2 - r1) / d
    x = r1 + k1m1 = r1 + (r2 - r1) / d * λ1m1 */
bool merge_exgcd()
{
    static int a, b, A, B, x, y;
    int d = exgcd(a, A, x, y);

    loong c = B - b;
    if (c % d)
        return false; // 裴蜀定理判是否可行

    x = x * c / d % (A / d);
    if (x < 0)
        x += A / d;
    loong p = lcm(a, A);
    b = (a * x + b) % p;
    if (b < 0)
        b += p;
    a = p;
    return true;
}
