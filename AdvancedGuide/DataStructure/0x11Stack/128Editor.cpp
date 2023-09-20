#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int q, x, cur1, pre[N], sum, mxv[N]{INT_MIN}, cur2, suf[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> q;
    char op;
    while (q--) {
        cin >> op;
        switch (op) {
            case 'I':
                cin >> x;
                pre[++cur1] = x, sum += x;
                mxv[cur1] = max(mxv[cur1 - 1], sum);
                break;
            case 'D':
                if (cur1) sum -= pre[cur1--];
                break;
            case 'L':
                if (cur1) sum -= pre[cur1], suf[++cur2] = pre[cur1--];
                break;
            case 'R':
                if (cur2) {
                    sum += suf[cur2], pre[++cur1] = suf[cur2--];
                    mxv[cur1] = max(mxv[cur1 - 1], sum);
                }
                break;
            case 'Q':
                cin >> x, cout << mxv[x] << '\n';
                break;
        }
    }
    return 0;
}