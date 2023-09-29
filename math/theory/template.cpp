#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e8;
// gcd & lcm
int gcd(int a, int b)  // Euclidean algorithm
{
    return !b ? a : gcd(b, a % b);
    // return __gcd(a, b); C++ 14
    // return std::gcd(a, b); C++ 17 in <numeric>
}
// lcm(x,y) = xy/gcd(x,y)
int lcm(int a, int b) { return (a * b) / gcd(a, b); }

// 分解质（只）因数
void decomp(int n) {
    static unordered_map<int, int> fac;
    for (int i = 2, j = sqrt(n); i <= j; i++)
        while (!(n % i)) fac[i] += 1, n /= i;
    if (n != 1) fac[n] += 1;
}
/*  对于一个数n，n = p1^a1 * p2^a2 * ... * pk^ak
    则其约数个数为 (a1 + 1)*(a2 + 1)*...*(ak + 1)
    约数和为 (1 + p1 + p1^2 +...+ p1^c1)*...*(1 + pk + pk^2 +...+ pk^ck)  */

// 欧拉函数（单个）：在分解质因数过程中求
int phi(int n) {
    int ans = n;
    for (int i = 2, j = sqrt(n); i <= j; i++)
        if (!(n % i)) {
            ans = ans / i * (i - 1);
            while (!(n % i)) n /= i;
        }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

// 素数筛法：暴力、埃筛、欧筛

// 暴力
bool isprime(int n) {
    if (n < 2)
        return 0;
    for (int i = 2, j = sqrt(n); i <= j; ++i)
        if (!(n % i)) return false;
    return true;
}

// 埃氏筛
void sieve(int n) {
    bitset<N> vis;
    vis.set(), vis[0] = vis[1] = 0;
    // fill(vis, vis + n + 1, true), vis[0] = vis[1] = false;
    for (int i = 2, u = sqrt(n); i <= u; i++)
        if (vis[i])
            for (int j = i * i; j <= n; j += i) vis[j] = 1;
}

// 考虑让每个数 x 的最小质因子 p, 让 x 被 (x / p) * p 筛掉
void euler(int n) {
    static int m, fac[N], pri[N];
    memset(fac, 0, sizeof(fac)), m = 0;
    for (int i = 2; i <= n; i++) {
        if (!fac[i]) fac[i] = i, pri[++m] = i;
        for (int j = 1; j <= m; j++) {
            if (pri[j] > fac[i] || pri[j] * i > n) break;
            fac[pri[j] * i] = pri[j];
        }
    }
}

// 欧拉函数：在筛质数的同时计算出phi值
void euler(int n) {
    static int phi[N];
    iota(phi + 2, phi + n + 1, 2);
    for (int i = 2; i <= n; i++)
        if (phi[i] == i)
            for (int j = i; j <= n; j += i)
                phi[j] = phi[j] / i * (i - 1);
}
void euler_phi(int n) {
    static int m, vis[N], pri[N], phi[N];
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) vis[i] = i, pri[++m] = i, phi[i] = i - 1;
        for (int j = 1; j <= m; j++) {
            if (pri[j] > vis[i] || pri[j] > n / i) break;
            vis[i * pri[j]] = pri[j];
            phi[i * pri[j]] = pri[i] * (i % pri[j] ? pri[j] - 1 : pri[j]);
        }
    }
}

// 费马小定理：若 (a,n)，则 a ^ phi(n) ≡ 1 (mod n)

// Bézout's lemma，一个关于最大公约数的定理
// 设 a,b∈ Z∗，则存在整数 x, y, 使得 ax+by=gcd(a,b)

// 扩展欧几里得
// https://img-blog.csdnimg.cn/4e0adc662dd14f509a8204356370c647.png
int exgcd(int a, int b, int &x, int &y) {
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
void exgcd(int a, int b, loong &x, loong &y) {
    if (!b)
        return x = 1, y = 0, void();
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

// 求乘法逆元：在模意义下的倒数
auto inverse = [](int a, int p) { int x, y; exgcd(a, p, x, y); return (x % p + p) % p; };

// 带模快速幂
int fast_pow(size_t a, int k, int m) {
    a %= m;
    size_t res = 1;
    while (k) {
        if (k & 1)
            res = res * a % m;
        a = a * a % m;
        k >>= 1;
    }
    return res;
}
auto inverse = [](int a, int p) { return fast_pow(a, p - 2, p); };  // x是a在mod p下的逆元

// 求一段连续区间的乘法逆元（递推）
void get_inverses(int n, const int p) {
    int inv[n + 1];
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
}

// 线性同余方程求解 ax ≡ b (mod n) Congruence equation
bool solve(int a, int b, int c, int &x, int &y) {
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
int CRT(int k, int *rs,  // 余数
        int *ps)         // 模数
{
    int n = 1, ans = 0;
    for (int i = 1; i <= k; i++)
        n = n * ps[i];
    for (int i = 1; i <= k; i++) {
        int m = n / ps[i], b, y;
        exgcd(m, ps[i], b, y);  // b * m mod ps[i] = 1
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
bool merge_exgcd() {
    static int a, b, A, B, x, y;
    int d = exgcd(a, A, x, y);

    loong c = B - b;
    if (c % d)
        return false;  // 裴蜀定理判是否可行

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
