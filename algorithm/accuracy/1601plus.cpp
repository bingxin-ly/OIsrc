#include <bits/stdc++.h>
using namespace std;
typedef vector<short> integer;

const integer ZERO = integer({0});
inline void read(integer &num)
{
    string s;
    cin >> s;
    num.clear();
    for (auto it = s.rbegin(); it < s.rend(); it++)
        num.push_back(short(*it - '0'));
}
inline void output(const integer &num)
{
    if (num.empty())
        cout << 0;
    for (auto i : num)
        cout << i;
    cout << endl;
}
integer pls(integer &num1, integer &num2, bool reversed = false) // &减少复制，实际只会对位数有影响
{
    integer result;
    int maxlen = max(num1.size(), num2.size());
    num1.resize(maxlen), num2.resize(maxlen), result.resize(maxlen + 1);
    for (int i = 0; i < maxlen; i++)
    {
        result[i] += (num1[i] + num2[i]);
        result[i + 1] = result[i] / 10;
        /* 可以 =也可以 +=，因为当到第 i位的时候第 i + 1位一定是没有被更新过的 */
        result[i] %= 10;
    }
    if (!result.back())
        result.pop_back();
    if (!reversed)
        reverse(result.begin(), result.end());
    return result;
}
integer multp(const integer &num1, const integer &num2)
{
    if (num1 == ZERO || num2 == ZERO)
        return ZERO;
    int maxlen = num1.size() + num2.size();
    integer result, tmp(maxlen);
    for (int i = 0; i < (int)num2.size(); i++)
    {
        tmp.assign(maxlen, 0);
        for (int j = 0, j_to = j + i; j < (int)num1.size(); j++, j_to++)
        {
            tmp[j_to] += num1[j] * num2[i];
            tmp[j_to + 1] = tmp[j_to] / 10;
            tmp[j_to] %= 10;
        }
        result = pls(result, tmp, true);
    }
    if (!result.back())
        result.pop_back();
    reverse(result.begin(), result.end());
    return result;
}

int main()
{
    integer A, B;
    read(A), read(B);
    auto res = multp(A, B);
    output(res);
    return 0;
}