#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int idx, heap[N];

void up(int p) {
    while (p > 1 && heap[p] > heap[p >> 1])
        swap(heap[p], heap[p >> 1]), p >>= 1;
}
void insert(int val) { heap[++idx] = val, up(idx); }
int top() { return heap[1]; }
void down(int p) {
    int s = p << 1;
    while (s <= idx) {
        if (s < idx && heap[s] < heap[s + 1]) s++;
        if (heap[s] > heap[p])
            swap(heap[s], heap[p]), p = s, s = p << 1;
        else
            break;
    }
}
void pop() { heap[1] = heap[idx--], down(1); }
void remove(int p) {
    heap[p] = heap[idx--];
    up(p), down(p);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, o, x;
    cin >> n;
    while (n--) {
        cin >> o;
        if (o == 1)
            cin >> x, insert(-x);
        else if (o == 2)
            cout << -top() << '\n';
        else
            pop();
    }
    return 0;
}