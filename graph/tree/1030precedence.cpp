#include <bits/stdc++.h>
using namespace std;

void solve(string a, string b) {
    if (a.size() <= 0) return;
    char ch = b.back();
    cout << ch;
    int k = a.find(ch);
    solve(a.substr(0, k), b.substr(0, k));
    solve(a.substr(k + 1), b.substr(k, a.size() - k - 1));
}

int main() {
    string mid, last;
    cin >> mid >> last;
    solve(mid, last);
    return 0;
}