#include <bits/stdc++.h>
using namespace std;
vector<short> A, B;

void read(vector<short> &input)
{
    string s;
    cin >> s;
    // input.resize(s.size());
    for (char temp : s)
        input.push_back(short(temp - '0'));
    reverse(input.begin(), input.end());
}
vector<short> pls(vector<short> &inputA, vector<short> &inputB)
{
    vector<short> result;
    int len = max(inputA.size(), inputB.size());
    inputA.resize(len), inputB.resize(len), result.resize(len + 1);
    for (int i = 0; i < len; i++)
    {
        inputA[i] += inputB[i];
        inputA[i + 1] += inputA[i] / 10;
        result[i] = inputA[i] % 10;
    }
    result[len] = inputA[len];
    if (!result[len])
        result.pop_back();
    reverse(result.begin(), result.end());
    return result;
}
void output(vector<short> &vec)
{
    for (auto i : vec)
        cout << i;
    cout << endl;
}

int main()
{
    read(A), read(B);
    auto res = pls(A, B);
    output(res);
    return 0;
}