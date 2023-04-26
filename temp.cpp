#include <bits/stdc++.h>
using namespace std;

class fraction
{
    typedef __int128 int128;
    int128 up, down;
    static int128 gcd(int128 a, int128 b)
    {
        if (!b)
            return a;
        return gcd(b, a % b);
    }
    static int128 lcm(int128 a, int128 b)
    {
        return a * b / gcd(a, b);
    }

public:
    fraction &divide()
    {
        int128 d = gcd(up, down);
        up /= d;
        down /= d;
        return *this;
    }
    fraction(long long _up, long long _down) : up(_up), down(_down) { divide(); }

    fraction operator+(const fraction &other)
    {
        int tmp = lcm(down, other.down);
        up = up * (tmp / down) + other.up * (tmp / other.down);
        down = tmp;
        return *this;
    }

    fraction operator*(const fraction &other)
    {
        up *= other.up, down *= other.down;
        return divide();
    }

    fraction operator*(const int other)
    {
        up *= other / gcd(other, down);
        return *this;
    }

    fraction operator/(const fraction &other)
    {
        up *= other.down, down *= other.up;
        return divide();
    }

    fraction operator/(const int other)
    {
        down *= other;
        return divide();
    }
    friend ostream &operator<<(ostream &out, const fraction &f)
    {
        return out << (long long)f.up << '/' << (long long)f.down;
    }
};
int main()
{
    fraction f(1, 2);
    cout << f / fraction(2, 3) * fraction(6, 4) << endl;
    return 0;
}