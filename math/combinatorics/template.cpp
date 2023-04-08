// 组合数学
#include <bits/stdc++.h>
typedef long long loong;
using namespace std;

map<int, loong> fac = {{0, 1}, {1, 1}};
loong get_fac(int n)
{
    if (n < 0)
        return -1;
    if (fac.count(n))
        return fac[n];
    // 反向迭代器！！！
    int lastn = fac.crbegin()->first;
    loong lastv = fac.crbegin()->second;
    for (int i = lastn + 1; i <= n; i++)
        lastv *= i, fac[i] = lastv;
    return lastv;
}
// 加法 & 乘法原理

/* 排列就是指从给定个数的元素中取出指定个数的元素进行排序
   组合则是指从给定个数的元素中仅仅取出指定个数的元素，不考虑排序 */
/* 排列数 A(n, m) = n(n - 1)(n - 2)...(n - m + 1) = n!/(n - m)!
   全排列 A(n, n) = n(n - 1)...3 * 2 * 1 = n! */
int A(int n, int m) { return get_fac(n) / get_fac(n - m); };

/* 组合数 C(n, m) = A(n, m) / m! = n!/(m!(n - m))!
   特别地，规定当 m > n 时，C(n, m) = A(n, m) = 0 */
/* 组合数性质：C(n, m) = C(n, n - m)
   C(n, m) = C(n - 1, m - 1) + C(n - 1, m) */
// 规定：C(n, 0)=1 C(n, n)=1 C(0, 0)=1
int C(int n, int m) { return A(n, m) / get_fac(m); };

// 插板法：C(n + k - 1, n)

// 二项式定理
// (a + b)^n = +(i=0 -> n) C(n, i) * a^(n - i) * b^i
// (杨辉三角)

// 卢卡斯定理：C(n, m) mod p = C(n/p, m/p) * C(n mod p, m mod p) mod p
ssize_t lucas(ssize_t n, ssize_t m, ssize_t p)
{
    if (m == 0)
        return 1;
    return C(n % p, m % p) * lucas(n / p, m / p, p) % p;
}

// 容斥原理
/* |∪(i=1->n) Si| = Σ(i)|Si| - Σ(i<j)|Si ∩ Sj| + Σ(i<j<k)|Si ∩ Sj ∩ Sk| - ...
   + (-1)^(m - 1) Σ(ai<ai+1)|∩(i=1 -> m)Sai| + ... + (-1)^(n - 1)|∩(i) Si|
   也即 |∪(i=1 -> n)Si| = Σ(m=1 -> n)(-1)^(m - 1)Σ(ai<ai+1)|∩(i=1 -> m)Sai|
 */
