#include <bits/stdc++.h>
using namespace std;

void read(vector<short> &input)
{
    string s;
    cin >> s;
    for (auto c : s)
        input.push_back(short(c - '0'));
    reverse(input.begin(), input.end());
}
void output(vector<short> &vec)
{
    for (auto i : vec)
        cout << i;
    cout << endl;
}
vector<short> pls(vector<short> inputA, vector<short> inputB)
{
    vector<short> result;
    int len = max(inputA.size(), inputB.size());
    inputA.resize(len), inputB.resize(len), result.resize(len + 1);
    for (int i = 0; i < len; i++)
    {
        result[i] += (inputA[i] + inputB[i]);
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }
    if (!result[len])
        result.pop_back();
    reverse(result.begin(), result.end());
    return result;
}

int main()
{
    vector<short> A, B;
    read(A), read(B);
    auto res = pls(A, B);
    output(res);
    return 0;
}