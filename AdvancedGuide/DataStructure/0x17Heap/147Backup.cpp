#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, k, s[N];
struct {
    int val, idx, prv, nxt;
} p[N];
struct {
    int val, pos;
} h[N];
int idx, ans;

void up(int i) {
    while (i > 1 && h[i].val < h[i >> 1].val)
        swap(h[i], h[i >> 1]), swap(p[h[i].pos].idx, p[h[i >> 1].pos].idx), i >>= 1;
}
void down(int i) {
    int j = i << 1;
    while (j <= idx) {
        if (j < idx && h[j].val > h[j + 1].val) j++;
        if (h[j].val < h[i].val) {
            swap(h[j], h[i]), swap(p[h[j].pos].idx, p[h[i].pos].idx);
            i = j, j = i << 1;
        } else
            break;
    }
}
void del_heap(int i) {
    if (i == idx) return idx--, void();
    swap(h[i], h[idx]), swap(p[h[i].pos].idx, p[h[idx].pos].idx);
    idx--, up(i), down(i);
}
void del_list(int i) {
    p[p[i].prv].nxt = p[i].nxt;
    p[p[i].nxt].prv = p[i].prv;
}

#define top h[1]
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i < n; i++) {
        p[i] = {s[i + 1] - s[i], ++idx, i - 1, i + 1};
        h[idx] = {s[i + 1] - s[i], i}, up(idx);
    }
    while (k--) {
        ans += top.val;
        if (!p[top.pos].prv || p[top.pos].nxt == n) {
            if (!p[top.pos].prv)
                del_heap(p[p[top.pos].nxt].idx), del_list(p[top.pos].nxt);
            else
                del_heap(p[p[top.pos].prv].idx), del_list(p[top.pos].prv);
            del_list(top.pos), del_heap(1);
        } else {
            int pos = top.pos;
            top.val = p[p[top.pos].prv].val + p[p[top.pos].nxt].val - p[top.pos].val;
            p[top.pos].val = top.val;
            down(1);
            del_heap(p[p[pos].prv].idx), del_heap(p[p[pos].nxt].idx);
            del_list(p[pos].prv), del_list(p[pos].nxt);
        }
    }
    cout << ans;
    return 0;
}