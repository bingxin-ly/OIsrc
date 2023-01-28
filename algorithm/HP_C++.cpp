#include <bits/stdc++.h>
using namespace std;
vector<short> A, B, carry, ans;

void read(vector<short> &input)
{
    string s;
    cin >> s;
    for (char temp: s)
        input.push_back(short(temp - '0'));
    reverse(input.begin(), input.end());
}
void pls(vector<short> &inputA, vector<short> &inputB)
{
    int len = max(inputA.size(), inputB.size());
    inputA.reserve(len), inputB.reserve(len);
    carry.resize(len + 1, 0);
    ans.resize(len + 1, 0);
    for (int i = 0; i < len; i++)
    {
        carry[i + 1] = (inputA[i] + inputB[i] + carry[i]) / 10;
        ans[i] = (A[i] + B[i] + carry[i]) % 10;
        cout << inputA[i] << ' ' << inputB[i] << ' ' << carry[i] << ' ' << ans[i] << endl;
    }
    ans[len] = carry[len];
    if (ans[len] == 0) ans.pop_back();
    reverse(ans.begin(), ans.end());
}
void output(vector<short> &vec)
{
    for (auto i: vec) cout << i;
    cout << endl;
}

int main()
{
    read(A);
    output(A);
    read(B);
    output(B);
    pls(A, B);
    output(ans);
    return 0;
}