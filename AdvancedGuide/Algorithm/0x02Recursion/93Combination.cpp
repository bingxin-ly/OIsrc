#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> v;
void dfs(int x) {
    if (v.size() > m || v.size() + (n - x + 1) < m)
        return;
    if (x == n + 1) {
        for (auto i : v)
            cout << i << ' ';
        cout << '\n';
        return;
    }
    v.emplace_back(x), dfs(x + 1), v.pop_back();  // 选 x 放前面，使字典序小的在前
    dfs(x + 1);
}

signed main() {
    cin >> n >> m, dfs(1);
    return 0;
}

// non-recursive
// 1. 把 k 个 1 和 n-k 个 0 塞进 vector 然后 next_permutation
// 2. GospersHack
void GospersHack(int n, int k) {
    int cur = (1 << k) - 1, lim = (1 << n);
    while (cur < lim) {
        int lb = cur & -cur, rit = cur + lb;
        cur = ((rit ^ cur) >> 2) / lb | rit;
        // cur = ((rit ^ cur) >> (__builtin_ctz(lb) + 2)) | rit;
    }
}