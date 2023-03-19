// 排列组合
/* 排列就是指从给定个数的元素中取出指定个数的元素进行排序
   组合则是指从给定个数的元素中仅仅取出指定个数的元素，不考虑排序 */
#include <bits/stdc++.h>
using namespace std;

// 写得最（不）满意的阶乘函数
map<int, size_t> fac = {{0, 1}, {1, 1}};
size_t get_fac(int n)
{
    if (n < 0)
        return -1; // size_t的 -1
    if (fac.find(n) != fac.end())
        return fac[n];
    else
    {
        // 神奇的部分：staitc 时不知道为什么初始值为 1，且cbegin会自动创建元素，所以能正常运行
        size_t lastn = fac.cbegin()->first, lastv = fac.cbegin()->second;
        for (int i = lastn + 1; i <= n; i++)
            lastv *= i, fac[i] = lastv;
        return lastv;
    }
}
// 加法 & 乘法原理

/* 排列数 A(n, m) = n(n - 1)(n - 2)...(n - m + 1) = n!/(n - m)!
   全排列 A(n, n) = n(n - 1)...3 * 2 * 1 = n!

   组合数 C(n, m) = A(n, m) / m! = n!/(m!(n - m))!
   特别地，规定当 m > n 时，C(n, m) = A(n, m) = 0 */

auto A = [](int n, int m)
// { return get_fac(n) / get_fac(n - m); };
{ return m <= n ? get_fac(n) / get_fac(n - m) : 0; };
/* 组合数性质：C(n, m) = C(n, n - m)
   C(n, m) = C(n - 1, m - 1) + C(n - 1, m) */
auto C = [](int n, int m)
{ return A(n, m) / get_fac(m); };

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
