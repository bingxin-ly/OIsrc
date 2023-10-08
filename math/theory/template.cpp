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
// lcm(x,y) = xy / gcd(x,y)
int lcm(int a, int b) { return (a * b) / gcd(a, b); }

// 分解质因数
void decomp(int n) {
    static unordered_map<int, int> fac;
    for (int i = 2, u = sqrt(n); i <= u; i++)
        while (!(n % i)) fac[i] += 1, n /= i;
    if (n != 1) fac[n] += 1;
}
/*  对于一个数n，n = p1^a1 * p2^a2 * ... * pk^ak
    则其约数个数为 (a1 + 1)*(a2 + 1)*...*(ak + 1)
    约数和为 (1 + p1 + p1^2 +...+ p1^c1)*...*(1 + pk + pk^2 +...+ pk^ck)  */

// 欧拉函数（单个）：在分解质因数过程中求
int phi(int n) {
    int ans = n;
    for (int i = 2, u = sqrt(n); i <= u; i++)
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
    for (int i = 2, u = sqrt(n); i <= u; ++i)
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
    static int v[N];
    vector<int> pri;
    for (int i = 2; i <= n; i++) {
        if (!v[i]) v[i] = i, pri.emplace_back(i);
        for (int p : pri) {
            if (p > v[i] || p > n / i) break;
            v[i * p] = p;
        }
    }
}

// 欧拉函数：在筛质数的同时计算出phi值
void phi_1(int n) {
    static int phi[N];
    iota(phi + 1, phi + n + 1, 1);
    for (int i = 2; i <= n; i++)
        if (phi[i] == i)
            for (int j = i; j <= n; j += i)
                phi[j] = phi[j] / i * (i - 1);
}
void phi_2(int n) {
    static int v[N], phi[N];
    vector<int> pri;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!v[i]) v[i] = i, phi[i] = i - 1, pri.emplace_back(i);
        for (int p : pri) {
            if (p > v[i] || p > n / i) break;
            v[i * p] = p, phi[i * p] = phi[i] * (i % p ? p - 1 : p);
        }
    }
}

// 费马小定理：若 p 是质数，则对于任意整数 a，有 a ^ p ≡ a (mod p)
// 欧拉定理：若正整数 (a, n) = 1，则 a ^ φ(n) ≡ 1 (mod n)

// Bézout's lemma
// 对于任意整数 a, b，存在一对整数 x, y，使得 ax + by = gcd(a, b)

// 扩展欧几里得
int exgcd(int a, int b, int &x, int &y) {
    if (!b) return x = 1, y = 0, a;
    /* int d = exgcd(b, a % b, x, y);
    int z = x; x = y; y = z - (a / b) * y; */
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
/* void exgcd(int a, int b, int &x, int &y) {
    if (!b) return x = 1, y = 0, void();
    exgcd(b, a % b, y, x), y -= a / b * x;
} */

// 求乘法逆元：在模意义下的倒数
int pow(int a, int b, int p);
int inverse_1(int a, int p) {
    return pow(a, p - 2, p);
}

int inverse_2(int a, int p) {
    int x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

// 求一段连续区间的乘法逆元（递推）
void inverses(int n, int p) {
    int inv[n + 1];
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
}

/*  中国剩余定理 CRT
    1. 计算所有模数的积 M；
    2. 对于第 i 个方程：
        a.计算 m_i = M / p_i；
        b.计算 m_i 在模 p_i 意义下的逆元 t_i；
    3. 方程组的一个特解即为：x = ∑b_i * m_i * t_i */
int CRT(int n, int *b, int *p) {
    int M = 1, X = 0;
    for (int i = 1; i <= n; i++) M *= p[i];
    for (int i = 1; i <= n; i++) {
        int m = M / p[i], x, y;
        exgcd(m, p[i], x, y);
        (X += b[i] * m * x % M) %= M;
    }
    return (X + M) % M;
}

int exCRT(int n, int *a, int *b) {
    int lcm = a[1], ans = b[1];
    for (int i = 2; i <= n; i++) {
        b[i] = (b[i] - ans % a[i] + a[i]) % a[i];
        int x, y, d = exgcd(lcm, a[i], x, y);
        if (b[i] % d) return false;

        int k = x * (b[i] / d) % a[i];
        ans += k * lcm, lcm = lcm / d * a[i];
        ans = (ans % lcm + lcm) % lcm;
    }
    return ans;
}

// Möbius 函数，当 n 包含相同的质因子时，μ(n) = 0；
// 剩下情况若 n 有偶数个质因子，μ(n) = 1；否则 μ(n) = -1
void mobius(int n) {
    static int v[N], miu[N];
    fill(miu + 1, miu + n + 1, 1);
    for (int i = 2; i <= n; i++) {
        if (v[i]) continue;
        miu[i] = -1;
        for (int j = 2 * i; j <= n; j += i) {
            v[j] = 1;
            miu[j] = j / i % i ? -miu[j] : 0;
        }
    }
}