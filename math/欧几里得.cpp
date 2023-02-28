#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

int exgcd(int a, int b, int &x, int &y)
{
    
}

int main()
{
    int x, y;
    cin >> x >> y;
    
}