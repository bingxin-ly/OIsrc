#include <bits/stdc++.h>
using namespace std;
struct huge : vector<int> // 用标准库vector做基类，完美解决位数问题，同时更易于实现
{
    // 将低精度转高精度的初始化，可以自动被编译器调用
    // 因此无需单独写高精度数和低精度数的运算函数，十分方便
    huge(int n = 0) // 默认初始化为0，但0的保存形式为空
    {
        push_back(n);
        check();
    }
    huge &check() // 在各类运算中经常用到的进位小函数，不妨内置
    {
        while (!empty() && !back())
            pop_back(); // 去除最高位可能存在的0
        if (empty())
            return *this;
        for (int i = 1; i < size(); ++i)
        {
            (*this)[i] += (*this)[i - 1] / 10;
            (*this)[i - 1] %= 10;
        }
        while (back() >= 10)
        {
            push_back(back() / 10);
            (*this)[size() - 2] %= 10;
        }
        return *this; // 为使用方便，将进位后的自身返回引用
    }
};
// 输入输出
istream &operator>>(istream &is, huge &n)
{
    string s;
    is >> s;
    n.clear();
    for (int i = s.size() - 1; i >= 0; --i)
        n.push_back(s[i] - '0');
    return is;
}
ostream &operator<<(ostream &os, const huge &n)
{
    if (n.empty())
        os << 0;
    for (int i = n.size() - 1; i >= 0; --i)
        os << n[i];
    return os;
}
// 比较，只需要写两个，其他的直接代入即可
// 常量引用当参数，避免拷贝更高效
bool operator!=(const huge &a, const huge &b)
{
    if (a.size() != b.size())
        return 1;
    for (int i = a.size() - 1; i >= 0; --i)
        if (a[i] != b[i])
            return 1;
    return 0;
}
bool operator==(const huge &a, const huge &b)
{
    return !(a != b);
}
bool operator<(const huge &a, const huge &b)
{
    if (a.size() != b.size())
        return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; --i)
        if (a[i] != b[i])
            return a[i] < b[i];
    return 0;
}
bool operator>(const huge &a, const huge &b)
{
    return b < a;
}
bool operator<=(const huge &a, const huge &b)
{
    return !(a > b);
}
bool operator>=(const huge &a, const huge &b)
{
    return !(a < b);
}
// 加法，先实现+=，这样更简洁高效
huge &operator+=(huge &a, const huge &b)
{
    if (a.size() < b.size())
        a.resize(b.size());
    for (int i = 0; i != b.size(); ++i)
        a[i] += b[i];
    return a.check();
}
huge operator+(huge a, const huge &b)
{
    return a += b;
}
// 减法，返回差的绝对值，由于后面有交换，故参数不用引用
huge &operator-=(huge &a, huge b)
{
    if (a < b)
        swap(a, b);
    for (int i = 0; i != b.size(); a[i] -= b[i], ++i)
        if (a[i] < b[i]) // 需要借位
        {
            int j = i + 1;
            while (!a[j])
                ++j;
            while (j > i)
            {
                --a[j];
                a[--j] += 10;
            }
        }
    return a.check();
}
huge operator-(huge a, const huge &b)
{
    return a -= b;
}
// 乘法不能先实现*=，原因自己想
huge operator*(const huge &a, const huge &b)
{
    huge n;
    n.assign(a.size() + b.size() - 1, 0);
    for (int i = 0; i != a.size(); ++i)
        for (int j = 0; j != b.size(); ++j)
            n[i + j] += a[i] * b[j];
    return n.check();
}
huge &operator*=(huge &a, const huge &b)
{
    return a = a * b;
}
// 除法和取模先实现一个带余除法函数
huge divmod(huge &a, const huge &b)
{
    huge ans;
    for (int t = a.size() - b.size(); a >= b; --t)
    {
        huge d;
        d.assign(t + 1, 0);
        d.back() = 1;
        huge c = b * d;
        while (a >= c)
        {
            a -= c;
            ans += d;
        }
    }
    return ans;
}
huge operator/(huge a, const huge &b)
{
    return divmod(a, b);
}
huge &operator/=(huge &a, const huge &b)
{
    return a = a / b;
}
huge &operator%=(huge &a, const huge &b)
{
    divmod(a, b);
    return a;
}
huge operator%(huge a, const huge &b)
{
    return a %= b;
}
// 顺手实现一个快速幂，可以看到和普通快速幂几乎无异
huge pow(const huge &n, const huge &k)
{
    if (k.empty())
        return 1;
    if (k == 2)
        return n * n;
    if (k.front() % 2)
        return n * pow(n, k - 1);
    return pow(pow(n, k / 2), 2);
}

int main()
{
    huge a, b;
    cin >> a >> b;
    cout << a + b << endl
         << (a >= b ? "" : "-") << a - b << endl
         << a * b << endl
         << a / b << endl
         << a % b << endl;
    return 0;
}
